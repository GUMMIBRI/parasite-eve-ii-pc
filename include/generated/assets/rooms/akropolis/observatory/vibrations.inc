/* rooms/akropolis/observatory/package: written from its room instance by tools/buildsteps/gen_room_inc.py. */

#include "gameplay/pad_script.h"

#ifndef PE_DECODE_PadScriptCmd
#define PE_DECODE_PadScriptCmd
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
static void peDecode_PadScriptCmd(PadScriptCmd* dst, const unsigned char* src)
{
    { uint8_t v; memcpy(&v, src + 0, 1); dst->holdCommand.bytes.opcode = v; }
    { uint8_t v; memcpy(&v, src + 1, 1); dst->holdCommand.bytes.operand = v; }
    { uint8_t v; memcpy(&v, src + 2, 1); dst->lerpCommand.bytes.opcode = v; }
    { uint8_t v; memcpy(&v, src + 3, 1); dst->lerpCommand.bytes.operand = v; }
}

#endif
PadScriptCmd gAkropolisObservatoryForkedRoadArrivalVibrationCommands[6];
static void peDecodeArr_gAkropolisObservatoryForkedRoadArrivalVibrationCommands(void* base, const unsigned char* src, size_t n)
{
    PadScriptCmd* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_PadScriptCmd(&dst[k], src + k * 4);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_observatory/gAkropolisObservatoryForkedRoadArrivalVibrationCommands", gAkropolisObservatoryForkedRoadArrivalVibrationCommands, peDecodeArr_gAkropolisObservatoryForkedRoadArrivalVibrationCommands);
PadScriptVibrationSegment gAkropolisObservatoryForkedRoadArrivalVibrationSegments[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_observatory/gAkropolisObservatoryForkedRoadArrivalVibrationSegments", gAkropolisObservatoryForkedRoadArrivalVibrationSegments);
#ifndef PE_DECODE_PadScriptCmd
#define PE_DECODE_PadScriptCmd
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
static void peDecode_PadScriptCmd(PadScriptCmd* dst, const unsigned char* src)
{
    { uint8_t v; memcpy(&v, src + 0, 1); dst->holdCommand.bytes.opcode = v; }
    { uint8_t v; memcpy(&v, src + 1, 1); dst->holdCommand.bytes.operand = v; }
    { uint8_t v; memcpy(&v, src + 2, 1); dst->lerpCommand.bytes.opcode = v; }
    { uint8_t v; memcpy(&v, src + 3, 1); dst->lerpCommand.bytes.operand = v; }
}

#endif
PadScriptCmd gAkropolisObservatoryPromenadeArrivalVibrationCommands[6];
static void peDecodeArr_gAkropolisObservatoryPromenadeArrivalVibrationCommands(void* base, const unsigned char* src, size_t n)
{
    PadScriptCmd* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_PadScriptCmd(&dst[k], src + k * 4);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_observatory/gAkropolisObservatoryPromenadeArrivalVibrationCommands", gAkropolisObservatoryPromenadeArrivalVibrationCommands, peDecodeArr_gAkropolisObservatoryPromenadeArrivalVibrationCommands);
PadScriptVibrationSegment gAkropolisObservatoryPromenadeArrivalVibrationSegments[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_observatory/gAkropolisObservatoryPromenadeArrivalVibrationSegments", gAkropolisObservatoryPromenadeArrivalVibrationSegments);
