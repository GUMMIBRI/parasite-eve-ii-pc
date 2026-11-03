/* rooms/akropolis/stage: written from its room instance by tools/buildsteps/gen_room_inc.py. */

#include "types.h"
#include "gameplay/map.h"
#include "stages/akropolis/map.h"

u8 gAkropolisStagePageFlagIds[8];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_stage/gAkropolisStagePageFlagIds", gAkropolisStagePageFlagIds);
MenuMapArea gAkropolisStageAreas[22];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_stage/gAkropolisStageAreas", gAkropolisStageAreas);
#ifndef PE_DECODE_MenuMapAreaShape
#define PE_DECODE_MenuMapAreaShape
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
static void peDecode_MenuMapAreaShape(MenuMapAreaShape* dst, const unsigned char* src)
{
    /* model: pointer, set by the array's fixups */
    { uint8_t v; memcpy(&v, src + 4, 1); dst->page = v; }
    { uint8_t v; memcpy(&v, src + 5, 1); dst->pairedArea = v; }
}

#endif
MenuMapAreaShape gAkropolisStageAreaShapes[21];
static void peDecodeArr_gAkropolisStageAreaShapes(void* base, const unsigned char* src, size_t n)
{
    MenuMapAreaShape* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_MenuMapAreaShape(&dst[k], src + k * 8);
    dst[1].model = &gAkropolisMapSquareShape;
    dst[2].model = &gAkropolisMapEastElevatorHallShape;
    dst[3].model = &gAkropolisMapPatioShape;
    dst[4].model = &gAkropolisMapCafeteriaShape;
    dst[6].model = &gAkropolisMapSecurityRoomShape;
    dst[7].model = &gAkropolisMapHallwayShape;
    dst[8].model = &gAkropolisMapFountainShape;
    dst[9].model = &gAkropolisMapForkedRoadShape;
    dst[10].model = &gAkropolisMapObservatoryShape;
    dst[11].model = &gAkropolisMapPromenadeShape;
    dst[12].model = &gAkropolisMapSanctuaryShape;
    dst[13].model = &gAkropolisMapRoofGardenShape;
    dst[14].model = &gAkropolisMapBridgeShape;
    dst[15].model = &gAkropolisMapFireEscapeShape;
    dst[16].model = &gAkropolisHelicopterLandingPadMapShape;
    dst[17].model = &gAkropolisMapWestElevatorHallShape;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_stage/gAkropolisStageAreaShapes", gAkropolisStageAreaShapes, peDecodeArr_gAkropolisStageAreaShapes);
MenuMapMarker gAkropolisStageMarkers[15];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_stage/gAkropolisStageMarkers", gAkropolisStageMarkers);
MenuMapIcon gAkropolisStageIcons[6];
#include "port/asset_bind.h"
PE_ASSET_BIND("room/akropolis_stage/gAkropolisStageIcons", gAkropolisStageIcons);
#ifndef PE_DECODE_MenuMapAreaName
#define PE_DECODE_MenuMapAreaName
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
static void peDecode_MenuMapAreaName(MenuMapAreaName* dst, const unsigned char* src)
{
    memcpy(dst->text, src + 0, 32);
}

#endif
MenuMapAreaName gAkropolisStageAreaNames[21];
static void peDecodeArr_gAkropolisStageAreaNames(void* base, const unsigned char* src, size_t n)
{
    MenuMapAreaName* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_MenuMapAreaName(&dst[k], src + k * 32);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_stage/gAkropolisStageAreaNames", gAkropolisStageAreaNames, peDecodeArr_gAkropolisStageAreaNames);
