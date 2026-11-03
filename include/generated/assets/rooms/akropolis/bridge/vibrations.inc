/* rooms/akropolis/bridge/package: written from its room instance by tools/buildsteps/gen_room_inc.py. */

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
static PadScriptCmd _gAkropolisBridgeKeypadMovieVibrationCommands[6];
static void peDecodeArr_gAkropolisBridgeKeypadMovieVibrationCommands(void* base, const unsigned char* src, size_t n)
{
    PadScriptCmd* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_PadScriptCmd(&dst[k], src + k * 4);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_bridge/_gAkropolisBridgeKeypadMovieVibrationCommands", _gAkropolisBridgeKeypadMovieVibrationCommands, peDecodeArr_gAkropolisBridgeKeypadMovieVibrationCommands);
static PadScriptVibrationSegment _gAkropolisBridgeKeypadMovieVibrationSegments[6];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_bridge/_gAkropolisBridgeKeypadMovieVibrationSegments", _gAkropolisBridgeKeypadMovieVibrationSegments);
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
static PadScriptCmd _gAkropolisBridgeArrivalVibrationCommands[6];
static void peDecodeArr_gAkropolisBridgeArrivalVibrationCommands(void* base, const unsigned char* src, size_t n)
{
    PadScriptCmd* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_PadScriptCmd(&dst[k], src + k * 4);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_bridge/_gAkropolisBridgeArrivalVibrationCommands", _gAkropolisBridgeArrivalVibrationCommands, peDecodeArr_gAkropolisBridgeArrivalVibrationCommands);
static PadScriptVibrationSegment _gAkropolisBridgeArrivalVibrationSegments[5];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_bridge/_gAkropolisBridgeArrivalVibrationSegments", _gAkropolisBridgeArrivalVibrationSegments);
