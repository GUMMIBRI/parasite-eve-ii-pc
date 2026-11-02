#ifndef PORT_ROOM_COLLISION_H
#define PORT_ROOM_COLLISION_H

#include "gameplay/collision.h"
#include "gameplay/room.h"

/* Native room overlays remain resident. Restore the transient collision state
 * that loading the original overlay would initialize, after the old lists have
 * been retired and before registering the new room's borrowed arrays. */
static inline void peResetRoomCollisionResources(const WorldCollisionRoomResources* room)
{
    WorldCollisionTrigger* arrays[2] = {room->viewBoundaryTriggers, room->actionTriggers};
    for (int i = 0; i < 2; ++i) {
        WorldCollisionTrigger* trigger = arrays[i];
        if (!trigger) continue;
        for (;;) {
            trigger->next = NULL;
            trigger->prevLink = NULL;
            trigger->hit = 0;
            trigger->flags &= WORLD_COLLISION_TRIGGER_PERSISTENT_FLAGS;
            if (trigger->flags & WORLD_COLLISION_TRIGGER_LAST) break;
            ++trigger;
        }
    }
    WorldCollisionOccluder* occluder = room->occluders;
    if (occluder) {
        for (;;) {
            occluder->next = NULL;
            occluder->prevLink = NULL;
            occluder->flags &= WORLD_COLLISION_OCCLUDER_PERSISTENT_FLAGS;
            if (occluder->flags & WORLD_COLLISION_OCCLUDER_LAST) break;
            ++occluder;
        }
    }
}
#endif
