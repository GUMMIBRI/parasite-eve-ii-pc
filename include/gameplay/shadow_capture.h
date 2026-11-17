#ifndef PE2_SHADOW_CAPTURE_H
#define PE2_SHADOW_CAPTURE_H
#include "main/tmd_types.h"
#include <libgpu.h>
#include <stdint.h>
#include "main/task_types.h"
#include "gameplay/world_collision.h"
enum { PE2_SHADOW_FACES=512, PE2_SHADOW_RUNS=96 };
typedef struct { short xy[8]; } Pe2ShadowRunQuad;
typedef struct {
    Pe2ShadowRunQuad quads[PE2_SHADOW_RUNS];
    unsigned count, shade, shadeValid, sourceRaw, sourceShade, originalOtIndex;
    unsigned originalTpage, originalClut;
    unsigned char originalUv[8];
    unsigned animFrame;
    s32 loopCount, otBuffer;
    uintptr_t otBase, modelIdentity, sourceIdentity, originalPacket;
    short originalXy[8];
    unsigned long long serial;
} Pe2ShadowRunBatch;
void Pe2ShadowSetMode(int mode);
int Pe2ShadowGetMode(void);
int Pe2ShadowGetStatus(void); /*0 off,1 original/unavailable,2 CPU outline prepared*/
const char *Pe2ShadowGetReason(void);
void Pe2ShadowCaptureBegin(TmdStreamWorkspace *, const TmdObject *);
void Pe2ShadowCaptureRecord(TmdStreamWorkspace *, const void *handler, int count);
void Pe2ShadowCaptureFace(TmdStreamWorkspace *, const SVECTOR *, const SVECTOR *, const SVECTOR *, const SVECTOR *);
void Pe2ShadowCaptureEnd(TmdStreamWorkspace *);
void Pe2ShadowReceiverBegin(void);
void Pe2ShadowReceiverBind(const Task *, const GfxCoord *, const VECTOR3 *, const WorldCollisionReceiver *, int shade, const POLY_FT4 *original);
/* Immutable copied CPU output only; caller still needs atomic GPU admission.
 * No source shadow is suppressed by any API in this module. */
int Pe2ShadowGetRunBatch(Pe2ShadowRunBatch *);
#endif
