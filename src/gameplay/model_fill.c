/* PE2 adapter. Original CPE/PE1 Build17 fill math retained below; integration
 * uses only PE2 typed model/coordinate sources. Original lighting authoritative. */
#include "gameplay/model_fill.h"
#include "main/gfx.h"
#include <psyz/gte.h>
#include <math.h>
#include <string.h>
static int selected_mode, fill_status;
static const char *fill_reason = "off";
void Pe2ModelFillSetMode(int mode) {
    selected_mode = mode >= 0 && mode <= 2 ? mode : 0;
    fill_status = selected_mode ? 1 : 0;
    fill_reason = selected_mode ? "awaiting-owned-lit-source" : "off";
}
int Pe2ModelFillGetMode(void) { return selected_mode; }
int Pe2ModelFillGetStatus(void) { return selected_mode ? fill_status : 0; }
const char *Pe2ModelFillGetReason(void) { return selected_mode ? fill_reason : "off"; }
/* Build17 orthogonal/uniform matrix acceptance, reused for each actual PE2
 * ancestor and the final composed world transform. */
static int uniform_rotation(const float r[3][3]) {
    float n[3] = {0};
    for (int i=0;i<3;i++) for(int j=0;j<3;j++) n[i] += r[i][j]*r[i][j];
    float mean=(n[0]+n[1]+n[2])/3.0f;
    if(mean<1e-8f || !__builtin_isfinite(mean)) return 0;
    for(int i=0;i<3;i++) if(fabsf(n[i]-mean)>mean*0.02f) return 0;
    for(int i=0;i<3;i++) for(int j=i+1;j<3;j++) {
        float dot=0; for(int k=0;k<3;k++) dot+=r[i][k]*r[j][k];
        if(fabsf(dot)>mean*0.02f) return 0;
    }
    return 1;
}
void Pe2ModelFillPrepare(Pe2ModelFillFrame *f, const TmdStreamWorkspace *ws) {
    memset(f,0,sizeof(*f));
    const int particles = Pe2ParticleLightsSealAvailable();
    if (!selected_mode && !particles) return;
    if (selected_mode) { fill_status=1; fill_reason="original-unknown-owner"; }
    if(!ws || !ws->obj || !ws->obj->source || !ws->obj->buffer ||
       !ws->normals || ws->normals!=ws->obj->source->normals ||
       ws->verts!=ws->obj->source->verts || !ws->obj->coords ||
       ws->obj->partCount<=0 || ws->obj->partCount>1024 ||
       ws->obj->partCount!=ws->obj->source->partCount ||
       (ws->obj->flags & TMD_OBJECT_SEMI_TRANS)) return;
    /* Match the complete live integer transform, not a guessed current part
     * index or a matrix from a previous frame. Read-only GTE accesses. */
    s16 rotation[9];
    for(unsigned reg=0;reg<5;reg++) {
        unsigned word=Psyz_GteCtrlRead(reg);
        rotation[reg*2]=(s16)word;
        if(reg<4) rotation[reg*2+1]=(s16)(word>>16);
    }
    const GfxCoord *part=NULL;
    for(int i=0;i<ws->obj->partCount;i++) {
        const GfxCoord *p=&ws->obj->coords[i];
        if(memcmp(p->workm.m,rotation,sizeof(rotation))) continue;
        if((s32)Psyz_GteCtrlRead(5)!=p->workm.t[0] ||
           (s32)Psyz_GteCtrlRead(6)!=p->workm.t[1] ||
           (s32)Psyz_GteCtrlRead(7)!=p->workm.t[2]) continue;
        /* Two distinct coordinate owners with the same integer transform do
         * not establish which original normal space is active. Decline. */
        if(part) { fill_reason="original-ambiguous-part"; return; }
        part=p;
    }
    if(!part) return;
    const GfxCoord *visited[64]; unsigned count=0;
    /* Establish the actual view ancestor without retaining borrowed pointers.
     * Do not reconstruct from mutable local coords: they can be newer than
     * the currently installed, already composed workm snapshot. */
    for(const GfxCoord *p=part;p!=&gGfxViewCoord;p=p->parent) {
        if(!p || count==64) {fill_reason="original-unknown-world-root";return;}
        for(unsigned i=0;i<count;i++) if(visited[i]==p) return;
        visited[count++]=p;
    }
    float view[3][3], world[3][3]={{0}};
    for(int i=0;i<3;i++) for(int j=0;j<3;j++)
        view[i][j]=gGfxViewCoord.workm.m[i][j]/4096.0f;
    if(!uniform_rotation(view)) {fill_reason="original-unsupported-view";return;}
    /* For the accepted uniform orthogonal view V, V^-1 = V^T / scale^2.
     * Thus world = V^-1 * exact installed part workm. No camera-facing key. */
    float scale2=0;
    for(int k=0;k<3;k++) scale2+=view[0][k]*view[0][k];
    for(int i=0;i<3;i++) for(int j=0;j<3;j++) for(int k=0;k<3;k++)
        world[i][j]+=view[k][i]*(rotation[k*3+j]/4096.0f)/scale2;
    if(!uniform_rotation(world)) return;
    memcpy(f->rotation,world,sizeof world);
    f->preset=selected_mode; f->directional=selected_mode==2;
    if (particles) Pe2ParticleLightsPrepareModel(&f->particles, ws, &part->workm, &gGfxViewCoord.workm);
    if (selected_mode) { fill_status=2; fill_reason="owned-lit-source-prepared"; }
}
static void modelFillApplyColour(const Pe2ModelFillFrame *f, const SVECTOR *normal, void *rgb) {
    if(!f || !f->preset || !normal || !rgb) return;
    /* Same complete normal already consumed by original lighting. Reject zero
     * and unsupported magnitudes rather than introduce fill for unknown data. */
    float len2=(float)normal->vx*normal->vx+(float)normal->vy*normal->vy+(float)normal->vz*normal->vz;
    if(len2<1024.0f*1024.0f || len2>8192.0f*8192.0f) return;
    uint32_t colour; memcpy(&colour,rgb,sizeof colour);
    unsigned r=colour&255,g=(colour>>8)&255,b=(colour>>16)&255;
    unsigned brightest=r>g?r:g;if(b>brightest)brightest=b;
    if(!brightest||brightest==255)return;
    unsigned strength=40;
    if(f->preset==2 && f->directional) {
        float world[3]={0};
        const s16 *n=&normal->vx;
        for(int row=0;row<3;row++)for(int col=0;col<3;col++)world[row]+=f->rotation[row][col]*n[col];
        float length=world[0]*world[0]+world[1]*world[1]+world[2]*world[2];
        if(length<=1e-8f||!__builtin_isfinite(length))return;
        float ndl=(-0.8f*world[1]-0.6f*world[2])/sqrtf(length);
        ndl=ndl<0?0:ndl>1?1:ndl;
        strength=24+(unsigned)(40.0f*ndl+0.5f);
    }
    unsigned headroom=255-brightest;
    r+=(r*headroom*strength+32768u)>>16;
    g+=(g*headroom*strength+32768u)>>16;
    b+=(b*headroom*strength+32768u)>>16;
    colour=(colour&0xff000000u)|(r>255?255:r)|((g>255?255:g)<<8)|((b>255?255:b)<<16);
    memcpy(rgb,&colour,sizeof colour);
}

void Pe2ModelFillDisable(Pe2ModelFillFrame *f)
{
    f->preset=0;f->particles.valid=0;
}
void Pe2ModelFillApply(const Pe2ModelFillFrame *f, const SVECTOR *normal, const SVECTOR *vertex, void *rgb)
{
    if(!f||(!f->preset&&!f->particles.valid)||!normal||!rgb)return;
    uint32_t authored;memcpy(&authored,rgb,sizeof authored);
    modelFillApplyColour(f,normal,rgb);
    if(f->particles.valid)Pe2ParticleLightsApply(&f->particles,vertex,normal,rgb,authored);
}
