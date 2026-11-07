/* Hidden GPU experiment: arbitrary foreground dimensions through SPRT_16 cells.
 * Explicit clip/offset input; no connection to live room OTs yet. */
#include "port/backgrounds.h"
#include "port/background_foreground.h"
#include <psyz.h>
#include <psyz/gpu.h>
#include <psyz/video.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void Psyz_PadsOverride(int port,char* frame,int length) {(void)port;(void)frame;(void)length;}
static unsigned short initial[1024*512],original[1024*512],enhanced[1024*512];
static PeForegroundPackets packets;
static int capture(const char* prefix,const char* suffix)
{
    int w,h;unsigned char* rgb=Psyz_VideoAllocRenderedFrame(&w,&h);
    if(!rgb)return 0;
    char path[4096];snprintf(path,sizeof path,"%s.%s.ppm",prefix,suffix);
    FILE* file=fopen(path,"wb");if(!file)return 0;
    fprintf(file,"P6\n%d %d\n255\n",w,h);fwrite(rgb,3,(size_t)w*h,file);
    int failed=ferror(file);if(fclose(file))failed=1;free(rgb);return !failed;
}
int main(int argc,char** argv)
{
    if(argc!=11)return 2;
    FILE* file=fopen(argv[1],"rb");if(!file || fread(initial,2,1024*512,file)!=1024*512)return 2;fclose(file);
    uint64_t key=strtoull(argv[2],NULL,16);
    ResetGraph(0);Psyz_VideoSetVsyncMode(PSYZ_VSYNC_LIMITLESS);
    Psyz_VideoSetInternalResolution((unsigned)atoi(argv[8]));
    DRAWENV draw;DISPENV display;
    SetDefDrawEnv(&draw,0,0,320,240);SetDefDispEnv(&display,0,0,320,240);
    draw.ofs[0]=160;draw.ofs[1]=120;PutDrawEnv(&draw);PutDispEnv(&display);SetDispMask(1);Psyz_VideoVSync(0);
    peBackgroundDraw(NULL,0,0,0); /* Registers the existing FIFO atlas selector. */
    peBackgroundSetWidescreen(atoi(argv[9]));peBackgroundSetCoverage(0,-64,384);
    if(strcmp(argv[3],"none")) {
        int loaded=Psyz_GpuLoadSpriteAtlas(key,argv[3]);
        const char* headless=getenv("PSYZ_HEADLESS");
        if(loaded<0 || (!loaded && (!headless || strcmp(headless,"1"))))return 2;
    }
    if(atoi(argv[10]))for(int i=0;i<256;i++)initial[255*1024+i]^=31;
    SPRT sprite;setSprt(&sprite);setRGB0(&sprite,96,160,128);sprite.code|=atoi(argv[7])&3;
    setXY0(&sprite,-7,-11);sprite.u0=248;sprite.v0=248;sprite.clut=getClut(0,255);
    sprite.w=atoi(argv[5]);sprite.h=atoi(argv[6]);
    RECT all={0,0,1024,512},clip={150,100,80,100};
    DR_AREA area;SetDrawArea(&area,&clip);
    DR_TPAGE mode;setDrawTPage(&mode,0,0,getTPage(1,(atoi(argv[7])>>2)&3,832,0));
    TILE front,witness;setTile(&front);setRGB0(&front,0,255,0);setXY0(&front,-3,-4);setWH(&front,3,4);
    SPRT ui=sprite;ui.x0=40; /* Same texture tuple, deliberately NOT registered. */
    setTile(&witness);setRGB0(&witness,0,0,255);setXY0(&witness,60,60);setWH(&witness,4,4);
    DR_STP mask={0},clearMask={0};setlen(&clearMask,1);setlen(&mask,1);
    clearMask.code[0]=0xe6000000u;
    mask.code[0]=0xe6000000u|(getenv("PE2_PROBE_MASK")?atoi(getenv("PE2_PROBE_MASK"))&3:0);
    DR_TWIN twin={0};setlen(&twin,1);twin.code[0]=getenv("PE2_PROBE_WINDOW")?0xe2000001u:0xe2000000u;
    int useOt=getenv("PE2_PROBE_OT")!=NULL;
    for(int pass=0;pass<2;pass++) {
        DrawPrim(&clearMask);DrawSync(0);LoadImage(&all,(u_long*)initial);DrawSync(0);
        if(pass && useOt) {
            OT_TYPE root={0};struct {DR_TPAGE mode;SPRT sprite;} merged={mode,sprite};
            if(MargePrim(&merged.mode,&merged.sprite))return 2;
            catPrim(&root,&area);catPrim(&area,&mask);catPrim(&mask,&twin);catPrim(&twin,&merged.mode);catPrim(&merged.mode,&ui);
            catPrim(&ui,&front);catPrim(&front,&witness);termPrim(&witness);
            peForegroundBeginOt(&root,1);peForegroundRegister(&root,&merged.mode,0);
            PeForegroundPack pack={.atlas_key=key,.count=1};
            pack.sources[0]=(PeForegroundSource){0,(unsigned)mode.code[0]&511,sprite.clut,sprite.w,sprite.h,sprite.u0,sprite.v0,0};
            PeGpuState state;if(!peGpuStateFromEnv(&state,&draw))return 2;
            OT_TYPE savedRoot=root;DR_AREA savedArea=area;DR_STP savedMask=mask;DR_TWIN savedTwin=twin;
            unsigned char savedMerged[sizeof merged];memcpy(savedMerged,&merged,sizeof merged);
            SPRT savedUi=ui;TILE savedFront=front,savedWitness=witness;
            unsigned replaced=peForegroundSubmitOt(&root,&state,&pack,240);
            if(memcmp(&root,&savedRoot,sizeof root) || memcmp(&area,&savedArea,sizeof area) || memcmp(&mask,&savedMask,sizeof mask) || memcmp(&twin,&savedTwin,sizeof twin) ||
               memcmp(&merged,savedMerged,sizeof merged) || memcmp(&ui,&savedUi,sizeof ui) ||
               memcmp(&front,&savedFront,sizeof front) || memcmp(&witness,&savedWitness,sizeof witness))return 4;
            printf("OT replacements: %u; original packet bytes restored\n",replaced);
        } else if(pass) {
            DrawPrim(&area);DrawPrim(&mask);DrawPrim(&twin);
            void* head=peForegroundBuild(&packets,&sprite,(uint32_t)mode.code[0],&clip,160,120,key,0);
            if(!head)return 2;DrawOTag(head);
            DrawPrim(&ui);DrawPrim(&front);DrawPrim(&witness);
        } else {DrawPrim(&area);DrawPrim(&mask);DrawPrim(&twin);DrawPrim(&mode);DrawPrim(&sprite);DrawPrim(&ui);DrawPrim(&front);DrawPrim(&witness);}
        DrawSync(0);Psyz_VideoVSync(0);
        StoreImage(&all,(u_long*)(pass?enhanced:original));
        if(!capture(argv[4],pass?"hd":"original"))return 2;
    }
    unsigned differences=0;for(unsigned i=0;i<1024*512;i++)differences+=original[i]!=enhanced[i];
    printf("Native differences: %u\n",differences);
    return differences?1:0;
}
