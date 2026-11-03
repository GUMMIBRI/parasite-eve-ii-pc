/* rooms/akropolis/sanctuary/package: written from its room instance by tools/buildsteps/gen_room_inc.py. */

#include "gameplay/message.h"

static ActorTransform _gAkropolisSanctuaryPlayerSceneStartPlacement;
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_sanctuary/_gAkropolisSanctuaryPlayerSceneStartPlacement", _gAkropolisSanctuaryPlayerSceneStartPlacement);
static ActorTransform _gAkropolisSanctuarySceneOriginPlacement;
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_sanctuary/_gAkropolisSanctuarySceneOriginPlacement", _gAkropolisSanctuarySceneOriginPlacement);
static ActorTransform _gAkropolisSanctuaryUnusedTransform;
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_sanctuary/_gAkropolisSanctuaryUnusedTransform", _gAkropolisSanctuaryUnusedTransform);
static ActorTransform _gAkropolisSanctuaryPlayerSceneClip48Placement;
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_sanctuary/_gAkropolisSanctuaryPlayerSceneClip48Placement", _gAkropolisSanctuaryPlayerSceneClip48Placement);
static ActorTransform _gAkropolisSanctuaryPlayerSceneClip49Placement;
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_sanctuary/_gAkropolisSanctuaryPlayerSceneClip49Placement", _gAkropolisSanctuaryPlayerSceneClip49Placement);
static ActorTransform _gAkropolisSanctuaryRupertRestoredPlacement;
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_sanctuary/_gAkropolisSanctuaryRupertRestoredPlacement", _gAkropolisSanctuaryRupertRestoredPlacement);
static ActorTransform _gAkropolisSanctuaryPlayerSceneClosingPlacement;
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_sanctuary/_gAkropolisSanctuaryPlayerSceneClosingPlacement", _gAkropolisSanctuaryPlayerSceneClosingPlacement);
static ActorTransform _gAkropolisSanctuaryPlayerSceneEndPlacement;
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_sanctuary/_gAkropolisSanctuaryPlayerSceneEndPlacement", _gAkropolisSanctuaryPlayerSceneEndPlacement);
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
static AnimationPlayRequest _gAkropolisSanctuaryPlayerWeaponClip1Request;
static void peDecodeArr_gAkropolisSanctuaryPlayerWeaponClip1Request(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_sanctuary/_gAkropolisSanctuaryPlayerWeaponClip1Request", _gAkropolisSanctuaryPlayerWeaponClip1Request, peDecodeArr_gAkropolisSanctuaryPlayerWeaponClip1Request);
