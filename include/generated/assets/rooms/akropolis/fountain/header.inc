/* rooms/akropolis/fountain/package: written from its room instance by tools/buildsteps/gen_room_inc.py. */

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
WorldCollisionRoomResources gAkropolisFountainRoomCollisionResources[2];
static void peDecodeArr_gAkropolisFountainRoomCollisionResources(void* base, const unsigned char* src, size_t n)
{
    WorldCollisionRoomResources* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_WorldCollisionRoomResources(&dst[k], src + k * 16);
    dst[0].grid = &_gAkropolisFountainCollisionGrid;
    dst[0].viewBoundaryTriggers = _gAkropolisFountainViewBoundaryTriggers;
    dst[0].actionTriggers = _gAkropolisFountainActionTriggers;
    dst[1].grid = &_gAkropolisFountainCollisionGrid;
    dst[1].viewBoundaryTriggers = _gAkropolisFountainViewBoundaryTriggers;
    dst[1].actionTriggers = _gAkropolisFountainActionTriggers;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_fountain/gAkropolisFountainRoomCollisionResources", gAkropolisFountainRoomCollisionResources, peDecodeArr_gAkropolisFountainRoomCollisionResources);
static u8 _gAkropolisFountainRoom2ViewMap[24];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_fountain/_gAkropolisFountainRoom2ViewMap", _gAkropolisFountainRoom2ViewMap);
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
u8* gAkropolisFountainViewMaps[2];
static void peDecodeArr_gAkropolisFountainViewMaps(void* base, const unsigned char* src, size_t n)
{
    u8** dst = base;
    for (size_t k = 0; k < n; k++) peDecode_ViewMapPtr(&dst[k], src + k * 4);
    dst[0] = (void*)&gViewIdentityMap;
    dst[1] = _gAkropolisFountainRoom2ViewMap;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_fountain/gAkropolisFountainViewMaps", gAkropolisFountainViewMaps, peDecodeArr_gAkropolisFountainViewMaps);
ViewCount gAkropolisFountainViewCounts[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_fountain/gAkropolisFountainViewCounts", gAkropolisFountainViewCounts);
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
WorldCoordRoomLighting gAkropolisFountainRoomLightingTable[2];
static void peDecodeArr_gAkropolisFountainRoomLightingTable(void* base, const unsigned char* src, size_t n)
{
    WorldCoordRoomLighting* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_WorldCoordRoomLighting(&dst[k], src + k * 8);
    dst[0].lights = &_gAkropolisFountainRoomLights;
    dst[1].lights = &_gAkropolisFountainRoomLights;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_fountain/gAkropolisFountainRoomLightingTable", gAkropolisFountainRoomLightingTable, peDecodeArr_gAkropolisFountainRoomLightingTable);
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
DirectionWarpEntry gAkropolisFountainWarpEntries[5];
static void peDecodeArr_gAkropolisFountainWarpEntries(void* base, const unsigned char* src, size_t n)
{
    DirectionWarpEntry* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_DirectionWarpEntry(&dst[k], src + k * 56);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_fountain/gAkropolisFountainWarpEntries", gAkropolisFountainWarpEntries, peDecodeArr_gAkropolisFountainWarpEntries);
