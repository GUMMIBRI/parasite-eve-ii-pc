/* rooms/akropolis/cafeteria/package: written from its room instance by tools/buildsteps/gen_room_inc.py. */

#include "types.h"
#include "gameplay/room.h"

static WorldCollisionFootstepSounds _gAkropolisCafeteriaSurface1FootstepSounds;
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_cafeteria/_gAkropolisCafeteriaSurface1FootstepSounds", _gAkropolisCafeteriaSurface1FootstepSounds);
static WorldCollisionFootstepSounds _gAkropolisCafeteriaSurface2FootstepSounds;
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_cafeteria/_gAkropolisCafeteriaSurface2FootstepSounds", _gAkropolisCafeteriaSurface2FootstepSounds);
static WorldCollisionFootstepSounds _gAkropolisCafeteriaSurfaces3And4FootstepSounds;
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_cafeteria/_gAkropolisCafeteriaSurfaces3And4FootstepSounds", _gAkropolisCafeteriaSurfaces3And4FootstepSounds);
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
static WorldCollisionSurfaceProperties _gAkropolisCafeteriaSilentSurfaceProperties;
static void peDecodeArr_gAkropolisCafeteriaSilentSurfaceProperties(void* base, const unsigned char* src, size_t n)
{
    WorldCollisionSurfaceProperties* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_WorldCollisionSurfaceProperties(&dst[k], src + k * 8);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_cafeteria/_gAkropolisCafeteriaSilentSurfaceProperties", _gAkropolisCafeteriaSilentSurfaceProperties, peDecodeArr_gAkropolisCafeteriaSilentSurfaceProperties);
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
static WorldCollisionSurfaceProperties _gAkropolisCafeteriaSurface1Properties;
static void peDecodeArr_gAkropolisCafeteriaSurface1Properties(void* base, const unsigned char* src, size_t n)
{
    WorldCollisionSurfaceProperties* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_WorldCollisionSurfaceProperties(&dst[k], src + k * 8);
    dst[0].footstepSounds = &_gAkropolisCafeteriaSurface1FootstepSounds;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_cafeteria/_gAkropolisCafeteriaSurface1Properties", _gAkropolisCafeteriaSurface1Properties, peDecodeArr_gAkropolisCafeteriaSurface1Properties);
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
static WorldCollisionSurfaceProperties _gAkropolisCafeteriaSurface2Properties;
static void peDecodeArr_gAkropolisCafeteriaSurface2Properties(void* base, const unsigned char* src, size_t n)
{
    WorldCollisionSurfaceProperties* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_WorldCollisionSurfaceProperties(&dst[k], src + k * 8);
    dst[0].footstepSounds = &_gAkropolisCafeteriaSurface2FootstepSounds;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_cafeteria/_gAkropolisCafeteriaSurface2Properties", _gAkropolisCafeteriaSurface2Properties, peDecodeArr_gAkropolisCafeteriaSurface2Properties);
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
static WorldCollisionSurfaceProperties _gAkropolisCafeteriaSurface3Properties;
static void peDecodeArr_gAkropolisCafeteriaSurface3Properties(void* base, const unsigned char* src, size_t n)
{
    WorldCollisionSurfaceProperties* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_WorldCollisionSurfaceProperties(&dst[k], src + k * 8);
    dst[0].footstepSounds = &_gAkropolisCafeteriaSurfaces3And4FootstepSounds;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_cafeteria/_gAkropolisCafeteriaSurface3Properties", _gAkropolisCafeteriaSurface3Properties, peDecodeArr_gAkropolisCafeteriaSurface3Properties);
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
static WorldCollisionSurfaceProperties _gAkropolisCafeteriaSurface4Properties;
static void peDecodeArr_gAkropolisCafeteriaSurface4Properties(void* base, const unsigned char* src, size_t n)
{
    WorldCollisionSurfaceProperties* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_WorldCollisionSurfaceProperties(&dst[k], src + k * 8);
    dst[0].footstepSounds = &_gAkropolisCafeteriaSurfaces3And4FootstepSounds;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_cafeteria/_gAkropolisCafeteriaSurface4Properties", _gAkropolisCafeteriaSurface4Properties, peDecodeArr_gAkropolisCafeteriaSurface4Properties);
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
WorldCollisionSurfaceProperties* gAkropolisCafeteriaSurfacePropertiesByClass[8];
static void peDecodeArr_gAkropolisCafeteriaSurfacePropertiesByClass(void* base, const unsigned char* src, size_t n)
{
    WorldCollisionSurfaceProperties** dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SurfacePtr(&dst[k], src + k * 4);
    dst[0] = &_gAkropolisCafeteriaSilentSurfaceProperties;
    dst[1] = &_gAkropolisCafeteriaSurface1Properties;
    dst[2] = &_gAkropolisCafeteriaSurface2Properties;
    dst[3] = &_gAkropolisCafeteriaSurface3Properties;
    dst[4] = &_gAkropolisCafeteriaSurface4Properties;
    dst[5] = &_gAkropolisCafeteriaSilentSurfaceProperties;
    dst[6] = &_gAkropolisCafeteriaSilentSurfaceProperties;
    dst[7] = &_gAkropolisCafeteriaSilentSurfaceProperties;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_cafeteria/gAkropolisCafeteriaSurfacePropertiesByClass", gAkropolisCafeteriaSurfacePropertiesByClass, peDecodeArr_gAkropolisCafeteriaSurfacePropertiesByClass);
