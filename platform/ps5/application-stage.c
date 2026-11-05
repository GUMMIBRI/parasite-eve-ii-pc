/* SPDX-License-Identifier: CC0-1.0
 * Native CRT stage output. No libc/errno/TLS before _init_env. */
#include <stddef.h>
#include <SDL3/SDL_log.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

extern long sceKernelWrite(int, const void*, size_t);
extern void ps5_fp_ieee(void);

static void rawWrite(const char* message)
{
    size_t left = 0;
    while (message[left]) ++left;
    while (left) {
        long written = sceKernelWrite(1, message, left);
        if (written <= 0 || (size_t)written > left) break;
        message += written;
        left -= (size_t)written;
    }
}

void pe_application_stage(const char* message)
{
    /* The reviewed application CRT calls this before _init_env/constructors.
     * The platform thread wrappers then preserve this IEEE MXCSR state. */
    static int fpInitialized;
    if (!fpInitialized) { fpInitialized = 1; ps5_fp_ieee(); }
    rawWrite(message);
}

static void SDLCALL logOutput(void* unused, int category, SDL_LogPriority priority, const char* message)
{
    (void)unused;
    int saved = errno;
    /* Suppress identical informational VSync chatter only. No synchronous
     * filesystem writes are introduced into audio/render callbacks. */
    static char lastVsync[512];
    if (priority == SDL_LOG_PRIORITY_INFO && message && strstr(message, "[ConfigureVSync]") && strlen(message) < sizeof lastVsync) {
        if (!strcmp(lastVsync, message)) { errno = saved; return; }
        strcpy(lastVsync, message);
    }
    char line[2048];
    snprintf(line, sizeof line, "SDL category=%d priority=%d: %s\n", category, (int)priority, message ? message : "(null)");
    rawWrite(line);
    errno = saved;
}

void pe_ps5_install_logging(void)
{
    SDL_SetLogOutputFunction(logOutput, NULL);
    pe_application_stage("PE2 native host: main entered\n");
}
