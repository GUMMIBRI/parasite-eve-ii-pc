/* rooms/akropolis/fire_escape/package: written from its room instance by tools/buildsteps/gen_room_inc.py. */

#include "gameplay/room.h"

static WorldCollisionFootstepSounds _gAkropolisFireEscapeSurfaceClass1FootstepSounds;
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_fire_escape/_gAkropolisFireEscapeSurfaceClass1FootstepSounds", _gAkropolisFireEscapeSurfaceClass1FootstepSounds);
static WorldCollisionFootstepSounds _gAkropolisFireEscapeSurfaceClass3FootstepSounds;
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_fire_escape/_gAkropolisFireEscapeSurfaceClass3FootstepSounds", _gAkropolisFireEscapeSurfaceClass3FootstepSounds);
static WorldCollisionFootstepSounds _gAkropolisFireEscapeDefaultFootstepSounds;
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_fire_escape/_gAkropolisFireEscapeDefaultFootstepSounds", _gAkropolisFireEscapeDefaultFootstepSounds);
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
static WorldCollisionSurfaceProperties _gAkropolisFireEscapeDefaultSurfaceProperties;
static void peDecodeArr_gAkropolisFireEscapeDefaultSurfaceProperties(void* base, const unsigned char* src, size_t n)
{
    WorldCollisionSurfaceProperties* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_WorldCollisionSurfaceProperties(&dst[k], src + k * 8);
    dst[0].footstepSounds = &_gAkropolisFireEscapeDefaultFootstepSounds;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_fire_escape/_gAkropolisFireEscapeDefaultSurfaceProperties", _gAkropolisFireEscapeDefaultSurfaceProperties, peDecodeArr_gAkropolisFireEscapeDefaultSurfaceProperties);
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
static WorldCollisionSurfaceProperties _gAkropolisFireEscapeSurfaceClass1Properties;
static void peDecodeArr_gAkropolisFireEscapeSurfaceClass1Properties(void* base, const unsigned char* src, size_t n)
{
    WorldCollisionSurfaceProperties* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_WorldCollisionSurfaceProperties(&dst[k], src + k * 8);
    dst[0].footstepSounds = &_gAkropolisFireEscapeSurfaceClass1FootstepSounds;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_fire_escape/_gAkropolisFireEscapeSurfaceClass1Properties", _gAkropolisFireEscapeSurfaceClass1Properties, peDecodeArr_gAkropolisFireEscapeSurfaceClass1Properties);
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
static WorldCollisionSurfaceProperties _gAkropolisFireEscapeSurfaceClass2Properties;
static void peDecodeArr_gAkropolisFireEscapeSurfaceClass2Properties(void* base, const unsigned char* src, size_t n)
{
    WorldCollisionSurfaceProperties* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_WorldCollisionSurfaceProperties(&dst[k], src + k * 8);
    dst[0].footstepSounds = &_gAkropolisFireEscapeDefaultFootstepSounds;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_fire_escape/_gAkropolisFireEscapeSurfaceClass2Properties", _gAkropolisFireEscapeSurfaceClass2Properties, peDecodeArr_gAkropolisFireEscapeSurfaceClass2Properties);
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
static WorldCollisionSurfaceProperties _gAkropolisFireEscapeSurfaceClass3Properties;
static void peDecodeArr_gAkropolisFireEscapeSurfaceClass3Properties(void* base, const unsigned char* src, size_t n)
{
    WorldCollisionSurfaceProperties* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_WorldCollisionSurfaceProperties(&dst[k], src + k * 8);
    dst[0].footstepSounds = &_gAkropolisFireEscapeSurfaceClass3FootstepSounds;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_fire_escape/_gAkropolisFireEscapeSurfaceClass3Properties", _gAkropolisFireEscapeSurfaceClass3Properties, peDecodeArr_gAkropolisFireEscapeSurfaceClass3Properties);
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
static WorldCollisionSurfaceProperties _gAkropolisFireEscapeSurfaceClass6Properties;
static void peDecodeArr_gAkropolisFireEscapeSurfaceClass6Properties(void* base, const unsigned char* src, size_t n)
{
    WorldCollisionSurfaceProperties* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_WorldCollisionSurfaceProperties(&dst[k], src + k * 8);
    dst[0].footstepSounds = &_gAkropolisFireEscapeDefaultFootstepSounds;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_fire_escape/_gAkropolisFireEscapeSurfaceClass6Properties", _gAkropolisFireEscapeSurfaceClass6Properties, peDecodeArr_gAkropolisFireEscapeSurfaceClass6Properties);
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
WorldCollisionSurfaceProperties* gAkropolisFireEscapeSurfacePropertiesByClass[8];
static void peDecodeArr_gAkropolisFireEscapeSurfacePropertiesByClass(void* base, const unsigned char* src, size_t n)
{
    WorldCollisionSurfaceProperties** dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SurfacePtr(&dst[k], src + k * 4);
    dst[0] = &_gAkropolisFireEscapeDefaultSurfaceProperties;
    dst[1] = &_gAkropolisFireEscapeSurfaceClass1Properties;
    dst[2] = &_gAkropolisFireEscapeSurfaceClass2Properties;
    dst[3] = &_gAkropolisFireEscapeSurfaceClass3Properties;
    dst[4] = &_gAkropolisFireEscapeDefaultSurfaceProperties;
    dst[5] = &_gAkropolisFireEscapeDefaultSurfaceProperties;
    dst[6] = &_gAkropolisFireEscapeSurfaceClass6Properties;
    dst[7] = &_gAkropolisFireEscapeDefaultSurfaceProperties;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_fire_escape/gAkropolisFireEscapeSurfacePropertiesByClass", gAkropolisFireEscapeSurfacePropertiesByClass, peDecodeArr_gAkropolisFireEscapeSurfacePropertiesByClass);
