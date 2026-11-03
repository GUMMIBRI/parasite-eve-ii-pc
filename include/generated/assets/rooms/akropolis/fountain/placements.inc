/* rooms/akropolis/fountain/package: written from its room instance by tools/buildsteps/gen_room_inc.py. */

#include "types.h"
#include "actors/actor_01100.h"
#include "gameplay/area.h"
#include "stages/akropolis/stage.h"

#ifndef PE_DECODE_AreaResource
#define PE_DECODE_AreaResource
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
static void peDecode_AreaResource(AreaResource* dst, const unsigned char* src)
{
    { uint16_t v; memcpy(&v, src + 0, 2); dst->entryId = v; }
    { int16_t v; memcpy(&v, src + 2, 2); dst->fileNumber = v; }
    { uint8_t v; memcpy(&v, src + 4, 1); dst->fileGroupIndex = v; }
    { uint8_t v; memcpy(&v, src + 5, 1); dst->taskIndex = v; }
    memcpy(dst->unknown_6, src + 6, 2);
    /* taskTable: pointer, set by the array's fixups */
}

#endif
static AreaResource _gAkropolisFountainVariant2Resources[2];
static void peDecodeArr_gAkropolisFountainVariant2Resources(void* base, const unsigned char* src, size_t n)
{
    AreaResource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AreaResource(&dst[k], src + k * 12);
    dst[0].taskTable = &gActor301100Tasks;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_fountain/_gAkropolisFountainVariant2Resources", _gAkropolisFountainVariant2Resources, peDecodeArr_gAkropolisFountainVariant2Resources);
#ifndef PE_DECODE_AreaResource
#define PE_DECODE_AreaResource
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
static void peDecode_AreaResource(AreaResource* dst, const unsigned char* src)
{
    { uint16_t v; memcpy(&v, src + 0, 2); dst->entryId = v; }
    { int16_t v; memcpy(&v, src + 2, 2); dst->fileNumber = v; }
    { uint8_t v; memcpy(&v, src + 4, 1); dst->fileGroupIndex = v; }
    { uint8_t v; memcpy(&v, src + 5, 1); dst->taskIndex = v; }
    memcpy(dst->unknown_6, src + 6, 2);
    /* taskTable: pointer, set by the array's fixups */
}

#endif
static AreaResource _gAkropolisFountainVariant7Resources[2];
static void peDecodeArr_gAkropolisFountainVariant7Resources(void* base, const unsigned char* src, size_t n)
{
    AreaResource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AreaResource(&dst[k], src + k * 12);
    dst[0].taskTable = &gActor01100Tasks;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_fountain/_gAkropolisFountainVariant7Resources", _gAkropolisFountainVariant7Resources, peDecodeArr_gAkropolisFountainVariant7Resources);
#ifndef PE_DECODE_AreaVariant
#define PE_DECODE_AreaVariant
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
static void peDecode_AreaVariant(AreaVariant* dst, const unsigned char* src)
{
    /* placements: pointer, set by the array's fixups */
    /* resources: pointer, set by the array's fixups */
}

#endif
AreaVariant gAkropolisFountainAreaVariants[11];
static void peDecodeArr_gAkropolisFountainAreaVariants(void* base, const unsigned char* src, size_t n)
{
    AreaVariant* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AreaVariant(&dst[k], src + k * 8);
    dst[2].placements = gAkropolisStageFountainVariant2Placements;
    dst[2].resources = _gAkropolisFountainVariant2Resources;
    dst[7].placements = gAkropolisStageFountainVariant7Placements;
    dst[7].resources = _gAkropolisFountainVariant7Resources;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_fountain/gAkropolisFountainAreaVariants", gAkropolisFountainAreaVariants, peDecodeArr_gAkropolisFountainAreaVariants);
