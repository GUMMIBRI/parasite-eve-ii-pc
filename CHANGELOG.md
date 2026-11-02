# Changelog

## Unreleased (planned: 0.1.0-alpha, source release)

Nothing has been released. 0.1.0-alpha will be a source release: no binaries, because the executable still embeds data
converted from the discs (see docs/RELEASING.md).

- Boots from a disc image through PsyZ: opening movie, title screen, New Game, the Mist shooting gallery and the
  Akropolis helicopter landing pad (recorded input).
- Runtime asset loading: package parts, declared clips, models, UI fonts and flat assets are read from the user's discs
  when the game starts; the build no longer embeds them (`-DPE_EMBED_ASSETS=ON` keeps the old behaviour for comparison).
- Disc reader for the CDF containers and LZSS packages, verified against both USA discs.
- 4,644 arrays are bound to the disc, 809 of them models and 468 flat room tables; embedded and disc-loaded builds give
  identical hash dumps.
- Host test suite (28 tests) that needs no game data; CI on macOS and Linux.
