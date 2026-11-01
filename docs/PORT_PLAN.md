# Port plan

One-way native port: the decompiled game code, compiled with a host C11
compiler and linked against PsyZ. Reference: `parasite-eve-pc` (port of the
first game). Matching the PS1 binaries is not a goal.

## Known gaps

| Gap | Notes |
|---|---|
| Game data | The decompilation generates C from the user's discs at build time. The port decodes disc records at runtime instead, as the first game's port does. |
| 64-bit pointers | ~1,670 pointer/integer casts; `u32` fields holding pointers; `STATIC_ASSERT_SIZEOF` on structs that contain pointers. Disc records are kept apart from host structures. |
| Overlays | 446 packages linked for fixed addresses, calling the executable by address. Need a module registry, a naming scheme (203 global names repeat across overlays) and explicit state/reset. |
| Handwritten asm | `src/main/hasm`: LZSS decompression and the TMD stream renderer (GTE). Rewrite in C. |
| PsyZ coverage | Verify libcd (`CdControl`/`CdReadyCallback`/`CdGetSector` streaming), SPU, MDEC (STR), XA, memory card, GTE accuracy (~3,800 uses). |

## Phases

0. **Foundation.** CMake and PsyZ submodule; compile `src/main` on the host; drop the matching toolchain once nothing depends on it.
1. **Boot to title.** Memory, task system, disc image mount (both discs), `fs`/`cdcmd` on PsyZ, LZSS and TMD in C, pad, fonts, `title` overlay.
2. **Overlays.** Module registry, naming, runtime data loader; first room with Aya and collision.
3. **Gameplay.** Actors, combat, items, menus, by family; verify against emulator traces (`tools/gametrace`).
4. **Sound and movies.** SPU sequencer, XA, STR through MDEC.
5. **Product.** Saves, settings, crash reports, HD/widescreen/60 Hz (from the first port), packaging.

Throughout: native tests per module and headless frame captures.
