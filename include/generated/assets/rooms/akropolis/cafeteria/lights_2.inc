/* rooms/akropolis/cafeteria/package: written from its room instance by tools/buildsteps/gen_room_inc.py. */

#include "types.h"
#include "gameplay/room.h"

#ifndef PE_DECODE_WorldCoordRoomLights
#define PE_DECODE_WorldCoordRoomLights
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
static void peDecode_WorldCoordRoomLights(WorldCoordRoomLights* dst, const unsigned char* src)
{
    { int32_t v; memcpy(&v, src + 0, 4); dst->directionalLightCount = v; }
    /* directionalLights: pointer, set by the array's fixups */
    { int32_t v; memcpy(&v, src + 8, 4); dst->pointLightCount = v; }
    /* pointLights: pointer, set by the array's fixups */
    { int32_t v; memcpy(&v, src + 16, 4); dst->coneLightCount = v; }
    /* coneLights: pointer, set by the array's fixups */
}

#endif
WorldCoordRoomLights gAkropolisCafeteriaRoomLights;
static void peDecodeArr_gAkropolisCafeteriaRoomLights(void* base, const unsigned char* src, size_t n)
{
    WorldCoordRoomLights* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_WorldCoordRoomLights(&dst[k], src + k * 24);
    dst[0].pointLights = gAkropolisCafeteriaPointLights;
    dst[0].coneLights = gAkropolisCafeteriaSpotLightStorage;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_cafeteria/gAkropolisCafeteriaRoomLights", gAkropolisCafeteriaRoomLights, peDecodeArr_gAkropolisCafeteriaRoomLights);
