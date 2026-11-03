/* rooms/akropolis/cafeteria/package: written from its room instance by tools/buildsteps/gen_room_inc.py. */

#include "types.h"
#include "gameplay/collision.h"

static SVECTOR _gAkropolisCafeteriaCollisionGridNormals[36];
#include "port/asset_bind.h"
PE_ASSET_BIND("akropolis_cafeteria_collision_0B1E8_normals", _gAkropolisCafeteriaCollisionGridNormals);
static SVECTOR _gAkropolisCafeteriaCollisionGridVerts[207];
#include "port/asset_bind.h"
PE_ASSET_BIND("akropolis_cafeteria_collision_0B1E8_verts", _gAkropolisCafeteriaCollisionGridVerts);
static WorldCollisionGridFace _gAkropolisCafeteriaCollisionGridFaces[120];
#include "port/asset_bind.h"
PE_ASSET_BIND("akropolis_cafeteria_collision_0B1E8_faces", _gAkropolisCafeteriaCollisionGridFaces);
static s16 _gAkropolisCafeteriaCollisionGridCells[480];
#include "port/asset_bind.h"
PE_ASSET_BIND("akropolis_cafeteria_collision_0B1E8_cells", _gAkropolisCafeteriaCollisionGridCells);
static s16* _gAkropolisCafeteriaCollisionGridTable[9];
#include "port/asset_bind.h"
PE_ASSET_BIND_AUX("akropolis_cafeteria_collision_0B1E8_table", _gAkropolisCafeteriaCollisionGridTable, _gAkropolisCafeteriaCollisionGridCells);
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
static WorldCollisionGrid _gAkropolisCafeteriaCollisionGrid;
static void peDecodeArr_gAkropolisCafeteriaCollisionGrid(void* base, const unsigned char* src, size_t n)
{
    WorldCollisionGrid* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_WorldCollisionGrid(&dst[k], src + k * 36);
    dst[0].normals = _gAkropolisCafeteriaCollisionGridNormals;
    dst[0].vertices = _gAkropolisCafeteriaCollisionGridVerts;
    dst[0].faces = _gAkropolisCafeteriaCollisionGridFaces;
    dst[0].cellFaceIds = _gAkropolisCafeteriaCollisionGridTable;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_cafeteria/_gAkropolisCafeteriaCollisionGrid", _gAkropolisCafeteriaCollisionGrid, peDecodeArr_gAkropolisCafeteriaCollisionGrid);
