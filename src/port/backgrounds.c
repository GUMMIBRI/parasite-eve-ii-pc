#include "port/backgrounds.h"
#include "port/background_pack.h"
#include <psyz/gpu.h>
#include <psyz/video.h>
#include <SDL3/SDL.h>
#include <libgpu.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct { u_long addr,len,words[3]; } AtlasSelection;
typedef struct { DR_TPAGE mode; AtlasSelection selection; SPRT_16 sprite; } BackgroundTile;
static BackgroundTile tilePackets[480];
static DR_TPAGE restorePacket;

static int selectAtlas(const u_long* words,int available,void* unused)
{
    (void)unused;
    if(available<3)return -1;
    uint64_t key=(uint64_t)(uint32_t)words[1]|((uint64_t)(uint32_t)words[2]<<32);
    Psyz_GpuSelectSpriteAtlas(key,(uint32_t)words[0]&0xffffff);
    return 3;
}

static uint16_t nativeRows[PE_BACKGROUND_PIXELS];
static uint64_t previousKey,observedKey;
static PeBackgroundPack currentPack;
static int packAvailable;
static char packRoot[4096];
static int configured;

static int location[6],locationDirty=1;
void peBackgroundSetLocation(int stage,int area,int view,int room_state,int warp,int variant)
{
    int next[6]={stage,area,view,room_state,warp,variant};
    if(memcmp(location,next,sizeof location)) {memcpy(location,next,sizeof location);locationDirty=1;}
}

static void recordLocation(uint64_t key)
{
    const char* root=getenv("PE2_DUMP_BACKGROUNDS");
    if(!root || !*root)return;
    char path[4352];
    if(!SDL_CreateDirectory(root))return;
    int n=snprintf(path,sizeof path,"%s/observations.jsonl",root);
    if(n<0 || n>=(int)sizeof path)return;
    FILE* file=fopen(path,"a");
    if(file) {
        fprintf(file,"{\"key\":\"%016" PRIx64 "\",\"stage\":%d,\"area\":%d,\"view\":%d,\"room_state\":%d,\"warp\":%d,\"variant\":%d}\n",
                key,location[0],location[1],location[2],location[3],location[4],location[5]);
        fclose(file);
    }
}

static void dumpNative(uint64_t key)
{
    const char* root=getenv("PE2_DUMP_BACKGROUNDS");
    if(!root || !*root)return;
    char path[4352];
    if(!SDL_CreateDirectory(root) || snprintf(path,sizeof path,"%s/%016" PRIx64 ".rgb555",root,key)>=(int)sizeof path)return;
    FILE* file=fopen(path,"rb");
    if(file) { fclose(file);return; }
    file=fopen(path,"wb");
    if(!file)return;
    for(unsigned i=0;i<PE_BACKGROUND_PIXELS;i++) {
        fputc(nativeRows[i]&255,file);fputc(nativeRows[i]>>8,file);
    }
    int failed=ferror(file);if(fclose(file))failed=1;
    if(failed)remove(path);
    else fprintf(stderr,"[background] captured %016" PRIx64 "\n",key);
}

static int materialIsOpaque(const char* path,const PeBackgroundPack* pack)
{
    SDL_Surface* image=SDL_LoadPNG(path);
    if(!image)return 0;
    SDL_Surface* rgba=SDL_ConvertSurface(image,SDL_PIXELFORMAT_RGBA32);
    SDL_DestroySurface(image);
    if(!rgba)return 0;
    int valid=rgba->w==16*68 && rgba->h==(int)((pack->cells+15)/16)*136;
    for(unsigned cell=0;cell<pack->cells && valid;cell++) {
        unsigned x=cell%16*68,y=cell/16*68;
        for(unsigned row=0;row<68 && valid;row++) {
            const unsigned char* pixels=(const unsigned char*)rgba->pixels+(y+row)*rgba->pitch+x*4;
            for(unsigned column=0;column<68;column++)if(pixels[column*4+3]!=255) {valid=0;break;}
        }
    }
    SDL_DestroySurface(rgba);return valid;
}

static void preparePack(uint64_t key)
{
    if(previousKey==key)return;
    previousKey=key;
    /* One live background's atlas: room/view changes cannot accumulate GPU memory.
     * Missing/animated unmodified sources do not force an idle GPU wait. */
    if(packAvailable)Psyz_GpuResetSpriteAtlases();
    packAvailable=0;
    if(!*packRoot)return;
    char path[4352];
    int n=snprintf(path,sizeof path,"%s/%016" PRIx64 ".pe2bg",packRoot,key);
    if(n<0 || n>=(int)sizeof path)return;
    FILE* file=fopen(path,"rb");
    if(!file)return;
    unsigned char metadata[PE_BACKGROUND_META_BYTES+1];
    size_t bytes=fread(metadata,1,sizeof metadata,file);
    int failed=ferror(file);fclose(file);
    if(failed || !peBackgroundParsePack(&currentPack,metadata,bytes,key)) {
        fprintf(stderr,"[background] invalid metadata for %016" PRIx64 "; using original\n",key);return;
    }
    n=snprintf(path,sizeof path,"%s/%016" PRIx64 ".png",packRoot,key);
    if(n<0 || n>=(int)sizeof path)return;
    /* Verify atlas extent against metadata before the shared GPU loader sees it. */
    unsigned char pngHeader[24];
    file=fopen(path,"rb");
    int valid=0;
    if(file) {
        size_t got=fread(pngHeader,1,sizeof pngHeader,file);
        if(!fseek(file,0,SEEK_END)) {
            long encoded=ftell(file);
            valid=encoded>=24 && encoded<=64*1024*1024 &&
                  peBackgroundCheckPngHeader(pngHeader,got,&currentPack);
        }
        fclose(file);
    }
    if(!valid || !materialIsOpaque(path,&currentPack) || Psyz_GpuLoadSpriteAtlas(key,path)!=1) {
        fprintf(stderr,"[background] unavailable atlas for %016" PRIx64 "; using original\n",key);return;
    }
    packAvailable=1;
    fprintf(stderr,"[background] loaded %016" PRIx64 " span %d..%d\n",key,currentPack.left,currentPack.right);
}

void peBackgroundDraw(const void* source,int columns,int buffer_y,int offset_y)
{
    if(!configured) {
        const char* root=getenv("PE2_HD_BACKGROUNDS");
        if(root && strlen(root)<sizeof packRoot)strcpy(packRoot,root);
        Psyz_GpuRegisterCommandHandler(0xf8,selectAtlas,NULL);
        configured=1;
    }
    /* Cropped transitions and movies do not claim static full-frame coverage. */
    if(!source || offset_y || (!*packRoot && !getenv("PE2_DUMP_BACKGROUNDS"))) {
        peBackgroundSetCoverage(buffer_y,0,320);return;
    }
    uint64_t key=peBackgroundCopyNative(nativeRows,source,columns);
    if(observedKey!=key || locationDirty) {recordLocation(key);locationDirty=0;}
    if(observedKey!=key) {dumpNative(key);observedKey=key;}
    /* PsyZ's material plane is display-only above native resolution. At 1x,
     * enabling wide without that plane would expose an unsqueezed LoadImage. */
    if(Psyz_VideoGetInternalResolution()<2) {peBackgroundSetCoverage(buffer_y,0,320);return;}
    preparePack(key);
    if(!packAvailable) { peBackgroundSetCoverage(buffer_y,0,320);return; }
    int wide=peBackgroundSetCoverage(buffer_y,currentPack.left,currentPack.right);
    DRAWENV saved;
    GetDrawEnv(&saved);
    unsigned cell=0,used=0;
    void* first=NULL;
    void* previous=NULL;
    for(int y=0;y<240;y+=16)for(int x=currentPack.left;x<currentPack.right;x+=16,cell++) {
        if(!wide && (x<0 || x>=320))continue;
        BackgroundTile* tile=&tilePackets[used++];
        int sourceX=x<0 || x>=320?0:x;
        setDrawTPage(&tile->mode,0,0,getTPage(2,0,sourceX&~255,buffer_y&~255));
        setlen(&tile->selection,3);
        tile->selection.words[0]=0xf8000000u|cell|(wide?0x800000u:0);
        tile->selection.words[1]=(uint32_t)key;
        tile->selection.words[2]=(uint32_t)(key>>32);
        setSprt16(&tile->sprite);setRGB0(&tile->sprite,128,128,128);
        setXY0(&tile->sprite,x-saved.ofs[0],y+buffer_y-saved.ofs[1]);
        tile->sprite.u0=sourceX&255;tile->sprite.v0=(buffer_y&255)+y;tile->sprite.clut=0;
        if(previous)catPrim(previous,&tile->mode);else first=&tile->mode;
        catPrim(&tile->mode,&tile->selection);catPrim(&tile->selection,&tile->sprite);
        previous=&tile->sprite;
    }
    setDrawTPage(&restorePacket,saved.dfe,saved.dtd,saved.tpage);
    if(previous)catPrim(previous,&restorePacket);
    termPrim(&restorePacket);
    /* One FIFO submission preserves atlas selection per sprite and avoids a
     * separate GPU submission/transfer allocation for every single tile. */
    if(first)DrawOTag(first);
    DrawSync(0);
}
