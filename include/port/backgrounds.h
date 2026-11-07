#ifndef PORT_BACKGROUNDS_H
#define PORT_BACKGROUNDS_H
#include <stdint.h>

typedef struct { uint64_t key; int location[6]; } PeBackgroundFrameInfo;
/* Metadata for a diagnostic capture of one physical display buffer. */
void peBackgroundBeginFrame(int buffer_y);
int peBackgroundGetFrameInfo(int buffer_y,PeBackgroundFrameInfo* info);
typedef struct {
    uint32_t anim_frame,frame_count,loop_count,loop_ticks,random_lcg;
} PeBackgroundSimulationState;
void peBackgroundEndFrame(int buffer_y,int field_frame,unsigned game_tick,unsigned vsync_count,
                          const PeBackgroundSimulationState* simulation);
/* Submit original OTs, or registered foreground material when a pack matches.
 * Optional PE2_DUMP_GPU_STATE=1 records ordered native state before replacement.
 * allow_staging is true only for the main field's sole resident OT. */
void peBackgroundSubmitOt(const void* head,int allow_staging);
/* Main-thread configuration; GPU resources change at the next background draw.
 * Empty path or enabled=0 restores the original image. Returns 0 for bad input. */
int peBackgroundConfigurePack(const char* path,int enabled);

/* Saved user preference; actual widescreen requires reviewed artwork coverage. */
void peBackgroundSetWidescreen(int enabled);
int peBackgroundGetWidescreen(void);
/* Call before drawing a frame. A missing/narrow span keeps original rendering.
 * Only an artwork presenter may supply a span beyond the original 0..320. */
int peBackgroundSetCoverage(int buffer_y, int left, int right);
/* Debug-export context: logical location; zero when no field session exists. */
void peBackgroundSetLocation(int stage,int area,int view,int room_state,int warp,int variant);
/* After the native image upload and before foreground/models. */
void peBackgroundDraw(const void* source,int columns,int buffer_y,int offset_y);
#endif
