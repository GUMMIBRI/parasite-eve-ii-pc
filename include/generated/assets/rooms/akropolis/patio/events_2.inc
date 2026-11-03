/* rooms/akropolis/patio/package: written from its room instance by tools/buildsteps/gen_room_inc.py. */

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
static AnimationPlayRequest _gAkropolisPatioFollowUpPlayerAnimation47Request;
static void peDecodeArr_gAkropolisPatioFollowUpPlayerAnimation47Request(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_patio/_gAkropolisPatioFollowUpPlayerAnimation47Request", _gAkropolisPatioFollowUpPlayerAnimation47Request, peDecodeArr_gAkropolisPatioFollowUpPlayerAnimation47Request);
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
static AnimationPlayRequest _gAkropolisPatioRetainedBank1Animation48Request;
static void peDecodeArr_gAkropolisPatioRetainedBank1Animation48Request(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_patio/_gAkropolisPatioRetainedBank1Animation48Request", _gAkropolisPatioRetainedBank1Animation48Request, peDecodeArr_gAkropolisPatioRetainedBank1Animation48Request);
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
static AnimationPlayRequest _gAkropolisPatioFollowUpPlayerAnimation49Request;
static void peDecodeArr_gAkropolisPatioFollowUpPlayerAnimation49Request(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_patio/_gAkropolisPatioFollowUpPlayerAnimation49Request", _gAkropolisPatioFollowUpPlayerAnimation49Request, peDecodeArr_gAkropolisPatioFollowUpPlayerAnimation49Request);
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
static AnimationPlayRequest _gAkropolisPatioFollowUpPlayerAnimation50Request;
static void peDecodeArr_gAkropolisPatioFollowUpPlayerAnimation50Request(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_patio/_gAkropolisPatioFollowUpPlayerAnimation50Request", _gAkropolisPatioFollowUpPlayerAnimation50Request, peDecodeArr_gAkropolisPatioFollowUpPlayerAnimation50Request);
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
static AnimationPlayRequest _gAkropolisPatioFollowUpPlayerAnimation51Request;
static void peDecodeArr_gAkropolisPatioFollowUpPlayerAnimation51Request(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_patio/_gAkropolisPatioFollowUpPlayerAnimation51Request", _gAkropolisPatioFollowUpPlayerAnimation51Request, peDecodeArr_gAkropolisPatioFollowUpPlayerAnimation51Request);
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
static AnimationPlayRequest _gAkropolisPatioFollowUpPlayerAnimation52Request;
static void peDecodeArr_gAkropolisPatioFollowUpPlayerAnimation52Request(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_patio/_gAkropolisPatioFollowUpPlayerAnimation52Request", _gAkropolisPatioFollowUpPlayerAnimation52Request, peDecodeArr_gAkropolisPatioFollowUpPlayerAnimation52Request);
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
static AnimationBankCopyRequest _gAkropolisPatioFollowUpPlayerBankCopyRequest;
static void peDecodeArr_gAkropolisPatioFollowUpPlayerBankCopyRequest(void* base, const unsigned char* src, size_t n)
{
    AnimationBankCopyRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationBankCopyRequest(&dst[k], src + k * 8);
    dst[0].sets = (void*)&_gAkropolisPatioFollowUpPlayerAnimationSets;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_patio/_gAkropolisPatioFollowUpPlayerBankCopyRequest", _gAkropolisPatioFollowUpPlayerBankCopyRequest, peDecodeArr_gAkropolisPatioFollowUpPlayerBankCopyRequest);
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
static AnimationPlayRequest _gAkropolisPatioPlayerIdleAnimationRequest;
static void peDecodeArr_gAkropolisPatioPlayerIdleAnimationRequest(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_patio/_gAkropolisPatioPlayerIdleAnimationRequest", _gAkropolisPatioPlayerIdleAnimationRequest, peDecodeArr_gAkropolisPatioPlayerIdleAnimationRequest);
static ActorTransform _gAkropolisPatioOpeningSwatPlacement;
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_patio/_gAkropolisPatioOpeningSwatPlacement", _gAkropolisPatioOpeningSwatPlacement);
static ActorTransform _gAkropolisPatioRestoredSwatPlacement;
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_patio/_gAkropolisPatioRestoredSwatPlacement", _gAkropolisPatioRestoredSwatPlacement);
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
static ActorCommand _gAkropolisPatioHideStrangerCommand;
static void peDecodeArr_gAkropolisPatioHideStrangerCommand(void* base, const unsigned char* src, size_t n)
{
    ActorCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_ActorCommand(&dst[k], src + k * 4);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_patio/_gAkropolisPatioHideStrangerCommand", _gAkropolisPatioHideStrangerCommand, peDecodeArr_gAkropolisPatioHideStrangerCommand);
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
static ActorCommand _gAkropolisPatioOpeningActorsStartCommand;
static void peDecodeArr_gAkropolisPatioOpeningActorsStartCommand(void* base, const unsigned char* src, size_t n)
{
    ActorCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_ActorCommand(&dst[k], src + k * 4);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_patio/_gAkropolisPatioOpeningActorsStartCommand", _gAkropolisPatioOpeningActorsStartCommand, peDecodeArr_gAkropolisPatioOpeningActorsStartCommand);
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
static ActorCommand _gAkropolisPatioSwatWarnCommand;
static void peDecodeArr_gAkropolisPatioSwatWarnCommand(void* base, const unsigned char* src, size_t n)
{
    ActorCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_ActorCommand(&dst[k], src + k * 4);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_patio/_gAkropolisPatioSwatWarnCommand", _gAkropolisPatioSwatWarnCommand, peDecodeArr_gAkropolisPatioSwatWarnCommand);
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
static ActorCommand _gAkropolisPatioSwatSlumpCommand;
static void peDecodeArr_gAkropolisPatioSwatSlumpCommand(void* base, const unsigned char* src, size_t n)
{
    ActorCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_ActorCommand(&dst[k], src + k * 4);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_patio/_gAkropolisPatioSwatSlumpCommand", _gAkropolisPatioSwatSlumpCommand, peDecodeArr_gAkropolisPatioSwatSlumpCommand);
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
static ActorCommand _gAkropolisPatioSwatRestCommand;
static void peDecodeArr_gAkropolisPatioSwatRestCommand(void* base, const unsigned char* src, size_t n)
{
    ActorCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_ActorCommand(&dst[k], src + k * 4);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_patio/_gAkropolisPatioSwatRestCommand", _gAkropolisPatioSwatRestCommand, peDecodeArr_gAkropolisPatioSwatRestCommand);
static ActorTransform _gAkropolisPatioOpeningStrangerPlacement;
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_patio/_gAkropolisPatioOpeningStrangerPlacement", _gAkropolisPatioOpeningStrangerPlacement);
static ActorTransform _gAkropolisPatioRestoredStrangerPlacement;
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_patio/_gAkropolisPatioRestoredStrangerPlacement", _gAkropolisPatioRestoredStrangerPlacement);
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
static EvsCommand _gAkropolisPatioOpeningScript[23];
static void peDecodeArr_gAkropolisPatioOpeningScript(void* base, const unsigned char* src, size_t n)
{
    EvsCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_EvsCommand(&dst[k], src + k * 24);
    dst[1].operand3.storage = &_gAkropolisPatioPlayerIdleAnimationRequest;
    dst[6].operand3.storage = &_gAkropolisPatioOpeningActorsStartCommand;
    dst[7].operand3.storage = &_gAkropolisPatioOpeningStrangerPlacement;
    dst[8].operand3.storage = &_gAkropolisPatioOpeningSwatPlacement;
    dst[9].operand3.storage = &_gAkropolisPatioOpeningActorsStartCommand;
    dst[16].operand3.storage = &_gAkropolisPatioRestoredSwatPlacement;
    dst[17].operand3.storage = &_gAkropolisPatioSwatRestCommand;
    dst[18].operand3.storage = &_gAkropolisPatioOpeningPlayerEndPlacement;
    dst[19].operand3.storage = &_gAkropolisPatioRestoredStrangerPlacement;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_patio/_gAkropolisPatioOpeningScript", _gAkropolisPatioOpeningScript, peDecodeArr_gAkropolisPatioOpeningScript);
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
static EvsCommand _gAkropolisPatioOpeningSkipScript[16];
static void peDecodeArr_gAkropolisPatioOpeningSkipScript(void* base, const unsigned char* src, size_t n)
{
    EvsCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_EvsCommand(&dst[k], src + k * 24);
    dst[2].operand3.storage = &_gAkropolisPatioPlayerIdleAnimationRequest;
    dst[3].operand3.storage = &_gAkropolisPatioRestoredSwatPlacement;
    dst[4].operand3.storage = &_gAkropolisPatioSwatRestCommand;
    dst[5].operand3.storage = &_gAkropolisPatioOpeningPlayerEndPlacement;
    dst[6].operand3.storage = &_gAkropolisPatioRestoredStrangerPlacement;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_patio/_gAkropolisPatioOpeningSkipScript", _gAkropolisPatioOpeningSkipScript, peDecodeArr_gAkropolisPatioOpeningSkipScript);
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
static EvsCommand _gAkropolisPatioFollowUpScript[45];
static void peDecodeArr_gAkropolisPatioFollowUpScript(void* base, const unsigned char* src, size_t n)
{
    EvsCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_EvsCommand(&dst[k], src + k * 24);
    dst[0].operand3.storage = &_gAkropolisPatioPlayerIdleAnimationRequest;
    dst[4].operand3.storage = &_gAkropolisPatioFollowUpPlayerBankCopyRequest;
    dst[6].operand0.storage = (void*)&_akropolisPatioSetPlayerHeadAimState;
    dst[8].operand3.storage = &_gAkropolisPatioOpeningSwatPlacement;
    dst[9].operand3.storage = &_gAkropolisPatioSwatRestCommand;
    dst[10].operand3.storage = &_gAkropolisPatioFollowUpPlayerStartPlacement;
    dst[11].operand3.storage = &_gAkropolisPatioFollowUpPlayerWalkDestination;
    dst[16].operand3.storage = &_gAkropolisPatioSwatWarnCommand;
    dst[17].operand3.storage = &_gAkropolisPatioFollowUpPlayerAnimationPlacement;
    dst[18].operand3.storage = &_gAkropolisPatioFollowUpPlayerAnimation51Request;
    dst[20].operand3.storage = &_gAkropolisPatioFollowUpPlayerAnimation47Request;
    dst[22].operand3.storage = &_gAkropolisPatioFollowUpPlayerAnimation49Request;
    dst[24].operand3.storage = &_gAkropolisPatioFollowUpPlayerAnimation50Request;
    dst[27].operand3.storage = &_gAkropolisPatioSwatSlumpCommand;
    dst[31].operand0.storage = (void*)&_akropolisPatioSetPlayerHeadAimState;
    dst[32].operand0.storage = (void*)&_akropolisPatioEnterPostSwatState;
    dst[35].operand3.storage = &_gAkropolisPatioFollowUpPlayerEndPlacement;
    dst[36].operand3.storage = &_gAkropolisPatioRestoredSwatPlacement;
    dst[38].operand0.storage = (void*)&_akropolisPatioSetPlayerHeadAimState;
    dst[39].operand3.storage = &_gAkropolisPatioFollowUpPlayerAnimation52Request;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_patio/_gAkropolisPatioFollowUpScript", _gAkropolisPatioFollowUpScript, peDecodeArr_gAkropolisPatioFollowUpScript);
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
static EvsCommand _gAkropolisPatioFollowUpSkipScript[16];
static void peDecodeArr_gAkropolisPatioFollowUpSkipScript(void* base, const unsigned char* src, size_t n)
{
    EvsCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_EvsCommand(&dst[k], src + k * 24);
    dst[2].operand3.storage = &_gAkropolisPatioPlayerIdleAnimationRequest;
    dst[3].operand3.storage = &_gAkropolisPatioFollowUpPlayerEndPlacement;
    dst[4].operand0.storage = (void*)&_akropolisPatioEnterPostSwatState;
    dst[7].operand0.storage = (void*)&_akropolisPatioSetPlayerHeadAimState;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_patio/_gAkropolisPatioFollowUpSkipScript", _gAkropolisPatioFollowUpSkipScript, peDecodeArr_gAkropolisPatioFollowUpSkipScript);
static EvsSceneKey _gAkropolisPatioCafeteriaDoorSceneKey;
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_patio/_gAkropolisPatioCafeteriaDoorSceneKey", _gAkropolisPatioCafeteriaDoorSceneKey);
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
static EvsCommand _gAkropolisPatioCafeteriaDoorScript[10];
static void peDecodeArr_gAkropolisPatioCafeteriaDoorScript(void* base, const unsigned char* src, size_t n)
{
    EvsCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_EvsCommand(&dst[k], src + k * 24);
    dst[0].operand3.storage = &_gAkropolisPatioPlayerIdleAnimationRequest;
    dst[2].operand0.storage = &_gAkropolisPatioCafeteriaDoorSceneKey;
    dst[4].operand0.storage = (void*)&_akropolisPatioSetActorControl;
    dst[7].operand0.storage = (void*)&_akropolisPatioSetActorControl;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_patio/_gAkropolisPatioCafeteriaDoorScript", _gAkropolisPatioCafeteriaDoorScript, peDecodeArr_gAkropolisPatioCafeteriaDoorScript);
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
static EvsCommand _gAkropolisPatioCafeteriaDoorSkipScript[9];
static void peDecodeArr_gAkropolisPatioCafeteriaDoorSkipScript(void* base, const unsigned char* src, size_t n)
{
    EvsCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_EvsCommand(&dst[k], src + k * 24);
    dst[2].operand3.storage = &_gAkropolisPatioPlayerIdleAnimationRequest;
    dst[7].operand0.storage = (void*)&_akropolisPatioSetActorControl;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_patio/_gAkropolisPatioCafeteriaDoorSkipScript", _gAkropolisPatioCafeteriaDoorSkipScript, peDecodeArr_gAkropolisPatioCafeteriaDoorSkipScript);
