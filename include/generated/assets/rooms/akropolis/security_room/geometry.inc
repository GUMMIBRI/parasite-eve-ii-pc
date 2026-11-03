/* rooms/akropolis/security_room/package: written from its room instance by tools/buildsteps/gen_room_inc.py. */

#include "types.h"
#include "gameplay/collision.h"

static SVECTOR _gAkropolisSecurityRoomCollisionGridNormals[11];
#include "port/asset_bind.h"
PE_ASSET_BIND("akropolis_security_room_collision_067D4_normals", _gAkropolisSecurityRoomCollisionGridNormals);
static SVECTOR _gAkropolisSecurityRoomCollisionGridVerts[50];
#include "port/asset_bind.h"
PE_ASSET_BIND("akropolis_security_room_collision_067D4_verts", _gAkropolisSecurityRoomCollisionGridVerts);
static WorldCollisionGridFace _gAkropolisSecurityRoomCollisionGridFaces[24];
#include "port/asset_bind.h"
PE_ASSET_BIND("akropolis_security_room_collision_067D4_faces", _gAkropolisSecurityRoomCollisionGridFaces);
static s16 _gAkropolisSecurityRoomCollisionGridCells[46];
#include "port/asset_bind.h"
PE_ASSET_BIND("akropolis_security_room_collision_067D4_cells", _gAkropolisSecurityRoomCollisionGridCells);
static s16* _gAkropolisSecurityRoomCollisionGridTable[2];
#include "port/asset_bind.h"
PE_ASSET_BIND_AUX("akropolis_security_room_collision_067D4_table", _gAkropolisSecurityRoomCollisionGridTable, _gAkropolisSecurityRoomCollisionGridCells);
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
static WorldCollisionGrid _gAkropolisSecurityRoomCollisionGrid;
static void peDecodeArr_gAkropolisSecurityRoomCollisionGrid(void* base, const unsigned char* src, size_t n)
{
    WorldCollisionGrid* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_WorldCollisionGrid(&dst[k], src + k * 36);
    dst[0].normals = _gAkropolisSecurityRoomCollisionGridNormals;
    dst[0].vertices = _gAkropolisSecurityRoomCollisionGridVerts;
    dst[0].faces = _gAkropolisSecurityRoomCollisionGridFaces;
    dst[0].cellFaceIds = _gAkropolisSecurityRoomCollisionGridTable;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_security_room/_gAkropolisSecurityRoomCollisionGrid", _gAkropolisSecurityRoomCollisionGrid, peDecodeArr_gAkropolisSecurityRoomCollisionGrid);
