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
void StCdInterrupt(void) {}

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
