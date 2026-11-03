/* rooms/akropolis/plaza/package: written from its room instance by tools/buildsteps/gen_room_inc.py. */

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
static AnimationPlayRequest _gAkropolisPlazaPlayerShowBadgeRequest;
static void peDecodeArr_gAkropolisPlazaPlayerShowBadgeRequest(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_plaza/_gAkropolisPlazaPlayerShowBadgeRequest", _gAkropolisPlazaPlayerShowBadgeRequest, peDecodeArr_gAkropolisPlazaPlayerShowBadgeRequest);
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
static AnimationPlayRequest _gAkropolisPlazaSergeantIdleRequest;
static void peDecodeArr_gAkropolisPlazaSergeantIdleRequest(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_plaza/_gAkropolisPlazaSergeantIdleRequest", _gAkropolisPlazaSergeantIdleRequest, peDecodeArr_gAkropolisPlazaSergeantIdleRequest);
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
static AnimationPlayRequest _gAkropolisPlazaSergeantClearedForEntryRequest;
static void peDecodeArr_gAkropolisPlazaSergeantClearedForEntryRequest(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_plaza/_gAkropolisPlazaSergeantClearedForEntryRequest", _gAkropolisPlazaSergeantClearedForEntryRequest, peDecodeArr_gAkropolisPlazaSergeantClearedForEntryRequest);
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
static AnimationPlayRequest _gAkropolisPlazaSergeantSlot3Request;
static void peDecodeArr_gAkropolisPlazaSergeantSlot3Request(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_plaza/_gAkropolisPlazaSergeantSlot3Request", _gAkropolisPlazaSergeantSlot3Request, peDecodeArr_gAkropolisPlazaSergeantSlot3Request);
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
static AnimationPlayRequest _gAkropolisPlazaSergeantGoRightInRequest;
static void peDecodeArr_gAkropolisPlazaSergeantGoRightInRequest(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_plaza/_gAkropolisPlazaSergeantGoRightInRequest", _gAkropolisPlazaSergeantGoRightInRequest, peDecodeArr_gAkropolisPlazaSergeantGoRightInRequest);
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
static AnimationPlayRequest _gAkropolisPlazaPlayerTurnToSergeantRequest;
static void peDecodeArr_gAkropolisPlazaPlayerTurnToSergeantRequest(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_plaza/_gAkropolisPlazaPlayerTurnToSergeantRequest", _gAkropolisPlazaPlayerTurnToSergeantRequest, peDecodeArr_gAkropolisPlazaPlayerTurnToSergeantRequest);
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
static AnimationPlayRequest _gAkropolisPlazaPlayerAskSituationRequest;
static void peDecodeArr_gAkropolisPlazaPlayerAskSituationRequest(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_plaza/_gAkropolisPlazaPlayerAskSituationRequest", _gAkropolisPlazaPlayerAskSituationRequest, peDecodeArr_gAkropolisPlazaPlayerAskSituationRequest);
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
static AnimationPlayRequest _gAkropolisPlazaSergeantOuttaControlRequest;
static void peDecodeArr_gAkropolisPlazaSergeantOuttaControlRequest(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_plaza/_gAkropolisPlazaSergeantOuttaControlRequest", _gAkropolisPlazaSergeantOuttaControlRequest, peDecodeArr_gAkropolisPlazaSergeantOuttaControlRequest);
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
static AnimationPlayRequest _gAkropolisPlazaSergeantOuttaControlGestureRequest;
static void peDecodeArr_gAkropolisPlazaSergeantOuttaControlGestureRequest(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_plaza/_gAkropolisPlazaSergeantOuttaControlGestureRequest", _gAkropolisPlazaSergeantOuttaControlGestureRequest, peDecodeArr_gAkropolisPlazaSergeantOuttaControlGestureRequest);
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
static AnimationPlayRequest _gAkropolisPlazaSergeantHelicopterDownRequest;
static void peDecodeArr_gAkropolisPlazaSergeantHelicopterDownRequest(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_plaza/_gAkropolisPlazaSergeantHelicopterDownRequest", _gAkropolisPlazaSergeantHelicopterDownRequest, peDecodeArr_gAkropolisPlazaSergeantHelicopterDownRequest);
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
static AnimationPlayRequest _gAkropolisPlazaPlayerTurnFromSergeantRequest;
static void peDecodeArr_gAkropolisPlazaPlayerTurnFromSergeantRequest(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_plaza/_gAkropolisPlazaPlayerTurnFromSergeantRequest", _gAkropolisPlazaPlayerTurnFromSergeantRequest, peDecodeArr_gAkropolisPlazaPlayerTurnFromSergeantRequest);
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
static AnimationPlayRequest _gAkropolisPlazaSergeantScenePlayerPutAwayBadgeRequest;
static void peDecodeArr_gAkropolisPlazaSergeantScenePlayerPutAwayBadgeRequest(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_plaza/_gAkropolisPlazaSergeantScenePlayerPutAwayBadgeRequest", _gAkropolisPlazaSergeantScenePlayerPutAwayBadgeRequest, peDecodeArr_gAkropolisPlazaSergeantScenePlayerPutAwayBadgeRequest);
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
static AnimationPlayRequest _gAkropolisPlazaSergeantScenePlayerIdleRequest;
static void peDecodeArr_gAkropolisPlazaSergeantScenePlayerIdleRequest(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_plaza/_gAkropolisPlazaSergeantScenePlayerIdleRequest", _gAkropolisPlazaSergeantScenePlayerIdleRequest, peDecodeArr_gAkropolisPlazaSergeantScenePlayerIdleRequest);
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
static AnimationPlayRequest _gAkropolisPlazaPlayerIdleRequest;
static void peDecodeArr_gAkropolisPlazaPlayerIdleRequest(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_plaza/_gAkropolisPlazaPlayerIdleRequest", _gAkropolisPlazaPlayerIdleRequest, peDecodeArr_gAkropolisPlazaPlayerIdleRequest);
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
static EvsCommand _gAkropolisPlazaSergeantSceneScript[32];
static void peDecodeArr_gAkropolisPlazaSergeantSceneScript(void* base, const unsigned char* src, size_t n)
{
    EvsCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_EvsCommand(&dst[k], src + k * 24);
    dst[2].operand4.storage = &_gAkropolisPlazaSergeantIdleRequest;
    dst[4].operand3.storage = &_gAkropolisPlazaSergeantScenePlayerIdleRequest;
    dst[6].operand3.storage = &_gAkropolisPlazaPlayerShowBadgeRequest;
    dst[7].operand3.storage = &_gAkropolisPlazaSergeantIdleRequest;
    dst[9].operand3.storage = &_gAkropolisPlazaSergeantScenePlayerPutAwayBadgeRequest;
    dst[11].operand3.storage = &_gAkropolisPlazaSergeantClearedForEntryRequest;
    dst[13].operand3.storage = &_gAkropolisPlazaSergeantGoRightInRequest;
    dst[15].operand3.storage = &_gAkropolisPlazaPlayerTurnToSergeantRequest;
    dst[17].operand3.storage = &_gAkropolisPlazaPlayerAskSituationRequest;
    dst[19].operand3.storage = &_gAkropolisPlazaSergeantOuttaControlRequest;
    dst[20].operand3.storage = &_gAkropolisPlazaSergeantOuttaControlGestureRequest;
    dst[22].operand3.storage = &_gAkropolisPlazaSergeantHelicopterDownRequest;
    dst[24].operand3.storage = &_gAkropolisPlazaPlayerTurnFromSergeantRequest;
    dst[26].operand3.storage = &_gAkropolisPlazaPlayerIdleRequest;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_plaza/_gAkropolisPlazaSergeantSceneScript", _gAkropolisPlazaSergeantSceneScript, peDecodeArr_gAkropolisPlazaSergeantSceneScript);
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
static EvsCommand _gAkropolisPlazaSergeantSceneSkipScript[10];
static void peDecodeArr_gAkropolisPlazaSergeantSceneSkipScript(void* base, const unsigned char* src, size_t n)
{
    EvsCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_EvsCommand(&dst[k], src + k * 24);
    dst[3].operand3.storage = &_gAkropolisPlazaPlayerIdleRequest;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_plaza/_gAkropolisPlazaSergeantSceneSkipScript", _gAkropolisPlazaSergeantSceneSkipScript, peDecodeArr_gAkropolisPlazaSergeantSceneSkipScript);
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
static EvsCommand _gAkropolisPlazaHelicopterWreckScript[6];
static void peDecodeArr_gAkropolisPlazaHelicopterWreckScript(void* base, const unsigned char* src, size_t n)
{
    EvsCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_EvsCommand(&dst[k], src + k * 24);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_plaza/_gAkropolisPlazaHelicopterWreckScript", _gAkropolisPlazaHelicopterWreckScript, peDecodeArr_gAkropolisPlazaHelicopterWreckScript);
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
static AnimationPlayRequest _gAkropolisPlazaPlayerAskAboutRoofRequest;
static void peDecodeArr_gAkropolisPlazaPlayerAskAboutRoofRequest(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_plaza/_gAkropolisPlazaPlayerAskAboutRoofRequest", _gAkropolisPlazaPlayerAskAboutRoofRequest, peDecodeArr_gAkropolisPlazaPlayerAskAboutRoofRequest);
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
static AnimationPlayRequest _gAkropolisPlazaOfficerLookAtBadgeRequest;
static void peDecodeArr_gAkropolisPlazaOfficerLookAtBadgeRequest(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_plaza/_gAkropolisPlazaOfficerLookAtBadgeRequest", _gAkropolisPlazaOfficerLookAtBadgeRequest, peDecodeArr_gAkropolisPlazaOfficerLookAtBadgeRequest);
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
static AnimationPlayRequest _gAkropolisPlazaOfficerExplainSwatRequest;
static void peDecodeArr_gAkropolisPlazaOfficerExplainSwatRequest(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_plaza/_gAkropolisPlazaOfficerExplainSwatRequest", _gAkropolisPlazaOfficerExplainSwatRequest, peDecodeArr_gAkropolisPlazaOfficerExplainSwatRequest);
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
static AnimationPlayRequest _gAkropolisPlazaPlayerThankOfficerRequest;
static void peDecodeArr_gAkropolisPlazaPlayerThankOfficerRequest(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_plaza/_gAkropolisPlazaPlayerThankOfficerRequest", _gAkropolisPlazaPlayerThankOfficerRequest, peDecodeArr_gAkropolisPlazaPlayerThankOfficerRequest);
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
static AnimationPlayRequest _gAkropolisPlazaOfficerStepAsideRequest;
static void peDecodeArr_gAkropolisPlazaOfficerStepAsideRequest(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_plaza/_gAkropolisPlazaOfficerStepAsideRequest", _gAkropolisPlazaOfficerStepAsideRequest, peDecodeArr_gAkropolisPlazaOfficerStepAsideRequest);
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
static AnimationPlayRequest _gAkropolisPlazaPlayerAskAboutCiviliansRequest;
static void peDecodeArr_gAkropolisPlazaPlayerAskAboutCiviliansRequest(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_plaza/_gAkropolisPlazaPlayerAskAboutCiviliansRequest", _gAkropolisPlazaPlayerAskAboutCiviliansRequest, peDecodeArr_gAkropolisPlazaPlayerAskAboutCiviliansRequest);
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
static AnimationPlayRequest _gAkropolisPlazaOfficerScenePlayerIdleRequest;
static void peDecodeArr_gAkropolisPlazaOfficerScenePlayerIdleRequest(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_plaza/_gAkropolisPlazaOfficerScenePlayerIdleRequest", _gAkropolisPlazaOfficerScenePlayerIdleRequest, peDecodeArr_gAkropolisPlazaOfficerScenePlayerIdleRequest);
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
static AnimationPlayRequest _gAkropolisPlazaOfficerShiftStanceRequest;
static void peDecodeArr_gAkropolisPlazaOfficerShiftStanceRequest(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_plaza/_gAkropolisPlazaOfficerShiftStanceRequest", _gAkropolisPlazaOfficerShiftStanceRequest, peDecodeArr_gAkropolisPlazaOfficerShiftStanceRequest);
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
static AnimationPlayRequest _gAkropolisPlazaOfficerScenePlayerIdleBlendRequest;
static void peDecodeArr_gAkropolisPlazaOfficerScenePlayerIdleBlendRequest(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_plaza/_gAkropolisPlazaOfficerScenePlayerIdleBlendRequest", _gAkropolisPlazaOfficerScenePlayerIdleBlendRequest, peDecodeArr_gAkropolisPlazaOfficerScenePlayerIdleBlendRequest);
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
static AnimationPlayRequest _gAkropolisPlazaOfficerScenePlayerShowBadgeRequest;
static void peDecodeArr_gAkropolisPlazaOfficerScenePlayerShowBadgeRequest(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_plaza/_gAkropolisPlazaOfficerScenePlayerShowBadgeRequest", _gAkropolisPlazaOfficerScenePlayerShowBadgeRequest, peDecodeArr_gAkropolisPlazaOfficerScenePlayerShowBadgeRequest);
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
static AnimationPlayRequest _gAkropolisPlazaOfficerScenePlayerPutAwayBadgeRequest;
static void peDecodeArr_gAkropolisPlazaOfficerScenePlayerPutAwayBadgeRequest(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_plaza/_gAkropolisPlazaOfficerScenePlayerPutAwayBadgeRequest", _gAkropolisPlazaOfficerScenePlayerPutAwayBadgeRequest, peDecodeArr_gAkropolisPlazaOfficerScenePlayerPutAwayBadgeRequest);
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
static EvsCommand _gAkropolisPlazaEntranceOfficerTalkScript[27];
static void peDecodeArr_gAkropolisPlazaEntranceOfficerTalkScript(void* base, const unsigned char* src, size_t n)
{
    EvsCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_EvsCommand(&dst[k], src + k * 24);
    dst[2].operand4.storage = &_gAkropolisPlazaOfficerLookAtBadgeRequest;
    dst[4].operand3.storage = &_gAkropolisPlazaOfficerScenePlayerIdleRequest;
    dst[5].operand3.storage = &_gAkropolisPlazaOfficerShiftStanceRequest;
    dst[7].operand3.storage = &_gAkropolisPlazaOfficerScenePlayerShowBadgeRequest;
    dst[8].operand3.storage = &_gAkropolisPlazaOfficerLookAtBadgeRequest;
    dst[10].operand3.storage = &_gAkropolisPlazaOfficerScenePlayerPutAwayBadgeRequest;
    dst[12].operand3.storage = &_gAkropolisPlazaPlayerAskAboutRoofRequest;
    dst[14].operand3.storage = &_gAkropolisPlazaOfficerExplainSwatRequest;
    dst[16].operand3.storage = &_gAkropolisPlazaPlayerAskAboutCiviliansRequest;
    dst[19].operand3.storage = &_gAkropolisPlazaPlayerThankOfficerRequest;
    dst[20].operand3.storage = &_gAkropolisPlazaOfficerStepAsideRequest;
    dst[22].operand3.storage = &_gAkropolisPlazaOfficerScenePlayerIdleBlendRequest;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_plaza/_gAkropolisPlazaEntranceOfficerTalkScript", _gAkropolisPlazaEntranceOfficerTalkScript, peDecodeArr_gAkropolisPlazaEntranceOfficerTalkScript);
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
static EvsCommand _gAkropolisPlazaEntranceOfficerTalkSkipScript[6];
static void peDecodeArr_gAkropolisPlazaEntranceOfficerTalkSkipScript(void* base, const unsigned char* src, size_t n)
{
    EvsCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_EvsCommand(&dst[k], src + k * 24);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_plaza/_gAkropolisPlazaEntranceOfficerTalkSkipScript", _gAkropolisPlazaEntranceOfficerTalkSkipScript, peDecodeArr_gAkropolisPlazaEntranceOfficerTalkSkipScript);
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
static AnimationPlayRequest _gAkropolisPlazaOfficerWalkToSergeantRequest;
static void peDecodeArr_gAkropolisPlazaOfficerWalkToSergeantRequest(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_plaza/_gAkropolisPlazaOfficerWalkToSergeantRequest", _gAkropolisPlazaOfficerWalkToSergeantRequest, peDecodeArr_gAkropolisPlazaOfficerWalkToSergeantRequest);
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
static AnimationPlayRequest _gAkropolisPlazaOfficerHaltRequest;
static void peDecodeArr_gAkropolisPlazaOfficerHaltRequest(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_plaza/_gAkropolisPlazaOfficerHaltRequest", _gAkropolisPlazaOfficerHaltRequest, peDecodeArr_gAkropolisPlazaOfficerHaltRequest);
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
static AnimationPlayRequest _gAkropolisPlazaOfficerReportAgentRequest;
static void peDecodeArr_gAkropolisPlazaOfficerReportAgentRequest(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_plaza/_gAkropolisPlazaOfficerReportAgentRequest", _gAkropolisPlazaOfficerReportAgentRequest, peDecodeArr_gAkropolisPlazaOfficerReportAgentRequest);
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
static AnimationPlayRequest _gAkropolisPlazaOfficerAskSergeantRequest;
static void peDecodeArr_gAkropolisPlazaOfficerAskSergeantRequest(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_plaza/_gAkropolisPlazaOfficerAskSergeantRequest", _gAkropolisPlazaOfficerAskSergeantRequest, peDecodeArr_gAkropolisPlazaOfficerAskSergeantRequest);
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
static AnimationPlayRequest _gAkropolisPlazaOfficerTurnAwayRequest;
static void peDecodeArr_gAkropolisPlazaOfficerTurnAwayRequest(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_plaza/_gAkropolisPlazaOfficerTurnAwayRequest", _gAkropolisPlazaOfficerTurnAwayRequest, peDecodeArr_gAkropolisPlazaOfficerTurnAwayRequest);
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
static AnimationPlayRequest _gAkropolisPlazaSergeantRaiseArmRequest;
static void peDecodeArr_gAkropolisPlazaSergeantRaiseArmRequest(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_plaza/_gAkropolisPlazaSergeantRaiseArmRequest", _gAkropolisPlazaSergeantRaiseArmRequest, peDecodeArr_gAkropolisPlazaSergeantRaiseArmRequest);
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
static AnimationPlayRequest _gAkropolisPlazaSergeantLowerArmRequest;
static void peDecodeArr_gAkropolisPlazaSergeantLowerArmRequest(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_plaza/_gAkropolisPlazaSergeantLowerArmRequest", _gAkropolisPlazaSergeantLowerArmRequest, peDecodeArr_gAkropolisPlazaSergeantLowerArmRequest);
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
static AnimationPlayRequest _gAkropolisPlazaSergeantListenRequest;
static void peDecodeArr_gAkropolisPlazaSergeantListenRequest(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_plaza/_gAkropolisPlazaSergeantListenRequest", _gAkropolisPlazaSergeantListenRequest, peDecodeArr_gAkropolisPlazaSergeantListenRequest);
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
static AnimationPlayRequest _gAkropolisPlazaSergeantTurnHeadRequest;
static void peDecodeArr_gAkropolisPlazaSergeantTurnHeadRequest(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_plaza/_gAkropolisPlazaSergeantTurnHeadRequest", _gAkropolisPlazaSergeantTurnHeadRequest, peDecodeArr_gAkropolisPlazaSergeantTurnHeadRequest);
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
static AnimationPlayRequest _gAkropolisPlazaSergeantHunterFromMistRequest;
static void peDecodeArr_gAkropolisPlazaSergeantHunterFromMistRequest(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_plaza/_gAkropolisPlazaSergeantHunterFromMistRequest", _gAkropolisPlazaSergeantHunterFromMistRequest, peDecodeArr_gAkropolisPlazaSergeantHunterFromMistRequest);
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
static AnimationPlayRequest _gAkropolisPlazaSergeantHeardOfThemRequest;
static void peDecodeArr_gAkropolisPlazaSergeantHeardOfThemRequest(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_plaza/_gAkropolisPlazaSergeantHeardOfThemRequest", _gAkropolisPlazaSergeantHeardOfThemRequest, peDecodeArr_gAkropolisPlazaSergeantHeardOfThemRequest);
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
static AnimationPlayRequest _gAkropolisPlazaSergeantDamnRookiesRequest;
static void peDecodeArr_gAkropolisPlazaSergeantDamnRookiesRequest(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_plaza/_gAkropolisPlazaSergeantDamnRookiesRequest", _gAkropolisPlazaSergeantDamnRookiesRequest, peDecodeArr_gAkropolisPlazaSergeantDamnRookiesRequest);
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
static AnimationPlayRequest _gAkropolisPlazaSergeantTurnAwayRequest;
static void peDecodeArr_gAkropolisPlazaSergeantTurnAwayRequest(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_plaza/_gAkropolisPlazaSergeantTurnAwayRequest", _gAkropolisPlazaSergeantTurnAwayRequest, peDecodeArr_gAkropolisPlazaSergeantTurnAwayRequest);
static ActorTransform _gAkropolisPlazaOfficersTalkOfficerPlacement;
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_plaza/_gAkropolisPlazaOfficersTalkOfficerPlacement", _gAkropolisPlazaOfficersTalkOfficerPlacement);
static ActorTransform _gAkropolisPlazaOfficersTalkSergeantPlacement;
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_plaza/_gAkropolisPlazaOfficersTalkSergeantPlacement", _gAkropolisPlazaOfficersTalkSergeantPlacement);
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
static EvsCommand _gAkropolisPlazaOfficersTalkScript[41];
static void peDecodeArr_gAkropolisPlazaOfficersTalkScript(void* base, const unsigned char* src, size_t n)
{
    EvsCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_EvsCommand(&dst[k], src + k * 24);
    dst[5].operand4.storage = &_gAkropolisPlazaOfficerWalkToSergeantRequest;
    dst[7].operand4.storage = &_gAkropolisPlazaSergeantRaiseArmRequest;
    dst[10].operand3.storage = &_gAkropolisPlazaOfficersTalkOfficerPlacement;
    dst[11].operand3.storage = &_gAkropolisPlazaOfficersTalkSergeantPlacement;
    dst[12].operand3.storage = &_gAkropolisPlazaOfficerWalkToSergeantRequest;
    dst[13].operand3.storage = &_gAkropolisPlazaSergeantRaiseArmRequest;
    dst[15].operand3.storage = &_gAkropolisPlazaOfficerHaltRequest;
    dst[16].operand3.storage = &_gAkropolisPlazaSergeantLowerArmRequest;
    dst[18].operand3.storage = &_gAkropolisPlazaOfficerReportAgentRequest;
    dst[19].operand3.storage = &_gAkropolisPlazaSergeantListenRequest;
    dst[21].operand3.storage = &_gAkropolisPlazaSergeantTurnHeadRequest;
    dst[23].operand3.storage = &_gAkropolisPlazaSergeantHunterFromMistRequest;
    dst[25].operand3.storage = &_gAkropolisPlazaOfficerAskSergeantRequest;
    dst[26].operand3.storage = &_gAkropolisPlazaSergeantListenRequest;
    dst[28].operand3.storage = &_gAkropolisPlazaSergeantHeardOfThemRequest;
    dst[30].operand3.storage = &_gAkropolisPlazaOfficerAskSergeantRequest;
    dst[32].operand3.storage = &_gAkropolisPlazaSergeantDamnRookiesRequest;
    dst[34].operand3.storage = &_gAkropolisPlazaOfficerTurnAwayRequest;
    dst[35].operand3.storage = &_gAkropolisPlazaSergeantTurnAwayRequest;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_plaza/_gAkropolisPlazaOfficersTalkScript", _gAkropolisPlazaOfficersTalkScript, peDecodeArr_gAkropolisPlazaOfficersTalkScript);
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
static EvsCommand _gAkropolisPlazaOfficersTalkEndScript[5];
static void peDecodeArr_gAkropolisPlazaOfficersTalkEndScript(void* base, const unsigned char* src, size_t n)
{
    EvsCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_EvsCommand(&dst[k], src + k * 24);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_plaza/_gAkropolisPlazaOfficersTalkEndScript", _gAkropolisPlazaOfficersTalkEndScript, peDecodeArr_gAkropolisPlazaOfficersTalkEndScript);
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
static AnimationPlayRequest _gAkropolisPlazaSergeantSomethingBigRequest;
static void peDecodeArr_gAkropolisPlazaSergeantSomethingBigRequest(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_plaza/_gAkropolisPlazaSergeantSomethingBigRequest", _gAkropolisPlazaSergeantSomethingBigRequest, peDecodeArr_gAkropolisPlazaSergeantSomethingBigRequest);
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
static AnimationPlayRequest _gAkropolisPlazaSergeantWatchYourselfRequest;
static void peDecodeArr_gAkropolisPlazaSergeantWatchYourselfRequest(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_plaza/_gAkropolisPlazaSergeantWatchYourselfRequest", _gAkropolisPlazaSergeantWatchYourselfRequest, peDecodeArr_gAkropolisPlazaSergeantWatchYourselfRequest);
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
static EvsCommand _gAkropolisPlazaSergeantAgain1Script[11];
static void peDecodeArr_gAkropolisPlazaSergeantAgain1Script(void* base, const unsigned char* src, size_t n)
{
    EvsCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_EvsCommand(&dst[k], src + k * 24);
    dst[2].operand4.storage = &_gAkropolisPlazaSergeantSomethingBigRequest;
    dst[4].operand3.storage = &_gAkropolisPlazaPlayerIdleRequest;
    dst[5].operand3.storage = &_gAkropolisPlazaSergeantSomethingBigRequest;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_plaza/_gAkropolisPlazaSergeantAgain1Script", _gAkropolisPlazaSergeantAgain1Script, peDecodeArr_gAkropolisPlazaSergeantAgain1Script);
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
static EvsCommand _gAkropolisPlazaSergeantAgain2Script[11];
static void peDecodeArr_gAkropolisPlazaSergeantAgain2Script(void* base, const unsigned char* src, size_t n)
{
    EvsCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_EvsCommand(&dst[k], src + k * 24);
    dst[2].operand4.storage = &_gAkropolisPlazaSergeantWatchYourselfRequest;
    dst[4].operand3.storage = &_gAkropolisPlazaPlayerIdleRequest;
    dst[5].operand3.storage = &_gAkropolisPlazaSergeantWatchYourselfRequest;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_plaza/_gAkropolisPlazaSergeantAgain2Script", _gAkropolisPlazaSergeantAgain2Script, peDecodeArr_gAkropolisPlazaSergeantAgain2Script);
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
static EvsCommand _gAkropolisPlazaSergeantAgainLaterScript[8];
static void peDecodeArr_gAkropolisPlazaSergeantAgainLaterScript(void* base, const unsigned char* src, size_t n)
{
    EvsCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_EvsCommand(&dst[k], src + k * 24);
    dst[3].operand3.storage = &_gAkropolisPlazaPlayerIdleRequest;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_plaza/_gAkropolisPlazaSergeantAgainLaterScript", _gAkropolisPlazaSergeantAgainLaterScript, peDecodeArr_gAkropolisPlazaSergeantAgainLaterScript);
