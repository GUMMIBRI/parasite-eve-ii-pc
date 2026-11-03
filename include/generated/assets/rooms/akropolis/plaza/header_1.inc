/* rooms/akropolis/plaza/package: written from its room instance by tools/buildsteps/gen_room_inc.py. */

#include "types.h"
#include "gameplay/room.h"
#include "gameplay/view.h"

#ifndef PE_DECODE_WorldCollisionRoomResources
#define PE_DECODE_WorldCollisionRoomResources
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
static void peDecode_WorldCollisionRoomResources(WorldCollisionRoomResources* dst, const unsigned char* src)
{
    /* grid: pointer, set by the array's fixups */
    /* viewBoundaryTriggers: pointer, set by the array's fixups */
    /* actionTriggers: pointer, set by the array's fixups */
    /* occluders: pointer, set by the array's fixups */
}

#endif
WorldCollisionRoomResources gAkropolisPlazaRoomCollisionResources[1];
static void peDecodeArr_gAkropolisPlazaRoomCollisionResources(void* base, const unsigned char* src, size_t n)
{
    WorldCollisionRoomResources* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_WorldCollisionRoomResources(&dst[k], src + k * 16);
    dst[0].grid = &_gAkropolisPlazaCollisionGrid;
    dst[0].actionTriggers = _gAkropolisPlazaHelicopterWreckTrigger;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_plaza/gAkropolisPlazaRoomCollisionResources", gAkropolisPlazaRoomCollisionResources, peDecodeArr_gAkropolisPlazaRoomCollisionResources);
#ifndef PE_DECODE_ViewMapPtr
#define PE_DECODE_ViewMapPtr
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
static void peDecode_ViewMapPtr(u8** dst, const unsigned char* src)
{
    /* : pointer, set by the array's fixups */
}

#endif
u8* gAkropolisPlazaViewMaps[1];
static void peDecodeArr_gAkropolisPlazaViewMaps(void* base, const unsigned char* src, size_t n)
{
    u8** dst = base;
    for (size_t k = 0; k < n; k++) peDecode_ViewMapPtr(&dst[k], src + k * 4);
    dst[0] = (void*)&gViewIdentityMap;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_plaza/gAkropolisPlazaViewMaps", gAkropolisPlazaViewMaps, peDecodeArr_gAkropolisPlazaViewMaps);
ViewCount gAkropolisPlazaViewCounts[1];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_plaza/gAkropolisPlazaViewCounts", gAkropolisPlazaViewCounts);
#ifndef PE_DECODE_WorldCoordRoomLighting
#define PE_DECODE_WorldCoordRoomLighting
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
static void peDecode_WorldCoordRoomLighting(WorldCoordRoomLighting* dst, const unsigned char* src)
{
    /* lights: pointer, set by the array's fixups */
    /* ambientTable: pointer, set by the array's fixups */
}

#endif
WorldCoordRoomLighting gAkropolisPlazaRoomLightingTable[1];
static void peDecodeArr_gAkropolisPlazaRoomLightingTable(void* base, const unsigned char* src, size_t n)
{
    WorldCoordRoomLighting* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_WorldCoordRoomLighting(&dst[k], src + k * 8);
    dst[0].lights = &_gAkropolisPlazaRoomLights;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_plaza/gAkropolisPlazaRoomLightingTable", gAkropolisPlazaRoomLightingTable, peDecodeArr_gAkropolisPlazaRoomLightingTable);
