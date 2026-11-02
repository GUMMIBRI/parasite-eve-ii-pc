#include "main/text.h"
#include <libgpu.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define CHECK(x) do { if (!(x)) { fprintf(stderr, "line %d: %s\n", __LINE__, #x); exit(1); } } while (0)
static int calls;
int LoadImage(RECT* rect, u_long* payload)
{
    const u16* colors = (const u16*)payload;
    CHECK(rect->h == 1 && rect->x + rect->w <= 1024 && rect->y < 512);
    if (calls++ == 0) {
        CHECK(rect->x == 256 && rect->y == 243 && rect->w == 64);
        CHECK(colors[0] == 0 && colors[1] == 0xA94A && colors[2] == 0xF39C && colors[3] == 0xFFFF);
    } else {
        CHECK(calls == 2 && rect->x == 976 && rect->y == 511 && rect->w == 48);
        for (int i = 0; i < 11; ++i) CHECK(colors[i] == 0);
        CHECK(colors[11] != 0 && colors[15] == 0xFFFF);
    }
    return 0;
}
int main(void)
{
    textUploadPalettes(); CHECK(calls == 2);
    puts("font palettes: packed RGB555 values and 64/48-colour VRAM bounds OK");
    return 0;
}
