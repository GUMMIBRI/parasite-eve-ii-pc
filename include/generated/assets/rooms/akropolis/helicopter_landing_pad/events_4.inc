/* rooms/akropolis/helicopter_landing_pad/package: written from its room instance by tools/buildsteps/gen_room_inc.py. */

#include "gameplay/evs.h"
#include "gameplay/message.h"
#include "gameplay/scene_combat.h"
#include "main/gfx.h"

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
static AnimationBankCopyRequest _gAkropolisHelicopterLandingPadDeparturePlayerBankCopyRequest;
static void peDecodeArr_gAkropolisHelicopterLandingPadDeparturePlayerBankCopyRequest(void* base, const unsigned char* src, size_t n)
{
    AnimationBankCopyRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationBankCopyRequest(&dst[k], src + k * 8);
    dst[0].sets = (void*)&_gAkropolisHelicopterLandingPadDeparturePlayerAnimationSets;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_helicopter_landing_pad/_gAkropolisHelicopterLandingPadDeparturePlayerBankCopyRequest", _gAkropolisHelicopterLandingPadDeparturePlayerBankCopyRequest, peDecodeArr_gAkropolisHelicopterLandingPadDeparturePlayerBankCopyRequest);
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
static AnimationPlayRequest _gAkropolisHelicopterLandingPadUnusedAnimation2;
static void peDecodeArr_gAkropolisHelicopterLandingPadUnusedAnimation2(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_helicopter_landing_pad/_gAkropolisHelicopterLandingPadUnusedAnimation2", _gAkropolisHelicopterLandingPadUnusedAnimation2, peDecodeArr_gAkropolisHelicopterLandingPadUnusedAnimation2);
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
static AnimationPlayRequest _gAkropolisHelicopterLandingPadDeparturePlayerClip48Request;
static void peDecodeArr_gAkropolisHelicopterLandingPadDeparturePlayerClip48Request(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_helicopter_landing_pad/_gAkropolisHelicopterLandingPadDeparturePlayerClip48Request", _gAkropolisHelicopterLandingPadDeparturePlayerClip48Request, peDecodeArr_gAkropolisHelicopterLandingPadDeparturePlayerClip48Request);
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
static AnimationPlayRequest _gAkropolisHelicopterLandingPadDeparturePlayerClip49Request;
static void peDecodeArr_gAkropolisHelicopterLandingPadDeparturePlayerClip49Request(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_helicopter_landing_pad/_gAkropolisHelicopterLandingPadDeparturePlayerClip49Request", _gAkropolisHelicopterLandingPadDeparturePlayerClip49Request, peDecodeArr_gAkropolisHelicopterLandingPadDeparturePlayerClip49Request);
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
static AnimationPlayRequest _gAkropolisHelicopterLandingPadPlayerClip1Request;
static void peDecodeArr_gAkropolisHelicopterLandingPadPlayerClip1Request(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_helicopter_landing_pad/_gAkropolisHelicopterLandingPadPlayerClip1Request", _gAkropolisHelicopterLandingPadPlayerClip1Request, peDecodeArr_gAkropolisHelicopterLandingPadPlayerClip1Request);
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
static AnimationPlayRequest _gAkropolisHelicopterLandingPadPlayerClip9Request;
static void peDecodeArr_gAkropolisHelicopterLandingPadPlayerClip9Request(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_helicopter_landing_pad/_gAkropolisHelicopterLandingPadPlayerClip9Request", _gAkropolisHelicopterLandingPadPlayerClip9Request, peDecodeArr_gAkropolisHelicopterLandingPadPlayerClip9Request);
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
static AnimationPlayRequest _gAkropolisHelicopterLandingPadUnusedAnimation3;
static void peDecodeArr_gAkropolisHelicopterLandingPadUnusedAnimation3(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_helicopter_landing_pad/_gAkropolisHelicopterLandingPadUnusedAnimation3", _gAkropolisHelicopterLandingPadUnusedAnimation3, peDecodeArr_gAkropolisHelicopterLandingPadUnusedAnimation3);
static EvsSceneKey _gAkropolisHelicopterLandingPadEncounterIntroSceneKey;
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_helicopter_landing_pad/_gAkropolisHelicopterLandingPadEncounterIntroSceneKey", _gAkropolisHelicopterLandingPadEncounterIntroSceneKey);
static EvsSceneKey _gAkropolisHelicopterLandingPadEncounterEndingSceneKey;
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_helicopter_landing_pad/_gAkropolisHelicopterLandingPadEncounterEndingSceneKey", _gAkropolisHelicopterLandingPadEncounterEndingSceneKey);
static EvsSceneKey _gAkropolisHelicopterLandingPadDepartureSceneKey;
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_helicopter_landing_pad/_gAkropolisHelicopterLandingPadDepartureSceneKey", _gAkropolisHelicopterLandingPadDepartureSceneKey);
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
static AnimationPlayRequest _gAkropolisHelicopterLandingPadDepartureActorClip1Request;
static void peDecodeArr_gAkropolisHelicopterLandingPadDepartureActorClip1Request(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_helicopter_landing_pad/_gAkropolisHelicopterLandingPadDepartureActorClip1Request", _gAkropolisHelicopterLandingPadDepartureActorClip1Request, peDecodeArr_gAkropolisHelicopterLandingPadDepartureActorClip1Request);
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
static AnimationPlayRequest _gAkropolisHelicopterLandingPadDepartureActorClip2Request;
static void peDecodeArr_gAkropolisHelicopterLandingPadDepartureActorClip2Request(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_helicopter_landing_pad/_gAkropolisHelicopterLandingPadDepartureActorClip2Request", _gAkropolisHelicopterLandingPadDepartureActorClip2Request, peDecodeArr_gAkropolisHelicopterLandingPadDepartureActorClip2Request);
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
static AnimationPlayRequest _gAkropolisHelicopterLandingPadDepartureActorClip3Request;
static void peDecodeArr_gAkropolisHelicopterLandingPadDepartureActorClip3Request(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_helicopter_landing_pad/_gAkropolisHelicopterLandingPadDepartureActorClip3Request", _gAkropolisHelicopterLandingPadDepartureActorClip3Request, peDecodeArr_gAkropolisHelicopterLandingPadDepartureActorClip3Request);
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
static ActorCommand _gAkropolisHelicopterLandingPadUnusedActorCommand;
static void peDecodeArr_gAkropolisHelicopterLandingPadUnusedActorCommand(void* base, const unsigned char* src, size_t n)
{
    ActorCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_ActorCommand(&dst[k], src + k * 4);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_helicopter_landing_pad/_gAkropolisHelicopterLandingPadUnusedActorCommand", _gAkropolisHelicopterLandingPadUnusedActorCommand, peDecodeArr_gAkropolisHelicopterLandingPadUnusedActorCommand);
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
static ActorCommand _gAkropolisHelicopterLandingPadRupertShowPropCommand;
static void peDecodeArr_gAkropolisHelicopterLandingPadRupertShowPropCommand(void* base, const unsigned char* src, size_t n)
{
    ActorCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_ActorCommand(&dst[k], src + k * 4);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_helicopter_landing_pad/_gAkropolisHelicopterLandingPadRupertShowPropCommand", _gAkropolisHelicopterLandingPadRupertShowPropCommand, peDecodeArr_gAkropolisHelicopterLandingPadRupertShowPropCommand);
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
static AnimationPlayRequest _gAkropolisHelicopterLandingPadLiftLowerRequest;
static void peDecodeArr_gAkropolisHelicopterLandingPadLiftLowerRequest(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_helicopter_landing_pad/_gAkropolisHelicopterLandingPadLiftLowerRequest", _gAkropolisHelicopterLandingPadLiftLowerRequest, peDecodeArr_gAkropolisHelicopterLandingPadLiftLowerRequest);
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
static AnimationPlayRequest _gAkropolisHelicopterLandingPadLiftParkLowerRequest;
static void peDecodeArr_gAkropolisHelicopterLandingPadLiftParkLowerRequest(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_helicopter_landing_pad/_gAkropolisHelicopterLandingPadLiftParkLowerRequest", _gAkropolisHelicopterLandingPadLiftParkLowerRequest, peDecodeArr_gAkropolisHelicopterLandingPadLiftParkLowerRequest);
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
EvsCommand gAkropolisHelicopterLandingPadAmbientSoundScript[2];
static void peDecodeArr_gAkropolisHelicopterLandingPadAmbientSoundScript(void* base, const unsigned char* src, size_t n)
{
    EvsCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_EvsCommand(&dst[k], src + k * 24);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_helicopter_landing_pad/gAkropolisHelicopterLandingPadAmbientSoundScript", gAkropolisHelicopterLandingPadAmbientSoundScript, peDecodeArr_gAkropolisHelicopterLandingPadAmbientSoundScript);
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
EvsCommand gAkropolisHelicopterLandingPadEncounterIntroScript[58];
static void peDecodeArr_gAkropolisHelicopterLandingPadEncounterIntroScript(void* base, const unsigned char* src, size_t n)
{
    EvsCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_EvsCommand(&dst[k], src + k * 24);
    dst[5].operand0.storage = &_gAkropolisHelicopterLandingPadEncounterIntroSceneKey;
    dst[8].operand3.storage = &_gAkropolisHelicopterLandingPadSceneOriginPlacement;
    dst[9].operand3.storage = &_gAkropolisHelicopterLandingPadEncounterActorClip1Request;
    dst[11].operand0.storage = _gAkropolisHelicopterLandingPadEncounterVibrationCommands;
    dst[11].operand1.storage = _gAkropolisHelicopterLandingPadEncounterVibrationSegments;
    dst[13].operand3.storage = &_gAkropolisHelicopterLandingPadPlayerClip1Request;
    dst[16].operand3.storage = &_gAkropolisHelicopterLandingPadPlayerClip9Request;
    dst[17].operand0.storage = (void*)&akropolisHelicopterLandingPadStartPlayerYawTurn;
    dst[25].operand3.storage = &_gAkropolisHelicopterLandingPadEncounterActorClip2Request;
    dst[26].operand3.storage = &_gAkropolisHelicopterLandingPadEncounterPlayerTurnPlacement;
    dst[27].operand3.storage = &_gAkropolisHelicopterLandingPadPlayerClip9Request;
    dst[35].operand3.storage = &_gAkropolisHelicopterLandingPadEncounterActorClip3Request;
    dst[37].operand3.storage = &_gAkropolisHelicopterLandingPadEncounterActorClip4Request;
    dst[44].operand3.storage = &_gAkropolisHelicopterLandingPadEncounterActorClip5Request;
    dst[45].operand3.storage = &_gAkropolisHelicopterLandingPadEncounterPlayerPlacement;
    dst[48].operand0.storage = (void*)&sceneEngageBattle;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_helicopter_landing_pad/gAkropolisHelicopterLandingPadEncounterIntroScript", gAkropolisHelicopterLandingPadEncounterIntroScript, peDecodeArr_gAkropolisHelicopterLandingPadEncounterIntroScript);
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
EvsCommand gAkropolisHelicopterLandingPadEncounterIntroSkipScript[16];
static void peDecodeArr_gAkropolisHelicopterLandingPadEncounterIntroSkipScript(void* base, const unsigned char* src, size_t n)
{
    EvsCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_EvsCommand(&dst[k], src + k * 24);
    dst[7].operand3.storage = &_gAkropolisHelicopterLandingPadEncounterPlayerPlacement;
    dst[8].operand3.storage = &_gAkropolisHelicopterLandingPadPlayerClip9Request;
    dst[12].operand0.storage = (void*)&sceneEngageBattle;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_helicopter_landing_pad/gAkropolisHelicopterLandingPadEncounterIntroSkipScript", gAkropolisHelicopterLandingPadEncounterIntroSkipScript, peDecodeArr_gAkropolisHelicopterLandingPadEncounterIntroSkipScript);
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
EvsCommand gAkropolisHelicopterLandingPadEncounterEndingScript[38];
static void peDecodeArr_gAkropolisHelicopterLandingPadEncounterEndingScript(void* base, const unsigned char* src, size_t n)
{
    EvsCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_EvsCommand(&dst[k], src + k * 24);
    dst[0].operand3.storage = &_gAkropolisHelicopterLandingPadPlayerClip1Request;
    dst[4].operand0.storage = &_gAkropolisHelicopterLandingPadEncounterEndingSceneKey;
    dst[8].operand3.storage = &_gAkropolisHelicopterLandingPadEncounterEndingActorPlacement;
    dst[11].operand0.storage = (void*)&akropolisHelicopterLandingPadLockAttachmentsForEncounter;
    dst[13].operand3.storage = &_gAkropolisHelicopterLandingPadSceneOriginPlacement;
    dst[14].operand3.storage = &_gAkropolisHelicopterLandingPadEncounterActorClip6Request;
    dst[16].operand0.storage = (void*)&akropolisHelicopterLandingPadPlacePlayerAfterEncounter;
    dst[21].operand3.storage = &_gAkropolisHelicopterLandingPadLiftLowerRequest;
    dst[34].operand0.storage = (void*)&akropolisHelicopterLandingPadReleaseEncounterBattle;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_helicopter_landing_pad/gAkropolisHelicopterLandingPadEncounterEndingScript", gAkropolisHelicopterLandingPadEncounterEndingScript, peDecodeArr_gAkropolisHelicopterLandingPadEncounterEndingScript);
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
EvsCommand gAkropolisHelicopterLandingPadEncounterEndingSkipScript[19];
static void peDecodeArr_gAkropolisHelicopterLandingPadEncounterEndingSkipScript(void* base, const unsigned char* src, size_t n)
{
    EvsCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_EvsCommand(&dst[k], src + k * 24);
    dst[5].operand3.storage = &_gAkropolisHelicopterLandingPadPlayerClip1Request;
    dst[6].operand3.storage = &_gAkropolisHelicopterLandingPadLiftParkLowerRequest;
    dst[8].operand0.storage = (void*)&akropolisHelicopterLandingPadPlacePlayerAfterEncounter;
    dst[15].operand0.storage = (void*)&akropolisHelicopterLandingPadReleaseEncounterBattle;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_helicopter_landing_pad/gAkropolisHelicopterLandingPadEncounterEndingSkipScript", gAkropolisHelicopterLandingPadEncounterEndingSkipScript, peDecodeArr_gAkropolisHelicopterLandingPadEncounterEndingSkipScript);
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
EvsCommand gAkropolisHelicopterLandingPadDepartureScript[69];
static void peDecodeArr_gAkropolisHelicopterLandingPadDepartureScript(void* base, const unsigned char* src, size_t n)
{
    EvsCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_EvsCommand(&dst[k], src + k * 24);
    dst[0].operand3.storage = &_gAkropolisHelicopterLandingPadDeparturePlayerBankCopyRequest;
    dst[3].operand0.storage = &_gAkropolisHelicopterLandingPadDepartureSceneKey;
    dst[6].operand3.storage = &_gAkropolisHelicopterLandingPadPlayerClip9Request;
    dst[7].operand3.storage = (void*)&gGfxViewCoord;
    dst[8].operand3.storage = &_gAkropolisHelicopterLandingPadDeparturePlayerPlacement;
    dst[9].operand0.storage = (void*)&akropolisHelicopterLandingPadStartPlayerMoveToSceneMark;
    dst[10].operand3.storage = &_gAkropolisHelicopterLandingPadSceneOriginPlacement;
    dst[11].operand3.storage = &_gAkropolisHelicopterLandingPadDepartureActorClip1Request;
    dst[18].operand0.storage = (void*)&akropolisHelicopterLandingPadSetPlayerPitchPulseState;
    dst[20].operand0.storage = (void*)&akropolisHelicopterLandingPadSetPlayerPitchPulseState;
    dst[26].operand3.storage = &_gAkropolisHelicopterLandingPadDepartureActorClip2Request;
    dst[28].operand3.storage = &_gAkropolisHelicopterLandingPadDepartureActorClip3Request;
    dst[35].operand3.storage = &_gAkropolisHelicopterLandingPadSceneOriginPlacement;
    dst[36].operand3.storage = &_gAkropolisHelicopterLandingPadSceneOriginPlacement;
    dst[37].operand3.storage = &_gAkropolisHelicopterLandingPadDeparturePlayerClip48Request;
    dst[38].operand3.storage = &_gAkropolisHelicopterLandingPadRupertShowPropCommand;
    dst[39].operand3.storage = &_gAkropolisHelicopterLandingPadSceneOriginPlacement;
    dst[40].operand3.storage = &_gAkropolisHelicopterLandingPadRupertClip2Request;
    dst[43].operand3.storage = &_gAkropolisHelicopterLandingPadDeparturePlayerClip49Request;
    dst[44].operand3.storage = &_gAkropolisHelicopterLandingPadRupertClip3Request;
    dst[48].operand0.storage = (void*)&akropolisHelicopterLandingPadStartDepartureShakeTimeline;
    dst[66].operand0.storage = (void*)&akropolisHelicopterLandingPadStartReturnToMist;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_helicopter_landing_pad/gAkropolisHelicopterLandingPadDepartureScript", gAkropolisHelicopterLandingPadDepartureScript, peDecodeArr_gAkropolisHelicopterLandingPadDepartureScript);
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
EvsCommand gAkropolisHelicopterLandingPadDepartureSkipScript[7];
static void peDecodeArr_gAkropolisHelicopterLandingPadDepartureSkipScript(void* base, const unsigned char* src, size_t n)
{
    EvsCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_EvsCommand(&dst[k], src + k * 24);
    dst[5].operand0.storage = (void*)&akropolisHelicopterLandingPadStartReturnToMist;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_helicopter_landing_pad/gAkropolisHelicopterLandingPadDepartureSkipScript", gAkropolisHelicopterLandingPadDepartureSkipScript, peDecodeArr_gAkropolisHelicopterLandingPadDepartureSkipScript);
