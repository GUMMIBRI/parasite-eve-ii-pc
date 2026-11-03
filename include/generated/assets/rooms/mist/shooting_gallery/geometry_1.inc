/* rooms/mist/shooting_gallery/package: written from its room instance by tools/buildsteps/gen_room_inc.py. */

#include "types.h"
#include "gameplay/collision.h"

static SVECTOR _gMistShootingGalleryStoryBarrierCollisionTemplateNormals[3];
#include "port/asset_bind.h"
PE_ASSET_BIND("mist_shooting_gallery_collision_07BD8_normals", _gMistShootingGalleryStoryBarrierCollisionTemplateNormals);
static SVECTOR _gMistShootingGalleryStoryBarrierCollisionTemplateVerts[8];
#include "port/asset_bind.h"
PE_ASSET_BIND("mist_shooting_gallery_collision_07BD8_verts", _gMistShootingGalleryStoryBarrierCollisionTemplateVerts);
static WorldCollisionGridFace _gMistShootingGalleryStoryBarrierCollisionTemplateFaces[3];
#include "port/asset_bind.h"
PE_ASSET_BIND("mist_shooting_gallery_collision_07BD8_faces", _gMistShootingGalleryStoryBarrierCollisionTemplateFaces);
static s16 _gMistShootingGalleryStoryBarrierCollisionTemplateCells[4];
#include "port/asset_bind.h"
PE_ASSET_BIND("mist_shooting_gallery_collision_07BD8_cells", _gMistShootingGalleryStoryBarrierCollisionTemplateCells);
static s16* _gMistShootingGalleryStoryBarrierCollisionTemplateTable[1];
#include "port/asset_bind.h"
PE_ASSET_BIND_AUX("mist_shooting_gallery_collision_07BD8_table", _gMistShootingGalleryStoryBarrierCollisionTemplateTable, _gMistShootingGalleryStoryBarrierCollisionTemplateCells);
#ifndef PE_DECODE_WorldCollisionGrid
#define PE_DECODE_WorldCollisionGrid
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
static void peDecode_WorldCollisionGrid(WorldCollisionGrid* dst, const unsigned char* src)
{
    /* viewCoord: pointer, set by the array's fixups */
    /* normals: pointer, set by the array's fixups */
    /* vertices: pointer, set by the array's fixups */
    /* faces: pointer, set by the array's fixups */
    /* cellFaceIds: pointer, set by the array's fixups */
    { int32_t v; memcpy(&v, src + 20, 4); dst->xBias = v; }
    { int32_t v; memcpy(&v, src + 24, 4); dst->zBias = v; }
    { uint16_t v; memcpy(&v, src + 28, 2); dst->cellCountX = v; }
    { uint16_t v; memcpy(&v, src + 30, 2); dst->cellCountZ = v; }
    { uint16_t v; memcpy(&v, src + 32, 2); dst->cellSize = v; }
    { uint16_t v; memcpy(&v, src + 34, 2); dst->faceCount = v; }
}

#endif
static WorldCollisionGrid _gMistShootingGalleryStoryBarrierCollisionTemplate;
static void peDecodeArr_gMistShootingGalleryStoryBarrierCollisionTemplate(void* base, const unsigned char* src, size_t n)
{
    WorldCollisionGrid* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_WorldCollisionGrid(&dst[k], src + k * 36);
    dst[0].normals = _gMistShootingGalleryStoryBarrierCollisionTemplateNormals;
    dst[0].vertices = _gMistShootingGalleryStoryBarrierCollisionTemplateVerts;
    dst[0].faces = _gMistShootingGalleryStoryBarrierCollisionTemplateFaces;
    dst[0].cellFaceIds = _gMistShootingGalleryStoryBarrierCollisionTemplateTable;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_shooting_gallery/_gMistShootingGalleryStoryBarrierCollisionTemplate", _gMistShootingGalleryStoryBarrierCollisionTemplate, peDecodeArr_gMistShootingGalleryStoryBarrierCollisionTemplate);
static SVECTOR _gMistShootingGalleryTrainingBarrierCollisionTemplateNormals[1];
#include "port/asset_bind.h"
PE_ASSET_BIND("mist_shooting_gallery_collision_07C38_normals", _gMistShootingGalleryTrainingBarrierCollisionTemplateNormals);
static SVECTOR _gMistShootingGalleryTrainingBarrierCollisionTemplateVerts[4];
#include "port/asset_bind.h"
PE_ASSET_BIND("mist_shooting_gallery_collision_07C38_verts", _gMistShootingGalleryTrainingBarrierCollisionTemplateVerts);
static WorldCollisionGridFace _gMistShootingGalleryTrainingBarrierCollisionTemplateFaces[1];
#include "port/asset_bind.h"
PE_ASSET_BIND("mist_shooting_gallery_collision_07C38_faces", _gMistShootingGalleryTrainingBarrierCollisionTemplateFaces);
static s16 _gMistShootingGalleryTrainingBarrierCollisionTemplateCells[2];
#include "port/asset_bind.h"
PE_ASSET_BIND("mist_shooting_gallery_collision_07C38_cells", _gMistShootingGalleryTrainingBarrierCollisionTemplateCells);
static s16* _gMistShootingGalleryTrainingBarrierCollisionTemplateTable[1];
#include "port/asset_bind.h"
PE_ASSET_BIND_AUX("mist_shooting_gallery_collision_07C38_table", _gMistShootingGalleryTrainingBarrierCollisionTemplateTable, _gMistShootingGalleryTrainingBarrierCollisionTemplateCells);
#ifndef PE_DECODE_WorldCollisionGrid
#define PE_DECODE_WorldCollisionGrid
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
static void peDecode_WorldCollisionGrid(WorldCollisionGrid* dst, const unsigned char* src)
{
    /* viewCoord: pointer, set by the array's fixups */
    /* normals: pointer, set by the array's fixups */
    /* vertices: pointer, set by the array's fixups */
    /* faces: pointer, set by the array's fixups */
    /* cellFaceIds: pointer, set by the array's fixups */
    { int32_t v; memcpy(&v, src + 20, 4); dst->xBias = v; }
    { int32_t v; memcpy(&v, src + 24, 4); dst->zBias = v; }
    { uint16_t v; memcpy(&v, src + 28, 2); dst->cellCountX = v; }
    { uint16_t v; memcpy(&v, src + 30, 2); dst->cellCountZ = v; }
    { uint16_t v; memcpy(&v, src + 32, 2); dst->cellSize = v; }
    { uint16_t v; memcpy(&v, src + 34, 2); dst->faceCount = v; }
}

#endif
static WorldCollisionGrid _gMistShootingGalleryTrainingBarrierCollisionTemplate;
static void peDecodeArr_gMistShootingGalleryTrainingBarrierCollisionTemplate(void* base, const unsigned char* src, size_t n)
{
    WorldCollisionGrid* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_WorldCollisionGrid(&dst[k], src + k * 36);
    dst[0].normals = _gMistShootingGalleryTrainingBarrierCollisionTemplateNormals;
    dst[0].vertices = _gMistShootingGalleryTrainingBarrierCollisionTemplateVerts;
    dst[0].faces = _gMistShootingGalleryTrainingBarrierCollisionTemplateFaces;
    dst[0].cellFaceIds = _gMistShootingGalleryTrainingBarrierCollisionTemplateTable;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_shooting_gallery/_gMistShootingGalleryTrainingBarrierCollisionTemplate", _gMistShootingGalleryTrainingBarrierCollisionTemplate, peDecodeArr_gMistShootingGalleryTrainingBarrierCollisionTemplate);
