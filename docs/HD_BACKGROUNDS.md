# HD and widescreen backgrounds: implementation in progress

The target is optional authored HD backgrounds with horizontally extended artwork,
using the existing PsyZ sprite-atlas presenter. The original 320x240 camera,
models, native image pixels, timing and foreground masks remain authoritative.
Only a fully covered extended background may activate 16:9. Missing or unreviewed
artwork must retain the original, centred 4:3 image. Square pixels remains an
independent existing option.

## Current implementation

The Graphics page cycles Classic 4:3 / Square pixels / Widescreen (16:9).
`--widescreen 0|1` overrides the saved `widescreen` preference; invalid, missing
or duplicate values fail before launch. The preference persists in settings.ini.
It is separate from the renderer's effective widescreen state. The coverage gate
only enables widescreen for complete centred artwork at least 428 pixels wide;
unsupported backends and narrower spans fall back to original rendering.
The optional loader is enabled with `PE2_HD_BACKGROUNDS=/absolute/pack/path`.
It identifies the unmodified MDEC output by a 64-bit FNV-1a hash over all original
RGB555 words in row order, serialized little endian. It supports contiguous and
20-column image layouts. Without an available valid pack, frame submission keeps
original 0..320 coverage. Cropped transitions and active movies do not claim
full static coverage. No generated room artwork is approved yet.

This distinction matters for PE2. Unlike PE1's sprite-built backgrounds, its base
image is uploaded directly with LoadImage. Enabling PsyZ's squeeze without
re-presenting that background misaligns it with the game geometry. The initial
GPU comparison reproduced this; it must not be reintroduced by the loader.
Actual framebuffer rows are 0 and 272, not 0 and 256.

`PE2_DUMP_FRAME=<pad-tick>:<file.ppm>` captures the actual GPU presenter,
including widescreen framing, without using desktop screenshots. It complements
`PE2_DUMP_VRAM`, which captures native VRAM.
`tools/hd/check_fallback.py` reproduces a no-pack off/on comparison with both
renderers from an existing replay, and optionally compares a pre-change baseline. Use `PSYZ_HEADLESS=gpu` for hidden
Metal/Vulkan/D3D output, or `PSYZ_HEADLESS=1` for the software renderer.

## Pack and presenter

`PE2_DUMP_BACKGROUNDS=/ignored/local/directory` records exact 153600-byte
`<key>.rgb555` native backdrops and `observations.jsonl`, associating their keys
with observed stage/area/logical view/room state/warp/variant. These observations
are not a complete reachability survey and can include load/title frames.
All exports remain local game data.

Create a pack for one registered canvas:

```sh
venv/bin/python3 tools/hd/pack.py --native /local/<key>.rgb555 \
  --art /local/registered.png --left -64 --right 384 \
  --output build-hd-study/pack
PE2_HD_BACKGROUNDS="$PWD/build-hd-study/pack" ./build-port/parasite-eve-ii-pc \
  --disc /path/to/disc1.cue --widescreen 1
```

Use Picture detail 2x or above for HD atlas presentation; the current shader's
HD path is display-only above native resolution. At 1x the loader deliberately
keeps the original 4:3 image and does not claim wider coverage. The tool rejects wrong-sized
or transparent base artwork. It never crops, resizes or shifts it. For -64..384,
input must be exactly 1792x960, with the original centre at x=256..1535. The
PNG uses PE1/PsyZ's existing two-plane 68-pixel cell atlas format: 64 material
pixels at 4x plus 2-pixel replicated gutters, and original RGB reference cells
below. New side cells are presentation-only. Existing native sprites continue
to own foreground occlusion, palettes, masks, effects and model rendering;
they are not HD foreground artwork yet.

Each asset has a 48-byte `<key>.pe2bg` descriptor. Its Python layout is
`<8sQIIiiIIII`: magic `PE2BG1\0\0`, key, native width/height (320/240), left/right
bounds, static-base flag (1), scale (4), cell count, reserved zero. Bounds must
be 16-pixel aligned within -96..0 and 320..416; count must cover every 16x16
cell in the span and all 240 rows. This is a format/version marker, not proof of
artistic review. A whole-pack installer/download manifest is not implemented.

The loader rejects extra/truncated metadata, wrong identities, invalid flags,
scale/count/bounds, mismatched/oversized PNG headers and transparent material
cells, including gutters. It checks PNG dimensions and a 64 MiB encoded-size
limit before decoding. It reuses one active source atlas on view changes, rather
than retaining every room in GPU memory. Sprite material selection is serialized
as an application GP0 command in one FIFO submission per background; a separate
DrawPrim per cell exhausted Metal submission resources and must not return.
The presenter compensates for the actual draw offset (normally 160,120), and
restores the original draw mode after submission. PsyZ is unchanged.

GPU integration gate (requires Pillow, NumPy and a GPU):

```sh
cmake --build build-port --target background_presenter_probe
venv/bin/python3 tools/hd/check_presenter.py
venv/bin/python3 tests/hd_pack_test.py
```

This gate uses entirely synthetic native pixels with mixed STP/transparent
values and a centred game-style draw offset. It checks native VRAM equality,
a visible HD material change, full 16:9 corner coverage, and exact original
fallback for eight bad-pack cases. It does not prove all-game mask correctness.

## Local inventory and artwork inputs

After extraction, with Pillow and NumPy installed:

```sh
venv/bin/python3 tools/hd/inventory.py --export
venv/bin/python3 tests/hd_inventory_test.py
```

The default output is `build-hd-study/inventory/`, an ignored directory containing
disc-derived data. Never commit its inventory, source images or packs. The tool
accepts both decoded PNGs and the current raw BS store. It records compressed
and decoded hashes, dimensions, mapped view-file indices, special-renderer
warnings and an explicit unverified runtime status. It deduplicates exported
sources by compressed hash. Source file indices do not establish reachable
logical-view mappings.

Current local extraction: 1899 references, 1759 distinct raw/decoded backgrounds,
all 320x240, no missing sources. Stage 0 accounts for 41 references and includes
non-field screens requiring separate classification. Code inspection flags
Akropolis Square and Shelter R47 scrolling backdrops, the B1 pod tunnel image
scroll, Underpass/Garden foreground sprites, Pyramid puzzle overlay, Water Hole
water and West Elevator Hall glow. These warnings are not a runtime sweep.
The title's 8-bit texture use is its chrome effect, not proof of wider base art.

The first imagegen candidate is local under
`build-hd-study/art/mist-shooting-gallery-view10/`: source metadata, source PNG,
generated-v1.png and provenance.json with the exact prompt. Requested canvas:
1792x960, original view at 4x in the central 1280 pixels, 256 new pixels on each
side. Actual output: 1659x948. **Unapproved:** its registration/geometry has not
been verified and it must not be used as accepted artwork or committed.
The built-in imagegen tool was used; no API-key fallback was used.

## Verification checkpoint

- 43 C host tests pass, including native layout hashing, metadata/PNG-header checks and coverage gating for complete, missing, partial,
  out-of-bounds and unsupported cases. The hidden GPU probe also proves that
  native 1x rendering falls back exactly with a valid wide pack supplied.
- Two synthetic pack tests and two synthetic inventory tests pass (duplicate pixel hashes, missing inputs,
  stage-0 classification, special renderers and raw-store path resolution).
- CLI rejection, preference persistence and subsequent settings reload pass
  against isolated local profiles and the owner's two disc images.
- A 6001-sample New Game replay reaches the gallery course menu. At pad tick
  6000 the hidden Metal renderer produces byte-identical rendered PPMs and whole
  native VRAM dumps with the preference off/on and no art. The off dump also
  matches the pre-gating GPU run. This is one scene, not all-room parity.
- Local evidence: `/tmp/pe2-hd-safe-parity/{0,1}/`,
  `/tmp/pe2-hd-coverage-tests.log`, `/tmp/pe2-hd-inventory.log`; the reproducible
  four-run check and report live in `build-hd-study/fallback-check/`.
- The software baseline for this exact replay, before option edits, has SHA-1
  `c5f7de402de5dc1c6057ac55b15cafda1381b59f` at tick 6000. This is a different
  checkpoint from the earlier handoff's default-scene hash.

## Remaining required work

1. Finish production pack activation/installation/versioning and transition handling.
   The native source loader and PE1-compatible atlas presentation are implemented;
   downloader/UI activation, hot reload, title/captured-screen handling, and full
   validation across the game remain open. Keep PsyZ unmodified.
2. Extend synthetic and real-scene validation to all views and foreground layers.
   One active gallery checkpoint at tick 10000 of a 12001-sample replay with
   `PSYZ_RASTER_CLOCK=virtual` has exact full VRAM equality between baseline and
   HD 4:3. Both HD and wide material are visible; the wide capture is 1707x960.
   Evidence: `build-hd-study/game-integration-centred/`, with baseline in
   `build-hd-study/game-integration/baseline/`. This is one scene only. Earlier
   misaligned-offset captures under `fixture-check/` are rejected evidence.
3. Register/review the first generated artwork and its side coverage. Preserve
   masks, occluders, effects, dynamic layers and original lettering. Do not accept
   a visually plausible generation as geometry evidence.
4. Map every logical room/view to decoded background identity; run a complete
   runtime sweep including both discs, special renderers, view transitions,
   menus, dialogue, title, captured-room screens and RGB24 movies.
5. Produce and review the remaining artwork, make the pack consumable, expose
   activation and document distribution. Source/artwork files remain local;
   committing generated artwork requires the owner's agreement.
6. Prove full all-room off/baseline parity and wide coverage without holes. Check
   native state and masks as well as rendered captures; exercise missing art
   fallback, toggles, malformed packs and each supported GPU backend.

Work remains on local main. No push is authorized by the handoff. Do not commit
hd_handoff.md, modify PsyZ, or publish local source captures.
