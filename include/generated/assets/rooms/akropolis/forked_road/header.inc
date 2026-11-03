/* rooms/akropolis/forked_road/package: written from its room instance by tools/buildsteps/gen_room_inc.py. */

#include "types.h"
#include "gameplay/direction.h"
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
WorldCollisionRoomResources gAkropolisForkedRoadRoomCollisionResources[3];
static void peDecodeArr_gAkropolisForkedRoadRoomCollisionResources(void* base, const unsigned char* src, size_t n)
{
    WorldCollisionRoomResources* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_WorldCollisionRoomResources(&dst[k], src + k * 16);
    dst[0].grid = &_gAkropolisForkedRoadCollisionGrid;
    dst[0].viewBoundaryTriggers = _gAkropolisForkedRoadViewBoundaryTriggers;
    dst[0].actionTriggers = _gAkropolisForkedRoadActionTriggers;
    dst[1].grid = &_gAkropolisForkedRoadCollisionGrid;
    dst[1].viewBoundaryTriggers = _gAkropolisForkedRoadViewBoundaryTriggers;
    dst[1].actionTriggers = _gAkropolisForkedRoadActionTriggers;
    dst[2].grid = &_gAkropolisForkedRoadCollisionGrid;
    dst[2].viewBoundaryTriggers = _gAkropolisForkedRoadViewBoundaryTriggers;
    dst[2].actionTriggers = _gAkropolisForkedRoadActionTriggers;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_forked_road/gAkropolisForkedRoadRoomCollisionResources", gAkropolisForkedRoadRoomCollisionResources, peDecodeArr_gAkropolisForkedRoadRoomCollisionResources);
static u8 _gAkropolisForkedRoadRoom2ViewMap[12];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_forked_road/_gAkropolisForkedRoadRoom2ViewMap", _gAkropolisForkedRoadRoom2ViewMap);
static u8 _gAkropolisForkedRoadRoom3ViewMap[12];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_forked_road/_gAkropolisForkedRoadRoom3ViewMap", _gAkropolisForkedRoadRoom3ViewMap);
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
u8* gAkropolisForkedRoadViewMaps[3];
static void peDecodeArr_gAkropolisForkedRoadViewMaps(void* base, const unsigned char* src, size_t n)
{
    u8** dst = base;
    for (size_t k = 0; k < n; k++) peDecode_ViewMapPtr(&dst[k], src + k * 4);
    dst[0] = (void*)&gViewIdentityMap;
    dst[1] = _gAkropolisForkedRoadRoom2ViewMap;
    dst[2] = _gAkropolisForkedRoadRoom3ViewMap;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_forked_road/gAkropolisForkedRoadViewMaps", gAkropolisForkedRoadViewMaps, peDecodeArr_gAkropolisForkedRoadViewMaps);
ViewCount gAkropolisForkedRoadViewCounts[3];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_forked_road/gAkropolisForkedRoadViewCounts", gAkropolisForkedRoadViewCounts);
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
WorldCoordRoomLighting gAkropolisForkedRoadRoomLightingTable[3];
static void peDecodeArr_gAkropolisForkedRoadRoomLightingTable(void* base, const unsigned char* src, size_t n)
{
    WorldCoordRoomLighting* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_WorldCoordRoomLighting(&dst[k], src + k * 8);
    dst[0].lights = &_gAkropolisForkedRoadRoomLights;
    dst[1].lights = &_gAkropolisForkedRoadRoomLights;
    dst[2].lights = &_gAkropolisForkedRoadRoomLights;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_forked_road/gAkropolisForkedRoadRoomLightingTable", gAkropolisForkedRoadRoomLightingTable, peDecodeArr_gAkropolisForkedRoadRoomLightingTable);
#ifndef PE_DECODE_DirectionWarpEntry
#define PE_DECODE_DirectionWarpEntry
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
static void peDecode_DirectionWarpEntry(DirectionWarpEntry* dst, const unsigned char* src)
{
    { int32_t v; memcpy(&v, src + 0, 4); dst->player.yaw.word = v; }
    { int32_t v; memcpy(&v, src + 4, 4); dst->player.x = v; }
    { int32_t v; memcpy(&v, src + 8, 4); dst->player.y = v; }
    { int32_t v; memcpy(&v, src + 12, 4); dst->player.z = v; }
    memcpy(dst->unknown_10, src + 16, 4);
    { int32_t v; memcpy(&v, src + 20, 4); dst->companion.yaw.word = v; }
    { int32_t v; memcpy(&v, src + 24, 4); dst->companion.x = v; }
    { int32_t v; memcpy(&v, src + 28, 4); dst->companion.y = v; }
    { int32_t v; memcpy(&v, src + 32, 4); dst->companion.z = v; }
    memcpy(dst->unknown_24, src + 36, 4);
    { int32_t v; memcpy(&v, src + 40, 4); dst->arrivalSound = v; }
    { int32_t v; memcpy(&v, src + 44, 4); dst->departureSound = v; }
    { int32_t v; memcpy(&v, src + 48, 4); dst->blockedSound = v; }
    { uint8_t v; memcpy(&v, src + 52, 1); dst->initialView = v; }
    { uint8_t v; memcpy(&v, src + 53, 1); dst->flags = v; }
    { uint16_t v; memcpy(&v, src + 54, 2); dst->mapFlagId = v; }
}

#endif
DirectionWarpEntry gAkropolisForkedRoadWarpEntries[5];
static void peDecodeArr_gAkropolisForkedRoadWarpEntries(void* base, const unsigned char* src, size_t n)
{
    DirectionWarpEntry* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_DirectionWarpEntry(&dst[k], src + k * 56);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_forked_road/gAkropolisForkedRoadWarpEntries", gAkropolisForkedRoadWarpEntries, peDecodeArr_gAkropolisForkedRoadWarpEntries);
