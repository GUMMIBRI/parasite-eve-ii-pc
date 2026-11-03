/* rooms/akropolis/plaza/package: written from its room instance by tools/buildsteps/gen_room_inc.py. */

#include "gameplay/direction.h"

#ifndef PE_DECODE_DirectionWarpEntry
#define PE_DECODE_DirectionWarpEntry
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
static void peDecode_DirectionWarpEntry(DirectionWarpEntry* dst, const unsigned char* src)
{
    { int32_t v; memcpy(&v, src + 0, 4); dst->player.yaw.word = v; }
    { int32_t v; memcpy(&v, src + 4, 4); dst->player.x = v; }
    { int32_t v; memcpy(&v, src + 8, 4); dst->player.y = v; }
    { int32_t v; memcpy(&v, src + 12, 4); dst->player.z = v; }
    memcpy(dst->unknown_10, src + 16, 4);
    { int32_t v; memcpy(&v, src + 20, 4); dst->companion.yaw.word = v; }
    { int32_t v; memcpy(&v, src + 24, 4); dst->companion.x = v; }
    { int32_t v; memcpy(&v, src + 28, 4); dst->companion.y = v; }
    { int32_t v; memcpy(&v, src + 32, 4); dst->companion.z = v; }
    memcpy(dst->unknown_24, src + 36, 4);
    { int32_t v; memcpy(&v, src + 40, 4); dst->arrivalSound = v; }
    { int32_t v; memcpy(&v, src + 44, 4); dst->departureSound = v; }
    { int32_t v; memcpy(&v, src + 48, 4); dst->blockedSound = v; }
    { uint8_t v; memcpy(&v, src + 52, 1); dst->initialView = v; }
    { uint8_t v; memcpy(&v, src + 53, 1); dst->flags = v; }
    { uint16_t v; memcpy(&v, src + 54, 2); dst->mapFlagId = v; }
}

#endif
DirectionWarpEntry gAkropolisPlazaWarpEntries[1];
static void peDecodeArr_gAkropolisPlazaWarpEntries(void* base, const unsigned char* src, size_t n)
{
    DirectionWarpEntry* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_DirectionWarpEntry(&dst[k], src + k * 56);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_plaza/gAkropolisPlazaWarpEntries", gAkropolisPlazaWarpEntries, peDecodeArr_gAkropolisPlazaWarpEntries);
