/* rooms/akropolis/east_elevator_hall/package: written from its room instance by tools/buildsteps/gen_room_inc.py. */

#include "types.h"
#include "gameplay/collision.h"

static SVECTOR _gAkropolisEastElevatorHallCollisionGridNormals[10];
#include "port/asset_bind.h"
PE_ASSET_BIND("akropolis_east_elevator_hall_collision_09278_normals", _gAkropolisEastElevatorHallCollisionGridNormals);
static SVECTOR _gAkropolisEastElevatorHallCollisionGridVerts[66];
#include "port/asset_bind.h"
PE_ASSET_BIND("akropolis_east_elevator_hall_collision_09278_verts", _gAkropolisEastElevatorHallCollisionGridVerts);
static WorldCollisionGridFace _gAkropolisEastElevatorHallCollisionGridFaces[33];
#include "port/asset_bind.h"
PE_ASSET_BIND("akropolis_east_elevator_hall_collision_09278_faces", _gAkropolisEastElevatorHallCollisionGridFaces);
static s16 _gAkropolisEastElevatorHallCollisionGridCells[90];
#include "port/asset_bind.h"
PE_ASSET_BIND("akropolis_east_elevator_hall_collision_09278_cells", _gAkropolisEastElevatorHallCollisionGridCells);
static s16* _gAkropolisEastElevatorHallCollisionGridTable[8];
#include "port/asset_bind.h"
PE_ASSET_BIND_AUX("akropolis_east_elevator_hall_collision_09278_table", _gAkropolisEastElevatorHallCollisionGridTable, _gAkropolisEastElevatorHallCollisionGridCells);
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
static WorldCollisionGrid _gAkropolisEastElevatorHallCollisionGrid;
static void peDecodeArr_gAkropolisEastElevatorHallCollisionGrid(void* base, const unsigned char* src, size_t n)
{
    WorldCollisionGrid* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_WorldCollisionGrid(&dst[k], src + k * 36);
    dst[0].normals = _gAkropolisEastElevatorHallCollisionGridNormals;
    dst[0].vertices = _gAkropolisEastElevatorHallCollisionGridVerts;
    dst[0].faces = _gAkropolisEastElevatorHallCollisionGridFaces;
    dst[0].cellFaceIds = _gAkropolisEastElevatorHallCollisionGridTable;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_east_elevator_hall/_gAkropolisEastElevatorHallCollisionGrid", _gAkropolisEastElevatorHallCollisionGrid, peDecodeArr_gAkropolisEastElevatorHallCollisionGrid);
