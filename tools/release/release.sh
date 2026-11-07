#!/bin/bash
# Local release: build, sign with the Developer ID certificate, notarize, checksum, and create a DRAFT GitHub release.
#
#   tools/release/release.sh <version>      (for example 0.1)
#
# The signing identity is PE_SIGN_IDENTITY, or the single "Developer ID Application" certificate in the keychain (the one
# the first game's releases use) and PE_NOTARY_PROFILE defaults to "parasite-eve", the first game's notarytool profile.
# Nothing is tagged or published: the release stays a draft until you publish it.
set -euo pipefail

version=${1:?version, for example 0.1}
root=$(cd "$(dirname "$0")/../.." && pwd)
cd "$root"

# Release exactly what is on origin/main.
if ! git diff --quiet || ! git diff --cached --quiet; then
    echo "working tree has uncommitted changes" >&2
    exit 1
fi
git fetch -q origin main
[ "$(git rev-parse HEAD)" = "$(git rev-parse origin/main)" ] || { echo "HEAD is not origin/main" >&2; exit 1; }

identity=${PE_SIGN_IDENTITY:-$(security find-identity -v -p codesigning | sed -n 's/.*"\(Developer ID Application:[^"]*\)".*/\1/p' | head -n1)}
[ -n "$identity" ] || { echo "no Developer ID Application certificate in the keychain" >&2; exit 1; }
echo "signing as: $identity"

tools/ci/check_no_game_data.sh
cmake -S . -B build-release -DCMAKE_BUILD_TYPE=Release
cmake --build build-release --parallel --target parasite-eve-ii-pc

out=dist
cargo build --manifest-path save-editor/Cargo.toml --locked --release
zip=$(tools/release/package_app.sh build-release/parasite-eve-ii-pc "$version" "$out" "$identity" save-editor/target/release/pe2-save-editor | tail -n1)
tools/release/notarize.sh "$zip"

# Same shape as the first game's releases: a bare version tag, "Parasite Eve II X-alpha", what changed, downloads.
tag="$version"
repo=khasinski/parasite-eve-ii-pc
asset=$(basename "$zip")
changes=$(sed -n "/^## ${version//./\\.}\$/,/^## /p" CHANGELOG.md | sed '1d;$d' | sed '/^$/d')
notes=$(cat <<NOTES
### What's changed

${changes}

### Download

- [macOS - Apple Silicon](https://github.com/${repo}/releases/download/${tag}/${asset}) · macOS 15+, signed and notarized

Extract the download and choose your own **North American CUE/BIN disc images** of both discs on the **Discs** page of the menu (**Esc**); keep each CUE beside its BIN. Game data is not included. **Esc** opens the settings and the controls page.

The save editor is included in the download (\`Parasite Eve II Save Editor.app\`). It has not been tried on a retail save: work on a copy. This remains a pre-alpha: native gameplay and save/reload have been exercised into the Shelter Laboratory on macOS. Later story progression and full gameplay on Linux/Windows remain unverified.

[Full changelog](https://github.com/${repo}/blob/${tag}/CHANGELOG.md)
NOTES
)

# The release is created as a draft so it can be read before it goes out; the tag appears when it is published.
gh release create "$tag" --draft --target "$(git rev-parse HEAD)" --title "Parasite Eve II ${version}-alpha" --notes "$notes" \
    "$zip" "$out/SHA256SUMS"
echo "draft release $tag created; publish with: gh release edit $tag --draft=false --latest"
