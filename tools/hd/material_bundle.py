#!/usr/bin/env python3
"""Separate atlas material planes from private owner-disc reference planes.

This does not certify artwork ownership or approval. Material bundles retain
layout metadata, cannot be loaded directly, and must be hydrated using a local
reference cache. Never distribute the reference cache or hydrated runtime pack.
"""
import argparse
import hashlib
import json
import os
from pathlib import Path
import re
import shutil
import struct
import tempfile

from PIL import Image
from install_pack import PAYLOAD, TOKEN, create, digest, read_manifest, validate_layout

MANIFEST = 'pe2-materials.json'
HASH = re.compile(r'[0-9a-f]{64}\Z')


def reference_digest(image):
    image = image.convert('RGBA')
    return hashlib.sha256(b'pe2-reference-plane-v1\0' +
                          struct.pack('<II', *image.size) + image.tobytes()).hexdigest()


def separate_paths(*paths):
    resolved = [p.resolve() for p in paths]
    for i, first in enumerate(resolved):
        for second in resolved[i + 1:]:
            if first == second or first in second.parents or second in first.parents:
                raise ValueError('Source, material, cache and output directories must be separate')


def read_reference(path, size, key):
    if path.is_symlink() or not path.is_file():
        raise ValueError('Missing private reference plane: ' + key)
    if not 0 < path.stat().st_size <= 64*1024*1024:
        raise ValueError('Invalid private reference size')
    with Image.open(path) as image:
        if image.format != 'PNG' or list(image.size) != list(size) or reference_digest(image) != key:
            raise ValueError('Private reference plane changed')
        return image.convert('RGBA')


def store_reference(cache, reference, key):
    cached = cache/(key + '.png')
    if cached.exists() or cached.is_symlink():
        read_reference(cached, reference.size, key)
        return
    # Publish a complete content-addressed file without replacing an existing
    # entry. Interrupted writes stay in the private temporary directory.
    with tempfile.TemporaryDirectory(prefix='.pe2-reference-', dir=cache) as temporary:
        staged = Path(temporary)/'plane.png'
        reference.save(staged)
        try:
            os.link(staged, cached)
        except FileExistsError:
            read_reference(cached, reference.size, key)


def publish(destination, writer):
    if destination.exists() or destination.is_symlink():
        raise ValueError('Output already exists; existing artifacts are immutable')
    destination.parent.mkdir(parents=True, exist_ok=True)
    with tempfile.TemporaryDirectory(prefix='.pe2-material-', dir=destination.parent) as temporary:
        staged = Path(temporary)/'payload'
        staged.mkdir()
        writer(staged)
        if destination.exists() or destination.is_symlink():
            raise ValueError('Output already exists')
        staged.rename(destination)


def read_bundle(root):
    path = root/MANIFEST
    if path.is_symlink():
        raise ValueError('Material manifest must not be a symlink')
    data = json.loads(path.read_text())
    if not isinstance(data, dict) or data.get('format') != 'pe2-material-planes-v1':
        raise ValueError('Unknown material bundle format')
    if any(not isinstance(data.get(k), str) or not TOKEN.fullmatch(data[k]) for k in ['id', 'version']):
        raise ValueError('Invalid bundle identity or version')
    files, atlases = data.get('files'), data.get('atlases')
    if not isinstance(files, dict) or not 1 <= len(files) <= 20000 or not isinstance(atlases, dict):
        raise ValueError('Invalid material inventory')
    if {p.name for p in root.iterdir()} != {MANIFEST, *files}:
        raise ValueError('Unlisted file or directory in material bundle')
    if set(atlases) != {name for name in files if name.endswith('.png')} or not atlases:
        raise ValueError('Incomplete material atlas inventory')
    for name, entry in files.items():
        if not PAYLOAD.fullmatch(name) or not isinstance(entry, dict):
            raise ValueError('Invalid material filename or record')
        if (type(entry.get('size')) is not int or not 0 < entry['size'] <= 128*1024*1024 or
                not isinstance(entry.get('sha256'), str) or not HASH.fullmatch(entry['sha256'])):
            raise ValueError('Invalid material size or hash')
        file = root/name
        if file.is_symlink() or not file.is_file() or file.stat().st_size != entry['size'] or digest(file) != entry['sha256']:
            raise ValueError('Missing or changed material: ' + name)
        if name in atlases:
            record = atlases[name]
            if not isinstance(record, dict) or not isinstance(record.get('reference'), str) or not HASH.fullmatch(record['reference']):
                raise ValueError('Invalid reference identity')
            size = record.get('size')
            if (not isinstance(size, list) or len(size) != 2 or any(type(n) is not int for n in size) or
                    size[0] != 1088 or not 68 <= size[1] <= 4080 or size[1] % 68):
                raise ValueError('Invalid material plane dimensions')
            with Image.open(file) as image:
                if image.format != 'PNG' or list(image.size) != size:
                    raise ValueError('Material plane dimensions disagree')
                image.verify()
    def check_atlas(name, size):
        plane = atlases.get(name)
        if plane is None or tuple([plane['size'][0], plane['size'][1]*2]) != size:
            raise ValueError('Material plane does not match descriptor layout')
    referenced = validate_layout(files, lambda name: (root/name).read_bytes(), check_atlas)
    if referenced != set(atlases):
        raise ValueError('Unreferenced material plane')
    return data


def split(source, materials, cache):
    separate_paths(source, materials, cache)
    original = read_manifest(source)
    expected_atlases = {name[:-6] + '.png' for name in original['files'] if name.endswith('.pe2bg')}
    for name in original['files']:
        if name.endswith('.pe2fg'):
            atlas = struct.unpack_from('<Q', (source/name).read_bytes(), 16)[0]
            expected_atlases.add(f'{atlas:016x}.fg.png')
    if expected_atlases != {name for name in original['files'] if name.endswith('.png')}:
        raise ValueError('Unreferenced atlas cannot be classified for export')

    def write(staged):
        files, atlases = {}, {}
        cache.mkdir(parents=True, exist_ok=True)
        for name in sorted(original['files']):
            target = staged/name
            if name.endswith('.png'):
                with Image.open(source/name) as image:
                    image = image.convert('RGBA')
                    height = image.height//2
                    material = image.crop((0, 0, image.width, height))
                    reference = image.crop((0, height, image.width, image.height))
                key = reference_digest(reference)
                store_reference(cache, reference, key)
                material.save(target)
                atlases[name] = dict(size=list(material.size), reference=key)
            else:
                shutil.copyfile(source/name, target)
            files[name] = dict(size=target.stat().st_size, sha256=digest(target))
        data = dict(format='pe2-material-planes-v1', id=original['id'], version=original['version'],
                    files=files, atlases=atlases,
                    scope='Reference planes excluded; material authorship, metadata and distribution still require review.')
        (staged/MANIFEST).write_text(json.dumps(data, indent=2) + '\n')
        read_bundle(staged)
        if read_manifest(source) != original:
            raise ValueError('Source pack changed during separation')
    publish(materials, write)
    return read_bundle(materials)


def hydrate(materials, cache, output):
    separate_paths(materials, cache, output)
    original = read_bundle(materials)

    def write(staged):
        for name in original['files']:
            if name not in original['atlases']:
                shutil.copyfile(materials/name, staged/name)
                continue
            record = original['atlases'][name]
            path = cache/(record['reference'] + '.png')
            reference = read_reference(path, record['size'], record['reference'])
            with Image.open(materials/name) as material:
                material = material.convert('RGBA')
            atlas = Image.new('RGBA', (material.width, material.height*2))
            atlas.paste(material, (0, 0))
            atlas.paste(reference, (0, material.height))
            atlas.save(staged/name)
        create(staged, original['id'], original['version'])
        if read_bundle(materials) != original:
            raise ValueError('Material bundle changed during hydration')
    publish(output, write)
    return read_manifest(output)


def acquire(materials, cache, native_root, foreground_roots=()):
    """Prepare only expected reference planes from private native exports."""
    from reference_sources import (background_reference, foreground_context,
                                   foreground_exports, foreground_reference)
    separate_paths(materials, cache, native_root, *foreground_roots)
    original = read_bundle(materials)
    plans = {}
    for name in sorted(original['files']):
        if name.endswith('.pe2bg'):
            plans.setdefault(name[:-6] + '.png', []).append(('background', (materials/name).read_bytes()))
        elif name.endswith('.pe2fg'):
            metadata = (materials/name).read_bytes()
            atlas_key = struct.unpack_from('<Q', metadata, 16)[0]
            plans.setdefault(f'{atlas_key:016x}.fg.png', []).append(('foreground', metadata))
    exports = None
    cache.mkdir(parents=True, exist_ok=True)
    records = []
    for name, choices in plans.items():
        spec = original['atlases'][name]
        path = cache/(spec['reference'] + '.png')
        if path.exists() or path.is_symlink():
            read_reference(path, spec['size'], spec['reference'])
            records.append(dict(atlas=name, reference=spec['reference'], cached=True))
            continue
        matched = None
        for kind, metadata in choices:
            if kind == 'background':
                plane = background_reference(metadata, native_root)
            else:
                if exports is None:
                    exports = foreground_exports(foreground_roots)
                export = exports.get(foreground_context(metadata))
                if export is None:
                    continue
                plane = foreground_reference(metadata, *export)
            if list(plane.size) == spec['size'] and reference_digest(plane) == spec['reference']:
                matched = plane
                break
        if matched is None:
            raise ValueError('No matching native export for reference plane: ' + name)
        store_reference(cache, matched, spec['reference'])
        records.append(dict(atlas=name, reference=spec['reference'], cached=False))
    if read_bundle(materials) != original:
        raise ValueError('Material bundle changed during reference acquisition')
    return dict(id=original['id'], version=original['version'], references=records, complete=True)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    commands = parser.add_subparsers(dest='command', required=True)
    export = commands.add_parser('split')
    export.add_argument('source', type=Path)
    export.add_argument('--materials', type=Path, required=True)
    export.add_argument('--private-cache', type=Path, required=True)
    restore = commands.add_parser('hydrate')
    restore.add_argument('materials', type=Path)
    restore.add_argument('--private-cache', type=Path, required=True)
    restore.add_argument('--output', type=Path, required=True)
    verify = commands.add_parser('verify')
    verify.add_argument('materials', type=Path)
    prepare = commands.add_parser('acquire')
    prepare.add_argument('materials', type=Path)
    prepare.add_argument('--private-cache', type=Path, required=True)
    prepare.add_argument('--native-root', type=Path, required=True, help='Local <key>.rgb555 background exports')
    prepare.add_argument('--foreground-sources', type=Path, action='append', default=[],
                         help='A foreground audit directory or parent containing one directory per context; repeatable')
    args = parser.parse_args()
    try:
        if args.command == 'split':
            data = split(args.source, args.materials, args.private_cache)
        elif args.command == 'hydrate':
            data = hydrate(args.materials, args.private_cache, args.output)
        elif args.command == 'acquire':
            data = acquire(args.materials, args.private_cache, args.native_root, args.foreground_sources)
            print(f'{data["id"]} {data["version"]}: {len(data["references"])} verified reference planes')
            return
        else:
            data = read_bundle(args.materials)
        print(f'{data["id"]} {data["version"]}: {len(data["files"])} verified files')
    except (OSError, ValueError, TypeError, KeyError, struct.error) as error:
        parser.exit(1, str(error) + '\n')


if __name__ == '__main__':
    main()
