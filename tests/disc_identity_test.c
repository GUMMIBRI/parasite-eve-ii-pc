#ifdef NDEBUG
#undef NDEBUG
#endif
#include "port/disc_assets.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
static unsigned char image[64*2352];
static void word(unsigned char* p,unsigned n) {for(int i=0;i<4;i++)p[i]=(n>>(8*i))&255;}
static size_t record(unsigned char* p,const char* name,unsigned sector,unsigned size) {
    size_t n=strlen(name),bytes=(33+n+1)&~1u;p[0]=bytes;p[32]=n;
    word(p+2,sector);word(p+10,size);memcpy(p+33,name,n);return bytes;
}
static void fixture(const char* bin,int disc,int malformed) {
    memset(image,0,sizeof image);
    unsigned char* p=image+16*2352+24;p[0]=1;memcpy(p+1,"CD001",5);
    word(p+158,20);word(p+166,2048);
    p=image+20*2352+24;
    const char* one[]={"STAGE1.CDF;1","STAGE2.CDF;1","PE_DISK.01;1","SLUS_010.42;1"};
    const char* two[]={"STAGE4.CDF;1","STAGE5.CDF;1","PE_DISK.02;1","SLUS_010.55;1"};
    for(int i=0;i<4;i++)p+=record(p,disc==1?one[i]:two[i],30,2048);
    if(malformed) {p=image+20*2352+24;p[0]=34;p[32]=255;}
    FILE* f=fopen(bin,"wb");assert(f);assert(fwrite(image,1,sizeof image,f)==sizeof image);assert(!fclose(f));
}
int main(void) {
    char dir[]="/tmp/pe2-disc-identity-XXXXXX";assert(mkdtemp(dir));
    char bin[512],cue[512];snprintf(bin,sizeof bin,"%s/game.bin",dir);snprintf(cue,sizeof cue,"%s/game.cue",dir);
    FILE* f=fopen(cue,"w");assert(f);fputs("FILE \"game.bin\" BINARY\n TRACK 01 MODE2/2352\n INDEX 01 00:00:00\n",f);fclose(f);
    for(int n=1;n<=2;n++) {fixture(bin,n,0);PeDisc* d=peDiscOpen(cue);assert(d);assert(peDiscNumber(d)==n);peDiscClose(d);}
    f=fopen(cue,"w");assert(f);fprintf(f,"  FILE \"%s\" BINARY\n",bin);fclose(f);
    PeDisc* absolute=peDiscOpen(cue);assert(absolute);assert(peDiscNumber(absolute)==2);peDiscClose(absolute);
    fixture(bin,1,1);PeDisc* d=peDiscOpen(cue);assert(d);assert(peDiscNumber(d)==0);peDiscClose(d);
    assert(peDiscNumber(NULL)==0);
    unlink(bin);unlink(cue);rmdir(dir);return 0;
}
