/* rooms/akropolis/fire_escape/package: written from its room instance by tools/buildsteps/gen_room_inc.py. */

#include "types.h"
#include "gameplay/collision.h"

SVECTOR gAkropolisFireEscapeCollisionGridNormals[10];
#include "port/asset_bind.h"
PE_ASSET_BIND("akropolis_fire_escape_collision_04CE8_normals", gAkropolisFireEscapeCollisionGridNormals);
SVECTOR gAkropolisFireEscapeCollisionGridVerts[55];
#include "port/asset_bind.h"
PE_ASSET_BIND("akropolis_fire_escape_collision_04CE8_verts", gAkropolisFireEscapeCollisionGridVerts);
WorldCollisionGridFace gAkropolisFireEscapeCollisionGridFaces[23];
#include "port/asset_bind.h"
PE_ASSET_BIND("akropolis_fire_escape_collision_04CE8_faces", gAkropolisFireEscapeCollisionGridFaces);
static s16 _gAkropolisFireEscapeCollisionGridCells[122];
#include "port/asset_bind.h"
PE_ASSET_BIND("akropolis_fire_escape_collision_04CE8_cells", _gAkropolisFireEscapeCollisionGridCells);
static s16* _gAkropolisFireEscapeCollisionGridTable[9];
#include "port/asset_bind.h"
PE_ASSET_BIND_AUX("akropolis_fire_escape_collision_04CE8_table", _gAkropolisFireEscapeCollisionGridTable, _gAkropolisFireEscapeCollisionGridCells);
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
static WorldCollisionGrid _gAkropolisFireEscapeCollisionGrid;
static void peDecodeArr_gAkropolisFireEscapeCollisionGrid(void* base, const unsigned char* src, size_t n)
{
    WorldCollisionGrid* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_WorldCollisionGrid(&dst[k], src + k * 36);
    dst[0].normals = gAkropolisFireEscapeCollisionGridNormals;
    dst[0].vertices = gAkropolisFireEscapeCollisionGridVerts;
    dst[0].faces = gAkropolisFireEscapeCollisionGridFaces;
    dst[0].cellFaceIds = _gAkropolisFireEscapeCollisionGridTable;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_fire_escape/_gAkropolisFireEscapeCollisionGrid", _gAkropolisFireEscapeCollisionGrid, peDecodeArr_gAkropolisFireEscapeCollisionGrid);
