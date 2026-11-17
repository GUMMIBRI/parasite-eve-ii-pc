#include "port/disc_assets.h"
#include "port/asset_bind.h"
#include "port/host_ui.h"
#include <stdio.h>
#include <stdlib.h>
#if !defined(_WIN32) && !defined(PE2_PS5_HOST)
#include <signal.h>
#include <execinfo.h>
#include <unistd.h>
#endif
#include <psyz.h>
#include <psyz/cd.h>
#include <psyz/video.h>
#include <libgpu.h>
#include <libetc.h>
#include "gamemain.h"
#ifdef PE2_PS5_HOST
extern void pe_application_stage(const char*);
extern void pe_application_failure(const char*, int, const char*);
#include <SDL3/SDL_error.h>
extern void pe_ps5_install_logging(void);
extern _Bool InitPlatform(void);
extern void ResetPlatform(void);
#endif

/* Crash report: where it faulted and the call chain (also the link register, since a call through a
 * NULL function pointer leaves no frame of its own). */
extern void* gHostCurrentTaskCallback;
#if !defined(_WIN32) && !defined(PE2_PS5_HOST)
static void crashHandler(int sig, siginfo_t* info, void* ctx)
{
    void* frames[32];
    int count;
#if defined(__APPLE__) && defined(__arm64__)
    ucontext_t* uc = ctx;
    fprintf(stderr, "\nCRASH signal %d addr=%p pc=%p lr=%p\n", sig, info->si_addr,
            (void*)uc->uc_mcontext->__ss.__pc, (void*)uc->uc_mcontext->__ss.__lr);
    frames[0] = (void*)uc->uc_mcontext->__ss.__lr;
    fprintf(stderr, "last task callback:\n");
    {
        void* cb[1] = { gHostCurrentTaskCallback };
        backtrace_symbols_fd(cb, 1, 2);
    }
    count = backtrace(frames + 1, 30) + 1;
#else
    (void)ctx;
    fprintf(stderr, "\nCRASH signal %d addr=%p\n", sig, info->si_addr);
    count = backtrace(frames, 32);
#endif
    backtrace_symbols_fd(frames, count, 2);
    _exit(128 + sig);
}
#endif

#ifdef PE2_PS5_HOST
#include <psyz/hd_upload.h>
#include "port/ps5_paths.h"
#include "port/ps5_app_discovery.h"
#endif

/* Port entry. Disc mounting goes here once the runtime loader exists; then the
 * original start-up path runs on the host stack (no SetSp). */
int main(int argc, char** argv) {
#ifdef PE2_PS5_HOST
    pe_ps5_install_logging();
#endif
#if !defined(_WIN32) && !defined(PE2_PS5_HOST)
    struct sigaction sa = { .sa_sigaction = crashHandler, .sa_flags = SA_SIGINFO };
    sigaction(SIGSEGV, &sa, NULL);
    sigaction(SIGBUS, &sa, NULL);
#endif
    /* Disc image: first argument, or PE2_DISC. Game data is read from it at run time. */
    const char* disc = NULL;
#ifdef PE2_PS5_HOST
    pe_application_stage("before host startup / disc selection");
#endif
    int startup = peHostStartup(argc, argv, &disc);
    if (startup <= 0) {
#ifdef PE2_PS5_HOST
        if (startup < 0)
            pe_application_failure("host startup", 2, peHostLastStatus());
        else
            pe_application_stage("host startup requested normal exit (help/menu/cancel), status 0");
        pe_application_stage(pePs5StorageReason());pe_application_stage("\n");
        pe_application_stage(pePs5DiscDiscoveryReason());pe_application_stage("\n");
        pe_application_stage(pePs5ApplicationDiscoveryReason());pe_application_stage("\n");
        pe_application_stage(peHostLastStatus());pe_application_stage("\n");
#endif
        return startup < 0 ? 2 : 0;
    }
#ifdef PE2_PS5_HOST
    pe_application_stage("before disc mount / CUE parse");
    pe_application_stage(disc);
#endif
    int mountStatus = Psyz_CdSetDiskPath(disc);
    if (mountStatus != 0) {
#ifdef PE2_PS5_HOST
        pe_application_failure("disc mount / CUE parse", mountStatus, disc);
#endif
        fprintf(stderr, "Cannot open the disc image \"%s\". Check that the file exists and that it is a CUE sheet or BIN image\n"
                        "of the North American Parasite Eve II (disc 1). Run with --host-menu to choose a different image.\n", disc);
        return 2;
    }
    Psyz_SetTitle("Parasite Eve 2");
#ifdef PE2_PS5_HOST
    pe_application_stage("PE2 disc mounted; before runtime asset load\n");
#endif
    /* Game tables the original source embedded at build time are filled from the disc here. */
    {
        extern int peAssetsDump(const char*);
        struct PeDisc* assets = peDiscOpen(disc);
        if (!assets) {
#ifdef PE2_PS5_HOST
            pe_application_failure("disc asset open", 2, disc);
#endif
            fprintf(stderr, "Cannot read the game files from \"%s\". It is not a North American Parasite Eve II disc image,\n"
                            "or the image is damaged (other regions and re-encoded images are not supported).\n", disc);
            return 2;
        }
#ifdef PE2_PS5_HOST
        pe_application_stage("disc asset open succeeded; before asset table load");
#endif
        fprintf(stderr, "[assets] %d arrays loaded from the disc\n", peAssetsLoad(assets));
#ifdef PE2_PS5_HOST
        pe_application_stage("asset table load returned");
#endif
        if (getenv("PE2_DISC2_ASSETS")) { /* development: load disc 2's arrays now, to compare the dump */
            struct PeDisc* second = peDiscOpen(getenv("PE2_DISC2_ASSETS"));
            if (second) { fprintf(stderr, "[assets] %d arrays loaded from disc 2\n", peAssetsLoad(second)); peDiscClose(second); }
        }
        if (getenv("PE2_DUMP_ASSETS")) peAssetsDump(getenv("PE2_DUMP_ASSETS"));
        peDiscClose(assets);
    }
#ifndef PE2_PS5_HOST
    if (getenv("PE2_DEBUG_PORT")) { /* development: PsyZ HTTP debug server on 127.0.0.1 (/screenshot, /vram, /input) */
        extern int Psyz_DebugServer(int);
        fprintf(stderr, "[debug] server on port %d\n", Psyz_DebugServer(atoi(getenv("PE2_DEBUG_PORT"))));
    }
#endif
#ifdef PE2_PS5_HOST
    pe_application_stage("before ResetGraph / renderer startup");
#endif
    ResetGraph(0);
#ifdef PE2_PS5_HOST
    if (!InitPlatform()) {
        pe_application_failure("native renderer startup", 3, SDL_GetError());
        return 3;
    }
    /* An explicit external pack root opts in before original texture uploads.
     * No bundled art, automatic download or successful-match claim. */
    const char *hd_character_root = getenv("PE2_HD_CHARACTER_ROOT");
    if (hd_character_root && hd_character_root[0]) {
        if (Psyz_GpuSetHdUploadCharacters(1, hd_character_root) < 0)
            pe_application_stage("PE2 optional character pack unavailable; retaining original textures\n");
        else
            pe_application_stage("PE2 optional character index admitted; waiting for exact player texture upload\n");
    }
    pe_application_stage("PE2 asset load/ResetGraph returned; entering original game\n");
#endif
    gameMainRun();
#ifdef PE2_PS5_HOST
    pe_application_stage("PE2 original game returned; shutting down platform");
    ResetPlatform();
    pe_application_stage("PE2 platform shutdown returned");
#endif
    return 0;
}
