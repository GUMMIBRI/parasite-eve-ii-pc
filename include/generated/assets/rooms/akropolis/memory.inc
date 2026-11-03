/* rooms/akropolis/stage: written from its room instance by tools/buildsteps/gen_room_inc.py. */

#include "types.h"
#include "main/gfx_types.h"

GfxImageSlot gAkropolisStageImageSlots[22] = {
    { .regionBase = NULL, .byteExtent = 0 },
    { .regionBase = PS1_RAM_PTR(0x8018C080), .byteExtent = 307072 },
    { .regionBase = PS1_RAM_PTR(0x80189470), .byteExtent = 318352 },
    { .regionBase = PS1_RAM_PTR(0x80189CC0), .byteExtent = 316224 },
    { .regionBase = PS1_RAM_PTR(0x80190E40), .byteExtent = 287168 },
    { .regionBase = PS1_RAM_PTR(0x8019AFD0), .byteExtent = 245808 },
    { .regionBase = PS1_RAM_PTR(0x801886F0), .byteExtent = 321808 },
    { .regionBase = PS1_RAM_PTR(0x80180060), .byteExtent = 356256 },
    { .regionBase = PS1_RAM_PTR(0x801869D0), .byteExtent = 329264 },
    { .regionBase = PS1_RAM_PTR(0x801869A0), .byteExtent = 329312 },
    { .regionBase = PS1_RAM_PTR(0x80185FA0), .byteExtent = 331872 },
    { .regionBase = PS1_RAM_PTR(0x801884F0), .byteExtent = 322320 },
    { .regionBase = PS1_RAM_PTR(0x8018A610), .byteExtent = 313840 },
    { .regionBase = PS1_RAM_PTR(0x80188280), .byteExtent = 322944 },
    { .regionBase = PS1_RAM_PTR(0x80193A20), .byteExtent = 275936 },
    { .regionBase = PS1_RAM_PTR(0x80185DB0), .byteExtent = 332368 },
    { .regionBase = PS1_RAM_PTR(0x8018B3A0), .byteExtent = 310368 },
    { .regionBase = PS1_RAM_PTR(0x80187BB0), .byteExtent = 324688 },
    { .regionBase = PS1_RAM_PTR(0x80187EF0), .byteExtent = 323856 },
    { .regionBase = PS1_RAM_PTR(0x8019C720), .byteExtent = 239840 },
    { .regionBase = PS1_RAM_PTR(0x80197530), .byteExtent = 260816 },
    { .regionBase = PS1_RAM_PTR(0x8017ED30), .byteExtent = 361168 },
};
s32 gAkropolisStageMovieWorkspaceBytesByArea[21];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_stage/gAkropolisStageMovieWorkspaceBytesByArea", gAkropolisStageMovieWorkspaceBytesByArea);
