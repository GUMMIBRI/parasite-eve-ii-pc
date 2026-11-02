#include "port/tmd_layout.h"
#include <libgpu.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#define CHECK(x) do { if (!(x)) { fprintf(stderr, "line %d: %s\n", __LINE__, #x); exit(1); } } while (0)
int main(void)
{
    /* Mixed pre-transformed packets, including a two-layer textured quad,
     * followed by direct triangles. Projection happens in an earlier group. */
    u32 stream[] = {
        0xC8, 0, 0x10002, 0, (4u << 16) | 8,
        0xC0, 0, 0x10003, 0, 0x808080, (32u << 16) | 36,
        0xC4, 0, 0x10001, 0x00080000, /* vertex 0 -> XY */
        0x40C8, 0, 0x10002, 0, (124u << 16) | 72,
        (u32)-2,
        0x21, 0, 0x10002, 0, 0,
        0x39, 0, 0x10005, 0, 0, 0, 0, 0,
        0x4079, 0, 0x10006, 0, 0, 0, 0, 0, 0,
        0x38, 0, 0x10006, 0, 0, 0, 0, 0, 0,
        0x04, 0, 0x10003, 0, 0, 0,
        (u32)-2, (u32)-1
    };
    u32 raw[sizeof stream / sizeof *stream];
    memcpy(raw, stream, sizeof stream);
    TmdSource src = { .bufferHalfBytes = 232, .preXformRegionBytes = 172, .stream = stream };
    CHECK(peTmdPreparePacketLayout(&src) == 0);
    unsigned pre = sizeof(POLY_G3) + sizeof(POLY_GT3) + 2 * sizeof(POLY_GT4);
    CHECK(src.preXformRegionBytes == pre);
    CHECK(src.bufferHalfBytes == pre + sizeof(POLY_GT3) + sizeof(POLY_F3));
    CHECK((stream[4] & 65535) == offsetof(POLY_G3, x0));
    CHECK((stream[4] >> 16) == offsetof(POLY_G3, r0));
    CHECK((stream[10] & 65535) == sizeof(POLY_G3) + offsetof(POLY_GT3, x0));
    CHECK((stream[10] >> 16) == sizeof(POLY_G3) + offsetof(POLY_GT3, r0));
    CHECK(stream[14] == ((u32)offsetof(POLY_G3, x0) << 16));
    CHECK((stream[19] & 65535) == sizeof(POLY_G3) + sizeof(POLY_GT3) + offsetof(POLY_GT4, r0));
    CHECK((stream[19] >> 16) == sizeof(POLY_G3) + sizeof(POLY_GT3) + sizeof(POLY_GT4) + offsetof(POLY_GT4, r0));
    u32 saved[sizeof stream / sizeof *stream];
    memcpy(saved, stream, sizeof stream);
    CHECK(peTmdPreparePacketLayout(&src) == 0 && memcmp(saved, stream, sizeof stream) == 0);
    TmdSource nativeSizes = { .bufferHalfBytes = src.bufferHalfBytes,
        .preXformRegionBytes = src.preXformRegionBytes, .stream = raw };
    CHECK(peTmdPreparePacketLayout(&nativeSizes) == 0);
    CHECK(nativeSizes.bufferHalfBytes == src.bufferHalfBytes &&
          nativeSizes.preXformRegionBytes == src.preXformRegionBytes);
    CHECK(memcmp(raw, stream, sizeof stream) == 0);
    /* Bad projection destination must not partially change earlier records. */
    u32 bad[] = { 0xC8, 0, 0x20002, 0, 0x00040008, 0, 0x00000008,
                  (u32)-2, 0x21, 0, 0x10002, 0, 0, (u32)-2, (u32)-1 };
    u32 original[sizeof bad / sizeof *bad]; memcpy(original, bad, sizeof bad);
    TmdSource invalid = { .bufferHalfBytes = 28, .preXformRegionBytes = 28, .stream = bad };
    CHECK(peTmdPreparePacketLayout(&invalid) == -1);
    CHECK(memcmp(original, bad, sizeof bad) == 0 && !invalid.handlersResolved);
    CHECK(invalid.bufferHalfBytes == 28 && invalid.preXformRegionBytes == 28);
    puts("tmd packet layout OK");
    return 0;
}
