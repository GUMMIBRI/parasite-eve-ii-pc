/* rooms/akropolis/plaza/package: written from its room instance by tools/buildsteps/gen_room_inc.py. */

#include "types.h"
#include "gameplay/collision.h"

static SVECTOR _gAkropolisPlazaCollisionGridNormals[30];
#include "port/asset_bind.h"
PE_ASSET_BIND("akropolis_plaza_collision_1BBC0_normals", _gAkropolisPlazaCollisionGridNormals);
static SVECTOR _gAkropolisPlazaCollisionGridVerts[80];
#include "port/asset_bind.h"
PE_ASSET_BIND("akropolis_plaza_collision_1BBC0_verts", _gAkropolisPlazaCollisionGridVerts);
static WorldCollisionGridFace _gAkropolisPlazaCollisionGridFaces[32];
#include "port/asset_bind.h"
PE_ASSET_BIND("akropolis_plaza_collision_1BBC0_faces", _gAkropolisPlazaCollisionGridFaces);
static s16 _gAkropolisPlazaCollisionGridCells[192];
#include "port/asset_bind.h"
PE_ASSET_BIND("akropolis_plaza_collision_1BBC0_cells", _gAkropolisPlazaCollisionGridCells);
static s16* _gAkropolisPlazaCollisionGridTable[28];
#include "port/asset_bind.h"
PE_ASSET_BIND_AUX("akropolis_plaza_collision_1BBC0_table", _gAkropolisPlazaCollisionGridTable, _gAkropolisPlazaCollisionGridCells);
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
static WorldCollisionGrid _gAkropolisPlazaCollisionGrid;
static void peDecodeArr_gAkropolisPlazaCollisionGrid(void* base, const unsigned char* src, size_t n)
{
    WorldCollisionGrid* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_WorldCollisionGrid(&dst[k], src + k * 36);
    dst[0].normals = _gAkropolisPlazaCollisionGridNormals;
    dst[0].vertices = _gAkropolisPlazaCollisionGridVerts;
    dst[0].faces = _gAkropolisPlazaCollisionGridFaces;
    dst[0].cellFaceIds = _gAkropolisPlazaCollisionGridTable;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_plaza/_gAkropolisPlazaCollisionGrid", _gAkropolisPlazaCollisionGrid, peDecodeArr_gAkropolisPlazaCollisionGrid);
