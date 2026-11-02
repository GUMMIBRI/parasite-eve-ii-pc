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
