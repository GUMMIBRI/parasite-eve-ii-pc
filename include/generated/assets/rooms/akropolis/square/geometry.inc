/* rooms/akropolis/square/package: written from its room instance by tools/buildsteps/gen_room_inc.py. */

#include "types.h"
#include "gameplay/collision.h"

static SVECTOR _gAkropolisSquareCollisionGridNormals[82];
#include "port/asset_bind.h"
PE_ASSET_BIND("akropolis_square_collision_07BDC_normals", _gAkropolisSquareCollisionGridNormals);
static SVECTOR _gAkropolisSquareCollisionGridVerts[262];
#include "port/asset_bind.h"
PE_ASSET_BIND("akropolis_square_collision_07BDC_verts", _gAkropolisSquareCollisionGridVerts);
static WorldCollisionGridFace _gAkropolisSquareCollisionGridFaces[115];
#include "port/asset_bind.h"
PE_ASSET_BIND("akropolis_square_collision_07BDC_faces", _gAkropolisSquareCollisionGridFaces);
static s16 _gAkropolisSquareCollisionGridCells[506];
#include "port/asset_bind.h"
PE_ASSET_BIND("akropolis_square_collision_07BDC_cells", _gAkropolisSquareCollisionGridCells);
static s16* _gAkropolisSquareCollisionGridTable[16];
#include "port/asset_bind.h"
PE_ASSET_BIND_AUX("akropolis_square_collision_07BDC_table", _gAkropolisSquareCollisionGridTable, _gAkropolisSquareCollisionGridCells);
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
static WorldCollisionGrid _gAkropolisSquareCollisionGrid;
static void peDecodeArr_gAkropolisSquareCollisionGrid(void* base, const unsigned char* src, size_t n)
{
    WorldCollisionGrid* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_WorldCollisionGrid(&dst[k], src + k * 36);
    dst[0].normals = _gAkropolisSquareCollisionGridNormals;
    dst[0].vertices = _gAkropolisSquareCollisionGridVerts;
    dst[0].faces = _gAkropolisSquareCollisionGridFaces;
    dst[0].cellFaceIds = _gAkropolisSquareCollisionGridTable;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_square/_gAkropolisSquareCollisionGrid", _gAkropolisSquareCollisionGrid, peDecodeArr_gAkropolisSquareCollisionGrid);
