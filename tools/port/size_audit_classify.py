#!/usr/bin/env python3
"""Classify the structs listed by size_audit.sh: why does the host size differ (pointer, long, size_t), and where
is the struct used (sizeof / memcpy / memFill / casts from raw bytes / globals defined from asm)?
Usage: size_audit_classify.py <audit_ast.json> <bad.txt>"""
import json, re, sys, subprocess, collections
ast = json.load(open(sys.argv[1]))['inner']
bad = [l.strip() for l in open(sys.argv[2]) if l.strip()]
tags, typedefs = {}, {}
for n in ast:
    if n['kind'] == 'RecordDecl' and n.get('completeDefinition'):
        if n.get('name'): tags[n['name']] = n
    elif n['kind'] == 'TypedefDecl':
        owned = None
        for c in n.get('inner', []):
            if c['kind'] == 'ElaboratedType':
                if 'ownedTagDecl' in c: owned = c['ownedTagDecl']['id']
                elif c.get('inner') and 'decl' in c['inner'][0]: owned = c['inner'][0]['decl']['id']
        typedefs[n['name']] = (n['type']['qualType'], owned)
byid = {n['id']: n for n in ast if n['kind'] == 'RecordDecl' and n.get('completeDefinition')}

def reasons(node, seen=None, pending=None):
    seen = seen or set()
    if node['id'] in seen: return set()
    seen = seen | {node['id']}
    out, pend = set(), None
    for c in node.get('inner', []):
        if c['kind'] == 'RecordDecl': pend = c
        if c['kind'] != 'FieldDecl': continue
        q = re.sub(r'\b(const|volatile)\b', '', c['type']['qualType']).strip()
        base = re.sub(r'\[[^\]]*\]', '', q).strip()
        if '(*' in q or base.endswith('*'):
            out.add('pointer')
        elif re.search(r'\b(unsigned long|long)\b', base) and 'long long' not in base:
            out.add('long')
        elif base == 'size_t' or 'size_t' in base or 'intptr' in base:
            out.add('size_t')
        else:
            sub = None
            m = re.match(r'^(struct|union) (\w+)$', base)
            if m:
                sub = tags.get(m.group(2)) or (byid.get(typedefs.get(m.group(2), (0, 0))[1]))
            elif base in typedefs:
                tq, ow = typedefs[base]
                sub = byid.get(ow) if ow else None
                if not sub:
                    mm = re.match(r'^(struct|union) (\w+)$', tq)
                    if mm: sub = tags.get(mm.group(2))
                if not sub and re.search(r'\blong\b', tq) and 'long long' not in tq: out.add('long')
                if not sub and tq.endswith('*'): out.add('pointer')
            elif 'unnamed' in base or 'anonymous' in base:
                sub = pend
            if sub: out |= reasons(sub, seen)
    return out

info = {}
for name in bad:
    d = typedefs.get(name)
    node = byid.get(d[1]) if d and d[1] else tags.get(name)
    if node is None and d:
        mm = re.match(r'^(struct|union) (\w+)$', d[0]); node = tags.get(mm.group(2)) if mm else None
    info[name] = sorted(reasons(node)) if node else ['?']

def count(pattern):
    r = subprocess.run(['grep', '-rEc', pattern, 'src', 'include'], capture_output=True, text=True).stdout
    return sum(int(l.rsplit(':', 1)[1]) for l in r.splitlines() if l.rsplit(':', 1)[1].isdigit())

rows = []
for name in bad:
    uses = {
        'sizeof': count(r'sizeof\((\*?\s*)?' + name + r'\)'),
        'memcpy/fill': count(r'(memCopyBytes|memFillBytes|memcpy|memset)\([^;]*\b' + name + r'\b'),
        'cast': count(r'\(\s*' + name + r'\s*\*\s*\)\s*[A-Za-z(&]'),
    }
    rows.append((name, info[name], uses))
by = collections.Counter(r for _, rs, _ in rows for r in rs)
print('reason counts:', dict(by))
print(f"{'struct':44} {'why':22} sizeof memcpy cast")
for name, rs, u in sorted(rows, key=lambda r: -(r[2]['cast'] + r[2]['memcpy/fill'])):
    print(f"{name:44} {','.join(rs):22} {u['sizeof']:6} {u['memcpy/fill']:6} {u['cast']:4}")
