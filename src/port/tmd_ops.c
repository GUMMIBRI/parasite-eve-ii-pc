/*
 * Lit, untransformed-vertex draw handlers from hasm/Tmd_StreamHandlers_Ops.s.
 *
 * Each handler walks `elemCount` elements of `elemStride` words, projects the
 * element's vertices with the GTE, culls by facing, lights with the element's
 * normals and prepends the packet to its ordering-table bucket. Every element
 * consumes a packet slot, accepted or not. Packets are PsyZ POLY_* slots at
 * `ws->primWrite`; offsets in an element are byte offsets into `ws->verts` /
 * `ws->normals`. The console version reuses a quad's vertex 3 from the previous
 * element when the offsets match; that is only a cache (the result is identical
 * to projecting again), so it is not kept.
 */
#include "tmd.h"
#include "main/tmd_types.h"

#include <string.h>
#include <psyz.h>
#include <libgpu.h>
#include <libgte.h>
#include <psyz/gte.h>

enum {
    GTE_NCCS = 0x4B08041B,
    GTE_NCCT = 0x4B18043F,
    DEPTH_MASK  = 0x3FFF,
    DEPTH_SHIFT = 4,
};

static SVECTOR* vertexAt(const TmdStreamWorkspace* ws, u32 byteOffset)
{
    return (SVECTOR*)((u8*)ws->verts + byteOffset);
}

static SVECTOR* normalAt(const TmdStreamWorkspace* ws, u32 byteOffset)
{
    return (SVECTOR*)((u8*)ws->normals + byteOffset);
}

static void loadV(unsigned slot, const SVECTOR* v)
{
    Psyz_GteDataWrite(slot * 2, (u32)(u16)v->vx | ((u32)(u16)v->vy << 16));
    Psyz_GteDataWrite(slot * 2 + 1, (u32)(u16)v->vz);
}

static void storeXy(short* dst, unsigned sxyReg)
{
    u32 v  = Psyz_GteDataRead(sxyReg);
    dst[0] = (short)(v & 0xFFFF);
    dst[1] = (short)(v >> 16);
}

/* Store RGB FIFO entry `reg` (20..22) as a packet colour word: r, g, b, code. */
static void storeRgb(u8* dst, unsigned reg)
{
    u32 v = Psyz_GteDataRead(reg);
    memcpy(dst, &v, 4);
}

static void linkPacket(TmdStreamWorkspace* ws, void* packet, u32 length)
{
    u32      otz    = Psyz_GteDataRead(7);
    u32      bucket = ((otz << (ws->otDepthShift & 31)) & DEPTH_MASK) >> DEPTH_SHIFT;
    OT_TYPE* head   = (OT_TYPE*)ws->ot + bucket;

    setlen(packet, length);
    addPrim(head, packet);
}

/* Untextured Gouraud triangle, one normal per corner. */
u32* tmdDrawStreamPrimG3CornerNormals(TmdStreamWorkspace* ws, s32 flags, u32* el)
{
    u8* slot = ws->primWrite;
    (void)flags;

    for (s32 count = ws->elemCount; count != 0; count--, slot += sizeof(POLY_G3), el += ws->elemStride) {
        POLY_G3* p = (POLY_G3*)slot;
        u32 w0 = el[0], w1 = el[1], w2 = el[2], w3 = el[3];

        loadV(0, vertexAt(ws, w0 & 0xFFFF));
        loadV(1, vertexAt(ws, w0 >> 16));
        loadV(2, vertexAt(ws, w1 & 0xFFFF));
        Psyz_GteRtpt();
        if (Psyz_GteReadflg() < 0) {
            continue;
        }
        Psyz_GteNclip();
        if ((s32)Psyz_GteDataRead(24) <= 0) {
            continue;
        }
        storeXy(&p->x0, 12);
        storeXy(&p->x1, 13);
        storeXy(&p->x2, 14);
        Psyz_GteAvsz3();
        Psyz_GteDataWrite(6, w3);
        loadV(0, normalAt(ws, w1 >> 16));
        loadV(1, normalAt(ws, w2 & 0xFFFF));
        loadV(2, normalAt(ws, w2 >> 16));
        Psyz_GteCommand(GTE_NCCT);
        storeRgb(&p->r0, 20);
        storeRgb(&p->r1, 21);
        storeRgb(&p->r2, 22);
        linkPacket(ws, p, 6);
    }
    ws->primWrite = slot;
    return el;
}

/* Untextured Gouraud quad, one normal per corner. */
u32* tmdDrawStreamPrimG4CornerNormals(TmdStreamWorkspace* ws, s32 flags, u32* el)
{
    u8* slot = ws->primWrite;
    (void)flags;

    for (s32 count = ws->elemCount; count != 0; count--, slot += sizeof(POLY_G4), el += ws->elemStride) {
        POLY_G4* p = (POLY_G4*)slot;
        u32 w0 = el[0], w1 = el[1], w2 = el[2], w3 = el[3], w4 = el[4];

        /* Vertex 3 first, so its depth ends up in SZ0 after the triangle projection. */
        loadV(0, vertexAt(ws, w1 >> 16));
        Psyz_GteRtps();
        if (Psyz_GteReadflg() < 0) {
            continue;
        }
        storeXy(&p->x3, 14);

        loadV(0, vertexAt(ws, w1 & 0xFFFF));
        loadV(1, vertexAt(ws, w0 >> 16));
        loadV(2, vertexAt(ws, w0 & 0xFFFF));
        Psyz_GteRtpt(); /* SXY0..2 = vertices 2, 1, 0; SZ0..3 = vertices 3, 2, 1, 0 */
        if (Psyz_GteReadflg() < 0) {
            continue;
        }
        storeXy(&p->x2, 12);
        storeXy(&p->x1, 13);
        storeXy(&p->x0, 14);
        Psyz_GteNclip();
        if ((s32)Psyz_GteDataRead(24) >= 0) {
            /* Fallback: keep the quad if triangle (2, 1, 3) faces the viewer. */
            Psyz_GteDataWrite(14, (u32)(u16)p->x3 | ((u32)(u16)p->y3 << 16));
            Psyz_GteNclip();
            if ((s32)Psyz_GteDataRead(24) <= 0) {
                continue;
            }
        }
        Psyz_GteAvsz4();
        Psyz_GteDataWrite(6, w4);
        loadV(0, normalAt(ws, w2 & 0xFFFF));
        loadV(1, normalAt(ws, w2 >> 16));
        loadV(2, normalAt(ws, w3 & 0xFFFF));
        Psyz_GteCommand(GTE_NCCT);
        storeRgb(&p->r0, 20);
        storeRgb(&p->r1, 21);
        storeRgb(&p->r2, 22);
        loadV(0, normalAt(ws, w3 >> 16));
        Psyz_GteCommand(GTE_NCCS);
        storeRgb(&p->r3, 22);
        linkPacket(ws, p, 8);
    }
    ws->primWrite = slot;
    return el;
}
