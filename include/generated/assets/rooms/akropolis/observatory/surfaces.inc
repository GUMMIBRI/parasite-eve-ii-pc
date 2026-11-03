/* rooms/akropolis/observatory/package: written from its room instance by tools/buildsteps/gen_room_inc.py. */

#include "types.h"
#include "gameplay/room.h"

static WorldCollisionFootstepSounds _gAkropolisObservatoryFootstepSounds;
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_observatory/_gAkropolisObservatoryFootstepSounds", _gAkropolisObservatoryFootstepSounds);
#ifndef PE_DECODE_WorldCollisionSurfaceProperties
#define PE_DECODE_WorldCollisionSurfaceProperties
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
static void peDecode_WorldCollisionSurfaceProperties(WorldCollisionSurfaceProperties* dst, const unsigned char* src)
{
    { uint8_t v; memcpy(&v, src + 0, 1); dst->field_0 = v; }
    { uint8_t v; memcpy(&v, src + 1, 1); dst->probePassThrough = v; }
    { uint8_t v; memcpy(&v, src + 2, 1); dst->weaponImpactEnabled = v; }
    { uint8_t v; memcpy(&v, src + 3, 1); dst->suppressPushback = v; }
    /* footstepSounds: pointer, set by the array's fixups */
}

#endif
static WorldCollisionSurfaceProperties _gAkropolisObservatorySilentSurfaceProperties;
static void peDecodeArr_gAkropolisObservatorySilentSurfaceProperties(void* base, const unsigned char* src, size_t n)
{
    WorldCollisionSurfaceProperties* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_WorldCollisionSurfaceProperties(&dst[k], src + k * 8);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_observatory/_gAkropolisObservatorySilentSurfaceProperties", _gAkropolisObservatorySilentSurfaceProperties, peDecodeArr_gAkropolisObservatorySilentSurfaceProperties);
#ifndef PE_DECODE_WorldCollisionSurfaceProperties
#define PE_DECODE_WorldCollisionSurfaceProperties
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
static void peDecode_WorldCollisionSurfaceProperties(WorldCollisionSurfaceProperties* dst, const unsigned char* src)
{
    { uint8_t v; memcpy(&v, src + 0, 1); dst->field_0 = v; }
    { uint8_t v; memcpy(&v, src + 1, 1); dst->probePassThrough = v; }
    { uint8_t v; memcpy(&v, src + 2, 1); dst->weaponImpactEnabled = v; }
    { uint8_t v; memcpy(&v, src + 3, 1); dst->suppressPushback = v; }
    /* footstepSounds: pointer, set by the array's fixups */
}

#endif
static WorldCollisionSurfaceProperties _gAkropolisObservatoryFootstepSurfaceProperties;
static void peDecodeArr_gAkropolisObservatoryFootstepSurfaceProperties(void* base, const unsigned char* src, size_t n)
{
    WorldCollisionSurfaceProperties* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_WorldCollisionSurfaceProperties(&dst[k], src + k * 8);
    dst[0].footstepSounds = &_gAkropolisObservatoryFootstepSounds;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_observatory/_gAkropolisObservatoryFootstepSurfaceProperties", _gAkropolisObservatoryFootstepSurfaceProperties, peDecodeArr_gAkropolisObservatoryFootstepSurfaceProperties);
#ifndef PE_DECODE_SurfacePtr
#define PE_DECODE_SurfacePtr
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
static void peDecode_SurfacePtr(WorldCollisionSurfaceProperties** dst, const unsigned char* src)
{
    /* : pointer, set by the array's fixups */
}

#endif
WorldCollisionSurfaceProperties* gAkropolisObservatorySurfacePropertiesByClass[8];
static void peDecodeArr_gAkropolisObservatorySurfacePropertiesByClass(void* base, const unsigned char* src, size_t n)
{
    WorldCollisionSurfaceProperties** dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SurfacePtr(&dst[k], src + k * 4);
    dst[0] = &_gAkropolisObservatorySilentSurfaceProperties;
    dst[1] = &_gAkropolisObservatoryFootstepSurfaceProperties;
    dst[2] = &_gAkropolisObservatorySilentSurfaceProperties;
    dst[3] = &_gAkropolisObservatorySilentSurfaceProperties;
    dst[4] = &_gAkropolisObservatorySilentSurfaceProperties;
    dst[5] = &_gAkropolisObservatorySilentSurfaceProperties;
    dst[6] = &_gAkropolisObservatorySilentSurfaceProperties;
    dst[7] = &_gAkropolisObservatorySilentSurfaceProperties;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_observatory/gAkropolisObservatorySurfacePropertiesByClass", gAkropolisObservatorySurfacePropertiesByClass, peDecodeArr_gAkropolisObservatorySurfacePropertiesByClass);
