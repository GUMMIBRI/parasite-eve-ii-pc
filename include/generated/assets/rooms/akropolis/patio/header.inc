/* rooms/akropolis/patio/package: written from its room instance by tools/buildsteps/gen_room_inc.py. */

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
WorldCollisionRoomResources gAkropolisPatioRoomCollisionResources[3];
static void peDecodeArr_gAkropolisPatioRoomCollisionResources(void* base, const unsigned char* src, size_t n)
{
    WorldCollisionRoomResources* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_WorldCollisionRoomResources(&dst[k], src + k * 16);
    dst[0].grid = &_gAkropolisPatioCollisionGrid;
    dst[0].viewBoundaryTriggers = _gAkropolisPatioViewBoundaryTriggers;
    dst[0].actionTriggers = _gAkropolisPatioRoom1ActionTriggers;
    dst[0].occluders = _gAkropolisPatioOccluders;
    dst[1].grid = &_gAkropolisPatioCollisionGrid;
    dst[1].viewBoundaryTriggers = _gAkropolisPatioViewBoundaryTriggers;
    dst[1].actionTriggers = _gAkropolisPatioRooms2And3ActionTriggers;
    dst[1].occluders = _gAkropolisPatioOccluders;
    dst[2].grid = &_gAkropolisPatioCollisionGrid;
    dst[2].viewBoundaryTriggers = _gAkropolisPatioViewBoundaryTriggers;
    dst[2].actionTriggers = _gAkropolisPatioRooms2And3ActionTriggers;
    dst[2].occluders = _gAkropolisPatioOccluders;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_patio/gAkropolisPatioRoomCollisionResources", gAkropolisPatioRoomCollisionResources, peDecodeArr_gAkropolisPatioRoomCollisionResources);
static u8 _gAkropolisPatioRoom2ViewMap[20];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_patio/_gAkropolisPatioRoom2ViewMap", _gAkropolisPatioRoom2ViewMap);
static u8 _gAkropolisPatioRoom3ViewMap[20];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_patio/_gAkropolisPatioRoom3ViewMap", _gAkropolisPatioRoom3ViewMap);
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
u8* gAkropolisPatioViewMaps[3];
static void peDecodeArr_gAkropolisPatioViewMaps(void* base, const unsigned char* src, size_t n)
{
    u8** dst = base;
    for (size_t k = 0; k < n; k++) peDecode_ViewMapPtr(&dst[k], src + k * 4);
    dst[0] = (void*)&gViewIdentityMap;
    dst[1] = _gAkropolisPatioRoom2ViewMap;
    dst[2] = _gAkropolisPatioRoom3ViewMap;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_patio/gAkropolisPatioViewMaps", gAkropolisPatioViewMaps, peDecodeArr_gAkropolisPatioViewMaps);
ViewCount gAkropolisPatioViewCounts[3];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_patio/gAkropolisPatioViewCounts", gAkropolisPatioViewCounts);
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
WorldCoordRoomLighting gAkropolisPatioRoomLightingTable[3];
static void peDecodeArr_gAkropolisPatioRoomLightingTable(void* base, const unsigned char* src, size_t n)
{
    WorldCoordRoomLighting* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_WorldCoordRoomLighting(&dst[k], src + k * 8);
    dst[0].lights = &_gAkropolisPatioRoomLights;
    dst[1].lights = &_gAkropolisPatioRoomLights;
    dst[2].lights = &_gAkropolisPatioRoomLights;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_patio/gAkropolisPatioRoomLightingTable", gAkropolisPatioRoomLightingTable, peDecodeArr_gAkropolisPatioRoomLightingTable);
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
DirectionWarpEntry gAkropolisPatioWarpEntries[4];
static void peDecodeArr_gAkropolisPatioWarpEntries(void* base, const unsigned char* src, size_t n)
{
    DirectionWarpEntry* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_DirectionWarpEntry(&dst[k], src + k * 56);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_patio/gAkropolisPatioWarpEntries", gAkropolisPatioWarpEntries, peDecodeArr_gAkropolisPatioWarpEntries);
