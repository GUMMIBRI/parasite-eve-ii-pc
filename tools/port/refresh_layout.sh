#!/bin/sh
# Rewrite the committed layout sources from the user's disc. Contributors only: building and playing need none of this.
# Needs the extraction toolchain (venv, splat, ninja, dumpsxiso) and both discs in rom/image (see docs/decomp/README.md).
#   include/generated/        <- build/include (tools/peassets), embed branches removed, pruned to what the build reads
#   src/port/asset_parts_table.c, src/port/asm_data.c, src/port/globals.c, src/port/unresolved_stubs.c
set -e
cd "$(dirname "$0")/../.."
PY=$PWD/venv/bin/python
$PY ninja_config.py --iso_extract
$PY ninja_config.py
$PWD/venv/bin/ninja generated-asset-includes
sh tools/port/regen_assets.sh
python3 tools/port/freeze_includes.py --all
cmake -S . -B build-port -DCMAKE_BUILD_TYPE=RelWithDebInfo -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
cmake --build build-port --parallel || true      # the first build registers the objects the pruning reads
sh tools/port/regen_stubs.sh
cmake --build build-port --parallel
python3 tools/port/freeze_includes.py --src include/generated --prune
cmake --build build-port --parallel
