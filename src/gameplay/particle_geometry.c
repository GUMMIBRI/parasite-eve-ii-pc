/* New PE2 binding of the user's accepted PE1 small extra-mesh policy.
 * Project-authored tetra topology/radius/spin reused with original provenance;
 * retained read-only projector in particle_project_pe1.h is explicitly MPL2.
 * No original simulation, RNG, pose, lifetime, palette or GTE writes. */
#include "gameplay/particle_geometry.h"
#include "gameplay/display.h"
#include "gameplay/scene.h"
#include "gameplay/room_effects.h"
#include "gameplay/world_collision.h"
#include "main/gfx.h"
#include "main/session.h"
#include "main/display.h"
#include "main/mem.h"
#include <psyz/gte.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
extern void effectTileTaskA4(Task *);
typedef struct { int32_t x,y,z; } PeParticleWorldPoint;
typedef MATRIX GteMatrix;
#include "particle_project_pe1.h"
enum { TRIANGLE_CAP=64, SPARK_DURATION=8, ORIGINAL_RESERVED_OT_ENTRIES=32 };
static struct {
    int mode,status,hasEpoch;
    unsigned triangles,anim; s32 loop,half;
    uintptr_t session,grid,effects,ot,arena;size_t arenaBytes;
    unsigned char location[6];MATRIX view;
    const char *reason;
} state;
static void fallback(const char *reason){if(state.status!=2)state.status=1;state.reason=reason;}
static int epoch(void) {
    if(!gGameSession||!gWorldCollisionActiveGrid||!gRoomEffectState||!gGameSession->location.stage||
       gDisplayState.displayOwner!=0||gDisplayState.otBuffer<0||gDisplayState.otBuffer>1||!gGpuCurrentOt){
        state.hasEpoch=0;state.triangles=0;state.status=state.mode?1:0;state.reason="original-unsupported-frame-owner";return 0;
    }
    int changed=!state.hasEpoch||state.anim!=gDisplayState.animFrame||state.loop!=gDisplayState.loopCount||
        state.half!=gDisplayState.otBuffer||state.ot!=(uintptr_t)gGpuCurrentOt||
        state.session!=(uintptr_t)gGameSession||state.grid!=(uintptr_t)gWorldCollisionActiveGrid||
        state.effects!=(uintptr_t)gRoomEffectState||state.arena!=(uintptr_t)gGpuPrimitiveBufferBase||state.arenaBytes!=gGpuPrimitiveBufferBytes||
        memcmp(state.location,&gGameSession->location,6)||memcmp(&state.view,&gGfxViewCoord.workm,sizeof(MATRIX));
    if(changed){state.triangles=0;state.status=state.mode?1:0;state.reason=state.mode?"original-awaiting-supported-spark":"original";
        state.anim=gDisplayState.animFrame;state.loop=gDisplayState.loopCount;state.half=gDisplayState.otBuffer;state.ot=(uintptr_t)gGpuCurrentOt;
        state.session=(uintptr_t)gGameSession;state.grid=(uintptr_t)gWorldCollisionActiveGrid;state.effects=(uintptr_t)gRoomEffectState;
        state.arena=(uintptr_t)gGpuPrimitiveBufferBase;state.arenaBytes=gGpuPrimitiveBufferBytes;
        memcpy(state.location,&gGameSession->location,6);state.view=gGfxViewCoord.workm;state.hasEpoch=1;}
    return 1;
}
void Pe2ParticleGeometrySetMode(int mode){mode=mode>=0&&mode<=2?mode:0;if(mode!=state.mode){memset(&state,0,sizeof state);state.mode=mode;state.status=mode?1:0;state.reason=mode?"original-awaiting-supported-spark":"original";}}
int Pe2ParticleGeometryGetMode(void){return state.mode;}
int Pe2ParticleGeometryGetStatus(void){if(state.mode&&!epoch())return 1;return state.mode?state.status:0;}
const char *Pe2ParticleGeometryGetReason(void){if(!state.mode)return "original";if(!epoch())return "original-unsupported-frame-owner";return state.reason;}
static int64_t area(const POLY_F3 *p){return(int64_t)(p->x1-p->x0)*(p->y2-p->y0)-(int64_t)(p->y1-p->y0)*(p->x2-p->x0);}
static int identity(const MATRIX *m){for(int r=0;r<3;r++){if(m->t[r])return 0;for(int c=0;c<3;c++)if(m->m[r][c]!=(r==c?4096:0))return 0;}return 1;}
static int validView(const MATRIX *m){
    double n[3]={0};for(int i=0;i<3;i++)for(int j=0;j<3;j++)n[i]+=(double)m->m[i][j]*m->m[i][j];
    double mean=(n[0]+n[1]+n[2])/3;if(mean<1||!__builtin_isfinite(mean))return 0;
    for(int i=0;i<3;i++)if(fabs(n[i]-mean)>.02*mean)return 0;
    for(int i=0;i<3;i++)for(int j=i+1;j<3;j++){double d=0;for(int k=0;k<3;k++)d+=(double)m->m[i][k]*m->m[j][k];if(fabs(d)>.02*mean)return 0;}return 1;
}
int Pe2ParticleGeometryPixelSpark(const Task *task,const GfxCoord *coord,const EffectWork *work,TILE *original,s32 sortingDepth){
    if(!state.mode)return 0;if(!epoch()){fallback("original-unsupported-frame-owner");return 0;}
    if(!task||task->callback!=effectTileTaskA4||task->bodyKind!=TASK_BODY_COORD||!task->extra.coordBody||
       task->extra.coordBody->coord!=coord||!coord||!work||task->spawnArg2.pointer!=work||work->age>=SPARK_DURATION||
       !task->state||!original){fallback("original-unknown-spark-source");return 0;}
    const GfxCoord *seen[64];unsigned chain=0;
    for(const GfxCoord *p=coord;p!=&gGfxViewCoord;p=p->parent){if(!p||chain==64){fallback("original-unknown-world-root");return 0;}for(unsigned i=0;i<chain;i++)if(seen[i]==p){fallback("original-coordinate-cycle");return 0;}seen[chain++]=p;}
    if(!identity(&GsWSMATRIX)||!validView(&state.view)||gDisplayState.otDepthShift<0||gDisplayState.otDepthShift>3){fallback("original-unsupported-projection-basis");return 0;}
    /* Exact active MAIN-LOOP heap half. A task-owned/static arena is not an
     * interchangeable capacity, even if some pointers happen to fall nearby. */
    uintptr_t base=(uintptr_t)gGpuPrimitiveBufferBase,total=gGpuPrimitiveBufferBytes;
    if(!base||total<20||(total&1)||base>UINTPTR_MAX-total){fallback("original-invalid-arena");return 0;}
    uintptr_t start=base+(uintptr_t)state.half*(total/2),end=start+total/2,src=(uintptr_t)original,cursor=(uintptr_t)gGpuPrimCursor;
    /* Original memory setup reserves/clears final10 trailer bytes; preserve them. */
    if(state.half==1)end-=10;
    size_t sourceBytes=sizeof(TILE)+sizeof(DR_TPAGE);
    if(src<start||src>end||sourceBytes>end-src||src%_Alignof(TILE)||cursor!=src+sourceBytes){fallback("original-unowned-source-arena");return 0;}
    if(!gGpuFrameOrderingTables[state.half].org||gGpuFrameOrderingTables[state.half].length!=10||gGpuCurrentOt!=(OT_TYPE*)gGpuFrameOrderingTables[state.half].org+ORIGINAL_RESERVED_OT_ENTRIES){fallback("original-unknown-ot-owner");return 0;}
    DR_TPAGE *blend=(DR_TPAGE*)(original+1),expected={0};
    setDrawTPage(&expected,0,1,getTPage(0,GPU_BLEND_ADD,640,0));
    unsigned index=(((u32)sortingDepth<<(unsigned)gDisplayState.otDepthShift)>>2)&GPU_ORDERING_TABLE_DEPTH_BYTE_MASK;index/=GPU_OT_TAG_BYTES;
    OT_TYPE *entry=&gGpuCurrentOt[index];
    if(getlen(original)!=3||getcode(original)!=0x62||work->angle<1||work->angle>2||original->w!=(s16)work->angle||original->h!=(s16)work->angle||
       !(original->r0|original->g0|original->b0)||getlen(blend)!=1||blend->code[0]!=expected.code[0]||
       getaddr(entry)!=(u_long)blend||getaddr(blend)!=(u_long)original){fallback("original-packet-order-unproven");return 0;}
    /* Original source pose already composed; local motion is marked dirty for
     * next tick. Verify exact original projected center before any new packet. */
    PeParticleWorldPoint center={coord->workm.t[0],coord->workm.t[1],coord->workm.t[2]};
    if(center.x< -32700||center.x>32700||center.y< -32700||center.y>32700||center.z< -32700||center.z>32700){fallback("original-source-coordinate-domain");return 0;}
    unsigned h=Psyz_GteCtrlRead(26)&65535u;s32 ox=(s32)Psyz_GteCtrlRead(24),oy=(s32)Psyz_GteCtrlRead(25);
    s16 sx,sy;unsigned sourceZ;
    if(!PeParticle_Project(&center,&GsWSMATRIX,h,ox,oy,&sx,&sy,&sourceZ)||sx!=original->x0||sy!=original->y0||
       sortingDepth!=(s32)((sourceZ>>2)+1)){fallback("original-projector-source-mismatch");return 0;}
    /* Source-owned procedural TETRAHEDRON, not a billboard. World-axis offsets
     * rotate through the actual view around the exact original 3D view center.
     * No approximate inverse/rounded world anchor moves the source center. */
    unsigned radius=4+(SPARK_DURATION-work->age)*8/SPARK_DURATION,phase=(work->age/3)&3;
    PeParticleWorldPoint offset[4]={{0,-(int)(2*radius),0},{(int)radius,(int)radius,0},{-(int)radius,(int)radius,(int)radius},{-(int)radius,(int)radius,-(int)radius}};
    PeParticleWorldPoint points[4];
    for(unsigned i=0;i<4;i++){
        int32_t x=offset[i].x,z=offset[i].z;
        if(phase==1){offset[i].x=-z;offset[i].z=x;}else if(phase==2){offset[i].x=-x;offset[i].z=-z;}else if(phase==3){offset[i].x=z;offset[i].z=-x;}
        const int32_t p[]={offset[i].x,offset[i].y,offset[i].z};int32_t *out[]={&points[i].x,&points[i].y,&points[i].z};const int32_t c[]={center.x,center.y,center.z};
        for(int r=0;r<3;r++){int64_t v=(int64_t)state.view.m[r][0]*p[0]+(int64_t)state.view.m[r][1]*p[1]+(int64_t)state.view.m[r][2]*p[2];v=(v>>12)+c[r];if(v< -32768||v>32767){fallback("original-mesh-coordinate-domain");return 0;}*out[r]=(int32_t)v;}
    }
    static const unsigned topology[4][3]={{0,2,1},{0,1,3},{0,3,2},{1,2,3}};
    struct {POLY_F3 packet;unsigned depth;} pending[4];memset(pending,0,sizeof pending);unsigned count=0;
    for(unsigned f=0;f<4;f++){
        POLY_F3 p={0};s16 xy[6];unsigned z[3];
        for(unsigned v=0;v<3;v++)if(!PeParticle_Project(&points[topology[f][v]],&GsWSMATRIX,h,ox,oy,&xy[v*2],&xy[v*2+1],&z[v])){fallback("original-whole-mesh-nearclip");return 0;}
        setPolyF3(&p);unsigned shade=255-f*24;p.r0=(unsigned)original->r0*shade/255;p.g0=(unsigned)original->g0*shade/255;p.b0=(unsigned)original->b0*shade/255;
        p.x0=xy[0];p.y0=xy[1];p.x1=xy[2];p.y1=xy[3];p.x2=xy[4];p.y2=xy[5];if(!area(&p))continue;
        pending[count].packet=p;pending[count].depth=z[0]+z[1]+z[2];count++;
    }
    if(!count||count>TRIANGLE_CAP-state.triangles){fallback("original-mesh-budget-or-degenerate");return 0;}
    /* All faces occupy original anchor's exact OT bucket. Stable back-to-front
     * within that bucket; original DR_TPAGE+point chain stays in original order.
     * New triangles are opaque code20 exactly as accepted PE1 mesh, hence no
     * ABR/dither/global draw-mode command is added or guessed/restored. */
    for(unsigned i=1;i<count;i++)for(unsigned j=i;j&&pending[j].depth>pending[j-1].depth;j--){
        POLY_F3 packet=pending[j].packet;unsigned depth=pending[j].depth;pending[j]=pending[j-1];pending[j-1].packet=packet;pending[j-1].depth=depth;
    }
    uintptr_t alignment=_Alignof(POLY_F3);if(cursor>UINTPTR_MAX-(alignment-1)){fallback("original-arena-overflow");return 0;}
    uintptr_t aligned=(cursor+alignment-1)&~(alignment-1);size_t bytes=count*sizeof(POLY_F3);
    if(aligned<start||aligned>end||bytes>end-aligned){fallback("original-whole-mesh-arena-full");return 0;}
    /* All fallible work is complete. Commit one immutable bounded chain, then
     * and ONLY THEN suppress the original rectangle for successful New mode. */
    POLY_F3 *dest=(POLY_F3*)aligned;u_long next=(u_long)original;
    for(unsigned i=0;i<count;i++){dest[i]=pending[i].packet;
        unsigned int xy;memcpy(&xy,&dest[i].x0,sizeof xy);Psyz_GteCopyPgxpSxy(NULL,&dest[i].x0,xy);
        memcpy(&xy,&dest[i].x1,sizeof xy);Psyz_GteCopyPgxpSxy(NULL,&dest[i].x1,xy);
        memcpy(&xy,&dest[i].x2,sizeof xy);Psyz_GteCopyPgxpSxy(NULL,&dest[i].x2,xy);
        setaddr(&dest[i],i+1<count?(u_long)&dest[i+1]:next);}
    gGpuPrimCursor=(void*)(aligned+bytes);setaddr(blend,dest);
    if(state.mode==2){original->w=0;original->h=0;}
    state.triangles+=count;state.status=2;state.reason="source-spark-3D-mesh-queued-unobserved";return 1;
}
