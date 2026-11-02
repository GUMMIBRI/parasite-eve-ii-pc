/* Execute the production release state with taskKill freeing its real work.
 * The retail idle tail must still query/play the saved player after teardown. */
#include "../src/stages/akropolis/rooms/observatory/observatory_effects.c"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define CHECK(x) do { if (!(x)) { fprintf(stderr, "line %d: %s\n", __LINE__, #x); exit(1); } } while (0)
DisplayState gDisplayState;
PlayerStatus gPlayerStatus;
McSaveData gMcSaveData[MEMORY_CARD_SAVE_COUNT];
AttachmentState gAttachmentState;
SceneCombatState gSceneCombatState;
static GameSession session;
GameSession* gGameSession = &session;
AnimationSet* gAkropolisObservatoryPlayerAnimationSets[2];
static Task player, scene;
static int killed, queries, plays, ends, playing;
void Psyz_PadsOverride(int p, char* f, int n) { (void)p; (void)f; (void)n; }
void* memCalloc(size_t n, bool aux) { (void)aux; return calloc(1,n); }
void memFillBytes(void* p, u32 v, size_t n) { memset(p,(unsigned char)v,n); }
Task* gameGetTaskSlot(s32 slot) { (void)slot; return &player; }
void sceneEngageBattle(s32 arg) { (void)arg; CHECK(0); }
void taskKill(Task* task)
{
    CHECK(task==&scene && ends==1 && !killed);
    free(task->work); /* Match the actual scheduler's immediate work teardown. */
    killed=1;
}
s32 taskMessageDispatch(Task* task, s32 id, TaskMessageWord first, TaskMessageWord second)
{
    CHECK(task==&player && second==0);
    if (id==GAME_ACTOR_MESSAGE_END_SCRIPTED) {
        CHECK(!killed && first==0); ++ends; return 0;
    }
    if (id==ANIMATION_MESSAGE_IS_PLAYING) {
        CHECK(killed && first==0); ++queries; return playing;
    }
    if (id==ANIMATION_MESSAGE_INSTALL_AND_PLAY) {
        const AnimationPlayRequest* request=(const void*)first;
        CHECK(killed && queries==1 && !playing);
        CHECK(request->source.sets==gAkropolisObservatoryPlayerAnimationSets);
        CHECK(request->animationId==1 && request->blend==ANIMATION_BLEND_INTERPOLATE);
        CHECK(request->blendFrames==10 && request->enableWorldCollision==ANIMATION_WORLD_COLLISION_ENABLE);
        ++plays; return 0;
    }
    CHECK(0); return 0;
}
int main(void)
{
    for (int follow=0; follow<2; ++follow) for (playing=0; playing<2; ++playing) {
        memset(&scene,0,sizeof scene);
        _SceneWork* work=calloc(1,sizeof *work); CHECK(work);
        work->playerTask=&player; work->followUpIndex=follow;
        scene.work=work; scene.state=6;
        killed=queries=plays=ends=0;
        _akropolisObservatoryScriptedBattleTask(&scene);
        CHECK(killed && ends==1 && queries==1);
        CHECK(plays==(follow && !playing));
    }
    puts("Observatory release: teardown precedes idle query; retained player and optional follow-up survive freed work OK");
    return 0;
}
