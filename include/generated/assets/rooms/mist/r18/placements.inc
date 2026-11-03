/* rooms/mist/r18/package: written from its room instance by tools/buildsteps/gen_room_inc.py. */

#include "types.h"
#include "actors/actor_213000.h"
#include "gameplay/area.h"
#include "stages/akropolis/actors/mist_rupert.h"
#include "stages/akropolis/stage.h"

#ifndef PE_DECODE_AreaResource
#define PE_DECODE_AreaResource
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
static void peDecode_AreaResource(AreaResource* dst, const unsigned char* src)
{
    { uint16_t v; memcpy(&v, src + 0, 2); dst->entryId = v; }
    { int16_t v; memcpy(&v, src + 2, 2); dst->fileNumber = v; }
    { uint8_t v; memcpy(&v, src + 4, 1); dst->fileGroupIndex = v; }
    { uint8_t v; memcpy(&v, src + 5, 1); dst->taskIndex = v; }
    memcpy(dst->unknown_6, src + 6, 2);
    /* taskTable: pointer, set by the array's fixups */
}

#endif
static AreaResource _gMistR18BriefingActorResources[3];
static void peDecodeArr_gMistR18BriefingActorResources(void* base, const unsigned char* src, size_t n)
{
    AreaResource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AreaResource(&dst[k], src + k * 12);
    dst[0].taskTable = &gMistRupertTaskDesc;
    dst[1].taskTable = &gActor213000EricBaldwinTaskDescriptors;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_r18/_gMistR18BriefingActorResources", _gMistR18BriefingActorResources, peDecodeArr_gMistR18BriefingActorResources);
#ifndef PE_DECODE_AreaVariant
#define PE_DECODE_AreaVariant
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
static void peDecode_AreaVariant(AreaVariant* dst, const unsigned char* src)
{
    /* placements: pointer, set by the array's fixups */
    /* resources: pointer, set by the array's fixups */
}

#endif
AreaVariant gMistR18AreaVariants[13];
static void peDecodeArr_gMistR18AreaVariants(void* base, const unsigned char* src, size_t n)
{
    AreaVariant* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AreaVariant(&dst[k], src + k * 8);
    dst[1].placements = gAkropolisStageMistR18Placements;
    dst[1].resources = _gMistR18BriefingActorResources;
    dst[3].placements = gAkropolisStageMistR18Placements;
    dst[3].resources = _gMistR18BriefingActorResources;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_r18/gMistR18AreaVariants", gMistR18AreaVariants, peDecodeArr_gMistR18AreaVariants);
