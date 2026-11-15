/* Exercise the production reticle at GTE screen-coordinate saturation. */
#include "port/gpu_len.h"
#include "../src/gameplay/world_targets.c"
#include <stdlib.h>
#include <string.h>
#define CHECK(x) do { if (!(x)) { fprintf(stderr,"line %d: %s\n",__LINE__,#x); exit(1); } } while (0)
DisplayState gDisplayState;
OT_TYPE* gGpuCurrentOt;
void* gGpuPrimCursor;
static GameDebugState debugState;
GameDebugState* gGameDebugState=&debugState;
static GameSession session;
GameSession* gGameSession=&session;
AttachmentState gAttachmentState;
_Alignas(16) u8 gHostScratchpad[0x400];
WorldTargetNode* gWorldTargetListHead;
WorldTargetNode* gWorldTargetCursorNode;
s32 gWorldTargetCursorXFixed8,gWorldTargetCursorYFixed8,gWorldTargetCursorEasingPass;
void actorRenderComposeCoord(GfxCoord* coord) {(void)coord;}
void textDrawString(TextDrawReq* request,const u8* text) {(void)request;(void)text;}
u8* textItoaUnsigned(u8* out,u32 value) {(void)value;out[0]=0;return out;}
u8* textItoaSigned(u8* out,s32 value) {(void)value;out[0]=0;return out;}
void uiDrawRectFrame(RECT* r,s32 ot,s32 style,const char* title) {(void)r;(void)ot;(void)style;(void)title;}
void Psyz_PadsOverride(int port,char* frame,int count) {(void)port;(void)frame;(void)count;}
static int signed11(int n) {return ((n&2047)^1024)-1024;}
int main(void)
{
    ResetGraph(0);InitGeom();SetGeomOffset(0,0);SetGeomScreen(320);
    *SCRATCH_STACK_CURSOR_SLOT=PLAYSTATION_SCRATCHPAD_ADDRESS(0x3f0);
    Enemy enemy={0};GfxCoord coord={0};enemy.coord=&coord;
    coord.workm.m[0][0]=coord.workm.m[1][1]=coord.workm.m[2][2]=4096;
    enemy.node.state.parts.targeted=1;gWorldTargetListHead=&enemy.node;
    const struct {int x,y,visible,easing;} cases[]={
        {6000,0,0},{-6000,0,0},{0,6000,0},{0,-6000,0},
        {0,0,1},{300,0,1},{-300,0,1},{1006,0,1},{-1006,0,1},
        {1009,0,0},{-1009,0,0},
        {1010,0,1,1},{-1010,0,1,1}
    };
    for(unsigned i=0;i<sizeof cases/sizeof cases[0];i++) {
        coord.workm.t[0]=cases[i].x;coord.workm.t[1]=cases[i].y;coord.workm.t[2]=320;
        gWorldTargetCursorNode=NULL;gWorldTargetCursorEasingPass=0;
        WorldTargetNode oldTarget={0};
        if(cases[i].easing) {
            gWorldTargetCursorNode=&oldTarget;
            gWorldTargetCursorXFixed8=cases[i].x*256;
            gWorldTargetCursorYFixed8=cases[i].y*256;
        }
        OT_TYPE ot[16];ClearOTagR(ot,16);gGpuCurrentOt=ot+8;
        _Alignas(16) unsigned char arena[1024];memset(arena,0xa5,sizeof arena);
        void* savedScratch=*SCRATCH_STACK_CURSOR_SLOT;
        gGpuPrimCursor=arena;worldTargetDrawOverlay();
        CHECK(*SCRATCH_STACK_CURSOR_SLOT==savedScratch);
        CHECK(gWorldTargetCursorNode==&enemy.node && enemy.node.state.parts.targeted==1);
        CHECK((gGpuPrimCursor!=arena)==cases[i].visible);
        if(gGpuPrimCursor!=arena) {
            POLY_FT4* quad=(void*)arena;
            CHECK(abs(signed11(quad->x1)-signed11(quad->x0))==(cases[i].easing?16:32));
            CHECK(abs(signed11(quad->y2)-signed11(quad->y0))==(cases[i].easing?16:32));
            CHECK(getlen(quad)==9 && getcode(quad)==0x2f);
        }
    }
    puts("off-screen reticle cannot wrap across the GPU signed-coordinate boundary");
    return 0;
}
