#include <stdio.h>
#include <psyz.h>
#include <libgpu.h>
#include <libetc.h>
#include "gamemain.h"

/* Port entry. Disc mounting goes here once the runtime loader exists; then the
 * original start-up path runs on the host stack (no SetSp). */
int main(void) {
    ResetGraph(0);
    gameMainRun();
    return 0;
}
