#!/usr/bin/env python3
"""Emit a data-free manifest of the game data the build reads from the user's extraction.

For every generated include (build/include/assets/*.inc) whose header names a source package,
record: symbol file, source package, kind and offset in the package. For every package, record where it
lives on the disc (disc file number and chunk name from the CDF tree in tools/peassets/asset_data.py) and
the sha1 of its decoded bytes, so a runtime loader can locate and verify it.

Usage: gen_asset_manifest.py [build/include/assets] > manifest.json   (contains no game data)
"""
import importlib.util, json, re, sys
from pathlib import Path


def load(name):
    s = importlib.util.spec_from_file_location(name, f'tools/peassets/{name}.py')
    m = importlib.util.module_from_spec(s)
    s.loader.exec_module(m)
    return m


data = load('asset_data')
inc_dir = Path(sys.argv[1] if len(sys.argv) > 1 else 'build/include/assets')

# package asset id -> (disc file number, chunk name)
where = {}


def walk(node, path):
    if isinstance(node, dict):
        for k, v in node.items():
            walk(v, path + [k])
    elif isinstance(node, str) and 'chunks' in path:
        i = path.index('chunks')
        f = path[i - 1]
        if f.startswith('file'):
            where.setdefault(node, (path[:i - 1], f, path[i + 1]))


walk(data.TREE, [])

hdr = re.compile(r'/\* Generated from assets/USA/pe2pkg/(\w+)\.pe2pkg; (.+?) at (0x[0-9A-Fa-f]+)\. \*/')
entries, pkgs, unmapped = [], {}, set()
for f in sorted(inc_dir.glob('*.inc')):
    with open(f) as fh:
        m = hdr.match(fh.readline())
    if not m:
        continue
    pkg, kind, off = m.group(1), m.group(2), int(m.group(3), 16)
    entries.append({'file': f.name, 'package': pkg, 'kind': kind, 'offset': off})
    if pkg not in pkgs:
        rec = data.ASSETS.get(pkg)
        loc = where.get(pkg)
        if rec is None or loc is None:
            unmapped.add(pkg)
        else:
            pkgs[pkg] = {'sha1': rec['sha1'], 'disc_file': int(loc[1][4:]), 'chunk': loc[2]}
json.dump({'packages': pkgs, 'entries': entries, 'unmapped_packages': sorted(unmapped)}, sys.stdout, indent=1)
print(f'{len(entries)} entries, {len(pkgs)} packages, {len(unmapped)} unmapped', file=sys.stderr)
