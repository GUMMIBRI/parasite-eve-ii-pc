/* rooms/mist/shooting_gallery/package: written from its room instance by tools/buildsteps/gen_room_inc.py. */

#include "types.h"
#include "gameplay/collision.h"

static SVECTOR _gMistShootingGalleryCollisionGridNormals[22];
#include "port/asset_bind.h"
PE_ASSET_BIND("mist_shooting_gallery_collision_0C3A8_normals", _gMistShootingGalleryCollisionGridNormals);
static SVECTOR _gMistShootingGalleryCollisionGridVerts[136];
#include "port/asset_bind.h"
PE_ASSET_BIND("mist_shooting_gallery_collision_0C3A8_verts", _gMistShootingGalleryCollisionGridVerts);
static WorldCollisionGridFace _gMistShootingGalleryCollisionGridFaces[57];
#include "port/asset_bind.h"
PE_ASSET_BIND("mist_shooting_gallery_collision_0C3A8_faces", _gMistShootingGalleryCollisionGridFaces);
static s16 _gMistShootingGalleryCollisionGridCells[474];
#include "port/asset_bind.h"
PE_ASSET_BIND("mist_shooting_gallery_collision_0C3A8_cells", _gMistShootingGalleryCollisionGridCells);
static s16* _gMistShootingGalleryCollisionGridTable[28];
#include "port/asset_bind.h"
PE_ASSET_BIND_AUX("mist_shooting_gallery_collision_0C3A8_table", _gMistShootingGalleryCollisionGridTable, _gMistShootingGalleryCollisionGridCells);
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
WorldCollisionGrid gMistShootingGalleryCollisionGrid;
static void peDecodeArr_gMistShootingGalleryCollisionGrid(void* base, const unsigned char* src, size_t n)
{
    WorldCollisionGrid* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_WorldCollisionGrid(&dst[k], src + k * 36);
    dst[0].normals = _gMistShootingGalleryCollisionGridNormals;
    dst[0].vertices = _gMistShootingGalleryCollisionGridVerts;
    dst[0].faces = _gMistShootingGalleryCollisionGridFaces;
    dst[0].cellFaceIds = _gMistShootingGalleryCollisionGridTable;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_shooting_gallery/gMistShootingGalleryCollisionGrid", gMistShootingGalleryCollisionGrid, peDecodeArr_gMistShootingGalleryCollisionGrid);
