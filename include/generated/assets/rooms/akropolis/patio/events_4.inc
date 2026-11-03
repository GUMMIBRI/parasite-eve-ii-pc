/* rooms/akropolis/patio/package: written from its room instance by tools/buildsteps/gen_room_inc.py. */

#include "gameplay/evs.h"

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
static EvsCommand _gAkropolisPatioAmbushScript[41];
static void peDecodeArr_gAkropolisPatioAmbushScript(void* base, const unsigned char* src, size_t n)
{
    EvsCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_EvsCommand(&dst[k], src + k * 24);
    dst[0].operand3.storage = &_gAkropolisPatioAmbushPlayerBankCopyRequest;
    dst[3].operand3.storage = &_gAkropolisPatioAmbushPlayerStartPlacement;
    dst[8].operand3.storage = &_gAkropolisPatioLeapingStranger1StartPlacement;
    dst[9].operand3.storage = &_gAkropolisPatioLeapingStranger2StartPlacement;
    dst[10].operand3.storage = &_gAkropolisPatioLeapingStranger1AnimationRequest;
    dst[11].operand3.storage = &_gAkropolisPatioLeapingStranger2AnimationRequest;
    dst[13].operand3.storage = &_gAkropolisPatioAmbushPlayerRunDestination;
    dst[14].operand3.storage = &_gAkropolisPatioRaiseStrangerHeadWeightCommand;
    dst[15].operand3.storage = &_gAkropolisPatioRaiseStrangerHeadWeightCommand;
    dst[17].operand3.storage = &_gAkropolisPatioLeapingStranger1Launch;
    dst[17].operand4.storage = &_gAkropolisPatioStrangerLeapAnimations;
    dst[19].operand3.storage = &_gAkropolisPatioLeapingStranger2Launch;
    dst[19].operand4.storage = &_gAkropolisPatioStrangerLeapAnimations;
    dst[20].operand3.storage = &_gAkropolisPatioLowerStrangerHeadWeightCommand;
    dst[21].operand3.storage = &_gAkropolisPatioLowerStrangerHeadWeightCommand;
    dst[23].operand3.storage = &_gAkropolisPatioAmbushPlayerAnimation9Request;
    dst[25].operand0.storage = (void*)&_akropolisPatioSpawnPlayerTurnLeft;
    dst[27].operand0.storage = (void*)&_akropolisPatioSetBattleActive;
    dst[34].operand3.storage = &_gAkropolisPatioAmbushStranger1BattlePlacement;
    dst[35].operand3.storage = &_gAkropolisPatioAmbushStranger2BattlePlacement;
    dst[38].operand3.storage = &_gAkropolisPatioPrintStrangerTransformCommand;
    dst[39].operand3.storage = &_gAkropolisPatioPrintStrangerTransformCommand;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_patio/_gAkropolisPatioAmbushScript", _gAkropolisPatioAmbushScript, peDecodeArr_gAkropolisPatioAmbushScript);
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
static EvsCommand _gAkropolisPatioAmbushSkipScript[21];
static void peDecodeArr_gAkropolisPatioAmbushSkipScript(void* base, const unsigned char* src, size_t n)
{
    EvsCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_EvsCommand(&dst[k], src + k * 24);
    dst[0].operand0.storage = (void*)&_akropolisPatioSetBattleActive;
    dst[8].operand3.storage = &_gAkropolisPatioAmbushStranger1BattlePlacement;
    dst[9].operand3.storage = &_gAkropolisPatioAmbushStranger2BattlePlacement;
    dst[11].operand3.storage = &_gAkropolisPatioAmbushPlayerSkipPlacement;
    dst[12].operand3.storage = &_gAkropolisPatioAmbushPlayerAnimation9Request;
    dst[17].operand0.storage = (void*)&_akropolisPatioSetBattleActive;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_patio/_gAkropolisPatioAmbushSkipScript", _gAkropolisPatioAmbushSkipScript, peDecodeArr_gAkropolisPatioAmbushSkipScript);
