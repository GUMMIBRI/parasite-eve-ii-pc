# Changelog

## 0.1.0-alpha (planned; not yet tagged)

First public preview. A macOS (Apple silicon) archive is built by `.github/workflows/release.yml` from the tag; other
platforms build from source. The executable contains no game data (sampled: 7 of 911 windows of disc data appear in it,
all small constants of the compiled decompiled code): it reads the user's own disc images when it starts.

Known limits: only Akropolis and the Mist shooting gallery are reachable in play (no overlay registry yet, so Dryfield,
the mine and the Neo Ark need the all-overlays development build); audio, movies and saves are incomplete; tested on
macOS (arm64) only; the story after the Akropolis helipad is unverified.

- Boots from a disc image through PsyZ: opening movie, title screen, New Game, the Mist shooting gallery and the
  Akropolis helicopter landing pad (recorded input).
- Runtime asset loading: package parts, declared clips, models, UI fonts, room collision and the data globals converted
  from the disassembly (27,419 arrays) are read from the user's discs when the game starts; the build no longer embeds
  them (`-DPE_EMBED_ASSETS=ON` keeps the old behaviour for comparison).
- Builds with CMake and a C compiler only: the generated layout sources are committed and the decompilation's matching
  toolchain is gone (the extraction tooling is kept at the git tag `pe2-layout-tooling`).
- Host menu (Esc): Graphics (detail, aspect, dithering, geometry correction, fullscreen, antialiasing, model
  filtering, smooth lighting), Controls, Audio, Discs; settings are saved.
- Disc reader for the CDF containers and LZSS packages, verified against both USA discs.
- Embedded and disc-loaded builds give identical asset hashes (16,891 bindings, two packed-short artifacts aside).
- Host test suite (32 tests) that needs no game data; CI on macOS and Linux.
