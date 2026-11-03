#ifndef ANIM_CUE_LATCH_INC_H
#define ANIM_CUE_LATCH_INC_H

/// Latches a footstep-style animation cue so that a held trigger cue sounds once.
///
/// `latch` holds the cue index that last fired, or `none` after any non-trigger
/// cue. Returns 1 when the sound must be emitted: a trigger cue that differs
/// from the latched one, which becomes the new latch. A held trigger cue returns
/// 0 and keeps the latch; a non-trigger cue clears it to `none` and returns 0.
static inline int animCueLatchPoll(unsigned short* latch, unsigned short cueIndex, int triggers, unsigned short none)
{
    if (!triggers) {
        *latch = none;
        return 0;
    }
    if (*latch == cueIndex) {
        return 0;
    }
    *latch = cueIndex;
    return 1;
}

#endif
