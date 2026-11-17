#ifndef PE2_PARTICLE_GEOMETRY_H
#define PE2_PARTICLE_GEOMETRY_H
#include "main/task_types.h"
#include "main/coord.h"
#include "gameplay/effects.h"
#include <libgpu.h>
void Pe2ParticleGeometrySetMode(int mode); /*0 Original default,1 Hybrid,2 New*/
int Pe2ParticleGeometryGetMode(void);
int Pe2ParticleGeometryGetStatus(void); /*0 Original,1 original fallback,2 mesh queued*/
const char *Pe2ParticleGeometryGetReason(void);
/* Call ONLY after original pixel TILE + its original additive draw mode and
 * independent light registration. Returns1 after complete bounded OT admission.
 * Unsupported keeps original. New collapses original point ONLY after success. */
int Pe2ParticleGeometryPixelSpark(const Task *, const GfxCoord *, const EffectWork *, TILE *original, s32 sortingDepth);
#endif
