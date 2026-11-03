/* rooms/mist/r18/package: written from its room instance by tools/buildsteps/gen_room_inc.py. */

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
static AnimationBankCopyRequest _gMistR18PlayerBriefingBankCopyRequest;
static void peDecodeArr_gMistR18PlayerBriefingBankCopyRequest(void* base, const unsigned char* src, size_t n)
{
    AnimationBankCopyRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationBankCopyRequest(&dst[k], src + k * 8);
    dst[0].sets = (void*)&_gMistR18PlayerBriefingAnimationSets;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_r18/_gMistR18PlayerBriefingBankCopyRequest", _gMistR18PlayerBriefingBankCopyRequest, peDecodeArr_gMistR18PlayerBriefingBankCopyRequest);
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
static AnimationPlayRequest _gMistR18PlayerBaseClip1Request;
static void peDecodeArr_gMistR18PlayerBaseClip1Request(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_r18/_gMistR18PlayerBaseClip1Request", _gMistR18PlayerBaseClip1Request, peDecodeArr_gMistR18PlayerBaseClip1Request);
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
static AnimationPlayRequest _gMistR18PlayerBriefingClip48Request;
static void peDecodeArr_gMistR18PlayerBriefingClip48Request(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_r18/_gMistR18PlayerBriefingClip48Request", _gMistR18PlayerBriefingClip48Request, peDecodeArr_gMistR18PlayerBriefingClip48Request);
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
static AnimationPlayRequest _gMistR18PlayerBriefingClip49Request;
static void peDecodeArr_gMistR18PlayerBriefingClip49Request(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_r18/_gMistR18PlayerBriefingClip49Request", _gMistR18PlayerBriefingClip49Request, peDecodeArr_gMistR18PlayerBriefingClip49Request);
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
static AnimationPlayRequest _gMistR18PlayerBriefingClip50Request;
static void peDecodeArr_gMistR18PlayerBriefingClip50Request(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_r18/_gMistR18PlayerBriefingClip50Request", _gMistR18PlayerBriefingClip50Request, peDecodeArr_gMistR18PlayerBriefingClip50Request);
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
static AnimationPlayRequest _gMistR18PlayerBriefingClip51Request;
static void peDecodeArr_gMistR18PlayerBriefingClip51Request(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_r18/_gMistR18PlayerBriefingClip51Request", _gMistR18PlayerBriefingClip51Request, peDecodeArr_gMistR18PlayerBriefingClip51Request);
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
static AnimationPlayRequest _gMistR18PlayerBriefingClip52Request;
static void peDecodeArr_gMistR18PlayerBriefingClip52Request(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_r18/_gMistR18PlayerBriefingClip52Request", _gMistR18PlayerBriefingClip52Request, peDecodeArr_gMistR18PlayerBriefingClip52Request);
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
static AnimationPlayRequest _gMistR18PlayerBriefingClip53Request;
static void peDecodeArr_gMistR18PlayerBriefingClip53Request(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_r18/_gMistR18PlayerBriefingClip53Request", _gMistR18PlayerBriefingClip53Request, peDecodeArr_gMistR18PlayerBriefingClip53Request);
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
static AnimationPlayRequest _gMistR18PlayerBriefingClip54Request;
static void peDecodeArr_gMistR18PlayerBriefingClip54Request(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_r18/_gMistR18PlayerBriefingClip54Request", _gMistR18PlayerBriefingClip54Request, peDecodeArr_gMistR18PlayerBriefingClip54Request);
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
static AnimationPlayRequest _gMistR18PlayerBriefingClip55Request;
static void peDecodeArr_gMistR18PlayerBriefingClip55Request(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_r18/_gMistR18PlayerBriefingClip55Request", _gMistR18PlayerBriefingClip55Request, peDecodeArr_gMistR18PlayerBriefingClip55Request);
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
static AnimationPlayRequest _gMistR18PlayerBriefingClip56Request;
static void peDecodeArr_gMistR18PlayerBriefingClip56Request(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_r18/_gMistR18PlayerBriefingClip56Request", _gMistR18PlayerBriefingClip56Request, peDecodeArr_gMistR18PlayerBriefingClip56Request);
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
static AnimationPlayRequest _gMistR18PlayerBriefingClip57Request;
static void peDecodeArr_gMistR18PlayerBriefingClip57Request(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_r18/_gMistR18PlayerBriefingClip57Request", _gMistR18PlayerBriefingClip57Request, peDecodeArr_gMistR18PlayerBriefingClip57Request);
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
static AnimationPlayRequest _gMistR18BaldwinResetClip1Request;
static void peDecodeArr_gMistR18BaldwinResetClip1Request(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_r18/_gMistR18BaldwinResetClip1Request", _gMistR18BaldwinResetClip1Request, peDecodeArr_gMistR18BaldwinResetClip1Request);
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
static AnimationPlayRequest _gMistR18BaldwinIntroClip1Request;
static void peDecodeArr_gMistR18BaldwinIntroClip1Request(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_r18/_gMistR18BaldwinIntroClip1Request", _gMistR18BaldwinIntroClip1Request, peDecodeArr_gMistR18BaldwinIntroClip1Request);
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
static AnimationPlayRequest _gMistR18BaldwinBriefingClip2Request;
static void peDecodeArr_gMistR18BaldwinBriefingClip2Request(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_r18/_gMistR18BaldwinBriefingClip2Request", _gMistR18BaldwinBriefingClip2Request, peDecodeArr_gMistR18BaldwinBriefingClip2Request);
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
static AnimationPlayRequest _gMistR18BaldwinBriefingClip3Request;
static void peDecodeArr_gMistR18BaldwinBriefingClip3Request(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_r18/_gMistR18BaldwinBriefingClip3Request", _gMistR18BaldwinBriefingClip3Request, peDecodeArr_gMistR18BaldwinBriefingClip3Request);
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
static AnimationPlayRequest _gMistR18BaldwinBriefingClip4Request;
static void peDecodeArr_gMistR18BaldwinBriefingClip4Request(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_r18/_gMistR18BaldwinBriefingClip4Request", _gMistR18BaldwinBriefingClip4Request, peDecodeArr_gMistR18BaldwinBriefingClip4Request);
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
static AnimationPlayRequest _gMistR18BaldwinBriefingClip5Request;
static void peDecodeArr_gMistR18BaldwinBriefingClip5Request(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_r18/_gMistR18BaldwinBriefingClip5Request", _gMistR18BaldwinBriefingClip5Request, peDecodeArr_gMistR18BaldwinBriefingClip5Request);
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
static AnimationPlayRequest _gMistR18BaldwinBriefingClip6Request;
static void peDecodeArr_gMistR18BaldwinBriefingClip6Request(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_r18/_gMistR18BaldwinBriefingClip6Request", _gMistR18BaldwinBriefingClip6Request, peDecodeArr_gMistR18BaldwinBriefingClip6Request);
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
static AnimationPlayRequest _gMistR18BaldwinBriefingClip7Request;
static void peDecodeArr_gMistR18BaldwinBriefingClip7Request(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_r18/_gMistR18BaldwinBriefingClip7Request", _gMistR18BaldwinBriefingClip7Request, peDecodeArr_gMistR18BaldwinBriefingClip7Request);
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
static AnimationPlayRequest _gMistR18BaldwinBriefingClip8Request;
static void peDecodeArr_gMistR18BaldwinBriefingClip8Request(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_r18/_gMistR18BaldwinBriefingClip8Request", _gMistR18BaldwinBriefingClip8Request, peDecodeArr_gMistR18BaldwinBriefingClip8Request);
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
static AnimationPlayRequest _gMistR18BaldwinBriefingClip9Request;
static void peDecodeArr_gMistR18BaldwinBriefingClip9Request(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_r18/_gMistR18BaldwinBriefingClip9Request", _gMistR18BaldwinBriefingClip9Request, peDecodeArr_gMistR18BaldwinBriefingClip9Request);
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
static AnimationPlayRequest _gMistR18BaldwinReminderClip10Request;
static void peDecodeArr_gMistR18BaldwinReminderClip10Request(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_r18/_gMistR18BaldwinReminderClip10Request", _gMistR18BaldwinReminderClip10Request, peDecodeArr_gMistR18BaldwinReminderClip10Request);
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
static AnimationPlayRequest _gMistR18RupertResetClip1Request;
static void peDecodeArr_gMistR18RupertResetClip1Request(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_r18/_gMistR18RupertResetClip1Request", _gMistR18RupertResetClip1Request, peDecodeArr_gMistR18RupertResetClip1Request);
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
static AnimationPlayRequest _gMistR18RupertIntroClip1Request;
static void peDecodeArr_gMistR18RupertIntroClip1Request(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_r18/_gMistR18RupertIntroClip1Request", _gMistR18RupertIntroClip1Request, peDecodeArr_gMistR18RupertIntroClip1Request);
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
static AnimationPlayRequest _gMistR18RupertBriefingClip2Request;
static void peDecodeArr_gMistR18RupertBriefingClip2Request(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_r18/_gMistR18RupertBriefingClip2Request", _gMistR18RupertBriefingClip2Request, peDecodeArr_gMistR18RupertBriefingClip2Request);
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
static AnimationPlayRequest _gMistR18RupertBriefingClip3Request;
static void peDecodeArr_gMistR18RupertBriefingClip3Request(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_r18/_gMistR18RupertBriefingClip3Request", _gMistR18RupertBriefingClip3Request, peDecodeArr_gMistR18RupertBriefingClip3Request);
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
static AnimationPlayRequest _gMistR18RupertBriefingClip4Request;
static void peDecodeArr_gMistR18RupertBriefingClip4Request(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_r18/_gMistR18RupertBriefingClip4Request", _gMistR18RupertBriefingClip4Request, peDecodeArr_gMistR18RupertBriefingClip4Request);
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
static AnimationPlayRequest _gMistR18RupertBriefingClip5Request;
static void peDecodeArr_gMistR18RupertBriefingClip5Request(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_r18/_gMistR18RupertBriefingClip5Request", _gMistR18RupertBriefingClip5Request, peDecodeArr_gMistR18RupertBriefingClip5Request);
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
static AnimationPlayRequest _gMistR18RupertBriefingClip6Request;
static void peDecodeArr_gMistR18RupertBriefingClip6Request(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_r18/_gMistR18RupertBriefingClip6Request", _gMistR18RupertBriefingClip6Request, peDecodeArr_gMistR18RupertBriefingClip6Request);
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
static AnimationPlayRequest _gMistR18RupertBriefingClip7Request;
static void peDecodeArr_gMistR18RupertBriefingClip7Request(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_r18/_gMistR18RupertBriefingClip7Request", _gMistR18RupertBriefingClip7Request, peDecodeArr_gMistR18RupertBriefingClip7Request);
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
static AnimationPlayRequest _gMistR18RupertReminderClip8Request;
static void peDecodeArr_gMistR18RupertReminderClip8Request(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_r18/_gMistR18RupertReminderClip8Request", _gMistR18RupertReminderClip8Request, peDecodeArr_gMistR18RupertReminderClip8Request);
static ActorTransform _gMistR18BriefingPlayerPlacement;
#include "port/asset_bind.h"
PE_ASSET_BIND("room/mist_r18/_gMistR18BriefingPlayerPlacement", _gMistR18BriefingPlayerPlacement);
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
static ActorCommand _gMistR18BaldwinShowFirstHeldModelCommand;
static void peDecodeArr_gMistR18BaldwinShowFirstHeldModelCommand(void* base, const unsigned char* src, size_t n)
{
    ActorCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_ActorCommand(&dst[k], src + k * 4);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_r18/_gMistR18BaldwinShowFirstHeldModelCommand", _gMistR18BaldwinShowFirstHeldModelCommand, peDecodeArr_gMistR18BaldwinShowFirstHeldModelCommand);
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
static ActorCommand _gMistR18BaldwinHideFirstHeldModelCommand;
static void peDecodeArr_gMistR18BaldwinHideFirstHeldModelCommand(void* base, const unsigned char* src, size_t n)
{
    ActorCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_ActorCommand(&dst[k], src + k * 4);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_r18/_gMistR18BaldwinHideFirstHeldModelCommand", _gMistR18BaldwinHideFirstHeldModelCommand, peDecodeArr_gMistR18BaldwinHideFirstHeldModelCommand);
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
static ActorCommand _gMistR18BaldwinShowSecondHeldModelCommand;
static void peDecodeArr_gMistR18BaldwinShowSecondHeldModelCommand(void* base, const unsigned char* src, size_t n)
{
    ActorCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_ActorCommand(&dst[k], src + k * 4);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_r18/_gMistR18BaldwinShowSecondHeldModelCommand", _gMistR18BaldwinShowSecondHeldModelCommand, peDecodeArr_gMistR18BaldwinShowSecondHeldModelCommand);
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
static ActorCommand _gMistR18BaldwinHideSecondHeldModelCommand;
static void peDecodeArr_gMistR18BaldwinHideSecondHeldModelCommand(void* base, const unsigned char* src, size_t n)
{
    ActorCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_ActorCommand(&dst[k], src + k * 4);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_r18/_gMistR18BaldwinHideSecondHeldModelCommand", _gMistR18BaldwinHideSecondHeldModelCommand, peDecodeArr_gMistR18BaldwinHideSecondHeldModelCommand);
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
static EvsCommand _gMistR18IntroScript[56];
static void peDecodeArr_gMistR18IntroScript(void* base, const unsigned char* src, size_t n)
{
    EvsCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_EvsCommand(&dst[k], src + k * 24);
    dst[0].operand0.storage = (void*)&_mistR18PrepareBriefingScene;
    dst[2].operand0.storage = (void*)&_mistR18StartSceneScriptPause;
    dst[4].operand0.storage = (void*)&_mistR18EnqueueScenePlayback;
    dst[7].operand0.storage = (void*)&_mistR18SpawnPlacedProp;
    dst[8].operand3.storage = &_gMistR18PlayerBriefingBankCopyRequest;
    dst[9].operand3.storage = &_gMistR18PlayerBaseClip1Request;
    dst[15].operand0.storage = (void*)&_mistR18SpawnBriefingCaption;
    dst[17].operand0.storage = (void*)&_mistR18StartBackdropCrossfade;
    dst[23].operand3.storage = &_gMistR18BriefingPlayerPlacement;
    dst[28].operand3.storage = &_gMistR18PlayerBriefingClip48Request;
    dst[29].operand3.storage = &_gMistR18BaldwinIntroClip1Request;
    dst[30].operand3.storage = &_gMistR18RupertIntroClip1Request;
    dst[31].operand0.storage = (void*)&_mistR18FinishSceneStream;
    dst[37].operand3.storage = &_gMistR18PlayerBriefingClip49Request;
    dst[39].operand3.storage = &_gMistR18BaldwinBriefingClip2Request;
    dst[41].operand3.storage = &_gMistR18BaldwinBriefingClip3Request;
    dst[46].operand3.storage = &_gMistR18BaldwinShowFirstHeldModelCommand;
    dst[51].operand3.storage = &_gMistR18BaldwinHideFirstHeldModelCommand;
    dst[52].operand3.storage = &_gMistR18BaldwinResetClip1Request;
    dst[53].operand3.storage = &_gMistR18RupertResetClip1Request;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_r18/_gMistR18IntroScript", _gMistR18IntroScript, peDecodeArr_gMistR18IntroScript);
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
static EvsCommand _gMistR18FirstHeldModelScript[37];
static void peDecodeArr_gMistR18FirstHeldModelScript(void* base, const unsigned char* src, size_t n)
{
    EvsCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_EvsCommand(&dst[k], src + k * 24);
    dst[1].operand0.storage = (void*)&_mistR18SpawnAttachedModel;
    dst[2].operand3.storage = &_gMistR18BriefingPlayerPlacement;
    dst[3].operand3.storage = &_gMistR18PlayerBriefingBankCopyRequest;
    dst[7].operand3.storage = &_gMistR18PlayerBriefingClip50Request;
    dst[8].operand3.storage = &_gMistR18BaldwinResetClip1Request;
    dst[9].operand3.storage = &_gMistR18RupertResetClip1Request;
    dst[14].operand3.storage = &_gMistR18PlayerBriefingClip51Request;
    dst[15].operand3.storage = &_gMistR18BaldwinBriefingClip4Request;
    dst[16].operand3.storage = &_gMistR18RupertBriefingClip2Request;
    dst[18].operand3.storage = &_gMistR18BaldwinBriefingClip5Request;
    dst[20].operand3.storage = &_gMistR18PlayerBriefingClip52Request;
    dst[22].operand3.storage = &_gMistR18PlayerBriefingClip53Request;
    dst[23].operand3.storage = &_gMistR18BaldwinBriefingClip6Request;
    dst[24].operand3.storage = &_gMistR18RupertBriefingClip3Request;
    dst[26].operand3.storage = &_gMistR18BaldwinShowSecondHeldModelCommand;
    dst[27].operand0.storage = (void*)&_mistR18KillPlacedProp;
    dst[32].operand0.storage = (void*)&_mistR18KillAttachedModel;
    dst[33].operand3.storage = &_gMistR18BaldwinHideSecondHeldModelCommand;
    dst[34].operand3.storage = &_gMistR18BaldwinResetClip1Request;
    dst[35].operand3.storage = &_gMistR18RupertResetClip1Request;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_r18/_gMistR18FirstHeldModelScript", _gMistR18FirstHeldModelScript, peDecodeArr_gMistR18FirstHeldModelScript);
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
static EvsCommand _gMistR18DepartureScript[41];
static void peDecodeArr_gMistR18DepartureScript(void* base, const unsigned char* src, size_t n)
{
    EvsCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_EvsCommand(&dst[k], src + k * 24);
    dst[2].operand0.storage = (void*)&_mistR18SpawnAttachedModel;
    dst[3].operand3.storage = &_gMistR18BriefingPlayerPlacement;
    dst[4].operand3.storage = &_gMistR18PlayerBriefingBankCopyRequest;
    dst[5].operand3.storage = &_gMistR18PlayerBriefingClip54Request;
    dst[9].operand3.storage = &_gMistR18BaldwinResetClip1Request;
    dst[10].operand3.storage = &_gMistR18RupertResetClip1Request;
    dst[12].operand0.storage = (void*)&_mistR18SetOrderingDepthShift;
    dst[16].operand0.storage = (void*)&_mistR18SetOrderingDepthShift;
    dst[17].operand3.storage = &_gMistR18PlayerBriefingClip55Request;
    dst[18].operand3.storage = &_gMistR18BaldwinBriefingClip7Request;
    dst[19].operand3.storage = &_gMistR18RupertBriefingClip4Request;
    dst[21].operand3.storage = &_gMistR18RupertBriefingClip5Request;
    dst[23].operand3.storage = &_gMistR18BaldwinBriefingClip8Request;
    dst[25].operand3.storage = &_gMistR18RupertBriefingClip6Request;
    dst[27].operand3.storage = &_gMistR18PlayerBriefingClip56Request;
    dst[28].operand3.storage = &_gMistR18BaldwinBriefingClip9Request;
    dst[29].operand3.storage = &_gMistR18RupertBriefingClip7Request;
    dst[34].operand0.storage = (void*)&_mistR18KillAttachedModel;
    dst[35].operand3.storage = &_gMistR18BaldwinResetClip1Request;
    dst[36].operand3.storage = &_gMistR18RupertResetClip1Request;
    dst[38].operand0.storage = (void*)&_mistR18SetOrderingDepthShift;
    dst[39].operand0.storage = (void*)&_mistR18ReloadParkingWithStarterLoadout;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_r18/_gMistR18DepartureScript", _gMistR18DepartureScript, peDecodeArr_gMistR18DepartureScript);
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
static EvsCommand _gMistR18PlacePropScript[16];
static void peDecodeArr_gMistR18PlacePropScript(void* base, const unsigned char* src, size_t n)
{
    EvsCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_EvsCommand(&dst[k], src + k * 24);
    dst[0].operand3.storage = &_gMistR18BriefingPlayerPlacement;
    dst[1].operand3.storage = &_gMistR18PlayerBriefingBankCopyRequest;
    dst[2].operand3.storage = &_gMistR18PlayerBaseClip1Request;
    dst[6].operand0.storage = (void*)&_mistR18KillPlacedProp;
    dst[13].operand0.storage = (void*)&_mistR18SpawnPlacedProp;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_r18/_gMistR18PlacePropScript", _gMistR18PlacePropScript, peDecodeArr_gMistR18PlacePropScript);
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
static EvsCommand _gMistR18OpenKeyItemsScript[16];
static void peDecodeArr_gMistR18OpenKeyItemsScript(void* base, const unsigned char* src, size_t n)
{
    EvsCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_EvsCommand(&dst[k], src + k * 24);
    dst[1].operand3.storage = &_gMistR18PlayerBriefingBankCopyRequest;
    dst[2].operand3.storage = &_gMistR18BriefingPlayerPlacement;
    dst[6].operand3.storage = &_gMistR18PlayerBriefingClip57Request;
    dst[7].operand3.storage = &_gMistR18BaldwinResetClip1Request;
    dst[8].operand3.storage = &_gMistR18RupertResetClip1Request;
    dst[11].operand0.storage = (void*)&_mistR18OpenKeyItemMenu;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_r18/_gMistR18OpenKeyItemsScript", _gMistR18OpenKeyItemsScript, peDecodeArr_gMistR18OpenKeyItemsScript);
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
static EvsCommand _gMistR18DryfieldMapReminderScript[20];
static void peDecodeArr_gMistR18DryfieldMapReminderScript(void* base, const unsigned char* src, size_t n)
{
    EvsCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_EvsCommand(&dst[k], src + k * 24);
    dst[1].operand3.storage = &_gMistR18PlayerBriefingBankCopyRequest;
    dst[2].operand3.storage = &_gMistR18BriefingPlayerPlacement;
    dst[6].operand3.storage = &_gMistR18PlayerBriefingBankCopyRequest;
    dst[7].operand3.storage = &_gMistR18PlayerBriefingClip57Request;
    dst[8].operand3.storage = &_gMistR18BaldwinReminderClip10Request;
    dst[9].operand3.storage = &_gMistR18RupertReminderClip8Request;
    dst[15].operand0.storage = (void*)&_mistR18OpenKeyItemMenu;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_r18/_gMistR18DryfieldMapReminderScript", _gMistR18DryfieldMapReminderScript, peDecodeArr_gMistR18DryfieldMapReminderScript);
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
static EvsCommand _gMistR18SkipIntroScript[8];
static void peDecodeArr_gMistR18SkipIntroScript(void* base, const unsigned char* src, size_t n)
{
    EvsCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_EvsCommand(&dst[k], src + k * 24);
    dst[2].operand0.storage = (void*)&_mistR18CancelScene;
    dst[3].operand3.storage = &_gMistR18BaldwinHideFirstHeldModelCommand;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_r18/_gMistR18SkipIntroScript", _gMistR18SkipIntroScript, peDecodeArr_gMistR18SkipIntroScript);
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
static EvsCommand _gMistR18SkipFirstHeldModelScript[8];
static void peDecodeArr_gMistR18SkipFirstHeldModelScript(void* base, const unsigned char* src, size_t n)
{
    EvsCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_EvsCommand(&dst[k], src + k * 24);
    dst[2].operand0.storage = (void*)&_mistR18KillPlacedProp;
    dst[3].operand0.storage = (void*)&_mistR18KillAttachedModel;
    dst[4].operand3.storage = &_gMistR18BaldwinHideSecondHeldModelCommand;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_r18/_gMistR18SkipFirstHeldModelScript", _gMistR18SkipFirstHeldModelScript, peDecodeArr_gMistR18SkipFirstHeldModelScript);
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
static EvsCommand _gMistR18SkipDepartureScript[3];
static void peDecodeArr_gMistR18SkipDepartureScript(void* base, const unsigned char* src, size_t n)
{
    EvsCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_EvsCommand(&dst[k], src + k * 24);
    dst[0].operand0.storage = (void*)&_mistR18SetOrderingDepthShift;
    dst[1].operand0.storage = (void*)&_mistR18ReloadParkingWithStarterLoadout;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_r18/_gMistR18SkipDepartureScript", _gMistR18SkipDepartureScript, peDecodeArr_gMistR18SkipDepartureScript);
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
static EvsCommand _gMistR18SkipPlacePropScript[7];
static void peDecodeArr_gMistR18SkipPlacePropScript(void* base, const unsigned char* src, size_t n)
{
    EvsCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_EvsCommand(&dst[k], src + k * 24);
    dst[2].operand0.storage = (void*)&_mistR18KillPlacedProp;
    dst[3].operand0.storage = (void*)&_mistR18SpawnPlacedProp;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_r18/_gMistR18SkipPlacePropScript", _gMistR18SkipPlacePropScript, peDecodeArr_gMistR18SkipPlacePropScript);
