/* rooms/mist/shooting_gallery/package: written from its room instance by tools/buildsteps/gen_room_inc.py. */

#ifndef PE_DECODE__MistShootingGallerySpawn
#define PE_DECODE__MistShootingGallerySpawn
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
static void peDecode__MistShootingGallerySpawn(_MistShootingGallerySpawn* dst, const unsigned char* src)
{
    { uint16_t v; memcpy(&v, src + 0, 2); dst->frame = v; }
    { int16_t v; memcpy(&v, src + 2, 2); dst->spawnArgLo = v; }
    { int16_t v; memcpy(&v, src + 4, 2); dst->spawnArgHi = v; }
    { int16_t v; memcpy(&v, src + 6, 2); dst->x = v; }
    { int16_t v; memcpy(&v, src + 8, 2); dst->y = v; }
    { int16_t v; memcpy(&v, src + 10, 2); dst->z = v; }
}

#endif
static _MistShootingGallerySpawn _gMistShootingGalleryCourse0WaveScript[60];
static void peDecodeArr_gMistShootingGalleryCourse0WaveScript(void* base, const unsigned char* src, size_t n)
{
    _MistShootingGallerySpawn* dst = base;
    for (size_t k = 0; k < n; k++) peDecode__MistShootingGallerySpawn(&dst[k], src + k * 12);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_shooting_gallery/_gMistShootingGalleryCourse0WaveScript", _gMistShootingGalleryCourse0WaveScript, peDecodeArr_gMistShootingGalleryCourse0WaveScript);
#ifndef PE_DECODE__MistShootingGallerySpawn
#define PE_DECODE__MistShootingGallerySpawn
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
static void peDecode__MistShootingGallerySpawn(_MistShootingGallerySpawn* dst, const unsigned char* src)
{
    { uint16_t v; memcpy(&v, src + 0, 2); dst->frame = v; }
    { int16_t v; memcpy(&v, src + 2, 2); dst->spawnArgLo = v; }
    { int16_t v; memcpy(&v, src + 4, 2); dst->spawnArgHi = v; }
    { int16_t v; memcpy(&v, src + 6, 2); dst->x = v; }
    { int16_t v; memcpy(&v, src + 8, 2); dst->y = v; }
    { int16_t v; memcpy(&v, src + 10, 2); dst->z = v; }
}

#endif
static _MistShootingGallerySpawn _gMistShootingGalleryCourse1WaveScript[66];
static void peDecodeArr_gMistShootingGalleryCourse1WaveScript(void* base, const unsigned char* src, size_t n)
{
    _MistShootingGallerySpawn* dst = base;
    for (size_t k = 0; k < n; k++) peDecode__MistShootingGallerySpawn(&dst[k], src + k * 12);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_shooting_gallery/_gMistShootingGalleryCourse1WaveScript", _gMistShootingGalleryCourse1WaveScript, peDecodeArr_gMistShootingGalleryCourse1WaveScript);
#ifndef PE_DECODE__MistShootingGallerySpawn
#define PE_DECODE__MistShootingGallerySpawn
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
static void peDecode__MistShootingGallerySpawn(_MistShootingGallerySpawn* dst, const unsigned char* src)
{
    { uint16_t v; memcpy(&v, src + 0, 2); dst->frame = v; }
    { int16_t v; memcpy(&v, src + 2, 2); dst->spawnArgLo = v; }
    { int16_t v; memcpy(&v, src + 4, 2); dst->spawnArgHi = v; }
    { int16_t v; memcpy(&v, src + 6, 2); dst->x = v; }
    { int16_t v; memcpy(&v, src + 8, 2); dst->y = v; }
    { int16_t v; memcpy(&v, src + 10, 2); dst->z = v; }
}

#endif
static _MistShootingGallerySpawn _gMistShootingGalleryCourse2WaveScript[75];
static void peDecodeArr_gMistShootingGalleryCourse2WaveScript(void* base, const unsigned char* src, size_t n)
{
    _MistShootingGallerySpawn* dst = base;
    for (size_t k = 0; k < n; k++) peDecode__MistShootingGallerySpawn(&dst[k], src + k * 12);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_shooting_gallery/_gMistShootingGalleryCourse2WaveScript", _gMistShootingGalleryCourse2WaveScript, peDecodeArr_gMistShootingGalleryCourse2WaveScript);
#ifndef PE_DECODE__MistShootingGallerySpawn
#define PE_DECODE__MistShootingGallerySpawn
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
static void peDecode__MistShootingGallerySpawn(_MistShootingGallerySpawn* dst, const unsigned char* src)
{
    { uint16_t v; memcpy(&v, src + 0, 2); dst->frame = v; }
    { int16_t v; memcpy(&v, src + 2, 2); dst->spawnArgLo = v; }
    { int16_t v; memcpy(&v, src + 4, 2); dst->spawnArgHi = v; }
    { int16_t v; memcpy(&v, src + 6, 2); dst->x = v; }
    { int16_t v; memcpy(&v, src + 8, 2); dst->y = v; }
    { int16_t v; memcpy(&v, src + 10, 2); dst->z = v; }
}

#endif
static _MistShootingGallerySpawn _gMistShootingGalleryCourse3WaveScript[106];
static void peDecodeArr_gMistShootingGalleryCourse3WaveScript(void* base, const unsigned char* src, size_t n)
{
    _MistShootingGallerySpawn* dst = base;
    for (size_t k = 0; k < n; k++) peDecode__MistShootingGallerySpawn(&dst[k], src + k * 12);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_shooting_gallery/_gMistShootingGalleryCourse3WaveScript", _gMistShootingGalleryCourse3WaveScript, peDecodeArr_gMistShootingGalleryCourse3WaveScript);
#ifndef PE_DECODE__MistShootingGallerySpawn
#define PE_DECODE__MistShootingGallerySpawn
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
static void peDecode__MistShootingGallerySpawn(_MistShootingGallerySpawn* dst, const unsigned char* src)
{
    { uint16_t v; memcpy(&v, src + 0, 2); dst->frame = v; }
    { int16_t v; memcpy(&v, src + 2, 2); dst->spawnArgLo = v; }
    { int16_t v; memcpy(&v, src + 4, 2); dst->spawnArgHi = v; }
    { int16_t v; memcpy(&v, src + 6, 2); dst->x = v; }
    { int16_t v; memcpy(&v, src + 8, 2); dst->y = v; }
    { int16_t v; memcpy(&v, src + 10, 2); dst->z = v; }
}

#endif
static _MistShootingGallerySpawn _gMistShootingGalleryCourse4WaveScript[80];
static void peDecodeArr_gMistShootingGalleryCourse4WaveScript(void* base, const unsigned char* src, size_t n)
{
    _MistShootingGallerySpawn* dst = base;
    for (size_t k = 0; k < n; k++) peDecode__MistShootingGallerySpawn(&dst[k], src + k * 12);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_shooting_gallery/_gMistShootingGalleryCourse4WaveScript", _gMistShootingGalleryCourse4WaveScript, peDecodeArr_gMistShootingGalleryCourse4WaveScript);
