# PE2 Save Editor (`save-editor/`)

Save editor for Parasite Eve II (PS1 / PC PsyZ port), modeled after the PE1
editor in `~/Projects/parasite-eve-pc/save-editor`: an egui GUI plus a clap
CLI over one shared save model.

## Save format

The format is taken directly from the decompilation (`src/main/mc.c`,
`include/main/mc_types.h`). One card file is one 8 KB block (`BASLUS-01042<A..O>`):

| Section | Offset | Copy size | Extent | Contents |
| --- | --- | --- | --- | --- |
| 0 header | 0x0000 | 0x200 | 0x200 | Card file header ('S','C', Shift-JIS title, CLUT, icons); no checksum |
| 1 save | 0x0200 | 0x944 | 0x1300 | `McSaveData` live copy + backup |
| 2 player | 0x1500 | 0x040 | 0x0080 | `PlayerStatus::save` + backup |
| 3..7 flags | 0x1580.. | bank | banks ×2 | Per-stage game-flag banks, live + backup |
| 8 nibble | 0x1C00 | 0x100 | 0x0200 | `GameFlagNibbleBank` live + backup |

Checksums (all low-16-bit, stored with ones' complement `0xFFFF - sum`):

- every checksummed record: signed-byte sum of its payload (`(s8)byte`)
- `headerChecksum`: signed-byte sum of the 56 bytes from `location`, with the
  pair itself pre-set to `0` / `0xFFFF` before summing (contribution -2)
- `titleChecksum`: signed-byte sum of the 0x200-byte card file header
- `bufferChecksum`: unsigned low-byte sum of the live sections' checksums;
  its pair is zeroed before section checksums are written, and written last

`SlotData::refresh_checksums` replicates the game's write order exactly:
title pair → header pair → zeroed buffer pair → section checksums → summary.

## Layout

- `src/layout.rs` — section table and file offsets
- `src/checksum.rs` — the four checksum algorithms and verifiers
- `src/save.rs` — typed `SaveImage` over the 0x944-byte record with offset
  accessors; `SaveTransfer` for lossless JSON round-trips of typed fields
- `src/card.rs` — containers: PsyZ directory, raw 0x2000 file, `.mcs`,
  `.srm`/`.mcr`/`.mcd`, DexDrive `.gme`
- `src/edit.rs` — `SlotData`: whole-file edits + checksum maintenance/verify
- `src/cli.rs` — CLI: `list`, `inspect`, `verify`, `edit`, `export`,
  `import`, `extract`
- `src/gui.rs` — egui app: slot browser, tabs (Summary, Character,
  Inventory, Weapons, Parasite Energy, Progression, Options)

Unknown bytes are never modeled or rewritten: edits go through the typed
accessors, JSON transfer carries only typed fields, and both operate on the
raw image so everything else is preserved verbatim.

## Usage

```sh
cargo run -- list bu00
cargo run -- verify bu00 --slot 2
cargo run -- edit bu00 --slot 2 --set exp=99999 --set mark-items-seen=384
cargo run -- export bu00 --slot 2 -o slot2.json
cargo run -- import bu00 --slot 2 -i slot2.json
cargo run            # GUI
```

## Verification

`cargo test` covers layout chaining, checksum round-trips, edit + verify,
corruption detection and transfer round-trips. Save files are never
rewritten in place without a fresh checksum refresh.