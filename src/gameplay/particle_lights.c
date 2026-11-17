/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 * Adapted directional gain/peak-gated colour policy from accepted CPE PE1
 * Build17 pe_particle_light_native.h (exact reference retained). PE2 source
 * ownership/epoch/model bindings are new, no PE1 actor IDs or structures.
 * Renderer-thread CPU only. No simulation/RNG/GTE/texture/palette mutation. */
#include "gameplay/particle_lights.h"
#include "gameplay/display.h"
#include "gameplay/effect_tasks.h"
#include "gameplay/world_collision.h"
#include "gameplay/scene.h"
#include "main/session.h"
#include "main/display.h"
#include "main/gfx.h"
#include <stdint.h>
#include <math.h>
#include <string.h>
extern void effectTileTaskA4(Task *); /* original global producer */
enum { LIGHT_CAP=8, MODEL_CAP=16, SPARK_TICKS=8, SPARK_RADIUS=192 };
typedef struct { double p[3]; unsigned rgb[3],radius; } Light;
typedef struct {
    unsigned anim; s32 loop,half; uintptr_t ot,session,grid,effects;
    unsigned char location[6]; MATRIX view;
} Epoch;
static struct {
    int enabled,hasEpoch,sealed,status;
    uint64_t serial;
    Epoch epoch;
    const char *reason;
    Light light[LIGHT_CAP];unsigned count,models;
    struct {uintptr_t model,source,buffer;} receiver[MODEL_CAP];
} state;
static int currentEpoch(Epoch *e) {
    memset(e,0,sizeof *e);
    if(!gGameSession||!gWorldCollisionActiveGrid||!gRoomEffectState||
       !gGameSession->location.stage||gDisplayState.displayOwner!=0||!gGpuCurrentOt||gDisplayState.otBuffer<0||gDisplayState.otBuffer>1)return 0;
    e->anim=gDisplayState.animFrame;e->loop=gDisplayState.loopCount;e->half=gDisplayState.otBuffer;
    e->ot=(uintptr_t)gGpuCurrentOt;e->session=(uintptr_t)gGameSession;
    e->grid=(uintptr_t)gWorldCollisionActiveGrid;e->effects=(uintptr_t)gRoomEffectState;
    memcpy(e->location,&gGameSession->location,6);e->view=gGfxViewCoord.workm;
    return 1;
}
static int same(const Epoch *a,const Epoch *b) {
    return a->anim==b->anim&&a->loop==b->loop&&a->half==b->half&&a->ot==b->ot&&
        a->session==b->session&&a->grid==b->grid&&a->effects==b->effects&&
        !memcmp(a->location,b->location,6)&&!memcmp(&a->view,&b->view,sizeof(MATRIX));
}
static void clearEpoch(const Epoch *e,int valid) {
    state.count=0;state.models=0;state.sealed=0;state.status=state.enabled?1:0;
    state.reason=state.enabled?"original-awaiting-current-spark":"off";
    state.hasEpoch=valid;if(valid)state.epoch=*e;
    if(state.serial!=UINT64_MAX)state.serial++;else{state.hasEpoch=0;state.reason="original-epoch-exhausted";}
}
static int refresh(void) {
    Epoch e;int valid=currentEpoch(&e);
    if(!valid||!state.hasEpoch||!same(&state.epoch,&e))clearEpoch(&e,valid);
    return state.enabled&&state.hasEpoch;
}
void Pe2ParticleLightsSetMode(int enabled) {
    enabled=enabled!=0;if(enabled==state.enabled)return;
    state.enabled=enabled;Epoch e;int valid=currentEpoch(&e);clearEpoch(&e,valid);
}
int Pe2ParticleLightsGetMode(void){return state.enabled;}
int Pe2ParticleLightsGetStatus(void){if(state.enabled)refresh();return state.enabled?state.status:0;}
const char *Pe2ParticleLightsGetReason(void){if(state.enabled)refresh();return state.reason?state.reason:"off";}
void Pe2ParticleLightsBeginFrame(void){Epoch e;int valid=currentEpoch(&e);clearEpoch(&e,valid);}
void Pe2ParticleLightsCommit(void){if(refresh())state.sealed=1;}
int Pe2ParticleLightsSealAvailable(void){if(!state.enabled||!refresh())return 0;state.sealed=1;return state.count!=0;}
static int inverse(const double m[3][3],double out[3][3]) {
    double det=m[0][0]*(m[1][1]*m[2][2]-m[1][2]*m[2][1])-m[0][1]*(m[1][0]*m[2][2]-m[1][2]*m[2][0])+m[0][2]*(m[1][0]*m[2][1]-m[1][1]*m[2][0]);
    if(!__builtin_isfinite(det)||fabs(det)<1e-8)return 0;
    double r[3][3]={
      {(m[1][1]*m[2][2]-m[1][2]*m[2][1])/det,(m[0][2]*m[2][1]-m[0][1]*m[2][2])/det,(m[0][1]*m[1][2]-m[0][2]*m[1][1])/det},
      {(m[1][2]*m[2][0]-m[1][0]*m[2][2])/det,(m[0][0]*m[2][2]-m[0][2]*m[2][0])/det,(m[0][2]*m[1][0]-m[0][0]*m[1][2])/det},
      {(m[1][0]*m[2][1]-m[1][1]*m[2][0])/det,(m[0][1]*m[2][0]-m[0][0]*m[2][1])/det,(m[0][0]*m[1][1]-m[0][1]*m[1][0])/det}};
    memcpy(out,r,sizeof r);return 1;
}
static int uniform(const double r[3][3]) {
    double n[3]={0};for(int i=0;i<3;i++)for(int j=0;j<3;j++)n[i]+=r[i][j]*r[i][j];
    double mean=(n[0]+n[1]+n[2])/3;if(mean<1e-8||!__builtin_isfinite(mean))return 0;
    for(int i=0;i<3;i++)if(fabs(n[i]-mean)>mean*.02)return 0;
    for(int i=0;i<3;i++)for(int j=i+1;j<3;j++){double dot=0;for(int k=0;k<3;k++)dot+=r[i][k]*r[j][k];if(fabs(dot)>mean*.02)return 0;}return 1;
}
static int viewInverse(const MATRIX *view,double out[3][3]) {
    double r[3][3];for(int i=0;i<3;i++)for(int j=0;j<3;j++)r[i][j]=view->m[i][j]/4096.0;
    return uniform(r)&&inverse(r,out);
}
void Pe2ParticleLightsEmitPixelSpark(const Task *task,const GfxCoord *coord,const EffectWork *work,unsigned colour) {
    if(!state.enabled||!refresh())return;
    if(state.sealed){state.reason="original-late-spark-not-added";return;}
    if(state.count==LIGHT_CAP)return;
    if(!task||task->callback!=effectTileTaskA4||task->bodyKind!=TASK_BODY_COORD||
       !task->extra.coordBody||task->extra.coordBody->coord!=coord||!coord||!work||
       task->spawnArg2.pointer!=work||work->age>=SPARK_TICKS||work->angle<1||work->angle>2||!task->state||
       !(colour&0x00ffffffu))return;
    /* The ORIGINAL callback composed this pose before advancing local motion;
     * current workm is exactly the source tile's current position even though
     * composeStamp is now dirty for the NEXT update. Never recompose here. */
    const GfxCoord *seen[64];unsigned count=0;
    for(const GfxCoord *p=coord;p!=&gGfxViewCoord;p=p->parent){
        if(!p||count==64)return;for(unsigned i=0;i<count;i++)if(seen[i]==p)return;seen[count++]=p;
    }
    double inv[3][3];if(!viewInverse(&state.epoch.view,inv))return;
    Light l={0};
    for(int i=0;i<3;i++){
        for(int k=0;k<3;k++)l.p[i]+=inv[i][k]*((double)coord->workm.t[k]-state.epoch.view.t[k]);
        if(!__builtin_isfinite(l.p[i])||fabs(l.p[i])>32760)return;
        unsigned c=(colour>>(i*8))&255;l.rgb[i]=c>127?255:c*2;
    }
    l.radius=SPARK_RADIUS;state.light[state.count++]=l;state.reason="current-sparks-collected";
}
void Pe2ParticleLightsPrepareModel(Pe2ParticleModelFrame *f,const TmdStreamWorkspace *ws,const MATRIX *part,const MATRIX *view) {
    memset(f,0,sizeof *f);if(!state.enabled||!refresh()||!state.sealed||!state.count||!ws||!ws->obj||!part||!view||memcmp(view,&state.epoch.view,sizeof(MATRIX)))return;
    const TmdObject *model=ws->obj;
    unsigned slot;for(slot=0;slot<state.models;slot++)if(state.receiver[slot].model==(uintptr_t)model)break;
    if(slot==state.models){if(state.models==MODEL_CAP)return;state.receiver[slot].model=(uintptr_t)model;state.receiver[slot].source=(uintptr_t)model->source;state.receiver[slot].buffer=(uintptr_t)model->buffer;state.models++;}
    else if(state.receiver[slot].source!=(uintptr_t)model->source||state.receiver[slot].buffer!=(uintptr_t)model->buffer)return;
    double invView[3][3],invWorld[3][3];if(!viewInverse(view,invView))return;
    for(int i=0;i<3;i++)for(int j=0;j<3;j++)for(int k=0;k<3;k++)f->world[i][j]+=invView[i][k]*(part->m[k][j]/4096.0);
    if(!uniform(f->world)||!inverse(f->world,invWorld))return;
    for(int i=0;i<3;i++){
        for(int k=0;k<3;k++)f->translation[i]+=invView[i][k]*((double)part->t[k]-view->t[k]);
        for(int j=0;j<3;j++)f->normal[i][j]=invWorld[j][i];
    }
    f->serial=state.serial;f->valid=1;
}
void Pe2ParticleLightsApply(const Pe2ParticleModelFrame *f,const SVECTOR *vertex,const SVECTOR *normal,void *rgb,uint32_t authored) {
    if(!f||!f->valid||!state.enabled||!refresh()||f->serial!=state.serial||!state.sealed||!vertex||!normal||!rgb)return;
    double point[3],n[3]={0};const s16 v[]={vertex->vx,vertex->vy,vertex->vz},sn[]={normal->vx,normal->vy,normal->vz};
    double originalLen=(double)sn[0]*sn[0]+(double)sn[1]*sn[1]+(double)sn[2]*sn[2];
    if(originalLen<1024.0*1024||originalLen>8192.0*8192)return;
    for(int i=0;i<3;i++){
        point[i]=f->translation[i];for(int k=0;k<3;k++){point[i]+=f->world[i][k]*v[k];n[i]+=f->normal[i][k]*sn[k];}
        if(!__builtin_isfinite(point[i])||fabs(point[i])>32760)return;
    }
    double len=n[0]*n[0]+n[1]*n[1]+n[2]*n[2];if(!__builtin_isfinite(len)||len<1e-8)return;len=sqrt(len);for(int i=0;i<3;i++)n[i]/=len;
    unsigned gain[3]={0};
    /* Accepted PE1 exact directional falloff and per-channel gain cap. */
    for(unsigned i=0;i<state.count;i++){
        const Light *l=&state.light[i];double d[]={l->p[0]-point[0],l->p[1]-point[1],l->p[2]-point[2]};
        double distance=d[0]*d[0]+d[1]*d[1]+d[2]*d[2],radius=(double)l->radius*l->radius;
        if(!__builtin_isfinite(distance)||distance>=radius||distance<1e-8)continue;
        double length=sqrt(distance),ndl=(n[0]*d[0]+n[1]*d[1]+n[2]*d[2])/length;
        if(ndl<=0)continue;if(ndl>1)ndl=1;
        double fade=1.0-distance/radius,weight=fade*fade*ndl*32.0/255.0;
        for(int c=0;c<3;c++)gain[c]+=(unsigned)(l->rgb[c]*weight+0.5);
    }
    for(int c=0;c<3;c++)if(gain[c]>48)gain[c]=48;
    unsigned peak=authored&255;if(((authored>>8)&255)>peak)peak=(authored>>8)&255;if(((authored>>16)&255)>peak)peak=(authored>>16)&255;
    if(!peak||!(gain[0]|gain[1]|gain[2]))return;
    uint32_t base;memcpy(&base,rgb,sizeof base);uint32_t lit=base&0xff000000u;
    for(int c=0;c<3;c++){unsigned v=((base>>(8*c))&255)+(peak*gain[c]+64)/128;if(v>255)v=255;lit|=v<<(8*c);}
    if(lit!=base){memcpy(rgb,&lit,sizeof lit);state.status=2;state.reason="current-spark-contributed-colour-unobserved";}
}
