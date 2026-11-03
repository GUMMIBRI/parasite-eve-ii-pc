/* rooms/mist/shooting_gallery/package: written from its room instance by tools/buildsteps/gen_room_inc.py. */

#include "types.h"
#include "gameplay/sprites.h"

static SpriteBatch _gMistShootingGalleryView1SpriteBatches[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/mist_shooting_gallery/_gMistShootingGalleryView1SpriteBatches", _gMistShootingGalleryView1SpriteBatches);
static SpriteBatch _gMistShootingGalleryView2SpriteBatches[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/mist_shooting_gallery/_gMistShootingGalleryView2SpriteBatches", _gMistShootingGalleryView2SpriteBatches);
static SpriteBatch _gMistShootingGalleryView3SpriteBatches[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/mist_shooting_gallery/_gMistShootingGalleryView3SpriteBatches", _gMistShootingGalleryView3SpriteBatches);
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
static SpriteSource _gMistShootingGalleryView4SpriteSources[13];
static void peDecodeArr_gMistShootingGalleryView4SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_shooting_gallery/_gMistShootingGalleryView4SpriteSources", _gMistShootingGalleryView4SpriteSources, peDecodeArr_gMistShootingGalleryView4SpriteSources);
static SpriteBatch _gMistShootingGalleryView4SpriteBatches[3];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/mist_shooting_gallery/_gMistShootingGalleryView4SpriteBatches", _gMistShootingGalleryView4SpriteBatches);
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
static SpriteSource _gMistShootingGalleryView5SpriteSources[32];
static void peDecodeArr_gMistShootingGalleryView5SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_shooting_gallery/_gMistShootingGalleryView5SpriteSources", _gMistShootingGalleryView5SpriteSources, peDecodeArr_gMistShootingGalleryView5SpriteSources);
static SpriteBatch _gMistShootingGalleryView5SpriteBatches[3];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/mist_shooting_gallery/_gMistShootingGalleryView5SpriteBatches", _gMistShootingGalleryView5SpriteBatches);
static SpriteBatch _gMistShootingGalleryView6SpriteBatches[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/mist_shooting_gallery/_gMistShootingGalleryView6SpriteBatches", _gMistShootingGalleryView6SpriteBatches);
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
static SpriteSource _gMistShootingGalleryView7SpriteSources[24];
static void peDecodeArr_gMistShootingGalleryView7SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_shooting_gallery/_gMistShootingGalleryView7SpriteSources", _gMistShootingGalleryView7SpriteSources, peDecodeArr_gMistShootingGalleryView7SpriteSources);
static SpriteBatch _gMistShootingGalleryView7SpriteBatches[4];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/mist_shooting_gallery/_gMistShootingGalleryView7SpriteBatches", _gMistShootingGalleryView7SpriteBatches);
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
static SpriteSource _gMistShootingGalleryView8SpriteSources[25];
static void peDecodeArr_gMistShootingGalleryView8SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_shooting_gallery/_gMistShootingGalleryView8SpriteSources", _gMistShootingGalleryView8SpriteSources, peDecodeArr_gMistShootingGalleryView8SpriteSources);
static SpriteBatch _gMistShootingGalleryView8SpriteBatches[4];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/mist_shooting_gallery/_gMistShootingGalleryView8SpriteBatches", _gMistShootingGalleryView8SpriteBatches);
static SpriteBatch _gMistShootingGalleryView9SpriteBatches[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/mist_shooting_gallery/_gMistShootingGalleryView9SpriteBatches", _gMistShootingGalleryView9SpriteBatches);
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
static SpriteSource _gMistShootingGalleryView10SpriteSources[9];
static void peDecodeArr_gMistShootingGalleryView10SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_shooting_gallery/_gMistShootingGalleryView10SpriteSources", _gMistShootingGalleryView10SpriteSources, peDecodeArr_gMistShootingGalleryView10SpriteSources);
static SpriteBatch _gMistShootingGalleryView10SpriteBatches[5];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/mist_shooting_gallery/_gMistShootingGalleryView10SpriteBatches", _gMistShootingGalleryView10SpriteBatches);
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
static SpriteSource _gMistShootingGalleryView11SpriteSources[13];
static void peDecodeArr_gMistShootingGalleryView11SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_shooting_gallery/_gMistShootingGalleryView11SpriteSources", _gMistShootingGalleryView11SpriteSources, peDecodeArr_gMistShootingGalleryView11SpriteSources);
static SpriteBatch _gMistShootingGalleryView11SpriteBatches[5];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/mist_shooting_gallery/_gMistShootingGalleryView11SpriteBatches", _gMistShootingGalleryView11SpriteBatches);
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
static SpriteSource _gMistShootingGalleryView12SpriteSources[14];
static void peDecodeArr_gMistShootingGalleryView12SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_shooting_gallery/_gMistShootingGalleryView12SpriteSources", _gMistShootingGalleryView12SpriteSources, peDecodeArr_gMistShootingGalleryView12SpriteSources);
static SpriteBatch _gMistShootingGalleryView12SpriteBatches[3];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/mist_shooting_gallery/_gMistShootingGalleryView12SpriteBatches", _gMistShootingGalleryView12SpriteBatches);
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
static SpriteSource _gMistShootingGalleryView13SpriteSources[12];
static void peDecodeArr_gMistShootingGalleryView13SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_shooting_gallery/_gMistShootingGalleryView13SpriteSources", _gMistShootingGalleryView13SpriteSources, peDecodeArr_gMistShootingGalleryView13SpriteSources);
static SpriteBatch _gMistShootingGalleryView13SpriteBatches[3];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/mist_shooting_gallery/_gMistShootingGalleryView13SpriteBatches", _gMistShootingGalleryView13SpriteBatches);
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
static SpriteSource _gMistShootingGalleryView14SpriteSources[29];
static void peDecodeArr_gMistShootingGalleryView14SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_shooting_gallery/_gMistShootingGalleryView14SpriteSources", _gMistShootingGalleryView14SpriteSources, peDecodeArr_gMistShootingGalleryView14SpriteSources);
static SpriteBatch _gMistShootingGalleryView14SpriteBatches[5];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/mist_shooting_gallery/_gMistShootingGalleryView14SpriteBatches", _gMistShootingGalleryView14SpriteBatches);
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
static SpriteSource _gMistShootingGalleryView15SpriteSources[164];
static void peDecodeArr_gMistShootingGalleryView15SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_shooting_gallery/_gMistShootingGalleryView15SpriteSources", _gMistShootingGalleryView15SpriteSources, peDecodeArr_gMistShootingGalleryView15SpriteSources);
static SpriteBatch _gMistShootingGalleryView15SpriteBatches[5];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/mist_shooting_gallery/_gMistShootingGalleryView15SpriteBatches", _gMistShootingGalleryView15SpriteBatches);
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
static SpriteSource _gMistShootingGalleryView16SpriteSources[58];
static void peDecodeArr_gMistShootingGalleryView16SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_shooting_gallery/_gMistShootingGalleryView16SpriteSources", _gMistShootingGalleryView16SpriteSources, peDecodeArr_gMistShootingGalleryView16SpriteSources);
static SpriteBatch _gMistShootingGalleryView16SpriteBatches[3];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/mist_shooting_gallery/_gMistShootingGalleryView16SpriteBatches", _gMistShootingGalleryView16SpriteBatches);
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
static SpriteSource _gMistShootingGalleryView17SpriteSources[6];
static void peDecodeArr_gMistShootingGalleryView17SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_shooting_gallery/_gMistShootingGalleryView17SpriteSources", _gMistShootingGalleryView17SpriteSources, peDecodeArr_gMistShootingGalleryView17SpriteSources);
static SpriteBatch _gMistShootingGalleryView17SpriteBatches[3];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/mist_shooting_gallery/_gMistShootingGalleryView17SpriteBatches", _gMistShootingGalleryView17SpriteBatches);
static SpriteBatch _gMistShootingGalleryView18SpriteBatches[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/mist_shooting_gallery/_gMistShootingGalleryView18SpriteBatches", _gMistShootingGalleryView18SpriteBatches);
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
SpriteView gMistShootingGallerySpriteViews[18];
static void peDecodeArr_gMistShootingGallerySpriteViews(void* base, const unsigned char* src, size_t n)
{
    SpriteView* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteView(&dst[k], src + k * 12);
    dst[0].sources.elements = _gMistShootingGalleryView1SpriteBatches;
    dst[0].batches = _gMistShootingGalleryView1SpriteBatches;
    dst[1].sources.elements = _gMistShootingGalleryView2SpriteBatches;
    dst[1].batches = _gMistShootingGalleryView2SpriteBatches;
    dst[2].sources.elements = _gMistShootingGalleryView3SpriteBatches;
    dst[2].batches = _gMistShootingGalleryView3SpriteBatches;
    dst[3].sources.elements = _gMistShootingGalleryView4SpriteSources;
    dst[3].batches = _gMistShootingGalleryView4SpriteBatches;
    dst[4].sources.elements = _gMistShootingGalleryView5SpriteSources;
    dst[4].batches = _gMistShootingGalleryView5SpriteBatches;
    dst[5].sources.elements = _gMistShootingGalleryView6SpriteBatches;
    dst[5].batches = _gMistShootingGalleryView6SpriteBatches;
    dst[6].sources.elements = _gMistShootingGalleryView7SpriteSources;
    dst[6].batches = _gMistShootingGalleryView7SpriteBatches;
    dst[7].sources.elements = _gMistShootingGalleryView8SpriteSources;
    dst[7].batches = _gMistShootingGalleryView8SpriteBatches;
    dst[8].sources.elements = _gMistShootingGalleryView9SpriteBatches;
    dst[8].batches = _gMistShootingGalleryView9SpriteBatches;
    dst[9].sources.elements = _gMistShootingGalleryView10SpriteSources;
    dst[9].batches = _gMistShootingGalleryView10SpriteBatches;
    dst[10].sources.elements = _gMistShootingGalleryView11SpriteSources;
    dst[10].batches = _gMistShootingGalleryView11SpriteBatches;
    dst[11].sources.elements = _gMistShootingGalleryView12SpriteSources;
    dst[11].batches = _gMistShootingGalleryView12SpriteBatches;
    dst[12].sources.elements = _gMistShootingGalleryView13SpriteSources;
    dst[12].batches = _gMistShootingGalleryView13SpriteBatches;
    dst[13].sources.elements = _gMistShootingGalleryView14SpriteSources;
    dst[13].batches = _gMistShootingGalleryView14SpriteBatches;
    dst[14].sources.elements = _gMistShootingGalleryView15SpriteSources;
    dst[14].batches = _gMistShootingGalleryView15SpriteBatches;
    dst[15].sources.elements = _gMistShootingGalleryView16SpriteSources;
    dst[15].batches = _gMistShootingGalleryView16SpriteBatches;
    dst[16].sources.elements = _gMistShootingGalleryView17SpriteSources;
    dst[16].batches = _gMistShootingGalleryView17SpriteBatches;
    dst[17].sources.elements = _gMistShootingGalleryView18SpriteBatches;
    dst[17].batches = _gMistShootingGalleryView18SpriteBatches;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_shooting_gallery/gMistShootingGallerySpriteViews", gMistShootingGallerySpriteViews, peDecodeArr_gMistShootingGallerySpriteViews);
