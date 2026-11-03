/* rooms/akropolis/bridge/package: written from its room instance by tools/buildsteps/gen_room_inc.py. */

#include "types.h"
#include "gameplay/area.h"
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
static AreaResource _gAkropolisBridgeDefaultAreaResources[2];
static void peDecodeArr_gAkropolisBridgeDefaultAreaResources(void* base, const unsigned char* src, size_t n)
{
    AreaResource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AreaResource(&dst[k], src + k * 12);
    dst[0].taskTable = (void*)&_gAkropolisBridgeEnemyTaskDescStorage;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_bridge/_gAkropolisBridgeDefaultAreaResources", _gAkropolisBridgeDefaultAreaResources, peDecodeArr_gAkropolisBridgeDefaultAreaResources);
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
static AreaResource _gAkropolisBridgeVariant2AreaResources[1];
static void peDecodeArr_gAkropolisBridgeVariant2AreaResources(void* base, const unsigned char* src, size_t n)
{
    AreaResource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AreaResource(&dst[k], src + k * 12);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_bridge/_gAkropolisBridgeVariant2AreaResources", _gAkropolisBridgeVariant2AreaResources, peDecodeArr_gAkropolisBridgeVariant2AreaResources);
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
static AreaResource _gAkropolisBridgeVariant3AreaResources[1];
static void peDecodeArr_gAkropolisBridgeVariant3AreaResources(void* base, const unsigned char* src, size_t n)
{
    AreaResource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AreaResource(&dst[k], src + k * 12);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_bridge/_gAkropolisBridgeVariant3AreaResources", _gAkropolisBridgeVariant3AreaResources, peDecodeArr_gAkropolisBridgeVariant3AreaResources);
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
AreaVariant gAkropolisBridgePlacementVariants[12];
static void peDecodeArr_gAkropolisBridgePlacementVariants(void* base, const unsigned char* src, size_t n)
{
    AreaVariant* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AreaVariant(&dst[k], src + k * 8);
    dst[1].placements = gAkropolisStageBridgeDefaultPlacements;
    dst[1].resources = _gAkropolisBridgeDefaultAreaResources;
    dst[2].placements = gAkropolisStageBridgeVariant2Placements;
    dst[2].resources = _gAkropolisBridgeVariant2AreaResources;
    dst[3].placements = gAkropolisStageBridgeVariant3Placements;
    dst[3].resources = _gAkropolisBridgeVariant3AreaResources;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_bridge/gAkropolisBridgePlacementVariants", gAkropolisBridgePlacementVariants, peDecodeArr_gAkropolisBridgePlacementVariants);
