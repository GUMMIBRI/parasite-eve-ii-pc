/* rooms/akropolis/west_elevator_hall/package: written from its room instance by tools/buildsteps/gen_room_inc.py. */

#include "gameplay/room.h"

static WorldCollisionFootstepSounds _gAkropolisWestElevatorHallFootstepSounds;
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_west_elevator_hall/_gAkropolisWestElevatorHallFootstepSounds", _gAkropolisWestElevatorHallFootstepSounds);
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
static WorldCollisionSurfaceProperties _gAkropolisWestElevatorHallSurfaceProperties;
static void peDecodeArr_gAkropolisWestElevatorHallSurfaceProperties(void* base, const unsigned char* src, size_t n)
{
    WorldCollisionSurfaceProperties* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_WorldCollisionSurfaceProperties(&dst[k], src + k * 8);
    dst[0].footstepSounds = &_gAkropolisWestElevatorHallFootstepSounds;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_west_elevator_hall/_gAkropolisWestElevatorHallSurfaceProperties", _gAkropolisWestElevatorHallSurfaceProperties, peDecodeArr_gAkropolisWestElevatorHallSurfaceProperties);
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
WorldCollisionSurfaceProperties* gAkropolisWestElevatorHallSurfacePropertiesByClass[8];
static void peDecodeArr_gAkropolisWestElevatorHallSurfacePropertiesByClass(void* base, const unsigned char* src, size_t n)
{
    WorldCollisionSurfaceProperties** dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SurfacePtr(&dst[k], src + k * 4);
    dst[0] = &_gAkropolisWestElevatorHallSurfaceProperties;
    dst[1] = &_gAkropolisWestElevatorHallSurfaceProperties;
    dst[2] = &_gAkropolisWestElevatorHallSurfaceProperties;
    dst[3] = &_gAkropolisWestElevatorHallSurfaceProperties;
    dst[4] = &_gAkropolisWestElevatorHallSurfaceProperties;
    dst[5] = &_gAkropolisWestElevatorHallSurfaceProperties;
    dst[6] = &_gAkropolisWestElevatorHallSurfaceProperties;
    dst[7] = &_gAkropolisWestElevatorHallSurfaceProperties;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_west_elevator_hall/gAkropolisWestElevatorHallSurfacePropertiesByClass", gAkropolisWestElevatorHallSurfacePropertiesByClass, peDecodeArr_gAkropolisWestElevatorHallSurfacePropertiesByClass);
