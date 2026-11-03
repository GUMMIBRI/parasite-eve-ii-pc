/* rooms/akropolis/patio/package: written from its room instance by tools/buildsteps/gen_room_inc.py. */

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
static AnimationBankCopyRequest _gAkropolisPatioAmbushPlayerBankCopyRequest;
static void peDecodeArr_gAkropolisPatioAmbushPlayerBankCopyRequest(void* base, const unsigned char* src, size_t n)
{
    AnimationBankCopyRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationBankCopyRequest(&dst[k], src + k * 8);
    dst[0].sets = (void*)&_gAkropolisPatioAmbushPlayerAnimationSets;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_patio/_gAkropolisPatioAmbushPlayerBankCopyRequest", _gAkropolisPatioAmbushPlayerBankCopyRequest, peDecodeArr_gAkropolisPatioAmbushPlayerBankCopyRequest);
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
static AnimationPlayRequest _gAkropolisPatioRetainedBank1AnimationRequests[4];
static void peDecodeArr_gAkropolisPatioRetainedBank1AnimationRequests(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_patio/_gAkropolisPatioRetainedBank1AnimationRequests", _gAkropolisPatioRetainedBank1AnimationRequests, peDecodeArr_gAkropolisPatioRetainedBank1AnimationRequests);
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
static AnimationPlayRequest _gAkropolisPatioAmbushPlayerAnimation9Request;
static void peDecodeArr_gAkropolisPatioAmbushPlayerAnimation9Request(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_patio/_gAkropolisPatioAmbushPlayerAnimation9Request", _gAkropolisPatioAmbushPlayerAnimation9Request, peDecodeArr_gAkropolisPatioAmbushPlayerAnimation9Request);
static ActorTransform _gAkropolisPatioAmbushPlayerStartPlacement;
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_patio/_gAkropolisPatioAmbushPlayerStartPlacement", _gAkropolisPatioAmbushPlayerStartPlacement);
static ActorTransform _gAkropolisPatioUnusedAmbushTransforms[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_patio/_gAkropolisPatioUnusedAmbushTransforms", _gAkropolisPatioUnusedAmbushTransforms);
static ActorTransform _gAkropolisPatioAmbushPlayerRunDestination;
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_patio/_gAkropolisPatioAmbushPlayerRunDestination", _gAkropolisPatioAmbushPlayerRunDestination);
static ActorTransform _gAkropolisPatioAmbushPlayerSkipPlacement;
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_patio/_gAkropolisPatioAmbushPlayerSkipPlacement", _gAkropolisPatioAmbushPlayerSkipPlacement);
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
static AnimationPlayRequest _gAkropolisPatioRetainedBank0Animation1To4Requests[5];
static void peDecodeArr_gAkropolisPatioRetainedBank0Animation1To4Requests(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_patio/_gAkropolisPatioRetainedBank0Animation1To4Requests", _gAkropolisPatioRetainedBank0Animation1To4Requests, peDecodeArr_gAkropolisPatioRetainedBank0Animation1To4Requests);
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
static AnimationPlayRequest _gAkropolisPatioLeapingStranger1AnimationRequest;
static void peDecodeArr_gAkropolisPatioLeapingStranger1AnimationRequest(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_patio/_gAkropolisPatioLeapingStranger1AnimationRequest", _gAkropolisPatioLeapingStranger1AnimationRequest, peDecodeArr_gAkropolisPatioLeapingStranger1AnimationRequest);
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
static AnimationPlayRequest _gAkropolisPatioLeapingStranger2AnimationRequest;
static void peDecodeArr_gAkropolisPatioLeapingStranger2AnimationRequest(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_patio/_gAkropolisPatioLeapingStranger2AnimationRequest", _gAkropolisPatioLeapingStranger2AnimationRequest, peDecodeArr_gAkropolisPatioLeapingStranger2AnimationRequest);
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
static AnimationPlayRequest _gAkropolisPatioRetainedBank0Animation7And8Requests[2];
static void peDecodeArr_gAkropolisPatioRetainedBank0Animation7And8Requests(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_patio/_gAkropolisPatioRetainedBank0Animation7And8Requests", _gAkropolisPatioRetainedBank0Animation7And8Requests, peDecodeArr_gAkropolisPatioRetainedBank0Animation7And8Requests);
static ActorTransform _gAkropolisPatioLeapingStranger1StartPlacement;
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_patio/_gAkropolisPatioLeapingStranger1StartPlacement", _gAkropolisPatioLeapingStranger1StartPlacement);
static ActorTransform _gAkropolisPatioLeapingStranger1Launch;
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_patio/_gAkropolisPatioLeapingStranger1Launch", _gAkropolisPatioLeapingStranger1Launch);
static ActorTransform _gAkropolisPatioLeapingStranger2StartPlacement;
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_patio/_gAkropolisPatioLeapingStranger2StartPlacement", _gAkropolisPatioLeapingStranger2StartPlacement);
static ActorTransform _gAkropolisPatioLeapingStranger2Launch;
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_patio/_gAkropolisPatioLeapingStranger2Launch", _gAkropolisPatioLeapingStranger2Launch);
static ActorTransform _gAkropolisPatioAmbushStranger1BattlePlacement;
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_patio/_gAkropolisPatioAmbushStranger1BattlePlacement", _gAkropolisPatioAmbushStranger1BattlePlacement);
static ActorTransform _gAkropolisPatioAmbushStranger2BattlePlacement;
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_patio/_gAkropolisPatioAmbushStranger2BattlePlacement", _gAkropolisPatioAmbushStranger2BattlePlacement);
static ActorMotionWalkAnim _gAkropolisPatioStrangerLeapAnimations;
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_patio/_gAkropolisPatioStrangerLeapAnimations", _gAkropolisPatioStrangerLeapAnimations);
#ifndef PE_DECODE_ActorCommand
#define PE_DECODE_ActorCommand
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
static void peDecode_ActorCommand(ActorCommand* dst, const unsigned char* src)
{
    { uint8_t v; memcpy(&v, src + 0, 1); dst->context.loc.stage = v; }
    { uint8_t v; memcpy(&v, src + 1, 1); dst->context.loc.area = v; }
    { uint16_t v; memcpy(&v, src + 2, 2); dst->command = v; }
}

#endif
static ActorCommand _gAkropolisPatioLowerStrangerHeadWeightCommand;
static void peDecodeArr_gAkropolisPatioLowerStrangerHeadWeightCommand(void* base, const unsigned char* src, size_t n)
{
    ActorCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_ActorCommand(&dst[k], src + k * 4);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_patio/_gAkropolisPatioLowerStrangerHeadWeightCommand", _gAkropolisPatioLowerStrangerHeadWeightCommand, peDecodeArr_gAkropolisPatioLowerStrangerHeadWeightCommand);
#ifndef PE_DECODE_ActorCommand
#define PE_DECODE_ActorCommand
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
static void peDecode_ActorCommand(ActorCommand* dst, const unsigned char* src)
{
    { uint8_t v; memcpy(&v, src + 0, 1); dst->context.loc.stage = v; }
    { uint8_t v; memcpy(&v, src + 1, 1); dst->context.loc.area = v; }
    { uint16_t v; memcpy(&v, src + 2, 2); dst->command = v; }
}

#endif
static ActorCommand _gAkropolisPatioRaiseStrangerHeadWeightCommand;
static void peDecodeArr_gAkropolisPatioRaiseStrangerHeadWeightCommand(void* base, const unsigned char* src, size_t n)
{
    ActorCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_ActorCommand(&dst[k], src + k * 4);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_patio/_gAkropolisPatioRaiseStrangerHeadWeightCommand", _gAkropolisPatioRaiseStrangerHeadWeightCommand, peDecodeArr_gAkropolisPatioRaiseStrangerHeadWeightCommand);
#ifndef PE_DECODE_ActorCommand
#define PE_DECODE_ActorCommand
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
static void peDecode_ActorCommand(ActorCommand* dst, const unsigned char* src)
{
    { uint8_t v; memcpy(&v, src + 0, 1); dst->context.loc.stage = v; }
    { uint8_t v; memcpy(&v, src + 1, 1); dst->context.loc.area = v; }
    { uint16_t v; memcpy(&v, src + 2, 2); dst->command = v; }
}

#endif
static ActorCommand _gAkropolisPatioPrintStrangerTransformCommand;
static void peDecodeArr_gAkropolisPatioPrintStrangerTransformCommand(void* base, const unsigned char* src, size_t n)
{
    ActorCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_ActorCommand(&dst[k], src + k * 4);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_patio/_gAkropolisPatioPrintStrangerTransformCommand", _gAkropolisPatioPrintStrangerTransformCommand, peDecodeArr_gAkropolisPatioPrintStrangerTransformCommand);
