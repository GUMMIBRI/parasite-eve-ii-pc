/* MPL-2.0. Exact model owner bridge to optional native texture admission. */
#include "gameplay/hd_player_textures.h"
#if defined(PE2_PS5_HOST)
#include "main/session.h"
#include "main/task_types.h"
#include <psyz/hd_upload.h>
static int is_player_model(const TmdObject *model)
{
    Task *player = gameGetTaskSlot(GAME_TASK_SLOT_PLAYER);
    return model && player && player->bodyKind == 1 && player->extra.tmd == model;
}
void pe2HdPlayerBeginBuild(const TmdObject *model)
{
    /* Invalidate the selected build half before any source-null early return. */
    if(model)Psyz_HdModelBuild(model,model->source,model->buffer,model->bufferHalfBytes,model->nextBufferHalf);
    Pe2HdUpload *state = Psyz_HdUploadState();
    if (state && is_player_model(model)) Pe2HdUploadClearOwners(state);
}
void pe2HdPlayerRegisterPacket(const TmdObject *model,unsigned page,unsigned clut)
{
    Pe2HdUpload *state = Psyz_HdUploadState();
    if (state && is_player_model(model)) Pe2HdUploadRegisterOwner(state,page,clut);
}
void pe2HdModelCreate(const TmdObject *m){Psyz_HdModelCreate(m);}
void pe2HdModelRetire(const TmdObject *m,int destroy){Psyz_HdModelRetire(m,destroy);}
void pe2HdModelReset(int destroy){Psyz_HdModelResetAll(destroy);}
void pe2HdModelDraw(const TmdObject *m,unsigned half){if(m)Psyz_HdModelDraw(m,m->source,m->buffer,m->bufferHalfBytes,half);}
void pe2HdModelRegisterPacket(const TmdObject *m,const void*p,unsigned b,unsigned v,unsigned g,unsigned page,unsigned clut,const unsigned char uv[8]){Psyz_HdModelRegister(m,p,b,v,g,page,clut,uv);}
#else
void pe2HdModelCreate(const TmdObject*m){(void)m;}
void pe2HdModelRetire(const TmdObject*m,int d){(void)m;(void)d;}
void pe2HdModelReset(int d){(void)d;}
void pe2HdModelDraw(const TmdObject*m,unsigned h){(void)m;(void)h;}
void pe2HdModelRegisterPacket(const TmdObject*m,const void*p,unsigned b,unsigned v,unsigned g,unsigned t,unsigned c,const unsigned char u[8]){(void)m;(void)p;(void)b;(void)v;(void)g;(void)t;(void)c;(void)u;}
void pe2HdPlayerBeginBuild(const TmdObject *model) { (void)model; }
void pe2HdPlayerRegisterPacket(const TmdObject *model,unsigned page,unsigned clut)
{ (void)model; (void)page; (void)clut; }
#endif
