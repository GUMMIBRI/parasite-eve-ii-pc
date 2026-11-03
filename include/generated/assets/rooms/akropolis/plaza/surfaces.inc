/* rooms/akropolis/plaza/package: written from its room instance by tools/buildsteps/gen_room_inc.py. */

#include "gameplay/room.h"

static WorldCollisionFootstepSounds _gAkropolisPlazaDefaultFootstepSounds;
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_plaza/_gAkropolisPlazaDefaultFootstepSounds", _gAkropolisPlazaDefaultFootstepSounds);
static WorldCollisionFootstepSounds _gAkropolisPlazaClass1FootstepSounds;
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_plaza/_gAkropolisPlazaClass1FootstepSounds", _gAkropolisPlazaClass1FootstepSounds);
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
static WorldCollisionSurfaceProperties _gAkropolisPlazaDefaultSurfaceProperties;
static void peDecodeArr_gAkropolisPlazaDefaultSurfaceProperties(void* base, const unsigned char* src, size_t n)
{
    WorldCollisionSurfaceProperties* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_WorldCollisionSurfaceProperties(&dst[k], src + k * 8);
    dst[0].footstepSounds = &_gAkropolisPlazaDefaultFootstepSounds;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_plaza/_gAkropolisPlazaDefaultSurfaceProperties", _gAkropolisPlazaDefaultSurfaceProperties, peDecodeArr_gAkropolisPlazaDefaultSurfaceProperties);
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
static WorldCollisionSurfaceProperties _gAkropolisPlazaClass1SurfaceProperties;
static void peDecodeArr_gAkropolisPlazaClass1SurfaceProperties(void* base, const unsigned char* src, size_t n)
{
    WorldCollisionSurfaceProperties* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_WorldCollisionSurfaceProperties(&dst[k], src + k * 8);
    dst[0].footstepSounds = &_gAkropolisPlazaClass1FootstepSounds;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_plaza/_gAkropolisPlazaClass1SurfaceProperties", _gAkropolisPlazaClass1SurfaceProperties, peDecodeArr_gAkropolisPlazaClass1SurfaceProperties);
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
WorldCollisionSurfaceProperties* gAkropolisPlazaSurfacePropertiesByClass[8];
static void peDecodeArr_gAkropolisPlazaSurfacePropertiesByClass(void* base, const unsigned char* src, size_t n)
{
    WorldCollisionSurfaceProperties** dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SurfacePtr(&dst[k], src + k * 4);
    dst[0] = &_gAkropolisPlazaDefaultSurfaceProperties;
    dst[1] = &_gAkropolisPlazaClass1SurfaceProperties;
    dst[2] = &_gAkropolisPlazaDefaultSurfaceProperties;
    dst[3] = &_gAkropolisPlazaDefaultSurfaceProperties;
    dst[4] = &_gAkropolisPlazaDefaultSurfaceProperties;
    dst[5] = &_gAkropolisPlazaDefaultSurfaceProperties;
    dst[6] = &_gAkropolisPlazaDefaultSurfaceProperties;
    dst[7] = &_gAkropolisPlazaDefaultSurfaceProperties;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_plaza/gAkropolisPlazaSurfacePropertiesByClass", gAkropolisPlazaSurfacePropertiesByClass, peDecodeArr_gAkropolisPlazaSurfacePropertiesByClass);
