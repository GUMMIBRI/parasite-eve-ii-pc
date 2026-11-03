/* rooms/akropolis/hallway/package: written from its room instance by tools/buildsteps/gen_room_inc.py. */

#include "types.h"
#include "gameplay/collision.h"

static SVECTOR _gAkropolisHallwayCollisionGridNormals[10];
#include "port/asset_bind.h"
PE_ASSET_BIND("akropolis_hallway_collision_01010_normals", _gAkropolisHallwayCollisionGridNormals);
static SVECTOR _gAkropolisHallwayCollisionGridVerts[35];
#include "port/asset_bind.h"
PE_ASSET_BIND("akropolis_hallway_collision_01010_verts", _gAkropolisHallwayCollisionGridVerts);
static WorldCollisionGridFace _gAkropolisHallwayCollisionGridFaces[17];
#include "port/asset_bind.h"
PE_ASSET_BIND("akropolis_hallway_collision_01010_faces", _gAkropolisHallwayCollisionGridFaces);
static s16 _gAkropolisHallwayCollisionGridCells[30];
#include "port/asset_bind.h"
PE_ASSET_BIND("akropolis_hallway_collision_01010_cells", _gAkropolisHallwayCollisionGridCells);
static s16* _gAkropolisHallwayCollisionGridTable[2];
#include "port/asset_bind.h"
PE_ASSET_BIND_AUX("akropolis_hallway_collision_01010_table", _gAkropolisHallwayCollisionGridTable, _gAkropolisHallwayCollisionGridCells);
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
static WorldCollisionGrid _gAkropolisHallwayCollisionGrid;
static void peDecodeArr_gAkropolisHallwayCollisionGrid(void* base, const unsigned char* src, size_t n)
{
    WorldCollisionGrid* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_WorldCollisionGrid(&dst[k], src + k * 36);
    dst[0].normals = _gAkropolisHallwayCollisionGridNormals;
    dst[0].vertices = _gAkropolisHallwayCollisionGridVerts;
    dst[0].faces = _gAkropolisHallwayCollisionGridFaces;
    dst[0].cellFaceIds = _gAkropolisHallwayCollisionGridTable;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_hallway/_gAkropolisHallwayCollisionGrid", _gAkropolisHallwayCollisionGrid, peDecodeArr_gAkropolisHallwayCollisionGrid);
