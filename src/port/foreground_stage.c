#include "port/foreground_stage.h"
#include <string.h>

static void occupy(PeForegroundStage* s,int x,int y,int w,int h,int write)
{
    if(w<=0 || h<=0)return;
    int right=x+w,bottom=y+h;
    if(x<0)x=0;if(y<0)y=0;if(right>1024)right=1024;if(bottom>512)bottom=512;
    if(x>=right || y>=bottom)return;
    for(int row=y/256;row<=(bottom-1)/256;row++)for(int col=x/64;col<=(right-1)/64;col++)
        s->occupied|=UINT32_C(1)<<(row*16+col);
    if(write && s->known)for(int row=y;row<bottom;row++)memset(s->known+row*1024+x,0,(size_t)(right-x));
}
void peForegroundStageBegin(PeForegroundStage* s,unsigned char* known)
{
    s->occupied=0;s->known=known;
    /* The gap between display buffers is not staging space. */
    occupy(s,0,0,320,512,0);
}
static void texture(PeForegroundStage* s,unsigned page,unsigned clut)
{
    unsigned depth=(page>>7)&3;
    if(depth==3) {s->occupied=UINT32_MAX;return;}
    occupy(s,(page&15)*64,((page>>4)&1)*256,64<<depth,256,0);
    if(depth<2)occupy(s,(clut&63)*16,clut>>6,depth?256:16,1,0);
}
void peForegroundStageObserve(const void* packet,unsigned offset,const uint32_t* w,
                             unsigned count,const PeGpuState* before,void* context)
{
    (void)packet;(void)offset;PeForegroundStage* s=context;
    if(!s || !w || !count || !before)return;
    unsigned code=w[0]>>24;
    if(code>=0x20 && code<0x80) {
        if(before->clip_left<0 || before->clip_top<0 || before->clip_right<before->clip_left ||
           before->clip_bottom<before->clip_top || before->clip_right>=1024 || before->clip_bottom>=512) {
            s->occupied=UINT32_MAX;return;
        }
        if(code<0x40 && (code&4)) {
            unsigned page_word=code&16?5:4;
            if(count<=page_word) {s->occupied=UINT32_MAX;return;}
            texture(s,w[page_word]>>16,w[2]>>16);
        } else if(code>=0x60 && (code&4)) {
            if(count<3) {s->occupied=UINT32_MAX;return;}
            texture(s,before->draw_mode,w[2]>>16);
        } else if(code>=0x40 && code<0x60 && (code&4)) {s->occupied=UINT32_MAX;return;}
        int x=before->clip_left,width=before->clip_right-x+1;
        /* A partial display scissor can move horizontally under widescreen.
         * Reserve its whole display width; offscreen scratch clips stay exact. */
        if(x>=0 && x+width<=320) {x=0;width=320;}
        occupy(s,x,before->clip_top,width,before->clip_bottom-before->clip_top+1,1);
    } else if(code==2) {
        if(count<3) {s->occupied=UINT32_MAX;return;}
        int x=(int16_t)w[1],y=(int16_t)(w[1]>>16),width=(int16_t)w[2],height=(int16_t)(w[2]>>16);
        if(width<0 || height<0 || x<0 || y<0 || x+width>1024 || y+height>512) {s->occupied=UINT32_MAX;return;}
        occupy(s,x,y,width,height,1);
    } else if(code==0x80 || code==0xc0) {
        if(count<(code==0x80?4u:3u)) {s->occupied=UINT32_MAX;return;}
        unsigned size=w[code==0x80?3:2];int width=(int16_t)size,height=(int16_t)(size>>16);
        if(width<0 || width>1024 || height<0 || height>512) {s->occupied=UINT32_MAX;return;}
        if(!width)width=1024;if(!height)height=512;
        int x=(int16_t)w[1],y=(int16_t)(w[1]>>16);
        if(x<0 || y<0) {s->occupied=UINT32_MAX;return;}
        if(x+width>1024 || y+height>512) {s->occupied=UINT32_MAX;return;}
        occupy(s,x,y,width,height,0);
        if(code==0x80) {
            x=(int16_t)w[2];y=(int16_t)(w[2]>>16);
            if(x<0 || y<0) {s->occupied=UINT32_MAX;return;}
            if(x+width>1024 || y+height>512) {s->occupied=UINT32_MAX;return;}
            occupy(s,x,y,width,height,1);
        }
    } else if(code>1 && code!=0xf8 && (code<0xe1 || code>0xe6))s->occupied=UINT32_MAX;
}
int peForegroundStageChoose(const PeForegroundStage* s,const unsigned char* known,int* x,int* y)
{
    if(!s || !known || !x || !y)return 0;
    for(unsigned tile=0;tile<32;tile++)if(!(s->occupied&(UINT32_C(1)<<tile))) {
        int left=(tile%16)*64,top=(tile/16)*256,valid=1;
        for(int row=top;row<top+256 && valid;row++)for(int col=left;col<left+64;col++)
            if(!known[row*1024+col]) {valid=0;break;}
        if(valid) {*x=left;*y=top;return 1;}
    }
    return 0;
}
int peForegroundStageCopy(const PeForegroundSource* s,const uint16_t* vram,
                         const unsigned char* known,unsigned first_cell,uint16_t* page)
{
    if(!s || !vram || !known || !page || !s->width || s->width>320 || !s->height || s->height>240 ||
       s->tpage>511 || s->clut>32767 || s->u>255 || s->v>255 || s->inset)return 0;
    unsigned columns=(s->width+15)/16,count=columns*((s->height+15)/16),depth=(s->tpage>>7)&3;
    if(depth==3 || first_cell>=64 || count>64-first_cell)return 0;
    unsigned shift=2-depth,base_x=(s->tpage&15)*64,base_y=((s->tpage>>4)&1)*256;
    for(unsigned cell=0;cell<count;cell++)for(unsigned dy=0;dy<16;dy++)for(unsigned dx=0;dx<16;dx++) {
        unsigned sx=(cell%columns)*16+dx,sy=(cell/columns)*16+dy;uint16_t colour=0;
        if(sx<s->width && sy<s->height) {
            unsigned u=(s->u+sx)&255,v=(s->v+sy)&255,x=base_x+(u>>shift),y=base_y+v;
            if(x>=1024 || !known[y*1024+x])return 0;
            colour=vram[y*1024+x];
            if(depth<2) {
                unsigned bits=depth?8:4,index=(colour>>((u&((1u<<shift)-1))*bits))&((1u<<bits)-1);
                x=(s->clut&63)*16+index;y=s->clut>>6;
                if(x>=1024 || !known[y*1024+x])return 0;
                colour=vram[y*1024+x];
            }
        }
        unsigned target=first_cell+cell;
        page[((target/4)*16+dy)*64+(target%4)*16+dx]=colour;
    }
    return 1;
}
