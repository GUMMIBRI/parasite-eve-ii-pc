#!/usr/bin/env python3
"""C decoders for room layouts that carry pointers: a disc record (PS1 layout, 32-bit addresses) to the host struct.

    gen_layout_decoders.py KIND [KIND...]    write the decoders to stdout

`void peDecode_<Type>(<Type>* dst, const unsigned char* src)` reads one record field by field at the offsets of
tools/peassets/room/layouts.py. A pointer field is accepted only as zero (stored as NULL); layouts whose data points
elsewhere need a resolver and are refused here. Little-endian host.
"""
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[2] / "tools" / "peassets"))
from room import layouts as L  # noqa: E402

SCALAR = {"b": ("int8_t", 1), "B": ("uint8_t", 1), "h": ("int16_t", 2), "H": ("uint16_t", 2),
          "i": ("int32_t", 4), "I": ("uint32_t", 4)}


def walk(kind, path: str, off: int, out: list[str]) -> None:
    if isinstance(kind, str):
        if kind in SCALAR:
            ctype, n = SCALAR[kind]
            out.append(f"    {{ {ctype} v; memcpy(&v, src + {off}, {n}); dst->{path} = v; }}")
            return
        for name, k, o in L._fields(kind):
            walk(k, f"{path}.{name}" if path and name else path or name, off + o, out)
        return
    tag = kind[0]
    if tag == "bytes":
        out.append(f"    memcpy(dst->{path}, src + {off}, {kind[1]});")
    elif tag == "named":
        walk(kind[1], path, off, out)
    elif tag == "arr":
        step = L.size(kind[1])
        for i in range(kind[2]):
            walk(kind[1], f"{path}[{i}]", off + i * step, out)
    elif tag == "union":
        walk(kind[2], f"{path}.{kind[1]}", off, out)
    elif tag == "ptr":
        out.append(f"    {{ uint32_t v; memcpy(&v, src + {off}, 4); if (v) abort(); dst->{path} = NULL; }}")
    else:
        raise SystemExit(f"{path}: layout kind {tag} has no decoder")


def decoder(kind: str) -> str:
    ctype = L.LAYOUTS[kind][0]
    body: list[str] = []
    for name, k, o in L._fields(kind):
        walk(k, name, o, body)
    return (f"static void peDecode_{kind}({ctype}* dst, const unsigned char* src)\n{{\n" + "\n".join(body) + "\n}\n")


if __name__ == "__main__":
    print("#include <stdint.h>\n#include <stdlib.h>\n#include <string.h>\n")
    for k in sys.argv[1:]:
        print(decoder(k))
