#include "port/tmd_layout.h"
#include <libgpu.h>
#include <stdint.h>
#include <stdlib.h>
#include <limits.h>
#include <stddef.h>

/* Command payloads remain packed words. Only packet storage grows: PsyZ has
 * pointer-sized links/lengths and may pad the end of a primitive. */
static unsigned packetSize(u32 opcode, unsigned* disk)
{
    u32 kind = opcode & ~(0x4000u | 0x8000u | 0x10000u | 0x20000u);
    if (kind != 0x156) kind &= ~0x100u; /* per-corner colours */
    kind &= ~3u; /* pre-transformed and semi-transparent variants */
    switch (kind) {
    case 0x04: *disk = 20; return sizeof(POLY_F3);
    case 0x44: *disk = 24; return sizeof(POLY_F4);
    case 0x00: case 0x20: *disk = 28; return sizeof(POLY_G3);
    case 0x40: case 0x60: *disk = 36; return sizeof(POLY_G4);
    case 0x1C: *disk = 32; return sizeof(POLY_FT3);
    case 0x5C: *disk = 40; return sizeof(POLY_FT4);
    case 0x18: case 0x30: case 0x38: *disk = 40; return sizeof(POLY_GT3);
    case 0x58: case 0x70: case 0x78: case 0x154: *disk = 52; return sizeof(POLY_GT4);
    default: *disk = 0; return 0; /* projection pass or skipped command */
    }
}

/* Return the element word containing destination halfwords. For C4 only the
 * high half is a destination; all others scatter to two packet words. */
static int destinationWord(u32 opcode)
{
    switch (opcode) {
    case 0xC0: return 2;
    case 0xC4: return 0;
    case 0xC8: case 0x40C8: case 0x200C8: return 1;
    default: return -1;
    }
}

static int remap(u32 ref, const u32* map, unsigned bytes, u32* result)
{
    if ((ref & 3) || ref >= bytes || map[ref / 4] == UINT32_MAX ||
        map[ref / 4] > UINT16_MAX) return -1;
    *result = map[ref / 4];
    return 0;
}

int peTmdPreparePacketLayout(TmdSource* source)
{
    if (!source || !source->stream) return -1;
    if (source->handlersResolved != 0) return 0;
    if (source->preXformRegionBytes < 0 || source->bufferHalfBytes < source->preXformRegionBytes ||
        (source->preXformRegionBytes & 3)) return -1;
    unsigned preBytes = source->preXformRegionBytes;
    u32* map = preBytes ? malloc((size_t)preBytes) : NULL;
    if (preBytes && !map) return -1;
    for (unsigned i = 0; i < preBytes / 4; ++i) map[i] = UINT32_MAX;
    uint64_t oldPre = 0, newPre = 0, oldDirect = 0, newDirect = 0;
    for (u32* p = source->stream; *p != UINT32_MAX;) {
        u32 opcode = *p++;
        if (opcode == UINT32_MAX - 1) continue;
        u32 dims = p[1];
        p += 2;
        unsigned count = dims >> 16, stride = dims & 65535;
        unsigned disk, host = packetSize(opcode, &disk);
        unsigned layers = opcode & 0x4000 ? 2 : 1;
        if (host && count) {
            uint64_t slots = (uint64_t)count * layers;
            if (opcode & 1) {
                if (oldPre + slots * disk > preBytes) goto fail;
                for (uint64_t i = 0; i < slots; ++i) {
                    /* All polygon command words after the PS1 tag have the
                     * same relative layout; trailing host padding is skipped. */
                    for (unsigned off = 4; off < disk; off += 4)
                        if (map) map[(oldPre + off) / 4] = (u32)(newPre + offsetof(POLY_F3, r0) + off - 4);
                    oldPre += disk;
                    newPre += host;
                }
            } else {
                oldDirect += slots * disk;
                newDirect += slots * host;
            }
        }
        p += (size_t)count * stride;
    }
    if (oldDirect > (unsigned)source->bufferHalfBytes - preBytes) goto fail;
    /* Some compiled sources already use sizeof(POLY_*), others still have
     * disk constants. Derive required capacities from the stream, retaining
     * any larger authored reservation without expanding it a second time. */
    uint64_t hostPre = preBytes > newPre ? preBytes : newPre;
    uint64_t directBytes = (unsigned)source->bufferHalfBytes - preBytes;
    uint64_t hostHalf = hostPre + (directBytes > newDirect ? directBytes : newDirect);
    if (hostHalf > UINT16_MAX) goto fail;
    /* Validate before changing any stream word, then apply the same walk. */
    for (int apply = 0; apply < 2; ++apply) {
        for (u32* p = source->stream; *p != UINT32_MAX;) {
            u32 opcode = *p++;
            if (opcode == UINT32_MAX - 1) continue;
            u32 dims = p[1];
            p += 2;
            unsigned count = dims >> 16, stride = dims & 65535;
            int dest = destinationWord(opcode);
            if (dest >= 0 && count && stride <= (unsigned)dest) goto fail;
            for (unsigned i = 0; dest >= 0 && i < count; ++i) {
                u32 value = p[(size_t)i * stride + dest];
                u32 lo = value & 65535, hi;
                if (remap(value >> 16, map, preBytes, &hi) != 0 ||
                    (opcode != 0xC4 && remap(lo, map, preBytes, &lo) != 0)) goto fail;
                if (apply) p[(size_t)i * stride + dest] = lo | hi << 16;
            }
            p += (size_t)count * stride;
        }
    }
    source->preXformRegionBytes = (s32)hostPre;
    source->bufferHalfBytes = (s32)hostHalf;
    source->handlersResolved = PE_TMD_HOST_LAYOUT_READY;
    free(map);
    return 0;
fail:
    free(map);
    return -1;
}
