#include "port/background_foreground.h"
#include <stdlib.h>
#include <string.h>
#include <psyz/video.h>
#include <psyz/gpu.h>
#include "port/foreground_stage.h"

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
    unsigned stage_cell;int staged;
    PeGpuState state;SPRT source;PeForegroundPackets packets;
} Replacement;
typedef struct {
    Registry* registry;Replacement* replacements;
    PeForegroundStage stage;const uint16_t* vram;unsigned cells;
} Plan;
static unsigned char stageKnown[1024*512];
static union {uint64_t alignment;uint16_t words[64*256];} stagePixels,stageBackup;
static union {uint64_t alignment;uint16_t words[1024*512];} stageSnapshot;
static Replacement* storage;
static unsigned storage_count;
static void observeReplacement(const void* packet,unsigned offset,const uint32_t* words,unsigned count,const PeGpuState* before,void* context)
{
    (void)offset;Plan* plan=context;int index=findRegistration(plan->registry,packet);if(index<0)return;
    Replacement* p=&plan->replacements[index];if(!p->entry)return;
    unsigned code=words[0]>>24;
    if(code==0xe1) {if(p->sprites || ++p->modes>1)p->bad=1;return;}
    if(!code && (words[0]==0 || words[0]==PSYZ_MERGED_PRIM_NOP))return;
    if((code&~3u)==0x64 && count==4 && p->modes==1 && !p->sprites++) {
        memset(&p->source,0,sizeof p->source);setSprt(&p->source);
        memcpy(&p->source.r0,words,16);p->state=*before;
        const PeForegroundSource* e=p->entry;
        if(plan->vram && !e->inset && !before->texture_window &&
           (p->source.w%16 || p->source.h%16) && p->source.w==e->width && p->source.h==e->height &&
           p->source.u0==e->u && p->source.v0==e->v && p->source.clut==e->clut && !((before->draw_mode^e->tpage)&0x19f)) {
            PeForegroundSource source=*e;source.tpage=before->draw_mode&511;
            if(peForegroundStageCopy(&source,plan->vram,plan->stage.known,plan->cells,stagePixels.words)) {
                p->staged=1;p->stage_cell=plan->cells;
                plan->cells+=((e->width+15)/16)*((e->height+15)/16);
            }
        }
        return;
    }
    p->bad=1;
}
static void observe(const void* packet,unsigned offset,const uint32_t* words,unsigned count,const PeGpuState* before,void* context)
{
    Plan* plan=context;
    /* Resolve the source before this primitive invalidates its destination. */
    observeReplacement(packet,offset,words,count,before,context);
    peForegroundStageObserve(packet,offset,words,count,before,&plan->stage);
}
unsigned peForegroundSubmitOt(const void* head,const PeGpuState* initial,const PeForegroundPack* pack,unsigned render_height,int allow_staging)
{
    Registry* r=registryAt(head);
    if(!r || !r->valid || !r->count || !initial || !pack || !pack->atlas_key || !pack->count || (render_height!=240 && render_height!=256) ||
       pack->count>PE_FOREGROUND_MAX_SOURCES) {DrawOTag((OT_TYPE*)head);return 0;}
    if(!r->sorted) {qsort(r->entries,r->count,sizeof(*r->entries),orderRegistration);r->sorted=1;}
    for(unsigned i=1;i<r->count;i++)if(r->entries[i-1].packet==r->entries[i].packet) {DrawOTag((OT_TYPE*)head);return 0;}
    if(r->count>storage_count) {
        Replacement* next=realloc(storage,(size_t)r->count*sizeof(*next));
        if(!next) {DrawOTag((OT_TYPE*)head);return 0;}
        storage=next;storage_count=r->count;
    }
    for(unsigned i=0;i<r->count;i++) {
        Replacement* p=&storage[i];p->entry=NULL;p->modes=p->sprites=0;p->bad=p->ready=p->staged=0;
        for(unsigned j=0;j<pack->count;j++)if(pack->sources[j].source_id==r->entries[i].source_id) {p->entry=&pack->sources[j];break;}
    }
    PeGpuState state=*initial;Plan plan={.registry=r,.replacements=storage};
    const unsigned char* known=NULL;DISPENV display;GetDispEnv(&display);
    int needStage=0;
    for(unsigned i=0;i<pack->count;i++)if(!pack->sources[i].inset && (pack->sources[i].width%16 || pack->sources[i].height%16))needStage=1;
    if(needStage && allow_staging && Psyz_VideoGetInternalResolution()>1 && !display.isrgb24 && display.disp.x==0 &&
       display.disp.w==320 && display.disp.h==240 && (display.disp.y==0 || display.disp.y==272) &&
       (!display.screen.h || display.screen.h==240) && display.screen.y>=0 && display.screen.y<=2) {
        PeGpuState validation=*initial;
        if(!peGpuWalkOt(&validation,head,NULL,NULL)) {DrawOTag((OT_TYPE*)head);return 0;}
        /* A completed native snapshot also resolves prior GPU work. A CPU
         * upload mirror cannot establish this transfer/readback boundary. */
        RECT all={0,0,1024,512};DrawSync(0);
        if(StoreImage(&all,(u_long*)stageSnapshot.words)>=0) {
            DrawSync(0);plan.vram=stageSnapshot.words;memset(stageKnown,1,sizeof stageKnown);known=stageKnown;
        }
    }
    peForegroundStageBegin(&plan.stage,plan.vram?stageKnown:NULL);
    if(!peGpuWalkOt(&state,head,observe,&plan)) {DrawOTag((OT_TYPE*)head);return 0;}
    int stageX=0,stageY=0;
    int stageAvailable=plan.cells && peForegroundStageChoose(&plan.stage,known,&stageX,&stageY);
    unsigned ready=0,stageUsed=0;
    for(unsigned i=0;i<r->count;i++) {
        Replacement* p=&storage[i];const PeForegroundSource* e=p->entry;
        if(!e || p->bad || p->modes!=1 || p->sprites!=1 || p->state.texture_window || p->source.w!=e->width || p->source.h!=e->height ||
           p->source.u0!=e->u || p->source.v0!=e->v || p->source.clut!=e->clut || ((p->state.draw_mode^e->tpage)&0x19f))continue;
        if(e->inset && (p->source.code&2))continue;
        int partial=p->source.w%16 || p->source.h%16;
        if(partial && !e->inset && !(p->staged && stageAvailable))continue;
        RECT clip={p->state.clip_left,p->state.clip_top,p->state.clip_right-p->state.clip_left+1,p->state.clip_bottom-p->state.clip_top+1};
        if(Psyz_VideoGetWidescreen()) {
            /* Never emit the legacy partial-cell scissor: it changes native
             * framebuffer feedback. Full cells, inset tails and staged zero
             * padding preserve the original batch. */
            if(display.isrgb24 || display.disp.w!=320 || display.disp.h!=240 ||
               (display.screen.h && display.screen.h!=240) || display.screen.y<0 || display.screen.y>2)continue;
            int x=p->source.x0+p->state.offset_x;
            int oldWide=clip.x>=display.disp.x && clip.x+clip.w<=display.disp.x+320 && clip.y>=0 && clip.y+clip.h<=2*(int)render_height;
            if(oldWide && ((p->source.w%16 && (x+p->source.w)%4) ||
               (clip.w==320 && (x<clip.x || x+p->source.w>clip.x+clip.w))))continue;
        }
        SPRT source=p->source;uint32_t mode=p->state.draw_mode;unsigned layout=e->inset;
        if(p->staged) {mode=(mode&~0x1ffu)|getTPage(2,(mode>>5)&3,stageX,stageY);source.clut=0;layout=2;}
        if(peForegroundBuildLayout(&p->packets,&source,mode,&clip,p->state.offset_x,p->state.offset_y,pack->atlas_key,e->first_cell,layout)) {
            if(p->staged) {
                unsigned cells=((e->width+15)/16)*((e->height+15)/16);
                for(unsigned cell=0;cell<cells;cell++) {
                    p->packets.tiles[cell].sprite.u0=((p->stage_cell+cell)%4)*16;
                    p->packets.tiles[cell].sprite.v0=((p->stage_cell+cell)/4)*16;
                }
                setlen(&p->packets.restore_mode,1);p->packets.restore_mode.code[0]=p->state.draw_mode;stageUsed=1;
            }
            p->ready=1;ready++;
        }
    }
    if(!ready) {DrawOTag((OT_TYPE*)head);return 0;}
    RECT stageRect={stageX,stageY,64,256};
    if(stageUsed) {
        /* Caller guarantees a drained main-field boundary. Never transfer
         * between original primitives: that would change framebuffer feedback. */
        DrawSync(0);
        for(unsigned row=0;row<256;row++)
            memcpy(stageBackup.words+row*64,plan.vram+(stageY+row)*1024+stageX,64*2);
        LoadImage(&stageRect,(u_long*)stagePixels.words);DrawSync(0);
    }
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
    if(stageUsed) {DrawSync(0);LoadImage(&stageRect,(u_long*)stageBackup.words);DrawSync(0);}
    return ready;
}
