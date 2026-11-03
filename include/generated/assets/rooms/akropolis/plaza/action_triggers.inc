/* rooms/akropolis/plaza/package: written from its room instance by tools/buildsteps/gen_room_inc.py. */

#include "types.h"
#include "gameplay/collision.h"

#ifdef __psyz
static struct _peNativeTriggerSpan_gAkropolisPlazaHelicopterWreckTrigger _peNativeTriggerSpan_gAkropolisPlazaHelicopterWreckTrigger = {
    .part0 = { { .next = NULL, .prevLink = NULL, .coord = NULL, .origin = { 5744, -112, 8227, 0 }, .vertices = { { 2736, 0, 3200, 0 }, { -3471, 0, -2304, 0 }, { 3471, 0, 2305, 0 }, { -2736, 0, -3199, 0 } }, .normal = { 0, 4113, 0, 0 }, .facingNormal = { 2106, 0, -3513, 0 }, .radius = 4190, .control = 32772, .parameter0 = 0, .parameter1 = 119, .flags = 3, .hit = 0 } },
    .part1 = { .next = NULL, .prevLink = NULL, .coord = NULL, .origin = { 17206, -32, 3038, 0 }, .vertices = { { 1967, 0, 3691, 0 }, { -3037, 0, -2925, 0 }, { 3036, 0, 2925, 0 }, { -1968, 0, -3691, 0 } }, .normal = { 0, 4098, 0, 0 }, .facingNormal = { 2106, 0, -3513, 0 }, .radius = 4190, .control = 32772, .parameter0 = 1, .parameter1 = 0, .flags = 3, .hit = 0 },
    .part2 = { { .next = NULL, .prevLink = NULL, .coord = NULL, .origin = { 928, -16, 13168, 0 }, .vertices = { { 2575, 0, 3297, 0 }, { -3632, 0, -2207, 0 }, { 3632, 0, 2208, 0 }, { -2575, 0, -3296, 0 } }, .normal = { 0, 4107, 0, 0 }, .facingNormal = { 2106, 0, -3513, 0 }, .radius = 4222, .control = 32772, .parameter0 = 2, .parameter1 = 0, .flags = 3, .hit = 0 }, { .next = NULL, .prevLink = NULL, .coord = NULL, .origin = { 13615, 0, 5313, 0 }, .vertices = { { 573, 0, 1873, 0 }, { -1312, 0, -558, 0 }, { 1601, 0, 143, 0 }, { -860, 0, -1457, 0 } }, .normal = { 0, 4106, 0, 0 }, .facingNormal = { 2910, 0, -2886, 0 }, .radius = 1958, .control = 4, .parameter0 = 3, .parameter1 = 0, .flags = 2, .hit = 0 }, { .next = NULL, .prevLink = NULL, .coord = NULL, .origin = { 19519, -32, 574, 0 }, .vertices = { { 1781, 0, -112, 0 }, { -480, 0, 1609, 0 }, { 481, 0, -1607, 0 }, { -1748, 0, 1137, 0 } }, .normal = { 0, 4108, 0, 0 }, .facingNormal = { 2106, 0, -3513, 0 }, .radius = 2079, .control = 4, .parameter0 = 6, .parameter1 = 0, .flags = 4, .hit = 0 }, { .next = NULL, .prevLink = NULL, .coord = NULL, .origin = { 23200, -32, 2048, 0 }, .vertices = { { 2418, 0, 652, 0 }, { -2420, 0, 505, 0 }, { 2419, 0, -506, 0 }, { -2419, 0, -653, 0 } }, .normal = { 0, 4096, 0, 0 }, .facingNormal = { -201, 0, -4092, 0 }, .radius = 2495, .control = 4, .parameter0 = 7, .parameter1 = 0, .flags = 130, .hit = 0 } },
};
#else
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
static WorldCollisionTrigger _gAkropolisPlazaHelicopterWreckTrigger[1];
static void peDecodeArr_gAkropolisPlazaHelicopterWreckTrigger(void* base, const unsigned char* src, size_t n)
{
    WorldCollisionTrigger* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_WorldCollisionTrigger(&dst[k], src + k * 76);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_plaza/_gAkropolisPlazaHelicopterWreckTrigger", _gAkropolisPlazaHelicopterWreckTrigger, peDecodeArr_gAkropolisPlazaHelicopterWreckTrigger);
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
static WorldCollisionTrigger _gAkropolisPlazaSergeantTrigger;
static void peDecodeArr_gAkropolisPlazaSergeantTrigger(void* base, const unsigned char* src, size_t n)
{
    WorldCollisionTrigger* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_WorldCollisionTrigger(&dst[k], src + k * 76);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_plaza/_gAkropolisPlazaSergeantTrigger", _gAkropolisPlazaSergeantTrigger, peDecodeArr_gAkropolisPlazaSergeantTrigger);
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
static WorldCollisionTrigger _gAkropolisPlazaEntranceAndExamineTriggers[4];
static void peDecodeArr_gAkropolisPlazaEntranceAndExamineTriggers(void* base, const unsigned char* src, size_t n)
{
    WorldCollisionTrigger* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_WorldCollisionTrigger(&dst[k], src + k * 76);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_plaza/_gAkropolisPlazaEntranceAndExamineTriggers", _gAkropolisPlazaEntranceAndExamineTriggers, peDecodeArr_gAkropolisPlazaEntranceAndExamineTriggers);
#endif
