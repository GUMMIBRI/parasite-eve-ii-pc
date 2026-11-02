/* Native overlay re-entry must restore the fountain's extra climb trigger. */
#include "port/gpu_len.h"
#include "port/room_collision.h"
#include "../src/stages/akropolis/rooms/fountain/fountain_water.c"
#include <stdio.h>
#include <stdlib.h>
#define CHECK(x) do { if (!(x)) { fprintf(stderr, "line %d: %s\n", __LINE__, #x); exit(1); } } while (0)
GfxCoord gGfxViewCoord;
WorldCollisionTrigger* gWorldCollisionViewBoundaryListHead;
void Psyz_PadsOverride(int p, char* f, int n) { (void)p; (void)f; (void)n; }
static void enter(void)
{
    /* Production native room loading retires old heads and resets only the
     * incoming room's ordinary arrays; the climb is a separate static record. */
    gWorldCollisionActionTriggerListHead = NULL;
    WorldCollisionRoomResources room = {.actionTriggers = _gAkropolisFountainActionTriggers};
    peResetRoomCollisionResources(&room);
    for (unsigned i = 0; i < 9; ++i)
        worldCollisionLinkTrigger(WORLD_COLLISION_TRIGGER_LIST_ACTION, &_gAkropolisFountainActionTriggers[i]);
    akropolisFountainEnableClimbTrigger();
}
static void check(void)
{
    WorldCollisionTrigger** incoming = &gWorldCollisionActionTriggerListHead;
    unsigned count = 0, climbs = 0;
    for (WorldCollisionTrigger* node = *incoming; node; node = node->next) {
        CHECK(++count <= 9);
        CHECK(node->prevLink == incoming);
        CHECK(node != &_gAkropolisFountainActionTriggers[5]);
        climbs += node == &_gAkropolisFountainClimbTrigger;
        incoming = &node->next;
    }
    CHECK(count == 9 && climbs == 1);
    CHECK(_gAkropolisFountainClimbTrigger.flags & WORLD_COLLISION_TRIGGER_ENABLED);
    CHECK(_gAkropolisFountainClimbTrigger.origin.vx == 2447);
    CHECK(_gAkropolisFountainClimbTrigger.origin.vz == -4713);
}
int main(void)
{
    enter(); check();
    akropolisFountainEnableClimbTrigger(); check();
    enter(); check();
    enter(); check();
    puts("Fountain climb trigger: replacement, repeated enable and native room re-entry OK");
    return 0;
}
