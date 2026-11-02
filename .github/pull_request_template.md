## What changed

## How it was checked

- [ ] `cmake --build build --target host_tests && ctest --test-dir build` passes
- [ ] `tools/ci/check_no_game_data.sh` passes (no game data in the diff)
- [ ] Behaviour checked against the original game, or a native test added
