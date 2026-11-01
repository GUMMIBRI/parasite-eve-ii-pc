#!/bin/sh
# Rebuild the generated placeholders from what the linker cannot resolve:
#  - globals the PS1 build placed by address -> src/port/globals.c (types from the game headers)
#  - of those, the ones with initialized data in asm -> src/port/asm_data.c (tools/port/gen_asm_data.py)
#  - everything else (overlay code not wired yet) -> weak placeholders in src/port/unresolved_stubs.c
set -e
cd "$(dirname "$0")/../.."
: > src/port/unresolved_stubs.c
echo > src/port/globals.c
: > src/port/asm_data.c
cmake --build build-port 2>&1 | grep -E '^  "_' | sed 's/^  "_//;s/", referenced.*//' | sort -u > "${TMPDIR:-/tmp}/pe2_undef.txt"
grep -E '^(g[A-Z]|D_)' "${TMPDIR:-/tmp}/pe2_undef.txt" | python3 tools/port/gen_globals.py
CMD=$(python3 -c "
import json
for c in json.load(open('build-port/compile_commands.json')):
    if c['file'].endswith('port/globals.c'): print(c['command'].split(' -o ')[0].replace('/usr/bin/cc','clang').replace(' -arch arm64',''))
")
(cd build-port && sh -c "$CMD -w -Xclang -ast-dump=json -fsyntax-only ../src/port/globals.c" > "${TMPDIR:-/tmp}/pe2_ast.json")
# data symbols the compiled C already defines (the link must not see them twice)
find build-port/CMakeFiles/game_overlays.dir build-port/CMakeFiles/game_main.dir -name '*.o' | xargs nm -gU 2>/dev/null |
    awk '$2 ~ /^[DSdsRr]$/ {sub(/^_/, "", $3); print $3}' | sort -u > "${TMPDIR:-/tmp}/pe2_cdefs.txt"
python3 tools/port/gen_asm_data.py "${TMPDIR:-/tmp}/pe2_ast.json" "${TMPDIR:-/tmp}/pe2_cdefs.txt"
cmake --build build-port 2>&1 | python3 tools/port/gen_unresolved_stubs.py
cmake --build build-port -j8 2>&1 | grep -E "error|duplicate" || true
