#include "gameplay/area.h"
#include "gameplay/scene_runtime.h"
#include "../src/gameplay/loading.h"
#include "main/fs.h"
#include "main/mc.h"
#include <stdio.h>
#include <stdlib.h>

#define CHECK(x) do { if (!(x)) { fprintf(stderr, "line %d: %s\n", __LINE__, #x); exit(1); } } while (0)
McSaveData gMcSaveData[MEMORY_CARD_SAVE_COUNT];
static AreaVariant* selected;
static unsigned queued;
static u16 idle;
static u8 lastIndex, lastGroup, lastHundreds;
extern AreaResource* _gLoadingAreaResourceCursor;
extern AreaPlacement* _gLoadingAreaPlacementCursor;
AreaVariant* areaGetVariant(const GameLocationKey* key)
{
    CHECK(key == &gMcSaveData[MEMORY_CARD_SAVE_LIVE].state.location);
    return selected;
}
u16 cdCmdIsIdle(void) { return idle; }
s32 cdCmdEnqueue(s32 command, const void* key, const void* args)
{
    CHECK(command == CD_COMMAND_LOAD_FILE);
    lastIndex = ((const u8*)key)[0];
    lastGroup = ((const u8*)key)[2];
    lastHundreds = ((const u8*)args)[0];
    ++queued;
    return 0;
}
static void reset(AreaVariant* layout)
{
    selected = layout;
    queued = 0;
    idle = 1;
    gLoadingAreaBaseResourcePhase = LOADING_AREA_INIT;
    gLoadingAreaPlacementFilePhase = LOADING_AREA_INIT;
}
int main(void)
{
    AreaPlacement emptyPlacements[] = {{.entryId = AREA_PLACEMENT_END}};
    AreaResource emptyResources[] = {{.entryId = AREA_PLACEMENT_END}};
    AreaVariant empty = {.placements = emptyPlacements, .resources = emptyResources};
    reset(NULL);
    CHECK(loadingPollAreaBaseResources() == 1);
    CHECK(_gLoadingAreaResourceCursor == NULL);
    CHECK(loadingPollAreaPlacementFiles() == 1);
    CHECK(_gLoadingAreaPlacementCursor == NULL && queued == 0);
    reset(&empty);
    CHECK(loadingPollAreaBaseResources() == 1);
    CHECK(loadingPollAreaPlacementFiles() == 1 && queued == 0);
    empty.resources = NULL;
    reset(&empty);
    CHECK(loadingPollAreaBaseResources() == 1);
    CHECK(loadingPollAreaPlacementFiles() == 1 && queued == 0);

    AreaResource resources[] = {{.entryId = 1, .fileNumber = 407, .fileGroupIndex = 0}, {.entryId = AREA_PLACEMENT_END}};
    AreaPlacement placements[] = {{.entryId = 1, .fileIdLow = 3}, {.entryId = AREA_PLACEMENT_END}};
    AreaVariant live = {.placements = placements, .resources = resources};
    reset(&live);
    CHECK(loadingPollAreaBaseResources() == 0 && queued == 1);
    CHECK(lastIndex == 0 && lastGroup == 14 && lastHundreds == 7);
    idle = 0;
    CHECK(loadingPollAreaBaseResources() == 0 && queued == 1);
    idle = 1;
    CHECK(loadingPollAreaBaseResources() == 0);
    CHECK(loadingPollAreaBaseResources() == 1 && queued == 1);
    CHECK(loadingPollAreaPlacementFiles() == 0 && queued == 2);
    CHECK(lastIndex == 3 && lastGroup == 14 && lastHundreds == 7);
    CHECK(loadingPollAreaPlacementFiles() == 0);
    CHECK(loadingPollAreaPlacementFiles() == 1 && queued == 2);
    puts("area resources: absent/empty layouts, base loads, extra files and CD waits OK");
}
