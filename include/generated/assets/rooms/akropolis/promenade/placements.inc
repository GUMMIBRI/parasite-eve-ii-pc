/* rooms/akropolis/promenade/package: written from its room instance by tools/buildsteps/gen_room_inc.py. */

#include "types.h"
#include "actors/actor_00700.h"
#include "actors/actor_01100.h"
#include "actors/actor_02600.h"
#include "actors/actor_05500.h"
#include "actors/actor_402200.h"
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
static AreaResource _gAkropolisPromenadeVariant1Resources[2];
static void peDecodeArr_gAkropolisPromenadeVariant1Resources(void* base, const unsigned char* src, size_t n)
{
    AreaResource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AreaResource(&dst[k], src + k * 12);
    dst[0].taskTable = &gActor301100Tasks;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_promenade/_gAkropolisPromenadeVariant1Resources", _gAkropolisPromenadeVariant1Resources, peDecodeArr_gAkropolisPromenadeVariant1Resources);
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
static AreaResource _gAkropolisPromenadeVariant2Resources[3];
static void peDecodeArr_gAkropolisPromenadeVariant2Resources(void* base, const unsigned char* src, size_t n)
{
    AreaResource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AreaResource(&dst[k], src + k * 12);
    dst[0].taskTable = &gActor200700RatTaskDesc;
    dst[1].taskTable = &gActor00700MothTaskDesc;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_promenade/_gAkropolisPromenadeVariant2Resources", _gAkropolisPromenadeVariant2Resources, peDecodeArr_gAkropolisPromenadeVariant2Resources);
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
static AreaResource _gAkropolisPromenadeVariant3Resources[3];
static void peDecodeArr_gAkropolisPromenadeVariant3Resources(void* base, const unsigned char* src, size_t n)
{
    AreaResource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AreaResource(&dst[k], src + k * 12);
    dst[0].taskTable = &gActor105500MaggotCaterpillarTasks;
    dst[1].taskTable = &gActor00700MothTaskDesc;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_promenade/_gAkropolisPromenadeVariant3Resources", _gAkropolisPromenadeVariant3Resources, peDecodeArr_gAkropolisPromenadeVariant3Resources);
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
static AreaResource _gAkropolisPromenadeVariant7Resources[2];
static void peDecodeArr_gAkropolisPromenadeVariant7Resources(void* base, const unsigned char* src, size_t n)
{
    AreaResource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AreaResource(&dst[k], src + k * 12);
    dst[0].taskTable = &gActor402200GolemTaskDesc;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_promenade/_gAkropolisPromenadeVariant7Resources", _gAkropolisPromenadeVariant7Resources, peDecodeArr_gAkropolisPromenadeVariant7Resources);
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
static AreaResource _gAkropolisPromenadeVariant8Resources[3];
static void peDecodeArr_gAkropolisPromenadeVariant8Resources(void* base, const unsigned char* src, size_t n)
{
    AreaResource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AreaResource(&dst[k], src + k * 12);
    dst[0].taskTable = &gActor02600MaggotCaterpillarBodyTask;
    dst[1].taskTable = &gActor00700MothTaskDesc;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_promenade/_gAkropolisPromenadeVariant8Resources", _gAkropolisPromenadeVariant8Resources, peDecodeArr_gAkropolisPromenadeVariant8Resources);
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
AreaVariant gAkropolisPromenadeAreaVariants[17];
static void peDecodeArr_gAkropolisPromenadeAreaVariants(void* base, const unsigned char* src, size_t n)
{
    AreaVariant* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AreaVariant(&dst[k], src + k * 8);
    dst[1].placements = gAkropolisStagePromenadeVariant1Placements;
    dst[1].resources = _gAkropolisPromenadeVariant1Resources;
    dst[2].placements = gAkropolisStagePromenadeVariant2Placements;
    dst[2].resources = _gAkropolisPromenadeVariant2Resources;
    dst[3].placements = gAkropolisStagePromenadeVariant3Placements;
    dst[3].resources = _gAkropolisPromenadeVariant3Resources;
    dst[7].placements = gAkropolisStagePromenadeVariant7Placements;
    dst[7].resources = _gAkropolisPromenadeVariant7Resources;
    dst[8].placements = gAkropolisStagePromenadeVariant8Placements;
    dst[8].resources = _gAkropolisPromenadeVariant8Resources;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_promenade/gAkropolisPromenadeAreaVariants", gAkropolisPromenadeAreaVariants, peDecodeArr_gAkropolisPromenadeAreaVariants);
