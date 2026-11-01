/* Host implementations of the PSY-Q calls PsyZ does not provide. */
#include <math.h>
#include <stdlib.h>

#include <psyz.h>
#include <libcd.h>
#include <libgte.h>
#include "port/psyq_compat.h"

/* libcd: the host disc image is always present and always a CD-ROM. */
int CdDiskReady(int mode)
{
    (void)mode;
    return CdlComplete;
}

int CdGetDiskType(void)
{
    return CdlCdromFormat;
}

/* The host CD layer needs no interrupt pump. */

/* libapi heap 3: the host allocator replaces the PlayStation arena. The arena
 * arguments are accepted and ignored. */
void InitHeap3(unsigned long* head, unsigned long size)
{
    (void)head;
    (void)size;
}

void* malloc3(unsigned long size)
{
    return malloc(size);
}

void free3(void* ptr)
{
    free(ptr);
}

/* libgte MatrixNormal: scale each row of the 3x3 to unit length (4096 = 1.0).
 * NOTE: approximates the SDK routine, whose exact fixed-point behaviour has not
 * been verified against hardware or an emulator trace. */
void MatrixNormal(MATRIX* m, MATRIX* n)
{
    for (int r = 0; r < 3; r++) {
        double x = m->m[r][0], y = m->m[r][1], z = m->m[r][2];
        double len = sqrt(x * x + y * y + z * z);
        for (int c = 0; c < 3; c++) {
            double v = len > 0.0 ? (double)m->m[r][c] * 4096.0 / len : 0.0;
            n->m[r][c] = (short)lround(v);
        }
    }
}

/* v1 = (m * v0) >> 12, exact in 64 bits (the SDK splits the vector to stay in
 * 32 bits; results agree unless the SDK's own intermediate overflows). */
VECTOR* ApplyMatrixLV(MATRIX* m, VECTOR* v0, VECTOR* v1)
{
    long long in[3] = { v0->vx, v0->vy, v0->vz };
    int out[3];
    for (int i = 0; i < 3; i++) {
        long long sum = 0;
        for (int j = 0; j < 3; j++) sum += (long long)m->m[i][j] * in[j];
        out[i] = (int)(sum >> 12);
    }
    v1->vx = out[0]; v1->vy = out[1]; v1->vz = out[2];
    return v1;
}

/* v1 = (transpose(m) * v0) >> 12 */
VECTOR* ApplyTransposeMatrixLV(MATRIX* m, VECTOR* v0, VECTOR* v1)
{
    long long in[3] = { v0->vx, v0->vy, v0->vz };
    int out[3];
    for (int i = 0; i < 3; i++) {
        long long sum = 0;
        for (int j = 0; j < 3; j++) sum += (long long)m->m[j][i] * in[j];
        out[i] = (int)(sum >> 12);
    }
    v1->vx = out[0]; v1->vy = out[1]; v1->vz = out[2];
    return v1;
}

SVECTOR* ApplyMatrixSV(MATRIX* m, SVECTOR* v0, SVECTOR* v1)
{
    long long in[3] = { v0->vx, v0->vy, v0->vz };
    short out[3];
    for (int i = 0; i < 3; i++) {
        long long sum = 0;
        for (int j = 0; j < 3; j++) sum += (long long)m->m[i][j] * in[j];
        out[i] = (short)(sum >> 12);
    }
    v1->vx = out[0]; v1->vy = out[1]; v1->vz = out[2];
    return v1;
}

/* Natural log of a positive integer, scaled by 4096. Rounded to nearest so exact
 * powers of two divide cleanly by ln(2) * 4096 = 2839. */
long cln(long x)
{
    return x > 0 ? lround(log((double)x) * 4096.0) : 0;
}

/* ---- PSY-Q calls PsyZ declares but does not implement ----------------------
 * Memory card, controller extras and SPU reverb are placeholders until their
 * subsystems are ported (phases 4-5): they report "nothing present". */

#include <libgpu.h>
#include <libmcrd.h>
#include <libspu.h>
#include <libetc.h>
#include <psyz/gte.h>

void MemCardInit(long val) { (void)val; }
void MemCardStart(void) {}
void MemCardClose(void) {}
long MemCardExist(long chan) { (void)chan; return 0; }
long MemCardAccept(long chan) { (void)chan; return 0; }
long MemCardOpen(long chan, char* file, long flag) { (void)chan; (void)file; (void)flag; return 0; }
long MemCardCreateFile(long chan, char* file, long blocks) { (void)chan; (void)file; (void)blocks; return 0; }
long MemCardFormat(long chan) { (void)chan; return 0; }
long MemCardReadData(unsigned long* adrs, long offset, long bytes) { (void)adrs; (void)offset; (void)bytes; return 0; }
long MemCardWriteData(unsigned long* adrs, long offset, long bytes) { (void)adrs; (void)offset; (void)bytes; return 0; }
long MemCardSync(long mode, long* cmds, long* result)
{
    (void)mode;
    if (cmds) *cmds = 0;
    if (result) *result = 0;
    return 1; /* nothing pending */
}

void PadInitDirect(unsigned char* pad1, unsigned char* pad2)
{
    if (pad1) memset(pad1, 0xFF, 34);
    if (pad2) memset(pad2, 0xFF, 34);
}
int PadInfoMode(int port, int term, int offs) { (void)port; (void)term; (void)offs; return 0; }
int PadSetMainMode(int port, int offs, int lock) { (void)port; (void)offs; (void)lock; return 1; }

long SpuReserveReverbWorkArea(long on_off) { return on_off; }
void SpuLSetVoiceAttr(int num, SpuLVoiceAttr* argList) { (void)num; (void)argList; }

unsigned long SetSp(unsigned long new_sp) { (void)new_sp; return 0; }
void SetMem(unsigned long n) { (void)n; }

/* Drawing is synchronous on the host, so a draw never needs to be suspended. */
u_long* BreakDraw(void) { return (u_long*)0; }
void ContinueDraw(u_long* inst_ot, u_long* cont_ot) { (void)inst_ot; (void)cont_ot; }

int StoreImage2(RECT* rect, u_long* p) { return StoreImage(rect, p); }

/* DR_STP: GPU "set mask bit" command (E6h); bit 0 sets the mask on draw, bit 1 checks it. */
void SetDrawStp(DR_STP* p, int stp)
{
    setlen(p, 2);
    p->code[0] = 0xE6000000u | (stp ? 1u : 0u);
    p->code[1] = 0;
}

/* GTE rotation matrix times m, result in m (SDK MulRotMatrix). */
MATRIX* MulRotMatrix(MATRIX* m)
{
    short r[3][3];
    u32   c[5];
    for (int i = 0; i < 5; i++) c[i] = Psyz_GteCtrlRead(i);
    r[0][0] = (short)(c[0] & 0xFFFF); r[0][1] = (short)(c[0] >> 16);
    r[0][2] = (short)(c[1] & 0xFFFF); r[1][0] = (short)(c[1] >> 16);
    r[1][1] = (short)(c[2] & 0xFFFF); r[1][2] = (short)(c[2] >> 16);
    r[2][0] = (short)(c[3] & 0xFFFF); r[2][1] = (short)(c[3] >> 16);
    r[2][2] = (short)c[4];
    short out[3][3];
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++) {
            long long sum = 0;
            for (int k = 0; k < 3; k++) sum += (long long)r[i][k] * m->m[k][j];
            out[i][j] = (short)(sum >> 12);
        }
    memcpy(m->m, out, sizeof out);
    return m;
}

/* m2 = m0 * m1 (3x3 only; translation untouched). */
MATRIX* MulMatrix0(MATRIX* m0, MATRIX* m1, MATRIX* m2)
{
    short out[3][3];
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++) {
            long long sum = 0;
            for (int k = 0; k < 3; k++) sum += (long long)m0->m[i][k] * m1->m[k][j];
            out[i][j] = (short)(sum >> 12);
        }
    memcpy(m2->m, out, sizeof out);
    return m2;
}

MATRIX* RotMatrix_gte(SVECTOR* r, MATRIX* m) { return RotMatrix(r, m); }

/* v1 = RT * v0 + TR (SVECTOR in and out); *flag receives the GTE FLAG word. */
void RotTransSV(SVECTOR* v0, SVECTOR* v1, int* flag)
{
    Psyz_GteDataWrite(0, (u32)(u16)v0->vx | ((u32)(u16)v0->vy << 16));
    Psyz_GteDataWrite(1, (u32)(u16)v0->vz);
    Psyz_GteCommand(0x4A480012);
    v1->vx = (short)Psyz_GteDataRead(9);
    v1->vy = (short)Psyz_GteDataRead(10);
    v1->vz = (short)Psyz_GteDataRead(11);
    if (flag) *flag = Psyz_GteReadflg();
}

/* libpress / MDEC bitstream decoding is part of the movie phase. */
int DecDCTvlc2(u_long* bs, u_long* buf, u_short* table) { (void)bs; (void)buf; (void)table; return -1; }
void DecDCTvlcBuild(u_short* table) { (void)table; }
int DecDCTvlcSize2(int size) { return size; }

void LoadAverageCol(unsigned char* c0, unsigned char* c1, int w0, int w1, unsigned char* out)
{
    int i;
    for (i = 0; i < 3; i++) {
        int v = (c0[i] * w0 + c1[i] * w1) >> 12;
        out[i] = v < 0 ? 0 : v > 255 ? 255 : (unsigned char)v;
    }
}

unsigned char gHostScratchpad[0x400] __attribute__((aligned(0x400)));

unsigned char gHostRam[0x200000] __attribute__((aligned(0x1000)));
unsigned int gHostGpuStatus[2] = { 0x1C000000u, 0 }; /* ready bits set */
void* _freep; /* libapi heap3 search cursor; unused with the host allocator */
