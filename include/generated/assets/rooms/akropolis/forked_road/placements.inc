/* rooms/akropolis/forked_road/package: written from its room instance by tools/buildsteps/gen_room_inc.py. */

#include "types.h"
#include "actors/actor_00700.h"
#include "actors/actor_01500.h"
#include "actors/actor_01600.h"
#include "actors/actor_01900.h"
#include "actors/actor_02000.h"
#include "actors/actor_02400.h"
#include "actors/actor_02500.h"
#include "actors/actor_02600.h"
#include "actors/actor_03700.h"
#include "actors/actor_03800.h"
#include "actors/actor_04600.h"
#include "actors/actor_05500.h"
#include "actors/actor_07000.h"
#include "actors/actor_207200.h"
#include "actors/actor_300700.h"
#include "actors/actor_401000.h"
#include "actors/actor_401800.h"
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
static AreaResource _gAkropolisForkedRoadVariant2Resources[2];
static void peDecodeArr_gAkropolisForkedRoadVariant2Resources(void* base, const unsigned char* src, size_t n)
{
    AreaResource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AreaResource(&dst[k], src + k * 12);
    dst[0].taskTable = &gActor301900GrinningStrangerTaskDesc;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_forked_road/_gAkropolisForkedRoadVariant2Resources", _gAkropolisForkedRoadVariant2Resources, peDecodeArr_gAkropolisForkedRoadVariant2Resources);
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
static AreaResource _gAkropolisForkedRoadVariant3Resources[3];
static void peDecodeArr_gAkropolisForkedRoadVariant3Resources(void* base, const unsigned char* src, size_t n)
{
    AreaResource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AreaResource(&dst[k], src + k * 12);
    dst[0].taskTable = &gActor401000StrangerTaskDesc;
    dst[1].taskTable = &gActor300700RatTaskDesc;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_forked_road/_gAkropolisForkedRoadVariant3Resources", _gAkropolisForkedRoadVariant3Resources, peDecodeArr_gAkropolisForkedRoadVariant3Resources);
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
static AreaResource _gAkropolisForkedRoadVariant4Resources[2];
static void peDecodeArr_gAkropolisForkedRoadVariant4Resources(void* base, const unsigned char* src, size_t n)
{
    AreaResource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AreaResource(&dst[k], src + k * 12);
    dst[0].taskTable = &gActor105500MaggotCaterpillarTasks;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_forked_road/_gAkropolisForkedRoadVariant4Resources", _gAkropolisForkedRoadVariant4Resources, peDecodeArr_gAkropolisForkedRoadVariant4Resources);
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
static AreaResource _gAkropolisForkedRoadVariant7Resources[3];
static void peDecodeArr_gAkropolisForkedRoadVariant7Resources(void* base, const unsigned char* src, size_t n)
{
    AreaResource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AreaResource(&dst[k], src + k * 12);
    dst[0].taskTable = &gActor102000PawnGolemTasks;
    dst[1].taskTable = &gActor200700RatTaskDesc;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_forked_road/_gAkropolisForkedRoadVariant7Resources", _gAkropolisForkedRoadVariant7Resources, peDecodeArr_gAkropolisForkedRoadVariant7Resources);
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
static AreaResource _gAkropolisForkedRoadVariant8Resources[2];
static void peDecodeArr_gAkropolisForkedRoadVariant8Resources(void* base, const unsigned char* src, size_t n)
{
    AreaResource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AreaResource(&dst[k], src + k * 12);
    dst[0].taskTable = &gActor02600MaggotCaterpillarBodyTask;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_forked_road/_gAkropolisForkedRoadVariant8Resources", _gAkropolisForkedRoadVariant8Resources, peDecodeArr_gAkropolisForkedRoadVariant8Resources);
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
static AreaResource _gAkropolisForkedRoadVariant9Resources[2];
static void peDecodeArr_gAkropolisForkedRoadVariant9Resources(void* base, const unsigned char* src, size_t n)
{
    AreaResource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AreaResource(&dst[k], src + k * 12);
    dst[0].taskTable = &gActor401800OddStrangerTaskDesc;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_forked_road/_gAkropolisForkedRoadVariant9Resources", _gAkropolisForkedRoadVariant9Resources, peDecodeArr_gAkropolisForkedRoadVariant9Resources);
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
static AreaResource _gAkropolisForkedRoadVariant10Resources[3];
static void peDecodeArr_gAkropolisForkedRoadVariant10Resources(void* base, const unsigned char* src, size_t n)
{
    AreaResource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AreaResource(&dst[k], src + k * 12);
    dst[0].taskTable = &gActor00700RatTaskDesc;
    dst[1].taskTable = &gActor00700MothTaskDesc;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_forked_road/_gAkropolisForkedRoadVariant10Resources", _gAkropolisForkedRoadVariant10Resources, peDecodeArr_gAkropolisForkedRoadVariant10Resources);
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
static AreaResource _gAkropolisForkedRoadVariant11Resources[2];
static void peDecodeArr_gAkropolisForkedRoadVariant11Resources(void* base, const unsigned char* src, size_t n)
{
    AreaResource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AreaResource(&dst[k], src + k * 12);
    dst[0].taskTable = &gActor102400Tasks;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_forked_road/_gAkropolisForkedRoadVariant11Resources", _gAkropolisForkedRoadVariant11Resources, peDecodeArr_gAkropolisForkedRoadVariant11Resources);
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
static AreaResource _gAkropolisForkedRoadVariant12Resources[2];
static void peDecodeArr_gAkropolisForkedRoadVariant12Resources(void* base, const unsigned char* src, size_t n)
{
    AreaResource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AreaResource(&dst[k], src + k * 12);
    dst[0].taskTable = &gActor102500Tasks;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_forked_road/_gAkropolisForkedRoadVariant12Resources", _gAkropolisForkedRoadVariant12Resources, peDecodeArr_gAkropolisForkedRoadVariant12Resources);
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
static AreaResource _gAkropolisForkedRoadVariant13Resources[2];
static void peDecodeArr_gAkropolisForkedRoadVariant13Resources(void* base, const unsigned char* src, size_t n)
{
    AreaResource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AreaResource(&dst[k], src + k * 12);
    dst[0].taskTable = &gActor02600MaggotCaterpillarBodyTask;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_forked_road/_gAkropolisForkedRoadVariant13Resources", _gAkropolisForkedRoadVariant13Resources, peDecodeArr_gAkropolisForkedRoadVariant13Resources);
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
static AreaResource _gAkropolisForkedRoadVariant14Resources[2];
static void peDecodeArr_gAkropolisForkedRoadVariant14Resources(void* base, const unsigned char* src, size_t n)
{
    AreaResource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AreaResource(&dst[k], src + k * 12);
    dst[0].taskTable = &gActor103700BatTaskDesc;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_forked_road/_gAkropolisForkedRoadVariant14Resources", _gAkropolisForkedRoadVariant14Resources, peDecodeArr_gAkropolisForkedRoadVariant14Resources);
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
static AreaResource _gAkropolisForkedRoadVariant15Resources[2];
static void peDecodeArr_gAkropolisForkedRoadVariant15Resources(void* base, const unsigned char* src, size_t n)
{
    AreaResource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AreaResource(&dst[k], src + k * 12);
    dst[0].taskTable = &gActor01500MindSucklerTaskDesc;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_forked_road/_gAkropolisForkedRoadVariant15Resources", _gAkropolisForkedRoadVariant15Resources, peDecodeArr_gAkropolisForkedRoadVariant15Resources);
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
static AreaResource _gAkropolisForkedRoadVariant16Resources[2];
static void peDecodeArr_gAkropolisForkedRoadVariant16Resources(void* base, const unsigned char* src, size_t n)
{
    AreaResource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AreaResource(&dst[k], src + k * 12);
    dst[0].taskTable = &gActor103800BlackBeetleTaskDesc;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_forked_road/_gAkropolisForkedRoadVariant16Resources", _gAkropolisForkedRoadVariant16Resources, peDecodeArr_gAkropolisForkedRoadVariant16Resources);
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
static AreaResource _gAkropolisForkedRoadVariant20Resources[2];
static void peDecodeArr_gAkropolisForkedRoadVariant20Resources(void* base, const unsigned char* src, size_t n)
{
    AreaResource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AreaResource(&dst[k], src + k * 12);
    dst[0].taskTable = &gActor101600ScavengerTaskDesc;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_forked_road/_gAkropolisForkedRoadVariant20Resources", _gAkropolisForkedRoadVariant20Resources, peDecodeArr_gAkropolisForkedRoadVariant20Resources);
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
static AreaResource _gAkropolisForkedRoadVariant21Resources[3];
static void peDecodeArr_gAkropolisForkedRoadVariant21Resources(void* base, const unsigned char* src, size_t n)
{
    AreaResource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AreaResource(&dst[k], src + k * 12);
    dst[0].taskTable = &gActor104600SucklercephTaskDesc;
    dst[1].taskTable = &gActor104600SkullStalkerTaskDesc;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_forked_road/_gAkropolisForkedRoadVariant21Resources", _gAkropolisForkedRoadVariant21Resources, peDecodeArr_gAkropolisForkedRoadVariant21Resources);
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
static AreaResource _gAkropolisForkedRoadVariant22Resources[5];
static void peDecodeArr_gAkropolisForkedRoadVariant22Resources(void* base, const unsigned char* src, size_t n)
{
    AreaResource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AreaResource(&dst[k], src + k * 12);
    dst[0].taskTable = &gActor107000SlouchTaskDescs;
    dst[1].taskTable = &gActor107000SucklercephTaskDescs;
    dst[2].taskTable = &gActor207200CreepingStrangerTaskDesc;
    dst[3].taskTable = &gActor207200SkullStalkerTaskDesc;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_forked_road/_gAkropolisForkedRoadVariant22Resources", _gAkropolisForkedRoadVariant22Resources, peDecodeArr_gAkropolisForkedRoadVariant22Resources);
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
AreaVariant gAkropolisForkedRoadAreaVariants[24];
static void peDecodeArr_gAkropolisForkedRoadAreaVariants(void* base, const unsigned char* src, size_t n)
{
    AreaVariant* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AreaVariant(&dst[k], src + k * 8);
    dst[2].placements = gAkropolisStageForkedRoadVariant2Placements;
    dst[2].resources = _gAkropolisForkedRoadVariant2Resources;
    dst[3].placements = gAkropolisStageForkedRoadVariant3Placements;
    dst[3].resources = _gAkropolisForkedRoadVariant3Resources;
    dst[4].placements = gAkropolisStageForkedRoadVariant4Placements;
    dst[4].resources = _gAkropolisForkedRoadVariant4Resources;
    dst[7].placements = gAkropolisStageForkedRoadVariant7Placements;
    dst[7].resources = _gAkropolisForkedRoadVariant7Resources;
    dst[8].placements = gAkropolisStageForkedRoadVariant8Placements;
    dst[8].resources = _gAkropolisForkedRoadVariant8Resources;
    dst[9].placements = gAkropolisStageForkedRoadVariant9Placements;
    dst[9].resources = _gAkropolisForkedRoadVariant9Resources;
    dst[10].placements = gAkropolisStageForkedRoadVariant10Placements;
    dst[10].resources = _gAkropolisForkedRoadVariant10Resources;
    dst[11].placements = gAkropolisStageForkedRoadVariant11Placements;
    dst[11].resources = _gAkropolisForkedRoadVariant11Resources;
    dst[12].placements = gAkropolisStageForkedRoadVariant12Placements;
    dst[12].resources = _gAkropolisForkedRoadVariant12Resources;
    dst[13].placements = gAkropolisStageForkedRoadVariant13Placements;
    dst[13].resources = _gAkropolisForkedRoadVariant13Resources;
    dst[14].placements = gAkropolisStageForkedRoadVariant14Placements;
    dst[14].resources = _gAkropolisForkedRoadVariant14Resources;
    dst[15].placements = gAkropolisStageForkedRoadVariant15Placements;
    dst[15].resources = _gAkropolisForkedRoadVariant15Resources;
    dst[16].placements = gAkropolisStageForkedRoadVariant16Placements;
    dst[16].resources = _gAkropolisForkedRoadVariant16Resources;
    dst[20].placements = gAkropolisStageForkedRoadVariant20Placements;
    dst[20].resources = _gAkropolisForkedRoadVariant20Resources;
    dst[21].placements = gAkropolisStageForkedRoadVariant21Placements;
    dst[21].resources = _gAkropolisForkedRoadVariant21Resources;
    dst[22].placements = gAkropolisStageForkedRoadVariant22Placements;
    dst[22].resources = _gAkropolisForkedRoadVariant22Resources;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_forked_road/gAkropolisForkedRoadAreaVariants", gAkropolisForkedRoadAreaVariants, peDecodeArr_gAkropolisForkedRoadAreaVariants);
