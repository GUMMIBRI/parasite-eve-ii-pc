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
# Packages the catalog does not name (the type store holds their inflated form): stages.json says which
# disc file and chunk each stored file stands for.
try:
    stages = json.load(open('assets/USA/stages.json'))
except OSError:
    stages = {}
tree_files = {}
for folder in data.TREE.values():
    for fname, frec in folder.get('files', {}).items():
        tree_files[fname] = frec
stored = {}
for skey, stage in stages.items():
    for fname, chunks in stage.get('files', {}).items():
        for cname, c in chunks.items():
            path = c.get('path', '')
            if path.startswith('pe2pkg/') and fname in tree_files:
                chunk = cname.rsplit('.', 1)[0]
                stored[path[len('pe2pkg/'):-len('.pe2pkg')]] = (tree_files[fname]['id'], chunk, None, int(skey[5:]))

tree_folders = {}
for root in data.TREE.values():
    for dname, drec in root.get('folders', {}).items():
        tree_folders[dname] = drec
for skey, stage in stages.items():
    for dname, files in stage.get('folders', {}).items():
        drec = tree_folders.get(dname)
        if drec is None:
            continue
        for fname, chunks in files.items():
            frec = drec.get('files', {}).get(fname)
            for cname, c in chunks.items():
                path = c.get('path', '')
                if frec is not None and path.startswith('pe2pkg/'):
                    stored[path[len('pe2pkg/'):-len('.pe2pkg')]] = (frec['id'], cname.rsplit('.', 1)[0], drec['id'], int(skey[5:]))

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
        if rec is not None and loc is not None:
            where_path = loc[0]
            entry = {'stage': where_path[0], 'sha1': rec['sha1'], 'disc_file': int(loc[1][4:]), 'chunk': loc[2]}
            if 'folders' in where_path:
                dname = where_path[where_path.index('folders') + 1]
                entry['disc_folder'] = data.TREE[where_path[0]]['folders'][dname]['id']
            pkgs[pkg] = entry
        elif pkg in stored:
            pkgs[pkg] = {'stage': stored[pkg][3], 'disc_file': stored[pkg][0], 'chunk': stored[pkg][1], **({'disc_folder': stored[pkg][2]} if stored[pkg][2] is not None else {})}
        else:
            unmapped.add(pkg)
json.dump({'packages': pkgs, 'entries': entries, 'unmapped_packages': sorted(unmapped)}, sys.stdout, indent=1)
print(f'{len(entries)} entries, {len(pkgs)} packages, {len(unmapped)} unmapped', file=sys.stderr)
