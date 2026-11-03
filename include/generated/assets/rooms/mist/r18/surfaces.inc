/* rooms/mist/r18/package: written from its room instance by tools/buildsteps/gen_room_inc.py. */

#include "gameplay/room.h"

static WorldCollisionFootstepSounds _gMistR18FootstepSounds;
#include "port/asset_bind.h"
PE_ASSET_BIND("room/mist_r18/_gMistR18FootstepSounds", _gMistR18FootstepSounds);
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
static WorldCollisionSurfaceProperties _gMistR18SurfaceProperties;
static void peDecodeArr_gMistR18SurfaceProperties(void* base, const unsigned char* src, size_t n)
{
    WorldCollisionSurfaceProperties* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_WorldCollisionSurfaceProperties(&dst[k], src + k * 8);
    dst[0].footstepSounds = &_gMistR18FootstepSounds;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_r18/_gMistR18SurfaceProperties", _gMistR18SurfaceProperties, peDecodeArr_gMistR18SurfaceProperties);
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
WorldCollisionSurfaceProperties* gMistR18SurfacePropertiesByClass[8];
static void peDecodeArr_gMistR18SurfacePropertiesByClass(void* base, const unsigned char* src, size_t n)
{
    WorldCollisionSurfaceProperties** dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SurfacePtr(&dst[k], src + k * 4);
    dst[0] = &_gMistR18SurfaceProperties;
    dst[1] = &_gMistR18SurfaceProperties;
    dst[2] = &_gMistR18SurfaceProperties;
    dst[3] = &_gMistR18SurfaceProperties;
    dst[4] = &_gMistR18SurfaceProperties;
    dst[5] = &_gMistR18SurfaceProperties;
    dst[6] = &_gMistR18SurfaceProperties;
    dst[7] = &_gMistR18SurfaceProperties;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_r18/gMistR18SurfacePropertiesByClass", gMistR18SurfacePropertiesByClass, peDecodeArr_gMistR18SurfacePropertiesByClass);
