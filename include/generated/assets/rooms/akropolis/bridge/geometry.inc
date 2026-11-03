/* rooms/akropolis/bridge/package: written from its room instance by tools/buildsteps/gen_room_inc.py. */

#include "types.h"
#include "gameplay/collision.h"

static SVECTOR _gAkropolisBridgeRoom1CollisionNormals[19];
#include "port/asset_bind.h"
PE_ASSET_BIND("akropolis_bridge_collision_0D2DC_normals", _gAkropolisBridgeRoom1CollisionNormals);
static SVECTOR _gAkropolisBridgeRoom1CollisionVerts[193];
#include "port/asset_bind.h"
PE_ASSET_BIND("akropolis_bridge_collision_0D2DC_verts", _gAkropolisBridgeRoom1CollisionVerts);
static WorldCollisionGridFace _gAkropolisBridgeRoom1CollisionFaces[92];
#include "port/asset_bind.h"
PE_ASSET_BIND("akropolis_bridge_collision_0D2DC_faces", _gAkropolisBridgeRoom1CollisionFaces);
static s16 _gAkropolisBridgeRoom1CollisionCells[274];
#include "port/asset_bind.h"
PE_ASSET_BIND("akropolis_bridge_collision_0D2DC_cells", _gAkropolisBridgeRoom1CollisionCells);
static s16* _gAkropolisBridgeRoom1CollisionTable[25];
#include "port/asset_bind.h"
PE_ASSET_BIND_AUX("akropolis_bridge_collision_0D2DC_table", _gAkropolisBridgeRoom1CollisionTable, _gAkropolisBridgeRoom1CollisionCells);
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
static WorldCollisionGrid _gAkropolisBridgeRoom1Collision;
static void peDecodeArr_gAkropolisBridgeRoom1Collision(void* base, const unsigned char* src, size_t n)
{
    WorldCollisionGrid* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_WorldCollisionGrid(&dst[k], src + k * 36);
    dst[0].normals = _gAkropolisBridgeRoom1CollisionNormals;
    dst[0].vertices = _gAkropolisBridgeRoom1CollisionVerts;
    dst[0].faces = _gAkropolisBridgeRoom1CollisionFaces;
    dst[0].cellFaceIds = _gAkropolisBridgeRoom1CollisionTable;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_bridge/_gAkropolisBridgeRoom1Collision", _gAkropolisBridgeRoom1Collision, peDecodeArr_gAkropolisBridgeRoom1Collision);
static SVECTOR _gAkropolisBridgeRoom2CollisionNormals[17];
#include "port/asset_bind.h"
PE_ASSET_BIND("akropolis_bridge_collision_0E0D4_normals", _gAkropolisBridgeRoom2CollisionNormals);
static SVECTOR _gAkropolisBridgeRoom2CollisionVerts[205];
#include "port/asset_bind.h"
PE_ASSET_BIND("akropolis_bridge_collision_0E0D4_verts", _gAkropolisBridgeRoom2CollisionVerts);
static WorldCollisionGridFace _gAkropolisBridgeRoom2CollisionFaces[93];
#include "port/asset_bind.h"
PE_ASSET_BIND("akropolis_bridge_collision_0E0D4_faces", _gAkropolisBridgeRoom2CollisionFaces);
static s16 _gAkropolisBridgeRoom2CollisionCells[274];
#include "port/asset_bind.h"
PE_ASSET_BIND("akropolis_bridge_collision_0E0D4_cells", _gAkropolisBridgeRoom2CollisionCells);
static s16* _gAkropolisBridgeRoom2CollisionTable[25];
#include "port/asset_bind.h"
PE_ASSET_BIND_AUX("akropolis_bridge_collision_0E0D4_table", _gAkropolisBridgeRoom2CollisionTable, _gAkropolisBridgeRoom2CollisionCells);
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
static WorldCollisionGrid _gAkropolisBridgeRoom2Collision;
static void peDecodeArr_gAkropolisBridgeRoom2Collision(void* base, const unsigned char* src, size_t n)
{
    WorldCollisionGrid* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_WorldCollisionGrid(&dst[k], src + k * 36);
    dst[0].normals = _gAkropolisBridgeRoom2CollisionNormals;
    dst[0].vertices = _gAkropolisBridgeRoom2CollisionVerts;
    dst[0].faces = _gAkropolisBridgeRoom2CollisionFaces;
    dst[0].cellFaceIds = _gAkropolisBridgeRoom2CollisionTable;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_bridge/_gAkropolisBridgeRoom2Collision", _gAkropolisBridgeRoom2Collision, peDecodeArr_gAkropolisBridgeRoom2Collision);
