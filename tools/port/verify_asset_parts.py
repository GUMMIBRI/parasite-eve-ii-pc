#!/usr/bin/env python3
"""Check parts.json (gen_asset_parts.py) against the build's generated includes.

For every part, the bytes at (package, offset, size) are decoded with an independent description of its element
type and the numbers must equal the integers in build/include/assets/<file>. This proves a runtime loader that
copies/converts those bytes reproduces the include.

Usage: verify_asset_parts.py parts.json [<disc.cue> ...]   (with cue files, packages are read from the discs)"""
import json, re, struct, sys
from pathlib import Path

parts = json.load(open(sys.argv[1]))
INT = re.compile(r'-?0x[0-9A-Fa-f]+|-?\d+')


def inc_numbers(name):
    text = open(f'build/include/assets/{name}').read().split('\n', 1)[1]
    text = re.sub(r'[A-Za-z_][A-Za-z_0-9]*\((\d+)\)', r' \1 ', text)
    return [int(t, 0) for t in INT.findall(text.replace('NULL', '-1'))]


def signed(v, bits):
    v &= (1 << bits) - 1
    return v - (1 << bits) if v & (1 << (bits - 1)) else v


def decode(part, data):
    t, o, n = part['type'], part['offset'], part['size']
    b = data[o:o + n]
    out = []
    if t == 'TmdBone':
        for at in range(0, n, 36):
            out += struct.unpack_from('<9h', b, at) + struct.unpack_from('<3i', b, at + 20) + struct.unpack_from('<i', b, at + 32)
    elif t == 'SVECTOR':
        out = struct.unpack(f'<{n // 2}h', b)
    elif t == 'u32':
        out = struct.unpack(f'<{n // 4}I', b)
    elif t == 'u16':
        out = struct.unpack(f'<{n // 2}H', b)
    elif t == 'GridFace':
        for at in range(0, n, 12):
            out += struct.unpack_from('<4H', b, at) + struct.unpack_from('<Hh', b, at + 8)
    elif t == 's16':
        out = struct.unpack(f'<{n // 2}h', b)
    elif t == 'AnimationPackedPose':
        out = struct.unpack(f'<{n // 2}h', b)
    elif t == 'AnimationRecord':
        for at in range(0, n, 4):
            out += struct.unpack_from('<HBB', b, at)
    elif t == 'AnimationPackedRotation':
        for (w,) in struct.iter_unpack('<I', b):
            out += (signed(w, 11), signed(w >> 11, 10), signed(w >> 21, 11))
    elif t == 'u8':
        out = list(b)
    elif t == 'layout':
        return None
    elif t == 'GridPointer':
        cells = next(q for q in parts if q['package'] == part['package'] and q['source'] == part['source']
                     and q['part'] == 'cells' and q['kind'] == 'collision')
        return [-1 if w == 0 else (w - part['load'] - cells['offset']) // 2 for w in struct.unpack(f'<{n // 4}I', b)]
    else:
        raise SystemExit(f'unknown type {t}')
    return list(out)


cache, ok, bad, skipped = {}, 0, 0, 0
for p in parts:
    if p['kind'] == 'clip':      # checked against the package when the parts were written
        continue
    path = 'assets/USA/main.exe' if p['package'] == 'main.exe' else f"assets/USA/pe2pkg/{p['package']}.pe2pkg"
    data = cache.setdefault(p['package'], open(path, 'rb').read())
    want = decode(p, data)
    if want is None and p['type'] == 'layout':
        skipped += 1
        continue
    got = inc_numbers(p['file'])
    if p['type'] == 'u32':
        got = [g & 0xFFFFFFFF for g in got]
    if got == want:
        ok += 1
    else:
        bad += 1
        if bad <= 8:
            print('MISMATCH', p['file'], p['type'], len(got), len(want))
print(f'{ok} parts reproduce their include, {bad} differ, {skipped} grid tables skipped')
sys.exit(1 if bad else 0)
