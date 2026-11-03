/* rooms/akropolis/fire_escape/package: written from its room instance by tools/buildsteps/gen_room_inc.py. */

#include "types.h"
#include "gameplay/sprites.h"

static SpriteBatch _gAkropolisFireEscapeView1SpriteBatches[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_fire_escape/_gAkropolisFireEscapeView1SpriteBatches", _gAkropolisFireEscapeView1SpriteBatches);
static SpriteBatch _gAkropolisFireEscapeView2SpriteBatches[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_fire_escape/_gAkropolisFireEscapeView2SpriteBatches", _gAkropolisFireEscapeView2SpriteBatches);
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
static SpriteSource _gAkropolisFireEscapeView3SpriteSources[13];
static void peDecodeArr_gAkropolisFireEscapeView3SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_fire_escape/_gAkropolisFireEscapeView3SpriteSources", _gAkropolisFireEscapeView3SpriteSources, peDecodeArr_gAkropolisFireEscapeView3SpriteSources);
static SpriteBatch _gAkropolisFireEscapeView3SpriteBatches[3];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_fire_escape/_gAkropolisFireEscapeView3SpriteBatches", _gAkropolisFireEscapeView3SpriteBatches);
static SpriteBatch _gAkropolisFireEscapeView4SpriteBatches[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_fire_escape/_gAkropolisFireEscapeView4SpriteBatches", _gAkropolisFireEscapeView4SpriteBatches);
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
static SpriteSource _gAkropolisFireEscapeView5SpriteSources[5];
static void peDecodeArr_gAkropolisFireEscapeView5SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_fire_escape/_gAkropolisFireEscapeView5SpriteSources", _gAkropolisFireEscapeView5SpriteSources, peDecodeArr_gAkropolisFireEscapeView5SpriteSources);
static SpriteBatch _gAkropolisFireEscapeView5SpriteBatches[3];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_fire_escape/_gAkropolisFireEscapeView5SpriteBatches", _gAkropolisFireEscapeView5SpriteBatches);
static SpriteBatch _gAkropolisFireEscapeView6SpriteBatches[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_fire_escape/_gAkropolisFireEscapeView6SpriteBatches", _gAkropolisFireEscapeView6SpriteBatches);
static SpriteDrawArea _gAkropolisFireEscapeView6SpriteDrawAreas[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_fire_escape/_gAkropolisFireEscapeView6SpriteDrawAreas", _gAkropolisFireEscapeView6SpriteDrawAreas);
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
static SpriteSource _gAkropolisFireEscapeView7SpriteSources[5];
static void peDecodeArr_gAkropolisFireEscapeView7SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_fire_escape/_gAkropolisFireEscapeView7SpriteSources", _gAkropolisFireEscapeView7SpriteSources, peDecodeArr_gAkropolisFireEscapeView7SpriteSources);
static SpriteBatch _gAkropolisFireEscapeView7SpriteBatches[3];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_fire_escape/_gAkropolisFireEscapeView7SpriteBatches", _gAkropolisFireEscapeView7SpriteBatches);
static SpriteBatch _gAkropolisFireEscapeView8SpriteBatches[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_fire_escape/_gAkropolisFireEscapeView8SpriteBatches", _gAkropolisFireEscapeView8SpriteBatches);
static SpriteBatch _gAkropolisFireEscapeViews9And10SpriteBatches[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_fire_escape/_gAkropolisFireEscapeViews9And10SpriteBatches", _gAkropolisFireEscapeViews9And10SpriteBatches);
static SpriteDrawArea _gAkropolisFireEscapeView9SpriteDrawAreas[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_fire_escape/_gAkropolisFireEscapeView9SpriteDrawAreas", _gAkropolisFireEscapeView9SpriteDrawAreas);
static SpriteBatch _gAkropolisFireEscapeUnusedSpriteBatches[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_fire_escape/_gAkropolisFireEscapeUnusedSpriteBatches", _gAkropolisFireEscapeUnusedSpriteBatches);
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
SpriteView gAkropolisFireEscapeSpriteViews[10];
static void peDecodeArr_gAkropolisFireEscapeSpriteViews(void* base, const unsigned char* src, size_t n)
{
    SpriteView* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteView(&dst[k], src + k * 12);
    dst[0].sources.elements = _gAkropolisFireEscapeView1SpriteBatches;
    dst[0].batches = _gAkropolisFireEscapeView1SpriteBatches;
    dst[1].sources.elements = _gAkropolisFireEscapeView2SpriteBatches;
    dst[1].batches = _gAkropolisFireEscapeView2SpriteBatches;
    dst[2].sources.elements = _gAkropolisFireEscapeView3SpriteSources;
    dst[2].batches = _gAkropolisFireEscapeView3SpriteBatches;
    dst[3].sources.elements = _gAkropolisFireEscapeView4SpriteBatches;
    dst[3].batches = _gAkropolisFireEscapeView4SpriteBatches;
    dst[4].sources.elements = _gAkropolisFireEscapeView5SpriteSources;
    dst[4].batches = _gAkropolisFireEscapeView5SpriteBatches;
    dst[5].sources.elements = _gAkropolisFireEscapeView6SpriteBatches;
    dst[5].batches = _gAkropolisFireEscapeView6SpriteBatches;
    dst[5].drawAreas = _gAkropolisFireEscapeView6SpriteDrawAreas;
    dst[6].sources.elements = _gAkropolisFireEscapeView7SpriteSources;
    dst[6].batches = _gAkropolisFireEscapeView7SpriteBatches;
    dst[7].sources.elements = _gAkropolisFireEscapeView8SpriteBatches;
    dst[7].batches = _gAkropolisFireEscapeView8SpriteBatches;
    dst[8].sources.elements = _gAkropolisFireEscapeViews9And10SpriteBatches;
    dst[8].batches = _gAkropolisFireEscapeViews9And10SpriteBatches;
    dst[8].drawAreas = _gAkropolisFireEscapeView9SpriteDrawAreas;
    dst[9].sources.elements = _gAkropolisFireEscapeViews9And10SpriteBatches;
    dst[9].batches = _gAkropolisFireEscapeViews9And10SpriteBatches;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_fire_escape/gAkropolisFireEscapeSpriteViews", gAkropolisFireEscapeSpriteViews, peDecodeArr_gAkropolisFireEscapeSpriteViews);
