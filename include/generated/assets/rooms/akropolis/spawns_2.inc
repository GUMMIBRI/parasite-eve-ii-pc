/* rooms/akropolis/stage: written from its room instance by tools/buildsteps/gen_room_inc.py. */

#include "types.h"
#include "gameplay/area_flags.h"
#include "stages/akropolis/rooms/helicopter_landing_pad.h"

#ifndef PE_DECODE_AreaObjectSpawn
#define PE_DECODE_AreaObjectSpawn
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
static void peDecode_AreaObjectSpawn(AreaObjectSpawn* dst, const unsigned char* src)
{
    { uint16_t v; memcpy(&v, src + 0, 2); dst->kind = v; }
    { uint16_t v; memcpy(&v, src + 4, 2); dst->taskDesc.header.fields.flags = v; }
    { uint16_t v; memcpy(&v, src + 6, 2); dst->taskDesc.header.fields.priority = v; }
    /* taskDesc.callback: pointer, set by the array's fixups */
    { uint32_t v; memcpy(&v, src + 12, 4); dst->taskDesc.data.value = v; }
}

#endif
static AreaObjectSpawn _gAkropolisStageHelicopterLandingPadObjectSpawns[3];
static void peDecodeArr_gAkropolisStageHelicopterLandingPadObjectSpawns(void* base, const unsigned char* src, size_t n)
{
    AreaObjectSpawn* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AreaObjectSpawn(&dst[k], src + k * 16);
    dst[0].taskDesc.callback = akropolisHelicopterLandingPadLiftTask;
    dst[0].taskDesc.data.model = &gAkropolisHelicopterLandingPadLiftModel;
    dst[1].taskDesc.callback = akropolisHelicopterLandingPadPickupModelTask;
    dst[1].taskDesc.data.model = &gAkropolisHelicopterLandingPadAmmunitionPickupModel;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_stage/_gAkropolisStageHelicopterLandingPadObjectSpawns", _gAkropolisStageHelicopterLandingPadObjectSpawns, peDecodeArr_gAkropolisStageHelicopterLandingPadObjectSpawns);
