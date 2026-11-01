#!/bin/sh
# Rebuild the generated placeholders from what the linker cannot resolve:
#  - globals the PS1 build placed by address -> src/port/globals.c (types from the game headers)
#  - everything else (overlay code not wired yet) -> weak placeholders in src/port/unresolved_stubs.c
set -e
cd "$(dirname "$0")/../.."
: > src/port/unresolved_stubs.c
echo > src/port/globals.c
cmake --build build-port 2>&1 | grep -E '^  "_' | sed 's/^  "_//;s/", referenced.*//' | sort -u > "${TMPDIR:-/tmp}/pe2_undef.txt"
grep -E '^(g[A-Z]|D_)' "${TMPDIR:-/tmp}/pe2_undef.txt" | python3 tools/port/gen_globals.py
cmake --build build-port 2>&1 | python3 tools/port/gen_unresolved_stubs.py
cmake --build build-port -j8 2>&1 | grep -E "error|duplicate" || true
