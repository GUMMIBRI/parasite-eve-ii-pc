/* rooms/mist/r18/package: written from its room instance by tools/buildsteps/gen_room_inc.py. */

#include "types.h"
#include "gameplay/sprites.h"

static SpriteBatch _gMistR18View1SpriteBatches[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/mist_r18/_gMistR18View1SpriteBatches", _gMistR18View1SpriteBatches);
static SpriteBatch _gMistR18View2SpriteBatches[4];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/mist_r18/_gMistR18View2SpriteBatches", _gMistR18View2SpriteBatches);
static SpriteBatch _gMistR18View3SpriteBatches[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/mist_r18/_gMistR18View3SpriteBatches", _gMistR18View3SpriteBatches);
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
static SpriteSource _gMistR18View4SpriteSources[10];
static void peDecodeArr_gMistR18View4SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_r18/_gMistR18View4SpriteSources", _gMistR18View4SpriteSources, peDecodeArr_gMistR18View4SpriteSources);
static SpriteBatch _gMistR18View4SpriteBatches[3];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/mist_r18/_gMistR18View4SpriteBatches", _gMistR18View4SpriteBatches);
static SpriteBatch _gMistR18View5SpriteBatches[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/mist_r18/_gMistR18View5SpriteBatches", _gMistR18View5SpriteBatches);
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
static SpriteSource _gMistR18View6SpriteSources[17];
static void peDecodeArr_gMistR18View6SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_r18/_gMistR18View6SpriteSources", _gMistR18View6SpriteSources, peDecodeArr_gMistR18View6SpriteSources);
static SpriteBatch _gMistR18View6SpriteBatches[3];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/mist_r18/_gMistR18View6SpriteBatches", _gMistR18View6SpriteBatches);
static SpriteBatch _gMistR18View7SpriteBatches[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/mist_r18/_gMistR18View7SpriteBatches", _gMistR18View7SpriteBatches);
static SpriteBatch _gMistR18View8SpriteBatches[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/mist_r18/_gMistR18View8SpriteBatches", _gMistR18View8SpriteBatches);
static SpriteBatch _gMistR18View9SpriteBatches[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/mist_r18/_gMistR18View9SpriteBatches", _gMistR18View9SpriteBatches);
static SpriteBatch _gMistR18View10SpriteBatches[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/mist_r18/_gMistR18View10SpriteBatches", _gMistR18View10SpriteBatches);
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
SpriteView gMistR18SpriteViews[10];
static void peDecodeArr_gMistR18SpriteViews(void* base, const unsigned char* src, size_t n)
{
    SpriteView* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteView(&dst[k], src + k * 12);
    dst[0].sources.elements = _gMistR18View1SpriteBatches;
    dst[0].batches = _gMistR18View1SpriteBatches;
    dst[1].sources.elements = _gMistR18View2SpriteBatches;
    dst[1].batches = _gMistR18View2SpriteBatches;
    dst[2].sources.elements = _gMistR18View3SpriteBatches;
    dst[2].batches = _gMistR18View3SpriteBatches;
    dst[3].sources.elements = _gMistR18View4SpriteSources;
    dst[3].batches = _gMistR18View4SpriteBatches;
    dst[4].sources.elements = _gMistR18View5SpriteBatches;
    dst[4].batches = _gMistR18View5SpriteBatches;
    dst[5].sources.elements = _gMistR18View6SpriteSources;
    dst[5].batches = _gMistR18View6SpriteBatches;
    dst[6].sources.elements = _gMistR18View7SpriteBatches;
    dst[6].batches = _gMistR18View7SpriteBatches;
    dst[7].sources.elements = _gMistR18View8SpriteBatches;
    dst[7].batches = _gMistR18View8SpriteBatches;
    dst[8].sources.elements = _gMistR18View9SpriteBatches;
    dst[8].batches = _gMistR18View9SpriteBatches;
    dst[9].sources.elements = _gMistR18View10SpriteBatches;
    dst[9].batches = _gMistR18View10SpriteBatches;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_r18/gMistR18SpriteViews", gMistR18SpriteViews, peDecodeArr_gMistR18SpriteViews);
