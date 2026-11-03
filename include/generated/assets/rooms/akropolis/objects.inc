/* rooms/akropolis/stage: written from its room instance by tools/buildsteps/gen_room_inc.py. */

#include "types.h"
#include "gameplay/area_flags.h"

#ifndef PE_DECODE_AreaObjectRoom
#define PE_DECODE_AreaObjectRoom
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
static void peDecode_AreaObjectRoom(AreaObjectRoom* dst, const unsigned char* src)
{
    { uint32_t v; memcpy(&v, src + 0, 4); dst->places.sentinel = v; }
    /* spawns: pointer, set by the array's fixups */
}

#endif
AreaObjectRoom gAkropolisStageObjectRooms[22];
static void peDecodeArr_gAkropolisStageObjectRooms(void* base, const unsigned char* src, size_t n)
{
    AreaObjectRoom* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AreaObjectRoom(&dst[k], src + k * 8);
    dst[1].places.list = _gAkropolisStageSquareObjectPlaces;
    dst[1].spawns = _gAkropolisStageSquareObjectSpawns;
    dst[2].places.list = _gAkropolisStageEastElevatorHallObjectPlaces;
    dst[2].spawns = _gAkropolisStageEastElevatorHallObjectSpawns;
    dst[4].places.list = _gAkropolisStageCafeteriaObjectPlaces;
    dst[4].spawns = _gAkropolisStageCafeteriaObjectSpawns;
    dst[6].places.list = _gAkropolisStageSecurityRoomObjectPlaces;
    dst[6].spawns = _gAkropolisStageSecurityRoomObjectSpawns;
    dst[7].places.list = _gAkropolisStageHallwayObjectPlaces;
    dst[7].spawns = _gAkropolisStageHallwayObjectSpawns;
    dst[8].places.list = _gAkropolisStageFountainObjectPlaces;
    dst[8].spawns = _gAkropolisStageFountainObjectSpawns;
    dst[9].places.list = _gAkropolisStageForkedRoadObjectPlaces;
    dst[9].spawns = _gAkropolisStageForkedRoadObjectSpawns;
    dst[10].places.list = _gAkropolisStageObservatoryObjectPlaces;
    dst[10].spawns = _gAkropolisStageObservatoryObjectSpawns;
    dst[11].places.list = _gAkropolisStagePromenadeObjectPlaces;
    dst[11].spawns = _gAkropolisStagePromenadeObjectSpawns;
    dst[12].places.list = _gAkropolisStageSanctuaryObjectPlaces;
    dst[12].spawns = _gAkropolisStageSanctuaryObjectSpawns;
    dst[13].places.list = _gAkropolisStageRoofGardenObjectPlaces;
    dst[13].spawns = _gAkropolisStageRoofGardenObjectSpawns;
    dst[15].places.list = _gAkropolisStageFireEscapeObjectPlaces;
    dst[15].spawns = _gAkropolisStageFireEscapeObjectSpawns;
    dst[16].places.list = _gAkropolisStageHelicopterLandingPadObjectPlaces;
    dst[16].spawns = _gAkropolisStageHelicopterLandingPadObjectSpawns;
    dst[17].places.list = _gAkropolisStageWestElevatorHallObjectPlaces;
    dst[17].spawns = _gAkropolisStageWestElevatorHallObjectSpawns;
    dst[19].places.list = _gAkropolisStageMistParkingObjectPlaces;
    dst[19].spawns = _gAkropolisStageMistParkingObjectSpawns;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_stage/gAkropolisStageObjectRooms", gAkropolisStageObjectRooms, peDecodeArr_gAkropolisStageObjectRooms);
