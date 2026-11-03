/* rooms/mist/parking/package: written from its room instance by tools/buildsteps/gen_room_inc.py. */

#include "types.h"
#include "gameplay/sprites.h"

static SpriteBatch _gMistParkingView1SpriteBatches[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/mist_parking/_gMistParkingView1SpriteBatches", _gMistParkingView1SpriteBatches);
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
static SpriteSource _gMistParkingView2SpriteSources[21];
static void peDecodeArr_gMistParkingView2SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_parking/_gMistParkingView2SpriteSources", _gMistParkingView2SpriteSources, peDecodeArr_gMistParkingView2SpriteSources);
static SpriteBatch _gMistParkingView2SpriteBatches[3];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/mist_parking/_gMistParkingView2SpriteBatches", _gMistParkingView2SpriteBatches);
static SpriteBatch _gMistParkingView3SpriteBatches[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/mist_parking/_gMistParkingView3SpriteBatches", _gMistParkingView3SpriteBatches);
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
static SpriteSource _gMistParkingView4SpriteSources[26];
static void peDecodeArr_gMistParkingView4SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_parking/_gMistParkingView4SpriteSources", _gMistParkingView4SpriteSources, peDecodeArr_gMistParkingView4SpriteSources);
static SpriteBatch _gMistParkingView4SpriteBatches[5];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/mist_parking/_gMistParkingView4SpriteBatches", _gMistParkingView4SpriteBatches);
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
static SpriteSource _gMistParkingView5SpriteSources[39];
static void peDecodeArr_gMistParkingView5SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_parking/_gMistParkingView5SpriteSources", _gMistParkingView5SpriteSources, peDecodeArr_gMistParkingView5SpriteSources);
static SpriteBatch _gMistParkingView5SpriteBatches[5];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/mist_parking/_gMistParkingView5SpriteBatches", _gMistParkingView5SpriteBatches);
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
static SpriteSource _gMistParkingView6SpriteSources[37];
static void peDecodeArr_gMistParkingView6SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_parking/_gMistParkingView6SpriteSources", _gMistParkingView6SpriteSources, peDecodeArr_gMistParkingView6SpriteSources);
static SpriteBatch _gMistParkingView6SpriteBatches[7];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/mist_parking/_gMistParkingView6SpriteBatches", _gMistParkingView6SpriteBatches);
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
static SpriteSource _gMistParkingView7SpriteSources[9];
static void peDecodeArr_gMistParkingView7SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_parking/_gMistParkingView7SpriteSources", _gMistParkingView7SpriteSources, peDecodeArr_gMistParkingView7SpriteSources);
static SpriteBatch _gMistParkingView7SpriteBatches[3];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/mist_parking/_gMistParkingView7SpriteBatches", _gMistParkingView7SpriteBatches);
static SpriteBatch _gMistParkingView8SpriteBatches[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/mist_parking/_gMistParkingView8SpriteBatches", _gMistParkingView8SpriteBatches);
static SpriteBatch _gMistParkingView9SpriteBatches[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/mist_parking/_gMistParkingView9SpriteBatches", _gMistParkingView9SpriteBatches);
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
static SpriteSource _gMistParkingView10SpriteSources[25];
static void peDecodeArr_gMistParkingView10SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_parking/_gMistParkingView10SpriteSources", _gMistParkingView10SpriteSources, peDecodeArr_gMistParkingView10SpriteSources);
static SpriteBatch _gMistParkingView10SpriteBatches[3];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/mist_parking/_gMistParkingView10SpriteBatches", _gMistParkingView10SpriteBatches);
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
static SpriteSource _gMistParkingView11SpriteSources[4];
static void peDecodeArr_gMistParkingView11SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_parking/_gMistParkingView11SpriteSources", _gMistParkingView11SpriteSources, peDecodeArr_gMistParkingView11SpriteSources);
static SpriteBatch _gMistParkingView11SpriteBatches[3];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/mist_parking/_gMistParkingView11SpriteBatches", _gMistParkingView11SpriteBatches);
static SpriteBatch _gMistParkingView12SpriteBatches[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/mist_parking/_gMistParkingView12SpriteBatches", _gMistParkingView12SpriteBatches);
static SpriteBatch _gMistParkingView13SpriteBatches[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/mist_parking/_gMistParkingView13SpriteBatches", _gMistParkingView13SpriteBatches);
static SpriteBatch _gMistParkingView14SpriteBatches[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/mist_parking/_gMistParkingView14SpriteBatches", _gMistParkingView14SpriteBatches);
static SpriteBatch _gMistParkingView15SpriteBatches[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/mist_parking/_gMistParkingView15SpriteBatches", _gMistParkingView15SpriteBatches);
static SpriteBatch _gMistParkingView16SpriteBatches[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/mist_parking/_gMistParkingView16SpriteBatches", _gMistParkingView16SpriteBatches);
static SpriteBatch _gMistParkingView17SpriteBatches[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/mist_parking/_gMistParkingView17SpriteBatches", _gMistParkingView17SpriteBatches);
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
static SpriteSource _gMistParkingView18SpriteSources[35];
static void peDecodeArr_gMistParkingView18SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_parking/_gMistParkingView18SpriteSources", _gMistParkingView18SpriteSources, peDecodeArr_gMistParkingView18SpriteSources);
static SpriteBatch _gMistParkingView18SpriteBatches[5];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/mist_parking/_gMistParkingView18SpriteBatches", _gMistParkingView18SpriteBatches);
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
static SpriteSource _gMistParkingView19SpriteSources[43];
static void peDecodeArr_gMistParkingView19SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_parking/_gMistParkingView19SpriteSources", _gMistParkingView19SpriteSources, peDecodeArr_gMistParkingView19SpriteSources);
static SpriteBatch _gMistParkingView19SpriteBatches[7];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/mist_parking/_gMistParkingView19SpriteBatches", _gMistParkingView19SpriteBatches);
static SpriteBatch _gMistParkingView20SpriteBatches[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/mist_parking/_gMistParkingView20SpriteBatches", _gMistParkingView20SpriteBatches);
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
SpriteView gMistParkingSpriteViews[20];
static void peDecodeArr_gMistParkingSpriteViews(void* base, const unsigned char* src, size_t n)
{
    SpriteView* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteView(&dst[k], src + k * 12);
    dst[0].sources.elements = _gMistParkingView1SpriteBatches;
    dst[0].batches = _gMistParkingView1SpriteBatches;
    dst[1].sources.elements = _gMistParkingView2SpriteSources;
    dst[1].batches = _gMistParkingView2SpriteBatches;
    dst[2].sources.elements = _gMistParkingView3SpriteBatches;
    dst[2].batches = _gMistParkingView3SpriteBatches;
    dst[3].sources.elements = _gMistParkingView4SpriteSources;
    dst[3].batches = _gMistParkingView4SpriteBatches;
    dst[4].sources.elements = _gMistParkingView5SpriteSources;
    dst[4].batches = _gMistParkingView5SpriteBatches;
    dst[5].sources.elements = _gMistParkingView6SpriteSources;
    dst[5].batches = _gMistParkingView6SpriteBatches;
    dst[6].sources.elements = _gMistParkingView7SpriteSources;
    dst[6].batches = _gMistParkingView7SpriteBatches;
    dst[7].sources.elements = _gMistParkingView8SpriteBatches;
    dst[7].batches = _gMistParkingView8SpriteBatches;
    dst[8].sources.elements = _gMistParkingView9SpriteBatches;
    dst[8].batches = _gMistParkingView9SpriteBatches;
    dst[9].sources.elements = _gMistParkingView10SpriteSources;
    dst[9].batches = _gMistParkingView10SpriteBatches;
    dst[10].sources.elements = _gMistParkingView11SpriteSources;
    dst[10].batches = _gMistParkingView11SpriteBatches;
    dst[11].sources.elements = _gMistParkingView12SpriteBatches;
    dst[11].batches = _gMistParkingView12SpriteBatches;
    dst[12].sources.elements = _gMistParkingView13SpriteBatches;
    dst[12].batches = _gMistParkingView13SpriteBatches;
    dst[13].sources.elements = _gMistParkingView14SpriteBatches;
    dst[13].batches = _gMistParkingView14SpriteBatches;
    dst[14].sources.elements = _gMistParkingView15SpriteBatches;
    dst[14].batches = _gMistParkingView15SpriteBatches;
    dst[15].sources.elements = _gMistParkingView16SpriteBatches;
    dst[15].batches = _gMistParkingView16SpriteBatches;
    dst[16].sources.elements = _gMistParkingView17SpriteBatches;
    dst[16].batches = _gMistParkingView17SpriteBatches;
    dst[17].sources.elements = _gMistParkingView18SpriteSources;
    dst[17].batches = _gMistParkingView18SpriteBatches;
    dst[18].sources.elements = _gMistParkingView19SpriteSources;
    dst[18].batches = _gMistParkingView19SpriteBatches;
    dst[19].sources.elements = _gMistParkingView20SpriteBatches;
    dst[19].batches = _gMistParkingView20SpriteBatches;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_parking/gMistParkingSpriteViews", gMistParkingSpriteViews, peDecodeArr_gMistParkingSpriteViews);
