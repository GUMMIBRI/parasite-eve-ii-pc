#ifndef PE2_MODEL_FILL_H
#define PE2_MODEL_FILL_H
#include "main/tmd_types.h"
#include <stdint.h>
#include "gameplay/particle_lights.h"
/* Renderer thread, default Off. Modes0 original,1 neutral,2 world key.
 * Status0 off,1 waiting/unsupported,2 owned lit source prepared (not observed). */
typedef struct Pe2ModelFillFrame {
    float rotation[3][3];
    int preset;
    int directional;
    Pe2ParticleModelFrame particles;
} Pe2ModelFillFrame;
void Pe2ModelFillSetMode(int mode);
int Pe2ModelFillGetMode(void);
int Pe2ModelFillGetStatus(void);
const char *Pe2ModelFillGetReason(void);
void Pe2ModelFillPrepare(Pe2ModelFillFrame *, const TmdStreamWorkspace *);
void Pe2ModelFillApply(const Pe2ModelFillFrame *, const SVECTOR *normal, const SVECTOR *vertex, void *rgb);
void Pe2ModelFillDisable(Pe2ModelFillFrame *);
#endif
