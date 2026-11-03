/* rooms/mist/shooting_gallery/pierce: written from its room instance by tools/buildsteps/gen_room_inc.py. */

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
static AnimationPlayRequest _gShootingGalleryPierceGalleryPierceClip0Request;
static void peDecodeArr_gShootingGalleryPierceGalleryPierceClip0Request(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/shooting_gallery_pierce/_gShootingGalleryPierceGalleryPierceClip0Request", _gShootingGalleryPierceGalleryPierceClip0Request, peDecodeArr_gShootingGalleryPierceGalleryPierceClip0Request);
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
static AnimationPlayRequest _gShootingGalleryPiercePierceGalleryIdleRequest;
static void peDecodeArr_gShootingGalleryPiercePierceGalleryIdleRequest(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/shooting_gallery_pierce/_gShootingGalleryPiercePierceGalleryIdleRequest", _gShootingGalleryPiercePierceGalleryIdleRequest, peDecodeArr_gShootingGalleryPiercePierceGalleryIdleRequest);
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
static AnimationPlayRequest _gShootingGalleryPiercePierceGalleryAskRequest;
static void peDecodeArr_gShootingGalleryPiercePierceGalleryAskRequest(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/shooting_gallery_pierce/_gShootingGalleryPiercePierceGalleryAskRequest", _gShootingGalleryPiercePierceGalleryAskRequest, peDecodeArr_gShootingGalleryPiercePierceGalleryAskRequest);
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
static AnimationPlayRequest _gShootingGalleryPiercePierceGalleryTalkRequest;
static void peDecodeArr_gShootingGalleryPiercePierceGalleryTalkRequest(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/shooting_gallery_pierce/_gShootingGalleryPiercePierceGalleryTalkRequest", _gShootingGalleryPiercePierceGalleryTalkRequest, peDecodeArr_gShootingGalleryPiercePierceGalleryTalkRequest);
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
static AnimationPlayRequest _gShootingGalleryPiercePierceGalleryTeaseRequest;
static void peDecodeArr_gShootingGalleryPiercePierceGalleryTeaseRequest(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/shooting_gallery_pierce/_gShootingGalleryPiercePierceGalleryTeaseRequest", _gShootingGalleryPiercePierceGalleryTeaseRequest, peDecodeArr_gShootingGalleryPiercePierceGalleryTeaseRequest);
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
static AnimationPlayRequest _gShootingGalleryPiercePierceGalleryReactRequest;
static void peDecodeArr_gShootingGalleryPiercePierceGalleryReactRequest(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/shooting_gallery_pierce/_gShootingGalleryPiercePierceGalleryReactRequest", _gShootingGalleryPiercePierceGalleryReactRequest, peDecodeArr_gShootingGalleryPiercePierceGalleryReactRequest);
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
static AnimationPlayRequest _gShootingGalleryPiercePierceLevelPromptRequest;
static void peDecodeArr_gShootingGalleryPiercePierceLevelPromptRequest(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/shooting_gallery_pierce/_gShootingGalleryPiercePierceLevelPromptRequest", _gShootingGalleryPiercePierceLevelPromptRequest, peDecodeArr_gShootingGalleryPiercePierceLevelPromptRequest);
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
static AnimationPlayRequest _gShootingGalleryPiercePierceLevelReplyRequest;
static void peDecodeArr_gShootingGalleryPiercePierceLevelReplyRequest(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/shooting_gallery_pierce/_gShootingGalleryPiercePierceLevelReplyRequest", _gShootingGalleryPiercePierceLevelReplyRequest, peDecodeArr_gShootingGalleryPiercePierceLevelReplyRequest);
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
static AnimationPlayRequest _gShootingGalleryPierceGalleryPlayerGalleryAcceptResetRequest;
static void peDecodeArr_gShootingGalleryPierceGalleryPlayerGalleryAcceptResetRequest(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/shooting_gallery_pierce/_gShootingGalleryPierceGalleryPlayerGalleryAcceptResetRequest", _gShootingGalleryPierceGalleryPlayerGalleryAcceptResetRequest, peDecodeArr_gShootingGalleryPierceGalleryPlayerGalleryAcceptResetRequest);
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
static AnimationPlayRequest _gShootingGalleryPierceGalleryPlayerGalleryAcceptRequest;
static void peDecodeArr_gShootingGalleryPierceGalleryPlayerGalleryAcceptRequest(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/shooting_gallery_pierce/_gShootingGalleryPierceGalleryPlayerGalleryAcceptRequest", _gShootingGalleryPierceGalleryPlayerGalleryAcceptRequest, peDecodeArr_gShootingGalleryPierceGalleryPlayerGalleryAcceptRequest);
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
static AnimationPlayRequest _gShootingGalleryPierceGalleryPlayerGalleryIdleRequest;
static void peDecodeArr_gShootingGalleryPierceGalleryPlayerGalleryIdleRequest(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/shooting_gallery_pierce/_gShootingGalleryPierceGalleryPlayerGalleryIdleRequest", _gShootingGalleryPierceGalleryPlayerGalleryIdleRequest, peDecodeArr_gShootingGalleryPierceGalleryPlayerGalleryIdleRequest);
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
static AnimationPlayRequest _gShootingGalleryPierceGalleryPlayerGalleryIntro6Request;
static void peDecodeArr_gShootingGalleryPierceGalleryPlayerGalleryIntro6Request(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/shooting_gallery_pierce/_gShootingGalleryPierceGalleryPlayerGalleryIntro6Request", _gShootingGalleryPierceGalleryPlayerGalleryIntro6Request, peDecodeArr_gShootingGalleryPierceGalleryPlayerGalleryIntro6Request);
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
static AnimationPlayRequest _gShootingGalleryPierceGalleryPlayerGalleryIntro9Request;
static void peDecodeArr_gShootingGalleryPierceGalleryPlayerGalleryIntro9Request(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/shooting_gallery_pierce/_gShootingGalleryPierceGalleryPlayerGalleryIntro9Request", _gShootingGalleryPierceGalleryPlayerGalleryIntro9Request, peDecodeArr_gShootingGalleryPierceGalleryPlayerGalleryIntro9Request);
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
static AnimationPlayRequest _gShootingGalleryPierceGalleryPlayerGalleryExcuseRequest;
static void peDecodeArr_gShootingGalleryPierceGalleryPlayerGalleryExcuseRequest(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/shooting_gallery_pierce/_gShootingGalleryPierceGalleryPlayerGalleryExcuseRequest", _gShootingGalleryPierceGalleryPlayerGalleryExcuseRequest, peDecodeArr_gShootingGalleryPierceGalleryPlayerGalleryExcuseRequest);
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
static AnimationPlayRequest _gShootingGalleryPierceGalleryPlayerGalleryDeclineRequest;
static void peDecodeArr_gShootingGalleryPierceGalleryPlayerGalleryDeclineRequest(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/shooting_gallery_pierce/_gShootingGalleryPierceGalleryPlayerGalleryDeclineRequest", _gShootingGalleryPierceGalleryPlayerGalleryDeclineRequest, peDecodeArr_gShootingGalleryPierceGalleryPlayerGalleryDeclineRequest);
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
static AnimationBankCopyRequest _gShootingGalleryPierceGalleryPlayerBankCopyRequest;
static void peDecodeArr_gShootingGalleryPierceGalleryPlayerBankCopyRequest(void* base, const unsigned char* src, size_t n)
{
    AnimationBankCopyRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationBankCopyRequest(&dst[k], src + k * 8);
    dst[0].sets = (void*)&_gShootingGalleryPierceGalleryPlayerAnimationSets;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/shooting_gallery_pierce/_gShootingGalleryPierceGalleryPlayerBankCopyRequest", _gShootingGalleryPierceGalleryPlayerBankCopyRequest, peDecodeArr_gShootingGalleryPierceGalleryPlayerBankCopyRequest);
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
static AnimationPlayRequest _gShootingGalleryPierceGalleryPlayerSlot10Request;
static void peDecodeArr_gShootingGalleryPierceGalleryPlayerSlot10Request(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/shooting_gallery_pierce/_gShootingGalleryPierceGalleryPlayerSlot10Request", _gShootingGalleryPierceGalleryPlayerSlot10Request, peDecodeArr_gShootingGalleryPierceGalleryPlayerSlot10Request);
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
static AnimationPlayRequest _gShootingGalleryPierceGalleryPlayerIdleRequest;
static void peDecodeArr_gShootingGalleryPierceGalleryPlayerIdleRequest(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/shooting_gallery_pierce/_gShootingGalleryPierceGalleryPlayerIdleRequest", _gShootingGalleryPierceGalleryPlayerIdleRequest, peDecodeArr_gShootingGalleryPierceGalleryPlayerIdleRequest);
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
static AnimationPlayRequest _gShootingGalleryPierceGalleryPlayerAimIdleRequest;
static void peDecodeArr_gShootingGalleryPierceGalleryPlayerAimIdleRequest(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/shooting_gallery_pierce/_gShootingGalleryPierceGalleryPlayerAimIdleRequest", _gShootingGalleryPierceGalleryPlayerAimIdleRequest, peDecodeArr_gShootingGalleryPierceGalleryPlayerAimIdleRequest);
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
static AnimationPlayRequest _gShootingGalleryPierceGalleryPlayerAimEnterRequest;
static void peDecodeArr_gShootingGalleryPierceGalleryPlayerAimEnterRequest(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/shooting_gallery_pierce/_gShootingGalleryPierceGalleryPlayerAimEnterRequest", _gShootingGalleryPierceGalleryPlayerAimEnterRequest, peDecodeArr_gShootingGalleryPierceGalleryPlayerAimEnterRequest);
static ActorTransform _gShootingGalleryPierceGalleryPiercePlacement;
#include "port/asset_bind.h"
PE_ASSET_BIND("room/shooting_gallery_pierce/_gShootingGalleryPierceGalleryPiercePlacement", _gShootingGalleryPierceGalleryPiercePlacement);
static ActorTransform _gShootingGalleryPierceGalleryPierceDemoPlacement;
#include "port/asset_bind.h"
PE_ASSET_BIND("room/shooting_gallery_pierce/_gShootingGalleryPierceGalleryPierceDemoPlacement", _gShootingGalleryPierceGalleryPierceDemoPlacement);
static ActorTransform _gShootingGalleryPierceGalleryPlayerMenuPlacement;
#include "port/asset_bind.h"
PE_ASSET_BIND("room/shooting_gallery_pierce/_gShootingGalleryPierceGalleryPlayerMenuPlacement", _gShootingGalleryPierceGalleryPlayerMenuPlacement);
static ActorTransform _gShootingGalleryPierceGalleryPlayerCoursePlacement;
#include "port/asset_bind.h"
PE_ASSET_BIND("room/shooting_gallery_pierce/_gShootingGalleryPierceGalleryPlayerCoursePlacement", _gShootingGalleryPierceGalleryPlayerCoursePlacement);
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
static EvsCommand _gShootingGalleryPierceGalleryIntroScript[59];
static void peDecodeArr_gShootingGalleryPierceGalleryIntroScript(void* base, const unsigned char* src, size_t n)
{
    EvsCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_EvsCommand(&dst[k], src + k * 24);
    dst[1].operand3.storage = &_gShootingGalleryPierceGalleryPlayerBankCopyRequest;
    dst[3].operand0.storage = (void*)&_shootingGalleryPierceStartGalleryMovie;
    dst[7].operand3.storage = &_gShootingGalleryPierceGalleryPlayerAimIdleRequest;
    dst[9].operand0.storage = (void*)&SetDispMask;
    dst[10].operand3.storage = &_gShootingGalleryPierceGalleryPlayerMenuPlacement;
    dst[11].operand3.storage = &_gShootingGalleryPierceGalleryPiercePlacement;
    dst[18].operand0.storage = (void*)&_shootingGalleryPierceSpawnGalleryDemoTargetIfEnabled;
    dst[20].operand0.storage = (void*)&_shootingGalleryPierceSetGalleryRedFlashLoop;
    dst[24].operand3.storage = &_gShootingGalleryPiercePierceGalleryIdleRequest;
    dst[25].operand3.storage = &_gShootingGalleryPierceGalleryPlayerGalleryIdleRequest;
    dst[29].operand0.storage = (void*)&_shootingGalleryPierceSetGalleryRedFlashLoop;
    dst[30].operand3.storage = &_gShootingGalleryPierceGalleryPlayerGalleryIntro6Request;
    dst[32].operand3.storage = &_gShootingGalleryPierceGalleryPlayerGalleryIdleRequest;
    dst[35].operand3.storage = &_gShootingGalleryPiercePierceGalleryTalkRequest;
    dst[37].operand3.storage = &_gShootingGalleryPiercePierceGalleryIdleRequest;
    dst[39].operand3.storage = &_gShootingGalleryPierceGalleryPlayerGalleryIntro9Request;
    dst[40].operand3.storage = &_gShootingGalleryPiercePierceGalleryTeaseRequest;
    dst[42].operand3.storage = &_gShootingGalleryPiercePierceGalleryReactRequest;
    dst[43].operand3.storage = &_gShootingGalleryPierceGalleryPlayerGalleryExcuseRequest;
    dst[45].operand3.storage = &_gShootingGalleryPierceGalleryPierceDemoPlacement;
    dst[46].operand3.storage = &_gShootingGalleryPiercePierceGalleryAskRequest;
    dst[48].operand3.storage = &_gShootingGalleryPiercePierceGalleryIdleRequest;
    dst[50].operand3.storage = &_gShootingGalleryPiercePierceGalleryTalkRequest;
    dst[52].operand3.storage = &_gShootingGalleryPiercePierceGalleryIdleRequest;
    dst[55].operand3.storage = &_gShootingGalleryPierceGalleryPiercePlacement;
    dst[56].operand3.storage = &_gShootingGalleryPierceGalleryPlayerGalleryIdleRequest;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/shooting_gallery_pierce/_gShootingGalleryPierceGalleryIntroScript", _gShootingGalleryPierceGalleryIntroScript, peDecodeArr_gShootingGalleryPierceGalleryIntroScript);
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
static EvsCommand _gShootingGalleryPierceGalleryIntroSkipScript[17];
static void peDecodeArr_gShootingGalleryPierceGalleryIntroSkipScript(void* base, const unsigned char* src, size_t n)
{
    EvsCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_EvsCommand(&dst[k], src + k * 24);
    dst[4].operand0.storage = (void*)&_shootingGalleryPierceSetViewRespawnPending;
    dst[5].operand0.storage = (void*)&SetDispMask;
    dst[7].operand0.storage = (void*)&_shootingGalleryPierceSetGalleryRedFlashLoop;
    dst[9].operand3.storage = &_gShootingGalleryPierceGalleryPlayerGalleryIdleRequest;
    dst[11].operand3.storage = &_gShootingGalleryPierceGalleryPiercePlacement;
    dst[12].operand3.storage = &_gShootingGalleryPiercePierceGalleryIdleRequest;
    dst[13].operand3.storage = &_gShootingGalleryPierceGalleryPlayerMenuPlacement;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/shooting_gallery_pierce/_gShootingGalleryPierceGalleryIntroSkipScript", _gShootingGalleryPierceGalleryIntroSkipScript, peDecodeArr_gShootingGalleryPierceGalleryIntroSkipScript);
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
static EvsCommand _gShootingGalleryPierceGalleryTrainingOfferScript[5];
static void peDecodeArr_gShootingGalleryPierceGalleryTrainingOfferScript(void* base, const unsigned char* src, size_t n)
{
    EvsCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_EvsCommand(&dst[k], src + k * 24);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/shooting_gallery_pierce/_gShootingGalleryPierceGalleryTrainingOfferScript", _gShootingGalleryPierceGalleryTrainingOfferScript, peDecodeArr_gShootingGalleryPierceGalleryTrainingOfferScript);
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
static EvsCommand _gShootingGalleryPierceGalleryIntroAcceptTrainingScript[6];
static void peDecodeArr_gShootingGalleryPierceGalleryIntroAcceptTrainingScript(void* base, const unsigned char* src, size_t n)
{
    EvsCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_EvsCommand(&dst[k], src + k * 24);
    dst[1].operand3.storage = &_gShootingGalleryPierceGalleryPlayerBankCopyRequest;
    dst[2].operand3.storage = &_gShootingGalleryPierceGalleryPlayerGalleryAcceptRequest;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/shooting_gallery_pierce/_gShootingGalleryPierceGalleryIntroAcceptTrainingScript", _gShootingGalleryPierceGalleryIntroAcceptTrainingScript, peDecodeArr_gShootingGalleryPierceGalleryIntroAcceptTrainingScript);
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
EvsCommand gShootingGalleryPierceGalleryWaitTrainingAcceptanceScript[3];
static void peDecodeArr_gShootingGalleryPierceGalleryWaitTrainingAcceptanceScript(void* base, const unsigned char* src, size_t n)
{
    EvsCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_EvsCommand(&dst[k], src + k * 24);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/shooting_gallery_pierce/gShootingGalleryPierceGalleryWaitTrainingAcceptanceScript", gShootingGalleryPierceGalleryWaitTrainingAcceptanceScript, peDecodeArr_gShootingGalleryPierceGalleryWaitTrainingAcceptanceScript);
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
EvsCommand gShootingGalleryPierceGalleryDeclineTrainingScript[18];
static void peDecodeArr_gShootingGalleryPierceGalleryDeclineTrainingScript(void* base, const unsigned char* src, size_t n)
{
    EvsCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_EvsCommand(&dst[k], src + k * 24);
    dst[0].operand3.storage = &_gShootingGalleryPierceGalleryPlayerBankCopyRequest;
    dst[1].operand3.storage = &_gShootingGalleryPierceGalleryPlayerGalleryDeclineRequest;
    dst[3].operand3.storage = &_gShootingGalleryPiercePierceGalleryAskRequest;
    dst[5].operand3.storage = &_gShootingGalleryPiercePierceGalleryIdleRequest;
    dst[11].operand3.storage = &_gShootingGalleryPierceGalleryPlayerIdleRequest;
    dst[12].operand3.storage = &_gShootingGalleryPierceGalleryPlayerCoursePlacement;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/shooting_gallery_pierce/gShootingGalleryPierceGalleryDeclineTrainingScript", gShootingGalleryPierceGalleryDeclineTrainingScript, peDecodeArr_gShootingGalleryPierceGalleryDeclineTrainingScript);
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
EvsCommand gShootingGalleryPierceGalleryPrepareTrainingMenuScript[9];
static void peDecodeArr_gShootingGalleryPierceGalleryPrepareTrainingMenuScript(void* base, const unsigned char* src, size_t n)
{
    EvsCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_EvsCommand(&dst[k], src + k * 24);
    dst[1].operand3.storage = &_gShootingGalleryPierceGalleryPlayerAimIdleRequest;
    dst[3].operand3.storage = &_gShootingGalleryPierceGalleryPlayerMenuPlacement;
    dst[4].operand3.storage = &_gShootingGalleryPierceGalleryPiercePlacement;
    dst[5].operand3.storage = &_gShootingGalleryPiercePierceGalleryIdleRequest;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/shooting_gallery_pierce/gShootingGalleryPierceGalleryPrepareTrainingMenuScript", gShootingGalleryPierceGalleryPrepareTrainingMenuScript, peDecodeArr_gShootingGalleryPierceGalleryPrepareTrainingMenuScript);
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
EvsCommand gShootingGalleryPierceGalleryOfferTrainingMenuScript[13];
static void peDecodeArr_gShootingGalleryPierceGalleryOfferTrainingMenuScript(void* base, const unsigned char* src, size_t n)
{
    EvsCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_EvsCommand(&dst[k], src + k * 24);
    dst[1].operand3.storage = &_gShootingGalleryPierceGalleryPlayerBankCopyRequest;
    dst[2].operand3.storage = &_gShootingGalleryPierceGalleryPlayerGalleryIdleRequest;
    dst[4].operand3.storage = &_gShootingGalleryPierceGalleryPlayerMenuPlacement;
    dst[6].operand3.storage = &_gShootingGalleryPierceGalleryPiercePlacement;
    dst[7].operand3.storage = &_gShootingGalleryPiercePierceGalleryIdleRequest;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/shooting_gallery_pierce/gShootingGalleryPierceGalleryOfferTrainingMenuScript", gShootingGalleryPierceGalleryOfferTrainingMenuScript, peDecodeArr_gShootingGalleryPierceGalleryOfferTrainingMenuScript);
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
EvsCommand gShootingGalleryPierceGalleryStartFixedViewTrainingScript[8];
static void peDecodeArr_gShootingGalleryPierceGalleryStartFixedViewTrainingScript(void* base, const unsigned char* src, size_t n)
{
    EvsCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_EvsCommand(&dst[k], src + k * 24);
    dst[0].operand3.storage = &_gShootingGalleryPierceGalleryPlayerIdleRequest;
    dst[2].operand3.storage = &_gShootingGalleryPierceGalleryPlayerCoursePlacement;
    dst[4].operand0.storage = (void*)&_shootingGalleryPierceSelectGalleryRoomLights;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/shooting_gallery_pierce/gShootingGalleryPierceGalleryStartFixedViewTrainingScript", gShootingGalleryPierceGalleryStartFixedViewTrainingScript, peDecodeArr_gShootingGalleryPierceGalleryStartFixedViewTrainingScript);
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
EvsCommand gShootingGalleryPierceGalleryStartFreeMovementTrainingScript[9];
static void peDecodeArr_gShootingGalleryPierceGalleryStartFreeMovementTrainingScript(void* base, const unsigned char* src, size_t n)
{
    EvsCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_EvsCommand(&dst[k], src + k * 24);
    dst[0].operand3.storage = &_gShootingGalleryPierceGalleryPlayerIdleRequest;
    dst[4].operand3.storage = &_gShootingGalleryPierceGalleryPlayerCoursePlacement;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/shooting_gallery_pierce/gShootingGalleryPierceGalleryStartFreeMovementTrainingScript", gShootingGalleryPierceGalleryStartFreeMovementTrainingScript, peDecodeArr_gShootingGalleryPierceGalleryStartFreeMovementTrainingScript);
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
EvsCommand gShootingGalleryPierceGalleryConfirmCourseScript[6];
static void peDecodeArr_gShootingGalleryPierceGalleryConfirmCourseScript(void* base, const unsigned char* src, size_t n)
{
    EvsCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_EvsCommand(&dst[k], src + k * 24);
    dst[1].operand3.storage = &_gShootingGalleryPiercePierceGalleryTalkRequest;
    dst[3].operand3.storage = &_gShootingGalleryPiercePierceGalleryIdleRequest;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/shooting_gallery_pierce/gShootingGalleryPierceGalleryConfirmCourseScript", gShootingGalleryPierceGalleryConfirmCourseScript, peDecodeArr_gShootingGalleryPierceGalleryConfirmCourseScript);
