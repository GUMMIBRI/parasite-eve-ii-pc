/* rooms/akropolis/cafeteria/package: written from its room instance by tools/buildsteps/gen_room_inc.py. */

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
WorldCollisionRoomResources gAkropolisCafeteriaCollisionRooms[4];
static void peDecodeArr_gAkropolisCafeteriaCollisionRooms(void* base, const unsigned char* src, size_t n)
{
    WorldCollisionRoomResources* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_WorldCollisionRoomResources(&dst[k], src + k * 16);
    dst[0].grid = &_gAkropolisCafeteriaCollisionGrid;
    dst[0].viewBoundaryTriggers = _gAkropolisCafeteriaRooms1To3ViewBoundaries;
    dst[0].actionTriggers = _gAkropolisCafeteriaRoom1ActionTriggers;
    dst[0].occluders = _gAkropolisCafeteriaSightOccluders;
    dst[1].grid = &_gAkropolisCafeteriaCollisionGrid;
    dst[1].viewBoundaryTriggers = _gAkropolisCafeteriaRooms1To3ViewBoundaries;
    dst[1].actionTriggers = _gAkropolisCafeteriaRooms2To4ActionTriggers;
    dst[1].occluders = _gAkropolisCafeteriaSightOccluders;
    dst[2].grid = &_gAkropolisCafeteriaCollisionGrid;
    dst[2].viewBoundaryTriggers = _gAkropolisCafeteriaRooms1To3ViewBoundaries;
    dst[2].actionTriggers = _gAkropolisCafeteriaRooms2To4ActionTriggers;
    dst[2].occluders = _gAkropolisCafeteriaSightOccluders;
    dst[3].grid = &_gAkropolisCafeteriaCollisionGrid;
    dst[3].viewBoundaryTriggers = _gAkropolisCafeteriaRoom4ViewBoundaries;
    dst[3].actionTriggers = _gAkropolisCafeteriaRooms2To4ActionTriggers;
    dst[3].occluders = _gAkropolisCafeteriaSightOccluders;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_cafeteria/gAkropolisCafeteriaCollisionRooms", gAkropolisCafeteriaCollisionRooms, peDecodeArr_gAkropolisCafeteriaCollisionRooms);
static u8 _gAkropolisCafeteriaRooms2And3ViewMap[24];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_cafeteria/_gAkropolisCafeteriaRooms2And3ViewMap", _gAkropolisCafeteriaRooms2And3ViewMap);
static u8 _gAkropolisCafeteriaRoom4ViewMap[24];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_cafeteria/_gAkropolisCafeteriaRoom4ViewMap", _gAkropolisCafeteriaRoom4ViewMap);
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
u8* gAkropolisCafeteriaViewMaps[4];
static void peDecodeArr_gAkropolisCafeteriaViewMaps(void* base, const unsigned char* src, size_t n)
{
    u8** dst = base;
    for (size_t k = 0; k < n; k++) peDecode_ViewMapPtr(&dst[k], src + k * 4);
    dst[0] = (void*)&gViewIdentityMap;
    dst[1] = _gAkropolisCafeteriaRooms2And3ViewMap;
    dst[2] = _gAkropolisCafeteriaRooms2And3ViewMap;
    dst[3] = _gAkropolisCafeteriaRoom4ViewMap;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_cafeteria/gAkropolisCafeteriaViewMaps", gAkropolisCafeteriaViewMaps, peDecodeArr_gAkropolisCafeteriaViewMaps);
ViewCount gAkropolisCafeteriaViewCounts[4];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_cafeteria/gAkropolisCafeteriaViewCounts", gAkropolisCafeteriaViewCounts);
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
WorldCoordRoomLighting gAkropolisCafeteriaRoomLightingTable[4];
static void peDecodeArr_gAkropolisCafeteriaRoomLightingTable(void* base, const unsigned char* src, size_t n)
{
    WorldCoordRoomLighting* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_WorldCoordRoomLighting(&dst[k], src + k * 8);
    dst[0].lights = &gAkropolisCafeteriaRoomLights;
    dst[0].ambientTable = gAkropolisCafeteriaViewAmbientColors;
    dst[1].lights = &gAkropolisCafeteriaRoomLights;
    dst[1].ambientTable = gAkropolisCafeteriaViewAmbientColors;
    dst[2].lights = &gAkropolisCafeteriaRoomLights;
    dst[2].ambientTable = gAkropolisCafeteriaViewAmbientColors;
    dst[3].lights = &gAkropolisCafeteriaRoomLights;
    dst[3].ambientTable = gAkropolisCafeteriaViewAmbientColors;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_cafeteria/gAkropolisCafeteriaRoomLightingTable", gAkropolisCafeteriaRoomLightingTable, peDecodeArr_gAkropolisCafeteriaRoomLightingTable);
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
DirectionWarpEntry gAkropolisCafeteriaWarps[3];
static void peDecodeArr_gAkropolisCafeteriaWarps(void* base, const unsigned char* src, size_t n)
{
    DirectionWarpEntry* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_DirectionWarpEntry(&dst[k], src + k * 56);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_cafeteria/gAkropolisCafeteriaWarps", gAkropolisCafeteriaWarps, peDecodeArr_gAkropolisCafeteriaWarps);
