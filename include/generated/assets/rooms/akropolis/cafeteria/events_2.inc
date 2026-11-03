/* rooms/akropolis/cafeteria/package: written from its room instance by tools/buildsteps/gen_room_inc.py. */

#include "gameplay/message.h"

#ifndef PE_DECODE_AnimationBankCopyRequest
#define PE_DECODE_AnimationBankCopyRequest
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
static void peDecode_AnimationBankCopyRequest(AnimationBankCopyRequest* dst, const unsigned char* src)
{
    /* sets: pointer, set by the array's fixups */
    { int32_t v; memcpy(&v, src + 4, 4); dst->count = v; }
}

#endif
static AnimationBankCopyRequest _gAkropolisCafeteriaOpeningPlayerBankCopy;
static void peDecodeArr_gAkropolisCafeteriaOpeningPlayerBankCopy(void* base, const unsigned char* src, size_t n)
{
    AnimationBankCopyRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationBankCopyRequest(&dst[k], src + k * 8);
    dst[0].sets = (void*)&_gAkropolisCafeteriaOpeningPlayerAnimationSets;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_cafeteria/_gAkropolisCafeteriaOpeningPlayerBankCopy", _gAkropolisCafeteriaOpeningPlayerBankCopy, peDecodeArr_gAkropolisCafeteriaOpeningPlayerBankCopy);
#ifndef PE_DECODE_AnimationPlayRequest
#define PE_DECODE_AnimationPlayRequest
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
static void peDecode_AnimationPlayRequest(AnimationPlayRequest* dst, const unsigned char* src)
{
    { uint32_t v; memcpy(&v, src + 0, 4); dst->source.index = v; }
    { int32_t v; memcpy(&v, src + 4, 4); dst->animationId = v; }
    { int32_t v; memcpy(&v, src + 8, 4); dst->blend = v; }
    { int32_t v; memcpy(&v, src + 12, 4); dst->blendFrames = v; }
    { int32_t v; memcpy(&v, src + 16, 4); dst->enableWorldCollision = v; }
}

#endif
static AnimationPlayRequest _gAkropolisCafeteriaPlayerOpeningAnimation47;
static void peDecodeArr_gAkropolisCafeteriaPlayerOpeningAnimation47(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_cafeteria/_gAkropolisCafeteriaPlayerOpeningAnimation47", _gAkropolisCafeteriaPlayerOpeningAnimation47, peDecodeArr_gAkropolisCafeteriaPlayerOpeningAnimation47);
