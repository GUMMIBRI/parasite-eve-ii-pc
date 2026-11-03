/* rooms/akropolis/security_room/package: written from its room instance by tools/buildsteps/gen_room_inc.py. */

#include "types.h"
#include "gameplay/area.h"
#include "stages/akropolis/actors/security_monitors.h"
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
static AreaResource _gAkropolisSecurityRoomActorResources[3];
static void peDecodeArr_gAkropolisSecurityRoomActorResources(void* base, const unsigned char* src, size_t n)
{
    AreaResource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AreaResource(&dst[k], src + k * 12);
    dst[0].taskTable = &gSecurityMonitorsRupertTaskDesc;
    dst[1].taskTable = &gSecurityMonitorsSwatTaskDesc;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_security_room/_gAkropolisSecurityRoomActorResources", _gAkropolisSecurityRoomActorResources, peDecodeArr_gAkropolisSecurityRoomActorResources);
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
AreaVariant gAkropolisSecurityRoomAreaVariants[4];
static void peDecodeArr_gAkropolisSecurityRoomAreaVariants(void* base, const unsigned char* src, size_t n)
{
    AreaVariant* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AreaVariant(&dst[k], src + k * 8);
    dst[1].placements = gAkropolisStageSecurityRoomVariant1Placements;
    dst[1].resources = _gAkropolisSecurityRoomActorResources;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_security_room/gAkropolisSecurityRoomAreaVariants", gAkropolisSecurityRoomAreaVariants, peDecodeArr_gAkropolisSecurityRoomAreaVariants);
