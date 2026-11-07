#include "port/background_pack.h"
#include <string.h>

uint64_t peBackgroundCopyNative(uint16_t* rows,const void* source,int columns)
{
    uint64_t hash=UINT64_C(14695981039346656037);
    const unsigned char* input=source;
    for(unsigned y=0;y<240;y++)for(unsigned x=0;x<320;x++) {
        unsigned index=columns?(x/16)*16*240+y*16+x%16:y*320+x;
        uint16_t value;
        memcpy(&value,input+index*2,2);
        rows[y*320+x]=value;
        hash=(hash^(value&255))*UINT64_C(1099511628211);
        hash=(hash^(value>>8))*UINT64_C(1099511628211);
    }
    return hash;
}
static uint32_t word(const unsigned char* p)
{
    return (uint32_t)p[0]|(uint32_t)p[1]<<8|(uint32_t)p[2]<<16|(uint32_t)p[3]<<24;
}
int peBackgroundParsePack(PeBackgroundPack* pack,const unsigned char* data,size_t size,uint64_t expected_key)
{
    if(!pack || !data || size!=48 || memcmp(data,"PE2BG1\0\0",8))return 0;
    uint64_t key=(uint64_t)word(data+8)|((uint64_t)word(data+12)<<32);
    /* Signed conversion without relying on unsigned-to-signed overflow. */
    int64_t left=word(data+24),right=word(data+28);
    if(left>INT32_MAX)left-=INT64_C(4294967296);
    if(right>INT32_MAX)right-=INT64_C(4294967296);
    if(!key || key!=expected_key || word(data+16)!=320 || word(data+20)!=240 ||
       left < -96 || left>0 || right<320 || right>416 || left%16 || right%16 ||
       word(data+32)!=1 || word(data+36)!=4 || word(data+44)!=0)return 0;
    unsigned cells=(unsigned)(right-left)/16*15;
    if(word(data+40)!=cells)return 0;
    pack->key=key;pack->left=(int)left;pack->right=(int)right;pack->cells=cells;
    return 1;
}

static uint32_t bigword(const unsigned char* p)
{
    return (uint32_t)p[0]<<24|(uint32_t)p[1]<<16|(uint32_t)p[2]<<8|p[3];
}
int peBackgroundCheckPngHeader(const unsigned char* bytes,size_t size,const PeBackgroundPack* pack)
{
    return bytes && pack && size>=24 && !memcmp(bytes,"\x89PNG\r\n\x1a\n",8) &&
           bigword(bytes+8)==13 && !memcmp(bytes+12,"IHDR",4) &&
           bigword(bytes+16)==16*68 && bigword(bytes+20)==((pack->cells+15)/16)*136;
}
