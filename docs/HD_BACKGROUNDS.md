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
Frame submission currently reports the original 0..320 coverage: **there is no
runtime HD loader yet, so selecting Widescreen does not widen any room yet**.

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

- 42 C host tests pass, including coverage gating for complete, missing, partial,
  out-of-bounds and unsupported cases.
- Two synthetic inventory tests pass (duplicate pixel hashes, missing inputs,
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

1. Implement native background capture/identity, versioned pack metadata, bounded
   loading and atlas presentation for the actual LoadImage path. Keep PsyZ
   unmodified. Decide how much of PE1's pack/downloader format can be reused;
   its geometry/tile identity is not directly the PE2 identity.
2. Validate one complete background replacement with synthetic material first:
   original native pixels must remain unchanged when widescreen is off, model
   registration must match, and missing/malformed packs must retain 4:3.
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
