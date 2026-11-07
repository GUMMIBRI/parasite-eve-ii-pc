#ifndef PORT_FOREGROUND_PACK_H
#define PORT_FOREGROUND_PACK_H
#include <stddef.h>
#include <stdint.h>
enum {PE_FOREGROUND_MAX_SOURCES=512,PE_FOREGROUND_PACK_HEADER=48,PE_FOREGROUND_PACK_ENTRY=16};
typedef struct {unsigned source_id,tpage,clut,width,height,u,v,first_cell,inset;} PeForegroundSource;
typedef struct {
    uint64_t background_key,atlas_key;
    unsigned location[4],count,cells;
    PeForegroundSource sources[PE_FOREGROUND_MAX_SOURCES];
} PeForegroundPack;
int peForegroundParsePack(PeForegroundPack* pack,const unsigned char* bytes,size_t size,
                          uint64_t background_key,const int location[6]);
#endif
