/* rooms/akropolis/promenade/package: written from its room instance by tools/buildsteps/gen_room_inc.py. */

#include "types.h"
#include "gameplay/room.h"

static WorldCollisionFootstepSounds _gAkropolisPromenadeSurfaceClass1FootstepSounds;
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_promenade/_gAkropolisPromenadeSurfaceClass1FootstepSounds", _gAkropolisPromenadeSurfaceClass1FootstepSounds);
static WorldCollisionFootstepSounds _gAkropolisPromenadeSurfaceClass2FootstepSounds;
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_promenade/_gAkropolisPromenadeSurfaceClass2FootstepSounds", _gAkropolisPromenadeSurfaceClass2FootstepSounds);
static WorldCollisionFootstepSounds _gAkropolisPromenadeSurfaceClass3FootstepSounds;
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_promenade/_gAkropolisPromenadeSurfaceClass3FootstepSounds", _gAkropolisPromenadeSurfaceClass3FootstepSounds);
static WorldCollisionFootstepSounds _gAkropolisPromenadeSurfaceClass4FootstepSounds;
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_promenade/_gAkropolisPromenadeSurfaceClass4FootstepSounds", _gAkropolisPromenadeSurfaceClass4FootstepSounds);
static WorldCollisionFootstepSounds _gAkropolisPromenadeSurfaceClass7FootstepSounds;
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_promenade/_gAkropolisPromenadeSurfaceClass7FootstepSounds", _gAkropolisPromenadeSurfaceClass7FootstepSounds);
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
static WorldCollisionSurfaceProperties _gAkropolisPromenadeDefaultSurfaceProperties;
static void peDecodeArr_gAkropolisPromenadeDefaultSurfaceProperties(void* base, const unsigned char* src, size_t n)
{
    WorldCollisionSurfaceProperties* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_WorldCollisionSurfaceProperties(&dst[k], src + k * 8);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_promenade/_gAkropolisPromenadeDefaultSurfaceProperties", _gAkropolisPromenadeDefaultSurfaceProperties, peDecodeArr_gAkropolisPromenadeDefaultSurfaceProperties);
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
static WorldCollisionSurfaceProperties _gAkropolisPromenadeSurfaceClass1Properties;
static void peDecodeArr_gAkropolisPromenadeSurfaceClass1Properties(void* base, const unsigned char* src, size_t n)
{
    WorldCollisionSurfaceProperties* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_WorldCollisionSurfaceProperties(&dst[k], src + k * 8);
    dst[0].footstepSounds = &_gAkropolisPromenadeSurfaceClass1FootstepSounds;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_promenade/_gAkropolisPromenadeSurfaceClass1Properties", _gAkropolisPromenadeSurfaceClass1Properties, peDecodeArr_gAkropolisPromenadeSurfaceClass1Properties);
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
static WorldCollisionSurfaceProperties _gAkropolisPromenadeSurfaceClass2Properties;
static void peDecodeArr_gAkropolisPromenadeSurfaceClass2Properties(void* base, const unsigned char* src, size_t n)
{
    WorldCollisionSurfaceProperties* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_WorldCollisionSurfaceProperties(&dst[k], src + k * 8);
    dst[0].footstepSounds = &_gAkropolisPromenadeSurfaceClass2FootstepSounds;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_promenade/_gAkropolisPromenadeSurfaceClass2Properties", _gAkropolisPromenadeSurfaceClass2Properties, peDecodeArr_gAkropolisPromenadeSurfaceClass2Properties);
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
static WorldCollisionSurfaceProperties _gAkropolisPromenadeSurfaceClass3Properties;
static void peDecodeArr_gAkropolisPromenadeSurfaceClass3Properties(void* base, const unsigned char* src, size_t n)
{
    WorldCollisionSurfaceProperties* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_WorldCollisionSurfaceProperties(&dst[k], src + k * 8);
    dst[0].footstepSounds = &_gAkropolisPromenadeSurfaceClass3FootstepSounds;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_promenade/_gAkropolisPromenadeSurfaceClass3Properties", _gAkropolisPromenadeSurfaceClass3Properties, peDecodeArr_gAkropolisPromenadeSurfaceClass3Properties);
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
static WorldCollisionSurfaceProperties _gAkropolisPromenadeSurfaceClass4Properties;
static void peDecodeArr_gAkropolisPromenadeSurfaceClass4Properties(void* base, const unsigned char* src, size_t n)
{
    WorldCollisionSurfaceProperties* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_WorldCollisionSurfaceProperties(&dst[k], src + k * 8);
    dst[0].footstepSounds = &_gAkropolisPromenadeSurfaceClass4FootstepSounds;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_promenade/_gAkropolisPromenadeSurfaceClass4Properties", _gAkropolisPromenadeSurfaceClass4Properties, peDecodeArr_gAkropolisPromenadeSurfaceClass4Properties);
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
static WorldCollisionSurfaceProperties _gAkropolisPromenadeSurfaceClass7Properties;
static void peDecodeArr_gAkropolisPromenadeSurfaceClass7Properties(void* base, const unsigned char* src, size_t n)
{
    WorldCollisionSurfaceProperties* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_WorldCollisionSurfaceProperties(&dst[k], src + k * 8);
    dst[0].footstepSounds = &_gAkropolisPromenadeSurfaceClass7FootstepSounds;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_promenade/_gAkropolisPromenadeSurfaceClass7Properties", _gAkropolisPromenadeSurfaceClass7Properties, peDecodeArr_gAkropolisPromenadeSurfaceClass7Properties);
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
WorldCollisionSurfaceProperties* gAkropolisPromenadeSurfacePropertiesByClass[8];
static void peDecodeArr_gAkropolisPromenadeSurfacePropertiesByClass(void* base, const unsigned char* src, size_t n)
{
    WorldCollisionSurfaceProperties** dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SurfacePtr(&dst[k], src + k * 4);
    dst[0] = &_gAkropolisPromenadeDefaultSurfaceProperties;
    dst[1] = &_gAkropolisPromenadeSurfaceClass1Properties;
    dst[2] = &_gAkropolisPromenadeSurfaceClass2Properties;
    dst[3] = &_gAkropolisPromenadeSurfaceClass3Properties;
    dst[4] = &_gAkropolisPromenadeSurfaceClass4Properties;
    dst[5] = &_gAkropolisPromenadeDefaultSurfaceProperties;
    dst[6] = &_gAkropolisPromenadeDefaultSurfaceProperties;
    dst[7] = &_gAkropolisPromenadeSurfaceClass7Properties;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_promenade/gAkropolisPromenadeSurfacePropertiesByClass", gAkropolisPromenadeSurfacePropertiesByClass, peDecodeArr_gAkropolisPromenadeSurfacePropertiesByClass);
