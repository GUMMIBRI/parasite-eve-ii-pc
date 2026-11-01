/* Lit draw handlers: projection into the packet, facing cull, lighting and link. */
#include <stdio.h>
#include <string.h>
#include <psyz.h>
#include <libgpu.h>
#include <libgte.h>
#include <psyz/gte.h>
#include "tmd.h"
#include "main/tmd_types.h"

u32* tmdXformStreamVerts(TmdStreamWorkspace*, s32, u32*);

#define FAIL(m) do { puts("FAIL: " m); return 1; } while (0)

int main(void)
{
    static OT_TYPE ot[1024];
    static SVECTOR verts[8], normals[2];
    POLY_G3 tri[2]; POLY_G4 quad[2];
    TmdStreamWorkspace ws; u32 el[10];
    MATRIX rot = {{{4096,0,0},{0,4096,0},{0,0,4096}}, {0,0,0}};
    MATRIX light = {{{0,0,4096},{0,0,0},{0,0,0}}, {0,0,0}}; /* light 0 along +Z */
    MATRIX color = {{{4096,0,0},{4096,0,0},{4096,0,0}}, {0,0,0}};
    memset(&ws, 0, sizeof ws); memset(tri, 0, sizeof tri); memset(quad, 0, sizeof quad);

    SetRotMatrix(&rot); SetLightMatrix(&light); SetColorMatrix(&color);
    SetGeomScreen(500); SetGeomOffset(160, 120);
    Psyz_GteCtrlWrite(5, 0); Psyz_GteCtrlWrite(6, 0); Psyz_GteCtrlWrite(7, 1000);
    Psyz_GteCtrlWrite(29, 341); Psyz_GteCtrlWrite(30, 256);
    SetBackColor(0, 0, 0);

    /* Triangle (front-facing on screen): three verts at z=0 (+1000 translation). */
    verts[0].vx = -100; verts[0].vy = -100; verts[0].vz = 0;
    verts[1].vx =  100; verts[1].vy = -100; verts[1].vz = 0;
    verts[2].vx = -100; verts[2].vy =  100; verts[2].vz = 0;
    verts[3].vx =  100; verts[3].vy =  100; verts[3].vz = 0;
    normals[0].vx = 0; normals[0].vy = 0; normals[0].vz = 4096;
    ws.primWrite = (u8*)tri; ws.verts = verts; ws.normals = normals; ws.ot = (u_long*)ot;
    ws.otDepthShift = 0; ws.elemCount = 2; ws.elemStride = 4;
    /* element: v0=0, v1=8, v2=16 (SVECTOR = 8 bytes); normals all 0; colour 0x30 80 80 80 */
    el[0] = 0 | (8u << 16); el[1] = 16 | (0u << 16); el[2] = 0; el[3] = 0;
    /* second element: swapped winding -> culled */
    el[4] = 8 | (0u << 16); el[5] = 16 | (0u << 16); el[6] = 0; el[7] = 0;
    /* colour word is el[3]; give it a code byte */
    el[3] = 0x34808080; el[7] = 0x34808080;
    u32* end = tmdDrawStreamPrimG3CornerNormals(&ws, 0, el);
    if (end != el + 8) FAIL("g3 cursor");
    if ((u8*)ws.primWrite != (u8*)(tri + 2)) FAIL("g3 packet cursor");
    if (tri[0].x0 != 160 - 50 || tri[0].y0 != 120 - 50) { printf("x0,y0=%d,%d\n", tri[0].x0, tri[0].y0); FAIL("g3 projection v0"); }
    if (tri[0].x1 != 160 + 50 || tri[0].y1 != 120 - 50) FAIL("g3 projection v1");
    if (tri[0].x2 != 160 - 50 || tri[0].y2 != 120 + 50) FAIL("g3 projection v2");
    if (tri[0].code != 0x34) FAIL("g3 code byte");
    if (((P_TAG*)&tri[0])->len != 6) FAIL("g3 len");
    int linked = 0; for (int i = 0; i < 1024; i++) if (ot[i].tag == (u_long)&tri[0]) linked = 1;
    if (!linked) FAIL("g3 not linked");
    /* Quad: v0=0 v1=8 v2=16 v3=24, normals 0, colour with code byte */
    memset(ot, 0, sizeof ot);
    ws.primWrite = (u8*)quad; ws.elemCount = 1; ws.elemStride = 5;
    el[0] = 0 | (8u << 16); el[1] = 16 | (24u << 16); el[2] = 0; el[3] = 0; el[4] = 0x3C808080;
    end = tmdDrawStreamPrimG4CornerNormals(&ws, 0, el);
    if (end != el + 5) FAIL("g4 cursor");
    if (quad[0].x0 != 110 || quad[0].y0 != 70 || quad[0].x1 != 210 || quad[0].y1 != 70) FAIL("g4 projection 0/1");
    if (quad[0].x2 != 110 || quad[0].y2 != 170 || quad[0].x3 != 210 || quad[0].y3 != 170) FAIL("g4 projection 2/3");
    if (quad[0].code != 0x3C || ((P_TAG*)&quad[0])->len != 8) FAIL("g4 code/len");
    linked = 0; for (int i = 0; i < 1024; i++) if (ot[i].tag == (u_long)&quad[0]) linked = 1;
    if (!linked) FAIL("g4 not linked");
    /* One-normal quad and triangle */
    memset(ot, 0, sizeof ot); memset(quad, 0, sizeof quad); memset(tri, 0, sizeof tri);
    ws.primWrite = (u8*)quad; ws.elemCount = 1; ws.elemStride = 4;
    el[0] = 0 | (8u << 16); el[1] = 16 | (24u << 16); el[2] = 0; el[3] = 0x3C808080;
    end = tmdDrawStreamPrimG4(&ws, 0, el);
    if (end != el + 4 || quad[0].x3 != 210 || quad[0].y3 != 170 || quad[0].code != 0x3C) FAIL("g4 one-normal");
    if (quad[0].r0 != quad[0].r3 || quad[0].g1 != quad[0].g2) FAIL("g4 one-normal colour repeated");
    ws.primWrite = (u8*)tri; ws.elemCount = 1; ws.elemStride = 3;
    el[0] = 0 | (8u << 16); el[1] = 16; el[2] = 0x34808080;
    end = tmdDrawStreamPrimG3(&ws, 0, el);
    if (end != el + 3 || tri[0].x2 != 110 || tri[0].y2 != 170 || tri[0].code != 0x34) FAIL("g3 one-normal");
    if (tri[0].r0 != tri[0].r2) FAIL("g3 one-normal colour repeated");
    /* Vertex pre-pass: element = { vertex 8 | normal 0 << 16, dest xy@0 colour@4 } */
    {
        static s32 depth[16]; u8 pkt[16]; u32 xy, rgb;
        memset(depth, 0, sizeof depth); memset(pkt, 0, sizeof pkt);
        ws.preXformWrite = pkt; ws.szTable = depth; ws.elemCount = 1; ws.elemStride = 2;
        el[0] = 8 | (0u << 16); el[1] = 0 | (4u << 16);
        end = tmdXformStreamVerts(&ws, 0, el);
        if (end != el + 2) FAIL("xform cursor");
        memcpy(&xy, pkt, 4); memcpy(&rgb, pkt + 4, 4);
        if ((short)(xy & 0xFFFF) != 210 || (short)(xy >> 16) != 70) FAIL("xform xy");
        if (depth[1] != 1000) { printf("depth=%d\n", depth[1]); FAIL("xform depth cache"); }
        if ((rgb & 0xFFFFFF) == 0) FAIL("xform lit colour");
    }
    puts("tmd ops OK");
    return 0;
}
