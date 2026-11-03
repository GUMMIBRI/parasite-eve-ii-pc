//! Memory-card containers: PsyZ directories, raw slot files, `.mcs` single
//! saves and full card images (`.srm` / `.mcr` / `.mcd` / `.gme`).
//!
//! All formats share the PS1 card conventions (128-byte sectors, 8 KB files,
//! 15 user slots). Non-PE2 files and container headers are preserved
//! byte-for-byte; only whole PE2 slot files are read or written.

use std::fs;
use std::path::{Path, PathBuf};

use anyhow::{bail, Context, Result};

use crate::layout::{FILE_SIZE, MAX_CARD_SLOTS, PRODUCT_CODE};

/// 128 KB raw PS1 card image.
pub const PS1_CARD_SIZE: usize = 0x20000;
/// DexDrive `.gme` header preceding the card image.
pub const GME_HEADER_SIZE: usize = 0x0F40;
/// `.mcs` single save: 128-byte directory header + one 8 KB file.
pub const MCS_SAVE_SIZE: usize = FILE_SIZE + 0x80;

/// One PE2 save file with the card filename it came from.
#[derive(Debug, Clone)]
pub struct SlotFile {
    /// Card filename without extension, e.g. `BASLUS-01042______A` (20 chars).
    pub filename: String,
    /// The 0x2000-byte slot file contents.
    pub data: Vec<u8>,
}

/// Which slot letter a filename occupies (`'A'..='O'`), if any.
pub fn slot_letter(filename: &str) -> Option<usize> {
    let rest = filename.strip_prefix(PRODUCT_CODE)?;
    let letter = rest.chars().last()?;
    let index = (letter as u8).wrapping_sub(b'A') as usize;
    (index < MAX_CARD_SLOTS && rest.len() <= 15).then_some(index)
}

/// Build a card filename for a slot index (`0 -> ...A`, `14 -> ...O`).
pub fn filename_for_slot(index: usize) -> String {
    let mut name = PRODUCT_CODE.to_string();
    while name.len() < 19 {
        name.push('_');
    }
    name.push((b'A' + index as u8) as char);
    name
}

fn looks_like_pe2_file(data: &[u8]) -> bool {
    data.len() == FILE_SIZE && data.starts_with(b"SC")
}

fn read_pe2_file(path: &Path) -> Result<SlotFile> {
    let data = fs::read(path).with_context(|| format!("reading {}", path.display()))?;
    if !looks_like_pe2_file(&data) {
        bail!("{} is not a PE2 save file (expected {} bytes starting with 'SC')", path.display(), FILE_SIZE);
    }
    Ok(SlotFile { filename: path.file_name().unwrap_or_default().to_string_lossy().into_owned(), data })
}

/// A memory card container holding up to 15 PE2 slots.
#[derive(Debug, Clone)]
pub enum CardContainer {
    /// Directory of per-slot files (`bu00/`, `bu10/`).
    Directory { path: PathBuf, slots: Vec<Option<SlotFile>> },
    /// One raw 0x2000-byte slot file.
    RawFile(SlotFile),
    /// `.mcs`: 128-byte header + one slot file.
    Mcs { header: Vec<u8>, slot: SlotFile },
    /// Full card image, optionally with a DexDrive header.
    CardImage { path: PathBuf, gme_header: Option<Vec<u8>>, raw: Vec<u8> },
}

impl CardContainer {
    /// Open any supported container.
    pub fn open(path: impl AsRef<Path>) -> Result<Self> {
        let path = path.as_ref();
        if path.is_dir() {
            return Self::open_directory(path);
        }
        let data = fs::read(path).with_context(|| format!("reading {}", path.display()))?;
        match data.len() {
            FILE_SIZE if data.starts_with(b"SC") => Ok(Self::RawFile(SlotFile {
                filename: path.file_name().unwrap_or_default().to_string_lossy().into_owned(),
                data,
            })),
            MCS_SAVE_SIZE if &data[0..2] == b"SC" && data[0x80..0x82].iter().eq(b"SC".iter()) => {
                Ok(Self::Mcs { header: data[..0x80].to_vec(), slot: SlotFile { filename: decode_mcs_filename(&data)?, data: data[0x80..].to_vec() } })
            }
            PS1_CARD_SIZE => Ok(Self::CardImage { path: path.to_path_buf(), gme_header: None, raw: data }),
            n if n == PS1_CARD_SIZE + GME_HEADER_SIZE && data.starts_with(b"123-456-789") => Ok(Self::CardImage {
                path: path.to_path_buf(),
                gme_header: Some(data[..GME_HEADER_SIZE].to_vec()),
                raw: data[GME_HEADER_SIZE..].to_vec(),
            }),
            _ => bail!("{}: unrecognized container size {}", path.display(), data.len()),
        }
    }

    fn open_directory(path: &Path) -> Result<Self> {
        let mut slots: Vec<Option<SlotFile>> = vec![None; MAX_CARD_SLOTS];
        let mut entries: Vec<PathBuf> = fs::read_dir(path)
            .with_context(|| format!("listing {}", path.display()))?
            .filter_map(|e| e.ok().map(|e| e.path()))
            .collect();
        entries.sort();
        for entry in entries {
            if !entry.is_file() {
                continue;
            }
            let name = entry.file_name().unwrap_or_default().to_string_lossy().into_owned();
            if let Some(index) = slot_letter(&name) {
                slots[index] = Some(read_pe2_file(&entry)?);
            }
        }
        Ok(Self::Directory { path: path.to_path_buf(), slots })
    }

    /// The PE2 slot files this container exposes, with their slot indices.
    pub fn slots(&self) -> Vec<(usize, SlotFile)> {
        match self {
            Self::Directory { slots, .. } => slots
                .iter()
                .enumerate()
                .filter_map(|(i, s)| s.as_ref().map(|f| (i, f.clone())))
                .collect(),
            Self::RawFile(file) => vec![(slot_letter(&file.filename).unwrap_or(0), file.clone())],
            Self::Mcs { slot, .. } => vec![(slot_letter(&slot.filename).unwrap_or(0), slot.clone())],
            Self::CardImage { raw, .. } => read_card_image_slots(raw),
        }
    }

    /// Replace one slot's data in the container.
    pub fn write_slot(&mut self, index: usize, data: &[u8]) -> Result<()> {
        if index >= MAX_CARD_SLOTS {
            bail!("slot index {} out of range", index);
        }
        if data.len() != FILE_SIZE {
            bail!("slot data must be {} bytes", FILE_SIZE);
        }
        match self {
            Self::Directory { path, slots } => {
                let file_path = path.join(filename_for_slot(index));
                fs::write(&file_path, data).with_context(|| format!("writing {}", file_path.display()))?;
                slots[index] = Some(SlotFile { filename: filename_for_slot(index), data: data.to_vec() });
            }
            Self::RawFile(file) => {
                file.data = data.to_vec();
                // A raw file has no directory name to derive the slot from when absent.
                if slot_letter(&file.filename).is_none() {
                    file.filename = filename_for_slot(index);
                }
            }
            Self::Mcs { slot, .. } => {
                slot.data = data.to_vec();
                if slot_letter(&slot.filename).is_none() {
                    slot.filename = filename_for_slot(index);
                }
            }
            Self::CardImage { raw, .. } => {
                let (offset, _) = card_slot_region(index).ok_or_else(|| anyhow::anyhow!("slot not addressable"))?;
                raw[offset..offset + FILE_SIZE].copy_from_slice(data);
            }
        }
        Ok(())
    }

    /// Persist container-level changes (card images, `.mcs`, raw files).
    pub fn save(&self) -> Result<()> {
        match self {
            Self::Directory { .. } => Ok(()), // slot writes already hit the filesystem
            Self::RawFile(file) => {
                let _ = file;
                bail!("raw files are written via write_slot_to_path")
            }
            Self::Mcs { .. } => bail!("use save_mcs to persist"),
            Self::CardImage { path, gme_header, raw } => {
                let mut out = gme_header.clone().unwrap_or_default();
                out.extend_from_slice(raw);
                fs::write(path, out).with_context(|| format!("writing {}", path.display()))
            }
        }
    }
}

/// Decode the card filename embedded in a `.mcs` directory header.
fn decode_mcs_filename(data: &[u8]) -> Result<String> {
    let bytes = &data[0x0A..0x0A + 20];
    let name: String = bytes.iter().map(|&b| if b.is_ascii_graphic() || b == b'_' { b as char } else { '_' }).collect();
    Ok(name)
}

/// Locate PE2 slot files inside a raw card image by scanning the directory
/// entries (0x40-byte entries after the 2 KB card header).
fn read_card_image_slots(raw: &[u8]) -> Vec<(usize, SlotFile)> {
    // Directory layout: entry i at 0x0800 + i*0x40; file content i at 0x2000 + i*0x2000.
    let mut found = Vec::new();
    for index in 0..MAX_CARD_SLOTS {
        let entry = 0x0800 + index * 0x40;
        if entry + 0x40 > raw.len() {
            break;
        }
        if raw[entry] != b'S' || raw[entry + 1] != b'C' {
            continue;
        }
        let filename: String = raw[entry + 0x0A..entry + 0x0A + 20]
            .iter()
            .map(|&b| if b.is_ascii_graphic() || b == b'_' { b as char } else { '_' })
            .collect();
        let content = 0x2000 + index * 0x2000;
        if content + FILE_SIZE > raw.len() {
            break;
        }
        if raw[content..content + 2] == *b"SC" {
            found.push((
                slot_letter(&filename).unwrap_or(index),
                SlotFile { filename, data: raw[content..content + FILE_SIZE].to_vec() },
            ));
        }
    }
    found
}

/// Card-image byte region for a slot: `(content_offset, allocated_bytes)`.
fn card_slot_region(index: usize) -> Option<(usize, usize)> {
    if index >= MAX_CARD_SLOTS {
        return None;
    }
    Some((0x2000 + index * 0x2000, 0x2000))
}

/// Write a slot file to an arbitrary path (export).
pub fn write_slot_file(path: impl AsRef<Path>, data: &[u8]) -> Result<()> {
    if data.len() != FILE_SIZE {
        bail!("slot data must be {} bytes", FILE_SIZE);
    }
    fs::write(&path, data).with_context(|| format!("writing {}", path.as_ref().display()))
}

#[cfg(test)]
mod tests {
    use super::*;

    /// A syntactically valid slot file: 'SC' magic + size.
    #[allow(dead_code)]
    pub fn synthetic_slot(seed: u8) -> Vec<u8> {
        let mut data = vec![0u8; FILE_SIZE];
        data[0] = b'S';
        data[1] = b'C';
        data[0x210] = seed; // inside the save image, past the checksum header
        data
    }

    #[test]
    fn slot_letters() {
        assert_eq!(slot_letter("BASLUS-01042A"), Some(0));
        assert_eq!(slot_letter("BASLUS-01042______O"), Some(14));
        assert_eq!(slot_letter("BASLUS-01042P"), None);
        assert_eq!(slot_letter("SCUS-94163"), None);
    }

}