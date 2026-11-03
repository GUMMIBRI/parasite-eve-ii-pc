/* rooms/akropolis/patio/package: written from its room instance by tools/buildsteps/gen_room_inc.py. */

#include "types.h"
#include "gameplay/sprites.h"

static SpriteBatch _gAkropolisPatioView1SpriteBatches[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_patio/_gAkropolisPatioView1SpriteBatches", _gAkropolisPatioView1SpriteBatches);
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
static SpriteSource _gAkropolisPatioView2SpriteSources[27];
static void peDecodeArr_gAkropolisPatioView2SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_patio/_gAkropolisPatioView2SpriteSources", _gAkropolisPatioView2SpriteSources, peDecodeArr_gAkropolisPatioView2SpriteSources);
static SpriteBatch _gAkropolisPatioView2SpriteBatches[7];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_patio/_gAkropolisPatioView2SpriteBatches", _gAkropolisPatioView2SpriteBatches);
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
static SpriteSource _gAkropolisPatioView3SpriteSources[45];
static void peDecodeArr_gAkropolisPatioView3SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_patio/_gAkropolisPatioView3SpriteSources", _gAkropolisPatioView3SpriteSources, peDecodeArr_gAkropolisPatioView3SpriteSources);
static SpriteBatch _gAkropolisPatioView3SpriteBatches[15];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_patio/_gAkropolisPatioView3SpriteBatches", _gAkropolisPatioView3SpriteBatches);
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
static SpriteSource _gAkropolisPatioView4SpriteSources[15];
static void peDecodeArr_gAkropolisPatioView4SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_patio/_gAkropolisPatioView4SpriteSources", _gAkropolisPatioView4SpriteSources, peDecodeArr_gAkropolisPatioView4SpriteSources);
static SpriteBatch _gAkropolisPatioView4SpriteBatches[5];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_patio/_gAkropolisPatioView4SpriteBatches", _gAkropolisPatioView4SpriteBatches);
static SpriteBatch _gAkropolisPatioView5SpriteBatches[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_patio/_gAkropolisPatioView5SpriteBatches", _gAkropolisPatioView5SpriteBatches);
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
static SpriteSource _gAkropolisPatioView6SpriteSources[13];
static void peDecodeArr_gAkropolisPatioView6SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_patio/_gAkropolisPatioView6SpriteSources", _gAkropolisPatioView6SpriteSources, peDecodeArr_gAkropolisPatioView6SpriteSources);
static SpriteBatch _gAkropolisPatioView6SpriteBatches[4];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_patio/_gAkropolisPatioView6SpriteBatches", _gAkropolisPatioView6SpriteBatches);
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
static SpriteSource _gAkropolisPatioView7SpriteSources[21];
static void peDecodeArr_gAkropolisPatioView7SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_patio/_gAkropolisPatioView7SpriteSources", _gAkropolisPatioView7SpriteSources, peDecodeArr_gAkropolisPatioView7SpriteSources);
static SpriteBatch _gAkropolisPatioView7SpriteBatches[5];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_patio/_gAkropolisPatioView7SpriteBatches", _gAkropolisPatioView7SpriteBatches);
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
static SpriteSource _gAkropolisPatioView8SpriteSources[56];
static void peDecodeArr_gAkropolisPatioView8SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_patio/_gAkropolisPatioView8SpriteSources", _gAkropolisPatioView8SpriteSources, peDecodeArr_gAkropolisPatioView8SpriteSources);
static SpriteBatch _gAkropolisPatioView8SpriteBatches[20];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_patio/_gAkropolisPatioView8SpriteBatches", _gAkropolisPatioView8SpriteBatches);
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
static SpriteSource _gAkropolisPatioView9SpriteSources[47];
static void peDecodeArr_gAkropolisPatioView9SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_patio/_gAkropolisPatioView9SpriteSources", _gAkropolisPatioView9SpriteSources, peDecodeArr_gAkropolisPatioView9SpriteSources);
static SpriteBatch _gAkropolisPatioView9SpriteBatches[15];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_patio/_gAkropolisPatioView9SpriteBatches", _gAkropolisPatioView9SpriteBatches);
static SpriteBatch _gAkropolisPatioView10SpriteBatches[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_patio/_gAkropolisPatioView10SpriteBatches", _gAkropolisPatioView10SpriteBatches);
static SpriteBatch _gAkropolisPatioView11SpriteBatches[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_patio/_gAkropolisPatioView11SpriteBatches", _gAkropolisPatioView11SpriteBatches);
static SpriteBatch _gAkropolisPatioView12SpriteBatches[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_patio/_gAkropolisPatioView12SpriteBatches", _gAkropolisPatioView12SpriteBatches);
static SpriteBatch _gAkropolisPatioUnusedBackgroundSpriteBatches1[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_patio/_gAkropolisPatioUnusedBackgroundSpriteBatches1", _gAkropolisPatioUnusedBackgroundSpriteBatches1);
static SpriteBatch _gAkropolisPatioView14SpriteBatches[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_patio/_gAkropolisPatioView14SpriteBatches", _gAkropolisPatioView14SpriteBatches);
static SpriteBatch _gAkropolisPatioView15SpriteBatches[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_patio/_gAkropolisPatioView15SpriteBatches", _gAkropolisPatioView15SpriteBatches);
static SpriteBatch _gAkropolisPatioView16SpriteBatches[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_patio/_gAkropolisPatioView16SpriteBatches", _gAkropolisPatioView16SpriteBatches);
static SpriteBatch _gAkropolisPatioUnusedBackgroundSpriteBatches2[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_patio/_gAkropolisPatioUnusedBackgroundSpriteBatches2", _gAkropolisPatioUnusedBackgroundSpriteBatches2);
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
static SpriteSource _gAkropolisPatioView18SpriteSources[20];
static void peDecodeArr_gAkropolisPatioView18SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_patio/_gAkropolisPatioView18SpriteSources", _gAkropolisPatioView18SpriteSources, peDecodeArr_gAkropolisPatioView18SpriteSources);
static SpriteBatch _gAkropolisPatioView18SpriteBatches[3];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_patio/_gAkropolisPatioView18SpriteBatches", _gAkropolisPatioView18SpriteBatches);
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
static SpriteSource _gAkropolisPatioView19SpriteSources[30];
static void peDecodeArr_gAkropolisPatioView19SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_patio/_gAkropolisPatioView19SpriteSources", _gAkropolisPatioView19SpriteSources, peDecodeArr_gAkropolisPatioView19SpriteSources);
static SpriteBatch _gAkropolisPatioView19SpriteBatches[3];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_patio/_gAkropolisPatioView19SpriteBatches", _gAkropolisPatioView19SpriteBatches);
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
SpriteView gAkropolisPatioSpriteViews[19];
static void peDecodeArr_gAkropolisPatioSpriteViews(void* base, const unsigned char* src, size_t n)
{
    SpriteView* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteView(&dst[k], src + k * 12);
    dst[0].sources.elements = _gAkropolisPatioView1SpriteBatches;
    dst[0].batches = _gAkropolisPatioView1SpriteBatches;
    dst[1].sources.elements = _gAkropolisPatioView2SpriteSources;
    dst[1].batches = _gAkropolisPatioView2SpriteBatches;
    dst[2].sources.elements = _gAkropolisPatioView3SpriteSources;
    dst[2].batches = _gAkropolisPatioView3SpriteBatches;
    dst[3].sources.elements = _gAkropolisPatioView4SpriteSources;
    dst[3].batches = _gAkropolisPatioView4SpriteBatches;
    dst[4].sources.elements = _gAkropolisPatioView5SpriteBatches;
    dst[4].batches = _gAkropolisPatioView5SpriteBatches;
    dst[5].sources.elements = _gAkropolisPatioView6SpriteSources;
    dst[5].batches = _gAkropolisPatioView6SpriteBatches;
    dst[6].sources.elements = _gAkropolisPatioView7SpriteSources;
    dst[6].batches = _gAkropolisPatioView7SpriteBatches;
    dst[7].sources.elements = _gAkropolisPatioView8SpriteSources;
    dst[7].batches = _gAkropolisPatioView8SpriteBatches;
    dst[8].sources.elements = _gAkropolisPatioView9SpriteSources;
    dst[8].batches = _gAkropolisPatioView9SpriteBatches;
    dst[9].sources.elements = _gAkropolisPatioView10SpriteBatches;
    dst[9].batches = _gAkropolisPatioView10SpriteBatches;
    dst[10].sources.elements = _gAkropolisPatioView11SpriteBatches;
    dst[10].batches = _gAkropolisPatioView11SpriteBatches;
    dst[11].sources.elements = _gAkropolisPatioView12SpriteBatches;
    dst[11].batches = _gAkropolisPatioView12SpriteBatches;
    dst[12].sources.elements = _gAkropolisPatioView7SpriteSources;
    dst[12].batches = _gAkropolisPatioView7SpriteBatches;
    dst[13].sources.elements = _gAkropolisPatioView14SpriteBatches;
    dst[13].batches = _gAkropolisPatioView14SpriteBatches;
    dst[14].sources.elements = _gAkropolisPatioView15SpriteBatches;
    dst[14].batches = _gAkropolisPatioView15SpriteBatches;
    dst[15].sources.elements = _gAkropolisPatioView16SpriteBatches;
    dst[15].batches = _gAkropolisPatioView16SpriteBatches;
    dst[16].sources.elements = _gAkropolisPatioView4SpriteSources;
    dst[16].batches = _gAkropolisPatioView4SpriteBatches;
    dst[17].sources.elements = _gAkropolisPatioView18SpriteSources;
    dst[17].batches = _gAkropolisPatioView18SpriteBatches;
    dst[18].sources.elements = _gAkropolisPatioView19SpriteSources;
    dst[18].batches = _gAkropolisPatioView19SpriteBatches;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_patio/gAkropolisPatioSpriteViews", gAkropolisPatioSpriteViews, peDecodeArr_gAkropolisPatioSpriteViews);
