/* rooms/akropolis/east_elevator_hall/package: written from its room instance by tools/buildsteps/gen_room_inc.py. */

#include "types.h"
#include "gameplay/sprites.h"

static SpriteBatch _gAkropolisEastElevatorHallView1SpriteBatches[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_east_elevator_hall/_gAkropolisEastElevatorHallView1SpriteBatches", _gAkropolisEastElevatorHallView1SpriteBatches);
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
static SpriteSource _gAkropolisEastElevatorHallView2SpriteSources[39];
static void peDecodeArr_gAkropolisEastElevatorHallView2SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_east_elevator_hall/_gAkropolisEastElevatorHallView2SpriteSources", _gAkropolisEastElevatorHallView2SpriteSources, peDecodeArr_gAkropolisEastElevatorHallView2SpriteSources);
static SpriteBatch _gAkropolisEastElevatorHallView2SpriteBatches[4];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_east_elevator_hall/_gAkropolisEastElevatorHallView2SpriteBatches", _gAkropolisEastElevatorHallView2SpriteBatches);
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
static SpriteSource _gAkropolisEastElevatorHallView3SpriteSources[41];
static void peDecodeArr_gAkropolisEastElevatorHallView3SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_east_elevator_hall/_gAkropolisEastElevatorHallView3SpriteSources", _gAkropolisEastElevatorHallView3SpriteSources, peDecodeArr_gAkropolisEastElevatorHallView3SpriteSources);
static SpriteBatch _gAkropolisEastElevatorHallView3SpriteBatches[4];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_east_elevator_hall/_gAkropolisEastElevatorHallView3SpriteBatches", _gAkropolisEastElevatorHallView3SpriteBatches);
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
static SpriteSource _gAkropolisEastElevatorHallView4SpriteSources[38];
static void peDecodeArr_gAkropolisEastElevatorHallView4SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_east_elevator_hall/_gAkropolisEastElevatorHallView4SpriteSources", _gAkropolisEastElevatorHallView4SpriteSources, peDecodeArr_gAkropolisEastElevatorHallView4SpriteSources);
static SpriteBatch _gAkropolisEastElevatorHallView4SpriteBatches[3];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_east_elevator_hall/_gAkropolisEastElevatorHallView4SpriteBatches", _gAkropolisEastElevatorHallView4SpriteBatches);
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
static SpriteSource _gAkropolisEastElevatorHallView5SpriteSources[28];
static void peDecodeArr_gAkropolisEastElevatorHallView5SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_east_elevator_hall/_gAkropolisEastElevatorHallView5SpriteSources", _gAkropolisEastElevatorHallView5SpriteSources, peDecodeArr_gAkropolisEastElevatorHallView5SpriteSources);
static SpriteBatch _gAkropolisEastElevatorHallView5SpriteBatches[3];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_east_elevator_hall/_gAkropolisEastElevatorHallView5SpriteBatches", _gAkropolisEastElevatorHallView5SpriteBatches);
static SpriteBatch _gAkropolisEastElevatorHallView6SpriteBatches[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_east_elevator_hall/_gAkropolisEastElevatorHallView6SpriteBatches", _gAkropolisEastElevatorHallView6SpriteBatches);
static SpriteBatch _gAkropolisEastElevatorHallView7SpriteBatches[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_east_elevator_hall/_gAkropolisEastElevatorHallView7SpriteBatches", _gAkropolisEastElevatorHallView7SpriteBatches);
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
SpriteView gAkropolisEastElevatorHallSpriteViews[7];
static void peDecodeArr_gAkropolisEastElevatorHallSpriteViews(void* base, const unsigned char* src, size_t n)
{
    SpriteView* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteView(&dst[k], src + k * 12);
    dst[0].sources.elements = _gAkropolisEastElevatorHallView1SpriteBatches;
    dst[0].batches = _gAkropolisEastElevatorHallView1SpriteBatches;
    dst[1].sources.elements = _gAkropolisEastElevatorHallView2SpriteSources;
    dst[1].batches = _gAkropolisEastElevatorHallView2SpriteBatches;
    dst[2].sources.elements = _gAkropolisEastElevatorHallView3SpriteSources;
    dst[2].batches = _gAkropolisEastElevatorHallView3SpriteBatches;
    dst[3].sources.elements = _gAkropolisEastElevatorHallView4SpriteSources;
    dst[3].batches = _gAkropolisEastElevatorHallView4SpriteBatches;
    dst[4].sources.elements = _gAkropolisEastElevatorHallView5SpriteSources;
    dst[4].batches = _gAkropolisEastElevatorHallView5SpriteBatches;
    dst[5].sources.elements = _gAkropolisEastElevatorHallView6SpriteBatches;
    dst[5].batches = _gAkropolisEastElevatorHallView6SpriteBatches;
    dst[6].sources.elements = _gAkropolisEastElevatorHallView7SpriteBatches;
    dst[6].batches = _gAkropolisEastElevatorHallView7SpriteBatches;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_east_elevator_hall/gAkropolisEastElevatorHallSpriteViews", gAkropolisEastElevatorHallSpriteViews, peDecodeArr_gAkropolisEastElevatorHallSpriteViews);
