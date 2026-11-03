/* rooms/akropolis/patio/package: written from its room instance by tools/buildsteps/gen_room_inc.py. */

#include "types.h"
#include "gameplay/collision.h"

static SVECTOR _gAkropolisPatioCollisionGridNormals[33];
#include "port/asset_bind.h"
PE_ASSET_BIND("akropolis_patio_collision_06838_normals", _gAkropolisPatioCollisionGridNormals);
static SVECTOR _gAkropolisPatioCollisionGridVerts[201];
#include "port/asset_bind.h"
PE_ASSET_BIND("akropolis_patio_collision_06838_verts", _gAkropolisPatioCollisionGridVerts);
static WorldCollisionGridFace _gAkropolisPatioCollisionGridFaces[70];
#include "port/asset_bind.h"
PE_ASSET_BIND("akropolis_patio_collision_06838_faces", _gAkropolisPatioCollisionGridFaces);
static s16 _gAkropolisPatioCollisionGridCells[402];
#include "port/asset_bind.h"
PE_ASSET_BIND("akropolis_patio_collision_06838_cells", _gAkropolisPatioCollisionGridCells);
static s16* _gAkropolisPatioCollisionGridTable[28];
#include "port/asset_bind.h"
PE_ASSET_BIND_AUX("akropolis_patio_collision_06838_table", _gAkropolisPatioCollisionGridTable, _gAkropolisPatioCollisionGridCells);
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
static WorldCollisionGrid _gAkropolisPatioCollisionGrid;
static void peDecodeArr_gAkropolisPatioCollisionGrid(void* base, const unsigned char* src, size_t n)
{
    WorldCollisionGrid* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_WorldCollisionGrid(&dst[k], src + k * 36);
    dst[0].normals = _gAkropolisPatioCollisionGridNormals;
    dst[0].vertices = _gAkropolisPatioCollisionGridVerts;
    dst[0].faces = _gAkropolisPatioCollisionGridFaces;
    dst[0].cellFaceIds = _gAkropolisPatioCollisionGridTable;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_patio/_gAkropolisPatioCollisionGrid", _gAkropolisPatioCollisionGrid, peDecodeArr_gAkropolisPatioCollisionGrid);
