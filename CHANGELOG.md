# Changelog

## 0.1

- First public preview of the native PC port of *Parasite Eve II* (USA). It reads your own North American CUE/BIN images of both discs when it starts; no game data is included.
- Boots from the disc image: opening movie, title screen and New Game, then the Akropolis up to the helicopter landing pad (including the No. 9 fight) and the Mist shooting gallery. Every stage (Dryfield, Dryfield by night, the mine, the Shelter / Neo Ark) is linked and every one of the 166 real areas loads and renders without a crash (`PE2_START_LOCATION`, `PE2_WARP`; checked by warping into each); MIST_R21 (area 21) has no per-area data (the program's tables hold 20 areas), so entering it runs an empty scene. Only the Akropolis has been played through, and the ending credits and a few boss models (unbound TMD data) are skipped on the host.
- Added a host menu (**Esc**): **Graphics** (picture detail, aspect ratio, dithering, geometry correction, fullscreen, antialiasing, model filtering, smooth lighting), **Controls** (keyboard remapping), **Audio** (volume) and **Discs** (choose the images, swap to disc 2 when the game asks). Settings are saved.
- Game data is loaded from the discs at start (models, animations, room collision, fonts and the tables converted from the original program) instead of being compiled in.
- The disc images are validated on selection: wrong region, wrong disc or a missing BIN is reported with what to fix.
- Builds with CMake and a C compiler; no extraction tools are needed. Host tests (32) run on macOS and Linux in CI.
- Known limits: audio, movies and saves are incomplete; tested on macOS (Apple silicon) only; the story after the Akropolis landing pad is unverified.
