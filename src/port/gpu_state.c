#include "port/gpu_state.h"
#include <string.h>

static int signed11(unsigned value) {value&=2047;return value&1024?(int)value-2048:(int)value;}
static unsigned commandLength(const uint32_t* words,unsigned available)
{
    unsigned code=words[0]>>24;
    if(code<=1 || (code>=0xe1 && code<=0xe6))return 1;
    if(code==2 || code==0xf8)return 3;
    if(code>=0x20 && code<0x40) {
        unsigned vertices=code&8?4:3,gouraud=(code>>4)&1,textured=(code>>2)&1;
        return 1+vertices*(1+gouraud+textured)-gouraud;
    }
    if(code>=0x40 && code<0x60) {
        if(!(code&8))return code&16?4:3;
        unsigned gouraud=(code>>4)&1;
        for(unsigned i=gouraud?4:3;i<available;i+=gouraud?2:1)
            if((words[i]&0xf000f000u)==0x50005000u)return i+1;
        return 0;
    }
    if(code>=0x60 && code<0x80)return 2+((code&4)!=0)+((code&0x18)==0);
    if(code==0x80)return 4;
    if(code==0xc0)return 3;
    /* PsyZ does not implement inline GP0(A0h) image payloads. Do not guess
     * where opaque/custom payloads end and accidentally interpret their pixels
     * as state commands. Real LoadImage uses the separate transfer API. */
    return 0;
}

int peGpuWalkWords(PeGpuState* state,const uint32_t* words,unsigned count,
                   const void* packet,PeGpuObserver observer,void* context)
{
    if(!state || (!words && count))return 0;
    for(unsigned i=0;i<count;) {
        unsigned code=words[i]>>24,length=commandLength(words+i,count-i);
        if(!length || length>count-i)return 0;
        if(observer)observer(packet,i,words+i,length,state,context);
        uint32_t word=words[i];
        switch(code) {
            case 0xe1:state->draw_mode=word;break;
            case 0xe2:state->texture_window=word&0xfffff;break;
            case 0xe3:state->clip_left=word&1023;state->clip_top=(word>>10)&1023;break;
            case 0xe4:state->clip_right=word&1023;state->clip_bottom=(word>>10)&1023;break;
            case 0xe5:state->offset_x=signed11(word);state->offset_y=signed11(word>>11);break;
            case 0xe6:state->mask_mode=word&3;break;
            default:
                /* Textured polygons change the page inherited by later sprites,
                 * preserving the draw-mode dither/display-area flags. */
                if(code>=0x20 && code<0x40 && (code&4)) {
                    unsigned page=(code&16)?5:4;
                    state->draw_mode=(state->draw_mode&~0x1ffu)|((words[i+page]>>16)&0x1ffu);
                }
                break;
        }
        i+=length;
    }
    return 1;
}

int peGpuWalkOt(PeGpuState* state,const void* head,PeGpuObserver observer,void* context)
{
    const OT_TYPE* node=head;
    for(unsigned visited=0;visited<65536;visited++) {
        if(!node || (uintptr_t)node<4096)return 0;
        u_long length=node->len;
        if(length>255)return 0;
        uint32_t words[255];
        const unsigned char* payload=(const unsigned char*)node+sizeof(OT_TYPE);
        /* This explicit format rule matches PsyZ GPU_Enqueue, including the
         * LP64 MargePrim marker. Native DR_* words use u_long strides; shape
         * and merged bodies retain packed 32-bit GP0 words. */
        int packed=sizeof(u_long)==4;
        if(length) {
            uint32_t first;memcpy(&first,payload,4);
            if((first>>24)>=0x20 && (first>>24)<0x80)packed=1;
            for(unsigned i=0;i<length && !packed;i++) {
                uint32_t word;memcpy(&word,payload+i*4,4);
                if(word==PSYZ_MERGED_PRIM_NOP)packed=1;
            }
        }
        for(unsigned i=0;i<length;i++)memcpy(&words[i],payload+i*(packed?4:sizeof(u_long)),4);
        if(!peGpuWalkWords(state,words,(unsigned)length,node,observer,context))return 0;
        if(isendprim(node))return 1;
        node=nextPrim(node);
    }
    return 0;
}

int peGpuStateFromEnv(PeGpuState* state,const DRAWENV* environment)
{
    if(!state || !environment)return 0;
    memset(state,0,sizeof(*state));
    DRAWENV copy=*environment;DR_ENV commands={0};SetDrawEnv(&commands,&copy);termPrim(&commands);
    return peGpuWalkOt(state,&commands,NULL,NULL);
}
