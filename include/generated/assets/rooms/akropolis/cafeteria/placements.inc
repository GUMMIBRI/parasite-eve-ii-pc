/* rooms/akropolis/cafeteria/package: written from its room instance by tools/buildsteps/gen_room_inc.py. */

#include "types.h"
#include "actors/actor_01200.h"
#include "actors/actor_05700.h"
#include "actors/actor_202900.h"
#include "actors/actor_210600.h"
#include "actors/actor_310600.h"
#include "actors/actor_401800.h"
#include "gameplay/area.h"
#include "stages/akropolis/actors/cafeteria_boss_stranger.h"
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
static AreaResource _gAkropolisCafeteriaOpeningSceneResources[4];
static void peDecodeArr_gAkropolisCafeteriaOpeningSceneResources(void* base, const unsigned char* src, size_t n)
{
    AreaResource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AreaResource(&dst[k], src + k * 12);
    dst[0].taskTable = &gCafeteriaBossStrangerTaskDesc;
    dst[1].taskTable = &gActor202900WomanTaskDescriptors;
    dst[2].taskTable = &gActor310600RupertBroderickTasks;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_cafeteria/_gAkropolisCafeteriaOpeningSceneResources", _gAkropolisCafeteriaOpeningSceneResources, peDecodeArr_gAkropolisCafeteriaOpeningSceneResources);
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
static AreaResource _gAkropolisCafeteriaBattleSceneResources[4];
static void peDecodeArr_gAkropolisCafeteriaBattleSceneResources(void* base, const unsigned char* src, size_t n)
{
    AreaResource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AreaResource(&dst[k], src + k * 12);
    dst[0].taskTable = &gCafeteriaBossStrangerTaskDesc;
    dst[1].taskTable = &gActor210600GrinningStrangerTaskDesc;
    dst[2].taskTable = &gActor310600RupertBroderickTasks;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_cafeteria/_gAkropolisCafeteriaBattleSceneResources", _gAkropolisCafeteriaBattleSceneResources, peDecodeArr_gAkropolisCafeteriaBattleSceneResources);
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
static AreaResource _gAkropolisCafeteriaSingleOddStrangerResources[2];
static void peDecodeArr_gAkropolisCafeteriaSingleOddStrangerResources(void* base, const unsigned char* src, size_t n)
{
    AreaResource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AreaResource(&dst[k], src + k * 12);
    dst[0].taskTable = &gActor401800OddStrangerTaskDesc;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_cafeteria/_gAkropolisCafeteriaSingleOddStrangerResources", _gAkropolisCafeteriaSingleOddStrangerResources, peDecodeArr_gAkropolisCafeteriaSingleOddStrangerResources);
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
static AreaResource _gAkropolisCafeteriaPairOddStrangerResources[2];
static void peDecodeArr_gAkropolisCafeteriaPairOddStrangerResources(void* base, const unsigned char* src, size_t n)
{
    AreaResource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AreaResource(&dst[k], src + k * 12);
    dst[0].taskTable = &gActor401800OddStrangerTaskDesc;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_cafeteria/_gAkropolisCafeteriaPairOddStrangerResources", _gAkropolisCafeteriaPairOddStrangerResources, peDecodeArr_gAkropolisCafeteriaPairOddStrangerResources);
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
static AreaResource _gAkropolisCafeteriaBoneSucklerResources[2];
static void peDecodeArr_gAkropolisCafeteriaBoneSucklerResources(void* base, const unsigned char* src, size_t n)
{
    AreaResource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AreaResource(&dst[k], src + k * 12);
    dst[0].taskTable = &gActor101200BoneSucklerTaskDesc;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_cafeteria/_gAkropolisCafeteriaBoneSucklerResources", _gAkropolisCafeteriaBoneSucklerResources, peDecodeArr_gAkropolisCafeteriaBoneSucklerResources);
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
static AreaResource _gAkropolisCafeteriaRookGolemResources[2];
static void peDecodeArr_gAkropolisCafeteriaRookGolemResources(void* base, const unsigned char* src, size_t n)
{
    AreaResource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AreaResource(&dst[k], src + k * 12);
    dst[0].taskTable = &gActor05700RookGolemTasks;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_cafeteria/_gAkropolisCafeteriaRookGolemResources", _gAkropolisCafeteriaRookGolemResources, peDecodeArr_gAkropolisCafeteriaRookGolemResources);
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
AreaVariant gAkropolisCafeteriaAreaVariants[11];
static void peDecodeArr_gAkropolisCafeteriaAreaVariants(void* base, const unsigned char* src, size_t n)
{
    AreaVariant* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AreaVariant(&dst[k], src + k * 8);
    dst[1].placements = gAkropolisStageCafeteriaVariant1Placements;
    dst[1].resources = _gAkropolisCafeteriaOpeningSceneResources;
    dst[2].placements = gAkropolisStageCafeteriaVariant2Placements;
    dst[2].resources = _gAkropolisCafeteriaBattleSceneResources;
    dst[3].placements = gAkropolisStageCafeteriaVariant3Placements;
    dst[3].resources = _gAkropolisCafeteriaSingleOddStrangerResources;
    dst[4].placements = gAkropolisStageCafeteriaVariant4Placements;
    dst[4].resources = _gAkropolisCafeteriaPairOddStrangerResources;
    dst[5].placements = gAkropolisStageCafeteriaVariant5Placements;
    dst[5].resources = _gAkropolisCafeteriaBoneSucklerResources;
    dst[7].placements = gAkropolisStageCafeteriaVariant7Placements;
    dst[7].resources = _gAkropolisCafeteriaRookGolemResources;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_cafeteria/gAkropolisCafeteriaAreaVariants", gAkropolisCafeteriaAreaVariants, peDecodeArr_gAkropolisCafeteriaAreaVariants);
