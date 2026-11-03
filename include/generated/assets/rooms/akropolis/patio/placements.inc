/* rooms/akropolis/patio/package: written from its room instance by tools/buildsteps/gen_room_inc.py. */

#include "types.h"
#include "actors/actor_00700.h"
#include "actors/actor_01900.h"
#include "actors/actor_300700.h"
#include "actors/actor_401000.h"
#include "gameplay/area.h"
#include "stages/akropolis/actors/patio_leaping_strangers.h"
#include "stages/akropolis/actors/patio_swat_member.h"
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
static AreaResource _gAkropolisPatioVariant1ActorResources[3];
static void peDecodeArr_gAkropolisPatioVariant1ActorResources(void* base, const unsigned char* src, size_t n)
{
    AreaResource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AreaResource(&dst[k], src + k * 12);
    dst[0].taskTable = &gActor101900GrinningStrangerTaskDesc;
    dst[1].taskTable = &gPatioSwatMemberTaskDesc;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_patio/_gAkropolisPatioVariant1ActorResources", _gAkropolisPatioVariant1ActorResources, peDecodeArr_gAkropolisPatioVariant1ActorResources);
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
static AreaResource _gAkropolisPatioVariant2ActorResources[3];
static void peDecodeArr_gAkropolisPatioVariant2ActorResources(void* base, const unsigned char* src, size_t n)
{
    AreaResource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AreaResource(&dst[k], src + k * 12);
    dst[0].taskTable = &gPatioLeapingStrangersTaskDesc;
    dst[1].taskTable = &gActor101900GrinningStrangerTaskDesc;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_patio/_gAkropolisPatioVariant2ActorResources", _gAkropolisPatioVariant2ActorResources, peDecodeArr_gAkropolisPatioVariant2ActorResources);
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
static AreaResource _gAkropolisPatioVariant3ActorResources[3];
static void peDecodeArr_gAkropolisPatioVariant3ActorResources(void* base, const unsigned char* src, size_t n)
{
    AreaResource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AreaResource(&dst[k], src + k * 12);
    dst[0].taskTable = &gActor00700RatTaskDesc;
    dst[1].taskTable = &gActor00700MothTaskDesc;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_patio/_gAkropolisPatioVariant3ActorResources", _gAkropolisPatioVariant3ActorResources, peDecodeArr_gAkropolisPatioVariant3ActorResources);
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
static AreaResource _gAkropolisPatioVariant4ActorResources[3];
static void peDecodeArr_gAkropolisPatioVariant4ActorResources(void* base, const unsigned char* src, size_t n)
{
    AreaResource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AreaResource(&dst[k], src + k * 12);
    dst[0].taskTable = &gActor300700MothTaskDesc;
    dst[1].taskTable = &gActor401000StrangerTaskDesc;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_patio/_gAkropolisPatioVariant4ActorResources", _gAkropolisPatioVariant4ActorResources, peDecodeArr_gAkropolisPatioVariant4ActorResources);
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
static AreaResource _gAkropolisPatioVariant5ActorResources[2];
static void peDecodeArr_gAkropolisPatioVariant5ActorResources(void* base, const unsigned char* src, size_t n)
{
    AreaResource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AreaResource(&dst[k], src + k * 12);
    dst[0].taskTable = &gActor401000StrangerTaskDesc;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_patio/_gAkropolisPatioVariant5ActorResources", _gAkropolisPatioVariant5ActorResources, peDecodeArr_gAkropolisPatioVariant5ActorResources);
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
static AreaResource _gAkropolisPatioVariant10ActorResources[1];
static void peDecodeArr_gAkropolisPatioVariant10ActorResources(void* base, const unsigned char* src, size_t n)
{
    AreaResource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AreaResource(&dst[k], src + k * 12);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_patio/_gAkropolisPatioVariant10ActorResources", _gAkropolisPatioVariant10ActorResources, peDecodeArr_gAkropolisPatioVariant10ActorResources);
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
AreaVariant gAkropolisPatioAreaVariants[12];
static void peDecodeArr_gAkropolisPatioAreaVariants(void* base, const unsigned char* src, size_t n)
{
    AreaVariant* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AreaVariant(&dst[k], src + k * 8);
    dst[1].placements = gAkropolisStagePatioVariant1Placements;
    dst[1].resources = _gAkropolisPatioVariant1ActorResources;
    dst[2].placements = gAkropolisStagePatioVariant2Placements;
    dst[2].resources = _gAkropolisPatioVariant2ActorResources;
    dst[3].placements = gAkropolisStagePatioVariant3Placements;
    dst[3].resources = _gAkropolisPatioVariant3ActorResources;
    dst[4].placements = gAkropolisStagePatioVariant4Placements;
    dst[4].resources = _gAkropolisPatioVariant4ActorResources;
    dst[5].placements = gAkropolisStagePatioVariant5Placements;
    dst[5].resources = _gAkropolisPatioVariant5ActorResources;
    dst[10].placements = gAkropolisStagePatioVariant10Placements;
    dst[10].resources = _gAkropolisPatioVariant10ActorResources;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_patio/gAkropolisPatioAreaVariants", gAkropolisPatioAreaVariants, peDecodeArr_gAkropolisPatioAreaVariants);
