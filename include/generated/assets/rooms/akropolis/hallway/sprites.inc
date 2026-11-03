/* rooms/akropolis/hallway/package: written from its room instance by tools/buildsteps/gen_room_inc.py. */

#include "types.h"
#include "gameplay/sprites.h"

static SpriteBatch _gAkropolisHallwayView1SpriteBatches[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_hallway/_gAkropolisHallwayView1SpriteBatches", _gAkropolisHallwayView1SpriteBatches);
static SpriteBatch _gAkropolisHallwayView2SpriteBatches[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_hallway/_gAkropolisHallwayView2SpriteBatches", _gAkropolisHallwayView2SpriteBatches);
static SpriteBatch _gAkropolisHallwayView3SpriteBatches[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_hallway/_gAkropolisHallwayView3SpriteBatches", _gAkropolisHallwayView3SpriteBatches);
static SpriteBatch _gAkropolisHallwayView4SpriteBatches[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_hallway/_gAkropolisHallwayView4SpriteBatches", _gAkropolisHallwayView4SpriteBatches);
static SpriteBatch _gAkropolisHallwayView5SpriteBatches[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_hallway/_gAkropolisHallwayView5SpriteBatches", _gAkropolisHallwayView5SpriteBatches);
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
SpriteView gAkropolisHallwaySpriteViews[5];
static void peDecodeArr_gAkropolisHallwaySpriteViews(void* base, const unsigned char* src, size_t n)
{
    SpriteView* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteView(&dst[k], src + k * 12);
    dst[0].sources.elements = _gAkropolisHallwayView1SpriteBatches;
    dst[0].batches = _gAkropolisHallwayView1SpriteBatches;
    dst[1].sources.elements = _gAkropolisHallwayView2SpriteBatches;
    dst[1].batches = _gAkropolisHallwayView2SpriteBatches;
    dst[2].sources.elements = _gAkropolisHallwayView3SpriteBatches;
    dst[2].batches = _gAkropolisHallwayView3SpriteBatches;
    dst[3].sources.elements = _gAkropolisHallwayView4SpriteBatches;
    dst[3].batches = _gAkropolisHallwayView4SpriteBatches;
    dst[4].sources.elements = _gAkropolisHallwayView5SpriteBatches;
    dst[4].batches = _gAkropolisHallwayView5SpriteBatches;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_hallway/gAkropolisHallwaySpriteViews", gAkropolisHallwaySpriteViews, peDecodeArr_gAkropolisHallwaySpriteViews);
