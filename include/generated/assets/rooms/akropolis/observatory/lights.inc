/* rooms/akropolis/observatory/package: written from its room instance by tools/buildsteps/gen_room_inc.py. */

#include "types.h"
#include "gameplay/light.h"
#include "gameplay/room.h"

#ifndef PE_DECODE_WorldCoordPointLight
#define PE_DECODE_WorldCoordPointLight
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
static void peDecode_WorldCoordPointLight(WorldCoordPointLight* dst, const unsigned char* src)
{
    { uint32_t v; memcpy(&v, src + 0, 4); dst->head.transform.lighting.composeStamp = v; }
    _Static_assert(sizeof(dst->head.transform.lighting.local.m) == 18, "head.transform.lighting.local.m");
    memcpy(&dst->head.transform.lighting.local.m, src + 4, 18);
    _Static_assert(sizeof(dst->head.transform.lighting.local.t) == 12, "head.transform.lighting.local.t");
    memcpy(&dst->head.transform.lighting.local.t, src + 24, 12);
    _Static_assert(sizeof(dst->head.transform.lighting.composed.m) == 18, "head.transform.lighting.composed.m");
    memcpy(&dst->head.transform.lighting.composed.m, src + 36, 18);
    _Static_assert(sizeof(dst->head.transform.lighting.composed.t) == 12, "head.transform.lighting.composed.t");
    memcpy(&dst->head.transform.lighting.composed.t, src + 56, 12);
    { int16_t v; memcpy(&v, src + 68, 2); dst->head.transform.lighting.viewId = v; }
    memcpy(dst->head.transform.lighting.unknown_46, src + 70, 4);
    { int16_t v; memcpy(&v, src + 74, 2); dst->head.transform.lighting.attenuation = v; }
    /* head.transform.lighting.parent: pointer, set by the array's fixups */
    { int16_t v; memcpy(&v, src + 80, 2); dst->head.color.r = v; }
    { int16_t v; memcpy(&v, src + 82, 2); dst->head.color.g = v; }
    { int16_t v; memcpy(&v, src + 84, 2); dst->head.color.b = v; }
    memcpy(dst->head.unknown_56, src + 86, 2);
    { int32_t v; memcpy(&v, src + 88, 4); dst->inner = v; }
    { int32_t v; memcpy(&v, src + 92, 4); dst->outer = v; }
}

#endif
static WorldCoordPointLight _gAkropolisObservatoryPointLights[12];
static void peDecodeArr_gAkropolisObservatoryPointLights(void* base, const unsigned char* src, size_t n)
{
    WorldCoordPointLight* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_WorldCoordPointLight(&dst[k], src + k * 96);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_observatory/_gAkropolisObservatoryPointLights", _gAkropolisObservatoryPointLights, peDecodeArr_gAkropolisObservatoryPointLights);
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
static WorldCoordRoomLights _gAkropolisObservatoryRoomLights;
static void peDecodeArr_gAkropolisObservatoryRoomLights(void* base, const unsigned char* src, size_t n)
{
    WorldCoordRoomLights* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_WorldCoordRoomLights(&dst[k], src + k * 24);
    dst[0].pointLights = _gAkropolisObservatoryPointLights;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_observatory/_gAkropolisObservatoryRoomLights", _gAkropolisObservatoryRoomLights, peDecodeArr_gAkropolisObservatoryRoomLights);
