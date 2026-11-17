/* Host settings/disc UI adapted from parasite-eve-pc/src/main/boot:
 * settings_overlay.h (Plex painter + SDL_GPU compositor), main.c (modal
 * event ownership, native file dialogs, audio/clock pause and pad reset).
 * Kept separate from retail headers: their bool typedef is not SDL's ABI. */
#include <SDL3/SDL.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <psyz.h>
#include <psyz/audio.h>
#include <psyz/cd.h>
#include <psyz/video.h>
#include <psyz/overlay.h>
#include <psyz/overlay_sdl3.h>
#include <psyz/overlay_sdl3_gpu.h>
#include <libgpu.h>
#include "port/host_ui.h"
#include "port/disc_assets.h"
#include "port/asset_bind.h"
#ifdef PE2_PS5_HOST
#include "port/ps5_paths.h"
#include "port/analog_controls.h"
#include <errno.h>
#include <psyz/font_profiles.h>
#endif
#define STBTT_STATIC
#define STB_TRUETYPE_IMPLEMENTATION
#include "ui/stb_truetype.h"
#include "ui/fonts/ibm_plex_sans.ttf.inc"
#include "../../third_party/psyz/external/SDL/src/render/gpu/shaders/tri_texture.vert.spv.h"
#include "../../third_party/psyz/external/SDL/src/render/gpu/shaders/tri_texture.vert.msl.h"
#include "../../third_party/psyz/external/SDL/src/render/gpu/shaders/tri_texture.vert.dxil.h"
#include "../../third_party/psyz/external/SDL/src/render/gpu/shaders/texture_rgba.frag.spv.h"
#include "../../third_party/psyz/external/SDL/src/render/gpu/shaders/texture_rgba.frag.msl.h"
#include "../../third_party/psyz/external/SDL/src/render/gpu/shaders/texture_rgba.frag.dxil.h"

enum { OVERLAY_HEADER_H=128, OVERLAY_ROW_H=46, OVERLAY_ACTION_GAP=14,
       OVERLAY_FOOTER_H=90, OVERLAY_REFERENCE_H=820, OVERLAY_PANEL_W=680 };
typedef struct { uint8_t* pixels; int w,h; } OverlaySurface;
typedef struct { float scale; int x,y,w,h; } OverlayLayout;
typedef struct { float r,g,b,a; } Color;
typedef struct { int open,page,row,scroll,dirty,quit,capture; } HostOverlayState;
/* The panel always shows this many rows, so its height, tab bar and footer stay put when the page changes. */
enum { VISIBLE_ROWS=8 };
static const Color kPanel={0.075f,0.082f,0.102f,0.96f}, kText={0.93f,0.95f,0.98f,1},
    kMuted={0.60f,0.65f,0.73f,1}, kAccent={0.27f,0.62f,1,1};
#include "ui/paint.h"
#ifdef PE2_PS5_HOST
#include "ui/appearance.h"
#endif
#ifdef PE2_PS5_HOST
static int PePresentationStatsReady(void);
#endif
#include "ui/gpu.h"
#ifdef PE2_PS5_HOST
#include "ui/presentation_stats.h"
#include "port/interpolation_bind.h"
#include "port/playtest_assists.h"
#include "ui/mod_preferences.h"
#include "ui/hd_preferences.h"
#include "ui/qol_preferences.h"
#include <psyz/fsr1.h>
#include <psyz/movie_policy.h>
#include <psyz/shadow_metadata.h>
extern void Pe2ModelFillSetMode(int mode);
extern int Pe2ModelFillGetMode(void);
extern const char *Pe2ModelFillGetReason(void);
extern void Psyz_VideoSetDisplayFilter(int mode);
extern int Psyz_VideoGetDisplayFilter(void);
extern const char *Psyz_VideoDisplayFilterStatus(void);
extern void Pe2ShadowSetMode(int mode);
extern int Pe2ShadowGetStatus(void);
extern const char *Pe2ShadowGetReason(void);
extern void Pe2ParticleLightsSetMode(int mode);
extern int Pe2ParticleLightsGetMode(void);
extern const char *Pe2ParticleLightsGetReason(void);
extern void Pe2ParticleGeometrySetMode(int mode);
extern int Pe2ParticleGeometryGetMode(void);
extern const char *Pe2ParticleGeometryGetReason(void);
extern const char *Psyz_GpuWideBackgroundStatus(void);
static void PeWideSetRequested(int enabled) {
    Psyz_VideoSetWidescreen(enabled);
    if(enabled) { Psyz_VideoSetWidescreenCentred(1); Psyz_VideoSetWidescreenField(0); }
    PeHdApplyBackgroundPreference();
}
#include "ui/visual_presets.h"
static PsyzOverlayFrameCB pe_previous_frame_callback;
static int pe_host_focus_blocked;
static void PeNativeOverlayFrame(void)
{
    if(pe_previous_frame_callback)pe_previous_frame_callback();
    if(!s_overlayState.open)PePresentationStatsRefreshGPU();
}
#endif

static char discPaths[2][4096], configPath[4096], statusText[256];
static int preferenceSaveFailed;
const char *peHostLastStatus(void) { return statusText; }
static int requiredDisc, selectedDisc;
static const char* const pages[]={"Graphics","Controls","Audio","Discs"
#ifdef PE2_PS5_HOST
    ,"System","Assists","Pause"
#endif
};
enum { HOST_PAGE_COUNT=sizeof pages/sizeof pages[0] };
#ifdef PE2_PS5_HOST
enum { HOST_PAGE_PAUSE=HOST_PAGE_COUNT-1 };
enum { PAUSE_RESUME, PAUSE_RETURN_TITLE, PAUSE_EXIT_GAME, PAUSE_ROW_COUNT };
#endif
static const char* const buttons[]={"Select","L3","R3","Start","Up","Right","Down","Left",
    "L2","R2","L1","R1","Triangle","Circle","Cross","Square"};
static const char* configDir;
static PsyzOverlayEventFilter_SDL3 previousFilter;
static SDL_Window* uiWindow;
#ifdef PE2_PS5_HOST
#include "ui/gamepad_bindings.h"
#include "ui/system_info.h"
#endif

static int rowCount(void) {
    return s_overlayState.page==0?
#ifdef PE2_PS5_HOST
        28:
#else
        8:
#endif
        s_overlayState.page==2?1:s_overlayState.page==1?
#ifdef PE2_PS5_HOST
        41:
#else
        16:
#endif
#ifdef PE2_PS5_HOST
        s_overlayState.page==HOST_PAGE_PAUSE?PAUSE_ROW_COUNT:
        s_overlayState.page==5?PeModRows():
        s_overlayState.page==4?PE_SYSTEM_ROWS:
#endif
        2;
}

static int maxScroll(void) { int n=rowCount()-VISIBLE_ROWS; return n>0?n:0; }

/* Scroll by the least amount that keeps the selected row in view (keyboard and pad); the mouse wheel sets it directly. */
static void ensureRowVisible(void) {
    if(s_overlayState.scroll>maxScroll())s_overlayState.scroll=maxScroll();
    if(s_overlayState.scroll<0)s_overlayState.scroll=0;
    if(s_overlayState.row<s_overlayState.scroll)s_overlayState.scroll=s_overlayState.row;
    else if(s_overlayState.row>=s_overlayState.scroll+VISIBLE_ROWS)
        s_overlayState.scroll=s_overlayState.row-VISIBLE_ROWS+1;
}

static void setPage(int page) { s_overlayState.page=page;s_overlayState.capture=0;s_overlayState.row=0;s_overlayState.scroll=0; }

static void saveOptions(void) {
    if(!*configPath){preferenceSaveFailed=1;SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION,"PE2 preferences: no writable configuration path");return;}
    char temp[4120];
    snprintf(temp,sizeof temp,"%s.tmp",configPath);
#ifdef PE2_PS5_HOST
    if (!pePs5WritePathAllowed(temp) || !pePs5WritePathAllowed(configPath)) {
        preferenceSaveFailed=1; SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION,"PE2 preferences: path rejected: %s",configPath);
        snprintf(statusText,sizeof statusText,"Preferences path is outside permitted USB/homebrew storage.");return;
    }
#endif
    FILE* f=fopen(temp,"w");
    if(!f) { preferenceSaveFailed=1; SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION,"PE2 preferences: open %s failed errno=%d",temp,errno); snprintf(statusText,sizeof statusText,"Could not save preferences."); return; }
    fprintf(f,"disc1=%s\ndisc2=%s\nscale=%u\naspect=%d\ndither=%d\ngeometry=%d\naa=%d\nfilter=%d\nlight=%d\nvolume=%u\n",
        discPaths[0],discPaths[1],Psyz_VideoGetInternalResolution(),Psyz_VideoGetAspectMode(),
        Psyz_VideoGetDitheringMode(),Psyz_VideoGetGeometryCorrection(),Psyz_VideoGetAntialiasing(),
        Psyz_VideoGetModelFiltering(),Psyz_VideoGetDynamicLighting(),Psyz_AudioGetOutputVolume());
#ifdef PE2_PS5_HOST
    fprintf(f,"always_run=%d\n",peAlwaysRun());
    fprintf(f,"hd_characters=%d\nmenu_font=%u\ndialogue_font=%u\nanalog_mode=%d\nanalog_run_threshold=%u\n",
        pe_hd_preference,Psyz_GpuGetFontStyle(PSYZ_FONT_MENU),Psyz_GpuGetFontStyle(PSYZ_FONT_DIALOGUE),peAnalogControlsMode(),peAnalogRunThreshold());
    fprintf(f,"hd_backgrounds=%d\n",pe_hd_background_preference);
    QolSave(f);
    PeVisualWrite(f);
    fprintf(f,"expanded_backgrounds=%d\n",Psyz_VideoGetWidescreen());
    PeModWrite(f);
    fprintf(f,"player_shadow=%d\nparticle_lights=%d\nparticle_geometry=%d\neffect_precision=%d\n",
        Psyz_GpuGetShadowMode(),Pe2ParticleLightsGetMode(),Pe2ParticleGeometryGetMode(),Psyz_VideoGetEffectGeometryCorrection());
    fprintf(f,"show_fps=%d\nframe_interpolation=%d\n",PePresentationShowFps(),Psyz_GpuGetFrameInterpolation());
    fprintf(f,"menu_style=%u\nmenu_text_size=%u\nmenu_pointer=%u\n",OverlayAppearanceGetStyle(),OverlayAppearanceGetTextSize(),OverlayAppearanceGetPointer());
    fprintf(f,"display_filter=%d\nfsr1=%d\nfsr1_sharpness=%d\nmodel_fill=%d\nmovie_cleanup=%d\nmovie_framing=%d\ngameplay_fill=%d\n",
        Psyz_VideoGetDisplayFilter(),Psyz_VideoGetFsr1Requested(),Psyz_VideoGetFsr1Sharpness(),Pe2ModelFillGetMode(),
        Psyz_VideoGetMovieCleanup(),Psyz_VideoGetMovieFraming(),Psyz_VideoGetGameplayFill());
#endif
    for(unsigned i=0;i<16;i++) fprintf(f,"key%u=%d\n",i,Psyz_GetKeyboardBinding_SDL3(i));
#ifdef PE2_PS5_HOST
    PePadWrite(f);
#endif
    int failed=(ferror)(f); if(fclose(f)) failed=1;
#ifdef PE2_PS5_HOST
    if(!pePs5WritePathAllowed(temp)||!pePs5WritePathAllowed(configPath))failed=1;
#endif
    if(failed) {
        preferenceSaveFailed=1;
        SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION,"PE2 preferences: write or close failed for %s",temp);
    } else if(rename(temp,configPath)) {
        preferenceSaveFailed=1;
        SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION,"PE2 preferences: rename %s to %s failed errno=%d",temp,configPath,errno);
    } else preferenceSaveFailed=0;
}

static void loadOptions(void) {
#ifdef PE2_PS5_HOST
    PePadBeginLoad();
#endif
#ifdef PE2_PS5_HOST
    /* Native first-run presentation defaults. Explicit saved values below win. */
    Psyz_VideoSetInternalResolution(2);
    Psyz_VideoSetGeometryCorrection(1);
#endif
    configDir=getenv("PE2_CONFIG_DIR");
#ifdef PE2_PS5_HOST
    configDir=pePs5ConfigDirectory();
    if(!configDir) { fprintf(stderr,"[ps5] Preferences unavailable: %s\n",pePs5StorageReason());configPath[0]=0;return; }
#else
    if(!configDir) configDir=SDL_GetPrefPath("parasite-eve","parasite-eve-ii");
    if(!configDir) configDir=".";
#endif
#ifdef PE2_PS5_HOST
    /* pePs5ConfigDirectory already created and positively opened the directory.
     * Do not repeat native directory creation through a different SDL provider. */
    if(!pePs5WritePathAllowed(configDir)) {
        fprintf(stderr,"[ps5] Preferences directory rejected: %s\n",pePs5StorageReason());
        configPath[0]=0;return;
    }
#else
    SDL_CreateDirectory(configDir);
#endif
    int configLength=snprintf(configPath,sizeof configPath,"%s/settings.ini",configDir);
    if(configLength<0 || configLength>=(int)sizeof configPath) {
        fprintf(stderr,"Preferences directory path is too long.\n");snprintf(statusText,sizeof statusText,"Preferences file path exceeds its bounded buffer.");configPath[0]=0;return;
    }
    FILE* f=fopen(configPath,"r"); if(!f)return;
    char line[8192];
#ifdef PE2_PS5_HOST
    int legacy_font=-1,menu_font=-1,dialogue_font=-1;
#endif
    while(fgets(line,sizeof line,f)) {
        line[strcspn(line,"\r\n")]=0;
        char* eq=strchr(line,'='); if(!eq)continue; *eq++=0;
        if(!strcmp(line,"disc1")||!strcmp(line,"disc2")) {
            if(strlen(eq)<sizeof discPaths[0]) strcpy(discPaths[line[4]-'1'],eq);
            continue;
        }
        char* end; long n=strtol(eq,&end,10);
        if(end==eq||*end){
#ifdef PE2_PS5_HOST
            if(!strcmp(line,"assist_group_enabled"))PeModParse(line,-1);
#endif
            continue;
        }
#ifdef PE2_PS5_HOST
        if(!strcmp(line,"expanded_backgrounds") && n>=0 && n<=1) { PeWideSetRequested((int)n);continue; }
        if(PeModParse(line,n)>=0)continue;
        if(PeVisualParse(line,n)>=0)continue;
#endif
        if(!strcmp(line,"scale") && n>=1 && n<=8) Psyz_VideoSetInternalResolution((unsigned)n);
        else if(!strcmp(line,"aspect") && n>=0 && n<=1) Psyz_VideoSetAspectMode(n);
        else if(!strcmp(line,"dither") && n>=0 && n<=1) Psyz_VideoSetDitheringMode(n);
        else if(!strcmp(line,"geometry") && n>=0 && n<=1) Psyz_VideoSetGeometryCorrection(n);
        else if(!strcmp(line,"aa") && n>=0 && n<=1) Psyz_VideoSetAntialiasing(n);
        else if(!strcmp(line,"filter") && n>=0 && n<=1) Psyz_VideoSetModelFiltering(n);
        else if(!strcmp(line,"light") && n>=0 && n<=1) Psyz_VideoSetDynamicLighting(n);
        else if(!strcmp(line,"volume") && n>=0 && n<=100) Psyz_AudioSetOutputVolume(n);
#ifdef PE2_PS5_HOST
        else if(PePadReadField(line,n)) {}
        else if(QolLoad(line,n)) {}
        else if(!strcmp(line,"player_shadow") && n>=0 && n<=2){Pe2ShadowSetMode(n!=0);Psyz_GpuSetShadowMode((int)n);}
        else if(!strcmp(line,"particle_lights") && n>=0 && n<=1)Pe2ParticleLightsSetMode((int)n);
        else if(!strcmp(line,"particle_geometry") && n>=0 && n<=2)Pe2ParticleGeometrySetMode((int)n);
        else if(!strcmp(line,"effect_precision") && n>=0 && n<=1)Psyz_VideoSetEffectGeometryCorrection((int)n);
        else if(!strcmp(line,"show_fps") && n>=0 && n<=1)PePresentationSetShowFps((int)n);
        else if(!strcmp(line,"frame_interpolation") && n>=0 && n<=1)Psyz_GpuSetFrameInterpolation((int)n);
        else if(!strcmp(line,"menu_style") && n>=0 && n<=1)OverlayAppearanceSetStyle((unsigned)n);
        else if(!strcmp(line,"menu_text_size") && n>=0 && n<=1)OverlayAppearanceSetTextSize((unsigned)n);
        else if(!strcmp(line,"menu_pointer") && n>=0 && n<=2)OverlayAppearanceSetPointer((unsigned)n);
        else if(!strcmp(line,"display_filter") && n>=0 && n<=2)Psyz_VideoSetDisplayFilter((int)n);
        else if(!strcmp(line,"fsr1") && n>=0 && n<=1)Psyz_VideoSetFsr1((int)n,Psyz_VideoGetFsr1Sharpness());
        else if(!strcmp(line,"fsr1_sharpness") && n>=0 && n<=2)Psyz_VideoSetFsr1(Psyz_VideoGetFsr1Requested(),(int)n);
        else if(!strcmp(line,"model_fill") && n>=0 && n<=2)Pe2ModelFillSetMode((int)n);
        else if(!strcmp(line,"movie_cleanup") && n>=0 && n<=3)Psyz_VideoSetMovieCleanup((int)n);
        else if(!strcmp(line,"movie_framing") && n>=0 && n<=1){Psyz_VideoSetMovieFraming((int)n);Psyz_VideoSetMovieBlur(n==0);}
        else if(!strcmp(line,"gameplay_fill") && n>=0 && n<=1)Psyz_VideoSetGameplayFill((int)n);
        else if(!strcmp(line,"hd_characters") && n>=0 && n<=1) pe_hd_preference=(int)n;
        else if(!strcmp(line,"hd_backgrounds") && n>=0 && n<=1) pe_hd_background_preference=(int)n;
        else if(!strcmp(line,"ui_font") && n>=0 && n<=1) legacy_font=(int)n;
        else if(!strcmp(line,"menu_font") && n>=0 && n<=3) menu_font=(int)n;
        else if(!strcmp(line,"dialogue_font") && n>=0 && n<=3) dialogue_font=(int)n;
        else if(!strcmp(line,"always_run") && n>=0 && n<=1) peAlwaysRunSet((int)n);
        else if(!strcmp(line,"analog_mode") && n>=0 && n<=1) peAnalogControlsSetMode((int)n);
        else if(!strcmp(line,"analog_run_threshold") && n>=50 && n<=100) peAnalogSetRunThreshold((unsigned)n);
#endif
        else if(!strncmp(line,"key",3)) {
            char* last; long index=strtol(line+3,&last,10);
            if(!*last && index>=0 && index<16 && n>=0 && n<SDL_SCANCODE_COUNT)
                Psyz_SetKeyboardBinding_SDL3(index,(SDL_Scancode)n);
        }
    }
    fclose(f);
#ifdef PE2_PS5_HOST
    PePadApplyLoaded();
    /* Explicit per-route values win regardless of file order. Old UI choice
     * applied to both routes; keep that behavior when migrating once. */
    if(menu_font>=0 || legacy_font>=0) Psyz_GpuSetFontStyle(PSYZ_FONT_MENU,(unsigned)(menu_font>=0?menu_font:legacy_font));
    if(dialogue_font>=0 || legacy_font>=0) Psyz_GpuSetFontStyle(PSYZ_FONT_DIALOGUE,(unsigned)(dialogue_font>=0?dialogue_font:legacy_font));
#endif
}

/* Raw BINs are presented to the SDK through a generated CUE in preferences.
 * The user's image is opened read-only and is never modified. */
/* Preserve the existing host absolute-form policy for BIN and CUE alike. */
static int discPathIsAbsolute(const char* path) {
    return path[0]=='/' || path[0]=='\\' || (path[0] && path[1]==':');
}
static int preparePath(const char* path,char out[4096]) {
    if(strlen(path)>=4096 || strpbrk(path,"\r\n\"")) return 0;
    const char* ext=strrchr(path,'.');
    if(ext && !SDL_strcasecmp(ext,".bin")) {
        int isAbsolute=discPathIsAbsolute(path);
        char* directory=isAbsolute?NULL:SDL_GetCurrentDirectory();
        char bin[4096];
        int length=isAbsolute?snprintf(bin,sizeof bin,"%s",path):
            snprintf(bin,sizeof bin,"%s%s",directory?directory:"",path);
        SDL_free(directory);
        if(length<0 || length>=(int)sizeof bin)return 0;
        /* Slot determined after validation; one temporary CUE per candidate. */
        snprintf(out,4096,"%s/selected-image.cue",configDir);
#ifdef PE2_PS5_HOST
        if(!pePs5WritePathAllowed(out))return 0;
#endif
        FILE* f=fopen(out,"w"); if(!f)return 0;
        fprintf(f,"FILE \"%s\" BINARY\n  TRACK 01 MODE2/2352\n    INDEX 01 00:00:00\n",bin);
        int failed=(ferror)(f); if(fclose(f))failed=1;
        return !failed;
    }
    if(discPathIsAbsolute(path))strcpy(out,path);
    else {
        char* directory=SDL_GetCurrentDirectory();
        int length=snprintf(out,4096,"%s%s",directory?directory:"",path);
        SDL_free(directory);if(length<0||length>=4096)return 0;
    }
    return 1;
}

static int acceptPath(const char* path,int expected) {
    char cue[4096]; if(!preparePath(path,cue))return 0;
    PeDisc* d=peDiscOpen(cue); int number=peDiscNumber(d); peDiscClose(d);
    if(!number || (expected && number!=expected)) {
        FILE* probe=fopen(path,"rb");
        if(!probe)snprintf(statusText,sizeof statusText,"Cannot open %s. Check the path and permissions.",path);
        else {
            fclose(probe);
            if(number)snprintf(statusText,sizeof statusText,"This is USA Disc %d, but Disc %d is needed here.",number,expected);
            else snprintf(statusText,sizeof statusText,"Not a supported USA Parasite Eve II image (keep the CUE next to its BIN, and use the North American release).");
        }
        return 0;
    }
    const char* ext=strrchr(path,'.');
    if(ext && !SDL_strcasecmp(ext,".bin")) {
        char stable[4096]; snprintf(stable,sizeof stable,"%s/disc%d.cue",configDir,number);
#ifdef PE2_PS5_HOST
        if(!pePs5WritePathAllowed(cue)||!pePs5WritePathAllowed(stable))return 0;
#endif
        if(rename(cue,stable))return 0;
        strcpy(cue,stable);
    }
    strcpy(discPaths[number-1],cue);
    snprintf(statusText,sizeof statusText,"USA Disc %d configured.",number);
    return number;
}

typedef struct { SDL_AtomicInt done; char* paths[2]; int failed; } DiscDialog;
static void SDLCALL discChosen(void* user,const char* const* files,int filter) {
    DiscDialog* d=user; (void)filter;
    if(!files)d->failed=1;
    else for(int i=0;files[i];i++) {
        if(i>=2) { d->failed=1; break; }
        d->paths[i]=SDL_strdup(files[i]); if(!d->paths[i])d->failed=1;
    }
    SDL_SetAtomicInt(&d->done,1);
}
static int chooseDiscs(SDL_Window* window,int expected) {
    const SDL_DialogFileFilter filters[]={{"Parasite Eve II USA disc images","cue;bin"}};
    DiscDialog d={0};
    Psyz_PauseHostClock_SDL3(true);
    SDL_ShowOpenFileDialog(discChosen,&d,window,filters,1,NULL,expected==0);
    while(!SDL_GetAtomicInt(&d.done)) { SDL_PumpEvents(); SDL_Delay(10); }
    int count=0;
    if(!d.failed)for(int i=0;i<2;i++) if(d.paths[i])count+=acceptPath(d.paths[i],expected)!=0;
    for(int i=0;i<2;i++)SDL_free(d.paths[i]);
    Psyz_PauseHostClock_SDL3(false);
    s_overlayState.dirty=1;
    return count;
}

static void rowText(int row,char label[128],char value[256]) {
    value[0]=0;
    if(s_overlayState.page==0) {
        const char* labels[]={"Picture detail","Aspect ratio","Dithering","Geometry correction","Fullscreen","Antialiasing","Model filtering","Smooth lighting"
#ifdef PE2_PS5_HOST
            ,"HD player textures","Menu font","HD backgrounds","Dialogue font",
            "Display filter","FSR1 spatial upscale","FSR1 sharpness","FSR1 status","Model fill lighting",
            "Movie cleanup","Movie framing","Fill the TV","Show display FPS","Smooth presentation",
            "Player shadow","Particle lights","Extra spark geometry","Presentation","Effect precision","Expanded backgrounds"
#endif
        };
        strcpy(label,labels[row]);
        if(row==0)snprintf(value,256,"%ux",Psyz_VideoGetInternalResolution());
        if(row==1)strcpy(value,Psyz_VideoGetAspectMode()?"Square pixels":"Classic 4:3");
        if(row==2)strcpy(value,Psyz_VideoGetDitheringMode()?"Off":"Original");
        if(row==3)strcpy(value,
#ifdef PE2_PS5_HOST
            "On (required)"
#else
            Psyz_VideoGetGeometryCorrection()?"On":"Off"
#endif
        );
        if(row==4)strcpy(value,(s_overlayGpuWindow && SDL_GetWindowFlags(s_overlayGpuWindow)&SDL_WINDOW_FULLSCREEN)?"On":"Off");
        if(row==5)strcpy(value,Psyz_VideoGetAntialiasing()?"On":"Off");
        if(row==6)strcpy(value,Psyz_VideoGetModelFiltering()?"On":"Off");
        if(row==7)strcpy(value,Psyz_VideoGetDynamicLighting()?"On":"Off");
#ifdef PE2_PS5_HOST
        if(row==8)strcpy(value,PeHdExplicitRoot()?"On (override)":PeHdRequested()?"On":"Off");
        if(row==9 || row==11) {
            static const char *const names[]={"Original","Plex","Retro","Atkinson"};
            unsigned style=Psyz_GpuGetFontStyle(row==9?PSYZ_FONT_MENU:PSYZ_FONT_DIALOGUE);
            snprintf(value,256,"%s%s",names[style],style && Psyz_VideoGetInternalResolution()==1?" (needs >1x)":"");
        }
        if(row==10)strcpy(value,!pe_hd_background_preference?"Off":Psyz_GpuGetHdBackgrounds()?"On":"On (unavailable)");
        if(row==12){static const char *names[]={"Off","Scanlines","CRT"};int n=Psyz_VideoGetDisplayFilter();strcpy(value,names[n>=0&&n<3?n:0]);}
        if(row==13)strcpy(value,Psyz_VideoGetFsr1Requested()?"On":"Off");
        if(row==14){static const char *names[]={"Strong","Balanced","Soft"};int n=Psyz_VideoGetFsr1Sharpness();strcpy(value,names[n>=0&&n<3?n:1]);}
        if(row==15){static const char *names[]={"Off","Original fallback","EASU + RCAS queued","Original (unavailable)"};int n=Psyz_VideoGetFsr1Status();strcpy(value,names[n>=0&&n<4?n:1]);}
        if(row==16){static const char *names[]={"Off","Neutral","World key"};int n=Pe2ModelFillGetMode();strcpy(value,names[n>=0&&n<3?n:0]);}
        if(row==17){static const char *names[]={"Original","Gentle","Stronger","Block smoothing"};int n=Psyz_VideoGetMovieCleanup();strcpy(value,names[n>=0&&n<4?n:0]);}
        if(row==18)strcpy(value,Psyz_VideoGetMovieFraming()?"Fill screen":"Original + blurred sides");
        if(row==19)strcpy(value,Psyz_VideoGetGameplayFill()?"On":"Off");
        if(row==20)strcpy(value,PePresentationShowFps()?"On":"Off");
        if(row==21)strcpy(value,Psyz_GpuGetFrameInterpolation()?"Requested":"Original");
        if(row==22){static const char *names[]={"Original","Strict outline","Experimental silhouette"};int n=Psyz_GpuGetShadowMode();strcpy(value,names[n>=0&&n<3?n:0]);}
        if(row==23)strcpy(value,Pe2ParticleLightsGetMode()?"On":"Off");
        if(row==24){static const char *names[]={"Original","Hybrid","New geometry"};int n=Pe2ParticleGeometryGetMode();strcpy(value,names[n>=0&&n<3?n:0]);}
        if(row==25)strcpy(value,PeVisualPresentationName());
        if(row==27)snprintf(value,256,"%s",Psyz_GpuWideBackgroundStatus());
        if(row==26)strcpy(value,Psyz_VideoGetEffectGeometryCorrection()?"On":"Off");
#endif
    } else if(s_overlayState.page==2) {
        strcpy(label,"Master volume");snprintf(value,256,"%u%%",Psyz_AudioGetOutputVolume());
    } else if(s_overlayState.page==1) {
#ifdef PE2_PS5_HOST
        if(row==16) { strcpy(label,"Left stick movement"); strcpy(value,peAnalogControlsMode()?"Direct":"Original tank"); return; }
        if(row==17) { strcpy(label,"Stick run threshold"); snprintf(value,256,"%u%%",peAnalogRunThreshold()); return; }
        if(row>=24&&row<40) { unsigned bit=(unsigned)(row-24);snprintf(label,128,"Controller %s",PePadBitName(bit));
            snprintf(value,256,"%s%s",s_overlayState.capture&&row==s_overlayState.row?"Press button / trigger...":PePadBindingName(Psyz_GetGamepadBinding_SDL3(bit)),PePadLocked(bit)?" (reserved)":"");return; }
        if(row==23) {strcpy(label,"Always run");strcpy(value,peAlwaysRun()?"On":"Off");return;}
        if(row==40) {strcpy(label,"Restore controller defaults");strcpy(value,"Choose...");return;}
        if(row==18) { strcpy(label,"Hold speed: keyboard");snprintf(value,256,"%s",s_overlayState.capture?"Press key / Del clears":qolKey<0?"Unbound":SDL_GetScancodeName((SDL_Scancode)qolKey));return; }
        if(row==19) { strcpy(label,"Hold speed: controller");snprintf(value,256,"%s",s_overlayState.capture?"Press button / Del clears":qolButton<0?"Unbound":SDL_GetGamepadStringForButton((SDL_GamepadButton)qolButton));return; }
        if(row==20) { strcpy(label,"Held speed factor");snprintf(value,256,"%dx",qolFactor);return; }
        if(row>=21) { strcpy(label,row==21?"Skip current scene":"Pause / Resume");strcpy(value,"Choose...");return; }

#endif
#ifdef PE2_PS5_HOST
        strcpy(label,PePadBitName((unsigned)row));
#else
        strcpy(label,buttons[row]);
#endif
        snprintf(value,256,"%s",s_overlayState.capture && row==s_overlayState.row?"Press a key...":
            SDL_GetScancodeName(Psyz_GetKeyboardBinding_SDL3(row)));
    }
#ifdef PE2_PS5_HOST
    else if(s_overlayState.page==HOST_PAGE_PAUSE){
        static const char *const labels[PAUSE_ROW_COUNT]={
            [PAUSE_RESUME]="Resume",
            [PAUSE_RETURN_TITLE]="Return to Title",
            [PAUSE_EXIT_GAME]="Exit Game",
        };
        strcpy(label,labels[row]);
        strcpy(value,requiredDisc && row!=PAUSE_RESUME?"Unavailable":"Choose...");
    }
    else if(s_overlayState.page==5){
        PeModRow(row,label,value);
    }
    else if(s_overlayState.page==4){
        if(row>=3){PeSystemRow(row,label,value);return;}
        static const char *labels[]={"Menu appearance","Menu text","Focus pointer"};
        strcpy(label,labels[row]);
        strcpy(value,row==0?OverlayAppearanceStyleName():row==1?OverlayAppearanceTextName():OverlayAppearancePointerName());
    }
#endif
    else {
        snprintf(label,128,"Disc %d",row+1);
        const char* p=strrchr(discPaths[row],'/'); p=p?p+1:discPaths[row];
        snprintf(value,256,"%.40s",*p?p:"Choose image...");
    }
}

static void paintPanel(OverlaySurface* surface,OverlayLayout* layout) {
    memset(surface->pixels,0,(size_t)surface->w*surface->h*4);
    float s=layout->scale;
#ifdef PE2_PS5_HOST
    if(qolConfirm) {QolPaintConfirm(surface,s);return;}
#endif
#ifdef PE2_PS5_HOST
    OverlayAppearancePaintPanel(surface,s);
#else
    FillRoundRect(surface,0,0,680*s,(surface->h-1),16*s,kPanel);
#endif
    DrawText(surface,32*s,42*s,24*s,"PARASITE EVE 2",kText,ALIGN_LEFT);
    DrawText(surface,648*s,42*s,14*s,"0.1 alpha / development",kMuted,ALIGN_RIGHT);
    for(int i=0;i<HOST_PAGE_COUNT;i++)DrawText(surface,(32+i*(644.f/HOST_PAGE_COUNT))*s,87*s,17*s,pages[i],
#ifdef PE2_PS5_HOST
        s_overlayState.page==i?OverlayAppearanceAccent():kMuted,ALIGN_LEFT);
#else
        s_overlayState.page==i?kAccent:kMuted,ALIGN_LEFT);
#endif
    ensureRowVisible();
    int first=s_overlayState.scroll;
    int rows=VISIBLE_ROWS;
    int shown=rowCount()<VISIBLE_ROWS?rowCount():VISIBLE_ROWS;
    for(int i=0;i<shown;i++) {
        int row=first+i; char label[128],value[256];rowText(row,label,value);
        float y=(128+i*46)*s;
#ifdef PE2_PS5_HOST
        if(row==s_overlayState.row)OverlayAppearancePaintFocus(surface,y,s);
        OverlayAppearancePaintRow(surface,y,s,label,value,row==s_overlayState.row);
#else
        if(row==s_overlayState.row)FillRoundRect(surface,20*s,y-27*s,640*s,40*s,7*s,
            (Color){0.27f,0.62f,1,0.16f});
        DrawText(surface,32*s,y,17*s,label,kText,ALIGN_LEFT);
        DrawText(surface,648*s,y,16*s,value,row==s_overlayState.row?kAccent:kMuted,ALIGN_RIGHT);
#endif
    }
    if(maxScroll()>0) {   /* scrollbar of a page with more rows than fit */
        float trackTop=(101+4)*s,trackH=(VISIBLE_ROWS*46-8)*s,thumbH=trackH*VISIBLE_ROWS/rowCount();
        float thumbTop=trackTop+(trackH-thumbH)*s_overlayState.scroll/maxScroll();
        FillRoundRect(surface,668*s,trackTop,4*s,trackH,2*s,(Color){0.93f,0.95f,0.98f,0.10f});
        Color thumb=kAccent;
#ifdef PE2_PS5_HOST
        thumb=OverlayAppearanceAccent();
#endif
        thumb.a=.65f;
        FillRoundRect(surface,668*s,thumbTop,4*s,thumbH,2*s,thumb);
    }
    float y=(128+rows*46+16)*s;
    const char *detail=statusText;
#ifdef PE2_PS5_HOST
    if(s_overlayState.page==4 && s_overlayState.row<3)detail=s_overlayState.row==0?"Changes native Settings appearance only.":s_overlayState.row==1?"Settings text size; game fonts are independent.":"Changes the selection indicator only.";
    if(s_overlayState.page==0 && s_overlayState.row==8)detail=PeHdStatus();
    if(s_overlayState.page==0 && s_overlayState.row==10)detail=PeHdBackgroundStatus();
    if(s_overlayState.page==0 && s_overlayState.row==12)detail=Psyz_VideoDisplayFilterStatus();
    if(s_overlayState.page==0 && (s_overlayState.row==13||s_overlayState.row==15))detail=Psyz_VideoGetFsr1Reason();
    if(s_overlayState.page==0 && s_overlayState.row==14)detail="FSR1 sharpening strength; lower stops sharpen more.";
    if(s_overlayState.page==0 && s_overlayState.row==16)detail=Pe2ModelFillGetReason();
    if(s_overlayState.page==0 && s_overlayState.row==17)detail=Psyz_VideoMovieCleanupStatus();
    if(s_overlayState.page==0 && s_overlayState.row==18)detail="Movie framing is separate from gameplay. Original keeps 4:3 proportions.";
    if(s_overlayState.page==0 && s_overlayState.row==19)detail="Stretches gameplay to the TV; movie framing stays independent.";
    if(s_overlayState.page==0 && s_overlayState.row==20)detail="Accepted TV submissions; game logic updates are not counted.";
    if(s_overlayState.page==0 && s_overlayState.row==21)detail="Supported model presentation only; game timing stays original. Failures keep original.";
    if(s_overlayState.page==0 && s_overlayState.row==22)detail=Pe2ShadowGetStatus()==2?Psyz_GpuShadowStatus():Pe2ShadowGetReason();
    if(s_overlayState.page==0 && s_overlayState.row==23)detail=Pe2ParticleLightsGetReason();
    if(s_overlayState.page==0 && s_overlayState.row==24)detail=Pe2ParticleGeometryGetReason();
    if(s_overlayState.page==5)detail=PeModHelp(s_overlayState.row);
    if(s_overlayState.page==0 && s_overlayState.row==25)detail=PeVisualStatus();
    if(s_overlayState.page==0 && s_overlayState.row==27)detail="Needs exact compatible expanded-room art; unsupported rooms keep original proportions.";
    if(s_overlayState.page==0 && s_overlayState.row==26)detail="Subpixel precision for supported effects; gameplay timing stays original.";
    if(s_overlayState.page==0 && (s_overlayState.row==9 || s_overlayState.row==11))detail="Original spacing; unsupported text keeps the original font. Needs 2x or above.";
#endif
#ifdef PE2_PS5_HOST
    if(s_overlayState.page==1 && s_overlayState.row==16)detail="Direct stick direction; D-pad keeps original tank controls.";
    if(s_overlayState.page==1 && s_overlayState.row==17)detail="Stick strength selects walking or running. Default: 85%.";
    if(s_overlayState.page==1 && s_overlayState.row==18)detail="Enter: bind keyboard hold. Delete: unbind. Esc is reserved for Settings.";
    if(s_overlayState.page==1 && s_overlayState.row==19)detail="Enter: bind controller hold. Delete/West: unbind. Start/sticks reserved.";
    if(s_overlayState.page==1 && s_overlayState.row==20)detail="Hold the bound control for 2x-4x speed; release restores 1x. Audio speeds up.";
    if(s_overlayState.page==1 && s_overlayState.row==21)detail="Uses the current original scene's skip script when allowed; some scenes cannot skip.";
    if(s_overlayState.page==1 && s_overlayState.row==22)detail="Requests pause or resume at a safe gameplay point; loading and movies block it.";
    if(s_overlayState.page==HOST_PAGE_PAUSE) {
        detail=s_overlayState.row==PAUSE_RESUME?"Close the pause menu.":requiredDisc?
            "Finish or cancel the disc prompt first.":"Confirmation required. Unsaved progress will be lost.";
    }
    if(s_overlayState.page==1&&s_overlayState.row>=24&&s_overlayState.row<40)detail=PePadLocked((unsigned)(s_overlayState.row-24))?"Reserved: Start and L3/R3 keep Settings reachable.":"Enter/South: bind button or trigger. Delete/West: unbind. Esc/Start cancels capture.";
    if(s_overlayState.page==1&&s_overlayState.row==23)detail="Normal movement only. Hold the original run button to walk; game restrictions still apply.";
    if(s_overlayState.page==1&&s_overlayState.row==40)detail="Restore original gamepad buttons only. Keyboard, sticks and speed hold stay unchanged.";

#endif
#ifdef PE2_PS5_HOST
    if(preferenceSaveFailed) detail="Settings could not be saved. See startup log for the path and error.";
    if(!preferenceSaveFailed && s_overlayState.page==4 && s_overlayState.row>=3)PeSystemPaintDetail(surface,y,s,s_overlayState.row);
    else {
#endif
    DrawText(surface,32*s,y,14*s,detail,kMuted,ALIGN_LEFT);
    DrawText(surface,32*s,y+27*s,13*s,"Tab / shoulders: page   Arrows: select / change   Enter: choose",kMuted,ALIGN_LEFT);
#ifdef PE2_PS5_HOST
    }
#endif
    DrawText(surface,32*s,y+48*s,13*s,requiredDisc?"Select the requested disc; Esc cancels.":"Esc / controller Start: resume   Controls: Enter to bind a key",kMuted,ALIGN_LEFT);
    surface->pixels[((size_t)surface->h*surface->w-1)*4+3]=255;
}

static int refreshPanel(SDL_Window* window) {
    int w,h; SDL_GetWindowSizeInPixels(window,&w,&h);if(w<=0||h<=0||!OverlayFontReady())return 0;
    OverlayLayout layout;OverlayFitLayout(680,OverlayDesignHeight(VISIBLE_ROWS),w,h,&layout);
    s_overlayWindowW=w;s_overlayWindowH=h;s_overlayLayout=layout;
    if(!OverlaySurfaceResize(&s_overlaySurface,layout.w,layout.h))return 0;
    paintPanel(&s_overlaySurface,&layout);
    if(getenv("PE2_DUMP_MENU")) {   /* development: the painted panel as a PPM (RGB over black), for a capture-free review */
#ifdef PE2_PS5_HOST
        FILE* f=pePs5WritePathAllowed(getenv("PE2_DUMP_MENU"))?fopen(getenv("PE2_DUMP_MENU"),"wb"):NULL;
#else
        FILE* f=fopen(getenv("PE2_DUMP_MENU"),"wb");
#endif
        if(f) {
            fprintf(f,"P6\n%d %d\n255\n",s_overlaySurface.w,s_overlaySurface.h);
            for(size_t i=0;i<(size_t)s_overlaySurface.w*s_overlaySurface.h;i++) {
                const unsigned char* px=&s_overlaySurface.pixels[i*4];
                for(int c=0;c<3;c++)fputc(px[c]*px[3]/255,f);
            }
            fclose(f);
        }
    }
    return 1;
}

static void changeRow(int direction,int activate) {
    int r=s_overlayState.row;
    if(s_overlayState.page==0) {
        if(r==0) { int n=(int)Psyz_VideoGetInternalResolution()+direction;
            if(n>=1&&n<=8) {
                int result=Psyz_VideoSetInternalResolution(n);
                SDL_Log("PE2 resolution requested=%d result=%d applied=%u",n,result,Psyz_VideoGetInternalResolution());
            } }
        if(r==1)Psyz_VideoSetAspectMode(!Psyz_VideoGetAspectMode());
        if(r==2)Psyz_VideoSetDitheringMode(!Psyz_VideoGetDitheringMode());
        if(r==3)Psyz_VideoSetGeometryCorrection(
#ifdef PE2_PS5_HOST
            1
#else
            !Psyz_VideoGetGeometryCorrection()
#endif
        );
        if(r==4 && s_overlayGpuWindow)SDL_SetWindowFullscreen(s_overlayGpuWindow,
            !(SDL_GetWindowFlags(s_overlayGpuWindow)&SDL_WINDOW_FULLSCREEN));
        if(r==5)Psyz_VideoSetAntialiasing(!Psyz_VideoGetAntialiasing());
        if(r==6)Psyz_VideoSetModelFiltering(!Psyz_VideoGetModelFiltering());
        if(r==7)Psyz_VideoSetDynamicLighting(!Psyz_VideoGetDynamicLighting());
#ifdef PE2_PS5_HOST
        if(r==8)PeHdTogglePreference();
        if(r==9 || r==11) {
            unsigned context=r==9?PSYZ_FONT_MENU:PSYZ_FONT_DIALOGUE;
            Psyz_GpuSetFontStyle(context,(Psyz_GpuGetFontStyle(context)+(direction<0?3:1))%4);
        }
        if(r==10)PeHdToggleBackgroundPreference();
        if(r==12)Psyz_VideoSetDisplayFilter((Psyz_VideoGetDisplayFilter()+3+direction)%3);
        if(r==13)Psyz_VideoSetFsr1(!Psyz_VideoGetFsr1Requested(),Psyz_VideoGetFsr1Sharpness());
        if(r==14)Psyz_VideoSetFsr1(Psyz_VideoGetFsr1Requested(),(Psyz_VideoGetFsr1Sharpness()+3+direction)%3);
        if(r==16)Pe2ModelFillSetMode((Pe2ModelFillGetMode()+3+direction)%3);
        if(r==17)Psyz_VideoSetMovieCleanup((Psyz_VideoGetMovieCleanup()+4+direction)%4);
        if(r==18){int n=!Psyz_VideoGetMovieFraming();Psyz_VideoSetMovieFraming(n);Psyz_VideoSetMovieBlur(!n);}
        if(r==19)Psyz_VideoSetGameplayFill(!Psyz_VideoGetGameplayFill());
        if(r==20)PePresentationSetShowFps(!PePresentationShowFps());
        if(r==21)Psyz_GpuSetFrameInterpolation(!Psyz_GpuGetFrameInterpolation());
        if(r==22){int n=(Psyz_GpuGetShadowMode()+3+direction)%3;Pe2ShadowSetMode(n!=0);Psyz_GpuSetShadowMode(n);}
        if(r==23)Pe2ParticleLightsSetMode(!Pe2ParticleLightsGetMode());
        if(r==24)Pe2ParticleGeometrySetMode((Pe2ParticleGeometryGetMode()+3+direction)%3);
        if(r==25)PeVisualSetPresentation(!PeVisualGetPresentation());
        if(r==27)PeWideSetRequested(!Psyz_VideoGetWidescreen());
        if(r==26)Psyz_VideoSetEffectGeometryCorrection(!Psyz_VideoGetEffectGeometryCorrection());
#endif
    } else if(s_overlayState.page==2) {
        int n=(int)Psyz_AudioGetOutputVolume()+direction*5;
        Psyz_AudioSetOutputVolume(n<0?0:n>100?100:n);
    } else if(s_overlayState.page==1) {
#ifdef PE2_PS5_HOST
        if(r==23)peAlwaysRunSet(!peAlwaysRun());
        else if(r>=24)PePadActivate(r,activate);
        else if(r==18||r==19) { if(activate){QolClearHold();s_overlayState.capture=1;} }
        else if(r==20) {qolFactor+=direction;qolFactor=qolFactor<2?2:qolFactor>4?4:qolFactor;QolClearHold();}
        else if(r>=21) {
            if(activate&&!requiredDisc) {
                qolPendingAction=r==21?PE_QOL_SKIP:PE_QOL_PAUSE_TOGGLE;
                s_overlayState.open=0;
            }
        }
        else if(r==16)peAnalogControlsSetMode(!peAnalogControlsMode());
        else if(r==17) { int threshold=(int)peAnalogRunThreshold()+direction*5;
            peAnalogSetRunThreshold((unsigned)(threshold<50?50:threshold>100?100:threshold)); }
        else
#endif
        if(activate)s_overlayState.capture=1;
    }
#ifdef PE2_PS5_HOST
    else if(s_overlayState.page==HOST_PAGE_PAUSE){
        if(!activate)return;
        if(r==PAUSE_RESUME) {
            s_overlayState.open=0;
        } else if(!requiredDisc) {
            qolConfirm=r==PAUSE_RETURN_TITLE?PE_QOL_RETURN_TITLE_CONFIRMED:PE_QOL_EXIT_GAME_CONFIRMED;
            qolYes=0;
        }
    }
    else if(s_overlayState.page==5){
        PeModChange(r,activate);
    }
    else if(s_overlayState.page==4){
        if(r>=3){PeSystemPageDetail(r,direction);s_overlayState.dirty=1;return;}
        if(r==0)OverlayAppearanceSetStyle((OverlayAppearanceGetStyle()+2+direction)%2);
        if(r==1)OverlayAppearanceSetTextSize((OverlayAppearanceGetTextSize()+2+direction)%2);
        if(r==2)OverlayAppearanceSetPointer((OverlayAppearanceGetPointer()+3+direction)%3);
    }
#endif
    else if(s_overlayState.page==3 && activate) {
        if(chooseDiscs(s_overlayGpuWindow,r+1) && requiredDisc==r+1) {
            selectedDisc=requiredDisc;s_overlayState.open=0;
        }
    }
    s_overlayState.dirty=1;
}

static void processEvent(const SDL_Event* e) {
    if(e->type==SDL_EVENT_QUIT) { s_overlayState.open=0;s_overlayState.quit=1;return; }
    int key=0;
#ifdef PE2_PS5_HOST
    QolSpeedEvent(e,1);
    if(PePadControlEvent(e))return;
    if(qolConfirm) {
        int confirm=0,cancel=0;
        if(e->type==SDL_EVENT_KEY_DOWN&&!e->key.repeat) {
            if(e->key.scancode==SDL_SCANCODE_LEFT||e->key.scancode==SDL_SCANCODE_RIGHT)qolYes=!qolYes;
            confirm=e->key.scancode==SDL_SCANCODE_RETURN;
            cancel=e->key.scancode==SDL_SCANCODE_ESCAPE;
        } else if(e->type==SDL_EVENT_GAMEPAD_BUTTON_DOWN) {
            if(e->gbutton.button==SDL_GAMEPAD_BUTTON_DPAD_LEFT||e->gbutton.button==SDL_GAMEPAD_BUTTON_DPAD_RIGHT)qolYes=!qolYes;
            confirm=e->gbutton.button==SDL_GAMEPAD_BUTTON_SOUTH;
            cancel=e->gbutton.button==SDL_GAMEPAD_BUTTON_EAST||e->gbutton.button==SDL_GAMEPAD_BUTTON_START;
        } else if(e->type==SDL_EVENT_MOUSE_BUTTON_DOWN&&e->button.button==SDL_BUTTON_LEFT&&uiWindow) {
            int w,h;SDL_GetWindowSize(uiWindow,&w,&h);
            float x=(e->button.x*s_overlayWindowW/w-s_overlayLayout.x)/s_overlayLayout.scale;
            float y=(e->button.y*s_overlayWindowH/h-s_overlayLayout.y)/s_overlayLayout.scale;
            if(y>=180&&y<=245&&x>=80&&x<=600){qolYes=x>=340;confirm=1;}
        }
        if(cancel||confirm) {
            if(confirm&&qolYes){qolPendingAction=qolConfirm;s_overlayState.open=0;}
            qolConfirm=0;
        }
        s_overlayState.dirty=1;return;
    }
    if(s_overlayState.page==1&&(s_overlayState.row==18||s_overlayState.row==19)) {
        if(e->type==SDL_EVENT_KEY_DOWN&&!e->key.repeat) {
            int k=e->key.scancode;
            if(k==SDL_SCANCODE_DELETE||k==SDL_SCANCODE_BACKSPACE) {
                if(s_overlayState.row==18)qolKey=-1;else qolButton=-1;
                QolClearHold();s_overlayState.capture=0;s_overlayState.dirty=1;return;
            }
            if(s_overlayState.capture) {
                if(k==SDL_SCANCODE_ESCAPE)s_overlayState.capture=0;
                else if(s_overlayState.row==18&&!QolReservedKey(k)){qolKey=k;s_overlayState.capture=0;QolClearHold();}
                s_overlayState.dirty=1;return;
            }
        }
        if(e->type==SDL_EVENT_GAMEPAD_BUTTON_DOWN) {
            int button=e->gbutton.button;
            if(!s_overlayState.capture&&button==SDL_GAMEPAD_BUTTON_WEST) {
                if(s_overlayState.row==18)qolKey=-1;else qolButton=-1;
                QolClearHold();s_overlayState.dirty=1;return;
            }
            if(s_overlayState.capture) {
                if(button==SDL_GAMEPAD_BUTTON_START)s_overlayState.capture=0;
                else if(s_overlayState.row==19&&!QolReservedButton(button)){qolButton=button;s_overlayState.capture=0;QolClearHold();}
                s_overlayState.dirty=1;return;
            }
        }
    }
#endif

    if(e->type==SDL_EVENT_MOUSE_BUTTON_DOWN && e->button.button==SDL_BUTTON_LEFT && uiWindow) {
        int w,h;SDL_GetWindowSize(uiWindow,&w,&h);
        float x=(e->button.x*s_overlayWindowW/w-s_overlayLayout.x)/s_overlayLayout.scale;
        float y=(e->button.y*s_overlayWindowH/h-s_overlayLayout.y)/s_overlayLayout.scale;
        if(y>=60 && y<=100 && x>=20 && x<664) {
            setPage((int)((x-20)/(644.f/HOST_PAGE_COUNT)));
        } else if(y>=101 && x>=20 && x<=660) {
            int first=s_overlayState.scroll;
            int row=first+(int)((y-101)/46);
            if(row<rowCount() && row<first+VISIBLE_ROWS) {
                s_overlayState.row=row;changeRow(x<500?-1:1,1);
            }
        }
        s_overlayState.dirty=1;return;
    }
    if(e->type==SDL_EVENT_MOUSE_WHEEL) {
        int n=s_overlayState.scroll-(int)(e->wheel.y>0?1:e->wheel.y<0?-1:0);
        s_overlayState.scroll=n<0?0:n>maxScroll()?maxScroll():n;
        s_overlayState.dirty=1;return;
    }
    if(e->type==SDL_EVENT_KEY_DOWN) {
        if(e->key.repeat)return;
        if(s_overlayState.capture) {
#ifdef PE2_PS5_HOST
            QolClearHold();
#endif
            if(e->key.scancode!=SDL_SCANCODE_ESCAPE)
                Psyz_SetKeyboardBinding_SDL3(s_overlayState.row,e->key.scancode);
            s_overlayState.capture=0;s_overlayState.dirty=1;return;
        }
        key=e->key.scancode;
    } else if(e->type==SDL_EVENT_GAMEPAD_BUTTON_DOWN) {
        switch(e->gbutton.button) {
        case SDL_GAMEPAD_BUTTON_DPAD_UP:key=SDL_SCANCODE_UP;break;
        case SDL_GAMEPAD_BUTTON_DPAD_DOWN:key=SDL_SCANCODE_DOWN;break;
        case SDL_GAMEPAD_BUTTON_DPAD_LEFT:key=SDL_SCANCODE_LEFT;break;
        case SDL_GAMEPAD_BUTTON_DPAD_RIGHT:key=SDL_SCANCODE_RIGHT;break;
        case SDL_GAMEPAD_BUTTON_SOUTH:key=SDL_SCANCODE_RETURN;break;
        case SDL_GAMEPAD_BUTTON_EAST:case SDL_GAMEPAD_BUTTON_START:key=SDL_SCANCODE_ESCAPE;break;
        case SDL_GAMEPAD_BUTTON_RIGHT_SHOULDER:key=SDL_SCANCODE_TAB;break;
        case SDL_GAMEPAD_BUTTON_LEFT_SHOULDER:
            setPage((s_overlayState.page+HOST_PAGE_COUNT-1)%HOST_PAGE_COUNT);break;
        default:break;
        }
    }
    if(key==SDL_SCANCODE_ESCAPE)s_overlayState.open=0;
    if(key==SDL_SCANCODE_TAB)setPage((s_overlayState.page+1)%HOST_PAGE_COUNT);
    if(key==SDL_SCANCODE_UP)s_overlayState.row=(s_overlayState.row+rowCount()-1)%rowCount();
    if(key==SDL_SCANCODE_DOWN)s_overlayState.row=(s_overlayState.row+1)%rowCount();
    ensureRowVisible();
    if(key==SDL_SCANCODE_LEFT)changeRow(-1,0);
    if(key==SDL_SCANCODE_RIGHT)changeRow(1,0);
    if(key==SDL_SCANCODE_RETURN)changeRow(1,1);
    s_overlayState.dirty=1;
}

static void settings(void) {
#ifdef PE2_PS5_HOST
    PePresentationStatsMenuBegin();
    peInterpSetHostBlocked(1);
#endif
    int wasPaused=Psyz_AudioIsPaused();
#ifdef PE2_PS5_HOST
    Psyz_ResetGamepadHeld_SDL3();
#endif
#ifdef PE2_PS5_HOST
    peQolSetUiBlocked(1);QolClearHold();qolPendingAction=0;qolConfirm=0;qolYes=0;
#endif
    Psyz_PauseHostClock_SDL3(true);Psyz_AudioPause();
    s_overlayState.open=1;s_overlayState.quit=0;
    if(getenv("PE2_MENU_PAGE")) setPage(atoi(getenv("PE2_MENU_PAGE"))&3);   /* development: open on this page */
    SDL_Window* fallback=NULL;SDL_Renderer* renderer=NULL;SDL_Texture* texture=NULL;
    if(!s_overlayGpuDevice) {
        fallback=SDL_CreateWindow("Parasite Eve 2 - Settings",900,720,SDL_WINDOW_HIGH_PIXEL_DENSITY|SDL_WINDOW_RESIZABLE);
        if(fallback)renderer=SDL_CreateRenderer(fallback,NULL);
        if(!renderer) { s_overlayState.open=0; goto done; }
    }
    while(s_overlayState.open) {
        SDL_Window* window=fallback?fallback:s_overlayGpuWindow;
        uiWindow=window;
        if(!window || !refreshPanel(window)) { s_overlayState.open=0; break; }
        if(fallback) {
            SDL_DestroyTexture(texture);
            texture=SDL_CreateTexture(renderer,SDL_PIXELFORMAT_RGBA32,SDL_TEXTUREACCESS_STREAMING,s_overlaySurface.w,s_overlaySurface.h);
            if(!texture)break;
            SDL_UpdateTexture(texture,NULL,s_overlaySurface.pixels,s_overlaySurface.w*4);
            SDL_SetRenderDrawColor(renderer,13,17,23,255);SDL_RenderClear(renderer);
            SDL_FRect rect={s_overlayLayout.x,s_overlayLayout.y,s_overlayLayout.w,s_overlayLayout.h};
            SDL_RenderTexture(renderer,texture,NULL,&rect);SDL_RenderPresent(renderer);
            SDL_Event e; if(SDL_WaitEventTimeout(&e,16))processEvent(&e);
        } else {
            if(!Host_EnsureOverlayPipeline(s_overlayGpuDevice,SDL_GetGPUSwapchainTextureFormat(s_overlayGpuDevice,window)) ||
               !Host_UploadOverlaySurfaceAndVertices(s_overlayGpuDevice)) {
                s_overlayState.open=0;break;
            }
            Psyz_VideoVSync(0);
        }
    }
    SDL_DestroyTexture(texture);SDL_DestroyRenderer(renderer);SDL_DestroyWindow(fallback);
    saveOptions();
done:
    uiWindow=NULL;s_overlayState.open=0;SDL_ResetKeyboard();Psyz_PauseHostClock_SDL3(false);
    if(!wasPaused)Psyz_AudioUnpause();
#ifdef PE2_PS5_HOST
    peInterpSetHostBlocked(pe_host_focus_blocked);
#endif
#ifdef PE2_PS5_HOST
    QolClearHold();Psyz_ResetGamepadHeld_SDL3();s_overlayState.capture=0;qolConfirm=0;
    peQolSetUiBlocked(0);
    if(!s_overlayState.quit&&qolPendingAction)peQolRequest(qolPendingAction);
    qolPendingAction=0;
#endif
    if(s_overlayState.quit) { SDL_Event e={.type=SDL_EVENT_QUIT};SDL_PushEvent(&e); }
}

static bool settingsEvent(const SDL_Event* e) {
#ifdef PE2_PS5_HOST
    PePadLifecycleEvent(e);
#endif
#ifdef PE2_PS5_HOST
    if(e->type==SDL_EVENT_WINDOW_FOCUS_LOST||e->type==SDL_EVENT_WINDOW_FOCUS_GAINED){
        pe_host_focus_blocked=e->type==SDL_EVENT_WINDOW_FOCUS_LOST;
        peInterpSetHostBlocked(1);
        peInterpSetHostBlocked(pe_host_focus_blocked||s_overlayState.open);
    }
    if(e->type==SDL_EVENT_GAMEPAD_REMOVED){
        peInterpSetHostBlocked(1);
        peInterpSetHostBlocked(pe_host_focus_blocked||s_overlayState.open);
    }
#endif
    if(s_overlayState.open) {processEvent(e);
#ifdef PE2_PS5_HOST
        /* Lifecycle events must still reach the real controller provider. */
        if(e->type==SDL_EVENT_GAMEPAD_ADDED||e->type==SDL_EVENT_GAMEPAD_REMOVED)return false;
#endif
        return true;}
    int open=e->type==SDL_EVENT_KEY_DOWN && e->key.scancode==SDL_SCANCODE_ESCAPE && !e->key.repeat;
    if(e->type==SDL_EVENT_GAMEPAD_BUTTON_DOWN &&
       (e->gbutton.button==SDL_GAMEPAD_BUTTON_LEFT_STICK||e->gbutton.button==SDL_GAMEPAD_BUTTON_RIGHT_STICK)) {
        SDL_Gamepad* pad=SDL_GetGamepadFromID(e->gbutton.which);
        open=pad && SDL_GetGamepadButton(pad,SDL_GAMEPAD_BUTTON_LEFT_STICK) && SDL_GetGamepadButton(pad,SDL_GAMEPAD_BUTTON_RIGHT_STICK);
    }
    if(open) {
#ifdef PE2_PS5_HOST
        setPage(HOST_PAGE_PAUSE);
#endif
        settings();
        return true;
    }
#ifdef PE2_PS5_HOST
    if(QolSpeedEvent(e,0))return true;
#endif
    return previousFilter?previousFilter(e):false;
}

int peHostStartup(int argc,char** argv,const char** disc) {
#ifdef PE2_PS5_HOST
    PeVisualBeginLoad();
    PeModBeginLoad();
#endif
    loadOptions();
#ifdef PE2_PS5_HOST
    PeModLoaded();
    PeVisualLoaded();
#endif
#ifdef PE2_PS5_HOST
    if(!*configPath) {
        extern void pe_application_stage(const char*);
        pe_application_stage("PE2 preferences setup failed: ");
        pe_application_stage(pePs5StorageReason());
        pe_application_stage("\n");
        if(statusText[0]){pe_application_stage(statusText);pe_application_stage("\n");}
        return -1;
    }
#endif
    int menuOnly=0,validateOnly=0;
    const char* explicitDisc=getenv("PE2_DISC");
    const char* explicitDisc2=getenv("PE2_DISC2");
    for(int i=1;i<argc;i++) {
        if(!strcmp(argv[i],"--host-menu"))menuOnly=1;
        else if(!strcmp(argv[i],"--validate-discs"))validateOnly=1;
        else if(!strcmp(argv[i],"--disc") && i+1<argc)explicitDisc=argv[++i];
        else if(!strcmp(argv[i],"--disc2") && i+1<argc)explicitDisc2=argv[++i];
        else if(argv[i][0]!='-' && !explicitDisc)explicitDisc=argv[i];
        else { fprintf(stderr,"usage: %s [disc.cue|disc.bin] [--disc2 image] [--host-menu]\n",argv[0]);return -1; }
    }
    if(explicitDisc && acceptPath(explicitDisc,1)!=1) {fprintf(stderr,"%s\n",statusText);return -1;}
    if(explicitDisc2 && acceptPath(explicitDisc2,2)!=2) {fprintf(stderr,"%s\n",statusText);return -1;}
#ifdef PE2_PS5_HOST
    /* Explicit arguments and persisted paths win; missing paths use console
     * discovery and still pass through the normal retail-identity validator. */
    /* Snapshot the complete default pair before acceptPath can normalize a raw
     * BIN into a generated CUE under configDir. Never rediscover its companion
     * from that generated CUE directory. Explicit paths keep their precedence. */
    if(!*discPaths[0] && !*discPaths[1]) {
        const char *pair[2]={pePs5FindDisc(1,NULL),pePs5FindDisc(2,NULL)};
        if(pePs5DiscDiscoveryError()) { fprintf(stderr,"[ps5] %s\n",pePs5DiscDiscoveryReason());return -1; }
        for(int i=0;i<2;i++)if(pair[i] && acceptPath(pair[i],i+1)!=i+1) {
            fprintf(stderr,"%s\n",statusText);return -1;
        }
    } else for(int i=0;i<2;i++) if(!*discPaths[i]) {
        const char *originalCompanion=i==1?explicitDisc:explicitDisc2;
        const char* found=pePs5FindDisc(i+1,originalCompanion&&*originalCompanion?originalCompanion:discPaths[1-i]);
        if(pePs5DiscDiscoveryError()) { fprintf(stderr,"[ps5] %s\n",pePs5DiscDiscoveryReason());return -1; }
        if(found && acceptPath(found,i+1)!=i+1) {
            fprintf(stderr,"%s\n",statusText);return -1;
        }
    }
    if(!*discPaths[0]) {
        fprintf(stderr,"[ps5] Put USA CUE/BIN pairs in "
                       "/mnt/usb0/parasite-eve-ii, or configure PE2_DISC.\n");
        return -1;
    }
#endif
    if(validateOnly) {
        for(int i=0;i<2;i++) {
            PeDisc* d=peDiscOpen(discPaths[i]);int number=peDiscNumber(d);peDiscClose(d);
            if(number!=i+1) {fprintf(stderr,"Disc %d validation failed.\n",i+1);return -1;}
            fprintf(stderr,"USA Disc %d validated: %s\n",number,discPaths[i]);
        }
        saveOptions();return 0;
    }
    s_prevOverlayInit=Psyz_OverlayInit_SDL3GPU(
#ifdef PE2_PS5_HOST
        PeHdOverlayInitGPU
#else
        Host_OverlayInitGPU
#endif
    );
    s_prevOverlayRender=Psyz_OverlayRender_SDL3GPU(Host_OverlayRenderGPU);
#ifdef PE2_PS5_HOST
    pe_previous_frame_callback=Psyz_OverlayFrameCB(PeNativeOverlayFrame);
#endif
    s_prevOverlayDestroy=Psyz_OverlayDestroyCB(Host_OverlayDestroyGPU);
    previousFilter=Psyz_SetOverlayEventFilter_SDL3(settingsEvent);
    if(menuOnly) {
        if(!SDL_InitSubSystem(SDL_INIT_VIDEO|SDL_INIT_GAMEPAD))return -1;
        Psyz_SetTitle("Parasite Eve 2 - Settings");
        ResetGraph(0);
        DISPENV display;
        SetDefDispEnv(&display,0,0,320,240);
        PutDispEnv(&display);
        SetDispMask(1);
        Psyz_VideoVSync(0);
        settings();return 0;
    }
    if(!*discPaths[0]) {
        if(getenv("PSYZ_HEADLESS")) { fprintf(stderr,"Provide Disc 1 with --disc or PE2_DISC.\n");return -1; }
        if(!SDL_InitSubSystem(SDL_INIT_VIDEO|SDL_INIT_GAMEPAD))return -1;
        if(!chooseDiscs(NULL,0))return 0;
    }
    PeDisc* d=peDiscOpen(discPaths[0]);int valid=peDiscNumber(d)==1;peDiscClose(d);
    if(!valid) {fprintf(stderr,"Configured Disc 1 is unavailable or unsupported.\n");return -1;}
#ifdef PE2_PS5_HOST
    /* This image was validated above. Selecting an arbitrary UI path does not
     * change the active pack; the renderer callback applies this before uploads. */
    PeHdSelectValidatedDisc(1);
#endif
    saveOptions();*disc=discPaths[0];return 1;
}

int peHostSwapDisc(int number) {
    if(getenv("PE2_TRACE"))fprintf(stderr,"[disc] swap to disc %d requested (path: %s)\n",number,number>=1&&number<=2&&*discPaths[number-1]?discPaths[number-1]:"none");
    if(number<1||number>2)return 0;
    requiredDisc=number;selectedDisc=0;
    s_overlayState.page=3;s_overlayState.row=number-1;
    snprintf(statusText,sizeof statusText,"Please select USA Disc %d.",number);
    if(!*discPaths[number-1])settings();
    requiredDisc=0;
    if(!*discPaths[number-1] || s_overlayState.quit)return 0;
    PeDisc* d=peDiscOpen(discPaths[number-1]);
    if(peDiscNumber(d)!=number) {peDiscClose(d);return 0;}
    Psyz_CdShellOpen(1);
    if(Psyz_CdSetDiskPath(discPaths[number-1])) {Psyz_CdShellOpen(0);peDiscClose(d);return 0;}
#ifdef PE2_PS5_HOST
    /* Both retail identity and the actual CD path switch succeeded. */
    PeHdSelectValidatedDisc(number);
#endif
    peAssetsLoad(d);
    peDiscClose(d);return 1;
}
