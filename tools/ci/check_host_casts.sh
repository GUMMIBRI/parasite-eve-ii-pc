#!/bin/sh
# The game sources build with -w, which hides 64-bit hazards. This syntax-only
# pass turns on the pointer/int cast warnings and fails when any appear.
# Usage: tools/ci/check_host_casts.sh [build-dir]   (needs compile_commands.json)
set -e
BUILD=${1:-build-port}
python3 - "$BUILD" <<'P'
import json, os, re, shlex, subprocess, sys
from concurrent.futures import ThreadPoolExecutor
build = sys.argv[1]
db = json.load(open(os.path.join(build, 'compile_commands.json')))
flags = '-fsyntax-only -Wpointer-to-int-cast -Wint-to-pointer-cast'
def run(e):
    f = e['file']
    if '/src/' not in f or 'third_party' in f or '_deps' in f:
        return []
    c = e['command'].replace(' -w ', ' ')
    c = re.sub(r' -o \S+', ' ', c)
    c = re.sub(r' -c \S+', ' ', c)
    out = subprocess.run(c + ' ' + flags + ' ' + shlex.quote(f), shell=True, cwd=e['directory'],
                         capture_output=True, text=True).stderr
    return [l for l in out.splitlines() if '-Wpointer-to-int-cast' in l or '-Wint-to-pointer-cast' in l]
with ThreadPoolExecutor(8) as ex:
    hits = sorted({l for r in ex.map(run, db) for l in r})
for h in hits:
    print(h)
print('%d pointer/int cast warning(s)' % len(hits))
sys.exit(1 if hits else 0)
P
