/* rooms/mist/shooting_gallery/package: written from its room instance by tools/buildsteps/gen_room_inc.py. */

#include "types.h"
#include "gameplay/room.h"

static WorldCollisionFootstepSounds _gMistShootingGallerySurface1FootstepSounds;
#include "port/asset_bind.h"
PE_ASSET_BIND("room/mist_shooting_gallery/_gMistShootingGallerySurface1FootstepSounds", _gMistShootingGallerySurface1FootstepSounds);
static WorldCollisionFootstepSounds _gMistShootingGallerySurface2FootstepSounds;
#include "port/asset_bind.h"
PE_ASSET_BIND("room/mist_shooting_gallery/_gMistShootingGallerySurface2FootstepSounds", _gMistShootingGallerySurface2FootstepSounds);
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
static WorldCollisionSurfaceProperties _gMistShootingGallerySilentSurfaceProperties;
static void peDecodeArr_gMistShootingGallerySilentSurfaceProperties(void* base, const unsigned char* src, size_t n)
{
    WorldCollisionSurfaceProperties* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_WorldCollisionSurfaceProperties(&dst[k], src + k * 8);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_shooting_gallery/_gMistShootingGallerySilentSurfaceProperties", _gMistShootingGallerySilentSurfaceProperties, peDecodeArr_gMistShootingGallerySilentSurfaceProperties);
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
static WorldCollisionSurfaceProperties _gMistShootingGallerySurface1Properties;
static void peDecodeArr_gMistShootingGallerySurface1Properties(void* base, const unsigned char* src, size_t n)
{
    WorldCollisionSurfaceProperties* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_WorldCollisionSurfaceProperties(&dst[k], src + k * 8);
    dst[0].footstepSounds = &_gMistShootingGallerySurface1FootstepSounds;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_shooting_gallery/_gMistShootingGallerySurface1Properties", _gMistShootingGallerySurface1Properties, peDecodeArr_gMistShootingGallerySurface1Properties);
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
static WorldCollisionSurfaceProperties _gMistShootingGallerySurface2Properties;
static void peDecodeArr_gMistShootingGallerySurface2Properties(void* base, const unsigned char* src, size_t n)
{
    WorldCollisionSurfaceProperties* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_WorldCollisionSurfaceProperties(&dst[k], src + k * 8);
    dst[0].footstepSounds = &_gMistShootingGallerySurface2FootstepSounds;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_shooting_gallery/_gMistShootingGallerySurface2Properties", _gMistShootingGallerySurface2Properties, peDecodeArr_gMistShootingGallerySurface2Properties);
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
WorldCollisionSurfaceProperties* gMistShootingGallerySurfacePropertiesByClass[8];
static void peDecodeArr_gMistShootingGallerySurfacePropertiesByClass(void* base, const unsigned char* src, size_t n)
{
    WorldCollisionSurfaceProperties** dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SurfacePtr(&dst[k], src + k * 4);
    dst[0] = &_gMistShootingGallerySilentSurfaceProperties;
    dst[1] = &_gMistShootingGallerySurface1Properties;
    dst[2] = &_gMistShootingGallerySurface2Properties;
    dst[3] = &_gMistShootingGallerySilentSurfaceProperties;
    dst[4] = &_gMistShootingGallerySilentSurfaceProperties;
    dst[5] = &_gMistShootingGallerySilentSurfaceProperties;
    dst[6] = &_gMistShootingGallerySilentSurfaceProperties;
    dst[7] = &_gMistShootingGallerySilentSurfaceProperties;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_shooting_gallery/gMistShootingGallerySurfacePropertiesByClass", gMistShootingGallerySurfacePropertiesByClass, peDecodeArr_gMistShootingGallerySurfacePropertiesByClass);
