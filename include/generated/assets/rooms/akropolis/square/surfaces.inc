/* rooms/akropolis/square/package: written from its room instance by tools/buildsteps/gen_room_inc.py. */

#include "types.h"
#include "gameplay/room.h"

static WorldCollisionFootstepSounds _gAkropolisSquareFootstepSounds;
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_square/_gAkropolisSquareFootstepSounds", _gAkropolisSquareFootstepSounds);
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
static WorldCollisionSurfaceProperties _gAkropolisSquareDefaultSurfaceProperties;
static void peDecodeArr_gAkropolisSquareDefaultSurfaceProperties(void* base, const unsigned char* src, size_t n)
{
    WorldCollisionSurfaceProperties* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_WorldCollisionSurfaceProperties(&dst[k], src + k * 8);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_square/_gAkropolisSquareDefaultSurfaceProperties", _gAkropolisSquareDefaultSurfaceProperties, peDecodeArr_gAkropolisSquareDefaultSurfaceProperties);
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
static WorldCollisionSurfaceProperties _gAkropolisSquareClass4SurfaceProperties;
static void peDecodeArr_gAkropolisSquareClass4SurfaceProperties(void* base, const unsigned char* src, size_t n)
{
    WorldCollisionSurfaceProperties* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_WorldCollisionSurfaceProperties(&dst[k], src + k * 8);
    dst[0].footstepSounds = &_gAkropolisSquareFootstepSounds;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_square/_gAkropolisSquareClass4SurfaceProperties", _gAkropolisSquareClass4SurfaceProperties, peDecodeArr_gAkropolisSquareClass4SurfaceProperties);
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
WorldCollisionSurfaceProperties* gAkropolisSquareSurfacePropertiesByClass[8];
static void peDecodeArr_gAkropolisSquareSurfacePropertiesByClass(void* base, const unsigned char* src, size_t n)
{
    WorldCollisionSurfaceProperties** dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SurfacePtr(&dst[k], src + k * 4);
    dst[0] = &_gAkropolisSquareDefaultSurfaceProperties;
    dst[1] = &_gAkropolisSquareDefaultSurfaceProperties;
    dst[2] = &_gAkropolisSquareDefaultSurfaceProperties;
    dst[3] = &_gAkropolisSquareDefaultSurfaceProperties;
    dst[4] = &_gAkropolisSquareClass4SurfaceProperties;
    dst[5] = &_gAkropolisSquareDefaultSurfaceProperties;
    dst[6] = &_gAkropolisSquareDefaultSurfaceProperties;
    dst[7] = &_gAkropolisSquareDefaultSurfaceProperties;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_square/gAkropolisSquareSurfacePropertiesByClass", gAkropolisSquareSurfacePropertiesByClass, peDecodeArr_gAkropolisSquareSurfacePropertiesByClass);
