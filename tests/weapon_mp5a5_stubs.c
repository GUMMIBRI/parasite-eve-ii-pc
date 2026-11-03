/* Storage and no-ops for the effect/render code that mp5a5.c's muzzle-flash task
 * references; the attack state's fire path never reaches it. */
unsigned char GsWSMATRIX[64], gDisplayState[1024], gGpuCurrentOt[64], gGpuPrimCursor[64];
unsigned char gRandomLcgState[16], gRoomEffectState[1024], gWorldCoordTransientPointLights[4096];
void actorRenderComposeCoord(void* c) { (void)c; }
void effectDrawScreenTint(void) { }
void effectKillTask(void* t) { (void)t; }
void gpuSetPrimitiveBlendMode(void) { }
