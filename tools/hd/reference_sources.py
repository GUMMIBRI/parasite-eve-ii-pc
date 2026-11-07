"""Rebuild reference planes from local native exports, never from HD material."""
import hashlib
import json
import re
import struct

from PIL import Image
from native_identity import identity

RGBA555 = [bytes((((word >> shift) & 31)*255//31 for shift in [0, 5, 10])) + b'\xff'
           for word in range(32768)]


def read_native(path, width, height):
    if path.is_symlink() or not path.is_file() or path.stat().st_size != width*height*2:
        raise ValueError('Missing or invalid native export: ' + str(path))
    raw = path.read_bytes()
    if len(raw) != width*height*2:
        raise ValueError('Native export changed while reading')
    return raw


def native_rgba(raw, width, height):
    return Image.frombytes('RGBA', (width, height),
                           b''.join(RGBA555[word & 32767] for word, in struct.iter_unpack('<H', raw)))


def put_reference(plane, cell, tile):
    tile = tile.resize((64, 64), Image.Resampling.NEAREST)
    raw = tile.tobytes()
    rows = [raw[y*256:(y+1)*256] for y in range(64)]
    rows = [row[:4]*2 + row + row[-4:]*2 for row in rows]
    padded = Image.frombytes('RGBA', (68, 68), rows[0]*2 + b''.join(rows) + rows[-1]*2)
    plane.paste(padded, (cell % 16*68, cell//16*68))


def background_reference(metadata, native_root):
    # The caller validates the complete descriptor layout before allocation.
    _, key, _, _, left, right, _, _, cells, _ = struct.unpack('<8sQIIiiIIII', metadata)
    raw = read_native(native_root/f'{key:016x}.rgb555', 320, 240)
    if identity(raw) != key:
        raise ValueError('Native background identity does not match descriptor')
    image = native_rgba(raw, 320, 240)
    plane = Image.new('RGBA', (1088, ((cells+15)//16)*68))
    for cell, (y, x) in enumerate((y, x) for y in range(0, 240, 16) for x in range(left, right, 16)):
        tile = image.crop((x, y, x+16, y+16)) if 0 <= x < 320 else Image.new('RGBA', (16, 16))
        put_reference(plane, cell, tile)
    return plane


def foreground_exports(roots):
    exports, seen = {}, set()
    for root in roots:
        paths = [root/'report.json'] if (root/'report.json').is_file() else sorted(root.glob('*/report.json'))
        for path in paths:
            resolved = path.resolve()
            if resolved in seen:
                continue
            seen.add(resolved)
            if path.is_symlink():
                raise ValueError('Foreground report must not be a symlink')
            report = json.loads(path.read_text())
            if not isinstance(report, dict) or report.get('format') != 'pe2-foreground-source-audit-v1':
                continue
            capture = report.get('capture', {})
            location = capture.get('location', [])
            key = capture.get('key')
            if (not isinstance(key, str) or not re.fullmatch('[0-9a-f]{16}', key) or
                    not isinstance(location, list) or len(location) != 6 or
                    any(type(n) is not int for n in location)):
                raise ValueError('Invalid foreground export context')
            context = (key, *location[:4])
            if context in exports:
                raise ValueError('Ambiguous foreground exports; select one directory per context')
            exports[context] = (path.parent, report)
    return exports


def foreground_context(metadata):
    _, key, _, stage, area, view, room, _, _ = struct.unpack('<8sQQ6I', metadata[:48])
    return (f'{key:016x}', stage, area, view, room)


def foreground_reference(metadata, source_root, report):
    magic, _, _, _, _, _, _, count, cells = struct.unpack('<8sQQ6I', metadata[:48])
    sprites = report.get('sprites')
    if not isinstance(sprites, list) or len(sprites) != count:
        raise ValueError('Foreground export source count does not match descriptor')
    plane = Image.new('RGBA', (1088, ((cells+15)//16)*68))
    for ordinal, record in enumerate(sprites):
        source, tpage, clut, w, h, u, v, first = struct.unpack_from('<IHHHHBBH', metadata, 48+ordinal*16)
        inset = magic == b'PE2FG2\0\0' and bool(source & 4096)
        if magic == b'PE2FG2\0\0':
            source &= ~4096
        s = record['source']
        if ([record['index'], s['tpage'] & 511, s['clut'], s['w'], s['h'], s['u0'], s['v0']] !=
                [source, tpage, clut, w, h, u, v] or (inset and s.get('codeFlags', 0) & 2)):
            raise ValueError('Foreground export metadata does not match descriptor')
        raw = read_native(source_root/f'sprite-{source:04d}.rgb555', w, h)
        if hashlib.sha256(raw).hexdigest() != record.get('native_sha256'):
            raise ValueError('Native foreground export changed since audit')
        image = native_rgba(raw, w, h)
        cell = first
        for y in range(0, h, 16):
            for x in range(0, w, 16):
                sx, sy = (min(x, w-16), min(y, h-16)) if inset else (x, y)
                tile = Image.new('RGBA', (16, 16), (0, 0, 0, 255))
                tile.paste(image.crop((sx, sy, min(sx+16, w), min(sy+16, h))), (0, 0))
                put_reference(plane, cell, tile)
                cell += 1
    return plane
