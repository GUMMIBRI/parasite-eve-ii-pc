/* rooms/akropolis/helicopter_landing_pad/package: written from its room instance by tools/buildsteps/gen_room_inc.py. */

#include "types.h"
#include "gameplay/collision.h"

SVECTOR gAkropolisHelicopterLandingPadCollisionGridNormals[15];
#include "port/asset_bind.h"
PE_ASSET_BIND("akropolis_helicopter_landing_pad_collision_083D8_normals", gAkropolisHelicopterLandingPadCollisionGridNormals);
SVECTOR gAkropolisHelicopterLandingPadCollisionGridVerts[92];
#include "port/asset_bind.h"
PE_ASSET_BIND("akropolis_helicopter_landing_pad_collision_083D8_verts", gAkropolisHelicopterLandingPadCollisionGridVerts);
WorldCollisionGridFace gAkropolisHelicopterLandingPadCollisionGridFaces[37];
#include "port/asset_bind.h"
PE_ASSET_BIND("akropolis_helicopter_landing_pad_collision_083D8_faces", gAkropolisHelicopterLandingPadCollisionGridFaces);
static s16 _gAkropolisHelicopterLandingPadCollisionGridCells[512];
#include "port/asset_bind.h"
PE_ASSET_BIND("akropolis_helicopter_landing_pad_collision_083D8_cells", _gAkropolisHelicopterLandingPadCollisionGridCells);
static s16* _gAkropolisHelicopterLandingPadCollisionGridTable[36];
#include "port/asset_bind.h"
PE_ASSET_BIND_AUX("akropolis_helicopter_landing_pad_collision_083D8_table", _gAkropolisHelicopterLandingPadCollisionGridTable, _gAkropolisHelicopterLandingPadCollisionGridCells);
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
static WorldCollisionGrid _gAkropolisHelicopterLandingPadCollisionGrid;
static void peDecodeArr_gAkropolisHelicopterLandingPadCollisionGrid(void* base, const unsigned char* src, size_t n)
{
    WorldCollisionGrid* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_WorldCollisionGrid(&dst[k], src + k * 36);
    dst[0].normals = gAkropolisHelicopterLandingPadCollisionGridNormals;
    dst[0].vertices = gAkropolisHelicopterLandingPadCollisionGridVerts;
    dst[0].faces = gAkropolisHelicopterLandingPadCollisionGridFaces;
    dst[0].cellFaceIds = _gAkropolisHelicopterLandingPadCollisionGridTable;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_helicopter_landing_pad/_gAkropolisHelicopterLandingPadCollisionGrid", _gAkropolisHelicopterLandingPadCollisionGrid, peDecodeArr_gAkropolisHelicopterLandingPadCollisionGrid);
