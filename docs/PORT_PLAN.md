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
