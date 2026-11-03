/* rooms/akropolis/plaza/package: written from its room instance by tools/buildsteps/gen_room_inc.py. */

#include "types.h"
#include "gameplay/sprites.h"

static SpriteBatch _gAkropolisPlazaHideImageSpriteBatches[1];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_plaza/_gAkropolisPlazaHideImageSpriteBatches", _gAkropolisPlazaHideImageSpriteBatches);
static SpriteBatch _gAkropolisPlazaShowImageSpriteBatches[1];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_plaza/_gAkropolisPlazaShowImageSpriteBatches", _gAkropolisPlazaShowImageSpriteBatches);
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
SpriteView gAkropolisPlazaSpriteViews[8];
static void peDecodeArr_gAkropolisPlazaSpriteViews(void* base, const unsigned char* src, size_t n)
{
    SpriteView* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteView(&dst[k], src + k * 12);
    dst[0].batches = _gAkropolisPlazaShowImageSpriteBatches;
    dst[1].batches = _gAkropolisPlazaHideImageSpriteBatches;
    dst[2].batches = _gAkropolisPlazaShowImageSpriteBatches;
    dst[3].batches = _gAkropolisPlazaShowImageSpriteBatches;
    dst[4].batches = _gAkropolisPlazaShowImageSpriteBatches;
    dst[5].batches = _gAkropolisPlazaShowImageSpriteBatches;
    dst[6].batches = _gAkropolisPlazaShowImageSpriteBatches;
    dst[7].batches = _gAkropolisPlazaHideImageSpriteBatches;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_plaza/gAkropolisPlazaSpriteViews", gAkropolisPlazaSpriteViews, peDecodeArr_gAkropolisPlazaSpriteViews);
