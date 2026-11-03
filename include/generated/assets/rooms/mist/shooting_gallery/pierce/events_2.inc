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
static AnimationPlayRequest _gShootingGalleryPierceConversationPierceClip0Request;
static void peDecodeArr_gShootingGalleryPierceConversationPierceClip0Request(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/shooting_gallery_pierce/_gShootingGalleryPierceConversationPierceClip0Request", _gShootingGalleryPierceConversationPierceClip0Request, peDecodeArr_gShootingGalleryPierceConversationPierceClip0Request);
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
static AnimationPlayRequest _gShootingGalleryPiercePiercePhoneListenRequest;
static void peDecodeArr_gShootingGalleryPiercePiercePhoneListenRequest(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/shooting_gallery_pierce/_gShootingGalleryPiercePiercePhoneListenRequest", _gShootingGalleryPiercePiercePhoneListenRequest, peDecodeArr_gShootingGalleryPiercePiercePhoneListenRequest);
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
static AnimationPlayRequest _gShootingGalleryPiercePiercePhoneTalkRequest;
static void peDecodeArr_gShootingGalleryPiercePiercePhoneTalkRequest(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/shooting_gallery_pierce/_gShootingGalleryPiercePiercePhoneTalkRequest", _gShootingGalleryPiercePiercePhoneTalkRequest, peDecodeArr_gShootingGalleryPiercePiercePhoneTalkRequest);
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
static AnimationPlayRequest _gShootingGalleryPiercePierceQuipRequest;
static void peDecodeArr_gShootingGalleryPiercePierceQuipRequest(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/shooting_gallery_pierce/_gShootingGalleryPiercePierceQuipRequest", _gShootingGalleryPiercePierceQuipRequest, peDecodeArr_gShootingGalleryPiercePierceQuipRequest);
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
static AnimationPlayRequest _gShootingGalleryPiercePierceTeaseRequest;
static void peDecodeArr_gShootingGalleryPiercePierceTeaseRequest(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/shooting_gallery_pierce/_gShootingGalleryPiercePierceTeaseRequest", _gShootingGalleryPiercePierceTeaseRequest, peDecodeArr_gShootingGalleryPiercePierceTeaseRequest);
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
static AnimationPlayRequest _gShootingGalleryPiercePierceWarnRequest;
static void peDecodeArr_gShootingGalleryPiercePierceWarnRequest(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/shooting_gallery_pierce/_gShootingGalleryPiercePierceWarnRequest", _gShootingGalleryPiercePierceWarnRequest, peDecodeArr_gShootingGalleryPiercePierceWarnRequest);
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
static AnimationPlayRequest _gShootingGalleryPiercePierceStory3Request;
static void peDecodeArr_gShootingGalleryPiercePierceStory3Request(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/shooting_gallery_pierce/_gShootingGalleryPiercePierceStory3Request", _gShootingGalleryPiercePierceStory3Request, peDecodeArr_gShootingGalleryPiercePierceStory3Request);
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
static AnimationPlayRequest _gShootingGalleryPiercePierceStory4Request;
static void peDecodeArr_gShootingGalleryPiercePierceStory4Request(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/shooting_gallery_pierce/_gShootingGalleryPiercePierceStory4Request", _gShootingGalleryPiercePierceStory4Request, peDecodeArr_gShootingGalleryPiercePierceStory4Request);
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
static AnimationPlayRequest _gShootingGalleryPiercePierceTalkRequest;
static void peDecodeArr_gShootingGalleryPiercePierceTalkRequest(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/shooting_gallery_pierce/_gShootingGalleryPiercePierceTalkRequest", _gShootingGalleryPiercePierceTalkRequest, peDecodeArr_gShootingGalleryPiercePierceTalkRequest);
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
static AnimationPlayRequest _gShootingGalleryPiercePierceTalkEndBlendRequest;
static void peDecodeArr_gShootingGalleryPiercePierceTalkEndBlendRequest(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/shooting_gallery_pierce/_gShootingGalleryPiercePierceTalkEndBlendRequest", _gShootingGalleryPiercePierceTalkEndBlendRequest, peDecodeArr_gShootingGalleryPiercePierceTalkEndBlendRequest);
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
static AnimationPlayRequest _gShootingGalleryPiercePierceCorrectHimselfBlendRequest;
static void peDecodeArr_gShootingGalleryPiercePierceCorrectHimselfBlendRequest(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/shooting_gallery_pierce/_gShootingGalleryPiercePierceCorrectHimselfBlendRequest", _gShootingGalleryPiercePierceCorrectHimselfBlendRequest, peDecodeArr_gShootingGalleryPiercePierceCorrectHimselfBlendRequest);
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
static AnimationPlayRequest _gShootingGalleryPiercePierceCorrectHimselfEndBlendRequest;
static void peDecodeArr_gShootingGalleryPiercePierceCorrectHimselfEndBlendRequest(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/shooting_gallery_pierce/_gShootingGalleryPiercePierceCorrectHimselfEndBlendRequest", _gShootingGalleryPiercePierceCorrectHimselfEndBlendRequest, peDecodeArr_gShootingGalleryPiercePierceCorrectHimselfEndBlendRequest);
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
static AnimationPlayRequest _gShootingGalleryPiercePierceRestRequest;
static void peDecodeArr_gShootingGalleryPiercePierceRestRequest(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/shooting_gallery_pierce/_gShootingGalleryPiercePierceRestRequest", _gShootingGalleryPiercePierceRestRequest, peDecodeArr_gShootingGalleryPiercePierceRestRequest);
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
static AnimationPlayRequest _gShootingGalleryPiercePierceRestBlendRequest;
static void peDecodeArr_gShootingGalleryPiercePierceRestBlendRequest(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/shooting_gallery_pierce/_gShootingGalleryPiercePierceRestBlendRequest", _gShootingGalleryPiercePierceRestBlendRequest, peDecodeArr_gShootingGalleryPiercePierceRestBlendRequest);
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
static AnimationPlayRequest _gShootingGalleryPiercePierceShortTalkRequest;
static void peDecodeArr_gShootingGalleryPiercePierceShortTalkRequest(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/shooting_gallery_pierce/_gShootingGalleryPiercePierceShortTalkRequest", _gShootingGalleryPiercePierceShortTalkRequest, peDecodeArr_gShootingGalleryPiercePierceShortTalkRequest);
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
static AnimationPlayRequest _gShootingGalleryPiercePierceShortTalkEndRequest;
static void peDecodeArr_gShootingGalleryPiercePierceShortTalkEndRequest(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/shooting_gallery_pierce/_gShootingGalleryPiercePierceShortTalkEndRequest", _gShootingGalleryPiercePierceShortTalkEndRequest, peDecodeArr_gShootingGalleryPiercePierceShortTalkEndRequest);
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
static AnimationPlayRequest _gShootingGalleryPiercePierceStory17Request;
static void peDecodeArr_gShootingGalleryPiercePierceStory17Request(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/shooting_gallery_pierce/_gShootingGalleryPiercePierceStory17Request", _gShootingGalleryPiercePierceStory17Request, peDecodeArr_gShootingGalleryPiercePierceStory17Request);
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
static AnimationPlayRequest _gShootingGalleryPierceConversationPlayerStoryIdleRetainedRequest;
static void peDecodeArr_gShootingGalleryPierceConversationPlayerStoryIdleRetainedRequest(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/shooting_gallery_pierce/_gShootingGalleryPierceConversationPlayerStoryIdleRetainedRequest", _gShootingGalleryPierceConversationPlayerStoryIdleRetainedRequest, peDecodeArr_gShootingGalleryPierceConversationPlayerStoryIdleRetainedRequest);
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
static AnimationPlayRequest _gShootingGalleryPierceConversationPlayerStoryIdleRequest;
static void peDecodeArr_gShootingGalleryPierceConversationPlayerStoryIdleRequest(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/shooting_gallery_pierce/_gShootingGalleryPierceConversationPlayerStoryIdleRequest", _gShootingGalleryPierceConversationPlayerStoryIdleRequest, peDecodeArr_gShootingGalleryPierceConversationPlayerStoryIdleRequest);
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
static AnimationPlayRequest _gShootingGalleryPierceConversationPlayerStoryAskHalRequest;
static void peDecodeArr_gShootingGalleryPierceConversationPlayerStoryAskHalRequest(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/shooting_gallery_pierce/_gShootingGalleryPierceConversationPlayerStoryAskHalRequest", _gShootingGalleryPierceConversationPlayerStoryAskHalRequest, peDecodeArr_gShootingGalleryPierceConversationPlayerStoryAskHalRequest);
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
static AnimationPlayRequest _gShootingGalleryPierceConversationPlayerStoryTalkRequest;
static void peDecodeArr_gShootingGalleryPierceConversationPlayerStoryTalkRequest(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/shooting_gallery_pierce/_gShootingGalleryPierceConversationPlayerStoryTalkRequest", _gShootingGalleryPierceConversationPlayerStoryTalkRequest, peDecodeArr_gShootingGalleryPierceConversationPlayerStoryTalkRequest);
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
static AnimationPlayRequest _gShootingGalleryPierceConversationPlayerStoryAskNmcsRequest;
static void peDecodeArr_gShootingGalleryPierceConversationPlayerStoryAskNmcsRequest(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/shooting_gallery_pierce/_gShootingGalleryPierceConversationPlayerStoryAskNmcsRequest", _gShootingGalleryPierceConversationPlayerStoryAskNmcsRequest, peDecodeArr_gShootingGalleryPierceConversationPlayerStoryAskNmcsRequest);
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
static AnimationPlayRequest _gShootingGalleryPierceConversationPlayerStoryImGoingRequest;
static void peDecodeArr_gShootingGalleryPierceConversationPlayerStoryImGoingRequest(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/shooting_gallery_pierce/_gShootingGalleryPierceConversationPlayerStoryImGoingRequest", _gShootingGalleryPierceConversationPlayerStoryImGoingRequest, peDecodeArr_gShootingGalleryPierceConversationPlayerStoryImGoingRequest);
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
static AnimationPlayRequest _gShootingGalleryPierceConversationPlayerStoryBoastRequest;
static void peDecodeArr_gShootingGalleryPierceConversationPlayerStoryBoastRequest(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/shooting_gallery_pierce/_gShootingGalleryPierceConversationPlayerStoryBoastRequest", _gShootingGalleryPierceConversationPlayerStoryBoastRequest, peDecodeArr_gShootingGalleryPierceConversationPlayerStoryBoastRequest);
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
static AnimationPlayRequest _gShootingGalleryPierceConversationPlayerStory17Request;
static void peDecodeArr_gShootingGalleryPierceConversationPlayerStory17Request(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/shooting_gallery_pierce/_gShootingGalleryPierceConversationPlayerStory17Request", _gShootingGalleryPierceConversationPlayerStory17Request, peDecodeArr_gShootingGalleryPierceConversationPlayerStory17Request);
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
static AnimationPlayRequest _gShootingGalleryPierceConversationPlayerStory24Request;
static void peDecodeArr_gShootingGalleryPierceConversationPlayerStory24Request(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/shooting_gallery_pierce/_gShootingGalleryPierceConversationPlayerStory24Request", _gShootingGalleryPierceConversationPlayerStory24Request, peDecodeArr_gShootingGalleryPierceConversationPlayerStory24Request);
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
static AnimationPlayRequest _gShootingGalleryPierceConversationPlayerStoryTalk2Request;
static void peDecodeArr_gShootingGalleryPierceConversationPlayerStoryTalk2Request(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/shooting_gallery_pierce/_gShootingGalleryPierceConversationPlayerStoryTalk2Request", _gShootingGalleryPierceConversationPlayerStoryTalk2Request, peDecodeArr_gShootingGalleryPierceConversationPlayerStoryTalk2Request);
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
static AnimationPlayRequest _gShootingGalleryPierceConversationPlayerStoryListenRequest;
static void peDecodeArr_gShootingGalleryPierceConversationPlayerStoryListenRequest(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/shooting_gallery_pierce/_gShootingGalleryPierceConversationPlayerStoryListenRequest", _gShootingGalleryPierceConversationPlayerStoryListenRequest, peDecodeArr_gShootingGalleryPierceConversationPlayerStoryListenRequest);
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
static AnimationPlayRequest _gShootingGalleryPierceConversationPlayerSlot12Request;
static void peDecodeArr_gShootingGalleryPierceConversationPlayerSlot12Request(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/shooting_gallery_pierce/_gShootingGalleryPierceConversationPlayerSlot12Request", _gShootingGalleryPierceConversationPlayerSlot12Request, peDecodeArr_gShootingGalleryPierceConversationPlayerSlot12Request);
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
static AnimationPlayRequest _gShootingGalleryPierceConversationPlayerSlot13Request;
static void peDecodeArr_gShootingGalleryPierceConversationPlayerSlot13Request(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/shooting_gallery_pierce/_gShootingGalleryPierceConversationPlayerSlot13Request", _gShootingGalleryPierceConversationPlayerSlot13Request, peDecodeArr_gShootingGalleryPierceConversationPlayerSlot13Request);
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
static AnimationPlayRequest _gShootingGalleryPierceConversationPlayerSlot14Request;
static void peDecodeArr_gShootingGalleryPierceConversationPlayerSlot14Request(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/shooting_gallery_pierce/_gShootingGalleryPierceConversationPlayerSlot14Request", _gShootingGalleryPierceConversationPlayerSlot14Request, peDecodeArr_gShootingGalleryPierceConversationPlayerSlot14Request);
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
static AnimationPlayRequest _gShootingGalleryPierceConversationPlayerSlot15Request;
static void peDecodeArr_gShootingGalleryPierceConversationPlayerSlot15Request(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/shooting_gallery_pierce/_gShootingGalleryPierceConversationPlayerSlot15Request", _gShootingGalleryPierceConversationPlayerSlot15Request, peDecodeArr_gShootingGalleryPierceConversationPlayerSlot15Request);
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
static AnimationPlayRequest _gShootingGalleryPierceConversationPlayerSlot16Request;
static void peDecodeArr_gShootingGalleryPierceConversationPlayerSlot16Request(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/shooting_gallery_pierce/_gShootingGalleryPierceConversationPlayerSlot16Request", _gShootingGalleryPierceConversationPlayerSlot16Request, peDecodeArr_gShootingGalleryPierceConversationPlayerSlot16Request);
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
static AnimationPlayRequest _gShootingGalleryPierceConversationPlayerSlot17Request;
static void peDecodeArr_gShootingGalleryPierceConversationPlayerSlot17Request(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/shooting_gallery_pierce/_gShootingGalleryPierceConversationPlayerSlot17Request", _gShootingGalleryPierceConversationPlayerSlot17Request, peDecodeArr_gShootingGalleryPierceConversationPlayerSlot17Request);
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
static AnimationPlayRequest _gShootingGalleryPierceConversationPlayerSlot18Request;
static void peDecodeArr_gShootingGalleryPierceConversationPlayerSlot18Request(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/shooting_gallery_pierce/_gShootingGalleryPierceConversationPlayerSlot18Request", _gShootingGalleryPierceConversationPlayerSlot18Request, peDecodeArr_gShootingGalleryPierceConversationPlayerSlot18Request);
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
static AnimationPlayRequest _gShootingGalleryPierceConversationPlayerSlot19Request;
static void peDecodeArr_gShootingGalleryPierceConversationPlayerSlot19Request(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/shooting_gallery_pierce/_gShootingGalleryPierceConversationPlayerSlot19Request", _gShootingGalleryPierceConversationPlayerSlot19Request, peDecodeArr_gShootingGalleryPierceConversationPlayerSlot19Request);
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
static AnimationBankCopyRequest _gShootingGalleryPierceConversationPlayerBankCopyRequest;
static void peDecodeArr_gShootingGalleryPierceConversationPlayerBankCopyRequest(void* base, const unsigned char* src, size_t n)
{
    AnimationBankCopyRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationBankCopyRequest(&dst[k], src + k * 8);
    dst[0].sets = (void*)&_gShootingGalleryPierceConversationPlayerAnimationSets;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/shooting_gallery_pierce/_gShootingGalleryPierceConversationPlayerBankCopyRequest", _gShootingGalleryPierceConversationPlayerBankCopyRequest, peDecodeArr_gShootingGalleryPierceConversationPlayerBankCopyRequest);
static ActorTransform _gShootingGalleryPierceStoryPierceOpeningPlacement;
#include "port/asset_bind.h"
PE_ASSET_BIND("room/shooting_gallery_pierce/_gShootingGalleryPierceStoryPierceOpeningPlacement", _gShootingGalleryPierceStoryPierceOpeningPlacement);
static ActorTransform _gShootingGalleryPierceStoryPierceDialoguePlacement;
#include "port/asset_bind.h"
PE_ASSET_BIND("room/shooting_gallery_pierce/_gShootingGalleryPierceStoryPierceDialoguePlacement", _gShootingGalleryPierceStoryPierceDialoguePlacement);
static ActorTransform _gShootingGalleryPierceConversationPierceReturnPlacement;
#include "port/asset_bind.h"
PE_ASSET_BIND("room/shooting_gallery_pierce/_gShootingGalleryPierceConversationPierceReturnPlacement", _gShootingGalleryPierceConversationPierceReturnPlacement);
static ActorTransform _gShootingGalleryPierceStoryPlayerDialoguePlacement;
#include "port/asset_bind.h"
PE_ASSET_BIND("room/shooting_gallery_pierce/_gShootingGalleryPierceStoryPlayerDialoguePlacement", _gShootingGalleryPierceStoryPlayerDialoguePlacement);
static ActorTransform _gShootingGalleryPierceConversationPlayerReturnPlacement;
#include "port/asset_bind.h"
PE_ASSET_BIND("room/shooting_gallery_pierce/_gShootingGalleryPierceConversationPlayerReturnPlacement", _gShootingGalleryPierceConversationPlayerReturnPlacement);
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
static AnimationPlayRequest _gShootingGalleryPierceConversationPlayerIdleRequest;
static void peDecodeArr_gShootingGalleryPierceConversationPlayerIdleRequest(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/shooting_gallery_pierce/_gShootingGalleryPierceConversationPlayerIdleRequest", _gShootingGalleryPierceConversationPlayerIdleRequest, peDecodeArr_gShootingGalleryPierceConversationPlayerIdleRequest);
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
static AnimationPlayRequest _gShootingGalleryPierceConversationPlayerIdleBlendRequest;
static void peDecodeArr_gShootingGalleryPierceConversationPlayerIdleBlendRequest(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/shooting_gallery_pierce/_gShootingGalleryPierceConversationPlayerIdleBlendRequest", _gShootingGalleryPierceConversationPlayerIdleBlendRequest, peDecodeArr_gShootingGalleryPierceConversationPlayerIdleBlendRequest);
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
EvsCommand gShootingGalleryPiercePierceStoryScript[117];
static void peDecodeArr_gShootingGalleryPiercePierceStoryScript(void* base, const unsigned char* src, size_t n)
{
    EvsCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_EvsCommand(&dst[k], src + k * 24);
    dst[0].operand0.storage = (void*)&_shootingGalleryPierceSetConversationCap;
    dst[2].operand3.storage = &_gShootingGalleryPierceConversationPlayerIdleBlendRequest;
    dst[8].operand3.storage = &_gShootingGalleryPierceConversationPlayerBankCopyRequest;
    dst[11].operand3.storage = &_gShootingGalleryPierceStoryPierceOpeningPlacement;
    dst[12].operand3.storage = &_gShootingGalleryPiercePiercePhoneListenRequest;
    dst[16].operand3.storage = &_gShootingGalleryPiercePiercePhoneTalkRequest;
    dst[18].operand3.storage = &_gShootingGalleryPiercePiercePhoneListenRequest;
    dst[20].operand3.storage = &_gShootingGalleryPiercePierceStory3Request;
    dst[24].operand3.storage = &_gShootingGalleryPiercePierceStory4Request;
    dst[26].operand3.storage = &_gShootingGalleryPiercePierceRestRequest;
    dst[28].operand3.storage = &_gShootingGalleryPierceStoryPierceDialoguePlacement;
    dst[29].operand3.storage = &_gShootingGalleryPierceStoryPlayerDialoguePlacement;
    dst[30].operand3.storage = &_gShootingGalleryPierceConversationPlayerStoryTalkRequest;
    dst[32].operand3.storage = &_gShootingGalleryPierceConversationPlayerStoryIdleRequest;
    dst[34].operand3.storage = &_gShootingGalleryPierceConversationPlayerStoryAskHalRequest;
    dst[36].operand3.storage = &_gShootingGalleryPierceConversationPlayerStoryIdleRequest;
    dst[38].operand3.storage = &_gShootingGalleryPiercePierceQuipRequest;
    dst[40].operand3.storage = &_gShootingGalleryPiercePierceRestRequest;
    dst[42].operand3.storage = &_gShootingGalleryPiercePierceTalkRequest;
    dst[44].operand3.storage = &_gShootingGalleryPiercePierceTalkEndBlendRequest;
    dst[46].operand3.storage = &_gShootingGalleryPiercePierceTalkRequest;
    dst[48].operand3.storage = &_gShootingGalleryPiercePierceTalkEndBlendRequest;
    dst[49].operand3.storage = &_gShootingGalleryPierceConversationPlayerStoryTalk2Request;
    dst[51].operand3.storage = &_gShootingGalleryPiercePierceRestRequest;
    dst[54].operand3.storage = &_gShootingGalleryPierceConversationPlayerStoryListenRequest;
    dst[55].operand3.storage = &_gShootingGalleryPiercePierceTeaseRequest;
    dst[57].operand3.storage = &_gShootingGalleryPierceConversationPlayerStoryIdleRequest;
    dst[60].operand3.storage = &_gShootingGalleryPiercePierceCorrectHimselfBlendRequest;
    dst[62].operand3.storage = &_gShootingGalleryPiercePierceCorrectHimselfEndBlendRequest;
    dst[64].operand3.storage = &_gShootingGalleryPiercePierceTalkEndBlendRequest;
    dst[66].operand3.storage = &_gShootingGalleryPiercePierceRestBlendRequest;
    dst[68].operand3.storage = &_gShootingGalleryPierceConversationPlayerStoryAskNmcsRequest;
    dst[71].operand3.storage = &_gShootingGalleryPierceConversationPlayerStory17Request;
    dst[73].operand3.storage = &_gShootingGalleryPierceConversationPlayerStoryIdleRequest;
    dst[74].operand3.storage = &_gShootingGalleryPiercePierceStory17Request;
    dst[76].operand3.storage = &_gShootingGalleryPiercePierceRestBlendRequest;
    dst[78].operand3.storage = &_gShootingGalleryPierceConversationPlayerStoryTalkRequest;
    dst[80].operand3.storage = &_gShootingGalleryPierceConversationPlayerStoryIdleRequest;
    dst[82].operand3.storage = &_gShootingGalleryPierceConversationPlayerStoryTalk2Request;
    dst[84].operand3.storage = &_gShootingGalleryPierceConversationPlayerStoryListenRequest;
    dst[85].operand3.storage = &_gShootingGalleryPiercePierceTalkRequest;
    dst[87].operand3.storage = &_gShootingGalleryPiercePierceTalkEndBlendRequest;
    dst[88].operand3.storage = &_gShootingGalleryPierceConversationPlayerStoryIdleRequest;
    dst[90].operand3.storage = &_gShootingGalleryPiercePierceTalkRequest;
    dst[92].operand3.storage = &_gShootingGalleryPiercePierceTalkEndBlendRequest;
    dst[94].operand3.storage = &_gShootingGalleryPiercePierceRestRequest;
    dst[96].operand3.storage = &_gShootingGalleryPierceConversationPlayerStoryImGoingRequest;
    dst[98].operand3.storage = &_gShootingGalleryPierceConversationPlayerStoryIdleRequest;
    dst[100].operand3.storage = &_gShootingGalleryPierceConversationPlayerStoryBoastRequest;
    dst[102].operand3.storage = &_gShootingGalleryPierceConversationPlayerStory24Request;
    dst[104].operand3.storage = &_gShootingGalleryPierceConversationPlayerStoryIdleRequest;
    dst[105].operand3.storage = &_gShootingGalleryPiercePierceWarnRequest;
    dst[109].operand3.storage = &_gShootingGalleryPierceConversationPierceReturnPlacement;
    dst[110].operand3.storage = &_gShootingGalleryPiercePierceRestRequest;
    dst[111].operand3.storage = &_gShootingGalleryPierceConversationPlayerIdleRequest;
    dst[112].operand3.storage = &_gShootingGalleryPierceConversationPlayerReturnPlacement;
    dst[115].operand0.storage = (void*)&_shootingGalleryPierceSetConversationCap;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/shooting_gallery_pierce/gShootingGalleryPiercePierceStoryScript", gShootingGalleryPiercePierceStoryScript, peDecodeArr_gShootingGalleryPiercePierceStoryScript);
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
EvsCommand gShootingGalleryPiercePierceStorySkipScript[15];
static void peDecodeArr_gShootingGalleryPiercePierceStorySkipScript(void* base, const unsigned char* src, size_t n)
{
    EvsCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_EvsCommand(&dst[k], src + k * 24);
    dst[6].operand3.storage = &_gShootingGalleryPierceConversationPlayerIdleRequest;
    dst[7].operand3.storage = &_gShootingGalleryPierceConversationPierceReturnPlacement;
    dst[8].operand3.storage = &_gShootingGalleryPiercePierceRestRequest;
    dst[9].operand3.storage = &_gShootingGalleryPierceConversationPlayerReturnPlacement;
    dst[13].operand0.storage = (void*)&_shootingGalleryPierceSetConversationCap;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/shooting_gallery_pierce/gShootingGalleryPiercePierceStorySkipScript", gShootingGalleryPiercePierceStorySkipScript, peDecodeArr_gShootingGalleryPiercePierceStorySkipScript);
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
static EvsCommand _gShootingGalleryPiercePierceFirstTalkScript[11];
static void peDecodeArr_gShootingGalleryPiercePierceFirstTalkScript(void* base, const unsigned char* src, size_t n)
{
    EvsCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_EvsCommand(&dst[k], src + k * 24);
    dst[0].operand0.storage = (void*)&_shootingGalleryPierceSetConversationCap;
    dst[2].operand3.storage = &_gShootingGalleryPierceConversationPlayerIdleBlendRequest;
    dst[3].operand3.storage = &_gShootingGalleryPiercePierceShortTalkRequest;
    dst[5].operand3.storage = &_gShootingGalleryPiercePierceShortTalkEndRequest;
    dst[7].operand3.storage = &_gShootingGalleryPiercePierceRestRequest;
    dst[9].operand0.storage = (void*)&_shootingGalleryPierceSetConversationCap;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/shooting_gallery_pierce/_gShootingGalleryPiercePierceFirstTalkScript", _gShootingGalleryPiercePierceFirstTalkScript, peDecodeArr_gShootingGalleryPiercePierceFirstTalkScript);
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
static EvsCommand _gShootingGalleryPiercePierceSecondTalkScript[43];
static void peDecodeArr_gShootingGalleryPiercePierceSecondTalkScript(void* base, const unsigned char* src, size_t n)
{
    EvsCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_EvsCommand(&dst[k], src + k * 24);
    dst[0].operand0.storage = (void*)&_shootingGalleryPierceSetConversationCap;
    dst[1].operand3.storage = &_gShootingGalleryPierceConversationPlayerBankCopyRequest;
    dst[3].operand3.storage = &_gShootingGalleryPierceConversationPlayerIdleBlendRequest;
    dst[4].operand3.storage = &_gShootingGalleryPiercePierceShortTalkRequest;
    dst[6].operand3.storage = &_gShootingGalleryPiercePierceShortTalkEndRequest;
    dst[8].operand3.storage = &_gShootingGalleryPiercePierceRestRequest;
    dst[10].operand3.storage = &_gShootingGalleryPiercePierceQuipRequest;
    dst[12].operand3.storage = &_gShootingGalleryPiercePierceRestRequest;
    dst[14].operand3.storage = &_gShootingGalleryPierceConversationPlayerSlot13Request;
    dst[16].operand3.storage = &_gShootingGalleryPierceConversationPlayerSlot14Request;
    dst[18].operand3.storage = &_gShootingGalleryPiercePierceShortTalkRequest;
    dst[20].operand3.storage = &_gShootingGalleryPiercePierceShortTalkEndRequest;
    dst[22].operand3.storage = &_gShootingGalleryPiercePierceRestRequest;
    dst[24].operand3.storage = &_gShootingGalleryPierceConversationPlayerSlot15Request;
    dst[26].operand3.storage = &_gShootingGalleryPierceConversationPlayerSlot16Request;
    dst[28].operand3.storage = &_gShootingGalleryPierceConversationPlayerSlot17Request;
    dst[30].operand3.storage = &_gShootingGalleryPiercePierceShortTalkRequest;
    dst[32].operand3.storage = &_gShootingGalleryPiercePierceShortTalkEndRequest;
    dst[34].operand3.storage = &_gShootingGalleryPiercePierceRestRequest;
    dst[36].operand3.storage = &_gShootingGalleryPierceConversationPlayerSlot18Request;
    dst[38].operand3.storage = &_gShootingGalleryPierceConversationPlayerSlot19Request;
    dst[41].operand0.storage = (void*)&_shootingGalleryPierceSetConversationCap;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/shooting_gallery_pierce/_gShootingGalleryPiercePierceSecondTalkScript", _gShootingGalleryPiercePierceSecondTalkScript, peDecodeArr_gShootingGalleryPiercePierceSecondTalkScript);
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
static EvsCommand _gShootingGalleryPiercePierceRepeatTalkScript[11];
static void peDecodeArr_gShootingGalleryPiercePierceRepeatTalkScript(void* base, const unsigned char* src, size_t n)
{
    EvsCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_EvsCommand(&dst[k], src + k * 24);
    dst[0].operand0.storage = (void*)&_shootingGalleryPierceSetConversationCap;
    dst[2].operand3.storage = &_gShootingGalleryPierceConversationPlayerIdleBlendRequest;
    dst[3].operand3.storage = &_gShootingGalleryPiercePierceShortTalkRequest;
    dst[5].operand3.storage = &_gShootingGalleryPiercePierceShortTalkEndRequest;
    dst[7].operand3.storage = &_gShootingGalleryPiercePierceRestRequest;
    dst[9].operand0.storage = (void*)&_shootingGalleryPierceSetConversationCap;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/shooting_gallery_pierce/_gShootingGalleryPiercePierceRepeatTalkScript", _gShootingGalleryPiercePierceRepeatTalkScript, peDecodeArr_gShootingGalleryPiercePierceRepeatTalkScript);
