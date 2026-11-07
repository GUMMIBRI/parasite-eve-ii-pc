/* Packet bounds and unsupported-state fallback; GPU parity is a separate probe. */
#include "port/background_foreground.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define CHECK(x) do {if(!(x)) {fprintf(stderr,"line %d: %s\n",__LINE__,#x);exit(1);}} while(0)
void Psyz_PadsOverride(int p,char* f,int n) {(void)p;(void)f;(void)n;}
static struct {PeForegroundPackets packets;uint64_t guard;} storage;
int main(void)
{
    SPRT sprite={0};setSprt(&sprite);setXY0(&sprite,-7,-11);setRGB0(&sprite,96,160,128);
    sprite.w=8;sprite.h=23;sprite.u0=248;sprite.v0=248;sprite.clut=123;
    SPRT original=sprite;RECT clip={150,100,80,100};
    PeForegroundPackets* p=&storage.packets;storage.guard=UINT64_C(0xfedcba9876543210);
    CHECK(peForegroundBuild(p,&sprite,0xe100008d,&clip,160,120,1,7)==&p->clip);
    CHECK(!memcmp(&sprite,&original,sizeof sprite));
    CHECK(p->tiles[0].sprite.u0==248 && p->tiles[0].sprite.v0==248);
    CHECK(p->tiles[1].sprite.u0==248 && p->tiles[1].sprite.v0==8);
    CHECK(p->tiles[0].selection.words[0]==0xf8000007);
    CHECK(p->tiles[1].selection.words[0]==0xf8000008);
    CHECK(nextPrim(&p->tiles[1].sprite)==&p->restore && isendprim(&p->restore));
    DR_AREA expected;SetDrawArea(&expected,&clip);
    CHECK(!memcmp(p->restore.code,expected.code,sizeof expected.code));
    sprite.x0=1000;sprite.w=32;
    CHECK(!peForegroundBuild(p,&sprite,0xe100008d,&clip,160,120,1,0));
    sprite=original;CHECK(!peForegroundBuild(p,&sprite,0xe100108d,&clip,160,120,1,0));
    CHECK(!peForegroundBuild(p,&sprite,0xe100008d,&clip,160,120,1,0x7fffff));
    sprite.w=320;sprite.h=240;
    CHECK(peForegroundBuild(p,&sprite,0xe100008d,&clip,160,120,1,0));
    CHECK(nextPrim(&p->tiles[PE_FOREGROUND_MAX_CELLS-1].sprite)==&p->restore);
    CHECK(storage.guard==UINT64_C(0xfedcba9876543210));
    sprite=original;sprite.w=32;sprite.h=40;
    CHECK(peForegroundBuildLayout(p,&sprite,0xe100008d,&clip,160,120,1,0,1));
    CHECK(getlen(&p->clip)==0 && getlen(&p->restore)==0);
    CHECK(p->tiles[4].sprite.x0==sprite.x0 && p->tiles[4].sprite.y0==sprite.y0+24);
    CHECK(p->tiles[4].sprite.v0==(unsigned char)(sprite.v0+24));
    sprite.code|=2;CHECK(!peForegroundBuildLayout(p,&sprite,0xe100008d,&clip,160,120,1,0,1));
    sprite=original;CHECK(!peForegroundBuildLayout(p,&sprite,0xe100008d,&clip,160,120,1,0,1));
    puts("Foreground packets: wrapped UV, exact clip restore, bounded cells and unsupported-state fallback OK");
    return 0;
}
