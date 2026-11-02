#include "../src/gameplay/item_menu.h"
#include "../src/gameplay/items.h"
#include "../src/gameplay/scene_runtime.h"
#include "../src/gameplay/cap.h"
#include "main/display.h"
#include "main/mc.h"
#include "main/session.h"
#include "main/stage.h"
#include "main/task.h"
#include "main/ui.h"
#include "main/wipsys.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CHECK(x) do { if (!(x)) { fprintf(stderr,"line %d: %s\n",__LINE__,#x); exit(1); } } while (0)
DisplayState gDisplayState;
static GameSession session;
GameSession* gGameSession = &session;
McSaveData gMcSaveData[MEMORY_CARD_SAVE_COUNT];
PlayerStatus gPlayerStatus;
AreaObjectStage gAreaObjectStages[6];
UiObjectDesc gItemMenuPanelDescriptors[ITEM_MENU_DESCRIPTOR_COUNT];
UiObjectDesc gItemMenuTransferScreenDescriptor;
u16 gItemPickupPublishedKind, gItemPickupPublishedPlaceState;
static UiObject rootObject;
static Task owner, player;
static TmdObject playerModel;
static GfxCoord playerRoot;
static Task* root;
static int reparented, killed, closed;
extern void itemPickupActionPromptTask(Task*);
void telephoneDispatchMenuTask(Task* task) { (void)task; }
int ratan2(int y,int x) { (void)y;(void)x; return 0; }
Task* gameGetTaskSlot(s32 slot) { (void)slot; return &player; }
s32 itemPickupPublishPlacedObject(s32 id) { CHECK(id==1); return 1; }
void displaySetFrameTiming(s32 mode) { (void)mode; }
void stageEnsureHeapTaskPrimitiveBuffer(void) {}
void stageReleaseTaskPrimitiveBuffer(void) {}
UiObject* (uiSpawnObject)(const UiObjectDesc* descriptor, TaskSpawnArg arg, s32 mode, s32 delay, UiObject* parent)
{
    (void)descriptor;(void)arg;(void)mode;(void)delay;
    CHECK(parent==NULL && root==NULL);
    root=calloc(1,sizeof(*root));CHECK(root);
    root->nextSibling=root;
    root->spawnArg2.pointer=&rootObject;
    rootObject.owner=root;
    return &rootObject;
}
void taskReparent(Task* parent,Task* child)
{
    CHECK(parent==&owner && child==root && parent->firstChild==NULL);
    child->parent=parent;parent->firstChild=child;++reparented;
}
void uiStartTreeClosing(UiObject* object,Task* task)
{
    CHECK(object==&rootObject && task==root && root->parent==&owner);
    /* Model the UI contract: closing detaches, then its task can be collected
     * independently before the prompt's 12-update closing interval ends. */
    root->parent->firstChild=NULL;
    free(root);root=NULL;++closed;
}
void taskKill(Task* task)
{
    CHECK(task==&owner && task->firstChild==NULL && root==NULL);
    ++killed;
}
static void run_prompt(u16 kind,s16 result)
{
    CapActionRequest request={0};request.actionId=1;
    memset(&owner,0,sizeof(owner));memset(&rootObject,0,sizeof(rootObject));
    owner.spawnArg2.pointer=&request;
    gItemPickupPublishedKind=kind;
    reparented=killed=closed=0;
    itemPickupActionPromptTask(&owner);
    CHECK(reparented==1 && owner.firstChild==root && root->parent==&owner);
    rootObject.result=result;rootObject.resultValue=result==USER_INTERFACE_RESULT_CONFIRM ? USER_INTERFACE_LIST_COMMAND_YES : 0;
    itemPickupActionPromptTask(&owner);
    CHECK(closed==1 && owner.firstChild==NULL && !request.done);
    for (int i=0;i<12;++i) itemPickupActionPromptTask(&owner);
    CHECK(request.done && killed==1);
    CHECK(request.accepted==(result==USER_INTERFACE_RESULT_CONFIRM));
}
int main(void)
{
    player.extra.tmd=&playerModel;playerModel.coords=&playerRoot;
    run_prompt(ITEM_PICKUP_PLACE_BANK_ITEM<<8,USER_INTERFACE_RESULT_CANCEL);
    run_prompt((ITEM_PICKUP_PLACE_BANK_SAVE_POINT<<8)|2,USER_INTERFACE_RESULT_CONFIRM);
    CHECK(gMcSaveData[0].state.savePoint==2);
    puts("item prompt: root ownership, independent UI collection and delayed teardown OK");
}
