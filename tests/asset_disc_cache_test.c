#ifdef NDEBUG
#undef NDEBUG
#endif
#include "port/asset_bind.h"
#include "port/asset_parts.h"
#include "port/disc_assets.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

static unsigned char actual[4];
PE_ASSET_BIND("test/disc", actual);
const PeAssetPackage gPeAssetPackages[]={{"test",1,0,0}};
const int gPeAssetPackageCount=1;
const PeAssetPart gPeAssetParts[]={{"test/disc",0,0,4,PE_ASSET_OP_COPY,0,0}};
const int gPeAssetPartCount=1;
struct PeDisc { unsigned char value; int readable; };
static unsigned reads;
uint8_t* peDiscReadPackage(PeDisc* d,int stage,int folder,int file,size_t* size) {
    (void)stage;(void)folder;(void)file;reads++;
    if(!d->readable)return NULL;
    uint8_t* bytes=malloc(4);assert(bytes);memset(bytes,d->value,4);*size=4;return bytes;
}
uint8_t* peDiscReadFile(PeDisc* d,const char* name,size_t* size) {
    (void)d;(void)name;(void)size;assert(0);return NULL;
}
int main(void) {
    PeDisc first={0x11,1},second={0x22,1},missing={0,0};
    assert(peAssetsLoad(&first)==1 && actual[0]==0x11 && actual[3]==0x11);
    assert(peAssetsLoad(&second)==1 && actual[0]==0x22 && actual[3]==0x22);
    assert(peAssetsLoad(&missing)==0 && actual[0]==0x22);
    assert(peAssetsLoad(&first)==1 && actual[0]==0x11);
    assert(reads==4);
    return 0;
}
