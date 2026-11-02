# Contributing

This is a native C11 port of *Parasite Eve II*, derived from a matching decompilation. Preserve the intended game
behaviour and data formats while making the code work on modern hosts. There is no byte-match requirement, stock PS1
compiler requirement or checksum gate: compiler-matching workarounds (register pins, scheduling barriers, declaration
order for the linker) can be removed when the code is repaired.

## Rules that matter

- **No game data in the repository.** No disc images, extracted files, generated sources, or text and images taken
  from the game. `tools/ci/check_no_game_data.sh` runs in CI and fails on the obvious cases; use judgement for the rest.
  Screenshots of your own game for documentation are fine in `docs/images/`.
- **Serialized formats keep their widths.** Disc records, saves and demo files retain their defined sizes, offsets and
  endianness. Host pointers use pointer types; never squeeze a pointer into a 32-bit field. Validate layouts against the
  serialized format (see [docs/SIZE_AUDIT.md](docs/SIZE_AUDIT.md)).
- **Load data from the disc at run time**, not from build-time includes ([docs/RUNTIME_ASSETS.md](docs/RUNTIME_ASSETS.md)).
  A converted array must hash identically to the embedded one: build with `-DPE_EMBED_ASSETS=ON` next to the normal
  build and compare the `PE2_DUMP_ASSETS` dumps.
- Assembly that does real work is translated to portable C, not replaced with a no-op stub.

## Workflow

1. Fork, branch, and keep changes focused.
2. Build and run the host tests, which need no game data:

   ```sh
   git submodule update --init third_party/psyz
   git -C third_party/psyz submodule update --init external/SDL
   cmake -S . -B build -DBUILD_TESTING=ON
   cmake --build build --target host_tests --parallel
   ctest --test-dir build --output-on-failure
   ```

3. For changes that touch the game itself, build it as described in the [README](README.md) and check the behaviour
   against the original game (a recorded input replay, `PE2_PAD_REPLAY`, makes this repeatable).
4. Add a native test under `tests/` for new logic that can be tested without data, and register it in `CMakeLists.txt`
   (`add_executable(... EXCLUDE_FROM_ALL ...)`). Tests that read extracted assets go in `PE_DATA_TESTS` and are run locally.
5. Open a pull request. CI builds and runs the host tests on macOS and Linux.

## Layout

| Path | What |
| --- | --- |
| `src/`, `include/` | game code from the decompilation, compiled for the host |
| `src/port/`, `include/port/` | the port layer: host Psy-Q glue, disc reader, runtime asset loader |
| `tools/port/` | port tooling (asset layout, stubs, replay helpers); `tools/peassets` is the decompilation's asset tooling |
| `tests/` | host tests |
| `docs/` | port plan, runtime assets, size audit; `docs/decomp/` is the decompilation's own documentation |

Questions and discussion go in GitHub issues.
