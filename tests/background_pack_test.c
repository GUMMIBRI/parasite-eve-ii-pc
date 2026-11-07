#include "port/background_pack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define CHECK(x) do { if(!(x)) {fprintf(stderr,"line %d: %s\n",__LINE__,#x);exit(1);} } while(0)
static void word(unsigned char* p,uint32_t value) {for(unsigned i=0;i<4;i++)p[i]=(unsigned char)(value>>(i*8));}
int main(void)
{
    static uint16_t rows[PE_BACKGROUND_PIXELS],columns[PE_BACKGROUND_PIXELS],out[PE_BACKGROUND_PIXELS];
    for(unsigned y=0;y<240;y++)for(unsigned x=0;x<320;x++) {
        uint16_t value=(uint16_t)((y*320+x)^0x8041);
        rows[y*320+x]=value;columns[x/16*16*240+y*16+x%16]=value;
    }
    uint64_t key=peBackgroundCopyNative(out,rows,0);
    CHECK(memcmp(out,rows,sizeof rows)==0);
    CHECK(peBackgroundCopyNative(out,columns,1)==key && memcmp(out,rows,sizeof rows)==0);
    columns[16*240+19]^=1;
    CHECK(peBackgroundCopyNative(out,columns,1)!=key);
    unsigned char data[49]={0};memcpy(data,"PE2BG1\0\0",8);
    word(data+8,(uint32_t)key);word(data+12,(uint32_t)(key>>32));word(data+16,320);word(data+20,240);
    word(data+24,(uint32_t)-64);word(data+28,384);word(data+32,1);word(data+36,4);word(data+40,420);
    PeBackgroundPack pack;
    CHECK(peBackgroundParsePack(&pack,data,48,key));
    CHECK(pack.left==-64 && pack.right==384 && pack.cells==420 && pack.key==key);
    CHECK(!peBackgroundParsePack(&pack,data,47,key));CHECK(!peBackgroundParsePack(&pack,data,49,key));
    CHECK(!peBackgroundParsePack(&pack,data,48,key^1));
    const unsigned offsets[]={0,16,20,24,28,32,36,40,44};
    for(unsigned i=0;i<sizeof offsets/sizeof offsets[0];i++) {
        unsigned char saved=data[offsets[i]];data[offsets[i]]^=1;
        CHECK(!peBackgroundParsePack(&pack,data,48,key));data[offsets[i]]=saved;
    }
    word(data+24,(uint32_t)-112);word(data+40,465);CHECK(!peBackgroundParsePack(&pack,data,48,key));
    word(data+24,0);word(data+28,320);word(data+40,300);CHECK(peBackgroundParsePack(&pack,data,48,key));
    unsigned char png[24]={137,'P','N','G',13,10,26,10,0,0,0,13,'I','H','D','R',0,0,4,64,0,0,10,24};
    /* 300 cells -> 19 atlas rows -> 1088 x 2584, bounded before image decode. */
    CHECK(peBackgroundCheckPngHeader(png,24,&pack));
    CHECK(!peBackgroundCheckPngHeader(png,23,&pack));
    png[16]=127;CHECK(!peBackgroundCheckPngHeader(png,24,&pack));png[16]=0;
    png[0]=0;CHECK(!peBackgroundCheckPngHeader(png,24,&pack));
    puts("Background pack: row/column identity and strict metadata validation pass");return 0;
}
