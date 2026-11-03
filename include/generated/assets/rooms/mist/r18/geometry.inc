/* rooms/mist/r18/package: written from its room instance by tools/buildsteps/gen_room_inc.py. */

#include "types.h"
#include "gameplay/collision.h"

static SVECTOR _gMistR18FloorCollisionGridNormals[1];
#include "port/asset_bind.h"
PE_ASSET_BIND("mist_r18_collision_09138_normals", _gMistR18FloorCollisionGridNormals);
static SVECTOR _gMistR18FloorCollisionGridVerts[4];
#include "port/asset_bind.h"
PE_ASSET_BIND("mist_r18_collision_09138_verts", _gMistR18FloorCollisionGridVerts);
static WorldCollisionGridFace _gMistR18FloorCollisionGridFaces[1];
#include "port/asset_bind.h"
PE_ASSET_BIND("mist_r18_collision_09138_faces", _gMistR18FloorCollisionGridFaces);
static s16 _gMistR18FloorCollisionGridCells[24];
#include "port/asset_bind.h"
PE_ASSET_BIND("mist_r18_collision_09138_cells", _gMistR18FloorCollisionGridCells);
static s16* _gMistR18FloorCollisionGridTable[12];
#include "port/asset_bind.h"
PE_ASSET_BIND_AUX("mist_r18_collision_09138_table", _gMistR18FloorCollisionGridTable, _gMistR18FloorCollisionGridCells);
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
static WorldCollisionGrid _gMistR18FloorCollisionGrid;
static void peDecodeArr_gMistR18FloorCollisionGrid(void* base, const unsigned char* src, size_t n)
{
    WorldCollisionGrid* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_WorldCollisionGrid(&dst[k], src + k * 36);
    dst[0].normals = _gMistR18FloorCollisionGridNormals;
    dst[0].vertices = _gMistR18FloorCollisionGridVerts;
    dst[0].faces = _gMistR18FloorCollisionGridFaces;
    dst[0].cellFaceIds = _gMistR18FloorCollisionGridTable;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_r18/_gMistR18FloorCollisionGrid", _gMistR18FloorCollisionGrid, peDecodeArr_gMistR18FloorCollisionGrid);
