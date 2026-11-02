#!/usr/bin/env python3
"""Rewrite `type name[] = { #include "assets/X.inc" };` sites so the array is filled from the disc at run time.

Each site becomes
    #ifdef PE_EMBED_ASSETS          (build-time include, kept for comparison runs)
    <original>
    #else
    <declaration with an explicit element count, zero-filled>;
    #endif
    PE_ASSET_BIND("X", name);
Usage: convert_asset_sites.py parts.json   (edits files under src/ in place; idempotent)"""
import glob, json, re, sys

parts = {p['file'][:-4]: p for p in json.load(open(sys.argv[1]))}
ELEM = {'TmdBone': 36, 'SVECTOR': 8, 'u32': 4, 'u16': 2, 's16': 2, 'GridFace': 12, 'AnimationRecord': 4,
        'AnimationPackedPose': 12, 'AnimationPackedRotation': 4, 'GridPointer': 4}
pat = re.compile(
    r'^(?P<head>[^\n=;{}#]*\b(?P<name>\w+)\s*(?P<dim>\[[^\]\n]*\])?(?P<attr>(?:\s*(?:SECTION|ALIGN|__attribute__)\([^\n=]*?\))*\s*))=\s*\{[ \t]*\n'
    r'(?P<mid>(?:[ \t]*#(?:undef|define)[^\n]*\n)*)#include "assets/(?P<key>[A-Za-z0-9_/]+)\.inc"\n(?:[ \t]*\n)*\};', re.M)
cellmacro = re.compile(r'#define\s+\w+\((\w+)\)\s*\(&(\w+)\[\(\1\)\]\)')
done = skipped = 0
for path in glob.glob('src/**/*.c', recursive=True) + glob.glob('src/**/*.h', recursive=True):
    s = open(path).read()
    out, last, n = [], 0, 0
    for m in pat.finditer(s):
        part = parts.get(m['key'])
        if s[:m.start()].endswith('#ifdef PE_EMBED_ASSETS\n'):
            continue                                  # already converted
        if not part:
            skipped += 1
            continue
        head = re.sub(r'\bconst\b\s*', '', m['head'])
        count = part['size'] // part['elem']
        dim = f"[{count}]" if m['dim'] else ""
        decl = f"{head[:m.start('dim') - m.start('head')] if m['dim'] else head.rstrip()}"
        # rebuild: everything of the head up to the name, then the dimension, then the attributes
        before = re.sub(r'\bconst\b\s*', '', s[m.start('head'):m.start('name')])
        attr = m['attr'].strip()
        decl = f"{before}{m['name']}{dim}{(' ' + attr) if attr else ''};"
        aux = 'NULL'
        if part['op'] == 'grid_table':
            macros = cellmacro.findall(s[:m.start()])
            if not macros:
                skipped += 1
                continue
            aux = macros[-1][1]
        bind = (f'PE_ASSET_BIND_AUX("{m["key"]}", {m["name"]}, {aux});' if aux != 'NULL'
                else f'PE_ASSET_BIND("{m["key"]}", {m["name"]});')
        block = (f'#ifdef PE_EMBED_ASSETS\n{m.group(0)}\n#else\n{decl}\n#endif\n{bind}')
        out.append(s[last:m.start()] + block)
        last = m.end()
        n += 1
    if not n:
        continue
    s2 = ''.join(out) + s[last:]
    # the binding macro lives in a port header
    first = re.search(r'^#include [<"][^\n]*\n', s2, re.M)
    if '#include "port/asset_bind.h"' in s2:
        pass
    elif first:
        s2 = s2[:first.end()] + '#include "port/asset_bind.h"\n' + s2[first.end():]
    else:
        s2 = '#include "port/asset_bind.h"\n' + s2
    open(path, 'w').write(s2)
    done += n
print(f'{done} sites converted, {skipped} left alone', file=sys.stderr)
