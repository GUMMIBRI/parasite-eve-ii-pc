/* rooms/akropolis/sanctuary/package: written from its room instance by tools/buildsteps/gen_room_inc.py. */

#include "types.h"
#include "gameplay/sprites.h"

static SpriteBatch _gAkropolisSanctuaryView1SpriteBatches[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_sanctuary/_gAkropolisSanctuaryView1SpriteBatches", _gAkropolisSanctuaryView1SpriteBatches);
#ifndef PE_DECODE_SpriteSource
#define PE_DECODE_SpriteSource
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
static void peDecode_SpriteSource(SpriteSource* dst, const unsigned char* src)
{
    { uint16_t v; memcpy(&v, src + 0, 2); dst->tpage = v; }
    { uint16_t v; memcpy(&v, src + 2, 2); dst->clut = v; }
    { int16_t v; memcpy(&v, src + 4, 2); dst->size.fields.w = v; }
    { int16_t v; memcpy(&v, src + 6, 2); dst->size.fields.h = v; }
    { int16_t v; memcpy(&v, src + 8, 2); dst->x0 = v; }
    { int16_t v; memcpy(&v, src + 10, 2); dst->y0 = v; }
    { uint16_t v; memcpy(&v, src + 12, 2); dst->depth = v; }
    { uint8_t v; memcpy(&v, src + 14, 1); dst->uv.fields.u0 = v; }
    { uint8_t v; memcpy(&v, src + 15, 1); dst->uv.fields.v0 = v; }
    { uint8_t v; memcpy(&v, src + 16, 1); dst->r0 = v; }
    { uint8_t v; memcpy(&v, src + 17, 1); dst->g0 = v; }
    { uint8_t v; memcpy(&v, src + 18, 1); dst->b0 = v; }
    { uint8_t v; memcpy(&v, src + 19, 1); dst->codeFlags = v; }
}

#endif
static SpriteSource _gAkropolisSanctuaryView2SpriteSources[40];
static void peDecodeArr_gAkropolisSanctuaryView2SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_sanctuary/_gAkropolisSanctuaryView2SpriteSources", _gAkropolisSanctuaryView2SpriteSources, peDecodeArr_gAkropolisSanctuaryView2SpriteSources);
static SpriteBatch _gAkropolisSanctuaryView2SpriteBatches[6];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_sanctuary/_gAkropolisSanctuaryView2SpriteBatches", _gAkropolisSanctuaryView2SpriteBatches);
#ifndef PE_DECODE_SpriteSource
#define PE_DECODE_SpriteSource
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
static void peDecode_SpriteSource(SpriteSource* dst, const unsigned char* src)
{
    { uint16_t v; memcpy(&v, src + 0, 2); dst->tpage = v; }
    { uint16_t v; memcpy(&v, src + 2, 2); dst->clut = v; }
    { int16_t v; memcpy(&v, src + 4, 2); dst->size.fields.w = v; }
    { int16_t v; memcpy(&v, src + 6, 2); dst->size.fields.h = v; }
    { int16_t v; memcpy(&v, src + 8, 2); dst->x0 = v; }
    { int16_t v; memcpy(&v, src + 10, 2); dst->y0 = v; }
    { uint16_t v; memcpy(&v, src + 12, 2); dst->depth = v; }
    { uint8_t v; memcpy(&v, src + 14, 1); dst->uv.fields.u0 = v; }
    { uint8_t v; memcpy(&v, src + 15, 1); dst->uv.fields.v0 = v; }
    { uint8_t v; memcpy(&v, src + 16, 1); dst->r0 = v; }
    { uint8_t v; memcpy(&v, src + 17, 1); dst->g0 = v; }
    { uint8_t v; memcpy(&v, src + 18, 1); dst->b0 = v; }
    { uint8_t v; memcpy(&v, src + 19, 1); dst->codeFlags = v; }
}

#endif
static SpriteSource _gAkropolisSanctuaryView3SpriteSources[50];
static void peDecodeArr_gAkropolisSanctuaryView3SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_sanctuary/_gAkropolisSanctuaryView3SpriteSources", _gAkropolisSanctuaryView3SpriteSources, peDecodeArr_gAkropolisSanctuaryView3SpriteSources);
static SpriteBatch _gAkropolisSanctuaryView3SpriteBatches[8];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_sanctuary/_gAkropolisSanctuaryView3SpriteBatches", _gAkropolisSanctuaryView3SpriteBatches);
#ifndef PE_DECODE_SpriteSource
#define PE_DECODE_SpriteSource
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
static void peDecode_SpriteSource(SpriteSource* dst, const unsigned char* src)
{
    { uint16_t v; memcpy(&v, src + 0, 2); dst->tpage = v; }
    { uint16_t v; memcpy(&v, src + 2, 2); dst->clut = v; }
    { int16_t v; memcpy(&v, src + 4, 2); dst->size.fields.w = v; }
    { int16_t v; memcpy(&v, src + 6, 2); dst->size.fields.h = v; }
    { int16_t v; memcpy(&v, src + 8, 2); dst->x0 = v; }
    { int16_t v; memcpy(&v, src + 10, 2); dst->y0 = v; }
    { uint16_t v; memcpy(&v, src + 12, 2); dst->depth = v; }
    { uint8_t v; memcpy(&v, src + 14, 1); dst->uv.fields.u0 = v; }
    { uint8_t v; memcpy(&v, src + 15, 1); dst->uv.fields.v0 = v; }
    { uint8_t v; memcpy(&v, src + 16, 1); dst->r0 = v; }
    { uint8_t v; memcpy(&v, src + 17, 1); dst->g0 = v; }
    { uint8_t v; memcpy(&v, src + 18, 1); dst->b0 = v; }
    { uint8_t v; memcpy(&v, src + 19, 1); dst->codeFlags = v; }
}

#endif
static SpriteSource _gAkropolisSanctuaryView4SpriteSources[46];
static void peDecodeArr_gAkropolisSanctuaryView4SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_sanctuary/_gAkropolisSanctuaryView4SpriteSources", _gAkropolisSanctuaryView4SpriteSources, peDecodeArr_gAkropolisSanctuaryView4SpriteSources);
static SpriteBatch _gAkropolisSanctuaryView4SpriteBatches[10];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_sanctuary/_gAkropolisSanctuaryView4SpriteBatches", _gAkropolisSanctuaryView4SpriteBatches);
#ifndef PE_DECODE_SpriteSource
#define PE_DECODE_SpriteSource
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
static void peDecode_SpriteSource(SpriteSource* dst, const unsigned char* src)
{
    { uint16_t v; memcpy(&v, src + 0, 2); dst->tpage = v; }
    { uint16_t v; memcpy(&v, src + 2, 2); dst->clut = v; }
    { int16_t v; memcpy(&v, src + 4, 2); dst->size.fields.w = v; }
    { int16_t v; memcpy(&v, src + 6, 2); dst->size.fields.h = v; }
    { int16_t v; memcpy(&v, src + 8, 2); dst->x0 = v; }
    { int16_t v; memcpy(&v, src + 10, 2); dst->y0 = v; }
    { uint16_t v; memcpy(&v, src + 12, 2); dst->depth = v; }
    { uint8_t v; memcpy(&v, src + 14, 1); dst->uv.fields.u0 = v; }
    { uint8_t v; memcpy(&v, src + 15, 1); dst->uv.fields.v0 = v; }
    { uint8_t v; memcpy(&v, src + 16, 1); dst->r0 = v; }
    { uint8_t v; memcpy(&v, src + 17, 1); dst->g0 = v; }
    { uint8_t v; memcpy(&v, src + 18, 1); dst->b0 = v; }
    { uint8_t v; memcpy(&v, src + 19, 1); dst->codeFlags = v; }
}

#endif
static SpriteSource _gAkropolisSanctuaryView5SpriteSources[41];
static void peDecodeArr_gAkropolisSanctuaryView5SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_sanctuary/_gAkropolisSanctuaryView5SpriteSources", _gAkropolisSanctuaryView5SpriteSources, peDecodeArr_gAkropolisSanctuaryView5SpriteSources);
static SpriteBatch _gAkropolisSanctuaryView5SpriteBatches[9];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_sanctuary/_gAkropolisSanctuaryView5SpriteBatches", _gAkropolisSanctuaryView5SpriteBatches);
#ifndef PE_DECODE_SpriteSource
#define PE_DECODE_SpriteSource
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
static void peDecode_SpriteSource(SpriteSource* dst, const unsigned char* src)
{
    { uint16_t v; memcpy(&v, src + 0, 2); dst->tpage = v; }
    { uint16_t v; memcpy(&v, src + 2, 2); dst->clut = v; }
    { int16_t v; memcpy(&v, src + 4, 2); dst->size.fields.w = v; }
    { int16_t v; memcpy(&v, src + 6, 2); dst->size.fields.h = v; }
    { int16_t v; memcpy(&v, src + 8, 2); dst->x0 = v; }
    { int16_t v; memcpy(&v, src + 10, 2); dst->y0 = v; }
    { uint16_t v; memcpy(&v, src + 12, 2); dst->depth = v; }
    { uint8_t v; memcpy(&v, src + 14, 1); dst->uv.fields.u0 = v; }
    { uint8_t v; memcpy(&v, src + 15, 1); dst->uv.fields.v0 = v; }
    { uint8_t v; memcpy(&v, src + 16, 1); dst->r0 = v; }
    { uint8_t v; memcpy(&v, src + 17, 1); dst->g0 = v; }
    { uint8_t v; memcpy(&v, src + 18, 1); dst->b0 = v; }
    { uint8_t v; memcpy(&v, src + 19, 1); dst->codeFlags = v; }
}

#endif
static SpriteSource _gAkropolisSanctuaryView6SpriteSources[32];
static void peDecodeArr_gAkropolisSanctuaryView6SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_sanctuary/_gAkropolisSanctuaryView6SpriteSources", _gAkropolisSanctuaryView6SpriteSources, peDecodeArr_gAkropolisSanctuaryView6SpriteSources);
static SpriteBatch _gAkropolisSanctuaryView6SpriteBatches[6];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_sanctuary/_gAkropolisSanctuaryView6SpriteBatches", _gAkropolisSanctuaryView6SpriteBatches);
#ifndef PE_DECODE_SpriteSource
#define PE_DECODE_SpriteSource
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
static void peDecode_SpriteSource(SpriteSource* dst, const unsigned char* src)
{
    { uint16_t v; memcpy(&v, src + 0, 2); dst->tpage = v; }
    { uint16_t v; memcpy(&v, src + 2, 2); dst->clut = v; }
    { int16_t v; memcpy(&v, src + 4, 2); dst->size.fields.w = v; }
    { int16_t v; memcpy(&v, src + 6, 2); dst->size.fields.h = v; }
    { int16_t v; memcpy(&v, src + 8, 2); dst->x0 = v; }
    { int16_t v; memcpy(&v, src + 10, 2); dst->y0 = v; }
    { uint16_t v; memcpy(&v, src + 12, 2); dst->depth = v; }
    { uint8_t v; memcpy(&v, src + 14, 1); dst->uv.fields.u0 = v; }
    { uint8_t v; memcpy(&v, src + 15, 1); dst->uv.fields.v0 = v; }
    { uint8_t v; memcpy(&v, src + 16, 1); dst->r0 = v; }
    { uint8_t v; memcpy(&v, src + 17, 1); dst->g0 = v; }
    { uint8_t v; memcpy(&v, src + 18, 1); dst->b0 = v; }
    { uint8_t v; memcpy(&v, src + 19, 1); dst->codeFlags = v; }
}

#endif
static SpriteSource _gAkropolisSanctuaryView7SpriteSources[24];
static void peDecodeArr_gAkropolisSanctuaryView7SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_sanctuary/_gAkropolisSanctuaryView7SpriteSources", _gAkropolisSanctuaryView7SpriteSources, peDecodeArr_gAkropolisSanctuaryView7SpriteSources);
static SpriteBatch _gAkropolisSanctuaryView7SpriteBatches[7];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_sanctuary/_gAkropolisSanctuaryView7SpriteBatches", _gAkropolisSanctuaryView7SpriteBatches);
#ifndef PE_DECODE_SpriteSource
#define PE_DECODE_SpriteSource
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
static void peDecode_SpriteSource(SpriteSource* dst, const unsigned char* src)
{
    { uint16_t v; memcpy(&v, src + 0, 2); dst->tpage = v; }
    { uint16_t v; memcpy(&v, src + 2, 2); dst->clut = v; }
    { int16_t v; memcpy(&v, src + 4, 2); dst->size.fields.w = v; }
    { int16_t v; memcpy(&v, src + 6, 2); dst->size.fields.h = v; }
    { int16_t v; memcpy(&v, src + 8, 2); dst->x0 = v; }
    { int16_t v; memcpy(&v, src + 10, 2); dst->y0 = v; }
    { uint16_t v; memcpy(&v, src + 12, 2); dst->depth = v; }
    { uint8_t v; memcpy(&v, src + 14, 1); dst->uv.fields.u0 = v; }
    { uint8_t v; memcpy(&v, src + 15, 1); dst->uv.fields.v0 = v; }
    { uint8_t v; memcpy(&v, src + 16, 1); dst->r0 = v; }
    { uint8_t v; memcpy(&v, src + 17, 1); dst->g0 = v; }
    { uint8_t v; memcpy(&v, src + 18, 1); dst->b0 = v; }
    { uint8_t v; memcpy(&v, src + 19, 1); dst->codeFlags = v; }
}

#endif
static SpriteSource _gAkropolisSanctuaryView8SpriteSources[9];
static void peDecodeArr_gAkropolisSanctuaryView8SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_sanctuary/_gAkropolisSanctuaryView8SpriteSources", _gAkropolisSanctuaryView8SpriteSources, peDecodeArr_gAkropolisSanctuaryView8SpriteSources);
static SpriteBatch _gAkropolisSanctuaryView8SpriteBatches[4];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_sanctuary/_gAkropolisSanctuaryView8SpriteBatches", _gAkropolisSanctuaryView8SpriteBatches);
#ifndef PE_DECODE_SpriteSource
#define PE_DECODE_SpriteSource
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
static void peDecode_SpriteSource(SpriteSource* dst, const unsigned char* src)
{
    { uint16_t v; memcpy(&v, src + 0, 2); dst->tpage = v; }
    { uint16_t v; memcpy(&v, src + 2, 2); dst->clut = v; }
    { int16_t v; memcpy(&v, src + 4, 2); dst->size.fields.w = v; }
    { int16_t v; memcpy(&v, src + 6, 2); dst->size.fields.h = v; }
    { int16_t v; memcpy(&v, src + 8, 2); dst->x0 = v; }
    { int16_t v; memcpy(&v, src + 10, 2); dst->y0 = v; }
    { uint16_t v; memcpy(&v, src + 12, 2); dst->depth = v; }
    { uint8_t v; memcpy(&v, src + 14, 1); dst->uv.fields.u0 = v; }
    { uint8_t v; memcpy(&v, src + 15, 1); dst->uv.fields.v0 = v; }
    { uint8_t v; memcpy(&v, src + 16, 1); dst->r0 = v; }
    { uint8_t v; memcpy(&v, src + 17, 1); dst->g0 = v; }
    { uint8_t v; memcpy(&v, src + 18, 1); dst->b0 = v; }
    { uint8_t v; memcpy(&v, src + 19, 1); dst->codeFlags = v; }
}

#endif
static SpriteSource _gAkropolisSanctuaryView9SpriteSources[4];
static void peDecodeArr_gAkropolisSanctuaryView9SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_sanctuary/_gAkropolisSanctuaryView9SpriteSources", _gAkropolisSanctuaryView9SpriteSources, peDecodeArr_gAkropolisSanctuaryView9SpriteSources);
static SpriteBatch _gAkropolisSanctuaryView9SpriteBatches[3];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_sanctuary/_gAkropolisSanctuaryView9SpriteBatches", _gAkropolisSanctuaryView9SpriteBatches);
static SpriteBatch _gAkropolisSanctuaryView10SpriteBatches[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_sanctuary/_gAkropolisSanctuaryView10SpriteBatches", _gAkropolisSanctuaryView10SpriteBatches);
#ifndef PE_DECODE_SpriteSource
#define PE_DECODE_SpriteSource
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
static void peDecode_SpriteSource(SpriteSource* dst, const unsigned char* src)
{
    { uint16_t v; memcpy(&v, src + 0, 2); dst->tpage = v; }
    { uint16_t v; memcpy(&v, src + 2, 2); dst->clut = v; }
    { int16_t v; memcpy(&v, src + 4, 2); dst->size.fields.w = v; }
    { int16_t v; memcpy(&v, src + 6, 2); dst->size.fields.h = v; }
    { int16_t v; memcpy(&v, src + 8, 2); dst->x0 = v; }
    { int16_t v; memcpy(&v, src + 10, 2); dst->y0 = v; }
    { uint16_t v; memcpy(&v, src + 12, 2); dst->depth = v; }
    { uint8_t v; memcpy(&v, src + 14, 1); dst->uv.fields.u0 = v; }
    { uint8_t v; memcpy(&v, src + 15, 1); dst->uv.fields.v0 = v; }
    { uint8_t v; memcpy(&v, src + 16, 1); dst->r0 = v; }
    { uint8_t v; memcpy(&v, src + 17, 1); dst->g0 = v; }
    { uint8_t v; memcpy(&v, src + 18, 1); dst->b0 = v; }
    { uint8_t v; memcpy(&v, src + 19, 1); dst->codeFlags = v; }
}

#endif
static SpriteSource _gAkropolisSanctuaryView11SpriteSources[8];
static void peDecodeArr_gAkropolisSanctuaryView11SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_sanctuary/_gAkropolisSanctuaryView11SpriteSources", _gAkropolisSanctuaryView11SpriteSources, peDecodeArr_gAkropolisSanctuaryView11SpriteSources);
static SpriteBatch _gAkropolisSanctuaryView11SpriteBatches[3];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_sanctuary/_gAkropolisSanctuaryView11SpriteBatches", _gAkropolisSanctuaryView11SpriteBatches);
#ifndef PE_DECODE_SpriteSource
#define PE_DECODE_SpriteSource
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
static void peDecode_SpriteSource(SpriteSource* dst, const unsigned char* src)
{
    { uint16_t v; memcpy(&v, src + 0, 2); dst->tpage = v; }
    { uint16_t v; memcpy(&v, src + 2, 2); dst->clut = v; }
    { int16_t v; memcpy(&v, src + 4, 2); dst->size.fields.w = v; }
    { int16_t v; memcpy(&v, src + 6, 2); dst->size.fields.h = v; }
    { int16_t v; memcpy(&v, src + 8, 2); dst->x0 = v; }
    { int16_t v; memcpy(&v, src + 10, 2); dst->y0 = v; }
    { uint16_t v; memcpy(&v, src + 12, 2); dst->depth = v; }
    { uint8_t v; memcpy(&v, src + 14, 1); dst->uv.fields.u0 = v; }
    { uint8_t v; memcpy(&v, src + 15, 1); dst->uv.fields.v0 = v; }
    { uint8_t v; memcpy(&v, src + 16, 1); dst->r0 = v; }
    { uint8_t v; memcpy(&v, src + 17, 1); dst->g0 = v; }
    { uint8_t v; memcpy(&v, src + 18, 1); dst->b0 = v; }
    { uint8_t v; memcpy(&v, src + 19, 1); dst->codeFlags = v; }
}

#endif
static SpriteSource _gAkropolisSanctuaryView12SpriteSources[32];
static void peDecodeArr_gAkropolisSanctuaryView12SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_sanctuary/_gAkropolisSanctuaryView12SpriteSources", _gAkropolisSanctuaryView12SpriteSources, peDecodeArr_gAkropolisSanctuaryView12SpriteSources);
static SpriteBatch _gAkropolisSanctuaryView12SpriteBatches[5];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_sanctuary/_gAkropolisSanctuaryView12SpriteBatches", _gAkropolisSanctuaryView12SpriteBatches);
#ifndef PE_DECODE_SpriteSource
#define PE_DECODE_SpriteSource
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
static void peDecode_SpriteSource(SpriteSource* dst, const unsigned char* src)
{
    { uint16_t v; memcpy(&v, src + 0, 2); dst->tpage = v; }
    { uint16_t v; memcpy(&v, src + 2, 2); dst->clut = v; }
    { int16_t v; memcpy(&v, src + 4, 2); dst->size.fields.w = v; }
    { int16_t v; memcpy(&v, src + 6, 2); dst->size.fields.h = v; }
    { int16_t v; memcpy(&v, src + 8, 2); dst->x0 = v; }
    { int16_t v; memcpy(&v, src + 10, 2); dst->y0 = v; }
    { uint16_t v; memcpy(&v, src + 12, 2); dst->depth = v; }
    { uint8_t v; memcpy(&v, src + 14, 1); dst->uv.fields.u0 = v; }
    { uint8_t v; memcpy(&v, src + 15, 1); dst->uv.fields.v0 = v; }
    { uint8_t v; memcpy(&v, src + 16, 1); dst->r0 = v; }
    { uint8_t v; memcpy(&v, src + 17, 1); dst->g0 = v; }
    { uint8_t v; memcpy(&v, src + 18, 1); dst->b0 = v; }
    { uint8_t v; memcpy(&v, src + 19, 1); dst->codeFlags = v; }
}

#endif
static SpriteSource _gAkropolisSanctuaryView13SpriteSources[5];
static void peDecodeArr_gAkropolisSanctuaryView13SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_sanctuary/_gAkropolisSanctuaryView13SpriteSources", _gAkropolisSanctuaryView13SpriteSources, peDecodeArr_gAkropolisSanctuaryView13SpriteSources);
static SpriteBatch _gAkropolisSanctuaryView13SpriteBatches[3];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_sanctuary/_gAkropolisSanctuaryView13SpriteBatches", _gAkropolisSanctuaryView13SpriteBatches);
#ifndef PE_DECODE_SpriteSource
#define PE_DECODE_SpriteSource
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
static void peDecode_SpriteSource(SpriteSource* dst, const unsigned char* src)
{
    { uint16_t v; memcpy(&v, src + 0, 2); dst->tpage = v; }
    { uint16_t v; memcpy(&v, src + 2, 2); dst->clut = v; }
    { int16_t v; memcpy(&v, src + 4, 2); dst->size.fields.w = v; }
    { int16_t v; memcpy(&v, src + 6, 2); dst->size.fields.h = v; }
    { int16_t v; memcpy(&v, src + 8, 2); dst->x0 = v; }
    { int16_t v; memcpy(&v, src + 10, 2); dst->y0 = v; }
    { uint16_t v; memcpy(&v, src + 12, 2); dst->depth = v; }
    { uint8_t v; memcpy(&v, src + 14, 1); dst->uv.fields.u0 = v; }
    { uint8_t v; memcpy(&v, src + 15, 1); dst->uv.fields.v0 = v; }
    { uint8_t v; memcpy(&v, src + 16, 1); dst->r0 = v; }
    { uint8_t v; memcpy(&v, src + 17, 1); dst->g0 = v; }
    { uint8_t v; memcpy(&v, src + 18, 1); dst->b0 = v; }
    { uint8_t v; memcpy(&v, src + 19, 1); dst->codeFlags = v; }
}

#endif
static SpriteSource _gAkropolisSanctuaryView14SpriteSources[8];
static void peDecodeArr_gAkropolisSanctuaryView14SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_sanctuary/_gAkropolisSanctuaryView14SpriteSources", _gAkropolisSanctuaryView14SpriteSources, peDecodeArr_gAkropolisSanctuaryView14SpriteSources);
static SpriteBatch _gAkropolisSanctuaryView14SpriteBatches[3];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_sanctuary/_gAkropolisSanctuaryView14SpriteBatches", _gAkropolisSanctuaryView14SpriteBatches);
static SpriteBatch _gAkropolisSanctuaryView15SpriteBatches[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_sanctuary/_gAkropolisSanctuaryView15SpriteBatches", _gAkropolisSanctuaryView15SpriteBatches);
#ifndef PE_DECODE_SpriteSource
#define PE_DECODE_SpriteSource
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
static void peDecode_SpriteSource(SpriteSource* dst, const unsigned char* src)
{
    { uint16_t v; memcpy(&v, src + 0, 2); dst->tpage = v; }
    { uint16_t v; memcpy(&v, src + 2, 2); dst->clut = v; }
    { int16_t v; memcpy(&v, src + 4, 2); dst->size.fields.w = v; }
    { int16_t v; memcpy(&v, src + 6, 2); dst->size.fields.h = v; }
    { int16_t v; memcpy(&v, src + 8, 2); dst->x0 = v; }
    { int16_t v; memcpy(&v, src + 10, 2); dst->y0 = v; }
    { uint16_t v; memcpy(&v, src + 12, 2); dst->depth = v; }
    { uint8_t v; memcpy(&v, src + 14, 1); dst->uv.fields.u0 = v; }
    { uint8_t v; memcpy(&v, src + 15, 1); dst->uv.fields.v0 = v; }
    { uint8_t v; memcpy(&v, src + 16, 1); dst->r0 = v; }
    { uint8_t v; memcpy(&v, src + 17, 1); dst->g0 = v; }
    { uint8_t v; memcpy(&v, src + 18, 1); dst->b0 = v; }
    { uint8_t v; memcpy(&v, src + 19, 1); dst->codeFlags = v; }
}

#endif
static SpriteSource _gAkropolisSanctuaryView16SpriteSources[38];
static void peDecodeArr_gAkropolisSanctuaryView16SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_sanctuary/_gAkropolisSanctuaryView16SpriteSources", _gAkropolisSanctuaryView16SpriteSources, peDecodeArr_gAkropolisSanctuaryView16SpriteSources);
static SpriteBatch _gAkropolisSanctuaryView16SpriteBatches[5];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_sanctuary/_gAkropolisSanctuaryView16SpriteBatches", _gAkropolisSanctuaryView16SpriteBatches);
#ifndef PE_DECODE_SpriteView
#define PE_DECODE_SpriteView
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
static void peDecode_SpriteView(SpriteView* dst, const unsigned char* src)
{
    /* sources.elements: pointer, set by the array's fixups */
    /* batches: pointer, set by the array's fixups */
    /* drawAreas: pointer, set by the array's fixups */
}

#endif
SpriteView gAkropolisSanctuarySpriteViews[16];
static void peDecodeArr_gAkropolisSanctuarySpriteViews(void* base, const unsigned char* src, size_t n)
{
    SpriteView* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteView(&dst[k], src + k * 12);
    dst[0].sources.elements = _gAkropolisSanctuaryView1SpriteBatches;
    dst[0].batches = _gAkropolisSanctuaryView1SpriteBatches;
    dst[1].sources.elements = _gAkropolisSanctuaryView2SpriteSources;
    dst[1].batches = _gAkropolisSanctuaryView2SpriteBatches;
    dst[2].sources.elements = _gAkropolisSanctuaryView3SpriteSources;
    dst[2].batches = _gAkropolisSanctuaryView3SpriteBatches;
    dst[3].sources.elements = _gAkropolisSanctuaryView4SpriteSources;
    dst[3].batches = _gAkropolisSanctuaryView4SpriteBatches;
    dst[4].sources.elements = _gAkropolisSanctuaryView5SpriteSources;
    dst[4].batches = _gAkropolisSanctuaryView5SpriteBatches;
    dst[5].sources.elements = _gAkropolisSanctuaryView6SpriteSources;
    dst[5].batches = _gAkropolisSanctuaryView6SpriteBatches;
    dst[6].sources.elements = _gAkropolisSanctuaryView7SpriteSources;
    dst[6].batches = _gAkropolisSanctuaryView7SpriteBatches;
    dst[7].sources.elements = _gAkropolisSanctuaryView8SpriteSources;
    dst[7].batches = _gAkropolisSanctuaryView8SpriteBatches;
    dst[8].sources.elements = _gAkropolisSanctuaryView9SpriteSources;
    dst[8].batches = _gAkropolisSanctuaryView9SpriteBatches;
    dst[9].sources.elements = _gAkropolisSanctuaryView10SpriteBatches;
    dst[9].batches = _gAkropolisSanctuaryView10SpriteBatches;
    dst[10].sources.elements = _gAkropolisSanctuaryView11SpriteSources;
    dst[10].batches = _gAkropolisSanctuaryView11SpriteBatches;
    dst[11].sources.elements = _gAkropolisSanctuaryView12SpriteSources;
    dst[11].batches = _gAkropolisSanctuaryView12SpriteBatches;
    dst[12].sources.elements = _gAkropolisSanctuaryView13SpriteSources;
    dst[12].batches = _gAkropolisSanctuaryView13SpriteBatches;
    dst[13].sources.elements = _gAkropolisSanctuaryView14SpriteSources;
    dst[13].batches = _gAkropolisSanctuaryView14SpriteBatches;
    dst[14].sources.elements = _gAkropolisSanctuaryView15SpriteBatches;
    dst[14].batches = _gAkropolisSanctuaryView15SpriteBatches;
    dst[15].sources.elements = _gAkropolisSanctuaryView16SpriteSources;
    dst[15].batches = _gAkropolisSanctuaryView16SpriteBatches;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_sanctuary/gAkropolisSanctuarySpriteViews", gAkropolisSanctuarySpriteViews, peDecodeArr_gAkropolisSanctuarySpriteViews);
