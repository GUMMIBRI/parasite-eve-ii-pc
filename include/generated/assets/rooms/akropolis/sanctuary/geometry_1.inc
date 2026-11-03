/* rooms/akropolis/sanctuary/package: written from its room instance by tools/buildsteps/gen_room_inc.py. */

#include "types.h"
#include "gameplay/collision.h"

static SVECTOR _gAkropolisSanctuaryBlockerCollisionGridNormals[4];
#include "port/asset_bind.h"
PE_ASSET_BIND("akropolis_sanctuary_collision_04D2C_normals", _gAkropolisSanctuaryBlockerCollisionGridNormals);
static SVECTOR _gAkropolisSanctuaryBlockerCollisionGridVerts[8];
#include "port/asset_bind.h"
PE_ASSET_BIND("akropolis_sanctuary_collision_04D2C_verts", _gAkropolisSanctuaryBlockerCollisionGridVerts);
static WorldCollisionGridFace _gAkropolisSanctuaryBlockerCollisionGridFaces[4];
#include "port/asset_bind.h"
PE_ASSET_BIND("akropolis_sanctuary_collision_04D2C_faces", _gAkropolisSanctuaryBlockerCollisionGridFaces);
static s16 _gAkropolisSanctuaryBlockerCollisionGridCells[6];
#include "port/asset_bind.h"
PE_ASSET_BIND("akropolis_sanctuary_collision_04D2C_cells", _gAkropolisSanctuaryBlockerCollisionGridCells);
static s16* _gAkropolisSanctuaryBlockerCollisionGridTable[1];
#include "port/asset_bind.h"
PE_ASSET_BIND_AUX("akropolis_sanctuary_collision_04D2C_table", _gAkropolisSanctuaryBlockerCollisionGridTable, _gAkropolisSanctuaryBlockerCollisionGridCells);
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
static WorldCollisionGrid _gAkropolisSanctuaryBlockerCollisionGrid;
static void peDecodeArr_gAkropolisSanctuaryBlockerCollisionGrid(void* base, const unsigned char* src, size_t n)
{
    WorldCollisionGrid* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_WorldCollisionGrid(&dst[k], src + k * 36);
    dst[0].normals = _gAkropolisSanctuaryBlockerCollisionGridNormals;
    dst[0].vertices = _gAkropolisSanctuaryBlockerCollisionGridVerts;
    dst[0].faces = _gAkropolisSanctuaryBlockerCollisionGridFaces;
    dst[0].cellFaceIds = _gAkropolisSanctuaryBlockerCollisionGridTable;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_sanctuary/_gAkropolisSanctuaryBlockerCollisionGrid", _gAkropolisSanctuaryBlockerCollisionGrid, peDecodeArr_gAkropolisSanctuaryBlockerCollisionGrid);
