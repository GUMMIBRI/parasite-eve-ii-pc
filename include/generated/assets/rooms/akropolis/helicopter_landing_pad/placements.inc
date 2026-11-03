/* rooms/akropolis/helicopter_landing_pad/package: written from its room instance by tools/buildsteps/gen_room_inc.py. */

#include "types.h"
#include "gameplay/area.h"
#include "stages/akropolis/actors/helicopter_departure.h"
#include "stages/akropolis/actors/helicopter_landing_pad_no_9.h"
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
static AreaResource _gAkropolisHelicopterLandingPadVariant1Resources[2];
static void peDecodeArr_gAkropolisHelicopterLandingPadVariant1Resources(void* base, const unsigned char* src, size_t n)
{
    AreaResource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AreaResource(&dst[k], src + k * 12);
    dst[0].taskTable = &gHelicopterLandingPadNo9TaskDescriptors;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_helicopter_landing_pad/_gAkropolisHelicopterLandingPadVariant1Resources", _gAkropolisHelicopterLandingPadVariant1Resources, peDecodeArr_gAkropolisHelicopterLandingPadVariant1Resources);
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
static AreaResource _gAkropolisHelicopterLandingPadVariant2Resources[4];
static void peDecodeArr_gAkropolisHelicopterLandingPadVariant2Resources(void* base, const unsigned char* src, size_t n)
{
    AreaResource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AreaResource(&dst[k], src + k * 12);
    dst[0].taskTable = &gHelicopterDepartureNo9GolemTaskDescriptors;
    dst[1].taskTable = &gHelicopterDepartureRupertTaskDescriptors;
    dst[2].taskTable = &gHelicopterDepartureHelicopterTaskDescriptors;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_helicopter_landing_pad/_gAkropolisHelicopterLandingPadVariant2Resources", _gAkropolisHelicopterLandingPadVariant2Resources, peDecodeArr_gAkropolisHelicopterLandingPadVariant2Resources);
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
AreaVariant gAkropolisHelicopterLandingPadAreaVariants[13];
static void peDecodeArr_gAkropolisHelicopterLandingPadAreaVariants(void* base, const unsigned char* src, size_t n)
{
    AreaVariant* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AreaVariant(&dst[k], src + k * 8);
    dst[1].placements = gAkropolisStageHelicopterLandingPadVariant1Placements;
    dst[1].resources = _gAkropolisHelicopterLandingPadVariant1Resources;
    dst[2].placements = gAkropolisStageHelicopterLandingPadVariant2Placements;
    dst[2].resources = _gAkropolisHelicopterLandingPadVariant2Resources;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_helicopter_landing_pad/gAkropolisHelicopterLandingPadAreaVariants", gAkropolisHelicopterLandingPadAreaVariants, peDecodeArr_gAkropolisHelicopterLandingPadAreaVariants);
