/* rooms/akropolis/roof_garden/package: written from its room instance by tools/buildsteps/gen_room_inc.py. */

#include "types.h"
#include "actors/actor_00700.h"
#include "actors/actor_02600.h"
#include "actors/actor_05500.h"
#include "gameplay/area.h"
#include "stages/akropolis/actors/roof_garden_swat_member.h"
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
static AreaResource _gAkropolisRoofGardenVariant1Resources[3];
static void peDecodeArr_gAkropolisRoofGardenVariant1Resources(void* base, const unsigned char* src, size_t n)
{
    AreaResource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AreaResource(&dst[k], src + k * 12);
    dst[0].taskTable = &gRoofGardenSwatMemberViewFigureTasks;
    dst[1].taskTable = &gActor205500MaggotCaterpillarTasks;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_roof_garden/_gAkropolisRoofGardenVariant1Resources", _gAkropolisRoofGardenVariant1Resources, peDecodeArr_gAkropolisRoofGardenVariant1Resources);
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
static AreaResource _gAkropolisRoofGardenVariant2Resources[3];
static void peDecodeArr_gAkropolisRoofGardenVariant2Resources(void* base, const unsigned char* src, size_t n)
{
    AreaResource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AreaResource(&dst[k], src + k * 12);
    dst[0].taskTable = &gActor105500MaggotCaterpillarTasks;
    dst[1].taskTable = &gActor00700MothTaskDesc;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_roof_garden/_gAkropolisRoofGardenVariant2Resources", _gAkropolisRoofGardenVariant2Resources, peDecodeArr_gAkropolisRoofGardenVariant2Resources);
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
static AreaResource _gAkropolisRoofGardenVariant7Resources[3];
static void peDecodeArr_gAkropolisRoofGardenVariant7Resources(void* base, const unsigned char* src, size_t n)
{
    AreaResource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AreaResource(&dst[k], src + k * 12);
    dst[0].taskTable = &gRoofGardenSwatMemberViewFigureTasks;
    dst[1].taskTable = &gActor202600MaggotCaterpillarBodyTask;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_roof_garden/_gAkropolisRoofGardenVariant7Resources", _gAkropolisRoofGardenVariant7Resources, peDecodeArr_gAkropolisRoofGardenVariant7Resources);
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
static AreaResource _gAkropolisRoofGardenVariant8Resources[3];
static void peDecodeArr_gAkropolisRoofGardenVariant8Resources(void* base, const unsigned char* src, size_t n)
{
    AreaResource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AreaResource(&dst[k], src + k * 12);
    dst[0].taskTable = &gActor02600MaggotCaterpillarBodyTask;
    dst[1].taskTable = &gActor00700MothTaskDesc;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_roof_garden/_gAkropolisRoofGardenVariant8Resources", _gAkropolisRoofGardenVariant8Resources, peDecodeArr_gAkropolisRoofGardenVariant8Resources);
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
AreaVariant gAkropolisRoofGardenAreaVariants[12];
static void peDecodeArr_gAkropolisRoofGardenAreaVariants(void* base, const unsigned char* src, size_t n)
{
    AreaVariant* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AreaVariant(&dst[k], src + k * 8);
    dst[1].placements = gAkropolisStageRoofGardenVariant1Placements;
    dst[1].resources = _gAkropolisRoofGardenVariant1Resources;
    dst[2].placements = gAkropolisStageRoofGardenVariant2Placements;
    dst[2].resources = _gAkropolisRoofGardenVariant2Resources;
    dst[7].placements = gAkropolisStageRoofGardenVariant7Placements;
    dst[7].resources = _gAkropolisRoofGardenVariant7Resources;
    dst[8].placements = gAkropolisStageRoofGardenVariant8Placements;
    dst[8].resources = _gAkropolisRoofGardenVariant8Resources;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_roof_garden/gAkropolisRoofGardenAreaVariants", gAkropolisRoofGardenAreaVariants, peDecodeArr_gAkropolisRoofGardenAreaVariants);
