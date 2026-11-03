/* rooms/akropolis/observatory/package: written from its room instance by tools/buildsteps/gen_room_inc.py. */

#include "types.h"
#include "actors/actor_01100.h"
#include "actors/actor_01200.h"
#include "actors/actor_01900.h"
#include "actors/actor_03700.h"
#include "actors/actor_04000.h"
#include "actors/actor_401000.h"
#include "actors/actor_401300.h"
#include "actors/actor_401800.h"
#include "gameplay/area.h"
#include "gameplay/areaplace.h"
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
static AreaResource _gAkropolisObservatoryVariant1Resources[2];
static void peDecodeArr_gAkropolisObservatoryVariant1Resources(void* base, const unsigned char* src, size_t n)
{
    AreaResource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AreaResource(&dst[k], src + k * 12);
    dst[0].taskTable = &gActor301900GrinningStrangerTaskDesc;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_observatory/_gAkropolisObservatoryVariant1Resources", _gAkropolisObservatoryVariant1Resources, peDecodeArr_gAkropolisObservatoryVariant1Resources);
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
static AreaResource _gAkropolisObservatoryVariant2Resources[2];
static void peDecodeArr_gAkropolisObservatoryVariant2Resources(void* base, const unsigned char* src, size_t n)
{
    AreaResource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AreaResource(&dst[k], src + k * 12);
    dst[0].taskTable = &gActor101100Tasks;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_observatory/_gAkropolisObservatoryVariant2Resources", _gAkropolisObservatoryVariant2Resources, peDecodeArr_gAkropolisObservatoryVariant2Resources);
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
static AreaResource _gAkropolisObservatoryVariant3Resources[2];
static void peDecodeArr_gAkropolisObservatoryVariant3Resources(void* base, const unsigned char* src, size_t n)
{
    AreaResource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AreaResource(&dst[k], src + k * 12);
    dst[0].taskTable = &gActor103700BatTaskDesc;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_observatory/_gAkropolisObservatoryVariant3Resources", _gAkropolisObservatoryVariant3Resources, peDecodeArr_gAkropolisObservatoryVariant3Resources);
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
static AreaResource _gAkropolisObservatoryVariant7Resources[2];
static void peDecodeArr_gAkropolisObservatoryVariant7Resources(void* base, const unsigned char* src, size_t n)
{
    AreaResource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AreaResource(&dst[k], src + k * 12);
    dst[0].taskTable = &gActor01100Tasks;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_observatory/_gAkropolisObservatoryVariant7Resources", _gAkropolisObservatoryVariant7Resources, peDecodeArr_gAkropolisObservatoryVariant7Resources);
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
static AreaResource _gAkropolisObservatoryVariant10Resources[2];
static void peDecodeArr_gAkropolisObservatoryVariant10Resources(void* base, const unsigned char* src, size_t n)
{
    AreaResource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AreaResource(&dst[k], src + k * 12);
    dst[0].taskTable = &gActor401300HornedStrangerTaskDesc;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_observatory/_gAkropolisObservatoryVariant10Resources", _gAkropolisObservatoryVariant10Resources, peDecodeArr_gAkropolisObservatoryVariant10Resources);
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
static AreaResource _gAkropolisObservatoryVariant11Resources[2];
static void peDecodeArr_gAkropolisObservatoryVariant11Resources(void* base, const unsigned char* src, size_t n)
{
    AreaResource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AreaResource(&dst[k], src + k * 12);
    dst[0].taskTable = &gActor401000StrangerTaskDesc;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_observatory/_gAkropolisObservatoryVariant11Resources", _gAkropolisObservatoryVariant11Resources, peDecodeArr_gAkropolisObservatoryVariant11Resources);
static AreaPlacement _gAkropolisObservatoryVariant11Placements[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_observatory/_gAkropolisObservatoryVariant11Placements", _gAkropolisObservatoryVariant11Placements);
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
static AreaResource _gAkropolisObservatoryVariants12And13Resources[2];
static void peDecodeArr_gAkropolisObservatoryVariants12And13Resources(void* base, const unsigned char* src, size_t n)
{
    AreaResource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AreaResource(&dst[k], src + k * 12);
    dst[0].taskTable = &gActor101200BoneSucklerTaskDesc;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_observatory/_gAkropolisObservatoryVariants12And13Resources", _gAkropolisObservatoryVariants12And13Resources, peDecodeArr_gAkropolisObservatoryVariants12And13Resources);
static AreaPlacement _gAkropolisObservatoryVariant12Placements[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_observatory/_gAkropolisObservatoryVariant12Placements", _gAkropolisObservatoryVariant12Placements);
static AreaPlacement _gAkropolisObservatoryVariant13Placements[7];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_observatory/_gAkropolisObservatoryVariant13Placements", _gAkropolisObservatoryVariant13Placements);
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
static AreaResource _gAkropolisObservatoryVariant14Resources[2];
static void peDecodeArr_gAkropolisObservatoryVariant14Resources(void* base, const unsigned char* src, size_t n)
{
    AreaResource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AreaResource(&dst[k], src + k * 12);
    dst[0].taskTable = &gActor04000BloodSucklerTaskDesc;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_observatory/_gAkropolisObservatoryVariant14Resources", _gAkropolisObservatoryVariant14Resources, peDecodeArr_gAkropolisObservatoryVariant14Resources);
static AreaPlacement _gAkropolisObservatoryVariant14Placements[3];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_observatory/_gAkropolisObservatoryVariant14Placements", _gAkropolisObservatoryVariant14Placements);
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
static AreaResource _gAkropolisObservatoryVariant15Resources[1];
static void peDecodeArr_gAkropolisObservatoryVariant15Resources(void* base, const unsigned char* src, size_t n)
{
    AreaResource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AreaResource(&dst[k], src + k * 12);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_observatory/_gAkropolisObservatoryVariant15Resources", _gAkropolisObservatoryVariant15Resources, peDecodeArr_gAkropolisObservatoryVariant15Resources);
static AreaPlacement _gAkropolisObservatoryVariant15Placements[3];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_observatory/_gAkropolisObservatoryVariant15Placements", _gAkropolisObservatoryVariant15Placements);
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
static AreaResource _gAkropolisObservatoryVariant16Resources[2];
static void peDecodeArr_gAkropolisObservatoryVariant16Resources(void* base, const unsigned char* src, size_t n)
{
    AreaResource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AreaResource(&dst[k], src + k * 12);
    dst[0].taskTable = &gActor401800OddStrangerTaskDesc;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_observatory/_gAkropolisObservatoryVariant16Resources", _gAkropolisObservatoryVariant16Resources, peDecodeArr_gAkropolisObservatoryVariant16Resources);
static AreaPlacement _gAkropolisObservatoryVariant16Placements[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_observatory/_gAkropolisObservatoryVariant16Placements", _gAkropolisObservatoryVariant16Placements);
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
static AreaResource _gAkropolisObservatoryVariant17Resources[2];
static void peDecodeArr_gAkropolisObservatoryVariant17Resources(void* base, const unsigned char* src, size_t n)
{
    AreaResource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AreaResource(&dst[k], src + k * 12);
    dst[0].taskTable = &gActor101900GrinningStrangerTaskDesc;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_observatory/_gAkropolisObservatoryVariant17Resources", _gAkropolisObservatoryVariant17Resources, peDecodeArr_gAkropolisObservatoryVariant17Resources);
static AreaPlacement _gAkropolisObservatoryVariant17Placements[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_observatory/_gAkropolisObservatoryVariant17Placements", _gAkropolisObservatoryVariant17Placements);
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
AreaVariant gAkropolisObservatoryAreaVariants[19];
static void peDecodeArr_gAkropolisObservatoryAreaVariants(void* base, const unsigned char* src, size_t n)
{
    AreaVariant* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AreaVariant(&dst[k], src + k * 8);
    dst[1].placements = gAkropolisStageObservatoryVariant1Placements;
    dst[1].resources = _gAkropolisObservatoryVariant1Resources;
    dst[2].placements = gAkropolisStageObservatoryVariant2Placements;
    dst[2].resources = _gAkropolisObservatoryVariant2Resources;
    dst[3].placements = gAkropolisStageObservatoryVariant3Placements;
    dst[3].resources = _gAkropolisObservatoryVariant3Resources;
    dst[7].placements = gAkropolisStageObservatoryVariant7Placements;
    dst[7].resources = _gAkropolisObservatoryVariant7Resources;
    dst[10].placements = gAkropolisStageObservatoryVariant10Placements;
    dst[10].resources = _gAkropolisObservatoryVariant10Resources;
    dst[11].placements = _gAkropolisObservatoryVariant11Placements;
    dst[11].resources = _gAkropolisObservatoryVariant11Resources;
    dst[12].placements = _gAkropolisObservatoryVariant12Placements;
    dst[12].resources = _gAkropolisObservatoryVariants12And13Resources;
    dst[13].placements = _gAkropolisObservatoryVariant13Placements;
    dst[13].resources = _gAkropolisObservatoryVariants12And13Resources;
    dst[14].placements = _gAkropolisObservatoryVariant14Placements;
    dst[14].resources = _gAkropolisObservatoryVariant14Resources;
    dst[15].placements = _gAkropolisObservatoryVariant15Placements;
    dst[15].resources = _gAkropolisObservatoryVariant15Resources;
    dst[16].placements = _gAkropolisObservatoryVariant16Placements;
    dst[16].resources = _gAkropolisObservatoryVariant16Resources;
    dst[17].placements = _gAkropolisObservatoryVariant17Placements;
    dst[17].resources = _gAkropolisObservatoryVariant17Resources;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_observatory/gAkropolisObservatoryAreaVariants", gAkropolisObservatoryAreaVariants, peDecodeArr_gAkropolisObservatoryAreaVariants);
