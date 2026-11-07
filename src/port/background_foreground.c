#include "port/background_foreground.h"
#include <stddef.h>

void* peForegroundBuildLayout(PeForegroundPackets* packets,const SPRT* source,
                       uint32_t draw_mode,const RECT* current_clip,
                       int offset_x,int offset_y,uint64_t atlas_key,unsigned first_cell,unsigned layout)
{
    if(!packets || !source || !current_clip || !atlas_key ||
       (draw_mode>>24)!=0xe1 || (source->code&~3)!=0x64 ||
       source->w<1 || source->w>320 || source->h<1 || source->h>240 ||
       current_clip->x<0 || current_clip->y<0 || current_clip->w<1 || current_clip->h<1 ||
       current_clip->x+current_clip->w>1024 || current_clip->y+current_clip->h>512 ||
       offset_x< -1024 || offset_x>1023 || offset_y< -1024 || offset_y>1023)return NULL;
    if(layout>2 || (layout==1 && ((source->code&2) || source->w<16 || source->h<16)) ||
       (layout==2 && (draw_mode&0x180)!=0x100))return NULL;
    unsigned columns=(source->w+15)/16,rows=(source->h+15)/16,count=columns*rows;
    if(count>PE_FOREGROUND_MAX_CELLS || first_cell>=0x800000u || count>0x800000u-first_cell)return NULL;
    if((draw_mode&0x3000) || source->x0< -1024 || source->y0< -1024 ||
       source->x0+(int)(columns-1)*16>1023 || source->y0+(int)(rows-1)*16>1023)return NULL;
    int x=source->x0+offset_x,y=source->y0+offset_y;
    int left=x>current_clip->x?x:current_clip->x;
    int top=y>current_clip->y?y:current_clip->y;
    int right=x+source->w<current_clip->x+current_clip->w?x+source->w:current_clip->x+current_clip->w;
    int bottom=y+source->h<current_clip->y+current_clip->h?y+source->h:current_clip->y+current_clip->h;
    if(left>=right || top>=bottom)return NULL;
    RECT clip={left,top,right-left,bottom-top},restore=*current_clip;
    SetDrawArea(&packets->clip,&clip);SetDrawArea(&packets->restore,&restore);
    /* Complete/inset cells fit inside the original SPRT. Keep its scissor and
     * batching: even a redundant DR_AREA would flush preceding GPU work. */
    if(layout || (!(source->w%16) && !(source->h%16))) {setlen(&packets->clip,0);setlen(&packets->restore,0);}
    setlen(&packets->mode,1);packets->mode.code[0]=draw_mode;
    catPrim(&packets->clip,&packets->mode);
    void* previous=&packets->mode;
    for(unsigned cell=0;cell<count;cell++) {
        int dx=(int)(cell%columns)*16,dy=(int)(cell/columns)*16;
        if(layout==1) {if(dx>source->w-16)dx=source->w-16;if(dy>source->h-16)dy=source->h-16;}
        PeForegroundTile* tile=&packets->tiles[cell];
        setlen(&tile->selection,3);
        tile->selection.words[0]=0xf8000000u|(first_cell+cell);
        tile->selection.words[1]=(uint32_t)atlas_key;
        tile->selection.words[2]=(uint32_t)(atlas_key>>32);
        setSprt16(&tile->sprite);tile->sprite.code|=source->code&3;
        setRGB0(&tile->sprite,source->r0,source->g0,source->b0);
        setXY0(&tile->sprite,source->x0+dx,source->y0+dy);
        tile->sprite.u0=(unsigned char)(source->u0+dx);
        tile->sprite.v0=(unsigned char)(source->v0+dy);tile->sprite.clut=source->clut;
        catPrim(previous,&tile->selection);catPrim(&tile->selection,&tile->sprite);
        previous=&tile->sprite;
    }
    setlen(&packets->restore_mode,0);catPrim(previous,&packets->restore_mode);
    catPrim(&packets->restore_mode,&packets->restore);termPrim(&packets->restore);
    return &packets->clip;
}

void* peForegroundBuild(PeForegroundPackets* packets,const SPRT* source,
                       uint32_t draw_mode,const RECT* current_clip,
                       int offset_x,int offset_y,uint64_t atlas_key,unsigned first_cell)
{
    return peForegroundBuildLayout(packets,source,draw_mode,current_clip,offset_x,offset_y,atlas_key,first_cell,0);
}
