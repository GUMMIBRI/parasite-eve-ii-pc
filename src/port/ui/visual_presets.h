/* SPDX-License-Identifier: MIT
 * Adapted from PE1 Build17 native_experience.h (explicitly MIT).
 * Bounded native visual presets do not own gameplay/System preferences.
 * Include after ui/hd_preferences.h in the native host settings TU. */
#ifndef PE2_VISUAL_PRESETS_H
#define PE2_VISUAL_PRESETS_H
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#ifdef PE2_PS5_HOST
#include <psyz/video.h>
#include <psyz/gpu.h>
#include <psyz/fsr1.h>
#include <psyz/font_profiles.h>
#include <psyz/movie_policy.h>
/* Only lightweight game declarations; no retail bool/type headers. */
extern void Pe2ModelFillSetMode(int);
extern int Pe2ModelFillGetMode(void);
extern void Pe2ParticleGeometrySetMode(int);
extern int Pe2ParticleGeometryGetMode(void);
extern void Pe2ParticleLightsSetMode(int);
extern int Pe2ParticleLightsGetMode(void);
extern void Pe2ShadowSetMode(int);
extern void Psyz_GpuSetShadowMode(int);
extern int Psyz_GpuGetShadowMode(void);
extern void Psyz_VideoSetDisplayFilter(int);
extern int Psyz_VideoGetDisplayFilter(void);

enum { PE_VISUAL_CLASSIC=0,PE_VISUAL_MODERN=1 };
/* Append only: stable mask IDs and flat config names, never unrelated fields. */
enum {
    PV_SCALE=0,PV_ASPECT=1,PV_DITHER=2,PV_AA=3,PV_FILTER=4,PV_LIGHT=5,
    PV_EFFECT=6,PV_BACKGROUNDS=7,PV_MODELS=8,PV_FILL=9,PV_FSR=10,PV_SHARP=11,
    PV_MODEL_FILL=12,PV_MOVIE_FRAME=13,PV_MOVIE_CLEANUP=14,PV_PARTICLES=15,
    PV_PARTICLE_LIGHTS=16,PV_DIALOGUE=17,PV_MENU_FONT=18,PV_SHADOW=19,
    PV_DISPLAY_FILTER=20,PV_INTERPOLATION=21,PV_WIDE=22,PV_COUNT=23
};
typedef struct { const char *key;unsigned min,max,classic; } PeVisualField;
static const PeVisualField pe_visual_fields[PV_COUNT]={
    {"scale",1,8,1},{"aspect",0,1,0},{"dither",0,1,0},{"aa",0,1,0},
    {"model_filter",0,1,0},{"dynamic_light",0,1,0},{"effect_precision",0,1,0},
    {"backgrounds",0,1,0},{"models",0,1,0},{"gameplay_fill",0,1,0},
    {"fsr",0,1,0},{"sharpness",0,2,1},{"model_fill",0,2,0},
    {"movie_framing",0,1,0},{"movie_cleanup",0,3,0},{"particles",0,2,0},
    {"particle_lights",0,1,0},{"dialogue_font",0,3,0},{"menu_font",0,3,0},
    {"shadow",0,2,0},{"display_filter",0,2,0},{"interpolation",0,1,0},{"expanded_backgrounds",0,1,0}
};
_Static_assert(PV_COUNT>0&&PV_COUNT<=32,"Visual snapshot uses at most32 stable fields");
#define PE_VISUAL_ALL (UINT32_MAX>>(32-PV_COUNT))
static unsigned pe_visual_modern[PV_COUNT];
static uint32_t pe_visual_seen,pe_visual_bad;
static int pe_visual_mode=PE_VISUAL_MODERN,pe_visual_pending=PE_VISUAL_MODERN;
static int pe_visual_presentation_seen,pe_visual_presentation_bad,pe_visual_loaded;

static unsigned PeVisualRead(unsigned field) {
    switch(field) {
    case PV_SCALE:return Psyz_VideoGetInternalResolution();
    case PV_ASPECT:return (unsigned)Psyz_VideoGetAspectMode();
    case PV_DITHER:return (unsigned)Psyz_VideoGetDitheringMode();
    case PV_AA:return (unsigned)Psyz_VideoGetAntialiasing();
    case PV_FILTER:return (unsigned)Psyz_VideoGetModelFiltering();
    case PV_LIGHT:return (unsigned)Psyz_VideoGetDynamicLighting();
    case PV_EFFECT:return (unsigned)Psyz_VideoGetEffectGeometryCorrection();
    case PV_BACKGROUNDS:return (unsigned)pe_hd_background_preference;
    case PV_MODELS:return (unsigned)pe_hd_preference;
    case PV_FILL:return (unsigned)Psyz_VideoGetGameplayFill();
    case PV_FSR:return (unsigned)Psyz_VideoGetFsr1Requested();
    case PV_SHARP:return (unsigned)Psyz_VideoGetFsr1Sharpness();
    case PV_MODEL_FILL:return (unsigned)Pe2ModelFillGetMode();
    case PV_MOVIE_FRAME:return (unsigned)Psyz_VideoGetMovieFraming();
    case PV_MOVIE_CLEANUP:return (unsigned)Psyz_VideoGetMovieCleanup();
    case PV_PARTICLES:return (unsigned)Pe2ParticleGeometryGetMode();
    case PV_PARTICLE_LIGHTS:return (unsigned)Pe2ParticleLightsGetMode();
    case PV_DIALOGUE:return Psyz_GpuGetFontStyle(PSYZ_FONT_DIALOGUE);
    case PV_MENU_FONT:return Psyz_GpuGetFontStyle(PSYZ_FONT_MENU);
    case PV_SHADOW:return (unsigned)Psyz_GpuGetShadowMode();
    case PV_DISPLAY_FILTER:return (unsigned)Psyz_VideoGetDisplayFilter();
    case PV_INTERPOLATION:return (unsigned)Psyz_GpuGetFrameInterpolation();
    case PV_WIDE:return (unsigned)Psyz_VideoGetWidescreen();
    default:return 0;
    }
}
static unsigned PeVisualBoundedRead(unsigned field) {
    unsigned value=PeVisualRead(field);
    return value>=pe_visual_fields[field].min&&value<=pe_visual_fields[field].max?
        value:pe_visual_fields[field].classic;
}
static void PeVisualWriteField(unsigned field,unsigned value) {
    if(PeVisualRead(field)==value)return;
    switch(field) {
    case PV_SCALE:Psyz_VideoSetInternalResolution(value);break;
    case PV_ASPECT:Psyz_VideoSetAspectMode((PsyzAspectMode)value);break;
    case PV_DITHER:Psyz_VideoSetDitheringMode((PsyzDitherMode)value);break;
    case PV_AA:Psyz_VideoSetAntialiasing((int)value);break;
    case PV_FILTER:Psyz_VideoSetModelFiltering((int)value);break;
    case PV_LIGHT:Psyz_VideoSetDynamicLighting((int)value);break;
    case PV_EFFECT:Psyz_VideoSetEffectGeometryCorrection((int)value);break;
    case PV_BACKGROUNDS:pe_hd_background_preference=(int)value;PeHdApplyBackgroundPreference();break;
    case PV_MODELS:if(!PeHdExplicitRoot()){pe_hd_preference=(int)value;PeHdApplyPreference();}break;
    case PV_FILL:Psyz_VideoSetGameplayFill((int)value);break;
    case PV_MODEL_FILL:Pe2ModelFillSetMode((int)value);break;
    case PV_MOVIE_FRAME:Psyz_VideoSetMovieFraming((int)value);Psyz_VideoSetMovieBlur(value==0);break;
    case PV_MOVIE_CLEANUP:Psyz_VideoSetMovieCleanup((int)value);break;
    case PV_PARTICLES:Pe2ParticleGeometrySetMode((int)value);break;
    case PV_PARTICLE_LIGHTS:Pe2ParticleLightsSetMode((int)value);break;
    case PV_DIALOGUE:Psyz_GpuSetFontStyle(PSYZ_FONT_DIALOGUE,value);break;
    case PV_MENU_FONT:Psyz_GpuSetFontStyle(PSYZ_FONT_MENU,value);break;
    case PV_SHADOW:Pe2ShadowSetMode(value!=0);Psyz_GpuSetShadowMode((int)value);break;
    case PV_DISPLAY_FILTER:Psyz_VideoSetDisplayFilter((int)value);break;
    case PV_INTERPOLATION:Psyz_GpuSetFrameInterpolation((int)value);break;
    case PV_WIDE:PeWideSetRequested((int)value);break;
    default:break; /* FSR pair is applied together, never two resource resets. */
    }
}
static void PeVisualSafety(void) {
    if(!Psyz_VideoGetGeometryCorrection())Psyz_VideoSetGeometryCorrection(1);
    Psyz_VideoSetMovieBlur(Psyz_VideoGetMovieFraming()==0);
}
static void PeVisualApply(const unsigned values[PV_COUNT]) {
    for(unsigned i=0;i<PV_COUNT;++i)if(i!=PV_FSR&&i!=PV_SHARP)PeVisualWriteField(i,values[i]);
    if(PeVisualRead(PV_FSR)!=values[PV_FSR]||PeVisualRead(PV_SHARP)!=values[PV_SHARP])
        Psyz_VideoSetFsr1((int)values[PV_FSR],(int)values[PV_SHARP]);
    PeVisualSafety();
}
static void PeVisualRememberModern(void) {
    for(unsigned i=0;i<PV_COUNT;++i) {
        /* Explicit root locks the active player choice. Keep its existing
         * stored Modern request even if Classic was loaded before the env
         * override appeared; a save must not erase that restore value. */
        if(i==PV_MODELS&&PeHdExplicitRoot()&&(pe_visual_seen&(UINT32_C(1)<<i)))continue;
        pe_visual_modern[i]=PeVisualBoundedRead(i);
    }
    pe_visual_seen=PE_VISUAL_ALL;
}
static void PeVisualBeginLoad(void) {
    pe_visual_seen=pe_visual_bad=0;
    pe_visual_pending=PE_VISUAL_MODERN;
    pe_visual_presentation_seen=pe_visual_presentation_bad=pe_visual_loaded=0;
}
/* Return1 valid/consumed,0 recognized but invalid,-1 unrelated/unknown.
 * Conflicting duplicates poison only that field: inherit loaded preferences
 * at finalize regardless of line order. Identical duplicates are harmless. */
static int PeVisualParse(const char *key,long value) {
    if(!key)return -1;
    if(!strcmp(key,"presentation")) {
        if(pe_visual_loaded||value<0||value>1||pe_visual_presentation_bad||
           (pe_visual_presentation_seen&&pe_visual_pending!=(int)value)) {
            pe_visual_presentation_bad=1;pe_visual_pending=PE_VISUAL_MODERN;return 0;
        }
        pe_visual_presentation_seen=1;pe_visual_pending=(int)value;return 1;
    }
    if(strncmp(key,"modern_",7))return -1;
    for(unsigned i=0;i<PV_COUNT;++i)if(!strcmp(key+7,pe_visual_fields[i].key)) {
        uint32_t bit=UINT32_C(1)<<i;
        if(pe_visual_loaded||value<(long)pe_visual_fields[i].min||
           value>(long)pe_visual_fields[i].max||(pe_visual_bad&bit)||
           ((pe_visual_seen&bit)&&pe_visual_modern[i]!=(unsigned)value)) {
            pe_visual_bad|=bit;pe_visual_seen&=~bit;return 0;
        }
        pe_visual_modern[i]=(unsigned)value;pe_visual_seen|=bit;return 1;
    }
    return -1;
}
/* Call exactly once AFTER all normal keys and old ui_font migration, including
 * missing-file/error paths. No file write, filesystem action or per-frame work. */
static void PeVisualLoaded(void) {
    if(pe_visual_loaded)return;
    for(unsigned i=0;i<PV_COUNT;++i)if(!(pe_visual_seen&(UINT32_C(1)<<i)))
        pe_visual_modern[i]=PeVisualBoundedRead(i);
    pe_visual_seen=PE_VISUAL_ALL;pe_visual_mode=pe_visual_pending;
    unsigned values[PV_COUNT];
    for(unsigned i=0;i<PV_COUNT;++i)values[i]=pe_visual_mode?
        pe_visual_modern[i]:pe_visual_fields[i].classic;
    pe_visual_loaded=1;PeVisualApply(values);
}
static int PeVisualGetPresentation(void) { return pe_visual_mode; }
static const char *PeVisualPresentationName(void) {
    return pe_visual_mode?"Modern":"Classic";
}
static const char *PeVisualStatus(void) {
    if(PeHdExplicitRoot())return pe_visual_mode?"Modern (HD pack override active)":
        "Classic (HD pack override active)";
    return pe_visual_mode?"Modern visual choices; controls and System appearance stay separate":
        "Classic visuals; saved Modern choices return when selected";
}
static void PeVisualSetPresentation(int mode) {
    if(mode<0||mode>1)return;
    if(!pe_visual_loaded)PeVisualLoaded();
    if(mode==pe_visual_mode)return;
    if(mode==PE_VISUAL_CLASSIC) {
        PeVisualRememberModern();unsigned values[PV_COUNT];
        for(unsigned i=0;i<PV_COUNT;++i)values[i]=pe_visual_fields[i].classic;
        PeVisualApply(values);
    } else PeVisualApply(pe_visual_modern);
    pe_visual_mode=mode;
}
static void PeVisualWrite(FILE *file) {
    if(!file)return;
    if(pe_visual_mode||pe_visual_seen!=PE_VISUAL_ALL)PeVisualRememberModern();
    fprintf(file,"presentation=%d\n",pe_visual_mode);
    for(unsigned i=0;i<PV_COUNT;++i)fprintf(file,"modern_%s=%u\n",pe_visual_fields[i].key,pe_visual_modern[i]);
}
#undef PE_VISUAL_ALL
#else
/* Desktop/guard build: the native preset owns no settings or extra APIs. */
static void PeVisualBeginLoad(void) { }
static void PeVisualLoaded(void) { }
static int PeVisualParse(const char *key,long value) { (void)key;(void)value;return -1; }
static int PeVisualGetPresentation(void) { return 1; }
static const char *PeVisualPresentationName(void) { return "Modern"; }
static const char *PeVisualStatus(void) { return "Native visual presets unavailable"; }
static void PeVisualSetPresentation(int mode) { (void)mode; }
static void PeVisualWrite(FILE *file) { (void)file; }
#endif
#endif
