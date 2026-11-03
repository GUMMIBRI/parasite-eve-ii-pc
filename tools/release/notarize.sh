#!/bin/bash
# Notarizes a signed release archive with Apple and staples the ticket to the app, then rebuilds the archive and its
# checksum. Run by hand on the machine that holds the Developer ID certificate; CI never sees it.
#
#   tools/release/notarize.sh <signed zip>        (profile: PE_NOTARY_PROFILE, default "parasite-eve")
#
# The default profile is the one the first game's releases use (Team ID DRR99SUARM). To create one:
#   xcrun notarytool store-credentials <profile> --apple-id <id> --team-id <team> --password <app-specific password>
set -euo pipefail

zip=${1:?signed archive from package_app.sh}
profile=${PE_NOTARY_PROFILE:-parasite-eve}

dir=$(cd "$(dirname "$zip")" && pwd)
file=$(basename "$zip")
name=${file%.zip}

xcrun notarytool submit "$dir/$file" --keychain-profile "$profile" --wait
rm -rf "$dir/$name"
ditto -x -k "$dir/$file" "$dir"
for app in "$dir/$name"/*.app; do
    xcrun stapler staple "$app"
    spctl --assess --type execute --verbose=2 "$app"
done
rm -f "$dir/$file"
(cd "$dir" && ditto -c -k --sequesterRsrc --keepParent "$name" "$file" && shasum -a 256 "$file" > SHA256SUMS)
echo "$dir/$file"
