#ifndef PORT_PSYQ_COMPAT_H
#define PORT_PSYQ_COMPAT_H

/* Small PSY-Q definitions the game uses that PsyZ's headers leave out. */

#include <psyz.h>
#include <libgpu.h>
#include <libgte.h>

/* libgte: the GTE treats 4096 as 1.0. */
#ifndef ONE
#define ONE 4096
#endif

/* libspu: voice channel masks, 32-bit as on the PlayStation (`long` is 64-bit on the host). */
#ifndef SPU_KEYCH
#define SPU_KEYCH(x) ((unsigned int)1 << (x))
#endif
#ifndef SPU_VOICECH
#define SPU_VOICECH(x) SPU_KEYCH(x)
#endif

/* libgpu: fill a DR_TWIN texture-window packet; `p` is any primitive pointer of that size. */
#ifndef setTexWindow
#define setTexWindow(p, tw) SetTexWindow((DR_TWIN*)(p), (tw))
#endif

/* libpad connection states and PadInfoMode terms (documented in PsyZ, not declared). */
enum {
    PadStateDiscon = 0, PadStateFindPad = 1, PadStateFindCTP1 = 2,
    PadStateFindCTP2 = 3, PadStateReqInfo = 4, PadStateExecCmd = 5, PadStateStable = 6
};
enum { InfoModeCurID = 1, InfoModeCurExID = 2, InfoModeCurExOffs = 3, InfoModeIdTable = 4 };

#ifndef ABS
#define ABS(x) ((x) < 0 ? -(x) : (x))
#endif

/* Calls PsyZ leaves out; implemented by the host platform layer. */
int CdDiskReady(int mode);
int CdGetDiskType(void);
void StCdInterrupt(void);
void InitHeap3(unsigned long* head, unsigned long size);
void* malloc3(unsigned long size);
void free3(void* ptr);

/* libgs world-screen matrices (defined in main/gfxlight.c). */
extern MATRIX GsWSMATRIX;
extern MATRIX GsLIGHTWSMATRIX;

/* libgte matrix-vector products PsyZ does not declare; see psyq_host.c. */
VECTOR* ApplyMatrixLV(MATRIX* m, VECTOR* v0, VECTOR* v1);
VECTOR* ApplyTransposeMatrixLV(MATRIX* m, VECTOR* v0, VECTOR* v1);
SVECTOR* ApplyMatrixSV(MATRIX* m, SVECTOR* v0, SVECTOR* v1);

#endif
