/* rooms/akropolis/sanctuary/package: written from its room instance by tools/buildsteps/gen_room_inc.py. */

#include "types.h"
#include "gameplay/collision.h"

static SVECTOR _gAkropolisSanctuaryCollisionGridNormals[42];
#include "port/asset_bind.h"
PE_ASSET_BIND("akropolis_sanctuary_collision_05FA8_normals", _gAkropolisSanctuaryCollisionGridNormals);
static SVECTOR _gAkropolisSanctuaryCollisionGridVerts[136];
#include "port/asset_bind.h"
PE_ASSET_BIND("akropolis_sanctuary_collision_05FA8_verts", _gAkropolisSanctuaryCollisionGridVerts);
static WorldCollisionGridFace _gAkropolisSanctuaryCollisionGridFaces[85];
#include "port/asset_bind.h"
PE_ASSET_BIND("akropolis_sanctuary_collision_05FA8_faces", _gAkropolisSanctuaryCollisionGridFaces);
static s16 _gAkropolisSanctuaryCollisionGridCells[386];
#include "port/asset_bind.h"
PE_ASSET_BIND("akropolis_sanctuary_collision_05FA8_cells", _gAkropolisSanctuaryCollisionGridCells);
static s16* _gAkropolisSanctuaryCollisionGridTable[9];
#include "port/asset_bind.h"
PE_ASSET_BIND_AUX("akropolis_sanctuary_collision_05FA8_table", _gAkropolisSanctuaryCollisionGridTable, _gAkropolisSanctuaryCollisionGridCells);
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
static WorldCollisionGrid _gAkropolisSanctuaryCollisionGrid;
static void peDecodeArr_gAkropolisSanctuaryCollisionGrid(void* base, const unsigned char* src, size_t n)
{
    WorldCollisionGrid* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_WorldCollisionGrid(&dst[k], src + k * 36);
    dst[0].normals = _gAkropolisSanctuaryCollisionGridNormals;
    dst[0].vertices = _gAkropolisSanctuaryCollisionGridVerts;
    dst[0].faces = _gAkropolisSanctuaryCollisionGridFaces;
    dst[0].cellFaceIds = _gAkropolisSanctuaryCollisionGridTable;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_sanctuary/_gAkropolisSanctuaryCollisionGrid", _gAkropolisSanctuaryCollisionGrid, peDecodeArr_gAkropolisSanctuaryCollisionGrid);
