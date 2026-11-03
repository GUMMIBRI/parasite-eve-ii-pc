/* rooms/akropolis/cafeteria/package: written from its room instance by tools/buildsteps/gen_room_inc.py. */

#include "gameplay/evs.h"
#include "gameplay/message.h"
#include "gameplay/scene_combat.h"

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
static AnimationBankCopyRequest _gAkropolisCafeteriaFollowUpPlayerBankCopy;
static void peDecodeArr_gAkropolisCafeteriaFollowUpPlayerBankCopy(void* base, const unsigned char* src, size_t n)
{
    AnimationBankCopyRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationBankCopyRequest(&dst[k], src + k * 8);
    dst[0].sets = (void*)&_gAkropolisCafeteriaFollowUpPlayerAnimationSets;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_cafeteria/_gAkropolisCafeteriaFollowUpPlayerBankCopy", _gAkropolisCafeteriaFollowUpPlayerBankCopy, peDecodeArr_gAkropolisCafeteriaFollowUpPlayerBankCopy);
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
static AnimationPlayRequest _gAkropolisCafeteriaPlayerFollowUpAnimation47;
static void peDecodeArr_gAkropolisCafeteriaPlayerFollowUpAnimation47(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_cafeteria/_gAkropolisCafeteriaPlayerFollowUpAnimation47", _gAkropolisCafeteriaPlayerFollowUpAnimation47, peDecodeArr_gAkropolisCafeteriaPlayerFollowUpAnimation47);
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
static AnimationPlayRequest _gAkropolisCafeteriaPlayerFollowUpAnimation48;
static void peDecodeArr_gAkropolisCafeteriaPlayerFollowUpAnimation48(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_cafeteria/_gAkropolisCafeteriaPlayerFollowUpAnimation48", _gAkropolisCafeteriaPlayerFollowUpAnimation48, peDecodeArr_gAkropolisCafeteriaPlayerFollowUpAnimation48);
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
static AnimationPlayRequest _gAkropolisCafeteriaPlayerFollowUpAnimation49;
static void peDecodeArr_gAkropolisCafeteriaPlayerFollowUpAnimation49(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_cafeteria/_gAkropolisCafeteriaPlayerFollowUpAnimation49", _gAkropolisCafeteriaPlayerFollowUpAnimation49, peDecodeArr_gAkropolisCafeteriaPlayerFollowUpAnimation49);
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
static AnimationPlayRequest _gAkropolisCafeteriaPlayerFollowUpAnimation50;
static void peDecodeArr_gAkropolisCafeteriaPlayerFollowUpAnimation50(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_cafeteria/_gAkropolisCafeteriaPlayerFollowUpAnimation50", _gAkropolisCafeteriaPlayerFollowUpAnimation50, peDecodeArr_gAkropolisCafeteriaPlayerFollowUpAnimation50);
static ActorTransform _gAkropolisCafeteriaStrangerBattleIntroPlacement;
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_cafeteria/_gAkropolisCafeteriaStrangerBattleIntroPlacement", _gAkropolisCafeteriaStrangerBattleIntroPlacement);
static ActorTransform _gAkropolisCafeteriaStrangerPostBattlePlacement;
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_cafeteria/_gAkropolisCafeteriaStrangerPostBattlePlacement", _gAkropolisCafeteriaStrangerPostBattlePlacement);
static ActorTransform _gAkropolisCafeteriaStrangerFollowUpStartPlacement;
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_cafeteria/_gAkropolisCafeteriaStrangerFollowUpStartPlacement", _gAkropolisCafeteriaStrangerFollowUpStartPlacement);
static ActorTransform _gAkropolisCafeteriaStrangerFollowUpAnimation48Placement;
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_cafeteria/_gAkropolisCafeteriaStrangerFollowUpAnimation48Placement", _gAkropolisCafeteriaStrangerFollowUpAnimation48Placement);
static ActorTransform _gAkropolisCafeteriaStrangerRecoilPlacement;
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_cafeteria/_gAkropolisCafeteriaStrangerRecoilPlacement", _gAkropolisCafeteriaStrangerRecoilPlacement);
static ActorTransform _gAkropolisCafeteriaStrangerFollowUpPlacement;
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_cafeteria/_gAkropolisCafeteriaStrangerFollowUpPlacement", _gAkropolisCafeteriaStrangerFollowUpPlacement);
static ActorTransform _gAkropolisCafeteriaStrangerFollowUpBurnPlacement;
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_cafeteria/_gAkropolisCafeteriaStrangerFollowUpBurnPlacement", _gAkropolisCafeteriaStrangerFollowUpBurnPlacement);
static ActorTransform _gAkropolisCafeteriaStrangerBattleStartPlacement;
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_cafeteria/_gAkropolisCafeteriaStrangerBattleStartPlacement", _gAkropolisCafeteriaStrangerBattleStartPlacement);
static ActorTransform _gAkropolisCafeteriaGrinningStrangerScenePlacement;
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_cafeteria/_gAkropolisCafeteriaGrinningStrangerScenePlacement", _gAkropolisCafeteriaGrinningStrangerScenePlacement);
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
static ActorCommand _gAkropolisCafeteriaUnusedActorCommand;
static void peDecodeArr_gAkropolisCafeteriaUnusedActorCommand(void* base, const unsigned char* src, size_t n)
{
    ActorCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_ActorCommand(&dst[k], src + k * 4);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_cafeteria/_gAkropolisCafeteriaUnusedActorCommand", _gAkropolisCafeteriaUnusedActorCommand, peDecodeArr_gAkropolisCafeteriaUnusedActorCommand);
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
static ActorCommand _gAkropolisCafeteriaStrangerStartCommand;
static void peDecodeArr_gAkropolisCafeteriaStrangerStartCommand(void* base, const unsigned char* src, size_t n)
{
    ActorCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_ActorCommand(&dst[k], src + k * 4);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_cafeteria/_gAkropolisCafeteriaStrangerStartCommand", _gAkropolisCafeteriaStrangerStartCommand, peDecodeArr_gAkropolisCafeteriaStrangerStartCommand);
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
static ActorCommand _gAkropolisCafeteriaStrangerPostBattleCommand;
static void peDecodeArr_gAkropolisCafeteriaStrangerPostBattleCommand(void* base, const unsigned char* src, size_t n)
{
    ActorCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_ActorCommand(&dst[k], src + k * 4);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_cafeteria/_gAkropolisCafeteriaStrangerPostBattleCommand", _gAkropolisCafeteriaStrangerPostBattleCommand, peDecodeArr_gAkropolisCafeteriaStrangerPostBattleCommand);
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
static ActorCommand _gAkropolisCafeteriaStrangerFollowUpTripleHitCommand;
static void peDecodeArr_gAkropolisCafeteriaStrangerFollowUpTripleHitCommand(void* base, const unsigned char* src, size_t n)
{
    ActorCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_ActorCommand(&dst[k], src + k * 4);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_cafeteria/_gAkropolisCafeteriaStrangerFollowUpTripleHitCommand", _gAkropolisCafeteriaStrangerFollowUpTripleHitCommand, peDecodeArr_gAkropolisCafeteriaStrangerFollowUpTripleHitCommand);
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
static ActorCommand _gAkropolisCafeteriaStrangerRecoilCommand;
static void peDecodeArr_gAkropolisCafeteriaStrangerRecoilCommand(void* base, const unsigned char* src, size_t n)
{
    ActorCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_ActorCommand(&dst[k], src + k * 4);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_cafeteria/_gAkropolisCafeteriaStrangerRecoilCommand", _gAkropolisCafeteriaStrangerRecoilCommand, peDecodeArr_gAkropolisCafeteriaStrangerRecoilCommand);
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
static ActorCommand _gAkropolisCafeteriaStrangerFollowUpCommand;
static void peDecodeArr_gAkropolisCafeteriaStrangerFollowUpCommand(void* base, const unsigned char* src, size_t n)
{
    ActorCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_ActorCommand(&dst[k], src + k * 4);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_cafeteria/_gAkropolisCafeteriaStrangerFollowUpCommand", _gAkropolisCafeteriaStrangerFollowUpCommand, peDecodeArr_gAkropolisCafeteriaStrangerFollowUpCommand);
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
static ActorCommand _gAkropolisCafeteriaStrangerSettleCommand;
static void peDecodeArr_gAkropolisCafeteriaStrangerSettleCommand(void* base, const unsigned char* src, size_t n)
{
    ActorCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_ActorCommand(&dst[k], src + k * 4);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_cafeteria/_gAkropolisCafeteriaStrangerSettleCommand", _gAkropolisCafeteriaStrangerSettleCommand, peDecodeArr_gAkropolisCafeteriaStrangerSettleCommand);
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
static ActorCommand _gAkropolisCafeteriaStrangerFollowUpBurnCommand;
static void peDecodeArr_gAkropolisCafeteriaStrangerFollowUpBurnCommand(void* base, const unsigned char* src, size_t n)
{
    ActorCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_ActorCommand(&dst[k], src + k * 4);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_cafeteria/_gAkropolisCafeteriaStrangerFollowUpBurnCommand", _gAkropolisCafeteriaStrangerFollowUpBurnCommand, peDecodeArr_gAkropolisCafeteriaStrangerFollowUpBurnCommand);
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
static ActorCommand _gAkropolisCafeteriaStrangerFollowUpClipCommand;
static void peDecodeArr_gAkropolisCafeteriaStrangerFollowUpClipCommand(void* base, const unsigned char* src, size_t n)
{
    ActorCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_ActorCommand(&dst[k], src + k * 4);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_cafeteria/_gAkropolisCafeteriaStrangerFollowUpClipCommand", _gAkropolisCafeteriaStrangerFollowUpClipCommand, peDecodeArr_gAkropolisCafeteriaStrangerFollowUpClipCommand);
static ActorTransform _gAkropolisCafeteriaRupertArrivalPlacement;
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_cafeteria/_gAkropolisCafeteriaRupertArrivalPlacement", _gAkropolisCafeteriaRupertArrivalPlacement);
static ActorTransform _gAkropolisCafeteriaRupertConversationPlacement;
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_cafeteria/_gAkropolisCafeteriaRupertConversationPlacement", _gAkropolisCafeteriaRupertConversationPlacement);
static ActorTransform _gAkropolisCafeteriaRupertDeparturePlacement;
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_cafeteria/_gAkropolisCafeteriaRupertDeparturePlacement", _gAkropolisCafeteriaRupertDeparturePlacement);
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
static AnimationPlayRequest _gAkropolisCafeteriaRupertShootingAnimation1;
static void peDecodeArr_gAkropolisCafeteriaRupertShootingAnimation1(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_cafeteria/_gAkropolisCafeteriaRupertShootingAnimation1", _gAkropolisCafeteriaRupertShootingAnimation1, peDecodeArr_gAkropolisCafeteriaRupertShootingAnimation1);
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
static AnimationPlayRequest _gAkropolisCafeteriaRupertArrivalAnimation2;
static void peDecodeArr_gAkropolisCafeteriaRupertArrivalAnimation2(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_cafeteria/_gAkropolisCafeteriaRupertArrivalAnimation2", _gAkropolisCafeteriaRupertArrivalAnimation2, peDecodeArr_gAkropolisCafeteriaRupertArrivalAnimation2);
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
static AnimationPlayRequest _gAkropolisCafeteriaRupertReloadAnimation3;
static void peDecodeArr_gAkropolisCafeteriaRupertReloadAnimation3(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_cafeteria/_gAkropolisCafeteriaRupertReloadAnimation3", _gAkropolisCafeteriaRupertReloadAnimation3, peDecodeArr_gAkropolisCafeteriaRupertReloadAnimation3);
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
static AnimationPlayRequest _gAkropolisCafeteriaRupertDepartureAnimation4;
static void peDecodeArr_gAkropolisCafeteriaRupertDepartureAnimation4(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_cafeteria/_gAkropolisCafeteriaRupertDepartureAnimation4", _gAkropolisCafeteriaRupertDepartureAnimation4, peDecodeArr_gAkropolisCafeteriaRupertDepartureAnimation4);
static EvsSceneKey _gAkropolisCafeteriaUnusedSceneKey;
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_cafeteria/_gAkropolisCafeteriaUnusedSceneKey", _gAkropolisCafeteriaUnusedSceneKey);
static EvsSceneKey _gAkropolisCafeteriaFollowUpSceneKey;
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_cafeteria/_gAkropolisCafeteriaFollowUpSceneKey", _gAkropolisCafeteriaFollowUpSceneKey);
static GameActorMoveAnim _gAkropolisCafeteriaPlayerFollowUpWalkAnimations;
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_cafeteria/_gAkropolisCafeteriaPlayerFollowUpWalkAnimations", _gAkropolisCafeteriaPlayerFollowUpWalkAnimations);
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
static EvsCommand _gAkropolisCafeteriaOpeningSceneScript[35];
static void peDecodeArr_gAkropolisCafeteriaOpeningSceneScript(void* base, const unsigned char* src, size_t n)
{
    EvsCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_EvsCommand(&dst[k], src + k * 24);
    dst[0].operand0.storage = (void*)&_akropolisCafeteriaCancelPeEffects;
    dst[2].operand3.storage = &_gAkropolisCafeteriaOpeningPlayerBankCopy;
    dst[8].operand3.storage = &_gAkropolisCafeteriaOpeningWomanAnimation1;
    dst[10].operand3.storage = &_gAkropolisCafeteriaPlayerOpeningAnimation47;
    dst[12].operand3.storage = &_gAkropolisCafeteriaPlayerOpeningScenePlacement;
    dst[14].operand0.storage = (void*)&_akropolisCafeteriaSetPlayerSurface;
    dst[24].operand3.storage = &_gAkropolisCafeteriaPlayerAnimation1;
    dst[30].operand3.storage = &_gAkropolisCafeteriaPlayerAnimation1;
    dst[33].operand3.storage = &_gAkropolisCafeteriaPlayerOpeningResumePlacement;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_cafeteria/_gAkropolisCafeteriaOpeningSceneScript", _gAkropolisCafeteriaOpeningSceneScript, peDecodeArr_gAkropolisCafeteriaOpeningSceneScript);
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
static EvsCommand _gAkropolisCafeteriaOpeningSceneSkipScript[14];
static void peDecodeArr_gAkropolisCafeteriaOpeningSceneSkipScript(void* base, const unsigned char* src, size_t n)
{
    EvsCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_EvsCommand(&dst[k], src + k * 24);
    dst[3].operand3.storage = &_gAkropolisCafeteriaPlayerAnimation1;
    dst[8].operand3.storage = &_gAkropolisCafeteriaPlayerAnimation1;
    dst[10].operand3.storage = &_gAkropolisCafeteriaPlayerOpeningResumePlacement;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_cafeteria/_gAkropolisCafeteriaOpeningSceneSkipScript", _gAkropolisCafeteriaOpeningSceneSkipScript, peDecodeArr_gAkropolisCafeteriaOpeningSceneSkipScript);
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
static EvsCommand _gAkropolisCafeteriaPostBattleSceneScript[19];
static void peDecodeArr_gAkropolisCafeteriaPostBattleSceneScript(void* base, const unsigned char* src, size_t n)
{
    EvsCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_EvsCommand(&dst[k], src + k * 24);
    dst[0].operand0.storage = (void*)&_akropolisCafeteriaPreparePostBattleScene;
    dst[1].operand3.storage = &_gAkropolisCafeteriaPlayerPostBattleAnimation9;
    dst[5].operand0.storage = (void*)&_akropolisCafeteriaCopyPostBattleVram;
    dst[7].operand3.storage = &_gAkropolisCafeteriaStrangerPostBattlePlacement;
    dst[8].operand3.storage = &_gAkropolisCafeteriaStrangerPostBattleCommand;
    dst[17].operand3.storage = &_gAkropolisCafeteriaPlayerPostBattleAnimation8;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_cafeteria/_gAkropolisCafeteriaPostBattleSceneScript", _gAkropolisCafeteriaPostBattleSceneScript, peDecodeArr_gAkropolisCafeteriaPostBattleSceneScript);
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
static EvsCommand _gAkropolisCafeteriaPostBattleSceneSkipScript[15];
static void peDecodeArr_gAkropolisCafeteriaPostBattleSceneSkipScript(void* base, const unsigned char* src, size_t n)
{
    EvsCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_EvsCommand(&dst[k], src + k * 24);
    dst[4].operand3.storage = &_gAkropolisCafeteriaStrangerRecoilCommand;
    dst[5].operand0.storage = (void*)&_akropolisCafeteriaCopyPostBattleVram;
    dst[6].operand3.storage = &_gAkropolisCafeteriaStrangerPostBattlePlacement;
    dst[13].operand3.storage = &_gAkropolisCafeteriaPlayerPostBattleAnimation8;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_cafeteria/_gAkropolisCafeteriaPostBattleSceneSkipScript", _gAkropolisCafeteriaPostBattleSceneSkipScript, peDecodeArr_gAkropolisCafeteriaPostBattleSceneSkipScript);
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
static EvsCommand _gAkropolisCafeteriaFollowUpSceneScript[80];
static void peDecodeArr_gAkropolisCafeteriaFollowUpSceneScript(void* base, const unsigned char* src, size_t n)
{
    EvsCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_EvsCommand(&dst[k], src + k * 24);
    dst[0].operand0.storage = &_gAkropolisCafeteriaFollowUpSceneKey;
    dst[7].operand3.storage = &_gAkropolisCafeteriaStrangerFollowUpStartPlacement;
    dst[8].operand3.storage = &_gAkropolisCafeteriaFollowUpPlayerBankCopy;
    dst[9].operand3.storage = &_gAkropolisCafeteriaPlayerFollowUpStartPlacement;
    dst[10].operand3.storage = &_gAkropolisCafeteriaPlayerFollowUpAnimation47;
    dst[12].operand3.storage = &_gAkropolisCafeteriaStrangerFollowUpClipCommand;
    dst[17].operand3.storage = &_gAkropolisCafeteriaStrangerRecoilCommand;
    dst[19].operand3.storage = &_gAkropolisCafeteriaPlayerBeforeRupertArrivalPlacement;
    dst[20].operand3.storage = &_gAkropolisCafeteriaStrangerFollowUpPlacement;
    dst[21].operand3.storage = &_gAkropolisCafeteriaStrangerFollowUpCommand;
    dst[25].operand3.storage = &_gAkropolisCafeteriaRupertArrivalPlacement;
    dst[26].operand3.storage = &_gAkropolisCafeteriaRupertArrivalAnimation2;
    dst[31].operand3.storage = &_gAkropolisCafeteriaStrangerFollowUpAnimation48Placement;
    dst[32].operand3.storage = &_gAkropolisCafeteriaStrangerFollowUpTripleHitCommand;
    dst[33].operand3.storage = &_gAkropolisCafeteriaPlayerFollowUpAnimation48;
    dst[36].operand3.storage = &_gAkropolisCafeteriaStrangerRecoilPlacement;
    dst[37].operand3.storage = &_gAkropolisCafeteriaRupertConversationPlacement;
    dst[38].operand3.storage = &_gAkropolisCafeteriaStrangerFollowUpClipCommand;
    dst[39].operand3.storage = &_gAkropolisCafeteriaRupertShootingAnimation1;
    dst[40].operand3.storage = &_gAkropolisCafeteriaPlayerFollowUpWalkStartPlacement;
    dst[44].operand3.storage = &_gAkropolisCafeteriaPlayerFollowUpWalkTarget;
    dst[44].operand4.storage = &_gAkropolisCafeteriaPlayerFollowUpWalkAnimations;
    dst[48].operand3.storage = &_gAkropolisCafeteriaPlayerFollowUpWalkTarget;
    dst[50].operand3.storage = &_gAkropolisCafeteriaPlayerAnimation1;
    dst[52].operand3.storage = &_gAkropolisCafeteriaStrangerFollowUpBurnPlacement;
    dst[53].operand3.storage = &_gAkropolisCafeteriaStrangerFollowUpBurnCommand;
    dst[54].operand3.storage = &_gAkropolisCafeteriaRupertConversationPlacement;
    dst[55].operand3.storage = &_gAkropolisCafeteriaRupertReloadAnimation3;
    dst[56].operand3.storage = &_gAkropolisCafeteriaRupertConversationPlacement;
    dst[57].operand3.storage = &_gAkropolisCafeteriaPlayerFollowUpAnimation49;
    dst[62].operand3.storage = &_gAkropolisCafeteriaGrinningStrangerScenePlacement;
    dst[63].operand3.storage = &_gAkropolisCafeteriaStrangerStartCommand;
    dst[66].operand3.storage = &_gAkropolisCafeteriaRupertDeparturePlacement;
    dst[67].operand3.storage = &_gAkropolisCafeteriaRupertDepartureAnimation4;
    dst[68].operand3.storage = &_gAkropolisCafeteriaRupertDeparturePlacement;
    dst[69].operand3.storage = &_gAkropolisCafeteriaPlayerFollowUpAnimation50;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_cafeteria/_gAkropolisCafeteriaFollowUpSceneScript", _gAkropolisCafeteriaFollowUpSceneScript, peDecodeArr_gAkropolisCafeteriaFollowUpSceneScript);
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
static EvsCommand _gAkropolisCafeteriaFollowUpSceneSkipScript[10];
static void peDecodeArr_gAkropolisCafeteriaFollowUpSceneSkipScript(void* base, const unsigned char* src, size_t n)
{
    EvsCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_EvsCommand(&dst[k], src + k * 24);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_cafeteria/_gAkropolisCafeteriaFollowUpSceneSkipScript", _gAkropolisCafeteriaFollowUpSceneSkipScript, peDecodeArr_gAkropolisCafeteriaFollowUpSceneSkipScript);
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
static EvsCommand _gAkropolisCafeteriaCap13ShakeScript[6];
static void peDecodeArr_gAkropolisCafeteriaCap13ShakeScript(void* base, const unsigned char* src, size_t n)
{
    EvsCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_EvsCommand(&dst[k], src + k * 24);
    dst[2].operand3.storage = &_gAkropolisCafeteriaPlayerAnimation1;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_cafeteria/_gAkropolisCafeteriaCap13ShakeScript", _gAkropolisCafeteriaCap13ShakeScript, peDecodeArr_gAkropolisCafeteriaCap13ShakeScript);
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
static EvsCommand _gAkropolisCafeteriaBattleIntroScript[19];
static void peDecodeArr_gAkropolisCafeteriaBattleIntroScript(void* base, const unsigned char* src, size_t n)
{
    EvsCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_EvsCommand(&dst[k], src + k * 24);
    dst[0].operand3.storage = &_gAkropolisCafeteriaPlayerAnimation1;
    dst[3].operand3.storage = &_gAkropolisCafeteriaStrangerBattleIntroPlacement;
    dst[5].operand3.storage = &_gAkropolisCafeteriaStrangerStartCommand;
    dst[8].operand0.storage = (void*)&SetDispMask;
    dst[10].operand0.storage = (void*)&sceneEngageBattle;
    dst[12].operand3.storage = &_gAkropolisCafeteriaPlayerBattleStartPlacement;
    dst[13].operand3.storage = &_gAkropolisCafeteriaStrangerBattleStartPlacement;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_cafeteria/_gAkropolisCafeteriaBattleIntroScript", _gAkropolisCafeteriaBattleIntroScript, peDecodeArr_gAkropolisCafeteriaBattleIntroScript);
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
static EvsCommand _gAkropolisCafeteriaGrinningStrangerAppearanceScript[4];
static void peDecodeArr_gAkropolisCafeteriaGrinningStrangerAppearanceScript(void* base, const unsigned char* src, size_t n)
{
    EvsCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_EvsCommand(&dst[k], src + k * 24);
    dst[1].operand3.storage = &_gAkropolisCafeteriaGrinningStrangerScenePlacement;
    dst[2].operand3.storage = &_gAkropolisCafeteriaStrangerStartCommand;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_cafeteria/_gAkropolisCafeteriaGrinningStrangerAppearanceScript", _gAkropolisCafeteriaGrinningStrangerAppearanceScript, peDecodeArr_gAkropolisCafeteriaGrinningStrangerAppearanceScript);
