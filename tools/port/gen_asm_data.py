#!/usr/bin/env python3
"""Turn initialized data that the decomp still keeps in asm (asm/USA/**/data/*.s) into C definitions.

The PS1 layout (4-byte pointers, 4-byte long) differs from the host layout, so the asm bytes cannot be
used as they are. For every global that src/port/globals.c defines zero-initialized and that has a
dlabel in the asm data, this reads the PS1 bytes, walks the C type with the PS1 layout, and writes an
initializer for the host type to src/port/asm_data.c (pointers become `&symbol` or PS1_RAM_PTR(addr)).
Converted globals are removed from globals.c. Globals it cannot convert stay zero-initialized.

Usage: gen_asm_data.py <ast.json of globals.c>   (see tools/port/regen_stubs.sh)"""
import json, re, sys, glob, struct, pathlib, os

ast = json.load(open(sys.argv[1]))['inner']
# Globals already defined by compiled C (nm of the game objects), passed as a file: never re-derived from asm.
cdefs = set(open(sys.argv[2]).read().split()) if len(sys.argv) > 2 else set()

# ---------------------------------------------------------------- types
tags, typedefs, enums = {}, {}, set()
unnamed_by_id = {}


class Unsupported(Exception):
    pass


def rec_info(node):
    return node


for n in ast:
    k = n['kind']
    if k == 'RecordDecl' and n.get('completeDefinition'):
        if n.get('name'):
            tags[(n['tagUsed'], n['name'])] = n
        unnamed_by_id[n['id']] = n
    elif k == 'EnumDecl':
        if n.get('name'):
            enums.add(n['name'])
    elif k == 'TypedefDecl':
        owned = None
        for c in n.get('inner', []):
            if c['kind'] == 'ElaboratedType' and 'ownedTagDecl' in c:
                owned = c['ownedTagDecl']['id']
            elif c['kind'] == 'ElaboratedType' and c.get('inner') and 'decl' in c['inner'][0]:
                owned = c['inner'][0]['decl']['id']
        typedefs[n['name']] = (n['type']['qualType'], owned)

SCALARS = {
    'char': (1, 's'), 'signed char': (1, 's'), 'unsigned char': (1, 'u'), 'short': (2, 's'), 'unsigned short': (2, 'u'),
    'int': (4, 's'), 'unsigned int': (4, 'u'), 'long': (4, 's'), 'unsigned long': (4, 'u'),
    'long long': (8, 's'), 'unsigned long long': (8, 'u'), 'float': (4, 'f'), 'double': (8, 'f'), '_Bool': (1, 'u'),
}


def layout(t):
    """-> (size, align) in the PS1 ABI."""
    k = t[0]
    if k == 'int':
        return t[1], min(t[1], 8)
    if k == 'ptr':
        return 4, 4
    if k == 'arr':
        s, a = layout(t[1])
        return s * t[2], a
    if k == 'rec':
        fields = t[2]
        if t[1] == 'union':
            sz = max((layout(f[1])[0] for f in fields), default=0)
            al = max((layout(f[1])[1] for f in fields), default=1)
            return (sz + al - 1) // al * al, al
        off, al = 0, 1
        for f in fields:
            fs, fa = layout(f[1])
            off = (off + fa - 1) // fa * fa + fs
            al = max(al, fa)
        return (off + al - 1) // al * al, al
    raise Unsupported(k)


def field_offsets(t):
    off, out = 0, []
    for f in t[2]:
        fs, fa = layout(f[1])
        if t[1] == 'struct':
            off = (off + fa - 1) // fa * fa
        out.append(off if t[1] == 'struct' else 0)
        if t[1] == 'struct':
            off += fs
    return out


_rec_cache = {}


def build_record(node):
    key = node['id']
    if key in _rec_cache:
        return _rec_cache[key]
    fields, pending = [], None
    placeholder = ['rec', node['tagUsed'], fields]
    _rec_cache[key] = placeholder
    for c in node.get('inner', []):
        if c['kind'] == 'RecordDecl':
            pending = c
        elif c['kind'] == 'FieldDecl':
            if c.get('isBitfield') or any(x['kind'] == 'ConstantExpr' for x in c.get('inner', []) if False):
                raise Unsupported('bitfield')
            fields.append((c.get('name'), resolve(c['type']['qualType'], pending)))
            if 'unnamed' in c['type']['qualType'] or 'anonymous' in c['type']['qualType']:
                pending = None
        elif c['kind'] == 'IndirectFieldDecl':
            pass
    return placeholder


def split_array(q):
    m = re.match(r'^(.*?)\s*((?:\[[^\]]*\])+)$', q)
    if not m:
        return None
    dims = re.findall(r'\[([^\]]*)\]', m.group(2))
    return m.group(1), dims


def resolve(q, pending=None, depth=0):
    q = re.sub(r'\b(const|volatile|restrict|__restrict)\b', '', q).strip()
    q = re.sub(r'\s+', ' ', q)
    if depth > 30:
        raise Unsupported('depth')
    a = split_array(q)
    if a and '(*' not in q.split('[')[0] or (a and q.endswith(']') and '(*)' not in q):
        base, dims = a
        t = resolve(base, pending, depth + 1)
        for d in reversed(dims):
            if d.strip() == '':
                raise Unsupported('incomplete array')
            t = ['arr', t, int(d)]
        return t
    if '(*' in q or '(*)' in q:
        return ['ptr', None]
    if q.endswith('*'):
        return ['ptr', q[:-1].strip()]
    if q in SCALARS:
        s, k = SCALARS[q]
        return ['int', s, k]
    m = re.match(r'^(struct|union) (\w+)$', q)
    if m:
        node = tags.get((m.group(1), m.group(2)))
        if not node and m.group(2) in typedefs and typedefs[m.group(2)][1] in unnamed_by_id:
            node = unnamed_by_id[typedefs[m.group(2)][1]]
        if not node:
            raise Unsupported('incomplete ' + q)
        return build_record(node)
    if q.startswith(('struct (', 'union (', 'struct (unnamed', 'union (unnamed', 'struct (anonymous', 'union (anonymous')):
        if pending is None:
            raise Unsupported('anonymous record')
        return build_record(pending)
    m = re.match(r'^enum (\w+)$', q)
    if m or q.startswith('enum ('):
        return ['int', 4, 's']
    if q in typedefs:
        tq, owned = typedefs[q]
        if (tq.startswith(('struct (', 'union (', 'enum (')) or True) and owned in unnamed_by_id and not tq.startswith('enum'):
            if tq.startswith('enum'):
                return ['int', 4, 's']
            return build_record(unnamed_by_id[owned])
        return resolve(tq, pending, depth + 1)
    if q in enums:
        return ['int', 4, 's']
    if q == 'void':
        raise Unsupported('void')
    raise Unsupported('type ' + q)


# ---------------------------------------------------------------- asm data
class Blob:
    def __init__(self):
        self.data = bytearray()
        self.reloc = {}


blobs = {}
dup = set()


def parse_asm(path):
    cur = None
    for line in open(path, errors='ignore'):
        line = line.strip()
        m = re.match(r'dlabel (\w+)', line)
        if m:
            cur = Blob()
            name = m.group(1)
            if name in blobs:
                dup.add(name)
            blobs[name] = cur
            continue
        if line.startswith('enddlabel'):
            cur = None
            continue
        if cur is None:
            continue
        m = re.match(r'(?:/\*.*?\*/\s*)?\.(word|short|byte|space|asciz|ascii)\s+(.*)$', line)
        if not m:
            continue
        d, arg = m.group(1), m.group(2).strip()
        if d == 'word':
            m2 = re.match(r'^(0x[0-9A-Fa-f]+|\d+)$', arg)
            if m2:
                cur.data += struct.pack('<I', int(arg, 0) & 0xFFFFFFFF)
            else:
                m3 = re.match(r'^(\w+)(?:\s*\+\s*(0x[0-9A-Fa-f]+|\d+))?$', arg)
                if not m3:
                    cur.data += b'\0\0\0\0'
                    continue
                cur.reloc[len(cur.data)] = (m3.group(1), int(m3.group(2) or '0', 0))
                cur.data += b'\0\0\0\0'
        elif d == 'short':
            cur.data += struct.pack('<H', int(arg, 0) & 0xFFFF)
        elif d == 'byte':
            cur.data += struct.pack('<B', int(arg, 0) & 0xFF)
        elif d == 'space':
            cur.data += bytes(int(arg, 0))
        else:
            s = bytes(arg.strip()[1:-1], 'latin1').decode('unicode_escape').encode('latin1')
            cur.data += s + (b'\0' if d == 'asciz' else b'')


for f in sorted(glob.glob('asm/USA/**/data/**/*.s', recursive=True)):
    parse_asm(f)

# ---------------------------------------------------------------- emit
derived = {}
ext = set()


class Ctx:
    def __init__(self, blob):
        self.b = blob
        self.warn = []


def rd(ctx, off, size):
    d = ctx.b.data[off:off + size]
    d = bytes(d) + bytes(size - len(d))
    return int.from_bytes(d, 'little')


def span_zero(ctx, off, size):
    d = ctx.b.data[off:off + size]
    if any(d):
        return False
    return not any(off <= r < off + size for r in ctx.b.reloc)


def emit(ctx, t, off):
    k = t[0]
    if k == 'int':
        s, kind = t[1], t[2]
        if off in ctx.b.reloc:
            ctx.warn.append('address stored in integer')
            return '0'
        v = rd(ctx, off, s)
        if kind == 'f':
            if s == 4:
                f = struct.unpack('<f', v.to_bytes(4, 'little'))[0]
                if f != f or f in (float('inf'), float('-inf')):
                    return '0'
                return repr(f) + 'f'
            f = struct.unpack('<d', v.to_bytes(8, 'little'))[0]
            return repr(f) if f == f and abs(f) != float('inf') else '0'
        if kind == 's' and v >= 1 << (8 * s - 1):
            v -= 1 << (8 * s)
        return str(v) if not (kind == 's' and v == -(1 << (8 * s - 1))) else f'({v + 1}-1)'
    if k == 'ptr':
        if off in ctx.b.reloc:
            sym, add = ctx.b.reloc[off]
            if sym not in declared:
                pointee = t[1]
                if pointee is not None and sym in blobs and sym not in dup and sym not in cdefs:
                    try:
                        resolve(pointee)
                        if derived.setdefault(sym, pointee) != pointee:
                            raise Unsupported('conflicting pointee for ' + sym)
                    except Unsupported:
                        ext.add(sym)
                else:
                    ext.add(sym)
            return f'(void*)&{sym}' if not add else f'(void*)((u8*)&{sym} + {add})'
        v = rd(ctx, off, 4)
        if v == 0:
            return '0'
        if 0x80000000 <= v < 0x80200000:
            return f'(void*)PS1_RAM_PTR(0x{v:08X})'
        return f'(void*)(uintptr_t)0x{v:X}'
    size, _ = layout(t)
    if span_zero(ctx, off, size):
        return '{0}'
    if k == 'arr':
        es, _ = layout(t[1])
        return '{' + ','.join(emit(ctx, t[1], off + i * es) for i in range(t[2])) + '}'
    if k == 'rec':
        offs = field_offsets(t)
        if t[1] == 'union':
            best = max(range(len(t[2])), key=lambda i: layout(t[2][i][1])[0])
            return '{' + emit(ctx, t[2][best][1], off) + '}'
        return '{' + ','.join(emit(ctx, f[1], off + o) for f, o in zip(t[2], offs)) + '}'
    raise Unsupported(k)


# ---------------------------------------------------------------- driver
src = pathlib.Path('src/port/globals.c').read_text().splitlines(keepends=True)
header = [l for l in src if l.startswith('#include') or l.startswith('/*')]
defline = re.compile(r'^(.*?[\s*])(\w+)((?:\[[^\]]*\])*);\s*$')
types = {}
declared = {n['name'] for n in ast if n['kind'] in ('VarDecl', 'FunctionDecl') and n.get('name')}
for n in ast:
    if n['kind'] == 'VarDecl' and n.get('name'):
        types[n['name']] = n['type']['qualType']
out, keep, done, skipped = [], [], 0, {}
for line in src:
    m = defline.match(line)
    if not m or line.startswith('#'):
        keep.append(line)
        continue
    name = m.group(2)
    b = blobs.get(name)
    if b is None or not any(b.data) and not b.reloc or name in dup or name not in types:
        keep.append(line)
        continue
    try:
        t = resolve(types[name])
        ctx = Ctx(b)
        init = emit(ctx, t, 0)
    except (Unsupported, KeyError, IndexError, ValueError, RecursionError) as e:
        skipped[name] = str(e)
        keep.append(line)
        continue
    if ctx.warn:
        skipped[name] = ctx.warn[0]
        keep.append(line)
        continue
    out.append(f'{m.group(1)}{name}{m.group(3)} = {init};\n')
    done += 1
fwd, done_derived = [], set()
while True:
    todo = [k for k in derived if k not in done_derived]
    if not todo:
        break
    for sym in todo:
        done_derived.add(sym)
        try:
            et = resolve(derived[sym])
            es = layout(et)[0]
            n = max(1, (len(blobs[sym].data) + es - 1) // es)
            ctx = Ctx(blobs[sym])
            init = emit(ctx, ['arr', et, n], 0)
            if ctx.warn:
                raise Unsupported(ctx.warn[0])
        except (Unsupported, KeyError, IndexError, ValueError, RecursionError) as e:
            skipped[sym] = 'derived: ' + str(e)
            ext.add(sym)
            continue
        out.append(f'{derived[sym]} {sym}[{n}] = {init};\n')
        fwd.append(f'extern {derived[sym]} {sym}[];\n')
fwd += [f'extern char {x}[];\n' for x in sorted((ext - declared) - {x for x in derived if x not in skipped})]
hdr = ['/* Generated by tools/port/gen_asm_data.py from the asm data files: initialized data, host layout. */\n',
       '#include <stdint.h>\n', '#include "port/psyq_compat.h"\n'] + [l for l in header if l.startswith('#include')]
pathlib.Path('src/port/asm_data.c').write_text(''.join(hdr) + ''.join(fwd) + ''.join(out))
pathlib.Path('src/port/globals.c').write_text(''.join(keep))
print(f'{done} initialized from asm, {len(skipped)} skipped', file=sys.stderr)
if os.environ.get('GEN_WHY'):
    for k, v in skipped.items():
        if os.environ['GEN_WHY'] in k: print(k, v, file=sys.stderr)
from collections import Counter
for r, c in Counter(skipped.values()).most_common(8):
    print('  ', c, r, file=sys.stderr)
