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

identity=${PE_SIGN_IDENTITY:-$(security find-identity -v -p codesigning | sed -n 's/.*"\(Developer ID Application:[^"]*\)".*/\1/p' | head -n1)}
[ -n "$identity" ] || { echo "no Developer ID Application certificate in the keychain" >&2; exit 1; }
echo "signing as: $identity"

tools/ci/check_no_game_data.sh
cmake -S . -B build-release -DCMAKE_BUILD_TYPE=Release
cmake --build build-release --parallel --target parasite-eve-ii-pc

out=dist
zip=$(tools/release/package_app.sh build-release/parasite-eve-ii-pc "$version" "$out" "$identity" | tail -n1)
tools/release/notarize.sh "$zip"

tag="v$version"
notes=$(sed -n "/^## ${version//./\\.}\$/,/^## /p" CHANGELOG.md | sed '1d;$d')
gh release create "$tag" --draft --prerelease --title "Parasite Eve II $version-alpha" --notes "$notes" \
    "$zip" "$out/SHA256SUMS"
echo "draft release $tag created; review it on GitHub and publish by hand"
