#!/bin/sh
# Rebuild src/port/unresolved_stubs.c from what the linker still cannot resolve.
set -e
cd "$(dirname "$0")/../.."
: > src/port/unresolved_stubs.c
cmake --build build-port 2>&1 | python3 tools/port/gen_unresolved_stubs.py
cmake --build build-port -j8 2>&1 | grep -E "error|duplicate" || true
