#include "port/foreground_pack.h"
#include <string.h>
static unsigned u16(const unsigned char* p) {return p[0]|(unsigned)p[1]<<8;}
static uint32_t u32(const unsigned char* p) {return u16(p)|(uint32_t)u16(p+2)<<16;}
static uint64_t u64(const unsigned char* p) {return u32(p)|(uint64_t)u32(p+4)<<32;}
int peForegroundParsePack(PeForegroundPack* pack,const unsigned char* bytes,size_t size,
                          uint64_t background_key,const int location[6])
{
    if(!pack || !bytes || !location || size<48 || (memcmp(bytes,"PE2FG1\0",8) && memcmp(bytes,"PE2FG2\0",8)))return 0;
    unsigned version=bytes[5]-'0';
    unsigned count=u32(bytes+40),cells=u32(bytes+44);
    if(!count || count>PE_FOREGROUND_MAX_SOURCES || !cells || cells>960 || size!=48+(size_t)count*16 ||
       !background_key || u64(bytes+8)!=background_key || !u64(bytes+16) || u64(bytes+16)==background_key)return 0;
    for(unsigned i=0;i<4;i++)if(u32(bytes+24+i*4)!=(unsigned)location[i])return 0;
    if(location[0]<1 || location[0]>5 || location[1]<1 || location[1]>255 ||
       location[2]<1 || location[2]>50 || location[3]<1 || location[3]>255)return 0;
    unsigned next=0,previous=0;
    for(unsigned i=0;i<count;i++) {
        const unsigned char* p=bytes+48+i*16;
        PeForegroundSource s={u32(p),u16(p+4),u16(p+6),u16(p+8),u16(p+10),p[12],p[13],u16(p+14),0};
        if(version==2) {s.inset=(s.source_id>>12)&1;s.source_id&=~4096u;}
        if((s.inset && (s.width<16 || s.height<16)) || s.source_id>4095 || (i && s.source_id<=previous) || s.tpage>511 || ((s.tpage>>7)&3)==3 ||
           s.clut>32767 || !s.width || s.width>320 || !s.height || s.height>240 || s.first_cell!=next)return 0;
        next+=((s.width+15)/16)*((s.height+15)/16);
        if(next>cells)return 0;
        pack->sources[i]=s;previous=s.source_id;
    }
    if(next!=cells)return 0;
    pack->background_key=background_key;pack->atlas_key=u64(bytes+16);pack->count=count;pack->cells=cells;
    for(unsigned i=0;i<4;i++)pack->location[i]=(unsigned)location[i];
    return 1;
}
