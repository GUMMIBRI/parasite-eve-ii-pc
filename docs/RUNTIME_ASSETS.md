# Runtime asset loading (Phase 0 gate)

## Today

Game data reaches the executable at **build time**. `assets/` (554 MB, git-ignored, extracted from the user's disc)
feeds `tools/peassets`, which writes `build/include/assets/*.inc` (4,834 files, 59 MB of C initializers) and about
400 headers; game sources `#include` them (4,968 includes). The same applies to `asm/` (git-ignored, from the
disc) which `tools/port/gen_asm_data.py` turns into `src/port/asm_data.c`.

So the repository holds no game data, but **a built binary does**. That is fine for development and unacceptable for
a release: a downloadable build must read the user's disc images at run time.

## Inventory of the generated includes

| Kind | Files (approx.) | Content |
|---|---|---|
| Model parts: `verts`, `normals`, `partVerts`, `skeleton`, `stream` | 390 / 268 / 184 / 184 / 184 | `SVECTOR`, `TmdBone`, part counts, TMD command stream words (patched in place by the game) |
| Area/room data: `records`, `indices`, `table`, `faces`, `cells` | 451 / 451 / 206 / 206 / 206 | Collision and area tables |
| `collision`, `image` | 23 / 16 | Collision blobs, font and image tables |

Everything above is plain integer arrays; the host layout equals the PS1 layout except where a record contains a
pointer (then the generator already emits symbol references).

## Plan

1. **Manifest instead of bytes.** At configure time, `peassets` emits for each include a manifest entry
   (symbol, disc file id, byte offset, element type, count) with no game data. The include is replaced by a
   zero-initialized definition `T sym[N]` placed in a writable section.
2. **Boot loader.** `src/port/asset_loader.c` reads each manifest entry from the mounted disc (both discs, as
   `fs` does) once at startup, or lazily per package, and fills the arrays. The disc reader already exists
   (`libcd`); decompression (`lzss.c`) already exists.
3. **Pointer-bearing records** (`CapFile`, `AreaRecord`, `AnimationSet`, ...) stay behind parse layers; see
   `docs/SIZE_AUDIT.md`.
4. **Verification.** A test mounts the real disc and compares every loaded array with the build-time include for
   the same symbol (byte for byte) before the includes are deleted.
5. **Remove the toolchain.** Delete `ninja_config.py`, `configs/`, `linkers/` and the `build/include/assets` rule
   once nothing includes a generated file. `gen_asm_data.py` follows the same path: its output moves to the manifest.

## Why this is not done yet

Step 1 touches 4,968 include sites and the generator that writes them; step 4 needs the real disc in CI. It is the
largest remaining piece of Phase 0 and should be done before any binary release.
