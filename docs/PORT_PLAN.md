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

0. **Foundation.** CMake and PsyZ submodule; compile `src/main` on the host; drop the matching toolchain once nothing depends on it. *Done:* CMake/PsyZ, `src/main` builds as `game_main`, matching hacks and GTE MIPS asm removed. *Left, gated:* `ninja_config.py`, `configs/` and `linkers/` still generate the asset includes `game_main` reads, so they go with the runtime loader (phase 2); `src/main/hasm/*.s` stays as the reference for the C rewrite (phase 1); `DEFINE_ALIAS` goes with the overlay registry (phase 2). Sources outside `src/main` are not yet compiled.
1. **Boot to title.** Memory, task system, disc image mount (both discs), `fs`/`cdcmd` on PsyZ, LZSS and TMD in C, pad, fonts, `title` overlay.
2. **Overlays.** Module registry, naming, runtime data loader; first room with Aya and collision.
3. **Gameplay.** Actors, combat, items, menus, by family; verify against emulator traces (`tools/gametrace`).
4. **Sound and movies.** SPU sequencer, XA, STR through MDEC.
5. **Product.** Saves, settings, crash reports, HD/widescreen/60 Hz (from the first port), packaging.

Throughout: native tests per module and headless frame captures.

## Status

Phase 0 is closed with the toolchain removal gated: `ninja_config.py`, `configs/`, `linkers/` go with the runtime loader (phase 2). Phase 1 is under way: `src/port/psyq_host.c` supplies host versions of the libcd/heap calls and an approximate `MatrixNormal`. Linking `game_main` into the executable currently reports 343 undefined symbols, nearly all overlay tasks and handlers (`src/` outside `main`), the `hasm` routines (`fsDecompress*`, `tmd*`), and a few PsyZ gaps (`DecDCTvlc*`, `BreakDraw`, `ContinueDraw`, `freep`).

## TMD stream renderer (hasm) — scoping notes

Remaining handwritten assembly: `tmdSkipStreamRecord` (28 lines), `Tmd_DispatchStream` (57), `tmdDrawModelStream` (163), the `Prim32`/`Prim3A` pre-transformed handlers (~280) and `Tmd_StreamHandlers_Ops` (2,400, 20 handlers). LZSS is already ported (`src/port/lzss.c`, `tests/lzss_test.c`).

Blocking design point: a TMD stream is a sequence of `{kind, handler, dimensions}` 12-byte records and the dispatcher `jalr`s the 32-bit code address stored in word 1 (`tmd.c` writes `tmdSkipStreamRecord` etc. into the stream). On a 64-bit host that word cannot hold a function pointer, so the stream needs a handler id (index into a table) instead; `tmd.c` writes the id, `Tmd_DispatchStream` indexes the table. Packet links also assume 24-bit OT addresses in `addPrim`; use PsyZ's pointer-width primitives. Decide this before porting the 20 handlers, and port them against `tests/gte_compat_test.c`-style reference arithmetic, then compare against emulator frame captures (`tools/gametrace`).

Decision (ordering tables): on the host an ordering table is an array of PsyZ `OT_TYPE` entries (pointer-width tag and length), and packets are PsyZ `POLY_*` structs, so packet sizes come from `sizeof`, not the console's 28/36 bytes. `workspace->ot` stays `u_long*` and is indexed in `OT_TYPE` units. Every other place that indexes `gGpuCurrentOt` as `u_long` needs the same treatment in the 64-bit audit. `Prim32`/`Prim3A` (4 entries) are ported in `src/port/tmd_prim.c` with `tests/tmd_prim_test.c`.

Host syntax survey of every `.c` outside `*.inc.c` (clang, `-D__psyz -DSKIP_ASM`): 523 of 566 pass. The rest are shared-source templates that need per-package build parameters (`WEAPON_INDEX`, `DRYFIELD_TIME`, ...), a few missing animation clip symbols, and four `SECTOR_SIZE` uses — all part of the overlay build design (phase 2). `SECTION(...)` is a no-op on the host and `<rand.h>` includes were replaced by `<stdlib.h>`.
