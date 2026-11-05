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

0. **Foundation.** CMake and PsyZ submodule; compile `src/main` on the host; drop the matching toolchain once nothing depends on it. *Done:* CMake/PsyZ, `src/main` builds as `game_main`, matching hacks and GTE MIPS asm removed. *Toolchain:* the build reads committed layout sources and the disc at run time (regeneration lives at the git tag `pe2-layout-tooling`); `src/main/hasm/*.s` stays as the reference for the C rewrite (phase 1); `DEFINE_ALIAS` goes with the overlay registry (phase 2). Sources outside `src/main` are not yet compiled.
1. **Boot to title.** Memory, task system, disc image mount (both discs), `fs`/`cdcmd` on PsyZ, LZSS and TMD in C, pad, fonts, `title` overlay.
2. **Overlays.** Module registry, naming, runtime data loader; first room with Aya and collision.
3. **Gameplay.** Actors, combat, items, menus, by family; verify against emulator traces (`tools/gametrace`).
4. **Sound and movies.** SPU sequencer, XA, STR through MDEC.
5. **Product.** Saves, settings, crash reports, HD/widescreen/60 Hz (from the first port), packaging.

Throughout: native tests per module and headless frame captures.

## Status (updated 2026-11-03)

**Phase 0** (foundation) is done: CMake and PsyZ, `src/main` as `game_main`, matching hacks and GTE MIPS asm removed,
and the build no longer depends on the decomp toolchain. Everything the compiler reads from the disc extraction is now
committed as layout only (`include/generated`, 633 files, 4 MB; `src/port/asm_data.c`, `asset_parts_table.c`): types,
sizes, decoders and registrations, with no game data. Cloning, building and playing need CMake and a C compiler plus
the user's discs. The matching compile/assemble/link/objdiff/checksum graph, its patches and helper scripts are deleted; `ninja_config.py`, `refresh_layout.sh` and the regeneration scripts are removed from the tree too. What remains of `configs/` and `tools/buildsteps/gen_overlay_*.py` is read by the asset tools (`main/gameplay/title.yaml` for the load addresses of memory slots, `overlays.toml`, `sym/`, and the `gen_overlay_configs` helper functions); `tools/check/suite.py` fails the same steps as at the tag (missing text assets, `clang`, node), and no others. The last state that could regenerate the layout from a disc is the git tag `pe2-layout-tooling`. Phases 1 and 2 are well advanced,
because the work was allowed to cut into them:

- Disc data: 27,419 arrays (clips, models, room structs, item catalog, and 10,622 globals converted from the
  disassembly) load from the user's discs at run time. Checked once, with `PE2_DUMP_ASSETS`, against a throwaway comparison build that still had the data compiled in (the `PE_EMBED_ASSETS` option; removed afterwards, the shipped game never carries disc data) with both discs mounted: 16,891 of 16,891 bindings agree, except two Underpass arrays whose hash differs while a byte comparison (`PE2_DUMP_KEY`) shows them identical (a packed-short artifact of the dump). Behaviour check on the same input route (`make_gallery_input.py --enter-cafeteria --frames 20000 --aim-cycle 180`, `PE2_DUMP_VRAM`): at pad tick 6000 the VRAM of two disc-loaded and two embedded runs is byte-identical; at tick 11000 runs of the *same* build already differ by about 10,000 bytes (frame timing), and disc vs embedded differ by about 5,900, i.e. within that noise.
- The default build links every overlay package with all variants (since 2026-11-03; before that only the Akropolis and a few packages); it links
  (669 clashing names get private names, `cmake/overlay_renames.cmake`) and shows Dryfield, Dryfield by night, the
  mine and the Shelter/Neo Ark rendering, with the player walking (see below).
- Host menu and disc validation follow parasite-eve-pc (page order, rows, style).

Open, and owned by later phases rather than Phase 0:

- **Cold-start timing:** at pad tick 6000 of the cafeteria route every run of the disc, embedded and fresh-clone builds is byte-identical, except the very first run of the fresh-clone binary (cold disc cache), which differed in a 64-byte block near rows 105-109; its second run matches exactly. Not a data or binary difference (malloc scribbling changes nothing); likely a timing-dependent frame. Not traced further.

- **Phase 2:** the module registry's run-time part (load a stage's packages by name, reset package state on a stage
  change); crossing rooms/stages during play is unobserved.
- **Phase 5:** saves beyond the host card, the first game's extra options (antialiasing, model filtering, frame
  interpolation, lighting, HD packs) and its Mods page.

## TMD stream renderer (hasm) — scoping notes

Remaining handwritten assembly: `tmdSkipStreamRecord` (28 lines), `Tmd_DispatchStream` (57), `tmdDrawModelStream` (163), the `Prim32`/`Prim3A` pre-transformed handlers (~280) and `Tmd_StreamHandlers_Ops` (2,400, 20 handlers). LZSS is already ported (`src/port/lzss.c`, `tests/lzss_test.c`).

Blocking design point: a TMD stream is a sequence of `{kind, handler, dimensions}` 12-byte records and the dispatcher `jalr`s the 32-bit code address stored in word 1 (`tmd.c` writes `tmdSkipStreamRecord` etc. into the stream). On a 64-bit host that word cannot hold a function pointer, so the stream needs a handler id (index into a table) instead; `tmd.c` writes the id, `Tmd_DispatchStream` indexes the table. Packet links also assume 24-bit OT addresses in `addPrim`; use PsyZ's pointer-width primitives. Decide this before porting the 20 handlers, and port them against `tests/gte_compat_test.c`-style reference arithmetic, then compare against emulator frame captures (`tools/gametrace`).

Decision (ordering tables): on the host an ordering table is an array of PsyZ `OT_TYPE` entries (pointer-width tag and length), and packets are PsyZ `POLY_*` structs, so packet sizes come from `sizeof`, not the console's 28/36 bytes. `workspace->ot` stays `u_long*` and is indexed in `OT_TYPE` units. Every other place that indexes `gGpuCurrentOt` as `u_long` needs the same treatment in the 64-bit audit. `Prim32`/`Prim3A` (4 entries) are ported in `src/port/tmd_prim.c` with `tests/tmd_prim_test.c`.

Host syntax survey of every `.c` outside `*.inc.c` (clang, `-D__psyz -DSKIP_ASM`): 523 of 566 pass. The rest are shared-source templates that need per-package build parameters (`WEAPON_INDEX`, `DRYFIELD_TIME`, ...), a few missing animation clip symbols, and four `SECTOR_SIZE` uses — all part of the overlay build design (phase 2). `SECTION(...)` is a no-op on the host and `<rand.h>` includes were replaced by `<stdlib.h>`.

## Handwritten assembly: done

All of `src/main/hasm` is now C (`src/port/lzss.c`, `tmd_dispatch.c`, `tmd_prim.c`, `tmd_ops.c`), with native tests (`lzss_test`, `tmd_model_test`, `tmd_prim_test`, `tmd_ops_test`). The `.s` files were removed; they remain in git history (`bd42083` and earlier) as the reference. The tests use hand-built streams, so each handler still needs a comparison against real model data and emulator frame captures. The link now reports no undefined TMD symbols; the remaining ~1,200 are overlay tasks and handlers (phase 2).

## Overlay build (experiment)

`cmake -DPE_ALL_OVERLAYS=ON` additionally compiles the 422 non-gameplay source files that build on the host (list in `cmake/overlay_sources.cmake`, the other 40 are in `PE_OVERLAY_SOURCES_PENDING`). With that the link reports 689 undefined symbols and no duplicate definitions yet (the linker reports undefined symbols first). The remainder are the 40 pending room/shared-source templates, a few PSY-Q libraries PsyZ lacks (memory card, `PadInitDirect`, SPU reverb, `MulMatrix0`, `StCdInterrupt`-style CD calls) and data defined only in the splat `asm/` data files.

Link survey after the PSY-Q placeholders (`PE_ALL_OVERLAYS=ON`): 660 undefined symbols — 54 are `func_8070xxxx` / `D_8072xxxx` names that `main` calls by overlay address (listed in `configs/USA/sym.main.imports.txt`), about 450 are `g*` data tables (task tables, room descriptors) whose definitions sit in files not yet compiled, and about 110 are overlay tasks (`akropolis*`, `dryfield*`, `actor*`). All three groups are the overlay module registry's job (phase 2): give each package a name space, resolve cross-package references by name instead of address, and pull in the 40 template files with their per-package parameters.

## Variant units (done)

`tools/port/gen_overlay_variants.py` reads `configs/USA/overlays.toml` and `configs/USA/generated/*.yaml` and writes
`cmake/overlay_variants.cmake`: 119 variant units (a package compiled from another package's shared source), each its
own object library with the slot's `-D` parameters (`WEAPON_INDEX`, `GRENADE_PISTOL_VARIANT`, ...) and, for
`aliases`, a force-included `cmake/aliases/<unit>.h` defining `PACKAGE_ALIASES`. `cmake --build build-port --target
overlay_variants` compiles all 119 on the host. They are not linked yet: the same global names recur across packages,
so linking needs per-package isolation (one module per package) rather than one flat executable.

## First link and boot (done)

The executable links and `gameMainRun` runs on the host. Mechanics:
- `src/main/main.c` (the PS1 stack switch) is excluded; `src/port/main.c` calls `gameMainRun` directly.
- Unported overlay symbols are weak placeholders in `src/port/unresolved_stubs.c`
  (`tools/port/regen_stubs.sh` regenerates it from the linker's undefined list). A function placeholder logs
  `unresolved call: <name>` and aborts, so the first missing piece names itself. Real definitions win over them.
  This list shrinks as overlay modules are wired; it is scaffolding, not part of the end state.
- PS1 RAM is the host array `gHostRam`; fixed game addresses go through `PS1_RAM_PTR`. The 1 KiB scratchpad is
  `gHostScratchpad` (cursor slot is pointer-sized). macOS arm64 refuses a small `__PAGEZERO`, so mapping RAM at
  0x80000000 is not an option.
- Current state: the boot loop reaches `fsScanIsoDirectory` and waits for the CD. Next: the runtime disc loader.

## Boots from a disc image (done)

`parasite-eve-ii-pc <disc.cue>` (or `PE2_DISC`) mounts the image through PsyZ and runs the cold-start path:
ISO directory scan, startup image read, MDEC decode and fade, then the main loop (idling at `VSync`).
- PsyZ fork additions: `Psyz_PollInterrupts` / `Psyz_CdPump` deliver CdSync/CdReady callbacks and VBlank callbacks
  (the game relies on interrupts); busy-wait loops poll it (`mdecStepImageDecode`).
- OT tags are `OT_TYPE` on the host; manual tag splicing was replaced by `addPrim` in `model_lighting.c`,
  `sprite_link.c`. Depth math divides by `GPU_OT_TAG_BYTES` (4), not the host entry size.
- `src/port/mdec_vlc.c`: STR v2 VLC decoder reused from the sibling PE1 port.
- `src/port/globals.c` (generated, `tools/port/gen_globals.py`): the 438 globals the PS1 link placed by address.
- 732 overlay functions are still weak placeholders that abort with their name on first call.

## Opening movie (plays)

PsyZ fork: movie reads (`ReadS` with ADPCM on and a 2340-byte size flag; the stream bit 0x100 does not survive
the 8-bit mode byte) now start both the XA audio path and a data read; ADPCM sectors are skipped on the data side.
`StCdInterrupt` is implemented (it was a stub): it fills the St ring (32-byte header entries followed by 2016-byte
payload slots), marks a frame ready through `data_ready_callback`, and leaves the sector unread when the ring is
full, which holds the drive until `StFreeRing`. The opening FMV plays with correct colours.
Open: bright highlights show streak artifacts (MDEC dequantisation/IDCT clamping in PsyZ or the VLC port);
the XA soundtrack and the end of the movie have not been checked.
Tools: `tools/port/probe.sh` (run + window-only capture), `tools/port/crash.sh`, crash handler in `src/port/main.c`.

## 32 vs 64 bit audit

`tools/port/size_audit.sh` rebuilds every `STATIC_ASSERT_SIZEOF` as a real assertion (`-DPE_SIZE_AUDIT`) and lists the structs whose host size differs from the PS1 size. At the time of writing it lists 130 of them (e.g. `GfxCoord`, `FsImgBuffers`, `GameActor`, `GameSession`, `CdCmdQueue`, `AreaVariant`). A struct on this list is only a problem when something treats it as PS1 bytes: disc/asm data (handled by `tools/port/gen_asm_data.py`), scratchpad or save overlays, `sizeof` arithmetic, GPU packet strides, `u_long` members. The list is the work queue for the clean-up.

## Runtime TMD descriptor decoder

`src/port/tmd_source.c` decodes the 0x24-byte PS1 `TmdSource` record into a
native descriptor using a package image and its original load address. It
borrows fixed-width geometry, bone and stream arrays from the aligned writable
image (little-endian hosts). It rejects truncated arrays/streams, invalid
addresses, cyclic bone hierarchies and missing group terminators; decoding
leaves the original disk callback words intact and sets the native descriptor
unresolved. `tmd_source_test` covers relocation, signed bone translations and
malformed packages.

This is not wired into package loading yet. Model globals are still empty
placeholders; the recorded player-model creation crash is not resolved by this
component alone. Before creating models from it, the loader must retain the
package image and convert the PS1 primitive-buffer capacities/region offsets to
host packet sizes. Geometry-index validation also remains outside this decoder.

## MIST startup wiring and image memory

The native overlay target now includes the Akropolis/MIST stage tables, the
shooting-gallery room and courses, Pierce's gallery controller, and the target
actors. This replaces the empty stage object-room table (which lacked its end
marker) and the initial room's collision/surface/view placeholders. Generated
fallback globals/stubs were refreshed against these compiled definitions.

Image slots generated from room instances now translate fixed RAM reservations
through `PS1_RAM_PTR`, as does `GRAPHICS_IMAGE_SLOT` for the map modules. The
resident image workspace pointer uses the same RAM mapping at 0x801D7000.
`FsImgBuffers` now stores 32-bit words, retaining the 153600-byte RGB16 frame and
7680-byte strip stride on LP64. `image_workspace_test` checks the frame/strip
extents and the relationship between area reservations and the resident image.

Verified with disc 1 and `PE2_SKIPINTRO=1 PE2_AUTOPRESS=300 PE2_TRACE=1`: startup
passes stage object-state seeding, image-memory setup and room surface loading.
It then reaches player equipment restoration and faults while creating the
unwired M93R weapon model. This is the next runtime blocker; the room is not yet
playable. The earlier model-crash attribution to Aya's body was too broad: the
current trace identifies the equipment-model spawn under `playerActorRestoreEquipment`.

## M93R and native model packet layout

M93R's source, model and player animation bank are now compiled into the native
overlay target. `src/port/tmd_layout.c`, called before model handler resolution,
computes packet capacities using PsyZ `sizeof(POLY_*)` and translates projection
pass destinations from PS1 packet offsets to host packet offsets. The mapping
accounts for trailing packet padding, mixed primitive types, two-layer packets,
and the unlit pre-pass's single destination halfword. It validates destinations
before mutating the stream. State 2 in `handlersResolved` means the layout is
ready; ordinary handler resolution finishes with state 1, so shared sources
are expanded once. The existing 65535-byte half-capacity limit is enforced
rather than silently truncating the cached u16 size.

Tests: `tmd_layout_test` covers mixed packets, layers, unlit projections,
idempotence, sources with existing native-size reservations, and atomic failure.
`tmd_layout_assets_test` checks real generated M93R and Aya 10400 body streams:
M93R's half is 2016 host bytes (1616 on PS1); Aya's is 29280 (22360), including
7680 bytes of pre-transformed packets (5800 on PS1). The seven earlier native
tests also pass.

The first disabled gallery mount is a room placement with spawn byte 0xFF,
parented to the scene task rather than a course controller. Its rejection path
now decrements a live-target count only when owned by the active controller;
the scene's NULL work must not be interpreted as gallery work.

Disc-1 new-game verification now passes equipment-model creation and that
mount's teardown. Next runtime fault: `capRelocateFile` dereferences raw PS1
address 0x80190010. The resource-bundle directory still overlays native pointers
on 16-byte disk entries (`_FsCdfResourceEntry`), and CAP headers/sequence slots
also contain 32-bit serialized references. Both need fixed-width decoding and
explicit lifetime management before dialogue/room startup can finish.

## CAP resources and message transport

The CDF bundle directory now retains its fixed 16-byte disk entries and maps
both destination addresses to host RAM. Resource byte lengths bound lazy CAP
decoding. `src/port/cap_asset.c` copies a CAP payload, expands its command index
and interleaved 12-byte command/text slots into aligned native slots, and keeps
text/glyph bytes in the owned copy. Native command counters persist in the
cached view; original file offsets are never overwritten. Empty sequence tables,
null command entries, terminators and commands following terminators are covered.
The decoder checks ranges, slot framing, record counts, command targets and text
terminators; it does not validate every glyph index or command's gameplay meaning.

Gameplay CAP and the shared room-caption implementation resolve the same cached
view through `cap_resource.c`. Views are released when a folder/bundle directory
invalidates the old resources, after old playback/caption users have ended, as
required for the source RAM too. Global CAP selections are cleared at that boundary.
`_capSequenceRecordAt` now uses native pointer arithmetic instead of truncating
a pointer through the union's 32-bit offset member.

Task-message transport now uses `TaskMessageWord` (`intptr_t` on the host) for
both payload registers, including stored `TaskMessageArg.value` and the pointer
adapters. Integer handlers still consume their low 32-bit values. The dispatcher
lives in `src/gameplay/task_message.c` so its ABI can be tested independently.
EVS callback arguments also retain pointer width. This fixes the opening script's
stair-climb request, whose payload address was previously truncated in dispatch.

Validation: all 139 extracted retail CAP payloads decode, plus malformed-data,
counter, slot-stride, owned-copy and cache-invalidation fixtures. The CAP decoder,
resource cache and message tests pass ASan/UBSan; all 12 native test executables
pass. New-game startup logs successful CAP loads for bundle slots 18 (30 commands,
157 records) and 20 (22 commands, 95 records), then advances past the former EVS
crash and movie processing. The run remained alive for 2m41s before being stopped
for inspection. This is not a playable-start claim: a capture of that process's
window was black, with unsupported GPU command FF warnings earlier in the log.
The inspected state was stage 1 / area 20 / view 15 / warp 7, eventState 1,
CAP idle, movieStep 0, CD queue step 5. Next work is the entry script/view-load
state and native GPU command storage, verified against an actual rendered frame.

## First rendered MIST view: CD header-only skips

The black startup view was blocked on a CDF read, not merely on presentation.
The inspected head request was LOAD_FILE (0x21), step 5, for the initial view.
`gFsNextReadSector` stayed at 75066 (chunk end 75071), payload phase SKIP (0xFF),
while the filesystem repeatedly resumed the chunk. Its skip callback consumes
only the sector header. PsyZ kept that sector buffered until a payload read,
so the next interrupt treated payload bytes as another header and retried.

PsyZ's `Psyz_CdPump` now discards an unread payload after a callback consumed
its header, advancing to the next sector. A callback that reads nothing still
holds the sector for retry, preserving full STR-ring backpressure. The callback's
sector number is captured after `CD_ready`, since it may skip XA audio sectors.
The change is in the PsyZ submodule (`psyz/src/psyz/libcd.c`), not a forced
filesystem completion in the game. `cd_pump_test` builds a synthetic MODE2 disc
and checks no-read retention, consecutive header-only skips, and a subsequent
header+payload read. All 13 native test executables pass, including 139 CAP files.

Disc-1 new-game verification now finishes the view read: filesystem/image status
0xFF and CD queue step 0. A window-only capture of that process shows the MIST
shooting-gallery background, target, and Aya's model, replacing the black view.
The development capture is `build-port/mist-cd-fixed.png` (not a shipped asset).
Remaining visible issues: corrupt HUD colours/geometry and white parts of the
model; the GPU log reports unsupported FF/04 commands around transitions.
No claim of correct gameplay/rendering is made yet. Inspect native packet
lengths and merged/fixed-size sprite packets next; the current generic `setlen`
override assumes that a pointer's storage type is also its emitted packet kind,
which is not true for every reserved SPRT slot.

## Native sprite views and font palettes

GPU packet-origin tracing identified malformed merged room-sprite packets:
`SpritePacket.packed` still started with a 4-byte PS1 tag, whereas PsyZ `SPRT`
starts with a native link and length. Stores of position/UV/size overwrote the
native header, including MargePrim's packed-command marker. That made the GPU
reader treat sprite coordinates as opcodes (FF/04/08). The packed view now uses
PsyZ `O_TAG` on the host, with real offset assertions for RGB, XY, UV, CLUT and
size. Packet arena strides remain `sizeof(SpriteDrawModePacket)`. The temporary
origin tracing was removed; there is no GPU-backend workaround hiding bad commands.

HUD HP/MP and target-HP caps reserve full SPRT slots but emit SPRT_8 commands.
Their setlen calls now name the emitted prefix type, so the host length adapter
keeps three GP0 words rather than sending an unused fourth word. Tests exercise
the production SpritePacket layout, merging before later attribute writes,
copying cached packets, and the emitted command words/NOP marker.

The resident text palettes were another LP64 issue: u_long arrays doubled the
pixel bytes and the inferred upload widths. The glyph palette upload at
(976,511) consequently requested 96 colours and was rejected as out of bounds.
`src/main/text_palette.c` now owns the packed u32 palette arrays and uploader
(previously in textutil.c); their data is aligned for the SDK's word-pointer
API. Font/glyph rows upload 64/48 RGB555 colours, and the test captures actual
LoadImage arguments, widths and adjacent halfword values. This follows PE1's
separation of native command headers and fixed-width GPU data.

All 15 native test executables pass, including all 139 CAP payloads. The new
sprite and palette tests also pass ASan/UBSan. A disc-1 new-game run through
8100 pad ticks had no unsupported-command or out-of-bounds-upload messages,
and its window capture (`build-port/mist-palettes-fixed.png`) shows readable
HP 100 / MP 50 over the shooting gallery. The earlier capture is retained for
comparison. Rendering/gameplay are still incomplete: white geometry remains
near the target, and input, animation, collision and scene transitions need
runtime verification beyond this startup view.

### Native modal ordering tables and shooting-gallery captions

A finite-input disc-1 run reached the Pierce training menu and the first course.
The earlier static shooting-gallery view was not evidence of free player control:
Start/Cross autoplay skips the introduction and chooses the first (fixed-view)
course, which then waits in a modal caption. A direction held during that caption
correctly did not move the player. Free movement/collision/combat remain unverified.

The modal path had two independent OT faults. Its resident banks allocated
u_long words rather than GsOT_TAG entries, overlapping the native tag extents.
They now reserve actual tags. PsyZ GsClearOt also built a forward chain rooted
at bucket zero; PE2 terminates bucket zero after clearing, making every higher
bucket unreachable. It now clears in reverse and publishes the last tag as the
draw root, matching the descending ordering tables used in the PE1 port. The
backend change is in the PsyZ submodule alongside the existing CD-pump fix.
The shared caption background reserves a DR_MODE slot but emits one E1 word;
its setlen now names the DR_TPAGE prefix to preserve that one-word command.

The new ordering_table_test checks two separate 64-tag banks with outer canaries,
all descending links, and traversal through a primitive inserted in caption
bucket two after explicitly terminating bucket zero. All 16 native test binaries
pass (including 139 retail CAP files); the new test also passes with its test
object instrumented by ASan/UBSan. The SDK library itself uses its normal build.
The rebuilt disc-1 runtime reached over 5000 pad ticks without unsupported GPU
commands or out-of-bounds uploads. build-port/mist-modal-final.png shows the
readable PROGRAM START modal over the HP/MP HUD. White triangles near the target
remain. The Pierce-facing view also still showed striped texture/image corruption.

Development input retains the existing legacy pad-poll clock (both ports count):
PE2_AUTOPRESS_UNTIL optionally ends Start/Cross autoplay; PE2_PAD_HOLD is a hex
PS1 pressed-button mask applied only on port zero during the half-open interval
[PE2_PAD_FROM, PE2_PAD_UNTIL). These optional hooks allow finite, repeatable input
without leaving Start pressed repeatedly throughout a gameplay check. A reproduced
caption checkpoint uses PE2_FAST=1 PE2_SKIPINTRO=1 PE2_AUTOPRESS=300
PE2_AUTOPRESS_UNTIL=4000 with disc 1; course/menu timing still depends on loading.

### Reference-emulator input workflow: native capture/replay foundation

The user identified the PE1 workflow: record input in the MCP DuckStation fork,
replay it in the native port, and compare state checkpoints. That is the next
reference path; native autoplay alone is not a fidelity oracle. This session
found PE1's `../parasite-pc/tools/scripts/emu_boot_test.py` AI-port/GDB driver
and PE2's existing tools/gametrace GDB probes. The DuckStation executable/source
and its MCP recording schema have not yet been located, and no DuckStation
comparison is claimed. A location was requested from the user.

PE2_PAD_RECORD and PE2_PAD_REPLAY now capture/replay port-zero raw pad replies.
Their native interchange format is `PE2PAD 1` followed by one line per sample:
zero-based decimal sample index, a space, and all raw pad bytes as contiguous
hex pairs. This preserves status, controller type, active-low buttons and analog
axes; it is deliberately not labelled a DuckStation-native format. The counter
advances once per valid port-zero sample, unlike the older two-port debug tick.
Replay replaces the whole sample after other development overrides. Missing or
malformed input fails explicitly; clean EOF exits successfully, so it cannot
silently fall back to keyboard input. Writes flush every complete record.

Example, from the repository root (use a fresh output path for each recording):

    PE2_SKIPINTRO=1 PE2_AUTOPRESS=300 PE2_AUTOPRESS_UNTIL=700 \
      PE2_PAD_RECORD=build-port/route.pad ./build-port/parasite-eve-ii-pc rom/image/SLUS-01042.cue
    PE2_SKIPINTRO=1 PE2_PAD_REPLAY=build-port/route.pad \
      ./build-port/parasite-eve-ii-pc rom/image/SLUS-01042.cue

Keep disc, build and non-input startup options equal. Sample indices are input
polls, not proof of matching console game frames: loading, intro skips and state
checkpoints must be aligned when converting the emulator's recording. No native
state or renderer comparison against the original has been completed yet.
The pad_trace_test verifies exact digital/analog round trips, frame order,
unsupported versions, truncation, bad hex/length, numeric overflow, EOF, and
unchanged output on malformed samples. It passes ASan/UBSan and strict compiler
warnings with the production codec instrumented.

A runtime recording of 1,293 port-zero samples (34 bytes per reply), including
Start/Cross press/release edges and subsequent neutral input, was replayed in
a second disc-1 process with autoplay disabled. Simultaneous recapture matched
the original file byte for byte (`cmp`), and replay exited 0 at sample 1293.
All 17 native test binaries pass. This verifies the native input hook and codec;
it does not establish deterministic game-state equivalence or emulator parity.

### Rendering investigation: authored foreground whites, loaded view-15 textures

The prior reports calling the white shapes by the target "white geometry" were
premature. They are authored foreground sprites, not a model, shadow, or a
Metal-only artifact. For mapped view 14, SpriteSource entries 7/8/9 copy rectangles
(96,176,16,32), (96,144,16,32), (96,208,16,32) from
assets/USA/rooms/mist/shooting_gallery/view14_page_1.png to screen (112,200),
(128,200), (144,200). Composing those exact atlas rectangles reproduces the
white silhouette (build-port/view14-authored-white.png). All 138 pixels with
RGB channels >=240 in that composition matched bright pixels at their prescribed
positions in the software-renderer framebuffer (each native RGB555 channel >=29).
Disabling the ground shadow and hiding only the equipped weapon in a disposable
debug run did not remove the shape. Those debugger-only changes were not written
to code or assets, and the process was terminated after inspection. No removal,
colour correction, or geometry workaround is justified by the current evidence.
The original emulator remains the authority for final presentation parity.

At mapped view 15, raw texture uploads and actual GPU VRAM readback agreed for
VRAM x896..1023/y0..254 and the two used 256-entry palette rows at y255/256.
Decoded runtime texture pages 1/2 using rows 0/1 matched the extracted asset PNGs
at every pixel after reducing RGB to the original five-bit channels (zero
mismatches for all four 128x256 images). PNG expansion and alpha conventions
differ, so this is a RGB555-colour comparison, not a PNG byte/alpha comparison.
Both 320x240 GPU framebuffer readbacks and a later window capture showed the
Pierce-facing scene without the earlier stripes, including readable "PIERCE /
Music?". The software renderer separately displayed the jukebox and M93R weapon
selection menus. These were separate input-timed runs, not synchronized emulator
or backend state comparisons. The earlier striped capture was during scene/menu
progression; its cause and precise readiness remain unproven. Do not claim a
new texture-data fix, and do not keep treating the stripes as a proven persistent
failure of a fully loaded view. The current stable capture is
build-port/view15-window-current.png. No runtime rendering code changed during
this investigation; it narrowed the next fidelity checks to reference playback
and actual movement/combat instead of deleting authored graphics.

### Fixed VECTOR3 ABI: first real target damage and destruction

The firing smoke exposed a common native-layout fault: `include/decomp/types.h`
still declared VECTOR3 as three `long` fields. LP64 made that a 24-byte vector,
while GTE XYZ loads/stores and MATRIX.t use three consecutive 32-bit words.
A yaw-lock breakpoint showed a correctly placed aim origin (-6650,-1258,2796)
but a corrupted target displacement (-1610612728770,279550831366306,508026782932).
The same path passed negative squared distances to SquareRoot0. The first
12-HP tutorial target remained at full health despite ammunition use.

VECTOR3 now uses s32 fields, preserving the console's 12-byte contract on the
host. A real native static assertion protects it (independent of the port's
disabled pointer-bearing console layout assertions). This fixes direct GTE
interoperability and MATRIX.t aliases throughout gameplay, rather than masking
the aim symptom or changing target hit points. The GTE test now exercises both
an actual XYZ load/translated store and the production GRAPHICS_MATRIX_TRANSLATION
alias with adjacent canaries. Before the type change it failed eight checks,
including damaged matrix-adjacent canaries; afterwards it passes. All 17 test
executables were rebuilt and passed, including 139 retail CAP files. The extended
GTE test also passes ASan/UBSan (test/compat code instrumented, SDK library normal).

The identical 12,000-sample input was replayed from a new disc-1 session using
the software renderer. A breakpoint in the production target hit-mark path
confirmed the first target fell from HP12 to HP6 on an actual hit. At replay EOF,
the course had advanced from phase8/spawnIndex1/kills0 to phase10/spawnIndex2
with kills[10]=1, one live subsequent target, and 5 loaded primary rounds. The
new target was still at HP12. The replay exited 0 and the uninterrupted fixed
run logged no SquareRoot0 diagnostics, crashes or unresolved calls. The capture
build-port/mist-first-target-hit.png shows the subsequent off-centre target and
ammunition count. This proves one target's damage/destruction and tutorial
progression, not complete combat, free movement, all course waves, Metal parity,
or synchronization with DuckStation. Continuous Square in this smoke does not
exercise deliberate reacquisition of the next off-centre target.

Reproduce the exact input (all synthetic input, no gameplay state edits):

    python3 tools/port/make_gallery_input.py build-port/course0-fire.pad
    PSYZ_HEADLESS=1 PE2_SKIPINTRO=1 PE2_PAD_REPLAY=build-port/course0-fire.pad \
      ./build-port/parasite-eve-ii-pc rom/image/SLUS-01042.cue

The generator's default output was compared byte for byte with the input used
for both pre-fix and post-fix investigations. Do not add PE2_FAST when reproducing
this software-renderer run: its movie-end toggle restores AUTO timing, whereas
headless defaults to limitless. Game state, not exit0 alone, is the progression
criterion. Debugger observations changed no live gameplay state in these runs.

### Empty lock scans and course-zero wave progression

Releasing and reacquiring aim exposed a reproducible native null write in
_playerActorSetTargetNode (address 0x9). Both worldTargetFindLockNode and
worldTargetFindLockNodeFromPad may return NULL, and the normal input handler
passes their result to the setter. The old code always wrote the new node's
`targeted` byte after transferring the actor's pointer. Host selection now
preserves the transferred NULL selection and skips that null mark store. It
still clears the old node's mark and does not change aim mode or unrelated node
flags. The console path retains the original unconditional store.

The production setter is now isolated in src/gameplay/player_target.c so the
new player_target_test exercises actual acquisition, cycling, empty initial
scans, clearing an existing selection, marking the same node again and
reacquisition, while retaining unrelated state. Normal input paths call this
same setter. All 18 native test executables pass; the complete new setter/test
also passes ASan/UBSan. The core runtime rebuild and diff checks pass.

The input generator accepts --aim-cycle N (0 preserves the original held-aim
route); it releases Square for 15 samples per cycle and otherwise holds it
while tapping R1. Its default output remains byte-identical to the previous
12,000-sample fixture. The new run is:

    python3 tools/port/make_gallery_input.py build-port/course0-reacquire.pad \
      --frames 20000 --aim-cycle 180
    PSYZ_HEADLESS=1 PE2_SKIPINTRO=1 PE2_PAD_REPLAY=build-port/course0-reacquire.pad \
      ./build-port/parasite-eve-ii-pc rom/image/SLUS-01042.cue

Before the null-store fix this exact file crashed during target acquisition.
After it, the full replay reaches EOF at sample20,000, exits0, and returns to
view8 after training. A breakpoint on _mistShootingGalleryFinishCourse proved
normal course timeout: timeLeft0, scriptFrame537, spawnIndex50, kills[10]=20,
with five live targets still leaving play. A separate breakpoint in the result
panel callback after cleanup showed liveTargets0, kills[10]=21, trainingActive0,
and BP200 (unchanged). The callback was reached, but a visible result/bonus
panel or reward credit was not verified; do not infer those from its invocation.
The capture build-port/mist-course0-result-0.png shows the post-course view with
Aya near Pierce. The fixed complete log contains no crash, unresolved call,
SquareRoot diagnostic, unsupported GPU command or out-of-bounds upload message.
These are software-renderer/native input results, not DuckStation parity or
proof of free movement, every course, or the rest of the game.

After controller teardown, gMistShootingGalleryControllerTask can retain its
old task address. Debug checkpoints must verify a live course task/work before
reading it; the EOF probe observed reused task storage with NULL work. The
active finish/result breakpoints above inspected still-owned work, not that
stale post-course pointer. No gameplay state was edited in the replay runs.

### Walking and first gallery airlock: real unarmed/P08 animation bank

Post-course input now verifies locomotion and collision independently of firing.
From the view8 return pose (-6800,128,2950), forward input was blocked by the
station rail; backward input moved Aya to (-8199,128,2950), where the booth's
wall stopped further travel. Turning and walking along the station changed Z
to5700, with matching yaw changes. The extracted collision faces show that the
route outside the booth goes through its decontamination door, rather than
through its wall. No collision flags, poses or story state were edited.

Approaching the first airlock trigger and pressing the normal interaction button
performed the room reload to area20/warp5/view5, but then crashed in
animationResetSlot with a NULL sets[1] on the restored actor. This was another
missing native package, not an invalid request: resourceVariant3 and weapon0
select animation-bank row1, gP08PlayerAnimationBank, which was still a zero-filled
placeholder. The default executable now links the existing manifest-configured
pe_var_p08__p08 object (WEAPON_INDEX4 and the package's original attack/effect
parameters). Its real authored bank supplies unarmed Aya's locomotion as well
as the P08 animations. No idle-clip substitution or null-animation fallback was
added. P08 and M93R both export their own authored gAyaIdleClip; P08's compilation
renames its copy gP08AyaIdleClip, keeping each resident bank bound to its package
copy and avoiding a duplicate link symbol. Generated assets are unchanged.

The exact previously crashing replay now exits0 at sample21,654, after entering
warp5/view5 with actor pose(-8000,129,-1800), yaw2048, weapon0 and resourceVariant3.
Subsequent ordinary movement inside the airlock also works. The attempted second
door remains in view5 at(-8800,129,-3078); a transition to the outside corridor or
parking lot is not yet proven. build-port/mist-airlock-p08-fixed.png captures the
airlock after this movement. The real P08 bank and both idle-clip copies have
initialized data symbols in the linked executable. The application rebuild,
all18 native tests, and diff checks pass. These tests do not establish full P08
combat or other weapon packages, and the runtime proof uses the software backend.

The verified first-door route is reproducible without debugger state edits:

    python3 tools/port/make_gallery_input.py build-port/leave-booth.pad \
      --frames 20000 --aim-cycle 180 --leave-booth
    PSYZ_HEADLESS=1 PE2_SKIPINTRO=1 PE2_PAD_REPLAY=build-port/leave-booth.pad \
      ./build-port/parasite-eve-ii-pc rom/image/SLUS-01042.cue

The generated output was compared byte-for-byte with the file used for the
pre-fix crash and successful first-door replay. The generator's default firing
fixture is also unchanged. The later second-door navigation experiment is not
included in this verified option.

### Resident room collision state: second airlock door

The second door failure was not a quad/facing geometry error. A production-query
fixture accepts the captured body and trigger in both room and camera frames.
At replay EOF the action list head was NULL while the gallery's static triggers
still carried LINKED and ENABLED. A late query breakpoint received no calls.
`worldCollisionResetListsAndGrid` deliberately drops heads without walking nodes;
the PS1 overlay reload restores initial record state, but native room data stays
resident. Consequently the next room setup skipped every previously linked node.

Native initial room setup now resets the selected room's trigger and occluder
links and transient flags before binding them. Trigger hit latches are cleared;
authored geometry, parameters, kind and LAST markers survive. The reset operates
on the new room's known-live arrays, avoiding traversal of retired owner storage.
Ordinary camera rebinding retains its existing behavior.

The same 23,438-sample replay now passes both airlock doors: the last warp request
is area20/warp2/roomState1 and Aya ends in the outside corridor at
(-11252,130,-3040), yaw3072. No poses, collision flags or story state were changed
through the debugger. Parking entry remains unverified and its native module is
not linked yet. This input is reproducible with:

```
python3 tools/port/make_gallery_input.py build-port/input/course0-airlock2.pad \
  --frames 20000 --aim-cycle 180 --leave-airlock
PSYZ_HEADLESS=1 PE2_SKIPINTRO=1 \
  PE2_PAD_REPLAY=build-port/input/course0-airlock2.pad \
  ./build-port/parasite-eve-ii-pc rom/image/SLUS-01042.cue
```

`action_trigger_test` exercises the production sphere/quad query, facing rejection,
scratch cursor restoration and three cycles of resident resource reset and
production trigger/occluder linking, including backlinks and preserved geometry.
All 19 current test executables pass, including CAP asset checks on 139 files.
The generated extended input matches the previously used fixture byte for byte.

### Parking MIST: resident room, actors and verified entry

The native overlay set now includes all five MIST parking translation units,
parking Pierce and Jodie (actor_213100). The shared post-cutscene update table
from Square is compiled once as resident native data, using the existing
generated authored table; Square retains its console definition only. This
resolves a shared room-cutscene dependency without substituting empty data.

Parking and Jodie each own copies of generic-named Aya clips. Source-specific
compile definitions preserve those separate copies and all their references;
Jodie's Euler-placement message handler is also namespaced against Pierce's.
The resulting symbols are strong definitions, not fallback stubs.

An ordinary input replay now completes training, passes both airlock doors,
triggers the mandatory control-room story, uses Start to execute its authored
skip script, enters parking, and walks through its entrance corridor. No
runtime poses, story flags or collision state are written by the debugger.
The 28,262-sample checkpoint reaches stage1/area19/roomState1/warp1/view2,
Aya (12012,129,-5053), idle and accepting movement. An additional 360 Up samples
and 60 neutral samples reach view5 at (5856,131,-5053), yaw3072. Both parking
Pierce and Jodie have live body/attached-model tasks. The room and glow callbacks
are the real parking implementations. VRAM inspection shows Aya, the corridor,
parking background, car and HUD; build-port/mist-parking-walk.png is the capture.
This does not yet verify conversations, shopping, telephone or departure.

A longer dialogue-only experiment progressed from the main briefing into a
subsequent Pierce conversation: continuous confirm presses can reopen dialogue,
so a stationary actor during that experiment was not evidence of a stuck scene.
The documented parking regression deliberately uses the normal Start skip.

```
python3 tools/port/make_gallery_input.py build-port/input/course0-parking-walk.pad \
  --frames 20000 --aim-cycle 180 --enter-parking
PSYZ_HEADLESS=1 PE2_SKIPINTRO=1 \
  PE2_PAD_REPLAY=build-port/input/course0-parking-walk.pad \
  ./build-port/parasite-eve-ii-pc rom/image/SLUS-01042.cue
```

The generated input matches the verified fixture byte for byte; the prior
--leave-airlock output is unchanged. The full native executable builds, all 19
current test executables pass (including 139 CAP assets), and git diff --check
passes. Complete parking interactions and the onward story route remain work
for subsequent iterations.

### Jodie shop: purchase, dialogue completion and return to parking

Ordinary input now verifies the parking room-state transition (1 to 2), Jodie
conversation, shop opening, category navigation, quantity confirmation, actual
inventory/currency updates, shop closure, remaining dialogue and return to room
state 1. The replay buys one Buckshot pack: BP changes from 200 to 140 and the
carried item172 stack becomes 10. The final checkpoint is area19/roomState1/view2,
Aya (8448,129,-3828), state0/mode0, eventState0 and uiOpen0. The purchase persists
across the room-state transition. No gameplay patch was needed for this path.

Initial probes stopped before Jodie's remaining lines had been confirmed. The
CAP record index advanced when further confirmations were supplied; this was
not a deadlock after shopping. The completed input backs Aya away as dialogue
ends to prevent later confirmation presses from reopening the interaction.

`make_gallery_input.py --shop-purchase` reproduces all 38,478 samples from title,
through training and parking entry, to this final checkpoint. Its existing
--enter-parking output remains byte-identical. The original firing and airlock
routes retain their existing defaults.

New `tools/port/replay_checkpoint.py` runs the executable under LLDB, stops at
replay EOF, and reads location, carried inventory, BP, player state/position and
UI/event state directly through debug information. It does not evaluate target
functions or change target data. It requires both a captured checkpoint and a
clean replay EOF, retains the full debugger log, and fails any unmet --expect
condition. An earlier eventState=0 assertion correctly failed while dialogue
was still active. The complete generated route passes these 11 assertions:

```
python3 tools/port/make_gallery_input.py build-port/input/shop-purchase-smoke.pad \
  --frames 20000 --aim-cycle 180 --shop-purchase
python3 tools/port/replay_checkpoint.py build-port/input/shop-purchase-smoke.pad \
  --expect location.stage=1 --expect location.area=19 \
  --expect location.roomState=1 --expect location.view=2 \
  --expect bp=140 --expect carried.172=10 --expect uiOpen=0 \
  --expect eventState=0 --expect actor.state=0 --expect actor.mode=0 \
  --expect 'actor.position=[8448,129,-3828]' \
  --log build-port/shop-purchase-smoke.log
```

The screenshot build-port/mist-shop-ammo.png shows the real ammunition list,
prices, preview, BP and descriptions. Python compilation and git diff --check
pass. No C implementation changed in this iteration; the previously passing
19 C tests were not rerun unnecessarily. Telephone, departure selection and
entry into Akropolis remain unverified.

### Akropolis departure and plaza entry: contiguous trigger storage

Linked the real Akropolis plaza and police-officer modules. The plaza owns its
own generic-named Aya idle clip; a source-specific host definition namespaces
that copy instead of substituting the M93R copy. The executable builds with
strong plaza, police and animation definitions.

Ordinary input after the Jodie purchase now approaches Pierce, opens the
three-choice departure prompt, selects Ready, continues dialogue and reaches
stage1/area5/roomState1/view2. Rapid confirmation in early probes selected the
default Not yet choice before capture; a single confirm plus a reveal interval
makes the prompt observable. This was not a missing CAP/menu implementation.

The first successful departure exposed a memory overwrite before sprite setup.
A hardware watchpoint on the plaza's hide-image batch caught
peResetRoomCollisionResources writing outside its trigger span. The retail
symbols are adjacent: helicopter trigger at0x801991A4 (one record), sergeant at
0x801991F0 (one), entrance/examine at0x8019923C (four). Only the sixth record has
LAST. The generated separate C objects did not retain this adjacency on the
host, so both a reset and the original sentinel-based room binder could run
into unrelated data. Merely setting LAST on the first trigger would omit five
authored interactions and is not an appropriate fix.

The room C generator now identifies adjacent private trigger objects whose
scan continues through LAST and emits one native aggregate with typed aliases
for their existing names. Original record values, names, array/scalar uses and
console definitions are retained. A real C static assertion verifies the
aggregate has exactly the total record size. For plaza the host span is 1+1+4.
Other room layouts are not claimed comprehensively verified by this change.
Gallery regeneration is unchanged; parking's authored definitions are unchanged
(the older generated cache only has two additional SDK include lines).

The same 45,340-sample input now reaches clean EOF. The checkpoint reports
Aya (23230,129,1598), state0/mode0, eventState0, uiOpen0, BP140 and Buckshot10.
The real sergeant/rookie controllers, ambient lights and plaza traversal/camera
sequence are live. build-port/akropolis-entry.png shows Aya beside the car and
police vehicles with the movie background and letterbox. This verifies entry,
not completion of the subsequent plaza scenes or entry into the tower.

```
python3 tools/port/make_gallery_input.py build-port/input/akropolis-entry-smoke.pad \
  --frames 20000 --aim-cycle 180 --enter-akropolis
python3 tools/port/replay_checkpoint.py build-port/input/akropolis-entry-smoke.pad \
  --expect location.stage=1 --expect location.area=5 \
  --expect location.roomState=1 --expect location.view=2 \
  --expect uiOpen=0 --expect actor.state=0 --expect actor.mode=0 \
  --log build-port/akropolis-entry-smoke.log
```

The new route matches the verified fixture byte for byte and the previous
parking/purchase routes remain unchanged. action_trigger_test now includes the
actual generated plaza declarations and triggers and checks addresses, terminal
marker, authored origins, reset and production list linking. Its instrumented
production collision/list sources pass AddressSanitizer and UndefinedBehavior-
Sanitizer. All 19 test executables pass, including 139 CAP files; the full build,
Python compilation and git diff --check also pass.

### Plaza scenes to west elevator hall: officer initialization and absent layouts

The native officer swap crashed when approaching the sergeant. Both the live
trace and console assembly show that task spawning attaches a TMD body but does
not dispatch its callback. The swap immediately writes playState through the
new task's still-NULL work pointer (console offset0x4F0, native0x5A8). The animated
body's first callback also retains the incoming NULL work pointer across its
initialization before falling through to its update. On native builds the swap
now dispatches that known model's first callback after placement and before
accessing work; its advanced state prevents duplicate initialization. The body
callback refreshes work after initialization. Console code is unchanged.

The same input now completes the sergeant scene, including swaps back to the
culled model. A read-only checkpoint confirms plaza eventStep2, idle actor and
eventState0, and action kinds [0,2,3,6,7]: the one-shot sergeant trigger is gone.
The replay then completes the helicopter-wreck scene and entrance-officer scene
and starts the intended reload into area17 (west elevator hall).

Linked the actual west-elevator-hall room module, including its doors, effects,
collision, backgrounds and arrival animation. This room has no area placement
variant table. Both area-load passes already return complete for a NULL layout,
but read its fields before checking NULL. Console assembly confirms that load
before the branch. Native builds now select a NULL cursor without accessing the
absent layout; console instruction ordering remains intact. No dummy placement
or resource table is substituted.

New area_resource_test compiles the production area_cd.c and verifies absent
layouts, empty tables, absent resources, real base and additional-file requests,
file-number splitting and waiting for CD idle. The test reproduces the original
NULL read with ASan/UBSan when compiled against the pre-fix source, and passes
with both sanitizers against the fixed source.

The generated --enter-tower route matches the verified 59,830-sample fixture.
It reaches stage1/area17/roomState1/view2/warp1 with Aya (-1388,129,922), state0,
mode0, uiOpen0, eventState0, BP140 and Buckshot10. The room and door-leaf tasks
are live, and build-port/west-elevator-entry.png shows Aya and the hall with HUD.
No debugger edits to gameplay state were used. Earlier --shop-purchase and
--enter-akropolis output is byte-identical.

```
python3 tools/port/make_gallery_input.py build-port/input/akropolis-tower-smoke.pad \
  --frames 20000 --aim-cycle 180 --enter-tower
python3 tools/port/replay_checkpoint.py build-port/input/akropolis-tower-smoke.pad \
  --expect location.stage=1 --expect location.area=17 \
  --expect location.roomState=1 --expect location.view=2 \
  --expect eventState=0 --expect uiOpen=0 \
  --expect actor.state=0 --expect actor.mode=0 \
  --expect bp=140 --expect carried.172=10 \
  --log build-port/akropolis-tower-smoke.log
```

replay_checkpoint.py additionally reports plaza event progress and active action
kinds when the checkpoint is on the plaza, enabling scene-completion assertions
without inferring them from the actor's pose. The full build and all 20 current
C test executables pass (including CAP checks on 139 assets); Python compilation
and git diff --check pass. Movement beyond the west hall, the tower's later
rooms and combat remain to be verified and ported.

### Central square and telephone: actor work and prompt-root ownership

Linked the real square room and its Grinning Stranger actor. The square's
cutscene sound-task pointer has its own host symbol, preserving its overlay
state independently of parking's copy. The already-resident authored area-update
table retains one host definition.

The first square load exposed a NULL work read in the Stranger's initial
callback. It captured task->work before its initializer allocated it, then used
the old pointer in the joint/light phase. Native code now refreshes that local
pointer after initialization and stops if allocation failed. The sequence's
teardown also returns immediately after taskKill on the host, before lighting
could access the freed work. The console paths remain unchanged. Actual replay
now covers actor initialization, idle animation, departure and task retirement.

Using the telephone exposed a second lifetime error in the generic
itemPickupActionPromptTask: it stored the UI root in firstChild without making
the root its child. uiStartTreeClosing consequently could not clear that handle
when it detached the root. Twelve callbacks later the prompt's taskKill walked
the already-collected root and called a NULL exit handler. Native code now uses
taskReparent when adopting the root. UI closure detaches it through the existing
parent relationship before it is freed; no global task-kill fallback is added.
This applies to item, transfer and save-point prompt roots.

New item_prompt_lifecycle_test compiles the production item_notice.c with mocked
UI/session boundaries. It exercises an item cancellation and a save-point
confirmation, independently collects the UI root before the close delay ends,
and checks request completion and safe owner teardown. The pre-fix production
source fails the ownership assertion; the fixed source passes with ASan/UBSan.
This is not a claim that actual memory-card save/load has been verified.

The full 75,032-sample --square-telephone input enters the square from the west
hall, completes the arrival and Stranger/telephone scene, approaches the phone,
uses the prompt, completes the story dialogue and walks away. Final state:
stage1/area1/roomState1/view8, idle Aya (-5989,-2072,1932), eventState0, uiOpen0,
BP140 and Buckshot10. The telephone-scene flag is1, its story-dialogue counter
is1, the pending-call flag is0 and the Stranger task is gone. The saved warp is1;
the session's cached warp remains7. The real square room, reflection and
telephone/glow logic run. build-port/square-telephone.png captures the square
when ringing started.

```
python3 tools/port/make_gallery_input.py build-port/input/square-telephone-smoke.pad \
  --frames 20000 --aim-cycle 180 --square-telephone
python3 tools/port/replay_checkpoint.py build-port/input/square-telephone-smoke.pad \
  --expect location.stage=1 --expect location.area=1 --expect location.roomState=1 \
  --expect eventState=0 --expect uiOpen=0 --expect actor.state=0 --expect actor.mode=0 \
  --expect square.telephoneSceneSeen=1 --expect square.telephoneDialogueCounter=1 \
  --expect square.telephoneCallPending=0 --expect square.savedWarp=1 \
  --expect square.strangerAlive=false --expect bp=140 --expect carried.172=10 \
  --log build-port/square-telephone-smoke.log
```

--enter-square is also available for the 61,514-sample entry checkpoint, before
the Stranger scene. Both generated routes match the verified fixtures byte for
byte. Earlier tower, plaza and purchase inputs are unchanged. The full native
build and all 21 C tests pass (including 139 CAP assets); Python compilation and
git diff --check pass. The patio route, stairs and subsequent combat remain
unverified and are the next part of the tower path to port.

### Native left stairs and patio arrival (2026-11-02)

The left square stairs work with moving interaction input. A stationary approach
stops short of the narrow stair facing quad; continuing with Up + Circle (run)
and Cross pulses starts the authored turn/climb without changing geometry,
collision flags, actor poses or story flags. The generated --square-stairs route
has 77,206 samples and ends idle at (-4641,-1470,-3144), square view4. Fourteen
checkpoint expectations pass, including retained telephone progress and inventory.
The previously observed floor offset is explained by the existing 128-unit
collision preparation bias in playerActorUpdateMove; it was not patched.

The default native overlay set now includes patio and its authored actor
resource dependencies: patio SWAT member/leaping strangers, actor_00700,
actor_300700 (both units), actor_401000 and the actor_101900 variant built from
actor_01900. Package-local duplicate exports are namespaced per source, keeping
their references inside the same package. The variant's two forced includes use
CMake SHELL grouping so deduplication does not discard its second -include flag.

DEFINE_ALIAS now emits underscore-prefixed symbols for native Apple builds.
The previous assembler spelling left the patio's Grinning Stranger descriptor
unresolved. nm verifies that _gActor01900GrinningStrangerTaskDesc and
_gActor101900GrinningStrangerTaskDesc have the same defined data address. The
console and other host paths retain their prior spelling.

Before linking patio, real automatic entry stopped in
worldCollisionLoadSurfacePushbackFlags on missing surface data. With the actual
room and actor resources linked, --enter-patio reaches stage1/area3/roomState1,
variant1/view2/warp4 and finishes arrival at (3907,129,506), actor state0/mode0,
eventState0/uiOpen0, BP140 and Buckshot10. This 83,506-sample route matches the
exploratory input byte for byte. It verifies arrival, not the full SWAT scene,
following combat or later patio variants.

Reproduce:
```
python3 tools/port/make_gallery_input.py build-port/input/patio-smoke.pad \
  --frames 20000 --aim-cycle 180 --enter-patio
python3 tools/port/replay_checkpoint.py build-port/input/patio-smoke.pad \
  --expect location.stage=1 --expect location.area=3 --expect location.roomState=1 \
  --expect location.variant=1 --expect location.view=2 --expect location.warp=4 \
  --expect actor.state=0 --expect actor.mode=0 \
  --expect 'actor.position=[3907,129,506]' --expect eventState=0 --expect uiOpen=0 \
  --expect bp=140 --expect carried.172=10 --log build-port/patio-checkpoint.log
```

The full native build and all 21 C tests pass after these changes, including
139 retail CAP files. Python compilation and git diff --check pass. DuckStation
MCP is not exposed in this session and no fork was found locally; these are
native replay observations, not original-emulator parity results. The next
runtime target is the patio opening/SWAT sequence and its combat.
Final arrival was repeated after rebuilding: 13 state expectations and clean EOF
pass. build-port/patio-arrival.png was visually inspected; it shows Aya, the
patio background and the HUD after fade-in. The real patio SWAT member task and
room light-effect tasks are live at that checkpoint.

### Patio SWAT scene, first live enemy fight and reciprocal contact fix (2026-11-02)

The real patio opening runs from its automatic trigger, including its EVS
sequence. It finishes at the authored (1452,1,593) placement (native collision
preparation gives Y129), view3, with the player back in normal mode. No scene
skip input or story-state writes were used.

The first sphere/capsule weapon contact exposed a native address truncation:
world_collision.c stored a sphere pointer in two 16-bit response fields. When
the single-contact capsule replaced its hit, it reconstructed only 32 bits and
crashed while releasing the old sphere's reciprocal entry. Native responses now
retain the full body pointer in the existing eight-byte response union; the
console retains its original halfword encoding. The direction's third halfword
must not be cleared after writing the native pointer because it overlaps the
upper address bits. Contact stride remains 24 bytes.

New pair_contact_test exercises production sphere/capsule intersection and
contact writing with real heap addresses above 32 bits, then replaces the hit
with a second sphere and repeats it. It verifies reciprocal entry release,
LAST/body-index flags, full pointers, scratch-stack balance and unchanged
response/contact sizes. The pre-fix production source fails the first retained
pointer assertion; the fixed source passes with ASan/UBSan. The test includes
the private production TU and links the production segment placement/body
position code, rather than adding a test API to the game.

With the fix, the same input kills the patio Stranger (HP -6, death-burn state21)
and earns BP48: BP140 becomes188. Carried 9mm ammo (item160) changes from100 to68;
Buckshot remains10. The retained corpse task is expected: death-burn hides the
model and releases rewards but does not destroy its task. The follow-up trigger
then sets patio cutscene progress4 and roomState2. Continuous confirms can
reopen the nearby examine caption; the final route backs away while confirming
and then releases all input so control can be checked without an active caption.

--patio-swat implies --enter-patio and appends the opening, walk toward the
Stranger, live aiming/firing, approach to the follow-up, dialogue and backing
away. It has104,660 samples and matches the exploratory input byte for byte.
The checkpoint tool now reads patio cutscene/route progress, player HP, battle
references, actor-control state and each live actor_01900's HP/behavior state.
These are debugger reads only. Cafeteria route progress remains0: its key comes
from the east elevator hall scene, which has not been ported/verified yet.

The full native build and all22 C tests pass after the contact change, including
139 retail CAP files. Python compilation and git diff --check also pass.

The final repeated replay passes20 explicit state expectations and clean EOF:
stage1/area3/roomState2/variant1/view4/warp4, idle normal Aya at
(-3994,131,-637), eventState0/uiOpen0, HP110, BP188, ammo68, Buckshot10,
patio cutsceneProgress4, cafeteriaRouteProgress0, battleRefs0 and actorControl0.
The Stranger remains in death-burn state21 with HP-6. The software VRAM image
build-port/patio-swat-finished.png was visually inspected: Aya, the SWAT member,
background and HUD are visible with control restored. An earlier checkpoint
while the nearby examine caption was reopening showed a green horizontal strip;
this caption rendering observation remains to investigate, even though the
final idle image is clear. No DuckStation visual-parity claim is made.

```
python3 tools/port/make_gallery_input.py build-port/input/patio-swat-smoke.pad \
  --frames 20000 --aim-cycle 180 --patio-swat
python3 tools/port/replay_checkpoint.py build-port/input/patio-swat-smoke.pad \
  --expect location.stage=1 --expect location.area=3 --expect location.roomState=2 \
  --expect location.view=4 --expect location.variant=1 --expect location.warp=4 \
  --expect actor.state=0 --expect actor.mode=0 \
  --expect 'actor.position=[-3994,131,-637]' --expect eventState=0 --expect uiOpen=0 \
  --expect bp=188 --expect carried.160=68 --expect carried.172=10 \
  --expect patio.cutsceneProgress=4 --expect patio.cafeteriaRouteProgress=0 \
  --expect patio.playerHp=110 --expect patio.battleRefs=0 --expect patio.actorControl=0 \
  --expect 'patio.strangers=[{"hp":-6,"state":21}]' \
  --log build-port/patio-swat-checkpoint.log
```

The next progression target is east elevator hall (Akropolis area2) and its
cafeteria-key scene, followed by the cafeteria route. Later patrol/ambush
variants, full game completion and emulator comparison remain unverified.

### East elevator hall opening and cafeteria key (2026-11-02)

The default host overlay set now includes east_elevator_hall and its SWAT view
figure (body, attached gun, authored clips and reflection/beacon effects).
Two external development-kit functions at 0x807245E4/0x80724608 are not part of
any linked retail image. They now have explicit aborting weak diagnostics for
linking; normal gameplay calls neither because gDisplayState.debugMode is0.
They have not been implemented or silently treated as successful no-ops.

The input route continues after the completed patio fight, crosses back through
both stair chains to the square, passes below its central obstacle and enters
the east hall. Real entry triggered the opening but exposed a scene-sector
transfer bug: CdGetSector's counts are 32-bit words, while five header/payload
size calculations used sizeof(u_long), eight on this host. The 60-byte scene
header was truncated and payload destinations advanced twice as far as their
2048-byte sectors. At the crash all cached image headers were empty, view7 was
waiting for a scene image, and _gMdecSceneImageHeader was NULL. The transfer
reader now uses sizeof(u32) for both word counts and cursor increments, matching
the existing regular file-sector reader and the console's actual word size.

New scene_sector_test exercises the production reader with a three-sector
serialized image: it checks the complete header and byte-for-byte contiguous
payload, all five destination buffers, VLC/timing prefixes, guard bytes, cached
header publication, completion and reuse/forced-reload behavior. The pre-fix
production source fails its 15-word header contract; the fixed source passes
with ASan/UBSan. No null-header fallback or scene skip was added.

The next actual runtime failure was a hung automatic key pickup. Its UI used a
one-past-table pointer to reach a separately declared obtained-notice recipe.
Native nm showed the three-entry table at0x100351350, preview at0x1003513C8 and
notice at0x1003513F0: the indexed pointer selected the preview. The screen showed
two previews (with the old ammunition picture) and never closed, leaving EVS
waiting for the CAP cue. Native itemPickupPanelTask now names the obtained-notice
descriptor directly; the console expression is retained. The real notice times
out, EVS continues and the opening returns control. Post-fix scene completion
verifies the integration; no standalone UI recipe imitation test was added.

The durable --east-hall-key route has121,987 samples and matches the exploratory
input byte for byte. It passes21 state expectations and clean EOF after a fresh
run: stage1/area2/roomState1/variant1/view5/warp1; Aya idle/normal at
(4440,129,-672); eventState0/uiOpen0; BP188, HP110, carried9mm68 and Buckshot10.
The cafeteria route flag is1, its door state2 (unlocked), Parthenon/Cafeteria Key
collection bit1 is set, and patio cutscene progress4 is preserved. The opening
started flag is1 and debugMode0. No state was written through the debugger.

```
python3 tools/port/make_gallery_input.py build-port/input/east-hall-key-smoke.pad \
  --frames 20000 --aim-cycle 180 --east-hall-key
python3 tools/port/replay_checkpoint.py build-port/input/east-hall-key-smoke.pad \
  --expect location.stage=1 --expect location.area=2 --expect location.roomState=1 \
  --expect location.view=5 --expect location.variant=1 --expect location.warp=1 \
  --expect actor.state=0 --expect actor.mode=0 \
  --expect 'actor.position=[4440,129,-672]' --expect eventState=0 --expect uiOpen=0 \
  --expect bp=188 --expect carried.160=68 --expect carried.172=10 \
  --expect eastHall.cafeteriaRouteProgress=1 --expect eastHall.cafeteriaDoorState=2 \
  --expect eastHall.patioCutsceneProgress=4 --expect eastHall.parthenonKey=true \
  --expect eastHall.openingStarted=1 --expect eastHall.playerHp=110 \
  --expect eastHall.debugMode=0 --log build-port/east-hall-key-smoke.log
```

The full build and all23 C tests pass, including139 retail CAP files; Python
compilation and git diff --check pass. Visual QA is incomplete: the earlier key
popup had the stale ammunition picture, and the final view5 screenshot
build-port/east-hall-key-finished.png shows incorrect foreground texture pieces.
Do not describe this as full rendering parity. An exploratory attempt to leave
the hall reaches (-5064,2,120), scripted mode2/state1, facing3072 in view4, but
has not yet completed departure (input east-hall-leave-probe.pad,124,181 samples,
log /tmp/pe2_east_leave.log). Next work should resolve scene/foreground texture
restoration and this departure, then continue to the cafeteria with the real key.

### Correct scene texture loading and east-hall departure (2026-11-02)

This supersedes the preceding foreground-rendering and departure limitations.
The cached scene image's atlas was decoded independently from the retail stream
using the existing tools/peassets/image_codec.py. Its view5 atlas is the Coca-Cola
machine foreground, matching the normal room asset. A native payload dump had
1,970 differing bytes, all inside its first1,988-byte payload segment; every
subsequent byte, including the strip table, was identical to the disc stream.
The view4 atlas loaded normally (all32,768 pixels matched), isolating the defect
to the scene sector's split transfer rather than the sprite geometry.

Psyz's CD_getsector assumed exactly two reads: a twelve-byte sector header and
one complete payload. The scene reader instead reads that header, then a
60-byte scene-image header and the remaining1,988 bytes. The backend invalidated
the sector after the second call, so the third returned failure and left old
bytes at the start of the MDEC bitstream. It now retains a byte cursor across
all FIFO reads and retires the sector after consuming its user data. The pump
still retains entirely unread sectors and skips intentionally unread payloads.
No scene skip, replacement texture or renderer workaround was added.

cd_pump_test now reads a real emulated sector through the SDK in all three
pieces and compares every payload byte; it also verifies that a fully consumed
sector cannot be read again. The preceding two-read backend fails the third
read assertion. The corrected backend passes this test with ASan/UBSan. The
existing production scene_sector_test still verifies header/offset arithmetic,
all five buffers, prefixes, guards and reuse. All23 C tests and the full native
build pass, including139 CAP files. A proposed scene-audio completion delay was
removed after isolating the FIFO bug; it is not part of the final change.

After the fix, the view5 atlas matches the reference at all32,768 pixels using
RGB555 colour comparison (maximum channel tolerance2). The inspected software
frame build-port/east-hall-fifo-fixed.png shows the correct camera/background,
Aya, SWAT member, vending machine and foreground; the earlier mismatched pieces
are gone. This is native-versus-disc-asset evidence, not DuckStation parity.

Correct stream timing changes the last frame of the old continuous-confirm
input: it can reopen the nearby "Go! Hurry..." conversation. --east-hall-key now
backs away while finishing CAP, then releases input. Its122,457 samples end
normal/idle at (2186,130,1229), view2, with eventState0/uiOpen0, key collected,
cafeteria route1/door2, patio progress4, HP110, BP188, ammo68 and Buckshot10.
--leave-east-hall extends this to124,929 samples, walks to the real exit and
returns to the square: stage1/area1/roomState1/variant2/view6/warp2, Aya
(6258,-2071,140), state0/mode0. The departure sound now completes without any
sound-script bypass or changes to SPU voice ownership. The telephone dialogue
counter is0 because the key scene selects the next story call.

The checkpoint tool now reads the shared Akropolis route/key flags in every
stage1 room. --vram saves the full1024x512 RGB555 software VRAM directly through
debugger memory reads, alongside the state checkpoint, for reproducible image
comparisons following the PE1 test approach. It never calls target functions.

```
python3 tools/port/make_gallery_input.py build-port/input/east-hall-return-smoke.pad \
  --frames 20000 --aim-cycle 180 --leave-east-hall
python3 tools/port/replay_checkpoint.py build-port/input/east-hall-return-smoke.pad \
  --expect location.stage=1 --expect location.area=1 --expect location.roomState=1 \
  --expect location.view=6 --expect location.variant=2 --expect location.warp=2 \
  --expect actor.state=0 --expect actor.mode=0 \
  --expect 'actor.position=[6258,-2071,140]' --expect bp=188 \
  --expect carried.160=68 --expect carried.172=10 --expect eventState=0 --expect uiOpen=0 \
  --expect akropolis.cafeteriaRouteProgress=1 --expect akropolis.cafeteriaDoorState=2 \
  --expect akropolis.patioCutsceneProgress=4 --expect akropolis.parthenonKey=true \
  --expect akropolis.playerHp=110 --expect square.telephoneSceneSeen=1 \
  --expect square.telephoneCallPending=0 --expect square.strangerAlive=false \
  --expect square.savedWarp=2 --expect square.telephoneDialogueCounter=0 \
  --vram build-port/east-hall-return.vram --log build-port/east-hall-return-smoke.log
```

Next progression target: return to patio with the real cafeteria key and enter
the cafeteria. Key-picture rendering during the acquisition popup, the earlier
patio caption strip and wider rendering/audio parity remain to verify.

The generated return route was repeated with the command above: all24 state
expectations and clean EOF passed, and --vram wrote exactly1,048,576 bytes.
The earlier --patio-swat fixture remains byte-identical after adding the flags.

### Cafeteria entry, real battle and CAP packet corruption

The default native build now links the cafeteria room/effects, Boss Stranger,
Woman (202900), Rupert (310600), Grinning Stranger (210600), Odd Stranger
(401800), Rook Golem (05700), and the manifest-specific Bone Suckler 101200
variant of actor01200. Package-local message exports and the two cafeteria
contact scratch globals have distinct native names. These are the authored
implementations and placement resources, not replacement actors.

`make_gallery_input.py --frames 20000 --aim-cycle 180 --enter-cafeteria`
reproduces the 140,435-sample entry route byte-for-byte. It returns from the
east hall with the collected key, crosses the square/patio, confirms the door
choice and runs up the cafeteria approach. Walking alone stopped before the
approach; running reaches the authored door trigger without collision edits.
The verified entry is stage1/area4/roomState1/variant1/view2/warp2, Aya normal
at (-4047,-171,2514), key retained, door state3, route1, HP110, BP188 and M93R
reserve68. The previously completed patio progress remains4.

`--cafeteria-combat` adds the battle-trigger approach, original opening,
transformation and actual combat. Before the graphics correction below, its
155,610-sample replay completed the battle: Boss Stranger HP-4 (from350),
scene progress2, battleRefs0, actorControl0, no remaining cafeteria scene task,
eventState0/uiOpen0, HP74, BP388 (+200), reserve27 and Buckshot10. The route
flag remains1: the post-battle examination/follow-up is still required.
The checkpoint reader now records cafeteria scene-task states, enemy HP,
player rotation and the software renderer's retained texture window.

The room also exposed persistent green player/HUD/shadow rendering. This was
VRAM corruption, not a palette-art or texture-window discrepancy: the HUD
palette at (176,240), shadow palette at (48,266), and shared atlas pixels had
all become RGB555 0x1100. A read-only breakpoint caught an unintended GP0 fill
with colour (0,64,32), rectangle (-25,89,16384,32). The queued command immediately
before it was CAP's 0xE100020A draw mode followed by the uninitialized spare
word 0x73fe77ff7fff7fff. The forced native `setlen` mapping always set DR_MODE
to2 even when `_capDrawTextBackground` explicitly requested1. The spare word
misaligned GP0 decoding; the gradient's colour2 became a fill command.

`port/gpu_len.h` now preserves explicit DR_MODE lengths0..2 while continuing
to normalize host-struct-size-derived lengths to the two-word capacity.
`caption_packet_test` includes the production CAP function and submits its
poisoned arena packets to the real GPU backend. It uploads a texture outside
the draw area and verifies it survives the gradient. Before the correction,
the actual texture comparison fails; afterward it passes. The test also
checks one-word CAP submission and normalization of the host-size expression.
All24 native tests pass, including all139 retail CAP files.

After the packet correction, the full combat replay passes24 explicit state
expectations with the same positions, damage, ammunition, rewards and scene
progress as before. `build-port/cafeteria-combat-fixed.png` was visually
inspected: Aya's textures and HUD text render normally and the shadow is
transparent again. Both sixteen-entry HUD/shadow palettes exactly match their
intact pre-corruption values from the east-hall-return checkpoint. This is
native runtime evidence; no DuckStation parity comparison is claimed.

The follow-up is also reached with genuine input. Its action ID is0, using
the corpse triggers around (-3296,-2296), (-3480,-1368), (-3496,-2824) and
(-4034,-2092); action2 at (40,-1272) is the unrelated dead SWAT examination.
Simply releasing aim for120 samples at the combat endpoint and confirming for
8000 samples completes CAP3, the authored follow-up EVS and departure.
`--cafeteria-follow-up` generates this163,730-sample route byte-identically to
the successful exploratory recording. The actual EOF is patio stage1/area3/
roomState3/variant2/view7/warp3, idle normal Aya at (-7014,-173,-4296), yaw0.
The story now records route2, boss report1, objective4 (contact MIST), dialogue4,
door3, key retained and patio progress4. HP74, BP388, reserve27, Buckshot10,
eventState0/uiOpen0 are preserved. The post-boss patio layout spawns its two
real Strangers (HP160 each, work state0), with battleRefs2/actorControl0.
This does not verify the next patio encounter or the subsequent report call.
The durable follow-up replay passes27 explicit EOF expectations. Its full
1MiB VRAM dump also retains the intact HUD and shadow palettes after returning
to the post-boss patio. All replay fixtures/dumps stay in ignored build-port.

### Post-cafeteria patio ambush and native Game Over

Walking back from the cafeteria crosses the real ambush trigger at
(-7201,-384,-2240). The two scripted leaping actors complete their EVS scene
and hand control to the two real actor101900 enemies. A read-only checkpoint
at165,385 pad samples sees ambushSeen1, eventState0, actorControl0, two battle
references, enemy HP59/57 (from160 each), Aya HP23 and no remaining M93R ammo.
The sustained-fire attempt then dies. This is actual combat damage/ammunition
consumption; no enemies, flags or player stats were bypassed to pass a replay.
The checkpoint reader now includes the saved ambush-seen flag.

Death exposed a missing native package: gGameOverTaskDescriptors still
resolved to its zero-initialized address-global placeholder. Restart loading
spawned its empty entry0 and task dispatch jumped toNULL. The default build now
links src/aya/game_over/game_over.c, using the original screen, logo drawing,
fade/hold/exit logic and CD display resource9. The previously failing death
route reaches the screen's hold phase with HP-2, renders the centred Game Over
logo over black (build-port/game-over-fixed.png, visually inspected), then
continues to clean replay EOF176,885 without the missing-handler crash.
This verifies the death presentation and its timer-driven exit, not loading a
saved game or an entire new-game/restart session.

The newly linked package's red-flash writer also still treated the packed
FsImgBuffers strips as u_long*, writing eight bytes per two-pixel word on
LP64 instead of four. Its pointer/pixel-pair type is now u32, preserving console
word/pixel counts. game_over_image_test includes the production implementation,
fills a complete frame and checks every pixel plus an adjacent frame canary.
The pre-fix writer fails the pixel assertion; the fixed writer passes, leaving
all adjacent bytes intact. All25 native tests pass, including139 retail CAP
files. The red-flash task's gameplay creation path remains unproven; the test
verifies its buffer-writing behavior directly.

The authored ambush also permits escape. The verified
`--return-after-cafeteria` route lets the full scene play, turns at the observed
post-scene yaw and crosses the patio to its stairs. It reaches the square at
168,929 samples: stage1/area1/roomState1/variant2/view8/warp5, Aya normal/idle at
(-3395,-2072,-1381), yaw0, HP74 and reserve27. Both patio enemies were alive
when leaving. BP388 becomes378 through the original -10 escape penalty in
src/gameplay/ending.c. Cafeteria route2, report1, objective4, dialogue4,
ambushSeen1, door3 and the real key survive. EventState0/uiOpen0 and the square's
already-finished Stranger/telephone opening remain intact. The generated route
matches the successful exploratory fixture byte-for-byte.

The checkpoint reader also reports movement mode, turn-rate selector, aim
request, movement-input gate and logical held buttons. This distinguished
ordinary running/aim locomotion and an overshot stair approach from a movement
or transition failure; no player movement constants or trigger geometry were
changed to make this route pass.

The report to MIST now completes through the original square phone interaction.
`--mist-report` extends the return route across the square, runs the story call,
closes its save-point prompt and backs away. The generated180,793 samples match
the successful exploratory fixture exactly. Actual final state: stage1/area1/
roomState1/variant2/view8/warp5, normal idle Aya at (-5989,-2072,2499), yaw1056,
HP74, BP378, reserve27 and Buckshot10. Cafeteria route3/report4, objective5
("Warn Rupert"), story dialogue4, ambushSeen1, door3 and key retained are read
from live saved flags. The telephone dialogue counter is1, pending call0,
Stranger task absent, eventState0/uiOpen0, movement input enabled and no held
buttons. This verifies dialogue completion and control return, not an actual
memory-card save. Next story target: return to Rupert after the report.
The repeated durable MIST report replay passes32 explicit state expectations
and clean EOF. Its1MiB VRAM dump preserves the intact HUD/shadow palettes.

### Hallway, fountain, Q12 surface classes and extra-trigger re-entry

The native build now links hallway.c, fountain.c and fountain_water.c, plus the
manifest-specific actor301100 variant of actor01100. That variant exports both
its original gActor01100Tasks and the authored gActor301100Tasks alias; nm
confirms equal defined addresses. Only that compilation is linked, since the
manifest supplies no behavioral defines requiring a second actor01100 copy.
Hallway's package-local ActorContact_ScratchPosition has a separate native
name so it cannot collide with actor01200's storage. These are actual rooms,
water/interaction tasks, model/clip resources and actor implementations.

The post-report native route re-enters patio room3/variant3, with the authored
three rats and three moths. A combat probe kills five, leaves a rat at HP18 and
runs out of ammunition; its default-list/Enemy HP snapshot and battleRefs1
agree. That diagnostic branch is not used for progression. Starting movement
soon after arrival instead retains HP74 and ammo27 on cafeteria re-entry:
stage1/area4/roomState4/variant3/view2/warp2, player (-4047,-171,2510), with the
real Odd Stranger at HP180. The updated checkpoint reader identifies these
room enemy callbacks and reads their actual Enemy records.

Crossing the cafeteria and its north door reaches the hallway at189,299 pad
samples: stage1/area7/roomState1/variant1/view2/warp4, player normal/idle at
(-2583,-872,-623), HP64, BP378, ammo27, with eight real rats at HP18. The next
door reaches the fountain at191,479 samples: stage1/area8/roomState1/variant1/
view3/warp3, normal/idle at (-4550,129,-4603), HP64/ammo27. BP368 reflects the
original additional10-BP escape cost. The fountain's first variant has no
placed enemies. The MIST report3/4, objective5 and other saved flags survive.

The red-leaved-tree interaction sets hidden-path flag0x012 and replaces its
inspection trigger with the extra climb trigger. Its one-step climb initially
stalled forever: mode2/state3/phase1, timer0, jumpSteps1, motion pending1 and
surfaceClass0. PlayerActorPlayFootstepCue cannot advance a stride on a silent
surface. The ordinary floor there is authored class4; the upper ledge class5.

Two host bugs erased/misdecoded that class. The previous cln stub calculated
log(integer)*4096; the SDK takes and returns Q12. Retail main.exe's cor_04
routine at0x8004AB60 normalizes using GTE Lzc, then refines with six integers
1661/914/482/248/126/63 and ln2=2839 (table0x80067714). The host now implements
those integer steps in src/port/fixed_log.c, including explicit32-bit shift and
wrap behavior, instead of a floating-point approximation. cln(4096)=0,
cln(8192)=2839, cln(12288)=4500 and cln(65536)=11356 match that routine.
The old psyq_compat.h comment describing cln(2) was incorrect and is corrected.

The two production grid-pushback resolvers and SurfaceClassFromKey also shifted
by the full tagged contact key, e.g.0x100104. MIPS sllv uses its low five bits,
but that shift is undefined in C; the native optimized resolver produced a
zero mask. The expressions now explicitly mask the shift to31. fixed_log_test
first fails against the old logarithm, and still fails at the actual production
contact mask with only the logarithm corrected. With both corrections it
passes: SDK reference values, all255 nonempty eight-bit surface masks, all
eight tagged-key classes and both real contact resolvers, with scratch balance.

The separate climb record also retained LINKED/backlinks after its old native
room list was retired. fountain_trigger_test includes production fountain code
and object-list functions. It verifies first replacement and repeat enable,
then reproduces re-entry via retired heads and the existing ordinary-array
reset; before the fix the second entry lacks the climb node. EnableClimbTrigger
now checks the current live list and clears the extra record's retired links
when absent, before registration. It does not traverse old links, and repeated
enables in the same visit preserve one correctly linked record. Console logic
is unchanged. The regression passes after the correction.

All27 native tests pass, including139 retail CAP files. A full repeated native
replay then completes the previously stuck climb:202,588 samples, normal idle
Aya at (2431,-72,-5918), surfaceClass5, motion pending0, hiddenPathFound1,
climbEnabled/climbLinked true, nine action triggers, eventState0/uiOpen0,
HP64, BP368 and ammo27. The screenshot fountain-climb-fixed.png was inspected.
The obsolete jumpSteps union is reported only while actually climbing.

The upper case contains item60, the Protein Capsule (per the authored item
catalog), rather than ammunition. Its pickup succeeds and a backing-away input
closes the examination: native EOF208,194 is fountain view7, normal idle Aya at
(1983,-72,-6584), yaw1119, surface5, motion pending0, eventState0/uiOpen0,
HP64/BP368/ammo27/Buckshot10 and one Protein Capsule. The capsule has not been
used. The main objective remains5 (warn Rupert); that conversation is still
pending, and neither a native second fountain visit nor actor301100's later
fountain variant has yet been exercised by this replay.

New generator flags --enter-hallway, --enter-fountain, --fountain-path and
--fountain-protein imply the verified earlier chain. The complete generated
--fountain-protein recording is byte-identical to the successful208,194-sample
exploration; it uses actual controller input throughout, with no target-memory
writes or direct game-function calls from the checkpoint tool.
The repeated --fountain-protein route passes36 explicit EOF expectations and
clean replay completion. Full native build, all27 tests, Python compilation
and git diff --check pass with the final sources.


### Security room native entry (2026-11-02)

The default host build now links the actual security-room overlay and its
security-monitor Rupert/SWAT actor package. The room action handler returns
zero instead of an invalid bare return in its signed-result function. The
item-box model's local definition is explicitly retained for its assembler
alias; otherwise Clang removes the unreferenced static object and the alias
has an undefined target. `nm` confirms the local model and public alias have
the same address. The room contact scratch export is namespaced for resident
host overlays, as in the hallway and cafeteria packages.

The real-input branch from the established hallway checkpoint enters area6,
roomState1, variant1, view2, warp1. The 191367-sample fixture is reproducible:

```
python3 tools/port/make_gallery_input.py build-port/input/security-entry-smoke.pad \
  --frames 20000 --aim-cycle 180 --enter-security-room
```

This branch excludes the optional fountain detour. Native EOF evidence in
`build-port/security-entry-smoke.log` (16 explicit expectations on the final
build) shows normal player mode/state0, root
(-46,-871,-2758), yaw0, HP64/BP368, ammunition27, no pending scripted motion,
and event/UI state0. Both actual monitor actor callbacks are live in state1;
monitor scene/key/route flags remain zero. Entry alone does not prove the
monitor interaction, Rupert playback, panel key use, or original-console
parity. The corresponding VRAM screenshot was inspected: room backdrop,
Aya and HP64/MP30 HUD are present. All 27 existing native tests pass
(`/tmp/pe2-security-tests.log`); the native executable builds successfully.
The checkpoint observer now reports security-room scene/key flags and live
monitor task states without calling target functions or writing game memory.


A subsequent real-input approach opens the monitor panel. Evidence:
`build-port/security-monitor-centered.log`, fixture196877 samples, area6/view8,
monitor task state2, eventState1, scripted hold mode2/state1, cursor (0,-28),
speed128. Actual panel rendering was inspected in
`build-port/security-monitor-panel.png`. This fixture retains long exploratory
pauses; it is separate from the durable entry generator. No monitor scene
flags have fired at this checkpoint, so it is not a Rupert playback test.


The real-input brightness interaction also works. From the open panel,
Left70/Up24 places the cursor at(-140,-76), the brighter hotspot; 1800 samples
of periodic confirm opens/confirms its actual hotspot menu repeatedly.
`build-port/security-monitor-brighten.log` reports screenLevel252, monitor
state2, cursor speed128, no scene flags set. The brightest monitor image
(`build-port/security-monitor-bright.png`) was rendered from the dumped VRAM
and visually inspected. The saved brightness nibble is still0 while the panel
is open; the original close handler persists the selected detent.


Rupert monitor playback and clean close are now verified with real input:
`build-port/security-rupert-finish.log`, six explicit expectations. The complete
203191-sample route is reproducible byte-for-byte as the successful fixture:

```
python3 tools/port/make_gallery_input.py build-port/input/security-rupert-smoke.pad \
  --frames 20000 --aim-cycle 180 --security-rupert-monitor
```

The camera button rectangles use top-left coordinates, not centers: camera10
starts at(16,81). The initial exploratory cursor(16,80) missed by one pixel;
Down82 from(-140,-76) after Right78 reaches(16,88) and selects it correctly.
No trigger, hotspot, actor or story flag was moved or bypassed.

At final EOF the scene-seen mask is2, Rupert-finished flag1, saved brightness4,
monitor task gone, Rupert actor gone, SWAT actor still live in state1, area6,
roomState1/variant1/view4/warp1, Aya normal mode0/state0, position
(-258,-871,1559), yaw88, HP64/BP368, ammunition27, event/UI state0 and no pending
scripted motion. The retail monitor scene has played; the "Warn Rupert"
objective is still5 and no actual conversation with Rupert is claimed. The
panel key mask and sanctuary-route progress are still0: blue-key acquisition
in the hallway and its actual use at the power-supply panel remain next.


### Blue key, left security lock and forked-road build (2026-11-02)

The real-input hallway interaction obtains the Blue Key (collection ID0x104),
then enters security and uses it through the left lock's actual Item submenu.
The pickup is a collected/key item, separate from ordinary carried inventory.
The observer now reads the authored collection display order and saved bits,
plus the power-supply work and selected menu rows, without modifying the game.
The key-item menu screenshot was inspected: Blue Key is selected, with its
proper key-chain preview and the left lock backdrop.

Durable fixtures are generated with `--frames 20000 --aim-cycle 180`:
`--hallway-blue-key` gives194002 samples; `--security-blue-unlock` gives204794.
Both outputs compare byte-for-byte with the successful native exploratory
fixtures. The latter is a separate branch from the hallway and does not
include the optional fountain detour or the independently verified Rupert
monitor scene.

`build-port/security-blue-unlock.log` passes six explicit checks: left-lock
mask1, sanctuary route2, Blue Key consumed, normal player mode, eventState0,
UI closed. Aya is(-46,-871,-123), yaw1056, area6/room1/variant1/view3/warp1,
HP45/BP368/ammunition27. Neither lock use nor the movie is replaced by a flag
write or an emulator/debugger shortcut.

The native build additionally links the actual forked-road room/effects and
all its referenced creature descriptor packages, including later encounter
variants; those later variants have not been exercised yet. Identical-source
Grinning Stranger variants101900/301900 and rat variants00700/200700 share
real descriptors through aliases (`nm` confirms equal defined addresses),
without compiling duplicate copies of the same package. The Pawn Golem's
eight shared-name sound/animation exports and the forked-road Aya standing
clip are namespaced to preserve each resident overlay's authored definitions.

Slouch/Sucklerceph code references two original Shelter encounter-spot tables.
Their28 unchanged rows now live in shared includes, used by the original
console room units and a single resident host data unit. An exact comparison
against the previous source definitions passes. This supplies the actual
data rather than empty stand-ins; it does not port those Shelter rooms.
The final native build succeeds and all27 existing tests pass again
(`/tmp/pe2-blue-unlock-tests.log`).


The rebuilt executable with all forked-road packages passes the full
206717-sample return replay (`build-port/blue-unlock-hallway-return.log`):
area7/variant1/view4/warp2, root(2271,-871,950), yaw2048, HP45/BP368,
left-lock mask1 and sanctuary-route2 retained, no Blue Key, normal control,
event/UI state0. This also replays and verifies the actual lock sequence
with the newly linked packages, not only the earlier binary.


The unlocked route reaches Fountain8 again with route2/left-lock1 retained
(`build-port/blue-unlock-fountain.log`). The original patio-door unbarring
sequence is then exercised: it changes cafeteria-route progress from3 to5
and enters Patio3/room3/variant3/warp2. Returning through the same door enters
Fountain8/room1/variant1/view2/warp1 with nine live action triggers and normal
control (`build-port/fountain-patio-reentry.log`,213185 samples). This is the
actual shortcut-unlock/revisit path; the optional hidden-tree climb was not
performed on this branch, so no climb-trigger revisit claim is made here.


### Forked-road native arrival verified

The successful route takes the upper/east Fountain path directly from the
hallway arrival, rather than attempting to cross the walled southern door
alcoves. Retail collision geometry was inspected to determine that path;
no wall or trigger was changed. The durable route includes the key pickup,
actual left-lock use, return to hallway, Fountain entry and forked-road door:

```
python3 tools/port/make_gallery_input.py build-port/input/forked-road-entry-smoke.pad \
  --frames 20000 --aim-cycle 180 --enter-forked-road
```

Its210963 samples compare byte-for-byte with the successful native input in
`build-port/input/forked-road-east-path.pad`. Six explicit checks pass in
`build-port/forked-road-east-path.log`: area9, sanctuary-route2, left-lock1,
normal player mode, eventState0, UI closed. The complete read-only checkpoint
also shows roomState2/variant2/view4/warp3, root(-5107,129,-3780), yaw0,
HP45/BP368/ammunition27, no pending scripted motion, fountainDoorOpened1,
return/ambush flags0, and one actual `_actor01900Task` with HP160/state2.
Thus the shared301900 Grinning Stranger descriptor is instantiated at runtime,
not merely linked. The native software VRAM dump was rendered and inspected
(`build-port/forked-road-entry.png`): Aya, room backdrop and HUD are present.

This direct durable branch retains cafeteria-route3 and skips the separate
patio-shortcut detour documented above. No fight, observatory ride, late
forked-road encounters, or DuckStation parity is claimed. Next: follow the
forked-road path, execute the original ride and port the observatory overlay.


### Observatory package linkage (2026-11-02)

The default native build now links all three original Observatory units
(room/effects/rides), Blood Suckler04000 and Horned Stranger401300. The latter's
shared-name actor message handlers and scratch coordinate are namespaced;
04000's place handler is likewise package-local on the host. No actor callback
is substituted with an empty implementation. The101100 and301100 manifests
use the same01100 source and parameters, so a host-only alias on the existing
301100 unit supplies the real101100 task bank as well; `nm` confirms all three
bank exports have the same defined address. Other Observatory actor packages
were already linked by the Fountain/forked-road work.

The executable builds and all27 existing native tests pass
(`/tmp/pe2-observatory-tests.log`). Arrival/ride verification is separate from
linkage. The observer now reads Observatory arrival flags, movie tasks,
stream sector/readiness/frame, actor-control and pad-script state, and live
Observatory enemies. Initial path exploration missed the escalator's trigger;
one prolonged wait led to the actual game-over screen, without a false
checkpoint success. A short waypoint replay instead confirms normal control
at(-1944,128,594), yaw968, HP45, route2, no movie task, stream sector117576
(`build-port/forked-road-east-waypoint.log`). No geometry was changed.


### Observatory outbound movie and arrival verified

The successful215576-sample native route is reproducible byte-for-byte:

```
python3 tools/port/make_gallery_input.py build-port/input/observatory-entry-smoke.pad \
  --frames 20000 --aim-cycle 180 --enter-observatory
```

It uses the verified forked-road waypoint, turns toward the escalator from
the south and finishes both original movie controllers without a Start skip.
`build-port/observatory-ride-door.log` passes its two CLI expectations, and an
additional23-value audit of the captured final/mid-movie states passes.
The end state is area10/room1/variant1/view2/warp4, root(-2582,-2861,-1742),
yaw1008, HP45/BP358/ammunition27, sanctuary-route3 and left-lock1. The original
escape cost is10 BP. ArrivalSceneStarted1, player mode/state/movementMode0,
no pending scripted motion, event/UI state0, actorControl0, padScriptFlags0
and no movie tasks prove that the arrival returned control. Two actual
Grinning Stranger tasks remain at HP160/state2. No Observatory fight has
been claimed or verified at this checkpoint.

A shorter prefix stops during the actual outbound ride:
`build-port/observatory-door-waypoint.log`,211676 samples, area9/view7,
player scripted hold, route3, stream sector117576, movieReady1/movieFrame6,
actorControl2, padScriptFlags129, outbound movie task in state4. Its VRAM was
rendered and visually inspected (`build-port/observatory-outbound-movie.png`):
Aya is on the escalator with the streamed backdrop and hidden HUD. The final
Observatory VRAM was also inspected (`build-port/observatory-entry.png`).
These are native execution/rendering checks, not a DuckStation parity claim.

The earlier forked-road durable generator remains byte-identical after adding
the new flag. Existing27 native tests and the full build pass. Later Observatory
variants, the reverse ride, and the route to the promenade are still unverified;
next work is the active Observatory encounter and the promenade passage.


### Promenade and Tonfa linkage / Observatory combat exploration (2026-11-02)

The native build now links the actual Promenade room and402200 Golem package.
Its idle/stagger clips are namespaced to keep their authored definitions
separate from the resident Rook/Pawn Golem packages. The original Tonfa Baton
weapon unit is also linked; its Aya idle clip has a separate host export.
The final build and all27 existing tests pass (`/tmp/pe2-tonfa-tests.log`).

A2500-sample primary-fire replay after Observatory arrival consumes all27
remaining9mm rounds. Actual enemy HP changes160/160 ->57/70 while Aya stays
at45HP (`build-port/observatory-combat-probe.log`). The HP result does not
prove a completed encounter. Total ammunition includes loaded rounds, as in
the original inventory model; it is not27 loose rounds plus the HUD's20.

The battle Start menu was inspected: it is the attachment-use panel, not the
full inventory/equipment interface. Source in attachment_stats.c confirms
Start requests that panel while HUD inBattle is set. Tonfa was not attached
and could not be equipped there. No menu restriction was bypassed. A separate
real-input branch starts from the safe security-room unlock checkpoint,
opens the full inventory and selects the Weapon menu. Its proper Tonfa/M93R
choice panel and Tonfa preview were visually inspected
(`build-port/security-weapon-choice.png`). This branch retains all27 rounds;
no prior exploratory ammunition depletion is injected into it.

The checkpoint observer additionally records HP/maxHP/MP, selected weapon,
ordinary inventory rows including attachment slots, and menu selections.
These are read-only debug reads; no item, status, cursor or actor is altered.


### Tonfa equipment, Recovery 2 and Observatory victory

The safe-room equipment branch is verified: `build-port/security-tonfa-equipped.log`
shows weapon19 (Tonfa), no weapon consumable slot, unchanged27 rounds, normal
control and closed UI in security. It reproduces207222 samples with
`--equip-tonfa --frames 20000 --aim-cycle 180`. Returning through the original
route with Tonfa also reaches Observatory, at32HP/BP348, with both enemies160HP
and all ammunition retained (`build-port/observatory-tonfa-entry.log`).

The battle attachment menu is then used properly: Start, Right twice to slot3,
Confirm. Recovery2 is consumed (ordinary item2 disappears), its90HP effect is
clamped to110 maximum HP, and the UI closes normally. This is captured in
`build-port/observatory-tonfa-healed.log`; no status/inventory write is made
by the debugger. The consumed Recovery is not the optional Fountain Protein
Capsule, which is not collected on this branch.

4000 samples of periodic aim/primary Tonfa attacks, followed by240 neutral,
defeat both Grinning Strangers: HP0/-9, Aya78HP, BP444 (+96), 27 rounds retained,
root(-5022,-2862,-9039), yaw3037, area10/view4, normal mode/state0, event/UI0.
`build-port/observatory-tonfa-combat.log` and its rendered/inspected screenshot
prove actual Tonfa model/attack/trail execution and victory, rather than just
successful equipment selection. HUD and shadow palette rows each remain
byte-identical (16 RGB555 entries) to their pre-combat values. This is not a
full rendering/AI comparison with the console.

The223344-sample victory route is reproducible byte-for-byte with
`--observatory-combat --frames 20000 --aim-cycle 180`. The prior M93R-only
`--enter-observatory` route remains byte-identical.


### Promenade arrival verified after Observatory victory

The durable225651-sample route is generated as follows:

```
python3 tools/port/make_gallery_input.py build-port/input/promenade-entry-smoke.pad \
  --frames 20000 --aim-cycle 180 --enter-promenade
```

It matches the successful exploratory input byte-for-byte and was rerun on
the final native build. `build-port/promenade-entry-smoke.log` passes20 explicit
expectations: area11/room1/variant1/warp4, normal player mode/state/movement,
no pending scripted motion, event/UI0, weapon19, HP78, ammunition27, BP444,
sanctuary-route4, left-lock1, arrivalMovieStarted1, actorControl0, padScriptFlags0
and no movie tasks. Actual end view2/root(726,170,9050)/yaw3072, EXP426, movie
frame81/ready0. The software VRAM was rendered and visually inspected
(`build-port/promenade-entry.png`). The original arrival has returned control.

The Promenade's two actual01100 Brute Mossback tasks are live at280HP each,
task state2. Combat currently reports battleRefs2/battlePhase0/endDelay0;
the room's battleFollowupState is0. This is an arrival checkpoint, not a
Promenade battle-clear claim. The observer now exposes these room/arrival,
combat and movie states. Next work: the Brute Mossbacks and the path toward
Sanctuary/Rupert. The Sanctuary overlay and its actors are not linked yet.
The27 native tests still pass; no C/runtime changes followed that test run.
All input/output fixtures, disc-derived VRAM and screenshots remain ignored
local artifacts. No DuckStation comparison has been performed.

### Sanctuary arrival and Rupert

The default native build now links Sanctuary, its scripted No.9 actor and
Rupert210700. The local item-box model needs the same host retention as the
Security Room model: its assembler alias alone does not keep Clang from
discarding the static target. Sanctuary's scratch-position symbol is namespaced.

`--promenade-combat --frames 20000 --aim-cycle 180` generates the verified
231114-sample Tonfa battle route: both Brute Mossbacks retire, battleRefs0,
HP28, BP648, EXP730 and ammunition27. `--enter-sanctuary` extends this to
243284 samples and reproduces `sanctuary-arrival-finish.pad` byte-for-byte.
The arrival dialogue finishes in area12/variant1/view3/warp3 with normal
player control, event/UI0, objective6 (Find No.9), route5 and bridgeProgress2.
Rupert and the scripted No.9 actor remain live. This is arrival-scene coverage,
not the later No.9 boss fight. The mid-dialogue software frame was inspected.

Rupert's three eye images were incorrectly declared as native `u_long[192]`:
LP64 inserted four zero bytes after every packed word. They are now aligned
`u32[192]`, preserving the SDK upload pointer type at the boundary. The real
blink routine is tested against all768 bytes of each retail image, including
closed/half/open timing. The test failed against the previous declarations.
Sanctuary's shipped scripts do not send the eye-setup message; this verifies
the actor API and does not claim that the arrival scene exercises blinking.

Repeat Rupert interaction exposed another console-address assumption.
Sanctuary's CAP command-table entry0 is genuinely zero, as are the trigger's
event flags. Retail `capRunCommand` reads opcode byte0 through that address
(`lbu` at0x800E3534). The PSX BIOS garbage word at address0 is typically3
after CD delays, selecting CAP_COMMAND_ROOM; see
[PSX-SPX BIOS garbage area](https://psx-spx.consoledev.net/kernelbios/#garbage-area-at-address-00000000h).
The native path explicitly dispatches zero CAP references to the room, without
changing trigger data or the decoded table. `cap_room_command_test` uses the
actual Sanctuary CAP file: the old path faults, the fixed path delivers room
command0, while ordinary dialogue and explicit room commands retain their
behavior. All29 native tests pass. This interpretation still needs a runtime
RAM comparison with the original emulator; no DuckStation parity is claimed.

The previously crashing253024-sample `sanctuary-red-key-north.pad` now reaches
clean EOF (`sanctuary-red-key-north-fixed.log`). A post-run audit passes nine
snapshot expectations: area12, normal mode/state, no pending motion or disabled
movement, event/UI0, objective6 and HP28. The initial CLI check used the wrong
observer key `uiState` instead of `uiOpen` and therefore exited1 despite the
successful replay; the audit reads the captured JSON and checks `uiOpen`.
The VRAM frame was rendered and visually inspected (`sanctuary-rupert-fixed.png`).
This route and a subsequent253019-sample aisle approach do not collect the Red
Key. Both finish with normal control, redKey false and bombSceneState0; the
aisle approach ends at(-3679,131,-8834), yaw2896. Navigation to the key and the
bomb/Roof Garden sequence remain work to do. No position, HP or story flags
were written by the debugger.

### Roof Garden arrival verified

Roof Garden and its SWAT view figure now use their actual source in the default
native build. Its scratch-position, Aya stand clip and paired-visibility handler
are namespaced like the other resident overlays. The manifest's105500/205500
packages use the same05500 unit without gameplay defines; the linked105500 unit
now also exports205500. `nm` confirms all three descriptor symbols have the same
defined data address. The02600/202600 descriptors were already supplied by their
shared production unit. There are no replacement enemy descriptors here.

The failed key approaches stop at the real Rupert blocker: its east wall is
x=-3980 after the room's placement offset, and Aya's root collision radius is
300, explaining the observed stop atx=-3679. The narrow gap to the pews is not
wide enough for that body. The successful route follows the outer aisle around
the south ends of the pews and triggers the original Sanctuary departure scene.

```
python3 tools/port/make_gallery_input.py build-port/input/roof-garden-entry-smoke.pad \
  --frames 20000 --aim-cycle 180 --enter-roof-garden
```

This249798-sample route is byte-identical to `roof-garden-entry-probe.pad`, which
was run on the final native build. The four CLI checks and18 captured-state
expectations pass (`build-port/roof-garden-entry-probe.log`): area13/room1/
variant1/warp2/view3, normal mode/state, no pending motion or disabled movement,
event/UI0, arrivalSceneStarted1, RupertLeft1, Sanctuary bombSceneState1,
enemyDropState0, actorControl0, HP28, Tonfa19 and ammunition27. Actual root is
(-7508,130,-8572), yaw407. Scene event is5; objective remains6 (Find No.9).
The software VRAM was rendered and inspected (`roof-garden-entry.png`).

Four actual Maggot/Caterpillar tasks are present at80HP each in task state1,
battleRefs4; their scripted drop has not started. This verifies the arrival,
not this encounter's combat or the later bomb examination. The29 native tests
pass after the new overlay linkage (`/tmp/pe2-roof-tests.log`). The checkpoint
observer now reports Roof Garden story/arrival flags and these enemy tasks.
No emulator comparison or Red Key pickup has been verified yet.

The252015-sample extension `sanctuary-rupert-left-probe.pad` returns through
Roof Garden's Sanctuary door. The repeat run passes seven CLI expectations
(`sanctuary-rupert-left-repeat.log`): area12/variant3, RupertLeft1,
bombSceneState1, normal mode, event/UI0. Root(-7465,129,-4299), yaw2048,
HP28/BP648/EXP730/ammunition27; Sanctuary's old actor tasks are gone. This
exercises the original room reentry and placement-variant change.

One earlier run of that exact extension ended in Observatory instead
(`sanctuary-rupert-left-probe.log`, area10, HP34, BP444, EXP426 and earlier
story flags), although its249798-sample prefix is byte-identical to the
successful Roof Garden route. No runtime code changed before the successful
repeat. The first point of divergence has not been isolated; deterministic
whole-route playback is therefore not proven. The observer now also captures
gameTick, loopTicks, frameCount, vsyncCount and the unsigned shared RNG state
for investigating this discrepancy. SDK scanline/root-counter reads still use
wall time in this accelerated runner; whether those caused this particular
outlier remains unverified.

The west-aisle approach after this reentry reaches the actual Red Key pickup
prompt (`sanctuary-red-key-return.pad`,256839 samples). Its screenshot was
inspected: the correct key preview and Yes/No question render. The prompt is
still open at that EOF; this is not an animation hang or a collected-key state.
An explicit Up/confirm sequence followed by backing away completes collection
(`sanctuary-red-key-confirm.pad`,258319 samples). Five CLI checks pass:
area12, redKey true, normal player mode, event/UI0. The collected display order
now includes259; HP28/BP648/EXP730/ammunition27 are retained, and the CAP/item/UI
interaction tasks have all retired. Both16-entry HUD and shadow palettes match
their Roof Garden arrival values exactly.

The complete input is generated byte-for-byte with:

```
python3 tools/port/make_gallery_input.py build-port/input/sanctuary-red-key-smoke.pad \
  --frames 20000 --aim-cycle 180 --sanctuary-red-key
```

This includes the Roof Garden arrival and Sanctuary return; it does not set
position, inventory or story state directly. The read-only observer also
reports remaining interaction tasks and pad input suppression to distinguish
an open prompt from normal control.

The generated `sanctuary-red-key-smoke.pad` was then rerun from boot on the
final build: all22 CLI expectations pass (`sanctuary-red-key-smoke.log`). Its
entire captured state, including timing counters and RNG, matches the successful
exploratory run exactly. The complete1MiB VRAM also matches byte-for-byte
(SHA256 d4d55e4c462cf693a9cb851757177dd4151adc068eaf2308c3bdf53a0f1c0ad0).
The final software frame was rendered and inspected
(`sanctuary-red-key-collected.png`). This gives two matching successful key
runs; it does not resolve the earlier Observatory outlier. Red Key use at the
Security Room's remaining lock, the Roof Garden encounter/bomb examination,
and the later No.9 fight are still unverified.

### Roof Garden ambush and Pyrokinesis

The route now returns to Roof Garden with the Red Key retained. The successful
265773-sample `roof-garden-return-west.pad` uses the outer western Sanctuary
aisle after two approaches hit the real pew boundaries. Five CLI checks pass
(`roof-garden-return-west.log`): area13, normal mode, event/UI0 and redKey true.
Actual room1/variant1/view2/warp1, root(-7458,128,-9712), yaw0, HP28,
ammunition27. The arrival scene is not repeated; four enemies are again in
their hidden entrance behavior8/step0, waiting for the room's release flag0.

Crossing the room's bend, arming the encounter and backing through the drop
trigger executes the original ten-command entrance script. In the267059-sample
`roof-garden-tonfa-short.pad` checkpoint, enemyDropState2 and
maggotCaterpillarEntranceReady1 confirm release, event/UI0 confirm script
completion, and battlePhase1/battleRefs3 show combat in progress. After800
Tonfa input samples one enemy is dying at-6HP and the others have48/39/80HP;
Aya has14HP. This frame was rendered and inspected. No victory is claimed here.

Casting from that state exposed a real missing module: the weak
`pyrokinesisCastTask` aborted. The default build now links the production
`src/pe/pyrokinesis/pyrokinesis.c`; its cast, volley, puff, ring and launch-cone
functions are all defined text symbols. Build and all29 native tests pass
(`/tmp/pe2-pyro-tests.log`). The same native cast now succeeds:

```
python3 tools/port/make_gallery_input.py build-port/input/roof-garden-pyrokinesis-smoke.pad \
  --frames 20000 --aim-cycle 180 --roof-garden-pyrokinesis
```

The267435-sample output is byte-identical to `roof-garden-pyro-cast.pad`, run
on the final build. Two CLI checks plus18 captured-state checks pass
(`roof-garden-pyro-cast.log`): MP30 ->22, normal player mode, no pending motion,
event/UI0, P.E. wheel/cast mode0 and the Red Key retained. One further enemy
has gone from48 to-26HP and another from80 to5HP; the remaining enemy has39HP.
BattleRefs is2 and Aya has6HP. The rendered frame was inspected. The spell's
real damage and8MP charge are covered; a full encounter clear remains unproven.
A second cast spends another8MP and leaves one39HP enemy, but Aya dies at-2HP
(`roof-garden-pyro-second.log`); this is a failed combat route.

The native full inventory and P.E. list were also exercised on the safe side
of the ambush (`roof-garden-pe-list.log`/PNG). Only Pyrokinesis1 is learned.
Healing1's retail cost is750EXP, more than the available730; no purchase,
healing, EXP or HP injection was performed. The observer now reports learned
P.E. levels, wheel state, player status flags, crawler behavior/step/root
position, the entrance-release flag, and the retained Red Key on Roof Garden.

The long6000-sample Tonfa-only failure was separately localized. Its later
crash is in `_stageResolvePlayerContacts` while opening an escape-result task,
but the captured transition is already a Dryfield attract demo: demoScene2,
stage2/area2/variant3, HP7168, entryMode0x102, `_sceneBattleResultTask`, arg1=1.
It is not evidence of a fault in the Roof Garden drop or the Pyrokinesis cast.
The replay helper captures mode-transition diagnostics on a fault, and saves
EOF VRAM before requiring a live player, so a failed checkpoint can still be
inspected. The bad demo state and unported later-stage path remain unresolved;
the engine has not been given a null-player bypass.

The successful continuation resumes Tonfa attacks immediately after the first
Pyrokinesis input, rather than waiting180 samples at that point. This clears
all four enemies (`roof-garden-pyro-tonfa.log`,271495 samples): seven CLI checks
pass, roomEnemies is empty, battleRefs0/battlePhase2/endDelay0, actorControl0,
normal player mode/state, event/UI0. Final root(-3255,130,-4830), yaw600, HP6,
MP26, BP760 and EXP754. The rewards match the actual four enemy parameter rows:
4x28BP, 4x6EXP and4x1MP;30MP minus the8MP cast plus4MP reward is26. Ammo remains27,
and the Red Key is retained. This verifies the full encounter clear.

```
python3 tools/port/make_gallery_input.py build-port/input/roof-garden-combat-smoke.pad \
  --frames 20000 --aim-cycle 180 --roof-garden-combat
```

This output is byte-identical to the successful exploratory combat input. The
standalone `--roof-garden-pyrokinesis` route remains byte-identical too: it keeps
the180-sample observation pause, whereas the combat extension deliberately
omits it. With754EXP after victory, learning Healing1 for750EXP is now possible;
learning and using it have not yet been verified.

### Roof Garden bomb examination completed

After victory the actual front-side bomb interaction now completes. The first
approach (`roof-garden-bomb-probe.pad`) did not reach it and retained objective6.
The next approach set objective7 (Bomb, how to escape) and storyDialogue6,
but stopped during a repeat of the CAP dialogue. The software frame was
inspected with "This could be bad..." visible. Confirming while backing away
finishes that interaction without immediately reopening it.

The final281395-sample `roof-garden-bomb-release.pad` reaches clean EOF with
nine CLI expectations and22 captured-state checks passing
(`roof-garden-bomb-release.log`): area13/variant1/view5/warp1, normal player
mode/state, no pending/disabled motion, event/UI0, actorControl0, battleRefs0,
endDelay0, no enemy tasks, objective7, storyDialogue6, Red Key retained, HP6,
MP26, BP760, EXP754 and ammunition27. Actual root(-4500,130,-2299), yaw2056.
The final frame was rendered and inspected (`roof-garden-bomb-complete.png`);
HUD and shadow palettes each match all16 RGB555 entries from Roof Garden's
arrival exactly, including after the spell and bomb dialogue.

```
python3 tools/port/make_gallery_input.py build-port/input/roof-garden-bomb-smoke.pad \
  --frames 20000 --aim-cycle 180 --roof-garden-bomb
```

The generated input is byte-identical to the successful final replay. The
existing combat and standalone Pyrokinesis routes also retain their verified
bytes. No runtime code changed after the successful Pyrokinesis linkage/test
run; subsequent changes are generator, read-only observer and documentation.
Next requirements include learning/casting Healing, using the Red Key at
Security's remaining lock, the onward route and No.9. The Dryfield attract-demo
failure and earlier rare long-replay divergence remain open.

### Healing learned and cast through the native menus

The real menu sequence after the bomb purchases Healing1: EXP754 ->4,
attachLevels[7]0 ->1, MP31/31 after the one-point maximum-MP bonus and purchase
refill (`roof-garden-healing-learn.log`,283119 samples, three CLI checks).
The P.E. list was rendered and inspected with Healing1, casting cost12 and
4EXP visible. Neither EXP nor the learned level was written by the debugger.

The default build now links `src/pe/healing/healing.c`, replacing the weak
abort placeholders with the real aura, sparkle and rising-spark task functions.
All three are defined text symbols. The build and29 native tests pass
(`/tmp/pe2-healing-tests.log`). Casting through the P.E. wheel outside battle
then gives HP6 ->36 and MP31 ->19, preserving EXP4, BP760, ammunition27 and
the Red Key. This matches `attachmentApplySelfEffect`: outside battle Healing1
uses its minimum30HP; battle healing can blend toward60. The spell is selected
automatically outside battle once learned.

```
python3 tools/port/make_gallery_input.py build-port/input/roof-garden-healing-smoke.pad \
  --frames 20000 --aim-cycle 180 --roof-garden-healing
```

The285443-sample generated input is byte-identical to the successful
`roof-garden-healing-cast.pad`. Seven CLI checks and22 captured-state checks
pass (`roof-garden-healing-cast.log`): normal mode/state, no pending or disabled
motion, event/UI0, actorControl0, battleRefs0, Healing activeIndex7/wheelIndex7
with idle P.E. mode0, and objective7 retained. Root(-4500,130,-2541), yaw2056.
The final software frame was inspected; all16 HUD and shadow RGB555 palette
entries match the pre-Healing bomb checkpoint. The earlier bomb input remains
byte-identical. Casting Healing during battle and HP-limit clamping have not
been exercised by this route.

### Healed return route and Observatory landing diagnostic

Normal recorded input returns from the Healing checkpoint through Sanctuary
variant3 (291063 samples), Promenade room2/variant2 (294022), and Observatory
variant2 (297408). Their corresponding `healed-*-return.log` checkpoints retain
HP36, MP19, EXP4, BP760, reserve27 and the Red Key. Promenade has four rats and
three moths; Observatory has two Mossbacks. No battle victory is claimed on
this return route.

The first southward Observatory attempt stops at root(-2690,-2861,-10650),
yaw4064, beside the north landing's platform. The checkpoint observer now
reads the root matrix's Q12 forward X/Z column: (-201,4091), confirming the
heading independently of the yaw assumption. An attempted east bypass instead
turned left: `observatory-east-lane-check.log` (298579 samples) shows yaw3096,
forward(-4093,151), and the same position. Thus that input turned west into
the platform; it is not evidence of an eastward collision failure. Both this
three-expectation checkpoint and the five-expectation full bypass checkpoint
retain normal control and unchanged HP/MP. The corrected eastward attempt uses
Right23 before forward movement. Its outcome must be inspected separately;
Security Room and Red Key insertion are not yet reached on this healed route.

The corrected east bypass (299087 samples) succeeds in passing the platform:
root(-2465,-2859,-4795), yaw3976, view3, normal control, HP36/MP19 and Red Key
retained (`observatory-east-bypass-corrected.log`, four expectations). The
software frame was inspected with both Mossbacks and intact HP/MP rendering.
However, the subsequent301503-sample exit attempt ends with no player and
HP-8/area0, not a verified Forked Road transition. A shorter approach checkpoint
is required to distinguish movement/door alignment from combat damage.

`--healed-observatory-return --frames 20000 --aim-cycle 180` now generates the
verified297408-sample Observatory arrival byte-for-byte. The existing Healing
fixture also remains byte-identical; Python compilation and diff checks pass.

The299180-sample short approach retains HP36/MP19, normal mode/state,
Red Key and both live280HP Mossbacks. Root(-2609,-2861,-3008), yaw4064,
view2, active locomotion3. This is still outside the Forked Road trigger's
Z interval[-2144,-1184], showing that this checkpoint has not yet reached the door. The prior90-sample approach covered only1787 Z units; assumed
34-units-per-sample movement must not be used for this segment. The next
input extends forward motion65 samples before turning toward the door.

The299448-sample contact probe does capture a live player despite the CLI's
missing post-detach completion marker: HP23/MP19, mode1/state0/phase2,
root(-4955,-2862,-3088), yaw3096. It confirms failure to advance south, followed
by westward movement and damage; do not describe this short probe as death.
The added read-only movementSign/turnSign/velocity fields are captured normally.

The authored collision explains this: face34 is the rail at Z=-2788 from
X=-7150 to-2343, vertical Y[-4235,-2990]. A radius300 body approaching at
X=-2609 stops around Z=-3088. The intended passage is east of X=-2043,
then south onto landing face59 and west toward the facing-quad door at
(-2352,-3016,-1664). A new input-only route tests that geometry; no collision
or runtime state has been patched.

The long rail-bypass attempt301479 also ends without a player (HP-2/area0).
It does not verify passage or the predicted eastward alignment. A shorter
299359-sample input stops immediately after the door approach to inspect its
actual position, without the long confirm wait that permits further attacks.
The checkpoint runner now resumes with LLDB `continue` after its read-only
snapshot instead of detaching: this should retain the normal EOF diagnostic
and exit status rather than racing debugger shutdown. Runtime validation is
pending in the short probe; the parser's completion requirement is retained.

### Incremental headless input after a finite replay

Following PE1's stdin advance workflow, opt-in `PE2_PAD_CONTROL=1` now continues
an exhausted `PE2_PAD_REPLAY` in a headless process. Commands are
`advance COUNT BUTTON_MASK` (physical PS1 digital mask, decimal count and
base-auto mask such as0x2010) or `quit`. A boundary prints
`[pad] control waiting at frame N`. The SDK host-clock pause excludes waiting
time from VBlank and wall-clock root counters; the game loop does not execute
while waiting. This development interface supplies pad samples only. Existing
finite replays keep their default EOF exit, and the checkpoint runner clears
the control environment option to preserve that contract.

`PE2_PAD_RECORD` captures the original replay and every incremental sample in
the existing PE2PAD1 format. A native smoke replayed100 samples exactly, then
advanced3 Up and2 neutral samples and quit with exit0. All105 recorded samples,
including prefix, indices and held masks, were checked. The expanded codec /
command parser test passes normally and with ASan/UBSan plus strict warnings;
it rejects malformed commands, zero/overflow durations and invalid masks
without changing outputs. The default app builds successfully. Full game
checkpoint/clock-pause validation of the interactive mode remains pending.

The read-only checkpoint runner's `continue` change is runtime verified by
`observatory-rail-bypass-contact.log` (299359) and
`observatory-escape-transition.log` (299759): both now retain the EOF diagnostic
and normal exit0. The contact checkpoint reaches the actual door:
root(-1948,-2989,-1712), scriptedmode2/state1, HP36/MP20, BP750, Red Key retained.
The400-neutral extension retains that pose and paused actors, with pendingMode129
and gameFlowReloadSessionTask state1. Earlier long confirm runs die later;
this is not sufficient evidence of a faulty collision or transition handler.
The observer now includes flow flags and active reload/result task states.

### Menu corner corruption fixed in the shared GPU decoder

A live read-only breakpoint in RasterSprite while opening the Forked Road
attachment menu catches the actual top-right frame corner: U16/V80, CLUT0x3C03,
but inherited cur_tpage143 (0x8F), instead of the authored frame atlas0x1E.
The atlas pixels and palette are present. Both rasterizers consume polygon
TPage locally without updating the page subsequently inherited by sprites.
The retail UI frame queues textured FT4 edges before its SPRT8 corners and
relies on the PlayStation polygon TPage write to draw-mode bits0..8.
Reference: https://psx-spx.consoledev.net/graphicsprocessingunitgpu/#tpage-attribute-parameter-for-textured-polygon-commands

PsyZ's shared libgpu DispatchPackets now updates those nine draw-mode bits
from the second vertex's TPage before dispatching a complete textured polygon.
It handles FT3/FT4/GT3/GT4 offsets, retains E1's dither/display bits9..10 and
sends the same mode to either rasterizer. No UI coordinates, assets or palettes
are changed. gpu_tpage_test reproduces the edge->corner dependency through
the real GPU backend: it fails on the old decoder and passes after the fix
for all four polygon formats, both PSYZ_HEADLESS=1 and the Metal-backed
PSYZ_HEADLESS=gpu mode. All30 native tests pass
(/tmp/pe2-tpage-regression.log), including139 retail CAP files.

The controlled native route reaches Forked Road normally after the escape
panel: area9/roomState2/variant3/view3/warp5, HP36/MP20, BP750, EXP4, reserve27,
Red Key retained. Its300007-sample snapshot is saved as
healed-forked-road-controlled.pad. The additional Start8/neutral300 produces
the300315-sample forked-road-menu-smoke.pad. Both before and after frame PNGs
were visually inspected: corrupted corners disappear in the same attachment
menu. Thirteen of fourteen compared snapshot groups match exactly, including
actor/location/status/inventory/input/UI/flow/RNG; timing alone differs by two
frame/loop counts while gameTick and VSync remain equal. No universal replay
determinism or console comparison is claimed. Images:
menu-corners-comparison.png and forked-road-menu-{before,fixed}.png.

The incremental control run also verifies a full input prefix and subsequent
400-neutral,8-confirm,240-neutral segments, normal result-panel completion,
Forked Road arrival, menu opening and clean quit. Clock pause depth1 and the
kernel's paused flag1 were read at the boundaries. The observation session is
closed before rebuilding the executable. The successful menu fixture replays
after the GPU fix with three CLI expectations and normal exit0.

### Healed return to Security Room and an in-battle Healing cast

The incremental input session `control-forked.log` continues from the verified
Forked Road arrival through Fountain and Hallway back to Security Room. At
301034 samples Fountain is area8/roomState1/variant1/view6/warp2, HP36/MP21,
BP740, EXP4 and Red Key retained. Both return encounters use the real escape
result panels, each charging10BP and returning1MP; no victory is claimed.
The Fountain medical-case dialogue also grants one Protein Capsule (item7)
through ordinary input. It remains carried and is not consumed.

Hallway's live encounter (one actor401800 with180HP and four18HP rats) damages
Aya and applies poison. The first Healing attempt does not release or spend
MP. A second attempt opens the wheel, selects the already learned Healing1
and reaches its actual release: sample305407 has HP48 (from1), MP9 (from21),
P.E. mode0, normal-mode PE state6/phase4, poison still active. This is runtime
verification of Healing during battle; do not claim a full60HP restore or
poison cure. Further damage leaves HP42 before the door. The escape clears
the status effects and restores1MP as the normal result procedure dictates.

The306027-sample `healed-security-return.pad` reaches Security Room area6/
roomState1/variant1/view2/warp1, normal mode/state0, event/UI0, no pending mode,
HP42/MP10, statusFlags0, BP730, EXP4, reserve27, Red Key retained and panelKeys1.
The new `--healed-security-return --frames 20000 --aim-cycle 180` reproduces
that entire input byte-for-byte. It inherits the existing Healing and
Observatory route; the appended run-length constants preserve all captured
alignment attempts and the successful combat recovery. Python compilation
and diff checks pass. It is a verified successful route, not an optimized or
universally deterministic input schedule.

At306877 samples the actual right-lock prompt is open (view6, cursor64/32,
hotspotId2, panel task state4, Item selected, Red Key first in the list). Its
menu image was inspected with intact corners. Full Red Key use and movie
completion remain pending. The first long probe lost its LLDB parent during
a turn interruption: the orphan was observed alive and progressing at227278
VSync polls, then exited before a second attach. No final state was captured,
so that run does not prove unlock or failure. A new full replay verifies the
completion independently. Red Key removal is checked through collected item259;
`akropolis.parthenonKey` denotes a different retained key and must remain true.

### Red Key inserted; Bridge source linked

The repeated310201-sample Red Key probe completes with three CLI expectations
(`security-red-unlock-verified.log`): Security Room retained, panelKeys3 and
collected list[258,257,262], with item259 removed. HP42/MP10, EXP4, BP730,
reserve27 and the unused Protein Capsule remain. The right-unlock controller
has returned to its panel scan state2/view6; eventState1 and scripted actor
mode2 mean this is not yet normal gameplay. A Circle20/neutral400 extension
is being verified separately for complete panel cleanup.

The default build now links the authored bridge.c, including its room,
keypad, enemy controller and effects. All14 exported akropolisBridge*Task
symbols are strong text definitions instead of weak abort stubs. Its included
glowDrawTintedDiscNoBias helper has a host-only room-specific name to coexist
with Promenade's separate console-overlay copy. No gameplay logic, keypad
code, collisions, assets or effect timings were changed. The build succeeds;
actual Bridge entry and its keypad/boss sequence still require native replay.

The final310621-sample cleanup (`security-red-unlock-finish.log`) passes nine
CLI expectations after the Bridge link: area6, both locks3, Red Key removed,
normal actor mode/state0, event/UI0, HP42 and MP10. Additional read-only checks
confirm no pending display mode/transition tasks, actorControl0, battleRefs0,
no status effects, enabled normal movement, no pending scripted motion and no
remaining power-supply task. View3, root(-46,-871,-123), yaw1056. The intermediate
panel image was inspected with both inserted keys and intact native textures.
All30 native tests pass after linking Bridge (/tmp/pe2-bridge-tests.log).

`--security-red-unlock --frames 20000 --aim-cycle 180` generates the complete
310621-sample route byte-identically to the successful final fixture. It
inherits --healed-security-return and preserves the older route prefixes.
Actual Bridge entry remains the next native runtime verification; linking
its source is not evidence that its keypad or boss fight already works.

### Post-Red route, Odd Stranger hold escape and Observatory lifecycle fault

The next incremental session is `control-red-return.log`, starting from the
310621-sample normal Security Room checkpoint. It verifies Hallway return,
then the actual Odd Stranger grab: scripted mode2/state6 requires eight
new eligible button presses. Alternating Cross/Square for32 samples releases
the hold through its original message path (HP14 ->13). Aya reaches Fountain
at312265 samples: area8/roomState2/variant2/view3/warp3, HP13/MP11, BP720,
statusFlags0. The new placement contains two280HP Mossbacks.

Running past them reaches Forked Road variant4 at313217 samples with HP13,
MP12, BP710 and four80HP Maggot Caterpillars. Outside active battle, another
native Healing cast gives HP43/MP0 (313649). The caterpillar entrance is then
activated while crossing the room; the encounter is escaped, not defeated.
Observatory entry314518 is area10/roomState2/variant3/view2/warp2, normal Aya
at(-2408,-2861,-1748), HP43/MP1, BP700, EXP4 and panelKeys3. Nine real bats
(_actor03700Task) are loaded at1HP each. The observer now captures those
creatures, batWave and the scripted ambush controller when present.

The ambush trigger at314726 sets batAmbushSeen1 and enters its scripted pose.
The subsequent update crashes before the requested314966 boundary; snapshots
after that fault are static crash-state reads, not evidence of continued play.
The actual recorded input stops at314914 samples. Backtrace points to
observatory_effects.c's release state: taskKill frees _SceneWork, then the
original idle tail reloads task->work and sends ANIMATION_MESSAGE_IS_PLAYING
through a freed/allocator-scribbled playerTask (receiver0xc89991d7b96fff00).
Do not call this a battle failure, hang or missing enemy implementation.

The controller now copies its borrowed player/clip values to a local block
before taskKill. The idle tail still runs after teardown, preserving the
release/query/optional follow-up order without reading freed task/work storage.
observatory_scene_lifecycle_test executes the production release state with
real free(), covering both follow-up indices and both animation-query results.
Old code fails its receiver check; an isolated old-code ASan run diagnoses
heap-use-after-free. The fixed code passes ASan/UBSan and all31 native tests
(/tmp/pe2-observatory-lifetime-tests.log). The app builds successfully.
A315314-sample replay of the exact captured crash prefix plus400 neutral
samples is validating the complete native handoff; its outcome remains pending.

The full315314-sample fixed replay now passes the former crash and exits0
(`observatory-bat-lifetime-fix.log`). Its CLI stops on the deliberately stronger
actor.mode0 expectation: after400 neutral samples, an actual bat has grabbed
Aya, so the live actor is scriptedmode2/state6 with eight escape presses and
HP33. This is the production actor03700 hold (constant8 in its begin-grab
helper), not the retired ambush controller or a replay crash. An additional
captured-state audit confirms ambushSeen1, roomState1, pendingMode0, no remaining
ambush/movie tasks, batWave2, nine active1HP bats and a normal EOF/exit0. The
six original CLI expectations must not be described as all passing.

The regression preserves the original teardown-before-idle-query order and
covers both idle/follow-up entries and both playing-query outcomes. ASan's old
heap-use-after-free trace is /tmp/pe2-observatory-lifetime-old-asan.log; the
fixed ASan/UBSan binary passes. The31-test suite and source diff checks pass.
The next native input at that checkpoint must release the bat hold before
fighting or traversing to Promenade. Later live verification is recorded below.

### Observatory victory, Bridge entry and keypad pointer forwarding

The subsequent controlled native run released the hold and defeated all nine
bats. At316908 samples (`observatory-bats-clear.pad`), normal control and no
pending display transition are restored: HP29, MP10, EXP49, BP862, battleRefs0.
The live route then crossed Promenade and entered Bridge at318332 samples
(`bridge-first-entry.pad`): area14, view6, HP29/MP11, BP852. The room and its
effects were visually inspected. `--bridge-entry` reproduces the captured
input bytes; this does not establish deterministic playback of the whole route.

The live keypad interaction accepted the three entered digits as0x561, then
crashed while broadcasting its actor command. The scene forwarder still took
an s32 payload, truncating a native stack pointer between two otherwise
pointer-safe dispatcher hops. Its declaration and definition now use
TaskMessageWord. `scene_broadcast_test` exercises both production dispatch
hops with a native stack command, signed integer payload, actor-bank filtering
and an empty scene. It fails with the old forwarder and passes with the fix;
all32 native tests pass (`/tmp/pe2-scene-broadcast-tests.log`).

In-game completion after this fix remains unverified. The finite321353-sample
`bridge-keypad-pointer-fix.pad` run exited normally, but diverged after combat
and finished in cleared Observatory rather than reaching the keypad. This is
not evidence that the bridge-raising sequence works. A controlled recovery
run is stopped at that replay's EOF to continue from its observed position.
Target stdout/stderr now go to separate files: the earlier interactive run
encountered debugger/target PTY backpressure during a large PutSTDIN batch.
Only executed input was retained; discarded queued bytes were not replayed.

The controlled recovery subsequently reached Bridge again at322762 samples.
After examining the panel and entering561, the fixed broadcast passed the
previous fault and started the keypad movie (view9, sequence state11 at324805).
At326005 the sequence has completed: bridgeProgress3, area14/roomState2,
view6, normal actor mode/state0, event/UI0, pendingMode0 and no keypad/movie
tasks. HP29/MP11, EXP49 and BP852 are preserved. This verifies the pointer fix
and the bridge-raising handoff in the native game. Evidence is in
`control-bridge-recovery.log`, `bridge-code-fixed.vram` and the captured
`bridge-raised-live.pad`; deterministic finite replay of this new capture has
not yet been verified.

### Fire Escape native package integration

The default overlay list now includes `fire_escape.c` and its real placed
enemy package, `enemies/stranger/lesser/lesser_stranger.c`. The initial room
link exposed the missing gLesserStrangerTaskDesc; linking the authored actor
resolved it. Its gStrangerLesserIdleClip name collides with actor210600's
separate console-overlay bank, so only this package's host build renames its
export to gFireEscapeStrangerIdleClip. Both banks and their data remain
separate. The native app builds successfully (`/tmp/pe2-fire-escape-build.log`),
and all five akropolisFireEscape task exports and gLesserStrangerTaskDesc are
strong symbols. Runtime room entry and enemy behavior remain to be checked.
The checkpoint observer now includes Fire Escape's enemy/movie tasks and the
Bridge door-scene flag to distinguish its first-use scene from departure.

The newly linked build replayed `bridge-raised-live.pad` to326005 with the
same Bridge position and raised state. Controlled input crossed both stair
flights and reached the Fire Escape door. By330112 the bridge battle result
has awarded EXP67/MP14/BP960 (HP29); six residual enemy tasks remain, while
battleRefs is zero. Task count alone does not establish active combatants.
At330968 the door
action is stuck in DIRECTION_WARP_PHASE_AWAIT_SOUND: sound0x510E0005 has
ended its command stream but retains voice22. After12000 neutral samples
it still waits, with the emulated voice inactive and its envelope zero.

Psyz's libspu status constants were reversed: its real status reader returns
3 for key-on/envelope-zero and2 for key-off/envelope-nonzero. The header now
agrees, allowing the game's existing voice-release logic to recognize natural
sample completion. `spu_key_status_test` calls the production reader for all
four combinations, including voice22. It fails against the old header and
passes fixed. The33-test set passes, with the Rupert and Sanctuary CAP tests
supplied their required retail input files.

The SPU fix exposed an earlier crash around4604 input samples: a queued sound
start surveyed another SOUND_SCRIPT_STARTING slot with NULL entryControls.
`_sndScriptStartSlot` now publishes its already-resolved controls together
with the cursor, before another event can survey it. oneC still reloads them
on execution. `sound_slot_start_test` fails old/passes fixed for first start,
same-batch survey and replacement of an old bank reference. The app builds;
full runtime verification of these audio fixes is in progress. Crash evidence
is retained in `fire-escape-spu-only-crash.log`.

With both fixes, the old full input passes4604 but no longer follows the old
route. Around163944 it is back in MIST Shooting Gallery (area20, HP100) and
faults in `_stageResolvePlayerContacts` while starting a battle-result mode
without a player task. Evidence is in `fire-escape-audio-fixed-route-crash.log`.
Do not claim Fire Escape entry or successful full playback after the audio
fixes. A60000-sample prefix is being checked to locate a usable normal-input
continuation; the missing-player transition requires separate investigation.

That prefix reaches a live controllable player at60000: West Elevator Hall area17,
roomState1/view3, position(952,128,987), yaw992, HP110/MP30, EXP0, objective1.
The active grid and room controller both confirm West Elevator Hall. An initial
interpretation as MIST Parking was wrong (that room is area19). This checkpoint
does not establish early route divergence; the full run diverges later. The
controlled session is retained for a normal-input continuation.

### Controller FIFO and corrected Square continuation

Normal input from60000 reached Square at61837, area1/roomState1/view15,
warp7, HP110/MP30. The captured prefix is `spu-fixed-square-entry.pad`.
This confirms a usable route after both sound fixes through West Elevator Hall.
Further arrival/dialogue verification is pending.

A large SBProcess.PutSTDIN batch can block LLDB's command thread while an
intermediate conditional breakpoint needs that same debugger thread; redirecting
target output alone did not prevent this. The recovery drained only unexecuted
input, after which this session closed stdin and exited0 at61837. It was not
a gameplay fault or a completed Square arrival scene.

Opt-in headless control now accepts `PE2_PAD_CONTROL_FIFO=/absolute/path` as
an alternative to stdin. The POSIX helper validates an existing FIFO and keeps
both ends open, so separate short-lived writers cannot close control between
batches. It is defined before SDK open() redirection to avoid PS1 path/8.3
translation. The normal stdin and finite-replay paths retain their behavior.
A native integration run used separate writers for3 Up and2 neutral samples
after a100-sample replay, verified all105 recorded samples, then quit with
exit0 (`pad-control-fifo-test.log`). Unsupported hosts reject this opt-in.

The control reader also retries EINTR after clearing the FILE error and now
reports other read failures as exit1, distinguishing them from clean EOF.
Debugger interruption of the earlier blocked read had been reported as EOF.
Control breakpoints must be derived from the current `control waiting` source
line (now299), rather than keeping the old line260 after adding host code.

The corrected route replayed to64237 and finished the Square arrival with
normal mode/state0. FIFO input then triggered the real Grinning Stranger
departure at72032 (telephoneSceneSeen1, pending call1, Stranger task gone).
At76292 the native telephone caption displays Baldwin's opening line; the
call consumes the pending flag and increments telephoneDialogueCounter to1.
At78812 control is normal again, actor(-6450,-2070,201), yaw936, HP110/MP30,
event/UI0 and pendingMode0. `spu-fixed-square-phone.pad` captures this prefix,
and `control-spu-fixed-square-next.log` retains the checkpoints. Finite replay
of the final telephone prefix has not yet been verified. The observer now
also reports the active grid and room-controller symbol; both identify Square.

### Patio route after the sound fixes

The controlled continuation passed the two Square stair flights normally and
entered Patio at82506 (area3/roomState1/view2, warp4, HP110/MP30). At85070
the SWAT opening has finished, patioCutsceneProgress3, normal control and one
160HP Stranger. The observer now includes actor01900 enemies in Patio,
Cafeteria and Hallway as well as the previously observed return-route rooms.

The M93R fired20 actual rounds (ammo100 to80), reducing this Stranger to4HP
without damaging Aya. Further shots defeat it; at86130 battleRefs0 and the
result transition award EXP42 and BP188. Approaching the authored follow-up
trigger and finishing its dialogue sets patioCutsceneProgress4 and selects
roomState2. At92036 Aya is in normal mode/state0, HP110/MP30, pendingMode0,
with no active event/UI. Input is captured in `spu-fixed-patio-clear.pad` and
the live evidence in `control-spu-fixed-square-next.log`. A separate finite
replay passes all nine expectations for area/state, completed follow-up,
HP/EXP/BP, normal control and no pending transition, then exits0
(`spu-fixed-patio-clear.log`). This verifies the corrected input from startup
through Patio after both sound fixes; no full-game or emulator parity is claimed.

### Parthenon Key route after the sound fixes

The controlled route returned from Patio to Square at94112, descended its
lower stair flight at94532, crossed below the central obstacle and entered
East Elevator Hall at100005. At102565 the real SWAT opening has awarded
Parthenon Key (collected257), cafeteriaRouteProgress1 and cafeteriaDoorState2.
The last caption still had to finish: a single further confirm at107373
advanced CAP to its terminator and cleared the EVS cue wait. At107613 actor
mode/state0, event/UI0 and pendingMode0 are restored, HP110/MP30 and EXP42.
The remaining scriptedMotionPending latch is recorded, not treated as proof
of a finished motion; normal movement on the next departure still needs checking.

`make_gallery_input.py --audio-fixed-east-hall --frames 20000 --aim-cycle 180`
now generates the108633-sample capture exactly. It reuses the first60000
unchanged startup samples and appends the physical controller segments in
`tools/port/routes/audio_fixed_east_hall.json`; repeated input patterns are
stored as loops. The generated file compares byte-for-byte with the live
recording `spu-fixed-east-hall-key-finish.pad`. This flag is exclusive with older
progression flags, whose historical routes should not be assumed to follow
the same timing after audio completion fixes. Python compilation and
git diff --check pass. A separate finite replay of this generated route is
checking the key award and scene cleanup.

The first finite107613-sample probe (`audio-fixed-east-hall-smoke.log`) did
award the key and preserve HP/EXP, but still ended in actor mode2/eventState1
on the final caption. It therefore failed the cleanup expectation. The input
was extended with a confirm-and-back-away tail, to let the caption finish
without reopening the nearby SWAT interaction. In the live run, backward
movement is verified at107793, and at108633 the player is(-861,129,1871),
normal mode/state0, event/UI0 and pendingMode0, with the key retained. The
scriptedMotionPending latch remains1 even while normal movement works; it
alone must not be treated as loss of control. The extended generated trace
is byte-identical to the executed controller recording. Its separate finite
replay passes all11 expectations (area, key/progression, HP/EXP, normal
mode/state, no pending transition/event/UI) and exits0 at108633
(`audio-fixed-east-hall-finish.log`).

### Cafeteria entry after the sound fixes

From108633 the live route leaves East Elevator Hall, returns through Square's
two stair flights and enters Patio again at111411 with the key retained.
The north-west ramp reaches the cafeteria door. At112652 the native caption
reads "Opened the door with the [Cafeteria Key]." At113260 the room has
loaded normally: Cafeteria area4/roomState1/view2, warp2, doorState3,
HP110/MP30, EXP42, normal control and pendingMode0.

`--audio-fixed-cafeteria --frames 20000 --aim-cycle 180` generates this
113260-sample input exactly. Its JSON segments extend the verified
108633-sample `audio_fixed_east_hall` route rather than duplicating it.
The generator's captured-route helper now supports this explicit base route;
regenerating the East Hall route still compares byte-for-byte with its capture.
A finite probe is checking entry, door/key flags, HP/EXP and restored control.

The live battle ribbon then starts the actual350HP boss and its controller.
At115770 the controller is waiting for setup (state14); a3600-neutral-sample
wait lets the intro finish but also lets the boss attack, leaving HP21 at119370.
M93R attacks reduce the boss to137HP, then97HP while Aya falls to4HP; the
following attempted P.E. input loses the run (HP-5 at120162). This failed
input is retained as `audio-fixed-cafeteria-first-fight-failed.pad`, with
checkpoints in `control-spu-fixed-square-next.log`. It is not a port crash.
A new controlled run replays only to115770 and will supply combat input
immediately after the intro, instead of preserving that idle wait.

That retry itself diverged: at115770 it remained in East Elevator Hall rather
than the expected battle setup. A separate finite cafeteria-entry probe also
failed its area expectation (area20 instead of4). The earlier single successful
East Hall/Patio replays do not prove repeatability of long wall-clock captures.
Do not use their exit0 or one passing checkpoint as a general determinism claim.

Psyz already provides `PSYZ_AUDIO_CLOCK=video`: both kernel time and offline
SPU consumption follow emulated video/audio batches, rather than host elapsed
time and the device callback. Two independent full-input probes are running
with that clock to assess their final-state agreement. The checkpoint CLI now
exposes `--clock host|video` and writes PE2_REPLAY_CLOCK to its log; omitting
the option still inherits the environment. No normal interactive clock default
has been changed. Further Cafeteria progression needs a repeatable input basis.

Both video-clock probes exit0 at113260 and agree on every checkpoint group
except timing. They end in the gallery airlock, area20/view5/warp5, position
(-8612,1,-3115), yaw3072, HP110/MP30, weapon0 and EXP0. RNG and frame/VSync
counts agree; gameTick/loopTicks differ by12. This is useful observed state
agreement, not proof of full determinism or compatibility with the wall-clock
route. The old input does not reach Cafeteria under the video clock.
A new controlled video-clock run starts from the shorter21654-sample first
airlock prefix to reconstruct the necessary input with this clock selected.

### Batched SPU voice attributes were still a no-op

The video-clock airlock probe exposed a more concrete missing native API.
`src/port/psyq_host.c` still implemented SpuLSetVoiceAttr as an empty stub.
The game's normal `spuFlushVoiceUpdates` calls it for its entire attribute
batch, so voice pitch, sample/loop addresses, ADSR and volume changes were
silently dropped. Live registers showed maximum pitch, address512 and zero
ADSR even while the door sound retained a voice. This invalidates assumptions
that the earlier status-constant fix alone completed native sound ownership.

`src/port/spu_voice_attributes.c` now applies each valid list entry through
the real SpuSetVoiceAttr, selecting its voiceNum and copying attributes so the
caller's batch is unchanged. Its production-register test covers two distinct
voices, a later pitch-only update, byte-to-SPU sample/loop addresses, ADSR,
stereo volumes, untouched neighboring voices and ignored out-of-range entries.
The old no-op fails; the implementation passes. The app builds and all35
native tests pass (`/tmp/pe2-spu-attrs-all-tests.log`), with required retail
files supplied to the Rupert and CAP tests.

The restarted video-clock native probe now writes valid voice attributes.
At21894, read-only inspection finds all eight sound-script slots idle and
their voice heads cleared, while the voices have the expected silent-parking
pitch/address/ADSR. The door action's next update is being checked. The
checkpoint observer now includes the direction action's active/phase/control,
parameters, warp result and retained sound id for these investigations.

At22014 the first airlock transition completes normally: view5/warp5,
(-8000,129,-1800), actor mode/state0, direction active/phase0. The usual
walk/turn/confirm input then crosses the second airlock. At23358 the player
is in the outer corridor, area20/view4/warp2, (-9944,130,-3040), yaw3072,
HP110/MP30, normal mode/state0 and no active direction action or pending mode.
This is native proof that the queued sound wait completes after real SPU
attributes reach hardware; audible/console audio parity is not claimed.

`make_gallery_input.py --video-clock-airlock --frames 20000 --aim-cycle 180`
generates this23358-sample capture exactly from the existing first-door base
and `routes/video_clock_airlock.json`. Run it with the checkpoint CLI's
`--clock video`. Two independent finite probes both pass all10 expectations
for exact position, area/view/warp, HP and restored action/control state,
then exit0 (`video-clock-airlock-fixed-a.log` and `-b.log`).
All checkpoint groups agree between these two runs, including RNG and all
recorded timing counters. This establishes observed repeatability for this
short route; longer route and cross-backend determinism remain unproven.
Historical wall-clock route captures above have not been revalidated against
this additional sound implementation and should not be treated as current
full-route regression guarantees.


### Video-clock route through parking to Akropolis Plaza (2026-11-02)

After the batched SPU voice-attribute implementation, the native route now
continues from the verified gallery airlocks through the control-room story
(normal Start skip), the parking garage round trip that enables Pierce, and
Ready in the departure menu to Akropolis Plaza. Only physical controller input
was used; no target game-state writes. No shop purchase was needed.

`tools/port/make_gallery_input.py --video-clock-akropolis --frames 20000
--aim-cycle 180 OUTPUT` is represented by `routes/video_clock_akropolis.json`
and recursively uses the verified video-clock airlock prefix. The generated
39036-sample file is byte-identical to the live recording. Two independent
finite `replay_checkpoint.py --clock video` runs each passed seven expectations:
area5, normal actor mode, event0, pendingMode0, HP110, MP30 and root
[23202,129,1764]. Their complete checkpoint dictionaries are identical,
including every timing counter and RNG. Logs:
`build-port/video-clock-akropolis-settled-{a,b}.log`. This verifies this route
on the current native build; console parity and later tower progression remain
unverified.

The first Plaza image was initially misread as corrupt because the old local
VRAM exporter assumes RGB555. This scene is actually RGB24; live display
state reports both display environments as RGB24 and the front rectangle at
y272. Decoding that rectangle produces a correct street/car image.
`tools/port/export_vram.py INPUT OUTPUT --rgb24 --y 272` now supports this
format explicitly, alongside the default RGB555 path. Both outputs were
checked byte-for-byte against their existing equivalent decodes. The apparent
corruption was an inspection error, not a demonstrated renderer bug.


### Verified Plaza traversal and tower entry (2026-11-02)

The corrected video-clock route now crosses Plaza, completes the automatic
sergeant scene, wreck scene and entrance-officer scene with normal Start
skips/confirm input, and reloads into West Elevator Hall (area17). No state
injection was used. The initial reload boundary at47088 has no player actor;
a further1200 neutral samples completes it normally. At48288 the player is
at[-1388,129,922], yaw2048, normal mode/state0, HP110/MP30, objective1,
storyDialogue1, event0 and pendingMode0; the runtime grid and controller both
identify West Elevator Hall. The displayed room and HUD were visually inspected
(`build-port/video-route-tower-settled.png`, RGB555, front rectangle y272).

New `--video-clock-tower` route metadata recursively uses the settled Plaza
prefix. Generated48288-sample input matches the live recording byte-for-byte.
Two finite `--clock video` probes passed seven expectations each; their complete
checkpoint dictionaries match, including RNG and all timing counters. Logs:
`build-port/video-clock-tower-{a,b}.log`. Later rooms and combat on this corrected
audio/clock route remain to be verified. These probes establish native replay
repeatability for the captured path, not original-console parity.


### Video-clock Square telephone and Patio entry (2026-11-02)

Continued from the verified48288-sample West Elevator Hall endpoint through
Square (area1), the automatic Stranger departure, the ringing telephone and
both stair interactions into Patio (area3). The telephone call clears its
pending flag and increments dialogue counter to1. Stationary confirmations
then reopen the save interaction; backwards movement with confirmation leaves
it normally. No save was made. The upper stair landing requires action input
at its authored climb trigger; walking into its boundary alone does not enter
Patio.

`--video-clock-patio --frames 20000 --aim-cycle 180` generates67738 samples
using `routes/video_clock_patio.json` and the verified tower prefix. Output
matches the live recording byte-for-byte. Two independent finite probes with
`--clock video` pass seven expectations. Both end at area3/roomState1,
view2/warp4, root[3907,129,506], yaw2304, normal mode/state0, event0,
pendingMode0, HP110/MP30. All non-timing checkpoint groups match. Unlike the
shorter tower route, complete dictionaries differ: frameCount57947 vs57949,
gameTick57210 vs57212 and RNG1930686106 vs3825858268; loopTicks64577 and
VSync67725 agree. Thus arrival is verified but full determinism is not.
These two probes ran concurrently; a sequential probe is being checked.
Logs: `build-port/video-clock-patio-{a,b}.log`. The settled room/HUD image
`build-port/video-patio-settled.png` was visually inspected. Combat and the
follow-up on the corrected audio/video-clock basis remain unverified.

The third, sequential probe also passes all seven expectations and matches all
non-timing groups. Its timing is frameCount57951, gameTick57208, loopTicks64571,
RNG3825858268, VSync67725 (`video-clock-patio-c.log`). Therefore concurrent
execution alone does not explain the variation; exact scheduling/CD/display
clock provenance remains to be isolated before making determinism claims.


### Video-clock Patio combat and follow-up (2026-11-02)

From the67738-sample Patio entry the real SWAT opening completes, then Aya
approaches and fires20 M93R shots (9mm stock100 to80). The160HP Stranger
reaches-3HP and battleRefs0 with Aya still HP110/MP30. The actual result awards
EXP42 and48BP (total248; this route made no earlier shop purchase). Approaching
the follow-up trigger and using the normal Start skip completes its scene:
at73170, area3/roomState2/view4, root[-6612,130,315], yaw3296,
patioCutsceneProgress4, actor mode/state0, event/UI0 and pendingMode0.
The inherited flowFlags193 and battleResetPending1 are recorded; no claim
that these fields are cleared is made. The settled room/HUD was visually
inspected (`build-port/video-patio-cleared.png`).

New `--video-clock-patio-clear --frames 20000 --aim-cycle 180` recursively
uses the verified Patio entry and matches the complete live recording
byte-for-byte (73170 samples). Two independent finite video-clock replays
pass ten expectations for room/progress, control, rewards, health and no
remaining battle reference (`build-port/video-clock-patio-clear-{a,b}.log`).
Their complete checkpoint dictionaries also match, including timing and RNG.
This pair does not erase the timing variations observed on the shorter Patio
entry probes or establish global determinism/console parity. The current
route now verifies combat and its follow-up after the SPU attribute fix.


### Related worktree: ambiguous globals review (2026-11-02)

User pointed out `/Users/hasik/Projects/parasite-eve-ii-port/pe2-ambiguous-globals`,
branch `fix/ambiguous-globals`, commit5884e6d over current base d616011. It is
clean and contains39-file naming cleanup: storage variants of room event,
departure and cutscene globals get type-specific names; screen-wave oscillator
arrays get module-specific names in actor205200, Submarine Tunnel and Garbage
Incinerator. Comment-stripped token comparison confirms that code changes are
identifier renames only (13 mappings), preserving initializers and logic.
`git apply --check` succeeds against the current dirty main worktree; the sole
overlapping file is incinerator_3.c and touches a separate region from our
encounter-table extraction. The patch has not been applied or committed here.

Useful before adding Dryfield/Shelter/Neo Ark overlays: it removes ambiguous
cross-module type names, but is not full host symbol isolation. Shared external
`gScreenWaveContext` and `gScreenWaveGrid` remain, as do same-type room globals
shared by overlays. Linking all rooms still needs independent storage/namespace
handling. None of the changed39 files has a compile command in the current
Akropolis-only build, so the current app build would not validate them. No
runtime/build validation of this branch is claimed from this review.


### Video-clock Parthenon Key and post-scene movement (2026-11-02)

Continued the corrected Patio combat route through the return stair, Square's
lower stair and East Elevator Hall. The hall's real automatic opening starts
as Aya approaches the SWAT member; normal Start skip and controller confirms
award Parthenon Key (collected257 alongside262), cafeteriaRouteProgress1,
cafeteriaDoorState2, objective2 and storyDialogue3. At79432 actor mode/state0,
event/UI0; a subsequent120-sample backwards movement changes root from
[4440,129,-672] to[3698,130,335], proving movement is available after the scene.
The scriptedMotionPending field remains1 and is explicitly recorded, not
claimed to be cleared. At79672 all flow flags, battleResetPending and
pendingMode are0; HP110/MP30, EXP42, BP248 are retained.

`--video-clock-parthenon-key --frames 20000 --aim-cycle 180` generates the
79672-sample controller capture using `routes/video_clock_parthenon_key.json`
and the verified Patio-clear prefix. Generated input is byte-identical to the
live recording. Two finite `--clock video` replays each pass ten expectations
and have identical complete checkpoint dictionaries, including timing/RNG.
Logs: `build-port/video-clock-parthenon-key-{a,b}.log`. The post-scene room and
HUD were visually inspected (`build-port/video-key-scene.png`). This verifies
the key and control on the corrected native route; Cafeteria entry/boss on
this route are still pending, and no original-console parity is claimed.


### Corrected video-clock Cafeteria entry and live boss victory (2026-11-02)

From the79672-sample key endpoint, the native route returns through Square's
stairs to Patio and uses the real key/door interaction to enter Cafeteria.
At86228: area4/roomState1/view2/warp2, root[-4047,-171,2704], normal actor,
event/UI0, pendingMode0, HP110/MP30, doorState3. New
`--video-clock-cafeteria --frames 20000 --aim-cycle 180` reproduces the live
recording byte-for-byte. Two finite video-clock probes pass eight expectations
and match complete checkpoint dictionaries including RNG/timing
(`build-port/video-clock-cafeteria-entry-{a,b}.log`).

Approaching the authored battle ribbon starts the350HP boss. The opening has
a separately scheduled streamed movie: the first Start skips the EVS intro;
a second Start during movie playback cancels the movie and restores the game.
Confirm input completes the battle-intro caption. Earlier fire inputs during
the movie consume no ammo. Actual M93R fire then reduces the boss to46HP,
with Aya at77HP; further fire defeats it at89414 (boss-4HP,28 actual rounds
consumed, carried9mm80 to52). Normal post-battle and follow-up scene skips
award300EXP/200BP and return to Patio. At93030: area3/roomState3/variant2,
view7/warp3, root[-7014,-173,-4296], normal actor/state0, HP77/MP30,
EXP342/BP448, cafeteriaBossReport1, cafeteriaRouteProgress2, objective4,
storyDialogue4, event/UI0 and all observed flow fields0. The resulting room
and HUD were visually inspected (`build-port/video-cafeteria-cleared.png`).

`--video-clock-cafeteria-clear` generates93030 samples from the captured
physical input with the verified Cafeteria-entry prefix. Byte-for-byte compare
and Python compilation pass; independent full boss-route probes are running.
No game-state writes were used. No new production-code fix was needed for this
path after the existing SPU fixes; this extends runtime coverage to the boss,
its rewards and post-battle room reload.

Both finite full boss-route probes now pass all12 expectations and have
identical complete checkpoint dictionaries, including RNG and timing:
`build-port/video-clock-cafeteria-clear-{a,b}.log`. They confirm the77HP
victory, EXP342/BP448 and normal post-follow-up Patio state. Global replay
determinism and original-console parity remain unproven.


### Post-Cafeteria Patio ambush victory and Recovery2 (2026-11-02)

The corrected video-clock route now defeats both160HP Strangers in the real
post-Cafeteria ambush instead of escaping. At94858 both have negative HP
(-2,-1) and battleRefs0; Aya has22HP and all remaining52 rounds of9mm were
used. A brief aim release after the first death reacquires the second target.
At96058 rewards are complete: EXP426, BP544, normal actor/state0, event0,
pendingMode0 and no battle references. New `--video-clock-patio-ambush
--frames 20000 --aim-cycle 180` generates96058 samples, byte-identical to the
live capture. Two finite probes pass nine expectations and their complete
checkpoint dictionaries match, including RNG/timing
(`build-port/video-clock-patio-ambush-{a,b}.log`).

The live continuation opens Start > Use, selects the unattached Recovery2,
chooses Use and closes the menu normally. HP rises22 to110 and item2 count
falls2 to1. At97226 menu/event0, pendingMode0 and normal control are restored.
This also clarifies item IDs in earlier informal notes: inventory item2 is
Recovery2, not the M93R weapon; carried146 is Tonfa,64 is GPS (as shown in the
actual menu). Weapon model/loadout identifiers are a separate namespace.
The item menu and its corners were visually inspected
(`build-port/video-item-menu.png`, `video-use-menu.png`, `video-recovery-use.png`).
Healing input is retained in `build-port/input/video-ambush-healed-capture.pad`;
its independent replay verification is pending as part of the phone route.
No health/ammo/item values were injected.


### Healing and Baldwin report after winning the ambush (2026-11-02)

The live continuation uses one Recovery2 in Start > Use, restores HP22 to110,
returns through Patio's authored stair interaction to Square, descends the
lower flight and calls Baldwin at the telephone. The report sets
cafeteriaBossReport4, cafeteriaRouteProgress3 and objective5. After finishing
the captions and backing away, at104117: area1/roomState1/variant2/view7,
root[-950,-2070,2133], yaw1056, normal mode/state0, HP110/MP30,
EXP426/BP544, event/UI0, battleResetPending0, flowFlags0 and pendingMode0.
Item2 (Recovery2) count is1, proving consumption alongside the HP increase.
The report caption was visually inspected (`build-port/video-mist-report.png`).

New `--video-clock-mist-report --frames 20000 --aim-cycle 180` generates104117
samples from the verified ambush prefix, byte-identical to the live capture.
This route includes the real inventory menu actions, healing, both stair
transitions and the phone report; independent finite replay checks are running.
No health, rewards, inventory or story flags were injected.

Both full104117-sample report probes pass all12 expectations and have identical
complete checkpoint dictionaries, including timing and RNG
(`build-port/video-clock-mist-report-{a,b}.log`). This independently verifies
the inventory healing/consumption as well as winning the ambush and the report.
The broader determinism limitation from earlier probes still applies.


### Video-clock Hallway and Fountain arrival (2026-11-02)

Continued from the104117-sample Baldwin report through Square stairs, Patio
and post-report Cafeteria (area4/roomState4/variant3), then the northwest door
into Hallway (area7/warp4). Runtime grid/controller identify Hallway. Eight18HP
rats attack during the arrival wait: at110752 Aya is in damage mode, HP64,
statusFlags4. A subsequent Start during normal mode opens the combat equipment
menu; Tonfa is in the backpack but absent from the available battle weapon
choices, so no claim of successful Tonfa equip is made. The menu and room
were visually inspected. The route closes it and runs east to Fountain's door.

After the escape, the display owner transitions and the reload task waits at
state1 while `_sceneBattleResultTask` is at WAIT_PANEL2. Neutral input leaves
this unchanged; normal confirm inputs close the result panel and complete
the reload. This was initially investigated as a potential stall, but no
production-code fault is established: it is a pending result confirmation.
Two10BP deductions are observed on this captured path (BP544 to524), not
claimed to be one escape charge. Rats remain alive; this is an escape route.

At113060: Fountain area8/roomState1/variant1/view3/warp3,
root[-4781,129,-4766], yaw1024, normal actor mode/state0, HP60/MP30,
EXP426/BP524, statusFlags0, event/UI0 and all observed flow fields0. The
settled room/HUD was visually inspected (`build-port/video-fountain-confirmed.png`).
`--video-clock-fountain --frames 20000 --aim-cycle 180` generates113060 samples
using `routes/video_clock_fountain.json` and the verified report prefix;
output matches the live capture byte-for-byte. Two independent finite probes
are checking arrival, health/status, rewards, control and objective. No target
game-state writes were used. Later Fountain traversal remains unverified on
this corrected audio/video-clock basis.

Both full Fountain probes passed all10 expectations. Differing checkpoint
groups: none (including RNG and timing). Logs:
`build-port/video-clock-fountain-{a,b}.log`. This verifies arrival after the
rat escape and result confirmation, not rat defeat or a cleared Hallway.


### Tonfa equipment and Fountain hidden path after audio fixes (2026-11-02)

Outside battle in Fountain, the normal inventory Use > Tonfa > Move flow can
select the weapon slot as destination. It equips Tonfa (weapon19) and returns
the M93R to the backpack; after closing the menu, the weapon resource reload
completes and normal control/pendingMode0 are restored. The route also performs
an attack input in the empty room; no enemy hit is claimed from that input.
The actual item menu visually confirms Tonfa Baton equipped
(`build-port/video-tonfa-equipped.png`).

Examination of the red tree enables hiddenPathFound1 and the additional climb
trigger. Finishing the captions and moving/confirming toward the trigger
performs the actual climb and scripted walk. At119943 Aya is on the upper
path, Fountain view8, root[3959,-70,-7949], yaw1561, surfaceClass5,
normal mode/state0, event/UI0, pendingMode0, HP60/MP30 and weapon19. The
climb remains linked and enabled. New `--video-clock-fountain-path --frames
20000 --aim-cycle 180` generates119943 samples, byte-identical to the live
capture. Two finite video-clock probes pass11 expectations and their complete
checkpoint dictionaries match, including timing/RNG
(`build-port/video-clock-fountain-path-{a,b}.log`). The subsequent live
continuation has opened the upper SWAT ammunition-case examination; pickup
completion is still being checked.


### Upper Fountain Protein Capsule pickup (2026-11-02)

The live continuation turns toward the upper SWAT ammunition case and finishes
its examination/choice, then backs away. At122534 inventory item60 (Protein
Capsule) count1 is present, normal actor mode/state0, event/UI0, pendingMode0,
weapon19, HP60/MP30 and upper surfaceClass5. Root[3621,-70,-7949], yaw65.
Item pickup and caption closure use only controller input; no health-max change
is claimed, since the capsule was taken but not consumed. The SWAT-case caption
and settled room were visually inspected (`build-port/video-protein-prompt.png`,
`video-protein-after.png`).

New `--video-clock-fountain-protein --frames 20000 --aim-cycle 180` generates
122534 samples with the verified Fountain-path prefix. Generated output is
byte-identical to the live recording, Python compilation and diff whitespace
checks pass. Two finite full-route probes are checking pickup, equipment,
health, upper-surface state and restored control.

Both full Protein Capsule probes now pass all10 expectations. Differing
checkpoint groups: timing. Logs:
`build-port/video-clock-fountain-protein-{a,b}.log`. This verifies pickup
and control after the climb on the corrected audio/video-clock route.


### Fountain descent, Hallway rat victory and combat healing (2026-11-02)

From the upper Protein pickup, normal navigation around the SWAT cases returns
to the ledge; forward/action input performs the descent. At123590 lower
surfaceClass4/root[2398,129,-4811] replaces upper class5. Returning through
Fountain's Hallway door restores area7 with all eight18HP rats present.
Tonfa attacks demonstrably damage/kill them. Retargeting after attack recovery
is needed; holding the previous lock yields inefficient attacks. One real
Pyrokinesis cast spends8MP, but no rat HP reduction was observed at the sampled
post-cast checkpoint, so no Pyrokinesis hit is claimed.

At15HP the combat attachment menu is opened. Its slots use horizontal Left/
Right navigation (the generic inventory attachment-list observer is unrelated).
Selecting attachment index2 and confirming consumes the last attached
Recovery2 and heals15 to105 while the battle is active; the menu then closes
normally. Subsequent Tonfa attacks with recovery/target-selection pauses kill
all remaining rats. At131427 the result is EXP458 (+32), BP700 (+176), HP101,
MP30, statusFlags0 and weapon19. Confirmation at the nearby door also returns
to Cafeteria area4/roomState4/view5, root[-986,-172,-5486]. This return is
preserved in the input rather than described as a Hallway endpoint.

`--video-clock-hallway-clear --frames 20000 --aim-cycle 180` generates131427
samples byte-identical to the live capture. Two finite probes each pass ten
expectations and have identical complete checkpoint dictionaries, including
RNG/timing (`build-port/video-clock-hallway-clear-{a,b}.log`). A normal-input
revisit at132083 independently shows Hallway with battleRefs0; the rats did
not respawn. The menu-healing and Tonfa enemy-hit path uses no game-state writes.

### Corrected Security Room entry after clearing Hallway (2026-11-02)

The live route returns through cleared Hallway and its south security door.
At133681: area6/roomState1/variant1/view2/warp1, normal actor/state0,
root[-46,-872,-2877], yaw0, HP101/MP30, EXP458/BP700, weapon19,
event/UI0 and all observed flow fields0. Grid/controller identify Security
Room. Room and HUD visually inspected (`build-port/video-security-settled.png`).
New `--video-clock-security --frames 20000 --aim-cycle 180` generates133681
samples from the verified rat-clear prefix and matches the live recording
byte-for-byte. Independent finite verification is running; monitor interaction
and Rupert playback are not yet verified on this corrected audio/video route.

The finite133681-sample Security entry replay passes all10 expectations and
exits normally (`build-port/video-clock-security-entry.log`), including exact
root, Tonfa, HP101, EXP458/BP700 and restored control. The prior rat-clear
endpoint was independently repeated twice; this entry probe was run once.


### Security monitors and Rupert playback on the corrected route (2026-11-02)

From Security entry133681, normal input approaches the console, aligns the
player and opens its actual monitor panel. Continuing movement during opening
moves the UI cursor to(0,-110); Left70/Down17 brings it to(-140,-74), inside
the brightness hotspot. Confirm input raises live screenLevel4 to252. Right78/
Down80 selects camera10 at(16,86), with no cursor/trigger/flag writes.

The real Rupert playback completes: monitorScenesSeen2, rupertSceneFinished1,
Rupert task gone, SWAT task retained. Additional confirms finish the camera
caption, then ordinary Cancel inputs close the monitor panel. At140435
monitorBrightness4 is persisted, monitor task gone, actor mode/state0,
event/UI0 and pendingMode0 restored. HP101/MP30, weapon19 and rewards retained.
The open panel, changed brightness and playback were visually inspected
(`build-port/video-monitor-trigger.png`, `video-monitor-brightness.png`,
`video-rupert-monitor.png`). This verifies camera playback and closure, not
an additional speaker-warning interaction.

New `--video-clock-rupert --frames 20000 --aim-cycle 180` generates140435
samples, recursively using the verified Security entry. Output matches the
live recording byte-for-byte; Python compilation and diff whitespace checks
pass. Two finite full-route probes are checking scene flags, brightness,
equipment, health and restored control. No production-code fix was required
for this interaction after the existing audio fixes.

Both full Rupert probes pass all10 expectations. Differing checkpoint groups:
none, including timing and RNG. Logs: `build-port/video-clock-rupert-{a,b}.log`.
The monitor task is absent and only the SWAT monitor actor remains after
closure; the Rupert actor has retired normally.


### Blue Key and left power lock after Rupert playback (2026-11-02)

The corrected native route now returns to cleared Hallway after the Rupert
monitor scene and collects Blue Key (collection260) through CAP2's key box at
(800,-928). The neighboring manual (CAP5) and extinguisher (CAP6) examinations
were explored first; neither yields the key. At154327 normal control/event/UI0
are restored and the collected display order contains[260,258,257,262]. New
`--video-clock-blue-key --frames 20000 --aim-cycle 180` generates154327 samples,
byte-identical to the capture; its finite video-clock probe passes eight
expectations (`build-port/video-clock-blue-key.log`).

Returning to Security, the power panel uses CAP2 at(192,144), distinct from
CAP1 graffiti at(-1088,-704). The panel opens with cursor(0,0). Moving to the
left lock(-56,32), choosing Item and confirming the actual Blue Key entry
consumes the key and starts the unlock scene. At159401 panelKeys1,
sanctuaryRouteProgress2, Blue Key absent, rupertSceneFinished1 retained,
actor mode/state0, event/UI0 and pendingMode0. HP101/MP30, weapon19 retained.
Actual key-item selection and the resulting scene were visually inspected
(`build-port/video-key-item-menu.png`, `video-blue-unlock-scene.png`).

New `--video-clock-blue-unlock` generates159401 samples using the verified
key prefix, byte-identical to the live input. Python compilation and whitespace
checks pass. Initial finite-probe launches did not run: a concurrent external
build temporarily removed the executable while relinking. Its process was
observed live, then terminal; the replacement binary is now present. The
current HEAD48d0b31 retains the SPU attribute implementation and overlay CMake
wiring. To avoid another relink interrupt, subsequent probes use a copied
binary `build-port/replay-bin/pe2-blue-unlock-48d0b31`; two full probes are
running. No build files were reverted by this task and no game-state values
were injected.

The two159401-sample probes on the copied replacement binary verify key
consumption, panelKeys1, sanctuaryRouteProgress2 and normal player/event/UI
state, but fail pendingMode0: each stops at pendingMode255 during the final
presentation handoff. The route is extended by120 neutral samples to159521;
it remains byte-identical to the live recording. Settled endpoint probes are
running against the same copied binary; the earlier failed gate is retained
in `video-clock-blue-unlock-{a,b}.log` rather than described as a pass.

Both settled159521-sample Blue Key unlock probes pass all11 expectations,
including pendingMode0. Differing complete checkpoint groups: none, including RNG/timing.
Evidence: `build-port/video-clock-blue-unlock-settled-{a,b}.log`. This also
checks the route against the externally rebuilt executable copied at HEAD
48d0b31, beyond the original live process.


### Fountain revisit, Forked Road and Observatory ride (2026-11-02)

After the Blue Key unlock, normal input revisits Fountain. At160958 the saved
hidden-path flag remains1 and the extra climb trigger is enabled/linked along
with all nine authored actions, verifying this branch's actual room re-entry.
The east/upper corridor reaches Forked Road at162274: area9/roomState2/
variant2/view4/warp3, root[-5107,129,-3780], yaw0, HP101/MP30,
weapon19, panelKeys1 and sanctuaryRouteProgress2 retained. A live160HP Stranger
is present; no Forked Road victory is claimed. `--video-clock-forked-road`
generates this capture byte-for-byte.

The controller route crosses to the escalator and executes the real outbound
and Observatory arrival movie paths. At164827: Observatory area10/roomState1/
variant1/view2/warp4, root[-2491,-2861,-1750], yaw1008, normal mode/state0,
event/UI0 and pendingMode0, HP101/MP30, weapon19. Arrival flag1, bat ambush0,
actorControl0, padScriptFlags0 and no remaining movie tasks. The rendered
arrival backdrop/player/HUD were visually inspected
(`build-port/video-observatory-arrival.png`). New `--video-clock-observatory
--frames 20000 --aim-cycle 180` generates164827 samples byte-identical to the
live recording. Two finite probes on copied binary48d0b31 pass11 expectations
and have identical complete checkpoint dictionaries, including timing/RNG
(`build-port/video-clock-observatory-{a,b}.log`).

A separate162274-sample Forked Road endpoint probe crashed before its EOF,
back in Gallery area20/HP100: `_stageResolvePlayerContacts` dereferences a
missing player task while `_sceneBattleResultTask` is queued with forced
reload entry258/spawnArg1=1. Log: `build-port/video-clock-forked-road.log`.
This resembles the earlier unresolved missing-player lifecycle failure; the
two successful longer-prefix probes do not invalidate it or prove global
replay stability. No NULL guard/state injection was added. `pe2-transition`
now records input sample index, player task pointer, display owner/hold and
both task lists even when full player collection is unavailable. It was
verified read-only in the live process at input164827. A replay of the failing
endpoint with expanded diagnostics is running. Later Observatory combat on
this corrected route remains unverified.

### Replay crash investigation: missing LLDB debug objects (2026-11-02)

The preserved `build-port/replay-bin/pe2-blue-unlock-48d0b31` executable still runs, but concurrent rebuilds have replaced several object files referenced by its Mach-O debug map. LLDB explicitly reports changed object timestamps and refuses their debug information. A fresh trace (`build-port/trace-session-clear.log`) completed the 162274-sample Forked Road recording without the earlier crash; it does not establish deterministic correctness. Some diagnostic values, notably HP, were silently reported as zero when their SBValue was unavailable. Do not infer a death/restart from those zeros.

`pe2-transition` now reports unavailable numeric values as JSON null, with `unavailableDebugValues`, while retaining the readable portion of the crash report. Verified against the affected executable in LLDB (`build-port/transition-missing-symbols.log`): HP is null and the unavailable list is populated; Python compilation passes. The session-reload/player-slot crash remains unresolved. Further source-level reproduction needs an isolated build with matching debug objects (or a preserved dSYM), rather than only a copied executable.

### Isolated replay build and verified divergence (2026-11-02)

Created `/tmp/pe2-reload-debug-20261102` as a copied source snapshot, including generated build headers and PsyZ, with separate CMake output. Snapshot metadata records HEAD f6b458eb46b2ff8a8cd418bcbecc2ddaf58861f2; the recorded working modification was docs/PORT_PLAN.md. Build completed. Preserved dSYM has the same UUID as the executable (64163E41-F8D3-352E-A68E-027BD5F9FA83); hashes and replay input hashes are saved alongside it. This is independent of subsequent main-tree object rebuilds.

Three finite runs have matching debug information and normal process exits, but different gameplay outcomes:
- `forked-road.log`: 162274 samples, expected Forked Road area9, root[-5107,129,-3780], HP101; both expectations pass.
- `forked-road-b.log`: identical input and binary, area4 Cafeteria, root[-1877,-170,-5700], HP40, sanctuaryRouteProgress0 rather than2; location expectation fails. This run was concurrent with the following Observatory run, so scheduling/load is a candidate variable, not a proven cause.
- `observatory-b.log`: 164827 samples, area10 Observatory, HP101; both expectations pass.

Full checkpoints and compact results are retained under the snapshot directory (`results.json`). No debug-map errors occurred. These runs do not prove the historical crash fixed; they prove that identical native input can diverge with a stable binary and valid symbols. Next investigation should compare earlier prefix checkpoints to locate the first gameplay divergence, rather than interpreting a normal exit as successful replay.

### Sampled route traces and host-stall experiment (2026-11-02)

In the isolated diagnostic snapshot only, added optional PE2_TRACE_ROUTE logging every1000 input samples: stage/area/roomState/variant/HP/MP/EXP/BP/weapon. Two concurrent full Forked Road runs (`trace-a.log`, `trace-b.log`) pass their area9 assertions and match all163 sampled state rows. Their EOF checkpoints differ only in timing: gameTick126034 vs126028 and loopTicks151774 vs151768; frameCount127789 and RNG1464263089 agree. This does not reproduce the earlier Cafeteria divergence and does not prove determinism between sampled points.

A subsequent diagnostic-only PE2_TRACE_HOST_STALL hook pauses50ms at input131000. `trace-stall.log` confirms the hook executed; all sampled rows still match and the final checkpoint again reaches area9/HP101. Only timing differs (frameCount127793, gameTick126024, loopTicks151758). Thus this particular pause is insufficient to reproduce gameplay divergence; do not claim it fixes or explains the crash. Trace comparison and full checkpoints are retained in `/tmp/pe2-reload-debug-20261102/trace-comparison.json`.

Code inspection identifies a concrete remaining host-time dependency: Psyz_VideoVSync(mode>=0) in PsyZ sdl3_common.h calculates scanlines from SDL_GetTicksNS even with PSYZ_AUDIO_CLOCK=video. Game-loop and display-task frame budgets use these values to choose whether to wait for a blank; input is polled by blank callbacks. Scene pacing also busy-waits on this counter, so simply freezing it at zero would hang active scene deadlines. Further investigation should measure or model this raster-clock path before changing timing semantics. No production clock behavior changed. The snapshot executable was rebuilt for diagnostic hooks and its dSYM regenerated; `hashes.json` records the original baseline, `trace-hashes.json` the first trace variant.

### Opt-in deterministic raster clock for offline replays (2026-11-02)

Implemented PSYZ_RASTER_CLOCK=virtual in PsyZ sdl3_common.h and exposed it as `replay_checkpoint.py --raster-clock virtual`. Normal/default host raster timing is unchanged. The offline model charges one scanline per raster query and resets at an explicit blank; it does not claim PS1 CPU-cycle accuracy. Progress on queries is necessary because the game busy-waits for scene raster deadlines. Together with PSYZ_AUDIO_CLOCK=video, this removes host-time measurements from frame-budget decisions. The runner records the selected raster mode in its log.

In the isolated diagnostic build, two full162274-sample Forked Road runs with virtual raster (`raster-a.log`, `raster-b.log`) produced identical complete checkpoint dictionaries, including all timing fields and RNG. The second injected the same50ms host stall at131000. Both area9/HP101 assertions pass; timing is frameCount127793/gameTick126024/loopTicks151756/RNG1464263089/vsyncCount162261. The final implementation (cached environment setting) also passes the164827-sample Observatory replay: area10 and HP101 (`raster-observatory.log`), normal exit.

Added raster_clock_test, which exercises actual PsyZ raster reads across a50ms host stall, deadline polling,16-bit wrap and explicit-blank reset. It passes with the new clock; rebuilding the same test against the old SDL timing header fails at the consecutive-read progression assertion; restoring the new header passes again. Logs: raster-test.log, raster-old-test.log, raster-restored-test.log under the isolated snapshot. The original crash is still not proven fixed. This change makes offline replay timing explicit and repeatable in the tested route; it does not establish global port determinism. PsyZ edits are in the nested submodule working tree and have not been committed.

### Observatory to Promenade: native controlled progression (2026-11-02)

The older controlled LLDB session handle4795 is terminal. Started a fresh controlled run from the164827-sample Observatory recording using the isolated executable, video audio clock and virtual raster clock. Current live handle99517, target17065, FIFO `/tmp/pe2-reload-debug-20261102/observatory-control.fifo`, log observatory-control.log. At170051 samples the game is in Promenade (stage1/area11/roomState1/variant1/view2/warp4), root[726,170,9050], yaw3072, HP29/MP30/EXP458/BP680. Sanctuary route progress4; arrivalMovieStarted1, battleFollowupState0; actor mode/state0, eventState0, uiOpen0, actorControl0, movie tasks empty. flowFlags10 are music-loading options, not transition errors; pendingMode0 and transitionTasks[] prove no retained mode request. Image `build-port/video-promenade-arrival.png` was visually inspected.

Crossed Observatory from the escalator entrance toward the north stairs. FACING_QUAD requires the body axis to oppose facingNormal (world_collision.h), so the exit with East-facing normal must be approached facing West. Confirmed the normal escape result (-10BP), then let the original Promenade arrival movie finish. Earlier exploratory turns and waiting cost72HP and are preserved in the input; no game-state writes were used.

Added `--video-clock-promenade` capture metadata (170051 samples, base video_clock_observatory164827), using video/virtual clocks. Generator output is byte-identical to the full controlled recording. A first finite attempt used the main-tree runner against the diagnostic snapshot: source-line differences meant its EOF breakpoint missed; the process itself exited normally but no checkpoint was collected, so it is not a passing validation. A second finite run uses the runner from the matching snapshot (promenade-finite-matched.log); collect its result before calling the route replay-verified. The live state and screenshot already prove native progression to the new room.

Promenade finite validation completed: `promenade-finite-matched.log` passes area11, HP29 and sanctuaryRouteProgress4, with normal exit and complete checkpoint. Subsequent live approach to Sanctuary died at170819 (HP-2); do not promote that suffix into a passing route. Retired only the owned dead live target17065 and debugger99517. A fresh controlled session84933/target16282 replays the verified170051-sample Promenade prefix, using promenade-control.fifo / promenade-control.log / promenade-controlled.pad in the isolated directory. Next action is ordinary menu use of Protein Capsule (item60): source item_use.c confirms +5 HP bonus and full HP restoration. No native state has been overwritten.

### Protein menu use and Sanctuary arrival (2026-11-02)

Fresh controlled Promenade session84933 successfully used item60 through Start -> Use -> right inventory pane -> row3 Capsule -> Use. Checkpoint170641 confirms HP29->115, HPmax110->115 and consumed item60; another Circle closes the menu by170769. Crossed the promenade at full health, facing East at the Sanctuary door and confirming the normal escape result. At173008 Sanctuary stage1/area12/roomState1/variant1/view16/warp3 is loaded, HP115, route progress5, objective6, bridgeProgress2. Arrival scene still active at that point.

At175544 a later fresh Start press completed the actual scene skip: actor mode/state0, root[-5724,130,-8276], eventState0, pendingMode0, transitionTasks[], inputBlockPolls0. No9 and Rupert tasks remain normally present; rupertLeft0/redKeyfalse. Image `build-port/video-sanctuary-ready.png` visually confirms Sanctuary, Aya and Rupert, with115HP. The native controls did not alter health or flags directly.

Added --video-clock-sanctuary (base video_clock_promenade170051, total175544), video/virtual clocks. Generated input matches the new full controlled recording byte-for-byte. Independent finite replay is running in exec session1626, `/tmp/pe2-reload-debug-20261102/sanctuary-finite.log`, checking area12, HP115, HPmax115, route5, actor mode0 and eventState0. Poll that handle before asserting finite validation complete. Live session84933 remains stopped at input175544; FIFO promenade-control.fifo and log promenade-control.log under the same snapshot directory.

### Sanctuary departure and Roof Garden arrival (2026-11-02)

The independent Sanctuary replay completed normally and passes all6 expectations (area12, HP115, maxHP115, sanctuary route5, actor mode0, eventState0). Continued the live controlled session84933 from175544. The scene skip leaves Aya facing West (yaw3072), not South; first exploratory movement ran into pew collisions. Successfully navigated via the outer west aisle: by176145 root[-9805,128,-4218], then approached the roof door from the west and faced South. At176455 the native Sanctuary departure task is active and bombSceneState becomes1.

A normal Start skip completes the Sanctuary departure; at177963 Roof Garden area13/roomState1/variant1/warp2 is loaded, arrivalSceneStarted1, rupertLeft1. Another normal Start skip ends its arrival scene. At178571 root[-7508,130,-8572], actor mode0, eventState0, pendingMode0 and transitionTasks[]; HP115/MP30/EXP458, Red Key still absent and enemyDropState0. Image `build-port/video-roof-garden-ready.png` was inspected and shows the normal controllable garden.

Added --video-clock-roof-garden (base video_clock_sanctuary175544, total178571), with video audio and virtual raster clocks. Generated file is byte-identical to the full native controlled recording. Finite verification is now running in exec78498, `/tmp/pe2-reload-debug-20261102/roof-garden-finite.log`, expecting area13, HP115, rupertLeft1, actor mode0 and eventState0. Poll the live handle before claiming replay validation complete. Controlled session84933 remains stopped at178571, FIFO promenade-control.fifo, log promenade-control.log. Next story work can return for the Red Key after Rupert's departure or explore the garden encounter; neither has been completed in this new route.

### Native Red Key collection after Rupert departure (2026-11-02)

Roof Garden finite replay completed normally and passes all5 expectations (area13, HP115, rupertLeft1, actor mode0, eventState0). Continued live session84933 from178571. Turned toward the garden's Sanctuary door and used a fresh confirm to return by179666: Sanctuary area12/roomState1/variant3/view7/warp2, Rupert and No9 tasks absent, rupertLeft1.

The actual Red Key placement is kind259/object flag28 at[-6600,-10,-8070], from generated rooms/akropolis/object_places_2.inc. Navigated Sanctuary's west outer aisle (root[-9490,130,-7390] at179857), crossed the front aisle and reached[-7060,130,-8080] facingEast at180170. Ten ordinary confirm/release cycles completed pickup and dismissed its UI. At180770 sanctuary.redKey=true, collected=[259,258,257,262], HP115/MP30; uiOpen0 and normal actor control. No game-state writes used.

Added --video-clock-red-key (base video_clock_roof_garden178571,total180770), video/virtual clocks. Generator is byte-identical to the controlled recording. Independent finite replay is running in exec54571, `/tmp/pe2-reload-debug-20261102/red-key-finite.log`, checking area12, HP115, Red Key, Rupert departure, actor mode0 and eventState0; poll before calling that replay verified. Live session84933 remains stopped at180770 with the same promenade-control.fifo/log under the isolated snapshot. Next progression can return to Roof Garden and its encounter while retaining the key.

### Roof Garden encounter: Tonfa, Pyrokinesis, rewards and loot (2026-11-02)

Red Key finite replay completed normally and passes all6 expectations. Continued live session84933 from180770, returned to Roof Garden by181758 with Red Key retained, area13/roomState1/variant1/warp1. Crossed the garden's first trap to arm enemyDropState1, then turned back through the second: at182401 enemyDropState2/crawlerEntranceReady1 and four Maggot Caterpillars80HP each are active.

Tonfa attack cycles inflict real damage; after12 cycles Aya has83HP and enemies58/37/80/59HP. Opened actual PE wheel with Triangle and cast Pyrokinesis: MP30->22; three enemies have negative HP and death tasks, last remains80HP. Continued Tonfa, advanced toward the last target and finished it. At184357 combat.battleRefs0, no room enemies, EXP482 (+24), BP782, MP26 (4MP battle reward), HP83. The first result confirm opened the Plastic Bottle loot pane rather than closing the entire result. Selected All, collected it, and dismissed the remaining presentation.

At185499 pendingMode0, transitionTasks[], uiOpen0, actor control enabled; Plastic Bottle item6 qty1 is in carried inventory, Red Key retained. battlePhase2/battleResetPending1 remain the game's completed-battle state; do not call them active transitions. Added --video-clock-roof-clear (base video_clock_red_key180770,total185499); generated input is byte-identical to live capture. Independent replay exec77401 is running, `/tmp/pe2-reload-debug-20261102/roof-clear-finite.log`, with9 expectations for area13/HP83/EXP482/MP26/BP782/no enemy refs/Plastic Bottle/Red Key/no pending mode. Poll before asserting finite replay verified. Live session84933 remains stopped at185499; FIFO promenade-control.fifo, log promenade-control.log in the isolated snapshot. Bomb examination and further story progression remain outstanding.

### Roof Garden bomb examined, helicopter objective advanced (2026-11-02)

Roof-clear finite replay completed normally and passes all9 expectations. Continued live84933 from185499, root[-7523,130,-8253]/yaw2861. Central pedestal blocks the direct south approach at[-4458,130,-5881]; navigated its east side via[-3384,130,-3618]. Approached the bomb at[-4356,130,-3546], yaw2069 (North, opposing the trigger's South normal), and confirmed normally.

At186181 the actual CAP caption says "Someone planted a bomb!"; objective advances6->7 and storyDialogue5->6, as the room's command4 handler specifies. Captured `build-port/video-bomb-examine.png`. Used ordinary confirm/release then backward movement to dismiss and leave the repeatable examine trigger. At186579 root[-4501,130,-2299], actor mode/state0, uiOpen0/eventState0/pendingMode0/transitionTasks[], HP83/MP26/EXP482/BP782 and Red Key retained. battleResetPending1 is still the completed encounter latch.

Added --video-clock-bomb (base video_clock_roof_clear185499,total186579), video/virtual clocks; generator matches full controlled capture byte-for-byte. Finite validation exec11786 is running, `/tmp/pe2-reload-debug-20261102/bomb-finite.log`, with8 expectations for area13, HP83, objective7, storyDialogue6, Red Key, actor mode0, closed UI and no pending mode. Poll before claiming replay verified. Live84933 remains stopped at186579 with promenade-control.fifo and promenade-control.log under isolated snapshot. Next progression: return with Red Key to Security Room and unlock its right panel lock; healing/reviving PE can also be exercised through ordinary menu if needed.

### Return toward Security: verified intermediate and failed combat suffix (2026-11-02)

Bomb finite replay completed normally and passes8 expectations. Continued live84933 from186579, navigated garden pedestal/flowerbed railings and returned to Sanctuary by188716: area12/roomState1/variant3, battleResetPending0, no retained mode request. Sanctuary->Promenade by189655 selects roomState2/variant2. By191370 reached Observatory area10/roomState1/variant2/view4/warp1, root[-2296,-2861,-11026]/yaw1024, HP83, Red Key retained and objective7. The return ride latch is1, actorControl0, movie tasks[].

Attempted to run through Observatory without fighting. Progress stopped near[-1915,-2860,-5149]; the next suffix ended in actual game over at193486. `pe2-transition` confirms HP-3/deathVariant2, location0 and _gameOverTask, not the historical NULL-player stage crash. Room variant2 resources are actor01100 (not variant3's scripted bats). Failed suffix must not be called a passing route. Retired only the owned dead target16282; its log/record remain intact.

Added --video-clock-observatory-return, total191370/base video_clock_bomb186579. It reproduces the living return-room arrival prefix exactly, before combat. Finite verification exec19066, observatory-return-finite.log in isolated snapshot, is running with area10/HP83/objective7/collected[259,258,257,262]/actor mode0 expectations. Fresh controlled recovery exec95430 is also replaying that191370 prefix, using return-control.fifo, return-control.log and return-controlled.pad under `/tmp/pe2-reload-debug-20261102`. Poll these handles before further action; new controlled breakpoint is psyq_host.c:301 and initial endpoint191370. Next action should inspect the room's actual enemies and fight/PE rather than repeat the failed running suffix. Security right-lock unlock remains outstanding.

Observatory return finite replay has now completed normally: all5 expectations pass (observatory-return-finite.log). Fresh controlled recovery95430 remains live and is still replaying the same prefix.

### Return Observatory Mossbacks cleared without HP loss (2026-11-02)

Controlled recovery95430 reached191370 normally; target68839, return-control.fifo/log/return-controlled.pad in isolated snapshot. Confirmed two actor01100 Mossbacks280HP each at[-1600,-2990,-4500] and[-4500,-2990,-8000]. Extended pe2-checkpoint Mossback rows with model root position and typed work state/mode/reaction/recentDamage/hidden; verified the read-only values against live symbols and actual work definitions.

Approached the west Mossback and cast Pyrokinesis twice through the real PE wheel: HP280->132->0, Aya HP83 unchanged, MP26->10. Approached the other enemy and cast once (HP280->136, MP2), then Tonfa attacks finished it. At193408 both enemies gone, battleRefs0, EXP786 (+304), MP12 (+10 reward), BP986 (+204), HP83 unchanged. Selected normal result/loot All and dismissed the presentation; at194150 pendingMode0/uiOpen0 and carried item161 qty50 (9mm ammo) added, Red Key retained.

A control batch sum assertion prevented sending an incorrectly sized result batch. During debugger interruption, LLDB lost the lexical binding of `index` in its breakpoint condition and stopped with an evaluation error at193416; the target did not crash. Replaced the condition with a read-only dereference of the resolved static Psyz_PadsOverride.padFrame symbol address, then resumed the already-queued remainder to194150. The current breakpoint1 condition uses that absolute address; for further endpoints resolve FindSymbols('Psyz_PadsOverride.padFrame') and set the numeric-memory condition rather than relying on a selected-frame index expression.

Added --video-clock-mossbacks-clear (base video_clock_observatory_return191370,total194150), video/virtual clocks. Generator matches full recording byte-for-byte. Finite replay exec86373, `/tmp/pe2-reload-debug-20261102/mossbacks-finite.log`, is running with8 checks (area10,HP83,EXP786,MP12,BP986,no battle refs,9mm50,no pending mode). Poll before claiming finite verification complete. Live95430 is stopped at194150, target68839. Next progression can now cross the empty Observatory to Forked Road and onward to Security Room.

### Forked Road return encounter: failed escape, recovery prepared (2026-11-02)

Mossbacks finite replay completed normally and passes all8 expectations. Continued live95430 from194150; Observatory exit/return ride reached Forked Road at195694 (stage1/area9/roomState2/variant3/view3/warp5, root[-560,129,1126], HP28). The long1200-neutral arrival tail allowed damage from the new encounter; do not treat that loss as transition corruption. Variant3 contains actor401000 Stranger plus three rats18HP. Added _actor401000StrangerTask to the checkpoint's existing typed Enemy HP census (verified live, HP109 after a Pyrokinesis cast), so the new encounter is no longer undercounted by the diagnostic.

At195930 a real Pyrokinesis cast spent MP12->4; rats remained18HP, Stranger109HP. Attempted running toward Fountain, but hits and recovery interrupted turning/movement. HP17 at196568,7 at196855; attempted Tonfa recovery ended at197215 in normal game over. pe2-transition confirms HP-3/deathVariant1, area0 and _gameOverTask; this is not the historical reload NULL-player crash. No passing route was generated from the failed suffix.

Retired only owned dead target68839/session95430. Fresh controlled recovery exec68412 replays verified video-clock-mossbacks-clear194150; FIFO mossback-return-control.fifo, log mossback-return-control.log, recording mossback-return-controlled.pad in `/tmp/pe2-reload-debug-20261102`. Poll before acting. It imports the current main-tree checkpoint tool, with the new Stranger census. Initial breakpoint1 is psyq_host.c:301; after initial stop resolve static padFrame numeric address for conditions. Next action: ordinary menu preparation before Observatory exit, equipping M93R with the collected50 rounds and learning/casting Healing if viable (current verified state HP83,MP12,EXP786). The legacy generator documents the actual Start->PE->Water->Healing->Revive->Yes input path; Healing slot7 is confirmed by attachment_state.h. Then revisit Forked Road with a shorter arrival wait and proper combat preparation. Security right lock remains outstanding.

### Native Healing revival, cast, M93R equip and Hydra loading (2026-11-02)

Controlled recovery68412 reached verified194150 Mossback-clear prefix. Used actual Start->PE->Water->Healing->Revive->Yes controls. At195084 Healing slot7 becomes level1, EXP786->36 (750 spent), MP maximum30->31 and current MP12->31. Closed menu, opened actual PE wheel and cast Healing: at195828 HP83->113, MP31->19 (12 spent), ability7 active. No state edits.

Navigated Use inventory and moved M93R into the weapon slot (weapon2, Tonfa retained). Ammo is item161 **9mm Hydra**, not ordinary9mm; screenshot identified it upon loading. Reload buttons alone do not select carried ammunition while the weapon supply is empty. In Use inventory selected ammo row3 -> Load -> M93R submenu -> confirm. Screenshot shows20 loaded and30 spare. Closing menu applies weaponSlotItem2; at198826 M93R is active, HP113/MP19/MPmax31/EXP36, uiOpen0/pendingMode0/transitionTasks[]. Carried total161 remains50 because loaded rounds are included in stock totals.

Added --video-clock-prepared-return (base video_clock_mossbacks_clear194150,total198826), video/virtual clocks; generated input equals the full recorded controller file. Finite exec45646 is running, `/tmp/pe2-reload-debug-20261102/prepared-finite.log`. One supplied expectation uses parasiteEnergy.levels.7; the already-running snapshot runner only supports dict traversal, so it will reject that path even if gameplay succeeds. Main-tree replay tool now implements checkpoint_value with list-index traversal, verified against level vectors, numeric inventory keys and out-of-range/negative indices. After the finite process ends, validate all10 intended conditions from its actual checkpoint using the new resolver instead of rerunning the route just for the old checker limitation.

Live controlled68412 remains stopped at198826, using mossback-return-control.fifo/log and mossback-return-controlled.pad under the isolated snapshot. LLDB Python variable addr is resolved to this process's static padFrame; use numeric-memory breakpoint1 conditions. Next action: Observatory exit with prepared M93R/Healing, shorten the long arrival neutral wait into Forked Road, then handle the Stranger/rat encounter or escape promptly. Security right lock remains outstanding.

Prepared-return finite process has now completed. Its old checker rejected the list path as anticipated; audited the actual single EOF checkpoint with the corrected resolver and verified normal exit: all10 intended conditions pass. Saved prepared-checks.json beside the log. No extra gameplay run was needed.

### Prepared Forked Road victory and return to Fountain (2026-11-02)

Continued live68412 from198826. Same Observatory exit with only300 neutral arrival samples reaches Forked Road by199470 with full prepared HP113, showing the previous long idle tail was avoidable combat exposure. New encounter is Stranger180HP plus three rats18HP. Twelve M93R attack/reload cycles kill Stranger (HP-4) with15 Hydra rounds, no HP lost. Further cycles kill two rats; last rat7HP is finished after backing away while aiming, then firing.

At201180 all active refs0, EXP36->90 (+54), MP19->26 (+7 reward), HP103 and statusFlags0 (status4 acquired during combat clears at result). BP986->1134 (+148); Hydra stock50->3. Corpse task _actor401000StrangerTask remains in task census with negative HP, so empty task list is not a valid requirement for victory; battleRefs0 is the active-enemy evidence. Result/loot confirms collect item8 qty1 and restore uiOpen0/pendingMode0 by201922.

Crossed Forked Road toward the Fountain door. Direct approach atx-4559/z-3100 hits its side obstruction; aligning tox≈-5100 permits the north-facing door trigger. At203121 Fountain stage1/area8/roomState1/variant1/view6/warp2, root[4015,129,3348]/yaw2048, HP103, MP26/EXP90/BP1134, Red Key retained and battleResetPending0/pendingMode0.

Added --video-clock-fountain-return (base video_clock_prepared_return198826,total203121), video/virtual clocks. Generated input is byte-identical to full capture. Finite replay exec62822, `/tmp/pe2-reload-debug-20261102/fountain-return-finite.log`, is running with8 expectations for area8/HP103/EXP90/MP26/BP1134/Hydra3/retained keys/no pending mode. Poll before asserting replay verified. Live68412 remains stopped at203121, LLDB addr variable and numeric-memory breakpoint conditions; FIFO mossback-return-control.fifo/log/record in isolated snapshot. Next step: traverse Fountain to Hallway and Security, then consume Red Key in right panel lock.

### Security right lock released with Red Key (2026-11-02)

Fountain-return finite replay completed normally and passes8 expectations. Continued live68412 from203121. Navigated north around Fountain, then west to Hallway door: at204604 Hallway area7/roomState1/variant4, HP103. Its Security exit queues the normal escape result; confirmed that result and arrived in Security by205308, BP1134->1124 (-10 escape), HP103.

Power panel CAP2 is at[192,-1088,144]. Approached from the doorway, faced East and opened it at206032. Cursor starts[0,0]; Right32/Down16 moves to[64,32], inside the right-lock hotspot[54,20,24,24]. An initial prompt input sequence selected Examine (not Item) while its opening was still in progress; the captured route preserves the actual caption dismissal and correction. Once prompt state4 was ready, Down selects Item, confirm opens collected inventory, confirm selects first row Red Key. At207206 usedKey2 and on-screen "Used Red Key." notice prove the actual key selection. Fresh confirm starts the authored unlock.

At208214 panelKeys1->3, collected list[258,257,262] (Red Key259 consumed), panel task list[], eventState0/uiOpen0/pendingMode0/transitionTasks[], actor control restored to Security room. HP103/MP27/MPmax31/EXP90/BP1124, M93R/Hydra selected. Screenshot build-port/video-red-unlocked.png visually confirms returned room, rather than a retained panel overlay.

Added --video-clock-red-unlock (base video_clock_fountain_return203121,total208214), video/virtual clocks. Generated input exactly matches full recorded controls. Finite validation exec64878 is running, `/tmp/pe2-reload-debug-20261102/red-unlock-finite.log`, checking area6,HP103,both keys3,Red Key consumed,actor mode0,eventState0,uiOpen0 and pendingMode0. Poll before marking finite verification complete. Live68412 remains stopped at208214; FIFO mossback-return-control.fifo/log/record in isolated snapshot, Python addr static padFrame for breakpoint conditions. Next progression can leave for the now-accessible bridge route. Full port remains incomplete.

### Current-tree integration validation after runtime asset conversions (2026-11-02)

Red-unlock baseline finite replay completed normally and passes8 expectations. To avoid continuing only on the older f6b458e snapshot, copied the current tree (HEAD91cf090 plus recorded local modifications) into `/tmp/pe2-current-debug-20261102`, including generated build/include and nested PsyZ edits. CMake configure/build succeeds for parasite-eve-ii-pc and raster_clock_test; raster test passes. Generated matching dSYM UUID52694A72-AC3C-3A7D-9E0B-DB5E532EB28C. Snapshot.json and hashes.json record source state, executable, relevant code and input.

Ran the complete208214-sample video-clock-red-unlock route on this current build with video/virtual clocks. Loader reports3128 arrays loaded from disc; no missing/debug-map/asset-size errors in the log. Finite runner exits normally and passes all8 checks. **Entire checkpoint dictionaries equal** the earlier baseline (including timing, RNG, inventory, PE and story/panel fields), saved in comparison.json. Exported displayed frame at VRAM y272 is byte-identical PNG to prior build-port/video-red-unlocked.png, SHA2561f24b8c2375416678e7d09073b2bc2c6af5d45129e357e6d71892f7257f38812. This validates the current runtime asset conversions over this route, not every game asset/overlay.

Started a fresh controlled current-build session77024 to carry progression onward: replay video-clock-red-unlock208214, record bridge-controlled.pad, FIFO bridge-control.fifo, log bridge-control.log under the new snapshot directory. Initial control breakpoint is psyq_host.c:299 (the current source, without older diagnostic hooks). Poll this handle; it is replaying until input208214. Old live68412 remains stopped at208214 in the previous snapshot; keep it until the new current-build checkpoint is confirmed, then retire only that owned process. Continue bridge-route work on the current build.

### Current-build departure from Security to powered Fountain (2026-11-02)

New current-build controlled77024 reached208214; its complete live checkpoint equals the verified red-unlock reference. Retired only old owned live68412. Continued on current snapshot `/tmp/pe2-current-debug-20261102`: control source breakpoint299, Python addr resolves padFrame in this process, FIFO bridge-control.fifo/log bridge-control.log/record bridge-controlled.pad.

Security->Hallway reaches208863, area7/variant4, Odd Stranger180HP plus four rats18HP. Escape attempt was disrupted by hits; some casts were ignored during damage mode and two Pyrokinesis casts spent16MP without observed enemy damage (one faced the wrong direction, another did not hit). Do not label these a verified spell fault: native aim/range/timing are not isolated. Added rootPosition to rat/actor401800/actor401000 checkpoint rows using the same typed model-coordinate read used for other actors; verified live values. A short alternating Cross/Square sequence coincided with recovery to normal mode; causality/hold escape was not proven.

Hallway's east approach atx≈2434,z≈-304 is obstructed by the counter. Moved north toz-895 before heading east; at211221 Fountain exit queued the actual escape result. Confirmed normally: at211529 Fountain area8/roomState2/variant2/view3/warp3, root[-4781,130,-4766], HP24/MP12, statusFlags0 and BP1114 (-10 escape). The powered room variant follows both panel keys3. Used actual Healing wheel outside battle; at211815 HP54/MP0, actor mode0, uiOpen0/eventState0/pendingMode0. Objective7 and key consumption remain retained. This is a passing native intermediate, not Bridge arrival.

Added --video-clock-powered-fountain (base video_clock_red_unlock208214,total211815), video/virtual clocks; generated controller stream equals full live recording. Finite verification exec95585, powered-fountain-finite.log under current snapshot, is running with8 checks (area8,roomState2,HP54,MP0,status0,panelKeys3,BP1114,pendingMode0). Poll before marking replay verified. Live77024 remains stopped at211815. Next progression must cross Fountain toward Forked Road; bridge route and later content remain outstanding.

### MP Boost1/Healing and powered Fountain south-west gate (2026-11-02)

Powered-Fountain finite replay completed normally and passes8 expectations. Continued live77024 from211815. Verified item6 Plastic Bottle is MP Boost1 (item_use.c nominal +25MP), used it through ordinary inventory; consumed item6 and observed MP30 after the complete menu batch at212683. Cast Healing outside battle: HP54->84/MP30->18 at212969, menu closed.

Attempted the north crossing of powered Fountain but enemy hits and camera-transition input suppression disrupted the batched heading changes. At213249 HP64. Traversed west side then south instead. A later confirm activated the **south-west Patio gate**, not the intended south-east Forked Road gate; actual caption "Unlocked the door" was inspected in fountain-south.png. Preserve this destination distinction. The caption and actual reload took further input; a checkpoint attempt during reload correctly failed due to missing player while pe2-transition already identified area3. Earlier ad-hoc parsing could otherwise have reused the previous checkpoint line; for the final observation sent a unique CP_DONE_215064 marker and parsed only the new stop's checkpoint/error.

At215064 actual Patio stage1/area3/roomState3/variant4/view6/warp2, root[4986,130,-3831]/yaw0, HP64/MP19, status0, uiOpen0/eventState0/pendingMode0/transitionTasks[]. Both panel keys3 remain. Added --video-clock-powered-patio (base video_clock_powered_fountain211815,total215064), video/virtual clocks, explicitly named for the actual destination. Generator is byte-identical to full recording. Finite validation exec47377, powered-patio-finite.log under current snapshot, is running with7 checks (area3,variant4,HP64,MP19,item6 absent,panelKeys3,no pending mode). Poll before calling it verified.

Live77024 is stopped at215064, same current snapshot FIFO bridge-control.fifo/log bridge-control.log/record bridge-controlled.pad, Python addr and source breakpoint299. Next route should return from Patio to Fountain and take the east gate after confirming each camera/heading change; do not replay the earlier attempted batched east turn as a proven path. Bridge has not been reached.

### Correct powered Fountain crossing to post-Red Forked Road (2026-11-02)

Powered-Patio finite replay completed normally and passes7 expectations. Continued live77024 from215064, turned north and re-entered Fountain by215394: root[-3896,131,3441], yaw2048. A direct eastward crossing from the south-west entrance stops near[-3520,130,2701]; this is not a connected unobstructed crossing to the east gate. Navigated north along west side instead, reaching[-4052,129,-4798] at216209. Compared the earlier verified video_clock_forked_road suffix (from its Hallway-side Fountain arrival): its north-strip eastward run, then south along east side, is the proven topology.

Turned East and ran260 samples; by216552 root[3865,128,-3136], yaw992, HP64. Turned south, ran180 and confirmed the east gate; at216943 the native escape result held reload. Confirmed normally; at217251 Forked Road area9/roomState2/variant4/view4/warp3, root[-5107,129,-3780]/yaw0, HP64/MP20, panelKeys3, objective7, status0, pendingMode0/transitionTasks[], actor mode0. New variant4 has4 battle refs with battlePhase0 and ambushSeen0; scripted post-Red ambush is not yet completed.

Added --video-clock-powered-forked (base video_clock_powered_patio215064,total217251), video/virtual clocks. Generated stream exactly matches full controlled capture. Finite verification exec63241, powered-forked-finite.log in current snapshot, is running with8 checks (area9,variant4,HP64,MP20,panelKeys3,ambushSeen0,pendingMode0,actor mode0). Poll before calling replay verified. Live77024 remains stopped at217251, current build, source breakpoint299/numeric addr condition, bridge-control.fifo/log/record. Next step is the new Forked Road ambush and the Observatory bat-state route toward Promenade/Bridge; not yet Bridge arrival.

### Post-Red Forked Road victory and Observatory arrival (2026-11-02)

Powered-Forked finite replay passed all8 expectations. Current-build controlled route then equipped Tonfa, triggered authored Caterpillar entrance and defeated4 enemies using Pyrokinesis, Healing and Tonfa. At220613 ambushSeen1, battleRefs0, battlePhase2, HP58/MP4/EXP114/BP1206; reward Recovery1 collected, results closed and control restored. Added video_clock_forked_ambush_clear; regenerated input equals physical recording. Independent finite replay completed normally and passed all9 expectations, forked-ambush-finite.log in current snapshot.

Continued ordinary inventory inputs; unsuccessful attempts preserved in capture. Screenshot identifies inventory rows Spray Can, M93R, Tablet (Recovery1), 9mm Hydra, Medkit (Penicillin). Recovery1 actual use raises HP58->108 (observed +50; supersedes earlier assumed +45), removes item1. Crossed cleared Forked Road to Observatory at223637: area10/roomState2/variant3/warp2, root[-2408,-2861,-1748], yaw1024, HP108/MP4, pendingMode0, no transition tasks. Added video_clock_powered_observatory with full captured suffix. Live77024 stopped at223637; bridge-control.fifo/log/record in /tmp/pe2-current-debug-20261102. Bridge remains unreached; full port incomplete.

### Observatory post-Red bat ambush cleared (2026-11-02)

Powered-Observatory independent finite replay completed and passes7 expectations. Continued live77024 at223637, moved east from entry then north. By224003 authored ambushSeen1 and scripted control; at224603 nine bats active, one holding player, HP90. Alternating fresh Cross/Square presses breaks holds; Tonfa aim/attack bursts kill bats. At225041 six battle refs and HP75; at225613 one battle ref and HP66. Final alternating release/attack bursts defeat last bat; results confirmed and closed. At226749 area10, actor mode0, battlePhase2/refs0, roomEnemies[], uiOpen0/pendingMode0; HP66/MP13/EXP159/BP1368 (reward +45EXP/+9MP/+162BP). Root[-2925,-2860,-5576], yaw3741. No memory edits or synthetic target calls.

Added video_clock_observatory_bats_clear, base223637 total226749, full physical recording; finite replay to be checked before claiming reproducibility. Live77024 remains stopped at226749 with bridge-control.fifo/log/record in current isolated snapshot. Next route continues north to Promenade, then Bridge; full port remains incomplete.

### Powered Bridge reached from cleared Observatory (2026-11-02)

Observatory-bats finite replay completed normally, all9 expectations pass. Continued live77024 from226749. First turn wrapped yaw and travelled south; preserved this physical input in captured route. Corrected yaw north and reached Observatory north door; by227925 Promenade area11/roomState2/variant3/warp1 root[642,170,9120], HP66/MP13. Followed west aisle north to bridge door trigger[-2208,-128,-2048], facing west. At228993 normal escape result holds reload (pendingMode129); fresh confirms release it.

At229409 Bridge area14/roomState1/variant1/view6/warp1, root[-3643,130,-2161]/yaw3072, actor mode0, pendingMode0/transitionTasks[], uiOpen0, actorControl0. HP66/MP14/EXP159/BP1358 (escape fee10), panelKeys3/bridgeProgress2. Three enemies present, battlePhase0. Displayed VRAM export bridge-arrival.png visually confirms room with bridge controls and three enemies. No memory edits. Added video_clock_bridge_arrival base226749,total229409, generated stream matches full physical capture. Independent finite replay started separately; do not claim it passed until result inspected. Live77024 stopped at229409, bridge-control FIFO/log/record in /tmp/pe2-current-debug-20261102. Next progression is bridge control and encounter; full port remains incomplete.

### Bridge keypad accepted and movie restored control (2026-11-02)

Bridge-arrival independent finite replay passes9 expectations. Continued ordinary inputs from229409, approached keypad[-4544,-128,-448] facing west. Keypad opens correctly. Initial hotspot menu retains Item selection; captured unsuccessful Item/list attempts preserved. Explicit Up after menu settles selects Examine, keypadExamined1. Cursor physical movements enter5,6,1; accepted code starts native bridge movie and enemy presentation.

Important capture diagnostic: movie consumes200 fewer pad samples than planned advance budget; expected endpoint breakpoint was missed. Interrupted only owned live PID97813 after stderr confirmed FIFO wait234673 and physical recording234673 samples. Fresh stopped checkpoint proves Bridge roomState2, bridgeProgress3, view6, actor mode0 root[-4215,129,-541], no bridge tasks, pendingMode0/transitionTasks[]. Thus movie completed and returned control. Earlier checkpoint requests while process running were stale and are not completion evidence. Physical recording is authoritative; added video_clock_bridge_raised base229409,total234673. Generated stream matches recording. Independent finite replay queued to validate actual endpoint. Live77024 stopped in FIFO read; numeric addr conditional remains required and next input should start from234673. Full port incomplete; bridge encounter/crossing and Fire Escape remain next.

### Fire Escape entry exposes room initialization diagnostic (2026-11-02)

Bridge-raised finite replay passed7 expectations. Continued live77024 from actual234673, navigated north to bridge descent trigger then west over lowered walking surface. At236087 direction climb active; at236665 westbound root[-10748,-871,-2378]. Opposite ascent restores rootY130 by237491. Fire Escape door first executes authored EVS scene, sets bridgeFireEscapeDoorSceneSeen1; at238521 normal escape result pending129. Confirmed results; at238937 area15/roomState1/variant1/view2/warp1 root[2628,1,-183], HP66/MP15/EXP159/BP1348. At239337 after400 neutral inputs, diagnostic still roomRuntime.controller=null and pendingMode255, grid _gAkropolisFireEscapeCollisionGrid, actor mode0/surface0. Do not claim complete playable initialization yet. Fire Escape implementation is linked and stage task descriptor names akropolisFireEscapeRoomTask; its init should publish GAME_TASK_SLOT_ROOM. Next work must inspect live task list/display state and enum representation before deciding whether controller absence is target bug or diagnostic issue. Added diagnostic video_clock_fire_escape_entry physical route234673->239337. Live77024 stopped at239337; same FIFO/log/record, current isolated build. Full port incomplete.

### Fire Escape entry crash identified: Lesser Stranger pre-init work access (2026-11-02)

Correction to previous entry: live77024 had stopped on EXC_BAD_ACCESS at actual input238611, not successful endpoints238937/239337. Process status and backtrace prove _lesserStrangerTask:608 dereferenced NULL work+0x59a on PHASE_INIT, before _lesserStrangerInit allocated it. Diagnostic route metadata already has correct physical totalSamples238611. Room slot was unset because loading had not completed; pending255 is DISPLAY_MODE_BARE_OT during loading, not itself the cause. Earlier marker-based reads did not verify stop reason, so the apparent settled state was invalid.

Fixed source src/enemies/stranger/lesser/lesser_stranger.c: preserve phase initialization before accessing saved presentation state; uninitialized paused/hidden actors wait for running control, existing initialized actors retain visibility transition handling. On failed init allocation, return after initializer kills task. Copied only this source into current isolated snapshot, rebuilt successfully and regenerated dSYM. Started finite verification exec47026 with physical Fire Escape entry plus600 neutral samples, checking area15, mode0, pending0 and actual akropolisFireEscapeRoomTask controller. Poll fire-escape-fixed-result.json/log before claiming fix verified; further crashes remain possible. Old live77024 is a stopped crash artifact (PID97813), do not feed input or treat it as running gameplay.

### Fire Escape presence-message callers repaired (2026-11-02)

Reviewed next initialization path while finite exec47026 remains live (runnerPID5300, LLDB8142, game9628; current log advancing). _lesserStrangerIsPresentMessage unconditionally writes its fourth payload u32*. Both Fire Escape callers passed zero: _akropolisFireEscapeHandleRoomCommand gate and _akropolisFireEscapeDisableAbsentActorInteraction. Replaced with local u32 output and TASK_MESSAGE_DISPATCH_SECOND_POINTER, preserving handler return and decision logic while carrying full native pointer width. Syntax check passes using isolated game's actual overlay defines/includes/compiler flags; git diff --check passes. This source is not yet copied/relinked into snapshot because first-init replay is running against its matching executable/dSYM. Next inspect exec47026 result, then copy Fire Escape source, rebuild/dSYM and repeat Fire Escape entry+600 settled replay. Do not restart first replay while live.

### Independent replay confirms second Fire Escape crash (2026-11-02)

Exec47026 ended with EXC_BAD_ACCESS address0 at _lesserStrangerIsPresentMessage:696, presenceResultNULL. This proves the first initialization fix passes its previous crash and reaches the next room initialization query. Previously identified presence caller fix addresses the observed failure. Copied Fire Escape source into isolated snapshot and launched combined build/dSYM/full physical replay plus600 neutral samples (fire-escape-combined-finite.log/result). Poll its live exec handle before claiming pass.

Hardened main tools/port/replay_checkpoint.py command: requires stopped process and rejects exception/fatal-signal stops, with explicit instruction to use pe2-transition/bt; SIGINT remains allowed for controlled FIFO inspections. Verified directly on old crashed live77024: pe2-checkpoint now returns `checkpoint rejected after target fault: EXC_BAD_ACCESS ...` and emits no normal checkpoint. Python compile and diff checks pass. This prevents the misleading crash-state-as-settled-state interpretation from earlier turns. Existing snapshot runner used for combined replay remains matching its target EOF source.

### Combined Fire Escape verification and continuation sessions (2026-11-02)

Combined build succeeds, no C compile failure; recorded exact updated source/binary/input SHA256 in /tmp/pe2-current-debug-20261102/fire-escape-combined-hashes.json. Finite replay exec78861 remains live (runner16878), log advancing; no terminal result yet. Started separate controlled continuation exec66791 with the same combined binary/dSYM, replay fire-escape-settled.pad239211 samples, record fire-escape-controlled.pad, FIFO fire-escape-control.fifo, logs fire-escape-control.log/fire-escape-stderr.log. It is replaying and should stop at source control breakpoint299 after EOF; do not feed live input until stop reason and fresh checkpoint are checked. Old77024 remains a crash artifact. Added area15 fireEscape.telephoneInspected, telephoneDialogueCounter and sceneEvent diagnostics to main runner; py_compile/diff checks pass. Need reload main runner in new controlled LLDB once stopped to access these added fields. Next poll both exact handles; inspect combined result, then continue actual Fire Escape gameplay.

### Fire Escape initialization verified after both fixes (2026-11-02)

Combined finite exec78861 completed normally and passed4 expectations: area15, actor.mode0, pendingMode0, roomRuntime.controller akropolisFireEscapeRoomTask. At239211 root[2600,128,-183], surface2, HP66/MP15/EXP159, Lesser Stranger hp50/taskState1, no movie tasks/transition tasks. Confirms removal of pre-init NULL work crash and NULL presence output crash across complete route, not full enemy lifecycle. Added reusable video_clock_fire_escape_ready route (base entry238611 +600 neutral =239211), equal to verified temporary fire-escape-settled.pad. Controlled66791 remains replaying same239211 input; wait for breakpoint299 before continuing. Full port incomplete.

Controlled66791 first run exited1 after completing all239211 replay samples because the new control FIFO did not exist. Explicit terminal result; not gameplay crash. Created named pipe fire-escape-control.fifo. The old PTY handle was gone, so started a new interactive controlled session using same launch script, fire-escape-control-retry.log. Poll new handle; startup must replay again. First PID72702 is terminal.

### Fire Escape Lesser Stranger lifecycle played through (2026-11-02)

Controlled retry45626/PID27392 successfully stopped at FIFO breakpoint239211, no crash. Main guarded checkpoint confirms initialized room/enemy and Fire Escape flags sceneEvent5/telephoneDialogueCounter3/telephoneInspected0. Static padFrame addr4403466432 bound to LLDB addr. Walked west18, turned north23, approached gate and confirmed its CAP; after fresh confirms at239954 control restored, enemy hp50.12 Tonfa aim/attack bursts reduce it to-3 at240394, taskState3 and battleRefs0. Waited death sequence then confirmed result/loot; at241178 enemy taskState4, HP66 (unchanged), MP19/EXP201/BP1430, carried Recovery2 item2 qty1. Results closed, actor mode0/pendingMode0, controller present. Confirms death/reward path live, beyond initial entry regression.

Added video_clock_fire_escape_clear, base239211,total241178, generated stream matches full physical capture. Independent finite replay launched separately; poll its result before claiming reproducibility. Live45626 stopped at241178 in source breakpoint299, fire-escape-control.fifo, fire-escape-controlled.pad, fire-escape-control-retry.log; numeric addr4403466432, PID27392. Next inspect bomb at[1312,-96,1856], telephone down stairs[-3392,-1856,2080], then route to Helicopter Landing Pad. Full port remains incomplete.

### Fire Escape bomb CAP progression under investigation (2026-11-02)

Fire-Escape-clear finite exec57201 completed normally, all9 expectations pass. Continued controlled45626 from241178: turned south/run100 then west toward bomb trigger[1312,-96,1856]. At241710 root[1714,2,1672], view8, sceneEvent5->7, actorControl2, CAP scene active. Screenshot fire-bomb.png shows bomb closeup and "Who could have set this...?". Further physical confirms switch to view3 and screenshot fire-dialogue.png shows "Maybe that man who attacked Rupert...?". At244695 still actor mode2/control1, no crash, storyDialogue6 unchanged, phoneInspected0, HP66MP19EXP201BP1430. Do not claim scene completed or phone reached. pe2-transition lists capEventTask/capPlaybackTask state1; no loading/transition pending. Main input masks gPadConfirmButtonMask64 (logical, physical Cross16384), no inputBlockPolls. Need inspect CAP record index/phase/delay/reveal fields, ensure fresh confirm handling; source captions.c around450-510 controls advancement. Live45626/PID27392 stopped at244695; addr4403466432; all suffix physical inputs retained in fire-escape-controlled.pad. Verified clear route241178 remains independent passing regression; newer bomb suffix not yet packaged as passing.

### Bomb CAP confirmed responsive; descent to telephone (2026-11-02)

Continued live45626 from244695. Read-only breakpoint captions.c478 proved physical Cross maps to logical buttons64/pressed64, no block polls. Step-over entered confirmation branch. At captions.c497 recordIndex8/variantKey2, next record9 textRef END. Thus CAP is responsive; repeated confirms near hotspot can reopen it, not a verified caption engine bug. Disabled temporary breakpoints2/3. Completed remaining8-sample press and300 Down/back input; at245003 actor mode0/actorControl0, moved out to[2624,130,1527]. StoryDialogue remains6, objective7, sceneEvent7; do not claim helicopter dialogue progressed.

Moved south corridor then west on platform:245612 root[1624,131,3762]. West run+confirm55 and fresh confirm engages descent action9. At246035 root[-2870,-1698,3882], direction.active1/control1/phase3, actor mode2/state3/phase1, scriptedMotionPending1. Native stairs moving normally; wait to finish before turning north toward telephone[-3392,-1856,2080], face East for interaction. Live45626/PID27392 stopped at246035; numericaddr4403466432 and usual fire-escape FIFO/record. No target writes. Full suffix remains physical record; no passing route yet for bomb/descent. Previous clear replay passed9.

### Fire Escape telephone conversation completed (2026-11-02)

Continued live45626 from246035 through stairs to[-3299,-1798,2424], facingEast1048. First telephone CAP queues display transition; confirms open repeat phone room cutscene(view9/state8->9). Menu opens and queued confirms attempted save; displayed explicit memory-card access failure, no save succeeded. Dismissed notice and cancelled menu; at249259 actor mode0/control0,eventState0,uiOpen0,pendingMode0,roomMovie.tasks[],root[-3299,-1670,2424],HP66MP19EXP201BP1430. Corrected NEW Fire Escape diagnostic nibble extraction against gameflag.c59: even flag IDs high nibble, odd low. telephoneInspected1,telephoneDialogueCounter1 (earlier0/3 readings were wrong). storyDialogue6 unchanged, no helicopter advancement claim.

Added video_clock_fire_escape_phone base241178,total249259 (actual physical record), generator matches exactly; includes bomb CAP corrections, stairs and failed-save notice dismissal. Independent replay follows using MAIN runner, whose EOF source line matches current snapshot psyq_host.c, so corrected flag fields and fault guard available. Live45626/PID27392 stopped at249259 via SIGINT in waiting FIFO; addr4403466432. Temporary CAP breakpoints2/3 disabled, breakpoint1 numeric next endpoint must be updated. Next leave phone and move west toward landing-pad passage near[-4320,-2384,544]; full port incomplete.

### Landing Pad entry reveals unlinked overlay lights (2026-11-02)

Continued live45626 from249259. Walked west from phone, north to stair action26 near[-4486,-1856,1184]. Next descent/automatic door reaches area16 at actual physical input250634, then EXC_BAD_ACCESS at worldCoordUpdateRoomLightsTask world_coords.c482 writing coneLight transform. Stop reason/backtrace verified; do not claim room playable. Runtime gAkropolisHelicopterLandingPadRoomLights resolves to weak unresolved_stubs.c byte buffer, has corrupt coneLightCount103894056, while generated real lights.inc declares1 directional/22 point/0 cone. None of the three Helicopter Landing Pad room sources is in current default CMake overlay list. Root cause is missing overlay integration, not a reason to clamp light counts or suppress lighting. Captured actual suffix in video_clock_landing_entry.json (base249259,total250634); not yet CLI wired. Live45626/PID27392 is now stopped crash artifact; no further gameplay input. Need link helicopter_landing_pad.c, helicopter_landing_pad_departure.c, helicopter_landing_pad_effects.c with required symbol isolation, build and replay entry. Previous phone replay49339 must be polled before modifying snapshot binary/dSYM; no terminal result yet inspected this turn. Full port incomplete.

Phone finite replay49339 passed7 expectations. Added three Landing Pad room sources to main and isolated CMake default overlay list. First link exposed two departure animation sets missing; definitions reside in actors/helicopter_departure/helicopter_departure.c. Added that real actor source as dependency (no placeholder clip definitions). Rebuild session41629/log landing-build.log; inspect result before replay. Snapshot binary may have been relinked, old live45626 remains crash artifact. Need regenerate dSYM and wire diagnostic landing-entry CLI, append settled samples, then finite verify.

### Landing Pad overlay links with real resources (2026-11-02)

Completed CMake integration of3 room sources plus helicopter_departure actor. Scoped actorMsgPlaceEuler separately for lift and departure, actorMsgPlaceRotMatrix for departure, departure scratch position and its duplicate GolemNo9 body model. Replaced17 generated asm_data initialized definitions with extern declarations because real room/actor now defines them; generator's existing cdefs exclusion supports regeneration. Main asm_data remains ignored/untracked generated file, so regenerate against compiled definitions when rebuilding elsewhere. No clamped light counts/disabled scene. Isolated build+link succeeds, dSYM regenerated. Wired video_clock_landing_entry CLI; generated physical entry plus600 neutral =251234 samples used for finite replay exec26600, landing-integrated-finite.log/result. Check area16, pending0, room controller; no pass claim yet. Old45626 is crash artifact, target executable has changed since its launch. Further encounter actor sources may still need integration; full port incomplete.

### Landing Pad No.9 actor integrated after verified stub abort (2026-11-02)

Finite26600 failed with explicit unresolved call _helicopterLandingPadNo9BodyTask and SIGABRT, after passing earlier corrupt-light initialization point. Added actual helicopter_landing_pad_no_9.c and helicopter_landing_pad_no_9_combat.c; both compile. Scoped conflicting Golem clips/models/message helper consistently across these two source files with CMake definitions (including ChargeRun/Slash/Windup clips shared with actor_102000 variant). Replaced generated asm_data No9 task descriptor definition with extern because real combat source supplies it. Full rebuild/dSYM/replay launched in exec65160, helipad-no9-link.log and landing-no9-finite.log/result. Inspect build result and replay before claiming playable encounter. Same251234-sample input as prior integrated-light attempt. Main generated asm_data ignored; regenerate against cdefs when rebuilding elsewhere. Full port incomplete.

### Landing Pad entry and real No.9 initialization verified (2026-11-02)

Finite65160 completed normally and passes3 expectations: area16, pending0, controller akropolisHelicopterLandingPadRoomTask. Main diagnostic additionally reads real No9 taskState1,HP1600,work.state0/subState0/animationFrame1, root[0,0,0] (not yet encounter positioned). Player root[-6400,129,-6478],yaw2048,actor mode0/surface3,HP66MP19EXP201, no transition tasks. Proves room and actor initialization past prior light crash/stub abort; does NOT prove boss combat/departure. Added video_clock_landing_ready250634+600=251234, same verified input; binary/source/input hashes landing-no9-hashes.json.

New controlled session69150 replays same landing-settled.pad on matching integrated binary/dSYM; FIFO landing-control.fifo already created, log landing-control.log, stderr landing-stderr.log, full record landing-controlled.pad. Poll this handle until actual breakpoint299 at251234, then read fresh checkpoint and resolve current process static padFrame address (old addr4403466432 belongs old crashed process45626 and must not be reused). Main runner includes No9 HP/root/state diagnostics, py_compile passes. No9 boss fight/lift/departure remain next. Full port incomplete.

### Landing Pad traversal and encounter arming topology (2026-11-02)

Controlled69150/PID88501 reached251234 matching finite checkpoint. Resolved current static padFrame addr4403184736 (LLDB addr). Initial turnSouth+confirm at entry caused valid return to Fire Escape; corrected path back through Fire Escape action26. At253111 automatic landing step51 active, then completed near[-6400,129,-6180]. North-strip route: faceNorth near1960, run40 reaches[-6258,129,-6897]; faceEast992 and run185 reaches[141,127,-6581]. Continued east to[3382,128,-6301] at255165. Southward runs stop exactlyz-6301; this is a collision boundary, not movement lock (actor normal, velocity0, control0). Need inspect geometry/screenshot landing-north.png and find connected entry to interior, rather than force through.

Source encounter action0 only arms if EncounterReady!=0; room update sets Ready when logicalview5 seen. Current view4,Ready0,Phase0, boss hp1600/state0/root0. Thus initialized idle actor is expected; encounter not yet triggered. Live69150 stopped255165 source299 numericaddr4403184736; landing-control.fifo/log/record, all physical suffix preserved. No production edit this traversal; full port incomplete.

### No9 intro to active encounter exercised (2026-11-02)

Continued69150 from255165. East100 along north strip reaches[6784,130,-6595], view5 arms encounterReady1. TurnWest45/run160 returns to trigger[1055,-128,-6657]; at255853 phase1/eventState1/view15, native EVS intro active, real No9 animation advancing. After neutral600/Start8/500 at256961 still cinematic; screenshot no9-intro.png confirms real model/room, evsInterpreterTask/capPlaybackTask active. Cross8/neutral400/Start8/1200 at258577 finishes authored scene, restores actor mode0/event0/view4 and active battlePhase1/refs1. No9 hp1600, root[-289,0,-6600], state1/subState8; playerHP23 after waiting exposed to attacks. Ordinary Healing Triangle8/neutral60/Cross8/200 succeeds: at258853 HP81/MP7, No9 state3/subState1, no crash/pending transition. No boss victory yet.

Added video_clock_no9_battle_start base251234,total258853 from full physical record; includes earlier navigation corrections and valid FireEscape roundtrip. Independent finite replay launched to check actual active battle/playerHP/MP/controller. Live69150/PID88501 stopped258853, addr4403184736, landing-control.fifo/log/record. Boss has1600HP, Aya81HP7MP, Tonfa; Recovery2 in backpack, Hydra3 rounds total. Next fight strategy must use ordinary items/attacks. Full port incomplete.

### No9 damage/reaction verified; prepare equipped retry (2026-11-02)

Continued69150 from258853. West run65 and8 Tonfa bursts: at259178 playerHP42, boss1590, hit reactionstate2/subState1. Approach west24 plus10 bursts: at259512 playerHP27, boss1537, reactionstate2/subState3. Confirms target damage/reaction and counterattacks using real collision/animations; no victory claim. Tonfa needs closer range than initial1470 gap. Existing route began66HP and spent long time exposed after intro; Recovery2 is in backpack rather than battle attachment. Preserve this session stopped259512 as evidence, no memory edits.

Started new controlled retry on same binary from verified landing-settled251234 prefix using no9-prep-control.lldb, precreated no9-prep-control.fifo, record no9-prep-controlled.pad, no9-prep-stderr/stdout.log. Next wait for prefix endpoint, resolve new padFrame addr, use ordinary prebattle inventory to heal/attach Recovery2 and optionally equip/load M93R (3Hydra rounds remain). Known short navigation from entry: faceNorth, move north toz-6900, faceEast across northstrip toview5x~6784, faceWest returntriggerx1055. Old return-to-FireEscape detour unnecessary. Need capture optimal prepared retry rather than replay failed gameplay suffix. Previous independent no9-start finite92971 still running; poll exact handle. Full port incomplete.

No9-start independent finite92971 has now completed normally, all7 expectations pass. New prepared retry exec80921 is replaying verified251234 prefix. Poll80921, not retired/crash handles.

### Equipped No9 retry prepared through inventory (2026-11-02)

New controlled80921/PID4882 reached251234 on same integrated build. Current process staticpadFrame addr4403184736 bound to LLDB addr. Ordinary Healing Triangle/Cross raisesHP66->96,MP19->7. Opened Use inventory, accidentally reopened weapon selector, Circleback; Down4/Cross selects empty armor attachment (actual index2/third slot), selector rows GPS/SprayCan/M93R/Recovery2; Down3/Cross attaches Recovery2. At252652 inventoryRows index5/item2/qty1 attachSlot3, menuSelection.armorAttachment2, uiOpen0/pending0, actor mode0,HP96MP7. No target writes.

Added video_clock_no9_prepared base251234,total252652, full record no9-prep-controlled.pad; generator matches physical capture. Finite verification launched separately, check attachment and HP/MP. Live80921 remains stopped252652, no9-prep-control.fifo/log/stderr/record, PID4882, numericaddr4403184736. Old69150 remains stopped259512 as low-health damage-path artifact. Next navigate North from entry toz~-6900, East across northstrip into view5, West to encounter trigger; avoid Cross at southern entry door. Recovery2 battle slot index2 needs two Right presses fromGPSindex0 if selection resets; verify actual selected slot before use. Full port incomplete.

### Prepared No9 retry: active fight and attached healing (2026-11-02)

Continued80921/PID4882 from252652. Short path North16,Left23/East370,Right46/West160 triggers intro253667 without FireEscape detour. Intro/dialogue requires several fresh confirms; at256842 battle active, HP96 unchanged, boss1600 at[-2000,0,-6600]. West85+12Tonfa bursts yields at257297 HP76,boss1538. West15+12 bursts at257682 HP41,boss1474. Damage and counterattacks functioning; not victory.

First Start during recovery ignored; second Start opens battle attachment menu. It retains selected attachment2 from equipment screen; two Right presses wrapped to empty index1 (verified actual gItemMenuSelectedAttachmentIndex1), Cross there does nothing. One further Right selects index2 Recovery2; Cross uses it directly. Screenshot battle-recovery.png at258268 displaysHP115, back to room. Need fresh checkpoint for removed item and final state; physical capture no9-prep-controlled.pad preserved. Live80921 stopped258268 atcontrol299, addr4403184736. Boss1474HP, player now115HP7MP, Recovery2 consumed (verify checkpoint). Full port incomplete.

### Transformer hit/destruction path exercised during No9 fight (2026-11-02)

Fresh checkpoint258268 verifies Recovery2 consumed,HP115/MP7,boss1474. Added read-only transformer diagnostics in main replay runner: state/index/rootPosition/contactViewPosition. workm coordinates include view transform (initially named contactPosition, corrected to contactViewPosition). Actual source roots:0[6458,-2658,535],1[-1336,-2658,6552],2[-6441,-2658,-100].

Continued80921/PID4882 from258268, escaped east along northstrip. At258747 x5551,z-6300 blocked by north railing,HP95. Corrected farther east before south: Right23/run42/Left23/run195 reaches[6898,130,684] at259100,HP95. No9 trails at[5015,0,-6600]. TurnRight20 (east),6Tonfa bursts and100neutral at259410 breaks transformer0: state0->2, HP85 (10damage during test), bossHP1474 unchanged because still distant[6600,0,-4560]. Confirms transformer collision/break/sparks path, not hazard hit on boss. Next lure boss near remaining transformer before breaking; first one spent.

Live80921 stopped259410 source299/addr4403184736, no9-prep FIFO/log/record, HP85MP7,boss1474, Recovery2 gone, Tonfa equipped. Full suffix preserved; no new passing packaged route yet. Other remaining transformer roots above; source hazardApply branch1048+ supports three hazard reactions. No code changes to game for this probe. Full port incomplete.

### Second transformer approach and collision-space diagnosis (2026-11-02)

Continued80921 from259410 around east and south perimeter without new damage:259889 root[-882,129,6635],HP85,boss[6600,0,2452]. Wait300 ->boss[4475,0,6600]; retreatWest40/wait200 ->player[-2178,129,6635],boss3866,stateDASH5. TurnEast46/wait60 then100 waits yields260635 boss[-886,0,6600],dashsub1. FreshTonfa8/aim70 at260713 hits boss for11 (1474->1463), playerHP85->71, transformer1 remains intact0. Thus this was normal direct hit, not environmental blast.

Added read-only contactWorldPosition by inverse orthonormal Q12 gGfxViewCoord.workm rotation/translation. Live values: transformer1 intact tip[-1327,-1644,6011], root[-1336,-2658,6552]; transformer2 tip[-5890,-1645,-88]; spent0tip[6483,-865,535]. High cable tips explain why ordinary near-ground Tonfa hit boss rather than cable; need ranged targeting or scripted boss slash. Important correction: earlier transformer0 destruction temporally observed after Tonfa burst does NOT prove Tonfa caused it; boss slash can break it as well, and was already passing that section. Source TickTransformerBreak requires targeted attack or slash, hazard2 enemy damage180, other source hazards240/520. No claim of environmental damage yet.

Live80921/PID4882 stopped260713, addr4403184736, HP71MP7, boss1463, transformer0spent1/2intact, Tonfa, M93R backpack3Hydra total, no Recovery2. Next inspect battle equipment/weapon switching and available ammunition pickup rather than repeating low-damage Tonfa exchanges. Full physical suffix retained no9-prep-controlled.pad. Main diagnostics py_compile/diff checks pass; full port incomplete.

### Battle weapon access verified; ranged retry prepared (2026-11-02)

Continued80921 from260713. First Start ignored; second Start opens normal attachment-use battle panel by261341, UI paused battle. Read item_use.c508-782: weapon pane is read-only summary, arrows select equipped attachment slots only, confirm applies attached item. M93R backpack cannot be selected here. No evidence of weapon-switch bug; equipment prerequisite was missing. HP71/boss1463 unchanged during menu. Leave old80921 stopped261341 as battle evidence.

Inspected CAP dialogue0 commands6/7/8 with cap_dialogue.commands/describe (no text atlas required). Variants are flags11/12/13, transformer descriptions; no object action or ammo pickup in those commands. Default python lacksPillow, created isolated /tmp/pe2-cap-inspect-venv with Pillow; text atlas PNG absent, so raw command decode used. Do not claim ammunition found.

Started controlled ranged retry from VERIFIED no9-prepared252652 prefix to attach M93R to empty armor slot1 before battle and load remaining3Hydra rounds. New no9-ranged-control.lldb/FIFO precreated, record no9-ranged-controlled.pad, stderr/stdout/log. Existing prep equips Recovery2slot3,HP96MP7. Next wait for252652, resolve process padFrame, ordinary inventory select empty slot1 then M93R, loadHydra; capture. Need ranged aim to test intact cable aboveTonfa reach. Full port incomplete, boss victory unachieved.

### M93R equipped as battle attachment with3Hydra loaded (2026-11-02)

Ranged retry55843/PID57673 completed verified prepared252652 prefix. Resolved padFrame addr4403184736. Ordinary Use menu: Down3 selects empty attachment index1 (second slot), selector GPS/Spray/M93R/Recovery2; Down2/Cross attachesM93R. FreshCross openscontext,Down selectsLoad,Cross opensHydra3 submenu,Cross loads. Start closes. At253774 actor mode0/uiOpen0/pending0, HP96MP7, inventoryRows4 M93R129 attachSlot2;Recovery2row5 attachSlot3. Added weaponLoads diagnostics reads actual McSaveState.weaponItems: weapon129 primaryItem161,primaryQty3; stock aggregate3 includes loaded rounds. No more spareHydra. Unownedweapon149 has stored default100load but is not carried, do NOT treat it as available equipment.

Added video_clock_no9_ranged_ready base252652,total253774, full physical capture. Independent finite replay started, inspect result before claiming pass. Live55843 stopped253774 by SIGINT in waiting FIFO after incorrect hand-total breakpoint; actual record/end authoritative. no9-ranged-control.fifo/log/stderr/record, PID57673,addr4403184736. Next short approach to boss, use battle attachment index1 to equip M93R and ranged target transformer whenNo9near; reserve3rounds forenvironment. Full port incomplete.

### Ranged No9 replay verified and transformer shooting exercised (2026-11-02)

Independent finite session54704 completed normally: video-clock-no9-ranged-ready253774 passes all7 expectations. Continued physical ranged capture55843/PID57673 through battle. Battle attachment selection retained index2, so first confirm consumed Recovery2; then selected index1 M93R, weapon2 equipped and Tonfa moved to attachment2. Do not claim Recovery2 remains available. At260224 HP77MP7, boss1600, M93R3Hydra, all transformers intact. Earlier short8-sample aim/fire attempt consumed no ammunition and is not a confirmed shot.

From260224 sent30aim32768,60aim+R1 34816,30aim32768. Stopped exactly260344 at pad control breakpoint1. Fresh checkpoint: HP77MP7 unchanged, M93R primaryQty3->0, carriedHydra removed, transformer0 state0->1 (sparking), other transformers intact. Boss1600HP unchanged, now[6600,0,-2340],state1/sub8; no environmental boss damage proven. Confirms actual ranged ammunition consumption and cable break path. Full physical no9-ranged-controlled.pad preserved. Current live55843 stopped260344, padFrame address4403184736, same FIFO/log. Boss not defeated; full port incomplete.

Rechecked suggested pe2-ambiguous-globals worktree: clean at5884e6d, parentd616011. Commit renames type-ambiguous room/screen-wave globals across39files (136insertions132deletions); useful for future room integration, not complete overlay namespace isolation. No changes imported during this check. Goal query reports active, historical blocked reason unavailable. No DuckStation MCP tool currently exposed in tool inventory.

### Imported type-derived overlay global names; build verified (2026-11-02)

Applied exact5884e6d patch from user-suggested pe2-ambiguous-globals worktree after clean git apply --check.39files, including32C translation units, remove type-ambiguous room event/cutscene/fade and screen-wave globals. Existing main dirty converter/runtime changes preserved; no commit or cherry-pick. All32modifiedC files pass native cc -fsyntax-only using current headers/generated assets. Detailed results /tmp/pe2-ambiguous-globals-syntax.json. Copied those39files into isolated snapshot, rebuilt game_main and game_overlays successfully (log /tmp/pe2-ambiguous-globals-object-build.log), then executed existing link command with separate output parasite-eve-ii-pc-namespaced: exit0, log /tmp/pe2-ambiguous-globals-link.log. Existing executable/dSYM and stopped gameplay processes untouched. This checks source/build integration, not gameplay of currently unlinked Dryfield/Shelter rooms.

Packaged full physical No9 ranged capture through260344 as video_clock_no9_transformer_shot (base ranged-ready253774,84suffixsegments). Generated output matches all260344captured samples. Independent finite replay session62377 launched using existing validated runtime,9expectations (HP77,weapon2,ammo0,transformer0sparking,boss1600,area16,engaged,closedUI,no pendingmode). Pending result /tmp/pe2-current-debug-20261102/no9-transformer-shot-result.json; do not claim pass before terminal verification.

Read m93rAttackState: PRIMARY R1 explicitly selects3-round burst; SECONDARY R2 selects1round. Physical aim+R2 mask33280. This explains3round expenditure on one cable; use secondary fire in next replay branch to retain ammunition for other cables/blastsource. Current55843 remains stopped260344 after confirmed transformer shot, no boss victory. Goal active; full port incomplete.

### No9 transformer regression passed; persistent memory-card backend in progress (2026-11-02)

Finite62377 terminated normally, video_clock_no9_transformer_shot260344 passes all9expectations. Captured shot/cable path verified; boss1600HP, not victory. Started controlled single-shot retry65032/PID26476 from full captured prefix260224 (/tmp/pe2-current-debug-20261102/no9-single-prefix.pad), FIFO/control.lldb/log/stderr/record use no9-single names. Only breakpoint1 control299, not yet stopped at EOF at last check (record index244939). Actual process is live; do not restart because observation timeout. Once stopped, resolve padFrame addr (likely4403184736 but verify), use numeric condition for advance, try physical aim+R2=33280 rather than R1 burst. Added read-only transformer status/sparkFrames/blastFlags/targeted diagnostics; at old55843@260344 transformer0sparks79,blastFlags32777 (PAIR_ENABLED0x8000),targeted0. Thus blast stillarmed; boss had retreated toz-2340 before shot, not consumed by player.

Investigated prior FireEscape phone failure: src/port/psyq_host.c had all MemCard functions as no-op stubs, Accept always0 and read/write no storage. Implemented src/port/memory_card.c and include/port/memory_card.h. Default root SDL_GetPrefPath parasit(e)-eve-ii application dir; PE2_MEMORY_CARD_DIR overrides for isolated runs. card0/card1 folders store unmodified individual save files, not raw PS1 card images.15x8192byte capacity, synchronous file creation/open/enumeration/format, one asynchronous completion for Accept/Exist/read/write, Sync1complete/-1idle. Atomic sibling temporary file plus fsync/rename per write preserves old bytes on pre-publication errors. Bounds/sector alignment and read/write modes checked, no fake-success IO results. Full20-byte retail filenames supported without NUL; backend normalizes bounded name separately. Hidden temporary files ignored in enumeration.

Main mc.h aliases fixed40-byte PeMemoryCardDirectoryEntry under__psyz; mc.c routes GetDirentry through typed peMemoryCardGetDirentry, avoiding incompatible PsyZ host filesystem DIRENTRY (lacks head). Existing long syncCommand/syncResult/entryCount already host-width, retained. Removed old memorycard stubs from psyq_host.c, CMake links backend and adds memory_card_test. Unit test passes persistence after reinit, byte exact partial writes, untouched neighboring sectors, asynchronous busy/idle/errors, out-of-bounds requests, wrong access modes,20-byte filename/directory ABI, wildcard+offset,15block capacity, card isolation/format and invalid storage errors. ASan+UBSan build also passes (/tmp/pe2-card-asan-test); deployment target warning on sanitizer harness objects only, not runtime.

New source snapshot /tmp/pe2-memory-card-20261102 cloned via APFS cp-cR to keep existing runtime/dSYM/source stable for stopped processes. Copied new backend/mainMC/header/psyq_host/CMake/runner only. Fresh card-out configuration succeeded after replacing relocated FetchContent subbuild cache with explicit FETCHCONTENT_SOURCE_DIR_PSYZ_WEBP pointing cloned out/_deps/psyz_webp-src. Full runtime build70559 in progress, /tmp/pe2-memory-card-full-build.log. Unit-only older snapshot build passes, existing game binary not relinked. Need finish full build, matchingdSYM, controlled phone save/load UI verification before claiming save feature playable. Avoid old full phone249259 replay on new backend: it includes formerlyfailedsave interaction, so may diverge; use prephone prefix (e.g246035 stairs) then interact deliberately. No DuckStation MCP tools exposed; optional async question pending for local fork path.

### Memory-card runtime built; original DuckStation reference recovered (2026-11-02)

Full memory-card runtime build70559 succeeded at /tmp/pe2-memory-card-20261102/card-out/parasite-eve-ii-pc, matchingdSYM generated86328. Unit target in same full build passes. Added fault-injection test with RLIMIT_FSIZE128 and ignoredSIGXFSZ: partial host write fails, Sync reportsCardInvalid, previous file bytes survive, no leftover temporary file/directorycount corruption. Rebuilt test93224 passes. Earlier ASan+UBSan suite before addingfaulttest passed; do not claim newfaultcase rerun under sanitizer yet.

Controlled phone-save session32486/PID84142 using new runtime, isolated PE2_MEMORY_CARD_DIR=/tmp/pe2-memory-card-20261102/test-saves, pre-phone physical prefix246035. Matching script/source at new snapshot: control268, padFrame4403184736. Actual246035 reached old known stairs position[-2870,-1698,3882],mode2/state3,directionactive. Continued exact physical approach through246819 firsttelephoneCAP (pendingMode129), then8Cross140neutral8Cross120neutral to247095, stopped breakpoint1. Latest state needs freshcheckpoint/VRAM; no successfulsaveclaimed yet. FIFO/script/log/record names phone-save-control.fifo/.lldb/.log, phone-save-controlled.pad,stderr/stdout.log. Existing no9 sessions use OLD binary/source/control299, don't mix runners after psyq_host memorycard stubs removal. New snapshottools runner matches newbinaryline.

No9 single-shot retry65032/PID26476: from260224 sent60aim+R2(33280),60aim. At260344 HP77 unchanged, boss1600->1420, state10sparkrecoil, transformer0sparking64frames, blastFlags9 (disabled after contact), gunammo3->1. Thus environmental180damage verified; holdingR2 repeated two single attacks. Use8-sample R2 press fornextshot. EquippedTonfa using8Start180neutral8Cross120neutral to260660 (weapon19,M93Rattachment2 with1round). Southperimeter path36Right30neutral165run60neutral to260951 root[6499,130,6853], then23Left30neutral220run60neutral to261284 root[-1682,129,6899],HP77.46Right30neutral400aim to261760 latestcheckpointHP77,boss1420 at[713,0,6600],state1/sub0, transformer1intact targeted1,player yaw1386. Live65032 stopped261760; same /tmp/pe2-current-debug-20261102/no9-single FIFO/record, padFrameaddr4403184736. No victory. Scriptedboss cable slashes in source occur only slashedTransformer==0 at lapDistance0x4B00/0x7F00 windows0x120; breaking sets-1, so do not assume boss will break both automatically.

User pointed to sshfenrir for DuckStation fork. Fenrir reachable; no source/build located underhome/Projects/src/Library searches, installed /Applications/DuckStation.app is stock build (GDB but noAIport strings). Found original PE1 harness docs in /Users/hasik/.claude-secondary/projects/-Users-hasik-Projects-parasite-pc/memory/duckstation-ai-control.md and duckstation-gdb-harness.md, plus cached DUCKSTATION_SETUP.md in .cache/github-copilot/project-context/parasite-pc.2c2c477f. Docs point to darwine. SSHdarwine works; ACTUAL fork /home/hasik/duckstation at2c527f4f2, dirty3files: SPU optionaltrace/dump additions and regtestAI/GDB. Existing build /home/hasik/duckstation/build/bin/duckstation-regtest. Patch /home/hasik/pe/duckstation-patches/ds-regtest-aiport-gdb.patch SHA2563601802cb68fe5fa00ba4bb1fd8ae3b0496eca7bcc4392ab84de1ea985afcee1. Existing other-task PE1 emulatorPID1906466 ports38797/42183 left untouched.

Copied USER-owned PE2 disc1 CUE/BIN to darwine:/tmp/pe2-reference-20261102/disc withrsync (session12878 completed). Launched OWN original-reference regtest foreground SSH exec22423, flags -frames300000 -ai-port48711 -gdb48692 -start-paused -console -logInfo, booting SLUS-01042.cue. BIOS already onmachine /home/hasik/.local/share/duckstation/bios/SCPH1001.BIN. Process bootsretail PE2 NTSC-U, memorycardnonpersistent. Own SSHtunnel54911 forwardslocalhost48711 and48692 tosameportsdarwine, active. No existing settings/source edits, no writes to otherpeople's processes. New tool tools/port/duckstation_control.py speaks actualAI lineprotocol (greeting, status,release/buttons,advancewithpollingcomplete,screenshotRGBA->PNGstdlib). Optional --record writes PE2PAD input one sampleperEMULATEDFRAME after successfuladvance; nativepadpoll/boot alignment must be established before claiming equivalence. Existingrecordvalidatedbeforeadvance. No emulatorstate/memorywrites or fabricatedoriginalresults.

Verified live API status paused/running1,remaining300000; advanced180neutral ->299820, screenshotframe181 blackboot; further900neutral ->298920, screenshotframe1081 visibleSquareSoftlogo. ActualPNG /tmp/pe2-duckstation-boot.png visuallyinspected320x224. Fullphysicalcommands exported /tmp/pe2-duckstation-input.pad1080samples. Originalreference remains paused atframe1081; CLI cancontinue via default48711, remoteprocess22423 +tunnel54911 mustremainalive. Next establish matched initial gameplaystate before replayingnativeinput/comparingrealPS1 memory+frames. Goalactive, port incomplete.

### Memory-card SDK completion fix, real save/load, and local DuckStation (2026-11-02)

Real phone UI on first backend failed at MemCardOpen: completed presence polling remained flagged busy until Sync, even though the UI legitimately changed states without reading that old result. Replaced boolean pending with CARD_IO_IDLE/RUNNING/COMPLETE. peMemoryCardAdvanceIo is pulsed once per host port0 pad poll (independent of wall time); requests expose one frame pending, completed unread results no longer block synchronous calls/new requests, blocking Sync can finish directly. Unit coverage now exercises the exact Exist->framepulse->directory/open/create/new write sequence. Updated unit+ASan+UBSan suites pass, including20-byte directory names and RLIMIT_FSIZE partial-write preservation. Old failure artifact binary/dSYM/source preserved in /tmp/pe2-memory-card-20261102/first-card-attempt. Updated full runtime build22833 and dSYM67351 succeeded; sourcecontrol269.

Controlled Square save69582/PID67757 used prefix52754 (before phone use), isolated test-saves-ready. Completed phone conversation, chose Save yes, NewBlock and create yes. Actual file test-saves-ready/card0/BASLUS-01042AX9T2sJm8192bytes, transport lastcommand6 result0, visible phone returned. Settled240neutral to55358 verifies uiOpen0,eventState0,pending0,normalcontroller,SquaretelephoneCounter1,callPending0,savedWarp1. The file's two McSaveData0x944copies match byte-for-byte; signed-byte payload checksum65458 and complement verified, savedlocation0601010101010000. Added route video_clock_square_save baseTower48288,total55358,generatedfullcapturematches. First finite86058 interrupted and incomplete; process confirmed gone before retry. Retry77479 completed normally: ALL9expectations pass, square-save-retry-result.json/log. New runner --memory-card-dir persists explicit fixture cards; otherwise uses a fresh temporary empty card directory per finite replay, avoiding user's default save directory and making card state explicit. Existing old no-card routes need revalidation with the new backend; do not claim all earlier long routes pass this build.

Load through a NEW native process: empty trace600neutral ->Start8/60neutral,Down8/20neutral,Cross8/180neutral selectsContinue and validSquare(1) preview (time0:12,EXP0,BP200). Cross8/600neutral gives1492samples, loadingSessionLoadTask7 stillloading (not crash). Original process/PTY ended during interruption; confirmed missing before restarting using preserved1492sample recording. New loadretry96341/PID29172 reached same1492loading state. Advanced1000neutral to2492: actual player restored at[5697,-2070,2181],yaw1024,HP110MP30BP200,M93R20PB+100reserve,Tonfa/Recovery2/GPS/Leather attachments retained,storyDialogue1,telephoneCounter1,callPending0,roomSquarecontroller. uiOpen0,eventState0,pending0,actor.mode0. Loaded warp1/variant2 is normal load setup vs original live warp7/variant1; no forced memory changes. Current loadretry96341 stopped2492, FIFO /tmp/pe2-memory-card-20261102/load-retry-control.fifo, record load-retry-controlled.pad, padFrame4403184736. Independent finite load42121 launched11expectations; inspect square-load-result.json/log before pass claim. No goal completion: full port and No9 victory remain unverified.

User explicitly authorized local fork copy/build. rsync copied entire dirty source+git history from darwine:/home/hasik/duckstation into /Users/hasik/Projects/duckstation-pe2-reference, excluding build directories/cache. Same2c527f4f2 and3dirtyfiles asremote, no source edits needed. Downloaded pinned release-20260526 macOSuniversal deps; SHA2562c0c347a8f62f862f8c578abfc5c35c0c83ca1ea07bfce01b2e1ccec7a03972a matchesrepositorypin. cmake build-local Release/arm64,BUILD_REGTESTON,OPENGL/VULKANOFF built successfully (log /tmp/pe2-duckstation-build.log). Local machine lacks Metal compiler. Reused /Applications/DuckStation.app/Contents/Resources/metal_shaders.metallib fromfenrir versione8938f063 only after gitdiff confirms ALLsrc/util/metal{device,streambuffer,shaders} code identical frome8938f063 to2c527f4f2. File placed in local src/duckstation-regtest for existing postbuildcopy. No global toolchain changes. Runtime uses copied pinned dylibs, Metal API/software PS1 rasterizer, nativeARM64 binary.

Portable local runtime root build-local/bin/portable.txt and bios/SCPH1001.BIN copied privately from user's existing darwineBIOS. Uses existing LOCAL PE2 CUE/BIN in mainrom/image; no remote disc needed. Started localexec86786: build-local/bin/duckstation-regtest -frames300000 -ai-port49711 -gdb49692 -start-paused -console -logInfo -- /Users/hasik/Projects/parasite-eve-ii-port/parasite-eve-ii-pc/rom/image/SLUS-01042.cue (stdout /tmp/pe2-duckstation-local.log). CLI status running1/paused1/remaining300000; advance1080neutral ->remaining298920. Screenshot frame1081,/tmp/pe2-duckstation-local-boot.png320x224 showsSquareSoftintro. PNG SHA2565668a809ec81d2604c45c4335aa30a9c6b134fc82b3e0dcbf8f42d70f6a32005 EXACTLYmatches priorDarwineboot PNG atsameframe/input. Read originalgPlayerStatus0x80073b88 viaLOCALGDB49692 returns128bytes. Switched duckstation_control.py defaultport49711 (class+CLI); explicit--port48711 stillsupportsoldremote. New local inputrecord /tmp/pe2-duckstation-local-input.pad1080samples. No SSHtunnel needed for future comparisons. Local original remains paused1081; remote own original lastknown9409MISTchoice aftertitle/NewGameintro, but remoteprocess may have died onearlierinterruption, don't assume live. Other-user PE1process onDarwine leftuntouched.

Independent native load42121 completed normally: ALL11expectations pass (square-load-result.json). Together with save retry9checks and checksum/copy validation, this verifies normal menu save then fresh-process Continue->Square restoration for this fixture. Local DuckStation status reconfirmed paused/running1,remaining298920.

### Original PS1 loads native save; matched input and corner comparison (2026-11-02)

Built a small SDK client against the LOCAL DuckStation memory-card image library (same regtest flags/libs, frontendobject replaced). It formats a128KiB card and WriteFile imports the unchanged native8192byte BASLUS-01042AX9T2sJm file. Utility uses actual DuckStation APIs, not a guessed card filesystem. Added durable source tools/port/export_card_image.cpp; compiled /tmp/pe2-export-card-image; verifies EnumerateFiles and byte-for-byte ReadFile and refuses existing output paths. Verified export /tmp/pe2-square-reference-verified.mcd,14freeblocks. First working card /tmp/pe2-square-reference.mcd used for original runtime below. No target memory writes or direct function calls to skip gameplay.

Started OWN second local original exec47385 with REGTEST_CARD1=/tmp/pe2-square-reference.mcd, AI49811,GDB49892,frames300000,startpaused, same local disc1. Log /tmp/pe2-duckstation-square-reference.log. Boot replayed actual original captured first4292frames (source /tmp/pe2-duckstation-input.pad); at4293 title NewGame/Continue screen. Down8,neutral20,Cross8,neutral600 reaches realPS1 filelistSquare(1),time0:12,EXP0,BP200. Cross8+2400neutral loads native-created save through unmodified retail Continue. Atoriginalframe7337 sceneSquare active and player live. Original record /tmp/pe2-square-original-input.pad saves allphysicalinput, finaltotal7722samples after comparisons below. Coreclient explicit--port49811; default49711 oldoriginalbootinstance remains paused1081.

Read ORIGINAL gPlayerStatus0x80073b88(128bytes), gGameSession pointer0x8005ed64 then locationat+4, and borrowed root matrix from PlayerStatus+4, translations+20. Read-only GDB /tmp/pe2-dsgdb.py on49892. Compared with paused native96341/PID29172 at2492: ALLsix locationfields equal(stage1/area1/state1/view6/warp1/variant2),HP110/max110,MP30/max30,BP200,EXP0,weapon2,armor1; exactroot[5697,-2070,2181],forward[4096,0]. This verifies actual cross-game compatibility for this save, not every state or region.

Paired physical input in both:10Right32+30neutral. Nativeend2532 yaw1464, originalmatrix-derivedyaw1464,positionsunchanged. Rootforwardcoefficients slightlydiffer: native[3198,-2559] vsoriginal[3204,-2564]; do not claim allGTE/math bit-exact. Then30Down64+30neutral, Nativeend2592,Originalframe7437: BOTHroot[5481,-2071,2361] exactly. Thus direct one-emulated-frame-per-native-pad-sample comparison works for this short controlled sequence. No timing scale guessed or applied.

Paired Start8+180neutral+Cross8+90neutral opens identical equipment/item menu; nativeend2878, originalframe7723. NativeVRAM /tmp/pe2-square-native-item-menu.vram,OriginalAI vramdump /tmp/pe2-square-original-item-menu.vram, PNGs sameprefix. Nativeviewport y280 (buffer272+8crop),original y8 (or y280, bothbufferssame) gives same320x224 visible coordinates. RawRGB555 compare excludes maskbit. Wholeimage71081/71680pixels equal; remaining differences NOT claimed fixed or diagnosed. Frame corner positions derive from menu_root.c descriptors plus _uiDrawPanelFrame inclusivewidth/height+1. Fourpanels(weapon destination,armordestination,inventory,caption),16corners*8x8=1024pixels:1023equal. Sole differingpixel[22,164] lies on transparenttexel, not framepaint. Confirmed source atlasTPage0x1E(4bpp,x896,y256),CLUT0x3C03(x48,y240),UVbottomleft0x28/0x50; eachcorner28opaque texels. ALL448/448 OPAQUEcornerpixels match original, allsource texelpalettevalues also match. This directly verifies the menu-corner repair against PS1 on a shared save/input; do not claim entireframe/entiregame pixel equality. Earlier exploratory ROI without inclusive+1 was corrected before final comparison.

Archived proof in main build-port/reference/square-shared-save: bothPNGs,rawVRAM,decodedinitialstates,post-move states,sourceoriginalinput,cornersJSON andchecksJSON. checksJSON9conditionsalltrue:location/stats/BP/EXP/equipment/position/forward/backward30position/opaquecorners. Native input full record remains /tmp/pe2-memory-card-20261102/load-retry-controlled.pad(now2878samples), FIFOload-retry-control.fifo, LLDB96341 stopped2878,addr4403184736. Original49811 paused with292278remaining; normalUI open inboth. Native initial2492loadstate and disk save are reusable for next port progression (No9/completion not achieved). Baseline originalGPU49711 untouched. All agents/tool sessions must be revalidated after interruption, never assume themlive fromthislog.

### Weapon teardown crash fixed; MIST R18 linked (2026-11-02)

Normal Square inventory input changing M93R to Tonfa crashed on close at sample3590. taskKill read nextSibling after a reflection child exit immediately freed its task. Save successor before dispatch. New tests/task_teardown_test.c exercises immediate, sibling ring, nested and deferred teardown. Old code ASan fails heap-use-after-free (/tmp/pe2-task-teardown-before.log); fixed ASan+UBSan and CMake target pass.

Isolated /tmp/pe2-mist-r18-20261102/r18-out full runtime builds successfully with real mist_r18.c overlay; replaced nine generated duplicate data definitions by extern declarations in main and snapshot asm_data.c. Runtime story entry to MIST briefing remains untested; No9 still not defeated.

Captured failing3590 inputs plus600 neutral replay to4190 now exits0. Five assertions pass: playerStatus.weapon19, uiOpen0, carried.160=100, eventState0, flow.pendingMode0. HP110/MP30 and normal Square controller retained. Evidence /tmp/pe2-tonfa-close-verified.log and JSON, input snapshot tonfa-close.pad with isolated tonfa-close-cards. First replay completed too but used incorrect top-level weapon assertion; corrected assertion rerun passes. git diff --check passes. Next ordinary progression Square->Patio preserving ammunition for No9.

### Fresh Square save -> Patio with ammunition retained (2026-11-02)

Full physical replay23444 on /tmp/pe2-mist-r18-20261102/r18-out/parasite-eve-ii-pc loads the real Square card fixture, equips Tonfa, closes inventory with corrected task teardown, crosses Square, completes stair hints and climbs to Patio. EOF clean exit0: stage1/area3/state1/variant1/view2/warp4, normal akropolisPatioRoomTask, position[3907,129,506], yaw2304, HP110/MP30, weapon19, PB item160 total100, ui0/event0/pending0. Ten explicit postconditions checked against decoded checkpoint. Evidence/input/checkpoint/expectations archived build-port/reference/square-save-to-patio. Replay requires initial card from /tmp/pe2-memory-card-20261102/test-saves-ready (or matching snapshot tonfa-close-cards), not an empty card.

Historical Patio suffix from west Square boundary initially failed to reach stairs because loaded position differed; no gameplay constants changed. Read actual authored triggers in build/include/assets/rooms/akropolis/square/action_triggers.inc. Needed move east off western boundary, dismiss CAP hint, approach north stairs; subsequent movement was consumed during stair animation until settled. Latest full route includes exploratory harmless movement/waits. Next continue Patio->Cafeteria story with Tonfa and preserve100PB for No9. No No9 victory or MIST entry claimed.

### Tonfa/Pyrokinesis Patio victory -> key -> Cafeteria (2026-11-02)

Continued fresh Square-save branch on R18 snapshot. Patio opening matched historical position/yaw exactly; Tonfa primary/secondary attack cycles lowered160HP Stranger to78 at25908 while Aya HP62. Two normal PE-wheel casts then defeat it (-69HP), Aya46HP/18MP; no gun rounds used. Cleared result prompts, approached SWAT follow-up, normal Start skip. At30208 matches historical cleared Patio root[-6612,130,315],yaw3296, roomState2,cutscene4, battleRefs0, EXP42/BP248, pending0. CarriedPB100 retained. This route takes damage; no claim of optimal combat.

Appended historical Parthenon Key suffix:36710 exits normally, both key=true and PB100 assertions pass. Appended Cafeteria-entry suffix:43266 exits0, all4 expectations pass (area4,PB100,ui0,pending0). Actual entry root[-4047,-171,2704],yaw2048,normal controller/state, HP46/MP18, Tonfa19; boss350HP not yet triggered. Evidence full physical input/replay/checkpoints/keylog archived build-port/reference/tonfa-cafeteria. Cards same isolated fixture as prior entry; initial save must exist. Extended read-only replay_checkpoint roomEnemies rootPosition diagnostics to actor01900Task (tested in Patio capture). No gameplay parameters changed. Next heal/prepare and fight Cafeteria without exhausting No9 ammunition; full port/No9 still incomplete.

### Healing item menu lifetime crash fixed (2026-11-02)

Cafeteria preparation using last Recovery2 through normal menu reproduced crash at43922. Correct sequence from43266: Start8/neutral120/Cross8/neutral120, four Down8+neutral20 (attachment index2), Cross8/120neutral, Down8/20neutral selects Use (first row is Exchange), Cross8/120neutral/Cross8/180neutral/Start8/300neutral, total44414. Earlier exploratory menu attempts selected Exchange and detached items; discarded those branches and restarted unchanged43266 input. No inventory writes.

itemMenuApplySelectedHealingItem dereferenced shared gItemMenuSelectedRow every update; consuming last row heals to110 but inventory refresh clears the shared pointer, causing next update NULL dereference. The use task already retains original itemId in spawnArg1 from _itemMenuOpenUsePanel. Callback now passes that stable id to itemMenuApplyHealingPanel, which applies effect once under state0 and then animates display. Main+snapshot source fixed, original source and binary saved under snapshot menu_actions-before-healing-fix.c/runtime-before-healing-fix. Full build passes. Same44414 input now exits0 with all5 assertions passing:HP110,UI0,PB100,Recovery2 absent,pending0. Logs/input/checkpoint archived build-port/reference/healing-item-lifetime. py_compile runner and git diff --check pass.

Continued Cafeteria intro skips to46700:boss350,HP95MP18,Tonfa,normal battle. Exploratory24Tonfa cycles branch49176 reduces boss141 but Aya11HP; PB100 intact, MP18 unchanged (attempted PE input did not cast). Do not reuse this branch blindly or claim victory. Safe reusable healed prefix44414 remains cafeteria-recovery-use.pad. Need proper PE target/cast input or M93R before next fight attempt. Full port remains incomplete.

### Fresh branch Cafeteria victory, verified PE input (2026-11-02)

Safe healed44414 prefix (cafeteria-recovery-use.pad) followed by normal M93R equip ends45310:weapon2,item129 primaryPB20,HP110MP18. Appended historical video_clock_cafeteria_clear suffix;52112 clean EOF/exit0 verifies9 explicit postconditions:Patio area3,state3,variant2,view7,warp3, root[-7014,-173,-4296],yaw0; bossReport1,route2,EXP342,HP77MP30,PB67,UI0,pending0. M93R consumed33 rounds on this branch (not historical28); Recovery2 reward available again. Evidence/input/expectations in build-port/reference/fresh-cafeteria-victory.

PE investigation separate discarded branch: first Triangle after intro was ignored, second Triangle opens actual mode1 wheel. From46836,physicalCross8+360neutral casts Pyrokinesis:boss350->202,MP18->10,HP80. PhysicalCircle cancels (MP unchanged). Next spell needed retry after damage;boss202->129,MP2,HP65. Tonfa finish attempt49116 dies HP-7,boss53; discard. Extended read-only parasiteEnergy diagnostics with flags,queuedIndex,menuOpen,soundStep,duration; py_compile passes. No spell implementation changed.

Blindly appended historical Patio ambush+MIST-report route to victory branch:63199 remainsPatio,ambushSeen1,EXP426,HP13MP30,PB18,storyDialogue4,not a successful report. It wastes49 rounds and should be discarded. Initial isolated card still unchanged (mtime19:03). Authoritative safe branch remains52112 victory (67PB), not63199. Next handle Patio ambush with verified Pyrokinesis/escape and deliberately approach Square phone; preserve ammunition. git diff --check passes. No No9/MIST R18 runtime completion claimed.

### Fresh Patio ambush cleared conserving ammunition (2026-11-02)

Continued safe Cafeteria-victory52112 prefix.155runUp,120neutral,Start8,120neutral,Triangle8,60neutral ->52583:two160HP enemies,battleRefs2,Aya77HP30MP,PEwheel not open. RetryTriangle8/60neutral/Cross8/160neutral casts first Pyro:enemies160/85,Aya61MP22.60neutral/Triangle8/30neutral/Cross8/120neutral secondcast ->90/9,Aya45MP14.Third samecast then two shortR1 bursts ->14/-1,Aya45MP6,PB61.Thirdburst initially misses,12HP damage; freshSquare and two furtherbursts finish ->-7/-1,battleRefs0,PB52,Aya33HP. ThreePyro24MP and15actualPB rounds total (vs49wasted in failed historicalsuffix). No combat constants changed.

After600samples result/loot confirms,54431 clean EOF/exit0:normalPatio,ambushSeen1,EXP426BP544,HP33MP14 (8MP reward),PB52,Recovery2item2=1 loose,lootitem59=1,ui0/event0/pending0,battleRefs0,bothenemyHPnegative.12explicit postconditions plus all-enemies-dead assertion verified against decoded runtime checkpoint. Archive build-port/reference/fresh-patio-ambush includes input/log/checkpoint/expectations. Playerroot[-2300,128,700],yaw3001. Next heal with looseRecovery2, walk east to stair trigger[3903,-96,895], returnSquare and report by actualphone. Do not append historical mist-report blindly: its startpose differs. Current safe input patio-ambush-results.pad; cards unchanged initialSquare fixture. Full port andNo9 remain incomplete. git diff --check passes.

### Loose Recovery2 and Square Baldwin report verified (2026-11-02)

From54431 fresh ambush-clear prefix, loose Recovery2 is inventory filtered row1 (Tonfa row0); command selection retained1 from equipment, so explicitly Up toUse0. Start8/120neutral/Cross8/120neutral/Right8/20neutral/Down8/20neutral/Cross8/120neutral/Up8/20neutral/Cross8/120neutral/Cross8/180neutral/Start8/300neutral ->55523. All4 expectations pass:HP110,Recovery2 absent,PB52,UI0. Confirms stable healing-id fix works for loose inventory too. Failed harmless menu attempts selecting wrong row/Move discarded.

TurnLeft45/runUp170 ->55798 near east Patio stairs[3732,129,793],yaw977. Left16,runCross8/run52,1800neutral,runCross8/run52,1200neutral ->58934 Square warp5 upper landing[-3426,-1470,-2580],yaw256. Left6,runCross8/run52,1800neutral ->60800 lower landing[-3426,-2072,-1382],yaw0. Southrun100/Right23/Eastrun250/neutral60/Cross8/neutral300 triggered CAP hint at[3916,-2199,2000]; dismiss12confirm cycles,run60/neutral60/Cross8/neutral600 ->62989 phone report sets bossReport4,route3,objective5. Initial16confirm cycles insufficient to finish captions; another40confirm cycles and30backwardsconfirm cycles close dialogue/save presentation and leave trigger normally.

Full69373 input square-report-settled.pad clean EOF/exit0, ALL9 expectations pass:bossReport4,route3,objective5,HP110,PB52,actor.mode0,ui0,event0,pending0. MP14,EXP426/BP544 retained. Archive build-port/reference/fresh-square-report includes complete input/log/checkpoint plus looseRecovery log. Uses isolated phone-report-cards; originalSquare fixture retained. No successfulnewsave claimed. Next proceed back viaPatio/Cafeteria northHallway towardFountain/Security, preserveammo andcollectlater50rounds. Full port andNo9/MISTbriefing runtime remain incomplete.

### Fresh post-report branch reaches Fountain (2026-11-02)

Historical fullFountain suffix from newSquare report pose diverged, ended78316 stillSquare; discarded. From safe69373 instead Right48/run80/Left24/three(runCross8/run52)/neutral1800 ->71505 Squareupperlanding[-4036,-1471,-2731],yaw2048. Right6/two(runCross8/run52)/neutral1800/runCross8/run52/neutral1200 ->74691 Patioarea3/state3/variant3,root[2541,129,-1250],yaw2432. Right14/run280/Left24/three(runCross8/run52)/neutral600 ->75789 westernCafeteriaapproach[-7929,-173,-3828],yaw2784. Left26/walk50/Right10/Cross8/neutral600 ->76483 pending129/reload1,normalescape result (HP88MP15 vs110/14 onreport).10confirmcycles+neutral120 ->77203 Cafeteriaarea4/state4/variant3,root[-4047,-171,2704],yaw2048,actor401800180HP; normalcontrol.

Historical Fountain blocks23..31 now from matchingCafeentry ->78883 actualHallwayarea7/warp4,root[-2951,-872,-623],yaw1024,HP88MP15.180run/Cross8/neutral300/10confirmcycles/neutral120 ->80091 at[694,-871,-623],HP79,status4 (rat encounter andone-timeCAP interrupted movement). Then80run/Cross8/neutral300/12confirmcycles/neutral120 closesescape result and arrivesFountain81319 cleanEOF/exit0. Actualstage1/area8/state1/variant1/view3/warp3,root[-4765,129,-4755],yaw1024,normalFountaincontroller,HP79MP16,status0,PB52,UI0/event0/pending0,flowFlags0,battleResetPending0.12explicit postconditions independently checked against decoded checkpoint. Fullphysicalinput/log/checkpoint/expectations archived build-port/reference/fresh-fountain-arrival. Initialcard unchanged. No gameplay constants changed to reach it.

Next Fountain route/path/protein and Security/Rupert/BlueKey, continue toward No9 with ammunition preserved. Fullport,No9victory,MIST_R18runtime still incomplete. git diff --check passes.

### Fresh Fountain Protein -> Security -> Rupert scene verified (2026-11-02)

From81319 freshFountain arrival, appended Fountainpath+protein historical suffixes ->90793:upperpathview8/root[3790,-70,-7949],yaw43,surface5,hiddenPathFound1,climbEnabled/Linkedtrue,item60ProteinCapsule1,Tonfa19,HP79MP16,PB52,normalcontrol. HistoricalHallwayclear blocks0..18 performdescent butend92332 stillFountain[-3000,129,-4020],yaw3083. Left23/walk55/Right23/run70/Cross8/240neutral ->92751[-5079,129,-4299],stillshortofdoor. Left23/walk40/Right23/Cross8/300neutral ->93145 actualHallwayarea7/warp1,root[2950,-871,-698],yaw3072,HP79MP16.

DirectSecurity route:walkWest35/Right23/walkSouth80/Cross8/240neutral,10confirmcycles+120neutral ->94251 Securityarea6/state1/variant1/view2/warp1,root[-46,-871,-2758],yaw0,normalcontroller/control,HP79MP16/Tonfa/PB52 unchanged. Hallway rats were escaped, NOT defeated; earlier historicalcleared-rat BlueKey path cannot be assumed safe unchanged.

Appended actual monitor/Rupert input suffix ->101005 clean EOF/exit0. Runtime:monitorScenesSeen2,rupertSceneFinished1,monitorBrightness4,monitorpanelgone,only_securityMonitorsSwatTask remains,actor mode/state0,ui0/event0/pending0,root[-379,-871,1559],yaw0,HP79MP16,PB52,Protein1.14explicitpostconditions and panelgone checked against decodedcheckpoint. Fullinput/log/checkpoint/expectations/protein/security states archived build-port/reference/fresh-rupert-monitor. No gameplayparameters altered. BlueKey stillnotcollected; next directHallway keybox approach while ratsremainalive, or properlyclearencounter before long exploration. Fullport andNo9/MIST_R18runtime remainincomplete. git diff --check passes.

### Fresh Blue Key pickup and left power lock verified (2026-11-02)

From101005 Rupert monitor end[-379,-871,1559]/yaw0:Right46/run120/Cross8/240neutral ->101419 stillSecurity[-238,-871,-2295].run25/Cross8/240neutral ->101692 Hallwayarea7/warp2,[2271,-871,950],yaw2048,HP79MP16. Directkeybox:run55/Right23/run40/Left23/Cross8/240neutral/12confirmcycles/120neutral ->102921 BlueKeytrue,collection260,HP79/PB52 preserved,root[894,-999,-950],yaw1960,pending129. Fourbackwardsconfirmcycles+120neutral closecaptionandretreat ->103281[660,-871,594],HP72/status4,UI0/event0/pending0. Ratsremainalive; no ratclearedclaim.

Left21/run46/Left23/walk12/Cross8/240neutral/10confirmcycles/120neutral ->104351 Hallway[2283,-871,562],yaw24,HP51/status4,justoutsideSecuritydoortrigger; extra walk20/Cross8/240neutral/10confirmcycles/120neutral ->105339 actualSecurityentry[-46,-872,-2877],yaw0,HP51MP17,status0,BlueKeytrue,normalcontrol. No ammo used; PB52.

Directpowerpanel:runSouth90/Right23/Cross8/300neutral/6confirmcycles ->106120 Securityview6,powerSupplyTask2,cursor0,0,root[-46,-999,120],yaw968. Appended verified BlueUnlock blocks22..end, plus600neutral settling ->108360 cleanEOF/exit0,ALL9expectations pass:BlueKeyfalse,panelKeys1,sanctuaryRouteProgress2,rupertSceneFinished1,actor.mode0,UI0,event0,pending0,PB52. Main proof archived build-port/reference/fresh-blue-unlock,input/log/checkpoint/keycheckpoint. py_compile runner andgit diff --check pass. No gameplayparameter/stateinjection. Next Sanctuary route viaForkedRoad/Observatory/Promenade, laterRedKey/rightpanel/No9. Fullport andNo9/MIST_R18runtime incomplete.

### Fresh Protein Capsule use, Forked Road and Observatory arrival (2026-11-02)

From108360 leftBlueUnlock end Securityroot[-46,-871,120],yaw968:Right23/run100/Cross8/240neutral ->108731 Hallwaywarp2,[2271,-999,950],yaw2048,pending129 caption.6confirmcycles/runNorth50/Left23/runEast20/Cross8/240neutral/10confirmcycles/120neutral ->110152 Fountainarea8/warp3,root[-4781,129,-4766],yaw1024,HP44MP18,PB52,status0,normalcontrol. Hallway rats escaped, still not defeated.

Read actual Protein effect item_boost.c:hpBonus+5,recalculatemax,refillHP. NormalinventoryUse:Start8/120neutral/Cross8/120neutral/Right8/20neutral/Down8/20neutral/Cross8/120neutral/Cross8/240neutral/Cross8/180neutral/Start8/300neutral ->111336. Protein was filteredinventoryrow1 (M93Rrow0),commandUse0. ALL6assertions pass:HP115,max115,Protein60 absent,PB52,UI0,pending0. No injections or consumableparameterchanges. This tests actual boost-item panel lifecycle aswell as healing.

Appended Fountain-only portion of historicalForked route steps9..end ->112652 actualForkedRoadarea9/state2/variant2/view4/warp3,root[-5107,129,-3780],yaw0,HP115MP18,Tonfa19,PB52,panelKeys1,sanctuaryRoute2,normalcontrol. Appended verified Observatory ride suffix ->115205 cleanEOF/exit0,ALL7CLIexpectations pass:area10,normalactormode,UI0,event0,pending0,PB52,HP115. Additional decodedchecks:arrivalSceneStarted1,no movie tasks,maxHP115. Fullinput/log/checkpoint plus Protein-use/Forkedproof archived build-port/reference/fresh-observatory-arrival. Next efficientObservatory northstair approach ->Promenade/Sanctuary, avoid historicalexploratorymovementthatlost72HP. Fullport andNo9/MIST_R18runtime remainincomplete. py_compile runner andgit diff --check pass.

### Efficient Observatory escape, Promenade and Sanctuary arrival (2026-11-02)

From115205 Observatoryarrival, first immediateRight23 plus300run-confirm approach ended115588 at[-803,-2861,-2979],yaw1184,HP99; discarded. Retried fromsafe115205 with60neutral/Right23/run260/20neutral ->115568 at[-819,-2860,-6999],yaw1624,HP115. Right9/run150/Right23/run45/Cross8/240neutral/10confirmcycles/1500neutral ->118143 actualPromenadearea11/state1/variant1/view2/warp4,root[726,170,9050],yaw3072,HP115MP20,PB52,arrivalMovieStarted1,movietasks[],normalcontrol. Earlier historicalexplorationslost72HP; newroute retainsall115. Partialinitialturn is observed, exactcause not proven; no movement/inputparameterchanges.

Started controlled native continuation exec97400/LLDBPID6126/target6296 from118143 recording. Newfiles /tmp/pe2-mist-r18-20261102/sanctuary-control.lldb/.fifo, sanctuary-controlled.pad, sanctuary-control-{stderr,stdout}.log. Initialbp1 psyq_host.c269, staticpadFrameaddr4403217472. Actual118286 after120neutral/Left23:heading2104. Left2/run435 ->118723 root[275,172,-4576],heading2016,HP115. Left23/neutral10/runCross30/240neutral ->119026 pending129/reload1,normal escape result. Cross8/1620neutral/Start8/600neutral/20confirmcycles/Start8/600neutral ->123070 actualSanctuaryarea12/state1/variant1/view3/warp3,root[-5724,130,-8276],yaw3072,HP115MP21,PB52,normalmode/state0,UI0/event0/pending0. sceneEvent6,rupertLeft0,redKeyfalse,No9/Rupertactorspresent; firstscene completed, Roofdeparture notyettriggered. Protein alreadyused earlier, omitted historicalroute's duplicateinventorysequence.

Copied exact123070-sample physicalrecord to fresh-sanctuary-arrival.pad (verified123071lines,finalindex123069). Independent freshprocessfinite replay passesALL10expectations:area12,normalmode/state,HP115,MP21,PB52,UI0,event0,pending0,panelKeys1,cleanexit0. Evidence input/log/live+finitecheckpoint/Promenadecheckpoint archived build-port/reference/fresh-sanctuary-arrival. Livecontrolled6296 remainsstoppedbp1 at123070, conditionend123070; revalidatebeforecontinuing. Never restart merelyfor observationtimeout. Next navigateSanctuarywestaisle toRoofGarden departure, letRupertleave, returnforRedKey. Fullport/No9boss/MIST_R18runtime remainincomplete. git diff --check passes.
Live/finite checkpoint differing groups: []. No broader determinism or console parity claim.

### Fresh Rupert departure, Red Key, Roof Garden victory and bomb (2026-11-02)

Revalidated live97400/target6296 stopped123070 Sanctuary. HistoricalRoofGarden suffix3027 ->126097 actualRoofGardenarea13/warp2,root[-7508,130,-8572],yaw407,HP115MP21,pending0,rupertLeft1,bombSceneState1,RedKeyfalse. HistoricalRedKey suffix2199 ->128296 Sanctuaryvariant3/warp2,root[-7060,130,-8080],yaw992,RedKeytrue,Rupert/No9tasksabsent,HP115MP21,normalcontrol. Saved fresh-red-key.pad exact128296 samples; independentfinite replay passesALL9expectations,checkpointidenticaltoliveincludingtiming.

HistoricalRoofClear suffix4729 ->133025 area13/warp1,root[-6032,129,-7998],yaw2638,HP89MP17,EXP450,PB52,MPBoost1item6=1,RedKeytrue,battleRefs0,roomEnemies[],enemyDropState2,UI0/event0/pending0. FourCaterpillarsdefeated withTonfa/onePyrokinesis; noammo used. Battleendresetlatch1 retained.

Bomb approach needed navigation around real collision geometry. DirectSouth/West attempts ended133434 trappedcorner[-6571,130,-7170],yaw4046. Generated diagnostic top-downmap from actual92verts/53faces using purePythonPPM+sips (Pillowunavailable), no gamegeometryedits. Map showed eastopening and west route aroundpedestal. Right24/run50/Left23/run45/Left23/run25/Right23/run70 ->133717[-5658,130,-3849]. walkSouth12/Right24/walk40/Right23/Cross8/240neutral ->134064[-5552,130,-3620],stilloutsidebombtrigger; Left21/walk25/Right23/Cross8/200neutral ->134341 actualbombaction,objective7/storyDialogue6. Eightbackwardsconfirmcycles+120neutral ->134941 root[-4861,130,-2299],yaw2062,normalmode/state0,event0/UI0/pending0. HP89MP17/EXP450/PB52/MPBoost1 andRedKey retained.

Copied fresh-bomb.pad exact134941samples(finalindex134940), independentfreshprocessfinite replay passesALL13expectations:area13,RedKey,objective7,dialogue6,HP89,MP17,PB52,item6=1,battleRefs0,normalmode,closedUI/event/pending;cleanexit0. Complete checkpointidenticaltolive. Archive build-port/reference/fresh-roof-bomb includes completeinput,bothfinite/liveproofs,collisionmapPNG+generator. No productioncodechangedthisstage. git diff --check passes.

Live97400/PID6296 remainsstoppedbp1/psyq_host269 at134941,padFrameaddr4403217472,condition134941,usual sanctuary-control FIFO/record underR18snapshot. Revalidatebeforeusing. Next returnwithRedKey viaSanctuary/Promenade/Observatory; reserveMPBoost1 torestoreMP beforeMossbackbattle. CurrentEXP450; twoMossbackkills+304 wouldyield754,enoughfor750 Healingrevival (ifnormalgatesallow), usefulbeforeNo9. Rightpowerlock,bridge,FireEscapephone save,No9boss andMIST_R18runtime remainincomplete.

### Fresh return Mossbacks, Hydra loot and Healing revival verified (2026-11-02)

Revalidated live97400/PID6296 stopped134941 RoofGardenbombend[-4861,130,-2299],yaw2062,HP89MP17. UsedlooseMPBoost1 via normalStart/Use/inventoryrow1:1184samples ->136125 MP30,boostitem6absent,HP89/PB52 unchanged,menuclosed. Actual stable healing-item callback handles MPBoost1 aswell.

HistoricalObservatoryreturn suffix(first30run increasedto42 tocompensate360Xoffset),4803samples ->140928 onlySanctuary[-8755,127,-4299],yaw856,RedKeyretained,noinjury; notObservatoryyet. ManuallyRight50/run32/Left23/run110/Right23/Cross8/500neutral ->141674 Promenadearea11/state2/variant2/warp2,[373,168,-4230],yaw3072,HP89MP30. Right23/run410/20neutral ->142127[-144,170,9668],yaw4040. Right24/walk25/Cross8/300neutral/10confirmcycles/1000neutral ->144084 actualObservatoryarea10/state1/variant2/view4/warp1,root[-2296,-2861,-11022],yaw1024,HP89MP30,PB52. TwoMossbacks280HP confirmed at[-1600,-2990,-4500]/[-4500,-2990,-8000].

HistoricalMossback-clear suffix2780 ->146864 bothenemiesgone,battleRefs0,EXP754(+304),HP69 (20lostonthisbranch, NOT historicalno-damagereplay),MP16,PB52,Hydraitem16150,RedKeyretained,UI/event/pending0. Loot and result confirmed.

Normalmenu Start->PE->Water->Healing->Revive->Yes, first934samplesofprepared-return suffix ->147798 Healingindex7level1,EXP754->4,maxMP30->31,currentMP16->31,HP69. CloseStart8/300neutral/Triangle8/120neutral/Cross8/300neutral ->148542 actualHealingcast HP69->99,MP31->19,activeIndex7,mode0,UI/event/pending0,normalactor. Root[-1700,-2860,-5390],yaw2649. No gun rounds used throughoutMossbackfight.

Copied exact148542-sample record fresh-healing-ready.pad. Independentfreshprocessfinite replay passesALL14expectations:Observatory,HP99,MP19,maxMP31,EXP4,Healing7level1,ParthenonKey,PB52,Hydra50,battleRefs0,normalmode,closedUI/event/pending,cleanexit0. Extra decodedchecks roomEnemies[] andRedKeycollection259. Archive build-port/reference/fresh-healing-ready includescompleteinput/log/live+finitecheckpoint. git diff --check passes.

Live97400/PID6296 stoppedbp1 psyq_host269 at148542,pad_addr4403217472,condition148542,sanctuary-control FIFO/record underR18snapshot;revalidatebeforecontinuing. NextM93R/attachment+Hydrapreparation ifneeded,emptyObservatorycrossing andForkedRoadreturn encounter,thenSecurityrightlock withRedKey. Fullport/No9boss/MIST_R18runtime remainincomplete.
Live/finite differing checkpoint groups: []. No broader determinism claim.

### Fresh M93R/Hydra preparation and efficient Forked Road victory (2026-11-02)

Revalidatedlive97400/PID6296 at148542 Observatorycleared/Healingready,HP99MP19. Remaining2998samplesoftheoldprepared-return menu suffix ended151540stillTonfa,resourcesunchanged; retainedexploratorycapturebutdoesnotproveweaponchange. DirectnormalStart/Use/weaponpickerDown1 sequence896samples ->152436 M93Rweapon2,PB20loaded. UseprimaryloadrowDown1,ammopickerDown1/Cross sequence924 ->153360 M93RprimaryHydra161qty20,carriedHydra50,PB52,UI0/pending0. No ammunition consumedbypreparation.

First644samplesofhistoricalFountainreturn ->154004 ForkedRoadarea9/state2/variant3/view3/warp5,root[-449,129,1205],yaw3072,Stranger180+3rats18,HP99MP19. Eightaim/R1cycles ->154244 boss30,Hydra41,HP93/status4. Twomorecyclesdidnotfirewhile recovering. Holdingaim/R1for60+30aim ->154394 boss-7,Hydra35,HP92 (15roundsused). RetargetbySquare+Circle8/neutral12/Square24,thenR2singles. Firsthitrat18->6,Hydra34. Nextsingleandretargettwosingles ->154730 two ratsgone,battleRefs1,Hydra31. LastsingleleftlastRat7,Hydra30/clip0,HP83. AttemptedreloadwithCross/SquareandR2didnotrefill; no productionbugestablished. Backaim60,R2press8,120aimstillclip0; freshR1press8/120aim ->155458 actualreloadprimary20,stock30unchanged,HP82.

LastR2single+120neutraland6confirmcycles ->156234 victory/result/lootclosed:StrangercorpseHP-7remainsintaskcensus,butbattleRefs0,rat tasksgone,EXP58(+54),HP81MP26,status0,M93R,PB52/Hydra29,item8loot1,UI0/event0/pending0. TotalHydra21rounds,versus47intheoldroute. Resourcesavoidedbyretargeting/singles; don'tclaimlowestpossibleroundcount. Oneincorrect412-samplebatchsumassertblockedallFIFOwritesbeforeexecution; correctedbreakconditionwhiletargetwaitedandcontinuedwithoutrestart.

Exact156234inputfresh-forked-clear.pad independentlyreplayedinfreshprocess:ALL14expectationspass,cleanexit0; RedKey259 independentlyconfirmedpresent. Fullinput/log/live+finitecheckpoint archived build-port/reference/fresh-forked-clear. Live/finite differinggroups: []. git diff --check passes. No gameplaycodechangedonthisstage.

Live97400/PID6296 remainsstoppedbp1 psyq_host269 at156234,padFrame4403217472,condition156234,sanctuary-control FIFO/record inR18snapshot. Currentroot[-837,129,1623],yaw1779,ForkedRoadcleared. NextnavigateFountaindoor near[-5100,-3900],thenHallway/SecurityrightlockusingRedKey. Healingavailable(26MP),ammoPB52+Hydra29. Fullport/No9boss/MIST_R18runtime remainincomplete.


### Fresh return to Security and right power lock (2026-11-03)

Continued the recorded physical-input branch from Forked Road checkpoint 156234 through Fountain and Hallway into Security Room. Fountain captions interrupted an initial traversal; waited for them and navigated normally. No target functions or target memory writes were used. Opened the power panel, moved its cursor to (64,32), selected the retained Item option and Red Key, then let the authored right-lock scene finish.

Checkpoint 165152: panelKeys=3 (both released), Red Key 259 absent, power task gone, actor mode/state=0, eventState=0, pendingMode=0. HP81/115, MP27/31, M93R equipped, 29 Hydra and 52 PB retained. Independent finite replay with video/virtual clocks passed ten expectations and its complete collected checkpoint dictionary equals the live dictionary. Evidence: build-port/reference/fresh-red-unlock/ (165152-sample input, live and finite checkpoints, debugger log). This proves native replay repeatability for this checkpoint, not console-wide parity.

Continued live to 165575: Hallway area7/state1/variant4/warp2, position [2271,-871,950], yaw2048; HP81/MP27 unchanged, normal control. Next: traverse toward the powered route, Fire Escape save and No9. No9 victory and post-boss MIST runtime remain unverified.

## Overlay registry: findings (2026-11-03)

- **Link.** `-DPE_ALL_OVERLAYS=ON -DPE_ALL_VARIANTS=ON` links: private per-object names for the 669 clashing globals
  (`cmake/overlay_renames.cmake`, `tools/port/gen_overlay_renames.py`, `tools/port/regen_overlay_renames.sh`).
- **What `main` calls by address.** 22 `func_8070xxxx` and a few `D_8072xxxx` names (task bank 3 in
  `src/main/stage_music.c`, `gTaskBank3Descs`; `func_80701400` in `textdraw.c`) are weak aborting stubs in
  `src/port/unresolved_stubs.c`. They are not an overlay to find: the PlayStation has 2 MB of RAM
  (`0x80000000`-`0x801FFFFF`), no package loads above `0x8017D5C0`, and no file under `asm/USA` defines code there.
  The addresses are in a retail-absent region (the 8 MB development-kit RAM), so those task slots can only hold code
  the shipped game never runs. Aborting if one is ever reached is the right behaviour; the stubs stay and are not part
  of the registry work. (This corrects the earlier assumption that they were a missing package.)
- **Run-time wiring still to build.** Load a stage's packages by name from the disc, call a package's reset hook, and
  None of this exists; the executable runs the Akropolis
  stage only.

### All-overlays executable, observed (2026-11-03)

With `PE2_START_LOCATION`, `PE2_DUMP_VRAM` (frames written from the port itself, no screen capture) and both discs
(`--disc2`), the all-overlays build shows, for each stage, its scene behind the HUD or the Triangle menu that the
scripted input opens: Dryfield (2, "Now Loading" card then the scene), Dryfield by night (3), the mine (4, Aya in a
cave) and the Shelter / Neo Ark (5, a corridor with a vehicle). The disc swap works: stages 4 and 5 first showed the
game's "Change to DISC 2" card because PsyZ kept read/play bits in the drive status across the lid cycle, so the
game's wait for a plain "standby" status never ended (fixed in the fork: `Psyz_CdShellOpen(0)` resets the status).
No crash and no aborting stub in these runs.

Walking: in Dryfield, holding Up (`PE2_PAD_HOLD=0010 PE2_PAD_FROM=1200`) after the loading card gives, at tick 4000, Aya
standing by a yellow car with the camera above her, and at tick 6500 a different camera on the street with the sky
behind her: the player moves and the view changes with the position, as in the original. 
Stage changes during play (`PE2_WARP`, which re-runs the session-start path with a new live location): from a new game
in Akropolis, warping at tick 3000 to Dryfield, to Dryfield by night, and (with disc 2) to the mine each loads the new
stage and renders it with the player (Dryfield with the HUD and Triangle menu, the night gas station with a car, the
mine area with a truck), without a crash or an aborting stub. So with every overlay linked, a stage change works
without a run-time registry; what it does not show is stale state left by the previous stage. Return trip: warping Akropolis, then
Dryfield at tick 3000, then Akropolis at tick 5000 (`PE2_WARP="3000:2,1,1,1,1,1;5000:1,1,1,1,1,1"`, same new-game input) and a direct warp to Akropolis
at tick 3000 show, at tick 14000, the same frame (the Triangle menu over the same scene): 60 of 76,800 visible pixels
differ (a 28 x 83 px patch, animation timing); the logs show no crash and the same stream of unsupported GPU command FF
warnings as the direct run, so no stale state from Dryfield was visible. VRAM outside the display differs, as expected.
Not yet checked: doors between rooms outside Akropolis, and saving.

### Missing-player transition crash: verified fixed (2026-11-03)

The `_stageResolvePlayerContacts` null-player guard (commit `2bd8ed6d`) was verified against the recorded failing
endpoint: `build-port/input/video-clock-forked-road.pad` (162,274 samples, the input that crashed
`_stageResolvePlayerContacts` at stage.c:454 while `_sceneBattleResultTask` held a forced reload with no player).
Replayed on the current build with `--clock video --raster-clock virtual`, it exits 0 with a live player
(HP110, East Elevator Hall, objective2/storyDialogue3). The route's content diverges from the old recording's
Forked Road endpoint (later audio/clock fixes changed earlier timing), so this verifies the crash fix, not that
the historical input still reaches its original state. The engine never dereferences a missing player task; the
guard skips only contact resolution when the slot is absent.


### Resumed physical-input branch: post-Red Forked Road victory (2026-11-03)

The former controlled PID6296/LLDB session no longer existed. Preserved its 169437-sample input record and replayed it using the matching isolated r18 executable (/tmp/pe2-mist-r18-20261102/r18-out/parasite-eve-ii-pc). This restores the validated branch; it is not evidence that the current HEAD reproduces the old timing. Recovered Fountain [4669,129,2782], yaw56, HP47/MP16, panelKeys3, PB52/Hydra29. Continued to post-Red Forked Road variant4 at170045.

Used ordinary Healing (47->77), MP Boost2 (item7 consumed, MP5->31), equipped Tonfa and cast Healing again (HP107/MP19). Triggered four80HP Caterpillars, used one Pyrokinesis (8MP), then fresh Tonfa attacks. At176237 the encounter is cleared: battleRefs0, result/loot closed, Recovery1 obtained, HP32/MP15, EXP82, PB52/Hydra29 unchanged. Independent finite replay passed seven expectations and the complete collected dictionary equals the live checkpoint. Input, both checkpoint JSONs and LLDB log are archived under build-port/reference/resumed-post-red-forked-clear/.

Recovery1 then consumed normally: HP32->82, MP15 unchanged, item1 absent at177521. Proceeding to Observatory; no new gameplay defect was established during this segment. No9 and later progression remain unfinished. Live runtime uses its isolated matching source/symbols; future defects must be checked against current HEAD before proposing a production fix.

At178173 reached Observatory area10/state2/variant3/warp2, root[-2408,-2861,-1748], yaw1024, HP82/MP15, Tonfa, PB52/Hydra29. Nine bats are staged above the room (holdingPlayer0, battlePhase0); the ambush is next. Live LLDB session20774/PID48363 is stopped at input boundary178173, source269; FIFO resume-fountain-control.fifo, record resumed-fountain-controlled.pad. Saved arrival input/live checkpoint under build-port/reference/resumed-observatory-arrival/. Arrival itself has not had a separate finite replay.


### Resumed branch: bats, Bridge and Fire Escape cleared (2026-11-03)

Continued live20774/PID48363 from178173 on the matching isolated r18 runtime. Triggered the nine-bat Observatory ambush and attacked earlier than the historical route's long idle delay. At179587 all nine are dead, HP82 unchanged, MP24 (reward+9), EXP127, result closed. Normal loot adds50 Hydra: total79, PB52 retained. Independent finite checkpoint equals the full live dictionary. Its initial CLI run exited1 only because the expectation still said Hydra29; seven corrected assertions against that captured checkpoint pass. Keep this distinction: evidence and explicit corrected validation are under build-port/reference/resumed-bats-clear/.

Crossed cleared Observatory to Promenade at180168, then entered Bridge at181606 without injury. Entered normal keypad code561, watched the bridge movie, restored control at186962: bridgeProgress3, HP82/MP25, Hydra79/PB52. Separate full replay passes8 expectations and its complete checkpoint equals live. Evidence: build-port/reference/resumed-bridge-raised/.

Crossed Bridge, completed the first Fire Escape door scene and settled room initialization at191500. Defeated50HP Lesser Stranger using Tonfa; at193467 HP82 remains unchanged, MP30, EXP169, Recovery2(item2) obtained, battleRefs0, UI/event/pending0. Dead Lesser Stranger task remains HP-1/state4. Player[1935,128,-1700], yaw2060, Tonfa19. Fire Escape input/live checkpoint archived under build-port/reference/resumed-fire-escape-clear/; this final endpoint has not yet had its own independent replay. Next: telephone, actual memory-card save, Healing/Recovery2 and No9.

Before any Fire Escape save, preserved the initial Square memory-card fixture as /tmp/pe2-mist-r18-20261102/phone-report-cards-initial-square. Live still writes phone-report-cards. Future full replays that include saving must use a disposable copy of the immutable initial fixture, otherwise changing the starting Continue save invalidates the recorded prefix. Live20774 is paused at193467, pad_addr4403217472, breakpoint1 source269, FIFO resume-fountain-control.fifo, record resumed-fountain-controlled.pad. No new gameplay crash established; all proof here concerns the isolated r18 build, not current HEAD.


### Current-build migration and No9 battle evidence (2026-11-03)

Completed the Fire Escape telephone conversation and saved through the actual overwrite-Yes menu. Immutable native card fixture SHA256 b1d92bbc1b474fc578ff916f0eb587b35d9001aca4fca691e105a01feda3f586; evidence/cards in build-port/reference/fire-escape-save-current/. Continue loads the same Fire Escape player/progression/inventory domains in isolated r18 and current main de9fa011. Exported a raw PS1 card, but have not verified loading this new save in original DuckStation. Main repository now resides at /Users/hasik/Projects/parasite-eve-ii-port/parasite-eve-ii-pc (parent is no longer a Git checkout).

Migrated play onto a frozen copy of current main binary in /tmp/pe2-current-fire-20261103. Current landing endpoint7077 passes9 finite expectations and full live/finite equality; evidence current-landing-ready/. Equipped M93R/Hydra and healed before entering the encounter. First transformer replay10417 inflicts180 damage (No9HP1322); its complete live/finite dictionaries match, evidence no9-first-transformer/.

A blind in-combat inventory sequence ended with Aya dead and Recovery2 unconsumed. Source attachment_stats.c confirms battle Start opens armor attachments, not the full inventory. Replayed from landing, equipped Recovery2 in armor slot3 through ordinary menus, and consumed it through battle Start/Right/Right/Confirm: HP72->115, item2 absent, No9HP1311. Endpoint13149 passes4 finite expectations and full live/finite equality; no9-recovery-battle/. An initial runner attempt omitted the initial card copy and loaded area20; corrected evidence explicitly uses the Fire Escape fixture.

Second transformer must fire late in the flame-lunge windup, not during grenade windup. Corrected physical replay15269 hits for180, leaves No9HP1023/Aya81HP, Hydra59, magazine0. Full independent/live equality in no9-second-transformer/. Automatic reload then refills20 Hydra normally. Reached third-transformer approach, used Healing correctly at16576: HP60->102, MP18->6, No9HP1023. Full independent/live equality in no9-third-healed/; original CLI expectationHP90 was a wrong assumed healing amount, corrected offline checks pass and the original output is retained. Battle PE directions cycle known spells, unlike the out-of-battle directional element menu: with Healing7 already selected, use Triangle/Confirm without a directional press.

No9 is NOT defeated. Following the healed checkpoint with idle aim lets him reach lethalPhase1/lap46588 before enough gun damage is dealt. This is an unsuccessful tactical branch, not a confirmed port defect. Need resume from16576 or earlier transformer checkpoint and deal substantially more gun damage during movement/windups rather than waiting for the next cable. Third-transformer shot at17084 did not hit (target was not acquired); fresh aim/target verification is needed. All replays use real controller samples, read-only LLDB; no state injection or target function calls.

Live owned debugger47770/PID61111 is stopped at boundary17084, breakpoint1 psyq_host.c305, pad_addr4309830688, FIFO third-control.fifo, record third-controlled.pad. Earlier owned sessions17662/71432/34470 were retired after replacement verification. Immutable input no9-third-healed.pad16576 remains the useful restore fixture; use a fresh disposable copy of initial-cards. No new engine crash established in this segment. Added read-only No9 state/lap/animation diagnostics to replay_checkpoint.py. Goal remains unfinished and active.


### No9 defeated; helicopter GPU corruption fixed; MIST reached (2026-11-03)

Completed No9 through ordinary controller play. Key missing tactic: shoot third transformer before No9 arrives, reacquire the newly armed blast-source target with a fresh Square press, then shoot that source while the cable still sparks. Third transformer inflicts180 (No9HP843); source blast531 (HP312) and stun; sustained R1 and a fresh empty-fire reload finish No9 before lethalPhase2. At17798 HP0/lethalPhase0; normal authored departure and reward follow. At20838 result closed, Aya102HP/31MP, EXP669(+500), BP2044(+800), battleRefs0/objective8. Independent replay passes8 expectations and full checkpoint equality; build-port/reference/no9-cleared/.

After battle, use the lowered lift: reach trigger1 near(-5274,-1840), face south, inspect and confirm Go up. Trigger8 is disabled during this phase; do not interpret the northbound walkway wall as an engine bug. Lift/departure scene and Rupert dialogue work. During view24 helicopter flight, old main de9fa011 crashes at input29172 in GPU_Enqueue. Native packet projection used PS1 offsets and overwrote packet length with XY2293731; the unchecked oversized packet then overwrote resident memory. The packet owner is _helicopterDepartureHelicopterSearchlightTask (unlitGT4 stream0x156). Evidence plus controller recording/cards and pre-overwrite checkpoint in no9-return-gpu-crash/.

Fixed six gte_compat.h polygon XY stores to use offsetof on their native PsyZ packet type. Corrected13 model_lighting.c payload lengths to console GP0 word counts (host tag/length/padding are not payload). Replaced the old GTE store test's erroneous disk-offset expectations with typed packets and sentinel checks preserving all bytes outside XY. Old implementation fails6 checks; fixed gte_compat_test passes. tmd_ops_test, tmd_prim_test, tmd_layout_test pass; production binary builds. Replay identical input through former crash succeeds30105, full live/finite equality. Continued through streamed interlude to MIST_R18 area18/state1/view10 at32505,115HP/31MP/669EXP/BP2044;8 finite expectations and full checkpoint equality. Evidence and exact fix.patch in build-port/reference/no9-return-mist-fixed/.

Current play uses frozen patched runtime /tmp/pe2-no9-fixed-20261103 (build-id.txt SHA256 plus patch in evidence), normal initial Fire Escape cards. Live debugger74101/PID56845 stopped at33273/sourcepsyq_host.c305; pad_addr4309830688; FIFO control.fifo; record controlled.pad. MIST briefing is running (area18/view4/eventState1), Rupert/Baldwin/Aya rendered normally. Prior crashed/probe sessions83468 and91251 retired only after verified patched replacement. Continue the briefing and subsequent game progression. Full goal remains active; this is not end-of-game completion.


### MIST briefing complete, Pierce walk fixed, Dryfield save validated (2026-11-03)

Continued from33273: briefing key-item menu requires opening Dryfield Map; closing early correctly triggers Baldwin's reminder. Read the map, completed departure dialogue, reached parking area19/state3/variant2. New mission resets the carried loadout (armor4,105HP/41MP, weapon initially0, M93R/PB100/Tonfa/Recovery2/GPS). At49037 intro dialogue ended with normal control;8 finite expectations and full live/finite equality in mist-briefing-parking-complete/.

Found Pierce stranded outside the map: old live50025 root[1805,0,-38459], idle, authored target[5030,0,-5680]. _actorMotionWalkAxisGap took const long* but callers pass native32-bit VECTOR/MATRIX fields; LP64 reads adjacent words and chooses the wrong signed subtraction order. Replaced it with scalar s32 arguments at all eight calls across parkingPierce, actor310600 and shared arrival carriers. actor_walk_gap_test covers negative parking coordinates, overshoot and intentional low-halfword boundary behavior; registered in CTest. New replay49037 has Pierce[5025,0,-5724], target unchanged, and full live/finite equality. Subsequent ordinary approach/talk works and Ready launches Dryfield departure. Evidence: pierce-walk-fixed/.

Important evidence limit: an additional old executable re-run after rebuilding could not collect a checkpoint because its Mach-O debug map references .o files since rebuilt. Retained failed old-finite output/log honestly; do NOT claim paired independent old/fixed NPC replays. Old pre-rebuild live snapshot is the before evidence. New fixed binary now has a standalone32MB dSYM in /tmp/pe2-pierce-fixed-20261103 to preserve symbols across future builds. Freeze dSYM along with executables before rebuilding, not only the Mach-O.

Arrived at Dryfield Gas Station stage2/area1/view2,105HP/41MP/M93R/armor4. At58033 normal control, eight finite expectations pass and full live/finite equality; dryfield-arrival/. The movie's apparent rainbow noise was the VRAM export using15-bit pixels; correct --rgb24 export shows Welcome to Dryfield normally. No movie engine defect established.

Walked to phone near[4384,-528], inspected, called Baldwin and saved through actual overwrite-Yes. At62105 normal control, native8192-byte card SHA256 ed668f357568f6cdbd5b95f0b4f1636a90481e5684132556b8c7768944ab0128. New immutable dryfield-save-cards plus build-port/reference/dryfield-save/cards/. Continue2492 passes8 expectations and independent/live full equality. Versus pre-load saved live state, playerStatus/carried/collected/weaponLoads/inventoryRows/PE levels match; warp changes1->2 to suppress arrival replay, rootY settles-2->126, transient PE selection resets. No full pre-save/post-load dictionary equality claim. Full62105 replay starts with full-replay-initial-cards (Fire Escape), whereas short Continue starts with final cards/.

Active debugger54700/PID82898 now runs short Continue on frozen patched /tmp/pe2-pierce-fixed-20261103, stopped at2492/psyq_host.c305; pad_addr4309830688; FIFO dryfield-control.fifo; record dryfield-controlled.pad; live card directory dryfield-live-cards. Runtime has binary+dSYM, initial-cards (Fire Escape) and dryfield-save-cards (new immutable save). Old debugger63389/PID63928 retired after the replacement's full state equality. Aya[4657,126,-1135], Gas Station view4, facing32, weapon2/PB20loaded100total, Recovery2 already attached slot2. Next: continue Dryfield exploration/combat from the phone. Goal remains active and game far from complete.

Validation after changes: production build succeeds; five selected CTests actor_walk_gap/gte_compat/tmd_ops/tmd_prim/tmd_layout pass, Python compile and git diff --check pass. No commits or reverts made.


### Dryfield combat and factory reached (2026-11-03)

Continued the short Dryfield save branch with normal pad input. Cleared Main Street Desert Chaser (75EXP/50BP/4MP, Hydra50 loot), Toilet Stranger (42EXP/82BP/4MP, MP Boost1 loot), and all25 Driveway bats (125EXP/450BP, MP capped). Each closed-result endpoint has an independent finite replay with eight expectations and complete live/finite dictionary equality: dryfield-first-chaser-cleared/ at6617, dryfield-toilet-cleared/ at14133, dryfield-driveway-bats-cleared/ at23784. Chaser archive retains pre-loot failed pendingMode expectation separately; this was a still-open loot screen, not an engine defect. Used last loose inventory row MP Boost1 normally (MP17->41; item removed). Bat holds require eight fresh direction/face-button edges; held R1 does not escape. Tonfa cleared bats without spending ammunition.

Healed45->105 using two ordinary Healing casts (MP41->17), entered Factory23 at25967. Entrance explicitly says It is not locked; do not confuse this with the genuinely locked Motel reception. Factory arrival replay passes eight expectations and complete live/finite equality in dryfield-factory-arrival/. Aya105HP/17MP, EXP911, BP2626, Tonfa19, PB82/Hydra35, Recovery2 attached. No new production defect established in this segment.

Read-only replay diagnostics now collect stage2 enemies, Desert Chaser state and bat positions; collect rejects running processes. One manual input sum was caught before submission; resumed the same live process rather than restarting. No production rebuild required for these Python-only additions.

Explored Factory normally: operator panel opens with rendered cursor and exits correctly; power is still off and no lift action attempted. Reached west Breezeway door at29223: actual caption Funny. It will not open. No transition failure inferred. Current live54700/PID82898 stopped at29223/source305, pad_addr4309830688, same frozen runtime/FIFO/card directories as above. Aya[842,2,7608], yaw3112, area23/view7, pendingMode129 from door caption. Close caption before moving. Exploration replay/live/screen in dryfield-factory-exploration/; this exploratory endpoint has no independent finite proof yet. Next: power/lift puzzle and Douglas route. Goal remains active and unfinished.


Factory continuation: normal approach to far-end breaker at[5525,10229] opens the authored power scene; accepted default choice turns breaker on, lights control panel and returns control at32395. Returned via west aisle, opened powered panel at35430. Cursor D-pad is2pixels/sample; Left30/Up28 reaches UP(-60,-56), Cross opens Push prompt, next Cross raises lift. Right40 reaches TURN(20,-56), Cross/Push rotates it; Circle exits. At37308 normal control, independently read live packedFlags[36]=0x13 (power1, lift raised|turned3). Eight finite expectations pass and full collected live/finite dictionaries equal; dryfield-factory-powered-lift/. Factory flags themselves are not yet in finite collection, so flag assertion is live-only. No production code defect established.

Current live54700/PID82898 stopped37853, Aya[5287,1,3647],yaw24, Factory23/view2, pending129 caption: A metal shutter. It is locked from the other side. This is the north face; route via lift/other side still needed. Current full physical input in runtime dryfield-controlled.pad. Previous fixed-point arithmetic issue in manual endpoint sum left debugger running at FIFO; added100 neutral to reach intended33281, no restart or target mutation. Do not collect while running; guard correctly rejected that attempt. Next continue puzzle: lowered turned lift (position2) enables hatch scene; raised turned is3. Inspect before choosing route. Goal unfinished.


Factory hatch loot completed at42700: reopened panel, DOWN/Push lowers the turned lift. Correct bit definitions in factory/config.h are TURNED=1, RAISED=2; earlier guidance saying lowered-turned2 was wrong. Live packedFlags[36] becomes0x11 (power1/lift1). At[1408,7142], facing east, inspect opens Shotgun Shell10 pickup; accept Yes and close. Carried174=10, normal control, HP105/MP17 unchanged. Six finite CLI expectations pass and full collected live/finite dictionaries equal in dryfield-factory-hatch-loot/. No new production defect established.

Current owned session54700/PID82898 stopped47422, same FIFO/runtime/pad_addr. Aya[3245,131,8454],yaw1288, Factory23/view8, pending0/event0. Trying to reach Garage east door around car/cylinders; geometry redirects several long movement batches, so use shorter steps and inspect yaw after movement. No claim that passage is defective. Latest live snapshot /tmp/pe2-factory-latest.json. Full input dryfield-controlled.pad includes all physical navigation. Goal remains active; Douglas not yet reached.


Factory shutter opened at50434. Important route: from south car side, west aisle north toz~5000, then east around its north end reaches[5626,5779]; inspecting east opens button scene. Advance descriptions/accept default action: red changes to green, caption says shutter seems to be unlocked. Approach[5696,4969] facing north, inspect shutter, confirm. RoomState changes1->2 and barrier visually disappears. Seven finite expectations and full collected live/finite dictionary equality in dryfield-factory-shutter-open/. No new production defect confirmed. Aya105HP/17MP, Shotgun Shell10 retained.

Returned toward panel to raise car for further passage. Current live54700/PID82898 stopped51873; latest /tmp/pe2-factory-current.json, same FIFO/runtime/record. Read current position/event before sending next action. Potential separate code concern to reproduce on future room reentry: _factoryHatchInit assigns work->state=0xff when hatch-open flag1, while _factoryHatchUpdate indexes a three-entry state table. This is source suspicion, not yet a verified runtime bug; do not patch without reproducing/understanding lifecycle. Goal active.


Reached Garage area24 at59580. Raised turned lift again at53243 (flags0x13), then TURN restores original direction at57450 (flags0x12). Car geometry changes accordingly. Successful route approaches garage via north side: from[4114,3649],yaw968, runEast35, Left22, runSouth95, Right23, Cross8,neutral300. Actual transition to Garage24/root[2484,128,2373],yaw1024/view7/warp1; Aya105HP/17MP, shell174=10. Event1 is garage intro, not free control yet. Independent finite dictionary equals live entirely; original CLI incorrectly expected event0 and exits1. Retained original output, seven corrected offline assertions pass in dryfield-garage-arrival/. No production defect established. Live54700/PID82898 stopped59580, same frozen runtime/FIFO/pad_addr; continue garage intro. Full input dryfield-controlled.pad. Goal remains active; Douglas encounter not completed.

Extracted factory collision vertices/faces read-only to /tmp/pe2-factory-grid.json to inspect route; normals read count28 is insufficient for all static faces, so do not treat it as a complete decoded collision export. No RAM edits or target calls performed.


Douglas garage scene completed (2026-11-03). Continued authored gunpoint introduction, conversation and subsequent ordinary talks through physical Cross edges. At71360 event0, normal HUD/control restored, Aya105HP/17MP, area24/view2/root[2250,129,2200], shell10 retained. Body task was interaction3/talkStage2 at71052; blank CAP still awaited a final fresh Cross, which cleared flags0x40->0 at71360. This was not a dialogue hang. Six finite CLI expectations pass and complete collected dictionaries equal in dryfield-douglas-dialogue-complete/.

Attempted south Junk Yard door triggers Douglas Where are you going? refusal; completing its ordinary dialogue restores control73518. Returned via garage west door to Factory23/state2/view6/warp3 at74360 without crash. Existing source suspicion about hatch-open initialization was not reproduced by this reentry; no production fix made. Current live54700/PID82898 stopped74360, same pad_addr/FIFO/frozen runtime. Latest /tmp/pe2-post-douglas-factory-live.json; full physical input dryfield-controlled.pad. Need continue onward from Factory after Douglas conversation. Goal remains active, game unfinished.


Post-Douglas Main Street scorpions (2026-11-03): exited Factory to cleared Driveway75882, Main Street76829 now variant2. Room4 inspect shows Nobody is home; east hotspot is TV, not stairs. Six actor02500 scorpions activated while traversing street. Previously roomEnemies omitted this callback, although combat.battleRefs6 correctly showed battle; do not infer no enemies from that list. Added read-only _actor02500Task HP/root capture to replay_checkpoint.py and frozen runtime helper. No production change.

Fresh Square+R1 Tonfa edges damage groups. At81262 two remain, Aya64HP;82302 last4HP, Aya38. At83222 all six defeated, reward120EXP/48BP/6MP -> EXP1031/BP2674/MP23. Loot Medkit(item8) collected, menus closed, ordinary Healing38->68 costing12MP. At84094 HP68/MP11, refs0, pending0, battleResetPending1 (do not claim reset flag0), PB82/Hydra35/Shell10 unchanged, item8=1. Input/live/screen archived dryfield-main-street-scorpions-cleared/. Independent finite replay currently running session98717; inspect same handle or /tmp/pe2-scorpions-finite.json and log before concluding result. Do not restart merely on timeout. Current live54700/PID82898 stopped84094; latest /tmp/pe2-scorpions-cleared-live.json; same frozen runtime/FIFO/pad_addr. Next heal/use Medkit as appropriate, continue motel/Water Tower progression. Goal active, no new production defect confirmed.

Scorpion finite replay session98717 exited0: all7 CLI expectations pass and full collected live/finite dictionaries identical. Evidence copied to dryfield-main-street-scorpions-cleared/.


Parking Lot variant2 encounter (2026-11-03): reached84898, two200HP Desert Chasers, not old cleared parking layout. Attempting stairs with Tonfa was a tactical failure: HP68->50, Recovery2 attachment used85544..85748 restores105 and item2 consumed; two subsequent rushes reduce45. Start during hurt may be ignored; repeated edge opens attachment-use panel. This panel only selects attachment slots with Left/Right; it does NOT switch weapons. No engine defect inferred.

Retreated east door. Fresh Cross triggers normal escape result at87431: EXP0, BP-10 (2674->2664), MP+1 (11->12). Close result87739 reaches MainStreet2/view6/warp3,HP45. Inventory Use Medkit8 reports No use for this now; remains carried. Do not claim it restored HP. Earlier /tmp/pe2-medkit-used-live.json name is misleading: item was not used. Equipped M93R with Hydra through regular weapon picker at90465: weapon2/slot2,35Hydra total20 loaded, PB82/Shell10 unchanged. Ordinary Healing at92205 restores45->75,MP12->0. Current ready state live54700/PID82898 stopped92205; same runtime/FIFO/pad_addr. Source /tmp/pe2-parking-prepared-live.json; archived replay/live dryfield-parking-retreat-prepared/ (no independent finite replay yet). Medkit remains1, Recovery2 gone. Need reenter parking with gun or find alternative progression; Chasers not defeated. Goal active, no new production defect established.


Parking Hydra attempt and verified restore (2026-11-03): reentered from92205, approached only80samples then aimed/fire from[8053,3077]. First Chaser200->98 at92777,32 at92997,dead-4 at93225; Aya75->45 from one rush. Second200->185->84 at93493; Hydra exhausted35total. Closing to stairs fails: Chaser69HP, Aya22 caught in128-press hold at94494.130 one-sample Square edges are too short to register every gameplay update; at94754 Aya5HP still held. This is tactical failure, no port defect confirmed. Evidence dryfield-parking-hydra-failed/; no claim parking cleared.

Restored by replaying physical input prefix92205 from immutable native Dryfield save, fresh disposable parking-retry-cards. New LLDB33787/PID49976 stopped92205/source305; full collected dictionary equals original /tmp/pe2-parking-prepared-live.json exactly. Latest /tmp/pe2-parking-restored-live.json. New FIFO parking-retry.fifo, recording parking-retry-controlled.pad, launch parking-retry.lldb in same /tmp/pe2-pierce-fixed-20261103. pad_addr4309830688. Aya75HP/0MP, EXP1031,BP2664,M93R Hydra35total20loaded, PB82,Shell10,Medkit1; MainStreet2/view6/warp3 root[-6465,130,2155],yaw1024. Old failed owned debugger54700/PID82898 retired only after replacement equality verified. Next prepare ordinary PB ammo or better supplies before parking; no Recovery2 remains. Goal active.


Additional parking PB branches (2026-11-03): ordinary weapon picker correctly loads PB82. Initial200->105HP Chaser at94013 with75HP Aya/PB7loaded. Stationary fire/late attempted dodges again lead captures; no engine defect established. Source shared/creatures/desert_chaser/desert_chaser.inc.c explicitly sets CATCH_PRESS_COUNT=128; do not claim numeric mismatch from that alone. PB-dodge/north branch replays/checkpoints archived dryfield-parking-pb-attempts/. Both94013 restores matched full before-dodge checkpoint. Failed tactical branches, not progression completion.

Verified new restore from immutable Dryfield cards through previously proven scorpion-clear prefix84094: full dictionary equals /tmp/pe2-scorpions-cleared-live.json. Current only owned active debugger23029/PID72789, stopped84094/source305, pad_addr4309830688. FIFO parking-fresh.fifo, record parking-fresh-controlled.pad, launch parking-fresh.lldb under same frozen /tmp/pe2-pierce-fixed-20261103. Aya68HP/11MP, Tonfa19, PB82/Hydra35/Shell10, Recovery2 still attached2, GPS1, Medkit1, EXP1031/BP2674. MainStreet2/variant2 root[-4113,125,1028],yaw2282. Retired previous owned33787/PID49976,27506/PID24539,79356/PID48805 only after replacement match. Next equip gun before parking, keep Recovery2 for battle and use Pyrokinesis8MP to reduce first Chaser before lunge. Earlier badly planned parking attempts and retreat are excluded from this fresh branch. Goal unfinished and active.


Parking Chasers cleared and motel balcony reached (2026-11-03). Failed PB+PE continuation archived dryfield-parking-pb-pe-failed/; no production defect established. Correct attachment indexing: carried attachSlot is1-based, UI selectedAttachmentIndex0-based; Recovery2 attachSlot2 is UI index1. Selecting UI2 was empty, not broken healing. Restored proven84094 with complete checkpoint equality, new runtime control parking-hydra-pe.lldb/FIFO parking-hydra-pe.fifo/record parking-hydra-pe-controlled.pad/cards parking-hydra-pe-cards. Owned old23029/PID72789 retired after match. Current debugger38459/PID72087, pad_addr4309830688.

Equipped M93R Hydra20loaded/35total. After parking intro wait200, Triangle opens PE, Right cycles Healing7->Pyro0, Confirm casts8MP (11->3), nearby Chaser200->125. Fresh Square can cycle to distant target; Square+Right confirmed nearest selection at86584 before firing. Damage contacts/interception still split damage across two enemies. At86962 enemy85/59HP, Aya38. Open attachment panel, Right once from0 selects Recovery2, Confirm consumes; heals105 but immediate rush leaves75. Fresh R1 reloads15Hydra. Sustained fire leaves one22HP at87736, Aya45/PB82 untouched,3Hydra loaded. Fresh aim acquires survivor, R1 finishes. At88484 refs0/enemiesempty, reward150EXP/100BP/8MP -> EXP1181/BP2774/MP11. Cross closes result88692. Seven independent finite expectations pass and complete collected live/finite dictionaries equal in dryfield-parking-chasers-cleared/. All35Hydra spent, Recovery2 consumed. No engine change necessary.

From parking cleared root[10494,3211],yaw2569: Right11/runWest160/Left23/runNorth30/Cross8/neutral240 enters motel balcony29/view2/warp1/variant2 at89164. Aya[-12638,-3070,1396],yaw0, HP45/MP11/M93R(emptyHydra selected), PB82/Shell10/Medkit1, Recovery2 absent. Live and replay/screen archived dryfield-motel-balcony-arrival/; arrival itself not separately finite-verified. Current owned38459/PID72087 stopped89164/source305; same frozen binary+dSYM. Next continue balcony/Water Tower route, load PB outside combat and consider MP supplies. Goal active, game incomplete.

User constraint: do not delete any more GitHub tags. No further tag deletions authorized.


Motel balcony and Room6 progression (2026-11-03): equipped PB before combat at90440 on exploratory branch,3 Odd Strangers180HP each. Stationary fight failed, HP-16 at91677; PE input while hurt was ignored (MP11 unchanged). Failed physical record/checkpoint in dryfield-balcony-failed/. No production defect established. Room6 key collection271(0x10f) already present from Douglas progression; loft requires masterkey275, so target Room6 rather than loft.

Restored89164 balcony arrival from native cards, complete live dictionary equality. New only owned LLDB20641/PID65311, runtime same patched binary+dSYM, pad_addr4309830688, FIFO balcony-route.fifo, record balcony-route-controlled.pad, launch balcony-route.lldb, cards balcony-route-cards. Old dead38459/PID72087 retired after replacement equality. Run south80/east175 approaches balcony, then south in short steps to[~6400,4424]. One hit45->25; walk west into hotspot[6698,4412] facing3050, Cross unlocks with Motel Key No6. Advance caption and normal escape result: BP2774->2764, MP11->12. At90840 Room6 area30/view2/warp1/variant1, normal control/event0/pending0, HP25/MP12/EXP1181, M93R selected emptyHydra, PB82 untouched (PB-equipped failed branch excluded). Seven finite expectations pass and complete collected live/finite dictionaries equal in dryfield-room6-arrival/.

Current owned20641/PID65311 stopped90840, Aya[4350,130,1500],yaw3072. Room6 has phone and water-tower route; inspect before exiting. WaterTower warp hotspot[672,6656], room actor event near[1304,7248], bedside descriptions near[1264,3024]. No new engine fix. Next heal safely (12MP available), phone save if possible, complete Room6 event and WaterTower progression. Goal remains active.


Room6 Healing and STR ring deadlock fixed (2026-11-03). Ordinary Healing25->55 costs12MP, now0. Daytime bed says not sleepy; no rest occurred. Examined portrait, canceled with Circle. Phone not used and no new memory-card save; do not claim a save. Navigated around furniture to rear terrace; inspecting near[~800,6656] triggers Room6 tower movie. Correct --rgb24 VRAM export shows valid frame;15-bit noise was only wrong viewer format.

Actual engine defect: at98481 after >3000 neutral samples movie remains frame6/scene6, movieStep3/decode, event1/pending255. STR ring40 has ready frames5..8, producer indices0/0 but consumer StRingIdx3=40. StFreeRing left exact-capacity consumer one past header table, so StGetNext reads payload as a header. Host StCdInterrupt also attempted an out-of-table wrap marker at that same boundary. Old state/replay/cards/RGB24 frame in room6-movie-ring-stall/; old initial regression reports frame5 unavailable.

Fixed PsyZ submodule decomp/src/libcd/c_007.c to wrap consumer at exact capacity. Host psyz/src/psyz/libcd.c now checks destination frame space before publishing wrap marker/resetting producer indices, and never accesses a wrap header at ringSize. Expanded regression exposed premature marker publication for41-sector rings (frame9 unavailable), also fixed. New main tests/cd_ring_test.c pumps genuine synthetic STR CD sectors through real producer/SDK consumer,12frames across40/41/37-sector rings, checks order/every payload byte including zero prefix (must never become wrap marker). CMake target auto-registers CTest. Production builds; cd_ring/cd_pump/gte_compat/actor_walk_gap tests pass; root/submodule diff checks pass. No commits/reverts/tags changed.

Frozen final runtime /tmp/pe2-movie-ring-final-20261103 has binary+standalone dSYM/source/helper, cards initial immutable Dryfield save copy, control.fifo, controlled.pad, control.lldb. Exact same98481 physical input now completes movie, event0/pending0, ordinary control. Seven independent finite CLI expectations and full collected live/finite equality in room6-movie-ring-fixed/, with SHA256 and exact submodule patch. Earlier intermediate fix reproduced same full live state; retired intermediate owned21461/PID59963 and old stalled20641/PID65311 only after final verified replacement. Current only owned debugger88695/PID85165 stopped98481/source305, pad_addr4309830688. Aya55HP/0MP/1181EXP/BP2764, Room6 area30/view5/warp1/variant1 rear terrace[787,129,7000],yaw3584, M93R(emptyHydra),PB82/Shell10/Medkit1. Next enter WaterTower via terrace hotspot672,6656 after movie. Goal active and full game unfinished.


### 2026-11-03 — Water Tower navigation after STR fix

The corrected movie completed and physical input reached Dryfield Water Tower (area20/state1/variant1) at99297. Equipped M93R PB normally (20 loaded, 82 total); opening actor scene completed at102875: ordinary control/event0, Aya[-700,131,-4500], yaw3072, HP55/MP0. Saved live checkpoint `/tmp/pe2-water-opening-complete-live.json`. Restoring this exact recorded prefix with the frozen final STR binary produced full collected checkpoint equality.

Read-only collision mesh inspection explains navigation: the east corridor is a dead end at z2500 (Aya stops about2199); the outside fence runs x3350 and north z-3150. The switch at[1008,3664] requires the west/south route around the enclosure. Chasers also patrol outside; treating both as permanently confined was incorrect. Two slow navigation attempts incurred lethal damage, with no established new engine defect. First attempt archived in `build-port/reference/dryfield-water-east-failed/` (physical replay, live checkpoint, raw mesh); second reached west/south[-5090,4700] with12HP before death. No inventory healing is available (item8 is status cure).

Current recovery uses the same immutable102875 prefix and initial cards through `/tmp/pe2-water-west-20261103/control.lldb`, frozen binary `/tmp/pe2-movie-ring-final-20261103/parasite-eve-ii-pc`. Next use shorter deliberate input segments, verify yaw after hits, and reach the switch or defeat the outside Chaser. No new code changes this segment. Full goal remains active. GitHub tags/releases must not be deleted.

Follow-up combat attempt: after restoring102875 with full equality, running west85 immediately received23 damage and displacement; this invalidated the planned turn. Holding M93R PB aim/fire subsequently killed the second Chaser (200→-85) using18 rounds, while the first remained200. First then reached176 after magazine emptied; fresh R1 reload worked, another10 shots reduced it to46, but Aya died HP-3. Archived `dryfield-water-combat-failed/`. This confirms gunfire across the fence works; next attempt should shoot immediately from102875, preserving the initial23HP instead of running into the opening lunge. Current recovery debugger follows the unchanged102875 prefix again.

Successful combat branch: restored physical prefix103469, first Chaser10HP and second200HP, Aya12HP. R1 alone (`2048`) preserved current target; fresh Square was previously cycling to the other enemy. At103599 first Chaser-2HP; after fresh target acquisition and a second R1 edge, reload succeeded. At104477 second Chaser-25HP, Aya still12HP, battleRefs7 during death animation. Subsequent movement confirmed both ChasersHP0 and battleRefs6. No reward screen yet because the room still has six other battle references.

Reached switch normally at105942, Aya[1051,1,3862], facing north; CAP text says it is connected to the fence. Physical Cross confirmations started opening event. By106678 event0/mode0, timed phase3. Latest stop106778: Aya[942,131,3863],yaw2097, HP12/MP0, elapsed187/750; north is blocked by the wall, route must go around. Current owned LLDB84278/PID12333 with `/tmp/pe2-water-west-20261103/control.fifo`, record `controlled.pad`, pad_addr4309830688, frozen final STR binary/dSYM. Archive `dryfield-water-switch-operated/` contains full replay, live checkpoint, cards and switch screen; independent finite replay validation is being collected. Goal active, puzzle incomplete.

Independent finite replay completed successfully at106778 with full collected live/finite checkpoint equality; evidence `dryfield-water-switch-operated/finite.json` and `validation.txt`. No new engine defect established this segment.


### 2026-11-03 — Water Tower timed-run correction

Prior assumption that six refs meant six other enemies was wrong. Read-only task-list inspection after restoring109444 shows only two enemy tasks, both `_desertChaserTask`, both restored to200HP by START_RUN. Source actor_421600.c command handler explicitly resets HP, with WAIT_RESPAWN lifecycle. Thus earlier HP0 records prove temporary knockdowns, not permanent clearance; do not report the Water Tower Chasers as cleared. Ref count alone is not an enemy count here.

First timer expired normally (750), ending script returned event0/control, retry starts900. At109444 Aya[1128,129,3975],yaw2049,HP12, PB42 total/0loaded, elapsed35. Both Chasers watch at[4183,-4515] and[5223,1209]. A second exterior-route run died north of fence; deterministic restored retry corrected turns by inserting15 neutral samples before turning (otherwise turn rate during running differs). At110041 Aya[-5084,128,-4900],yaw2049,HP12. Old vehicle collision blocks north atz-4900; jog east40 then north25 reaches north boundary-5700. Continuing east triggers mapped view3, first Chaser's scripted entrance lunge; caught Aya around[1399,-5700],HP-3. `_actor421600WatchRunPlayerState` explicitly triggers entrance lunge for placed actor0 in mapped view3 and actor1 in mapped view8. This is a gameplay obstacle, not proof of port defect. Need dodge/interruption at camera change rather than hold a long straight input. Raw replay archived `dryfield-water-run-chaser-intercept/`.

Manual breakpoint arithmetic error (100 samples too high) caused FIFO wait at110383 while process reported running; guarded collect rejected read, no RAM data taken. SIGSTOP arrived normally; queued100neutral were consumed under original breakpoint110483, then playback continued. Later branch restored109444 and discarded that wait. Always compute end from sequence, never hand-sum. Current recovery prefix110270 from corrected route is being restored to inspect first lunge before impact. Goal active; puzzle unfinished. No new code fix proven this segment.

Restored corrected route110270: Aya[-1389,131,-5672],yaw1081,HP12; Chasers remain watching at their run placements. Advancing40 then20 runUp samples reaches110330: Aya[555,129,-5707],logicalview3, firstChaserstate3 at[3991,-4574]. Backstep/runDown40+neutral15 failed:110385 HP-3, Chaserthrowstate30. Source entrance lunge moves200/frame and catches via avoidance contact with8-press hold, initial damage is immediate. Retreating backward is too slow. Archive `dryfield-water-backstep-failed/` includes replay/live. Next safe branch restores110270 before triggering view3; M93R0loaded/PB42total, so preload before approach and test shooting/stagger interruption or perpendicular dodge. No RAM writes/target calls used. Runtime recovery again uses prefix110270 and the same frozen binary/dSYM.

Latest useful branch: from110270, Square8/R1alone120/neutral20 reloaded and shot first Chaser34HP before triggering view3. R1alone240/neutral15 at110673 reduced it166→-10 (knockdown20), left2loaded/PB24total. runUp185/neutral15 successfully passed first lunge area without damage:110873 Aya[4461,128,-3770],yaw829,HP12; firstHP0/state0, second200/watch32. Timer725/900. This is the new recovery prefix. Moving south triggered second lunge:110970 Aya[4311,-1745],logicalview8, second[4638,-1339]state3; reacting20R1 too late, death110990. Archive `dryfield-water-second-lunge-failed/`. Next interrupt/knock down second BEFORE moving into view8, as worked for first; reload2remaining before crossing. Only175timerframes left, so may need replay109444 and deliberately let safe switch-side timer expire once to raise next limit1050 (then repeat route with original42PB). Do not waste scarce PB on a run that will time out, because START_RUN resets enemyHP. Current owned replacement restores110873 from physical prefix. All gameplay via pad, LLDB read-only. Puzzle incomplete.

Final verified owned stop110873: debugger58319/PID50895, Aya[4461,128,-3770],yaw829,HP12. Independent finite replay full collected checkpoint equality passed; `dryfield-water-first-lunge-passed/` has replay/cards/live/finite/validation. Next avoid view8 until second is interrupted; consider safe timeout to1050 before repeating because current timer725/900. No engine code edits this turn.


### 2026-11-04 — Water Tower run completed; prepare for final arena

A successful physical branch raised retry limit to1050 by safely allowing second timeout at switch. At111740 timer35/1050, Aya[1128,3975],HP12,PB42total. Repeated west/north route and pre-shot both watching Chasers before their mapped camera triggers. First down112969, second down113642. Entered open east gate before timeout:113789 `runResult=2` (COMPLETED), elapsed1002/1050, Aya[1996,0,-270]. At114289 ending scene finished, Aya[1900,128,-270],yaw3072,HP12, event0, driverstate7/phase1 (WAIT_CHASERS). Independent finite replay full collected checkpoint equality passed: `dryfield-water-run-completed/` contains replay/cards/live/finite/validation.

Final arena is NOT complete: START_FINAL_BATTLE restores the two actors and requires exhausting shared eight-life pack. `_gActor421600RemainingLives` decrements on every defeat, and final respawn repeats until zero, then ROOM_MESSAGE_ACTOR_EVENT triggers falling-prop ending. battleRefs4 corresponds to four remaining pack lives here, not four extra actors. PB10total/8loaded and12HP were insufficient. Attempt to reach Water Tank warp from final arena via southern edge took9damage then died15damage; `dryfield-water-final-arena-failed/`. No proven engine defect.

Restored actual Water Tower arrival99297 (PB82,HP55,MP0,EXP1181), before intro/active battle, to prepare legal battle weapon switching. Full USE menu: Cross enters equipment grid; armor row is below weapon/ammo. Attachments are vertical below armor. Chose empty slot2, picker candidates GPS/PB/Tonfa/... and attached Tonfa146 to attachSlot2. It is now available in battle attachment UI1 (GPS UI0). M93R remains equipped, switched emptyHydra→PB20loaded/82total through weapon picker.

PE upgrade purchases restore full MP after `equipmentRecalculateMaxMp` (menu_actions.c). Tiny screenshot cost misreads led two rejected attempts; read-only table confirmed Pyro2=1250EXP, Healing2=1750, both unaffordable at1181. No bug: insufficient-EXP notice is correct. Actual successful purchase through menu was Combustion1 (ability1), cost750, not Necrosis as initially intended. State confirms levels[1,1,0,0,0,0,0,1,...], EXP431, MP42/42. Cast Healing1 normally outside battle: HP55→85, MP42→30. New canonical prepared checkpoint105815: Aya[5500,129,-5310],yaw3072,area20/state1/variant1,event0,ui0,HP85/MP30,EXP431, PB82/20loaded, Tonfa attachSlot2. `dryfield-water-prepared85/` has physical replay/live/cards; independent finite validation pending below.

After interruption original debugger handle disappeared, but owned PID59496 was live and blocked in FIFO; attached new LLDB41698 to same process instead of restarting. Confirmed state104873, resumed same physical recording. Later replayed successful old input100433→102875 from prepared105815; reached108257 same opening-end Aya[-700,-4500],HP85/MP30. Replaying old gunfight102875→104477 diverged with RNG/target timing: first dead, second still200, HP55, no loaded rounds/PB42total. Additional firing killed second but spent most ammo and took more damage. At110647 Aya[5248,130,-4101],HP12/MP30, first0/second0 (knocked down), PB~5total. Archived `dryfield-water-prepared-combat-spent/`. This is a failed tactical branch, not a new engine defect. Do not continue it with insufficient bullets.

Current recovery returns to prepared105815 with original82PB; new owned debugger67532 uses `/tmp/pe2-water-west-20261103/control.lldb` and frozen STR-fixed binary/dSYM. Next repeat intro2442samples (old successful replay100433:102875) and use Pyrokinesis1 plus gunfire to conserve bullets in first two defeats, with Healing available for recovery. Then complete timed run via proven1050 route and use attached Tonfa in final four-life arena. Do not blindly replay full old fights after changed preparation/RNG; validate target HP, shots and held state at short boundaries. Full game goal remains active, no GitHub tags/releases touched.

Prepared105815 independent finite replay passed full collected live/finite equality; restored owned67532/PID50583. Goal active.


### 2026-11-04 — Efficient Water Tower opening

Prepared85 branch replayed intro to108257 (Aya[-700,-4500],85HP/30MP). Triangle8/Right8/Cross8/neutral100 cast Pyro1: first Chaser200→60, no HP loss. Square8/neutral20/R1alone70/neutral20 finished it with6PB rounds. Target next with Square8/neutral25, Triangle8/Cross8/neutral120/R1alone90/neutral20: second down, Aya85HP/14MP, 70PBtotal/8loaded. This is much better than blind old fight replay. Navigated west/south to switch109589 without damage. Allowed750 then900 timeout safely and started1050 retry at115327 (timer35), preserving8lives pack decrements from two opening defeats.

Reached north pre-lunge116154, firstwatch200. Fired8remaining rounds→108HP, freshR1220 reloaded/finished first at116587 (timer647),11loaded. Ran185+neutral15 east; targeted second beforeview8, Pyro1 plus6shots finished second at117051. Aya[5065,128,-3848],yaw4094,85HP/6MP,5loaded, about47PBtotal; timer869/1050, first0/second0, remainingpack4. Tried south90 then west65 but arrivedz-1129, outside gate opening clearance; stoppedx3651 and timed out during following250neutral. Archive `dryfield-water-good-run-gate-edge/`. Source thresholds: first run Chaser appears at remainingLives>=4; second>=5.

Recovery prefix117051 restores before east gate approach, use south110 (not90) to getz~-500 before west into completion trigger. Next final arena has attached Tonfa2,85HP and substantially more PB than earlier failed12HP branch. Current replacement launched with same frozen binary and prefix117051. No new engine defect; goal active.

Efficient-run correction succeeded after restoring117051: south110/neutral15/left23/west70/neutral300 crossed open gate;117569 Aya[1900,128,-270],85HP/6MP, PB47total/5loaded, finalpack4. `dryfield-water-final85/` holds replay/live/cards. This supersedes failed gate-edge branch.

Arena test from same eastern position spent17 rounds without enemy HP change. After stepping south to[2010,1512], six rounds damaged both (first200→95, second200→154), but Aya took30HP. Central pole between eastern starting mark and west-side enemies is the likely blocker; no engine bug proven. Do not fire from original[1900,-270] line. Attachment weapon switching is confirmed: UI selected index was2(empty), causing earlier confirmations to do nothing; read gItemMenuSelectedAttachmentIndex, Left once→1 then Confirm equippedTonfa19 and reattachedM93R toslot2. TonfaR1 fresh40/neutral8 hits20HP; repeated swings hit first95→35 but received14damage, then R2trial hit second20 and received23. Current unhealthy test18HP archived `dryfield-water-final-pole-and-tonfa/`. Restore117569 healthy canonical85 and move south before any gunfire; wait until transition states6/7 become targetable39, then fire. Current replacement debugger8736 restoring same prefix; no code edits this segment.


### 2026-11-04 — WATER TOWER CLEARED, entered Water Tank

Restored healthy final85 checkpoint117569 and moved south before firing. The final arena's first two entrance/throw attacks cost30HP (85→55). Five rounds damaged both actors (first142,second160); initial empty R1 edge was ignored while hurt. Fresh Square reacquired second, fresh R1180 reloaded and killed it at118298; remainingpack3. Targeted first and killed it at118456; pack2. Waited140, then100 before acquisition to avoid transition7 invulnerability; five rounds left second54HP/downed20 at118804. First empty-R1 request occurred before ready, second freshR1 correctly reloaded and killed second at119114; pack1,55HP,17loaded. Last200HP took126damage and a23HP throw hit, then another38, then remaining36 finished at119657. Pack0 confirmed, Aya32HP. Final successful branch kept M93R throughout; Tonfa remains attached2 for later, no RAM writes.

Closing prop scene completed normally:120257 driverstate9(FINISHED), event0, refs0; result600EXP/400BP/32MP. Recovery2 collected via normal All;120761 ordinary control, EXP1031 (431+600), BP3164 (2764+400), HP32, MP38/42, PB2remaining, Shell10/Medkit1/Tonfa1/Recovery2item2qty1. Full physical replay + cards/live/finite/screens `dryfield-water-tower-cleared/`. SEVEN independent finite CLI expectations passed, plus FULL collected live/finite dictionary equality at120761. This proves complete room fight/ending/rewards, not just gate crossing. No new engine defect established in this segment.

Healed normally twice after battle (32→62→92HP;38→26→14MP). Wheel outside battle automatically defaultsHealing7; left fromHealing7 goesCombustion1 because it is now learned, so a misguided selection had no cast/effect and was correctedRight back toHealing7. Moved around central pole (x1000,0) via south, approached Water Tank hatch facingWest. Transition briefly had no player actor at122269/area21 (normal loading), then neutral300 completed arrival122569: stage2/area21/state1/view2/warp1/variant1, Aya[-2327,-11871,1143],yaw512,HP92MP14,EXP1031BP3164. Upper catwalk render correct, event0,refs0. `dryfield-water-tank-arrival/` has replay/live/cards/arrival image; independent finite validation pending below. Aya artifact66b4975d-37a3-44a7-9f73-ac43e34094d1 shows arrival.

Current only owned debugger8736/PID38661, stopped122569 at psyq_host305, pad_addr4309830688. Same frozen STR-fixed binary/dSYM, FIFO `/tmp/pe2-water-west-20261103/control.fifo`, record `controlled.pad`. No native save since earlier Dryfield phone fixture; full physical replay is preserved. Next Water Tank actions are in dryfield_water_tank.c (not_2): automatic path scene around[-656,-12065,2160], movie trigger[2512,-12064,720], mechanismCAP[1432,-12067,-17]. Return warp[-2449,-12128,640] facesNorth, avoid accidental exit. Goal active, whole game unfinished. No GH tags/releases touched.

Water Tank arrival122569 verified: seven independent finite CLI expectations passed, full collected live/finite equality passed, evidence `dryfield-water-tank-arrival/finite.json` and `validation.txt`. Current8736/PID38661 unchanged at122569. Goal remains active.


### 2026-11-04 — Kyle conversation, second STR movie, tank gate operated

Owned8736/PID38661 continued from verified Water Tank arrival122569. RunUp50/neutral180 along initial southeast heading automatically triggered path scene:122799 Aya[2530,-12000,610],view5,event1, Kyle walker/hands spawned correctly. Repeated physical Cross pages advanced conversation. At124287 no caption and record18 looked idle, but fresh Cross advanced to22 and rendered next Kyle line; this was waiting for confirmation, not an engine stall. Do not infer a bug solely from caption absence. Total scene CAP reached68;129531 event0, normal control, Aya[2412,-11870,1118],yaw1024,view3. Kyle scene updates objective14/storydialogue3 and saved area variants (see source).

Turned north/right23, walked16 then20 into automatic movie trigger.130190 RGB24 movie visible, event1/pending255, Aya[2436,-11998,830]. RGB555 export showed rainbow noise; correct `--rgb24` capture valid desert/tower clip. After1200neutral131390 movieFrame308/sceneFrame308, available0, black image; another600neutral advanced normally to EOF320, movieStep0, movieAtEnd1, movieReady0, event0/pending0. Thus no new ring stall; this movie further exercises the existing STR ring fix.131990 player[2600,-11869,-450],yaw512,normal control.

Turned left35 toWest and inspected mechanism with Cross. CAP text: lever says GATE. Another Cross started gate operation; neutral600 returned normal control132911. Read-only packed flags confirm: byte0x19=0x21 ⇒ WaterTower progress0x32=2(COMPLETE), Kyle scene0x33=1(SEEN); byte0x1b=0x10 ⇒ movie0x36=1(SEEN); byte0x2a=0x13 ⇒ mechanism0x55=3(TANK_OPERATED). Movie diagnostics step0/sceneFrame320/AtEnd1 preserved in `dryfield-water-tank-kyle-and-gate/diagnostic.json`. Full physical replay, live checkpoint, cards, image in same folder; independent finite verification pending below. No new code edits/engine bug established.

Current only owned8736/PID38661 stopped132911, Aya[2600,-11869,-450],yaw3024,stage2/area21/state1/view3/warp1/variant1,HP92/MP14,EXP1031BP3164, PB2/Shell10/Recovery2x1/Medkitx1, Tonfa attached2. FIFO/record unchanged `/tmp/pe2-water-west-20261103/`. Next return around tank's south catwalk to exit[-2449,-12128,640] facingNorth, then new saved WaterTower variant (scorpions) or east Breezeway. Need replenish ammunition at Douglas/garage and find a native phone save; no native save since earlier Dryfield phone fixture. Room6 now savedvariant2 after Kyle talk. Whole-game goal remains active. No GH tags/releases touched.

Water Tank Kyle/movie/gate132911 verified: seven independent finite CLI expectations passed and full collected live/finite equality passed. Evidence `dryfield-water-tank-kyle-and-gate/finite.json` and `validation.txt`. Owned8736/PID38661 remains stopped132911; goal active.


### 2026-11-04 — post-Kyle encounters and new native Gas Station save

Continued owned debugger8736/PID38661 through153159 using physical FIFO pad input only. Exited tank via south catwalk; five Scorpions in WaterTower variant3 defeated with Tonfa, reward100EXP/40BP/5MP. Breezeway variant1 mandatory Desert Chaser defeated using two Pyro casts, Tonfa and final2PB. Reward75EXP/50BP/4MP and MPBoost1 collected. Used Recovery2 and MPBoost1 normally: HP19→105, MP7→37. Douglas intercom instructs garage route around trailer; no FactoryKey or BottlecapMagnet obtained. Returned through Tower, Room6, Balcony, ParkingLot, MainStreet and GasStation. Six balcony Scorpions bypassed without damage. Room6 TV CAP needed all pages closed before movement; no engine bug established.

At153159 native phone conversation with Baldwin about Kyle completed; selected existing GasStation save then explicitly Yes on overwrite. Card SHA256 changed from ed668f357568f6cdbd5b95f0b4f1636a90481e5684132556b8c7768944ab0128 to 3b860f22028bce2cb6292de9c2554e7adb514bb02f47866db5ef0e2380aaef0c. Ordinary control event0/pending0, area1, HP105 MP37 EXP1206 BP3254. M93R empty/no PB; Tonfa attached2, Shell10, Medkit1. Evidence build-port/reference/dryfield-after-kyle-native-save contains full replay153159, live checkpoint, screenshot, initial and saved cards. Independent finite replay launched; validation pending, do not yet claim replay equality or saved-load verification. Next garage Douglas resupply. Same live8736 remains stopped153159. No code fixes in this segment, no GitHub tags/releases touched. Whole-game goal active.

Native post-Kyle save153159 independently verified: all seven finite CLI expectations pass, FULL collected live/finite equality true, and saved-card bytes identical. validation.txt in dryfield-after-kyle-native-save. Continue/load of new native save still not independently checked.

Continued live to160114. Returned GasStation→MainStreet→Driveway25 without damage, HP105 MP37. Factory rear door around[-3680,480] invokes normal story refusal CAP: If this is the back door / I wonder where the front door is. Read-only source dryfield_driveway_resolve.inc.c refuses Factory while GAME_FLAG_030==1; do not assume old route remains accessible after Kyle. Sign farther from door initially intercepted Cross. Actual door approached[-3592,454],yaw3056; current160114 still CAPpending129 (last line), ordinary eventState0 alone does not prove caption closed. Next close caption then resolve front route/key puzzle via Breezeway, magnet and grate; no engine bug established, no RAM writes. Full current physical replay/live in dryfield-after-kyle-driveway. Same owned8736/PID38661 stopped160114, FIFO/record unchanged. Goal active, no GitHub tags/releases touched.


### 2026-11-04 — route audit after factory refusal; resource loss retained honestly

Live8736/PID38661 advanced160114→167618. Closed driveway refusal, returned MainStreet. Navigation along motel wall entered two-enemy combat; Aya105→12HP. Exit to Parking triggered ordinary flee result BP-10,MP+1;164943 Parking15 ordinarycontrol HP12MP38. Three physical Healing casts restored102HP/2MP at165621. Traversed parking toward Saloon, seven combat refs, took36damage overall; current167618 HP66MP2, emptyM93R, Tonfaattached2. Saloonfront Cross displays This door is closed! (pending129); NOT a successful transition. Earlier file /tmp/pe2-saloon-return-live.json is actually Parking15, do not interpret filename as location. No new native save; canonical new GasStation card remains105HP37MP and safely archived.

Source parking_lot_event_msg.inc.c requires SaloonKey0x110 absent from collected list. G&RKitchen connects directly WaterTower20 (kitchen door[96,2784]) and Saloon18; therefore next route should return Balcony→Room6→clearedTower then kitchen, rather than repeatedly trying locked parking/front or driveway/rear doors. Walkthrough confirms BottlecapMagnet on G&RKitchen fridge: https://www.neoseeker.com/parasiteeve2/faqs/53224-parasite-eve-ii-g.html . Need obtain magnet then Breezeway retrieval puzzle for FactoryKey. CurrentParking[-6435,2,-655],yaw4080, pendingCAP129, probably close last page before movement. Rawinput/live/image archived dryfield-magnet-route-audit. No new engine defect proven; damage/navigation errors are gameplay. Some manually computed boundaries earlier differed by2 from command sums; hence ALWAYS compute sum programmatically and inspect location/yaw/HP after short sequences in enemy rooms. Goal active, no tags/releases touched.

CAP text helper tooling investigated in /tmp/pe2-cap-inspect-venv (Pillow installed only there). Correct legacy asset names dryfield_motel_lobby_bundle and dryfield_saloon_g_r_bundle, but cap_text.py fails because legacy atlas PNGs assets/USA/pe2img/*dialogue_0_atlas.png absent after asset migration; no repo changes to workaround. Use runtime captions/source or new asset decoder instead.


### 2026-11-04 — Game Over and Continue exposes stale battle result

Current owned8736/PID38661 stopped173796. Failed parking traversal: HP66→16, equippedTonfa through battle attachment, hit Chaser200→138 but Aya7HP; retreat to stairs failed and death HP-8 at169908. GameOver displayed170608, Start returned title171624, Start menu171832 defaultContinue, Cross172080 selects native GasStation(2) TIME1:38 EXP1206 BP3254. Cross172688 then500neutral173188 player actor unavailable, HP105 area1; screenshot reveals BATTLE RESULT on black background, EXP0 BP-10 MP+1, totalsBP3244MP38. Cross+600neutral173796 returned normal GasStation1/state1/view6/warp2/variant1, HP105MP38BP3244. Expected native savedMP37BP3254 (verified prior card unchanged). Thus stale flee result applied on Continue after GameOver, new reproducible runtime defect candidate; must independently replay and root-cause before patching. gSceneCombatState after result is reset (phase0/refs0/rewards0), so inspect lifecycle before loaded result. No production fix yet.

Full original-from-initial-save replay through173796 and live are in game-over-stale-battle-result/. Canonical new native card remains archived dryfield-after-kyle-native-save/saved-cards (105HP37MP3254BP). Same FIFO/runtime/record as before. Resume defect investigation now before returning to gameplay; goal active. No GH tags/releases touched.

Independent full replay for stale GameOver result launched in exec session42370, output game-over-stale-battle-result/finite.json, log /tmp/pe2-game-over-finite.log, disposable cards /tmp/pe2-game-over-finite-cards. Poll SAME handle; do not restart on timeout. Current live remains173796. Root-cause entry: src/gameplay/area_entry.c _sceneBattleResultTask spawns escape panel and applies loaded rewards; inspect its caller and GameOver/title reset lifecycle. No patch made yet.


### 2026-11-04 — FIXED stale combat after Game Over → Continue

Original full replay through173796 independently passes5 CLI checks and complete live/finite dictionary equality; confirms wrong loadedMP38/BP3244. Root cause: scene combat globals survive native gameplay overlay reload. Fresh-session _gameFlowHandOffSessionLoad queues gameFlowReloadSessionTask, whose prepare phase calls sceneQueueBattleEscapeResult BEFORE area load_screen resets combat. Thus previous engaged battle is treated as escape against newly restored player save.

Fix src/main/gameflow.c: under __psyz clear entire gSceneCombatState once gameplay bootstrap CD work has drained and immediately before handing fresh session to reload. Ordinary area transitions do not use this fresh-session handoff, so escape results remain intact there. Existing sceneResetCombatState later derives difficulty and encounter defaults as before. Original PS1 overlay path unchanged. Native build passed; CTest actor_walk_gap_test,gte_compat_test,cd_ring_test,cd_pump_test all4 pass; git diff --check clean.

Fixed full physical replay (same input, stop173188 BEFORE workaround confirmation) passes7 CLI checks: area1, HP105, MP37, BP3254, event0, pending0, refs0. All saved playerStatus/BP/weaponLoads/carried/inventoryRows/collected equal native pre-death checkpoint, and output card bytes equal archived original post-Kyle save. Evidence game-over-stale-battle-result/fixed.json, validation-fixed.txt, reload-before-confirm.pad, gameflow-fixed.c. Fix frozen binary+dSYM /tmp/pe2-game-over-fix-20261104/parasite-eve-ii-pc ready for subsequent live play. Old owned8736 still runs OLD binary and is stopped173796 with contaminated in-memoryBP3244MP38; never save that state. Next start fixed runtime from archived saved-cards via normal Continue, equipTonfa and attachMedkit before entering enemies, proceed to kitchen via clearedTower. No tags/releases/commits. Goal active.


### 2026-11-04 — fixed runtime resumed; SALOON KEY collected

Retired old debugger8736/PID38661 only after launching fixed frozen runtime. New owned LLDB71296/PID64104 stopped19655, binary/dSYM /tmp/pe2-game-over-fix-20261104/parasite-eve-ii-pc; pad_addr4309830688. FIFO/control/cards/record /tmp/pe2-kitchen-fixed-20261104/. New replay starts from post-Kyle GasStation(2) native save, prefix2492 verified HP105MP37BP3254; old initial Dryfield cards MUST NOT be used for this new replay. EquippedTonfa19 via inventory and attachedMedkit8 toslot1 (replacedGPS64); M93Rempty attached2. Normal MainStreet escape and Parking escape each appliedBP-10/MP+1, confirming fresh-session fix leaves ordinary escape results. ParkingChaser threw Aya105→75, escaped via stairs successfully. Balcony no additional damage. Room6 Healing75→105,MP39→27.

Room6 reliable geometry: bed spansX200..2523,Z2164..3836; from frontdoor go around east side of bed toZ4184, then west toX1695 and south toZ6242 through bathroom gapX1173..2183. South toZ6955 then westwalk toX~700, Cross exits; earlier X870 was too far despite visible gate. Read-only collision export /tmp/pe2-room6-grid.json (158vertices/56faces). No RAM writes. Tower clear persists0refs. Kitchen rear door ALSO requiresSaloonKey0x110 (water_tower_event_msg.inc.c), previous assumption of free access corrected. Both kitchen and saloon doors locked without key.

Returned Tank21: Tower ladder hotspot[-2400,112] faceWest. Arrival[-2327,-11871,1143],yaw512. Run50/neutral40/right12/east65/neutral40 to[812,-11870,2373]; right15/run23 to[1290,-11871,1834]. FaceNW right20 (yaw2560),Cross climbs ladder to[820,-16270,884],view4. RunNW93/neutral40/Cross inspects corpse[-1170,-16397,-1106]. FiveCross pages and2 more confirmations collect SaloonKey272 (0x110) andRecovery1 item1qty1. Current19655 ordinary control event0/pending0; HP105MP27EXP1206BP3234, Tonfa equipped, Medkitattached1,M93Remptyattached2, no native save sinceGasStation(2).

Evidence dryfield-saloon-key/ contains new replay through19655, live and initial-cards(post-Kyle save). Independent finite launched exec91221, output finite.json/log /tmp/pe2-saloon-key-finite.log/disposablecards /tmp/pe2-saloon-key-finite-cards; poll same handle, validation pending. Next climb down (top ladder[1255,1247], faceSE~512), go around south tank catwalk and exit, returnKitchen now with key, obtain fridgeMagnet then BreezewayFactoryKey puzzle. Whole-game goal active, no GH tags/releases or commits touched.

SaloonKey19655 verified: six CLI expectations pass, full live/finite collected dictionary equality passes; explicit SaloonKey272 and Recovery1qty1 assertions pass. Evidence dryfield-saloon-key/validation.txt. Same live71296 remains stopped19655.


### 2026-11-04 — kitchen unlock CRASH, live preserved

Continued owned71296/PID64104 from19655. That checkpoint had CAP residual corpse closing text despite event0/pending0; first movement batch ignored. Cross closed Not that I am one to talk at20383, then SErun85/Cross descends to[1868,-11870,1740]21063. Around south catwalk, exit22141 Tower[-2100,129,170]. East205/north158/west222 approached kitchen; corrected at23073[-3904,-4964], then left22/east30/neutral40/right23/north20/neutral40/Cross8/neutral120. At pad23317 CRASH before requested boundary23376.

EXC_BAD_ACCESS addr0x1ad in worldCoordUpdateRoomLightsTask/_worldCoordGetRoomLights world_coords.c1926, roomLighting0x1ad. Crucially live location corrupted to{stage2,area0,roomState0,view0,warp0,variant1}. pe2-transition callback capActionPromptExitTask, entryMode0, hold1, no combat refs. Stale/invalid transition location after kitchen unlock is likely upstream; do NOT merely nullguard lighting or mask indices. Evidence kitchen-unlock-crash/replay.pad (record flush ends23317), initial-cards(post-Kyle), crash.vram, diagnostic.txt. Same fixed binary/dSYM /tmp/pe2-game-over-fix-20261104, live session71296 stopped at exception (NOT ordinary pad boundary); do not send advance blindly. Need independently reproduce then inspect CAP room-event gate staging/location decode. No new patch yet. Goal active, no native save sinceGasStation(2), no GH changes.

Crash root-cause evidence read-only: `_gRoomEventMsg` for dayTower contains correct {areaId19,warp2,roomState1,field_4=1,query0,flag477}. But gRoomEventTaskDesc.callback resolves0x1004771a0 `roomEventTask`, image lookup CompileUnit build-port/variants/pe_var_dryfield_factory__factory.c! Only one linked roomEventTask symbol. Shared callback reads factory-local static destination(empty), producingarea0. Generic gRoomEventTaskDesc/gRoomEventReq/gRoomEventActive/roomEventTask names need coherent per-overlay binding, including cross-TU dayTower descriptor in_2 and gate/task in.c; generated renames alone leave wrong public callback. Investigate cmake/overlay_renames.cmake and shared/room/room_events.h binding before patch. No nullguard workaround.

Kitchen crash independently reproduced by finite replay (exec64242 terminal exit1), sameEXC_BAD_ACCESS/world_coords1926/input23317/area0. validation-old.txt stored. Live71296 remains at exception, root cause callback symbol collision identified, fix still pending.


### 2026-11-04 — FIXED Tower/Kitchen callback collision; MAGNET obtained

Fix cmake/game.cmake propagates generated definition renames to sibling references in day/night WaterTower TUs: each gate now references its own _2 descriptor, each descriptor its own roomEventTask; daytime _2 message/sound table refers daytime callbacks; daytime request storage isolated from factory. No lighting/null/index guard workaround. Build and4existing CTests pass, diffcheck passes. Frozen binary+dSYM /tmp/pe2-kitchen-unlock-fix-20261104/parasite-eve-ii-pc. Night binding compiled/inspected but no night gameplay proof.

Old replay crashed23317. Fixed replay plus600neutral reached23917 normal unlock caption Opened the door with Saloon Key, not Kitchen yet. Original CLI expectedarea19 prematurely and exited1; keep output kitchen-unlock-crash/fixed.json. Full live/finite equality at23917 proven (validation-fixed-prefix.txt). Cross+400neutral24325 enters Kitchen19/state1/view2/warp2/variant1 at[0,128,2512],105HP27MP. Five independent finiteCLI expectations pass plusFULL live/finite equality, kitchen-unlock-fixed/finite.json,validation.txt.

New owned LLDB48514/PID8005 stopped26762, FIFO/cards/prefix/record/control /tmp/pe2-kitchen-unlock-live-20261104/. pad_addr4309830688, breakpoint1 psyq_host305. Replay initial cards are post-Kyle GasStation2 (same as saloon-key), not originalDryfieldSave. Old71296/PID64104 remains crashed until explicitly retired below.

Kitchen variant1 has3MindSucklers (helper does not capture _actor01500Task yet, refs3 accurate). North105run to[0,1135] engages, Square then10Tonfa32/6 killedone; freshSquare+12swings killed remainingtwo25318. NoHP/MP consumed:105HP27MP. Result36EXP108BP6MP ⇒1242EXP3342BP33MP. LootKeyChain item65qty1 collected, battleResetPending1 normal after victory. FridgeCAP1 at[416,-2400] approached[291,-2001], inspectednorth. FourCross + morepageclosing collectedBottlecapMagnet283(0x11b). TwoCircle closes caption fully26762: ordinarycontrol pending0/mode0, stage2area19,HP105MP33EXP1242BP3342, Tonfaequipped,Medkitattached1,M93Remptyattached2,Recovery1qty1. No native save sinceGasStation2.

Evidence dryfield-bottlecap-magnet/ replay26762/live/initial-cards. Independent finite verification launched next; next gameplay exit south KitchenWaterTower at[96,2784], faceSouth, then Breezeway to retrieveFactoryKey usingMagnet. No more code edits this segment. Goal active, no GH tags/releases/commits.

Old crashed71296/PID64104 retired after verified fixed Kitchen arrival and Magnet collection. Only live48514/PID8005 remains. Magnet finite job exec66288; poll samehandle.

Magnet26762 verified: sevenCLI expectations andFULL live/finite equality pass; explicitMagnet283/KeyChain65 assertions pass. Job66288 exited0. Fixed descriptor read-only pointsPE_rooms_dryfield_water_tower_dryfield_water_tower_roomEventTask (0x100242bf0), no factorycallback. Current48514 remains26762.


### 2026-11-04 — FACTORY KEY obtained; Breezeway unlock same callback collision

Continued live48514/PID8005 from26762. Kitchenexit south→Tower27338[-2437,-5662], East220/north? actual route physical right23/east220/left23/south200/right23/Cross entersBreezeway28265. East300 reachesFactorydoor[17701,1571], locked. ClosedCAP withtwoCircle, turnedSouthleft23/run52 to[17701,3440]29534; Cross starts key retrieval model event. Cursorcenter must moveDown12 toY24 beforeCross opensExamine/UseItem. Down1→UseItem, Magnet selectedfirstCross, close UsednoticeCross. Cursor(0,24) thenUpRight15/neutral20 gives(22,1); UpRight42/neutral20/Right12/neutral40 reaches(106,-59), line target success30188. CrosscollectFactoryKey277, closeCross30296→30454 ordinarycontrol[17700,129,3440],yaw56. HP105MP33EXP1242BP3342 unchanged. Magnet remains283, key277 collected. FactoryKey evidence dryfield-factory-key/replay.pad through30454/live.json; initialcards samepost-KyleGasStation2.

TurnNorthright45/run47/neutral40/Left23/Cross attemptsFactorydoor. CRASH atpad30674 beforetarget30767: EXC_BAD_ACCESS0x1ad world_coords1926, locationstage2/area0/roomState0, callbackcapPlaybackTask. gRoomEventTaskDesc.callback again0x1004771a0 factoryroomEventTask. Breezeway.c hasrenamedcallback but_2 descriptor referencedpubliccallback; same defect asTower. Oldlive48514 remains atEXCEPTION; do not advance blindly. Rawrecord build-port/reference/breezeway-unlock-crash/replay.pad (30674samples).

Expanded cmake/game.cmake split-reference fix toBreezeway, plus identical remaining cross-TU descriptors foundbysourceaudit: nightDilapidatedHouse,nightMotelBalcony,nightParkingLot,ShelterB2NorthMaintenanceWalkway. Existinggenerateddescriptorrenames propagatedtocfile; callbackrenamefromc propagatedto_2. Breezeway formerlypublicdescriptor now uniquelynamedin_2 too. Buildinprogress exec30341 /tmp/pe2-breezeway-fix-build.log; CMakefile editedduringbuild toaddauditrooms, so AFTERcurrentbuildfinishes rerun cmakebuild toinclude latestchanges. No runtimeproof oflaterlocationsyet. Fixedreplay pending in breezeway-unlock-crash/fixed-replay.pad through31274; disposableinitialcards prepared /tmp/pe2-breezeway-fixed-finite-cards. Need finite replay finalbinary, initiallyexpectCAPwaitinginarea22, thenCross normaltoFactory23. No native save sinceGasStation2. Goalactive, no GH changes.

FactoryKey30454 independently verified:5CLI expectations pass, FULL live/finite equality passes, FactoryKey277 retainedMagnet283 explicitassertions. OldBreezeway unlockcrash independently reproduced at30674 (job18118exit1), validation-old.txt. Finalexpanded build rerun82144 exited0 (firstintermediatebuild30341failedundefinedfourdescriptorsbecauseCMakeeditedduringbuild; finalconfigresolvesall). Source/compilecommands audit confirms descriptor AND callback names consistentacrossbothTUs for7splitrooms. FourCTestspass, diffcheckclean. Finalbinary+dSYM frozen /tmp/pe2-room-event-fix-20261104/parasite-eve-ii-pc. Fixedfinite replaythrough31274 runningexec11331, /tmp/pe2-breezeway-fixed-finite.log, breezeway-unlock-crash/fixed.json, cards /tmp/pe2-breezeway-fixed-finite-cards. NewliveLLDBlaunch36877 replayingsameprefix31274, controlfolder /tmp/pe2-factory-unlock-live-20261104. Pollsamehandles. Old48514 stillcrashed untilnewverified. NeedCrossunlockcaptionthenverifyactualFactory23arrival; do notclaimarrivalfromCAPalone.

FinalBreezewayfix verified atprefix31274:3CLI expectations and full live/finite equality pass, normalunlockCAPinsteadcrash. NewliveLLDB36877/PID36857, /tmp/pe2-factory-unlock-live-20261104 FIFO/cards/prefix/record/control; frozenbinary+dSYM /tmp/pe2-room-event-fix-20261104/parasite-eve-ii-pc; pad_addr4309830688. Cross8/neutral400 entersFACTORY31682:stage2area23/state2/view7/warp2/variant1,root[642,130,7493],normalcontrolpending0,event0,HP105MP33EXP1242BP3342,Tonfaequipped,Medkitattached1,M93Remptyattached2,FactoryKey277+Magnet283 retained. Archive breezeway-unlock-fixed/live/replay31682. Independentfinite launched next. Next garage eastdoor[5456,7056] via northsidecar/lift geometry; prior garageaccessflags preserved. No native save sinceGasStation2. Goalactive. Oldcrashed48514/PID8005 canretireafterfixedarrival verified. NoGHchanges.

Oldcrashed48514/PID8005 retired afternewliveFactoryarrival. Onlycurrent36877/PID36857. Factoryarrivalfiniteexec45795 running; pollsamehandle. SourceFactoryarrivalwarp2facesEast1024; garagedoor[5456,7056]faceEast. Canroute via northsidecar: north toZ~3500, east toX~5400, south toZ~7000. Preserveexistinglift/shutterflags, inspectcollisionbeforenamingbug.

Factoryarrival31682 verified:6CLI expectations and FULL live/finite dictionary equality passed; key277 retained. Job45795exit0. Current36877/PID36857stopped31682.


### 2026-11-04 — Garage cleared, Douglas shop and Shelter conversation

Continued live36877/PID36857 from31682. Factory car route via westaisle/northside toGarage33201:area24/state1/view2/warp1/variant2,[853,130,2741]. Variant2fiveMindSucklers, notDouglas. TonfaSquare+freshR1 repeated32/6: refs5→3→1→0 at36114, HP105→81,MP33unchanged. Result36442 reward60EXP180BP; MP33→42cap,EXP1302BP3522. Healing restored105HP costs12MP→30. No battleloot. Southgarageexit toJunkYard26at37167 allowedafterKylescene, nooldWhereAreYouGoingrefusal.

JunkYard east path initiallyblockedat[10264,324]; south80thenEast320 to[20910,3126], east30/north42+closerwalk8/Cross entersTrailer27/state1/view6/warp2/variant1 at39151,[4870,-900],event1. IntroDouglasguncollectionconversation closes41471. ToordinaryDouglasinteractionwalkNW25 then45to[4198,-1572],Cross→YouNeedSomething/Cross→choiceShowMeYourGuns(default)/TellMeAboutShelter. Default→shop at42399. AmmoDown1,9mmPB50cost30, CrossPurchase thenquantityRight3 selects4packs, Cross42868 bought200PBfor120BP:3522→3402. Circle2closes43044ordinarycontrol. Tonfastillequipped,emptyM93Rattached2; PB200loose(notyetloaded),Medkitattached1.

ReinteractedDouglas, selectedTellMeAboutShelterDown1; firststoryscene43371→48535, manyphysicalCrosspages, alladvancenormally. Final48535event0pending0ordinarycontrol inTrailer27,HP105MP30EXP1302BP3402,PB200,Recovery1qty1,Medkit1,Shell10,Tonfa1,KeyChain65qty1. Source _dryfieldTrailerCoachStartFirstStoryConversation commitsobjective15/sceneEvent6/Drivewayprogress1/companionschedule1. NoMonkeyWrenchyet; nextconversationmayadvanceprogress3 orwrenchrequest. PhoneCAProomcommand14 likelytrigger[160,-656] (inspectbeforeclaimsave). No nativesavesinceGasStation2; preservearchive.

Evidence dryfield-douglas-resupplied/replay48535/live/initial-cards(postKyle). Independentfinite launchednext. Currentonlyowned36877/PID36857stopped48535, frozen /tmp/pe2-room-event-fix-20261104/parasite-eve-ii-pc,dSYM,FIFO/cards/record/control /tmp/pe2-factory-unlock-live-20261104. Goalactive,noGHtags/releases/commits. Noenginebugfoundthissegment.

Resupplied finite runningexec96160, /tmp/pe2-douglas-resupplied-finite.log, outputdryfield-douglas-resupplied/finite.json; pollsamehandle. IMPORTANT correction: roomcommand14 is STORY SCENE handler, NOT phone (see lines2221+); do notwalkto[160,-656]assumingtelephone. Telephonehelper exists butactualCAP/savehotspotunverified. No native save thisturn. Current36877stopped48535.

Douglasresupplied48535 verified:7CLI checks and FULL live/finite dictionary equality passed; PB200explicitassertionpassed. Job96160exit0. Same36877/PID36857remainsstopped48535.


### 2026-11-04 — second Douglas conversation, Wire Rope and Junk Yard ambush

Same36877/PID36857 continued48535→57500. Returned nearDouglas, choseotherconversation; secondstoryended andextraCrossreopenedtopicmenu49745. EnteredshopthenCircleexit50177ordinarycontrol. Read-onlypackedflags verifiedTrailerCoachprogress0x28=3,Driveway0x3a=1,wrenchrequest0x4f=0. Fullmenu equippedM93R2, automaticload20PB/reserve180(total200),Tonfaattached2. ExitTrailer via[1536,-784],faceSouth, requiredwestcloserapproach;51566JunkYard26variant2root[21921,129,1639],4Scorpions68HP.

FollowedFlintwest. Eastenddogscriptinterruptedturnbatch, resultingSouthheadingat[21455,4070]; correctedWest400→[7001,4432]. ForkliftblocksWestat[4236,4466]; routeNorth40toZ2933thenWest95→[1213,2933]. MistakenSouthwestpileCAPat[931,4195] notrope. Read-onlytasklistlocated dryfieldJunkYardWireRopeTask root[1745,0,280],placeKey7,workType276. RopeCAP6hotspot[1744,351]. North98reached[1299,469] andscriptedScorpionambushactivated. Earlyinputsignoredwhileknockdown, notenginebug.

M93R8PBspentonly20damage againstarmoredScorpions; totalPB200→192. Aya105→75→65. Startwhilehurtignoredfirst; retryopensattachment. UsedMedkit8 (curesstatus,NOT HPheal; HPremained65thendamage55), thenRight1→Tonfaattachment,confirm. TwelveTonfaswings(32/6)distributedhits27/68/27/16butAya23HP. Healing7normal23→53(cost12MP30→18),thenPyro0cost8kills2weakscorps; got10damage→43,MP10. FreshSquare/Triangle/CrosssecondPyrocost8 killed16HPscorp; received7damage→36,MP2. Last68scorpionfreshSquare+10Tonfaswings→6HP, Aya35. TwoextraR1kills; battleclear56470EXP+80=1382,BP+32=3434,MP+4=6,HP35. NoammoduringTonfa/PEportion.

Ropeat[1745,280] inspectedCross:coilofrope/useatwell captions, confirmYesthenObtained. CollectedID276(0x114)at56950. ClosednoticeandopenedfullmenuRecovery1(index1,rowitem1), commandpersistedMove1; UpselectUse thenCross consumedRecovery1, HP35→85(+50). Startclosed57500ordinarycontrolui0/pending0;HP85MP6EXP1382BP3434,Tonfaequipped,M93Rattached2loaded12PB+reserve180(total192),Shell10,GPS64,KeyChain65. MedkitandRecovery1consumed, nopotionsleft. WireRope276,FactoryKey277,Magnet283 retained. FourScorpsdead, refs0. Noenginebugproven.

Archive dryfield-wire-rope/replay57500/live/initialcards(postKyleGasStation2). Independentfinite launchednext. Next useRopeatDriveway wellregion[-1504,2400], viaGarage→Factory→Driveway; optionallyrecoverMP/savebeforeunderground. WrenchnotyetrequireduntilWarehouseinspect. No native savesinceGasStation2, noGHtags/releases/commits. Goalactive.

WireRopefiniteexec90281running, log/tmp/pe2-wire-rope-finite.log, outputdryfield-wire-rope/finite.json; pollsamehandle. Current36877/PID36857stillstopped57500, samefrozenruntime/controlfolder. Validationpending; donotclaimfullcheckpointcomparisonyet.


WireRope57500 verification complete: 7 CLI checks, full live/finite dictionary equality and explicit collected276 assertion passed; validation.txt archived. Same live36877/PID36857 continued to60665, escaped Garage24 variant3 three enemies via westFactorydoor. Hurt repeatedly interrupted turning, HP85→5; no new engine fault proven. Escape result required Cross; Factory23/state2/warp3/view6/variant1 arrived[5445,128,6866],yaw3072, HP5 MP7 EXP1382, WireRope276 retained. Replay/live archived dryfield-factory-return. Needs healing before further combat; no native save sinceGasStation2. Same frozenruntime/controlfolder. No GH changes. Goal active.


### 2026-11-04 — Wire Rope used, Water Hole entered
Same live36877/PID36857 continued60665→64213. Factory route west/north around machinery: [3477,1169], East49 to[5281,1103], Cross unlocked Drivewaydoor. Closedcaption thenCross, arrival61964 Driveway25/state1/variant2[-3400,600],HP5MP7. East52/South27 to[-1458,1494], CrosswellCAP severalpages; ordinarycontrol62978. Start→Down(KeyItem)→Cross, Ropefirstrow→CrossUse→Cross63153/63311. Usednotice, closeCross: roomState2, event1; rope276removedby63719. TwofurtherCrosspages advanced/enteredWaterHole32 at64213, state2/view3/warp1/variant1, normalcontrol event0 pending0, HP5MP7EXP1382BP3424. Eight1HPbatsrefs8, phase0 waiting, root[7400,128,-1350]. No damage thissegment/no newenginebug. Archive dryfield-rope-used/replay64213/live/initialcards. Independentfinite session9383 running, log/tmp/pe2-rope-used-finite.log, outputarchive/finite.json; pollsamehandle, compareFULLdict andassert276absent. Currentonlyownedlive36877stopped64213, samefrozenruntime/controlfolder. Needheal urgently beforebatfight; no nativesavesinceGasStation2. Goalactive. No GH changes.


Rope-used64213 finite session9383 finished exit0:5CLI, full live/finite dict equality and276absent assertion passed, validation.txt archived. Livecontinued→69557: WaterHoleturnRight46/Cross returnsDriveway64497 withoutdamage. Drivewaynorthblockednearwell; turnedSouth95thenWest170 reachedMainStreetexit[-9697,-1351],Cross65531 MainStreet2variant3 refs2phase0. North300fromeastwall→[-1371,-2286],North29/East24/Cross66486 GasStation1variant1 safeHP5MP7. GeneralStoredoor[2657,-331] approach[2893,-583]Cross producedJackCactuscaption, noentry; nothealingyet. Phone[4384,-528]East38,faceSouthCross68007; PiercecallandphysicalCrosspages→save. DownselectedNewBlock; CrosscreateYes; SaveComplete69449. Closednotice69557. Newnativecards+replay+live archived dryfield-gas-station-3-save; initialcards preservepostKylebeforethisnewsave. Current36877/PID36857 stopped69557, samefrozenruntime/controlfolder,HP5MP7EXP1382BP3424, Tonfaequipped, M93Rattached2loaded12+180reserve. Needrecovery/MP items, noenginebugproven. Goalactive,noGHchanges.


### 2026-11-04 — recovered95HP and returnedWaterHole
Same live36877 continued69557. GeneralStoredoor verified locked by sharedroomvariant flag0x3b, cannotopenfromGasStation. FoundaffordablePEupgrade: fullmenuStart→PE(Pyrodefault)CrossStrengthen/CrossYes at69858 Pyrokinesislevel2,EXP1382→132(1250spent),MP7→43/max43. CloseStart→Triangle initiallyHealingselected; LeftincorrectlyselectedCombustion1(unusableoutsidebattle,notspent), RightreturnsHealing7. Cross70496HP5→35MP43→31. TwomoreTriangle/Crosscasts71118HP95MP7. Archived dryfield-healed95:5CLI expectations andFULLlive/finiteequality passed, validation.txt. NativecardsstillbeforeupgradeGasStation3-save, replayhasnative-saveactions. Noenginebug.
ReturnedviaGasStationwestgate72009MainStreet, South325thenEast34/South13/Cross73044Driveway, East170/South78/East39/South18/Cross73796WaterHole32state2variant1normalcontrolHP95MP7. Eight1HPbatsphase0waiting. StartfullmenuUse→Down3M93Rattachment→CrossExchange→Cross equippedgun; current74146verification shows weaponSTILL19Tonfa, ui0; Exchange didNOTequipgun yet. Next inspectordinaryEquipflow, do notclaimgunready. Sameowned36877/PID36857,frozenruntime/controlfolder. Goalactive,noGHchanges.


### 2026-11-04 — WaterHole bats in progress
Same36877 continued74146→77661. ActualgunEquiprequiresUseweaponTonfa(toprow)Cross→SelectWeaponM93RdefaultCross; equipsweapon2 confirmed74547. PreviousExchangeattachmentwasnotEquip. East70fromwellreached[9668,0,-1154], battlephase1. First5shotsmissedperchbats; lateragitatedall8. Circle/Rightturn/runmovedback[8612,-1601]. First12clipspentkills3, refs5,HP89. BatsHOLDPLAYER: state6/mode2 orstate1/mode2 withbat.holdingPlayer1. Reload/Start/turnignoredwhileheld, notconfirmedportbug. NeededrapidalternatingCross/Right/Circle/Left(twoframesperbutton),96samplesreleasedfirsthold76454. FreshR1reload succeeded76641 clip20HP57. Subsequentbatchcommandsignoredagainbecauseanotherhold. Mash208samples77312→77440 finallyfreedstate2mode0HP39; R1twobursts6roundsusedbutnoadditionalbatkills. RetargetSquare/Circle/SquarefollowedR1interruptedbyholdagain77661,HP35MP7EXP132,clip14reserve160(total174),refs5all1HPoneholdingPlayer1. Currentlive36877/PID36857stopped77661samefrozenruntime/controlfolder; recordingpreserved. Noenginebugproven; needbettershortmash/aimtargetstrategy orescape. NativeGasStation3savepreupgradeHP5; healed95replay71118 verifiedfullfiniteandcanrestoreifdeathonly. No restartnow, noGHchanges.


### 2026-11-04 — WaterHole bats cleared, Underpass arrival
Same36877/PID36857 continued77661→80319. Read sourceUpdateLockTargetFromPad: CROSS clearsoldlock; freshSQUARE acquiresnearest, SQUAREcyclesexisting. Mash112framesfreedbat77773HP35; Cross8/neutral8/Square8/neutral22/R1=24/neutral4 killed2bats77847; repeat killed1 at77917; twomorerepeats clearedrefs0at78113. No furtherHPdamage. Result78409 rewards40EXP,8MP,EXP172MP15HP35,BP(nochangefrom3424,inspectlive),totalPB162(2loaded+160reserve),M93R2equipped. Archive dryfield-water-hole-bats-clear:6CLIchecks+FULLlive/finiteequality passedsession10007exit0,validation.txt. Noenginebugproved; repeatedineffectiveinputswhilebatheld. Healingcast78720HP35→65MP15→3.
NavigatedWaterHole: from[8591,-1366]attemptNorthblockedinitialwestcorridor; Eastto[11601,-1295], EastblockeduntilNorth70atx11595toz-3012,East270to[21417,-2401],North17/East45reached[21820,-2973]stairs. Cross8/neutral180/run40/neutral150→80319UNDERPASS area38/state6/view2/warp2/variant1 root[16394,-871,-4216],HP65MP3EXP172,normalpending0. Archive dryfield-underpass-arrival/live/replay; thisarrivalnotyetindependentlyverified. Currentonlyownedlive36877stopped80319samefrozenruntime/controlfolder. NextinspectUnderpassenemies/route. NativecardsGasStation3preupgradeHP5 preserved, healed95verifiedreplayavailable. Goalactive,noGHchanges.


### 2026-11-04 — Underpass switch and GrayStalker, retreat
Same36877 continued80319. BPcorrect3568 atUnderpassarrival (batreward144, earlierguessed3424wrong). South90tofirstswitch16608,-576; too far byfewunits/approach, west8walkthenSouth12at[16642,-781] CrossfinallyCAP81040. Cross2closed/toggledswitch1 room6→5 verified81236. North140triggeredGrayStalkerintro81512;3Cross/140neutralcycles finished81956room1/event0battle1,HP65. M93Rbursts spent20rounds, damage65→37→18; enemyhp296/450 readfromtask511425779008.spawnArg2.pointer typedEnemy, notwork. Reloadinitialhurtignored thenfreshR1succeeded82609clip17; morebursts leftclip2andHP18; targetcachehp296maycached(notrevalidatedSBvalue). Furtherreloadattemptgot14damageHP4/clip0. EscapedviaCrossclear/Left68/run24/Cross83265:pending129_sceneBattleResultTask,notdeath. Cross/neutral220to83493returnsWaterHole(verifytooloutput). Samecurrentowned36877/PID36857,frozenruntime/controlfolder. NeedrecoverHP/suppliesandbetterstrategy; GrayStalkernotdead. Recordingpreserved; noenginebugproved. NoGHchanges,goalactive.


### 2026-11-04 — retreat surface route failed at parking lot
Same36877 continued83493. LitWaterHoleCAP6attempts[16508,-3076]/facings/north14 didnottrigger; norecoveryfound. West245blockedx10404,z-3299. South52blockedz-1762;South14thenWest72 reached[8127,-1298], faceNorthCross85136DrivewayHP4MP4. West62/North86/West170/Cross85841MainStreet. North180/West170→[-6698,3094],North29faceWestCross86627ParkingLot15variant3refs7. West200towardLobby triggeredbattle; South12Cross87112pending129 butCAPNobodyHere, NOTescapedroom. Closedcaption87360thenattemptedEast27/North45towardbalconystairs causednormaldeath87654 HP-11area0. Newbugnotproven; thiswasfailedsurvivalroute. Archivedfullfailedrecord dryfield-underpass-retreat-failed. Sameownedlive36877/PID36857stillaliveatGameOver; inspectbeforecleanup. To recoverusefully: restoreverifieddryfield-healed95prefix71118 physicalreplay withinitialpostKylecardsinNEWisolatedcontrolfolder/frozenbinary, orordinaryContinueGasStation3HP5(preupgrade). Do notclaimcurrentAyaalive. NeedacquireRecovery/MPsuppliesBEFOREStalker viaDouglas, oravoidfight/runpasttoGeneralStore. BackStreetonlyconnectsGeneralStore/Souvenir/Warehouse/DilapidatedHouse; NOTMotelRoom1. LobbyonlyParkingLot; closedunoccupied. NoGHchanges,goalactive.


### 2026-11-04 — recovered batclear and bypassed Stalker to GeneralStore
Newownedlive41794/PID45591,frozenbinarysame/tmp/pe2-room-event-fix-20261104,controlfolder/tmp/pe2-underpass-retry-live-20261104(FIFO/cards/prefix/record/control.lldb),pad_addrresolvedinLLDB. Restoredverifiedbatclear78409 fullsnapshotdictEQUALarchive,HP35MP15. Onlythenretiredolddead36877/PID36857. Newhelperadvancefunctionsstorepoints41794/newfolder,end83249. Replayedsamephysicaloldrecordsuffix78409→81956(healing+Underpassswitch+Stalkerintro),HP65MP3. Extendedread-onlycheckpointtoolGrayStalker_actor400500Task:HP/taskstate/rootPosition+typedworkstate/subState/cloakLevel/playerCaught/posture/commandActive. py_compile/diffcheckpass; actuallive81956shows450HP.
Insteadshooting, ranNorth140→[16096,-7107]HP37(one28hit),North36/Right23/West280→[6295,-7838],West137/Right23/South8/Cross82821storeexit[1281,-7509]. Neutral180awaitedrealEscapeResult,MP3→4BP3568→3558; Cross8/neutral240→83249GENERALSTORE area3/state1/view14/warp3/variant1 root[8649,128,7411],HP37MP4EXP172,normalpending0. No Stalker kill requiredforthisroute. NativeGasStation3saveunchanged. Archive dryfield-general-store-arrival/live/replay/initialcards; finitevalidationlaunchednext. NeedsearchstoreRecovery/MPitems+unlockGasStationfrontdoor. Currentonlyownedlive41794stopped83249. Goalactive,noGHchanges.


### 2026-11-04 — General Store cleared
Arrival83249finite11268finishedexit0,4CLI+FULLlive/finiteequalitypassedvalidation.txt. Sameowned41794/PID45591 continuedstoreexploration. Backcorridorfromx8649,z7411 separatedbywallz6550; triedrightsideunsuccessfully, CAP9at8240,6384switchprompt toggledlightbutnoitem. ActualpassagearoundWESTend: West193from8299,6550thenNorth140reached[1514,5600],triggeredbattlephase1. North82blocked[1310,4640]. FivegroundredMindSuckler-lookingfoes, refs5. M93RfreshSquare/R1burstscleared5→2at86672HP25,→1at86918HP15,→0at87120HP6. Result87406EXP+40→212,MP+20→24,PB162→144(18spent). SmallBoxitem58lootconfirmedAll,carried87650. Healing7twice88272(expectedend):HP6→66MP24→0,normalcontrol; verifytooloutput. Archive dryfield-store-cleared/replay/live/initialcards, finiteverificationoutstanding. Storeclearedsafe, stillneedrecovery/MPshelvesandunlockfrontdoorGasStationat[2816,224],faceNorth. Current41794stopped88272samefrozenruntime/controlfolder. Goalactive,noGHchanges.


### 2026-11-04 — store front door unlocked
Same41794/PID45591 continued88272→90324. SmallBox58actualUse returnedNotForThisNow at88541, keptitem; likelyinspectseparately, noenginebug. Storecleared88272finite19103exit0:5CLI+FULLlive/finitedictequalitypassedvalidation.txt. Searchedbutnoshelfitemyet. From[1373,4640]East36/North60→[2588,2849],west15/North20walk→[2350,2562],counterCAPnottriggered. East14/North53→[2938,634]frontdoor;walk14+7+13closerapproachto[2978,346]finallyCrossUnlockcaption90008. ClosedCross/neutral60/Cross/neutral240→90324GasStation(verifytooloutput),HP66MP0EXP212,SmallBox58stillcarried. Archive dryfield-store-front-open/replay/live; independentvalidationoutstanding. Sameownedlive41794stopped90324, /tmp/pe2-underpass-retry-live-20261104 control/cards/record; frozen /tmp/pe2-room-event-fix-20261104. Nextactualsavephone[4384,-528]andresupplystorefrontnowaccessible. Goalactive,noGHchanges.


### 2026-11-04 — native GasStation4save, located supplies source
Same41794 continued90324. East34faceSouthphone90547; newPiercecallmanyCrosspages→save92167selectGasStation3. DownNewBlock/CrossCreate/CrossYes→SaveComplete92607; closed92715. Nativecards+replay/livearchived dryfield-gas-station-4-save, preservingoldblocks. HP66MP0EXP212,Storecleared/frontdoorunlocked.
Read-onlyallitemrows showed50:9mmHydra27,51:59pepperSpray,52:8Penicillin;80:PB50,81/82:4STIM, NOThealing. SmallBox58isFLARE(unidentified), cannotordinaryUseoutsidebattle; notbug. Wentcararea93436[13377,-5375],yaw4032,butnoinventoryinteractionyet. ACTUALsuppliesidentifiedsource src/gameplay/item_placement.c gAreaDryfieldGeneralStoreObjectPlaces:placemententry15COLA,16RECOVERY3,available! Needreturnclearedstoreandread-onlyfinditempickuptasksentry15/16modelcoords; thenphysicallycollect. Currentonlyowned41794/PID45591stopped93436, samefrozenruntime/controlfolder. Allpriorverifiedcheckpointsintact,goalactive,noGHchanges.

Current41794continued93436→95820. Mis-turncorrectedgasstationcarroute:South80/West240→3185,-2641,South53walk41→frontStore94942[3100,439]. StorestillclearHP66MP0. NoitempickupTasks; Cola/Recovery3areCAP/shelfpickups, notdynamicmodelactors. FrontaisleEast166blocked7988,1199;East34thensouth24→[9002,2012],faceEastwalk12/Cross95820CAP20saysFishingequipment, NOTfridge/Cola. Currentcaptionopen,closebeforemoving; atx~9100z2012. NextinspectotherCAPs:23shelf[5824,1344]normalNorth(faceSouth);19frontshelf[6544,160]normalSouth(faceNorth);17[336,800]normalEast(faceWest); Colaentry15/Recovery3entry16stillavailableperstaticinitialtable, actualflagsnotyetread. NativeGasStation4save92715archivedandcomplete. Goalactive,noGHchanges.


### 2026-11-04 — Cola and Recovery3 collected
Same41794/PID45591 continued95820→98140. Existing/tmp/pe2-cap-inspect-venv supportsPIL; fullcap_dialoguefailedmissingatlas, so parsedrawCAPcommandswithcap_dialogue.commands/describe(withouttext). StoreCAP5talliesentry15andinvokesobject15(COLA),CAP6entry16RECOVERY3. Exactsourceactions, no guessing. ClosedfishingCAPseveralCrossuntilnormal96214. South85thenWest38/South12reached[8400,5043],too farby13forCAP6min5056; walk8Cross96864Drinkscaption. TwoCrossconfirmedpickup97080item3Bottle(Recovery3),inventorynow3:1. Closednotice/Circle,North10/West92/South10→[5883,4963],faceSouth;walk17/Cross3→97984item5Can(Cola). Closednotice/Circle98140ordinaryui0. HP66MP0EXP212PB144,SmallBox58,Recovery3qty1,Colaqty1. Archive dryfield-store-supplies/replay/live/initialcards; independentfiniteverificationlaunchednext. Currentonlyowned41794stopped98140, samefrozenruntime/controlfolder. NativeGasStation4save92715beforepickups preserved. NextuseCola5(+80MPcapped43peritem_use.c),Healingto96HP, keepRecovery3asreserve; thenBackStreet/Warehouseprogress. Goalactive,noGHchanges.


### 2026-11-04 — Cola used, Warehouse dresser inspected
Same41794/PID45591 continued98140→102848. Suppliesfinite11336exit0,5CLI+FULLlive/finiteequalitypassedvalidation.txt. FullmenuUse→Right/Down6Can5→Use:Colaconsumed98444,HP66→86(+20),MP0→43cap. Startinitialignoredbyresultpopup; secondStartclosed,Healing99202HP105MP31. Recovery3retained.
BackStreetviaStoreeastdoor:North12/East101blocked8573,4966;North9/East28→9462,4907,walk13East/Cross100234BackStreet5/state1/variant1[-9597,4667]east,2DesertChasers200HP. East210runtriggeredbattleandinterruptedturn100650[-1254,4667]. RetryLeft23/South25→[-1340,5546]HP87(one18hit),yaw3502;Right14/Cross100933EscapeResultMP31→32;Cross/neutral240→101181Warehouse7/state1/view2/warp1variant1[2599,-3535],refs0.
South45/East68→4705,-1814,faceSE440Crossoutofrange. Walk12+18+6blockedx4903; turnEast13/walk12/turnSE12/Cross102092at[4950,-1553]CAP4starts. Persistentcounterflag79(0x4f),initialscratchesonthefloor. ManyCrosspagesreexamine→dresserboltedtowall/needsomethingtoremovescrews102740,closeCross102848. Ordinaryactorpending0,HP87MP32EXP212Recovery3retained,Colaabsent. Archive dryfield-warehouse-inspected/replay/live, notyetindependentlyverified. NeedgetMonkeyWrenchDouglasnowrequesttriggered; nativeGasStation4preColasavepreserved. Sameonlyowned41794stopped102848controlfolder/tmp/pe2-underpass-retry-live-20261104 frozenbinarysame. Goalactive,noGHchanges.


### 2026-11-04 — verified wrenchrequest3, returnedclearedstore
Importantcorrectflagdecode: gameFlagGetNibble usesODDlow/evenHIGH. Prioradhoctest79>>4falsely0; actualbyte39=3 =>flag79=3 CONFIRMED. No gameplaybug. Existingcheckpointflagreadsbeyondscope shouldauditlater(particularlyAkropolisexplicitfields). Same41794continued102848. WarehousefurnitureblocksWestatx4302fromnorthside. Correctreturnroute from4950,-1553 viaEastside/Northleddeadend; finalSouth50toz-1974/West46→[2783,-1974],North40blockedTV[2599,-3039]. CrossaccidentallyopenedCAP7TVlongtext; repeatedCrossreopened. FinalsingleCross105956TVpage2,another106064fullyclosed;Right24/Westwalk22/Left23/Northwalk45/Cross106476BackStreet5warp3[-1423,5449],HP87MP32. North25/West220→[-9700,3918]too farNorthofstoretriggerby18;Southwalk12faceWestCross107226EscapeResultMP33. Cross/neutral240→107474GeneralStorearrivalverifyoutput,HP87MP33EXP212Recovery3retained. Archive dryfield-wrench-request-return/replay/live. Currentonlyowned41794/PID45591stopped107474samefrozenruntime/controlfolder. NextreturnDouglasviaStore→GasStation→MainStreet→Driveway→Factory→Garage→JunkYard→Trailer; getwrenchconversationavailableflag79=3. Noenginebugproved. Goalactive,noGHchanges.


### 2026-11-04 — Monkey Wrench273 obtained
Same41794/PID45591 continued107474→122993. Returned clearedStore/GasStation/MainStreet/Driveway/Factory/Garage withoutdamage. GarageSouth124/walk16/Cross→JunkYard113340,escapeMP34HP87. South75/East425/East45/North68→Trailer114389. ApproachedDouglas[4209,-1582],Cross/DownInformation triggered firstWrenchconversation115372;8Cross120cycles ended116396,flagFD1. ReturnedJunkYard117174,South65/West450/North112→Garage118201. Added_actor01500Task/_actor04000Task checkpointcensusHP/root. ThreeMindSucklers50HP,gunfightcleared120070refs0HP49,55PBspent144→89;reward36EXP→248,6MP→40. Healingtwice121008HP105MP16. GarageeastsideviaNorth139/East200→8064,1442;South126/East35blockedbarrel8164,5598;South22/East34→9304,6204. CrossCAP16dispatchflagFD1→CAP22. FinalCross2collectedMonkeyWrench273at122993,ordinarycontrol. HP105MP16EXP248PB89Recovery3qty1. Noenginebugproved. Archive dryfield-monkey-wrench/live/replay/initialcards, finite launchednext. Currentonlyowned41794stopped122993samefrozenruntime/controlfolder/tmp/pe2-underpass-retry-live-20261104. NextreturnWarehouseUseWrenchatdresser5456,-1824. NativeGasStation4save92715preColapreserved. Goalactive,noGHchanges.


### 2026-11-04 — Warehouse dresser unbolted
MonkeyWrench122993 finite24883exit0:5CLI+full live/finite equality+273present passedvalidation.txt. Same41794/PID45591 continued→131502. ReturnedGarageviaNorth123/West228→1599,2009,South26/West22/walk15→Factory124135. FactoryNorth155/West24/North61→3523,1243,East49Cross124895Driveway;East22/North55/West190blocked-6708,-1459,South12/West82→-9378,-1350Cross125990MainStreet. North325/East17Cross126686GasStation,East64/South83/walk15Cross127199Store. Eastaisleblocked7988,1175;East21/South100/Eastwalk49Cross128709BackStreet. East210interruptedturn;retrySouth25Cross129245escape(nohurt),Cross129483WarehouseHP105MP17EXP248.
Sameapproachdresser[4950,-1481],yaw528SE; KeyItemWrenchUse130086REFUSEDbecausefacingeventtriggernotCAP4. Close/reopenafterturnEast11(yaw1012),Use130450SUCCESSUsedMonkeyWrench,event1. NoticeCrossandsceneCross/neutral→131074room2blackfade;neutral240/Cross/neutral180→131502scenecompleteevent0,room2/view4,root[4654,-1968],HP105MP17EXP248,normalpending0. Wardrobemoved,revealedpassage. Archive dryfield-warehouse-open/live/replay/initialcards; independentfinite launchednext. Needenterrevealedpassageandcontinue. Sameonlyowned41794stopped131502,samefrozenruntime/controlfolder/tmp/pe2-underpass-retry-live-20261104. Noenginebugproved,noGHchanges,goalactive.


### 2026-11-04 — Dilapidated House entered, No9 Golem battle started
Warehouseopen131502finite87871exit0:5CLI+FULLlive/finiteequalitypassedvalidation.txt. Sameowned41794/PID45591continued→137567. SErun35thenfaceEast→5058,-1098,walk29EastCross132114DilapidatedHouse9/state1/view2/warp2/variant1[-5403,-400],HP105MP17refs0. East40blockedx-5000;North40reached-1800. South20faceEastCrossCAP3NothingOfInterest;closeCrossthenNorth20/East40→132953mainroomtrigger,sceneevent1refs1. PhysicalCross/neutral120..180cyclesprogressedAya/anmcwoman/No9dialogue. At137453sceneends,event0battle1AyaHP105MP17,No9GOLEM1100HP at[-392,129,-313],_actor521100BodyTask. Addedthiscallbacktoexistingread-onlyEnemycensuswithrootcoords; py_compile/diffcheckpass. Archive dryfield-house-no9-battle/replay137453/live/initialcards, finitevalidationNOTlaunchedyet. ThenSquare8/neutral20/twoR1bursts35/8→137567:No9HP1080,6PBspentclip14, totalPB83, AyaHP105stillMP17. Currentonlyownedlive41794stopped137567samefrozenruntime/controlfolder. No9armorGUARDordinarydamage>>3,normal>>1; hitresponsebystate/attacktable; inspectbeforewastingammo. Enemyparams1100HP800EXP300BP50MPreward. Needactualfightstrategy, Recovery3retained. Noenginebugconfirmed,goalactive,noGHchanges.


### 2026-11-04 — No.9 first combat attempt, equipment restriction confirmed
Owned live41794/PID45591 continued137567→140736 using physical FIFO only. No9 attackLive window confirmed: Pyrokinesis2 during slash recovery dealt204HP (1077→873), guarded cast only26 (873→847); MP17→3. Bursts to138452 brought boss811HP, then four bullets brought799HP but Aya105→65; subsequent hit65→50. Automatic reload eventually completed, M93R clip20/reserve69. Changed to Tonfa through battle attachments menu; No9 grabbed Aya (50→43), escaped scripted grab after physical button alternation; later long slash43→24. Boss remains799HP. Recovery3 item3 qty1 is NOT attached (attachSlot0), so unavailable in battle equipment menu; earlier claim of usable healing reserve was incorrect. Only alternate weapon was attached. Menu selection persists, and empty ammo rows are skipped; blind Down counts switched weapons twice. Actual Tonfa damage not yet tested (earlier inputs happened during grab).
Retreated physically west to entrance[-5498,-424], yaw3045, view2; Cross opened refusal dialogue (pending129), not escape. Closed it, still area9 battleRefs1 at140736; boss[-4171,-1917]. No crash or proven engine bug. Current Aya24/105HP,3/43MP,Tonfa19; Recovery3 retained in inventory. Archive dryfield-no9-first-attempt/live/replay/initial-cards; not independently verified yet. Continue from same stopped process; do not restart on observation timeout. No GH mutations. Goal remains active.


### 2026-11-04 — No9 death path and prepared retry
First attempt physical tonfa landed35 total (799→764HP); Aya24→1→-19, then death animation and area0 GameOver by141950. Checkpoint collect correctly refuses no player at GameOver; VRAM archived /tmp/pe2-no9-first-gameover.vram. No crash. Recovery3 unavailable because unattached, not engine failure.
Independent battle-entry137453 finite12900 exited0:3CLI expectations and FULL dictionary equality passed, validation.txt written. New live96086/PID98155 replayed verified Warehouse131502 and FULL dictionary equality passed before any new input. Only then retired old41794/PID45591. New control /tmp/pe2-no9-prepared-live-20261104, same frozen binary. Full menu main Item opens KEY ITEM; Use above opens inventory. Recovery3 Bottle moved from carried to armor attachSlot1 at132405; Tonfa remains2. Flare SmallBox moved to attachSlot3 at132695. Closed Start, normal gameplay132803. Aya105HP17MP,89PB. Archive dryfield-no9-prepared/live/replay/initial-cards, not independently verified yet. Ready to enter house with actual in-battle healing and flare available. Goal active, no GH mutations.


### 2026-11-04 — No9 second attempt reached384HP; battle menu is horizontal
Owned96086/PID98155 replayed canonical input segment131502→137453 after prepared132803: newbattleentry138754 HP105MP17boss1100. No9 longslash hit25 then first Pyrokinesis139308 dealt204→896; grab10→HP70 escaped via physical alternation; second attempted wheel ignored while hurt (noMP spent). Another slash→45 andshortslash→34. Correctly timed Pyro140455 dealt210→686,MP3.
Important battle-menu correction: itemMenuArmorAttachmentPanelTask uses LEFT/RIGHT, not UP/DOWN. Its selected index is gItemMenuSelectedAttachmentIndex, distinct from full-inventory gItemMenuArmorAttachmentList. Earlier Down commands were ignored and confirmed remembered Tonfa1. This unnecessary weapon swap let boss approach. At140760 read selected1, Left→0/Cross used Recovery3 (full105), then stance hit40→65 by140904. Flare slot2 viaRight2/Cross dealt102→584 at141192, consumed58. Left1 selected attached M93R, equipped141394. Gun bursts dealt5HP/bullet, Aya65→25→17. At142162 boss439,clip11. Furtherbursts→142420boss384,Aya-3,clip0; second attempt failed18HP above counter threshold. Counter source requires boss<=366,Aya<61,frontgrabandescape. Noenginebugproved. Secondattempt replay/live/initialcards archived.
New retry92460 launching /tmp/pe2-no9-heal-retry-live-20261104, samefrozenbinary, originalinitialcards, recordedinputprefix140455 (after secondPyro, before wrongmenu). Need verify currentreadback before retiring old96086. Intendedcorrectnextsteps: Start and read gItemMenuSelectedAttachmentIndex; selectRecovery0 horizontally, use while retainingM93R. ThenFlare2,shootwithlargerhealthreserve. NoGHchanges,goalactive.


### 2026-11-04 — third attempt failed, MP-preserving preparation required
New92460/PID30510 replayed140455 prefix: expectedHP34MP3boss686,M93R20,Recovery+Flareattached confirmed. Retired old96086 only after new stop. Start/read selected1/Left/Cross used Recovery correctly→105HP at140602 retainingM93R. Sixbursts→140880boss616,Aya65,clip5. FirstStartignoredwhilefiring; confirmedno itemspent. RetryStart141156pending66,slot0,Right2/Cross→Flare102boss514,butstancehit40→Aya25 at141366. PhysicalCross/turnLeft36/run65 retreatedwest to[-5349,-2369],took8hurt→17HP. Shotsboss506,clip0 at141596. Reload/6bursts failednextstance:142022Aya-3,boss476,clip12. Archived thirdattemptlive/replay/initialcards. Noenginebugproved.
Next strategy preservesMP instead of repeating short-resource attempts: newlive launching from canonicalMonkeyWrench replay truncated120070 (GarageclearHP49MP40, beforetwoHealing spells consumed24MP). Use Recovery3 out of battle to restoreHP105 and retain40MP; then repeattoolpickup+Warehouse route and equipFlare. FivewelltimedPyro2casts~1020damage plusFlare102 suffice, reducingrequiredgunfight. Newsession'sstopnotyetobserved; do notretire92460untilreplacementverified. Control /tmp/pe2-no9-mp-retry-live-20261104. Samefrozenbinary,originalinitialcards. Goalactive,noGHchanges.


### 2026-11-04 — No9 defeated; post-battle negative capture LP64 corruption fixed
Owned28930/PID75610 replayed Garage120070 (HP49MP34 beforebattle reward); settledbattle, UsedRecovery3insteadHealing→120758HP105MP40EXP248. Canonicalphysicalroute121008→129483reused; newWarehouse129354HP105MP41. Reuseddressersequence→131373room2. EquippedFlare58slot1,closedmenu131817. Archive dryfield-no9-mp-prepared/live/replay/initialcards; finite92442exit0,5CLI+FULLsnapshot equality passedvalidation.txt.
Battleentry137768:HP105MP41boss1100. FivePyro2casts timedafterattackLive dealt210,212,210,212,204:138362boss890HP105MP34;139054boss678HP75MP27;139955boss468HP65MP20;140291boss256HP65MP13;140772boss52HP65MP6. PhysicalDownbackwardwalkbeforewindup preservedrange; onegrabescapedwithalternatingbuttons,took10. Gunbursts→141015boss6,then141293boss-2,Aya25HP6MP,closingevent1view14. No9DEFEATED; ammo73left,Flareunused.
ClosingphysicalCross/neutral180scenehitrealnativecrashatpad142131: EXC_BAD_ACCESS _taskInsert,next=0x8842884288438842. gFsImageWorkspacePtr0x102552000,TaskList0x10259b0e8(~299KBoffset). Sharedscreennegative capture andfilter erroneously usedu_long8bytewords, whileFsImgBuffersstripsu32and153600bytes; capturestridesandfilterwalkdoubledt307200bytes,overwritingtasklistwithpixels. Correctedbothsharedfragmentstou32,withAPI-onlyu_longcast. AffectsNo9andactor460200samehelper.
Addedtests/screen_negative_test.c+CMakehosttarget: realcapture/filterfragmentswithboundedmockStoreImage, fourdebug/buffercombinations, all76800pixelscheckedagainstscalarRGB555oracleandcanaryguards,releaseverified. TestfailsHEADoldcodeonbounds(line29), passesfix. Buildgame+testpassed;CTestscreennegative/gtecompat/actorwalkgap/cdring4/4passed;gitdiffcheckpassed. Crashfixture build-port/reference/dryfield-no9-closing-crash/replay142131/initialcards/backtrace/screen/notes.
Newfixedruntime frozen/tmp/pe2-negative-fix-live-20261104/parasite-eve-ii-pc, LLDB16523 launchedvictoryprefix141293; stopnotyetobserved. Oldcrashed28930retaineduntilliveverifiedreplacement. NeedcontinueclosingCrossinputpast142131andverifyprogression/rewards; donotclaimruntimefixverifiedyet. Goalactive,noGHmutations.


### 2026-11-04 — negative fix runtime passed; next R08 debris UAF identified
Fixednegative16523/PID99070 restoredvictory141293 (HP25MP6boss-2), thenphysical10Cross180→143173, pastold142131crash,validtasklist/save-backedinventory,roomview21. Further10Cross180→145053 transitionedDryfieldR08area8/view4,event1,awarded800EXP/300BP:EXP1048BP4066,HP105MP43,PB73. No9closingandnegativeeffectsuccessfullycompleted. Oldcrashed28930retiredonlyafterfixedreplacementverified.
AddedexplicitAPIcastfornegative-debugStoreImageaswell(storagealwaysu32). Fullbuildand4targetedCTests pass. IsolatedHEADoldfilterwithfixedcaptureunderASANalsofailsglobal-buffer-overflowread8; fixedcapture+filterASANpassesallfourcapturemodes. Logarchiveddryfield-no9-closing-crash/old-filter-asan.txt.
Next8Cross180batch inR08 hitnewmallocfreelisttrap atpad145312 (actualrecordedrows145312),stackmemMalloc→_actor121300LampDebrisTask850. Rootsource: debrisFALLtaskKill971 freesworkimmediately(task.c355) butfallthroughworldCoordSetModelLighting980 writesmodelcolorMtxinsidefreedwork. AddedreturnaftertaskKill, preservingmodelreleaseandavoidinglightingafterteardown. Otherkillsinactorreviewed, noanalogousfallthroughfound. Build+4CTests+diffcheckpassed. Archive dryfield-r08-lamp-crash/replay/initialcards/backtrace/live-crash.
Newfrozenruntime/tmp/pe2-lamp-fix-live-20261104/parasite-eve-ii-pc(+dSYM), liveLLDB85166 launchingrecordedprefix145053 beforelampcrash; awaitingstop/runtimeverification. Old16523remainscrashedforinspection. Needverifyreplacement145053thencontinuephysicalCrossesandconfirmpast145312andsceneend. NoGHmutations,goalactive.


### 2026-11-04 — both crash fixes passed; night-house transition now stalled
New85166/PID46325 restored145053 with expectedR08HP105MP43EXP1048BP4066, thenold16523retired. Same8Cross180→146557 passedold145312malloctrap, R08view5withlampsbroken. Further12Cross180→148813 transitionedstage3(DryfieldNight)area9/room1/view6/warp3, Aya[1596,129,-2540]yaw0,normalactor0. Howeverevent1,pending255andgarbledcapturedframe. Neutral240/Cross/neutral240→149301leftgameTick120503/frameCount122341UNCHANGEDwhileloopTicks/vsyncadvanced. This is a third native transition/render stall, not completion of scene. No moreguessing/resets;inspecttransitiontasksandroomcallbacknext.
Currentonlyownedlive85166/PID46325 stopped149301, control/tmp/pe2-lamp-fix-live-20261104, frozenbinary+dSYMwithnegativeu32+debrisreturnfix. Archive dryfield-night-house-transition/live/replay/initialcards/screen, notindependentlyverified. Bothpreviouscrashlocationspassedactualruntime. Build+4CTests+diffcheckpassed. No9defeatedand800EXP300BPawardedverified; current105HP43MP1048EXP4066BP,73PB,Flarepreservedslot1,Tonfa2. Goalactive,noGHchanges.


### 2026-11-04 — night movie was healthy RGB24; Kyle scene complete, BackStreet cleared
Correctionto149301diagnosis: no thirdnativebug. Night-house movie state3 intentionally holds gameplay. VRAMexportRGB555incorrectlyrenderedRGB24STR; correct--rgb24showedKyleframe. movieFrame475→925after1800neutral,thenanother1800→152901moviefinished,pending0anddialogueview9. 22physicalCross180cyclesfinished157037event0/actor0/pending0area9view5,HP105MP43EXP1048BP4066,Kylepresent100HP. Archive dryfield-night-kyle-scene-complete/live/replay/initialcards. Independentfinite15015exit0:8CLIexpectations+FULLlive/finiteequalitypassedvalidation.txt. BothnegativebufferandlampUAFfixesverifiedthroughentirescene.
OpenedBackStreetfrontdoor1712,-2768:west35/Left23/North70→1489,-2268;walk15+15→1462,-2592,CrossCAPUnlatchedDoor157539;Crossclose/Cross→157875nightBackStreetarea5warp4[9463,5532]North. SixScorpions_actor02500Task68HP atx4800,-500,-6200. Extendedcheckpointenemycensustostage3; pycompile/diffcheckpendinglaststage. West120triggerbattle158046,initialSquareignoredintro. Gunbursts killedone,Kyletooksecond,initialmissedretargetwastedammo. Aya105→95→65→48. Triangleat159272confirmedwheelopen;Pyro159430killedtwo,MP43→36. Healing159636HP48→83MP24. PhysicalWest185→198,5273HP82;Pyro160164killedone,secondPyro160533lastdead/reward120EXP+48BP+6MP. Healed160827HP105MP4EXP1168BP4114PB41(clip20),Flareunused.
BackStreetclearedrefs0. West260→[-9560,5392],Northwalk24/WestCrossmissedtriggerby12at5068;Northwalk10/WestCross→161793NightGeneralStorearea3/view7/warp2[9669,4832],HP105MP4,refs4dormant. Archive dryfield-night-general-store-arrival/live/replay/initialcards,notindependentverifiedyet. Currentonlyowned85166/PID46325stopped161793same/tmp/pe2-lamp-fix-live-20261104. NextcrossStoretoGasStationwithKyle,needresupply/save. NoGHmutations,goalactive.


### 2026-11-04 — night GasStation Scavengers defeated, safely reached Room6
Owned85166/PID46325 continued161793. StoreWest180→3756,4832;West60/North120blocked1320,3300;East40/North85/Cross→162771NightGasStationarea1,scriptactive. 10Cross180endedintrobutalsoallowedcombat:164651Aya91HP,Kyle92. Ten_actor01600TaskScavengers85HP initially. Added_actor01600Tasktoexistingread-onlyenemyHP/rootcensus; reloadconfirmed. UsedFlare58attachedslot0 viaStart/Left/Cross164888, killedtwoanddamagedfutureone33HP. Gunbursts+Kylekilledmore;shortenedrangefrom7767,-2200to10135,-4050,HP91→77. PBtotal41exhaustedby166409,remaining35HP+18HP+two85HP. EquippedTonfa19viaStart/Right/Cross,walkedUp70andphysicalR1swings,killedtwo;freshSquare/Up45/sixR1swings→167215bothlastScavengersdead. OnecorpsekeptbattleRef1after500neutral because deathPhase255 reportedtoroomandawaitedfollowupCAP,notenginebug. SixCross180→169211roomEnemiesempty/refs0,EXP1288(+120),MP28(+24),BP4858(+744),Recovery2item2obtained. Healing169427HP77→105MP16.
GasStationphone4384,-608 approachedviaWest200→4941,-3628,Westwalk20/South75+15Cross169941:Linehasbeensevered. Closed170029. GasStation→MainStreet170562 viaNorth65/West115Cross,HP105. TriedRoom1mainstreetdoorat-6912,-2816whilemistakingforLobby;entered171856area11,immediatelyexited172151withouthurt. MainStreetParkingLotentranceactually[-6880,2016]area15. East30/South120/West35Cross172700triggeredescaperesult;Cross→172948ParkingLotvariant3,MP17,BP4848,HP105. Lobby3040,3744CAPlocked(noLobbyKey):confirmedIt'slocked,notportbug.
ParkingLotstairs4752,1936:approach[4326,2361],Eastwalk25/Northwalk15/Cross→174986Balcony29arrival[-12638,-3070,1396]. South80/East175interruptedbyoneScavenger14hit→91HP[-9074,2544]. East80→[-6563,2420];South52+walk8/faceWestCross175839escaperesult,MP18;Cross→176087NightRoom6area30,HP91,MP18,BP4838,EXP1288,Tonfa19,M93Rattached2empty,Recovery2qty1unattached. Phone896,1199at[1011,1500]WestCross176295ALSOlinecut. ClosedsingleCross→176383safestoppedRoom6. Bothnightphonesunavailable;no native savewritten. Archive dryfield-night-room6-safe/live/replay/initialcards; independentfinitevalidationlaunchednext. Goalcontinues:needDouglasresupply/JerryCanfuelquest, noenginebugprovedthisturn. Currentonlyowned85166/PID46325same/tmp/pe2-lamp-fix-live-20261104. NoGHmutations.


### 2026-11-04 — night JunkYard reached; unsuccessful Stalker escape
Room6 verification correction: finite replay FULL matched live, but pendingMode129 (phone CAP) contradicted the pendingMode0 CLI expectation. Second Cross closes CAP at176491. Physical route passed WaterTower177814, Breezeway178329 (bat grab cost9HP), Factory179594, Driveway181413, back Factory181816, Garage182564 and JunkYard182975. Factory car blocks direct south from Driveway: route west belowx3697, south beyondz3700 then east avoids it. JunkYard Stalker encounter triggered en route to Trailer; HP82→56→18→5→-8 at185567. Failed navigation/PE inputs, not established engine fault. Cross cancels PE wheel; inspect held confirm/cast state before advancing. Archive build-port/reference/dryfield-night-junkyard-failed. Next recover through physical deterministic replay, attach Recovery2 in safe room before retry. No GitHub mutations. Goal remains active.


### 2026-11-04 — recovered Room6 and reached Douglas; ammunition purchased
Recovery initially diverged because copying initial cards over an existing output-card directory left two extra save files. Owned PID57859 stopped; renamed entire contaminated cards directory and restored only fixture initial-cards. PID31791 replay correctly reproduced Room6 at176491. Phone caption still visible despite pendingMode0; physical Cross8 closes it. At177576 Recovery2 attached slot1; archive dryfield-night-room6-prepared. Replayed physical route to JunkYard184060, HP82MP20. Added Zebra Stalker _actor400600Task HP/root to read-only checkpoint census; both180HP confirmed. East run reached13018,4371 at184713. East280/Right25 reached21354,3825North2112 HP56; Left2/North70 reached21414,1591. Cross8 opens escape result185293, anotherCross8→185541TrailerCoach27/warp2. EightCross180cycles finish first arrival186981. WalkNorthWest30/Cross→Douglas, Show me your guns→Ammunition→9mmP.B.→Purchase10packs. At188062 carried160=500, BP4808→4508, HP56MP21. Recovery2 retained attachedslot1. Archive dryfield-night-trailer-ammo with clean initial cards. No new engine bug established; no GH mutations. Cross1 pulses were unreliable for PE; previously successful Healing input uses Cross8. Next reload/equipM93R, heal, progress Douglas story choice and secure native save.

Trailer ammo checkpoint independently verified: finite60423 exit0, fourCLI + FULLsnapshot equality passed. Healing with Triangle8/neutral20/Cross8/neutral180 worked188437: HP56→86 MP21→9. EquippedM93R and loaded20 through Use weapon/load rows188952. Douglas conversation Tell me about shelter was repeat; Lend me a car selected189842, scene finished192730event0/pending0, collected newkey274. Archive dryfield-night-trailer-story-complete at192730, not independently verified yet. Current owned85166/PID31791, no finite jobs remain.


### 2026-11-04 — radio contact and native night save
Continued owned85166/PID31791 from192730. New collected274 verified include/gameplay/items.h as LobbyKey0x112; JerryCan0x117 remains missing. Trailer radio trigger[160,-656] approachedWest from4870,-900:Right12/West90→1954,-828 thenWest43/Cross→radio193138. Jodie conversation progressed22Cross180cycles through197256 save selection. Cross→Overwrite, Up/Cross→197580 visually Save complete. Working cardfile BASLUS-01042CI0pWqFo updated07:49; screenshot archived. Closed197796. Archive dryfield-night-trailer-radio-saved contains replay/live/initial-cards plus separate saved-cards (never use saved-cards as initial for full replay). Next return via JunkYard/Garage to MotelLobby, unlock with LobbyKey and get JerryCan fromLoft. HP86MP9M93Rloaded20/ammo500total,Recovery2attached. No new engine bug established, noGHmutations.

Return fromTrailer198208JunkYard21921,1639South. South75/West450→9182,3426 HP86→60. West110/North90/Cross→199277escape result HP60MP10. NextCross/neutral requested199505 instead crashed actual199309loadingNightGarage24. EXC_BAD_ACCESS fsBuildFolderTables(stage3,group24,folder1) fs.c1285 index0: directorybuffer begins80010160,00090005,00000299,00003d4c. Wrong sector payload interpreted as FsCdfFile; root cause unproven. Archive dryfield-night-garage-directory-crash replay/cleaninitialcards/backtrace. Owned85166/PID31791 retained stopped at exception; load(end)=199505 is requested boundary, NOT actual. Next inspect FS/CD sector provenance, fix actual cause and replay through transition. NoGHmutations.

Crash narrowed: _gFsStageFolders[21].folderId at0x100e460bc is10003 instead of2401; its sectorOffset9669 and neighboring entries remain correct. Disc stage3CDF header atabsolute100127 directly checked viaBIN2352+24:entry21=(2401,858). Missingfolder lookup reaches sentinel and reads124221, explaining wrong payload. Need catch original write via data watchpoint in deterministic replay; do not substitute bounds-only workaround.


### 2026-11-04 — garage directory corruption root cause and fix
Deterministic hardware watchpoint replay66050/PID15337 stopped writing10003 in fsBuildFolderTables(stage3/group24/folder1), not another subsystem. Old _gFsFolderFileSectors base0x100e45f30; base+99*4 exactly0x100e460bc, folderentry21. Retail folder2401 entry16=(99,334);334+9669=10003. Thus old51-element sector table OOB write corrupted folder2401 on first visit; reentry failed. Expanded src/main/fs.c array to100 for two-digit local file IDs. Disc audit stages1/2/3 maxIDs27/49/99; onlystage3folder2401 hasid>=51. Buildpassed;diffcheckpassed. Frozen fixed binary /tmp/pe2-folder-fix-verify-20261104/parasite-eve-ii-pc. Independent replay3114 running through199505, extending originalcrash199309 by196neutral samples; checks stage3/area24/HP60. Old owned85166/PID31791 remains atcrash. WatchpointLLDB66050 terminalexit0 (script completed afterstop), no longerlive. NoGHmutations.

Independent fixed replay3114 completedexit0 at199505. ThreeCLIexpectations passed (stage3/area24/HP60); snapshot fixed-live.json archived with validation.txt. Original frozenbinary crashes199309 on samephysicalinput. Garagetransition regression nowpassed.


### 2026-11-04 — fixed runtime live verified; MainStreet route attempt failed
New owned39864/PID78424 frozen/tmp/pe2-folder-fix-live-20261104. Replayed199505; FULLlive/finiteequalitypassed. Garagevariant4now3ZebraStalkers. North120grab→43HP;16escape cycles,Westwalk14/Cross→200321escape,200549Factory. Recovery2 used201059HP43→105MP11. FactoryNorth100/West50/North68→3720,1085 thenEast45/Cross→201886Driveway. Batsgrabbed,escape16cycles;onegunburstkilledone. FacedWest andrun210→203499exitresult,203727MainStreetwarp7[-488,8495],HP69MP12. West170/North180→[-4473,4202]safe; nextturn interrupted byDesertChaser200HP,knockedbacktowardsSouth. Healing204683MP12→0,HP39→69thenhit55. Escapeandgunbursts damagedChaser200→163→80, butAya55→32→12→-3at205519. Archive dryfield-night-mainstreet-chaser-failed. No newenginebug; next use GameOverContinue/nativeRadio save to retry with better combat/route, not full replay. Native savedcards archived dryfield-night-trailer-radio-saved. Onlyactiveowned39864/PID78424stopped205519;old85166/PID31791crashretained. NoGHmutations.

GameOverStart→Title206615,Start→Continue206723,Cross→cardlist206911,Down2→TrailerCoach1EXP1288BP4508,Cross206967→load. At207275HP86area27,butrc.collect playerwork unavailable. 300+600neutral through208175 stillNowLoading. pe2-transition archived dryfield-night-trailer-continue-loading: viewgate3,loadingRoomResources1,playerActorWorkTask1,zeroBattleRefs/actorControl/CDqueueidle,displayholdState127. Stage retained descriptor sceneBattleStartTransitionTask requestFlags0x80000000, but stalecallback as cause NOT proven. Need inspect missing player work and loaderstate1/nativeContinue initialization. Current39864/PID78424 stopped208175loading, no RAM edits. New load hang investigated; do not call established bug root cause yet.


### 2026-11-04 — Continue confirmed healthy; better supplies for retry
Correction: no Continue hang proven. At same208175 freshtarget/player SBValue and fresh VRAM show healthyTrailerCoach, actualplayerwork0x77b1463000,rc.collect successful HP86MP9BP4508 andLobbyKey retained. Prior loading/unavailable observations premature/stale; descriptorleftover notcause. MovementEast100→208357root3817,-800 confirmscontrols. DouglasTalk→guns→Items; shopremembersPass selection, firstattemptsno-op. SetpopupUp→Purchase. At211141 confirmedBP3148,Recovery1item1qty4,MPBoost1item6qty3,Recovery2item2qty1retainedattached1,ammo160total500. Closedshop211320; archive dryfield-night-trailer-resupplied replay/live/cleaninitialcards. Current39864/PID78424/tmp/pe2-folder-fix-live-20261104, goalactive. Needattachsupplies/useMPboost thenretryrouteLobby/Loft; optionalM4A1/shotgun upgrade ifcombatneeded. No newenginebugthisturn,noGHmutations.


### 2026-11-04 — DesertChaser defeated, Lobby unlocked
Continued39864/PID78424 from211320. UsedMPBoost1 at211647→212017MP9→39; retained2MPboost,4Recovery1. LeftTrailer213058. JunkYardroute wentoffx3761,1156 afterhits; HP86→3; initialbattleMenuCross equippedTonfa accidentally (slot1remembered). ReopenedStart/Left/Cross usedRecovery2 at214796HP3→93; thenEastNorth approach4881,500faceNorth escaped215116. GarageNorth110 hit26,wait50+Westwalk14/Cross escaped215829HP41MP41;FactoryHealing→216273HP71MP29. FactorysafeWestcarroute→Driveway217181. Repeatedbatsgrabs whilex-3592blocked bywall; truewestexitrequiresz<-~1000. Escape16cycles,Left20/North60→218797[-3514,-1599],Right23/West180/Cross+Cross→219356MainStreetHP53MP23. PyroinDrivewaykilled2bats7MP; restignored. MainStreetWest270blocked[-4685,8495],soNorth100→[-5001,5699]. FreshSquaretargetsChaser; shortTriangle8ignored,Triangle35 reliablyopenswheel0. Cross35/neutral100Pyro220131Chaser200→98,Aya53MP16. Triangle35/Cross35/neutral120 secondPyro220321Chaser98→-114,Aya53MP9. Cleartarget/runNorthWest→[-5562,1858];Right26/West35/Cross→220749escaperesult,MP10. Cross→220977ParkingLot[10645,3077]West. West215→3193,3077;Right23/Southwalk25/Cross→221438Opened door with LobbyKey. TwoCross→221724NightLobby17[2940,316]South,HP53MP10,refs0. Archive dryfield-night-lobby-unlocked replay/live/cleaninitialcards. Current39864stopped221724. No newenginebugproved;nextLobbyitems/masterkey+LoftJerryCan. NoGHmutations.


### 2026-11-04 — Bronco Masterkey collected from lobby cash register
Continued39864/PID78424 from221724. Lobby safe,HP53MP10. Reception CAPs multi-page swallow turns/movement evenevent0/pending0; visually close before navigation. Northern pictureCAP6 contains1881Tombstone, southernmemoCAP1 containsDoc/Holliday/Earp codehint. Behind-counter path requires southern gap:z>5300 thenx~4800,north intoaislex4600..5100; north side blocked bycountercrossbarz1950. Read-onlyactualgrid33faces confirmsgeometry. EmptycabinetCAP2 at5312,4928. Registertrigger4497,4464faceWest approached5085,4691yaw3032 at230729. Examine→CAP A cashregister→cursor. Sourceinspection disclosedcorrectcode3033 (not claimed independentlysolved). Physicalcursor # atrelative20,32 opensentry231521. Up14/Cross→3,Down14/Left28/Cross→0,Up14/Right28/Cross twice→3033at231791; Right22/Down28/CrossTOTAL→232076drawerkey. Cross→pickup232291,Up/Confirm→keypicked,closed232749. Collected275=BroncoMasterkey0x113 nowconfirmed;Objectiveupdatesviaexistingroommonitor. Archive dryfield-night-bronco-masterkey replay/live/cleaninitialcards. Currentowned39864/PID78424frozen/tmp/pe2-folder-fix-live-20261104 stopped232749Lobby17[5085,4691]West. Next exitlobbyviaaroundcounterSouth,ParkingLotstairs→Balcony→LoftJerryCan. Preserve4Recovery1/2MPBoost1;Recovery2usedearlier;Tonfaequipped,M93Rcarriedloaded20. Noenginebugprovedthisturn,noGHmutations.


### 2026-11-04 — balcony reached; safely rearmed in Room6
Continued39864/PID78424 from232749. LobbycounterSouthgap usedtoexit;exitroot2547,577blockeduntilcenteredx~2992thenNorthcross.234712ParkingLot[3200,3472]North. NE45→4262,2464;Eastwalk24/Northwalk23thenEastwalk12/Northwalk12Cross→235605Balcony29[-12638,1396]South. South80/East250→236028[-6158,2400],HP53→33fromZebraStalker180(twoinsteadoldScavengers). ApproachedRoom6South60/Westwalk16+16+8/Cross;HP33→15.236960escape,thenRoom6 safe236797+ correctedactualentry237399menu. Inventorynavigationconfirmed4Recovery1 beforeuse. UsedRecovery1→237938HP15→65; attemptedsecondinsteadusedMPBoost1→238479MP11→41. Recovery1row12 attachedslot1,remainingRecovery1qty3,MPBoost1qty1. Re-equippedM93R129 loaded20, Tonfa146attachedslot2. Healing239146HP65→95MP41→29. SafeRoom6actor4259,1500West,ui0,masterkey275retained. Archive dryfield-night-room6-rearmed replay/live/cleaninitialcards. Next exitBalconyandfollowcorridortoLoftat[-1872,10799]faceSouth; needavoid/killZebraStalkers ifblocking. Noenginebugproved,noGHmutations.


### 2026-11-04 — Loft entered; Jerry Can collected
Continued39864/PID78424 from239146. Room6exitEast47/walk12/Cross→239495Balcony[-6669,4477]East. Square/Pyro239807MP29→22 butbothStalkers180 unchanged, Aya95→69. Clearedtarget;Left31/run155→[-5460,6105]yaw841,Left19/South130→240255[-5358,10700]yaw49. Right22/East100/Left23/Cross→240620loftdooropenedBroncoMasterkey;3Cross35/neutralcycles→241145NightLoft31[3953,-2156]South,HP69MP23. South60/West260blocked[1266,-457]. ActualbypasswasNorth45/West190→241909[-4460,-1628]yaw2952. Right26/South45/Left23/West30→242318[-4946,-786]West3128. Westwalk20→[-5198,-765],facingEastdidnotactivate;faceWest47/Cross→242897GascanCAP. TwoCross→243327JerryCanpickup;Up/Confirm+close→243785collected279(0x117)verified,HP69MP23area31event0/pending0. Archive dryfield-night-jerrycan-collected replay/live/cleaninitialcards. Current39864/PID78424frozen/tmp/pe2-folder-fix-live-20261104 stopped243785,near[-5198,-765]West. NextreturntoGasStation tofillcan thenGarageBronco, mainstreetDesertChaseralreadydead inthissession. 3Recovery1(oneattachedslot1),1MPBoost1 retained;M93Rloaded20. Noenginebugproved,noGHmutations.


### 2026-11-04 — return from Loft failed near balcony stairs; replay recovery launched
From243785JerryCan. LoftNorth26/East260 interruptedhit26,244188[-3222,-1628]HP43yaw1848;Left19/East205→4068,-943;North30/Cross→244656escape,thenCross→244946Balcony[-1990,10664]North. Healing43→73MP24→12;West100→245289[-5797,10648],North225hit26→245573[-5797,5383]HP47. NextNorth80/Right23/West200turnwasinterrupted,ended245946[-6699,-4088]North2224HP27. Recovery1attachedslot0used→77,thenStalkergrab/hits→246367HP32South3984sameposition.16escapecycles/South200→246730[-6923,2552]HP11. Left21/West150→246936[-12107,2104]West3016HP11MP12; this islastsafeinputboundary. TriedWest12/North23/Crossstairs,hit13killed247168[-12350,1354]HP-2. Archive dryfield-night-balcony-return-failed. KilledonlyownedPID78424 afterdeath; cleaninitialcards restored (renamedoldoutputcards). prefix now246936, nextlaunchsamefixedbinary/FIFO toboundary; plan immediateHealing7 beforestairs. JerryCan279 andMasterkey275 preserved in replay. Noenginebugproved,noGHmutations.


### 2026-11-04 — JerryCan returned to ParkingLot; fuel interaction blocked by combat
Originalreturnfailed247168HP-2nearstairs,archivebalcony-return-failed. Recoveryto246936HP11failedcastbeforeenemyhit;archived/tmp/pe2-folder-fix-live-20261104/return-retry-failed.pad. Recoveredearlier245573HP47viafullphysicalreplay, ownedPID93628(session39864). Start35attachmentmenu245686/Cross35→245801Recovery1usedHP47→92. North80→245916[-5797,2386]safe; intendedWestturninterruptedhit26andranNorth→246149[-6699,-2996]HP66. IsolatedturnRight19→West3016,Right25→South64;South145→246343[-6195,2107]. Left25verifiedWest3104;West170→246543[-12108,2399];Left24/North30/Cross→246737escapeHP66MP13. Cross→246992ParkingLot4771,2237South,Kanister279retained. Archiveddryfield-night-jerrycan-parking replay/live/cleaninitialcards (safe retrypoint). South20/East165/Cross→247510MainStreet[-6673,2155]East. DesertChaserrespawned200, avoidedbyNorth160to[-6699,-2927],East184/Cross→248196GasStation1variant2HP66MP13. East340→10500,-3482,2ZebraStalkers180. South82→10738,-728insidefueltriggerx12736±2416/z-384±704facingSouth. Select1opensVibrationoption,notfullinventory;Startonlyattachmentsbecausebattleactive. TryingCrossatfueltriggerattacked:249274HP12grab;escape16→249517HP7,Triangle35openHealing7butCrosscastinterruptedhit13→249647HP-6MP13unchanged. Kanisternotfilled. Archive dryfield-night-fuel-stalker-failed. NeedrecoverParkingLot246992,attachremaining2Recovery1(oneeachslot)andMPboost/usebeforefight,thenkill2Stalkersbeforekeyitemmenu; fuelkeyhandlerrequiresactiveRoomEventtriggerhit andJerryCan279. GasStationUseJerryCanMsg3173; actualfueltrigger12736,-384. Currentowned39864/PID93628stopped249647dead; noenginebugproved,noGHmutations.

### 2026-11-04 — Holy Water collected and attached

Physical replay reached the Loft safe at (-5020,-1628), facing north, before collecting JerryCan. Entered 4487 using ordinary CAP choices; 1-sample navigation can miss polling, 8-sample pulses confirmed selected indices 4/4/8/7 and opened the safe. Collected item56 and moved it through the full inventory menu to armor attachment2, replacing Tonfa. Recovery1 remains attached in slot1. Read-only runtime inventory confirms item56 attachSlot2, HP69 MP23. Fixture: `build-port/reference/dryfield-night-holy-water-attached/`, replay boundary245863, clean initial cards included. No engine change needed. Current owned process34638 / LLDB PTY94071.

JerryCan279 subsequently collected at physical replay boundary247182 with HolyWater still attached and HP69 MP23. Combined fixture: `build-port/reference/dryfield-night-holy-water-jerrycan/`. Next: leave Loft, heal before balcony Stalkers, reach GasStation and obtain Gasoline280.

### 2026-11-04 — Holy Water return to parking

Reached ParkingLot15 warp5 physically, with JerryCan279 and HolyWater56 still attached2. Loft exit cost no damage; balcony Stalkers interrupted movement/grabbed twice. Escaped both grabs through normal input and used Recovery1 once during battle (17→67 before chip damage); parking arrival31HP25MP. Used second Recovery1 outside battle to reach81HP, then attached last Recovery1 slot1. Boundary251834, fixture `build-port/reference/dryfield-night-holy-water-parking-ready/`. Owned PID34638 / LLDB94071. No engine defect established in this route; next GasStation fuel combat.

### 2026-11-04 — Gasoline obtained

Physical route ParkingLot→MainStreet north bypass→GasStation completed without damage. Killed both night Zebra Stalkers: first180→72→0 using two Pyrokinesis2 casts; second180→78 using Pyro2 then M93R held R1 fire78→11→0. Short R1 attempts before target acquisition spent no ammo; held fire after menu close succeeded. Battle reward yielded EXP1500, MP14; HP81 unchanged. Full Key Item menu Use JerryCan at(10708,-883), yaw4061, correctly spawned fuel event and replaced key279 with Gasoline280. Verified obtained notice and runtime collected list. Fixture `build-port/reference/dryfield-night-gasoline-collected/`, sample255628. HolyWater remains attached2, Recovery1 attached1. No engine fix required. Next return fuel to Douglas. Owned PID34638 LLDB94071.

### 2026-11-04 — Douglas refueling scene completed

Returned physically from GasStation through MainStreet/Driveway/Factory to Garage24 variant2 (no enemies). Bats on Driveway reduced HP81→69; escaped grabs with normal input. Factory car bypass requires west of car until z3732, then east to~5500 and south6600; Garage door faces EAST. Garage approach via north of car reached refueling hotspot(5047,5058), facingSouth. Gasoline280 consumed, refueling scene played, Douglas dialogue completed and shop opened. Exited shop ordinarily; eventState0, uiOpen0, player input enabled. HP69 MP15. Fixture `build-port/reference/dryfield-night-douglas-refueled/`, sample264075. Owned PID34638 PTY94071. No new engine bug demonstrated. Next resupply and continue post-refueling story/Room6 rest.

### 2026-11-04 — Post-refueling resupply

Douglas shop reopens normally after refueling. Bought4Recovery1 (400BP),3MPBoost1 (960BP), BP3130→1770. Used one carried Recovery1 and one MPBoost1 through ordinary inventory Use; HP69→105, MP15→43. Remaining4Recovery1 (one attached1),3MPBoost1; HolyWater attached2. Fixture `build-port/reference/dryfield-night-refueled-resupplied/`, sample267010, ownedPID34638/PT Y94071. Source confirms Room6 rest interaction gates on refueling and advances area layouts; next physically return toRoom6 and rest. No source fix required in shop/inventory flow.

### 2026-11-04 — Return toward motel after refueling

Owned34638/94071 continued267010 onward. Garage exit successful. Factory bypass needed explicit checked headings: from~5500,3580 south to4308, west then north blocked near3914,3152; west20run to3247 then north60 reached1029; east55/Cross→Driveway25 variant3. Bats interrupted turning/running; escaped via physical alternating inputs. HP105→75, MP43 unchanged. Reached west Driveway exit and continued at271115; current snapshot/replay in `build-port/reference/dryfield-night-post-fuel-return/`. No new engine defect established. Next MainStreet→ParkingLot→Balcony→Room6 rest.

Correction/continuation:271115 was still Driveway25, HP66, not a completed exit. Escaped another bat hold; Pyro2 at271421 killed2bats, MP43→36 HP63. Explicit heading3064 thenWest25/Cross produced escape result271551. Confirm→271736 MainStreet2, HP63 MP37. Fixture `build-port/reference/dryfield-night-post-fuel-mainstreet/`. Next ParkingLot via west/north bypass; Room6 rest remains untested.

### 2026-11-04 — Room6 rest reached, completion under investigation

Returned MainStreet→Parking15 variant2→Balcony29 variant6→Room6 area30, HP63MP37 unchanged. No enemies on these post-refuel areas. BedCAP available; initial mistakenUp wrapped defaultTakeNap0 toStay1. Reopened; read-only choice index0/count2/stride1 then confirmedTakeNap; CAP says sleepy/lie down and Aya animates, but at278420 HP63MP37 and room variant1 remain. Rest completion NOT verified. Fixture `build-port/reference/dryfield-night-room6-rest-investigation/`; inspect live CAP/rest task lifecycle before diagnosing bug. Owned34638/PT Y94071.

### 2026-11-04 — Rest verified, false alarm resolved

No rest engine bug: first Up wrappedTakeNap0 toStay1. CAP16 persists counter in flag70, switching later prompts to sleepy choices NotYet(default0,key11)/ReallyTired(1,key10). Prior repeatedCross choseNotYet; animation moved Aya back toz1668 outside bed trigger. Read-only task/caption inspection established this. Physically walkedSouth20 back inside trigger, reopenedCAP16; Right8 selectedReallyTired, Cross35 confirmed. Breakpoint atRestTask state2 saw key10, then normal continuation restoredHP105/MP43 and loaded area8 dream, event1. Boundary279755; fixture `build-port/reference/dryfield-night-room6-rest-complete/`. No source changes warranted. Owned34638/94071; breakpoint2 disabled, pad breakpoint1 active. Next dream scene and post-rest story.

Post-rest dream area8 animated through views3→8 and returned toBalcony29 room2 variant2 warp5, event1. Wake-up FMV active; RGB24 export correctly showsAya waking in bed (16-bit export looks like noise, not rendering bug). Continued neutral input through285355, movie imagery changes; film not yet completed. Fixture `build-port/reference/dryfield-night-post-rest-movie/`. HP105MP43. Live34638/94071 padbreakpoint1 at285355, taskbreakpoint2disabled.

### 2026-11-04 — Burner arrival shadow crash, fix under validation

Post-rest wake-up FMV progressed normally (RGB24), then Burner arrival rendered on Balcony29 view18. At actual physical sample290599 livePID34638 crashed EXC_BAD_ACCESS0x38 in worldCollisionProjectGroundPoint, caller_actor335800SceneGroundShadowTask line1022. Task dump bodyKind255, callbackNoop, workNULL; coordinate body retained pointer but coordNULL: taskKill had released coordinate body then function fell through togroundprojection. Added return after all four taskKill exits in this callback; live ticks unchanged. Build passed. Original crash process preserved in94071. Fixture `build-port/reference/dryfield-night-burner-shadow-crash/` containscrash.pad/backtrace/initialcards/through.pad extendingneutralto291055. Independent fixed replay launchedPTY6457 withvideoclock/virtualraster,cleanvalidationcards,expect stage3/area29/HP105; result pending. Requestedload(end)291055 is NOT reached by original process(actual290599). Do not resume original crash. Next poll6457 and inspectfixedsnapshot; then launchcorrectedcontrolledruntime/replay forcontinuation.

Burner shadow regression: independent replay6457 exited0, all3expectations passed(stage3/area29/HP105) at291055, normal replay completion. Archivedvalidation.txt/fixed-live.json. New controlled LLDB91306 launching frozen correctedbinary `/tmp/pe2-burner-shadow-fixed-live-20261104/parasite-eve-ii-pc` with same291055prefix, cleaninitialcards, video/virtualclocks. Original34638 crash preserved. Next waitnewcontrolledrun→291055 and comparefullfinite/live state beforefurtherinput.

### 2026-11-04 — Corrected runtime continued into Burner fight

New controlledPID13511/PT Y91306 reached291055; FULL finite/live snapshot equality True, addedcontrolled-live.json/validation.txt tocrashfixture. Continuedneutral900: fightstarted,AyaHP67,event0,near(-6420,10238). AttachedRecovery1used→105HP; freshSquare35 afterinitialshotsofftarget successfullylocksBurner, heldR1damage4650→4607→4534. Aya105MP43 at292662, M93Rmagazine0 (total488beforecurrentbursts),3carriedRecovery1remain,3MPBoost. Fixture `build-port/reference/dryfield-night-burner-combat/`. Bossactualcallback_actor403100Task; HPreadvia_gActor403100Enemy, notyetincensus. No furthercrash. Currenthelper91306/tmp/pe2-burner-shadow-fixed-live-20261104, end292662. Original94071/PID34638remainsatcrash290599, preserve. Nextreloadandcontinuefight, inspectpositionsforflameavoidance.

### 2026-11-04 — Burner fight294442

HeldM93R fire and freshR1 afterempty magazine auto-reloads correctly: Burner4534→4418→4390→4194→4063. Flamehit105→86→67. InitialPyrointerruptedbeforeMPspend; neutral45 thenTriangle35/readwheel0/Cross35/neutral100 succeeded, Burner4063→3957, MP43→36, Aya67. Added_actor403100Task toread-only checkpointenemycensus (EnemyfromspawnArg2, standardTMDroot); pycompile andliveinspectionpassed. Fixture `build-port/reference/dryfield-night-burner-fight-progress/`, boundary294442. Current13511/91306, correctedshadowbinary, oldcrashpreserved. Fightongoing, notwon;3Recovery1carriedbutattachedslot1spent, HolyWaterattached2,3MPBoostunattached. Needtimedmovementtoavoidflames andhealingPE7 ifHPdrops; avoidblindlongstandingfire.

Burner continued294442→296532. Gun3957→3816→3701; Aya67→48. Healing1 successful48→94,MP36→24. WheelRight cycleslearned0→1→7; Downhasnoeffect. Cross35neededtoleaveaim/reaction beforeturn, thenLeft9heading984East/run75 movedx-6406→-4219,z10373. Flamehit94→75; gunboss3701→3634, furthercontinued296532 (snapshotauthoritative). Fixture `build-port/reference/dryfield-night-burner-fight-progress2/`. Live13511/91306. Fightongoing; no newenginefault.

Burner296532→298406: approachNorthblockedat(-4247,9601), Aya56→44. Healing7 cast restoredthenhit→60MP12. BattleStartemptyattachmentCross cannotrefillfromcarried. Closedmenu, West40/North100 reached(-5453,6350)withoutdamage, thenaim/fire gotarm/flamehits60→45→27, boss3506→3446. FirstHealinginputignored; secondTriangleconfirmedwheel7 thenCross cast, Aya46MP0 at298406. Fixture `build-port/reference/dryfield-night-burner-fight-progress3/`. No newenginebug; combatstrategycurrentlypoor, needdodge/reposition andmayreplayfromprecombat toattachMPBoost orbetterweapon. Do notclaimbossdefeated. Live13511/91306.

### 2026-11-04 — Burner retry preparation

Currentfight298406 leavesAya46MP0,boss3446; archivedbeforeabandonment. StrategycheckedexternalBurnerwiki: Necrosis recommended, runalongbalconytododgeflame. Source_actor403100ProcessCombatContacts supportsdamageovertime(quartered); noenginechangeproposed. Killedonlyowned13511 afterarchiving; launchednewcontrolledPID13387 inexistingLLDB91306 withcorrectedshadowbinary(stilltarget/tmp/pe2-burner-shadow-fixed-live-20261104/parasite-eve-ii-pc), envpaths `/tmp/pe2-burner-prep-retry-20261104/`, cleaninitialcards andprefix274200(beforebed). Processconfirmedrunning. Nextwait91306 firstpadstop274200, reacquiretarget/pad_addr, fullmenuP.Energy unlockNecrosis using1500EXP, attachMPBoost replacingempty/RecoverywhilekeepingHolyWater. Thenrest/selectcorrectyes andretryboss. Originalcrash34638/94071untouched. HelperupdatednewFIFOdir,end274200(requesteduntilstop).

### 2026-11-04 — Necrosis and MPBoost prepared physically

RetryPID13387/91306 reached274200 Room6. OrdinaryStart→P.Energy→Necrosis→Revive→Yes spent500EXP (1500→1000), learnedlevels[3]=1, maxMP43→44 andMPfilled44. Level2cost1200 exceedsremaining1000, declined. OrdinaryUseinventory movedMPBoost1 item6 row13 toattachment1 replacingRecovery1; HolyWater56 retainedattachment2. Runtimeverified;4Recovery1 nowcarried,3MPBoost total(oneattached). HP63MP44 beforefreebedrest. Fixture `build-port/reference/dryfield-night-necrosis-prepared/`, boundary275349. Fullmenuopen, nextCircle2close, bedrouteWest60/South30 thenWest28/Cross, defaultTakeNap0 confirm directly(noUp); watchsecondchoiceNotYet/ReallyTired ifcounterchanged. LivehelpernewFIFOdir/tmp/pe2-burner-prep-retry-20261104.

### 2026-11-04 — Necrosis retry in combat

Closedinventory, bedroute at275823. Firstprompt defaultCross eventuallydeclined; actualsecondprompt NotYet/ReallyTired Right8/Cross accepted277148→277899 dream, restored105HP44MP. Neutral10000 then800/400/350 broughtBurnerfight289449HP90; no recurring shadowcrash. Triangleinitialhurtignored, retryopenedwheel0; Righttwice→Necrosis3, Cross35/neutral140 cast289781MP44→37, boss4650→4634 reactionFlags4(activeDOT). AftercastCross/turninitialignored; secondLeft23thenSouthrun120 reached(-6629,8360),HP71,boss4588 at289994. Fixture `build-port/reference/dryfield-night-burner-necrosis-active/`. Live13387/91306 helper/tmp/pe2-burner-prep-retry-20261104. Necrosisworking; needdodgeflameearlierandgun/refreshDOT; MPBoostattached1 HolyWater2.

Necrosisretry289994→295003: gun/DOT boss4588→4441→4290→4180→4079. Aya71→37; Healing7(rightfromNecrosis3) restored83MP25. DOTexpired(reactionFlags0). Attemptrefreshignored(noMPspent); subsequentgun4040→3928→3660→3444. Aya64→45→35 thenBurnergrab: menusignorednormally. Escapes2/8samplealternations reducedgrab, player18HP; bossstate5/substate9 releaseanimationstillheldcontrol until294868. Trianglefinallymode1; Crosscast at295003. Snapshotauthoritative `build-port/reference/dryfield-night-necrosis-fight-progress2/`. Needavoidstandingwhilesubstategrabapproaches; noenginebugestablished. Live13387/91306, MPBoostattached1stillunused.

Necrosisretry295003→296990: StartinitiallyignoredwhileplayerstateTimer40; thirdStartopenedbattleattachments. UsedMPBoost1 slot1→MP13→38 (+25), HolyWater2preserved. Necrosisrefresh7MPconfirmedreactionFlags4 andboss3444→3429. Gun/DOT3429→3133→3037;Aya53→35. SeveralTriangleedgesignoredduringforcedmotions(noMPspend); only296839mode1/wheel3confirmed. Right→Healing7 Crosscast296990; snapshotauthoritative in `build-port/reference/dryfield-night-necrosis-fight-progress3/`. Current13387/91306. Fightnotcomplete, attachMPBoostspent,2MPboostcarriedunattached.

BurnerNecrosisretry296990→300085: gun3037→2821→2603→2541, Aya73→54→39. Healing7confirmedmode1 thenCross39→healed+flamehit→54, MP19→7. Continuedgunboss2347→2269(underhalf), then300085snapshotauthoritative. No newcrash. Fixture `build-port/reference/dryfield-night-burner-below-half/`. MPBoostattachedspent; HolyWaterstill2,2MPboost/4Recoverycarriedunavailableinbattle. Bossstate4sub6 at299173(jumprecovery). Needreacttoflame/jumpandconservehealth; Necrosislast7MPstillpossible, healingrequires12. Live13387/91306.

Burner300085→301485: shortgun100/160samplechecks inrecovery states3.4/4.7/4.8 reduced2142→2130→2089→2001→1944,Aya39unchanged. Atstate5.3 grabapproach,triedCross35/Right13/Northrun90; too late, Ayaalreadyheld/flying[-3055,-8101,7598],HP39. Alternatedall8face/directions4samples each2x320samples; state10grab, HP35 afterfirstset. Snapshotaftersecondauthoritative in `build-port/reference/dryfield-night-burner-under-2000/`. Needwaitreleaseandavoidnextattack;MP7 cannotHealing12. Live13387/91306. Noenginefault.

Burner301485→303002: waitedreleaseuntil301775 PEmode1, LeftfromHealing7→Necrosis3/Crosscastlast7MP; reactionFlags4confirmed, boss1944→1929. Gun/recoverychecksboss1829→1706;Aya27unchanged. At4.8 recovery canceledaimCross35/Left13+5→South~0 andrun170 movedNorthend(-7100,-1200)→(-6247,4895), avoidedattackHP27; boss1660. State3.1 flame: continuedSouth110 thenSquare/R1 foundactorstillSouth, position(-6178,6758), HP27,boss1614. State6.1sideflame;Cross35 thenSouth90→303002snapshotauthoritative. Fixture `build-port/reference/dryfield-night-burner-dodge/`. Needcontinueavoidance, thenreacquiretargetwhenplayernormal; MP0. Live13387/91306. Noenginebug.

### 2026-11-04 — Burner retreated (not defeated)

303002event1 wasretreatscene. Continuednormalneutral450/800/900→305152battleResult1000EXP/0BP/0MP, ItemObtained. Confirm→lootRecovery2+MPBoost1, All→305402ordinarybalconycontrol,variant4,room3. ReadflagGAME_FLAG_BURNER_DEFEATED0x73=0; source_actor403100FinishSceneDeparture halvesEXPandclearsBP/MP, confirmsretreatnotkill. Collectedloot;HP27MP0EXP2000. Fixture `build-port/reference/dryfield-night-burner-retreated/`. No enginecrash inentirefight/outro aftershadowfix. NexthealwithcarriedRecovery2/MPboost, inspectDouglas/Flintstory, continueprogress. Do notclaimBurnerkilled/Flintsaved. Retrypre-restfixturepreservedifneedbetteroutcome. Live13387/91306end305402.

Post-retreat305550 fullUse menu: usednewRecovery2→HP27→105 at305786. ReopenedUse andMPBoost1→306221, snapshot `build-port/reference/dryfield-night-post-burner-healed/`. Normalcontrol/menu andlootflowverified. CurrentfullmenuafterMPuse; closeCircle2+Circletoordinarycontrol. Needattachreplacementhealing/MPbeforeenemies, continuestory.

### 2026-11-04 — Post-Burner Room6 return

ReattachedRecovery1 row9→slot1 throughfullUse/Move; HolyWater2unchanged. BalconyNorth30/Westwalk28/Cross→Room6area30 at307080. HP105MP30. Attemptnativephone save notyetcompleted: closetCAP9at975,1500; northdeskCAP3regionblockedz1021; CAP5/11SouthportraitconfirmedAnnieOakley(longpagesclosed); actualphonevisibleatbedsideleft, command22region352,5568. Roomgeometrybed/tableblocksapproach; current311444 pos1320,4870South, no saveclaim. Sourcecommand22spawnsroomcutscene(CAPfiledependingchapter), phone menuincludedbutnotyetactivated. Fixture `build-port/reference/dryfield-night-post-burner-room6/`. Next reachphonecloselyorcontinueDougnearRoom1; walkthroughconfirmsTruckKeythere, thenKyleGarage. BurnerretreatkillsFlint perguide, so noM950reward later; userhasnotrequiredspecificending. No newenginefaultproved. Live13387/91306end311444.

PostBurnerRoom6 continued311444→313435. Phoneattemptstillnotcompleted; apparentbedsidephoneactuallyrouteblockedbybed/tableandoutsideledge. MovedSouthto6975/East? thenWest35to690,6909,North35blocked6600; Westface/Cross313235transitiontoWaterTower20, playerworktransientunavailable(HP105) asnormalroomload. Neutral200→313435snapshotauthoritative. Fixture `build-port/reference/dryfield-night-post-burner-room-exit/`. No savemade, noenginebugestablished. NextWaterTowerroute→Breezeway/ParkingtoDougRoom1TruckKey. Live13387/91306end313435.

PostBurner313435→315382: WaterTowerSouth185/EastCross escaped→Breezeway22 at313996(noinjury), butBreezewayonlyleadsFactory, so returnedTower20. North/WestmovementsinterruptedStalkers105→85→65. CorrectNorthbypass after[3570,-2331]:North85→[3623,-3708],North55/West170→[-2729,-5699],Northface/Cross escapeandconfirm→315382NightKitchen. Fixture `build-port/reference/dryfield-night-post-burner-kitchen/`. NextSaloon→ParkingtoDougRoom1TruckKey. HP65MP32expectedescapeincrements; snapshotauthoritative. Recovery1attached1 HolyWater2. Live13387/91306. Noenginebugproved.

PostBurner315382→318531: KitchenWest30/Cross→Saloon18 at315735,65HP. West60/North240furnituredeflectedto1371,-1929, East30/North80/Cross→Parking15variant4 at316609. GaryactuallyMainStreet2 nearRoom1(area11), notParking. ParkingSouth/East routeblockednear1334,1047; correctedSouth60/East240→9299,3500,Chaserhits65→27andgrab. Escapealternating16/Start→battleRecovery1used23→73thenhit60. East25/Cross+resultconfirm→318531snapshotauthoritativeMainStreet. Fixture `build-port/reference/dryfield-night-post-burner-mainstreet/`. NextMainStreetNorthalongwestside toRoom1trigger(-6912,-2816) andGaryactor136100nearby; TruckKey278missing. Recoveryattachedspent,3carriedleft. Live13387/91306. Noenginebug.

Correction:318531 and318829 remainedParking15 (HP34→29), exitinputsinterruptedbyChasergrab. Alternatingescape16cycles+East20/Cross then319172 finallyMainStreet2(-6673,2155),HP29MP32. Updatedpost-burner-mainstreetfixture replay/live to319172. Nexthealfirst(fullmenuorHealing7 afterload), thenNorth~130toRoom1near(-6912,-2816) andDoug. Do notclaimTruckKeyyet.


### 2026-11-04 — Disc 2 / Mesa asset reload crash

Post-Burner route reached Douglas's mourning scene, then Kyle in Garage. Truck Key collection bit 278 is set; full Kyle conversation and departure choice passed. At pad 370310 the game requests Disc 2; both USA images pass built-in `--validate-discs`. The waiting original PID13387 remains stopped in the native host selector, with 75 HP / 32 MP and Holy Water attached in slot 2.

Two independent full replays with Disc 2 configured crashed at pad 370832 on the first Mesa model draw (stage 4, area 1). `gAya10300BodyModel.handlersResolved` is 1 but `_gAya10300BodyModelStream` contains the raw handler slot 0. The handler registry itself is valid (19 entries). `peHostSwapDisc` calls `peAssetsLoad`, which recopies common arrays over runtime TMD fixups while the owning source retains its resolved flag.

Changed `asset_loader.c` to remember successful bindings and populate only missing bindings on subsequent mounts. This also preserves room-owned mutations across swaps. Updated `asset_disc_cache_test` checks that a simulated resolved handler survives, a missing package is retried, and Disc 2 supplies its previously missing binding. Fixed unit test passes; equivalent pre-fix loader fails the second-disc assertion. Full build and `git diff --check` pass. Full fixed replay passed at pad 372310 (exit 0; stage 4, area 1 and HP 75 assertions). Its full snapshot equals the independent controlled replay snapshot at the same boundary. Controlled PID52501/session35121 subsequently completed the arrival FMV and first Kyle conversation at pad378628 without a fault (75HP/32MP). Kyle HP5 is explicitly authored by the Mesa arrival task. Live control is now /tmp/pe2-disc2-fixed-live-20261104; fixture mine-mesa-arrival-disc2 preserves current progress. Extended the read-only enemy census to stage 4 and verified the Mesa Desert Chaser record. Fixtures/evidence: `build-port/reference/dryfield-night-disc2-request/`. Crashed old controlled PID97654/session32092 remains stopped for inspection. No commits or GitHub mutations.


Mesa combat attempt: physically attached Recovery1 in slot1, retained HolyWater2, Healing75→105/MP32→20, approached west battle trigger. Killed intro Chaser (200HP) at381033. Subsequent scripted scene starts ten-enemy wave; initial idle advance overran scene end, Aya45→27. Used attached Recovery1, then Healing and Pyro2 (cost7, hit156→53), killed another Chaser and one jumped off cliff. At386385 wave remaining8, Aya10HP1MP, two Chasers117/200. No new port fault established. Saved mine-mesa-first-wave-attempt; PID52501/session35121 stopped. Started legitimate full input replay retry from mine-mesa-arrival-disc2 boundary378628: PID46521/session13908, /tmp/pe2-mesa-retry-20261104. On EOF import replay_checkpoint, set target/pad_addr0x100e2cc20, switch advance helper session/FIFO and end378628. Next use carriedRecovery1 out of battle to105 (keepMP32), attachMPBoost1slot1 (keepHolyWater2), reloadM93R before trigger; use shorter combat checks and movement to avoid repeated grabs. Retry currently running, not yet claimed at EOF.

Mesa retry reached exact378628snapshot. UsedRecoveryoutbattleHP105/MP32, attachedMPBoost1slot1/HolyWater2, reloadedM93R20; fixture mine-mesa-prepared-retry380112. Northboundarytriggerallowedrangebuttruckblockedtargeting untilmovingaroundright. IntroChaser finallykilled382822 HP82MP18, reloaded20beforecutscene. Checkedsceneendin100samplebatches;383960 event0 begins10enemywave withHP82unchanged,MPBoostattachedunused. Fixture mine-mesa-wave-retry-start. CurrentPID46521/session13908, end383960 FIFO/tmp/pe2-mesa-retry-20261104. OldattemptPID52501/session35121 remainsstoppedHP10. No newenginebug.

Mesa retry383960→386665: wave1killed (9remaining), MPBoostused6→31, Healing41→78thenhit55, Pyro2target200→99 thenM93Rkilled385828. SubsequentPyro/gunattemptnearNorthedge9638,527 endedChaserthrow: Aya[11005,6000,-6542] HP-2111 deathVariant1. Savedmine-mesa-retry-cliff-death. Exactfataldamagecode notyettraced; noportbugclaim. Startednewphysicalreplayfromprepared380112 in session50332 (/tmp/pe2-mesa-healing2-retry-20261104), usepending_liveforhelper, doNOTcontinueold13908deadprocess. PlanbuyHealing2 outsidebattle with1750EXP (available2000): runtimegAttachmentLevelTable.rows23 amount40/healMax70 cast12 mpBonus1. KeepHolyWater2/MPBoost1. NeedfightawayfromNorthcliffedge andtryCombustion1 coneifbothfoesclose (cast14 amount120). Previousattemptcurrent46521/session13908retaineddead, originalfirst52501/session35121 HP10stillretained.

ConfirmedMesa fatalfall in actor_00100.c: playerY clamps6000 then PLAYER_FALL_ATTACK appliesup to10timesuntilfatal. PreviousHP-2111 matchesauthoredfallpath, noenginefault. NewretryPID11327/session50332 reached380112exactfullsnapshotmatch. PhysicallystrengthenedHealing2for1750EXP, EXP2000→250 MPmax44→45 refilled45, HP105. MPBoost1slot1 HolyWater2 M93R20. TruckboxopenedCAP1andclosednormally; empty. Fixturemine-mesa-healing2-prepared381273 (ordinarycontrolneartruck7777,2398yaw106). CurrentFIFO/tmp/pe2-mesa-healing2-retry-20261104/control.fifo.

- 2026-11-04 Mesa continuation: Healing II physically purchased; intro Chaser knocked off cliff with Combustion; two of ten wave Chasers killed (Pyrokinesis II finishing blows). Replay/state archived in `build-port/reference/mine-mesa-healing2-wave-progress` at input 387019, HP63/MP18, Holy Water attached slot2. No additional native crash observed during this attempt; battle remains unfinished.

- Mesa retry ended in ordinary combat death at input388342 (HP-2, MP18), archived `mine-mesa-healing2-wave-death`. Healing II attempts repeatedly interrupted before MP debit. Read-through of actor00100 caught-player handling shows timed/animation-driven release, not a pad-mashing escape check in that path. Next attempt: short neutral waits during scripted hold, movement immediately after release; avoid accidental PE opening from alternating buttons. No new port defect established.

- Mesa timed-release retry: physically replayed to383217 in isolated cards/process61951; safe west-to-south truck bypass (x2567 then z6007) reached open shooting area. Repositioning before Healing II succeeded at384455 (HP59→105, MP31→19). Archived replay/state at384557 in `mine-mesa-south-route-healed`; MP Boost remains unused and Holy Water attached2. Battle ongoing, no wave kills in this retry yet.

- Timed-release Mesa retry progressed to387101: one wave kill, HP37/MP13, M93R8; replay/state archived `mine-mesa-timed-release-wave-progress`. Verified neutral-only release of scripted hold in live game. MP Boost used (19→44); Pyrokinesis II finished first wave Chaser at385388, Healing II restored HP at385556 and386901. Still repeatedly caught during stationary fire; no new native crash or proven port defect.

- Mesa timed-release retry reached second wave kill at388838, HP47/MP1. Repositioning around truck allowed heal37→93; right-side shooting at9876,6284 subsequently killed Chaser151→0 with no HP loss. Archived `mine-mesa-timed-release-two-kills`. Full wave remains unfinished; no additional native crash observed.

- Mesa input389685: third wave Chaser killed (HP-7/death20), Aya27HP/1MP, M93R11. Right-side arena position allowed two consecutive wave kills. Counter verified8 at389055 after second removal; third death still pending removal. Replay/state archived `mine-mesa-timed-release-three-kills`. Encounter unfinished and no new port defect established.

- Mesa input390670: fourth wave Chaser killed (HP-7/death20), Aya14HP/1MP/M93R11. Wave counter7 confirmed389896 after third release. Fourth kill recording/state preserved in `mine-mesa-timed-release-four-kills`; encounter remains unfinished. No new native crash or confirmed port defect.

- Mesa timed-release attempt ended by393392 in normal death/game-over transition (player unavailable, HP-5, area0), archived `mine-mesa-timed-release-terminal`. Four wave kills, remaining6 verified390935. Continuous truck circling kept HP2 from390805 through393041 and enabled Kyle to lower both live enemies to170HP. Death occurred inside393041→393392 movement batch; exact sample not isolated. Next retry should prepare carried Recovery1 in an accessible attachment and inspect corners in shorter intervals. No additional native crash.

- New Mesa preparation at382148 (PID64006): replay at381273 exactly matched archived state; physically attached carried Recovery1 in slot3 while preserving MPBoost1 slot1/HolyWater slot2. HP105/MP45/HealingII/M93R20, before battle. Saved `mine-mesa-recovery-attached-prepared` with initial cards and full recorded input. Prior attempts had Recovery carried but inaccessible during combat.

- Recovery-attached retry ended at383431 in intro cliff death: HP-2990, rootY6000/z-6578, state6mode1; archived `mine-mesa-recovery-intro-cliff-death`. Intro Chaser163HP, no wave kills. Eastern/northern trigger produced southern Chaser, whose throw drove Aya north. This matches previously verified authored fall mechanic; no new native crash. Prepared prebattle recovery checkpoint remains available; next entry should start from southwest/lower field.

- New south-entry route reproduced recovery-prepared checkpoint exactly and killed intro Chaser with only7MP used (PyrokinesisII, aided by Kyle/bullets). Main wave control returned at384995: HP82/MP38, HealingII, Recovery1 attached3 and MPBoost1 attached1 unused, HolyWater2. Archived replay/state `mine-mesa-south-entry-wave-start` (PID79194). Main wave still uncompleted, no new native crash.

- South-entry wave retry at387117: THREE kills confirmed by remaining7, Aya105HP/12MP after HealingII, Recovery1slot3 and MPBoost1slot1 still unused, HolyWater2. PyrokinesisII hit two nearby Chasers, then bullets finished both; only23HP lost during wave before heal. Archived full replay/state `mine-mesa-south-entry-three-kills-healed`, PID79194. Main wave remains unfinished; no new native crash.

- South-entry retry input388941: FOUR wave kills, remaining6 verified388896, Aya82HP/23MP with attached Recovery1 still unused; MPBoost used12→37 earlier. Fourth kill via Pyro123→17 then bullets. Moved off southern boundary after hold release; replay/state archived `mine-mesa-south-entry-four-kills`. No new native crash; encounter unfinished.

- South-entry Mesa at390141: FIFTH wave Chaser killed (HP-4/state21 pending removal). Aya56HP/16MP, M93R2; Recovery1 consumed through attachment menu (Start,Right2,index2,Cross), HolyWater remains2. Pyrokinesis113→10 then bullets finished fifth. Replay/state archived `mine-mesa-south-entry-five-kills`; half-wave remains. No new native crash or proven port defect.

- Mesa south-entry attempt at392240 reached SEVEN wave kills: sixth fell outside arena (remaining4 verified391317), seventh shot4→-4 (pending death release). Aya3HP/4MP/M93R13, all healing consumed, HolyWater2 retained. Archived `mine-mesa-south-entry-seven-kills`; native game still running/stopped at input boundary. Held-state R1 edges were ignored in earlier attempts; explicit state2/mode0 check enabled seventh kill. Encounter unfinished; no new native crash.

- Mesa retry reached EIGHT wave kills at394330 (remaining2, Aya3HP/4MP). Continuous counterclockwise truck circuit avoided damage and Kyle lowered surviving Chaser159→129; another Chaser fell, supplying eighth kill. Fatal following batch394330→394536: new NW Chaser caught Aya on northern traverse, HP-9/deathstate10. Preserved `mine-mesa-south-entry-eight-kills` prefix with observed subset (full snapshot not captured there), plus `mine-mesa-south-entry-eight-kills-death` full replay/live death snapshot. No new native crash.

- **Mesa wave completed physically at396559 (2026-11-04).** Remaining kills0, roomEnemies empty, battleRefs0, event0; Aya survived3HP, MP restored45, EXP250→1075. Replayed eight-kill prefix394330 and verified observed state, filled missing full snapshot. Backward65 followed west/south sidestep avoided fatal prior route. Circling caused ninth cliff kill; Kyle knocked final129→114; bullets finished114→-15 at396209. Full replay + initial cards/live state archived `mine-mesa-wave-victory` (PID74798). No RAM writes/target calls; no new native crash. Next heal, then west mine entrance.

- **Entered mine after Mesa victory at397889:** stage4/area3, roomState1/view2/warp1/variant1, event0 ordinarycontrol; HP83/MP21 after two HealingII uses. Collected all battle drops: Recovery3×1, Hydra9mm×50, Rifle5.56×80; BP+550/EXP+825. HolyWater attached2. West exit including Kyle-concern dialogue completed without crash. Full input replay, initial cards, live state and screenshot archived `mine-entry-after-mesa-wave` (PID74798/LLDB94039). Next explore mine, find native save and prepare Hydra ammo.

- Mine Tunnel Entrance (area3) fully loaded census has2 Chasers +5 moths; prior empty census at arrival was transient. Physically loaded Hydra20, attached Recovery3 slot3 (HolyWater2 unchanged). Initial aim selected moth despite Chasers approaching: extended replay_checkpoint.py common Enemy census with `targeted` for every supported actor, removed redundant Chaser-only assignment; py_compile and live targeted moth→Chaser verified. Recovery3 consumed22→105; at400046 Aya59HP21MP, Chasers130/200, Hydra12loaded, no native crash. Archived `mine-tunnel-entrance-first-fight`. Next finish combat or retreat to attach CombatLight before dark-room retry; preserve Mesa victory prefix.

- **Cleared Mine Tunnel Entrance battle and entered Forked Tunnel at402523.** Two Chasers+five moths defeated; results160EXP/190BP/13MP, status cleared. PyroII multi-hit followed manual Hydra fire finished Chasers (final31→-3); no new crash. HealingII restored35→75HP, MP20→8. Traversed entrance and north branch at2992,-624 into stage4/area7, roomState1/view3/warp1/variant1, position2350,10500 facingNorth. Full replay+initial cards/live state/screenshot archived `mine-forked-tunnel-arrival`. Save point still not reached.

- Forked Tunnel exploration: used authored brake lever (default Pull lever choice), watched wagon motion and passed prior block. Examined immovable doors and oak board; board only description under current progress flag, not collected. Returned to cleared Tunnel Entrance then entered main Mine Tunnel (stage4/area4) at405765: HP75/MP8,5actor01600 enemies85HP, player15600,1200 facingWest. No crash/newnativebug. Archived `mine-tunnel-arrival-cart-released` replay+initialcards/live state. Native save still not reached; next prepareCombatLight/Hydra and continue towardGorge/Refuge.

- Main Tunnel encounter: attached CombatLight3 (HolyWater2), PyroII killed3of5 enemies85HP withoutdamage; Hydra killed4th, last55HP remained when Hydra exhausted. Retreat toclearedarea3 succeeded (0EXP,-10BP,+1MP), no crash. Physically loadedPB20 and attachedPB105slot1 for combat reload. Learned MetabolismI for500EXP through nativePE menu; EXP735, maxMP46/fullMP46, then HealingII twice21→101HP and46→22MP. Archived safe preparedstate411008 in `mine-tunnel-retreat-rearmed-metabolism`. MainTunnel NOT cleared, savepoint notyet reached. Note newly learnedMetabolism changes waterwheeldefault; Down selectsHealing7 fromMetabolism6.

- Main Tunnel retry ended in ordinary combat death at413378 (HP-5/MP15), one of five Scavengers defeated; archived full input/live state in `mine-scavenger-five-press-retry-death`. Corrected combat assumption: actor01600 is Scavenger and its grab requests FIVE button presses (`actor_01600.c`, `_gActor01600GrabButtonPressHold`, `GAME_ACTOR_MESSAGE_AWAIT_BUTTON_PRESSES`), unlike Mesa Chaser timed hold. Five Up press/release cycles live changed held phase0 to phase1 at412060 without HP loss; subsequent escape also verified. Healing attempts interrupted before MP debit, Pyro missed submerged enemy. No proven port defect or new native crash. Safe prepared411008 fixture remains available.

- **Main Mine Tunnel cleared at413066** in isolated replay PID49407/LLDB75901. Exact full snapshot match at411008 verified before retry. Three Scavengers shot from eastern entrance; moved slightly west, waited for remaining two to surface, single PyroII killed46/85 HP together. Aya101HP unchanged throughout, MP22 to15 then25 reward, EXP735 to785, battleRefs0. Full replay/initialcards/live state archived `mine-main-tunnel-victory`. No new crash or proven port bug. Continue west to Gorge/Refuge native save.

- Reached **Gorge stage4/area5 at414548**, ordinary control at17800,1600 facingWest; HP101/MP25. MainTunnel west exit passed normally. Archived replay/initialcards/live/screenshot `mine-gorge-arrival`. Gorge census12 actor03700 HP1 (inactive initial action7), encounter not started; Refuge exit1408,3744 facesSouth. Native save still not reached. ActivePID49407/LLDB75901, FIFO `/tmp/pe2-mine-distance-retry-20261104/control.fifo`.

- **Oak board acquired at418754** after physically inspecting Gorge broken rails (CAP1 at11744,1568), returning through cleared MainTunnel and ForkedTunnel. Native Take-the-board choice confirmed, new collectedbit287. Earlier board inspection before bridge visit correctly offered only description. Aya101HP/25MP unchanged; no respawn in cleared tunnel, no new crash. Replay/initialcards/live snapshot archived `mine-oak-board-collected`. Current area7 at1119,1001,1682 yaw3016 PID49407/LLDB75901; return to Gorge bridge, then Refuge/save.

- **Gorge bridge repaired and 12-bat encounter cleared at425143.** Physically returned with board, used native KeyItem menu Board/Use at broken rail trigger; roomState2 and patch confirmation verified, walked beyond prior barrier. Bat wave20 started, bullets plus3 PyroII defeated all12; battleRefs0. Aya74HP at last kill, MP4 before reward. Archived full replay/initialcards/live `mine-gorge-bridge-bats-victory`. No new native crash/proven port defect; Refuge/save still ahead. ActivePID49407/LLDB75901 at425143.

- **Refuge reached425837 and native save completed428150**. Stage4area6, HP74/MP16/EXP845. Physically used telephone at1024,2416 facingWest, completed Baldwin/MIST story call, selected NewBlock then CreateYes. Save-complete screen observed; original AX9T2sJm card file byte-identical, new B/C/D 8192-byte files. Archived full replay, initialcards, live428220, screenshots and output `saved-cards` in `mine-refuge-native-save`. Native load not independently verified yet. ActivePID49407/LLDB75901, FIFO `/tmp/pe2-mine-distance-retry-20261104/control.fifo`. No new native crash/proven port defect. Next inspect Refuge supplies/power panel and continue story.

- Refuge supplies at429828: opened ammo case CAP3 at1024,4544 and accepted PB refill, carried160 now500. Bat reward includes MPBoost1 item6 (not Recovery3), preserved. Opened/examined/closed circuit panel normally; physical Square exits, Circle did not. Puzzle uses JumperPlug IDs0x120/0x12C (map_shelter catalog), despite battery naming in actor548100 comments. No plugs collected yet. Archived full replay/initialcards/live/outputcards `mine-refuge-ammo-resupply`; native save from428150 preserved. No new crash or proven port defect. ActivePID49407/75901 end429828 at1328,4345 yaw3080.

- **Refuge Gate1 powered at434386**: physically examined socket4, extracted Plug288 (collection verified432440), used Plug through socket2 Item menu, lowered main lever. Animated current completed; both Gate1/2 indicators green and native caption reports outside gate sound. HP74MP16/PB500 unchanged. First sockets inspected were empty; socket4 originally held plug. No new native crash/proven defect. Archived full replay/initialcards/live/screen/outputcards `mine-refuge-gate1-powered`; phone save predates panel change. CurrentPID49407/LLDB75901 end434386, caption active on panel; next leave and enter newly powered cavern via Gorge.

- **Entered Cavern and completed Madigan intro437404**. Refuge plug gate successfully passed via Gorge; stage4area2 room1 variant1. Control returned into BlizzardChaser fight (actor403000,500HP). Aya74HP16MP, position12802,1680 West, enemy5746,1546; no initial damage. Extended read-only replay_checkpoint enemy census to actor403000 with root/targeted; py_compile and live HP500 verified. Archived full replay/initialcards/live/screen `mine-cavern-blizzard-chaser-start`. ActivePID49407/75901 end437404. Fight unfinished, no new native crash/proven port defect.

- Cavern BlizzardChaser progressed500→257HP at440966. Aya86HP4MP after successful HealingII51→105 and later19damage; PB14loaded, MPBoost1 carried unused. Source confirms actor403000 catch uses zero-press hold (not Scavenger mashing); recovery phase1 can outlast200 input samples, freshfire only afterstate2. Repositioned from SW corner to9195,2181; enemy currently500,6700. Full replay/initialcards/live archived `mine-cavern-blizzard-chaser-half-hp`. Active49407/75901 end440966. Fight unfinished, no new native crash/proven port defect.

- BlizzardChaser first phase down257→56HP at446737, Aya11HP4MP PB8loaded. Ground attacks/ceiling grabs reduced HP86→11; waiting for state2 verified before freshshot. Enemy rapidly withdraws between room ends; target can clear and aim retain old heading, but no original-vs-port evidence of defect. Full replay/initialcards/live archived `mine-cavern-blizzard-chaser-56hp`. Current16145,4672 yaw3710, enemy2475,6542; fight unfinished. ActivePID49407/75901 FIFO `/tmp/pe2-mine-distance-retry-20261104/control.fifo`; initial437404 and safer440966 fixtures retained. No native crash.

- Cavern first attempt ended in authored combat death447104 (HP-1, BlizzardChaser56). Full input/live archived `mine-cavern-blizzard-chaser-death`. Retry from prebattle Refuge gate checkpoint434386, prepare MP via legitimate PE purchase and MPBoost attachment before entry. Prior process49407 retained.

- **Cavern retry preparation at436414 PID56989/LLDB65574**. Replayed Refuge gate434386 exactfullsnapshot match, learnedPlasmaI for750EXP845→95 and MPmax46→47/full47. HealingII74→105 MP47→35. Physically movedMPBoost1 toattachment3, CombatLight returnedbag; HolyWater2/PB1 retained,500PB20loaded. Full replay/initialcards/live archived `mine-cavern-plasma-mpboost-prepared`. FIFO `/tmp/pe2-cavern-prepared-retry-20261104/control.fifo`. Olddead49407 retained. FirstCavernfight unfinished; no new crash/provenportdefect.

- Prepared Cavern retry at443966: BlizzardChaser292HP, Aya86HP27MP after2successfulPyroII hits and1miss. MPBoost consumed via combat attachment (native selection uses Left/Right only, not Up/Down; index2 confirmed), MP14→39; HealingII63→105, then anotherceilingdrop19damage. Firstceilingrun evaded at440903, laterroutecaught. Full replay/initialcards/live archived `mine-cavern-prepared-retry-progress`. Active56989/65574 FIFO `/tmp/pe2-cavern-prepared-retry-20261104/control.fifo`, heldphase1 at1352,2319 yaw1069. No newnativecrash/provenportdefect; fightunfinished.

- **BlizzardChaser first500HP phase defeated at446499** (finishing PyroII84→-25 at446349). Verified battleRefs0, results300EXP200BP10MP; Aya86HP16MP EXP395. Two ceiling attacks evaded by earlylongrun. Lasttwo PyroII192→84→-25 withoutHP loss. Fullreplay/initialcards/live/screenshot archived `mine-cavern-blizzard-chaser-phase1-victory`. Event1/resultscreen nextscene pending; fullCavern encounter NOT claimedcomplete. ActivePID56989/LLDB65574 FIFO `/tmp/pe2-cavern-prepared-retry-20261104/control.fifo`. No new nativecrash/provenportdefect.

- **Cavern phase2 control returned448138**, after Kyle-related dialogue and burned-model reset; BlizzardChaser2500HP confirmed. Aya86HP16MP EXP395 at3880,6678 yaw910. Added mineCavernTargetTask to read-onlycensus;4targets HP30/24/30/30, blast radius3000. py_compile/liveverified. Archived full replay/initialcards/live `mine-cavern-blizzard-chaser-phase2-start`. Active56989/65574 FIFO `/tmp/pe2-cavern-prepared-retry-20261104/control.fifo`. Next exploit nearby target blasts; phase2unfinished, no newcrash/provenbug.

- Phase2 blastattempt449731: SWtarget4340,8710 prepared30→6→4 then destroyed; boss2486HP (14bulletdamage), no400blastdamage. Aya50HP16MP M93Rempty aftergrabs. Verified source `_actor403000CheckTargetBlast`: onlynewdestroyedflag bits, distanceXZ strictly<3000, consumesbit evenoutside; explosionvisualduration doesnotextenddamagewindow. Three targetsremain30/24/30. Fullreplay/initialcards/live archived `mine-cavern-phase2-first-blast-attempt`. Active56989/65574 end449731 at3666,6657 yaw1303. No nativecrash/provenbug, phase2unfinished.

- Phase2 continued452969: healed50→93 (MP16→4), traversedwestside toNWtarget4550,310, prepared30→6HP. Subsequentgrabs reducedAya39HP. Boss2460HP: lastR1series whileNWtargetselected1 damagedboss26 andlefttarget6, consistentwithinterception butnoenginefaultproven. Needcheckshotgeometry/aimbeforeburningmoretargets. Current3584,2163yaw1676, boss17214,2686; otherNE/SEtargets24/30. Fullreplay/initialcards/live archived `mine-cavern-phase2-north-target-prepared`. Active56989/65574 end452969; phase2unfinished,no nativecrash.

- **Phase2 first successful timed blast at453557:** NWtarget4550,310 destroyed with boss5033,1086 inside3000 radius; boss2460→2046 (400blast plus14bulletdamage). Aya29HP4MP, M93R17loaded, position2060,3607 yaw1598. Target had2HP before reload; authored grab interrupted first reload, waited180 and freshaim/fire reloaded20 then detonated. Live snapshot `/tmp/pe2-cavern-prepared-retry-20261104/blast-453557.json`, full controlled.pad retained. Confirms blast mechanic works in native port; no new proven defect. NE/SE targets24/30 remain. ActivePID56989/LLDB65574, phase2unfinished.

- Cavern phase2 retry ended in ordinary combat death458137 (Aya-3HP, boss1981HP). Full input remains `/tmp/pe2-cavern-prepared-retry-20261104/controlled.pad`, live death snapshot `phase2-death.json`; process56989 retained. NEblast missed (boss2046unchanged), SEtarget20HP remained. North-object dialogue explained ignored movement, screenshot verified; later crate collision bypassed east to16065,8567. No crash/provenportbug. Next retry from intact448138 phase2-start fullreplay; conserve health by moving early during ceiling attacks and prepare targets before timing 400HP blasts.

- Started isolated phase2 retry PID28740/LLDB32880, directory `/tmp/pe2-cavern-phase2-retry-20261104`; full replay448138 and initialcards restored. Snapshot existing fields including all enemy records exactmatch. Extended read-only BlizzardChaser census with state/prevState/stateFrame/dropDelay/playerCaught/seenTargetsDestroyed/attackTarget; py_compile and live originalprocess read verified. Source confirms drop latches player position on state12entry, delay20 then catch check atframe10 radius1000. FirstSWtargetprepared6HP, ordinarylungecaughtAya86→71. No newnativebug.

- **Phase2 retry firstSWblast hit449659:** target4340,8710 prepared2HP, shortR1press4+neutral80 reloaded20 withoutfire. Luredceilingdrop at4203,6983; state15frame19 waited86samples then ran50: player4159,8050, dropstate12frame7, >1000away fromlatchedtarget. NoHPdamage62retained. Subsequentfire destroyedSWtarget and boss2429→2029, knockdown17, flag4. Three targets30/24/30 remain; muchbetterthanpreviousmissedSW. Live evidence `/tmp/pe2-cavern-phase2-retry-20261104/first-timed-blast.json` is449605 preblast; fullrecordcontrolled.pad includes449659success. CurrentPID28740/LLDB32880. No newnativebug.

- HealingII succeeded62→105HP, MP16→4 at449971; PErecoveryfinishing. Archived fullreplay/initialcards/live `mine-cavern-phase2-sw-blast-healed`. Boss2029HP, three targetsintact. Active28740/32880.

- **Phase2 secondblast NW success451108:** boss2008→1593 (400blast+15bullet), seenflags5, knockdown17. Aya90HP4MP afterone15damagecatch; NWtargetdestroyed. Crossednorthcorridor to11559,1202 withnoadditionaldamage. NEtargetprepared2HP/fullreload20 at452011, ceilingstate15frame34. AttemptedNErun collidednear13072,650, moved<1000 andcaught75→61HP. Afterrelease NEtargetdestroyed452404 butbossalreadyceiling, no400damage; boss1567HP, flags7, SEtarget30 remains. No nativecrash/provenbug. Active28740/32880, fullcontrolled.pad preserved.

- **Phase2 third successful blast454704:** SEtarget30→6→2 prepared; firstceilingevade453495 withoutHPdamage butmagazineexhausted beforedetonation. Secondwestescape collidedtarget, drop47→36HP. Groundlunge36→26; afterrelease retainedtarget fire destroyedSE andboss1508→1070 (400blast+38bullets), knockdown17, seenflags15. Allfourtargetsused, three400blastslandedtotal; NEonlymiss. ActivePID28740/LLDB32880, fullinputcontrolled.pad and `/tmp/pe2-cavern-phase2-retry-20261104/se-blast.json` authoritative. No newnativecrash/provenbug.

- Postknockdownfire454933 reducedboss1070→958HP withoutHPdamage. Aya26HP4MP M93R1loaded; archivedfullreplay/initialcards/live `mine-cavern-phase2-three-blasts`. Bossgroundpatrol16500,1043; player16319,6908 yaw2056. Fightunfinished.

- Phase2 retry ended456995 authoreddeath(Aya-3HP), boss858HP. Postblastshooting958→934→883→858 but lunge/drop catches exhausted26HP. Active28740 retainedstoppeddead. Fullinput `/tmp/pe2-cavern-phase2-retry-20261104/controlled.pad`, deathsnapshot latest.json. Safer449971 three-targets/105HP checkpoint intact. Next reviseweapon/loadout and aim/dodge strategy before replay; no nativecrash/provenbug.

- Loadout investigation afterdeath: carriedweapons129=M93R,132=P229,146=Tonfa; shotgunammo173/174 andrifle175 carriedwithoutcompatiblegun, so cannotassumePA3/M4available. `attachments.c` table confirmsPlasmaI6MP (remaining4insufficient). Next retryshouldpreserveMPforPlasma orchangeP229flash strategy/saferfiringposition.

- New isolated retryPID25541/LLDB78940 `/tmp/pe2-cavern-final-retry-20261104` restored449971 fixture `mine-cavern-phase2-sw-blast-healed`, **full snapshot exactmatch True** includingextendedenemyfields. Prior dead28740retained. Nativeinput resumed towardNWtarget; shortcombinednavigation differedandgrab105→96HP, boss2029 three targetsintact at450557. FIFO/controlhelper now78940. No nativecrash.

- Currentretry451566: Aya81HP4MP boss1957HP, NWtarget4HP. Shooting selectedNWtarget sometimes damagesbossbehind playerroot, requiring investigationbeforebugclaim. Added read-only `aimYaw`, `aimTrackingState`, `weaponForwardView` to checkpointactor; py_compile/liveverified. Workm weaponforward is VIEWspace whereas rootForward local/worldparent; cannotcomparevectorsdirectly. actor403000 clearsallframecontacts; stalecontacthypothesisunproven. Current1658,2936 yaw1474, boss511,5041. Snapshot `/tmp/pe2-cavern-final-retry-20261104/aim-investigation.json`, fullcontrolled.pad. Active25541/78940; noRAMwrites/nativefix.

- Aim investigation451615: inverseviewrotation transformsweaponforward toworld[3212,-959,-2362], consistentwithselectedNWtargetNE ofplayer. Temporary read-only breakpoint `_actor403000ApplyHitDamage` didnottriggerduring45shotsequence; NWtarget4→0, boss1957unchanged, flags5. Removedbreakpoint3. Thusnoconfirmedmisdirectedcollision; earlierpostseriesbosspositioncannotprovebehind-playerhitattimeofshot. NWblastmissedthisretry. Aya81HP4MP, NE24/SE30 remain, boss1957. Addedaimdiagnostics syntax/livePASS. Active25541/78940, fullinput preserved.

- Currentretry453768 SEtargetprepared2HP and movingceilingevade succeeded57HPunchanged; boss1861HP. Player14335,7996; latchedlanding16090,6673 was3190fromtarget, avoidedprematureblast. Freshlock453907, waitedpatrol/nextambush454107state15frame26, target2HPretained. Read-onlydiagnostics/fullinput preserved in `/tmp/pe2-cavern-final-retry-20261104`. EarlierNE24destroyed452441outsideblast,no400damage. No newnativebug.

- Retry movement455905: aftersecondceilingcatch46→35HP, heldrunleftcatch then routed14315,6271→16664,2511→10832,1107→10799,2470. Allmovement/lungeavoidance maintained35HP, shortfirepress reloaded20. Boss1861HP atstate15frame5, alltargetsgone; plan preturnNorth then timedrun toescape openNorthcorridor. This establishes usablecorridorroutewithoutnativechanges. Active25541/78940, latest.json/fullcontrolled.pad.

- **OpenNorthcorridor evade/fire cycle successful456365:** from10799,2470 yaw4075, bossambush15frame5: Left46, neutral70, run65, neutral20, Right46, aim25, fire90 reducedboss1861→1810 withoutHPdamage; followup90fire1810→1795. Aya35HP4MP retained. Player10809,651 yaw3170, M93R8loaded; boss45,6998 approach11. Fullreplay/initialcards/live archived `mine-cavern-open-corridor-dodge`. Active25541/78940. No nativecrash/provenbug.

- Current456898: boss1776HP, Aya25HP4MP. Lungehit35→25 afterattemptedlate21sampleturn. BattleStartmenu visuallyverified: M93R, PB2loaded, AssaultSuit, HolyWaterattachment2. Cross onselectedemptyslot closedmenu; weaponchangeNOT yetperformed. RegisteredVRAMcommand with `command script import tools/port/replay_checkpoint.py` (plainPythonimportalone didnotregister). Active25541/78940 remainsalive. No newnativebug.

- Battlemenuinvestigation456927: nativeStart/Selectopensattachmentusepanel, weaponpanelbesideitissummary. `item_use.c` activeattachmentpanel onlyConfirm/Left/Right/Cancel/Menu; nofullweaponequipnavigation. P229carriedbutunattached, nochangeperformed. HolyWater2preserved. Aya25HP4MP boss1776HP. ClosedmenuandresumedM93R. No nativebug; avoidclaimingweaponchangepossibleinthispanel. Active25541/78940.

- Currentretry457858: successfulfullreload20 at457655 afterlunge25→16HP. BossapproachedfromSouth; turned17right/freshaim25/fire45 hit1776→1721 butgrab16→11HP. Active25541/78940, alltargetsused, MP4. Stillordinarycombat,noenginecrash. Latestinput/live retained `/tmp/pe2-cavern-final-retry-20261104`.

- Currentretry458562: lunge11→3HP whileturning/runningNorth, boss1721HP. Heldrun280 throughcatch release allowedmovementto17202,2932 withoutadditionaldamage, boss15247,1504 turning4frame14. Nativecontrol/liveprocess25541/78940 retained; fullcontrolled.pad. No newenginecrash.

- Retry ended459064 authoreddeath(-5HP), boss1693HP. PreservedPID25541/LLDB78940, fullcontrolled.pad and death.json. Verified lungecode `_actor403000LungeState`: distance-dependentstep=(distance-900)/20, movementframes5..24, tracksplayerframes5..14 atmax64yawunits/tick, catchesONLYframe23 viaheadcapsulecontact. Earlierescapeattempts beganlongbeforecommit andbosssteeredafterplayer; late90degturntakes~11ticks andexceedsremaining9tick window. Next retryshouldpreorientperpendicularlybeforestate8 andrunthroughwind/commit, ratherthanbeginningturnatframe21. Bestsavedthree-blasts454933boss958/Aya26 remainsavailable. No nativecrash/provenbug.

- New best-state retryPID49063/LLDB60131 `/tmp/pe2-cavern-best-retry-20261104` restoredfullinput454933 `mine-cavern-phase2-three-blasts`. Allprevioussnapshotfields exactmatchTrue; newaimdiagnosticsadditional. Aya26HP4MP boss958HP. Prior dead25541retained. Registeredcheckpoint/VRAMcommands viaLLDBimport, BP2line305 andinputhelperupdated60131. First45fireusedlastbulletwithoutdamage, fullreloadnext. No nativecrash.

- **Lungeevade verified455241 bestretry:** fullreloadrequiredR1held16+neutral65 (prior4tooearlyignored). Atbossstate5position9118,7580, player16319,6908yaw2261: Left5 thenrun85 →player16517,4235, bosslunge8frame40/playerCaught0; Aya26HPunchanged. Preorient/runperpendicular BEFORElungeworks atthisposition, unlikelateturnatframe21. Active49063/60131, boss958HP; fullinput/live retained.

- **Secondlungeevade bestretry455656:** bossstate5at5771,7518, player16517,4235yaw2508. StraightRun85moved15135,2160, boss13531,6080lunge8frame25/playerCaught0. Aya26HPretained. Thus two consecutivepreorientedperpendicularrunsavoidedcatch; no nativefixneeded. NextRight30/aim25/fire90 duringrecovery. Active49063/60131.

- Bestretry456406: thirdpreorientattempt mistakenlyLeft10fromSouth pointedSWtowardcrate, lungecaught26→17HP. Releasedandfullreload20confirmed; boss937HPunchanged, player15538,920yaw3960. Live/input preserved `/tmp/pe2-cavern-best-retry-20261104`, PID49063/60131. ExaminingauthoredGorgewarp18240,1888Eastforlegitimateresupply; notyetverifiedallowedinvariant4. No newnativebug.

- **Retreatattempt verifiedblocked456703:** physicallyreachedGorgewarp17968,980 facingEast1008 andCross. Nativecaption **It won’t open...** screenshot `/tmp/pe2-cavern-best-retry-20261104/exit-check.png`; stage4area2variant4unchanged, Aya17HP4MP. Cannotresupplybyexitingthisphase. Closedcaptionandresumedmovement. Boss937HP, active49063/60131; no enginebug.

- Bestretry457366: preorientedWest2944 at17705,3726, bossapproachedEastwaypoint17054,6379 state11. Run85 failedwithFRONTGRAB(state6), notlunge8; Aya17→12HP, player15710,3006. Close-rangegrabneedsdifferentavoidancefromverifiedlongrangelunge. Alltargetsused,boss937HP, active49063/60131. Fullinput/live preserved. No nativecrash/provenbug.

- **Ceilingevade+punish bestretry457942:** at15710,3006yaw3547/bossambush15frame21: Right36, neutral48, Run60 escapedEastto17991,2911; Aya12HPretained, dropframe13/playerCaught0. Right46,aim20,fire45 hit937→915; fresh45firewhileturn4frame14 hit915→872, still12HP. Goodshortserieswindowafterceilinglanding. Active49063/60131, fullinput/live preserved; no nativecrash/provenbug.

- Bestretry458272: postceilingboss851HP, Aya12HP4MP maintainedthroughreload. Empty-triggerattemptduringrecoveryignored; repeatedfreshR1held16afterlongneutralconfirmed20loaded. Boss9925,6961 approach11; movingNorthbeforeEastwaypointtoavoidcloserangegrab. Active49063/60131, fullinput/live preserved.

- Bestretry458947: aftergrab7HP, traversedNorthcorridor9434,669; bossambush15frame53. Neutral20 thenRun65West, Left45/aim20/fire45 evadedceilingandhit851→831 withoutHPdamage. Player7085,466yaw912, boss14070,1516patrol2frame16, M93R17loaded. This openNorthcorridorceilingcycleworksagain. Active49063/60131, fullinput/live preserved.

- Read-onlylivecollisionvertexcensus: centralobstacle spansapproximatelyx2970..15630,z2690..5970, northedge6920,2690→15150,2860. Explainsblockedmovement; no nativecollisionbug. Bestretry459218: player7085,466 facingSouth, bossapproach11x1439,483; Run65 ended7235,2316 caughtfrontgrab6, HP7→2. This wascloserangegrabafterringapproach, notlunge. Boss816HP. Openpathaloneinsufficient; needprepositiontokeepchaseentrylongrange. Active49063/60131, fullinput/live preserved.

- **Curvedrun frontgrab evade verified459595:** from7377,633yaw1986/bossgrab7frame14at6786,2107, heldphysicalmask8240(Up+Circle+Right)50 thenneutral4. Aya2HPretained, moved5958,683yaw3586; bossendedturn4frame5at6651,1892/playerCaught0. SubsequentRight19/aim20/fire45 hit816→784withoutHPdamage459683. Newusefulnativeinputdodge, noRAMwrites. Active49063/60131, fullinput/live preserved.

- Bestretryended460037 authoreddeathHP-6, boss784HP. Reloadcomplete459983 butlungealreadyframe19; curvedrunstartedtoolate, catchframe23. PreservedPID49063/LLDB60131, fullcontrolled.pad/death.json. Needchangepreparationratherthanrepeatlowhealingloadout: investigatelegitimateshop/resupplybeforebattle fromsafeRefugegate434386. Bestcombatfixturesintact. No nativecrash/provenbug.

- NewresupplyPID49087/LLDB42297 `/tmp/pe2-cavern-resupply-20261104`: replay434386Refugegate previoussnapshotfields exactmatchTrue. Aya74HP16MP EXP845 BP2936. **Correctedprep error: AssaultSuititem99 baseAttachmentSlots5, saveditemLevelBonus[3]=0, actual5slots (priorassumption3wrong).** KeepHoly2/PB1, canattachMPBoost3 plusotheritems4/5. Save-backedrows outsidecarried includeHydra27(row50), PepperSpray59(row51), Penicillin8(row52), PB50/stims(rows80..82), Buckshot20/Grenades8(rows130..131). NeedverifywhichstorageaccessibleandpickupviaUI; noRAMwrites. Activehelper42297/end434386.

- Resupplyroute434877: exitedpanelnormally; Refugeplayer1550,1186North2088 HP74MP16. Hydra27savedrows50..79=containerselector3(retainedextras/trainingprizes), NOTRefugePBcase. Rows80..89=Motelroom6box, rows90..109=garagebox. Needshop/appropriatecontainerphysicalUIaccess; noinventorywrites. AssaultSuit5actualslotsconfirmed. Active49087/42297 `/tmp/pe2-cavern-resupply-20261104`.

- Resupplyroute435838: GorgepatchedbridgecrossedEastwithoutdamage/combat. Player16959,1175yaw1080, HP74MP16unchanged; approachingauthoredEastMainTunnelexit17840,1504. Active49087/42297, fullcontrolled.pad/live preserved. No nativecrash.

- Resupplyroute436985 MainTunnelclearedbacktrack: traversedEastfrom500,1630 throughcrateobstruction, correctedroutevia10252,2353South thenEastto14741,2198. HP74MP16unchanged, noenemies. ApproachingEastTunnelEntrancewarp15904,1024. Active49087/42297, fullinput/live preserved,no nativecrash.

- **ResupplybacktrackreachedMesa438091:** stage4area1view5warp2variant1, player315,3562East1024. TunnelEntranceclearedtraversalEastandwarp17568,2112completedwithoutdamage; HP74MP16EXP845, censusMesaempty. Nativealltransitionsnormal. Active49087/42297, fullcontrolled.pad preserved; seekingDryfieldroute/shop.

- Mesaresupplyaudit438569: inspectedall19actiontriggers, onlywarpisTunnelEntrance; companiontalk gatedbeforeMesaevent, noshopcallback. SouthCAP9at6111,7503physicallycaption **[DANGER! NO ENTRY TRESPASSING]**, notitemstorage. Aya74HP16MPunchanged, player5512,7369 facingSouth56; captionopen. DryfieldshopbacktracknotavailableviaordinaryMesawarps; earlierresupplyassumptionunprovenandnowrejected. Nextpreparewithfiveactualslots/availableitemsorreturnearliercheckpointbeforeonewayMesaentry. Active49087/42297.

- **Five-slotpreparation439981 verifiednativeUI:** outsidebattlefullmenuUse(row0), InventoryrightMPBoostrow4→Move→Leftarmorrow→Down4→Confirm. Inventoryrow6item6attachSlot4; CombatLight65slot3/HolyWater56slot2/PB160slot1 unchanged, fifthfree. No itemconsumed, Aya74HP16MP845EXP. Fullreplay/initialcards/live archived `mine-mesa-five-slot-mpboost-prepared`. Active49087/42297, currentlymenuopenMesa5512,7369. Confirmsprior3slotassumptionwasoperatorerror,nativeUIworks.

- ReturnfromMesapreparation440677enteredTunnelEntrance(stage4area3) withoutdamage. PhysicalfullmenuclosedandMesawestwarpused; equipmentPB1/Holy2/Light3/MPBoost4 unchanged. At441092player2534,1750West, proceedingMainTunnelWestexit544,1088. HP74MP16. Active49087/42297, fullinput/live preserved,no nativecrash.

- Returnroute442363 MainTunnel→Gorgepassednormally, HP74MP16unchanged. GorgepatchedbridgeWestto3544,1600 at442778; proceedingRefugeentry1408,3744South. Fullcontrolled.pad/livepreservedactive49087/42297. PreparedMPBoost4/Light3/Holy2/PB1 unchanged. No newnativecrash.

- Resupplypreparation443846: learnedPlasmaI viaPEmenuRevive750EXP845→95, MP16→47/max47. SlotsPB1/Holy2/Light3/MPBoost4 retained. OutsidefullPEmenuoffersStrengthen; TrianglewheelautochoosesHealing7whenoutsidebattle. CastingHealingIIat444630 thenverifyfullHP/MP. Archivedfullreplay/initialcards/live `mine-refuge-five-slot-plasma-healed`. Active49087/42297, Refugearrival1472,330South.

- PreparedretryenteredCavern445237 fromRefuge/Gorge with105HP35MP95EXP. SlotsPB1/Holy2/CombatLight3/MPBoost4, fifthfree. Introevent1nativewalkview9; physicalStartdidnotskip. Advancingauthoredscene/dialoguewithneutral/Confirm; noRAMwrites. Active49087/42297, fullcontrolled.pad+entrysnapshot `/tmp/pe2-cavern-resupply-20261104/cavern-entry.json`. No newnativecrash.

### 2026-11-04 — Cavern continuation, resupply retry

Live PID 49087 / LLDB session 42297, input counter 454271; recording `/tmp/pe2-cavern-resupply-20261104/controlled.pad`, observation `latest-live.json`. First phase remains unfinished: boss 460 HP, Aya 41 HP / 21 MP. Holy Water and Combat Light remain attached, MP Boost unconsumed. Ceiling drop avoided at 452166 by moving after latched attack target; no new confirmed port bug. Two Pyrokinesis casts failed to connect with moving/distant boss (14 MP total), so do not repeat without confirming range and timing. Reload verified 20 rounds at 452322. Boss watch state timeout is 300 simulation ticks, not 300 pad samples; returns to prowl. Preserve earlier safer replay fixtures, especially `mine-refuge-five-slot-plasma-healed`.

### 2026-11-04 — Cavern first phase defeated with MP Boost retained

Physical-input retry won first phase at counter458227: Aya82HP19MP, EXP395, reservePB425. Full replay fixture `mine-cavern-phase1-victory-mpboost-retained`. SE target blast at458045 reduced boss409HP to2; final M93R burst killed. HealingII earlier restored41 to105HP for12MP. Important input correction: keep Square held while firing for active aim request; R1-only requests aim exit. Fresh Square or Square+direction cycles targets, but distant targets may be unavailable and nearest fixtures can intercept selection. No native code change justified.

Second phase verified at459867: boss2500HP, Aya82HP19MP; MPBoost remains in attachment4, HolyWater2/CombatLight3 retained. Full replay fixture `mine-cavern-phase2-start-mpboost-retained`. P229 is now carried but Start opens only combat attachment-use menu; full-inventory window not verified. Only NW30HP and NE18HP explosives remain: first-phase consumed SW/SE targets do not reset. Live PID49087 LLDB42297, menu open, FIFO `/tmp/pe2-cavern-resupply-20261104/control.fifo`. Goal incomplete.

### 2026-11-04 — Second-phase NE blast and MP restored

At464235 NE explosive delivered400 damage (2432→2032) after safe ceiling dodge: Aya11609,2012, boss15frame38 at464078; run20/neutral28, neutral4/run50/aim20/fire25. Followup aimed bursts reduced boss to1915. Reached NW explosive (6HP) but later lunge hit15HP; HealingII restored58→105 for12MP. MPBoost1 consumed at467151,7→32MP (+25, not +30). Current Aya96HP32MP, boss1915HP, NW6HP remaining; HolyWater and CombatLight retained. Full replay fixture `mine-cavern-phase2-ne-blast-mp-restored`, original initial cards. Live PID49087 LLDB42297, counter467151.

Attachment UI: read gItemMenuSelectedAttachmentIndex directly (0-based), index3 is MPBoost in slot4. Earlier VRAM y272 snapshots displayed stale alternate frames and led to wrong selection assumptions. Circle50 successfully returned from a hidden menu; no hang established. Confirm only verified slot. Goal remains incomplete; no gameplay RAM edits or target function calls.

Second-phase continuation ended at counter468768, same live process/FIFO. Last pre-reload observation468687: Aya67HP32MP, boss1866HP, all explosives consumed; NW blast missed because aim20 let patrol depart radius. Safe ceiling dodge468403→468587: boss15frame59, Aya2038,2420 yaw1443; neutral8/run55/right46/aim20/fire45, no HP loss, boss1915→1891; aimed fire90 reduced1866. Reload16+65 executed; inspect latest-live.json for resulting authoritative state before next input. Earlier good full replay `mine-cavern-phase2-ne-blast-mp-restored` retained. MPBoost is +25MP, selected attachment index3. No confirmed new native defect.

### 2026-11-04 — Second-phase boss1673HP continuation

Full replay `mine-cavern-phase2-boss1673`, counter471681, live PID49087/LLDB42297, same resupply FIFO. Aya90HP13MP, boss1673HP, HolyWater/CombatLight retained; all explosives consumed. Ceiling dodge at468878→469098 succeeded without loss (boss15frame7, reload16+65, right29 reached state12entry; neutral4/run50/right46/aim20/fire90), boss1866→1795 then aimed90→1759. East corridor ceiling dodge469827→470139 also safe: reload16+65/run65/right46/aim20/fire90, boss1742→1697, Aya67 unchanged. Later frontgrab and lunge damaged Aya; HealingII succeeded, then another15HP lunge left90. PlasmaI attempted at boss7frame3 was interrupted without MP consumption; cast from boss4frame13 at471325 completed, cost7MP and damage16 only. Preserve remaining13MP for HealingII. No newly proven port defect; do not repeat Plasma for efficiency.

### 2026-11-04 — CORRECTION: Necrosis poison, boss1286HP

Earlier notes incorrectly called PE index3 PlasmaI. Index3 is NecrosisI; PlasmaI is index4. Cast471325→471601 applied poison (Enemy.reactionFlags4, grade1), not just16 damage. Read-only observation saw25HP pulses during neutral/run input, confirmed by damageTickEnemyDamageOverTime and actor403000 quarter-strength DOT. Enemy parameter damageOverTimeTicks20; do not assume indefinite poison. This corrects earlier recommendation to avoid the spell based on initial16 alone.

At473698 boss1286HP, Aya66HP13MP. Full replay fixture `mine-cavern-phase2-boss1286-poison`, original initial cards. Same live PID49087/LLDB42297/FIFO. Safe ceiling cycle472304→472529 (neutral4/run55/right46/aim20/fire90) preserved81HP and reduced1598→1525. Later lunge hit15HP. Safe subsequent lunge:473319 reload16+65, left23/run95 reached boss8frame22 at473528, then run50/aim20/fire90, HP66 unchanged and boss1334→1286. Preserve13MP for HealingII. No new native code defect confirmed.

### 2026-11-04 — Boss1079HP, Aya full HP

Current counter475686, livePID49087/LLDB42297, sameFIFO. Boss1079HP, Aya105HP1MP, last HealingII successfully cast at475047 (57→105,13→1MP). Full replay fixture `mine-cavern-phase2-boss1079-full-hp`, original initial cards. Native poison appears expired: bossHP1079 remained constant through475686. Weapon only2rounds loaded; do not assume reload completed. HolyWater and CombatLight retained.

Safe lunge sequence473970→474131: Aya16637,5509yaw4034, boss11farWest; right46/run105, Aya17067,2026 boss8frame37, HP66 unchanged. Aim25/fire90 reducedboss1187→1143, subsequentfire/reload reduced1104. Another frontgrab hit9; lastheal then safe lunge475389→475515 left31/run85, Aya16033,1724 boss8frame26, full105HP unchanged. Recent shots without targeted lock did no damage; always inspect target before committing firing sequence. No new native defect confirmed. Goal incomplete.

### 2026-11-04 — Boss991HP, no HP loss this continuation

Full replay fixture `mine-cavern-phase2-boss991-full-hp`, counter477372, samePID49087/LLDB42297/FIFO. Aya105HP1MP, boss991HP, M93R2rounds loaded. HolyWater/CombatLight retained. Shifted to west corridor, acquired lock before fire. Safe ceiling sequence476595→476846: boss15prev2frame47 (entry not yet reset), neutral130/run55/right46/aim20, Aya2242,5470 vs boss12frame44, no damage; fire90 reduced1059→1035. Safe CURVED LUNGE dodge477172→477272: Aya2500,1987 yaw1998, boss5 at10030,1398; mask8240(Run+Right)65/neutral10/aim25 -> Aya868,2181, boss8frame48, HP105 unchanged. Fire90 reduced1035→991. New evidence: curved dodge can work for lunge when started early, not at late frame19. No new native defect confirmed.

### 2026-11-04 — Boss894HP, full HP retained

Full replay `mine-cavern-phase2-boss894-full-hp`, counter478205, samePID49087/LLDB42297/FIFO. Aya105HP1MP, boss894HP, M93R8rounds. No HP loss this continuation. Boss5 at9701,1371 while Aya982,2181yaw2073 (477905): mask8336(Run+Left)65/neutral10/aim25 safely dodged lunge, Aya2596,2517 and boss8frame44 at478005. Fire90 reduced976→913, next90 reduced894. Left curve avoids west wall when starting near x1000; prior right curve required more westward room. Preserve previous replay fixtures. No new native defect.

### 2026-11-04 — Boss844HP, full HP retained

Full replay `mine-cavern-phase2-boss844-full-hp`, counter479131, samePID49087/LLDB42297/FIFO. Aya105HP1MP, boss844HP, M93R8rounds. Safe ceiling478295→478480: boss15frame32, neutral64/run55/right46/aim20, no HP loss. Safe curved lunge478831→478931: Aya2082,5640yaw22, boss8frame7 at7726,1408; mask8240x65/neutral10/aim25 -> Aya2658,5187 boss8frame57, HP105 unchanged. Fire90 reduced870→844; subsequent90 missed as boss crossed arena and lock was lost. No confirmed new native bug.

### 2026-11-04 — Boss742HP, full HP retained

Full replay `mine-cavern-phase2-boss742-full-hp`, counter480070, samePID49087/LLDB42297/FIFO. Aya105HP1MP, boss742HP, M93R14rounds. No HP loss. Safe right curved lunge479414→479514 from boss8frame3, Aya2487,2109yaw2033:8240x65/neutral10/aim25; fire/reload reduced844→788. Safe ceiling479775→479970: boss15frame27 Aya875,2391yaw134; neutral74/run55/right46/aim20, boss12frame37 and targeted; fire90 reduced788→742. Preserve earlier fixtures. No new confirmed native bug.

### 2026-11-04 — Boss566HP, Aya91HP

Full replay `mine-cavern-phase2-boss566`, counter481451, samePID49087/LLDB42297/FIFO. Aya91HP1MP, boss566HP, M93R8rounds. Safe ceiling480170→480391: boss15frame14; right20/neutral80/run55/right46/aim20, thenfire90 reduced742→694. Longer firing/reload sequence let next drop reachframe7; late run failed,14HP loss. Avoid long multi-input combat sequences without intermediate boss observation. Safe left curved lunge481151→481251: Aya1120,5595yaw4080 boss5 at10205,2248;8336x65/neutral10/aim25, no loss; twofire90 series reduced679→566. No new confirmed native defect.

### 2026-11-04 — Boss382HP, Aya76HP

Full replay `mine-cavern-phase2-boss382`, counter483162, samePID49087/LLDB42297/FIFO. Aya76HP1MP, boss382HP, M93R2rounds. Right curved dodge at482171 failed from long-distance boss5 (14584,481 vs Aya2442,2254),15HP lost; do not assume all early5 curves work at every distance. Safe ceiling482726→483062: boss15frame6, Aya769,4402yaw1379; right15/neutral100/run55/right46/aim20/fire90, HP76 unchanged, boss507→434; nextfire90→382. Preserve prior safer fixtures. No confirmed new native defect.

### 2026-11-04 — Boss160HP, Aya76HP retained

Full replay `mine-cavern-phase2-boss160`, counter484687, samePID49087/LLDB42297/FIFO. Aya76HP1MP, boss160HP, M93R14rounds. No HP loss. Left curved lunge483442→483542 from Aya969,5374yaw22 boss5 at8231,2527 safely avoided; fire reduced372→310→264. Another left curve484013→484113 from Aya592,2110yaw2033 boss5 at9395,1367 safely avoided; fire/reload reduced264→193. Safe ceiling484374→484587: boss15frame18, Aya2183,2547yaw21; neutral92/run55/right46/aim20; fire90 reduced193→160. No new confirmed native bug.

### 2026-11-04 — CAVERN BLIZZARD CHASER BOTH PHASES COMPLETE

Second-phase boss killed by native input at486897 (HP-7, scripted state23). Dialogue advanced through488622; victory proven by battleRefs0/event0, reward500EXP300BP30MP (EXP395→895, BP3136→3436, MP1→31). Aya76HP; HolyWater preserved. Full replay fixture `mine-cavern-blizzard-chaser-complete` includes original initial cards, full controlled.pad, victory-before-heal.json and latest healed snapshot; not a native save. LivePID49087/LLDB42297, sameFIFO, counter488847 after healing inputs. All prior retries retained. No new native code fix was justified in this fight. Goal continues: advance beyond Cavern and fix any verified issues.

### 2026-11-04 — Motorcycle switch and second power wiring unlocked

After victory healed Aya105HP19MP, Cavern roomState2. Secret passage warp at1792,-352 remains closed (LED faintly lit). Physically inspected motorcycle at CAP trigger896,1440; from1535,1419 faceyaw2444 toactivate. Full caption describes extra remote-control switch by ignition; used it, Nothing happened caption. At492036 read-only live nibble verification:0xBB secret passage2,0xBE power panel stage2,0xC4 progress1. This proves stage2 wiring unlocked. Next return via Cavern east Gorge warp18240,1888 facingEast, thenRefuge power panel, solve second wiring and revisit passage. Full replay `mine-cavern-motorcycle-switch-inspected`. SamePID49087/LLDB42297/FIFO. No confirmed native defect.

### 2026-11-04 — Returned to Refuge second power panel

Counter495866, samePID49087/LLDB42297/FIFO. Cavern east warp returnedGorge at492827. NewGorgevariant2 spawned12bats1HP; initial holds cost12HP. Escape needs8newbutton presses (actor03700 source), alternatingCross/Circle4+4samples12times released. PlasmaI index4 confirmed:6MP percast, firstkilled9, second3. Victory494182:93HP19MP, EXP955 BP3652 (reward60EXP216BP12MP). Refuge arrival494508. Panel at2060,4090 facingEast activated new GATE1lamp-out dialogue and second wiring. At495866 interactive panel open with Examine/Item popup. Full replay `mine-refuge-second-panel-arrival`. Next solve second wiring; secret passage stillnotopened. No new confirmed native bug.

### 2026-11-04 — Refuge SECOND WIRING SOLVED

Counter499436, full replay `mine-refuge-second-panel-powered`, samePID49087/LLDB42297/FIFO. NativeUI retrievedfirstJumper288 fromsocket2, placeditinsocket4; placedcarriedsecondJumper300 insocket1. Bothsocket2/3empty. Loweredmainlever, greenflowandbothGATE1/GATE2lampsverified, captionhearddoorsunlock. Read-onlynibbles0xBB3(secretpassagepoweredsecond),0xBE2(stage2),0xBF2(socket1secondplug),0xC21(socket4firstplug),0xC31(switchon). Aya93HP19MP unchanged. NeedreturnCavernandoperatemotorcycleremoteswitchtoopenpassagefinally. PopupExamine/Itemselectionpersists: chooseUpforExaminewhenlastusedItem. Cursorcentre0,0;2pixels/sampleaxis,1.4diagonal. Longkeymenuclosingtransitionsneedverificationbeforecursorinputs. No confirmednativebug.

### 2026-11-04 — SECRET PASSAGE REACHED

ReturnedRefuge→Gorge500631→Cavern500977 without combat/loss. Motorcycle interaction at1337,1486 facing2456 opened GATE2 remote choice; pressed native switch. Verified passageflag0xBB1(open)502031. Cavern passage trigger needs z<=192: at1295,251 Crossdidnotwarp; runNorth10 thenCross enteredstage4area8room1variant1 at502568, Aya1400,13411North. New entrydialog What is this place. Advanced4dialogueinputs through503148. Full replay `mine-secret-passage-arrival`, original initialcards. Aya93HP19MP. SamePID49087/LLDB42297/FIFO. No confirmednewnativebug. Goal continues beyondSecretPassage.

### 2026-11-04 — SHELTER B1 ELEVATOR HALL REACHED

Full replay `shelter-b1-elevator-hall-arrival`, counter505294, samePID49087/LLDB42297/FIFO. Nativeinput traversedSecretPassage withoutcombat: northfrom1400,13411 to5311, north50/left23/east180 ->7858,4416; east230+90 ->17955,4124; east70/left23/Cross -> liftpanel20529,4194, choseGoDown. At504769 resultpanel displayed0EXP,-10BP,+1MP; acknowledgedCross then500neutral -> stage4area9room1variant1view2. Aya93HP20MP EXP955. The resultpanel/cost is observed but not classified as bug; investigate if relevant rather than assuming correctness or alteringstate. No crash or failedtransition. SecretPassage weaponCAPat17056,800 was not explored; do not claimpickup. Goalcontinues throughShelterB1.

### 2026-11-04 — B1 south maintenance cleared, Watcher census fixed

MainCorridor door at-4064,1072 fromElevHall islocked, rejectsnativekeyitem use; wentviaSouthMaintenancewarp10112,4064East. Arrival506600 stage4area10room1variant1,6rats18HP plus2Watchers70HP. Ratsinitiallyoutsidebattlethenwander/despawn; PlasmaI6MP killedremainingrats. battleRefs2 with emptyoldcensus was NOTleak: live tasks contained2_actor02100Task Watchers. Extendedtools/port/replay_checkpoint.py censusandrootpositionlists with_actor02100Task; py_compilePASS andlive reloadverified70HP at2700,-2000,5000 and1300,-2000,5000.

Reached1461,-3491 thenSouthtowards2584; laserhitscostHP. Gunshots killedfirstWatcher, second70→34; PlasmaI6MPfailedtohit highWatcher at~3.2k3Ddistance. Reload/nativeaimfirekilledlast at509036, battleRefs0. Rewardverified509341:54EXP132BP6MP, EXP1009 BP3774 Aya39HP14MP. NativeHealingII executedthrough509566; fixture `shelter-b1-south-maintenance-cleared` live.json authoritative. SamePID49087/LLDB42297/FIFO. Next Storeroomwarp1984,4480South. No confirmednativegamebug; diagnosticcoverageimproved.

### 2026-11-04 — Shelter B1 Storeroom gameplay

Continued physical FIFO input from south maintenance walkway into area 11 variant 1. Cleared three Rats and two Odd Strangers using M93R; battleRefs reached 0, reward +80 EXP/+9 MP. Aya 59/105 HP, 11/47 MP, EXP1089; Holy Water remains attached in slot 2. No new native defect established. Full replay and read-only live snapshot: `build-port/reference/shelter-b1-storeroom-cleared` (counter 512096, original initial cards; not a native save). Supplies and next native save remain to be found.

2026-11-04 continuation: inspected storeroom fridge (empty) and laboratory equipment (text only), then entered B1 North Maintenance Walkway, area12 variant1, counter516274. Two Watchers at70HP; Aya59HP/11MP. Fixture `shelter-b1-north-maintenance-arrival` preserves full replay/original cards. No new native defect confirmed; sleeping quarters exit is next.

2026-11-04 — traversed North Maintenance Walkway to Sleeping Quarters (area14 variant1). Ambush reduced Aya59→4HP; exited without clearing enemies. Initial two-Watcher census was incomplete (battleRefs5); additional attackers need census investigation. Used carried Recovery2 through ordinary inventory, verified +100HP to104/105, MP6/47; HolyWater slot2 retained. PB reserve21, loaded20. Fixture `shelter-b1-sleeping-quarters-healed`, counter518967, full physical replay/original cards; no native save yet and no new native defect established.

2026-11-04 — traversed Sleeping Quarters westward, killed one Odd Stranger and one rat with M93R without HP loss, left three rats alive, entered B1 Main Corridor area15 variant1 warp5. Aya104HP/7MP EXP1089; PB2 loaded +21 reserve; HolyWater slot2 retained. Main corridor census: three Watchers70HP and two actor01100 at280HP. Fixture `shelter-b1-main-corridor-arrival` counter523205 preserves full replay/original cards; native save remains pending. No new native defect established.

### 2026-11-04 — Sterilization container LP64 crash

Entered B1 Sterilization Room area16 variant1 from Main Corridor; Aya74HP/8MP, HolyWater retained. Traversed entry chamber through ordinary CAP/door interactions. Opening the far-end sturdy box reproduced EXC_BAD_ACCESS in `itemPickupPublishPlacedObjectTask` at item_menu.c:1902: Enemy pointer `0x6329900`. Root cause: both branches of `itemPickupContainerLidTask` queued `spawnArg2.value` (32 bits) instead of the borrowed Enemy pointer. Changed both to `spawnArg2.pointer`; complete native build passed. Original crashed PID49087/LLDB42297 preserved; full input fixture `shelter-b1-container-pointer-crash` with original initial cards. Fixed full replay validation running; no native telephone save yet.

Container validation: original trace ends at pad528041; fixed replay reached EOF528042 and exited0, but snapshot pendingMode129 precedes pickup execution, so this alone is insufficient. Added240 neutral physical samples in `replay-after-crash.pad`; extended full replay running under exec session18137, log `fixed-after-crash.log`, VRAM `/tmp/pe2-container-fixed.vram`. Need verify resulting pickup UI before declaring runtime fix proven. Original crashed process remains untouched.

Extended batch replay ended in Akropolis and is INVALID for container coverage: first batch run used initial-cards as writable card storage, modifying it through replayed native saves. Restored fixture initial-cards from original gate1 fixture. New live corrected-binary PID41054/LLDB72007 uses an independent fresh copy of original cards under `/tmp/pe2-container-fixed-live-20261104`; full replay in progress. Never reuse fixture initial-cards directly as writable replay card directory.

### 2026-11-05 — Container fix verified and native Shelter save

Fresh-card full live replay PID41054/LLDB72007 reached correct area16 pickup UI after original crash boundary (528282); box displayed120Buckshot/8grenades. Successfully transferred grenades to carried stack12, closed container and continued to telephone. This proves corrected pointer handoff and subsequent UI interaction in real gameplay. Telephone report completed; selected empty save slot and confirmed Create save data, new native8192-byte file BASLUS-01042Eb2rWIXi created. `shelter-b1-sterilization-native-save` preserves original initial cards, full replay, live snapshot and saved-cards (531205). Aya74HP/8MP, HolyWater slot2; M93R empty/PB1 reserve. Independent save reload still pending. Original crash process retained.

2026-11-05 — entered Pod Access Tunnel area17 variant1, completed long opening event (eventState0) and regained control. Inspected east door: reinforced card required. Next native interaction is pod terminal[4721,-672]. Aya74HP8MP unchanged; HolyWater slot2, grenades12. Intro showed suspicious colored stripes/texture artifacts around capsule: rendering issue remains unclassified/unfixed. Fixture `shelter-b1-pod-access-intro-complete` counter537821 preserves full replay and current snapshot.

2026-11-05 — B1 pod lift inspected and GoDown selected through native CAP choice. Reached B2 Pod Access Tunnel stage4 area35 variant1 warp3, counter539431. Aya74HP8MP unchanged; three Watchers70HP and actor01100 280HP present. Fixture `shelter-b2-pod-access-arrival` preserves full physical replay and live snapshot. No new transition defect confirmed.

2026-11-05 — learned AntibodyI for500EXP (EXP589, MPmax49/full), healed74→105HP with HealingII, traversed B2 tunnel leaving enemies alive; Watcher damage to81HP. Confirmed item169 is40mm ammunition requiring launcher (cannot throw). SepticTank transition crashed at input541868: bad audio poll target0x7c00089f94 in sndbank.c1157 during loadingSessionLoadTask state4; live location stage4area0. Root cause not established. Crashed PID41054/LLDB72007 retained. Fixture `shelter-b2-septic-transition-crash` contains full input/original cards for diagnosis.

### 2026-11-05 — Septic transition corruption root cause

Read-only hardware watchpoint in fresh replay PID76315/LLDB68084 caught fsBuildFolderTables(stage4,fileGroup0,folder1) writing fileId1201/sector124 beyond100-entry table onto midiTick poll high word. This was downstream: gShelterB2PodAccessTunnelStagedEventTaskDesc.callback resolved to unrenamed roomEventStagedTask in Dryfield Driveway, whose staged destination is zero. B2 controller TU callback is independently renamed; descriptor in _2.c was not. Added unique shelterB2PodAccessTunnelStagedEventTask entry point in controller TU wrapping its local staged task, declared in private header and bound in descriptor. Native build and diff-check passed; disassembly confirms unique entry tail-branches to PE_rooms_shelter_b2_pod_access_tunnel...roomEventStagedTask. No audio guard or file-id masking substituted for transition fix.

Full replay validation running exec29674, `/tmp/pe2-septic-fixed-20261105/replay.pad` (original trace plus1000neutral samples), independent writable cards copied from original gate1 initial cards. Expected stage4area34 (SepticTank), log `build-port/reference/shelter-b2-septic-transition-crash/fixed-replay.log`. Original crashed PID41054/LLDB72007 and writer-watchpoint PID76315/LLDB68084 retained. Must inspect replay result before declaring runtime repair verified.

2026-11-05 — Septic fix VERIFIED in live replay PID47346/LLDB1397. Original trace+1000neutral alone stopped on native battle-result popup (batch expected-area assertion correctly failed, not a successful destination test). Confirmed popup with physical Cross12 then420neutral: reached stage4area34 SepticTank variant1 warp2, restored control, no crash, HP81MP38. Full fixture `shelter-b2-septic-tank-arrival` counter543300 includes screenshot, replay/original cards/live snapshot. Also corrected analogous cross-TU staged callback in NeoArkForestZone via unique entry point; build/diff-check/disassembly confirm binding to its own room implementation, gameplay validation deferred until reached. Remaining direct roomEventStagedTask descriptors are defined in their implementation TU.

2026-11-05 — SepticTank intro completed; long neutral observation crossed into fight and Aya81→18HP. Native HealingII restored18→82HP for12MP. Added missing actor00400BodyTask to checkpoint enemy/root census (two240HP enemies), py_compile and live read verified. Traversed SepticTank without kills, entered MainCorridor B2 area33 variant1 warp6 at547466 with82HP27MP. Fixture `shelter-b2-main-corridor-arrival` preserves full replay/original initial cards/live snapshot. No new native defect confirmed this segment.

2026-11-05 — entered B2 BreedingRoom area32 variant1 from MainCorridor. Completed lengthy first Bowman diary at desk through native CAP inputs, restored control; left cage inspections command9/10 yielded text only. HP82MP27 unchanged; four maggotCaterpillar160HP east. Room data confirms replenish9mm/Stim/Cola objects but none collected. Fixture `shelter-b2-breeding-bowman-notes` counter564741 captures exploration. CAP can remain active with actor.state0; ensure dialogue fully closed before path inputs. No new native bug confirmed.

2026-11-05 — BreedingRoom ammo supply obtained via native CAP4 at southwest box: faceSouth from[2839,5619], inspect and confirm pickup. Verified PB160 reserve1→500 at568220. M93R still empty at568484; reload pending after closing remaining notice/CAP. HP82MP27 unchanged; HolyWater slot2. Fixture `shelter-b2-breeding-ammo-resupplied` preserves full physical replay/original cards/live snapshot. Confirmed pickup mapping from existing usage evidence: CAP4=PBflag25, CAP5=Colaflag52, CAP17=Stimflag23. Cola/Stim not collected.

2026-11-05 — reloaded M93R20 with480 reserve, attempted shooting caged BreedingRoom larva from[5123,3509] and one NecrosisI7MP; no HP change, collision/restriction unclassified, no native bug claim. Traversed room without kills, exited to B2NorthMaintenance area30 variant1 warp2 at570478. Aya82HP21MP, HolyWater2; fixture `shelter-b2-north-maintenance-arrival`. Cola/Stim remain uncollected.

2026-11-05 — completed B2NorthMaintenance introduction: actor00300EnemyTask400HP appeared during script, was removed by native scene teardown, control returned without damage (82HP21MP). Added actor00300EnemyTask to read-only checkpoint census, syntax/live verified. Reached OperatingRoom door, native card-reader refusal on this side. Fixture `shelter-b2-north-scene-complete` counter573627 preserves full replay/original cards/live state and locked-door screenshot. Need card/alternate approach via laboratory. Rendering artifacts during intro remain unclassified.

### 2026-11-05 — B2 north walkway return callback

Returning to BreedingRoom reproduced area0/audio poll0x7c00089f94 crash in PID47346/LLDB1397. Direct read confirms gShelterB2NorthMaintenanceWalkwayStagedEventTaskDesc callback was Dryfield roomEventStagedTask0x1001f6b9c. Previous audit missed positional initializer in _2.c. Fixed unique shelterB2NorthMaintenanceWalkwayStagedEventTask wrapper in controller TU, private declaration and descriptor. Build/diff-check pass; disassembly confirms branch to this room local staged implementation. Expanded generic staged-task search across all numbered room TUs now finds none. Runtime validation not yet complete: new fresh-card full replay `/tmp/pe2-b2-north-fixed-live-20261105` running, binary frozen there, initial prefix original crash replay+1000neutral. Fixture `shelter-b2-north-return-crash` preserves original input/cards and diagnosis.

2026-11-05 — B2NorthMaintenance return fix VERIFIED in fresh-card live full replay PID26558/LLDB54211. At575335 still native BreedingRoom caption, confirmed via physical Crosses; at575855 reached BreedingRoom area32 variant2 warp2, control restored, HP82MP21 unchanged, no audio corruption/crash. Fixture `shelter-b2-north-return-fixed` preserves replay/original cards/snapshot/screenshot. Next route back toMainCorridor/Lab orElevatorHall.

### 2026-11-05 — Maggot puff descriptor adjacency crash

BreedingRoom variant2 has three larvae moving on floor. Shooting now damages them, unlike variant1 caged encounter (supports geometry restriction, not established damage bug). At spray, EXC_BAD_ACCESS scheduler called _gCrawlerIdleClip data0x1009d7560 as task callback; original PID26558/LLDB54211 retained. actor02600 cached &gActor02600MaggotCaterpillarBodyTask scalar as two-entry array; index1 assumed separate static puff descriptor adjacent. Replaced cached recipe run with actual TaskDesc[2], retaining public body placement symbol/alias. Native build and diff-check pass. Fixture `shelter-b2-breeding-maggot-puff-crash`; fresh-card interactive full replay running from `/tmp/pe2-maggot-fixed-live-20261105` (binary frozen), runtime verification still pending. Aya82HP21MP, one larva118HP, others160; loaded17 reserve465 at crash (snapshot if needed).

2026-11-05 — companion puff bounds audit: both actor02600 and05500 drew puff age14 through radius[14] of14-element arrays; recovered source documents adjacent PS1 body flags halfword1. Expanded both radius tables to15 entries ending1, preserving recovered visual value with defined indexing; updated shared comment. Native build/diff-check pass. Current frozen interactive replay91537/PID357 tests descriptor fix only (started before radius edit); final-radius runtime coverage remains pending on next rebuild launch.

2026-11-05 — Maggot descriptor fix runtime VERIFIED in fresh replay PID357/LLDB91537: passed original scheduler crash at576484; actual puff attack applied darkness and8HP damage, subsequent attacks proceeded without crash. MetabolismI consumed7MP and cleared status; HealingII attempts interrupted before cost, HP47MP14 at577315. Active battle ongoing; no kills yet. Fixture `shelter-b2-maggot-puff-fixed`. Frozen live binary predates separately built radius-age14 bounds fix. Debug static padFrame address moved to0x100e2cc60, corrected controller condition after FIFO wait; process was temporarily debugger-stopped then resumed.

### 2026-11-05: physical replay reached Neo Ark

Continued the maggot-fixed live replay to input 584452. Repeated Breeding Room variant 2 puff attacks no longer hit the old invalid task callback crash. Escaped to B2 Main Corridor with HP71; confirmed the Elevator Hall door is locked. Lab approach did not trigger a transition (do not treat that as proof of a port defect or confirmed lock). Corridor Divers reduced HP to38 while near the laboratory. Used the western lift panel, selected Go down and reached Neo Ark Eve Access Tunnel (stage5 area8 variant1), then approached the Eve elevator. Its native caption says it has no power. HP32 MP2, statusFlags64, Holy Water remains attachment2. Full physical input and original card baseline: build-port/reference/neo-ark-eve-access-arrival. Next: retreat to corridor and investigate Observatory route / power progression, preserving the current process. Radius table bounds correction remains build-verified only; frozen live binary includes descriptor fix but predates radius correction.

### 2026-11-05: native save restoration verified after Game Over

Eve Access Watchers inflicted confusion/paralysis; physical direction mashing escaped paralysis and returned through the lift with HP9 MP3 and cleared statuses (input587802). Observatory-side corridor panel displayed a blank caption box; debugger confirmed CAP record/choice advancement, so this was not a proven interpreter deadlock. Rendering issue remains unclassified. Subsequent return to combat killed Aya and triggered normal Game Over. Used native title Continue, moved five entries down to Sterilization Room(1), and loaded it. At input592114 restored stage4 area16 variant1, HP74 MP8/47 EXP1089 BP3878, Holy Water slot2 and 12x40mm. Actor control restored, no transition tasks. This closes the previously unverified native-save load check. Full replay fixture: build-port/reference/shelter-b1-native-save-reloaded. Next run should preserve healing MP, obtain Cola and 9mm in Breeding Room before optional north scene / Eve detour, and investigate Observatory access flag and blank caption rendering.

### 2026-11-05: Cola recovery and correct Bowman route identified

After native save load, replayed Pod scene and descended B2. Pod Watchers punished a blocked turn (HP74->12); escaped west corridor to Septic and Breeding Room without further loss. Collected Cola from cabinet near [399,-2127], native item5; used via USE menu: HP12->32, MP10->47. Two HealingII casts restored HP105 at MP23. Native ammo case replenished PB160 reserve to500. Holy Water attachment2 retained. Checkpoint610214: build-port/reference/shelter-b2-cola-healed-resupplied.

Route correction: B2 North Operating door requires Yoshida card0x122 (alternate Kyle route), so repeated attempts there were unproductive. Normal Bowman card comes from Brain Stinger in B1 North Maintenance Walkway after B2 North intro; use that card via B2 Elevator Hall / South Walkway into Operating and Laboratory. Walkthrough corroboration: https://shrines.rpgclassics.com/psx/pe2/walkthrough.shtml (Bowman Fate). Source corroborates north gate collectedBit0x22, B2 Elevator Hall gate Bowman card, Lab/Observatory progression dependencies. Next trigger B2 North intro then return B1 via Pod lift, fight Bowman with fresh ammo and healing MP.

### 2026-11-05: Dust Chute CAP overflows LP64 static primitive arena

Triggered B2 North intro and returned to B1 via Pod; no damage through Breeding, later corridor/tunnel hits reduced HP. Healing restored33->73 HP (MP28->16). Returning through Sterilization east internal door triggered native gas trap. Reached Dust Chute prompt with HP39 MP16. At input626747, closing CAP record3 crashes GPU_Enqueue reading env0xC. Read-only debugger proves static arena base0x102594000 bytes0x6000, frameBuffer1, cursor0x10259a100, so frame half0x3000 overflowed by0x100. Adjacent gGpuTaskOrderingTables at0x10259a010 contain glyph packet words, including tag0xC. Full fixture: build-port/reference/sterilization-dust-chute-gpu-overflow; original PID357/LLDB91537 preserved.

Source correction in src/main/display_types.h doubles resident primitive arena to0xC000 for 64-bit __psyz builds, retaining console0x6000. Host DMA packet links/lengths enlarge packet storage. Native build and git diff --check PASS. New frozen replay /tmp/pe2-dust-arena-fixed-live-20261105 launched in LLDB11566, full626748-sample prefix with freshly copied original card baseline. Runtime validation pending. Next advance past Dust Chute caption, escape to Dumping Hole, then continue normal route to Bowman.

Runtime validation of static arena fix: full physical replay reached626748 with identical HP39 MP16 and Dust Chute position/scene. Advanced100 neutral to626848 past original GPU fault. Both GsOT descriptors valid (length6, correct small-bank links); caption choices now render fully. Selected right-hand Here goes nothing and accepted. Input627878 reached Dumping Hole stage4 area39 warp3 variant1 with HP39 MP16, arrival scene still running. Fixture build-port/reference/sterilization-dust-chute-fixed-dumping-arrival. New active PID51902 LLDB11566, FIFO /tmp/pe2-dust-arena-fixed-live-20261105/control.fifo. Old crashed process retained. Expanded arena fix is runtime verified; no GPU guard masking or RAM writes used.

### 2026-11-05: Dumping Hole Glutton preparation and capture

At629278 arrival scene finished at[8800,-6000]. HealingII restored39->79HP, then learned AntibodyI through native PE menu for500EXP: MP4/47->49/49, EXP1089->589. Healing restored105HP MP37. Advancing east triggered Glutton introduction. At631063 player still scripted at[10436,-6000], facingEast. At632463 player was already captured ([7088,-6105], facingWest), Glutton state13/anim3. An additional60 aimed-fire input samples on a deterministic retry could not act because control was held and capture progressed to anim15, applying fatal damage105->-1251. This is an established capture sequence, not a confirmed port defect. The shared GLUTTON_STATE_DEATH=13 symbol does not describe this carrier state: actor403200 own state13 is HOLD_PLAYER.

Added _actor403200HostTask to read-only census plus GluttonWork state/stateTicks/phase/attackDelay/animId/wallDistance; py_compile and diffcheckPASS, runtime verifies3000HP. Preserve PID51902/LLDB11566 GameOver and retryPID33836/LLDB3416 captured/dead. Started earlier exact replay prefix631063 in /tmp/pe2-glutton-entry-live-20261105, same fixed frozen executable and fresh original cards. Next stop before capture and observe small increments; reload gun through native battle/menu, aim host mouth and avoid being caught. Holy Water remains slot2, reserve500.

### 2026-11-05: Glutton first controlled fight

Earlier retry stopped before capture (631063). Tracked intro in short increments: control returns at632273, scripted camera turns player West; previous held Run therefore ran into the boss, explaining capture. Native R1 reload loaded20 at632373. Aimed shots reduced host3000->2830 during first inhale; backwardRun8256 avoided capture with105HP. Later damage/healing and ineffective Necrosis: no poison reactionFlags0, only2 initial damage. Summoned Mad Chasers110HP can be swallowed for100HP each; body/closed-mouth shots at long range often deal1 or miss. Added _madChaserHiddenTask to census, plus Glutton pendingHeals/hostExposed. Actual aiming code: physicalCircle clears existing target, Square+Left/Right changes selection; turns during firing recovery may be partly ignored.

Current636960: Aya93HP6MP, Glutton2830/3000 phase0 state3 tick78, player[12014,128,-5912] yaw1867, gun2. One MadChaser killed0HP before swallowing, second110HP at[9363,-60,-6814]. Full fixture build-port/reference/dumping-hole-glutton-fight-progress. ActivePID85237 LLDB41601, FIFO /tmp/pe2-glutton-entry-live-20261105/control.fifo, helper retargeted. Boss still far from defeated. Continue retarget/reload, avoid capture and rain/spinner projectiles, kill summons promptly. No new proven native defect in this fight.

2026-11-05 — Dumping Hole supply crates verified with physical interactions: north [8816,-7824] CAP25 gives PB500; south [8816,-3984] CAP19 gives Hydra500. At638838 Aya66HP6MP, boss2770HP phase0. Hydra unattached; battle Start is attachment-use-only, so cannot load newly acquired type mid-fight. CombatLight65 consumed earlier during menu investigation. Preserved fixture dumping-hole-hydra-acquired and PID85237/LLDB41601. Starting exact full replay to629278 before battle to collect/equip Hydra and P229 first. No new native defect confirmed.

2026-11-05 — Hydra preparation fixture631879 verified105HP37MP, Hydra20 loaded/slot1 HolyWater2 CombatLight3 P2294. Physical gameplay progressed Glutton3000->641HP phase2 at646322; Aya32HP7MP, P229Hydra7 rounds, M93RHydra20 backup. Phase2 capture killed Aya at646911 (boss513HP), mouth reaches worldx13875: phase0/1 safe-distance assumptions inadequate after advance. Original PID12282 LLDB66410 retained. Full-input retry to646322 starting /tmp/pe2-glutton-final-live-20261105. Important armor has SIX attachment slots, not four; current attachment-use selected index must be read from gItemMenuSelectedAttachmentIndex, separate from inventory armorAttachment census. Fresh Start after weapon-switch/cast recovery required; ignored Start caused wasted neutral frames. No new native bug proven.

2026-11-05 — Glutton DEFEATED via full physical replay, boss-19HP state12 collapse at647994. Retry avoided phase2 inhale using Eastward forward run, not backwards: max pull52 exceeds backward speed24. Read-only census now includes root/mouth coordinates, exactXZdistance and mouth animation cue (mask0x3ff), verified against fatal hold distance677 and safe retry2298+. P229 critical hits triggered exposed retraction, finished boss without further damage. Rewards500EXP200BP/fullMP49, Recovery3/rifle80/grenades4 all collected. Aya healed32->105 via2 HealingII, MP25. At650862 entering GarbageIncinerator area40, native allocator trap _xzm_xzone_malloc_freelist_outlined during new Aya attachment TMD allocation176: confirmed crash, preceding heap corruption suspected, root cause pending. Fixture glutton-defeated-incinerator-heap-crash preserves full replay, original binary and snapshot. Active PID61858/LLDB98501 preserved stopped at fault; ASan build being prepared separately.

ASan full instrumentation stops earlier in spuCalcPitch(spu.c853), 2-byte read26 bytes past96-entry gSpuSemitonePitchTable (index109). Preserved separate asan-spu-pitch-read fixture and PID89276/LLDB12080. This read cannot explain later heap freelist write corruption. Preparing separate write-instrumented ASan build (-asan-instrument-reads=false) to locate the corrupting write without altering gameplay source/inputs; audio pitch bounds remain a confirmed separate defect to investigate.

Diagnostic caveat: write-ASan with default fill0xbe hung at133830 on scene timing deadline0xbebebebe (DryfieldWaterTower); PID22520 LLDB31496 retained stopped. New write-ASan malloc_fill_byte=0 reached650862 but had diverged to DryfieldGasStation, so this run does NOT validate the Glutton route or heap bug. PID46136 LLDB12227 at EOF preserved. Switched to GuardMalloc with exact frozen original binary/full trace in /tmp/pe2-incinerator-guard-live-20261105 (PID81381 LLDB94804). No game source workaround applied. Static review also notes Glutton exit omits hit-body2 and swipeBody unlinks despite both being linked; causal relation not yet runtime established.

GuardMalloc exact frozen binary with MALLOC_ALLOW_READS=1 caught first corrupting write at163356: _actor01600StepStagedMotion4004 animFrame++ after _actor01600Remove freed work (stage3area1 variant1 scripted Scavenger). Caller _actor01600StepActivation also subsequently accessed work/color/root. Fixed staged-motion helper to return removal status, immediately propagate skip to activation/tick; added immediate returns to two equivalent fall-removal paths in Tick. Guard originalPID4324 LLDB42237 and fixture scavenger-staged-removal-uaf retained. Earlier GuardMalloc without allowreads stopped on MDEC VLC table read at152515, PID81381/LLDB94804 preserved. Build/runtime validation pending. No claim yet that this is the sole cause of650862 heap crash.

Scavenger fix runtime VERIFIED: GuardMalloc passed163356 and reached649597, while native replay reproduced650862 allocator trap. Thus Scavenger was a separate confirmed UAF, not sole incinerator cause. Guard649597 now catches exact Glutton collapse corruption: _shelterB3DumpingHoleCollapseEventTask taskKill frees work then falls through worldCoordSetModelLighting, whose colorMtx points into freed work. Fixed immediate return after normal taskKill and allocation-failure taskKill (also prevented NULL-work dereference). Fixture dumping-hole-collapse-lighting-uaf, PID81419/LLDB16048 retained, nativePID81421/LLDB25729 retained. New build/runtime validation pending.

2026-11-05 — BOTH fixes runtime VERIFIED on exact full650862-sample replay plus400neutral=651262: nativePID36107/LLDB47570 and GuardMallocPID36108/LLDB97994 reached stage4area40 GarbageIncinerator warp3room1 scripted arrival at[3200,0,-2500], HP105MP25 P229Hydra12, HolyWater2, Recovery3 carried. Both passed163356 Scavenger,649597 collapse lighting and650862 original native allocator fault. No other source workaround or target RAM change. Fixture glutton-defeated-incinerator-fixed includes physical trace, native/guard snapshots, screenshot. New active native FIFO /tmp/pe2-collapse-fixed-native-live-20261105/control.fifo, counter651262. Build/diffcheck/py_compile pass.

Incinerator native progress: entrance script completed652262, Glutton2 full3000HP. Trigger1 lift switch at[17280,-14561] reached653753, lift descends3units/tick from3000 to0 (~2000 physical samples), phaseLanded2 and room3 at655703, Aya67HP25MP from green debris. Control-room exit switch2[17248,-22368] blocked untilDescentComplete3. Actor444000 chooseattack requires phase4 HP<2500 plusplayerZ<-15800, thenphase5 HP<2000 plusZ<-17000 toadvance onto lift. Thus another1000HP required, not pure escape. At656315 player[14903,-23737] yaw2056, HP67MP25, boss3000phase4, safe far checkpoint. Later approach toz16336 left boss in middle range choosing deadly debris; died658336 withboss2994. Correct attack selection: distance>=9001 fromhost+(1311,250,-607) ALWAYSinhale, so withrootZ-9525 stayZ<-19133 (ideally-21000), avoidmidrange7k. Retry fullphysicalprefix656315 in /tmp/pe2-incinerator-fight-retry-live-20261105; deadnativePID36107 LLDB47570 preserved. Added actor444000GluttonTask toread-onlycensus/sharedGluttonWork, runtimeverified.

2026-11-05 — Incinerator optimized retry: restored656315 HP67MP25 safe far. Healing->105, AntibodyI6MP, switchedM93R. Actual bullet reach8704 units, so far21000–23000 forcesinhale (rootZ9525 far thresholdplayerZ<-19133) but mustallowpulluntilmouthdistance<~8200 beforefiring. Fullhealth retainedthroughHP3000->2580->2438->2280->2140->2036->1986. HP<2500advancedphase5rootZ-13025; HP<2000advancedphase6rootZ-16925 onto lift. DescentComplete3 at662114; stepEast intoautomatictrigger2at[17248,-22368] startsnativeexitsequence. Actor342000 doorclose script NULLcrash663492: _actor342000UpdateSceneStaging unconditionally loadswork->glutton->work even after_ actor342000RemoveGluttonModel clearsglutton; currentmode0NONEusesnoGluttondata. PointergluttonNULL verified; fault0x38. Fixed loadingGluttonWorkonlyin3modeswhichuseit (SINKS,ALONE,DOORS_SHAKE), preservingdoor/nonebehaviorwithoutlowRAMread. OriginalPID58715LLDB31548 retained; fixtureincinerator-door-staging-nullfulltrace/bt/snapshot. Build/runtimevalidationpending.


### 2026-11-05 — Incinerator door fix verified; control-room native save

The actor342000 staging NULL-load correction passed the identical physical input prefix in both native and GuardMalloc runs through counter 664092 (second Glutton battle rewards, 105 HP, full 49 MP). The native run then escaped the burning incinerator and completed Kyle’s control-room arrival dialogue by counter 673967. The control-room panel is a working telephone: Baldwin conversation and the native memory-card UI completed a save at counter 676607 (`Save complete.`). Recovery3 was attached through the inventory UI to empty slot 5 at counter 677187; Holy Water remains in slot 2. This attachment change occurred after the native save. Current state: Shelter B3 Incinerator Control Room, stage 4 / area 41, 105/105 HP, 49/49 MP, EXP 1789, BP 4208. Fixture `build-port/reference/incinerator-door-fixed-control-room` preserves the physical replay, checkpoint, screenshot, saved cards and GuardMalloc verification snapshot. No target calls or memory edits were used.

Physical continuation reached Shelter B4 Lower Sewer (stage 4 / area 43 / room 1 / warp 1) with Kyle at counter 679963, via the control-room east stairs. The north elevator-hall door reports locked. Replay fixture updated through the sewer arrival; native save remains the control-room save before attachment change.


### 2026-11-05 — Shelter B4 sewer traversal and reservoir

Physical replay continued from control room through Lower Sewer and Upper Sewer, clearing both enemy groups without HP loss (EXP 1789 -> 1829 -> 1865), and reached Reservoir (stage 4 / area 45 / room 1 / warp 2). Reservoir Bog Diver defeated through normal gunfire, EXP 1935, HP 87/105, MP 49/49, Kyle still 100 HP. Reservoir floodgate-A panel is reachable and its native numeric/password CAP UI runs, but code-entry attempts were rejected; puzzle remains unresolved at counter 690367. Fixture `shelter-b4-reservoir-panel` preserves the full physical input replay, live checkpoint and panel screenshot. No new crash observed on this segment. Last native save remains Incinerator Control Room before Recovery3 attachment.


### 2026-11-05 — Floodgate opened; Water Supply diver cleanup NULL

Reservoir code 18 accepted after verifying native `gCapSelectedChoiceIndex` and using four-sample button impulses; earlier one/two-sample inputs could be missed by gameplay sampling, so rejected attempts did not demonstrate a password defect. Native floodgate release/drain scene completed, room state 2 at counter 693571. Entered Water Supply (area 46) at 695378 and defeated its Bog Diver. At counter 697494 `_actor00400ReleaseSurfaceSpot` crashed writing address 0x6: `surfaceSpots == NULL`, index 0. The room is explicitly configured with NULL surface spots in `_gActor00400AreaConfigs`. Cleanup now releases a claim only when a list exists, retaining the despawn delay/state transition for both configurations. Build and `git diff --check` pass; full physical replay runtime validation pending. Original PID 54627 / LLDB 24225 remains preserved; fixture `water-supply-diver-null-surface-spots` includes crashing binary, input and checkpoint.

Runtime validation: the rebuilt native binary replayed the identical 697494-sample prefix, then passed cleanup and 600 neutral samples to 698094: Bog Diver HP 0/state 5, battleRefs 0, EXP 2005, Aya 87/105 HP and 49/49 MP. Continued native traversal up the east stair to the Water Hole route gate at counter 699453; gate is locked because the normal route-open flag is not yet set. No bypass used. Fixture `water-supply-diver-fixed` preserves verification/current checkpoints and replay. Active fixed process PID 69063 / LLDB 86336; original crash process retained.


### 2026-11-05 — Full Moon Gate and native return to Dryfield

Returned through Reservoir/Water Supply to the upper walkway in Upper Sewer (warp 3, variant 2). Defeated the remaining lower-channel Bog Diver (EXP 2075), making the OUTSIDE_BATTLE panel usable. Entered code 15 through native CAP choices and completed Full Moon Gate opening. Returned through Water Supply, east stairs and gate; native first-use departure reached Dryfield Night Water Hole (stage 3 / area 32 / room 3 / warp 3 / variant 10) at counter 717765, with Kyle arrival dialogue in progress. Aya 87/105 HP, 49/49 MP, Kyle 100 HP. No additional crash. Fixture `dryfield-return-from-shelter` records replay, checkpoint and screenshot. The diver cleanup fix remains in the running frozen binary; original crash retained.


### 2026-11-05 — Pierce reached and rescued on Water Tank

Completed Kyle’s Water Hole dialogue and traversed Driveway -> Factory -> Breezeway -> Water Tower -> Water Tank via native controls. Water Tank variant 10 spawned three Mind Sucklers (50 HP each). Cleared them using M93R and two successful Pyrokinesis II casts, with Healing II during combat; collected 50 Hydra from battle loot. EXP 2111, Aya 69/105 HP and 17/49 MP after rewards. Approaching Pierce triggered the native rescue conversation, including his acknowledgement of the rescue; timed scene completed by 738691. Follow-up interaction reports he is asleep and moving him could hurt him; Ice Bag handover has not been performed. Current counter 739753, stage 3 / area 21 / room 1 / variant 10. Fixture `dryfield-pierce-water-tank-rescue` preserves physical input, checkpoint and screenshot. No new crash in the segment; last memory-card save remains Incinerator Control Room.


### 2026-11-05 — Return from Pierce toward Main Street

Descended Water Tank, navigated the Water Tower fence via its east opening and entered G&R Kitchen variant 11. Three Scavengers and four actor04000 targets present; Scavengers defeated through native gunfire. Used attached Recovery3 at 14 HP to restore 105 HP; Holy Water untouched. Subsequent HP 58, MP 12 after leaving the remaining four targets through the Saloon door (native retreat result: -10 BP, +1 MP, no EXP). Arrived Saloon G&R stage 3 / area 18 / room 1 / warp 2 / variant 3 at counter 749582. Ice Bag not acquired and no new native save yet. Fixture `dryfield-saloon-after-pierce` preserves physical input and checkpoint. No new crash.


### 2026-11-05 — Saloon cleared after physical replay retry

Initial saloon attempt left Aya at 3 HP after interrupted Healing II casts; preserved PID 69063 / LLDB 86336 and low-HP snapshot. A separate process replayed the identical physical prefix through 749582, preserving the full Pierce rescue and all earlier fixes. At saloon entrance healed 58 -> 98 HP, loaded M93R with plentiful 9mm P.B. through the native inventory, and attached the remaining Recovery3 to slot 5. Used that Recovery3 during the fight. Native battle victory granted 48 EXP / 276 BP / 12 MP (EXP 2159, BP 5022); healed after victory 25 -> 65 HP using the reward MP. Saloon battleRefs 0, all four Scavengers and actor04000 target defeated. Reached Parking Lot stage 3 / area 15 / room 2 / warp 4 / variant 4 at counter 757693, HP 65, MP 0. No new crash. Ice Bag and native save still outstanding. Active process PID 84334 / LLDB 84019 in `/tmp/pe2-saloon-retry-native-live-20261105`; fixture `dryfield-saloon-cleared-parking` stores replay and current checkpoint.


### 2026-11-05 — Parking combat retry, no crash

Parking variant 4 contains five 68-HP actor02500 enemies and a 200-HP Desert Chaser. First physical continuation from 757693 lost Aya to the Chaser at 760100 (HP -1), after poorly positioned long-range targeting and attempted menu input during knockdown. P229 swap succeeded only after actor damage state 6/2 completed; this is input/state behavior, not evidence of a port defect. Preserved dead run PID 84334 / LLDB 84019 and fixture `parking-chaser-physical-death`. Started separate frozen-binary replay through the successful parking-entry prefix 757693 in `/tmp/pe2-parking-pe-retry-native-live-20261105`, LLDB 39374, to prepare PE/MP before reengagement. Goal remains active.


### 2026-11-05 — Parking Desert Chaser defeated on prepared retry

Separate physical replay reproduced successful parking entrance through 757693 (PID 40801 / LLDB 39374). Native PE menu strengthened Combustion I -> II for 1750 EXP, raising MP max 49 -> 50 and refilling MP; EXP 2159 -> 409. Used Healing II outside battle (65 -> 105 HP) and cast Antibody I once battle activated. Two Pyrokinesis II casts during Chaser movement phases did not damage it; switched through native attachment menu to P229, explicitly faced/locked the Chaser and defeated it with Hydra fire plus normal reload. At counter 761701 Desert Chaser HP -10 / state 21, Aya 95/105 HP and 18/50 MP, P229 8 Hydra loaded, battery 50. Five actor02500 enemies remain; no final parking reward, Ice Bag or new native save yet. Fixture `parking-chaser-defeated` preserves physical replay and checkpoint. No port crash. Original failed processes remain preserved.


### 2026-11-05 — Motel Lobby native save after Pierce rescue

Continued parking combat: three scorpions remained after Chaser and two scorpion kills; Hydra exhausted, switched to M93R/P.B. Used Healing II (59 -> 99 HP, MP 18 -> 6), reached lobby entrance and withdrew from remaining three scorpions (-10 BP, +1 MP). Arrived Motel Lobby stage 3 / area 17 / room 1 / warp 1 / variant 1 at 765963. Navigated behind the reception counter via its south end (counter occupies X 3700..4300, Z 2150..5000). Telephone interaction at [4751,2851] facing North: first CAP 10 description, repeat action starts Baldwin scene. Ask-about menu has THREE entries; third exits conversation (repeated Shelter/Backup choices loop normally, no softlock). Advanced to native memory-card overwrite UI, selected Yes and confirmed by counter 781185. Card0 `BASLUS-01042Eb2rWIXi` was updated at 2026-11-05 05:40:42 local, SHA256 3a7a469f98116439c191f8b0551fcf8ae2a3fc642b2e187c7205eedb9d5679ec, distinct from prior control-room card. Current Aya 57/105 HP, 7/50 MP, EXP 409, BP 5012; Combustion II learned, Holy Water remains attached. Fixture `dryfield-motel-lobby-native-save` preserves saved cards, full physical replay and checkpoint. Ice Bag still outstanding. No new crash. Active PID 40801 / LLDB 39374 preserved.


### 2026-11-05 — Native Motel Lobby save reload verified

Left Motel Lobby, encountered respawned full Parking Lot variant 4 (escape had not committed room clear), fled via Main Street exit with 11 HP. Main Street variant 1 includes six moths and another Desert Chaser; Aya died there after Antibody cast, no program crash. Native Game Over -> Start -> Continue -> four Down selections displayed `Motel Lobby (1)`, EXP 409/BP 5012. Loaded it through the native card UI; gameplay restored by counter 788868 to stage 3 / area 17 / room 1 / variant 1, HP 57/105, MP 7/50, Combustion II and prior inventory. This directly verifies the lobby card write/load, beyond file modification evidence. Fixture `dryfield-motel-lobby-save-reloaded` preserves the full input including death, native continue and the restored checkpoint. Ice Bag remains unacquired. Next work should replenish HP/MP/ammo or use better controlled combat before further traversal. Active PID 40801 / LLDB 39374; end 788868.


### 2026-11-05 — P229 secondary flash validated; native continue again

Prepared P229 with 12 P.B. rounds and its existing 50 battery through native inventory. Parking trial confirmed physical secondary button R2 (Square+R2 mask 33280) consumes one battery and sends Desert Chaser into state 17. Primary fire after flash reduced Chaser 200 -> 17; second successful flash/primary sequence killed it at counter 792496 (HP -63/state 21), using P.B., battery 48. This is a materially better native combat method than the previous unaided exchange. The five scorpions remained; Aya died at 793810 while attempting Combat Light at 2 HP. No crash. Native Game Over/Continue reloaded Motel Lobby correctly again by 797234: 57/105 HP, 7/50 MP, EXP 409. Fixture `parking-p229-flash-verified` preserves the physical trial and current reloaded checkpoint. Last successful native card remains unchanged; no Ice Bag acquired. Next resource options found in authored placements: Cola in Saloon G&R (object 0x15), MP Boost2 in Motel Room3 (object 0x2A), Recovery3/Cola in General Store; availability must be checked through native exploration. Bronco Masterkey collection 0x113 is already held.


### 2026-11-05 — Main Street cleared and first Ice Bag delivered to Pierce

Continued the live physical FIFO replay from native Motel Lobby save (797234). Traversed Parking to already-cleared Saloon G&R without HP loss; refrigerator CAP 11 at approximately [3639,-3973] provided Cola through native pickup. Used it: HP 57 -> 77, MP 8 -> 50, then Healing II -> 105 HP/38 MP. Equipped P229 and loaded 12 P.B. through native inventory. Fled Parking to Main Street with 59 HP/39 MP. Collected Ice Bag natively from the ice machine (collection 281); moth hits interrupted two Healing casts without consuming MP. Metabolism cleared status flag 1 (7 MP). Plasma I (6 MP) killed all six nearby moths and stunned/damaged Desert Chaser; Healing II then succeeded at 8 HP -> 53 HP. Two P229 R2 flashes followed by primary P.B. fire defeated remaining Chaser without further HP loss. Full Main Street reward confirmed by 809684: +87 EXP, +158 BP, +10 MP, totals EXP496/BP5150/MP24.

Driveway route is blocked by the authored post-balcony story gate. Returned physically via Main Street -> Parking -> Saloon -> Kitchen -> Water Tower -> Water Tank. Healing II in Parking restored 53 -> 105 HP; Chaser/scorpions reduced it to 74, then escaped to Saloon (+1 MP). Ice Bag remained held through the route and Water Tank loaded variant11. Reached Pierce at [1677,-2085] facing West; native interaction at 819386 consumed Ice Bag, dialogue explicitly accepted the ice. Received Cola reward by 820142, confirmed item5 quantity1. Current Aya 74/105 HP, 13/50 MP, EXP496; Holy Water remains attached slot2. No new crash or source fix during this run. Fixture `pierce-first-ice-delivered` preserves full physical replay and checkpoint; this is replay evidence, not a new memory-card save. Last native card remains earlier Motel Lobby. Active PID40801 / LLDB39374 preserved.


### 2026-11-05 — Motel Room6 native save and reload after first Pierce ice

The remaining Pierce no-ice CAP pages were still open after handover; continued physical Cross input closed them by 821750, restoring actor state0 and pendingMode0. This was ordinary caption progression, not a proven softlock. Descended Water Tank, crossed Water Tower's east fence opening and used its northeast Room6 back entrance at approximately [5568,-5248] facing East. This avoids Parking/Balcony combat entirely. Room6 arrival [770,6640] is in the rear passage; navigate South to z~7580, North back to z~6745, East to x~1680, then North through the x1173..2183 gap to z6016. Facing West/Cross there activates phone command22. Earlier phone attempts had been blocked by bathroom furniture; command11 at [3936,4000] is not the phone.

Phone led directly to native save list. Overwrote the previous fifth MotelLobby file with MotelRoom6(1) by 825770. Card0 file BASLUS-01042Eb2rWIXi updated at 2026-11-05 06:31:41 local, SHA256 e69f1d277d27ac154d8deca744739f954d253d6db7ce2998b082b27cd75eec5f. Backed up saved cards. Verified by physical soft-reset chord Select+Start+L1+L2+R1+R2 (mask3849), title Start -> Continue -> four Down selections: native menu displayed Motel Room6(1), EXP496/BP5140. Actual reload completed by 829406, stage3/area30/room1/view4/variant1, [1683,6016], HP74/105, MP13/50, EXP496, BP5140, Cola1, P229 loaded12 P.B./battery48, HolyWater attached2. Handover progress nibble0x7B is3, proving first bag state persisted (next is second bag). Full replay, pre-reload checkpoint, reloaded checkpoint, card backup and load-menu screenshot stored in `room6-after-pierce-native-save`. No new crash or source fix. Native Room6 save is now the recovery point; active PID40801/LLDB39374 preserved, end829406.


### 2026-11-05 — Returned from Dryfield to B1; Brain Stinger reached; Ringer recovery

Continued native Room6 save after actual load. Used Pierce's Cola (HP74 ->94, MP13->50), exited via back door -> WaterTower -> Breezeway -> Factory. Garage now variant4 contains three Zebra Stalkers, not Douglas/shop; withdrew after HP94->74. Traversed Factory/Driveway -> WaterHole (well interaction faces SOUTH at [-1629,1700]) -> WaterSupply, stage4area46. Native east stairs descended; crossed floor, climbed west stairs, accepted Go down ladder CAP to UpperSewer variant4. Bypassed 450HP actor01100 and two240HP BogDivers without damage there. LowerSewer had one240HP BogDiver; hit once, HP74->56.

Correction to earlier route notes: LowerSewer's actual B3 ElevatorHall stair at [-6528,-1024] facingWest is OPEN. Cross climbed and automatically departed after retreat result; arrived B3 ElevatorHall area42/warp2 at848218. This differs from the previously inspected locked-looking doorway. Navigated hall around its north corridor to elevator [-4799,1136] facingEast. First-use caption releases emergency stop; native elevator sequence took Aya to B1 ElevatorHall area9/warp3/variant2 by850717. B1 corridor door flag0xA5 remains0, so use SouthWalkway -> Storeroom instead. Healed56->96, MP50->38. B1 SouthWalkway variant2 has two280HP actor01100; traversed to Storeroom with81HP/35MP.

Storeroom variant2 has SEVEN Green/Red Amoebas (actor02400 body), not an empty room. Extended read-only replay_checkpoint.py callback census/root positions for _actor02400BodyTask; py_compile and live census verified six80HP + one280HP. Silence is status0x10 and prevents ALL PE (including Metabolism), explaining blocked casts; repeated Amoeba touches also drainMP. Found native Ringer's Solution placement object0x32 in CAP command5 at [~3335,-1060] facingSouth. Native pickup displayed unidentified Vinyl Pack; item61 quantity1 confirmed. CombatLight65 was consumed through quick-menu input during this segment; no battle-clearing effect established.

Reached B1 NorthWalkway area12/variant2 at857203; BrainStinger400HP intro dialogue completed. P229/PB trial reduced400->130, but ranged attacks inflicted paralysis/silence and drain. Fifteen distinct directional/face-button presses release each paralysis episode; status can cause later episodes until timer expires. Used MetabolismI7MP and HealingII12MP (33->91HP). P229 secondary flashes consumed batteries but reaction9 has no special BrainStinger reaction; do NOT infer Chaser's stun strategy works here. BrainStinger heals below50% when MP permits and can recharge/drain to regainMP: a momentary0MP does NOT prove it cannot heal again. With Aya24HP/0MP, retreated through native Storeroom caption; Brain had healed to243HP by861997. No kill/Bowman card yet.

Storeroom re-entry at862213 was battlePhase0 before Amoeba engagement. Opened full Start menu there, used identified Ringer's Solution: HP24->105, MP1->50, no statuses (864391). This avoids losing live progress. Full item list preserves blank rows left by consumed items: Vinyl Pack was visible index8, not7. Native inventory then loaded P22912PB, equippedM93R and loaded20PB. Current867741: B1Storeroom area11/warp3/view6/variant2, [5750,2200] facingNorth, HP105/105 MP50/50 EXP496, HolyWater attached2, P229 attached4/battery45; full inventory still open and battlePhase0. Fixture `b1-return-ringer-rearmed` preserves replay/checkpoint. Last native card is verified MotelRoom6 save; current B1 recovery is replay-only. No port crash or source gameplay fix in this segment. Active PID40801/LLDB39374 preserved. Next close menus, immediately faceSouth/re-enter NorthWalkway, use Antibody early and offensive PE/M93R with full resources; secure Bowman card and a new native save.


### 2026-11-05 — Brain Stinger defeated; Bowman card acquired

Physical replay retry from rearmed B1 Storeroom succeeded. Cast Antibody I early, used M93R bursts, Pyrokinesis II, one Healing II and one Combustion II. Closed distance to approximately1000 world units for stronger gun bursts. Brain repeatedly recovered100HP; MP recharge/drain permits further healing even after briefly reaching0MP. Paralysis episodes released using fifteen distinct Square press edges, without rotating Aya. Confirmed lethal Brain HP-12/taskState2 at873175. Native reward completed: EXP496->601, BP5070->5228, MP0->8, HP34/105; statuses cleared and M93R reloaded20PB automatically. After native confirmation, collection0x121/289 (Bowman card, verified items.h) present at874599. HolyWater remains attached slot2; P22912PB/battery45, reserve299PB.

Entered B1 SleepingQuarters area14/warp2/variant2 at876340, [11820,5980] facingNorth. Room contains five80HP and two280HP actor02400 Amoebas. Fixture brain-stinger-bowman-card contains full physical trace and checkpoint at876340. No new native save yet: latest native card is still MotelRoom6; Bowman progress is replay-only. No crash or gameplay source change in this segment. Active PID40801/LLDB39374 preserved.

Post-card route: crossed SleepingQuarters west through internal doorway atX8300/Z5000, then via[1657,-1052] toMainCorridor area15/warp5 at879025. No damage inSleepingQuarters. MainCorridor variant2 contains THREE180HP ZebraStalkers (placementsZ-4000,-8500,-14500). Blindly attempting west thenSouth towardSterilization with34HP failed: firstStalker intercepted, AyaHP0 at879839 before room departure. PID40801/LLDB39374 preserved atdeath. Started independent physical replay fromBowmanfixture under PID52344/LLDB39173 in /tmp/pe2-bowman-recovery-native-live-20261105; empty isolatedcards, copiedpreferences, exact frozenbinary, matchingvideo/virtualclocks. Target is876340 checkpoint inSleepingQuarters; replay still running when this note was written. Must verify replaymatches before advancing. Need restoreHP/MP or fight firstStalker before continuing corridor; do not repeat blind traversal.

Recovery correction: first replay PID52344 with EMPTY cards diverged (endedAkropolis stage1area20/100HP), so not valid. Original full trace requires initial Gate1 save BASLUS-01042AX9T2sJm, preserved in mine-cavern-blizzard-chaser-complete/initial-cards. Added that initial-cards tree to brain-stinger-bowman-card fixture and trimmed trace to exact876340 samples matching checkpoint (earlier asynchronouscopy contained356extra samples). Corrected replay now running /tmp/pe2-bowman-original-card-live-20261105, LLDB52698; BP1 EOF452, BP2control305disabled. Verify checkpoint atEOF before continuation. Old advance helper still pointsdeadLLDB39374: replace only after corrected recovery verified.


### 2026-11-05 — Bowman card native save verified by actual reload

Corrected physical replay with ORIGINAL Gate1 initial card reached exact876340 checkpoint: SleepingQuarters[11820,5980],34HP8MP EXP601 andBowman0x121 collected. New activePID20345/LLDB52698, /tmp/pe2-bowman-original-card-live-20261105. Updated advance helper tothissession/FIFO.

Reproduced safeSleepingQuarters route. EnteredMainCorridor with220neutral aftertrigger instead oflongwait; firstStalker stillat[2,-4000] by877995. West145samples (first95onlymoved1620duearrivaldelay), turnSouth23, run48: onehit14HP. ContinuedSouth38 to[107,-542], native retreat reward-10BP+1MP, Crossconfirmations ->Sterilization at879175,20HP9MP. No need to defeat firstStalker for this escape; previous claimthatfightwasnecessary corrected. Sterilization remainsvariant1/empty.

Centerdoor at[3456,5449] sayssystemdown. Westto[2066,5449]andSouthCross nativeinternaldoorwarps to[2066,6626]; runSouth140+Cross ->[1992,11566], thenSouth40 tofarend. Phone is WEST at[1280,12544], facingWest, NOTboxat[4576,13056]. Actualinteraction at[1450,12647]West opens phone/save. Selected fifth existingfile, overwrite defaultsNo; Up selectsYes. Confirmedwrite883320. File BASLUS-01042Eb2rWIXi SHA2564a76b0d9a2c8b9f11284c20be8d19b8183766945631f7f90b076d7394ec472a1.

Native softreset/titleContinue/fourDown selectsSterilizationRoom(1), time4:26 EXP601/BP5218. Actual reload completed887006: verify reloaded.json for fullstate, Bowman289present. Fixture bowman-card-sterilization-native-save contains fulltrace, initialcards, savedcards, pre/reloadedcheckpoints andloadscreen. This replacesRoom6 aslatestverifiednative recovery; Room6backup preserved. HolyWater staysslot2. No newcrash/gameplayfix. Next obtainHP/MPsupplies and continueBowmangate throughB2ElevatorHall/SouthWalkway, avoidingYoshidacardNorthOperatingdoor.


### 2026-11-05 — Armory vending machine reached; medical recovery

FromBowmanSterilizationnative save20HP9MP, B1Podvariant3 has two280HP actor01100. AntibodyI cast afterengagement (outsidebattlecastrefused), then bypass reachedB2Podvariant3 with8HP4MP. B2Pod has three160HP larvae +450HP actor01100; bypass died890227. Reloadednative save. SterilizationWESTmiddlepassage isONEWAY andcannotreturn north. CENTERdoors report systemdown. Correct return: farendmoveSouthawayfromcenterdoorpillar toZ12566, EastX4736, NorthZ11756; CAPdoor4note thenrepeataction enters[4885,10452]. North125 to6550, CAPdoor8note/confirmations, exitsfront via[4995,1825]. Westto3456, Northdoor ->MainCorridor area15warp6. NoHP lossinsideSterilization. Reused physical recordedinput segment893913..898352 forlaterretry (87RLEsegments4439samples), verifiedsamearrival20HP9MP.

MainCorridorvariant2 three180HP ZebraStalkers. Onefailedcombatattempt with8HPafterfirstkill ranintosecond atclose range anddied900486. Native reloadandrepeat: firstZebra killed909598 withNOHP loss, M93R20PB from[0,-1259]; sustainedprimary fire isbetterthantryingTrianglebeforeweaponrecovery. Reloaded20PB, castAntibodyI6MP, advancedonly60run samples to[197,-3421]. Aimlocked FARZebra at6k whileNEARinvisibleZebra jumpedbehindAya: HP20->14->2, noportbugestablished. Nearactorbehaviour17=hiddenidle, far132HP. Nativequickattachment navigation usesLEFT/RIGHT, NOTUP/DOWN. Startonlyopensafterdamage/recoveryfinishes; threeStartattempts needed. Rightfromselectedslot3 ->slot4M93R/P229; Cross equipsP229, M93Rmovesattachment4.

P229secondary flashes DO holdZebraStalker: read-onlywork verified far132HP actor state5/substate1/clip15 afterR2flash, radius/range reached~6600. Near180HP actorstate17hiddenidle remaineduntargeted; do not inferbothstunned. Threeflashcharges usedduringtest, furtherflashrefreshedfarhold; battery45->41. RanNorth170 then30to[216,-9877], East86to[3051,-9842], nativeArmoryretreat confirmations ->area13warp1variant1 at913101,2HP4MP BP5208. Armoryempty. Basicvendingmachine isaccessibleWITHOUTArmoryCardkey; keyonlylocksinnerroom.

Vendingtrigger[4048,-2304]North: arrival[4503,-1869]was3unitsoutsidequad, extra8run andCross. SeveralintroCAPpages thennative shop. Cancelweaponslist ->categoryDown3Items. Actualitemlistorder Recovery1/Recovery2/MPBoost1/Penicillin/Stim/CombatLight/PepperSpray/Flare. Bought3Recovery2(item2,180BP each) +3MPBoost1(item6,320BP each), spent1500, BP3708. UsedoneRecovery2:2->102HP; oneMPBoost1:4->34MP. Twoeachremain.

AttachedRecovery2slots1and3, MPBoost1slot5; HolyWaterstill2, M93R4, slot6empty; P229equipped12PB/battery41. Fullattachmentpickerincludesammo/oldemptybottleentry, resetscandidate0GPS. CandidateRecovery2indices9/10, MPBoostindices11/12. Somefirstdirectionpulsesaftertransitionignored: alwaysreadselectionbeforeconfirm. CancelledaccidentalDiscardprompt withoutdiscard; oneMPBooststillcarriednotattached. Current927372: Armoryarea13,102HP34MP EXP601/BP3708; fixturebowman-armory-resupplied fulltrace+originalinitialcards/checkpoint. NativecardstillverifiedSterilization20HP9MP withBowman; newmedicalprogressreplayonly. No newcrash/sourcegameplayfix. Next exploitnormalB1Hall elevator route toB2Hall/Bowmangate instead ofreturningthroughdeadlyPod; corridorhallunlockfrominsideavailable.


### 2026-11-05 — Bowman gate opened; Laboratory native save reloaded

ContinuedArmory102HP34MP from927372. ReturnedMainCorridorarea15warp3 at927984, [3510,-10025]West. West140onlymoved2430duearrivaldelay, thenAntibodyI6MP, West30/Northturn23/run220 reached[-306,-18044] withoutHP loss. ExtraNorth12+action/CAPconfirmations unlocksB1Hall corridor gate frominside; arrived929451 B1Hallwarp2[-3864,1073]North,102HP29MP. North45/East280 ->[6099,26], East103 ->[9987,218]East, elevatorCAPB2default; nativeconfirmations reachedB2Hallarea27warp2variant1 at930742,102HP30MP. This route avoids B1/B2Pod.

B2Hallvariant1 SEVEN160HP larvae, bypassedeastside withoutdamage. South120+65, East24turn/16run ->[9453,3546]East. Nativegate explicitlydisplayed “The door unlocked when I swiped [Bowman’s Card] through the reader.” Cross/CAP/battleresult confirmations reachedSouthMaintenanceWalkwayarea28variant1 at931798,102HP31MP. Bowman gate nowunlocked.

SouthWalkwayhasfour70HPWatchers +fourAmoebas (80/80/29/80 observed). East130 ->[2205,-3946], South200 ->[2551,1886], Silence16/MP29. Watcherparalysis18stoppednextmovement;15Squaremashingedges canresumeaimand AUTO-ROTATE AyaNorth towardtarget. Do notassumeSquarepreservesfacing! RepeatedepisodesandwrongNorthorientationcausedlostHP. Eventually15Upedges, explicitheldLeft46 (noendneutral) verifiedyaw75South, forward55 ->[2405,4061], then15Upedges/Cross successfullystartedOperatingRoomCAPwith22HP. Battleescape/CAPconfirmations ->Operatingarea29warp1variant1 at934218,22HP24MP,statusclear.

UsedattachedRecovery2slot3 throughfullUSE: menuMain hadretainedKEY1, soCircle/Up/Cross selectedUSE0. P229weapon0/twoDownselectsbattery, twomoreDownselectsattachment3 (attachmentlayoutmovesbytwovertically). CommandsretainlastselectionDiscard2; Up1selectsUse1. HP22->105 at936456, MP24; oneRecovery2 remainsattached1, MPBoost1two(oneslot5,onecarried), HolyWater2/M93R4.

IMPORTANT census correction: OperatingRoom is NOTempty. OldhelperroomEnemies[]wasincomplete; actualbattleRefs6 androomplacements showtwoSlouch,threeCreepingStranger,oneSkullStalker. Aya105->75 duringtraversal. Extendedread-onlyreplay_checkpoint.py census/rootcallbacks with _actor07000SlouchTask/_actor07000SlouchHiddenTask/_actor207200CreepingStrangerTask/_skullStalkerTask. py_compilePASS andlivehelperreload/LabsnapshotPASS; sixenemycoverage notyetretestedlive inOperating. Gameplaybinaryunchanged.

Operatingroutefrom[10200,400]: mainentryVestibuleWestblocked9330. Southnear2446, Westto8195, SouthblockedthenWestto6600/2926, South45to4700 thenWest130to2550. WestblockeduntilNorth105to1326; West55to1188/1509; West12to832 thenNorth15to1256, nativeLabCAP/battleresult ->Labarea31warp2variant1 at939383,75HP25MP/no statuses, battleRefs0.

Labphoneat[3489,-3680], floor Northboundary~Z-3000. Clearaisle X4500..5000 betweenconsolebenches. Fromentry[6350,2900]NorthblockedZ264, goWestto~4700 thenNorth throughaisle, notWestedge. Collisiongridread-onlymap /tmp/pe2-lab-map.png helpedidentifyaisle; map usesrawgridfaces (floorpolygonsunreorderedsoillustrativeonly). Currentphonespot[3732,-2918]. NEAR_OR_FACING_QUAD triggerkind4 IGNORES authoredfacingNormal and testsbearingTOorigin unlessdistance<500; exactWestfailed despiteinsidequad. Left20 fromyaw3144 ->2264NorthWest facingphone triggeredscene942606. PhysicalCircle8192mapslogicalCross64 inGameSession, whileUIgPadConfirm64isphysicalCross16384; sessionremapscontrols, existingphysicalCrossinteractionremainscorrect. Do notchangecontrols basedonlylogicalconstants.

Phone4Cross reachedsaveoverwritepromptNo-default; Up/Confirm wrotefifthfile943784. NativeLabfileSHA256 e47f669994d1c31acf249a964b47584bcfbb17096dcc33712bb9136d63a29dd6. Softreset/Continue/fourDown showsLaboratory(1),4:31 EXP601/BP3658. Actualreload947470 verifiedLabarea31warp2variant1, [3732,-2918]yaw2264,75HP25MP andBowman289present, oneRec2/twoMPBoost1/HolyWater2. Fixturebowman-laboratory-native-save fulltrace/originalinitialcards/savedcards/loadscreen/pre/reloadedcheckpoints. Latestnative recovery nowLaboratory; olderSterilizationbackup preserved. ActivePID20345/LLDB52698/FIFOunchanged. Nextconsole puzzle/progression, phone postconsole scene andObservatory/NeoArk power. No newportcrash.
