#!/usr/bin/env python3
"""C decoders for room layouts that carry pointers: a disc record (PS1 layout, 32-bit addresses) to the host struct.

`void peDecode_<Type>(<Type>* dst, const unsigned char* src)` reads one record field by field at the offsets of
tools/peassets/room/layouts.py. A pointer field is accepted only as zero (stored as NULL); layouts whose data points
elsewhere need a resolver and are refused here. Little-endian host.
"""
from . import layouts as L

SCALAR = {"b": ("int8_t", 1), "B": ("uint8_t", 1), "h": ("int16_t", 2), "H": ("uint16_t", 2),
          "i": ("int32_t", 4), "I": ("uint32_t", 4)}


def numbers(kind) -> bool:
    """Whether a kind is only scalars, possibly in arrays: its bytes are contiguous on the host too."""
    if isinstance(kind, str):
        return kind in SCALAR
    return kind[0] == "arr" and numbers(kind[1])


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
    elif tag == "arr" and numbers(kind):                  # contiguous numbers (a vector type or a plain array)
        n = L.size(kind)
        out.append(f"    _Static_assert(sizeof(dst->{path}) == {n}, \"{path}\");")
        out.append(f"    memcpy(&dst->{path}, src + {off}, {n});")
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



def ptrs_null(kind, value) -> bool:
    """Whether every pointer field of a value of this kind is zero (what decoder() accepts)."""
    if isinstance(kind, str):
        if kind in SCALAR:
            return True
        return all(ptrs_null(k, value[n] if n else value) for n, k in L.LAYOUTS[kind][1])
    tag = kind[0]
    if tag == "ptr":
        return value == 0
    if tag == "named":
        return True
    if tag == "arr":
        return all(ptrs_null(kind[1], v) for v in value)
    if tag == "union":
        return ptrs_null(kind[2], value)
    return True


def has_pointer(kind) -> bool:
    if isinstance(kind, str):
        return kind not in SCALAR and any(has_pointer(k) for _n, k in L.LAYOUTS[kind][1])
    if kind[0] == "ptr":
        return True
    if kind[0] == "arr":
        return has_pointer(kind[1])
    return kind[0] == "union" and has_pointer(kind[2])
