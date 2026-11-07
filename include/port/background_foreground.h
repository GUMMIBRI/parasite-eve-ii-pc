#ifndef PORT_BACKGROUND_FOREGROUND_H
#define PORT_BACKGROUND_FOREGROUND_H
#include <stdint.h>
#include <libgpu.h>
#include "port/foreground_pack.h"
#include "port/gpu_state.h"

enum { PE_FOREGROUND_MAX_CELLS=20*15 };
typedef struct { u_long addr,len,words[3]; } PeForegroundAtlasSelection;
typedef struct { PeForegroundAtlasSelection selection; SPRT_16 sprite; } PeForegroundTile;
typedef struct {
    DR_AREA clip;
    DR_TPAGE mode;
    PeForegroundTile tiles[PE_FOREGROUND_MAX_CELLS];
    DR_AREA restore;
} PeForegroundPackets;

/* Build a replacement for one native SPRT, with the same native texels and
 * draw-mode word. The atlas is row-major ceil(w/16) by ceil(h/16).
 * Caller MUST supply the actual GPU clip/offset at this primitive's OT position,
 * load the referenced atlas and register the background F8 selector first.
 * The packet arena stays alive until the OT retires. Returns NULL for unsupported
 * input, so a caller can retain the complete original primitive unchanged.
 */
void* peForegroundBuild(PeForegroundPackets* packets,const SPRT* source,
                       uint32_t draw_mode,const RECT* current_clip,
                       int offset_x,int offset_y,uint64_t atlas_key,unsigned first_cell);
/* Inset tails overlap only opaque sources; no extra scissor/flush is emitted. */
void* peForegroundBuildLayout(PeForegroundPackets* packets,const SPRT* source,
                       uint32_t draw_mode,const RECT* current_clip,
                       int offset_x,int offset_y,uint64_t atlas_key,unsigned first_cell,unsigned inset);
/* Registry epochs follow actual OT clears. Only room sprite emitters register. */
void peForegroundBeginOt(const void* first_tag,unsigned tag_count);
void peForegroundRegister(const void* depth_base,const void* packet,unsigned source_id);
/* Validate/compose in OT order, submit once, then restore all original links.
 * PsyZ snapshots the OT synchronously in DrawOTag. render_height is the actual
 * GP1 draw-time height (240 or 256), not the cached presentation DISPENV.
 * Returns replacement count. */
unsigned peForegroundSubmitOt(const void* head,const PeGpuState* initial,const PeForegroundPack* pack,unsigned render_height);
#endif
