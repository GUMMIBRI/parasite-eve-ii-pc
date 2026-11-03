/* rooms/mist/shooting_gallery/package: written from its room instance by tools/buildsteps/gen_room_inc.py. */

#ifndef PE_DECODE__MistShootingGalleryTargetScore
#define PE_DECODE__MistShootingGalleryTargetScore
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
static void peDecode__MistShootingGalleryTargetScore(_MistShootingGalleryTargetScore* dst, const unsigned char* src)
{
    { int32_t v; memcpy(&v, src + 0, 4); dst->points = v; }
    /* name: pointer, set by the array's fixups */
}

#endif
static _MistShootingGalleryTargetScore _gMistShootingGalleryTargetScores[13];
static void peDecodeArr_gMistShootingGalleryTargetScores(void* base, const unsigned char* src, size_t n)
{
    _MistShootingGalleryTargetScore* dst = base;
    for (size_t k = 0; k < n; k++) peDecode__MistShootingGalleryTargetScore(&dst[k], src + k * 8);
    dst[0].name = (void*)&_gMistShootingGalleryBacteriumTargetLabel;
    dst[1].name = (void*)&_gMistShootingGalleryBearTargetLabel;
    dst[2].name = (void*)&_gMistShootingGalleryMonkeyTargetLabel;
    dst[3].name = (void*)&_gMistShootingGalleryRatTargetLabel;
    dst[4].name = (void*)&_gMistShootingGalleryScorpionTargetLabel;
    dst[5].name = (void*)&_gMistShootingGallerySnakeTargetLabel;
    dst[6].name = (void*)&_gMistShootingGallerySpiderTargetLabel;
    dst[7].name = (void*)&_gMistShootingGalleryBeeTargetLabel;
    dst[8].name = (void*)&_gMistShootingGalleryCrowTargetLabel;
    dst[9].name = (void*)&_gMistShootingGalleryWomanTargetLabel;
    dst[10].name = (void*)&_gMistShootingGalleryYellowTargetLabel;
    dst[11].name = (void*)&_gMistShootingGalleryBrownTargetLabel;
    dst[12].name = (void*)&_gMistShootingGalleryRedTargetLabel;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_shooting_gallery/_gMistShootingGalleryTargetScores", _gMistShootingGalleryTargetScores, peDecodeArr_gMistShootingGalleryTargetScores);
