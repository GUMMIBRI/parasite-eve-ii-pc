/* rooms/akropolis/fountain/package: written from its room instance by tools/buildsteps/gen_room_inc.py. */

#include "types.h"
#include "gameplay/sprites.h"

static SpriteBatch _gAkropolisFountainView1SpriteBatches[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_fountain/_gAkropolisFountainView1SpriteBatches", _gAkropolisFountainView1SpriteBatches);
static SpriteBatch _gAkropolisFountainView2SpriteBatches[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_fountain/_gAkropolisFountainView2SpriteBatches", _gAkropolisFountainView2SpriteBatches);
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
static SpriteSource _gAkropolisFountainView3SpriteSources[95];
static void peDecodeArr_gAkropolisFountainView3SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_fountain/_gAkropolisFountainView3SpriteSources", _gAkropolisFountainView3SpriteSources, peDecodeArr_gAkropolisFountainView3SpriteSources);
static SpriteBatch _gAkropolisFountainView3SpriteBatches[9];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_fountain/_gAkropolisFountainView3SpriteBatches", _gAkropolisFountainView3SpriteBatches);
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
static SpriteSource _gAkropolisFountainView4SpriteSources[84];
static void peDecodeArr_gAkropolisFountainView4SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_fountain/_gAkropolisFountainView4SpriteSources", _gAkropolisFountainView4SpriteSources, peDecodeArr_gAkropolisFountainView4SpriteSources);
static SpriteBatch _gAkropolisFountainView4SpriteBatches[15];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_fountain/_gAkropolisFountainView4SpriteBatches", _gAkropolisFountainView4SpriteBatches);
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
static SpriteSource _gAkropolisFountainView5SpriteSources[73];
static void peDecodeArr_gAkropolisFountainView5SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_fountain/_gAkropolisFountainView5SpriteSources", _gAkropolisFountainView5SpriteSources, peDecodeArr_gAkropolisFountainView5SpriteSources);
static SpriteBatch _gAkropolisFountainView5SpriteBatches[8];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_fountain/_gAkropolisFountainView5SpriteBatches", _gAkropolisFountainView5SpriteBatches);
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
static SpriteSource _gAkropolisFountainView6SpriteSources[16];
static void peDecodeArr_gAkropolisFountainView6SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_fountain/_gAkropolisFountainView6SpriteSources", _gAkropolisFountainView6SpriteSources, peDecodeArr_gAkropolisFountainView6SpriteSources);
static SpriteBatch _gAkropolisFountainView6SpriteBatches[3];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_fountain/_gAkropolisFountainView6SpriteBatches", _gAkropolisFountainView6SpriteBatches);
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
static SpriteSource _gAkropolisFountainView7SpriteSources[71];
static void peDecodeArr_gAkropolisFountainView7SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_fountain/_gAkropolisFountainView7SpriteSources", _gAkropolisFountainView7SpriteSources, peDecodeArr_gAkropolisFountainView7SpriteSources);
static SpriteBatch _gAkropolisFountainView7SpriteBatches[9];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_fountain/_gAkropolisFountainView7SpriteBatches", _gAkropolisFountainView7SpriteBatches);
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
static SpriteSource _gAkropolisFountainView8SpriteSources[99];
static void peDecodeArr_gAkropolisFountainView8SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_fountain/_gAkropolisFountainView8SpriteSources", _gAkropolisFountainView8SpriteSources, peDecodeArr_gAkropolisFountainView8SpriteSources);
static SpriteBatch _gAkropolisFountainView8SpriteBatches[18];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_fountain/_gAkropolisFountainView8SpriteBatches", _gAkropolisFountainView8SpriteBatches);
static SpriteBatch _gAkropolisFountainView9SpriteBatches[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_fountain/_gAkropolisFountainView9SpriteBatches", _gAkropolisFountainView9SpriteBatches);
static SpriteBatch _gAkropolisFountainView10SpriteBatches[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_fountain/_gAkropolisFountainView10SpriteBatches", _gAkropolisFountainView10SpriteBatches);
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
static SpriteSource _gAkropolisFountainView11SpriteSources[54];
static void peDecodeArr_gAkropolisFountainView11SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_fountain/_gAkropolisFountainView11SpriteSources", _gAkropolisFountainView11SpriteSources, peDecodeArr_gAkropolisFountainView11SpriteSources);
static SpriteBatch _gAkropolisFountainView11SpriteBatches[9];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_fountain/_gAkropolisFountainView11SpriteBatches", _gAkropolisFountainView11SpriteBatches);
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
static SpriteSource _gAkropolisFountainView12SpriteSources[92];
static void peDecodeArr_gAkropolisFountainView12SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_fountain/_gAkropolisFountainView12SpriteSources", _gAkropolisFountainView12SpriteSources, peDecodeArr_gAkropolisFountainView12SpriteSources);
static SpriteBatch _gAkropolisFountainView12SpriteBatches[15];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_fountain/_gAkropolisFountainView12SpriteBatches", _gAkropolisFountainView12SpriteBatches);
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
static SpriteSource _gAkropolisFountainView13SpriteSources[39];
static void peDecodeArr_gAkropolisFountainView13SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_fountain/_gAkropolisFountainView13SpriteSources", _gAkropolisFountainView13SpriteSources, peDecodeArr_gAkropolisFountainView13SpriteSources);
static SpriteBatch _gAkropolisFountainView13SpriteBatches[8];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_fountain/_gAkropolisFountainView13SpriteBatches", _gAkropolisFountainView13SpriteBatches);
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
static SpriteSource _gAkropolisFountainView14SpriteSources[8];
static void peDecodeArr_gAkropolisFountainView14SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_fountain/_gAkropolisFountainView14SpriteSources", _gAkropolisFountainView14SpriteSources, peDecodeArr_gAkropolisFountainView14SpriteSources);
static SpriteBatch _gAkropolisFountainView14SpriteBatches[3];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_fountain/_gAkropolisFountainView14SpriteBatches", _gAkropolisFountainView14SpriteBatches);
static SpriteBatch _gAkropolisFountainUnusedEmptySpriteBatches[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_fountain/_gAkropolisFountainUnusedEmptySpriteBatches", _gAkropolisFountainUnusedEmptySpriteBatches);
static SpriteBatch _gAkropolisFountainView16SpriteBatches[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_fountain/_gAkropolisFountainView16SpriteBatches", _gAkropolisFountainView16SpriteBatches);
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
static SpriteSource _gAkropolisFountainView17SpriteSources[28];
static void peDecodeArr_gAkropolisFountainView17SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_fountain/_gAkropolisFountainView17SpriteSources", _gAkropolisFountainView17SpriteSources, peDecodeArr_gAkropolisFountainView17SpriteSources);
static SpriteBatch _gAkropolisFountainView17SpriteBatches[4];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_fountain/_gAkropolisFountainView17SpriteBatches", _gAkropolisFountainView17SpriteBatches);
static SpriteBatch _gAkropolisFountainView18SpriteBatches[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_fountain/_gAkropolisFountainView18SpriteBatches", _gAkropolisFountainView18SpriteBatches);
static SpriteBatch _gAkropolisFountainView19SpriteBatches[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_fountain/_gAkropolisFountainView19SpriteBatches", _gAkropolisFountainView19SpriteBatches);
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
static SpriteSource _gAkropolisFountainView20SpriteSources[9];
static void peDecodeArr_gAkropolisFountainView20SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_fountain/_gAkropolisFountainView20SpriteSources", _gAkropolisFountainView20SpriteSources, peDecodeArr_gAkropolisFountainView20SpriteSources);
static SpriteBatch _gAkropolisFountainView20SpriteBatches[3];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_fountain/_gAkropolisFountainView20SpriteBatches", _gAkropolisFountainView20SpriteBatches);
static SpriteBatch _gAkropolisFountainView21SpriteBatches[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_fountain/_gAkropolisFountainView21SpriteBatches", _gAkropolisFountainView21SpriteBatches);
static SpriteBatch _gAkropolisFountainView22SpriteBatches[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_fountain/_gAkropolisFountainView22SpriteBatches", _gAkropolisFountainView22SpriteBatches);
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
SpriteView gAkropolisFountainSpriteViews[22];
static void peDecodeArr_gAkropolisFountainSpriteViews(void* base, const unsigned char* src, size_t n)
{
    SpriteView* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteView(&dst[k], src + k * 12);
    dst[0].sources.elements = _gAkropolisFountainView1SpriteBatches;
    dst[0].batches = _gAkropolisFountainView1SpriteBatches;
    dst[1].sources.elements = _gAkropolisFountainView2SpriteBatches;
    dst[1].batches = _gAkropolisFountainView2SpriteBatches;
    dst[2].sources.elements = _gAkropolisFountainView3SpriteSources;
    dst[2].batches = _gAkropolisFountainView3SpriteBatches;
    dst[3].sources.elements = _gAkropolisFountainView4SpriteSources;
    dst[3].batches = _gAkropolisFountainView4SpriteBatches;
    dst[4].sources.elements = _gAkropolisFountainView5SpriteSources;
    dst[4].batches = _gAkropolisFountainView5SpriteBatches;
    dst[5].sources.elements = _gAkropolisFountainView6SpriteSources;
    dst[5].batches = _gAkropolisFountainView6SpriteBatches;
    dst[6].sources.elements = _gAkropolisFountainView7SpriteSources;
    dst[6].batches = _gAkropolisFountainView7SpriteBatches;
    dst[7].sources.elements = _gAkropolisFountainView8SpriteSources;
    dst[7].batches = _gAkropolisFountainView8SpriteBatches;
    dst[8].sources.elements = _gAkropolisFountainView9SpriteBatches;
    dst[8].batches = _gAkropolisFountainView9SpriteBatches;
    dst[9].sources.elements = _gAkropolisFountainView10SpriteBatches;
    dst[9].batches = _gAkropolisFountainView10SpriteBatches;
    dst[10].sources.elements = _gAkropolisFountainView11SpriteSources;
    dst[10].batches = _gAkropolisFountainView11SpriteBatches;
    dst[11].sources.elements = _gAkropolisFountainView12SpriteSources;
    dst[11].batches = _gAkropolisFountainView12SpriteBatches;
    dst[12].sources.elements = _gAkropolisFountainView13SpriteSources;
    dst[12].batches = _gAkropolisFountainView13SpriteBatches;
    dst[13].sources.elements = _gAkropolisFountainView14SpriteSources;
    dst[13].batches = _gAkropolisFountainView14SpriteBatches;
    dst[14].sources.elements = _gAkropolisFountainView7SpriteSources;
    dst[14].batches = _gAkropolisFountainView7SpriteBatches;
    dst[15].sources.elements = _gAkropolisFountainView16SpriteBatches;
    dst[15].batches = _gAkropolisFountainView16SpriteBatches;
    dst[16].sources.elements = _gAkropolisFountainView17SpriteSources;
    dst[16].batches = _gAkropolisFountainView17SpriteBatches;
    dst[17].sources.elements = _gAkropolisFountainView18SpriteBatches;
    dst[17].batches = _gAkropolisFountainView18SpriteBatches;
    dst[18].sources.elements = _gAkropolisFountainView19SpriteBatches;
    dst[18].batches = _gAkropolisFountainView19SpriteBatches;
    dst[19].sources.elements = _gAkropolisFountainView20SpriteSources;
    dst[19].batches = _gAkropolisFountainView20SpriteBatches;
    dst[20].sources.elements = _gAkropolisFountainView21SpriteBatches;
    dst[20].batches = _gAkropolisFountainView21SpriteBatches;
    dst[21].sources.elements = _gAkropolisFountainView22SpriteBatches;
    dst[21].batches = _gAkropolisFountainView22SpriteBatches;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_fountain/gAkropolisFountainSpriteViews", gAkropolisFountainSpriteViews, peDecodeArr_gAkropolisFountainSpriteViews);
