#!/usr/bin/env python3
"""Describe every generated model/animation/collision include as (package, byte offset, size, element type).

Run with the project's venv Python (ninja_config imports spimdisasm):
    venv/bin/python tools/port/gen_asset_parts.py > parts.json

The description holds layout facts only (where in which package a part lives and what it is), never game data.
A runtime loader copies or converts `size` bytes at `offset` of the package into the part's array; `op` says how:
  copy        the bytes are the array (element types without pointers have the same layout on the host)
  rotation    4-byte packed words -> three signed fields of 11, 10 and 11 bits (AnimationPackedRotation)
  grid_table  32-bit PS1 addresses -> host pointers into the grid's cell lists (the table's own `cells` part)
"""
import json, sys
from pathlib import Path

sys.path.insert(0, '.')
import ninja_config as nc
from tools.buildsteps import gen_animation_inc, gen_collision_inc, gen_model_inc

V = 'USA'
parts = []


def add(kind, package, load, source, comps, out_files, extra=None):
    byname = {Path(f).name: f for f in out_files}
    for comp, f in zip(comps, out_files):
        rec = {'file': Path(f).name, 'kind': kind, 'package': package, 'load': load, 'source': source,
               'part': comp['name'], 'offset': comp['offset'], 'size': comp['size'],
               'type': comp.get('type', 'SVECTOR' if comp['name'] in ('normals', 'verts') else
                                'GridFace' if comp['name'] == 'faces' else
                                'GridPointer' if comp['name'] == 'table' else 's16')}
        rec['op'] = ('rotation' if rec['type'] == 'AnimationPackedRotation' else
                     'grid_table' if comp['name'] == 'table' and kind == 'collision' else 'copy')
        if extra:
            rec.update(extra)
        parts.append(rec)


for raw, outs, load, source, name in nc.model_includes(V):
    data = raw.read_bytes()
    add('model', raw.stem, load, source, gen_model_inc.components(data, load, source), outs)
for raw, outs, load, source in nc.animation_includes(V):
    data = raw.read_bytes()
    add('animation', raw.stem, load, source, gen_animation_inc.components(data, load, source), outs)
for raw, outs, load, source, extra in nc.collision_includes(V):
    data = raw.read_bytes()
    if extra and extra[0] == '--cell-face-list-macro':
        comps = gen_collision_inc.components(data, load, source)
        add('collision', raw.stem, load, source, comps, outs)
    else:  # patch: `extra` is the piece list
        pieces = gen_collision_inc.patch_pieces(source, extra)
        for piece, f in zip(pieces, outs):
            parts.append({'file': Path(f).name, 'kind': 'collision_patch', 'package': raw.stem, 'load': load,
                          'source': source, 'part': piece['name'], 'offset': piece['offset'],
                          'size': piece['size'], 'type': 'SVECTOR' if piece['name'] == 'vectors' else 'GridFace',
                          'op': 'copy'})
# Assets embedded in a unit's data (asset_data.EMBEDDED_ASSETS): a slice of a package, or of the executable.
import importlib.util, struct
_spec = importlib.util.spec_from_file_location('asset_data', 'tools/peassets/asset_data.py')
_data = importlib.util.module_from_spec(_spec)
_spec.loader.exec_module(_data)
for raw, out, width in nc.asset_includes(V):
    aid = out.relative_to('build/include/assets').with_suffix('').as_posix()
    rec = _data.EMBEDDED_ASSETS[aid]
    src = rec['source']
    container = Path('assets/USA/pe2pkg') / src if src.endswith('.pe2pkg') else Path('assets/USA') / src
    blob, data = raw.read_bytes(), container.read_bytes()
    at = data.find(blob)
    if at < 0:
        raise SystemExit(f'{aid}: not found in {src}')
    if data.find(blob, at + 1) >= 0:      # several identical slices: the include's own name carries the offset
        import re
        m = re.search(r'_([0-9A-F]{4,5})$', aid)
        at = int(m.group(1), 16) if m and data[int(m.group(1), 16):][:len(blob)] == blob else at
    if width == 'TmdBone':
        elem, typ = 36, 'TmdBone'
    elif isinstance(width, int):
        elem, typ = width, f'u{width * 8}'
    else:
        elem, typ = struct.calcsize('<' + width), 'layout'
    parts.append({'file': aid + '.inc', 'kind': 'asset', 'package': 'main.exe' if src == 'main.exe' else src.removesuffix('.pe2pkg'),
                  'load': 0, 'source': at, 'part': 'data', 'offset': at, 'size': len(blob), 'type': typ,
                  'elem': elem, 'op': 'copy'})
# Font glyph tables (gen_font_inc.py output): the exe holds the same bytes the include spells out.
import re as _re
_exe = Path('assets/USA/main.exe').read_bytes()
for _id in ('ui/font/small_glyphs', 'ui/font/medium_glyphs', 'ui/font/large_glyphs', 'ui/caption_font/glyphs'):
    _blob = bytes(int(x, 16) for x in _re.findall(r'0x([0-9A-Fa-f]{2})\b', Path(f'build/include/assets/{_id}.inc').read_text()))
    _at = _exe.find(_blob)
    if _at < 0 or _exe.find(_blob, _at + 1) >= 0:
        raise SystemExit(f'{_id}: not found exactly once in main.exe')
    parts.append({'file': _id + '.inc', 'kind': 'asset', 'package': 'main.exe', 'load': 0, 'source': _at, 'part': 'data',
                  'offset': _at, 'size': len(_blob), 'type': 'u8', 'elem': 1, 'op': 'copy'})
ELEM = {'TmdBone': 36, 'SVECTOR': 8, 'u32': 4, 'u16': 2, 's16': 2, 'GridFace': 12, 'AnimationRecord': 4,
        'AnimationPackedPose': 12, 'AnimationPackedRotation': 4, 'GridPointer': 4}
for p_ in parts:
    if 'elem' not in p_:
        p_['elem'] = ELEM[p_['type']]
json.dump(parts, sys.stdout, indent=0)
print(f'{len(parts)} parts', file=sys.stderr)
