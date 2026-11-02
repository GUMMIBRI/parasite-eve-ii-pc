#!/usr/bin/env python3
"""Export a raw PsyZ VRAM rectangle, respecting the display's pixel format."""
import argparse
from pathlib import Path
import struct
import zlib


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('input', type=Path)
    parser.add_argument('output', type=Path)
    parser.add_argument('--x', type=int, default=0, help='VRAM word coordinate')
    parser.add_argument('--y', type=int, default=0)
    parser.add_argument('--width', type=int, default=320, help='display pixels')
    parser.add_argument('--height', type=int, default=240)
    parser.add_argument('--rgb24', action='store_true')
    args = parser.parse_args()
    data = args.input.read_bytes()
    stride = 3 if args.rgb24 else 2
    if (len(data) != 1024 * 512 * 2 or min(args.x, args.y) < 0
            or min(args.width, args.height) < 1
            or args.x * 2 + args.width * stride > 2048
            or args.y + args.height > 512):
        parser.error('invalid VRAM dump or display rectangle')
    raw = bytearray()
    for y in range(args.y, args.y + args.height):
        raw.append(0)
        offset = y * 2048 + args.x * 2
        row = data[offset:offset + args.width * stride]
        if args.rgb24:
            raw.extend(row)
        else:
            for (pixel,) in struct.iter_unpack('<H', row):
                raw.extend(((pixel & 31) * 255 // 31,
                            ((pixel >> 5) & 31) * 255 // 31,
                            ((pixel >> 10) & 31) * 255 // 31))

    def chunk(kind, payload):
        return (struct.pack('>I', len(payload)) + kind + payload
                + struct.pack('>I', zlib.crc32(kind + payload) & 0xffffffff))

    args.output.write_bytes(b'\x89PNG\r\n\x1a\n'
        + chunk(b'IHDR', struct.pack('>IIBBBBB', args.width, args.height, 8, 2, 0, 0, 0))
        + chunk(b'IDAT', zlib.compress(raw)) + chunk(b'IEND', b''))


if __name__ == '__main__':
    main()
