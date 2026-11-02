#include "../src/gameplay/player_actor.h"
#include <stdio.h>
#include <stdlib.h>
#define CHECK(x) do { if (!(x)) { fprintf(stderr,"line %d: %s\n",__LINE__,#x); exit(1); } } while (0)
int main(void)
{
    GameActor actor = {0}; Task task = {0}; task.work = &actor;
    WorldTargetNode a = {0}, b = {0};
    a.state.parts.flags = 0xa5; b.state.parts.flags = 0x5a;
    actor.aimTrackingState = 7;
    playerActorSetLockTarget(&task, NULL);
    CHECK(actor.targetNode == NULL);
    playerActorSetLockTarget(&task, &a);
    CHECK(actor.targetNode == &a && a.state.parts.targeted == 1);
    playerActorSetLockTarget(&task, &b);
    CHECK(actor.targetNode == &b && !a.state.parts.targeted && b.state.parts.targeted == 1);
    b.state.parts.targeted = 0;
    playerActorSetLockTarget(&task, &b);
    CHECK(b.state.parts.targeted == 1);
    playerActorSetLockTarget(&task, NULL);
    CHECK(actor.targetNode == NULL && !b.state.parts.targeted);
    CHECK(a.state.parts.flags == 0xa5 && b.state.parts.flags == 0x5a);
    CHECK(actor.aimTrackingState == 7);
    playerActorSetLockTarget(&task, &a);
    CHECK(actor.targetNode == &a && a.state.parts.targeted == 1);
    puts("player target: acquisition, cycling, empty scans and reacquisition OK");
}
