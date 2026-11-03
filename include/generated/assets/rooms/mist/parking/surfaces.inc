/* rooms/mist/parking/package: written from its room instance by tools/buildsteps/gen_room_inc.py. */

#include "types.h"
#include "gameplay/room.h"

static WorldCollisionFootstepSounds _gMistParkingFootstepSounds;
#include "port/asset_bind.h"
PE_ASSET_BIND("room/mist_parking/_gMistParkingFootstepSounds", _gMistParkingFootstepSounds);
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
static WorldCollisionSurfaceProperties _gMistParkingDefaultSurfaceProperties;
static void peDecodeArr_gMistParkingDefaultSurfaceProperties(void* base, const unsigned char* src, size_t n)
{
    WorldCollisionSurfaceProperties* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_WorldCollisionSurfaceProperties(&dst[k], src + k * 8);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_parking/_gMistParkingDefaultSurfaceProperties", _gMistParkingDefaultSurfaceProperties, peDecodeArr_gMistParkingDefaultSurfaceProperties);
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
static WorldCollisionSurfaceProperties _gMistParkingSurfaceClass1Properties;
static void peDecodeArr_gMistParkingSurfaceClass1Properties(void* base, const unsigned char* src, size_t n)
{
    WorldCollisionSurfaceProperties* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_WorldCollisionSurfaceProperties(&dst[k], src + k * 8);
    dst[0].footstepSounds = &_gMistParkingFootstepSounds;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_parking/_gMistParkingSurfaceClass1Properties", _gMistParkingSurfaceClass1Properties, peDecodeArr_gMistParkingSurfaceClass1Properties);
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
static WorldCollisionSurfaceProperties _gMistParkingSurfaceClass2Properties;
static void peDecodeArr_gMistParkingSurfaceClass2Properties(void* base, const unsigned char* src, size_t n)
{
    WorldCollisionSurfaceProperties* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_WorldCollisionSurfaceProperties(&dst[k], src + k * 8);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_parking/_gMistParkingSurfaceClass2Properties", _gMistParkingSurfaceClass2Properties, peDecodeArr_gMistParkingSurfaceClass2Properties);
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
static WorldCollisionSurfaceProperties _gMistParkingSurfaceClass3Properties;
static void peDecodeArr_gMistParkingSurfaceClass3Properties(void* base, const unsigned char* src, size_t n)
{
    WorldCollisionSurfaceProperties* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_WorldCollisionSurfaceProperties(&dst[k], src + k * 8);
    dst[0].footstepSounds = &_gMistParkingFootstepSounds;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_parking/_gMistParkingSurfaceClass3Properties", _gMistParkingSurfaceClass3Properties, peDecodeArr_gMistParkingSurfaceClass3Properties);
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
WorldCollisionSurfaceProperties* gMistParkingSurfacePropertiesByClass[8];
static void peDecodeArr_gMistParkingSurfacePropertiesByClass(void* base, const unsigned char* src, size_t n)
{
    WorldCollisionSurfaceProperties** dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SurfacePtr(&dst[k], src + k * 4);
    dst[0] = &_gMistParkingDefaultSurfaceProperties;
    dst[1] = &_gMistParkingSurfaceClass1Properties;
    dst[2] = &_gMistParkingSurfaceClass2Properties;
    dst[3] = &_gMistParkingSurfaceClass3Properties;
    dst[4] = &_gMistParkingDefaultSurfaceProperties;
    dst[5] = &_gMistParkingDefaultSurfaceProperties;
    dst[6] = &_gMistParkingDefaultSurfaceProperties;
    dst[7] = &_gMistParkingDefaultSurfaceProperties;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_parking/gMistParkingSurfacePropertiesByClass", gMistParkingSurfacePropertiesByClass, peDecodeArr_gMistParkingSurfacePropertiesByClass);
