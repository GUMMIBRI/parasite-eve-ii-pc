/* Exercise the production blink and compare every uploaded byte to retail IMG data. */
#include "port/gpu_len.h"
#include "../src/actors/actor_210700/actor_210700.c"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#define CHECK(x) do { if (!(x)) { fprintf(stderr, "line %d: %s\n", __LINE__, #x); exit(1); } } while (0)

static unsigned char expected[3][768];
static unsigned calls;

s32 actorRenderUploadTexture(Task* task, GpuImageUpload* uploads, const RECT* rect)
{
    CHECK(task != NULL && calls < 3);
    CHECK(rect->x == 0 && rect->y == 40 && rect->w == 24 && rect->h == 16);
    CHECK(uploads[0].operation == GPU_IMAGE_UPLOAD_COPY);
    CHECK(uploads[0].destination.w == 24 && uploads[0].destination.h == 16);
    CHECK(uploads[1].operation == GPU_IMAGE_UPLOAD_END);
    CHECK((uintptr_t)uploads[0].pixels % _Alignof(u_long) == 0);
    CHECK(memcmp(uploads[0].pixels, expected[calls], sizeof(expected[0])) == 0);
    ++calls;
    return 0;
}

void Psyz_PadsOverride(int port, char* frame, int size) { (void)port; (void)frame; (void)size; }

int main(int argc, char** argv)
{
    CHECK(argc == 4); /* Closed, half-open, open retail frames. */
    for (int i = 0; i < 3; ++i) {
        FILE* file = fopen(argv[i + 1], "rb");
        CHECK(file != NULL);
        CHECK(fread(expected[i], 1, sizeof(expected[i]), file) == sizeof(expected[i]));
        CHECK(fgetc(file) == EOF);
        CHECK(fclose(file) == 0);
    }
    _Actor210700Work work = { 0 };
    Task task = { 0 };
    task.work = &work;
    work.blinkStep = ACTOR_210700_BLINK_CLOSED;
    work.blinkCountdown = 1;
    work.blinkFrameDelay = 2;
    _actor210700UpdateBlink(&task);
    CHECK(calls == 0);
    _actor210700UpdateBlink(&task);
    CHECK(calls == 1 && work.blinkStep == ACTOR_210700_BLINK_HALF);
    for (int phase = 0; phase < 2; ++phase) {
        _actor210700UpdateBlink(&task);
        _actor210700UpdateBlink(&task);
        CHECK(calls == (unsigned)phase + 1);
        _actor210700UpdateBlink(&task);
        CHECK(calls == (unsigned)phase + 2);
    }
    CHECK(work.blinkStep == ACTOR_210700_BLINK_NONE);
    _actor210700UpdateBlink(&task);
    CHECK(calls == 3);
    CHECK(sizeof(_gActor210700OpenEyesPixels) == sizeof(expected[0]));
    CHECK(sizeof(_gActor210700HalfOpenEyesPixels) == sizeof(expected[0]));
    CHECK(sizeof(_gActor210700ClosedEyesPixels) == sizeof(expected[0]));
    puts("Rupert blink: timing and all three 768-byte retail eye frames OK");
    return 0;
}
