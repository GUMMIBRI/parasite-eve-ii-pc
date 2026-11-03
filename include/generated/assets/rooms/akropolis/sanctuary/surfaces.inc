/* rooms/akropolis/sanctuary/package: written from its room instance by tools/buildsteps/gen_room_inc.py. */

#include "types.h"
#include "gameplay/room.h"

static WorldCollisionFootstepSounds _gAkropolisSanctuarySurfaceClass1FootstepSounds;
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_sanctuary/_gAkropolisSanctuarySurfaceClass1FootstepSounds", _gAkropolisSanctuarySurfaceClass1FootstepSounds);
static WorldCollisionFootstepSounds _gAkropolisSanctuarySurfaceClass2FootstepSounds;
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_sanctuary/_gAkropolisSanctuarySurfaceClass2FootstepSounds", _gAkropolisSanctuarySurfaceClass2FootstepSounds);
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
static WorldCollisionSurfaceProperties _gAkropolisSanctuaryDefaultSurfaceProperties;
static void peDecodeArr_gAkropolisSanctuaryDefaultSurfaceProperties(void* base, const unsigned char* src, size_t n)
{
    WorldCollisionSurfaceProperties* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_WorldCollisionSurfaceProperties(&dst[k], src + k * 8);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_sanctuary/_gAkropolisSanctuaryDefaultSurfaceProperties", _gAkropolisSanctuaryDefaultSurfaceProperties, peDecodeArr_gAkropolisSanctuaryDefaultSurfaceProperties);
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
static WorldCollisionSurfaceProperties _gAkropolisSanctuarySurfaceClass1Properties;
static void peDecodeArr_gAkropolisSanctuarySurfaceClass1Properties(void* base, const unsigned char* src, size_t n)
{
    WorldCollisionSurfaceProperties* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_WorldCollisionSurfaceProperties(&dst[k], src + k * 8);
    dst[0].footstepSounds = &_gAkropolisSanctuarySurfaceClass1FootstepSounds;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_sanctuary/_gAkropolisSanctuarySurfaceClass1Properties", _gAkropolisSanctuarySurfaceClass1Properties, peDecodeArr_gAkropolisSanctuarySurfaceClass1Properties);
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
static WorldCollisionSurfaceProperties _gAkropolisSanctuarySurfaceClass2Properties;
static void peDecodeArr_gAkropolisSanctuarySurfaceClass2Properties(void* base, const unsigned char* src, size_t n)
{
    WorldCollisionSurfaceProperties* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_WorldCollisionSurfaceProperties(&dst[k], src + k * 8);
    dst[0].footstepSounds = &_gAkropolisSanctuarySurfaceClass2FootstepSounds;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_sanctuary/_gAkropolisSanctuarySurfaceClass2Properties", _gAkropolisSanctuarySurfaceClass2Properties, peDecodeArr_gAkropolisSanctuarySurfaceClass2Properties);
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
WorldCollisionSurfaceProperties* gAkropolisSanctuarySurfacePropertiesByClass[8];
static void peDecodeArr_gAkropolisSanctuarySurfacePropertiesByClass(void* base, const unsigned char* src, size_t n)
{
    WorldCollisionSurfaceProperties** dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SurfacePtr(&dst[k], src + k * 4);
    dst[0] = &_gAkropolisSanctuaryDefaultSurfaceProperties;
    dst[1] = &_gAkropolisSanctuarySurfaceClass1Properties;
    dst[2] = &_gAkropolisSanctuarySurfaceClass2Properties;
    dst[3] = &_gAkropolisSanctuaryDefaultSurfaceProperties;
    dst[4] = &_gAkropolisSanctuaryDefaultSurfaceProperties;
    dst[5] = &_gAkropolisSanctuaryDefaultSurfaceProperties;
    dst[6] = &_gAkropolisSanctuaryDefaultSurfaceProperties;
    dst[7] = &_gAkropolisSanctuaryDefaultSurfaceProperties;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_sanctuary/gAkropolisSanctuarySurfacePropertiesByClass", gAkropolisSanctuarySurfacePropertiesByClass, peDecodeArr_gAkropolisSanctuarySurfacePropertiesByClass);
