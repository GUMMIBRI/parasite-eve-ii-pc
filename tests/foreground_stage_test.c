#include "port/foreground_stage.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define CHECK(x) do {if(!(x)){fprintf(stderr,"line %d: %s\n",__LINE__,#x);exit(1);}}while(0)
void Psyz_PadsOverride(int p,char* f,int n) {(void)p;(void)f;(void)n;}
static unsigned char known[1024*512];
static uint16_t vram[1024*512];
static struct {uint16_t page[64*256];uint64_t guard;} output;
int main(void)
{
    PeForegroundStage stage;int x=-1,y=-1;memset(known,1,sizeof known);
    peForegroundStageBegin(&stage,known);CHECK(peForegroundStageChoose(&stage,known,&x,&y) && x==320 && y==0);
    PeGpuState state={.clip_left=0,.clip_top=0,.clip_right=319,.clip_bottom=239,.draw_mode=0xe1000105};
    uint32_t sprite[]={0x65000000,0,0,0x00100010};
    peForegroundStageObserve(NULL,0,sprite,4,&state,&stage);
    CHECK(peForegroundStageChoose(&stage,known,&x,&y) && x==576 && y==0);
    CHECK(!known[0] && !known[239*1024+319] && known[255*1024]);
    uint32_t copy[]={0x80000000,576,640,0x00100010};
    peForegroundStageObserve(NULL,0,copy,4,&state,&stage);
    CHECK(peForegroundStageChoose(&stage,known,&x,&y) && x==704 && y==0);
    CHECK(!known[640] && known[576]);
    memset(known,0,sizeof known);CHECK(!peForegroundStageChoose(&stage,known,&x,&y));
    memset(known,1,sizeof known);peForegroundStageBegin(&stage,known);
    /* A polygon's embedded page overrides the preceding sprite mode. */
    uint32_t polygon[]={0x24000000,0,0,0,0x01050000,0,0};
    peForegroundStageObserve(NULL,0,polygon,7,&state,&stage);
    CHECK(peForegroundStageChoose(&stage,known,&x,&y) && x==576 && y==0);
    /* Indexed CLUT entries also exclude pages even when their texpage is elsewhere. */
    peForegroundStageBegin(&stage,known);state.draw_mode=0xe100008f;sprite[2]=(uint32_t)(320/16+255*64)<<16;
    peForegroundStageObserve(NULL,0,sprite,4,&state,&stage);
    CHECK(peForegroundStageChoose(&stage,known,&x,&y) && x==576 && y==0);
    state.clip_bottom=1000;peForegroundStageObserve(NULL,0,sprite,4,&state,&stage);
    CHECK(!peForegroundStageChoose(&stage,known,&x,&y));
    memset(known,1,sizeof known);peForegroundStageBegin(&stage,known);
    uint32_t fill[]={0x02000000,0,0x02000400};
    peForegroundStageObserve(NULL,0,fill,3,&state,&stage);
    CHECK(!peForegroundStageChoose(&stage,known,&x,&y));
    memset(known,1,sizeof known);peForegroundStageBegin(&stage,known);copy[3]=0x00100401;
    peForegroundStageObserve(NULL,0,copy,4,&state,&stage);
    CHECK(!peForegroundStageChoose(&stage,known,&x,&y));
    memset(known,1,sizeof known);memset(vram,0,sizeof vram);
    PeForegroundSource source={.tpage=143,.clut=255*64,.width=8,.height=8,.u=104,.v=0};
    for(unsigned row=0;row<8;row++)for(unsigned col=0;col<4;col++)vram[row*1024+960+52+col]=0x0201;
    vram[255*1024+1]=0x8000;vram[255*1024+2]=0x7fff;
    output.guard=UINT64_C(0x123456789abcdef0);memset(output.page,0x55,sizeof output.page);
    CHECK(peForegroundStageCopy(&source,vram,known,63,output.page));
    CHECK(output.page[240*64+48]==0x8000 && output.page[240*64+49]==0x7fff);
    CHECK(output.page[240*64+56]==0 && output.page[248*64+48]==0);
    CHECK(output.guard==UINT64_C(0x123456789abcdef0));
    PeForegroundSource four=source;four.tpage=15;
    for(unsigned row=0;row<8;row++)for(unsigned col=0;col<2;col++)vram[row*1024+960+26+col]=0x2121;
    CHECK(peForegroundStageCopy(&four,vram,known,0,output.page));
    CHECK(output.page[0]==0x8000 && output.page[1]==0x7fff && output.page[8]==0);
    known[255*1024+2]=0;CHECK(!peForegroundStageCopy(&source,vram,known,0,output.page));
    known[255*1024+2]=1;known[1012]=0;CHECK(!peForegroundStageCopy(&source,vram,known,0,output.page));
    memset(known,1,sizeof known);peForegroundStageBegin(&stage,known);
    PeGpuState overwritten={.clip_left=960,.clip_top=0,.clip_right=1023,.clip_bottom=239};
    uint32_t tile[]={0x60000000,0,0x00100010};
    peForegroundStageObserve(NULL,0,tile,3,&overwritten,&stage);
    CHECK(!peForegroundStageCopy(&source,vram,known,0,output.page));
    memset(known,1,sizeof known);source.tpage=256;source.width=16;source.u=248;source.v=248;
    vram[248*1024+248]=123;vram[248*1024]=456;
    CHECK(peForegroundStageCopy(&source,vram,known,0,output.page));
    CHECK(output.page[0]==123 && output.page[8]==456);
    source.width=32;CHECK(!peForegroundStageCopy(&source,vram,known,63,output.page));
    source.tpage=384;CHECK(!peForegroundStageCopy(&source,vram,known,0,output.page));
    puts("Foreground staging: original OT footprints, known backups, exact indexed/STP words, UV wrap and zero padding OK");
    return 0;
}
