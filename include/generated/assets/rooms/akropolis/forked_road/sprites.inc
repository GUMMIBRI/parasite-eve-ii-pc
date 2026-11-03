/* rooms/akropolis/forked_road/package: written from its room instance by tools/buildsteps/gen_room_inc.py. */

#include "types.h"
#include "gameplay/sprites.h"

static SpriteBatch _gAkropolisForkedRoadView1SpriteBatches[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_forked_road/_gAkropolisForkedRoadView1SpriteBatches", _gAkropolisForkedRoadView1SpriteBatches);
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
static SpriteSource _gAkropolisForkedRoadView2SpriteSources[85];
static void peDecodeArr_gAkropolisForkedRoadView2SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_forked_road/_gAkropolisForkedRoadView2SpriteSources", _gAkropolisForkedRoadView2SpriteSources, peDecodeArr_gAkropolisForkedRoadView2SpriteSources);
static SpriteBatch _gAkropolisForkedRoadView2SpriteBatches[12];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_forked_road/_gAkropolisForkedRoadView2SpriteBatches", _gAkropolisForkedRoadView2SpriteBatches);
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
static SpriteSource _gAkropolisForkedRoadViews3And12SpriteSources[6];
static void peDecodeArr_gAkropolisForkedRoadViews3And12SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_forked_road/_gAkropolisForkedRoadViews3And12SpriteSources", _gAkropolisForkedRoadViews3And12SpriteSources, peDecodeArr_gAkropolisForkedRoadViews3And12SpriteSources);
static SpriteBatch _gAkropolisForkedRoadViews3And12SpriteBatches[3];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_forked_road/_gAkropolisForkedRoadViews3And12SpriteBatches", _gAkropolisForkedRoadViews3And12SpriteBatches);
static SpriteBatch _gAkropolisForkedRoadView4SpriteBatches[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_forked_road/_gAkropolisForkedRoadView4SpriteBatches", _gAkropolisForkedRoadView4SpriteBatches);
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
static SpriteSource _gAkropolisForkedRoadView5SpriteSources[6];
static void peDecodeArr_gAkropolisForkedRoadView5SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_forked_road/_gAkropolisForkedRoadView5SpriteSources", _gAkropolisForkedRoadView5SpriteSources, peDecodeArr_gAkropolisForkedRoadView5SpriteSources);
static SpriteBatch _gAkropolisForkedRoadView5SpriteBatches[3];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_forked_road/_gAkropolisForkedRoadView5SpriteBatches", _gAkropolisForkedRoadView5SpriteBatches);
static SpriteBatch _gAkropolisForkedRoadView6SpriteBatches[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_forked_road/_gAkropolisForkedRoadView6SpriteBatches", _gAkropolisForkedRoadView6SpriteBatches);
static SpriteBatch _gAkropolisForkedRoadUnusedEmptySpriteBatches1[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_forked_road/_gAkropolisForkedRoadUnusedEmptySpriteBatches1", _gAkropolisForkedRoadUnusedEmptySpriteBatches1);
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
static SpriteSource _gAkropolisForkedRoadViews7And8SpriteSources[58];
static void peDecodeArr_gAkropolisForkedRoadViews7And8SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_forked_road/_gAkropolisForkedRoadViews7And8SpriteSources", _gAkropolisForkedRoadViews7And8SpriteSources, peDecodeArr_gAkropolisForkedRoadViews7And8SpriteSources);
static SpriteBatch _gAkropolisForkedRoadViews7And8SpriteBatches[6];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_forked_road/_gAkropolisForkedRoadViews7And8SpriteBatches", _gAkropolisForkedRoadViews7And8SpriteBatches);
static SpriteBatch _gAkropolisForkedRoadView9SpriteBatches[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_forked_road/_gAkropolisForkedRoadView9SpriteBatches", _gAkropolisForkedRoadView9SpriteBatches);
static SpriteBatch _gAkropolisForkedRoadView10SpriteBatches[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_forked_road/_gAkropolisForkedRoadView10SpriteBatches", _gAkropolisForkedRoadView10SpriteBatches);
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
static SpriteSource _gAkropolisForkedRoadView11SpriteSources[62];
static void peDecodeArr_gAkropolisForkedRoadView11SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_forked_road/_gAkropolisForkedRoadView11SpriteSources", _gAkropolisForkedRoadView11SpriteSources, peDecodeArr_gAkropolisForkedRoadView11SpriteSources);
static SpriteBatch _gAkropolisForkedRoadView11SpriteBatches[7];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_forked_road/_gAkropolisForkedRoadView11SpriteBatches", _gAkropolisForkedRoadView11SpriteBatches);
static SpriteBatch _gAkropolisForkedRoadUnusedEmptySpriteBatches2[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_forked_road/_gAkropolisForkedRoadUnusedEmptySpriteBatches2", _gAkropolisForkedRoadUnusedEmptySpriteBatches2);
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
SpriteView gAkropolisForkedRoadSpriteViews[12];
static void peDecodeArr_gAkropolisForkedRoadSpriteViews(void* base, const unsigned char* src, size_t n)
{
    SpriteView* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteView(&dst[k], src + k * 12);
    dst[0].sources.elements = _gAkropolisForkedRoadView1SpriteBatches;
    dst[0].batches = _gAkropolisForkedRoadView1SpriteBatches;
    dst[1].sources.elements = _gAkropolisForkedRoadView2SpriteSources;
    dst[1].batches = _gAkropolisForkedRoadView2SpriteBatches;
    dst[2].sources.elements = _gAkropolisForkedRoadViews3And12SpriteSources;
    dst[2].batches = _gAkropolisForkedRoadViews3And12SpriteBatches;
    dst[3].sources.elements = _gAkropolisForkedRoadView4SpriteBatches;
    dst[3].batches = _gAkropolisForkedRoadView4SpriteBatches;
    dst[4].sources.elements = _gAkropolisForkedRoadView5SpriteSources;
    dst[4].batches = _gAkropolisForkedRoadView5SpriteBatches;
    dst[5].sources.elements = _gAkropolisForkedRoadView6SpriteBatches;
    dst[5].batches = _gAkropolisForkedRoadView6SpriteBatches;
    dst[6].sources.elements = _gAkropolisForkedRoadViews7And8SpriteSources;
    dst[6].batches = _gAkropolisForkedRoadViews7And8SpriteBatches;
    dst[7].sources.elements = _gAkropolisForkedRoadViews7And8SpriteSources;
    dst[7].batches = _gAkropolisForkedRoadViews7And8SpriteBatches;
    dst[8].sources.elements = _gAkropolisForkedRoadView9SpriteBatches;
    dst[8].batches = _gAkropolisForkedRoadView9SpriteBatches;
    dst[9].sources.elements = _gAkropolisForkedRoadView10SpriteBatches;
    dst[9].batches = _gAkropolisForkedRoadView10SpriteBatches;
    dst[10].sources.elements = _gAkropolisForkedRoadView11SpriteSources;
    dst[10].batches = _gAkropolisForkedRoadView11SpriteBatches;
    dst[11].sources.elements = _gAkropolisForkedRoadViews3And12SpriteSources;
    dst[11].batches = _gAkropolisForkedRoadViews3And12SpriteBatches;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_forked_road/gAkropolisForkedRoadSpriteViews", gAkropolisForkedRoadSpriteViews, peDecodeArr_gAkropolisForkedRoadSpriteViews);
