# Releasing

## 0.1.0-alpha: source and a macOS archive

The executable no longer embeds game data: the disc-derived arrays are loaded at run time and the committed layout
sources hold no disc bytes (a sample of 911 windows of disc data found 7 in the binary, all small constants of the
compiled decompiled code). So a binary can be published. `.github/workflows/release.yml` builds the macOS (Apple
silicon) archive on a `v*` tag and attaches it to a GitHub release; "Run workflow" builds the same archive as a workflow
artifact without publishing. Linux and Windows archives wait until those platforms are run, not only built.

## Checklist

1. CI is green on `main` (`native-c`: repository check, host tests on macOS and Linux, tool syntax).
2. `tools/ci/check_no_game_data.sh` passes and `git ls-files` holds no disc-derived file.
3. A clean clone builds the host tests and the game (README: CMake and a C compiler; no extraction).
4. CHANGELOG has a dated `0.1.0-alpha` section with known limits.
5. README status matches the changelog.
6. The repository is made public only on the owner's instruction. Tag `v0.1.0-alpha` after that, and write the release
   notes from the CHANGELOG.

## After 0.1.0-alpha

Binary releases need the embedded data above gone. The packaging model of the first game's port
(`parasite-eve-pc`: CI-built Linux and Windows archives, a macOS bundle with `Info.plist`) applies once that is true.

## Known link status (measured 2026-11-03)

- Default build (`build-port`, Akropolis and a few packages): links and runs.
- `-DPE_ALL_OVERLAYS=ON -DPE_ALL_VARIANTS=ON` (every overlay and every per-package variant): **links** (2026-11-03;
  it had 442 undefined symbols) and starts. Overlays that the PS1 loaded one at a time export the same names
  (`gRoomEventMsg`, `gChaserMadBurstHead`, ...: 669 clashes). `cmake/overlay_renames.cmake` gives each object private
  names for them (`-Dname=PE_<object>_name`); a name another object refers to stays public in one definition.
  Regenerate with `BUILD=build-all sh tools/port/regen_stubs.sh` (the tables for that configuration) and then
  `sh tools/port/regen_overlay_renames.sh`; restore the default build's tables with plain `regen_stubs.sh`.
  What this is not yet: a module registry. Nothing loads, unloads or resets an overlay at run time, so Dryfield, the
  Shelter, the Neo Ark and the Mine are still unreachable in play. That wiring (load by package, state reset, the
  54 `func_8070xxxx` calls from `main`) is the remaining phase 2 work.
