/* Captured RGB16 frames must remain packed even though PsyZ u_long is
 * pointer-sized. Check that map reservations use the same host RAM image. */
#include "main/gfx_types.h"
#include <stdio.h>
#include <stddef.h>

_Alignas(4) unsigned char gHostRam[0x200000];
static const GfxImageSlot slot = GRAPHICS_IMAGE_SLOT(0x4AF80);
_Static_assert(sizeof(FsImgBuffers) == 320 * 240 * 2, "packed RGB16 frame");
_Static_assert(sizeof(((FsImgBuffers*)0)->strips[0]) == 16 * 240 * 2, "packed strip stride");
int main(void)
{
    FsImgBuffers* image = PS1_RAM_PTR(0x801D7000);
    if (slot.regionBase != gHostRam + 0x18C080 ||
        slot.regionBase + slot.byteExtent != (u8*)image ||
        (u8*)(image + 1) != gHostRam + 0x1FC800) return 1;
    image->strips[19][FILE_SYSTEM_IMAGE_STRIP_WORDS - 1] = 0x12345678;
    if (gHostRam[0x1FC7FC] != 0x78 || gHostRam[0x1FC7FF] != 0x12) return 1;
    puts("image workspace OK");
    return 0;
}
