/* rooms/akropolis/roof_garden/package: written from its room instance by tools/buildsteps/gen_room_inc.py. */

#include "gameplay/message.h"

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
static ActorCommand _gAkropolisRoofGardenUnusedActorCommand;
static void peDecodeArr_gAkropolisRoofGardenUnusedActorCommand(void* base, const unsigned char* src, size_t n)
{
    ActorCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_ActorCommand(&dst[k], src + k * 4);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_roof_garden/_gAkropolisRoofGardenUnusedActorCommand", _gAkropolisRoofGardenUnusedActorCommand, peDecodeArr_gAkropolisRoofGardenUnusedActorCommand);
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
static AnimationPlayRequest _gAkropolisRoofGardenArrivalFinalPlayerAnimation;
static void peDecodeArr_gAkropolisRoofGardenArrivalFinalPlayerAnimation(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_roof_garden/_gAkropolisRoofGardenArrivalFinalPlayerAnimation", _gAkropolisRoofGardenArrivalFinalPlayerAnimation, peDecodeArr_gAkropolisRoofGardenArrivalFinalPlayerAnimation);
static ActorTransform _gAkropolisRoofGardenArrivalFigurePlacement;
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_roof_garden/_gAkropolisRoofGardenArrivalFigurePlacement", _gAkropolisRoofGardenArrivalFigurePlacement);
static ActorTransform _gAkropolisRoofGardenArrivalStartPlayerPlacement;
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_roof_garden/_gAkropolisRoofGardenArrivalStartPlayerPlacement", _gAkropolisRoofGardenArrivalStartPlayerPlacement);
static ActorTransform _gAkropolisRoofGardenUnusedTransform;
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_roof_garden/_gAkropolisRoofGardenUnusedTransform", _gAkropolisRoofGardenUnusedTransform);
static ActorTransform _gAkropolisRoofGardenArrivalEndPlayerPlacement;
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_roof_garden/_gAkropolisRoofGardenArrivalEndPlayerPlacement", _gAkropolisRoofGardenArrivalEndPlayerPlacement);
