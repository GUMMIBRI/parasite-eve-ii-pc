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

## Where the bytes come from

- The ~90 catalogued embedded assets (`asset_data.EMBEDDED_ASSETS` with `include`: images, CLUTs, camera and movie
  paths, morph data, font glyphs, `mc_save_header`, `spu_voice_block`) each name a source container
  (`actor_121300.pe2pkg`, `main.exe`, ...), a size and an element width (`u8`/`u16`/`u32`/`TmdBone` or a struct
  `layout`). These map one to one onto manifest entries.
- The bulk (model `verts`/`normals`/`partVerts`/`skeleton`/`stream`, area `records`/`indices`/`faces`/`cells`) is
  written per model or room from a `.pe2pkg` package at a recorded offset (the first line of each include says
  e.g. `model at 0x7FC4`). The runtime reads the same package from the disc and the same offset.
- Header census of the 4,834 generated includes: 1,804 `animation at 0x…`, 1,030 `grid header at 0x…`,
  798 `model at 0x…`, 23 `collision patch array at 0x…` (all from a named `.pe2pkg` at an offset, so manifestable
  as (package, kind, offset)), and 33 from raw files in the asset store. The per-kind body (nested records, pointer
  fields in animation and grid tables) is written by the generators in `tools/peassets`; the loader has to
  reproduce each one, which is the real work of step 2.
- A runtime lookup needs the disc location of each `.pe2pkg`/`main.exe`; the CDF tree in `asset_data.py` carries the
  disc ids and sha1s (no data), so the manifest can be generated without game data.

## Manifest generator (done)

`tools/port/gen_asset_manifest.py` writes a data-free JSON manifest from the generated includes, the CDF tree in
`asset_data.py` and `assets/USA/stages.json`. It covers all 3,655 includes that name a package (include file,
package, kind, offset) over **203 packages, every one located on the disc** (disc folder, disc file number, chunk
name; the sha1 of the on-disc payload where the catalog has one). 146 resolve through the catalog; 32 through
`stages.json` (stored file name -> TREE file id); 25 room packages (`akropolis_*`, `mist_*`, `shelter_*`) through
`stages.json` folder entries -> TREE folder id plus file. Next: the C reader and the per-kind body writers.

## Disc reader (done, verified)

`src/port/disc_assets.c` (`include/port/disc_assets.h`) reads the game's CDF containers straight from a disc image:
cue sheet -> BIN (raw 2352-byte sectors) -> ISO 9660 root -> `STAGE0.HED` / `STAGEn.CDF` tables -> chunk chain ->
package chunk -> one-shot LZSS decode. It is synchronous and independent of the game's asynchronous CD queue.
`tools/port/verify_disc_packages.py` compares every package of the manifest with the extraction
(`assets/USA/pe2pkg/`): **all 203 packages read from the two disc images are byte-identical** (disc 1 and disc 2).
Build the tool with `cmake --build build-port --target pe2_discread`.

## Part descriptions (done, verified)

`tools/port/gen_asset_parts.py` (run with `venv/bin/python`, it imports `ninja_config`) asks the build's own planning
functions which models (184), animation sets (451) and collision grids and patches (211 + patches) the C sources
embed and writes one record per generated include: package, load address, byte offset and size inside the decoded
package, element type and an operation (`copy`, `rotation` for the packed animation words, `grid_table` for the
32-bit cell addresses). 3,655 records cover exactly the 3,655 includes that carry a package header.
`tools/port/verify_asset_parts.py` decodes the package bytes with an independent description of each element type
and compares the numbers with the include: **all 3,655 reproduce their include**. The records contain layout facts
only, no game data.

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
