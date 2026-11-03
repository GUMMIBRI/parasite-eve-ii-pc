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

## Runtime loading of the arrays (started)

`tools/port/convert_asset_sites.py` rewrote 3,655 sites in 205 source files from
`type name[] = { #include "assets/X.inc" };` into
`#ifdef PE_EMBED_ASSETS <original> #else type name[COUNT]; #endif` followed by `PE_ASSET_BIND("X", name);`
(`include/port/asset_bind.h`). `src/port/asset_loader.c` walks the bindings registered in the `__peassets` section,
looks each key up in `src/port/asset_parts_table.c` (layout facts, generated by `tools/port/regen_assets.sh`, not
committed) and fills the array from the package that `disc_assets.c` reads from the disc image. Rotation words are
a plain copy (the bit-field struct has the same layout); grid cell tables become host pointers into their cell
lists.

Comparison builds: `-DPE_EMBED_ASSETS=ON` keeps the build-time includes. `PE2_DUMP_ASSETS=<file>` writes a hash per
binding. For the 33 bindings linked into the executable today (model parts, collision patches, grid faces, cells
and a pointer table) the embedded build and the disc-loaded build produce **identical dumps**. The other sources are
not linked yet, so their bindings are covered by `verify_asset_parts.py` (3,655 of 3,655) rather than by a run.
Still embedded: 39 sites the converter does not match and 553 includes that no decoder covers yet (measured 2026-11-03, below).

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

## Remaining generated includes (measured 2026-11-02)

Converted to runtime loading: 3,731 package parts plus 76 flat assets (all animation, grid-header, model, collision-patch and flat `EMBEDDED` includes); 56 bindings are linked in the current executable and match the embedded build byte for byte (hash dump).

Still compiled from generated C text in `build/include/assets/` (not flat byte ranges: they are initialised structs with pointers and enum/macro references, written by `gen_room_inc.py` and the USD-to-C generators):

| Group | Files | Size of generated C |
| --- | ---: | ---: |
| rooms | 679 | 13.1 MB |
| enemies | 246 | 13.2 MB |
| weapons | 83 | 9.4 MB |
| characters | 92 | 3.5 MB |
| encounters | 40 | 1.3 MB |
| ui | 5 | 43 KB |

These need a per-type decoder that rebuilds the host structs from the disc bytes (pointer fields become host pointers into the loaded blobs), not another `PE_ASSET_BIND`. Group by type (room descriptors, spawn tables, enemy model sets, weapon sets) and do one decoder per type, verified against the embedded build as above.

### Recount (2026-11-03, after the clip and model work)

Counting every `assets/*.inc` include (also those bound with `PE_ASSET_BIND_AUX`, and generated sources that bind
inside), what no decoder covers yet is **553 includes**:

| Family | Includes | Notes |
| --- | --- | --- |
| rooms | 455 | `gen_room_inc` output read from the extracted assets: maps, spawns, placements, tables, music; structs with pointers |
| animation banks (enemies, weapons, characters, encounters) | ~105 | `AnimationSet*` slot tables that point at the static clips; they hold no disc bytes, only slot layout from the asset table |
| inventory catalog, one motion table | 2 | |

The room includes are the real remaining work. The banks can stay compiled. Dumps match: 4,176 bound arrays, 809 of
them models, embedded and disc-loaded builds identical.

### After the flat room arrays (2026-11-03)

468 pointer-free room arrays (music, rewards and every other table of numbers in rooms, actors and stage overlays) now
load from the disc: 4,644 bound arrays, embedded and disc-loaded dumps identical. What remains is **450 includes**:

- ~210 animation banks (`*_bank`, enemies, weapons, characters, encounters and rooms): `AnimationSet*` slot tables
  that point at the static clips. They hold no disc bytes and can stay compiled.
- ~230 room includes with pointers: events (38), geometry, lights, surfaces, action triggers, view boundaries and
  placements (~20 rooms each), per-room declarations, occluders, markers, spawns, jukebox, scores and waves.
- inventory catalog and one motion table.

These need per-type decoders (disc record with 32-bit addresses to host structure with pointers).

### After the pointer decoders (2026-11-03)

Room structs with pointers load from the disc too: the numbers are read by generated per-layout decoders
(`tools/peassets/room/decoders.py`, `PE_ASSET_OP_DECODE`) and the pointers are set by generated fixups, so the
topology stays code and the data comes from the disc. 4,924 arrays are bound; the embedded and disc-loaded builds give
identical dumps (the dump hashes a pointer as its target array and offset, so two executables compare).

**347 includes remain.** 239 are animation banks (`AnimationSet*` slot tables, no disc bytes) and 18 are declaration
files (types and macros). About 75 carry data: room events (38), geometry (22), markers, spawns, header, jukebox,
waves, one object, surface and action-trigger table, the inventory catalog, one encounter, one enemy and one motion
table.

### After the single structs and const tables (2026-11-03)

5,850 arrays are bound and load from the disc; embedded and disc-loaded builds give identical dumps. **272 includes
remain**, and only one carries disc data:

- 241 animation banks (`AnimationSet*` slot tables: no disc bytes, only which clip sits in which slot);
- 30 declaration files (types, macros, forward declarations: no data);
- `inventory/catalog` (44 KB of item text and a table of pointers to it): needs a text decoder.

One more table (`actor_341700_motion_142DC`) is bound but its actor is not linked yet; `verify_asset_parts.py` covers
it. So the data left in the build is the item catalog, plus whatever the globals and `asm_data.c` hold (the next
blocker for a binary release).
