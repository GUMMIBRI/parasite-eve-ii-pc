/* rooms/akropolis/observatory/package: written from its room instance by tools/buildsteps/gen_room_inc.py. */

#include "types.h"
#include "gameplay/sprites.h"

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
static SpriteSource _gAkropolisObservatoryView4SpriteSources[67];
static void peDecodeArr_gAkropolisObservatoryView4SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_observatory/_gAkropolisObservatoryView4SpriteSources", _gAkropolisObservatoryView4SpriteSources, peDecodeArr_gAkropolisObservatoryView4SpriteSources);
static SpriteBatch _gAkropolisObservatoryView4SpriteBatches[12];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_observatory/_gAkropolisObservatoryView4SpriteBatches", _gAkropolisObservatoryView4SpriteBatches);
static SpriteBatch _gAkropolisObservatoryView5SpriteBatches[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_observatory/_gAkropolisObservatoryView5SpriteBatches", _gAkropolisObservatoryView5SpriteBatches);
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
static SpriteSource _gAkropolisObservatoryView6SpriteSources[29];
static void peDecodeArr_gAkropolisObservatoryView6SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_observatory/_gAkropolisObservatoryView6SpriteSources", _gAkropolisObservatoryView6SpriteSources, peDecodeArr_gAkropolisObservatoryView6SpriteSources);
static SpriteBatch _gAkropolisObservatoryView6SpriteBatches[6];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_observatory/_gAkropolisObservatoryView6SpriteBatches", _gAkropolisObservatoryView6SpriteBatches);
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
static SpriteSource _gAkropolisObservatoryView7SpriteSources[36];
static void peDecodeArr_gAkropolisObservatoryView7SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_observatory/_gAkropolisObservatoryView7SpriteSources", _gAkropolisObservatoryView7SpriteSources, peDecodeArr_gAkropolisObservatoryView7SpriteSources);
static SpriteBatch _gAkropolisObservatoryView7SpriteBatches[8];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_observatory/_gAkropolisObservatoryView7SpriteBatches", _gAkropolisObservatoryView7SpriteBatches);
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
static SpriteSource _gAkropolisObservatoryView8SpriteSources[81];
static void peDecodeArr_gAkropolisObservatoryView8SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_observatory/_gAkropolisObservatoryView8SpriteSources", _gAkropolisObservatoryView8SpriteSources, peDecodeArr_gAkropolisObservatoryView8SpriteSources);
static SpriteBatch _gAkropolisObservatoryView8SpriteBatches[10];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_observatory/_gAkropolisObservatoryView8SpriteBatches", _gAkropolisObservatoryView8SpriteBatches);
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
SpriteView gAkropolisObservatorySpriteViews[8];
static void peDecodeArr_gAkropolisObservatorySpriteViews(void* base, const unsigned char* src, size_t n)
{
    SpriteView* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteView(&dst[k], src + k * 12);
    dst[0].sources.elements = _gAkropolisObservatoryView1SpriteBatches;
    dst[0].batches = _gAkropolisObservatoryView1SpriteBatches;
    dst[1].sources.elements = _gAkropolisObservatoryView2SpriteSources;
    dst[1].batches = _gAkropolisObservatoryView2SpriteBatches;
    dst[2].sources.elements = _gAkropolisObservatoryView3SpriteSources;
    dst[2].batches = _gAkropolisObservatoryView3SpriteBatches;
    dst[3].sources.elements = _gAkropolisObservatoryView4SpriteSources;
    dst[3].batches = _gAkropolisObservatoryView4SpriteBatches;
    dst[4].sources.elements = _gAkropolisObservatoryView5SpriteBatches;
    dst[4].batches = _gAkropolisObservatoryView5SpriteBatches;
    dst[5].sources.elements = _gAkropolisObservatoryView6SpriteSources;
    dst[5].batches = _gAkropolisObservatoryView6SpriteBatches;
    dst[6].sources.elements = _gAkropolisObservatoryView7SpriteSources;
    dst[6].batches = _gAkropolisObservatoryView7SpriteBatches;
    dst[7].sources.elements = _gAkropolisObservatoryView8SpriteSources;
    dst[7].batches = _gAkropolisObservatoryView8SpriteBatches;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_observatory/gAkropolisObservatorySpriteViews", gAkropolisObservatorySpriteViews, peDecodeArr_gAkropolisObservatorySpriteViews);
