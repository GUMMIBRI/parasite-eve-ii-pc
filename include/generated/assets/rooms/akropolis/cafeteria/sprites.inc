/* rooms/akropolis/cafeteria/package: written from its room instance by tools/buildsteps/gen_room_inc.py. */

#include "types.h"
#include "gameplay/sprites.h"

static SpriteBatch _gAkropolisCafeteriaViews1And4SpriteBatches[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_cafeteria/_gAkropolisCafeteriaViews1And4SpriteBatches", _gAkropolisCafeteriaViews1And4SpriteBatches);
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
static SpriteSource _gAkropolisCafeteriaView2SpriteSources[40];
static void peDecodeArr_gAkropolisCafeteriaView2SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_cafeteria/_gAkropolisCafeteriaView2SpriteSources", _gAkropolisCafeteriaView2SpriteSources, peDecodeArr_gAkropolisCafeteriaView2SpriteSources);
static SpriteBatch _gAkropolisCafeteriaView2SpriteBatches[10];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_cafeteria/_gAkropolisCafeteriaView2SpriteBatches", _gAkropolisCafeteriaView2SpriteBatches);
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
static SpriteSource _gAkropolisCafeteriaView3SpriteSources[67];
static void peDecodeArr_gAkropolisCafeteriaView3SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_cafeteria/_gAkropolisCafeteriaView3SpriteSources", _gAkropolisCafeteriaView3SpriteSources, peDecodeArr_gAkropolisCafeteriaView3SpriteSources);
static SpriteBatch _gAkropolisCafeteriaView3SpriteBatches[19];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_cafeteria/_gAkropolisCafeteriaView3SpriteBatches", _gAkropolisCafeteriaView3SpriteBatches);
static SpriteBatch _gAkropolisCafeteriaUnusedBackgroundSpriteBatches1[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_cafeteria/_gAkropolisCafeteriaUnusedBackgroundSpriteBatches1", _gAkropolisCafeteriaUnusedBackgroundSpriteBatches1);
static SpriteBatch _gAkropolisCafeteriaView5SpriteBatches[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_cafeteria/_gAkropolisCafeteriaView5SpriteBatches", _gAkropolisCafeteriaView5SpriteBatches);
static SpriteDrawArea _gAkropolisCafeteriaView5DrawAreas[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_cafeteria/_gAkropolisCafeteriaView5DrawAreas", _gAkropolisCafeteriaView5DrawAreas);
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
static SpriteSource _gAkropolisCafeteriaView6SpriteSources[39];
static void peDecodeArr_gAkropolisCafeteriaView6SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_cafeteria/_gAkropolisCafeteriaView6SpriteSources", _gAkropolisCafeteriaView6SpriteSources, peDecodeArr_gAkropolisCafeteriaView6SpriteSources);
static SpriteBatch _gAkropolisCafeteriaView6SpriteBatches[6];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_cafeteria/_gAkropolisCafeteriaView6SpriteBatches", _gAkropolisCafeteriaView6SpriteBatches);
static SpriteBatch _gAkropolisCafeteriaView7SpriteBatches[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_cafeteria/_gAkropolisCafeteriaView7SpriteBatches", _gAkropolisCafeteriaView7SpriteBatches);
static SpriteBatch _gAkropolisCafeteriaView8SpriteBatches[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_cafeteria/_gAkropolisCafeteriaView8SpriteBatches", _gAkropolisCafeteriaView8SpriteBatches);
static SpriteBatch _gAkropolisCafeteriaView9SpriteBatches[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_cafeteria/_gAkropolisCafeteriaView9SpriteBatches", _gAkropolisCafeteriaView9SpriteBatches);
static SpriteBatch _gAkropolisCafeteriaView10SpriteBatches[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_cafeteria/_gAkropolisCafeteriaView10SpriteBatches", _gAkropolisCafeteriaView10SpriteBatches);
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
static SpriteSource _gAkropolisCafeteriaView11SpriteSources[7];
static void peDecodeArr_gAkropolisCafeteriaView11SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_cafeteria/_gAkropolisCafeteriaView11SpriteSources", _gAkropolisCafeteriaView11SpriteSources, peDecodeArr_gAkropolisCafeteriaView11SpriteSources);
static SpriteBatch _gAkropolisCafeteriaView11SpriteBatches[3];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_cafeteria/_gAkropolisCafeteriaView11SpriteBatches", _gAkropolisCafeteriaView11SpriteBatches);
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
static SpriteSource _gAkropolisCafeteriaView12SpriteSources[2];
static void peDecodeArr_gAkropolisCafeteriaView12SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_cafeteria/_gAkropolisCafeteriaView12SpriteSources", _gAkropolisCafeteriaView12SpriteSources, peDecodeArr_gAkropolisCafeteriaView12SpriteSources);
static SpriteBatch _gAkropolisCafeteriaView12SpriteBatches[3];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_cafeteria/_gAkropolisCafeteriaView12SpriteBatches", _gAkropolisCafeteriaView12SpriteBatches);
static SpriteBatch _gAkropolisCafeteriaView13SpriteBatches[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_cafeteria/_gAkropolisCafeteriaView13SpriteBatches", _gAkropolisCafeteriaView13SpriteBatches);
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
static SpriteSource _gAkropolisCafeteriaViews14And22SpriteSources[31];
static void peDecodeArr_gAkropolisCafeteriaViews14And22SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_cafeteria/_gAkropolisCafeteriaViews14And22SpriteSources", _gAkropolisCafeteriaViews14And22SpriteSources, peDecodeArr_gAkropolisCafeteriaViews14And22SpriteSources);
static SpriteBatch _gAkropolisCafeteriaViews14And22SpriteBatches[17];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_cafeteria/_gAkropolisCafeteriaViews14And22SpriteBatches", _gAkropolisCafeteriaViews14And22SpriteBatches);
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
static SpriteSource _gAkropolisCafeteriaView15SpriteSources[12];
static void peDecodeArr_gAkropolisCafeteriaView15SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_cafeteria/_gAkropolisCafeteriaView15SpriteSources", _gAkropolisCafeteriaView15SpriteSources, peDecodeArr_gAkropolisCafeteriaView15SpriteSources);
static SpriteBatch _gAkropolisCafeteriaView15SpriteBatches[3];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_cafeteria/_gAkropolisCafeteriaView15SpriteBatches", _gAkropolisCafeteriaView15SpriteBatches);
static SpriteBatch _gAkropolisCafeteriaView16SpriteBatches[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_cafeteria/_gAkropolisCafeteriaView16SpriteBatches", _gAkropolisCafeteriaView16SpriteBatches);
static SpriteBatch _gAkropolisCafeteriaView17SpriteBatches[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_cafeteria/_gAkropolisCafeteriaView17SpriteBatches", _gAkropolisCafeteriaView17SpriteBatches);
static SpriteBatch _gAkropolisCafeteriaView18SpriteBatches[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_cafeteria/_gAkropolisCafeteriaView18SpriteBatches", _gAkropolisCafeteriaView18SpriteBatches);
static SpriteBatch _gAkropolisCafeteriaView19SpriteBatches[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_cafeteria/_gAkropolisCafeteriaView19SpriteBatches", _gAkropolisCafeteriaView19SpriteBatches);
static SpriteBatch _gAkropolisCafeteriaView20SpriteBatches[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_cafeteria/_gAkropolisCafeteriaView20SpriteBatches", _gAkropolisCafeteriaView20SpriteBatches);
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
static SpriteSource _gAkropolisCafeteriaView21SpriteSources[75];
static void peDecodeArr_gAkropolisCafeteriaView21SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_cafeteria/_gAkropolisCafeteriaView21SpriteSources", _gAkropolisCafeteriaView21SpriteSources, peDecodeArr_gAkropolisCafeteriaView21SpriteSources);
static SpriteBatch _gAkropolisCafeteriaView21SpriteBatches[19];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_cafeteria/_gAkropolisCafeteriaView21SpriteBatches", _gAkropolisCafeteriaView21SpriteBatches);
static SpriteBatch _gAkropolisCafeteriaUnusedBackgroundSpriteBatches2[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_cafeteria/_gAkropolisCafeteriaUnusedBackgroundSpriteBatches2", _gAkropolisCafeteriaUnusedBackgroundSpriteBatches2);
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
static SpriteSource _gAkropolisCafeteriaView23SpriteSources[16];
static void peDecodeArr_gAkropolisCafeteriaView23SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_cafeteria/_gAkropolisCafeteriaView23SpriteSources", _gAkropolisCafeteriaView23SpriteSources, peDecodeArr_gAkropolisCafeteriaView23SpriteSources);
static SpriteBatch _gAkropolisCafeteriaView23SpriteBatches[5];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_cafeteria/_gAkropolisCafeteriaView23SpriteBatches", _gAkropolisCafeteriaView23SpriteBatches);
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
static SpriteSource _gAkropolisCafeteriaView24SpriteSources[1];
static void peDecodeArr_gAkropolisCafeteriaView24SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_cafeteria/_gAkropolisCafeteriaView24SpriteSources", _gAkropolisCafeteriaView24SpriteSources, peDecodeArr_gAkropolisCafeteriaView24SpriteSources);
static SpriteBatch _gAkropolisCafeteriaView24SpriteBatches[3];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_cafeteria/_gAkropolisCafeteriaView24SpriteBatches", _gAkropolisCafeteriaView24SpriteBatches);
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
SpriteView gAkropolisCafeteriaSpriteViews[24];
static void peDecodeArr_gAkropolisCafeteriaSpriteViews(void* base, const unsigned char* src, size_t n)
{
    SpriteView* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteView(&dst[k], src + k * 12);
    dst[0].sources.elements = _gAkropolisCafeteriaViews1And4SpriteBatches;
    dst[0].batches = _gAkropolisCafeteriaViews1And4SpriteBatches;
    dst[1].sources.elements = _gAkropolisCafeteriaView2SpriteSources;
    dst[1].batches = _gAkropolisCafeteriaView2SpriteBatches;
    dst[2].sources.elements = _gAkropolisCafeteriaView3SpriteSources;
    dst[2].batches = _gAkropolisCafeteriaView3SpriteBatches;
    dst[3].sources.elements = _gAkropolisCafeteriaViews1And4SpriteBatches;
    dst[3].batches = _gAkropolisCafeteriaViews1And4SpriteBatches;
    dst[4].sources.elements = _gAkropolisCafeteriaView5SpriteBatches;
    dst[4].batches = _gAkropolisCafeteriaView5SpriteBatches;
    dst[4].drawAreas = _gAkropolisCafeteriaView5DrawAreas;
    dst[5].sources.elements = _gAkropolisCafeteriaView6SpriteSources;
    dst[5].batches = _gAkropolisCafeteriaView6SpriteBatches;
    dst[6].sources.elements = _gAkropolisCafeteriaView7SpriteBatches;
    dst[6].batches = _gAkropolisCafeteriaView7SpriteBatches;
    dst[7].sources.elements = _gAkropolisCafeteriaView8SpriteBatches;
    dst[7].batches = _gAkropolisCafeteriaView8SpriteBatches;
    dst[8].sources.elements = _gAkropolisCafeteriaView9SpriteBatches;
    dst[8].batches = _gAkropolisCafeteriaView9SpriteBatches;
    dst[9].sources.elements = _gAkropolisCafeteriaView10SpriteBatches;
    dst[9].batches = _gAkropolisCafeteriaView10SpriteBatches;
    dst[10].sources.elements = _gAkropolisCafeteriaView11SpriteSources;
    dst[10].batches = _gAkropolisCafeteriaView11SpriteBatches;
    dst[11].sources.elements = _gAkropolisCafeteriaView12SpriteSources;
    dst[11].batches = _gAkropolisCafeteriaView12SpriteBatches;
    dst[12].sources.elements = _gAkropolisCafeteriaView13SpriteBatches;
    dst[12].batches = _gAkropolisCafeteriaView13SpriteBatches;
    dst[13].sources.elements = _gAkropolisCafeteriaViews14And22SpriteSources;
    dst[13].batches = _gAkropolisCafeteriaViews14And22SpriteBatches;
    dst[14].sources.elements = _gAkropolisCafeteriaView15SpriteSources;
    dst[14].batches = _gAkropolisCafeteriaView15SpriteBatches;
    dst[15].sources.elements = _gAkropolisCafeteriaView16SpriteBatches;
    dst[15].batches = _gAkropolisCafeteriaView16SpriteBatches;
    dst[16].sources.elements = _gAkropolisCafeteriaView17SpriteBatches;
    dst[16].batches = _gAkropolisCafeteriaView17SpriteBatches;
    dst[17].sources.elements = _gAkropolisCafeteriaView18SpriteBatches;
    dst[17].batches = _gAkropolisCafeteriaView18SpriteBatches;
    dst[18].sources.elements = _gAkropolisCafeteriaView19SpriteBatches;
    dst[18].batches = _gAkropolisCafeteriaView19SpriteBatches;
    dst[19].sources.elements = _gAkropolisCafeteriaView20SpriteBatches;
    dst[19].batches = _gAkropolisCafeteriaView20SpriteBatches;
    dst[20].sources.elements = _gAkropolisCafeteriaView21SpriteSources;
    dst[20].batches = _gAkropolisCafeteriaView21SpriteBatches;
    dst[21].sources.elements = _gAkropolisCafeteriaViews14And22SpriteSources;
    dst[21].batches = _gAkropolisCafeteriaViews14And22SpriteBatches;
    dst[22].sources.elements = _gAkropolisCafeteriaView23SpriteSources;
    dst[22].batches = _gAkropolisCafeteriaView23SpriteBatches;
    dst[23].sources.elements = _gAkropolisCafeteriaView24SpriteSources;
    dst[23].batches = _gAkropolisCafeteriaView24SpriteBatches;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_cafeteria/gAkropolisCafeteriaSpriteViews", gAkropolisCafeteriaSpriteViews, peDecodeArr_gAkropolisCafeteriaSpriteViews);
