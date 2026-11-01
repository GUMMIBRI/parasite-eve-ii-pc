#include <stdio.h>
#include <stdlib.h>
#include <psyz.h>
#include <psyz/cd.h>
#include <libgpu.h>
#include <libetc.h>
#include "gamemain.h"

/* Port entry. Disc mounting goes here once the runtime loader exists; then the
 * original start-up path runs on the host stack (no SetSp). */
int main(int argc, char** argv) {
    /* Disc image: first argument, or PE2_DISC. Game data is read from it at run time. */
    const char* disc = argc > 1 ? argv[1] : getenv("PE2_DISC");
    if (disc == NULL) {
        fprintf(stderr, "usage: %s <disc.cue>   (or set PE2_DISC)\n", argv[0]);
        return 2;
    }
    if (Psyz_CdSetDiskPath(disc) != 0) {
        fprintf(stderr, "cannot open disc image: %s\n", disc);
        return 2;
    }
    ResetGraph(0);
    gameMainRun();
    return 0;
}
