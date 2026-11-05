#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main/fs_types.h"
#include "main/task.h"
#include "main/display.h"
#include "../src/shared/screen/screen_negative.h"

#define CHECK(x) do { if (!(x)) { fprintf(stderr, "line %d: %s\n", __LINE__, #x); exit(1); } } while (0)

static struct {
    u32 before[8];
    FsImgBuffers image;
    u32 after[8];
} storage;
FsImgBuffers* gFsImageWorkspacePtr = &storage.image;
DisplayState gDisplayState;
u8 gEvsPlaybackPaused;
static RECT _gScreenNegativeStripRect = {0, 0, 16, 240};
static RECT _gScreenNegativeFrameRect = {0, 0, 320, 240};
static unsigned captureCalls, killed;

int StoreImage(RECT* rect, u_long* data)
{
    unsigned char* dst = (unsigned char*)data;
    unsigned char* begin = (unsigned char*)&storage.image;
    size_t bytes = (size_t)rect->w * rect->h * 2;
    CHECK(dst >= begin && dst <= begin + sizeof(storage.image));
    CHECK(bytes <= (size_t)(begin + sizeof(storage.image) - dst));
    u16* pixels = (u16*)dst;
    for (size_t i = 0; i < bytes / 2; ++i)
        pixels[i] = (u16)(i * 97 + rect->x * 113 + rect->y);
    ++captureCalls;
    return 0;
}
int DrawSync(int mode) { (void)mode; return 0; }
void taskKill(Task* task) { (void)task; ++killed; }

#include "../src/shared/screen/screen_negative_filter.inc.c"
#include "../src/shared/screen/screen_negative_capture.inc.c"

static u16 negative(u16 pixel)
{
    unsigned r = pixel & 31, g = (pixel >> 5) & 31, b = (pixel >> 10) & 31;
    unsigned luminance = 31 - (3 * r + 4 * g + b) / 8;
    return (u16)(luminance | (luminance << 5) | (luminance << 10));
}

int main(void)
{
    static u16 input[320 * 240];
    for (unsigned debug = 0; debug < 2; ++debug) {
        for (unsigned buffer = 0; buffer < 2; ++buffer) {
            memset(&storage, 0xA5, sizeof(storage));
            captureCalls = killed = 0;
            gDisplayState.debugMode = debug ? -1 : 0;
            gDisplayState.drawBuffer = buffer;
            ScreenNegativeCaptureArgs args = {.duration = 1};
            Task task = {0};
            task.spawnArg2.pointer = &args;
            _screenNegativeCaptureTask(&task);
            CHECK(captureCalls == (debug ? 1 : FILE_SYSTEM_IMAGE_STRIP_COUNT));
            CHECK(gDisplayState.skipDraw == 1 && task.state == 1);
            memcpy(input, &storage.image, sizeof(input));
            _screenNegativeCaptureTask(&task);
            const u16* output = (const u16*)&storage.image;
            for (unsigned i = 0; i < 320 * 240; ++i) CHECK(output[i] == negative(input[i]));
            for (unsigned i = 0; i < 8; ++i) {
                CHECK(storage.before[i] == 0xA5A5A5A5);
                CHECK(storage.after[i] == 0xA5A5A5A5);
            }
            _screenNegativeCaptureTask(&task);
            CHECK(killed == 1 && args.done && !gDisplayState.skipDraw);
        }
    }
    puts("screen negative capture bounds and RGB555 conversion OK");
    return 0;
}
