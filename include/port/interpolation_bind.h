/* MPL-2.0. Original PE2 producer lifetime bridge. */
#ifndef PE_INTERPOLATION_BIND_H
#define PE_INTERPOLATION_BIND_H
#include <stdint.h>
typedef struct {uint64_t serial;uint32_t originalAnimFrame;int currentBuffer,nextBuffer,currentY,nextY;} PeInterpFrame;
#if defined(PE2_PS5_HOST)
void peInterpCreate(void* model);
void peInterpAttach(void* model,void* task);
void peInterpRetire(void* model,int destroy);
void peInterpReset(void);
void peInterpRetireAllBuffers(void);
void peInterpSetHostBlocked(int blocked);
void peInterpBuildBegin(void* model,unsigned half);
void peInterpBuildRecord(void* model,unsigned half,unsigned part,const void* record,unsigned kind,unsigned count,unsigned stride,const void* before,const void* after,const void* preBefore,const void* preAfter);
void peInterpBuildEnd(void* model,unsigned half);
void peInterpDraw(void* model);
void peInterpBeforeOt(int buffer);
void peInterpPrepare(void);
int peInterpCurrentFrame(PeInterpFrame* out);
#else
#define peInterpCurrentFrame(a) 0
#define peInterpCreate(a) ((void)0)
#define peInterpAttach(a,b) ((void)0)
#define peInterpRetire(a,b) ((void)0)
#define peInterpReset() ((void)0)
#define peInterpRetireAllBuffers() ((void)0)
#define peInterpSetHostBlocked(a) ((void)0)
#define peInterpBuildBegin(a,b) ((void)0)
#define peInterpBuildRecord(a,b,c,d,e,f,g,h,i,j,k) ((void)0)
#define peInterpBuildEnd(a,b) ((void)0)
#define peInterpDraw(a) ((void)0)
#define peInterpBeforeOt(a) ((void)0)
#define peInterpPrepare() ((void)0)
#endif
#endif
