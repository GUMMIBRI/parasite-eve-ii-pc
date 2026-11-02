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
json.dump(parts, sys.stdout, indent=0)
print(f'{len(parts)} parts', file=sys.stderr)
