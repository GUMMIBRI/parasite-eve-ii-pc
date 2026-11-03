/* rooms/mist/parking/package: written from its room instance by tools/buildsteps/gen_room_inc.py. */

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
static AnimationBankCopyRequest _gMistParkingCommand1PlayerBankCopy;
static void peDecodeArr_gMistParkingCommand1PlayerBankCopy(void* base, const unsigned char* src, size_t n)
{
    AnimationBankCopyRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationBankCopyRequest(&dst[k], src + k * 8);
    dst[0].sets = (void*)&_gMistParkingCommand1PlayerAnimationSets;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_parking/_gMistParkingCommand1PlayerBankCopy", _gMistParkingCommand1PlayerBankCopy, peDecodeArr_gMistParkingCommand1PlayerBankCopy);
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
static AnimationPlayRequest _gMistParkingCommand1PlayerAnimation;
static void peDecodeArr_gMistParkingCommand1PlayerAnimation(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_parking/_gMistParkingCommand1PlayerAnimation", _gMistParkingCommand1PlayerAnimation, peDecodeArr_gMistParkingCommand1PlayerAnimation);
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
static AnimationPlayRequest _gMistParkingPlayerRoomTransitionAnimation;
static void peDecodeArr_gMistParkingPlayerRoomTransitionAnimation(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_parking/_gMistParkingPlayerRoomTransitionAnimation", _gMistParkingPlayerRoomTransitionAnimation, peDecodeArr_gMistParkingPlayerRoomTransitionAnimation);
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
static EvsCommand _gMistParkingSelectRoom2Script[15];
static void peDecodeArr_gMistParkingSelectRoom2Script(void* base, const unsigned char* src, size_t n)
{
    EvsCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_EvsCommand(&dst[k], src + k * 24);
    dst[0].operand3.storage = &_gMistParkingPlayerRoomTransitionAnimation;
    dst[1].operand0.storage = (void*)&_mistParkingSpawnCapEventIfIdle;
    dst[7].operand3.storage = &_gMistParkingRoom2PlayerPlacement;
    dst[8].operand0.storage = (void*)&_mistParkingSelectChapterRoom;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_parking/_gMistParkingSelectRoom2Script", _gMistParkingSelectRoom2Script, peDecodeArr_gMistParkingSelectRoom2Script);
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
static EvsCommand _gMistParkingSelectRoom1Script[13];
static void peDecodeArr_gMistParkingSelectRoom1Script(void* base, const unsigned char* src, size_t n)
{
    EvsCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_EvsCommand(&dst[k], src + k * 24);
    dst[0].operand3.storage = &_gMistParkingPlayerRoomTransitionAnimation;
    dst[5].operand3.storage = &_gMistParkingRoom1PlayerPlacement;
    dst[6].operand0.storage = (void*)&_mistParkingSelectChapterRoom;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_parking/_gMistParkingSelectRoom1Script", _gMistParkingSelectRoom1Script, peDecodeArr_gMistParkingSelectRoom1Script);
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
static EvsCommand _gMistParkingCommand1Script[12];
static void peDecodeArr_gMistParkingCommand1Script(void* base, const unsigned char* src, size_t n)
{
    EvsCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_EvsCommand(&dst[k], src + k * 24);
    dst[0].operand3.storage = &_gMistParkingCommand1PlayerPlacement;
    dst[1].operand3.storage = &_gMistParkingCommand1PlayerBankCopy;
    dst[2].operand3.storage = &_gMistParkingCommand1PlayerAnimation;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_parking/_gMistParkingCommand1Script", _gMistParkingCommand1Script, peDecodeArr_gMistParkingCommand1Script);
