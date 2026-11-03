/* rooms/akropolis/sanctuary/package: written from its room instance by tools/buildsteps/gen_room_inc.py. */

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
static AnimationBankCopyRequest _gAkropolisSanctuaryPlayerSceneBankExtensionRequest;
static void peDecodeArr_gAkropolisSanctuaryPlayerSceneBankExtensionRequest(void* base, const unsigned char* src, size_t n)
{
    AnimationBankCopyRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationBankCopyRequest(&dst[k], src + k * 8);
    dst[0].sets = (void*)&_gAkropolisSanctuaryPlayerSceneAnimationSets;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_sanctuary/_gAkropolisSanctuaryPlayerSceneBankExtensionRequest", _gAkropolisSanctuaryPlayerSceneBankExtensionRequest, peDecodeArr_gAkropolisSanctuaryPlayerSceneBankExtensionRequest);
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
static AnimationPlayRequest _gAkropolisSanctuaryPlayerSceneClip47Request;
static void peDecodeArr_gAkropolisSanctuaryPlayerSceneClip47Request(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_sanctuary/_gAkropolisSanctuaryPlayerSceneClip47Request", _gAkropolisSanctuaryPlayerSceneClip47Request, peDecodeArr_gAkropolisSanctuaryPlayerSceneClip47Request);
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
static AnimationPlayRequest _gAkropolisSanctuaryPlayerSceneClip48Request;
static void peDecodeArr_gAkropolisSanctuaryPlayerSceneClip48Request(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_sanctuary/_gAkropolisSanctuaryPlayerSceneClip48Request", _gAkropolisSanctuaryPlayerSceneClip48Request, peDecodeArr_gAkropolisSanctuaryPlayerSceneClip48Request);
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
static AnimationPlayRequest _gAkropolisSanctuaryPlayerSceneClip49Request;
static void peDecodeArr_gAkropolisSanctuaryPlayerSceneClip49Request(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_sanctuary/_gAkropolisSanctuaryPlayerSceneClip49Request", _gAkropolisSanctuaryPlayerSceneClip49Request, peDecodeArr_gAkropolisSanctuaryPlayerSceneClip49Request);
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
static AnimationPlayRequest _gAkropolisSanctuaryPlayerSceneClip50Request;
static void peDecodeArr_gAkropolisSanctuaryPlayerSceneClip50Request(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_sanctuary/_gAkropolisSanctuaryPlayerSceneClip50Request", _gAkropolisSanctuaryPlayerSceneClip50Request, peDecodeArr_gAkropolisSanctuaryPlayerSceneClip50Request);
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
static AnimationPlayRequest _gAkropolisSanctuaryPlayerSceneClip51Request;
static void peDecodeArr_gAkropolisSanctuaryPlayerSceneClip51Request(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_sanctuary/_gAkropolisSanctuaryPlayerSceneClip51Request", _gAkropolisSanctuaryPlayerSceneClip51Request, peDecodeArr_gAkropolisSanctuaryPlayerSceneClip51Request);
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
static AnimationPlayRequest _gAkropolisSanctuaryPlayerSceneClip52Request;
static void peDecodeArr_gAkropolisSanctuaryPlayerSceneClip52Request(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_sanctuary/_gAkropolisSanctuaryPlayerSceneClip52Request", _gAkropolisSanctuaryPlayerSceneClip52Request, peDecodeArr_gAkropolisSanctuaryPlayerSceneClip52Request);
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
static AnimationPlayRequest _gAkropolisSanctuaryPlayerSceneClip52LongBlendRequest;
static void peDecodeArr_gAkropolisSanctuaryPlayerSceneClip52LongBlendRequest(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_sanctuary/_gAkropolisSanctuaryPlayerSceneClip52LongBlendRequest", _gAkropolisSanctuaryPlayerSceneClip52LongBlendRequest, peDecodeArr_gAkropolisSanctuaryPlayerSceneClip52LongBlendRequest);
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
static AnimationPlayRequest _gAkropolisSanctuaryPlayerSceneClip53Request;
static void peDecodeArr_gAkropolisSanctuaryPlayerSceneClip53Request(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_sanctuary/_gAkropolisSanctuaryPlayerSceneClip53Request", _gAkropolisSanctuaryPlayerSceneClip53Request, peDecodeArr_gAkropolisSanctuaryPlayerSceneClip53Request);
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
static AnimationPlayRequest _gAkropolisSanctuaryPlayerSceneClip54Request;
static void peDecodeArr_gAkropolisSanctuaryPlayerSceneClip54Request(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_sanctuary/_gAkropolisSanctuaryPlayerSceneClip54Request", _gAkropolisSanctuaryPlayerSceneClip54Request, peDecodeArr_gAkropolisSanctuaryPlayerSceneClip54Request);
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
static AnimationPlayRequest _gAkropolisSanctuaryPlayerSpecialWeaponRestoreRequest;
static void peDecodeArr_gAkropolisSanctuaryPlayerSpecialWeaponRestoreRequest(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_sanctuary/_gAkropolisSanctuaryPlayerSpecialWeaponRestoreRequest", _gAkropolisSanctuaryPlayerSpecialWeaponRestoreRequest, peDecodeArr_gAkropolisSanctuaryPlayerSpecialWeaponRestoreRequest);
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
static AnimationPlayRequest _gAkropolisSanctuaryPlayerWeaponRestoreRequest;
static void peDecodeArr_gAkropolisSanctuaryPlayerWeaponRestoreRequest(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_sanctuary/_gAkropolisSanctuaryPlayerWeaponRestoreRequest", _gAkropolisSanctuaryPlayerWeaponRestoreRequest, peDecodeArr_gAkropolisSanctuaryPlayerWeaponRestoreRequest);
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
static AnimationPlayRequest _gAkropolisSanctuaryNo9Clip1Request;
static void peDecodeArr_gAkropolisSanctuaryNo9Clip1Request(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_sanctuary/_gAkropolisSanctuaryNo9Clip1Request", _gAkropolisSanctuaryNo9Clip1Request, peDecodeArr_gAkropolisSanctuaryNo9Clip1Request);
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
static AnimationPlayRequest _gAkropolisSanctuaryNo9Clip2Request;
static void peDecodeArr_gAkropolisSanctuaryNo9Clip2Request(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_sanctuary/_gAkropolisSanctuaryNo9Clip2Request", _gAkropolisSanctuaryNo9Clip2Request, peDecodeArr_gAkropolisSanctuaryNo9Clip2Request);
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
static AnimationPlayRequest _gAkropolisSanctuaryNo9Clip3Request;
static void peDecodeArr_gAkropolisSanctuaryNo9Clip3Request(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_sanctuary/_gAkropolisSanctuaryNo9Clip3Request", _gAkropolisSanctuaryNo9Clip3Request, peDecodeArr_gAkropolisSanctuaryNo9Clip3Request);
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
static AnimationPlayRequest _gAkropolisSanctuaryNo9Clip4Request;
static void peDecodeArr_gAkropolisSanctuaryNo9Clip4Request(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_sanctuary/_gAkropolisSanctuaryNo9Clip4Request", _gAkropolisSanctuaryNo9Clip4Request, peDecodeArr_gAkropolisSanctuaryNo9Clip4Request);
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
static AnimationPlayRequest _gAkropolisSanctuaryRupertClip1Request;
static void peDecodeArr_gAkropolisSanctuaryRupertClip1Request(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_sanctuary/_gAkropolisSanctuaryRupertClip1Request", _gAkropolisSanctuaryRupertClip1Request, peDecodeArr_gAkropolisSanctuaryRupertClip1Request);
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
static AnimationPlayRequest _gAkropolisSanctuaryRupertClip2Request;
static void peDecodeArr_gAkropolisSanctuaryRupertClip2Request(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_sanctuary/_gAkropolisSanctuaryRupertClip2Request", _gAkropolisSanctuaryRupertClip2Request, peDecodeArr_gAkropolisSanctuaryRupertClip2Request);
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
static AnimationPlayRequest _gAkropolisSanctuaryRupertClip3Request;
static void peDecodeArr_gAkropolisSanctuaryRupertClip3Request(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_sanctuary/_gAkropolisSanctuaryRupertClip3Request", _gAkropolisSanctuaryRupertClip3Request, peDecodeArr_gAkropolisSanctuaryRupertClip3Request);
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
static AnimationPlayRequest _gAkropolisSanctuaryRupertClip4Request;
static void peDecodeArr_gAkropolisSanctuaryRupertClip4Request(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_sanctuary/_gAkropolisSanctuaryRupertClip4Request", _gAkropolisSanctuaryRupertClip4Request, peDecodeArr_gAkropolisSanctuaryRupertClip4Request);
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
static AnimationPlayRequest _gAkropolisSanctuaryRupertClip5Request;
static void peDecodeArr_gAkropolisSanctuaryRupertClip5Request(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_sanctuary/_gAkropolisSanctuaryRupertClip5Request", _gAkropolisSanctuaryRupertClip5Request, peDecodeArr_gAkropolisSanctuaryRupertClip5Request);
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
static AnimationPlayRequest _gAkropolisSanctuaryRupertClip6Request;
static void peDecodeArr_gAkropolisSanctuaryRupertClip6Request(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_sanctuary/_gAkropolisSanctuaryRupertClip6Request", _gAkropolisSanctuaryRupertClip6Request, peDecodeArr_gAkropolisSanctuaryRupertClip6Request);
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
static AnimationPlayRequest _gAkropolisSanctuaryRupertRestoredClip3Request;
static void peDecodeArr_gAkropolisSanctuaryRupertRestoredClip3Request(void* base, const unsigned char* src, size_t n)
{
    AnimationPlayRequest* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AnimationPlayRequest(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_sanctuary/_gAkropolisSanctuaryRupertRestoredClip3Request", _gAkropolisSanctuaryRupertRestoredClip3Request, peDecodeArr_gAkropolisSanctuaryRupertRestoredClip3Request);
static EvsSceneKey _gAkropolisSanctuaryArrivalSceneKey;
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_sanctuary/_gAkropolisSanctuaryArrivalSceneKey", _gAkropolisSanctuaryArrivalSceneKey);
static EvsSceneKey _gAkropolisSanctuaryUnusedSceneKey;
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_sanctuary/_gAkropolisSanctuaryUnusedSceneKey", _gAkropolisSanctuaryUnusedSceneKey);
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
static EvsCommand _gAkropolisSanctuaryArrivalScript[121];
static void peDecodeArr_gAkropolisSanctuaryArrivalScript(void* base, const unsigned char* src, size_t n)
{
    EvsCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_EvsCommand(&dst[k], src + k * 24);
    dst[1].operand3.storage = &_gAkropolisSanctuarySceneOriginPlacement;
    dst[4].operand3.storage = &_gAkropolisSanctuaryPlayerWeaponClip1Request;
    dst[5].operand3.storage = &_gAkropolisSanctuaryPlayerSceneBankExtensionRequest;
    dst[6].operand0.storage = &_gAkropolisSanctuaryArrivalSceneKey;
    dst[10].operand0.storage = (void*)&_akropolisSanctuaryApplyScriptSpriteSelection;
    dst[11].operand0.storage = (void*)&_akropolisSanctuaryApplyScriptSpriteSelection;
    dst[12].operand3.storage = &_gAkropolisSanctuaryRupertClip1Request;
    dst[13].operand3.storage = &_gAkropolisSanctuaryNo9Clip1Request;
    dst[14].operand3.storage = &_gAkropolisSanctuaryPlayerSceneStartPlacement;
    dst[22].operand0.storage = (void*)&_akropolisSanctuaryRestorePlayerWeaponAnimation;
    dst[27].operand3.storage = &_gAkropolisSanctuaryRupertClip2Request;
    dst[28].operand3.storage = &_gAkropolisSanctuaryNo9Clip2Request;
    dst[31].operand3.storage = &_gAkropolisSanctuaryNo9Clip3Request;
    dst[36].operand3.storage = &_gAkropolisSanctuaryNo9Clip4Request;
    dst[37].operand3.storage = &_gAkropolisSanctuarySceneOriginPlacement;
    dst[38].operand3.storage = &_gAkropolisSanctuaryPlayerSceneClip47Request;
    dst[39].operand0.storage = (void*)&_akropolisSanctuaryApplyScriptSpriteSelection;
    dst[44].operand0.storage = (void*)&_akropolisSanctuaryApplyScriptSpriteSelection;
    dst[53].operand3.storage = &_gAkropolisSanctuaryPlayerSceneClip48Placement;
    dst[54].operand3.storage = &_gAkropolisSanctuaryPlayerSceneClip48Request;
    dst[55].operand3.storage = &_gAkropolisSanctuaryRupertRestoredPlacement;
    dst[56].operand3.storage = &_gAkropolisSanctuaryRupertClip4Request;
    dst[58].operand3.storage = &_gAkropolisSanctuaryRupertClip3Request;
    dst[59].operand3.storage = &_gAkropolisSanctuaryPlayerSceneClip52Request;
    dst[62].operand3.storage = &_gAkropolisSanctuaryPlayerSceneClip49Placement;
    dst[63].operand3.storage = &_gAkropolisSanctuaryPlayerSceneClip49Request;
    dst[65].operand3.storage = &_gAkropolisSanctuaryPlayerSceneClip50Request;
    dst[67].operand3.storage = &_gAkropolisSanctuaryPlayerSceneClip52Request;
    dst[69].operand3.storage = &_gAkropolisSanctuaryRupertClip5Request;
    dst[71].operand3.storage = &_gAkropolisSanctuaryRupertClip6Request;
    dst[73].operand3.storage = &_gAkropolisSanctuaryRupertClip3Request;
    dst[75].operand3.storage = &_gAkropolisSanctuaryPlayerSceneClip49Request;
    dst[77].operand3.storage = &_gAkropolisSanctuaryPlayerSceneClip50Request;
    dst[79].operand3.storage = &_gAkropolisSanctuaryPlayerSceneClip52Request;
    dst[81].operand3.storage = &_gAkropolisSanctuaryRupertClip5Request;
    dst[83].operand3.storage = &_gAkropolisSanctuaryRupertClip6Request;
    dst[85].operand3.storage = &_gAkropolisSanctuaryRupertClip3Request;
    dst[87].operand3.storage = &_gAkropolisSanctuaryPlayerSceneClip49Request;
    dst[89].operand3.storage = &_gAkropolisSanctuaryPlayerSceneClip50Request;
    dst[91].operand3.storage = &_gAkropolisSanctuaryPlayerSceneClip52Request;
    dst[93].operand3.storage = &_gAkropolisSanctuaryRupertClip5Request;
    dst[95].operand3.storage = &_gAkropolisSanctuaryRupertClip6Request;
    dst[97].operand3.storage = &_gAkropolisSanctuaryRupertClip3Request;
    dst[99].operand3.storage = &_gAkropolisSanctuaryPlayerSceneClip51Request;
    dst[101].operand3.storage = &_gAkropolisSanctuaryPlayerSceneClip52LongBlendRequest;
    dst[103].operand3.storage = &_gAkropolisSanctuaryPlayerSceneClip53Request;
    dst[106].operand3.storage = &_gAkropolisSanctuaryPlayerSceneClosingPlacement;
    dst[108].operand3.storage = &_gAkropolisSanctuaryPlayerSceneClip54Request;
    dst[109].operand3.storage = &_gAkropolisSanctuaryRupertClip6Request;
    dst[111].operand3.storage = &_gAkropolisSanctuaryRupertClip3Request;
    dst[115].operand3.storage = &_gAkropolisSanctuaryPlayerWeaponClip1Request;
    dst[118].operand3.storage = &_gAkropolisSanctuaryPlayerSceneEndPlacement;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_sanctuary/_gAkropolisSanctuaryArrivalScript", _gAkropolisSanctuaryArrivalScript, peDecodeArr_gAkropolisSanctuaryArrivalScript);
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
static EvsCommand _gAkropolisSanctuaryArrivalSkipScript[18];
static void peDecodeArr_gAkropolisSanctuaryArrivalSkipScript(void* base, const unsigned char* src, size_t n)
{
    EvsCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_EvsCommand(&dst[k], src + k * 24);
    dst[4].operand3.storage = &_gAkropolisSanctuaryPlayerWeaponClip1Request;
    dst[5].operand3.storage = &_gAkropolisSanctuaryPlayerSceneEndPlacement;
    dst[6].operand3.storage = &_gAkropolisSanctuaryRupertRestoredPlacement;
    dst[7].operand3.storage = &_gAkropolisSanctuaryRupertRestoredClip3Request;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_sanctuary/_gAkropolisSanctuaryArrivalSkipScript", _gAkropolisSanctuaryArrivalSkipScript, peDecodeArr_gAkropolisSanctuaryArrivalSkipScript);
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
static EvsCommand _gAkropolisSanctuaryBlockerScript[11];
static void peDecodeArr_gAkropolisSanctuaryBlockerScript(void* base, const unsigned char* src, size_t n)
{
    EvsCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_EvsCommand(&dst[k], src + k * 24);
    dst[1].operand3.storage = &_gAkropolisSanctuaryPlayerWeaponClip1Request;
    dst[3].operand3.storage = &_gAkropolisSanctuaryRupertClip5Request;
    dst[6].operand3.storage = &_gAkropolisSanctuaryRupertClip6Request;
    dst[8].operand3.storage = &_gAkropolisSanctuaryRupertClip3Request;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_sanctuary/_gAkropolisSanctuaryBlockerScript", _gAkropolisSanctuaryBlockerScript, peDecodeArr_gAkropolisSanctuaryBlockerScript);
