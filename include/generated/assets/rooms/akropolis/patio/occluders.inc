/* rooms/akropolis/patio/package: written from its room instance by tools/buildsteps/gen_room_inc.py. */

#include "types.h"
#include "gameplay/collision.h"

#ifndef PE_DECODE_WorldCollisionOccluder
#define PE_DECODE_WorldCollisionOccluder
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
static void peDecode_WorldCollisionOccluder(WorldCollisionOccluder* dst, const unsigned char* src)
{
    /* next: pointer, set by the array's fixups */
    /* prevLink: pointer, set by the array's fixups */
    _Static_assert(sizeof(dst->origin) == 8, "origin");
    memcpy(&dst->origin, src + 8, 8);
    _Static_assert(sizeof(dst->vertices) == 32, "vertices");
    memcpy(&dst->vertices, src + 16, 32);
    _Static_assert(sizeof(dst->normal) == 8, "normal");
    memcpy(&dst->normal, src + 48, 8);
    { uint16_t v; memcpy(&v, src + 56, 2); dst->radius = v; }
    { uint8_t v; memcpy(&v, src + 58, 1); dst->flags = v; }
    { int8_t v; memcpy(&v, src + 59, 1); dst->unknown_3B = v; }
}

#endif
static WorldCollisionOccluder _gAkropolisPatioOccluders[2];
static void peDecodeArr_gAkropolisPatioOccluders(void* base, const unsigned char* src, size_t n)
{
    WorldCollisionOccluder* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_WorldCollisionOccluder(&dst[k], src + k * 60);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_patio/_gAkropolisPatioOccluders", _gAkropolisPatioOccluders, peDecodeArr_gAkropolisPatioOccluders);
