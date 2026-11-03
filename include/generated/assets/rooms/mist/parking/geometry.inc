/* rooms/mist/parking/package: written from its room instance by tools/buildsteps/gen_room_inc.py. */

#include "types.h"
#include "gameplay/collision.h"

static SVECTOR _gMistParkingCollisionGridNormals[13];
#include "port/asset_bind.h"
PE_ASSET_BIND("mist_parking_collision_14C44_normals", _gMistParkingCollisionGridNormals);
static SVECTOR _gMistParkingCollisionGridVerts[125];
#include "port/asset_bind.h"
PE_ASSET_BIND("mist_parking_collision_14C44_verts", _gMistParkingCollisionGridVerts);
static WorldCollisionGridFace _gMistParkingCollisionGridFaces[66];
#include "port/asset_bind.h"
PE_ASSET_BIND("mist_parking_collision_14C44_faces", _gMistParkingCollisionGridFaces);
static s16 _gMistParkingCollisionGridCells[434];
#include "port/asset_bind.h"
PE_ASSET_BIND("mist_parking_collision_14C44_cells", _gMistParkingCollisionGridCells);
static s16* _gMistParkingCollisionGridTable[28];
#include "port/asset_bind.h"
PE_ASSET_BIND_AUX("mist_parking_collision_14C44_table", _gMistParkingCollisionGridTable, _gMistParkingCollisionGridCells);
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
WorldCollisionGrid gMistParkingCollisionGrid;
static void peDecodeArr_gMistParkingCollisionGrid(void* base, const unsigned char* src, size_t n)
{
    WorldCollisionGrid* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_WorldCollisionGrid(&dst[k], src + k * 36);
    dst[0].normals = _gMistParkingCollisionGridNormals;
    dst[0].vertices = _gMistParkingCollisionGridVerts;
    dst[0].faces = _gMistParkingCollisionGridFaces;
    dst[0].cellFaceIds = _gMistParkingCollisionGridTable;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_parking/gMistParkingCollisionGrid", gMistParkingCollisionGrid, peDecodeArr_gMistParkingCollisionGrid);
