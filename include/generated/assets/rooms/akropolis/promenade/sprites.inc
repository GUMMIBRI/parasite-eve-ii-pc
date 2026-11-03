/* rooms/akropolis/promenade/package: written from its room instance by tools/buildsteps/gen_room_inc.py. */

#include "types.h"
#include "gameplay/sprites.h"

static SpriteBatch _gAkropolisPromenadeViews1And13SpriteBatches[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_promenade/_gAkropolisPromenadeViews1And13SpriteBatches", _gAkropolisPromenadeViews1And13SpriteBatches);
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
static SpriteSource _gAkropolisPromenadeView2SpriteSources[74];
static void peDecodeArr_gAkropolisPromenadeView2SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_promenade/_gAkropolisPromenadeView2SpriteSources", _gAkropolisPromenadeView2SpriteSources, peDecodeArr_gAkropolisPromenadeView2SpriteSources);
static SpriteBatch _gAkropolisPromenadeView2SpriteBatches[11];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_promenade/_gAkropolisPromenadeView2SpriteBatches", _gAkropolisPromenadeView2SpriteBatches);
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
static SpriteSource _gAkropolisPromenadeView3SpriteSources[17];
static void peDecodeArr_gAkropolisPromenadeView3SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_promenade/_gAkropolisPromenadeView3SpriteSources", _gAkropolisPromenadeView3SpriteSources, peDecodeArr_gAkropolisPromenadeView3SpriteSources);
static SpriteBatch _gAkropolisPromenadeView3SpriteBatches[5];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_promenade/_gAkropolisPromenadeView3SpriteBatches", _gAkropolisPromenadeView3SpriteBatches);
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
static SpriteSource _gAkropolisPromenadeView4SpriteSources[56];
static void peDecodeArr_gAkropolisPromenadeView4SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_promenade/_gAkropolisPromenadeView4SpriteSources", _gAkropolisPromenadeView4SpriteSources, peDecodeArr_gAkropolisPromenadeView4SpriteSources);
static SpriteBatch _gAkropolisPromenadeView4SpriteBatches[9];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_promenade/_gAkropolisPromenadeView4SpriteBatches", _gAkropolisPromenadeView4SpriteBatches);
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
static SpriteSource _gAkropolisPromenadeView5SpriteSources[83];
static void peDecodeArr_gAkropolisPromenadeView5SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_promenade/_gAkropolisPromenadeView5SpriteSources", _gAkropolisPromenadeView5SpriteSources, peDecodeArr_gAkropolisPromenadeView5SpriteSources);
static SpriteBatch _gAkropolisPromenadeView5SpriteBatches[9];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_promenade/_gAkropolisPromenadeView5SpriteBatches", _gAkropolisPromenadeView5SpriteBatches);
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
static SpriteSource _gAkropolisPromenadeView6SpriteSources[63];
static void peDecodeArr_gAkropolisPromenadeView6SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_promenade/_gAkropolisPromenadeView6SpriteSources", _gAkropolisPromenadeView6SpriteSources, peDecodeArr_gAkropolisPromenadeView6SpriteSources);
static SpriteBatch _gAkropolisPromenadeView6SpriteBatches[9];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_promenade/_gAkropolisPromenadeView6SpriteBatches", _gAkropolisPromenadeView6SpriteBatches);
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
static SpriteSource _gAkropolisPromenadeView7SpriteSources[32];
static void peDecodeArr_gAkropolisPromenadeView7SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_promenade/_gAkropolisPromenadeView7SpriteSources", _gAkropolisPromenadeView7SpriteSources, peDecodeArr_gAkropolisPromenadeView7SpriteSources);
static SpriteBatch _gAkropolisPromenadeView7SpriteBatches[8];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_promenade/_gAkropolisPromenadeView7SpriteBatches", _gAkropolisPromenadeView7SpriteBatches);
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
static SpriteSource _gAkropolisPromenadeView8SpriteSources[46];
static void peDecodeArr_gAkropolisPromenadeView8SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_promenade/_gAkropolisPromenadeView8SpriteSources", _gAkropolisPromenadeView8SpriteSources, peDecodeArr_gAkropolisPromenadeView8SpriteSources);
static SpriteBatch _gAkropolisPromenadeView8SpriteBatches[9];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_promenade/_gAkropolisPromenadeView8SpriteBatches", _gAkropolisPromenadeView8SpriteBatches);
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
static SpriteSource _gAkropolisPromenadeView9SpriteSources[78];
static void peDecodeArr_gAkropolisPromenadeView9SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_promenade/_gAkropolisPromenadeView9SpriteSources", _gAkropolisPromenadeView9SpriteSources, peDecodeArr_gAkropolisPromenadeView9SpriteSources);
static SpriteBatch _gAkropolisPromenadeView9SpriteBatches[10];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_promenade/_gAkropolisPromenadeView9SpriteBatches", _gAkropolisPromenadeView9SpriteBatches);
static SpriteBatch _gAkropolisPromenadeView10SpriteBatches[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_promenade/_gAkropolisPromenadeView10SpriteBatches", _gAkropolisPromenadeView10SpriteBatches);
static SpriteBatch _gAkropolisPromenadeView11SpriteBatches[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_promenade/_gAkropolisPromenadeView11SpriteBatches", _gAkropolisPromenadeView11SpriteBatches);
static SpriteBatch _gAkropolisPromenadeView12SpriteBatches[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_promenade/_gAkropolisPromenadeView12SpriteBatches", _gAkropolisPromenadeView12SpriteBatches);
static SpriteBatch _gAkropolisPromenadeUnusedEmptySpriteBatches[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_promenade/_gAkropolisPromenadeUnusedEmptySpriteBatches", _gAkropolisPromenadeUnusedEmptySpriteBatches);
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
SpriteView gAkropolisPromenadeSpriteViews[13];
static void peDecodeArr_gAkropolisPromenadeSpriteViews(void* base, const unsigned char* src, size_t n)
{
    SpriteView* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteView(&dst[k], src + k * 12);
    dst[0].sources.elements = _gAkropolisPromenadeViews1And13SpriteBatches;
    dst[0].batches = _gAkropolisPromenadeViews1And13SpriteBatches;
    dst[1].sources.elements = _gAkropolisPromenadeView2SpriteSources;
    dst[1].batches = _gAkropolisPromenadeView2SpriteBatches;
    dst[2].sources.elements = _gAkropolisPromenadeView3SpriteSources;
    dst[2].batches = _gAkropolisPromenadeView3SpriteBatches;
    dst[3].sources.elements = _gAkropolisPromenadeView4SpriteSources;
    dst[3].batches = _gAkropolisPromenadeView4SpriteBatches;
    dst[4].sources.elements = _gAkropolisPromenadeView5SpriteSources;
    dst[4].batches = _gAkropolisPromenadeView5SpriteBatches;
    dst[5].sources.elements = _gAkropolisPromenadeView6SpriteSources;
    dst[5].batches = _gAkropolisPromenadeView6SpriteBatches;
    dst[6].sources.elements = _gAkropolisPromenadeView7SpriteSources;
    dst[6].batches = _gAkropolisPromenadeView7SpriteBatches;
    dst[7].sources.elements = _gAkropolisPromenadeView8SpriteSources;
    dst[7].batches = _gAkropolisPromenadeView8SpriteBatches;
    dst[8].sources.elements = _gAkropolisPromenadeView9SpriteSources;
    dst[8].batches = _gAkropolisPromenadeView9SpriteBatches;
    dst[9].sources.elements = _gAkropolisPromenadeView10SpriteBatches;
    dst[9].batches = _gAkropolisPromenadeView10SpriteBatches;
    dst[10].sources.elements = _gAkropolisPromenadeView11SpriteBatches;
    dst[10].batches = _gAkropolisPromenadeView11SpriteBatches;
    dst[11].sources.elements = _gAkropolisPromenadeView12SpriteBatches;
    dst[11].batches = _gAkropolisPromenadeView12SpriteBatches;
    dst[12].sources.elements = _gAkropolisPromenadeViews1And13SpriteBatches;
    dst[12].batches = _gAkropolisPromenadeViews1And13SpriteBatches;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_promenade/gAkropolisPromenadeSpriteViews", gAkropolisPromenadeSpriteViews, peDecodeArr_gAkropolisPromenadeSpriteViews);
