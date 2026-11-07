#ifndef PORT_BACKGROUND_PACK_H
#define PORT_BACKGROUND_PACK_H
#include <stddef.h>
#include <stdint.h>

enum { PE_BACKGROUND_WIDTH=320, PE_BACKGROUND_HEIGHT=240,
       PE_BACKGROUND_PIXELS=320*240, PE_BACKGROUND_META_BYTES=48 };
typedef struct {
    uint64_t key;
    int left, right;
    unsigned cells;
} PeBackgroundPack;
/* Flatten native MDEC columns (20 x 16 x 240) or contiguous RGB555 rows.
 * The caller supplies the complete resident image and a 320x240 destination. */
uint64_t peBackgroundCopyNative(uint16_t* rows,const void* source,int columns);
/* Strict version-1 metadata, pointer-free little endian. Returns 1 if valid. */
int peBackgroundParsePack(PeBackgroundPack* pack,const unsigned char* bytes,size_t size,uint64_t expected_key);
int peBackgroundCheckPngHeader(const unsigned char* bytes,size_t size,const PeBackgroundPack* pack);
#endif
