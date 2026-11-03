/* rooms/akropolis/roof_garden/package: written from its room instance by tools/buildsteps/gen_room_inc.py. */

#include "types.h"
#include "gameplay/sprites.h"

static SpriteBatch _gAkropolisRoofGardenView1SpriteBatches[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_roof_garden/_gAkropolisRoofGardenView1SpriteBatches", _gAkropolisRoofGardenView1SpriteBatches);
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
static SpriteSource _gAkropolisRoofGardenView2SpriteSources[26];
static void peDecodeArr_gAkropolisRoofGardenView2SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_roof_garden/_gAkropolisRoofGardenView2SpriteSources", _gAkropolisRoofGardenView2SpriteSources, peDecodeArr_gAkropolisRoofGardenView2SpriteSources);
static SpriteBatch _gAkropolisRoofGardenView2SpriteBatches[3];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_roof_garden/_gAkropolisRoofGardenView2SpriteBatches", _gAkropolisRoofGardenView2SpriteBatches);
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
static SpriteSource _gAkropolisRoofGardenView3SpriteSources[57];
static void peDecodeArr_gAkropolisRoofGardenView3SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_roof_garden/_gAkropolisRoofGardenView3SpriteSources", _gAkropolisRoofGardenView3SpriteSources, peDecodeArr_gAkropolisRoofGardenView3SpriteSources);
static SpriteBatch _gAkropolisRoofGardenView3SpriteBatches[9];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_roof_garden/_gAkropolisRoofGardenView3SpriteBatches", _gAkropolisRoofGardenView3SpriteBatches);
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
static SpriteSource _gAkropolisRoofGardenView4SpriteSources[21];
static void peDecodeArr_gAkropolisRoofGardenView4SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_roof_garden/_gAkropolisRoofGardenView4SpriteSources", _gAkropolisRoofGardenView4SpriteSources, peDecodeArr_gAkropolisRoofGardenView4SpriteSources);
static SpriteBatch _gAkropolisRoofGardenView4SpriteBatches[6];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_roof_garden/_gAkropolisRoofGardenView4SpriteBatches", _gAkropolisRoofGardenView4SpriteBatches);
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
static SpriteSource _gAkropolisRoofGardenView5SpriteSources[47];
static void peDecodeArr_gAkropolisRoofGardenView5SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_roof_garden/_gAkropolisRoofGardenView5SpriteSources", _gAkropolisRoofGardenView5SpriteSources, peDecodeArr_gAkropolisRoofGardenView5SpriteSources);
static SpriteBatch _gAkropolisRoofGardenView5SpriteBatches[5];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_roof_garden/_gAkropolisRoofGardenView5SpriteBatches", _gAkropolisRoofGardenView5SpriteBatches);
static SpriteBatch _gAkropolisRoofGardenView6SpriteBatches[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_roof_garden/_gAkropolisRoofGardenView6SpriteBatches", _gAkropolisRoofGardenView6SpriteBatches);
static SpriteBatch _gAkropolisRoofGardenView7SpriteBatches[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_roof_garden/_gAkropolisRoofGardenView7SpriteBatches", _gAkropolisRoofGardenView7SpriteBatches);
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
SpriteView gAkropolisRoofGardenSpriteViews[7];
static void peDecodeArr_gAkropolisRoofGardenSpriteViews(void* base, const unsigned char* src, size_t n)
{
    SpriteView* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteView(&dst[k], src + k * 12);
    dst[0].sources.elements = _gAkropolisRoofGardenView1SpriteBatches;
    dst[0].batches = _gAkropolisRoofGardenView1SpriteBatches;
    dst[1].sources.elements = _gAkropolisRoofGardenView2SpriteSources;
    dst[1].batches = _gAkropolisRoofGardenView2SpriteBatches;
    dst[2].sources.elements = _gAkropolisRoofGardenView3SpriteSources;
    dst[2].batches = _gAkropolisRoofGardenView3SpriteBatches;
    dst[3].sources.elements = _gAkropolisRoofGardenView4SpriteSources;
    dst[3].batches = _gAkropolisRoofGardenView4SpriteBatches;
    dst[4].sources.elements = _gAkropolisRoofGardenView5SpriteSources;
    dst[4].batches = _gAkropolisRoofGardenView5SpriteBatches;
    dst[5].sources.elements = _gAkropolisRoofGardenView6SpriteBatches;
    dst[5].batches = _gAkropolisRoofGardenView6SpriteBatches;
    dst[6].sources.elements = _gAkropolisRoofGardenView7SpriteBatches;
    dst[6].batches = _gAkropolisRoofGardenView7SpriteBatches;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_roof_garden/gAkropolisRoofGardenSpriteViews", gAkropolisRoofGardenSpriteViews, peDecodeArr_gAkropolisRoofGardenSpriteViews);
