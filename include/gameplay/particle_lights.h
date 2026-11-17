/* MPL-2.0. PE2 adaptation of CPE PE1 directional particle-light contribution. */
#ifndef PE2_PARTICLE_LIGHTS_H
#define PE2_PARTICLE_LIGHTS_H
#include "main/coord.h"
#include "main/task_types.h"
#include "gameplay/effects.h"
#include <stdint.h>
typedef struct Pe2ParticleModelFrame {
    double world[3][3], translation[3], normal[3][3];
    uint64_t serial;
    int valid;
} Pe2ParticleModelFrame;
void Pe2ParticleLightsSetMode(int enabled);
int Pe2ParticleLightsGetMode(void);
int Pe2ParticleLightsGetStatus(void); /*0 off,1 no changed colour yet,2 contributed*/
const char *Pe2ParticleLightsGetReason(void);
/* Optional root-owned frame hooks. Lazy epoch retirement independently protects
 * every producer/consumer if those hooks are not installed. Commit seals list. */
void Pe2ParticleLightsBeginFrame(void);
void Pe2ParticleLightsCommit(void);
int Pe2ParticleLightsSealAvailable(void);
void Pe2ParticleLightsEmitPixelSpark(const Task *, const GfxCoord *, const EffectWork *, unsigned colour);
void Pe2ParticleLightsPrepareModel(Pe2ParticleModelFrame *, const TmdStreamWorkspace *, const MATRIX *part, const MATRIX *view);
void Pe2ParticleLightsApply(const Pe2ParticleModelFrame *, const SVECTOR *vertex, const SVECTOR *normal, void *rgb, uint32_t authoredColour);
#endif
