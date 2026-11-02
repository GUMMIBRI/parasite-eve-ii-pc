# 32 vs 64 bit struct audit

`tools/port/size_audit.sh` rebuilds every `STATIC_ASSERT_SIZEOF` as a real assertion and lists the structs whose host
size differs from the PS1 size (126 today; 103 contain a pointer, 4 a `long`, the rest are tables of function
pointers). `tools/port/size_audit_classify.py` adds how each one is used.

## What actually breaks

A host-sized struct is harmless while it is only allocated, copied or indexed as a C type. It breaks when
**raw bytes cross a boundary**: a struct overlaid on bytes read from disc, a save or a demo file, a checksum or
`memcpy` over its bytes, or a hard-coded offset or size in the original code.

| Class | Structs | State |
|---|---|---|
| Save / demo byte images | `PlayerStatus` | Fixed: `coordMtx` pointer became `u32 coordMtxRef` (host pointer in `gHostPlayerCoordMtx`); the demo and save image now line up. `McSaveData` was never on the list. |
| Disc-relocated formats | `CapFile`, `CapCommandRef/Table`, `CapSequenceRecord/Table`, `CapTextRef`, `AreaRecord`, `AnimationSet`, `EvsCommand/EvsOperand`, `ViewCameraTable`, `ViewCountTable`, `ViewIndexTable`, `WorldCollision*`, `SpriteView`, `SpriteAreaTable` | CAP has a native decoder (`src/port/cap_asset.c`, `cap_resource.c`). Room collision has `room_collision.h`. The rest are decoded by the asset tools or built from compiled-in data (`gen_asm_data.py` lays them out with host sizes). Not all verified individually. |
| Static data from asm | everything the generator emits | Positional initializers use the host layout; pointer fields become symbol references. Checked by the build. |
| GPU packets | `SpriteDrawModePacket`, `SpritePacket`, `ActorLimbShadowScratch` | `long` members. `setlen` is type-based (`include/port/gpu_len.h`). |
| Runtime-only, allocation-only | `Task*`, `Enemy`, `GameActor`, `*Work`, `*Scratch`, `Ui*`, `TaskFuncTable*`, `TmdAllocation`, ... | No raw-byte use. Allocation and `sizeof` are host-consistent. Remaining risk is a hard-coded size or offset, which the audit counts as `sizeof`/`memcpy`/cast sites. |

## Open

- `Enemy` (461 casts), `Task` (202) and `GameActor` (32) are cast between each other and from raw words. Review these
  casts before adding more actor packages.
- `TaskFuncTable*` are arrays of function pointers indexed by an unchecked state. Fine on the host, but a state
  outside the table reads past it.
- Disc-relocated formats still need one decoder test each against the real disc.
