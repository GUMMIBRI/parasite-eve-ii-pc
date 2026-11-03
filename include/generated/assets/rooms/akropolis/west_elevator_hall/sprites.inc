/* rooms/akropolis/west_elevator_hall/package: written from its room instance by tools/buildsteps/gen_room_inc.py. */

#include "types.h"
#include "gameplay/sprites.h"

static SpriteBatch _gAkropolisWestElevatorHallView1SpriteBatches[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_west_elevator_hall/_gAkropolisWestElevatorHallView1SpriteBatches", _gAkropolisWestElevatorHallView1SpriteBatches);
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
static SpriteSource _gAkropolisWestElevatorHallView2SpriteSources[26];
static void peDecodeArr_gAkropolisWestElevatorHallView2SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_west_elevator_hall/_gAkropolisWestElevatorHallView2SpriteSources", _gAkropolisWestElevatorHallView2SpriteSources, peDecodeArr_gAkropolisWestElevatorHallView2SpriteSources);
static SpriteBatch _gAkropolisWestElevatorHallView2SpriteBatches[4];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_west_elevator_hall/_gAkropolisWestElevatorHallView2SpriteBatches", _gAkropolisWestElevatorHallView2SpriteBatches);
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
static SpriteSource _gAkropolisWestElevatorHallView3SpriteSources[63];
static void peDecodeArr_gAkropolisWestElevatorHallView3SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_west_elevator_hall/_gAkropolisWestElevatorHallView3SpriteSources", _gAkropolisWestElevatorHallView3SpriteSources, peDecodeArr_gAkropolisWestElevatorHallView3SpriteSources);
static SpriteBatch _gAkropolisWestElevatorHallView3SpriteBatches[5];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_west_elevator_hall/_gAkropolisWestElevatorHallView3SpriteBatches", _gAkropolisWestElevatorHallView3SpriteBatches);
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
static SpriteSource _gAkropolisWestElevatorHallView4SpriteSources[60];
static void peDecodeArr_gAkropolisWestElevatorHallView4SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_west_elevator_hall/_gAkropolisWestElevatorHallView4SpriteSources", _gAkropolisWestElevatorHallView4SpriteSources, peDecodeArr_gAkropolisWestElevatorHallView4SpriteSources);
static SpriteBatch _gAkropolisWestElevatorHallView4SpriteBatches[4];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_west_elevator_hall/_gAkropolisWestElevatorHallView4SpriteBatches", _gAkropolisWestElevatorHallView4SpriteBatches);
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
static SpriteSource _gAkropolisWestElevatorHallView5SpriteSources[26];
static void peDecodeArr_gAkropolisWestElevatorHallView5SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_west_elevator_hall/_gAkropolisWestElevatorHallView5SpriteSources", _gAkropolisWestElevatorHallView5SpriteSources, peDecodeArr_gAkropolisWestElevatorHallView5SpriteSources);
static SpriteBatch _gAkropolisWestElevatorHallView5SpriteBatches[3];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_west_elevator_hall/_gAkropolisWestElevatorHallView5SpriteBatches", _gAkropolisWestElevatorHallView5SpriteBatches);
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
SpriteView gAkropolisWestElevatorHallSpriteViews[5];
static void peDecodeArr_gAkropolisWestElevatorHallSpriteViews(void* base, const unsigned char* src, size_t n)
{
    SpriteView* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteView(&dst[k], src + k * 12);
    dst[0].sources.elements = _gAkropolisWestElevatorHallView1SpriteBatches;
    dst[0].batches = _gAkropolisWestElevatorHallView1SpriteBatches;
    dst[1].sources.elements = _gAkropolisWestElevatorHallView2SpriteSources;
    dst[1].batches = _gAkropolisWestElevatorHallView2SpriteBatches;
    dst[2].sources.elements = _gAkropolisWestElevatorHallView3SpriteSources;
    dst[2].batches = _gAkropolisWestElevatorHallView3SpriteBatches;
    dst[3].sources.elements = _gAkropolisWestElevatorHallView4SpriteSources;
    dst[3].batches = _gAkropolisWestElevatorHallView4SpriteBatches;
    dst[4].sources.elements = _gAkropolisWestElevatorHallView5SpriteSources;
    dst[4].batches = _gAkropolisWestElevatorHallView5SpriteBatches;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_west_elevator_hall/gAkropolisWestElevatorHallSpriteViews", gAkropolisWestElevatorHallSpriteViews, peDecodeArr_gAkropolisWestElevatorHallSpriteViews);
