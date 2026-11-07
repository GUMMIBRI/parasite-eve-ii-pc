#ifndef PORT_GPU_STATE_H
#define PORT_GPU_STATE_H
#include <stddef.h>
#include <stdint.h>
#include <libgpu.h>
typedef struct {
    int clip_left,clip_top,clip_right,clip_bottom,offset_x,offset_y;
    uint32_t draw_mode,texture_window,mask_mode;
} PeGpuState;
typedef void (*PeGpuObserver)(const void* packet,unsigned word_offset,
                              const uint32_t* words,unsigned count,
                              const PeGpuState* before,void* context);
/* Read-only interpretation of the same native/packed packet ABI PsyZ consumes.
 * Unknown/truncated commands or cycles return 0; callbacks from that partial
 * traversal must not be treated as a complete frame audit. No GPU submission. */
int peGpuWalkWords(PeGpuState* state,const uint32_t* words,unsigned count,
                   const void* packet,PeGpuObserver observer,void* context);
int peGpuWalkOt(PeGpuState* state,const void* head,PeGpuObserver observer,void* context);
int peGpuStateFromEnv(PeGpuState* state,const DRAWENV* environment);
#endif
