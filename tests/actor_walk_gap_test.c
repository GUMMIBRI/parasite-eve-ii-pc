#include <stdio.h>
#include "../src/shared/actor/actor_motion_walk_helpers.h"

int main(void)
{
    const struct { s32 target, root, expected; } cases[] = {
        {5030, 1805, 3225}, {5030, 5029, 1}, {5030, 5031, 1},
        {-5680, -5681, 1}, {-5680, -5679, 1}, {-5680, -5680, 0},
        {0, -1, -65535}, {-1, 0, -65535},
        {65536, 65535, -65535}, {65535, 65536, -65535},
        {-65536, -65537, -65535}, {32768, 32767, 1}
    };
    for (unsigned i = 0; i < sizeof(cases) / sizeof(cases[0]); ++i) {
        s32 gap = _actorMotionWalkAxisGap(cases[i].target, cases[i].root);
        if (gap != cases[i].expected) {
            fprintf(stderr, "gap case %u: %d != %d\n", i, gap, cases[i].expected);
            return 1;
        }
    }
    puts("actor walk gaps OK");
    return 0;
}
