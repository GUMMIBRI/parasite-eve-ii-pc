/* Original PE2 storage discovery, CC0-1.0. Uses public PS5 homebrew /data
 * and /mnt/usb0 conventions, without reusing PE1 assets or save formats. */
#include "port/ps5_paths.h"
#include <SDL3/SDL.h>
#include <stdio.h>
#include <string.h>

static const char* const roots[] = {
    "/data/parasite-eve-ii", "/mnt/usb0/parasite-eve-ii"
};
static char discovered[2][4096];

const char* pePs5ConfigDirectory(void)
{
    /* No working-directory fallback: a launcher may own that directory. */
    if (!SDL_CreateDirectory(roots[0])) {
        fprintf(stderr, "[ps5] Cannot create PE2 data directory: %s\n", SDL_GetError());
        return NULL;
    }
    return roots[0];
}

const char* pePs5CardDirectory(void)
{
    static const char path[] = "/data/parasite-eve-ii/memory-cards";
    if (!pePs5ConfigDirectory() || !SDL_CreateDirectory(path)) {
        fprintf(stderr, "[ps5] Cannot create PE2 memory-card directory\n");
        return NULL;
    }
    return path;
}

static const char* findInDirectory(int number, const char* directory, size_t length)
{
    const char* const names[2][2] = {
        { "SLUS-01042.cue", "Parasite Eve II (USA) (Disc 1).cue" },
        { "SLUS-01055.cue", "Parasite Eve II (USA) (Disc 2).cue" }
    };
    if (length >= sizeof discovered[0]) return NULL;
    for (unsigned i = 0; i < 2; i++) {
        int written = snprintf(discovered[number - 1], sizeof discovered[0],
                               "%.*s/%s", (int)length, directory, names[number - 1][i]);
        if (written < 0 || (size_t)written >= sizeof discovered[0]) continue;
        FILE* file = fopen(discovered[number - 1], "rb");
        if (!file) continue;
        fclose(file);
        /* Discovery only; the caller must validate USA disc identity. */
        return discovered[number - 1];
    }
    discovered[number - 1][0] = 0;
    return NULL;
}

const char* pePs5FindDisc(int number, const char* companion)
{
    if (number != 1 && number != 2) return NULL;
    if (companion && *companion) {
        const char* slash = strrchr(companion, '/');
        if (slash) {
            const char* found = findInDirectory(number, companion, (size_t)(slash - companion));
            if (found) return found;
        }
    }
    for (unsigned i = 0; i < sizeof roots / sizeof roots[0]; i++) {
        const char* found = findInDirectory(number, roots[i], strlen(roots[i]));
        if (found) return found;
    }
    return NULL;
}
