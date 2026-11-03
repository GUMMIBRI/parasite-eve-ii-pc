/* rooms/akropolis/bridge/package: written from its room instance by tools/buildsteps/gen_room_inc.py. */

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
static AnimationPlayRequest _gAkropolisBridgeArrivalWeaponAnimationRequest;
static void peDecodeArr_gAkropolisBridgeArrivalWeaponAnimationRequest(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_bridge/_gAkropolisBridgeArrivalWeaponAnimationRequest", _gAkropolisBridgeArrivalWeaponAnimationRequest, peDecodeArr_gAkropolisBridgeArrivalWeaponAnimationRequest);
static EvsSceneKey _gAkropolisBridgeArrivalSceneKey;
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_bridge/_gAkropolisBridgeArrivalSceneKey", _gAkropolisBridgeArrivalSceneKey);
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
static EvsCommand _gAkropolisBridgeArrivalScript[26];
static void peDecodeArr_gAkropolisBridgeArrivalScript(void* base, const unsigned char* src, size_t n)
{
    EvsCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_EvsCommand(&dst[k], src + k * 24);
    dst[0].operand0.storage = (void*)&_akropolisBridgePrepareArrivalScene;
    dst[1].operand0.storage = (void*)&_akropolisBridgeSelectArrivalSpriteFrame;
    dst[3].operand3.storage = &_gAkropolisBridgeArrivalWeaponAnimationRequest;
    dst[5].operand0.storage = &_gAkropolisBridgeArrivalSceneKey;
    dst[12].operand0.storage = _gAkropolisBridgeArrivalVibrationCommands;
    dst[12].operand1.storage = _gAkropolisBridgeArrivalVibrationSegments;
    dst[14].operand0.storage = (void*)&_akropolisBridgeSelectArrivalSpriteFrame;
    dst[16].operand0.storage = (void*)&_akropolisBridgeSelectArrivalSpriteFrame;
    dst[21].operand0.storage = (void*)&_akropolisBridgeSetArrivalSpritesHidden;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_bridge/_gAkropolisBridgeArrivalScript", _gAkropolisBridgeArrivalScript, peDecodeArr_gAkropolisBridgeArrivalScript);
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
static EvsCommand _gAkropolisBridgeArrivalSkipScript[11];
static void peDecodeArr_gAkropolisBridgeArrivalSkipScript(void* base, const unsigned char* src, size_t n)
{
    EvsCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_EvsCommand(&dst[k], src + k * 24);
    dst[4].operand0.storage = (void*)&_akropolisBridgeSelectArrivalSpriteFrame;
    dst[5].operand0.storage = (void*)&_akropolisBridgeSetArrivalSpritesHidden;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_bridge/_gAkropolisBridgeArrivalSkipScript", _gAkropolisBridgeArrivalSkipScript, peDecodeArr_gAkropolisBridgeArrivalSkipScript);
