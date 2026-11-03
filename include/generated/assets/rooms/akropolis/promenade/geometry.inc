/* rooms/akropolis/promenade/package: written from its room instance by tools/buildsteps/gen_room_inc.py. */

#include "types.h"
#include "gameplay/collision.h"

static SVECTOR _gAkropolisPromenadeRoom1CollisionGridNormals[30];
#include "port/asset_bind.h"
PE_ASSET_BIND("akropolis_promenade_collision_04E1C_normals", _gAkropolisPromenadeRoom1CollisionGridNormals);
static SVECTOR _gAkropolisPromenadeRoom1CollisionGridVerts[93];
#include "port/asset_bind.h"
PE_ASSET_BIND("akropolis_promenade_collision_04E1C_verts", _gAkropolisPromenadeRoom1CollisionGridVerts);
static WorldCollisionGridFace _gAkropolisPromenadeRoom1CollisionGridFaces[38];
#include "port/asset_bind.h"
PE_ASSET_BIND("akropolis_promenade_collision_04E1C_faces", _gAkropolisPromenadeRoom1CollisionGridFaces);
static s16 _gAkropolisPromenadeRoom1CollisionGridCells[144];
#include "port/asset_bind.h"
PE_ASSET_BIND("akropolis_promenade_collision_04E1C_cells", _gAkropolisPromenadeRoom1CollisionGridCells);
static s16* _gAkropolisPromenadeRoom1CollisionGridTable[10];
#include "port/asset_bind.h"
PE_ASSET_BIND_AUX("akropolis_promenade_collision_04E1C_table", _gAkropolisPromenadeRoom1CollisionGridTable, _gAkropolisPromenadeRoom1CollisionGridCells);
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
static WorldCollisionGrid _gAkropolisPromenadeRoom1CollisionGrid;
static void peDecodeArr_gAkropolisPromenadeRoom1CollisionGrid(void* base, const unsigned char* src, size_t n)
{
    WorldCollisionGrid* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_WorldCollisionGrid(&dst[k], src + k * 36);
    dst[0].normals = _gAkropolisPromenadeRoom1CollisionGridNormals;
    dst[0].vertices = _gAkropolisPromenadeRoom1CollisionGridVerts;
    dst[0].faces = _gAkropolisPromenadeRoom1CollisionGridFaces;
    dst[0].cellFaceIds = _gAkropolisPromenadeRoom1CollisionGridTable;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_promenade/_gAkropolisPromenadeRoom1CollisionGrid", _gAkropolisPromenadeRoom1CollisionGrid, peDecodeArr_gAkropolisPromenadeRoom1CollisionGrid);
static SVECTOR _gAkropolisPromenadeRoom2CollisionGridNormals[30];
#include "port/asset_bind.h"
PE_ASSET_BIND("akropolis_promenade_collision_05610_normals", _gAkropolisPromenadeRoom2CollisionGridNormals);
static SVECTOR _gAkropolisPromenadeRoom2CollisionGridVerts[103];
#include "port/asset_bind.h"
PE_ASSET_BIND("akropolis_promenade_collision_05610_verts", _gAkropolisPromenadeRoom2CollisionGridVerts);
static WorldCollisionGridFace _gAkropolisPromenadeRoom2CollisionGridFaces[46];
#include "port/asset_bind.h"
PE_ASSET_BIND("akropolis_promenade_collision_05610_faces", _gAkropolisPromenadeRoom2CollisionGridFaces);
static s16 _gAkropolisPromenadeRoom2CollisionGridCells[172];
#include "port/asset_bind.h"
PE_ASSET_BIND("akropolis_promenade_collision_05610_cells", _gAkropolisPromenadeRoom2CollisionGridCells);
static s16* _gAkropolisPromenadeRoom2CollisionGridTable[10];
#include "port/asset_bind.h"
PE_ASSET_BIND_AUX("akropolis_promenade_collision_05610_table", _gAkropolisPromenadeRoom2CollisionGridTable, _gAkropolisPromenadeRoom2CollisionGridCells);
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
static WorldCollisionGrid _gAkropolisPromenadeRoom2CollisionGrid;
static void peDecodeArr_gAkropolisPromenadeRoom2CollisionGrid(void* base, const unsigned char* src, size_t n)
{
    WorldCollisionGrid* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_WorldCollisionGrid(&dst[k], src + k * 36);
    dst[0].normals = _gAkropolisPromenadeRoom2CollisionGridNormals;
    dst[0].vertices = _gAkropolisPromenadeRoom2CollisionGridVerts;
    dst[0].faces = _gAkropolisPromenadeRoom2CollisionGridFaces;
    dst[0].cellFaceIds = _gAkropolisPromenadeRoom2CollisionGridTable;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_promenade/_gAkropolisPromenadeRoom2CollisionGrid", _gAkropolisPromenadeRoom2CollisionGrid, peDecodeArr_gAkropolisPromenadeRoom2CollisionGrid);
