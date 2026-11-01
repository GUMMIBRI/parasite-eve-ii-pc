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
