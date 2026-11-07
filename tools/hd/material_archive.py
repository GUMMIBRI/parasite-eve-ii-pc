#!/usr/bin/env python3
"""Transfer verified material folders without private native reference caches.

Archives are not loadable game packs or artwork/distribution approval. Unpack
with a separately trusted SHA-256, acquire local references, then hydrate.
"""
import argparse
import hashlib
import json
import os
from pathlib import Path
import stat
import struct
import tempfile
import zipfile
import zlib

from PIL import Image
from install_pack import PAYLOAD, digest
from material_bundle import HASH, MANIFEST, publish, read_bundle, separate_paths

MAX_FILES = 20001
MAX_FILE_BYTES = 128*1024*1024
MAX_TOTAL_BYTES = 64*1024**3


def entries(archive):
    files = archive.infolist()
    if not 1 <= len(files) <= MAX_FILES:
        raise ValueError('Invalid archive file count')
    names = set()
    total = 0
    for entry in files:
        mode = stat.S_IFMT(entry.external_attr >> 16)
        if (entry.filename in names or entry.orig_filename != entry.filename or
                (entry.filename != MANIFEST and not PAYLOAD.fullmatch(entry.filename)) or
                entry.is_dir() or mode not in (0, stat.S_IFREG) or entry.flag_bits & 1 or
                entry.compress_type not in (zipfile.ZIP_STORED, zipfile.ZIP_DEFLATED)):
            raise ValueError('Invalid, duplicate or non-regular archive entry')
        if not 0 < entry.file_size <= MAX_FILE_BYTES:
            raise ValueError('Invalid archive entry size')
        total += entry.file_size
        names.add(entry.filename)
    if MANIFEST not in names or total > MAX_TOTAL_BYTES:
        raise ValueError('Missing material manifest or excessive archive size')
    return files


def create(source, output):
    separate_paths(source, output)
    if output.exists() or output.is_symlink():
        raise ValueError('Output already exists; archives are immutable')
    original = read_bundle(source)
    manifest = (source/MANIFEST).read_bytes()
    if json.loads(manifest) != original:
        raise ValueError('Material manifest changed before archiving')
    if (len(original['files']) + 1 > MAX_FILES or len(manifest) > MAX_FILE_BYTES or
            len(manifest) + sum(entry['size'] for entry in original['files'].values()) > MAX_TOTAL_BYTES):
        raise ValueError('Material bundle exceeds archive limits')
    output.parent.mkdir(parents=True, exist_ok=True)
    with tempfile.TemporaryDirectory(prefix='.pe2-archive-', dir=output.parent) as temporary:
        staged = Path(temporary)/'materials.zip'
        with zipfile.ZipFile(staged, 'w', allowZip64=True) as archive:
            for name in sorted([MANIFEST, *original['files']]):
                raw = manifest if name == MANIFEST else (source/name).read_bytes()
                if name != MANIFEST:
                    expected = original['files'][name]
                    if len(raw) != expected['size'] or hashlib.sha256(raw).hexdigest() != expected['sha256']:
                        raise ValueError('Material changed while archiving')
                entry = zipfile.ZipInfo(name, date_time=(1980, 1, 1, 0, 0, 0))
                entry.create_system = 3
                entry.external_attr = (stat.S_IFREG | 0o644) << 16
                archive.writestr(entry, raw, compress_type=zipfile.ZIP_STORED)
        with zipfile.ZipFile(staged) as archive:
            entries(archive)
        if read_bundle(source) != original or (source/MANIFEST).read_bytes() != manifest:
            raise ValueError('Material bundle changed while archiving')
        checksum = digest(staged)
        # The staged file is complete. Hard-link publication cannot overwrite
        # a concurrently created output, unlike a POSIX rename.
        os.link(staged, output)
    return dict(id=original['id'], version=original['version'], sha256=checksum)


def unpack(source, output, expected_sha256):
    separate_paths(source, output)
    if not isinstance(expected_sha256, str) or not HASH.fullmatch(expected_sha256):
        raise ValueError('Expected a trusted lowercase SHA-256')
    if (source.is_symlink() or not source.is_file() or
            not 0 < source.stat().st_size <= MAX_TOTAL_BYTES + 32*1024*1024):
        raise ValueError('Missing or invalid material archive')
    if digest(source) != expected_sha256:
        raise ValueError('Material archive SHA-256 mismatch')

    def write(staged):
        with zipfile.ZipFile(source) as archive:
            inventory = entries(archive)
            for entry in inventory:
                # Names are flat, allowlisted and unique; never use extractall.
                raw = archive.read(entry)
                if len(raw) != entry.file_size:
                    raise ValueError('Truncated material archive entry')
                (staged/entry.filename).write_bytes(raw)
        read_bundle(staged)
        if digest(source) != expected_sha256:
            raise ValueError('Material archive changed during unpacking')
    publish(output, write)
    return read_bundle(output)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    commands = parser.add_subparsers(dest='command', required=True)
    pack = commands.add_parser('create')
    pack.add_argument('materials', type=Path)
    pack.add_argument('--output', type=Path, required=True)
    restore = commands.add_parser('unpack')
    restore.add_argument('archive', type=Path)
    restore.add_argument('--sha256', required=True, help='Separately trusted archive checksum')
    restore.add_argument('--output', type=Path, required=True)
    args = parser.parse_args()
    try:
        if args.command == 'create':
            result = create(args.materials, args.output)
            print(f'{result["id"]} {result["version"]}: SHA-256 {result["sha256"]}')
        else:
            result = unpack(args.archive, args.output, args.sha256)
            print(f'{result["id"]} {result["version"]}: {len(result["files"])} verified material files')
    except (OSError, ValueError, KeyError, TypeError, struct.error, zipfile.BadZipFile,
            zlib.error, Image.DecompressionBombError) as error:
        parser.exit(1, str(error) + '\n')


if __name__ == '__main__':
    main()
