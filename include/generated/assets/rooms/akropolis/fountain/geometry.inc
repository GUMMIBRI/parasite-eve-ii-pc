/* rooms/akropolis/fountain/package: written from its room instance by tools/buildsteps/gen_room_inc.py. */

#include "types.h"
#include "gameplay/collision.h"

static SVECTOR _gAkropolisFountainCollisionGridNormals[32];
#include "port/asset_bind.h"
PE_ASSET_BIND("akropolis_fountain_collision_0204C_normals", _gAkropolisFountainCollisionGridNormals);
static SVECTOR _gAkropolisFountainCollisionGridVerts[181];
#include "port/asset_bind.h"
PE_ASSET_BIND("akropolis_fountain_collision_0204C_verts", _gAkropolisFountainCollisionGridVerts);
static WorldCollisionGridFace _gAkropolisFountainCollisionGridFaces[66];
#include "port/asset_bind.h"
PE_ASSET_BIND("akropolis_fountain_collision_0204C_faces", _gAkropolisFountainCollisionGridFaces);
static s16 _gAkropolisFountainCollisionGridCells[326];
#include "port/asset_bind.h"
PE_ASSET_BIND("akropolis_fountain_collision_0204C_cells", _gAkropolisFountainCollisionGridCells);
static s16* _gAkropolisFountainCollisionGridTable[16];
#include "port/asset_bind.h"
PE_ASSET_BIND_AUX("akropolis_fountain_collision_0204C_table", _gAkropolisFountainCollisionGridTable, _gAkropolisFountainCollisionGridCells);
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
static WorldCollisionGrid _gAkropolisFountainCollisionGrid;
static void peDecodeArr_gAkropolisFountainCollisionGrid(void* base, const unsigned char* src, size_t n)
{
    WorldCollisionGrid* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_WorldCollisionGrid(&dst[k], src + k * 36);
    dst[0].normals = _gAkropolisFountainCollisionGridNormals;
    dst[0].vertices = _gAkropolisFountainCollisionGridVerts;
    dst[0].faces = _gAkropolisFountainCollisionGridFaces;
    dst[0].cellFaceIds = _gAkropolisFountainCollisionGridTable;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_fountain/_gAkropolisFountainCollisionGrid", _gAkropolisFountainCollisionGrid, peDecodeArr_gAkropolisFountainCollisionGrid);
