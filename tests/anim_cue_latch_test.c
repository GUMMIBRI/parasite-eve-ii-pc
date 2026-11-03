// Characterises the footstep cue latch shared by the walking actors: a held trigger
// cue sounds once, a non-trigger cue re-arms it, and a different trigger cue sounds again.
#include <stdio.h>

#include "../src/shared/actor/anim_cue_latch.inc.h"

static int sFailures;

static void expect(int condition, const char* what)
{
    if (!condition) {
        printf("FAIL: %s\n", what);
        sFailures++;
    }
}

int main(void)
{
    unsigned short latch = 0;

    expect(animCueLatchPoll(&latch, 0x11, 1, 0) == 1 && latch == 0x11, "first trigger sounds and latches");
    expect(animCueLatchPoll(&latch, 0x11, 1, 0) == 0 && latch == 0x11, "held trigger stays silent");
    expect(animCueLatchPoll(&latch, 0x15, 1, 0) == 1 && latch == 0x15, "other trigger sounds");
    expect(animCueLatchPoll(&latch, 0x03, 0, 0) == 0 && latch == 0, "non-trigger clears the latch");
    expect(animCueLatchPoll(&latch, 0x15, 1, 0) == 1 && latch == 0x15, "re-armed trigger sounds again");

    latch = 0xFFFF;
    expect(animCueLatchPoll(&latch, 0x01, 0, 0xFFFF) == 0 && latch == 0xFFFF, "custom none value is stored");
    expect(animCueLatchPoll(&latch, 0xFFFF, 1, 0xFFFF) == 0, "latch equal to cue stays silent");

    if (sFailures == 0) {
        printf("anim_cue_latch_test: ok\n");
    }
    return sFailures != 0;
}
