/* Exercise the real SDK setter and emulated SPU register interface. */
#include <libspu.h>
#include <psyz/spu.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define CHECK(x) do { if (!(x)) { fprintf(stderr, "line %d: %s\n", __LINE__, #x); exit(1); } } while (0)
void Psyz_PadsOverride(int p,char* f,int n){(void)p;(void)f;(void)n;}
static unsigned short reg(int voice, int word) { return Psyz_SpuRead(voice * 16 + word * 2); }
int main(void)
{
    SpuLVoiceAttr entries[5] = {0}, saved[5];
    unsigned short before[24][8];
    for (int v=0;v<24;++v) for(int w=0;w<8;++w) before[v][w]=reg(v,w);
    for (int i=0;i<2;++i) {
        entries[i].voiceNum=i ? 22 : 2;
        SpuVoiceAttr* a=&entries[i].attr;
        a->voice=1u<<7; /* List voiceNum, rather than this ignored selector, owns routing. */
        a->mask=SPU_VOICE_VOLL|SPU_VOICE_VOLR|SPU_VOICE_PITCH|SPU_VOICE_WDSA|SPU_VOICE_LSAX|SPU_VOICE_ADSR_ADSR1|SPU_VOICE_ADSR_ADSR2;
        a->volume.left=0x1234+i; a->volume.right=0x2345+i;
        a->pitch=0x1000+i*0x200; a->addr=0x1200+i*0x1000; a->loop_addr=0x1600+i*0x1000;
        a->adsr1=0x80ff; a->adsr2=0xffe0;
    }
    entries[2].voiceNum=2; entries[2].attr.mask=SPU_VOICE_PITCH; entries[2].attr.pitch=0x1800;
    entries[3].voiceNum=-1; entries[4].voiceNum=24;
    memcpy(saved,entries,sizeof entries);
    SpuLSetVoiceAttr(5,entries);
    CHECK(reg(2,2)==0x1800 && reg(22,2)==0x1200);
    for(int i=0;i<2;++i) {
        int v=entries[i].voiceNum;
        CHECK(reg(v,0)==0x1234+i && reg(v,1)==0x2345+i);
        CHECK(reg(v,3)==entries[i].attr.addr/8 && reg(v,7)==entries[i].attr.loop_addr/8);
        CHECK(reg(v,4)==0x80ff && reg(v,5)==0xffe0);
    }
    CHECK(memcmp(entries,saved,sizeof entries)==0);
    SpuLSetVoiceAttr(0,NULL);
    for(int v=0;v<24;++v) if(v!=2 && v!=22)
        for(int w=0;w<8;++w) CHECK(reg(v,w)==before[v][w]);
    puts("SPU list attributes: two voices, partial update, sample/loop addresses, ADSR and volumes reach hardware; input and other voices preserved");
    return 0;
}
