/* MPL-2.0. PE1 Build17 FPS overlay policy, adapted to PE2 normal Plex UI.
 * Include AFTER ui/gpu.h. Root calls refresh before its normal overlay draw. */
#ifndef PE_PRESENTATION_STATS_UI_H
#define PE_PRESENTATION_STATS_UI_H
#include <psyz/presentation_stats.h>
static int pe_show_presented_fps,pe_stats_surface;
static Uint64 pe_stats_last_refresh;
static int PePresentationShowFps(void){return pe_show_presented_fps;}
static void PePresentationSetShowFps(int enabled) {
 pe_show_presented_fps=!!enabled;pe_stats_surface=0;s_overlayState.dirty=1;
}
static void PePresentationStatsMenuBegin(void){pe_stats_surface=0;s_overlayState.dirty=1;}
static int PePresentationStatsReady(void) {
 return pe_show_presented_fps&&pe_stats_surface&&Psyz_GpuPresentationStatsVisible();
}
static int PePresentationStatsRefreshGPU(void) {
 if(s_overlayState.open||!pe_show_presented_fps||!Psyz_GpuPresentationStatsVisible())return 0;
 SDL_Window *window=Psyz_GetWindow_SDL3();int w=0,h=0;
 if(!window||!s_overlayGpuDevice||!OverlayFontReady())return 0;
 SDL_GetWindowSizeInPixels(window,&w,&h);if(w<=0||h<=0)return 0;
 Uint64 now=SDL_GetTicks();
 if(pe_stats_surface&&w==s_overlayWindowW&&h==s_overlayWindowH&&now-pe_stats_last_refresh<250)return 1;
 pe_stats_surface=0;
 if(!OverlaySurfaceResize(&s_overlaySurface,260,55))return 0;
 memset(s_overlaySurface.pixels,0,260u*55u*4u);
 FillRoundRect(&s_overlaySurface,0,0,260,54,8,(Color){0.02f,0.025f,0.03f,0.80f});
 float fps=Psyz_GpuGetPresentedFps();char label[64];
 if(fps>0&&fps<10000)snprintf(label,sizeof label,"Display %.1f FPS",fps);
 else snprintf(label,sizeof label,"Display FPS: measuring");
 DrawText(&s_overlaySurface,14,35,23,label,kText,ALIGN_LEFT);
 float scale=(float)h/1080;if(scale<1)scale=1;if(scale>3)scale=3;
 s_overlayWindowW=w;s_overlayWindowH=h;
 s_overlayLayout=(OverlayLayout){.x=(int)(w*0.03f),.y=(int)(h*0.03f),.w=(int)(260*scale),.h=(int)(54*scale),.scale=scale};
 if(!Host_EnsureOverlayPipeline(s_overlayGpuDevice,SDL_GetGPUSwapchainTextureFormat(s_overlayGpuDevice,window))||
    !Host_UploadOverlaySurfaceAndVertices(s_overlayGpuDevice))return 0;
 pe_stats_surface=1;pe_stats_last_refresh=now;s_overlayState.dirty=1;return 1;
}
#endif
