/* Hidden-GPU integration probe using supplied synthetic native pixels.
 * Not a default CTest: needs a GPU and locally built atlas fixture. */
#include "port/backgrounds.h"
#include <psyz.h>
#include <psyz/video.h>
#include <libgpu.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void Psyz_PadsOverride(int port,char* frame,int length) {(void)port;(void)frame;(void)length;}
static unsigned short pixels[320*240],before[1024*512],after[1024*512];
int main(int argc,char** argv)
{
    if(argc!=4 && argc!=5)return 2;
    FILE* file=fopen(argv[1],"rb");
    if(!file || fread(pixels,2,320*240,file)!=320*240)return 2;
    fclose(file);
    ResetGraph(0);
    Psyz_VideoSetVsyncMode(PSYZ_VSYNC_LIMITLESS);
    Psyz_VideoSetInternalResolution(argc==5?(unsigned)atoi(argv[4]):4);
    DRAWENV draw;DISPENV display;
    SetDefDrawEnv(&draw,0,0,320,240);SetDefDispEnv(&display,0,0,320,240);
    draw.ofs[0]=160;draw.ofs[1]=120; /* PE2 uses centred coordinates. */
    PutDrawEnv(&draw);PutDispEnv(&display);SetDispMask(1);
    Psyz_VideoVSync(0);
    RECT rect={0,0,320,240},all={0,0,1024,512};
    LoadImage(&rect,(u_long*)pixels);DrawSync(0);
    StoreImage(&all,(u_long*)before);
    peBackgroundSetWidescreen(atoi(argv[2]));
    peBackgroundDraw(pixels,0,0,0);
    DrawSync(0);Psyz_VideoVSync(0);
    StoreImage(&all,(u_long*)after);
    unsigned differences=0;for(unsigned i=0;i<1024*512;i++)differences+=before[i]!=after[i];
    int w,h;unsigned char* rgb=Psyz_VideoAllocRenderedFrame(&w,&h);
    if(!rgb)return 3;
    file=fopen(argv[3],"wb");if(!file)return 3;
    fprintf(file,"P6\n%d %d\n255\n",w,h);fwrite(rgb,3,(size_t)w*h,file);fclose(file);free(rgb);
    printf("Native differences: %u; rendered %dx%d\n",differences,w,h);
    return !atoi(argv[2]) && differences?1:0;
}
