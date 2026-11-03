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


def walk(kind, path: str, off: int, out: list[str], skip_ptr: bool = False) -> None:
    if isinstance(kind, str):
        if kind in SCALAR:
            ctype, n = SCALAR[kind]
            out.append(f"    {{ {ctype} v; memcpy(&v, src + {off}, {n}); dst->{path} = v; }}")
            return
        for name, k, o in L._fields(kind):
            walk(k, f"{path}.{name}" if path and name else path or name, off + o, out, skip_ptr)
        return
    tag = kind[0]
    if tag == "bytes":
        out.append(f"    memcpy(dst->{path}, src + {off}, {kind[1]});")
    elif tag in ("named", "bits"):                         # a number in the field's own format
        walk(kind[1], path, off, out, skip_ptr)
    elif tag == "word":                                    # an integer, or a pointer set by the array's fixups
        out.append(f"    {{ uint32_t v; memcpy(&v, src + {off}, 4); dst->{path}.{kind[1]} = v; }}")
    elif tag == "arr" and numbers(kind):                  # contiguous numbers (a vector type or a plain array)
        n = L.size(kind)
        out.append(f"    _Static_assert(sizeof(dst->{path}) == {n}, \"{path}\");")
        out.append(f"    memcpy(&dst->{path}, src + {off}, {n});")
    elif tag == "arr":
        step = L.size(kind[1])
        for i in range(kind[2]):
            walk(kind[1], f"{path}[{i}]", off + i * step, out, skip_ptr)
    elif tag == "union":
        walk(kind[2], f"{path}.{kind[1]}", off, out, skip_ptr)
    elif tag == "text":
        out.append(f"    memcpy(dst->{path}, src + {off}, {kind[1]});")
    elif tag == "ptr" and skip_ptr:
        out.append(f"    /* {path}: pointer, set by the array's fixups */")
    elif tag == "ptr":
        out.append(f"    {{ uint32_t v; memcpy(&v, src + {off}, 4); if (v) abort(); dst->{path} = NULL; }}")
    else:
        raise SystemExit(f"{path}: layout kind {tag} has no decoder")


def decoder(kind: str, skip_ptr: bool = False) -> str:
    ctype = L.LAYOUTS[kind][0]
    body: list[str] = []
    for name, k, o in L._fields(kind):
        walk(k, name, o, body, skip_ptr)
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
    return kind[0] == "word" or (kind[0] == "union" and has_pointer(kind[2]))


def n_fill(k) -> bool:
    return hasattr(L, "_filled")


def fixups(kind, values, pointer, c_value) -> list[str]:
    """`dst[i].path = target;` for each non-zero pointer of an array's values: the topology stays code, the numbers
    come from the disc. `pointer` and `c_value` are the room generator's."""
    out: list[str] = []

    def walk_value(k, v, path: str) -> None:
        if isinstance(k, str):
            if k in SCALAR:
                return
            v = L._filled(v, k) if n_fill(k) else v
            for n, kk in L.LAYOUTS[k][1]:
                walk_value(kk, v[n] if n else v, f"{path}.{n}" if n else path)
        elif k[0] == "word":
            if isinstance(v, str):
                out.append(f"    {path}.{k[2]} = {pointer(v)};")
        elif k[0] == "ptr":
            if v != 0:
                out.append(f"    {path} = {c_value(v, k, pointer)};")
        elif k[0] == "arr":
            for i, e in enumerate(v):
                walk_value(k[1], e, f"{path}[{i}]")
        elif k[0] == "union":
            walk_value(k[2], v, f"{path}.{k[1]}")

    for i, v in enumerate(values):
        walk_value(kind, v, f"dst[{i}]")
    return out


def pointer_free_of_words(kind) -> bool:
    """Whether the kind has none of the layouts the decoder cannot read (bit fields, word unions, special slots)."""
    try:
        decoder(kind, skip_ptr=True)
    except SystemExit:
        return False
    return kind != "GfxImageSlot"
