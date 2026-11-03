#!/bin/sh
# Rebuild the generated placeholders from what the linker cannot resolve:
#  - globals the PS1 build placed by address -> src/port/globals.c (types from the game headers)
#  - of those, the ones with initialized data in asm -> src/port/asm_data.c (tools/port/gen_asm_data.py);
#    converting data can reference further globals, so this repeats until no new ones appear
#  - everything else (overlay code not wired yet) -> weak placeholders in src/port/unresolved_stubs.c
set -e
cd "$(dirname "$0")/../.."
T=${TMPDIR:-/tmp}
B=${BUILD:-build-port}
: > src/port/unresolved_stubs.c
echo > src/port/globals.c
: > src/port/asm_data.c
: > "$T/pe2_all_undef.txt"
CMD=$(python3 -c "
import json
for c in json.load(open('$B/compile_commands.json')):
    if c['file'].endswith('port/globals.c'): print(c['command'].split(' -o ')[0].replace('/usr/bin/cc','clang').replace(' -arch arm64',''))
")
pass=0
while [ $pass -lt 5 ]; do
    pass=$((pass + 1))
    cmake --build $B 2>&1 | grep -E '^  "_' | sed 's/^  "_//;s/", referenced.*//' | sort -u > "$T/pe2_undef.txt"
    before=$(wc -l < "$T/pe2_all_undef.txt")
    grep -E '^(g[A-Z]|D_)' "$T/pe2_undef.txt" | cat - "$T/pe2_all_undef.txt" | sort -u > "$T/pe2_all_undef2.txt"
    mv "$T/pe2_all_undef2.txt" "$T/pe2_all_undef.txt"
    [ "$(wc -l < "$T/pe2_all_undef.txt")" = "$before" ] && [ $pass -gt 1 ] && break
    python3 tools/port/gen_globals.py < "$T/pe2_all_undef.txt"
    (cd $B && sh -c "$CMD -w -Xclang -ast-dump=json -fsyntax-only ../src/port/globals.c" > "$T/pe2_ast.json")
    # data symbols the compiled C already defines (the link must not see them twice)
    find $B/CMakeFiles -name '*.o' -not -path '*/parasite-eve-ii-pc.dir/*' | xargs nm -gU 2>/dev/null |
        awk '$2 ~ /^[DSdsRr]$/ {sub(/^_/, "", $3); print $3}' | sort -u > "$T/pe2_cdefs.txt"
    : > src/port/asm_data.c
    python3 tools/port/gen_asm_data.py "$T/pe2_ast.json" "$T/pe2_cdefs.txt"
done
cmake --build $B 2>&1 | python3 tools/port/gen_unresolved_stubs.py
cmake --build $B -j8 2>&1 | grep -E "error|duplicate" || true
