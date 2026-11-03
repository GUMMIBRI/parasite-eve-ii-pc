/* rooms/mist/parking/package: written from its room instance by tools/buildsteps/gen_room_inc.py. */

#include "gameplay/evs.h"
#include "gameplay/message.h"

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
static ActorCommand _gMistParkingShopPierceAimHeadCommand;
static void peDecodeArr_gMistParkingShopPierceAimHeadCommand(void* base, const unsigned char* src, size_t n)
{
    ActorCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_ActorCommand(&dst[k], src + k * 4);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_parking/_gMistParkingShopPierceAimHeadCommand", _gMistParkingShopPierceAimHeadCommand, peDecodeArr_gMistParkingShopPierceAimHeadCommand);
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
static ActorCommand _gMistParkingShopPierceReleaseHeadCommand;
static void peDecodeArr_gMistParkingShopPierceReleaseHeadCommand(void* base, const unsigned char* src, size_t n)
{
    ActorCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_ActorCommand(&dst[k], src + k * 4);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_parking/_gMistParkingShopPierceReleaseHeadCommand", _gMistParkingShopPierceReleaseHeadCommand, peDecodeArr_gMistParkingShopPierceReleaseHeadCommand);
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
static AnimationPlayRequest _gMistParkingUnusedBank0Clip1Animation;
static void peDecodeArr_gMistParkingUnusedBank0Clip1Animation(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_parking/_gMistParkingUnusedBank0Clip1Animation", _gMistParkingUnusedBank0Clip1Animation, peDecodeArr_gMistParkingUnusedBank0Clip1Animation);
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
AnimationPlayRequest gMistParkingJodieIdleAnimation;
static void peDecodeArr_gMistParkingJodieIdleAnimation(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_parking/gMistParkingJodieIdleAnimation", gMistParkingJodieIdleAnimation, peDecodeArr_gMistParkingJodieIdleAnimation);
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
static AnimationPlayRequest _gMistParkingUnusedBank0Clips2To4Animations[3];
static void peDecodeArr_gMistParkingUnusedBank0Clips2To4Animations(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_parking/_gMistParkingUnusedBank0Clips2To4Animations", _gMistParkingUnusedBank0Clips2To4Animations, peDecodeArr_gMistParkingUnusedBank0Clips2To4Animations);
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
AnimationPlayRequest gMistParkingJodieShopExitAnimation;
static void peDecodeArr_gMistParkingJodieShopExitAnimation(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_parking/gMistParkingJodieShopExitAnimation", gMistParkingJodieShopExitAnimation, peDecodeArr_gMistParkingJodieShopExitAnimation);
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
static AnimationPlayRequest _gMistParkingUnusedBank0Clip6Animation;
static void peDecodeArr_gMistParkingUnusedBank0Clip6Animation(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_parking/_gMistParkingUnusedBank0Clip6Animation", _gMistParkingUnusedBank0Clip6Animation, peDecodeArr_gMistParkingUnusedBank0Clip6Animation);
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
AnimationPlayRequest gMistParkingJodieGreetingAnimation;
static void peDecodeArr_gMistParkingJodieGreetingAnimation(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_parking/gMistParkingJodieGreetingAnimation", gMistParkingJodieGreetingAnimation, peDecodeArr_gMistParkingJodieGreetingAnimation);
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
AnimationPlayRequest gMistParkingJodieReplyAnimation;
static void peDecodeArr_gMistParkingJodieReplyAnimation(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_parking/gMistParkingJodieReplyAnimation", gMistParkingJodieReplyAnimation, peDecodeArr_gMistParkingJodieReplyAnimation);
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
AnimationPlayRequest gMistParkingJodieReplyEndAnimation;
static void peDecodeArr_gMistParkingJodieReplyEndAnimation(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_parking/gMistParkingJodieReplyEndAnimation", gMistParkingJodieReplyEndAnimation, peDecodeArr_gMistParkingJodieReplyEndAnimation);
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
static EvsCommand _gMistParkingShopDepartureMenuScript[10];
static void peDecodeArr_gMistParkingShopDepartureMenuScript(void* base, const unsigned char* src, size_t n)
{
    EvsCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_EvsCommand(&dst[k], src + k * 24);
    dst[0].operand0.storage = (void*)&_mistParkingStartShopPlayerHeadAim;
    dst[1].operand3.storage = &gMistParkingShopPlayerAnimationBankCopy;
    dst[2].operand3.storage = &_gMistParkingShopPierceAimHeadCommand;
    dst[5].operand3.storage = &_gMistParkingPlayerDepartureMenuAnimation;
    dst[6].operand3.storage = &_gMistParkingPierceDepartureMenuAnimation;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_parking/_gMistParkingShopDepartureMenuScript", _gMistParkingShopDepartureMenuScript, peDecodeArr_gMistParkingShopDepartureMenuScript);
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
static EvsCommand _gMistParkingShopStayScript[12];
static void peDecodeArr_gMistParkingShopStayScript(void* base, const unsigned char* src, size_t n)
{
    EvsCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_EvsCommand(&dst[k], src + k * 24);
    dst[0].operand3.storage = &gMistParkingShopPlayerAnimationBankCopy;
    dst[1].operand0.storage = (void*)&_mistParkingRunShopDialogueCommand;
    dst[2].operand3.storage = &_gMistParkingPlayerStayAnimation;
    dst[4].operand3.storage = &_gMistParkingShopPierceDepartureReplyAnimation;
    dst[6].operand0.storage = (void*)&_mistParkingControlShopPlayerHeadAim;
    dst[7].operand3.storage = &_gMistParkingPlayerStayAnimation;
    dst[8].operand3.storage = &_gMistParkingShopPierceReleaseHeadCommand;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_parking/_gMistParkingShopStayScript", _gMistParkingShopStayScript, peDecodeArr_gMistParkingShopStayScript);
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
static EvsCommand _gMistParkingShopDepartForAkropolisScript[18];
static void peDecodeArr_gMistParkingShopDepartForAkropolisScript(void* base, const unsigned char* src, size_t n)
{
    EvsCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_EvsCommand(&dst[k], src + k * 24);
    dst[0].operand3.storage = &gMistParkingShopPlayerAnimationBankCopy;
    dst[1].operand0.storage = (void*)&_mistParkingRunShopDialogueCommand;
    dst[3].operand3.storage = &_gMistParkingShopPierceDepartureReplyAnimation;
    dst[8].operand0.storage = (void*)&_mistParkingQueueDelayedShopDisplayModeExit;
    dst[12].operand0.storage = (void*)&_mistParkingSelectShopDialogueResource;
    dst[14].operand0.storage = (void*)&_mistParkingStartShopDepartureMovie;
    dst[16].operand0.storage = (void*)&_mistParkingQueueAkropolisDeparture;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_parking/_gMistParkingShopDepartForAkropolisScript", _gMistParkingShopDepartForAkropolisScript, peDecodeArr_gMistParkingShopDepartForAkropolisScript);
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
static EvsCommand _gMistParkingShopDepartForShootingGalleryScript[12];
static void peDecodeArr_gMistParkingShopDepartForShootingGalleryScript(void* base, const unsigned char* src, size_t n)
{
    EvsCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_EvsCommand(&dst[k], src + k * 24);
    dst[0].operand3.storage = &gMistParkingShopPlayerAnimationBankCopy;
    dst[1].operand0.storage = (void*)&_mistParkingRunShopDialogueCommand;
    dst[3].operand3.storage = &_gMistParkingShopPierceDepartureReplyAnimation;
    dst[8].operand0.storage = (void*)&_mistParkingQueueDelayedShopDisplayModeExit;
    dst[10].operand0.storage = (void*)&_mistParkingReloadShopAkropolisArea;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_parking/_gMistParkingShopDepartForShootingGalleryScript", _gMistParkingShopDepartForShootingGalleryScript, peDecodeArr_gMistParkingShopDepartForShootingGalleryScript);
