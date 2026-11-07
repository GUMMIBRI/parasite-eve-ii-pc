#include "port/background_foreground.h"
#include <stdlib.h>
#include <string.h>
#include <psyz/video.h>

typedef struct {const void* packet;unsigned source_id;} Registration;
typedef struct {
    uintptr_t first,end;unsigned count,epoch;int valid,sorted;
    Registration entries[PE_FOREGROUND_MAX_SOURCES];
} Registry;
static Registry registries[4];
static unsigned epoch;
static Registry* registryAt(const void* pointer)
{
    uintptr_t value=(uintptr_t)pointer;
    for(unsigned i=0;i<4;i++)if(value>=registries[i].first && value<registries[i].end)return &registries[i];
    return NULL;
}
void peForegroundBeginOt(const void* first_tag,unsigned tag_count)
{
    uintptr_t first=(uintptr_t)first_tag,end=first+(size_t)tag_count*sizeof(OT_TYPE);
    if(!first || !tag_count || tag_count>65536 || end<first)return;
    Registry* selected=NULL;
    for(unsigned i=0;i<4;i++)if(first<registries[i].end && end>registries[i].first) {
        registries[i].first=registries[i].end=0;selected=&registries[i];
    }
    if(!selected)for(unsigned i=0;i<4;i++)if(!registries[i].first) {selected=&registries[i];break;}
    if(!selected) {
        selected=&registries[0];
        for(unsigned i=1;i<4;i++)if(registries[i].epoch<selected->epoch)selected=&registries[i];
    }
    selected->first=first;selected->end=end;selected->count=0;selected->valid=1;selected->sorted=0;selected->epoch=++epoch;
}
void peForegroundRegister(const void* depth_base,const void* packet,unsigned source_id)
{
    Registry* r=registryAt(depth_base);if(!r || !r->valid)return;
    if(!packet || source_id>4095 || r->count==PE_FOREGROUND_MAX_SOURCES) {r->valid=0;return;}
    r->entries[r->count++]=(Registration){packet,source_id};r->sorted=0;
}
static int orderRegistration(const void* a,const void* b)
{
    uintptr_t x=(uintptr_t)((const Registration*)a)->packet,y=(uintptr_t)((const Registration*)b)->packet;
    return (x>y)-(x<y);
}
static int findRegistration(const Registry* r,const void* packet)
{
    unsigned lo=0,hi=r->count;uintptr_t value=(uintptr_t)packet;
    while(lo<hi) {unsigned mid=(lo+hi)/2;uintptr_t current=(uintptr_t)r->entries[mid].packet;
        if(current==value)return (int)mid;if(current<value)lo=mid+1;else hi=mid;}
    return -1;
}
typedef struct {
    const PeForegroundSource* entry;unsigned modes,sprites;int bad,ready;
    PeGpuState state;SPRT source;PeForegroundPackets packets;
} Replacement;
typedef struct {Registry* registry;Replacement* replacements;} Plan;
static Replacement* storage;
static unsigned storage_count;
static void observe(const void* packet,unsigned offset,const uint32_t* words,unsigned count,const PeGpuState* before,void* context)
{
    (void)offset;Plan* plan=context;int index=findRegistration(plan->registry,packet);if(index<0)return;
    Replacement* p=&plan->replacements[index];if(!p->entry)return;
    unsigned code=words[0]>>24;
    if(code==0xe1) {if(p->sprites || ++p->modes>1)p->bad=1;return;}
    if(!code && (words[0]==0 || words[0]==PSYZ_MERGED_PRIM_NOP))return;
    if((code&~3u)==0x64 && count==4 && p->modes==1 && !p->sprites++) {
        memset(&p->source,0,sizeof p->source);setSprt(&p->source);
        memcpy(&p->source.r0,words,16);p->state=*before;return;
    }
    p->bad=1;
}
unsigned peForegroundSubmitOt(const void* head,const PeGpuState* initial,const PeForegroundPack* pack)
{
    Registry* r=registryAt(head);
    if(!r || !r->valid || !r->count || !initial || !pack || !pack->atlas_key || !pack->count ||
       pack->count>PE_FOREGROUND_MAX_SOURCES) {DrawOTag((OT_TYPE*)head);return 0;}
    if(!r->sorted) {qsort(r->entries,r->count,sizeof(*r->entries),orderRegistration);r->sorted=1;}
    for(unsigned i=1;i<r->count;i++)if(r->entries[i-1].packet==r->entries[i].packet) {DrawOTag((OT_TYPE*)head);return 0;}
    if(r->count>storage_count) {
        Replacement* next=realloc(storage,(size_t)r->count*sizeof(*next));
        if(!next) {DrawOTag((OT_TYPE*)head);return 0;}
        storage=next;storage_count=r->count;
    }
    for(unsigned i=0;i<r->count;i++) {
        Replacement* p=&storage[i];p->entry=NULL;p->modes=p->sprites=0;p->bad=p->ready=0;
        for(unsigned j=0;j<pack->count;j++)if(pack->sources[j].source_id==r->entries[i].source_id) {p->entry=&pack->sources[j];break;}
    }
    PeGpuState state=*initial;Plan plan={r,storage};
    if(!peGpuWalkOt(&state,head,observe,&plan)) {DrawOTag((OT_TYPE*)head);return 0;}
    unsigned ready=0;
    for(unsigned i=0;i<r->count;i++) {
        Replacement* p=&storage[i];const PeForegroundSource* e=p->entry;
        if(!e || p->bad || p->modes!=1 || p->sprites!=1 || p->state.texture_window || p->source.w!=e->width || p->source.h!=e->height ||
           p->source.u0!=e->u || p->source.v0!=e->v || p->source.clut!=e->clut || ((p->state.draw_mode^e->tpage)&0x19f))continue;
        RECT clip={p->state.clip_left,p->state.clip_top,p->state.clip_right-p->state.clip_left+1,p->state.clip_bottom-p->state.clip_top+1};
        if(Psyz_VideoGetWidescreen()) {
            DISPENV display;GetDispEnv(&display);
            /* PsyZ classifies a draw as widescreen from its current scissor.
             * Partial-cell clipping must not change that classification (PE2's
             * second buffer ends at row 511, beyond two 240-line displays).
             * Keep complete original sprites for these unresolved cases. */
            if(display.isrgb24 || display.disp.w!=320 || display.disp.h!=240 ||
               (display.screen.h && display.screen.h!=240) || display.screen.y<0 || display.screen.y>2)continue;
            int x=p->source.x0+p->state.offset_x,y=p->source.y0+p->state.offset_y;
            int left=x>clip.x?x:clip.x,top=y>clip.y?y:clip.y;
            int right=x+p->source.w<clip.x+clip.w?x+p->source.w:clip.x+clip.w;
            int bottom=y+p->source.h<clip.y+clip.h?y+p->source.h:clip.y+clip.h;
            int oldWide=clip.x>=display.disp.x && clip.x+clip.w<=display.disp.x+320 && clip.y>=0 && clip.y+clip.h<=480;
            int newWide=left>=display.disp.x && right<=display.disp.x+320 && top>=0 && bottom<=480;
            if(oldWide!=newWide)continue;
            if(oldWide && ((p->source.w%16 && (x+p->source.w)%4) ||
               (clip.w==320 && (x<clip.x || x+p->source.w>clip.x+clip.w))))continue;
        }
        if(peForegroundBuild(&p->packets,&p->source,p->state.draw_mode,&clip,p->state.offset_x,p->state.offset_y,pack->atlas_key,e->first_cell)) {p->ready=1;ready++;}
    }
    if(!ready) {DrawOTag((OT_TYPE*)head);return 0;}
    struct {OT_TYPE* node;u_long address;} changed[PE_FOREGROUND_MAX_SOURCES];unsigned changes=0;
    OT_TYPE *node=(OT_TYPE*)head,*previous=NULL;const void* output=head;
    for(unsigned visited=0;visited<65536;visited++) {
        OT_TYPE* next=nextPrim(node);int index=findRegistration(r,node);
        if(index>=0 && storage[index].ready) {
            Replacement* p=&storage[index];
            if(previous) {changed[changes].node=previous;changed[changes++].address=getaddr(previous);setaddr(previous,&p->packets.clip);}
            else output=&p->packets.clip;
            setaddr(&p->packets.restore,getaddr(node));previous=(OT_TYPE*)&p->packets.restore;
        } else previous=node;
        if(isendprim(node))break;node=next;
    }
    /* PsyZ psyz_addque2 calls GPU_Enqueue synchronously, copying LP64 command
     * bodies and interpolation metadata before returning; 32-bit dispatch is
     * immediate. Never restore links before this snapshot completes. */
    DrawOTag((OT_TYPE*)output);
    while(changes) {changes--;setaddr(changed[changes].node,changed[changes].address);}
    return ready;
}
