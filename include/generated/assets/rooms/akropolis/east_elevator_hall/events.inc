/* rooms/akropolis/east_elevator_hall/package: written from its room instance by tools/buildsteps/gen_room_inc.py. */

#include "gameplay/evs.h"
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
static AnimationPlayRequest _gAkropolisEastElevatorHallOpeningPlayerMainAnimationRequest;
static void peDecodeArr_gAkropolisEastElevatorHallOpeningPlayerMainAnimationRequest(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);
    dst[0].source.sets = (void*)&_gAkropolisEastElevatorHallOpeningPlayerMainAnimationSets;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_east_elevator_hall/_gAkropolisEastElevatorHallOpeningPlayerMainAnimationRequest", _gAkropolisEastElevatorHallOpeningPlayerMainAnimationRequest, peDecodeArr_gAkropolisEastElevatorHallOpeningPlayerMainAnimationRequest);
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
static AnimationPlayRequest _gAkropolisEastElevatorHallOpeningPlayerLeadInAnimationRequest;
static void peDecodeArr_gAkropolisEastElevatorHallOpeningPlayerLeadInAnimationRequest(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);
    dst[0].source.sets = (void*)&_gAkropolisEastElevatorHallOpeningPlayerLeadInAnimationSets;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_east_elevator_hall/_gAkropolisEastElevatorHallOpeningPlayerLeadInAnimationRequest", _gAkropolisEastElevatorHallOpeningPlayerLeadInAnimationRequest, peDecodeArr_gAkropolisEastElevatorHallOpeningPlayerLeadInAnimationRequest);
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
static AnimationPlayRequest _gAkropolisEastElevatorHallOpeningPlayerExitAnimationRequest;
static void peDecodeArr_gAkropolisEastElevatorHallOpeningPlayerExitAnimationRequest(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);
    dst[0].source.sets = (void*)&_gAkropolisEastElevatorHallOpeningPlayerExitAnimationSets;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_east_elevator_hall/_gAkropolisEastElevatorHallOpeningPlayerExitAnimationRequest", _gAkropolisEastElevatorHallOpeningPlayerExitAnimationRequest, peDecodeArr_gAkropolisEastElevatorHallOpeningPlayerExitAnimationRequest);
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
static AnimationPlayRequest _gAkropolisEastElevatorHallWeaponAnimationRequest;
static void peDecodeArr_gAkropolisEastElevatorHallWeaponAnimationRequest(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_east_elevator_hall/_gAkropolisEastElevatorHallWeaponAnimationRequest", _gAkropolisEastElevatorHallWeaponAnimationRequest, peDecodeArr_gAkropolisEastElevatorHallWeaponAnimationRequest);
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
static AnimationPlayRequest _gAkropolisEastElevatorHallSwatFreezeAnimationRequest;
static void peDecodeArr_gAkropolisEastElevatorHallSwatFreezeAnimationRequest(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_east_elevator_hall/_gAkropolisEastElevatorHallSwatFreezeAnimationRequest", _gAkropolisEastElevatorHallSwatFreezeAnimationRequest, peDecodeArr_gAkropolisEastElevatorHallSwatFreezeAnimationRequest);
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
static AnimationPlayRequest _gAkropolisEastElevatorHallSwatOpeningTalkAnimationRequest;
static void peDecodeArr_gAkropolisEastElevatorHallSwatOpeningTalkAnimationRequest(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_east_elevator_hall/_gAkropolisEastElevatorHallSwatOpeningTalkAnimationRequest", _gAkropolisEastElevatorHallSwatOpeningTalkAnimationRequest, peDecodeArr_gAkropolisEastElevatorHallSwatOpeningTalkAnimationRequest);
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
static AnimationPlayRequest _gAkropolisEastElevatorHallSwatWatchYourBackAnimationRequest;
static void peDecodeArr_gAkropolisEastElevatorHallSwatWatchYourBackAnimationRequest(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_east_elevator_hall/_gAkropolisEastElevatorHallSwatWatchYourBackAnimationRequest", _gAkropolisEastElevatorHallSwatWatchYourBackAnimationRequest, peDecodeArr_gAkropolisEastElevatorHallSwatWatchYourBackAnimationRequest);
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
static AnimationPlayRequest _gAkropolisEastElevatorHallSwatRestAnimationRequest;
static void peDecodeArr_gAkropolisEastElevatorHallSwatRestAnimationRequest(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_east_elevator_hall/_gAkropolisEastElevatorHallSwatRestAnimationRequest", _gAkropolisEastElevatorHallSwatRestAnimationRequest, peDecodeArr_gAkropolisEastElevatorHallSwatRestAnimationRequest);
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
static AnimationPlayRequest _gAkropolisEastElevatorHallSwatUrgeHurryAnimationRequest;
static void peDecodeArr_gAkropolisEastElevatorHallSwatUrgeHurryAnimationRequest(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_east_elevator_hall/_gAkropolisEastElevatorHallSwatUrgeHurryAnimationRequest", _gAkropolisEastElevatorHallSwatUrgeHurryAnimationRequest, peDecodeArr_gAkropolisEastElevatorHallSwatUrgeHurryAnimationRequest);
static EvsSceneKey _gAkropolisEastElevatorHallOpeningSceneKey;
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_east_elevator_hall/_gAkropolisEastElevatorHallOpeningSceneKey", _gAkropolisEastElevatorHallOpeningSceneKey);
static EvsSceneKey _gAkropolisEastElevatorHallUnusedSceneKey;
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_east_elevator_hall/_gAkropolisEastElevatorHallUnusedSceneKey", _gAkropolisEastElevatorHallUnusedSceneKey);
static ActorTransform _gAkropolisEastElevatorHallUnusedTransform;
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_east_elevator_hall/_gAkropolisEastElevatorHallUnusedTransform", _gAkropolisEastElevatorHallUnusedTransform);
static ActorTransform _gAkropolisEastElevatorHallOpeningPlayerWalkTarget;
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_east_elevator_hall/_gAkropolisEastElevatorHallOpeningPlayerWalkTarget", _gAkropolisEastElevatorHallOpeningPlayerWalkTarget);
static ActorTransform _gAkropolisEastElevatorHallOpeningOriginTransform;
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_east_elevator_hall/_gAkropolisEastElevatorHallOpeningOriginTransform", _gAkropolisEastElevatorHallOpeningOriginTransform);
static ActorTransform _gAkropolisEastElevatorHallOpeningPlayerLeadInTransform;
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_east_elevator_hall/_gAkropolisEastElevatorHallOpeningPlayerLeadInTransform", _gAkropolisEastElevatorHallOpeningPlayerLeadInTransform);
static ActorTransform _gAkropolisEastElevatorHallUnusedEndTurnTransform;
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_east_elevator_hall/_gAkropolisEastElevatorHallUnusedEndTurnTransform", _gAkropolisEastElevatorHallUnusedEndTurnTransform);
static ActorTransform _gAkropolisEastElevatorHallOpeningPlayerEndTransform;
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_east_elevator_hall/_gAkropolisEastElevatorHallOpeningPlayerEndTransform", _gAkropolisEastElevatorHallOpeningPlayerEndTransform);
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
static EvsCommand _gAkropolisEastElevatorHallOpeningScript[36];
static void peDecodeArr_gAkropolisEastElevatorHallOpeningScript(void* base, const unsigned char* src, size_t n)
{
    EvsCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_EvsCommand(&dst[k], src + k * 24);
    dst[2].operand0.storage = &_gAkropolisEastElevatorHallOpeningSceneKey;
    dst[4].operand3.storage = &_gAkropolisEastElevatorHallOpeningOriginTransform;
    dst[5].operand3.storage = &_gAkropolisEastElevatorHallSwatFreezeAnimationRequest;
    dst[6].operand3.storage = &_gAkropolisEastElevatorHallOpeningPlayerWalkTarget;
    dst[8].operand3.storage = &_gAkropolisEastElevatorHallWeaponAnimationRequest;
    dst[13].operand3.storage = &_gAkropolisEastElevatorHallOpeningPlayerLeadInTransform;
    dst[14].operand3.storage = &_gAkropolisEastElevatorHallOpeningPlayerLeadInAnimationRequest;
    dst[19].operand3.storage = &_gAkropolisEastElevatorHallOpeningOriginTransform;
    dst[20].operand3.storage = &_gAkropolisEastElevatorHallOpeningPlayerMainAnimationRequest;
    dst[21].operand3.storage = &_gAkropolisEastElevatorHallSwatOpeningTalkAnimationRequest;
    dst[26].operand3.storage = &_gAkropolisEastElevatorHallOpeningPlayerExitAnimationRequest;
    dst[27].operand3.storage = &_gAkropolisEastElevatorHallSwatWatchYourBackAnimationRequest;
    dst[29].operand3.storage = &_gAkropolisEastElevatorHallSwatRestAnimationRequest;
    dst[30].operand3.storage = &_gAkropolisEastElevatorHallWeaponAnimationRequest;
    dst[32].operand3.storage = &_gAkropolisEastElevatorHallOpeningPlayerEndTransform;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_east_elevator_hall/_gAkropolisEastElevatorHallOpeningScript", _gAkropolisEastElevatorHallOpeningScript, peDecodeArr_gAkropolisEastElevatorHallOpeningScript);
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
static EvsCommand _gAkropolisEastElevatorHallOpeningSkipScript[15];
static void peDecodeArr_gAkropolisEastElevatorHallOpeningSkipScript(void* base, const unsigned char* src, size_t n)
{
    EvsCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_EvsCommand(&dst[k], src + k * 24);
    dst[2].operand3.storage = &_gAkropolisEastElevatorHallOpeningPlayerEndTransform;
    dst[3].operand3.storage = &_gAkropolisEastElevatorHallWeaponAnimationRequest;
    dst[4].operand3.storage = &_gAkropolisEastElevatorHallSwatRestAnimationRequest;
    dst[11].operand0.storage = (void*)&_akropolisEastElevatorHallStartSkipCapSequence;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_east_elevator_hall/_gAkropolisEastElevatorHallOpeningSkipScript", _gAkropolisEastElevatorHallOpeningSkipScript, peDecodeArr_gAkropolisEastElevatorHallOpeningSkipScript);
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
static EvsCommand _gAkropolisEastElevatorHallUrgeHurryScript[9];
static void peDecodeArr_gAkropolisEastElevatorHallUrgeHurryScript(void* base, const unsigned char* src, size_t n)
{
    EvsCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_EvsCommand(&dst[k], src + k * 24);
    dst[2].operand3.storage = &_gAkropolisEastElevatorHallWeaponAnimationRequest;
    dst[3].operand3.storage = &_gAkropolisEastElevatorHallSwatUrgeHurryAnimationRequest;
    dst[6].operand3.storage = &_gAkropolisEastElevatorHallSwatRestAnimationRequest;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_east_elevator_hall/_gAkropolisEastElevatorHallUrgeHurryScript", _gAkropolisEastElevatorHallUrgeHurryScript, peDecodeArr_gAkropolisEastElevatorHallUrgeHurryScript);
