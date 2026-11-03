/* rooms/akropolis/observatory/package: written from its room instance by tools/buildsteps/gen_room_inc.py. */

#include "types.h"
#include "gameplay/collision.h"

static SVECTOR _gAkropolisObservatoryCollisionGridNormals[22];
#include "port/asset_bind.h"
PE_ASSET_BIND("akropolis_observatory_collision_03490_normals", _gAkropolisObservatoryCollisionGridNormals);
static SVECTOR _gAkropolisObservatoryCollisionGridVerts[155];
#include "port/asset_bind.h"
PE_ASSET_BIND("akropolis_observatory_collision_03490_verts", _gAkropolisObservatoryCollisionGridVerts);
static WorldCollisionGridFace _gAkropolisObservatoryCollisionGridFaces[62];
#include "port/asset_bind.h"
PE_ASSET_BIND("akropolis_observatory_collision_03490_faces", _gAkropolisObservatoryCollisionGridFaces);
static s16 _gAkropolisObservatoryCollisionGridCells[232];
#include "port/asset_bind.h"
PE_ASSET_BIND("akropolis_observatory_collision_03490_cells", _gAkropolisObservatoryCollisionGridCells);
static s16* _gAkropolisObservatoryCollisionGridTable[9];
#include "port/asset_bind.h"
PE_ASSET_BIND_AUX("akropolis_observatory_collision_03490_table", _gAkropolisObservatoryCollisionGridTable, _gAkropolisObservatoryCollisionGridCells);
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
static WorldCollisionGrid _gAkropolisObservatoryCollisionGrid;
static void peDecodeArr_gAkropolisObservatoryCollisionGrid(void* base, const unsigned char* src, size_t n)
{
    WorldCollisionGrid* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_WorldCollisionGrid(&dst[k], src + k * 36);
    dst[0].normals = _gAkropolisObservatoryCollisionGridNormals;
    dst[0].vertices = _gAkropolisObservatoryCollisionGridVerts;
    dst[0].faces = _gAkropolisObservatoryCollisionGridFaces;
    dst[0].cellFaceIds = _gAkropolisObservatoryCollisionGridTable;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_observatory/_gAkropolisObservatoryCollisionGrid", _gAkropolisObservatoryCollisionGrid, peDecodeArr_gAkropolisObservatoryCollisionGrid);
