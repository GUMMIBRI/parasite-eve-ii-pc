/* rooms/akropolis/security_room/package: written from its room instance by tools/buildsteps/gen_room_inc.py. */

#include "types.h"
#include "gameplay/sprites.h"

static SpriteBatch _gAkropolisSecurityRoomView1SpriteBatches[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_security_room/_gAkropolisSecurityRoomView1SpriteBatches", _gAkropolisSecurityRoomView1SpriteBatches);
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
static SpriteSource _gAkropolisSecurityRoomView2SpriteSources[18];
static void peDecodeArr_gAkropolisSecurityRoomView2SpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_security_room/_gAkropolisSecurityRoomView2SpriteSources", _gAkropolisSecurityRoomView2SpriteSources, peDecodeArr_gAkropolisSecurityRoomView2SpriteSources);
static SpriteBatch _gAkropolisSecurityRoomView2SpriteBatches[3];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_security_room/_gAkropolisSecurityRoomView2SpriteBatches", _gAkropolisSecurityRoomView2SpriteBatches);
static SpriteBatch _gAkropolisSecurityRoomView3SpriteBatches[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_security_room/_gAkropolisSecurityRoomView3SpriteBatches", _gAkropolisSecurityRoomView3SpriteBatches);
static SpriteBatch _gAkropolisSecurityRoomView4SpriteBatches[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_security_room/_gAkropolisSecurityRoomView4SpriteBatches", _gAkropolisSecurityRoomView4SpriteBatches);
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
static SpriteSource _gAkropolisSecurityRoomMonitorFrameSpriteSources[10];
static void peDecodeArr_gAkropolisSecurityRoomMonitorFrameSpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_security_room/_gAkropolisSecurityRoomMonitorFrameSpriteSources", _gAkropolisSecurityRoomMonitorFrameSpriteSources, peDecodeArr_gAkropolisSecurityRoomMonitorFrameSpriteSources);
static SpriteBatch _gAkropolisSecurityRoomMonitorFrameSpriteBatches[3];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_security_room/_gAkropolisSecurityRoomMonitorFrameSpriteBatches", _gAkropolisSecurityRoomMonitorFrameSpriteBatches);
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
static SpriteSource _gAkropolisSecurityRoomReleasedLockSpriteSources[2];
static void peDecodeArr_gAkropolisSecurityRoomReleasedLockSpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_security_room/_gAkropolisSecurityRoomReleasedLockSpriteSources", _gAkropolisSecurityRoomReleasedLockSpriteSources, peDecodeArr_gAkropolisSecurityRoomReleasedLockSpriteSources);
static SpriteBatch _gAkropolisSecurityRoomReleasedLockSpriteBatches[4];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_security_room/_gAkropolisSecurityRoomReleasedLockSpriteBatches", _gAkropolisSecurityRoomReleasedLockSpriteBatches);
static SpriteBatch _gAkropolisSecurityRoomView7SpriteBatches[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_security_room/_gAkropolisSecurityRoomView7SpriteBatches", _gAkropolisSecurityRoomView7SpriteBatches);
static SpriteBatch _gAkropolisSecurityRoomUnusedEmptySpriteBatchLists[8][2] = {
    { { .firstSprite = 0, .spriteCount = 0, .hidden = 0, .skipCachedPackets = 0, .field_6 = { 0, 0 } }, { .firstSprite = 65535, .spriteCount = 0, .hidden = 0, .skipCachedPackets = 0, .field_6 = { 0, 0 } } },
    { { .firstSprite = 0, .spriteCount = 0, .hidden = 0, .skipCachedPackets = 0, .field_6 = { 0, 0 } }, { .firstSprite = 65535, .spriteCount = 0, .hidden = 0, .skipCachedPackets = 0, .field_6 = { 0, 0 } } },
    { { .firstSprite = 0, .spriteCount = 0, .hidden = 0, .skipCachedPackets = 0, .field_6 = { 0, 0 } }, { .firstSprite = 65535, .spriteCount = 0, .hidden = 0, .skipCachedPackets = 0, .field_6 = { 0, 0 } } },
    { { .firstSprite = 0, .spriteCount = 0, .hidden = 0, .skipCachedPackets = 0, .field_6 = { 0, 0 } }, { .firstSprite = 65535, .spriteCount = 0, .hidden = 0, .skipCachedPackets = 0, .field_6 = { 0, 0 } } },
    { { .firstSprite = 0, .spriteCount = 0, .hidden = 0, .skipCachedPackets = 0, .field_6 = { 0, 0 } }, { .firstSprite = 65535, .spriteCount = 0, .hidden = 0, .skipCachedPackets = 0, .field_6 = { 0, 0 } } },
    { { .firstSprite = 0, .spriteCount = 0, .hidden = 0, .skipCachedPackets = 0, .field_6 = { 0, 0 } }, { .firstSprite = 65535, .spriteCount = 0, .hidden = 0, .skipCachedPackets = 0, .field_6 = { 0, 0 } } },
    { { .firstSprite = 0, .spriteCount = 0, .hidden = 0, .skipCachedPackets = 0, .field_6 = { 0, 0 } }, { .firstSprite = 65535, .spriteCount = 0, .hidden = 0, .skipCachedPackets = 0, .field_6 = { 0, 0 } } },
    { { .firstSprite = 0, .spriteCount = 0, .hidden = 0, .skipCachedPackets = 0, .field_6 = { 0, 0 } }, { .firstSprite = 65535, .spriteCount = 0, .hidden = 0, .skipCachedPackets = 0, .field_6 = { 0, 0 } } },
};
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
static SpriteSource _gAkropolisSecurityRoomRightUnlockSpriteSources[84];
static void peDecodeArr_gAkropolisSecurityRoomRightUnlockSpriteSources(void* base, const unsigned char* src, size_t n)
{
    SpriteSource* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteSource(&dst[k], src + k * 20);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_security_room/_gAkropolisSecurityRoomRightUnlockSpriteSources", _gAkropolisSecurityRoomRightUnlockSpriteSources, peDecodeArr_gAkropolisSecurityRoomRightUnlockSpriteSources);
static SpriteBatch _gAkropolisSecurityRoomRightUnlockSpriteBatches[15];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_security_room/_gAkropolisSecurityRoomRightUnlockSpriteBatches", _gAkropolisSecurityRoomRightUnlockSpriteBatches);
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
SpriteView gAkropolisSecurityRoomSpriteViews[16];
static void peDecodeArr_gAkropolisSecurityRoomSpriteViews(void* base, const unsigned char* src, size_t n)
{
    SpriteView* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteView(&dst[k], src + k * 12);
    dst[0].sources.elements = _gAkropolisSecurityRoomView1SpriteBatches;
    dst[0].batches = _gAkropolisSecurityRoomView1SpriteBatches;
    dst[1].sources.elements = _gAkropolisSecurityRoomView2SpriteSources;
    dst[1].batches = _gAkropolisSecurityRoomView2SpriteBatches;
    dst[2].sources.elements = _gAkropolisSecurityRoomView3SpriteBatches;
    dst[2].batches = _gAkropolisSecurityRoomView3SpriteBatches;
    dst[3].sources.elements = _gAkropolisSecurityRoomView4SpriteBatches;
    dst[3].batches = _gAkropolisSecurityRoomView4SpriteBatches;
    dst[4].sources.elements = _gAkropolisSecurityRoomMonitorFrameSpriteSources;
    dst[4].batches = _gAkropolisSecurityRoomMonitorFrameSpriteBatches;
    dst[5].sources.elements = _gAkropolisSecurityRoomReleasedLockSpriteSources;
    dst[5].batches = _gAkropolisSecurityRoomReleasedLockSpriteBatches;
    dst[6].sources.elements = _gAkropolisSecurityRoomView7SpriteBatches;
    dst[6].batches = _gAkropolisSecurityRoomView7SpriteBatches;
    dst[7].sources.elements = _gAkropolisSecurityRoomMonitorFrameSpriteSources;
    dst[7].batches = _gAkropolisSecurityRoomMonitorFrameSpriteBatches;
    dst[8].sources.elements = _gAkropolisSecurityRoomMonitorFrameSpriteSources;
    dst[8].batches = _gAkropolisSecurityRoomMonitorFrameSpriteBatches;
    dst[9].sources.elements = _gAkropolisSecurityRoomMonitorFrameSpriteSources;
    dst[9].batches = _gAkropolisSecurityRoomMonitorFrameSpriteBatches;
    dst[10].sources.elements = _gAkropolisSecurityRoomMonitorFrameSpriteSources;
    dst[10].batches = _gAkropolisSecurityRoomMonitorFrameSpriteBatches;
    dst[11].sources.elements = _gAkropolisSecurityRoomMonitorFrameSpriteSources;
    dst[11].batches = _gAkropolisSecurityRoomMonitorFrameSpriteBatches;
    dst[12].sources.elements = _gAkropolisSecurityRoomMonitorFrameSpriteSources;
    dst[12].batches = _gAkropolisSecurityRoomMonitorFrameSpriteBatches;
    dst[13].sources.elements = _gAkropolisSecurityRoomView4SpriteBatches;
    dst[13].batches = _gAkropolisSecurityRoomView4SpriteBatches;
    dst[14].sources.elements = _gAkropolisSecurityRoomView4SpriteBatches;
    dst[14].batches = _gAkropolisSecurityRoomView4SpriteBatches;
    dst[15].sources.elements = _gAkropolisSecurityRoomRightUnlockSpriteSources;
    dst[15].batches = _gAkropolisSecurityRoomRightUnlockSpriteBatches;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_security_room/gAkropolisSecurityRoomSpriteViews", gAkropolisSecurityRoomSpriteViews, peDecodeArr_gAkropolisSecurityRoomSpriteViews);
