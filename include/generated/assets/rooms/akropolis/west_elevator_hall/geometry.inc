/* rooms/akropolis/west_elevator_hall/package: written from its room instance by tools/buildsteps/gen_room_inc.py. */

#include "types.h"
#include "gameplay/collision.h"

static SVECTOR _gAkropolisWestElevatorHallCollisionGridNormals[7];
#include "port/asset_bind.h"
PE_ASSET_BIND("akropolis_west_elevator_hall_collision_07D3C_normals", _gAkropolisWestElevatorHallCollisionGridNormals);
static SVECTOR _gAkropolisWestElevatorHallCollisionGridVerts[29];
#include "port/asset_bind.h"
PE_ASSET_BIND("akropolis_west_elevator_hall_collision_07D3C_verts", _gAkropolisWestElevatorHallCollisionGridVerts);
static WorldCollisionGridFace _gAkropolisWestElevatorHallCollisionGridFaces[14];
#include "port/asset_bind.h"
PE_ASSET_BIND("akropolis_west_elevator_hall_collision_07D3C_faces", _gAkropolisWestElevatorHallCollisionGridFaces);
static s16 _gAkropolisWestElevatorHallCollisionGridCells[52];
#include "port/asset_bind.h"
PE_ASSET_BIND("akropolis_west_elevator_hall_collision_07D3C_cells", _gAkropolisWestElevatorHallCollisionGridCells);
static s16* _gAkropolisWestElevatorHallCollisionGridTable[6];
#include "port/asset_bind.h"
PE_ASSET_BIND_AUX("akropolis_west_elevator_hall_collision_07D3C_table", _gAkropolisWestElevatorHallCollisionGridTable, _gAkropolisWestElevatorHallCollisionGridCells);
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
static WorldCollisionGrid _gAkropolisWestElevatorHallCollisionGrid;
static void peDecodeArr_gAkropolisWestElevatorHallCollisionGrid(void* base, const unsigned char* src, size_t n)
{
    WorldCollisionGrid* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_WorldCollisionGrid(&dst[k], src + k * 36);
    dst[0].normals = _gAkropolisWestElevatorHallCollisionGridNormals;
    dst[0].vertices = _gAkropolisWestElevatorHallCollisionGridVerts;
    dst[0].faces = _gAkropolisWestElevatorHallCollisionGridFaces;
    dst[0].cellFaceIds = _gAkropolisWestElevatorHallCollisionGridTable;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_west_elevator_hall/_gAkropolisWestElevatorHallCollisionGrid", _gAkropolisWestElevatorHallCollisionGrid, peDecodeArr_gAkropolisWestElevatorHallCollisionGrid);
