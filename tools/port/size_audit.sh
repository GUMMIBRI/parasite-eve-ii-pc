#!/bin/sh
# List every game struct whose host size differs from its PS1 size (STATIC_ASSERT_SIZEOF values).
# These are the 32-vs-64-bit hazards: pointers or u_long inside structs that are also overlaid on raw
# bytes (disc data, scratchpad, save data, GPU packets), copied with sizeof, or indexed by stride.
set -e
cd "$(dirname "$0")/../.."
T=${TMPDIR:-/tmp}
CMD=$(python3 -c "
import json
for c in json.load(open('build-port/compile_commands.json')):
    if c['file'].endswith('port/globals.c'): print(c['command'].split(' -o ')[0].replace('/usr/bin/cc','clang').replace(' -arch arm64',''))
")
python3 - "$T/pe2_audit.c" <<'P'
import glob, sys
hs = sorted(glob.glob('include/**/*.h', recursive=True))
open(sys.argv[1], 'w').write('#include "types.h"\n#include "common.h"\n' + ''.join(f'#include "{h[8:]}"\n' for h in hs))
P
(cd build-port && sh -c "$CMD -DPE_SIZE_AUDIT -w -ferror-limit=0 -fsyntax-only $T/pe2_audit.c" 2>&1) |
    grep -oE "static_assertion_sizeof_\w+" | sed 's/static_assertion_sizeof_//' | sort -u
