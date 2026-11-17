/* MPL-2.0. Positive task/model/build ownership; no simulation-clock changes. */
#include "port/interpolation_bind.h"
#if defined(PE2_PS5_HOST)
#include "main/tmd_types.h"
#include "main/task_types.h"
#include "main/display.h"
#include "main/gamemain.h"
#include "main/fs.h"
#include "main/session.h"
#include "main/gfx.h"
#include <psyz/gpu.h>
#include <psyz/video.h>
#include <psyz/cap_font.h>
#include <psyz/gte.h>
#include <string.h>
#include <stddef.h>
#include <stdint.h>
extern s32 gDisplayVSyncWaitMode;
enum { OWNERS=128, RECORDS=64, PAIRS=4096, PARTS=64, MORPH_POSES=2048 };
typedef struct {const uint32_t* words;unsigned part,kind,count,stride,offset;} Record;
typedef struct {
 TmdObject *model;Task *task;TmdSource *source;void *buffer;GfxCoord *coords;
 uint64_t generation,digest[2];unsigned halfBytes,mask,n[2],bad,ambiguous,registered,flags,lastDraw;
 const u32 *stream,*partCounts;const SVECTOR *verts,*normals;const TmdBone *skeleton;int parts;
 const GfxCoord *parents[PARTS];Record records[2][RECORDS];
} Owner;
static Owner owners[OWNERS];static uint64_t generation;static int exhausted;
/* Each original frame owns a bounded by-value bank. Keys name the actual live
 * model generation, stream part and source byte offset, never packet arenas.
 * No source vertex pointers are retained by a pose entry. */
typedef struct {uint64_t owner;unsigned part,offset;PsyzPgxpMorphSnapshot pose;} MorphPose;
static MorphPose morphPoses[2][MORPH_POSES];
static unsigned morphCount[2],morphBank;static int morphReset,morphOverflow;
static unsigned short morphIndex[2][4096];

static unsigned char canonical[262144];static size_t used;
static uint32_t drawAnim;static unsigned framePairs,frameFallback;
static uint64_t originalFrame;static PeInterpFrame frame;static int lastBuffer=-1;
static uint32_t lastAnim,location;static int frameReady,frameY,hostBlocked;static MATRIX camera;
static void invalidate(void){Psyz_GpuClearInterpolationPackets();Psyz_GpuPrepareInterpolatedPresent(-1);frameReady=0;for(unsigned i=0;i<OWNERS;i++)owners[i].registered=0;}
void peInterpReset(void){invalidate();memset(owners,0,sizeof owners);memset(morphCount,0,sizeof morphCount);memset(morphIndex,0,sizeof morphIndex);}
void peInterpRetireAllBuffers(void){invalidate();for(unsigned i=0;i<OWNERS;i++){owners[i].buffer=NULL;owners[i].mask=0;owners[i].bad=0;}}
void peInterpSetHostBlocked(int blocked){hostBlocked=!!blocked;if(blocked)invalidate();}
static Owner* find(const void *model){for(unsigned i=0;i<OWNERS;i++)if(owners[i].model==model)return &owners[i];return NULL;}
static int fresh(Owner *o){if(exhausted||generation==UINT64_MAX){exhausted=1;invalidate();return 0;}o->generation=++generation;return 1;}
void peInterpCreate(void *model){
 if(!model||exhausted)return;Owner *o=find(model);if(o){memset(o,0,sizeof *o);invalidate();}
 if(!o)for(unsigned i=0;i<OWNERS;i++)if(!owners[i].model){o=&owners[i];break;}
 if(!o)return;memset(o,0,sizeof *o);o->model=model;fresh(o);
}
void peInterpAttach(void *model,void *task){Owner *o=find(model);if(!o)return;if(o->task&&o->task!=task){o->bad=1;o->ambiguous=1;invalidate();return;}o->task=task;}
void peInterpRetire(void *model,int destroy){Owner *o=find(model);if(!o)return;invalidate();o->buffer=NULL;o->mask=0;o->bad=0;if(destroy)memset(o,0,sizeof *o);}
void peInterpBuildBegin(void *model,unsigned half){
 Owner *o=find(model);TmdObject *m=model;if(!o||half>1)return;
 if(o->buffer!=m->buffer||o->source!=m->source||o->halfBytes!=m->bufferHalfBytes||(m->source&&(o->stream!=m->source->stream||o->verts!=m->source->verts||o->normals!=m->source->normals||o->skeleton!=m->source->skeleton||o->partCounts!=m->source->partVertexCounts||o->parts!=m->partCount))){
  invalidate();if(!fresh(o))return;o->mask=0;o->buffer=m->buffer;o->source=m->source;o->halfBytes=m->bufferHalfBytes;
  o->stream=m->source?m->source->stream:NULL;o->verts=m->source?m->source->verts:NULL;
  o->normals=m->source?m->source->normals:NULL;o->skeleton=m->source?m->source->skeleton:NULL;o->parts=m->partCount;o->partCounts=m->source?m->source->partVertexCounts:NULL;
 }
 if(o->mask==3){o->mask=0;o->bad=0;o->registered=0;invalidate();}
 o->n[half]=0;
 if(!m->buffer||!m->source||m->partCount<0||m->partCount>PARTS||m->source->partCount!=m->partCount)o->bad=1;
}
void peInterpBuildRecord(void *model,unsigned half,unsigned part,const void *record,unsigned kind,unsigned count,unsigned stride,const void *before,const void *after,const void *preBefore,const void *preAfter){
 Owner *o=find(model);if(!o||half>1||o->bad)return;
 if(before==after&&preBefore==preAfter)return;
 uintptr_t base=(uintptr_t)o->buffer+half*o->halfBytes,a=(uintptr_t)before,b=(uintptr_t)after;
 unsigned size=kind==3?sizeof(POLY_GT3):kind==4?sizeof(POLY_GT4):0;
 if(!size||preBefore!=preAfter||!count||stride<4||count>PAIRS||part>=PARTS||o->n[half]>=RECORDS||a<base||b<a||b-base>o->halfBytes||b-a!=(uint64_t)count*size){o->bad=1;return;}
 o->records[half][o->n[half]++]=(Record){record,part,kind,count,stride,(unsigned)(a-base)};
}
void peInterpBuildEnd(void *model,unsigned half){Owner *o=find(model);if(!o||half>1)return;o->mask|=1u<<half;}
static int append16(unsigned word){if(used+2>sizeof canonical)return 0;canonical[used++]=(unsigned char)word;canonical[used++]=(unsigned char)(word>>8);return 1;}
static MorphPose *morphFind(unsigned bank,uint64_t owner,unsigned part,unsigned offset,unsigned *empty){
 uint64_t h=owner^((uint64_t)part<<32)^((uint64_t)offset*UINT64_C(0x9e3779b97f4a7c15));
 unsigned slot=(unsigned)(h^(h>>32))&4095u;
 for(unsigned n=0;n<4096;++n,slot=(slot+1)&4095u){unsigned index=morphIndex[bank][slot];
  if(!index){if(empty)*empty=slot;return NULL;}
  MorphPose *p=&morphPoses[bank][index-1];
  if(p->owner==owner&&p->part==part&&p->offset==offset)return p;
 }if(empty)*empty=4096;return NULL;
}
static int morphVector(const SVECTOR *v,uint64_t owner,unsigned part,unsigned offset){
 PsyzPgxpMorphSnapshot current;
 if(!Psyz_GteGetPgxpMorphSnapshot(v,&current))return 0;
 unsigned bucket=0;MorphPose *entry=morphFind(morphBank,owner,part,offset,&bucket);
 if(!entry){
  unsigned index=morphCount[morphBank];
  if(index==MORPH_POSES||bucket==4096){morphOverflow=1;return -1;}
  morphPoses[morphBank][index]=(MorphPose){owner,part,offset,current};
  morphIndex[morphBank][bucket]=(unsigned short)(index+1);++morphCount[morphBank];
 }else{
  /* A changed producer snapshot inside one original draw is not a coherent pose. */
  const PsyzPgxpMorphSnapshot *a=&entry->pose;
  for(unsigned axis=0;axis<3;++axis)if(a->integer[axis]!=current.integer[axis]||a->xyz[axis]!=current.xyz[axis]||
      a->rest[axis]!=current.rest[axis]||a->delta[axis]!=current.delta[axis]){morphOverflow=1;return -1;}
  if(a->weight!=current.weight){morphOverflow=1;return -1;}
 }
 const MorphPose *previous=morphFind(morphBank^1u,owner,part,offset,NULL);
 const PsyzPgxpMorphSnapshot *before=previous?&previous->pose:NULL;
 if(!before)morphReset=1;
 for(unsigned axis=0;axis<3;++axis){
  /* Stable rest+delta is the positive gteMIMefunc source association. Weight
   * and actual coordinates may change; normals/topology/style may not. */
  if(before&&(before->rest[axis]!=current.rest[axis]||before->delta[axis]!=current.delta[axis]))morphReset=1;
  if(!append16(current.rest[axis])||!append16(current.delta[axis]))return -1;
 }
 return 1;
}
static int vector(const SVECTOR *v){
 double precise[3];
 if(!append16(v->vx)||!append16(v->vy)||!append16(v->vz))return 0;
 int present=Psyz_GteGetPgxpMorph(v,precise);
 if(!append16(present))return 0;
 if(present)for(unsigned axis=0;axis<3;axis++){
  uint64_t bits;memcpy(&bits,&precise[axis],sizeof bits);
  for(unsigned word=0;word<4;word++)if(!append16((unsigned)(bits>>(16*word))))return 0;
 }
 return 1;
}
static int contextAllowed(void){return !exhausted&&!hostBlocked&&Psyz_VideoGetSpeed()==1&&gGameSession&&gDisplayState.gameMode==DISPLAY_GAME_ACTIVE&&gDisplayState.gameRunning&&gDisplayState.displayOwner==DISPLAY_OWNER_GAME_LOOP&&gDisplayState.pendingMode==DISPLAY_MODE_NONE&&gDisplayState.demoScene==DISPLAY_DEMO_NONE&&gGameMainHaltFlags==0&&gCdCmdQueue.movieStep==0&&gGameSession->eventState==0&&gDisplayVSyncWaitMode==2&&gDisplayState.height==240;}
static int allowed(void){return contextAllowed()&&Psyz_GpuGetFrameInterpolation();}
void peInterpDraw(void *model){
 Owner *o=find(model);TmdObject *m=model;uint64_t hash[2];unsigned pairs=0;
 if(drawAnim!=gDisplayState.animFrame){drawAnim=gDisplayState.animFrame;framePairs=0;frameFallback=0;morphBank^=1u;morphCount[morphBank]=0;memset(morphIndex[morphBank],0,sizeof morphIndex[morphBank]);}
 if(frameFallback)return;
 if(!o)return;
 if(!allowed()){invalidate();return;}
 if(o->bad||o->ambiguous||o->mask!=3||!o->task||o->task->extra.tmd!=m||o->task->bodyKind!=TASK_BODY_TMD||o->source!=m->source||o->buffer!=m->buffer||o->halfBytes!=m->bufferHalfBytes||o->n[0]!=o->n[1]||o->stream!=m->source->stream||o->verts!=m->source->verts||o->normals!=m->source->normals||o->skeleton!=m->source->skeleton||o->partCounts!=m->source->partVertexCounts||o->parts!=m->partCount||m->source->partCount!=m->partCount||m->partCount<0||m->partCount>PARTS||(m->partCount&&!m->coords)){if(o->registered)invalidate();return;}
 if(o->lastDraw==gDisplayState.animFrame){frameFallback=1;invalidate();return;}
 o->lastDraw=gDisplayState.animFrame;
 used=0;morphReset=0;morphOverflow=0;
 if(o->partCounts)for(int part=0;part<m->partCount;part++)if(!append16(o->partCounts[part])||!append16(o->partCounts[part]>>16)){o->bad=1;invalidate();return;}
 for(unsigned r=0;r<o->n[0];r++){
  Record *a=&o->records[0][r],*b=&o->records[1][r];
  if(a->words!=b->words||a->part!=b->part||a->kind!=b->kind||a->count!=b->count||a->stride!=b->stride||a->offset!=b->offset||pairs+a->count>PAIRS){o->bad=1;invalidate();return;}
  if(a->words[-1]!=((a->count<<16)|a->stride)||
     (a->words[-3]&~2u)!=(a->kind==3?0x38u:0x78u)){o->bad=1;invalidate();return;}
  pairs+=a->count;
  for(unsigned i=0;i<a->count;i++){
   const uint32_t *el=a->words+(size_t)i*a->stride;
   for(unsigned w=0;w<a->stride;w++)if(!append16(el[w])||!append16(el[w]>>16)){o->bad=1;invalidate();return;}
   unsigned offsets[4]={el[0]&65535,el[0]>>16,el[1]&65535,el[1]>>16};
   unsigned normals[4]={el[1]>>16,el[2]&65535,el[2]>>16,0};
   if(a->kind==4){normals[0]=el[2]&65535;normals[1]=el[2]>>16;normals[2]=el[3]&65535;normals[3]=el[3]>>16;}
   for(unsigned v=0;v<a->kind;v++){
    if(offsets[v]%sizeof(SVECTOR)||normals[v]%sizeof(SVECTOR)||!m->source->verts||!m->source->normals){o->bad=1;invalidate();return;}
    const SVECTOR *vertex=(const SVECTOR*)((const unsigned char*)m->source->verts+offsets[v]);
    /* Explicit pose kind prevents an absent/unproven companion from aliasing
     * an admitted morph. Unknown direct writes retain full-coordinate hash. */
    double precise[3];int hasMorph=Psyz_GteGetPgxpMorph(vertex,precise);
    if(!append16(hasMorph)){o->bad=1;invalidate();return;}
    int pose=hasMorph?morphVector(vertex,o->generation,a->part,offsets[v]):0;
    if(pose<0||(hasMorph&&pose!=1)){if(morphOverflow)frameFallback=1;else o->bad=1;invalidate();return;}
    if((!hasMorph&&!vector(vertex))||!vector((const SVECTOR*)((const unsigned char*)m->source->normals+normals[v]))){o->bad=1;invalidate();return;}
   }
  }
 }
 if(framePairs+pairs>PAIRS){frameFallback=1;invalidate();return;}
 framePairs+=pairs;
 Psyz_FontHash128(canonical,used,hash);
 int reset=morphReset||!o->registered||o->coords!=m->coords||o->flags!=m->flags||o->digest[0]!=hash[0]||o->digest[1]!=hash[1];
 for(int i=0;i<m->partCount;i++)if(o->parents[i]!=m->coords[i].parent)reset=1;
 for(unsigned r=0;r<o->n[0];r++){
  Record *a=&o->records[0][r];unsigned size=a->kind==3?sizeof(POLY_GT3):sizeof(POLY_GT4);
  unsigned payload=a->kind==3?offsetof(POLY_GT3,r0):offsetof(POLY_GT4,r0);
  for(unsigned i=0;i<a->count;i++){
   const unsigned char *first=(const unsigned char*)m->buffer+a->offset+i*size+payload;
   if(reset)Psyz_GpuRegisterInterpolationPair(first,first+m->bufferHalfBytes);
   else Psyz_GpuEnsureInterpolationPair(first,first+m->bufferHalfBytes);
  }
 }
 o->registered=1;o->coords=m->coords;o->flags=m->flags;o->digest[0]=hash[0];o->digest[1]=hash[1];
 for(int i=0;i<m->partCount;i++)o->parents[i]=m->coords[i].parent;
}
static int sameCamera(void){for(unsigned i=0;i<3;i++){if(camera.t[i]!=gGfxViewCoord.workm.t[i])return 0;for(unsigned j=0;j<3;j++)if(camera.m[i][j]!=gGfxViewCoord.workm.m[i][j])return 0;}return 1;}
void peInterpBeforeOt(int buffer){
 if(!contextAllowed()||buffer<0||buffer>1||gDisplayState.otBuffer!=buffer||lastAnim==gDisplayState.animFrame){invalidate();return;}
 uint32_t current=GAME_LOCATION_WORD(gGameSession->location);
 if(location!=current||!sameCamera()||lastAnim+1u!=gDisplayState.animFrame||lastBuffer==buffer)invalidate();
 if(originalFrame==UINT64_MAX){exhausted=1;invalidate();return;}
 ++originalFrame;lastBuffer=buffer;
 location=current;camera=gGfxViewCoord.workm;lastAnim=gDisplayState.animFrame;
 if(Psyz_GpuGetFrameInterpolation()&&!frameFallback)Psyz_GpuBeginInterpolationFrame();
 else Psyz_GpuPrepareInterpolatedPresent(-1);
 frameY=gDisplayState.drawEnv[buffer].clip.y;
 frame=(PeInterpFrame){originalFrame,gDisplayState.animFrame,buffer,buffer^1,frameY,gDisplayState.drawEnv[buffer^1].clip.y};frameReady=1;
}
int peInterpCurrentFrame(PeInterpFrame *out){if(!out||!frameReady)return 0;*out=frame;return 1;}
void peInterpPrepare(void){
 if(!frameReady||frameFallback||!allowed()||location!=GAME_LOCATION_WORD(gGameSession->location)||!sameCamera()){invalidate();return;}
 Psyz_GpuPrepareInterpolatedPresent(frameY);
}
#endif
