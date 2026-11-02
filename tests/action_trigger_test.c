#include "../src/gameplay/world_collision.h"
#include "../src/gameplay/collision.h"
#include "main/scratch.h"
#include "port/room_collision.h"
#include "gameplay/world_collision.h"
#include "assets/rooms/akropolis/plaza/declarations.inc"
#include "assets/rooms/akropolis/plaza/action_triggers.inc"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
_Alignas(void*) u8 gHostScratchpad[0x400];
s32 gWorldCollisionActionHitClearingEnabled;
WorldCollisionFaceEdge gWorldCollisionFaceEdges[5] = {{2,1},{1,0},{0,2},{2,3},{3,1}};
void Psyz_PadsOverride(int p,char*f,int n){(void)p;(void)f;(void)n;}
static void identity(MATRIX* m) { memset(m,0,sizeof *m);m->m[0][0]=m->m[1][1]=m->m[2][2]=4096; }
int main(void)
{
    GfxCoord root={0},view={0};identity(&view.workm);
    root.coord.m[0][0]=201;root.coord.m[0][2]=-4091;root.coord.m[1][1]=4096;root.coord.m[2][0]=4091;root.coord.m[2][2]=201;
    root.coord.t[0]=-8800;root.coord.t[1]=130;root.coord.t[2]=-3078;root.workm=root.coord;
    WorldCollisionBody body={0};body.coord=&root;body.pos.vy=-300;body.radius=300;
    WorldCollisionTrigger trigger={0};trigger.coord=&view;
    trigger.origin=(SVECTOR){-8784,-48,-2912,0};
    trigger.vertices[0]=(SVECTOR){-467,0,-778,0};trigger.vertices[1]=(SVECTOR){462,0,-768,0};
    trigger.vertices[2]=(SVECTOR){-461,0,768,0};trigger.vertices[3]=(SVECTOR){469,0,778,0};
    trigger.normal=(SVECTOR){0,4105,0,0};trigger.facingNormal=(SVECTOR){4092,0,-115,0};trigger.radius=907;trigger.flags=2;
    *SCRATCH_STACK_CURSOR_SLOT=(void*)SCRATCH_STACK_CURSOR_SLOT;
    worldCollisionTestActionTriggerSphere(&body,&trigger);
    printf("airlock identity-frame hit=%d\n",trigger.hit);
    if (trigger.hit != 1) return 1;
    root.workm=(MATRIX){.m={{3867,0,-1347},{-966,2856,-2772},{938,2935,2697}},.t={-446,-3,4409}};
    view.workm=(MATRIX){.m={{1535,0,3797},{2721,2856,-1100},{-2648,2935,1070}},.t={5706,4926,-568}};
    trigger.hit=0;
    worldCollisionTestActionTriggerSphere(&body,&trigger);
    printf("airlock camera-frame hit=%d\n",trigger.hit);
    if (trigger.hit != 1) return 1;
    /* Reversing Aya must fail the facing gate in either camera frame. */
    root.coord.m[0][2] = 4091;
    root.coord.m[2][2] = -201;
    trigger.hit = 0;
    worldCollisionTestActionTriggerSphere(&body, &trigger);
    if (trigger.hit != 0) return 1;
    if (*SCRATCH_STACK_CURSOR_SLOT != (void*)SCRATCH_STACK_CURSOR_SLOT) return 1;
    WorldCollisionTrigger actions[2] = {0};
    WorldCollisionTrigger boundaries[1] = {0};
    WorldCollisionOccluder occluders[1] = {0};
    WorldCollisionRoomResources room = {0};
    room.actionTriggers = actions;
    room.viewBoundaryTriggers = boundaries;
    room.occluders = occluders;
    actions[0].flags = 2;
    actions[1].flags = 2 | WORLD_COLLISION_TRIGGER_LAST;
    actions[0].origin.vx = -8784;
    boundaries[0].flags = 1 | WORLD_COLLISION_TRIGGER_LAST;
    occluders[0].flags = WORLD_COLLISION_OCCLUDER_LAST;
    for (int visit = 0; visit < 3; ++visit) {
        peResetRoomCollisionResources(&room);
        if (actions[0].flags != 2 || actions[1].flags != (2 | WORLD_COLLISION_TRIGGER_LAST)) return 1;
        if (actions[0].origin.vx != -8784 || actions[0].hit || actions[0].next || actions[0].prevLink) return 1;
        if (boundaries[0].hit || boundaries[0].flags != (1 | WORLD_COLLISION_TRIGGER_LAST)) return 1;
        if (occluders[0].next || occluders[0].prevLink || occluders[0].flags != WORLD_COLLISION_OCCLUDER_LAST) return 1;
        worldCollisionLinkTrigger(0, &actions[0]);
        worldCollisionLinkTrigger(0, &actions[1]);
        if (gWorldCollisionActionTriggerListHead != actions || actions[0].next != &actions[1] || actions[1].prevLink != &actions[0].next) return 1;
        worldCollisionLinkTrigger(1, &boundaries[0]);
        worldCollisionLinkOccluder(0, &occluders[0]);
        if (gWorldCollisionViewBoundaryListHead != boundaries || gWorldCollisionOccluderListHead != occluders) return 1;
        actions[0].hit = 1;
        boundaries[0].hit = 1;
        boundaries[0].flags |= WORLD_COLLISION_TRIGGER_LINKED | WORLD_COLLISION_TRIGGER_ENABLED;
        occluders[0].flags |= WORLD_COLLISION_OCCLUDER_LINKED | WORLD_COLLISION_OCCLUDER_ENABLED;
        worldCollisionResetListsAndGrid();
    }
    /* The retail scan crosses three separately named objects: 1 + 1 + 4.
     * Verify the generated host data remains contiguous through LAST. */
    WorldCollisionTrigger* plaza = _gAkropolisPlazaHelicopterWreckTrigger;
    if ((uintptr_t)&_gAkropolisPlazaSergeantTrigger != (uintptr_t)plaza + sizeof(*plaza)) return 1;
    if ((uintptr_t)_gAkropolisPlazaEntranceAndExamineTriggers != (uintptr_t)plaza + 2 * sizeof(*plaza)) return 1;
    WorldCollisionRoomResources plazaRoom = {.actionTriggers = plaza};
    peResetRoomCollisionResources(&plazaRoom);
    for (int i = 0; i < 6; ++i) {
        if ((plaza[i].flags & WORLD_COLLISION_TRIGGER_LAST) != (i == 5 ? WORLD_COLLISION_TRIGGER_LAST : 0)) return 1;
        worldCollisionLinkTrigger(0, &plaza[i]);
    }
    if (plaza[0].origin.vx != 5744 || plaza[1].origin.vx != 17206 || plaza[5].origin.vx != 23200) return 1;
    if (plaza[4].next != &plaza[5] || plaza[5].next != NULL) return 1;
    worldCollisionClearTriggerList(0);
    puts("plaza: generated 1+1+4 trigger span, reset, linking and terminal marker OK");
    puts("room collision: repeated resident-overlay registration OK");
    puts("action trigger: airlock contact in room/camera frames and facing rejection OK");
    return 0;
}
