/* rooms/akropolis/square/package: written from its room instance by tools/buildsteps/gen_room_inc.py. */

#include "types.h"
#include "gameplay/sprites.h"

static SpriteBatch _gAkropolisSquareView1SpriteBatches[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_square/_gAkropolisSquareView1SpriteBatches", _gAkropolisSquareView1SpriteBatches);
static SpriteBatch _gAkropolisSquareView2SpriteBatches[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_square/_gAkropolisSquareView2SpriteBatches", _gAkropolisSquareView2SpriteBatches);
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
static SpriteSource _gAkropolisSquareView3SpriteSources[73];
static void peDecodeArr_gAkropolisSquareView3SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_square/_gAkropolisSquareView3SpriteSources", _gAkropolisSquareView3SpriteSources, peDecodeArr_gAkropolisSquareView3SpriteSources);
static SpriteBatch _gAkropolisSquareView3SpriteBatches[11];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_square/_gAkropolisSquareView3SpriteBatches", _gAkropolisSquareView3SpriteBatches);
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
static SpriteSource _gAkropolisSquareView4SpriteSources[41];
static void peDecodeArr_gAkropolisSquareView4SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_square/_gAkropolisSquareView4SpriteSources", _gAkropolisSquareView4SpriteSources, peDecodeArr_gAkropolisSquareView4SpriteSources);
static SpriteBatch _gAkropolisSquareView4SpriteBatches[5];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_square/_gAkropolisSquareView4SpriteBatches", _gAkropolisSquareView4SpriteBatches);
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
static SpriteSource _gAkropolisSquareView5SpriteSources[31];
static void peDecodeArr_gAkropolisSquareView5SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_square/_gAkropolisSquareView5SpriteSources", _gAkropolisSquareView5SpriteSources, peDecodeArr_gAkropolisSquareView5SpriteSources);
static SpriteBatch _gAkropolisSquareView5SpriteBatches[5];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_square/_gAkropolisSquareView5SpriteBatches", _gAkropolisSquareView5SpriteBatches);
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
static SpriteSource _gAkropolisSquareView6SpriteSources[91];
static void peDecodeArr_gAkropolisSquareView6SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_square/_gAkropolisSquareView6SpriteSources", _gAkropolisSquareView6SpriteSources, peDecodeArr_gAkropolisSquareView6SpriteSources);
static SpriteBatch _gAkropolisSquareView6SpriteBatches[12];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_square/_gAkropolisSquareView6SpriteBatches", _gAkropolisSquareView6SpriteBatches);
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
static SpriteSource _gAkropolisSquareView7SpriteSources[94];
static void peDecodeArr_gAkropolisSquareView7SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_square/_gAkropolisSquareView7SpriteSources", _gAkropolisSquareView7SpriteSources, peDecodeArr_gAkropolisSquareView7SpriteSources);
static SpriteBatch _gAkropolisSquareView7SpriteBatches[18];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_square/_gAkropolisSquareView7SpriteBatches", _gAkropolisSquareView7SpriteBatches);
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
static SpriteSource _gAkropolisSquareView8SpriteSources[53];
static void peDecodeArr_gAkropolisSquareView8SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_square/_gAkropolisSquareView8SpriteSources", _gAkropolisSquareView8SpriteSources, peDecodeArr_gAkropolisSquareView8SpriteSources);
static SpriteBatch _gAkropolisSquareView8SpriteBatches[13];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_square/_gAkropolisSquareView8SpriteBatches", _gAkropolisSquareView8SpriteBatches);
static SpriteBatch _gAkropolisSquareView9SpriteBatches[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_square/_gAkropolisSquareView9SpriteBatches", _gAkropolisSquareView9SpriteBatches);
static SpriteBatch _gAkropolisSquareView10SpriteBatches[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_square/_gAkropolisSquareView10SpriteBatches", _gAkropolisSquareView10SpriteBatches);
static SpriteBatch _gAkropolisSquareView11SpriteBatches[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_square/_gAkropolisSquareView11SpriteBatches", _gAkropolisSquareView11SpriteBatches);
static SpriteBatch _gAkropolisSquareView12SpriteBatches[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_square/_gAkropolisSquareView12SpriteBatches", _gAkropolisSquareView12SpriteBatches);
static SpriteBatch _gAkropolisSquareView13SpriteBatches[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_square/_gAkropolisSquareView13SpriteBatches", _gAkropolisSquareView13SpriteBatches);
static SpriteBatch _gAkropolisSquareView14SpriteBatches[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_square/_gAkropolisSquareView14SpriteBatches", _gAkropolisSquareView14SpriteBatches);
static SpriteBatch _gAkropolisSquareView15SpriteBatches[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_square/_gAkropolisSquareView15SpriteBatches", _gAkropolisSquareView15SpriteBatches);
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
SpriteView gAkropolisSquareSpriteViews[15];
static void peDecodeArr_gAkropolisSquareSpriteViews(void* base, const unsigned char* src, size_t n)
{
    SpriteView* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteView(&dst[k], src + k * 12);
    dst[0].sources.elements = _gAkropolisSquareView1SpriteBatches;
    dst[0].batches = _gAkropolisSquareView1SpriteBatches;
    dst[1].sources.elements = _gAkropolisSquareView2SpriteBatches;
    dst[1].batches = _gAkropolisSquareView2SpriteBatches;
    dst[2].sources.elements = _gAkropolisSquareView3SpriteSources;
    dst[2].batches = _gAkropolisSquareView3SpriteBatches;
    dst[3].sources.elements = _gAkropolisSquareView4SpriteSources;
    dst[3].batches = _gAkropolisSquareView4SpriteBatches;
    dst[4].sources.elements = _gAkropolisSquareView5SpriteSources;
    dst[4].batches = _gAkropolisSquareView5SpriteBatches;
    dst[5].sources.elements = _gAkropolisSquareView6SpriteSources;
    dst[5].batches = _gAkropolisSquareView6SpriteBatches;
    dst[6].sources.elements = _gAkropolisSquareView7SpriteSources;
    dst[6].batches = _gAkropolisSquareView7SpriteBatches;
    dst[7].sources.elements = _gAkropolisSquareView8SpriteSources;
    dst[7].batches = _gAkropolisSquareView8SpriteBatches;
    dst[8].sources.elements = _gAkropolisSquareView9SpriteBatches;
    dst[8].batches = _gAkropolisSquareView9SpriteBatches;
    dst[9].sources.elements = _gAkropolisSquareView10SpriteBatches;
    dst[9].batches = _gAkropolisSquareView10SpriteBatches;
    dst[10].sources.elements = _gAkropolisSquareView11SpriteBatches;
    dst[10].batches = _gAkropolisSquareView11SpriteBatches;
    dst[11].sources.elements = _gAkropolisSquareView12SpriteBatches;
    dst[11].batches = _gAkropolisSquareView12SpriteBatches;
    dst[12].sources.elements = _gAkropolisSquareView13SpriteBatches;
    dst[12].batches = _gAkropolisSquareView13SpriteBatches;
    dst[13].sources.elements = _gAkropolisSquareView14SpriteBatches;
    dst[13].batches = _gAkropolisSquareView14SpriteBatches;
    dst[14].sources.elements = _gAkropolisSquareView15SpriteBatches;
    dst[14].batches = _gAkropolisSquareView15SpriteBatches;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_square/gAkropolisSquareSpriteViews", gAkropolisSquareSpriteViews, peDecodeArr_gAkropolisSquareSpriteViews);
