#!/bin/bash
# Builds "Parasite Eve II.app" around the game executable and zips the release folder.
#
#   tools/release/package_app.sh <executable> <version> <out-dir> [signing-identity]
#
# Without an identity the bundle is only ad-hoc signed (enough to run on the machine that built it, and what CI
# produces). With one (a "Developer ID Application: ..." name or hash) the bundle is signed with the hardened runtime
# and a secure timestamp, ready for notarization by tools/release/notarize.sh.
# The archive holds no game data: the game reads the user's own disc images when it starts.
set -euo pipefail

exe=${1:?executable}
version=${2:?version}
out=${3:?output directory}
identity=${4:-}

root=$(cd "$(dirname "$0")/../.." && pwd)
name="parasite-eve-ii-${version}-macos-arm64"
stage="$out/$name"
app="$stage/Parasite Eve II.app"

rm -rf "$stage"
mkdir -p "$app/Contents/MacOS" "$app/Contents/Resources"
cp "$exe" "$app/Contents/MacOS/Parasite Eve II"
cp "$root/packaging/macos/ParasiteEveII.icns" "$app/Contents/Resources/"
sed "s/@VERSION@/${version}/g" "$root/packaging/macos/Info.plist.in" > "$app/Contents/Info.plist"
cp "$root/README.md" "$root/LICENSE" "$root/THIRD_PARTY_NOTICES.md" "$root/CHANGELOG.md" "$stage/"
cat > "$stage/START-HERE.txt" <<TXT
Parasite Eve II, native port (unofficial, alpha). This archive contains no game data.
You need your own North American CUE/BIN images of both discs.

Open "Parasite Eve II.app", then choose your disc 1 image on the Discs page of the menu (Esc), or start it from a
terminal:

  "Parasite Eve II.app/Contents/MacOS/Parasite Eve II" "path/to/Parasite Eve II (Disc 1).cue"

Put disc 2 next to disc 1 or choose it on the same page when the game asks.
TXT

if [ -n "$identity" ]; then
    codesign --force --options runtime --timestamp --sign "$identity" "$app"
else
    codesign --force --sign - "$app"
fi
codesign --verify --strict --verbose=2 "$app"

(cd "$out" && ditto -c -k --sequesterRsrc --keepParent "$name" "$name.zip")
echo "$out/$name.zip"
