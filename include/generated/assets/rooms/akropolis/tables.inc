/* rooms/akropolis/stage: written from its room instance by tools/buildsteps/gen_room_inc.py. */

#include "types.h"
#include "gameplay/direction.h"
#include "gameplay/room.h"
#include "gameplay/sprites.h"
#include "gameplay/view.h"
#include "stages/akropolis/rooms/bridge.h"
#include "stages/akropolis/rooms/cafeteria.h"
#include "stages/akropolis/rooms/east_elevator_hall.h"
#include "stages/akropolis/rooms/fire_escape.h"
#include "stages/akropolis/rooms/forked_road.h"
#include "stages/akropolis/rooms/fountain.h"
#include "stages/akropolis/rooms/hallway.h"
#include "stages/akropolis/rooms/helicopter_landing_pad.h"
#include "stages/akropolis/rooms/mist_parking.h"
#include "stages/akropolis/rooms/mist_r18.h"
#include "stages/akropolis/rooms/mist_shooting_gallery.h"
#include "stages/akropolis/rooms/observatory.h"
#include "stages/akropolis/rooms/patio.h"
#include "stages/akropolis/rooms/plaza.h"
#include "stages/akropolis/rooms/promenade.h"
#include "stages/akropolis/rooms/roof_garden.h"
#include "stages/akropolis/rooms/sanctuary.h"
#include "stages/akropolis/rooms/security_room.h"
#include "stages/akropolis/rooms/square.h"
#include "stages/akropolis/rooms/west_elevator_hall.h"

#ifndef PE_DECODE_AreaTableWorldCoordRoomLighting
#define PE_DECODE_AreaTableWorldCoordRoomLighting
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
static void peDecode_AreaTableWorldCoordRoomLighting(WorldCoordRoomLighting** dst, const unsigned char* src)
{
    /* : pointer, set by the array's fixups */
}

#endif
WorldCoordRoomLighting* gAkropolisStageAreaRoomLightingTables[20];
static void peDecodeArr_gAkropolisStageAreaRoomLightingTables(void* base, const unsigned char* src, size_t n)
{
    WorldCoordRoomLighting** dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AreaTableWorldCoordRoomLighting(&dst[k], src + k * 4);
    dst[0] = (void*)&gAkropolisSquareRoomLightingTable;
    dst[1] = (void*)&gAkropolisEastElevatorHallRoomLightingTable;
    dst[2] = (void*)&gAkropolisPatioRoomLightingTable;
    dst[3] = (void*)&gAkropolisCafeteriaRoomLightingTable;
    dst[4] = (void*)&gAkropolisPlazaRoomLightingTable;
    dst[5] = (void*)&gAkropolisSecurityRoomRoomLightingTable;
    dst[6] = (void*)&gAkropolisHallwayRoomLightingTable;
    dst[7] = (void*)&gAkropolisFountainRoomLightingTable;
    dst[8] = (void*)&gAkropolisForkedRoadRoomLightingTable;
    dst[9] = (void*)&gAkropolisObservatoryRoomLightingTable;
    dst[10] = (void*)&gAkropolisPromenadeRoomLightingTable;
    dst[11] = (void*)&gAkropolisSanctuaryRoomLightingTable;
    dst[12] = (void*)&gAkropolisRoofGardenRoomLightingTable;
    dst[13] = (void*)&gAkropolisBridgeRoomLightingTable;
    dst[14] = (void*)&gAkropolisFireEscapeRoomLightingTable;
    dst[15] = (void*)&gAkropolisHelicopterLandingPadRoomLightingTable;
    dst[16] = (void*)&gAkropolisWestElevatorHallRoomLightingTable;
    dst[17] = (void*)&gMistR18RoomLightingTable;
    dst[18] = (void*)&gMistParkingRoomLightingTable;
    dst[19] = (void*)&gMistShootingGalleryRoomLightingTable;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_stage/gAkropolisStageAreaRoomLightingTables", gAkropolisStageAreaRoomLightingTables, peDecodeArr_gAkropolisStageAreaRoomLightingTables);
#ifndef PE_DECODE_AreaTableWorldCollisionRoomResources
#define PE_DECODE_AreaTableWorldCollisionRoomResources
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
static void peDecode_AreaTableWorldCollisionRoomResources(WorldCollisionRoomResources** dst, const unsigned char* src)
{
    /* : pointer, set by the array's fixups */
}

#endif
static WorldCollisionRoomResources* _gAkropolisStageWorldCollisionAreaRooms[20];
static void peDecodeArr_gAkropolisStageWorldCollisionAreaRooms(void* base, const unsigned char* src, size_t n)
{
    WorldCollisionRoomResources** dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AreaTableWorldCollisionRoomResources(&dst[k], src + k * 4);
    dst[0] = (void*)&gAkropolisSquareRoomCollisionResources;
    dst[1] = (void*)&gAkropolisEastElevatorHallRoomCollisionResources;
    dst[2] = (void*)&gAkropolisPatioRoomCollisionResources;
    dst[3] = (void*)&gAkropolisCafeteriaCollisionRooms;
    dst[4] = (void*)&gAkropolisPlazaRoomCollisionResources;
    dst[5] = (void*)&gAkropolisSecurityRoomRoomCollisionResources;
    dst[6] = (void*)&gAkropolisHallwayRoomCollisionResources;
    dst[7] = (void*)&gAkropolisFountainRoomCollisionResources;
    dst[8] = (void*)&gAkropolisForkedRoadRoomCollisionResources;
    dst[9] = (void*)&gAkropolisObservatoryRoomCollisionResources;
    dst[10] = (void*)&gAkropolisPromenadeRoomCollisionResources;
    dst[11] = (void*)&gAkropolisSanctuaryRoomCollisionResources;
    dst[12] = (void*)&gAkropolisRoofGardenCollisionRoomResources;
    dst[13] = (void*)&gAkropolisBridgeRoomCollisionResources;
    dst[14] = (void*)&gAkropolisFireEscapeCollisionRoomResources;
    dst[15] = (void*)&gAkropolisHelicopterLandingPadCollisionRoomResources;
    dst[16] = (void*)&gAkropolisWestElevatorHallCollisionRoomResources;
    dst[17] = (void*)&gMistR18CollisionRoomResources;
    dst[18] = (void*)&gMistParkingRoomCollisionResources;
    dst[19] = (void*)&gMistShootingGalleryRoomCollisionResources;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_stage/_gAkropolisStageWorldCollisionAreaRooms", _gAkropolisStageWorldCollisionAreaRooms, peDecodeArr_gAkropolisStageWorldCollisionAreaRooms);
#ifndef PE_DECODE_WorldCollisionStageResources
#define PE_DECODE_WorldCollisionStageResources
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
static void peDecode_WorldCollisionStageResources(WorldCollisionStageResources* dst, const unsigned char* src)
{
    /* areaRooms: pointer, set by the array's fixups */
}

#endif
WorldCollisionStageResources gAkropolisStageWorldCollisionResources;
static void peDecodeArr_gAkropolisStageWorldCollisionResources(void* base, const unsigned char* src, size_t n)
{
    WorldCollisionStageResources* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_WorldCollisionStageResources(&dst[k], src + k * 4);
    dst[0].areaRooms = _gAkropolisStageWorldCollisionAreaRooms;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_stage/gAkropolisStageWorldCollisionResources", gAkropolisStageWorldCollisionResources, peDecodeArr_gAkropolisStageWorldCollisionResources);
#ifndef PE_DECODE_AreaTableSpriteView
#define PE_DECODE_AreaTableSpriteView
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
static void peDecode_AreaTableSpriteView(SpriteView** dst, const unsigned char* src)
{
    /* : pointer, set by the array's fixups */
}

#endif
static SpriteView* _gAkropolisStageAreaSpriteViews[20];
static void peDecodeArr_gAkropolisStageAreaSpriteViews(void* base, const unsigned char* src, size_t n)
{
    SpriteView** dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AreaTableSpriteView(&dst[k], src + k * 4);
    dst[0] = (void*)&gAkropolisSquareSpriteViews;
    dst[1] = (void*)&gAkropolisEastElevatorHallSpriteViews;
    dst[2] = (void*)&gAkropolisPatioSpriteViews;
    dst[3] = (void*)&gAkropolisCafeteriaSpriteViews;
    dst[4] = (void*)&gAkropolisPlazaSpriteViews;
    dst[5] = (void*)&gAkropolisSecurityRoomSpriteViews;
    dst[6] = (void*)&gAkropolisHallwaySpriteViews;
    dst[7] = (void*)&gAkropolisFountainSpriteViews;
    dst[8] = (void*)&gAkropolisForkedRoadSpriteViews;
    dst[9] = (void*)&gAkropolisObservatorySpriteViews;
    dst[10] = (void*)&gAkropolisPromenadeSpriteViews;
    dst[11] = (void*)&gAkropolisSanctuarySpriteViews;
    dst[12] = (void*)&gAkropolisRoofGardenSpriteViews;
    dst[13] = (void*)&gAkropolisBridgeSpriteViews;
    dst[14] = (void*)&gAkropolisFireEscapeSpriteViews;
    dst[15] = (void*)&gAkropolisHelicopterLandingPadSpriteViews;
    dst[16] = (void*)&gAkropolisWestElevatorHallSpriteViews;
    dst[17] = (void*)&gMistR18SpriteViews;
    dst[18] = (void*)&gMistParkingSpriteViews;
    dst[19] = (void*)&gMistShootingGallerySpriteViews;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_stage/_gAkropolisStageAreaSpriteViews", _gAkropolisStageAreaSpriteViews, peDecodeArr_gAkropolisStageAreaSpriteViews);
#ifndef PE_DECODE_SpriteAreaTable
#define PE_DECODE_SpriteAreaTable
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
static void peDecode_SpriteAreaTable(SpriteAreaTable* dst, const unsigned char* src)
{
    /* areaViews: pointer, set by the array's fixups */
}

#endif
SpriteAreaTable gAkropolisStageSpriteAreaTable;
static void peDecodeArr_gAkropolisStageSpriteAreaTable(void* base, const unsigned char* src, size_t n)
{
    SpriteAreaTable* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_SpriteAreaTable(&dst[k], src + k * 4);
    dst[0].areaViews = _gAkropolisStageAreaSpriteViews;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_stage/gAkropolisStageSpriteAreaTable", gAkropolisStageSpriteAreaTable, peDecodeArr_gAkropolisStageSpriteAreaTable);
#ifndef PE_DECODE_AreaTableDirectionWarpEntry
#define PE_DECODE_AreaTableDirectionWarpEntry
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
static void peDecode_AreaTableDirectionWarpEntry(DirectionWarpEntry** dst, const unsigned char* src)
{
    /* : pointer, set by the array's fixups */
}

#endif
DirectionWarpEntry* gAkropolisStageAreaWarpEntries[20];
static void peDecodeArr_gAkropolisStageAreaWarpEntries(void* base, const unsigned char* src, size_t n)
{
    DirectionWarpEntry** dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AreaTableDirectionWarpEntry(&dst[k], src + k * 4);
    dst[0] = (void*)&gAkropolisSquareWarpEntries;
    dst[1] = (void*)&gAkropolisEastElevatorHallWarpEntries;
    dst[2] = (void*)&gAkropolisPatioWarpEntries;
    dst[3] = (void*)&gAkropolisCafeteriaWarps;
    dst[4] = (void*)&gAkropolisPlazaWarpEntries;
    dst[5] = (void*)&gAkropolisSecurityRoomWarpEntries;
    dst[6] = (void*)&gAkropolisHallwayWarpEntries;
    dst[7] = (void*)&gAkropolisFountainWarpEntries;
    dst[8] = (void*)&gAkropolisForkedRoadWarpEntries;
    dst[9] = (void*)&gAkropolisObservatoryWarpEntries;
    dst[10] = (void*)&gAkropolisPromenadeWarpEntries;
    dst[11] = (void*)&gAkropolisSanctuaryWarpEntries;
    dst[12] = (void*)&gAkropolisRoofGardenWarpEntries;
    dst[13] = (void*)&gAkropolisBridgeWarpEntries;
    dst[14] = (void*)&gAkropolisFireEscapeWarpEntries;
    dst[15] = (void*)&gAkropolisHelicopterLandingPadWarps;
    dst[16] = (void*)&gAkropolisWestElevatorHallWarpEntries;
    dst[17] = (void*)&gMistR18WarpEntries;
    dst[18] = (void*)&gMistParkingWarpEntries;
    dst[19] = (void*)&gMistShootingGalleryWarpEntries;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_stage/gAkropolisStageAreaWarpEntries", gAkropolisStageAreaWarpEntries, peDecodeArr_gAkropolisStageAreaWarpEntries);
#ifndef PE_DECODE_AreaTableViewCount
#define PE_DECODE_AreaTableViewCount
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
static void peDecode_AreaTableViewCount(ViewCount** dst, const unsigned char* src)
{
    /* : pointer, set by the array's fixups */
}

#endif
static ViewCount* _gAkropolisStageAreaViewCounts[20];
static void peDecodeArr_gAkropolisStageAreaViewCounts(void* base, const unsigned char* src, size_t n)
{
    ViewCount** dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AreaTableViewCount(&dst[k], src + k * 4);
    dst[0] = (void*)&gAkropolisSquareViewCounts;
    dst[1] = (void*)&gAkropolisEastElevatorHallViewCounts;
    dst[2] = (void*)&gAkropolisPatioViewCounts;
    dst[3] = (void*)&gAkropolisCafeteriaViewCounts;
    dst[4] = (void*)&gAkropolisPlazaViewCounts;
    dst[5] = (void*)&gAkropolisSecurityRoomViewCounts;
    dst[6] = (void*)&gAkropolisHallwayViewCounts;
    dst[7] = (void*)&gAkropolisFountainViewCounts;
    dst[8] = (void*)&gAkropolisForkedRoadViewCounts;
    dst[9] = (void*)&gAkropolisObservatoryViewCounts;
    dst[10] = (void*)&gAkropolisPromenadeViewCounts;
    dst[11] = (void*)&gAkropolisSanctuaryViewCounts;
    dst[12] = (void*)&gAkropolisRoofGardenViewCounts;
    dst[13] = (void*)&gAkropolisBridgeViewCounts;
    dst[14] = (void*)&gAkropolisFireEscapeViewCounts;
    dst[15] = (void*)&gAkropolisHelicopterLandingPadViewCounts;
    dst[16] = (void*)&gAkropolisWestElevatorHallViewCounts;
    dst[17] = (void*)&gMistR18ViewCounts;
    dst[18] = (void*)&gMistParkingViewCounts;
    dst[19] = (void*)&gMistShootingGalleryViewCounts;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_stage/_gAkropolisStageAreaViewCounts", _gAkropolisStageAreaViewCounts, peDecodeArr_gAkropolisStageAreaViewCounts);
#ifndef PE_DECODE_ViewCountTable
#define PE_DECODE_ViewCountTable
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
static void peDecode_ViewCountTable(ViewCountTable* dst, const unsigned char* src)
{
    /* viewCounts: pointer, set by the array's fixups */
}

#endif
ViewCountTable gAkropolisStageViewCountTable;
static void peDecodeArr_gAkropolisStageViewCountTable(void* base, const unsigned char* src, size_t n)
{
    ViewCountTable* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_ViewCountTable(&dst[k], src + k * 4);
    dst[0].viewCounts = _gAkropolisStageAreaViewCounts;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_stage/gAkropolisStageViewCountTable", gAkropolisStageViewCountTable, peDecodeArr_gAkropolisStageViewCountTable);
#ifndef PE_DECODE_AreaTableViewCamera
#define PE_DECODE_AreaTableViewCamera
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
static void peDecode_AreaTableViewCamera(ViewCamera** dst, const unsigned char* src)
{
    /* : pointer, set by the array's fixups */
}

#endif
static ViewCamera* _gAkropolisStageAreaCameras[20];
static void peDecodeArr_gAkropolisStageAreaCameras(void* base, const unsigned char* src, size_t n)
{
    ViewCamera** dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AreaTableViewCamera(&dst[k], src + k * 4);
    dst[0] = (void*)&gAkropolisSquareViewCameras;
    dst[1] = (void*)&gAkropolisEastElevatorHallViewCameras;
    dst[2] = (void*)&gAkropolisPatioViewCameras;
    dst[3] = (void*)&gAkropolisCafeteriaViewCameras;
    dst[4] = (void*)&gAkropolisPlazaViewCameras;
    dst[5] = (void*)&gAkropolisSecurityRoomViewCameras;
    dst[6] = (void*)&gAkropolisHallwayViewCameras;
    dst[7] = (void*)&gAkropolisFountainViewCameras;
    dst[8] = (void*)&gAkropolisForkedRoadViewCameras;
    dst[9] = (void*)&gAkropolisObservatoryViewCameras;
    dst[10] = (void*)&gAkropolisPromenadeViewCameras;
    dst[11] = (void*)&gAkropolisSanctuaryViewCameras;
    dst[12] = (void*)&gAkropolisRoofGardenViewCameras;
    dst[13] = (void*)&gAkropolisBridgeViewCameras;
    dst[14] = (void*)&gAkropolisFireEscapeViewCameras;
    dst[15] = (void*)&gAkropolisHelicopterLandingPadViewCameras;
    dst[16] = (void*)&gAkropolisWestElevatorHallViewCameras;
    dst[17] = (void*)&gMistR18ViewCameras;
    dst[18] = (void*)&gMistParkingViewCameras;
    dst[19] = (void*)&gMistShootingGalleryViewCameras;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_stage/_gAkropolisStageAreaCameras", _gAkropolisStageAreaCameras, peDecodeArr_gAkropolisStageAreaCameras);
#ifndef PE_DECODE_ViewCameraTable
#define PE_DECODE_ViewCameraTable
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
static void peDecode_ViewCameraTable(ViewCameraTable* dst, const unsigned char* src)
{
    /* cameras: pointer, set by the array's fixups */
}

#endif
ViewCameraTable gAkropolisStageViewCameraTable;
static void peDecodeArr_gAkropolisStageViewCameraTable(void* base, const unsigned char* src, size_t n)
{
    ViewCameraTable* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_ViewCameraTable(&dst[k], src + k * 4);
    dst[0].cameras = _gAkropolisStageAreaCameras;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_stage/gAkropolisStageViewCameraTable", gAkropolisStageViewCameraTable, peDecodeArr_gAkropolisStageViewCameraTable);
#ifndef PE_DECODE_AreaTableViewMapPtr
#define PE_DECODE_AreaTableViewMapPtr
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
static void peDecode_AreaTableViewMapPtr(u8*** dst, const unsigned char* src)
{
    /* : pointer, set by the array's fixups */
}

#endif
static u8** _gAkropolisStageAreaViewMaps[20];
static void peDecodeArr_gAkropolisStageAreaViewMaps(void* base, const unsigned char* src, size_t n)
{
    u8*** dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AreaTableViewMapPtr(&dst[k], src + k * 4);
    dst[0] = (void*)&gAkropolisSquareViewMaps;
    dst[1] = (void*)&gAkropolisEastElevatorHallViewMaps;
    dst[2] = (void*)&gAkropolisPatioViewMaps;
    dst[3] = (void*)&gAkropolisCafeteriaViewMaps;
    dst[4] = (void*)&gAkropolisPlazaViewMaps;
    dst[5] = (void*)&gAkropolisSecurityRoomViewMaps;
    dst[6] = (void*)&gAkropolisHallwayViewMaps;
    dst[7] = (void*)&gAkropolisFountainViewMaps;
    dst[8] = (void*)&gAkropolisForkedRoadViewMaps;
    dst[9] = (void*)&gAkropolisObservatoryViewMaps;
    dst[10] = (void*)&gAkropolisPromenadeViewMaps;
    dst[11] = (void*)&gAkropolisSanctuaryViewMaps;
    dst[12] = (void*)&gAkropolisRoofGardenViewMaps;
    dst[13] = (void*)&gAkropolisBridgeViewMaps;
    dst[14] = (void*)&gAkropolisFireEscapeViewMaps;
    dst[15] = (void*)&gAkropolisHelicopterLandingPadViewMaps;
    dst[16] = (void*)&gAkropolisWestElevatorHallViewMaps;
    dst[17] = (void*)&gMistR18ViewMaps;
    dst[18] = (void*)&gMistParkingViewMaps;
    dst[19] = (void*)&gMistShootingGalleryViewMaps;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_stage/_gAkropolisStageAreaViewMaps", _gAkropolisStageAreaViewMaps, peDecodeArr_gAkropolisStageAreaViewMaps);
#ifndef PE_DECODE_ViewIndexTable
#define PE_DECODE_ViewIndexTable
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
static void peDecode_ViewIndexTable(ViewIndexTable* dst, const unsigned char* src)
{
    /* viewMaps: pointer, set by the array's fixups */
}

#endif
ViewIndexTable gAkropolisStageViewIndexTable;
static void peDecodeArr_gAkropolisStageViewIndexTable(void* base, const unsigned char* src, size_t n)
{
    ViewIndexTable* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_ViewIndexTable(&dst[k], src + k * 4);
    dst[0].viewMaps = _gAkropolisStageAreaViewMaps;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_stage/gAkropolisStageViewIndexTable", gAkropolisStageViewIndexTable, peDecodeArr_gAkropolisStageViewIndexTable);
#ifndef PE_DECODE_AreaTableSurfacePtr
#define PE_DECODE_AreaTableSurfacePtr
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
static void peDecode_AreaTableSurfacePtr(WorldCollisionSurfaceProperties*** dst, const unsigned char* src)
{
    /* : pointer, set by the array's fixups */
}

#endif
WorldCollisionSurfaceProperties** gAkropolisStageSurfacePropertiesByArea[20];
static void peDecodeArr_gAkropolisStageSurfacePropertiesByArea(void* base, const unsigned char* src, size_t n)
{
    WorldCollisionSurfaceProperties*** dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AreaTableSurfacePtr(&dst[k], src + k * 4);
    dst[0] = (void*)&gAkropolisSquareSurfacePropertiesByClass;
    dst[1] = (void*)&gAkropolisEastElevatorHallSurfacePropertiesByClass;
    dst[2] = (void*)&gAkropolisPatioSurfacePropertiesByClass;
    dst[3] = (void*)&gAkropolisCafeteriaSurfacePropertiesByClass;
    dst[4] = (void*)&gAkropolisPlazaSurfacePropertiesByClass;
    dst[5] = (void*)&gAkropolisSecurityRoomSurfacePropertiesByClass;
    dst[6] = (void*)&gAkropolisHallwaySurfacePropertiesByClass;
    dst[7] = (void*)&gAkropolisFountainSurfacePropertiesByClass;
    dst[8] = (void*)&gAkropolisForkedRoadSurfacePropertiesByClass;
    dst[9] = (void*)&gAkropolisObservatorySurfacePropertiesByClass;
    dst[10] = (void*)&gAkropolisPromenadeSurfacePropertiesByClass;
    dst[11] = (void*)&gAkropolisSanctuarySurfacePropertiesByClass;
    dst[12] = (void*)&gAkropolisRoofGardenSurfacePropertiesByClass;
    dst[13] = (void*)&gAkropolisBridgeSurfacePropertiesByClass;
    dst[14] = (void*)&gAkropolisFireEscapeSurfacePropertiesByClass;
    dst[15] = (void*)&gAkropolisHelicopterLandingPadSurfacePropertiesByClass;
    dst[16] = (void*)&gAkropolisWestElevatorHallSurfacePropertiesByClass;
    dst[17] = (void*)&gMistR18SurfacePropertiesByClass;
    dst[18] = (void*)&gMistParkingSurfacePropertiesByClass;
    dst[19] = (void*)&gMistShootingGallerySurfacePropertiesByClass;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_stage/gAkropolisStageSurfacePropertiesByArea", gAkropolisStageSurfacePropertiesByArea, peDecodeArr_gAkropolisStageSurfacePropertiesByArea);
