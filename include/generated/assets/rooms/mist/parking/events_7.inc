/* rooms/mist/parking/package: written from its room instance by tools/buildsteps/gen_room_inc.py. */

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
AnimationBankCopyRequest gMistParkingShopPlayerAnimationBankCopy;
static void peDecodeArr_gMistParkingShopPlayerAnimationBankCopy(void* base, const unsigned char* src, size_t n)
{
    AnimationBankCopyRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationBankCopyRequest(&dst[k], src + k * 8);
    dst[0].sets = (void*)&_gMistParkingShopPlayerAnimationSets;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_parking/gMistParkingShopPlayerAnimationBankCopy", gMistParkingShopPlayerAnimationBankCopy, peDecodeArr_gMistParkingShopPlayerAnimationBankCopy);
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
static AnimationPlayRequest _gMistParkingUnusedBank1Clip1Animation;
static void peDecodeArr_gMistParkingUnusedBank1Clip1Animation(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_parking/_gMistParkingUnusedBank1Clip1Animation", _gMistParkingUnusedBank1Clip1Animation, peDecodeArr_gMistParkingUnusedBank1Clip1Animation);
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
AnimationPlayRequest gMistParkingPlayerShopTalkAnimation;
static void peDecodeArr_gMistParkingPlayerShopTalkAnimation(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_parking/gMistParkingPlayerShopTalkAnimation", gMistParkingPlayerShopTalkAnimation, peDecodeArr_gMistParkingPlayerShopTalkAnimation);
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
static AnimationPlayRequest _gMistParkingPlayerDepartureMenuAnimation;
static void peDecodeArr_gMistParkingPlayerDepartureMenuAnimation(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_parking/_gMistParkingPlayerDepartureMenuAnimation", _gMistParkingPlayerDepartureMenuAnimation, peDecodeArr_gMistParkingPlayerDepartureMenuAnimation);
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
static AnimationPlayRequest _gMistParkingPlayerStayAnimation;
static void peDecodeArr_gMistParkingPlayerStayAnimation(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_parking/_gMistParkingPlayerStayAnimation", _gMistParkingPlayerStayAnimation, peDecodeArr_gMistParkingPlayerStayAnimation);
