#include "port/foreground_pack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define CHECK(x) do {if(!(x)){fprintf(stderr,"line %d: %s\n",__LINE__,#x);exit(1);}} while(0)
static void put(unsigned char* p,unsigned value,unsigned bytes) {for(unsigned i=0;i<bytes;i++)p[i]=(unsigned char)(value>>(i*8));}
int main(void)
{
    unsigned char data[80]={0},bad[81];memcpy(data,"PE2FG1\0",8);put(data+8,0x1234,4);put(data+16,0x5678,4);
    const int location[6]={1,20,10,1,1,1};for(unsigned i=0;i<4;i++)put(data+24+i*4,location[i],4);
    put(data+40,2,4);put(data+44,10,4);
    for(unsigned i=0;i<2;i++) {unsigned char* p=data+48+i*16;put(p,i*3,4);put(p+4,143,2);put(p+6,16320,2);
        put(p+8,i?24:8,2);put(p+10,i?56:23,2);p[12]=104;p[13]=8;put(p+14,i?2:0,2);}
    PeForegroundPack pack;CHECK(peForegroundParsePack(&pack,data,sizeof data,0x1234,location));
    CHECK(pack.count==2 && pack.cells==10 && pack.sources[1].first_cell==2 && pack.atlas_key==0x5678);
    CHECK(!peForegroundParsePack(&pack,data,sizeof data-1,0x1234,location));
    CHECK(!peForegroundParsePack(&pack,data,sizeof data,0x1235,location));
    for(unsigned i=0;i<4;i++) {int other[6];memcpy(other,location,sizeof other);other[i]++;CHECK(!peForegroundParsePack(&pack,data,sizeof data,0x1234,other));}
    const unsigned positions[]={0,8,40,44,56,74,78};
    for(unsigned i=0;i<sizeof positions/sizeof positions[0];i++) {memcpy(bad,data,sizeof data);bad[positions[i]]^=255;CHECK(!peForegroundParsePack(&pack,bad,sizeof data,0x1234,location));}
    memcpy(bad,data,sizeof data);bad[80]=0;CHECK(!peForegroundParsePack(&pack,bad,sizeof bad,0x1234,location));
    memcpy(bad,data,sizeof data);put(bad+64,0,4);CHECK(!peForegroundParsePack(&pack,bad,sizeof data,0x1234,location));
    memcpy(bad,data,sizeof data);put(bad+16,0,4);CHECK(!peForegroundParsePack(&pack,bad,sizeof data,0x1234,location));
    memcpy(bad,data,sizeof data);bad[5]='2';put(bad+64,4099,4);
    CHECK(peForegroundParsePack(&pack,bad,sizeof data,0x1234,location));
    CHECK(pack.sources[1].source_id==3 && pack.sources[1].inset==1 && !pack.sources[0].inset);
    put(bad+48,4096,4);CHECK(!peForegroundParsePack(&pack,bad,sizeof data,0x1234,location));
    put(bad+48,0,4);put(bad+64,8195,4);CHECK(!peForegroundParsePack(&pack,bad,sizeof data,0x1234,location));
    puts("Foreground pack: exact identity/context, bounded contiguous cells and strict metadata length OK");return 0;
}
