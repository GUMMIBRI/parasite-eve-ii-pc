/* rooms/akropolis/roof_garden/package: written from its room instance by tools/buildsteps/gen_room_inc.py. */

#include "types.h"
#include "gameplay/collision.h"

static SVECTOR _gAkropolisRoofGardenCollisionGridNormals[31];
#include "port/asset_bind.h"
PE_ASSET_BIND("akropolis_roof_garden_collision_07EE4_normals", _gAkropolisRoofGardenCollisionGridNormals);
static SVECTOR _gAkropolisRoofGardenCollisionGridVerts[92];
#include "port/asset_bind.h"
PE_ASSET_BIND("akropolis_roof_garden_collision_07EE4_verts", _gAkropolisRoofGardenCollisionGridVerts);
static WorldCollisionGridFace _gAkropolisRoofGardenCollisionGridFaces[53];
#include "port/asset_bind.h"
PE_ASSET_BIND("akropolis_roof_garden_collision_07EE4_faces", _gAkropolisRoofGardenCollisionGridFaces);
static s16 _gAkropolisRoofGardenCollisionGridCells[136];
#include "port/asset_bind.h"
PE_ASSET_BIND("akropolis_roof_garden_collision_07EE4_cells", _gAkropolisRoofGardenCollisionGridCells);
static s16* _gAkropolisRoofGardenCollisionGridTable[9];
#include "port/asset_bind.h"
PE_ASSET_BIND_AUX("akropolis_roof_garden_collision_07EE4_table", _gAkropolisRoofGardenCollisionGridTable, _gAkropolisRoofGardenCollisionGridCells);
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
static WorldCollisionGrid _gAkropolisRoofGardenCollisionGrid;
static void peDecodeArr_gAkropolisRoofGardenCollisionGrid(void* base, const unsigned char* src, size_t n)
{
    WorldCollisionGrid* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_WorldCollisionGrid(&dst[k], src + k * 36);
    dst[0].normals = _gAkropolisRoofGardenCollisionGridNormals;
    dst[0].vertices = _gAkropolisRoofGardenCollisionGridVerts;
    dst[0].faces = _gAkropolisRoofGardenCollisionGridFaces;
    dst[0].cellFaceIds = _gAkropolisRoofGardenCollisionGridTable;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_roof_garden/_gAkropolisRoofGardenCollisionGrid", _gAkropolisRoofGardenCollisionGrid, peDecodeArr_gAkropolisRoofGardenCollisionGrid);
