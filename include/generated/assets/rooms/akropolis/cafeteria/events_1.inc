/* rooms/akropolis/cafeteria/package: written from its room instance by tools/buildsteps/gen_room_inc.py. */

#include "gameplay/message.h"

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
static AnimationPlayRequest _gAkropolisCafeteriaPlayerAnimation1;
static void peDecodeArr_gAkropolisCafeteriaPlayerAnimation1(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_cafeteria/_gAkropolisCafeteriaPlayerAnimation1", _gAkropolisCafeteriaPlayerAnimation1, peDecodeArr_gAkropolisCafeteriaPlayerAnimation1);
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
static AnimationPlayRequest _gAkropolisCafeteriaUnusedPlayerAnimation;
static void peDecodeArr_gAkropolisCafeteriaUnusedPlayerAnimation(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_cafeteria/_gAkropolisCafeteriaUnusedPlayerAnimation", _gAkropolisCafeteriaUnusedPlayerAnimation, peDecodeArr_gAkropolisCafeteriaUnusedPlayerAnimation);
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
static AnimationPlayRequest _gAkropolisCafeteriaPlayerPostBattleAnimation8;
static void peDecodeArr_gAkropolisCafeteriaPlayerPostBattleAnimation8(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_cafeteria/_gAkropolisCafeteriaPlayerPostBattleAnimation8", _gAkropolisCafeteriaPlayerPostBattleAnimation8, peDecodeArr_gAkropolisCafeteriaPlayerPostBattleAnimation8);
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
static AnimationPlayRequest _gAkropolisCafeteriaPlayerPostBattleAnimation9;
static void peDecodeArr_gAkropolisCafeteriaPlayerPostBattleAnimation9(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_cafeteria/_gAkropolisCafeteriaPlayerPostBattleAnimation9", _gAkropolisCafeteriaPlayerPostBattleAnimation9, peDecodeArr_gAkropolisCafeteriaPlayerPostBattleAnimation9);
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
static AnimationPlayRequest _gAkropolisCafeteriaOpeningWomanAnimation1;
static void peDecodeArr_gAkropolisCafeteriaOpeningWomanAnimation1(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_cafeteria/_gAkropolisCafeteriaOpeningWomanAnimation1", _gAkropolisCafeteriaOpeningWomanAnimation1, peDecodeArr_gAkropolisCafeteriaOpeningWomanAnimation1);
static ActorTransform _gAkropolisCafeteriaPlayerOpeningScenePlacement;
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_cafeteria/_gAkropolisCafeteriaPlayerOpeningScenePlacement", _gAkropolisCafeteriaPlayerOpeningScenePlacement);
static ActorTransform _gAkropolisCafeteriaPlayerOpeningResumePlacement;
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_cafeteria/_gAkropolisCafeteriaPlayerOpeningResumePlacement", _gAkropolisCafeteriaPlayerOpeningResumePlacement);
static ActorTransform _gAkropolisCafeteriaPlayerFollowUpStartPlacement;
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_cafeteria/_gAkropolisCafeteriaPlayerFollowUpStartPlacement", _gAkropolisCafeteriaPlayerFollowUpStartPlacement);
static ActorTransform _gAkropolisCafeteriaPlayerBeforeRupertArrivalPlacement;
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_cafeteria/_gAkropolisCafeteriaPlayerBeforeRupertArrivalPlacement", _gAkropolisCafeteriaPlayerBeforeRupertArrivalPlacement);
static ActorTransform _gAkropolisCafeteriaPlayerBattleStartPlacement;
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_cafeteria/_gAkropolisCafeteriaPlayerBattleStartPlacement", _gAkropolisCafeteriaPlayerBattleStartPlacement);
static ActorTransform _gAkropolisCafeteriaPlayerFollowUpWalkStartPlacement;
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_cafeteria/_gAkropolisCafeteriaPlayerFollowUpWalkStartPlacement", _gAkropolisCafeteriaPlayerFollowUpWalkStartPlacement);
static ActorTransform _gAkropolisCafeteriaPlayerFollowUpWalkTarget;
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_cafeteria/_gAkropolisCafeteriaPlayerFollowUpWalkTarget", _gAkropolisCafeteriaPlayerFollowUpWalkTarget);
static ActorTransform _gAkropolisCafeteriaUnusedPlayerPlacement;
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_cafeteria/_gAkropolisCafeteriaUnusedPlayerPlacement", _gAkropolisCafeteriaUnusedPlayerPlacement);
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
static AnimationPlayRequest _gAkropolisCafeteriaUnusedActorAnimation;
static void peDecodeArr_gAkropolisCafeteriaUnusedActorAnimation(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_cafeteria/_gAkropolisCafeteriaUnusedActorAnimation", _gAkropolisCafeteriaUnusedActorAnimation, peDecodeArr_gAkropolisCafeteriaUnusedActorAnimation);
