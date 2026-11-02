#include "port/tmd_source.h"
#include <string.h>

static uint32_t word(const unsigned char* p)
{
    return (uint32_t)p[0] | (uint32_t)p[1] << 8 |
           (uint32_t)p[2] << 16 | (uint32_t)p[3] << 24;
}

static void* array(unsigned char* image, size_t bytes, uint32_t base,
                   uint32_t address, size_t extent)
{
    if (address < base || (address & 3)) return NULL;
    size_t offset = (size_t)(address - base);
    if (offset > bytes || extent > bytes - offset) return NULL;
    return image + offset;
}

int peTmdDecodeSource(TmdSource* out, void* data, size_t bytes,
                      uint32_t base, size_t offset)
{
    unsigned char* image = data;
    const uint32_t endian = 1;
    TmdSource source = {0};
    /* The fixed-width PsyZ geometry types match the disk arrays on LE hosts. */
    _Static_assert(sizeof(TmdBone) == 36, "disk bone layout");
    _Static_assert(offsetof(TmdBone, local.t) == 20, "disk translation offset");
    _Static_assert(offsetof(TmdBone, parentIndex) == 32, "disk parent offset");
    _Static_assert(sizeof(SVECTOR) == 8, "disk vector layout");
    if (!out || !image || *(const unsigned char*)&endian != 1 ||
        ((uintptr_t)image & 3) || (offset & 3) || offset > bytes ||
        bytes - offset < 36 || bytes > UINT32_MAX ||
        (uint64_t)base + bytes > (uint64_t)UINT32_MAX + 1) return -1;
    const unsigned char* record = image + offset;
    uint32_t parts = word(record + 12);
    uint32_t half = word(record + 4), pre = word(record + 8);
    if (word(record) != 0 || parts > 256 || half > UINT16_MAX || pre > half) return -1;
    source.partCount = parts;
    source.bufferHalfBytes = half;
    source.preXformRegionBytes = pre;
    source.partVertexCounts = array(image, bytes, base, word(record + 16), (size_t)parts * 4);
    source.verts = array(image, bytes, base, word(record + 20), 8);
    source.normals = array(image, bytes, base, word(record + 24), 8);
    source.skeleton = array(image, bytes, base, word(record + 28), (size_t)parts * 36);
    source.stream = array(image, bytes, base, word(record + 32), 4);
    if (!source.partVertexCounts || !source.verts || !source.normals ||
        !source.skeleton || !source.stream) return -1;
    for (uint32_t i = 0; i < parts; ++i) {
        uint32_t parent = i;
        /* Every chain must end at a self-parented root, never a cycle. */
        for (uint32_t hops = 0;; ++hops) {
            uint32_t next = (uint32_t)source.skeleton[parent].parentIndex;
            if (next >= parts || hops >= parts) return -1;
            if (next == parent) break;
            parent = next;
        }
    }
    size_t cursor = (unsigned char*)source.stream - image;
    int groupStart = 1;
    for (;;) {
        if (bytes - cursor < 4) return -1;
        uint32_t opcode = word(image + cursor);
        cursor += 4;
        if (opcode == UINT32_MAX) {
            if (!groupStart) return -1;
            break;
        }
        if (opcode == UINT32_MAX - 1) { groupStart = 1; continue; }
        groupStart = 0;
        if (bytes - cursor < 8) return -1;
        uint32_t dims = word(image + cursor + 4);
        cursor += 8;
        uint64_t payload = (uint64_t)(dims >> 16) * (dims & 65535) * 4;
        if (payload > bytes - cursor) return -1;
        cursor += (size_t)payload;
    }
    /* Disk handler addresses must be resolved to host IDs on first creation. */
    *out = source;
    return 0;
}
