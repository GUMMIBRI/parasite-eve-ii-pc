/* rooms/akropolis/roof_garden/package: written from its room instance by tools/buildsteps/gen_room_inc.py. */

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
static AnimationBankCopyRequest _gAkropolisRoofGardenArrivalPlayerBankCopy;
static void peDecodeArr_gAkropolisRoofGardenArrivalPlayerBankCopy(void* base, const unsigned char* src, size_t n)
{
    AnimationBankCopyRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationBankCopyRequest(&dst[k], src + k * 8);
    dst[0].sets = (void*)&_gAkropolisRoofGardenArrivalPlayerAnimationSets;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_roof_garden/_gAkropolisRoofGardenArrivalPlayerBankCopy", _gAkropolisRoofGardenArrivalPlayerBankCopy, peDecodeArr_gAkropolisRoofGardenArrivalPlayerBankCopy);
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
static AnimationPlayRequest _gAkropolisRoofGardenArrivalOpeningPlayerAnimation;
static void peDecodeArr_gAkropolisRoofGardenArrivalOpeningPlayerAnimation(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_roof_garden/_gAkropolisRoofGardenArrivalOpeningPlayerAnimation", _gAkropolisRoofGardenArrivalOpeningPlayerAnimation, peDecodeArr_gAkropolisRoofGardenArrivalOpeningPlayerAnimation);
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
static AnimationPlayRequest _gAkropolisRoofGardenArrivalClosingPlayerAnimation;
static void peDecodeArr_gAkropolisRoofGardenArrivalClosingPlayerAnimation(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_roof_garden/_gAkropolisRoofGardenArrivalClosingPlayerAnimation", _gAkropolisRoofGardenArrivalClosingPlayerAnimation, peDecodeArr_gAkropolisRoofGardenArrivalClosingPlayerAnimation);
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
static AnimationPlayRequest _gAkropolisRoofGardenArrivalDialoguePlayerAnimation;
static void peDecodeArr_gAkropolisRoofGardenArrivalDialoguePlayerAnimation(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_roof_garden/_gAkropolisRoofGardenArrivalDialoguePlayerAnimation", _gAkropolisRoofGardenArrivalDialoguePlayerAnimation, peDecodeArr_gAkropolisRoofGardenArrivalDialoguePlayerAnimation);
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
static AnimationPlayRequest _gAkropolisRoofGardenArrivalFigureAnimation1;
static void peDecodeArr_gAkropolisRoofGardenArrivalFigureAnimation1(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_roof_garden/_gAkropolisRoofGardenArrivalFigureAnimation1", _gAkropolisRoofGardenArrivalFigureAnimation1, peDecodeArr_gAkropolisRoofGardenArrivalFigureAnimation1);
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
static AnimationPlayRequest _gAkropolisRoofGardenArrivalFigureAnimation2;
static void peDecodeArr_gAkropolisRoofGardenArrivalFigureAnimation2(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_roof_garden/_gAkropolisRoofGardenArrivalFigureAnimation2", _gAkropolisRoofGardenArrivalFigureAnimation2, peDecodeArr_gAkropolisRoofGardenArrivalFigureAnimation2);
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
static AnimationPlayRequest _gAkropolisRoofGardenArrivalFigureAnimation3;
static void peDecodeArr_gAkropolisRoofGardenArrivalFigureAnimation3(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_roof_garden/_gAkropolisRoofGardenArrivalFigureAnimation3", _gAkropolisRoofGardenArrivalFigureAnimation3, peDecodeArr_gAkropolisRoofGardenArrivalFigureAnimation3);
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
static AnimationPlayRequest _gAkropolisRoofGardenArrivalFigureAnimation4;
static void peDecodeArr_gAkropolisRoofGardenArrivalFigureAnimation4(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_roof_garden/_gAkropolisRoofGardenArrivalFigureAnimation4", _gAkropolisRoofGardenArrivalFigureAnimation4, peDecodeArr_gAkropolisRoofGardenArrivalFigureAnimation4);
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
static AnimationPlayRequest _gAkropolisRoofGardenArrivalFigureAnimation5;
static void peDecodeArr_gAkropolisRoofGardenArrivalFigureAnimation5(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_roof_garden/_gAkropolisRoofGardenArrivalFigureAnimation5", _gAkropolisRoofGardenArrivalFigureAnimation5, peDecodeArr_gAkropolisRoofGardenArrivalFigureAnimation5);
static EvsSceneKey _gAkropolisRoofGardenUnusedSceneKey;
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_roof_garden/_gAkropolisRoofGardenUnusedSceneKey", _gAkropolisRoofGardenUnusedSceneKey);
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
static EvsCommand _gAkropolisRoofGardenArrivalScript[44];
static void peDecodeArr_gAkropolisRoofGardenArrivalScript(void* base, const unsigned char* src, size_t n)
{
    EvsCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_EvsCommand(&dst[k], src + k * 24);
    dst[3].operand3.storage = &_gAkropolisRoofGardenArrivalPlayerBankCopy;
    dst[4].operand3.storage = &_gAkropolisRoofGardenArrivalStartPlayerPlacement;
    dst[5].operand3.storage = &_gAkropolisRoofGardenArrivalOpeningPlayerAnimation;
    dst[6].operand0.storage = (void*)&_akropolisRoofGardenControlCutsceneSound;
    dst[10].operand3.storage = &_gAkropolisRoofGardenArrivalDialoguePlayerAnimation;
    dst[14].operand3.storage = &_gAkropolisRoofGardenArrivalFigurePlacement;
    dst[15].operand3.storage = &_gAkropolisRoofGardenArrivalFigureAnimation1;
    dst[17].operand3.storage = &_gAkropolisRoofGardenArrivalFigureAnimation2;
    dst[20].operand3.storage = &_gAkropolisRoofGardenArrivalFigureAnimation3;
    dst[22].operand3.storage = &_gAkropolisRoofGardenArrivalFigureAnimation4;
    dst[24].operand3.storage = &_gAkropolisRoofGardenArrivalFigureAnimation5;
    dst[34].operand3.storage = &_gAkropolisRoofGardenArrivalClosingPlayerAnimation;
    dst[35].operand0.storage = (void*)&_akropolisRoofGardenControlCutsceneSound;
    dst[38].operand3.storage = &_gAkropolisRoofGardenArrivalFinalPlayerAnimation;
    dst[41].operand3.storage = &_gAkropolisRoofGardenArrivalEndPlayerPlacement;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_roof_garden/_gAkropolisRoofGardenArrivalScript", _gAkropolisRoofGardenArrivalScript, peDecodeArr_gAkropolisRoofGardenArrivalScript);
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
static EvsCommand _gAkropolisRoofGardenArrivalSkipScript[17];
static void peDecodeArr_gAkropolisRoofGardenArrivalSkipScript(void* base, const unsigned char* src, size_t n)
{
    EvsCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_EvsCommand(&dst[k], src + k * 24);
    dst[4].operand3.storage = &_gAkropolisRoofGardenArrivalEndPlayerPlacement;
    dst[5].operand3.storage = &_gAkropolisRoofGardenArrivalFinalPlayerAnimation;
    dst[7].operand3.storage = &_gAkropolisRoofGardenArrivalFigureAnimation1;
    dst[9].operand0.storage = (void*)&_akropolisRoofGardenControlCutsceneSound;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_roof_garden/_gAkropolisRoofGardenArrivalSkipScript", _gAkropolisRoofGardenArrivalSkipScript, peDecodeArr_gAkropolisRoofGardenArrivalSkipScript);
