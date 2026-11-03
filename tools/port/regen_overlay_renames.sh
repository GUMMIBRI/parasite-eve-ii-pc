#!/bin/sh
# Rebuild cmake/overlay_renames.cmake by linking the all-overlays build and reading what clashes.
# Needs: cmake -S . -B build-all -DPE_ALL_OVERLAYS=ON -DPE_ALL_VARIANTS=ON.
set -e
cd "$(dirname "$0")/../.."
T=${TMPDIR:-/tmp}
link() { cmake -S . -B build-all >/dev/null 2>&1; cmake --build build-all --parallel 2>&1 | grep -v 'tentative definition' > "$1" || true; }
: > cmake/overlay_renames.cmake
link "$T/pe_ren_dups.log"
: > "$T/pe_ren_public.log"
python3 tools/port/gen_overlay_renames.py "$T/pe_ren_dups.log"
for i in 1 2 3 4 5 6; do
    link "$T/pe_ren_try.log"
    d=$(grep -c '^duplicate symbol' "$T/pe_ren_try.log" || true)
    u=$(grep -cE '^  "_' "$T/pe_ren_try.log" || true)
    echo "pass $i: $d duplicates, $u undefined" >&2
    [ "$d" = 0 ] && [ "$u" = 0 ] && break
    # names that are referenced from outside stay public in one object; those whose kept object was wrong flip
    cat "$T/pe_ren_try.log" >> "$T/pe_ren_public.log"
    python3 tools/port/gen_overlay_renames.py "$T/pe_ren_dups.log" "$T/pe_ren_public.log" "$T/pe_ren_try.log"
done
