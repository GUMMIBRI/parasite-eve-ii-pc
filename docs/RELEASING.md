# Releasing

## 0.1.0-alpha: a source release

A binary cannot be published yet. The executable still contains data converted from the discs, so redistributing it
would redistribute game data. What is embedded today:

| Embedded in the executable | Size | Needed for a binary release |
| --- | --- | --- |
| `src/port/asm_data.c` (initialized globals converted from the original program) | generated | a runtime decoder or removal |
| Room structures with pointers (events, geometry, lights, surfaces, triggers, placements), ~230 includes | ~2.5 MB | per-type decoders (docs/RUNTIME_ASSETS.md) |
| Animation bank slot tables, ~210 includes | layout only | none: they hold no disc bytes |
| Inventory catalog, one motion table | ~48 KB | decoders |

So 0.1.0-alpha is the repository at a tag, built by each user from their own discs (README, "Build").

## Checklist

1. CI is green on `main` (`native-c`: repository check, host tests on macOS and Linux, tool syntax).
2. `tools/ci/check_no_game_data.sh` passes and `git ls-files` holds no disc-derived file.
3. A clean clone builds the host tests, and the game builds from a fresh extraction (README).
4. CHANGELOG has a dated `0.1.0-alpha` section with known limits.
5. README status matches the changelog.
6. The repository is made public only on the owner's instruction. Tag `v0.1.0-alpha` after that, and write the release
   notes from the CHANGELOG.

## After 0.1.0-alpha

Binary releases need the embedded data above gone. The packaging model of the first game's port
(`parasite-eve-pc`: CI-built Linux and Windows archives, a macOS bundle with `Info.plist`) applies once that is true.

## Known link status (measured 2026-11-03)

- Default build (`build-port`, Akropolis and a few packages): links and runs.
- `-DPE_ALL_OVERLAYS=ON` (every overlay package): compiles, fails to link with 442 unique undefined symbols (overlay
  functions and data that need the module registry, phase 2 in `docs/PORT_PLAN.md`). The option is experimental by
  design. Dryfield, the Shelter, the Neo Ark and the Mine are unreachable until this is closed.
