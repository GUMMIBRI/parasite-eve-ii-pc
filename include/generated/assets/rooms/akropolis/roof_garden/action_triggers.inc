/* rooms/akropolis/roof_garden/package: written from its room instance by tools/buildsteps/gen_room_inc.py. */

#include "types.h"
#include "gameplay/collision.h"

#ifndef PE_DECODE_WorldCollisionTrigger
#define PE_DECODE_WorldCollisionTrigger
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
static void peDecode_WorldCollisionTrigger(WorldCollisionTrigger* dst, const unsigned char* src)
{
    /* next: pointer, set by the array's fixups */
    /* prevLink: pointer, set by the array's fixups */
    /* coord: pointer, set by the array's fixups */
    _Static_assert(sizeof(dst->origin) == 8, "origin");
    memcpy(&dst->origin, src + 12, 8);
    _Static_assert(sizeof(dst->vertices) == 32, "vertices");
    memcpy(&dst->vertices, src + 20, 32);
    _Static_assert(sizeof(dst->normal) == 8, "normal");
    memcpy(&dst->normal, src + 52, 8);
    _Static_assert(sizeof(dst->facingNormal) == 8, "facingNormal");
    memcpy(&dst->facingNormal, src + 60, 8);
    { uint16_t v; memcpy(&v, src + 68, 2); dst->radius = v; }
    { uint16_t v; memcpy(&v, src + 70, 2); dst->control = v; }
    { uint8_t v; memcpy(&v, src + 72, 1); dst->parameter0 = v; }
    { uint8_t v; memcpy(&v, src + 73, 1); dst->parameter1 = v; }
    { uint8_t v; memcpy(&v, src + 74, 1); dst->flags = v; }
    { int8_t v; memcpy(&v, src + 75, 1); dst->hit = v; }
}

#endif
static WorldCollisionTrigger _gAkropolisRoofGardenActionTriggers[7];
static void peDecodeArr_gAkropolisRoofGardenActionTriggers(void* base, const unsigned char* src, size_t n)
{
    WorldCollisionTrigger* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_WorldCollisionTrigger(&dst[k], src + k * 76);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_roof_garden/_gAkropolisRoofGardenActionTriggers", _gAkropolisRoofGardenActionTriggers, peDecodeArr_gAkropolisRoofGardenActionTriggers);
