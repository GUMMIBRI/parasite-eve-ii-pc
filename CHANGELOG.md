# Changelog

## Unreleased

Pre-alpha; nothing has been released.

- Boots from a disc image through PsyZ: opening movie, title screen, New Game, the Mist shooting gallery and the
  Akropolis helicopter landing pad (recorded input).
- Runtime asset loading: package parts, declared clips, models, UI fonts and flat assets are read from the user's discs
  when the game starts; the build no longer embeds them (`-DPE_EMBED_ASSETS=ON` keeps the old behaviour for comparison).
- Disc reader for the CDF containers and LZSS packages, verified against both USA discs.
- Host test suite (28 tests) that needs no game data; CI on macOS and Linux.
