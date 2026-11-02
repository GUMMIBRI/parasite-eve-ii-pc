#include "port/tmd_source.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define CHECK(x) do { if (!(x)) { fprintf(stderr, "line %d: %s\n", __LINE__, #x); exit(1); } } while (0)
static void put(unsigned char* p, uint32_t v)
{
    for (int i = 0; i < 4; ++i) p[i] = (unsigned char)(v >> (i * 8));
}
int main(void)
{
    _Alignas(4) unsigned char image[256] = {0};
    const uint32_t base = 0x80100000;
    unsigned char* record = image + 200;
    TmdSource out;
    put(record + 4, 120); put(record + 8, 40); put(record + 12, 2);
    put(record + 16, base); put(record + 20, base + 8);
    put(record + 24, base + 16); put(record + 28, base + 24);
    put(record + 32, base + 96);
    put(image + 24 + 20, (uint32_t)-23); /* signed bone translation */
    put(image + 24 + 36 + 32, 0); /* second bone parent is first */
    put(image + 96, 4); put(image + 100, 0x80012345); /* disk callback */
    put(image + 104, 0x10002); /* one two-word element */
    put(image + 116, (uint32_t)-2); put(image + 120, (uint32_t)-1);
    CHECK(peTmdDecodeSource(&out, image, sizeof image, base, 200) == 0);
    CHECK(out.skeleton[0].local.t[0] == -23 && out.partCount == 2);
    CHECK(out.stream == (u32*)(image + 96) && out.handlersResolved == 0);
    CHECK(out.stream[1] == 0x80012345); /* decoding does not mutate package */
    TmdSource saved = out;
    put(record + 32, base + 252); /* no terminator before end */
    CHECK(peTmdDecodeSource(&out, image, sizeof image, base, 200) == -1);
    CHECK(memcmp(&out, &saved, sizeof out) == 0);
    put(record + 32, base + 96);
    put(image + 104, UINT32_MAX); /* payload length overflow/truncation */
    CHECK(peTmdDecodeSource(&out, image, sizeof image, base, 200) == -1);
    put(image + 104, 0x10002);
    put(image + 116, UINT32_MAX); /* missing group marker */
    CHECK(peTmdDecodeSource(&out, image, sizeof image, base, 200) == -1);
    put(image + 116, UINT32_MAX - 1);
    put(image + 24 + 32, 1); /* 0 -> 1 -> 0 cycle */
    CHECK(peTmdDecodeSource(&out, image, sizeof image, base, 200) == -1);
    put(image + 24 + 32, 0);
    put(record + 28, base + 240); /* truncated skeleton */
    CHECK(peTmdDecodeSource(&out, image, sizeof image, base, 200) == -1);
    put(record + 28, base + 24);
    put(record + 20, base - 4);
    CHECK(peTmdDecodeSource(&out, image, sizeof image, base, 200) == -1);
    CHECK(peTmdDecodeSource(&out, image, 220, base, 200) == -1);
    CHECK(peTmdDecodeSource(&out, image + 1, 255, base, 200) == -1);
    puts("tmd source decode OK");
    return 0;
}
