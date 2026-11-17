/* MPL-2.0. Actual PE2 player ownership; no geometry classification. */
#ifndef PE2_HD_PLAYER_TEXTURES_H
#define PE2_HD_PLAYER_TEXTURES_H
#include "main/tmd_types.h"
void pe2HdPlayerBeginBuild(const TmdObject *model);
void pe2HdPlayerRegisterPacket(const TmdObject *model,unsigned page,unsigned clut);
void pe2HdModelCreate(const TmdObject *model);
void pe2HdModelRetire(const TmdObject *model,int destroy);
void pe2HdModelDraw(const TmdObject *model,unsigned half);
void pe2HdModelReset(int destroy);
void pe2HdModelRegisterPacket(const TmdObject *model,const void *payload,unsigned bytes,unsigned vertices,unsigned gouraud,unsigned page,unsigned clut,const unsigned char uv[8]);
#endif
