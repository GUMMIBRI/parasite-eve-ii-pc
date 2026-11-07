#ifndef PORT_BACKGROUND_FOREGROUND_H
#define PORT_BACKGROUND_FOREGROUND_H
#include <stdint.h>
#include <libgpu.h>

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
 * This builder is not yet connected to live room OTs. */
void* peForegroundBuild(PeForegroundPackets* packets,const SPRT* source,
                       uint32_t draw_mode,const RECT* current_clip,
                       int offset_x,int offset_y,uint64_t atlas_key,unsigned first_cell);
#endif
