/* MPL-2.0. PE2 original still-image ownership; no replacement assets. */
#include "port/hd_background.h"
#if defined(PE2_PS5_HOST)
#include <stdint.h>
#include <string.h>
#include <libgpu.h>
#include <psyz/cap_font.h>
#include <psyz/hd_background.h>
static const unsigned char *owner;
static int rows, validated;
static uint64_t stripDigest[20][2];
static uint64_t serial, digest[2];
/* Decode generation above is NOT an upload invocation identity. */
static uint64_t uploadCounter, uploadFrameSerial;
static PsyzHdBackgroundFrame uploadFrame;
static unsigned char canonical[320*240*2], column[16*240*2];
static const uint16_t *armed;
static int ax,ay,aw,ah;
static PsyzHdBackgroundUpload pending;
/* FsImgBuffers is twenty packed 16x240 RGB16 columns, or one row frame.
 * Explicit LE bytes keep identity independent of host struct/padding. */
static void hashOwner(uint64_t hash[2]) {
 unsigned x,y;
 for(y=0;y<240;y++) for(x=0;x<320;x++) {
  unsigned i=rows?(y*320+x):((x/16)*16*240+y*16+x%16);
  uint16_t word; memcpy(&word,owner+2*i,2);
  canonical[2*(y*320+x)]=(unsigned char)word;
  canonical[2*(y*320+x)+1]=(unsigned char)(word>>8);
 }
 Psyz_FontHash128(canonical,sizeof(canonical),hash);
}
static int lookup(const uint16_t *pixels,int x,int y,int w,int h,
                  PsyzHdBackgroundUpload *out) {
 unsigned xx,yy;
 if(!owner||!validated||!armed||pixels!=armed||x!=ax||y!=ay||w!=aw||h!=ah||!out)return 0;
 /* Revalidate exactly the live upload, against the frame snapshot validated
  * once at producer entry. Source layout is packed in both admitted cases. */
 for(yy=0;yy<(unsigned)h;yy++)for(xx=0;xx<(unsigned)w;xx++) {
  uint16_t word;unsigned i=2*((pending.cropY+yy)*320+pending.cropX+xx);
  memcpy(&word,(const unsigned char*)pixels+2*(yy*w+xx),2);
  if(canonical[i]!=(unsigned char)word||canonical[i+1]!=(unsigned char)(word>>8)) {
   peHdBackgroundRetire();return 0;
  }
 }
 *out=pending;return 1;
}
void peHdBackgroundRetire(void) {
 owner=0;armed=0;validated=0;Psyz_GpuSetHdBackgroundLookup(0);
}
void peHdBackgroundBegin(void) {
 uint64_t now[2];validated=0;armed=0;
 /* EVERY call retires the preceding frame admission, even with no owner.
  * Never wrap/reuse a valid serial: exhaustion publishes unsupported0 forever. */
 uploadFrameSerial=uploadCounter<UINT64_MAX-1?++uploadCounter:0;
 memset(&uploadFrame,0,sizeof uploadFrame);uploadFrame.uploadFrameSerial=uploadFrameSerial;
 if(owner) {
  hashOwner(now);
  if(now[0]!=digest[0]||now[1]!=digest[1])peHdBackgroundRetire();
  else {
   validated=1;
   if(uploadFrameSerial){uploadFrame.known=1;uploadFrame.generation=serial;
    uploadFrame.sourceHash[0]=digest[0];uploadFrame.sourceHash[1]=digest[1];
    uploadFrame.sourceWidth=320;uploadFrame.sourceHeight=240;}
  }
 }
 Psyz_GpuBackgroundFrameBegin(&uploadFrame);
}
void peHdBackgroundEnd(void) {
 /* Keep invocation identity even when its owner retired or no upload armed. */
 uint64_t ended=uploadFrameSerial;validated=0;armed=0;uploadFrameSerial=0;
 Psyz_GpuBackgroundFrameEnd(ended);
}
void peHdBackgroundRegister(const void *workspace,int contiguous) {
 peHdBackgroundRetire();
 if(!workspace||serial==UINT64_MAX)return;
 owner=(const unsigned char*)workspace;rows=!!contiguous;++serial;
 hashOwner(digest);
 if(!rows) {
  unsigned strip,y;for(strip=0;strip<20;strip++) {
   for(y=0;y<240;y++)memcpy(column+y*32,canonical+(y*320+strip*16)*2,32);
   Psyz_FontHash128(column,sizeof(column),stripDigest[strip]);
  }
 }
 Psyz_GpuSetHdBackgroundLookup(lookup);
}
void peHdBackgroundLoad(int x,int y,int w,int h,void *pixels) {
 RECT rect;uintptr_t start=(uintptr_t)owner,p=(uintptr_t)pixels;unsigned offset,cx,cy;
 armed=0;
 if(owner&&validated&&p>=start&&p-start<sizeof(canonical)&&w>0&&h>0&&h<=240) {
  offset=(unsigned)(p-start);
  if(!(offset&1)) {
   if(rows){cx=(offset/2)%320;cy=(offset/2)/320;}
   else {cx=(offset/(16*240*2))*16;cy=(offset%(16*240*2))/(16*2);}
   if(cx+(unsigned)w<=320&&cy+(unsigned)h<=240&&
      ((rows&&w==320&&cx==0)||(!rows&&w==16&&offset%(16*2)==0))) {
    pending.stripWidth=0;pending.stripHash[0]=pending.stripHash[1]=0;
    if(!rows) {
     pending.stripHash[0]=stripDigest[cx/16][0];pending.stripHash[1]=stripDigest[cx/16][1];pending.stripWidth=16;
    }
    pending.uploadFrameSerial=uploadFrameSerial;
    pending.generation=serial;pending.sourceHash[0]=digest[0];pending.sourceHash[1]=digest[1];
    pending.sourceWidth=320;pending.sourceHeight=240;
    pending.cropX=cx;pending.cropY=cy;pending.cropWidth=w;pending.cropHeight=h;
    ax=x;ay=y;aw=w;ah=h;armed=(const uint16_t*)pixels;
   }
  }
 }
 rect.x=x;rect.y=y;rect.w=w;rect.h=h;
 LoadImage(&rect,(u_long*)pixels);armed=0;
}
#endif
