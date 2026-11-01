#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <execinfo.h>
#include <unistd.h>
#include <psyz.h>
#include <psyz/cd.h>
#include <psyz/video.h>
#include <libgpu.h>
#include <libetc.h>
#include "gamemain.h"

/* Crash report: where it faulted and the call chain (also the link register, since a call through a
 * NULL function pointer leaves no frame of its own). */
static void crashHandler(int sig, siginfo_t* info, void* ctx)
{
    void* frames[32];
    int count;
#if defined(__APPLE__) && defined(__arm64__)
    ucontext_t* uc = ctx;
    fprintf(stderr, "\nCRASH signal %d addr=%p pc=%p lr=%p\n", sig, info->si_addr,
            (void*)uc->uc_mcontext->__ss.__pc, (void*)uc->uc_mcontext->__ss.__lr);
    frames[0] = (void*)uc->uc_mcontext->__ss.__lr;
    count = backtrace(frames + 1, 30) + 1;
#else
    (void)ctx;
    fprintf(stderr, "\nCRASH signal %d addr=%p\n", sig, info->si_addr);
    count = backtrace(frames, 32);
#endif
    backtrace_symbols_fd(frames, count, 2);
    _exit(128 + sig);
}

/* Port entry. Disc mounting goes here once the runtime loader exists; then the
 * original start-up path runs on the host stack (no SetSp). */
int main(int argc, char** argv) {
    struct sigaction sa = { .sa_sigaction = crashHandler, .sa_flags = SA_SIGINFO };
    sigaction(SIGSEGV, &sa, NULL);
    sigaction(SIGBUS, &sa, NULL);
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
    Psyz_SetTitle("Parasite Eve II");
    ResetGraph(0);
    gameMainRun();
    return 0;
}
