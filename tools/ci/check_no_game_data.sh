#!/bin/sh
# Fail if the repository tracks anything that looks like game data: disc images, extracted game files, or
# generated sources that are produced from a user's disc (see docs/RUNTIME_ASSETS.md). Run from CI and before a release.
set -eu
cd "$(dirname "$0")/../.."
bad=$(git ls-files | grep -Ei '\.(bin|cue|iso|img|exe|cdf|hed|pe2pkg|tmd|tim|vab|vh|vb|xa|str|mdec|sbi|7z|zip)$' || true)
bad="$bad
$(git ls-files | grep -E '^(assets|asm|rom|build|build-[^/]+)/|^src/port/(asm_data|asset_parts_table)\.c$' || true)"
bad=$(printf '%s\n' "$bad" | sed '/^$/d')
if [ -n "$bad" ]; then
    echo "Tracked files that must not be in the repository:" >&2
    printf '%s\n' "$bad" >&2
    exit 1
fi
big=$(git ls-files -z | xargs -0 ls -l 2>/dev/null | awk '$5 > 12000000 {print $9 " (" $5 " bytes)"}')
if [ -n "$big" ]; then
    echo "Unexpectedly large tracked files:" >&2
    printf '%s\n' "$big" >&2
    exit 1
fi
echo "no game data tracked"
