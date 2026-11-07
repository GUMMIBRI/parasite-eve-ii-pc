#ifndef PORT_FOREGROUND_STAGE_H
#define PORT_FOREGROUND_STAGE_H
#include "port/gpu_state.h"
#include "port/foreground_pack.h"

enum {PE_FOREGROUND_STAGE_WIDTH=64,PE_FOREGROUND_STAGE_HEIGHT=256,PE_FOREGROUND_STAGE_CELLS=64};
typedef struct {
    uint32_t occupied;
    /* Optional caller-owned copy of PsyZ's known map; preceding draws clear it. */
    unsigned char* known;
} PeForegroundStage;
/* Reserve both PE2 display buffers and conservatively track original OT accesses.
 * Use as a peGpuWalkOt observer; a failed walk invalidates the entire plan. */
void peForegroundStageBegin(PeForegroundStage* stage,unsigned char* known);
void peForegroundStageObserve(const void* packet,unsigned offset,const uint32_t* words,
                             unsigned count,const PeGpuState* before,void* context);
/* A candidate also needs a fully known native backup. No GPU work is issued. */
int peForegroundStageChoose(const PeForegroundStage* stage,const unsigned char* known,int* x,int* y);
/* Decode original native words into a 64x256 direct-colour page, with literal
 * zero padding outside the source extent. Unknown texels/CLUTs reject the source.
 * On failure, discard the tentative cells; this never modifies actual VRAM. */
int peForegroundStageCopy(const PeForegroundSource* source,const uint16_t* vram,
                         const unsigned char* known,unsigned first_cell,uint16_t* page);
#endif
