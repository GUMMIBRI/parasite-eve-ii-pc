#!/bin/sh
# Regenerate the runtime asset layout table (no game data) and convert source sites. Needs the extraction
# (assets/USA) and the project venv. Safe to re-run: converted sites are skipped.
set -e
cd "$(dirname "$0")/../.."
T=${TMPDIR:-/tmp}
venv/bin/python tools/port/gen_asset_parts.py > "$T/pe2_parts.json"
venv/bin/python tools/port/gen_asset_manifest.py build/include/assets "$T/pe2_parts.json" > "$T/pe2_manifest.json"
python3 tools/port/gen_asset_table.py "$T/pe2_parts.json" "$T/pe2_manifest.json" > src/port/asset_parts_table.c
python3 tools/port/verify_asset_parts.py "$T/pe2_parts.json"
