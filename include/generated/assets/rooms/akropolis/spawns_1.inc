/* rooms/akropolis/stage: written from its room instance by tools/buildsteps/gen_room_inc.py. */

#include "types.h"
#include "gameplay/area_flags.h"
#include "gameplay/item_menu.h"
#include "stages/akropolis/rooms/cafeteria.h"
#include "stages/akropolis/rooms/hallway.h"
#include "stages/akropolis/rooms/roof_garden.h"
#include "stages/akropolis/rooms/sanctuary.h"
#include "stages/akropolis/rooms/security_room.h"

#ifndef PE_DECODE_AreaObjectSpawn
#define PE_DECODE_AreaObjectSpawn
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
static void peDecode_AreaObjectSpawn(AreaObjectSpawn* dst, const unsigned char* src)
{
    { uint16_t v; memcpy(&v, src + 0, 2); dst->kind = v; }
    { uint16_t v; memcpy(&v, src + 4, 2); dst->taskDesc.header.fields.flags = v; }
    { uint16_t v; memcpy(&v, src + 6, 2); dst->taskDesc.header.fields.priority = v; }
    /* taskDesc.callback: pointer, set by the array's fixups */
    { uint32_t v; memcpy(&v, src + 12, 4); dst->taskDesc.data.value = v; }
}

#endif
static AreaObjectSpawn _gAkropolisStageSquareObjectSpawns[1];
static void peDecodeArr_gAkropolisStageSquareObjectSpawns(void* base, const unsigned char* src, size_t n)
{
    AreaObjectSpawn* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AreaObjectSpawn(&dst[k], src + k * 16);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_stage/_gAkropolisStageSquareObjectSpawns", _gAkropolisStageSquareObjectSpawns, peDecodeArr_gAkropolisStageSquareObjectSpawns);
#ifndef PE_DECODE_AreaObjectSpawn
#define PE_DECODE_AreaObjectSpawn
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
static void peDecode_AreaObjectSpawn(AreaObjectSpawn* dst, const unsigned char* src)
{
    { uint16_t v; memcpy(&v, src + 0, 2); dst->kind = v; }
    { uint16_t v; memcpy(&v, src + 4, 2); dst->taskDesc.header.fields.flags = v; }
    { uint16_t v; memcpy(&v, src + 6, 2); dst->taskDesc.header.fields.priority = v; }
    /* taskDesc.callback: pointer, set by the array's fixups */
    { uint32_t v; memcpy(&v, src + 12, 4); dst->taskDesc.data.value = v; }
}

#endif
static AreaObjectSpawn _gAkropolisStageEastElevatorHallObjectSpawns[1];
static void peDecodeArr_gAkropolisStageEastElevatorHallObjectSpawns(void* base, const unsigned char* src, size_t n)
{
    AreaObjectSpawn* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AreaObjectSpawn(&dst[k], src + k * 16);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_stage/_gAkropolisStageEastElevatorHallObjectSpawns", _gAkropolisStageEastElevatorHallObjectSpawns, peDecodeArr_gAkropolisStageEastElevatorHallObjectSpawns);
#ifndef PE_DECODE_AreaObjectSpawn
#define PE_DECODE_AreaObjectSpawn
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
static void peDecode_AreaObjectSpawn(AreaObjectSpawn* dst, const unsigned char* src)
{
    { uint16_t v; memcpy(&v, src + 0, 2); dst->kind = v; }
    { uint16_t v; memcpy(&v, src + 4, 2); dst->taskDesc.header.fields.flags = v; }
    { uint16_t v; memcpy(&v, src + 6, 2); dst->taskDesc.header.fields.priority = v; }
    /* taskDesc.callback: pointer, set by the array's fixups */
    { uint32_t v; memcpy(&v, src + 12, 4); dst->taskDesc.data.value = v; }
}

#endif
static AreaObjectSpawn _gAkropolisStageCafeteriaObjectSpawns[3];
static void peDecodeArr_gAkropolisStageCafeteriaObjectSpawns(void* base, const unsigned char* src, size_t n)
{
    AreaObjectSpawn* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AreaObjectSpawn(&dst[k], src + k * 16);
    dst[0].taskDesc.callback = akropolisCafeteriaStimPickupTask;
    dst[0].taskDesc.data.model = &gAkropolisCafeteriaStimPickupModel;
    dst[1].taskDesc.callback = akropolisCafeteriaMendelPickupTask;
    dst[1].taskDesc.data.model = &gAkropolisCafeteriaMendelJournalModel;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_stage/_gAkropolisStageCafeteriaObjectSpawns", _gAkropolisStageCafeteriaObjectSpawns, peDecodeArr_gAkropolisStageCafeteriaObjectSpawns);
#ifndef PE_DECODE_AreaObjectSpawn
#define PE_DECODE_AreaObjectSpawn
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
static void peDecode_AreaObjectSpawn(AreaObjectSpawn* dst, const unsigned char* src)
{
    { uint16_t v; memcpy(&v, src + 0, 2); dst->kind = v; }
    { uint16_t v; memcpy(&v, src + 4, 2); dst->taskDesc.header.fields.flags = v; }
    { uint16_t v; memcpy(&v, src + 6, 2); dst->taskDesc.header.fields.priority = v; }
    /* taskDesc.callback: pointer, set by the array's fixups */
    { uint32_t v; memcpy(&v, src + 12, 4); dst->taskDesc.data.value = v; }
}

#endif
static AreaObjectSpawn _gAkropolisStageSecurityRoomObjectSpawns[2];
static void peDecodeArr_gAkropolisStageSecurityRoomObjectSpawns(void* base, const unsigned char* src, size_t n)
{
    AreaObjectSpawn* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AreaObjectSpawn(&dst[k], src + k * 16);
    dst[0].taskDesc.callback = itemPickupContainerLidTask;
    dst[0].taskDesc.data.model = &gAkropolisSecurityRoomItemBoxModel;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_stage/_gAkropolisStageSecurityRoomObjectSpawns", _gAkropolisStageSecurityRoomObjectSpawns, peDecodeArr_gAkropolisStageSecurityRoomObjectSpawns);
#ifndef PE_DECODE_AreaObjectSpawn
#define PE_DECODE_AreaObjectSpawn
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
static void peDecode_AreaObjectSpawn(AreaObjectSpawn* dst, const unsigned char* src)
{
    { uint16_t v; memcpy(&v, src + 0, 2); dst->kind = v; }
    { uint16_t v; memcpy(&v, src + 4, 2); dst->taskDesc.header.fields.flags = v; }
    { uint16_t v; memcpy(&v, src + 6, 2); dst->taskDesc.header.fields.priority = v; }
    /* taskDesc.callback: pointer, set by the array's fixups */
    { uint32_t v; memcpy(&v, src + 12, 4); dst->taskDesc.data.value = v; }
}

#endif
static AreaObjectSpawn _gAkropolisStageHallwayObjectSpawns[2];
static void peDecodeArr_gAkropolisStageHallwayObjectSpawns(void* base, const unsigned char* src, size_t n)
{
    AreaObjectSpawn* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AreaObjectSpawn(&dst[k], src + k * 16);
    dst[0].taskDesc.callback = akropolisHallwayBlueKeyPickupTask;
    dst[0].taskDesc.data.model = &gAkropolisHallwayBlueKeyPickupModel;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_stage/_gAkropolisStageHallwayObjectSpawns", _gAkropolisStageHallwayObjectSpawns, peDecodeArr_gAkropolisStageHallwayObjectSpawns);
#ifndef PE_DECODE_AreaObjectSpawn
#define PE_DECODE_AreaObjectSpawn
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
static void peDecode_AreaObjectSpawn(AreaObjectSpawn* dst, const unsigned char* src)
{
    { uint16_t v; memcpy(&v, src + 0, 2); dst->kind = v; }
    { uint16_t v; memcpy(&v, src + 4, 2); dst->taskDesc.header.fields.flags = v; }
    { uint16_t v; memcpy(&v, src + 6, 2); dst->taskDesc.header.fields.priority = v; }
    /* taskDesc.callback: pointer, set by the array's fixups */
    { uint32_t v; memcpy(&v, src + 12, 4); dst->taskDesc.data.value = v; }
}

#endif
static AreaObjectSpawn _gAkropolisStageFountainObjectSpawns[1];
static void peDecodeArr_gAkropolisStageFountainObjectSpawns(void* base, const unsigned char* src, size_t n)
{
    AreaObjectSpawn* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AreaObjectSpawn(&dst[k], src + k * 16);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_stage/_gAkropolisStageFountainObjectSpawns", _gAkropolisStageFountainObjectSpawns, peDecodeArr_gAkropolisStageFountainObjectSpawns);
#ifndef PE_DECODE_AreaObjectSpawn
#define PE_DECODE_AreaObjectSpawn
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
static void peDecode_AreaObjectSpawn(AreaObjectSpawn* dst, const unsigned char* src)
{
    { uint16_t v; memcpy(&v, src + 0, 2); dst->kind = v; }
    { uint16_t v; memcpy(&v, src + 4, 2); dst->taskDesc.header.fields.flags = v; }
    { uint16_t v; memcpy(&v, src + 6, 2); dst->taskDesc.header.fields.priority = v; }
    /* taskDesc.callback: pointer, set by the array's fixups */
    { uint32_t v; memcpy(&v, src + 12, 4); dst->taskDesc.data.value = v; }
}

#endif
static AreaObjectSpawn _gAkropolisStageForkedRoadObjectSpawns[1];
static void peDecodeArr_gAkropolisStageForkedRoadObjectSpawns(void* base, const unsigned char* src, size_t n)
{
    AreaObjectSpawn* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AreaObjectSpawn(&dst[k], src + k * 16);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_stage/_gAkropolisStageForkedRoadObjectSpawns", _gAkropolisStageForkedRoadObjectSpawns, peDecodeArr_gAkropolisStageForkedRoadObjectSpawns);
#ifndef PE_DECODE_AreaObjectSpawn
#define PE_DECODE_AreaObjectSpawn
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
static void peDecode_AreaObjectSpawn(AreaObjectSpawn* dst, const unsigned char* src)
{
    { uint16_t v; memcpy(&v, src + 0, 2); dst->kind = v; }
    { uint16_t v; memcpy(&v, src + 4, 2); dst->taskDesc.header.fields.flags = v; }
    { uint16_t v; memcpy(&v, src + 6, 2); dst->taskDesc.header.fields.priority = v; }
    /* taskDesc.callback: pointer, set by the array's fixups */
    { uint32_t v; memcpy(&v, src + 12, 4); dst->taskDesc.data.value = v; }
}

#endif
static AreaObjectSpawn _gAkropolisStageObservatoryObjectSpawns[1];
static void peDecodeArr_gAkropolisStageObservatoryObjectSpawns(void* base, const unsigned char* src, size_t n)
{
    AreaObjectSpawn* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AreaObjectSpawn(&dst[k], src + k * 16);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_stage/_gAkropolisStageObservatoryObjectSpawns", _gAkropolisStageObservatoryObjectSpawns, peDecodeArr_gAkropolisStageObservatoryObjectSpawns);
#ifndef PE_DECODE_AreaObjectSpawn
#define PE_DECODE_AreaObjectSpawn
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
static void peDecode_AreaObjectSpawn(AreaObjectSpawn* dst, const unsigned char* src)
{
    { uint16_t v; memcpy(&v, src + 0, 2); dst->kind = v; }
    { uint16_t v; memcpy(&v, src + 4, 2); dst->taskDesc.header.fields.flags = v; }
    { uint16_t v; memcpy(&v, src + 6, 2); dst->taskDesc.header.fields.priority = v; }
    /* taskDesc.callback: pointer, set by the array's fixups */
    { uint32_t v; memcpy(&v, src + 12, 4); dst->taskDesc.data.value = v; }
}

#endif
static AreaObjectSpawn _gAkropolisStagePromenadeObjectSpawns[1];
static void peDecodeArr_gAkropolisStagePromenadeObjectSpawns(void* base, const unsigned char* src, size_t n)
{
    AreaObjectSpawn* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AreaObjectSpawn(&dst[k], src + k * 16);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_stage/_gAkropolisStagePromenadeObjectSpawns", _gAkropolisStagePromenadeObjectSpawns, peDecodeArr_gAkropolisStagePromenadeObjectSpawns);
#ifndef PE_DECODE_AreaObjectSpawn
#define PE_DECODE_AreaObjectSpawn
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
static void peDecode_AreaObjectSpawn(AreaObjectSpawn* dst, const unsigned char* src)
{
    { uint16_t v; memcpy(&v, src + 0, 2); dst->kind = v; }
    { uint16_t v; memcpy(&v, src + 4, 2); dst->taskDesc.header.fields.flags = v; }
    { uint16_t v; memcpy(&v, src + 6, 2); dst->taskDesc.header.fields.priority = v; }
    /* taskDesc.callback: pointer, set by the array's fixups */
    { uint32_t v; memcpy(&v, src + 12, 4); dst->taskDesc.data.value = v; }
}

#endif
static AreaObjectSpawn _gAkropolisStageSanctuaryObjectSpawns[3];
static void peDecodeArr_gAkropolisStageSanctuaryObjectSpawns(void* base, const unsigned char* src, size_t n)
{
    AreaObjectSpawn* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AreaObjectSpawn(&dst[k], src + k * 16);
    dst[0].taskDesc.callback = akropolisSanctuaryItemVisibilityTask;
    dst[0].taskDesc.data.model = &gAkropolisSanctuaryRedKeyPickupModel;
    dst[1].taskDesc.callback = itemPickupContainerLidTask;
    dst[1].taskDesc.data.model = &gAkropolisSanctuaryItemBoxModel;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_stage/_gAkropolisStageSanctuaryObjectSpawns", _gAkropolisStageSanctuaryObjectSpawns, peDecodeArr_gAkropolisStageSanctuaryObjectSpawns);
#ifndef PE_DECODE_AreaObjectSpawn
#define PE_DECODE_AreaObjectSpawn
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
static void peDecode_AreaObjectSpawn(AreaObjectSpawn* dst, const unsigned char* src)
{
    { uint16_t v; memcpy(&v, src + 0, 2); dst->kind = v; }
    { uint16_t v; memcpy(&v, src + 4, 2); dst->taskDesc.header.fields.flags = v; }
    { uint16_t v; memcpy(&v, src + 6, 2); dst->taskDesc.header.fields.priority = v; }
    /* taskDesc.callback: pointer, set by the array's fixups */
    { uint32_t v; memcpy(&v, src + 12, 4); dst->taskDesc.data.value = v; }
}

#endif
static AreaObjectSpawn _gAkropolisStageRoofGardenObjectSpawns[2];
static void peDecodeArr_gAkropolisStageRoofGardenObjectSpawns(void* base, const unsigned char* src, size_t n)
{
    AreaObjectSpawn* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AreaObjectSpawn(&dst[k], src + k * 16);
    dst[0].taskDesc.callback = akropolisRoofGardenPickupModelTask;
    dst[0].taskDesc.data.model = &gAkropolisRoofGardenArmoryCardkeyPickupModel;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_stage/_gAkropolisStageRoofGardenObjectSpawns", _gAkropolisStageRoofGardenObjectSpawns, peDecodeArr_gAkropolisStageRoofGardenObjectSpawns);
#ifndef PE_DECODE_AreaObjectSpawn
#define PE_DECODE_AreaObjectSpawn
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
static void peDecode_AreaObjectSpawn(AreaObjectSpawn* dst, const unsigned char* src)
{
    { uint16_t v; memcpy(&v, src + 0, 2); dst->kind = v; }
    { uint16_t v; memcpy(&v, src + 4, 2); dst->taskDesc.header.fields.flags = v; }
    { uint16_t v; memcpy(&v, src + 6, 2); dst->taskDesc.header.fields.priority = v; }
    /* taskDesc.callback: pointer, set by the array's fixups */
    { uint32_t v; memcpy(&v, src + 12, 4); dst->taskDesc.data.value = v; }
}

#endif
static AreaObjectSpawn _gAkropolisStageFireEscapeObjectSpawns[1];
static void peDecodeArr_gAkropolisStageFireEscapeObjectSpawns(void* base, const unsigned char* src, size_t n)
{
    AreaObjectSpawn* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AreaObjectSpawn(&dst[k], src + k * 16);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_stage/_gAkropolisStageFireEscapeObjectSpawns", _gAkropolisStageFireEscapeObjectSpawns, peDecodeArr_gAkropolisStageFireEscapeObjectSpawns);
#ifndef PE_DECODE_AreaObjectSpawn
#define PE_DECODE_AreaObjectSpawn
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
static void peDecode_AreaObjectSpawn(AreaObjectSpawn* dst, const unsigned char* src)
{
    { uint16_t v; memcpy(&v, src + 0, 2); dst->kind = v; }
    { uint16_t v; memcpy(&v, src + 4, 2); dst->taskDesc.header.fields.flags = v; }
    { uint16_t v; memcpy(&v, src + 6, 2); dst->taskDesc.header.fields.priority = v; }
    /* taskDesc.callback: pointer, set by the array's fixups */
    { uint32_t v; memcpy(&v, src + 12, 4); dst->taskDesc.data.value = v; }
}

#endif
static AreaObjectSpawn _gAkropolisStageWestElevatorHallObjectSpawns[1];
static void peDecodeArr_gAkropolisStageWestElevatorHallObjectSpawns(void* base, const unsigned char* src, size_t n)
{
    AreaObjectSpawn* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AreaObjectSpawn(&dst[k], src + k * 16);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_stage/_gAkropolisStageWestElevatorHallObjectSpawns", _gAkropolisStageWestElevatorHallObjectSpawns, peDecodeArr_gAkropolisStageWestElevatorHallObjectSpawns);
#ifndef PE_DECODE_AreaObjectSpawn
#define PE_DECODE_AreaObjectSpawn
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
static void peDecode_AreaObjectSpawn(AreaObjectSpawn* dst, const unsigned char* src)
{
    { uint16_t v; memcpy(&v, src + 0, 2); dst->kind = v; }
    { uint16_t v; memcpy(&v, src + 4, 2); dst->taskDesc.header.fields.flags = v; }
    { uint16_t v; memcpy(&v, src + 6, 2); dst->taskDesc.header.fields.priority = v; }
    /* taskDesc.callback: pointer, set by the array's fixups */
    { uint32_t v; memcpy(&v, src + 12, 4); dst->taskDesc.data.value = v; }
}

#endif
static AreaObjectSpawn _gAkropolisStageMistParkingObjectSpawns[1];
static void peDecodeArr_gAkropolisStageMistParkingObjectSpawns(void* base, const unsigned char* src, size_t n)
{
    AreaObjectSpawn* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_AreaObjectSpawn(&dst[k], src + k * 16);

}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/akropolis_stage/_gAkropolisStageMistParkingObjectSpawns", _gAkropolisStageMistParkingObjectSpawns, peDecodeArr_gAkropolisStageMistParkingObjectSpawns);
