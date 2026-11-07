#ifndef PE_BACKGROUND_CAPTURE_TARGET_H
#define PE_BACKGROUND_CAPTURE_TARGET_H

#include "port/backgrounds.h"
#include <inttypes.h>
#include <stdio.h>

typedef struct {
    unsigned stage, area, view, room;
    uint64_t key;
} PeBackgroundCaptureTarget;

static inline int peBackgroundParseCaptureTarget(const char* text, PeBackgroundCaptureTarget* target)
{
    PeBackgroundCaptureTarget parsed = {0};
    int used = 0;
    if (!text || sscanf(text, "%u,%u,%u,%u:%16" SCNx64 "%n",
                        &parsed.stage, &parsed.area, &parsed.view, &parsed.room,
                        &parsed.key, &used) != 5 || text[used] ||
        parsed.stage < 1 || parsed.stage > 5 || parsed.area < 1 || parsed.area > 255 ||
        parsed.view < 1 || parsed.view > 50 || parsed.room < 1 || parsed.room > 255 || !parsed.key)
        return 0;
    *target = parsed;
    return 1;
}

static inline int peBackgroundCaptureMatchesTarget(const PeBackgroundCaptureTarget* target,
                                                   const PeBackgroundFrameInfo* info)
{
    return info->key == target->key && info->location[0] == (int)target->stage &&
           info->location[1] == (int)target->area && info->location[2] == (int)target->view &&
           info->location[3] == (int)target->room;
}

#endif
