#include "port/gpu_state.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define CHECK(x) do {if(!(x)){fprintf(stderr,"line %d: %s\n",__LINE__,#x);exit(1);}} while(0)
void Psyz_PadsOverride(int p,char* f,int n) {(void)p;(void)f;(void)n;}
static unsigned sprites;
static PeGpuState observed[2];
static void observe(const void* packet,unsigned offset,const uint32_t* words,unsigned count,const PeGpuState* state,void* context)
{
    (void)packet;(void)offset;(void)count;(void)context;
    if((words[0]>>24&~3u)==0x64) {CHECK(sprites<2);observed[sprites++]=*state;}
}
int main(void)
{
    ResetGraph(0);
    DRAWENV env;SetDefDrawEnv(&env,0,272,320,240);env.ofs[0]=160;env.ofs[1]=392;
    PeGpuState state;CHECK(peGpuStateFromEnv(&state,&env));
    CHECK(state.clip_left==0 && state.clip_top==272 && state.clip_right==319 && state.clip_bottom==511);
    CHECK(state.offset_x==160 && state.offset_y==392 && state.mask_mode==0);
    DR_AREA first,second;RECT clip1={10,280,100,80},clip2={20,290,80,60};
    SetDrawArea(&first,&clip1);SetDrawArea(&second,&clip2);
    DR_OFFSET offset;u_short origin[2]={(u_short)-3,272};SetDrawOffset(&offset,origin);
    struct {DR_MODE mode;SPRT sprite;} merged={0};
    SetDrawMode(&merged.mode,0,1,0x8f,NULL);setSprt(&merged.sprite);setXY0(&merged.sprite,0,0);
    setWH(&merged.sprite,8,23);CHECK(MargePrim(&merged.mode,&merged.sprite)==0);
    POLY_FT4 polygon={0};setPolyFT4(&polygon);polygon.tpage=0x101;
    /* Payload words resembling state commands are vertex data, not GP0 state. */
    polygon.x0=(short)0xe300;polygon.y0=(short)0xe400;
    SPRT last={0};setSprt(&last);setWH(&last,24,56);
    catPrim(&first,&offset);catPrim(&offset,&merged.mode);catPrim(&merged.mode,&second);
    catPrim(&second,&polygon);catPrim(&polygon,&last);termPrim(&last);
    CHECK(peGpuWalkOt(&state,&first,observe,NULL));CHECK(sprites==2);
    CHECK(observed[0].clip_left==10 && observed[0].clip_right==109 && observed[0].clip_top==280);
    CHECK(observed[0].offset_x== -3 && observed[0].offset_y==272);
    CHECK((observed[0].draw_mode&0x3ff)==0x28f);
    CHECK(observed[1].clip_left==20 && observed[1].clip_right==99 && observed[1].clip_top==290);
    CHECK((observed[1].draw_mode&0x3ff)==0x301);
    uint32_t commands[]={0xe2001234,0xe6000003,0xf8000000,0xe3ffffff,0xe4ffffff,0x48000000,0,0,0x55555555};
    CHECK(peGpuWalkWords(&state,commands,sizeof commands/4,NULL,NULL,NULL));
    CHECK(state.texture_window==0x1234 && state.mask_mode==3);
    CHECK(state.clip_left==20 && state.clip_right==99 && state.clip_top==290);
    uint32_t truncated[]={0xe3000000,0x64000000,0};
    CHECK(!peGpuWalkWords(&state,truncated,3,NULL,NULL,NULL));
    uint32_t unknown[]={0xf7000000};CHECK(!peGpuWalkWords(&state,unknown,1,NULL,NULL,NULL));
    uint32_t unterminated[]={0x48000000,0,0,0};CHECK(!peGpuWalkWords(&state,unterminated,4,NULL,NULL,NULL));
    setaddr(&last,&last);CHECK(!peGpuWalkOt(&state,&last,NULL,NULL));
    if(sizeof(u_long)>4) {
        last.len=(u_long)UINT32_MAX+1;termPrim(&last);
        CHECK(!peGpuWalkOt(&state,&last,NULL,NULL));
    }
    puts("GPU OT state: LP64 merge, ordered clips, signed offsets, inherited page, opaque payload and failure gates OK");
    return 0;
}
