#include "player_actor.h"

/// Transfers the targeted mark, retaining all unrelated target and actor state.
void playerActorSetLockTarget(Task* task, WorldTargetNode* target)
{
    GameActor* actor = task->work;
    WorldTargetNode* previousTarget = actor->targetNode;
    if (previousTarget != target) {
        if (previousTarget != NULL) previousTarget->state.parts.targeted = 0;
        actor->targetNode = target;
    }
#ifdef __psyz
    /* Both acquisition and cycling scans return NULL with no eligible node.
     * The console's unconditional low-address mark store cannot be made
     * through a native null pointer. The actor's NULL selection is retained. */
    if (target == NULL) return;
#endif
    target->state.parts.targeted = 1;
}
