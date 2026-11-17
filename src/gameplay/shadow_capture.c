/* PE2 bounded real-producer capture and exact original receiver proof.
 * Disjoint silhouette raster/run math adapted from PE1 Build17's explicitly
 * MIT-licensed planar_shadow_native.h (retained in reference/). No PE1 structs.
 * CPU only, renderer thread. Never emits/suppresses original GPU packets. */
#include "gameplay/shadow_capture.h"
#include "main/tmd.h"
#include "main/session.h"
#include "main/display.h"
#include "main/gfx.h"
#include "main/mem.h"
#include <psyz/gte.h>
#include <psyz/shadow_metadata.h>
#include <stdint.h>
#include <math.h>
#include <string.h>
/* Handler names not all declared in main/tmd.h on this source baseline. */
extern u32 *tmdDrawStreamPrimG3CornerNormals(TmdStreamWorkspace*,s32,u32*);
extern u32 *tmdDrawStreamPrimG4CornerNormals(TmdStreamWorkspace*,s32,u32*);
extern u32 *tmdDrawStreamPrimG3(TmdStreamWorkspace*,s32,u32*);
extern u32 *tmdDrawStreamPrimG4(TmdStreamWorkspace*,s32,u32*);
extern u32 *tmdDrawStreamGt3(TmdStreamWorkspace*,s32,u32*);
extern u32 *tmdDrawStreamGt4(TmdStreamWorkspace*,s32,u32*);
extern u32 *tmdDrawStreamPrimGt3OneNormal(TmdStreamWorkspace*,s32,u32*);
extern u32 *tmdDrawStreamPrimGt4OneNormal(TmdStreamWorkspace*,s32,u32*);
extern u32 *tmdDrawStreamPrimGt3CornerColors(TmdStreamWorkspace*,s32,u32*);
extern u32 *tmdDrawStreamPrimGt4CornerColors(TmdStreamWorkspace*,s32,u32*);
typedef struct { double p[4][3]; unsigned count; } Face;
typedef struct { int x,z; } Point;
typedef struct { unsigned x0,x1,y0,y1; } Run;
typedef struct { unsigned anim; s32 loop; uintptr_t ot; s32 half; } Epoch;
static struct {
    int mode,status,active,failed,complete,receiver;
    const char *reason;
    uintptr_t workspace,model,source,coords,vertices;
    int partCount;
    Epoch epoch,receiverEpoch;
    MATRIX view,anchor;
    uintptr_t receiverModel,receiverSource;
    WorldCollisionReceiver floor;
    VECTOR3 hit;
    unsigned shade,sourceRaw,originalTpage,originalClut,faces,expected,recordRemaining,originalOtIndex;
    unsigned char originalUv[8];
    unsigned projectionH;
    s32 projectionX,projectionY;
    uintptr_t originalPacket;
    short originalXy[8];
    uint64_t serial;
    Face face[PE2_SHADOW_FACES];
    Pe2ShadowRunBatch batch;
} state;
static Epoch epoch(void) {
    return (Epoch){gDisplayState.animFrame,gDisplayState.loopCount,(uintptr_t)gGpuCurrentOt,gDisplayState.otBuffer};
}
static int sameEpoch(Epoch a,Epoch b) {return a.anim==b.anim&&a.loop==b.loop&&a.ot==b.ot&&a.half==b.half;}
static void reject(const char *reason) {state.failed=1;state.complete=0;state.batch.count=0;state.status=1;state.reason=reason;Psyz_GpuShadowBeginEpoch(0);}
void Pe2ShadowSetMode(int mode) {
    uint64_t serial=state.serial;
    memset(&state,0,sizeof state);state.serial=serial;state.mode=mode==1;
    Psyz_GpuShadowBeginEpoch(0);
    state.status=state.mode?1:0;state.reason=state.mode?"original-awaiting-capture":"off";
}
int Pe2ShadowGetMode(void){return state.mode;}
int Pe2ShadowGetStatus(void){return state.mode?state.status:0;}
const char *Pe2ShadowGetReason(void){return state.reason?state.reason:"off";}
static int uniform(const MATRIX *m,double out[3][3],double *scale) {
    double n[3]={0};
    for(int r=0;r<3;r++)for(int c=0;c<3;c++){out[r][c]=m->m[r][c]/4096.0;n[r]+=out[r][c]*out[r][c];}
    double mean=(n[0]+n[1]+n[2])/3;
    if(mean<1e-8||!__builtin_isfinite(mean))return 0;
    for(int r=0;r<3;r++)if(fabs(n[r]-mean)>mean*.02)return 0;
    for(int r=0;r<3;r++)for(int c=r+1;c<3;c++){double d=0;for(int k=0;k<3;k++)d+=out[r][k]*out[c][k];if(fabs(d)>mean*.02)return 0;}
    *scale=mean;return 1;
}
static int toWorld(const MATRIX *view,const double in[3],double out[3]) {
    double r[3][3],scale;if(!uniform(view,r,&scale))return 0;
    /* Exact inverse of the accepted current Q12 matrix, rather than assume
     * quantized coefficients are perfectly orthogonal. */
    double det=r[0][0]*(r[1][1]*r[2][2]-r[1][2]*r[2][1])-
        r[0][1]*(r[1][0]*r[2][2]-r[1][2]*r[2][0])+
        r[0][2]*(r[1][0]*r[2][1]-r[1][1]*r[2][0]);
    if(fabs(det)<1e-8)return 0;
    double inv[3][3]={
        {(r[1][1]*r[2][2]-r[1][2]*r[2][1])/det,(r[0][2]*r[2][1]-r[0][1]*r[2][2])/det,(r[0][1]*r[1][2]-r[0][2]*r[1][1])/det},
        {(r[1][2]*r[2][0]-r[1][0]*r[2][2])/det,(r[0][0]*r[2][2]-r[0][2]*r[2][0])/det,(r[0][2]*r[1][0]-r[0][0]*r[1][2])/det},
        {(r[1][0]*r[2][1]-r[1][1]*r[2][0])/det,(r[0][1]*r[2][0]-r[0][0]*r[2][1])/det,(r[0][0]*r[1][1]-r[0][1]*r[1][0])/det}};
    for(int i=0;i<3;i++){out[i]=0;for(int k=0;k<3;k++)out[i]+=inv[i][k]*(in[k]-view->t[k]);if(!__builtin_isfinite(out[i])||fabs(out[i])>32760)return 0;}
    return 1;
}
static int controlled(const TmdObject *model) {
    Task *p=gameGetTaskSlot(GAME_TASK_SLOT_PLAYER);
    return p&&p->bodyKind==TASK_BODY_TMD&&p->extra.tmd==model;
}
static void prepare(void);
static void publish(void);
void Pe2ShadowCaptureBegin(TmdStreamWorkspace *ws,const TmdObject *model) {
    if(!state.mode||!controlled(model))return;
    Psyz_GpuShadowBeginEpoch(0);
    state.active=0;state.complete=0;state.failed=0;state.faces=0;state.expected=0;state.recordRemaining=0;state.batch.count=0;
    state.status=1;state.reason="original-capture-in-progress";
    if(state.serial==UINT64_MAX){reject("original-epoch-exhausted");return;}state.serial++;
    if(!ws||ws->obj!=model||!model->source||!model->buffer||!model->coords||
       model->partCount<2||model->partCount>32||model->partCount!=model->source->partCount||
       !ws->verts||ws->verts!=model->source->verts||model->flags&(TMD_OBJECT_SKIP_ACTIVE_DRAW|TMD_OBJECT_SEMI_TRANS)) {
        reject("original-unknown-controlled-pose");return;
    }
    state.workspace=(uintptr_t)ws;state.model=(uintptr_t)model;state.source=(uintptr_t)model->source;
    state.coords=(uintptr_t)model->coords;state.vertices=(uintptr_t)ws->verts;state.partCount=model->partCount;
    state.epoch=epoch();state.view=gGfxViewCoord.workm;state.anchor=model->coords[1].workm;
    state.projectionH=Psyz_GteCtrlRead(26)&65535u;
    state.projectionX=(s32)Psyz_GteCtrlRead(24);state.projectionY=(s32)Psyz_GteCtrlRead(25);
    state.active=1;
}
void Pe2ShadowCaptureRecord(TmdStreamWorkspace *ws,const void *handler,int count) {
    if(!state.active||(uintptr_t)ws!=state.workspace)return;
    if(state.recordRemaining){reject("original-incomplete-face-record");return;}
    if(count<=0)return;
    const void *allowed[]={tmdDrawStreamPrimG3CornerNormals,tmdDrawStreamPrimG4CornerNormals,
        tmdDrawStreamPrimG3,tmdDrawStreamPrimG4,tmdDrawStreamGt3,tmdDrawStreamGt4,
        tmdDrawStreamPrimGt3OneNormal,tmdDrawStreamPrimGt4OneNormal,
        tmdDrawStreamPrimGt3CornerColors,tmdDrawStreamPrimGt4CornerColors};
    unsigned i;for(i=0;i<sizeof allowed/sizeof allowed[0];i++)if(handler==allowed[i])break;
    if(i==sizeof allowed/sizeof allowed[0]){reject("original-unsupported-model-handler");return;}
    if((unsigned)count>PE2_SHADOW_FACES-state.expected){reject("original-face-budget");return;}
    state.expected+=(unsigned)count;state.recordRemaining=(unsigned)count;
}
void Pe2ShadowCaptureFace(TmdStreamWorkspace *ws,const SVECTOR *a,const SVECTOR *b,const SVECTOR *c,const SVECTOR *d) {
    if(!state.active||state.failed||(uintptr_t)ws!=state.workspace)return;
    if(!state.recordRemaining||state.faces==PE2_SHADOW_FACES||!a||!b||!c){reject("original-face-contract");return;}
    if(!sameEpoch(state.epoch,epoch())||memcmp(&state.view,&gGfxViewCoord.workm,sizeof(MATRIX))){reject("original-view-changed");return;}
    /* Exact current integer producer transform; no previous matrix or layout
     * guesses. Must belong to this current controlled-player model. */
    s16 rot[9];s32 trans[3];
    for(unsigned reg=0;reg<5;reg++){unsigned v=Psyz_GteCtrlRead(reg);rot[reg*2]=(s16)v;if(reg<4)rot[reg*2+1]=(s16)(v>>16);}
    for(unsigned i=0;i<3;i++)trans[i]=(s32)Psyz_GteCtrlRead(5+i);
    const TmdObject *model=ws->obj;int owned=0;
    if((uintptr_t)model!=state.model||(uintptr_t)model->source!=state.source||!controlled(model)||
       (uintptr_t)model->coords!=state.coords||model->partCount!=state.partCount||
       (uintptr_t)ws->verts!=state.vertices||ws->verts!=model->source->verts||
       model->source->partCount!=state.partCount){reject("original-source-changed");return;}
    for(int i=0;i<model->partCount;i++)if(!memcmp(rot,model->coords[i].workm.m,sizeof rot)&&!memcmp(trans,model->coords[i].workm.t,sizeof trans)){owned=1;break;}
    if(!owned){reject("original-unowned-part-transform");return;}
    Face *face=&state.face[state.faces];const SVECTOR *v[]={a,b,c,d};face->count=d?4:3;
    for(unsigned j=0;j<face->count;j++) {
        double in[3];const s16 xyz[]={v[j]->vx,v[j]->vy,v[j]->vz};
        for(int r=0;r<3;r++)in[r]=trans[r]+((double)rot[r*3]*xyz[0]+(double)rot[r*3+1]*xyz[1]+(double)rot[r*3+2]*xyz[2])/4096.0;
        if(!toWorld(&state.view,in,face->p[j])){reject("original-unsupported-world-transform");return;}
    }
    state.faces++;state.recordRemaining--;
}
void Pe2ShadowCaptureEnd(TmdStreamWorkspace *ws) {
    if(!state.active||(uintptr_t)ws!=state.workspace)return;state.active=0;
    if(state.failed)return;
    if(!state.faces||state.faces!=state.expected||state.recordRemaining){reject("original-incomplete-model");return;}
    state.complete=1;state.reason="original-awaiting-exact-receiver";prepare();
}
void Pe2ShadowReceiverBegin(void) {
    Psyz_GpuShadowBeginEpoch(0);
    state.receiver=0;state.batch.count=0;if(state.mode){state.status=1;state.reason="original-awaiting-ground-hit";}
}
void Pe2ShadowReceiverBind(const Task *player,const GfxCoord *coord,const VECTOR3 *hit,const WorldCollisionReceiver *floor,int shade,const POLY_FT4 *original) {
    if(!state.mode||!player||player!=gameGetTaskSlot(GAME_TASK_SLOT_PLAYER)||player->bodyKind!=TASK_BODY_TMD||!player->extra.tmd||!coord||!hit||!floor)return;
    const TmdObject *model=player->extra.tmd;
    if(!model->source||!model->coords||model->partCount<2||coord->parent!=&model->coords[1])return;
    /* Original FT4 must have been actually admitted by the just-completed
     * original drawer, inside the exact main-loop arena half, not a guessed
     * pointer range or an independent task-owned presentation arena. */
    if(!original||gDisplayState.otBuffer<0||gDisplayState.otBuffer>1||!gGpuPrimitiveBufferBase||
       !gGpuPrimitiveBufferBytes||(gGpuPrimitiveBufferBytes&1)||gDisplayState.displayOwner!=0||
       gDisplayState.otDepthShift<0||gDisplayState.otDepthShift>3)return;
    uintptr_t base=(uintptr_t)gGpuPrimitiveBufferBase,half=gGpuPrimitiveBufferBytes/2;
    if(base>UINTPTR_MAX-gGpuPrimitiveBufferBytes)return;
    uintptr_t start=base+(uintptr_t)gDisplayState.otBuffer*half,end=start+half,p=(uintptr_t)original;
    if(p<start||p>end||sizeof(*original)>end-p||(uintptr_t)gGpuPrimCursor!=p+sizeof(*original)||
       (p%_Alignof(POLY_FT4))||(original->code!=0x2e&&original->code!=0x2f)||
       original->tpage!=getTPage(0,GPU_BLEND_SUBTRACT,512,0)||original->clut!=getClut(48,266))return;
    unsigned depth=(Psyz_GteDataRead(19)>>2);
    state.originalOtIndex=(((depth<<(unsigned)gDisplayState.otDepthShift)>>2)&GPU_ORDERING_TABLE_DEPTH_BYTE_MASK)/GPU_OT_TAG_BYTES;
    if((uintptr_t)gGpuCurrentOt[state.originalOtIndex].tag!=(uintptr_t)original)return;
    state.originalPacket=p;state.sourceRaw=original->code==0x2f;
    state.originalTpage=original->tpage;state.originalClut=original->clut;
    const unsigned char uv[]={original->u0,original->v0,original->u1,original->v1,original->u2,original->v2,original->u3,original->v3};
    memcpy(state.originalUv,uv,sizeof uv);
    const short xy[]={original->x0,original->y0,original->x1,original->y1,original->x2,original->y2,original->x3,original->y3};
    memcpy(state.originalXy,xy,sizeof xy);
    state.receiverEpoch=epoch();state.receiverModel=(uintptr_t)model;state.receiverSource=(uintptr_t)model->source;
    state.floor=*floor;state.hit=*hit;state.shade=shade>0&&shade<=255?(unsigned)shade:0;
    state.receiver=1;prepare();
}
/* MIT PE1 Build17 bounded disjoint silhouette raster core. */
static int64_t area(int ax,int az,int bx,int bz,int cx,int cz){return(int64_t)(bx-ax)*(cz-az)-(int64_t)(bz-az)*(cx-ax);}
static int raster(uint32_t mask[32],Point a,Point b,Point c,unsigned *work){
    int64_t ar=area(a.x,a.z,b.x,b.z,c.x,c.z);if(!ar)return 1;
    int x0=a.x<b.x?a.x:b.x,x1=a.x>b.x?a.x:b.x,y0=a.z<b.z?a.z:b.z,y1=a.z>b.z?a.z:b.z;
    if(c.x<x0)x0=c.x;if(c.x>x1)x1=c.x;if(c.z<y0)y0=c.z;if(c.z>y1)y1=c.z;
    x0=x0/2;if(x0<0)x0=0;y0=y0/2;if(y0<0)y0=0;x1=(x1+1)/2;if(x1>=32)x1=31;y1=(y1+1)/2;if(y1>=32)y1=31;
    unsigned need=(unsigned)(x1-x0+1)*(unsigned)(y1-y0+1);if(need>131072-*work)return 0;*work+=need;
    for(int y=y0;y<=y1;y++)for(int x=x0;x<=x1;x++){int u=x*2+1,v=y*2+1;int64_t e0=area(a.x,a.z,b.x,b.z,u,v),e1=area(b.x,b.z,c.x,c.z,u,v),e2=area(c.x,c.z,a.x,a.z,u,v);if(ar>0?(e0>=0&&e1>=0&&e2>=0):(e0<=0&&e1<=0&&e2<=0))mask[y]|=UINT32_C(1)<<x;}return 1;
}
static int runs(const uint32_t mask[32],Run out[PE2_SHADOW_RUNS],unsigned *count){
    *count=0;for(unsigned y=0;y<32;y++)for(unsigned x=0;x<32;){if(!(mask[y]&(UINT32_C(1)<<x))){x++;continue;}unsigned start=x;while(x<32&&(mask[y]&(UINT32_C(1)<<x)))x++;unsigned r;for(r=0;r<*count;r++)if(out[r].x0==start&&out[r].x1==x&&out[r].y1==y){out[r].y1=y+1;break;}if(r==*count){if(*count==PE2_SHADOW_RUNS)return 0;out[(*count)++]=(Run){start,x,y,y+1};}}return *count!=0;
}
static int inside(double x,double z,const WorldCollisionReceiver *floor) {
    const unsigned order[]={0,1,floor->cornerCount==4?3:2,2};int sign=0;
    for(unsigned i=0;i<floor->cornerCount;i++){
        const SVECTOR *a=&floor->corners[order[i]],*b=&floor->corners[order[(i+1)%floor->cornerCount]];
        double cross=(b->vx-a->vx)*(z-a->vz)-(b->vz-a->vz)*(x-a->vx);
        if(fabs(cross)<1e-6)return 0;int s=cross>0?1:-1;if(sign&&sign!=s)return 0;sign=s;
    }return sign!=0;
}
/* Fresh active typed grid only. Never dereference a stored identity pointer.
 * Exact original accepted indices, current descriptor/pool identities and
 * same-frame copied values must still agree; no independent mesh scan. */
static int receiverLive(const WorldCollisionReceiver *floor) {
    if(!floor->valid||(floor->cornerCount!=3&&floor->cornerCount!=4))return 0;
    const WorldCollisionGrid *grid=gWorldCollisionActiveGrid;
    if(!grid||(uintptr_t)grid!=floor->gridIdentity||(uintptr_t)grid->vertices!=floor->verticesIdentity||
       (uintptr_t)grid->normals!=floor->normalsIdentity||(uintptr_t)grid->faces!=floor->facesIdentity||
       !grid->faces||!grid->vertices||!grid->normals||!grid->viewCoord||
       grid->faceCount!=floor->faceCount||grid->faceCount>256||floor->faceIndex>=grid->faceCount||
       memcmp(&floor->face,&grid->faces[floor->faceIndex],sizeof floor->face)||
       memcmp(&floor->view,&grid->viewCoord->workm,sizeof(MATRIX)))return 0;
    if(memcmp(&floor->normal,&grid->normals[floor->face.normalIndex],sizeof(SVECTOR)))return 0;
    for(unsigned i=0;i<floor->cornerCount;i++)
        if(memcmp(&floor->corners[i],&grid->vertices[floor->face.vertexIndices[i]],sizeof(SVECTOR)))return 0;
    return 1;
}
static void prepare(void) {
    if(!state.mode||!state.complete||state.failed||!state.receiver)return;
    if(!sameEpoch(state.epoch,state.receiverEpoch)||!sameEpoch(state.epoch,epoch())||state.model!=state.receiverModel||state.source!=state.receiverSource){state.reason="original-source-epoch-mismatch";return;}
    WorldCollisionReceiver *floor=&state.floor;
    if(!receiverLive(floor)){state.reason="original-receiver-source-changed";return;}
    if(!floor->valid||(floor->cornerCount!=3&&floor->cornerCount!=4)||memcmp(&floor->view,&state.view,sizeof(MATRIX))||floor->normal.vx||floor->normal.vz||floor->normal.vy!=-4096){state.reason="original-unsupported-flat-receiver";return;}
    int y=floor->corners[0].vy;for(unsigned i=1;i<floor->cornerCount;i++)if(floor->corners[i].vy!=y){state.reason="original-nonflat-face";return;}
    /* Strict convex face certificate, not merely a point-plane agreement. */
    {const unsigned order[]={0,1,floor->cornerCount==4?3:2,2};int sign=0;
    for(unsigned i=0;i<floor->cornerCount;i++){
        const SVECTOR *a=&floor->corners[order[i]],*b=&floor->corners[order[(i+1)%floor->cornerCount]],*c=&floor->corners[order[(i+2)%floor->cornerCount]];
        int64_t cross=area(a->vx,a->vz,b->vx,b->vz,c->vx,c->vz);int next=cross>0?1:cross<0?-1:0;
        if(!next||(sign&&sign!=next)){state.reason="original-nonconvex-face";return;}sign=next;
    }}
    double hit[]={state.hit.vx,state.hit.vy,state.hit.vz},worldHit[3];
    if(!toWorld(&floor->view,hit,worldHit)||fabs(worldHit[1]-y)>2||!inside(worldHit[0],worldHit[2],floor)){state.reason="original-receiver-hit-mismatch";return;}
    double projected[PE2_SHADOW_FACES][4][2];double minx=32760,minz=32760,maxx=-32760,maxz=-32760;
    for(unsigned i=0;i<state.faces;i++)for(unsigned j=0;j<state.face[i].count;j++){
        double height=y-state.face[i].p[j][1];if(height < -16||height>4096){state.reason="original-height-unsupported";return;}if(height<0)height=0;
        double x=state.face[i].p[j][0]+height*.5,z=state.face[i].p[j][2]+height*.25;
        if(!__builtin_isfinite(x)||!__builtin_isfinite(z)||fabs(x)>32760||fabs(z)>32760)return;
        projected[i][j][0]=x;projected[i][j][1]=z;
        if(x<minx)minx=x;if(x>maxx)maxx=x;if(z<minz)minz=z;if(z>maxz)maxz=z;
    }
    minx=floorf((float)minx)-1;minz=floorf((float)minz)-1;maxx=ceilf((float)maxx)+1;maxz=ceilf((float)maxz)+1;
    double spanx=maxx-minx,spanz=maxz-minz;if(spanx<=0||spanz<=0||spanx>2048||spanz>2048){state.reason="original-footprint-budget";return;}
    /* Entire expanded raster rectangle must lie inside the ONE original face.
     * Therefore every generated run is supported, not just sampled probes. */
    for(unsigned i=0;i<4;i++)if(!inside(i&1?maxx:minx,i&2?maxz:minz,floor)){state.reason="original-footprint-crosses-floor-edge";return;}
    uint32_t mask[32]={0};unsigned work=0;
    for(unsigned i=0;i<state.faces;i++){
        Point p[4];for(unsigned j=0;j<state.face[i].count;j++)p[j]=(Point){(int)((projected[i][j][0]-minx)*64/spanx),(int)((projected[i][j][1]-minz)*64/spanz)};
        if(!raster(mask,p[0],p[1],p[2],&work)||(state.face[i].count==4&&!raster(mask,p[1],p[3],p[2],&work))){state.reason="original-raster-budget";return;}
    }
    Run run[PE2_SHADOW_RUNS];unsigned count;if(!runs(mask,run,&count)){state.reason="original-run-budget";return;}
    unsigned h=state.projectionH;int32_t ox=state.projectionX,oy=state.projectionY;
    if(h!=(Psyz_GteCtrlRead(26)&65535u)||ox!=(int32_t)Psyz_GteCtrlRead(24)||oy!=(int32_t)Psyz_GteCtrlRead(25)){state.reason="original-camera-changed";return;}
    if(!h){state.reason="original-invalid-camera";return;}
    Pe2ShadowRunBatch pending={0};pending.count=count;pending.serial=state.serial;pending.shade=state.shade/3;if(pending.shade>24)pending.shade=24;
    pending.shadeValid=state.shade!=0&&!state.sourceRaw;
    pending.sourceRaw=state.sourceRaw;pending.sourceShade=state.shade;
    pending.originalTpage=state.originalTpage;pending.originalClut=state.originalClut;
    memcpy(pending.originalUv,state.originalUv,sizeof pending.originalUv);
    for(unsigned i=0;i<count;i++)for(unsigned j=0;j<4;j++){
        double p[]={minx+spanx*(j&1?run[i].x1:run[i].x0)/32,y,minz+spanz*(j&2?run[i].y1:run[i].y0)/32},v[3];
        for(int r=0;r<3;r++){v[r]=state.view.t[r];for(int k=0;k<3;k++)v[r]+=state.view.m[r][k]*p[k]/4096.0;}
        if(v[2]<32||v[2]>65535){state.reason="original-projection-clipped";return;}
        double x=ox/65536.0+h*v[0]/v[2],sy=oy/65536.0+h*v[1]/v[2];if(x< -1024||x>1023||sy< -1024||sy>1023){state.reason="original-projection-clipped";return;}
        pending.quads[i].xy[j*2]=(short)lrint(x);pending.quads[i].xy[j*2+1]=(short)lrint(sy);
    }
    for(unsigned i=0;i<count;i++) {
        const short *q=pending.quads[i].xy;
        int64_t a=area(q[0],q[1],q[2],q[3],q[4],q[5]),b=area(q[2],q[3],q[6],q[7],q[4],q[5]);
        if(!a||!b||(a>0)!=(b>0)){state.reason="original-degenerate-projected-run";return;}
    }
    pending.originalOtIndex=state.originalOtIndex;pending.animFrame=state.epoch.anim;pending.loopCount=state.epoch.loop;
    pending.otBuffer=state.epoch.half;pending.otBase=state.epoch.ot;pending.modelIdentity=state.model;pending.sourceIdentity=state.source;
    pending.originalPacket=state.originalPacket;memcpy(pending.originalXy,state.originalXy,sizeof pending.originalXy);
    state.batch=pending;state.status=2;state.reason=pending.shadeValid?"CPU-outline-prepared-original-shadow-retained":"CPU-outline-prepared-source-palette-unresolved-original-retained";
    publish();
}
int Pe2ShadowGetRunBatch(Pe2ShadowRunBatch *out){
    if(!out||!state.mode||state.status!=2||!state.batch.count||!sameEpoch(state.epoch,epoch())||!receiverLive(&state.floor))return 0;
    Task *player=gameGetTaskSlot(GAME_TASK_SLOT_PLAYER);
    if(!player||player->bodyKind!=TASK_BODY_TMD||(uintptr_t)player->extra.tmd!=state.model||
       !player->extra.tmd->source||(uintptr_t)player->extra.tmd->source!=state.source||
       (uintptr_t)player->extra.tmd->coords!=state.coords||player->extra.tmd->partCount!=state.partCount||
       (uintptr_t)player->extra.tmd->source->verts!=state.vertices||
       (player->extra.tmd->flags&(TMD_OBJECT_SKIP_ACTIVE_DRAW|TMD_OBJECT_SEMI_TRANS))||
       memcmp(&state.anchor,&player->extra.tmd->coords[1].workm,sizeof(MATRIX))||
       memcmp(&state.view,&gGfxViewCoord.workm,sizeof(MATRIX))||
       state.projectionH!=(Psyz_GteCtrlRead(26)&65535u)||state.projectionX!=(s32)Psyz_GteCtrlRead(24)||state.projectionY!=(s32)Psyz_GteCtrlRead(25))return 0;
    *out=state.batch;return 1;
}
/* Publish only from the completing real producer. GPU queue traversal remains
 * the sole draw point; no original OT links or primitive bytes are changed. */
static void publish(void)
{
    Pe2ShadowRunBatch cpu;
    Psyz_GpuShadowBeginEpoch(0);
    if(!Pe2ShadowGetRunBatch(&cpu)||!cpu.serial||cpu.count>PSYZ_SHADOW_RUN_LIMIT)return;
    int mode=Psyz_GpuGetShadowMode();
    if(!mode||(cpu.sourceRaw&&mode!=PSYZ_SHADOW_RAW_PEAK_EXPERIMENTAL)||
        (!cpu.sourceRaw&&(!cpu.shadeValid||!cpu.shade)))return;
    if(gDisplayState.otBuffer<0||gDisplayState.otBuffer>1||cpu.otBuffer!=gDisplayState.otBuffer||
        cpu.otBase!=(uintptr_t)gGpuCurrentOt||!gGpuPrimitiveBufferBase||
        !gGpuPrimitiveBufferBytes||(gGpuPrimitiveBufferBytes&1))return;
    uintptr_t base=(uintptr_t)gGpuPrimitiveBufferBase,half=gGpuPrimitiveBufferBytes/2,p=cpu.originalPacket;
    if(base>UINTPTR_MAX-gGpuPrimitiveBufferBytes)return;
    uintptr_t start=base+(uintptr_t)gDisplayState.otBuffer*half,end=start+half,cursor=(uintptr_t)gGpuPrimCursor;
    if(p<start||p>end||sizeof(POLY_FT4)>end-p||p%_Alignof(POLY_FT4)||
        cursor> end||cursor<p+sizeof(POLY_FT4))return;
    const POLY_FT4 *original=(const POLY_FT4 *)p;
    if(original->code!=(cpu.sourceRaw?0x2f:0x2e)||original->tpage!=cpu.originalTpage||original->clut!=cpu.originalClut)return;
    const short xy[]={original->x0,original->y0,original->x1,original->y1,original->x2,original->y2,original->x3,original->y3};
    const unsigned char uv[]={original->u0,original->v0,original->u1,original->v1,original->u2,original->v2,original->u3,original->v3};
    if(memcmp(xy,cpu.originalXy,sizeof xy)||memcmp(uv,cpu.originalUv,sizeof uv))return;
    if(!cpu.sourceRaw&&(original->r0!=cpu.sourceShade||original->g0!=cpu.sourceShade||original->b0!=cpu.sourceShade))return;
    PsyzShadowBatch gpu={0};gpu.epoch=cpu.serial;gpu.count=cpu.count;
    gpu.shade=cpu.sourceRaw?0:cpu.shade;gpu.shadeValid=cpu.sourceRaw?0:cpu.shadeValid;
    gpu.sourceRaw=cpu.sourceRaw;gpu.sourcePolicy=cpu.sourceRaw?PSYZ_SHADOW_SOURCE_RAW_PEAK:PSYZ_SHADOW_SOURCE_CONSTANT;
    memcpy(gpu.packet,&original->r0,sizeof gpu.packet);
    for(unsigned i=0;i<cpu.count;i++)memcpy(gpu.xy[i],cpu.quads[i].xy,sizeof gpu.xy[i]);
    Psyz_GpuShadowBeginEpoch(cpu.serial);
    if(!Psyz_GpuShadowRegister(&original->r0,&gpu))Psyz_GpuShadowBeginEpoch(0);
}
