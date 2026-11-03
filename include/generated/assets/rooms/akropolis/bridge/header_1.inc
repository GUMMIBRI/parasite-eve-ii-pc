/* rooms/akropolis/bridge/package: written from its room instance by tools/buildsteps/gen_room_inc.py. */

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
WorldCollisionRoomResources gAkropolisBridgeRoomCollisionResources[2];
static void peDecodeArr_gAkropolisBridgeRoomCollisionResources(void* base, const unsigned char* src, size_t n)
{
    WorldCollisionRoomResources* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_WorldCollisionRoomResources(&dst[k], src + k * 16);
    dst[0].grid = &_gAkropolisBridgeRoom1Collision;
    dst[0].viewBoundaryTriggers = _gAkropolisBridgeViewBoundaryTriggers;
    dst[0].actionTriggers = _gAkropolisBridgeRoom1ActionTriggers;
    dst[1].grid = &_gAkropolisBridgeRoom2Collision;
    dst[1].viewBoundaryTriggers = _gAkropolisBridgeViewBoundaryTriggers;
    dst[1].actionTriggers = _gAkropolisBridgeRoom2ActionTriggers;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_bridge/gAkropolisBridgeRoomCollisionResources", gAkropolisBridgeRoomCollisionResources, peDecodeArr_gAkropolisBridgeRoomCollisionResources);
static u8 _gAkropolisBridgeRoom2ViewMap[12];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_bridge/_gAkropolisBridgeRoom2ViewMap", _gAkropolisBridgeRoom2ViewMap);
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
u8* gAkropolisBridgeViewMaps[2];
static void peDecodeArr_gAkropolisBridgeViewMaps(void* base, const unsigned char* src, size_t n)
{
    u8** dst = base;
    for (size_t k = 0; k < n; k++) peDecode_ViewMapPtr(&dst[k], src + k * 4);
    dst[0] = (void*)&gViewIdentityMap;
    dst[1] = _gAkropolisBridgeRoom2ViewMap;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_bridge/gAkropolisBridgeViewMaps", gAkropolisBridgeViewMaps, peDecodeArr_gAkropolisBridgeViewMaps);
ViewCount gAkropolisBridgeViewCounts[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_bridge/gAkropolisBridgeViewCounts", gAkropolisBridgeViewCounts);
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
WorldCoordRoomLighting gAkropolisBridgeRoomLightingTable[2];
static void peDecodeArr_gAkropolisBridgeRoomLightingTable(void* base, const unsigned char* src, size_t n)
{
    WorldCoordRoomLighting* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_WorldCoordRoomLighting(&dst[k], src + k * 8);
    dst[0].lights = &_gAkropolisBridgeRoomLights;
    dst[1].lights = &_gAkropolisBridgeRoomLights;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_bridge/gAkropolisBridgeRoomLightingTable", gAkropolisBridgeRoomLightingTable, peDecodeArr_gAkropolisBridgeRoomLightingTable);
