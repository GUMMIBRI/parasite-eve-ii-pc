/* tmdDrawModelStream installs, per part, rotation R, translation, and the light
 * matrix B*R in the GTE; check against a plain C product (Q12). */
#include <stdio.h>
#include <string.h>
#include <psyz/gte.h>
#include "tmd.h"
#include "main/tmd_types.h"
#include "main/coord.h"

static s16 q(int v) { return (s16)v; }

int main(void)
{
    TmdStreamWorkspace ws; TmdObject model; GfxCoord part; u32 stream[5] = { 0x21, 0, 0x00000002, (u32)-2, (u32)-1 }; /* one empty record */
    stream[1] = tmdHandlerToId((void*)tmdSkipStreamRecord);
    memset(&ws, 0, sizeof ws); memset(&model, 0, sizeof model); memset(&part, 0, sizeof part);
    s16 R[3][3] = {{ 4096, 0, 0 }, { 0, 2896, -2896 }, { 0, 2896, 2896 }};
    s16 B[3][3] = {{ 3000, 1000, -500 }, { -700, 2500, 1200 }, { 100, -2000, 3500 }};
    memcpy(part.workm.m, R, sizeof R); memcpy(ws.viewLightRotation, B, sizeof B);
    part.workm.t[0] = 11; part.workm.t[1] = -22; part.workm.t[2] = 33;
    model.partCount = 1; model.coords = &part;
    tmdDrawModelStream(&ws, 0, stream, &model);

    s16 exp[3][3];
    for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) {
        long long sum = 0;
        for (int k = 0; k < 3; k++) sum += (long long)B[i][k] * R[k][j];
        exp[i][j] = q((int)(sum >> 12));
    }
    unsigned got[5]; for (int i = 0; i < 5; i++) got[i] = Psyz_GteCtrlRead(8 + i);
    unsigned want[5] = {
        (u16)exp[0][0] | ((unsigned)(u16)exp[0][1] << 16), (u16)exp[0][2] | ((unsigned)(u16)exp[1][0] << 16),
        (u16)exp[1][1] | ((unsigned)(u16)exp[1][2] << 16), (u16)exp[2][0] | ((unsigned)(u16)exp[2][1] << 16),
        (u16)exp[2][2] };
    for (int i = 0; i < 5; i++) if (got[i] != want[i]) { printf("light reg %d: %08x != %08x\n", 8 + i, got[i], want[i]); return 1; }
    if ((int)Psyz_GteCtrlRead(5) != 11 || (int)Psyz_GteCtrlRead(6) != -22 || (int)Psyz_GteCtrlRead(7) != 33) { puts("translation FAIL"); return 1; }
    if (Psyz_GteCtrlRead(0) != ((u16)R[0][0] | ((unsigned)(u16)R[0][1] << 16))) { puts("rotation FAIL"); return 1; }
    puts("tmd model OK");
    return 0;
}
