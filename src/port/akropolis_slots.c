// Akropolis image-slot table: initialized data that the decomp still keeps in asm
// (asm/USA/mapui/data/akropolis_stage/stage.data.s). Extents are bytes below the image workspace.
#include "common.h"
#include "main/gfx_types.h"
#include "main/areas.h"
#include "stages/akropolis/stage.h"

GfxImageSlot gAkropolisStageImageSlots[GAME_AREA_MIST_R21 + 1] = {
    [1] = GRAPHICS_IMAGE_SLOT(0x4AF80),
    [2] = GRAPHICS_IMAGE_SLOT(0x4DB90),
    [3] = GRAPHICS_IMAGE_SLOT(0x4D340),
    [4] = GRAPHICS_IMAGE_SLOT(0x461C0),
    [5] = GRAPHICS_IMAGE_SLOT(0x3C030),
    [6] = GRAPHICS_IMAGE_SLOT(0x4E910),
    [7] = GRAPHICS_IMAGE_SLOT(0x56FA0),
    [8] = GRAPHICS_IMAGE_SLOT(0x50630),
    [9] = GRAPHICS_IMAGE_SLOT(0x50660),
    [10] = GRAPHICS_IMAGE_SLOT(0x51060),
    [11] = GRAPHICS_IMAGE_SLOT(0x4EB10),
    [12] = GRAPHICS_IMAGE_SLOT(0x4C9F0),
    [13] = GRAPHICS_IMAGE_SLOT(0x4ED80),
    [14] = GRAPHICS_IMAGE_SLOT(0x435E0),
    [15] = GRAPHICS_IMAGE_SLOT(0x51250),
    [16] = GRAPHICS_IMAGE_SLOT(0x4BC60),
    [17] = GRAPHICS_IMAGE_SLOT(0x4F450),
    [18] = GRAPHICS_IMAGE_SLOT(0x4F110),
    [19] = GRAPHICS_IMAGE_SLOT(0x3A8E0),
    [20] = GRAPHICS_IMAGE_SLOT(0x3FAD0),
    [21] = GRAPHICS_IMAGE_SLOT(0x582D0),
};
