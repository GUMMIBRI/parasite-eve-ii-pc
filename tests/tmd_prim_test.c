/* Pre-transformed G3/G4 handlers: facing cull, depth cull, OT bucket and link. */
#include <stdio.h>
#include <string.h>
#include <psyz.h>
#include <libgpu.h>
#include <psyz/gte.h>
#include "tmd.h"
#include "main/tmd_types.h"

#define FAIL(m) do { puts("FAIL: " m); return 1; } while (0)

int main(void)
{
    static OT_TYPE ot[1024];
    static s32 sz[1024];
    POLY_G3 tri[3]; POLY_G4 quad[2];
    TmdStreamWorkspace ws; u32 el[6];
    memset(&ws, 0, sizeof ws); memset(tri, 0, sizeof tri); memset(quad, 0, sizeof quad);

    Psyz_GteCtrlWrite(29, 341); Psyz_GteCtrlWrite(30, 256); /* ZSF3, ZSF4 */
    sz[0] = 100; sz[1] = 200; sz[2] = 300; sz[3] = 0x80000000u | 5; /* index*4 byte offsets */
    /* tri[0] front-facing, tri[1] back-facing, tri[2] front-facing with a rejected depth */
    tri[0].x0 = 0; tri[0].y0 = 0; tri[0].x1 = 10; tri[0].y1 = 0; tri[0].x2 = 0; tri[0].y2 = 10;
    tri[1].x0 = 0; tri[1].y0 = 0; tri[1].x1 = 0; tri[1].y1 = 10; tri[1].x2 = 10; tri[1].y2 = 0;
    tri[2] = tri[0];
    ws.preXformWrite = (u8*)tri; ws.szTable = sz; ws.ot = (u_long*)ot; ws.otDepthShift = 0;
    ws.elemCount = 3; ws.elemStride = 2;
    /* offsets: corner0=0, corner1=4, corner2=8 ; third element uses the rejected entry (12) */
    el[0] = 0 | (4u << 16); el[1] = 8; el[2] = 0 | (4u << 16); el[3] = 8; el[4] = 12 | (4u << 16); el[5] = 8;
    u32* end = tmdDrawStreamPrimG3PreXform(&ws, 0, el);
    if (end != el + 6) FAIL("g3 return cursor");
    if ((u8*)ws.preXformWrite != (u8*)(tri + 3)) FAIL("g3 packet cursor");
    if (ot[3].tag != (u_long)&tri[0]) FAIL("g3 not linked in bucket 3");
    if (tri[0].code != 0x30 || ((P_TAG*)&tri[0])->len != 6) FAIL("g3 code/len");
    if (tri[1].code != 0 || tri[2].code != 0) FAIL("culled packets modified");

    /* Quad: first triangle front-facing; zsf4 256 -> OTZ = sum*256>>12 */
    quad[0].x0 = 0; quad[0].y0 = 0; quad[0].x1 = 10; quad[0].y1 = 0; quad[0].x2 = 0; quad[0].y2 = 10; quad[0].x3 = 10; quad[0].y3 = 10;
    quad[1] = quad[0]; quad[1].x1 = 0; quad[1].y1 = 10; quad[1].x2 = 10; quad[1].y2 = 0; quad[1].x3 = 20; quad[1].y3 = 20; /* both windings reject */
    memset(ot, 0, sizeof ot);
    ws.preXformWrite = (u8*)quad; ws.elemCount = 2;
    el[0] = 0 | (4u << 16); el[1] = 8 | (4u << 16); el[2] = el[0]; el[3] = el[1];
    end = tmdDrawStreamPrimG4PreXform(&ws, 0, el);
    if (end != el + 4) FAIL("g4 return cursor");
    /* depths 100+200+300+(sz[1]=200) = 800 -> *256>>12 = 50 -> bucket 3 */
    if (ot[3].tag != (u_long)&quad[0]) { printf("otz=%u code=%x\n", Psyz_GteDataRead(7), quad[0].code); for (int i=0;i<64;i++) if (ot[i].tag) printf("bucket %d\n", i); FAIL("g4 not linked in bucket 3"); }
    if (quad[0].code != 0x38 || ((P_TAG*)&quad[0])->len != 8) FAIL("g4 code/len");
    /* Textured pre-transformed triangle: front-facing accepted, opcode by flags */
    {
        POLY_GT3 t[1]; memset(t, 0, sizeof t); memset(ot, 0, sizeof ot);
        t[0].x0 = 0; t[0].y0 = 0; t[0].x1 = 10; t[0].y1 = 0; t[0].x2 = 0; t[0].y2 = 10;
        ws.preXformWrite = (u8*)t; ws.elemCount = 1; ws.elemStride = 2;
        el[0] = 0 | (4u << 16); el[1] = 8;
        end = tmdDrawStreamPrimGt3PreXform(&ws, 0x02, el);
        if (end != el + 2 || t[0].code != 0x36 || ((P_TAG*)&t[0])->len != 9) FAIL("gt3 prexform");
        if (ot[3].tag != (u_long)&t[0]) FAIL("gt3 prexform link");
        memset(t, 0, sizeof t); t[0].x1 = 10; t[0].y2 = 10; ws.preXformWrite = (u8*)t; memset(ot, 0, sizeof ot);
        tmdDrawStreamPrimGt3PreXform(&ws, 0x10, el);
        if (t[0].code != 0) FAIL("gt3 prexform reverse must cull front face");
    }
    puts("tmd prim OK");
    return 0;
}
