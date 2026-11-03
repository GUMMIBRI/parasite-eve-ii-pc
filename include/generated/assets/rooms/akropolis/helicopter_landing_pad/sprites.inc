/* rooms/akropolis/helicopter_landing_pad/package: written from its room instance by tools/buildsteps/gen_room_inc.py. */

#include "types.h"
#include "gameplay/sprites.h"

static SpriteBatch _gAkropolisHelicopterLandingPadView1SpriteBatches[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_helicopter_landing_pad/_gAkropolisHelicopterLandingPadView1SpriteBatches", _gAkropolisHelicopterLandingPadView1SpriteBatches);
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
static SpriteSource _gAkropolisHelicopterLandingPadView2SpriteSources[17];
static void peDecodeArr_gAkropolisHelicopterLandingPadView2SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_helicopter_landing_pad/_gAkropolisHelicopterLandingPadView2SpriteSources", _gAkropolisHelicopterLandingPadView2SpriteSources, peDecodeArr_gAkropolisHelicopterLandingPadView2SpriteSources);
static SpriteBatch _gAkropolisHelicopterLandingPadView2SpriteBatches[3];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_helicopter_landing_pad/_gAkropolisHelicopterLandingPadView2SpriteBatches", _gAkropolisHelicopterLandingPadView2SpriteBatches);
static SpriteBatch _gAkropolisHelicopterLandingPadView3SpriteBatches[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_helicopter_landing_pad/_gAkropolisHelicopterLandingPadView3SpriteBatches", _gAkropolisHelicopterLandingPadView3SpriteBatches);
static SpriteDrawArea _gAkropolisHelicopterLandingPadView3DrawAreas[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_helicopter_landing_pad/_gAkropolisHelicopterLandingPadView3DrawAreas", _gAkropolisHelicopterLandingPadView3DrawAreas);
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
static SpriteSource _gAkropolisHelicopterLandingPadView4SpriteSources[5];
static void peDecodeArr_gAkropolisHelicopterLandingPadView4SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_helicopter_landing_pad/_gAkropolisHelicopterLandingPadView4SpriteSources", _gAkropolisHelicopterLandingPadView4SpriteSources, peDecodeArr_gAkropolisHelicopterLandingPadView4SpriteSources);
static SpriteBatch _gAkropolisHelicopterLandingPadView4SpriteBatches[3];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_helicopter_landing_pad/_gAkropolisHelicopterLandingPadView4SpriteBatches", _gAkropolisHelicopterLandingPadView4SpriteBatches);
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
static SpriteSource _gAkropolisHelicopterLandingPadView5SpriteSources[8];
static void peDecodeArr_gAkropolisHelicopterLandingPadView5SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_helicopter_landing_pad/_gAkropolisHelicopterLandingPadView5SpriteSources", _gAkropolisHelicopterLandingPadView5SpriteSources, peDecodeArr_gAkropolisHelicopterLandingPadView5SpriteSources);
static SpriteBatch _gAkropolisHelicopterLandingPadView5SpriteBatches[3];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_helicopter_landing_pad/_gAkropolisHelicopterLandingPadView5SpriteBatches", _gAkropolisHelicopterLandingPadView5SpriteBatches);
static SpriteDrawArea _gAkropolisHelicopterLandingPadView5DrawAreas[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_helicopter_landing_pad/_gAkropolisHelicopterLandingPadView5DrawAreas", _gAkropolisHelicopterLandingPadView5DrawAreas);
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
static SpriteSource _gAkropolisHelicopterLandingPadView6SpriteSources[10];
static void peDecodeArr_gAkropolisHelicopterLandingPadView6SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_helicopter_landing_pad/_gAkropolisHelicopterLandingPadView6SpriteSources", _gAkropolisHelicopterLandingPadView6SpriteSources, peDecodeArr_gAkropolisHelicopterLandingPadView6SpriteSources);
static SpriteBatch _gAkropolisHelicopterLandingPadView6SpriteBatches[3];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_helicopter_landing_pad/_gAkropolisHelicopterLandingPadView6SpriteBatches", _gAkropolisHelicopterLandingPadView6SpriteBatches);
static SpriteDrawArea _gAkropolisHelicopterLandingPadView6DrawAreas[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_helicopter_landing_pad/_gAkropolisHelicopterLandingPadView6DrawAreas", _gAkropolisHelicopterLandingPadView6DrawAreas);
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
static SpriteSource _gAkropolisHelicopterLandingPadView7SpriteSources[29];
static void peDecodeArr_gAkropolisHelicopterLandingPadView7SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_helicopter_landing_pad/_gAkropolisHelicopterLandingPadView7SpriteSources", _gAkropolisHelicopterLandingPadView7SpriteSources, peDecodeArr_gAkropolisHelicopterLandingPadView7SpriteSources);
static SpriteBatch _gAkropolisHelicopterLandingPadView7SpriteBatches[5];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_helicopter_landing_pad/_gAkropolisHelicopterLandingPadView7SpriteBatches", _gAkropolisHelicopterLandingPadView7SpriteBatches);
static SpriteDrawArea _gAkropolisHelicopterLandingPadView7DrawAreas[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_helicopter_landing_pad/_gAkropolisHelicopterLandingPadView7DrawAreas", _gAkropolisHelicopterLandingPadView7DrawAreas);
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
static SpriteSource _gAkropolisHelicopterLandingPadView8SpriteSources[10];
static void peDecodeArr_gAkropolisHelicopterLandingPadView8SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_helicopter_landing_pad/_gAkropolisHelicopterLandingPadView8SpriteSources", _gAkropolisHelicopterLandingPadView8SpriteSources, peDecodeArr_gAkropolisHelicopterLandingPadView8SpriteSources);
static SpriteBatch _gAkropolisHelicopterLandingPadView8SpriteBatches[3];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_helicopter_landing_pad/_gAkropolisHelicopterLandingPadView8SpriteBatches", _gAkropolisHelicopterLandingPadView8SpriteBatches);
static SpriteDrawArea _gAkropolisHelicopterLandingPadView8DrawAreas[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_helicopter_landing_pad/_gAkropolisHelicopterLandingPadView8DrawAreas", _gAkropolisHelicopterLandingPadView8DrawAreas);
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
static SpriteSource _gAkropolisHelicopterLandingPadView9SpriteSources[12];
static void peDecodeArr_gAkropolisHelicopterLandingPadView9SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_helicopter_landing_pad/_gAkropolisHelicopterLandingPadView9SpriteSources", _gAkropolisHelicopterLandingPadView9SpriteSources, peDecodeArr_gAkropolisHelicopterLandingPadView9SpriteSources);
static SpriteBatch _gAkropolisHelicopterLandingPadView9SpriteBatches[3];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_helicopter_landing_pad/_gAkropolisHelicopterLandingPadView9SpriteBatches", _gAkropolisHelicopterLandingPadView9SpriteBatches);
static SpriteDrawArea _gAkropolisHelicopterLandingPadView9DrawAreas[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_helicopter_landing_pad/_gAkropolisHelicopterLandingPadView9DrawAreas", _gAkropolisHelicopterLandingPadView9DrawAreas);
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
static SpriteSource _gAkropolisHelicopterLandingPadView10SpriteSources[27];
static void peDecodeArr_gAkropolisHelicopterLandingPadView10SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_helicopter_landing_pad/_gAkropolisHelicopterLandingPadView10SpriteSources", _gAkropolisHelicopterLandingPadView10SpriteSources, peDecodeArr_gAkropolisHelicopterLandingPadView10SpriteSources);
static SpriteBatch _gAkropolisHelicopterLandingPadView10SpriteBatches[5];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_helicopter_landing_pad/_gAkropolisHelicopterLandingPadView10SpriteBatches", _gAkropolisHelicopterLandingPadView10SpriteBatches);
static SpriteDrawArea _gAkropolisHelicopterLandingPadView10DrawAreas[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_helicopter_landing_pad/_gAkropolisHelicopterLandingPadView10DrawAreas", _gAkropolisHelicopterLandingPadView10DrawAreas);
static SpriteBatch _gAkropolisHelicopterLandingPadView11SpriteBatches[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_helicopter_landing_pad/_gAkropolisHelicopterLandingPadView11SpriteBatches", _gAkropolisHelicopterLandingPadView11SpriteBatches);
static SpriteBatch _gAkropolisHelicopterLandingPadView12SpriteBatches[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_helicopter_landing_pad/_gAkropolisHelicopterLandingPadView12SpriteBatches", _gAkropolisHelicopterLandingPadView12SpriteBatches);
static SpriteBatch _gAkropolisHelicopterLandingPadView13SpriteBatches[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_helicopter_landing_pad/_gAkropolisHelicopterLandingPadView13SpriteBatches", _gAkropolisHelicopterLandingPadView13SpriteBatches);
static SpriteBatch _gAkropolisHelicopterLandingPadView14SpriteBatches[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_helicopter_landing_pad/_gAkropolisHelicopterLandingPadView14SpriteBatches", _gAkropolisHelicopterLandingPadView14SpriteBatches);
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
static SpriteSource _gAkropolisHelicopterLandingPadViews15And27SpriteSources[1];
static void peDecodeArr_gAkropolisHelicopterLandingPadViews15And27SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_helicopter_landing_pad/_gAkropolisHelicopterLandingPadViews15And27SpriteSources", _gAkropolisHelicopterLandingPadViews15And27SpriteSources, peDecodeArr_gAkropolisHelicopterLandingPadViews15And27SpriteSources);
static SpriteBatch _gAkropolisHelicopterLandingPadViews15And27SpriteBatches[3];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_helicopter_landing_pad/_gAkropolisHelicopterLandingPadViews15And27SpriteBatches", _gAkropolisHelicopterLandingPadViews15And27SpriteBatches);
static SpriteDrawArea _gAkropolisHelicopterLandingPadViews15And27DrawAreas[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_helicopter_landing_pad/_gAkropolisHelicopterLandingPadViews15And27DrawAreas", _gAkropolisHelicopterLandingPadViews15And27DrawAreas);
static SpriteBatch _gAkropolisHelicopterLandingPadView16SpriteBatches[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_helicopter_landing_pad/_gAkropolisHelicopterLandingPadView16SpriteBatches", _gAkropolisHelicopterLandingPadView16SpriteBatches);
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
static SpriteSource _gAkropolisHelicopterLandingPadView17SpriteSources[3];
static void peDecodeArr_gAkropolisHelicopterLandingPadView17SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_helicopter_landing_pad/_gAkropolisHelicopterLandingPadView17SpriteSources", _gAkropolisHelicopterLandingPadView17SpriteSources, peDecodeArr_gAkropolisHelicopterLandingPadView17SpriteSources);
static SpriteBatch _gAkropolisHelicopterLandingPadView17SpriteBatches[3];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_helicopter_landing_pad/_gAkropolisHelicopterLandingPadView17SpriteBatches", _gAkropolisHelicopterLandingPadView17SpriteBatches);
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
static SpriteSource _gAkropolisHelicopterLandingPadView18SpriteSources[4];
static void peDecodeArr_gAkropolisHelicopterLandingPadView18SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_helicopter_landing_pad/_gAkropolisHelicopterLandingPadView18SpriteSources", _gAkropolisHelicopterLandingPadView18SpriteSources, peDecodeArr_gAkropolisHelicopterLandingPadView18SpriteSources);
static SpriteBatch _gAkropolisHelicopterLandingPadView18SpriteBatches[3];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_helicopter_landing_pad/_gAkropolisHelicopterLandingPadView18SpriteBatches", _gAkropolisHelicopterLandingPadView18SpriteBatches);
static SpriteBatch _gAkropolisHelicopterLandingPadView19SpriteBatches[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_helicopter_landing_pad/_gAkropolisHelicopterLandingPadView19SpriteBatches", _gAkropolisHelicopterLandingPadView19SpriteBatches);
static SpriteBatch _gAkropolisHelicopterLandingPadView20SpriteBatches[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_helicopter_landing_pad/_gAkropolisHelicopterLandingPadView20SpriteBatches", _gAkropolisHelicopterLandingPadView20SpriteBatches);
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
static SpriteSource _gAkropolisHelicopterLandingPadView21SpriteSources[6];
static void peDecodeArr_gAkropolisHelicopterLandingPadView21SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_helicopter_landing_pad/_gAkropolisHelicopterLandingPadView21SpriteSources", _gAkropolisHelicopterLandingPadView21SpriteSources, peDecodeArr_gAkropolisHelicopterLandingPadView21SpriteSources);
static SpriteBatch _gAkropolisHelicopterLandingPadView21SpriteBatches[3];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_helicopter_landing_pad/_gAkropolisHelicopterLandingPadView21SpriteBatches", _gAkropolisHelicopterLandingPadView21SpriteBatches);
static SpriteBatch _gAkropolisHelicopterLandingPadView22SpriteBatches[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_helicopter_landing_pad/_gAkropolisHelicopterLandingPadView22SpriteBatches", _gAkropolisHelicopterLandingPadView22SpriteBatches);
static SpriteBatch _gAkropolisHelicopterLandingPadView23SpriteBatches[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_helicopter_landing_pad/_gAkropolisHelicopterLandingPadView23SpriteBatches", _gAkropolisHelicopterLandingPadView23SpriteBatches);
static SpriteBatch _gAkropolisHelicopterLandingPadView24SpriteBatches[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_helicopter_landing_pad/_gAkropolisHelicopterLandingPadView24SpriteBatches", _gAkropolisHelicopterLandingPadView24SpriteBatches);
static SpriteBatch _gAkropolisHelicopterLandingPadView25SpriteBatches[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_helicopter_landing_pad/_gAkropolisHelicopterLandingPadView25SpriteBatches", _gAkropolisHelicopterLandingPadView25SpriteBatches);
static SpriteBatch _gAkropolisHelicopterLandingPadView26SpriteBatches[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_helicopter_landing_pad/_gAkropolisHelicopterLandingPadView26SpriteBatches", _gAkropolisHelicopterLandingPadView26SpriteBatches);
static SpriteDrawArea _gAkropolisHelicopterLandingPadUnselectedDrawAreas[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_helicopter_landing_pad/_gAkropolisHelicopterLandingPadUnselectedDrawAreas", _gAkropolisHelicopterLandingPadUnselectedDrawAreas);
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
SpriteView gAkropolisHelicopterLandingPadSpriteViews[27];
static void peDecodeArr_gAkropolisHelicopterLandingPadSpriteViews(void* base, const unsigned char* src, size_t n)
{
    SpriteView* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteView(&dst[k], src + k * 12);
    dst[0].sources.elements = _gAkropolisHelicopterLandingPadView1SpriteBatches;
    dst[0].batches = _gAkropolisHelicopterLandingPadView1SpriteBatches;
    dst[1].sources.elements = _gAkropolisHelicopterLandingPadView2SpriteSources;
    dst[1].batches = _gAkropolisHelicopterLandingPadView2SpriteBatches;
    dst[2].sources.elements = _gAkropolisHelicopterLandingPadView3SpriteBatches;
    dst[2].batches = _gAkropolisHelicopterLandingPadView3SpriteBatches;
    dst[2].drawAreas = _gAkropolisHelicopterLandingPadView3DrawAreas;
    dst[3].sources.elements = _gAkropolisHelicopterLandingPadView4SpriteSources;
    dst[3].batches = _gAkropolisHelicopterLandingPadView4SpriteBatches;
    dst[4].sources.elements = _gAkropolisHelicopterLandingPadView5SpriteSources;
    dst[4].batches = _gAkropolisHelicopterLandingPadView5SpriteBatches;
    dst[4].drawAreas = _gAkropolisHelicopterLandingPadView5DrawAreas;
    dst[5].sources.elements = _gAkropolisHelicopterLandingPadView6SpriteSources;
    dst[5].batches = _gAkropolisHelicopterLandingPadView6SpriteBatches;
    dst[5].drawAreas = _gAkropolisHelicopterLandingPadView6DrawAreas;
    dst[6].sources.elements = _gAkropolisHelicopterLandingPadView7SpriteSources;
    dst[6].batches = _gAkropolisHelicopterLandingPadView7SpriteBatches;
    dst[6].drawAreas = _gAkropolisHelicopterLandingPadView7DrawAreas;
    dst[7].sources.elements = _gAkropolisHelicopterLandingPadView8SpriteSources;
    dst[7].batches = _gAkropolisHelicopterLandingPadView8SpriteBatches;
    dst[7].drawAreas = _gAkropolisHelicopterLandingPadView8DrawAreas;
    dst[8].sources.elements = _gAkropolisHelicopterLandingPadView9SpriteSources;
    dst[8].batches = _gAkropolisHelicopterLandingPadView9SpriteBatches;
    dst[8].drawAreas = _gAkropolisHelicopterLandingPadView9DrawAreas;
    dst[9].sources.elements = _gAkropolisHelicopterLandingPadView10SpriteSources;
    dst[9].batches = _gAkropolisHelicopterLandingPadView10SpriteBatches;
    dst[9].drawAreas = _gAkropolisHelicopterLandingPadView10DrawAreas;
    dst[10].sources.elements = _gAkropolisHelicopterLandingPadView11SpriteBatches;
    dst[10].batches = _gAkropolisHelicopterLandingPadView11SpriteBatches;
    dst[11].sources.elements = _gAkropolisHelicopterLandingPadView12SpriteBatches;
    dst[11].batches = _gAkropolisHelicopterLandingPadView12SpriteBatches;
    dst[12].sources.elements = _gAkropolisHelicopterLandingPadView13SpriteBatches;
    dst[12].batches = _gAkropolisHelicopterLandingPadView13SpriteBatches;
    dst[13].sources.elements = _gAkropolisHelicopterLandingPadView14SpriteBatches;
    dst[13].batches = _gAkropolisHelicopterLandingPadView14SpriteBatches;
    dst[14].sources.elements = _gAkropolisHelicopterLandingPadViews15And27SpriteSources;
    dst[14].batches = _gAkropolisHelicopterLandingPadViews15And27SpriteBatches;
    dst[14].drawAreas = _gAkropolisHelicopterLandingPadViews15And27DrawAreas;
    dst[15].sources.elements = _gAkropolisHelicopterLandingPadView16SpriteBatches;
    dst[15].batches = _gAkropolisHelicopterLandingPadView16SpriteBatches;
    dst[16].sources.elements = _gAkropolisHelicopterLandingPadView17SpriteSources;
    dst[16].batches = _gAkropolisHelicopterLandingPadView17SpriteBatches;
    dst[17].sources.elements = _gAkropolisHelicopterLandingPadView18SpriteSources;
    dst[17].batches = _gAkropolisHelicopterLandingPadView18SpriteBatches;
    dst[18].sources.elements = _gAkropolisHelicopterLandingPadView19SpriteBatches;
    dst[18].batches = _gAkropolisHelicopterLandingPadView19SpriteBatches;
    dst[19].sources.elements = _gAkropolisHelicopterLandingPadView20SpriteBatches;
    dst[19].batches = _gAkropolisHelicopterLandingPadView20SpriteBatches;
    dst[20].sources.elements = _gAkropolisHelicopterLandingPadView21SpriteSources;
    dst[20].batches = _gAkropolisHelicopterLandingPadView21SpriteBatches;
    dst[21].sources.elements = _gAkropolisHelicopterLandingPadView22SpriteBatches;
    dst[21].batches = _gAkropolisHelicopterLandingPadView22SpriteBatches;
    dst[22].sources.elements = _gAkropolisHelicopterLandingPadView23SpriteBatches;
    dst[22].batches = _gAkropolisHelicopterLandingPadView23SpriteBatches;
    dst[23].sources.elements = _gAkropolisHelicopterLandingPadView24SpriteBatches;
    dst[23].batches = _gAkropolisHelicopterLandingPadView24SpriteBatches;
    dst[24].sources.elements = _gAkropolisHelicopterLandingPadView25SpriteBatches;
    dst[24].batches = _gAkropolisHelicopterLandingPadView25SpriteBatches;
    dst[25].sources.elements = _gAkropolisHelicopterLandingPadView26SpriteBatches;
    dst[25].batches = _gAkropolisHelicopterLandingPadView26SpriteBatches;
    dst[26].sources.elements = _gAkropolisHelicopterLandingPadViews15And27SpriteSources;
    dst[26].batches = _gAkropolisHelicopterLandingPadViews15And27SpriteBatches;
    dst[26].drawAreas = _gAkropolisHelicopterLandingPadViews15And27DrawAreas;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_helicopter_landing_pad/gAkropolisHelicopterLandingPadSpriteViews", gAkropolisHelicopterLandingPadSpriteViews, peDecodeArr_gAkropolisHelicopterLandingPadSpriteViews);
