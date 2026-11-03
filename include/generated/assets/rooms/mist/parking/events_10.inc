/* rooms/mist/parking/package: written from its room instance by tools/buildsteps/gen_room_inc.py. */

#include "gameplay/evs.h"
#include "gameplay/item_menu.h"

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
EvsCommand gMistParkingJodieShopTalkScript[8];
static void peDecodeArr_gMistParkingJodieShopTalkScript(void* base, const unsigned char* src, size_t n)
{
    EvsCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_EvsCommand(&dst[k], src + k * 24);
    dst[0].operand3.storage = &gMistParkingShopPlayerAnimationBankCopy;
    dst[1].operand3.storage = &gMistParkingPlayerShopTalkAnimation;
    dst[2].operand3.storage = &gMistParkingJodieIdleAnimation;
    dst[4].operand3.storage = &gMistParkingJodieGreetingAnimation;
    dst[6].operand3.storage = &gMistParkingJodieIdleAnimation;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_parking/gMistParkingJodieShopTalkScript", gMistParkingJodieShopTalkScript, peDecodeArr_gMistParkingJodieShopTalkScript);
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
EvsCommand gMistParkingJodieOpenShopScript[10];
static void peDecodeArr_gMistParkingJodieOpenShopScript(void* base, const unsigned char* src, size_t n)
{
    EvsCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_EvsCommand(&dst[k], src + k * 24);
    dst[0].operand3.storage = &gMistParkingShopPlayerAnimationBankCopy;
    dst[1].operand0.storage = (void*)&shopOpenSession;
    dst[3].operand3.storage = &gMistParkingPlayerShopTalkAnimation;
    dst[4].operand3.storage = &gMistParkingJodieReplyAnimation;
    dst[6].operand3.storage = &gMistParkingJodieReplyEndAnimation;
    dst[8].operand3.storage = &gMistParkingJodieShopExitAnimation;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_parking/gMistParkingJodieOpenShopScript", gMistParkingJodieOpenShopScript, peDecodeArr_gMistParkingJodieOpenShopScript);
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
EvsCommand gMistParkingJodieShopReplyScript[8];
static void peDecodeArr_gMistParkingJodieShopReplyScript(void* base, const unsigned char* src, size_t n)
{
    EvsCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_EvsCommand(&dst[k], src + k * 24);
    dst[0].operand3.storage = &gMistParkingShopPlayerAnimationBankCopy;
    dst[1].operand3.storage = &gMistParkingPlayerShopTalkAnimation;
    dst[2].operand3.storage = &gMistParkingJodieReplyAnimation;
    dst[4].operand3.storage = &gMistParkingJodieReplyEndAnimation;
    dst[6].operand3.storage = &gMistParkingJodieIdleAnimation;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_parking/gMistParkingJodieShopReplyScript", gMistParkingJodieShopReplyScript, peDecodeArr_gMistParkingJodieShopReplyScript);
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
EvsCommand gMistParkingJodieShopFarewellScript[8];
static void peDecodeArr_gMistParkingJodieShopFarewellScript(void* base, const unsigned char* src, size_t n)
{
    EvsCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_EvsCommand(&dst[k], src + k * 24);
    dst[0].operand3.storage = &gMistParkingShopPlayerAnimationBankCopy;
    dst[1].operand3.storage = &gMistParkingPlayerShopTalkAnimation;
    dst[2].operand3.storage = &gMistParkingJodieReplyAnimation;
    dst[4].operand3.storage = &gMistParkingJodieReplyEndAnimation;
    dst[6].operand3.storage = &gMistParkingJodieShopExitAnimation;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_parking/gMistParkingJodieShopFarewellScript", gMistParkingJodieShopFarewellScript, peDecodeArr_gMistParkingJodieShopFarewellScript);
