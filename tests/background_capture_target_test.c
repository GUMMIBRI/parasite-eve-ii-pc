#include "../src/port/background_capture_target.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CHECK(x) do { if (!(x)) { fprintf(stderr, "line %d: %s\n", __LINE__, #x); exit(1); } } while (0)

int main(void)
{
    PeBackgroundCaptureTarget target;
    PeBackgroundFrameInfo frame = { UINT64_C(0x123456789abcdef0), {4,40,11,1,3,2} };
    CHECK(peBackgroundParseCaptureTarget("4,40,11,1:123456789abcdef0", &target));
    CHECK(peBackgroundCaptureMatchesTarget(&target, &frame));
    for (int i = 0; i < 4; ++i) {
        ++frame.location[i];
        CHECK(!peBackgroundCaptureMatchesTarget(&target, &frame));
        --frame.location[i];
    }
    ++frame.key;
    CHECK(!peBackgroundCaptureMatchesTarget(&target, &frame));
    --frame.key;
    memset(frame.location, 0, sizeof(frame.location));
    CHECK(!peBackgroundCaptureMatchesTarget(&target, &frame));
    const char* invalid[] = {NULL, "", "4,40,11,1", "0,40,11,1:1", "6,40,11,1:1",
        "4,0,11,1:1", "4,256,11,1:1", "4,40,0,1:1", "4,40,51,1:1",
        "4,40,11,0:1", "4,40,11,256:1", "4,40,11,1:0", "4,40,11,1:gg",
        "4,40,11,1:123456789abcdef01", "4,40,11,1:1garbage"};
    for (unsigned i = 0; i < sizeof(invalid)/sizeof(invalid[0]); ++i) {
        PeBackgroundCaptureTarget saved = target;
        CHECK(!peBackgroundParseCaptureTarget(invalid[i], &target));
        CHECK(target.stage == saved.stage && target.area == saved.area &&
              target.view == saved.view && target.room == saved.room && target.key == saved.key);
    }
    CHECK(peBackgroundParseCaptureTarget("5,255,50,255:ffffffffffffffff", &target));
    puts("Capture target: exact source and room context, malformed inputs rejected");
    return 0;
}
