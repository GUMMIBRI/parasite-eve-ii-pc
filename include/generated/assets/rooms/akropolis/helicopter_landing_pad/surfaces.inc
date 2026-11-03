/* rooms/akropolis/helicopter_landing_pad/package: written from its room instance by tools/buildsteps/gen_room_inc.py. */

#include "types.h"
#include "gameplay/room.h"

static WorldCollisionFootstepSounds _gAkropolisHelicopterLandingPadFloorFootstepSounds;
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_helicopter_landing_pad/_gAkropolisHelicopterLandingPadFloorFootstepSounds", _gAkropolisHelicopterLandingPadFloorFootstepSounds);
static WorldCollisionFootstepSounds _gAkropolisHelicopterLandingPadStairFootstepSounds;
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_helicopter_landing_pad/_gAkropolisHelicopterLandingPadStairFootstepSounds", _gAkropolisHelicopterLandingPadStairFootstepSounds);
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
static WorldCollisionSurfaceProperties _gAkropolisHelicopterLandingPadSilentSolidSurface;
static void peDecodeArr_gAkropolisHelicopterLandingPadSilentSolidSurface(void* base, const unsigned char* src, size_t n)
{
    WorldCollisionSurfaceProperties* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_WorldCollisionSurfaceProperties(&dst[k], src + k * 8);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_helicopter_landing_pad/_gAkropolisHelicopterLandingPadSilentSolidSurface", _gAkropolisHelicopterLandingPadSilentSolidSurface, peDecodeArr_gAkropolisHelicopterLandingPadSilentSolidSurface);
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
static WorldCollisionSurfaceProperties _gAkropolisHelicopterLandingPadStairSurface;
static void peDecodeArr_gAkropolisHelicopterLandingPadStairSurface(void* base, const unsigned char* src, size_t n)
{
    WorldCollisionSurfaceProperties* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_WorldCollisionSurfaceProperties(&dst[k], src + k * 8);
    dst[0].footstepSounds = &_gAkropolisHelicopterLandingPadStairFootstepSounds;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_helicopter_landing_pad/_gAkropolisHelicopterLandingPadStairSurface", _gAkropolisHelicopterLandingPadStairSurface, peDecodeArr_gAkropolisHelicopterLandingPadStairSurface);
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
static WorldCollisionSurfaceProperties _gAkropolisHelicopterLandingPadFloorSurface;
static void peDecodeArr_gAkropolisHelicopterLandingPadFloorSurface(void* base, const unsigned char* src, size_t n)
{
    WorldCollisionSurfaceProperties* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_WorldCollisionSurfaceProperties(&dst[k], src + k * 8);
    dst[0].footstepSounds = &_gAkropolisHelicopterLandingPadFloorFootstepSounds;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_helicopter_landing_pad/_gAkropolisHelicopterLandingPadFloorSurface", _gAkropolisHelicopterLandingPadFloorSurface, peDecodeArr_gAkropolisHelicopterLandingPadFloorSurface);
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
static WorldCollisionSurfaceProperties _gAkropolisHelicopterLandingPadPerimeterSurface;
static void peDecodeArr_gAkropolisHelicopterLandingPadPerimeterSurface(void* base, const unsigned char* src, size_t n)
{
    WorldCollisionSurfaceProperties* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_WorldCollisionSurfaceProperties(&dst[k], src + k * 8);
    dst[0].footstepSounds = &_gAkropolisHelicopterLandingPadFloorFootstepSounds;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_helicopter_landing_pad/_gAkropolisHelicopterLandingPadPerimeterSurface", _gAkropolisHelicopterLandingPadPerimeterSurface, peDecodeArr_gAkropolisHelicopterLandingPadPerimeterSurface);
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
static WorldCollisionSurfaceProperties _gAkropolisHelicopterLandingPadSurface5Properties;
static void peDecodeArr_gAkropolisHelicopterLandingPadSurface5Properties(void* base, const unsigned char* src, size_t n)
{
    WorldCollisionSurfaceProperties* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_WorldCollisionSurfaceProperties(&dst[k], src + k * 8);
    dst[0].footstepSounds = &_gAkropolisHelicopterLandingPadFloorFootstepSounds;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_helicopter_landing_pad/_gAkropolisHelicopterLandingPadSurface5Properties", _gAkropolisHelicopterLandingPadSurface5Properties, peDecodeArr_gAkropolisHelicopterLandingPadSurface5Properties);
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
static WorldCollisionSurfaceProperties _gAkropolisHelicopterLandingPadOuterBoundarySurface;
static void peDecodeArr_gAkropolisHelicopterLandingPadOuterBoundarySurface(void* base, const unsigned char* src, size_t n)
{
    WorldCollisionSurfaceProperties* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_WorldCollisionSurfaceProperties(&dst[k], src + k * 8);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_helicopter_landing_pad/_gAkropolisHelicopterLandingPadOuterBoundarySurface", _gAkropolisHelicopterLandingPadOuterBoundarySurface, peDecodeArr_gAkropolisHelicopterLandingPadOuterBoundarySurface);
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
WorldCollisionSurfaceProperties* gAkropolisHelicopterLandingPadSurfacePropertiesByClass[8];
static void peDecodeArr_gAkropolisHelicopterLandingPadSurfacePropertiesByClass(void* base, const unsigned char* src, size_t n)
{
    WorldCollisionSurfaceProperties** dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SurfacePtr(&dst[k], src + k * 4);
    dst[0] = &_gAkropolisHelicopterLandingPadSilentSolidSurface;
    dst[1] = &_gAkropolisHelicopterLandingPadSilentSolidSurface;
    dst[2] = &_gAkropolisHelicopterLandingPadStairSurface;
    dst[3] = &_gAkropolisHelicopterLandingPadFloorSurface;
    dst[4] = &_gAkropolisHelicopterLandingPadPerimeterSurface;
    dst[5] = &_gAkropolisHelicopterLandingPadSurface5Properties;
    dst[6] = &_gAkropolisHelicopterLandingPadOuterBoundarySurface;
    dst[7] = &_gAkropolisHelicopterLandingPadSilentSolidSurface;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_helicopter_landing_pad/gAkropolisHelicopterLandingPadSurfacePropertiesByClass", gAkropolisHelicopterLandingPadSurfacePropertiesByClass, peDecodeArr_gAkropolisHelicopterLandingPadSurfacePropertiesByClass);
