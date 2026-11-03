/* rooms/akropolis/west_elevator_hall/package: written from its room instance by tools/buildsteps/gen_room_inc.py. */

#include "gameplay/evs.h"
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
static AnimationBankCopyRequest _gAkropolisWestElevatorHallArrivalAnimationBankCopyRequest;
static void peDecodeArr_gAkropolisWestElevatorHallArrivalAnimationBankCopyRequest(void* base, const unsigned char* src, size_t n)
{
    AnimationBankCopyRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationBankCopyRequest(&dst[k], src + k * 8);
    dst[0].sets = (void*)&_gAkropolisWestElevatorHallArrivalAnimationSets;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_west_elevator_hall/_gAkropolisWestElevatorHallArrivalAnimationBankCopyRequest", _gAkropolisWestElevatorHallArrivalAnimationBankCopyRequest, peDecodeArr_gAkropolisWestElevatorHallArrivalAnimationBankCopyRequest);
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
static AnimationPlayRequest _gAkropolisWestElevatorHallArrivalAnimationRequest;
static void peDecodeArr_gAkropolisWestElevatorHallArrivalAnimationRequest(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_west_elevator_hall/_gAkropolisWestElevatorHallArrivalAnimationRequest", _gAkropolisWestElevatorHallArrivalAnimationRequest, peDecodeArr_gAkropolisWestElevatorHallArrivalAnimationRequest);
static ActorTransform _gAkropolisWestElevatorHallPlayerArrivalHiddenTransform;
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_west_elevator_hall/_gAkropolisWestElevatorHallPlayerArrivalHiddenTransform", _gAkropolisWestElevatorHallPlayerArrivalHiddenTransform);
static ActorTransform _gAkropolisWestElevatorHallPlayerDoorwayTransform;
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_west_elevator_hall/_gAkropolisWestElevatorHallPlayerDoorwayTransform", _gAkropolisWestElevatorHallPlayerDoorwayTransform);
static ActorTransform _gAkropolisWestElevatorHallUnusedTransform;
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_west_elevator_hall/_gAkropolisWestElevatorHallUnusedTransform", _gAkropolisWestElevatorHallUnusedTransform);
static ActorTransform _gAkropolisWestElevatorHallPlayerArrivalEndTransform;
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_west_elevator_hall/_gAkropolisWestElevatorHallPlayerArrivalEndTransform", _gAkropolisWestElevatorHallPlayerArrivalEndTransform);
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
static AnimationPlayRequest _gAkropolisWestElevatorHallPlayerIdleAnimationRequest;
static void peDecodeArr_gAkropolisWestElevatorHallPlayerIdleAnimationRequest(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_west_elevator_hall/_gAkropolisWestElevatorHallPlayerIdleAnimationRequest", _gAkropolisWestElevatorHallPlayerIdleAnimationRequest, peDecodeArr_gAkropolisWestElevatorHallPlayerIdleAnimationRequest);
#ifndef PE_DECODE_EvsCommand
#define PE_DECODE_EvsCommand
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
static void peDecode_EvsCommand(EvsCommand* dst, const unsigned char* src)
{
    { int32_t v; memcpy(&v, src + 0, 4); dst->opcode = v; }
    { uint32_t v; memcpy(&v, src + 4, 4); dst->operand0.value = v; }
    { uint32_t v; memcpy(&v, src + 8, 4); dst->operand1.value = v; }
    { uint32_t v; memcpy(&v, src + 12, 4); dst->operand2.value = v; }
    { uint32_t v; memcpy(&v, src + 16, 4); dst->operand3.value = v; }
    { uint32_t v; memcpy(&v, src + 20, 4); dst->operand4.value = v; }
}

#endif
static EvsCommand _gAkropolisWestElevatorHallArrivalScript[26];
static void peDecodeArr_gAkropolisWestElevatorHallArrivalScript(void* base, const unsigned char* src, size_t n)
{
    EvsCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_EvsCommand(&dst[k], src + k * 24);
    dst[2].operand3.storage = &_gAkropolisWestElevatorHallPlayerIdleAnimationRequest;
    dst[3].operand3.storage = &_gAkropolisWestElevatorHallArrivalAnimationBankCopyRequest;
    dst[4].operand3.storage = &_gAkropolisWestElevatorHallPlayerArrivalHiddenTransform;
    dst[12].operand3.storage = &_gAkropolisWestElevatorHallPlayerDoorwayTransform;
    dst[13].operand3.storage = &_gAkropolisWestElevatorHallArrivalAnimationRequest;
    dst[24].operand3.storage = &_gAkropolisWestElevatorHallPlayerArrivalEndTransform;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_west_elevator_hall/_gAkropolisWestElevatorHallArrivalScript", _gAkropolisWestElevatorHallArrivalScript, peDecodeArr_gAkropolisWestElevatorHallArrivalScript);
#ifndef PE_DECODE_EvsCommand
#define PE_DECODE_EvsCommand
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
static void peDecode_EvsCommand(EvsCommand* dst, const unsigned char* src)
{
    { int32_t v; memcpy(&v, src + 0, 4); dst->opcode = v; }
    { uint32_t v; memcpy(&v, src + 4, 4); dst->operand0.value = v; }
    { uint32_t v; memcpy(&v, src + 8, 4); dst->operand1.value = v; }
    { uint32_t v; memcpy(&v, src + 12, 4); dst->operand2.value = v; }
    { uint32_t v; memcpy(&v, src + 16, 4); dst->operand3.value = v; }
    { uint32_t v; memcpy(&v, src + 20, 4); dst->operand4.value = v; }
}

#endif
static EvsCommand _gAkropolisWestElevatorHallArrivalSkipScript[13];
static void peDecodeArr_gAkropolisWestElevatorHallArrivalSkipScript(void* base, const unsigned char* src, size_t n)
{
    EvsCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_EvsCommand(&dst[k], src + k * 24);
    dst[2].operand3.storage = &_gAkropolisWestElevatorHallPlayerArrivalEndTransform;
    dst[3].operand3.storage = &_gAkropolisWestElevatorHallPlayerIdleAnimationRequest;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_west_elevator_hall/_gAkropolisWestElevatorHallArrivalSkipScript", _gAkropolisWestElevatorHallArrivalSkipScript, peDecodeArr_gAkropolisWestElevatorHallArrivalSkipScript);
