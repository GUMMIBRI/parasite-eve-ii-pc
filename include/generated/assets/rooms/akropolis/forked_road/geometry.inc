/* rooms/akropolis/forked_road/package: written from its room instance by tools/buildsteps/gen_room_inc.py. */

#include "types.h"
#include "gameplay/collision.h"

static SVECTOR _gAkropolisForkedRoadCollisionGridNormals[18];
#include "port/asset_bind.h"
PE_ASSET_BIND("akropolis_forked_road_collision_05630_normals", _gAkropolisForkedRoadCollisionGridNormals);
static SVECTOR _gAkropolisForkedRoadCollisionGridVerts[118];
#include "port/asset_bind.h"
PE_ASSET_BIND("akropolis_forked_road_collision_05630_verts", _gAkropolisForkedRoadCollisionGridVerts);
static WorldCollisionGridFace _gAkropolisForkedRoadCollisionGridFaces[38];
#include "port/asset_bind.h"
PE_ASSET_BIND("akropolis_forked_road_collision_05630_faces", _gAkropolisForkedRoadCollisionGridFaces);
static s16 _gAkropolisForkedRoadCollisionGridCells[244];
#include "port/asset_bind.h"
PE_ASSET_BIND("akropolis_forked_road_collision_05630_cells", _gAkropolisForkedRoadCollisionGridCells);
static s16* _gAkropolisForkedRoadCollisionGridTable[24];
#include "port/asset_bind.h"
PE_ASSET_BIND_AUX("akropolis_forked_road_collision_05630_table", _gAkropolisForkedRoadCollisionGridTable, _gAkropolisForkedRoadCollisionGridCells);
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
static WorldCollisionGrid _gAkropolisForkedRoadCollisionGrid;
static void peDecodeArr_gAkropolisForkedRoadCollisionGrid(void* base, const unsigned char* src, size_t n)
{
    WorldCollisionGrid* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_WorldCollisionGrid(&dst[k], src + k * 36);
    dst[0].normals = _gAkropolisForkedRoadCollisionGridNormals;
    dst[0].vertices = _gAkropolisForkedRoadCollisionGridVerts;
    dst[0].faces = _gAkropolisForkedRoadCollisionGridFaces;
    dst[0].cellFaceIds = _gAkropolisForkedRoadCollisionGridTable;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_forked_road/_gAkropolisForkedRoadCollisionGrid", _gAkropolisForkedRoadCollisionGrid, peDecodeArr_gAkropolisForkedRoadCollisionGrid);
