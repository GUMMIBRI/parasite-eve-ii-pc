/* A slow host must not change offline scanline deadlines or frame budgets. */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <psyz/video.h>
#include <libgpu.h>
#define CHECK(x) do { if (!(x)) { fprintf(stderr, "line %d: %s\n", __LINE__, #x); exit(1); } } while (0)
void Psyz_PadsOverride(int p, char* f, int n) { (void)p; (void)f; (void)n; }
int main(void)
{
    CHECK(setenv("PSYZ_RASTER_CLOCK", "virtual", 1) == 0);
    CHECK(setenv("PSYZ_AUDIO_CLOCK", "video", 1) == 0);
    CHECK(setenv("PSYZ_HEADLESS", "1", 1) == 0);
    ResetGraph(0);
    Psyz_VideoVSync(0);
    CHECK(Psyz_VideoVSync(1) == 0);
    CHECK(Psyz_VideoVSync(1) == 1);
    struct timespec stall = {0, 50000000};
    nanosleep(&stall, NULL);
    CHECK(Psyz_VideoVSync(1) == 2);
    /* A scene waiting for a future raster deadline must still terminate. */
    unsigned polls = 0;
    while (Psyz_VideoVSync(1) < 100) CHECK(++polls < 101);
    /* Preserve the SDK query's 16-bit wrap. */
    for (unsigned i = 101; i < 65536; ++i) CHECK(Psyz_VideoVSync(1) == (int)i);
    CHECK(Psyz_VideoVSync(1) == 0);
    Psyz_VideoVSync(0);
    CHECK(Psyz_VideoVSync(1) == 0);
    puts("Offline raster: host stall, deadline progress, wrap and blank reset OK");
    return 0;
}
