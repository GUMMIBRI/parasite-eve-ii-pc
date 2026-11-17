/* Authorized same-project adaptation of PE1 Build17 settings_overlay.h.
 * That source declares no blanket license; no MIT relicensing is asserted.
 * Existing IBM Plex/stb dependency notices remain applicable and unchanged.
 * Include after ui/paint.h in the native host settings translation unit. */
#ifndef PE2_SETTINGS_APPEARANCE_H
#define PE2_SETTINGS_APPEARANCE_H

enum { OVERLAY_APPEARANCE_ORIGINAL=0, OVERLAY_APPEARANCE_MODERN=1 };
enum { OVERLAY_TEXT_ORIGINAL=0, OVERLAY_TEXT_LARGE=1 };
enum { OVERLAY_POINTER_BAR=0, OVERLAY_POINTER_CHEVRON=1, OVERLAY_POINTER_BOTH=2 };
/* Accepted PE1 Build17 defaults; explicitly saved settings take precedence. */
static unsigned overlay_appearance_style=OVERLAY_APPEARANCE_MODERN;
static unsigned overlay_appearance_text=OVERLAY_TEXT_LARGE;
static unsigned overlay_appearance_pointer=OVERLAY_POINTER_BOTH;
static unsigned OverlayAppearanceGetStyle(void) { return overlay_appearance_style; }
static unsigned OverlayAppearanceGetTextSize(void) { return overlay_appearance_text; }
static unsigned OverlayAppearanceGetPointer(void) { return overlay_appearance_pointer; }
static void OverlayAppearanceSetStyle(unsigned value) { if(value<2)overlay_appearance_style=value; }
static void OverlayAppearanceSetTextSize(unsigned value) { if(value<2)overlay_appearance_text=value; }
static void OverlayAppearanceSetPointer(unsigned value) { if(value<3)overlay_appearance_pointer=value; }
static const char *OverlayAppearanceStyleName(void) {
    return overlay_appearance_style?"Modern":"Original overlay";
}
static const char *OverlayAppearanceTextName(void) {
    return overlay_appearance_text?"Large":"Original";
}
static const char *OverlayAppearancePointerName(void) {
    static const char *const names[]={"Original bar","Chevron","Both"};
    return names[overlay_appearance_pointer];
}
static Color OverlayAppearancePanel(void) {
    return overlay_appearance_style?(Color){0.052f,0.066f,0.064f,0.965f}:
        (Color){0.075f,0.082f,0.102f,0.96f};
}
static Color OverlayAppearanceAccent(void) {
    return overlay_appearance_style?(Color){0.38f,0.72f,0.62f,1.0f}:
        (Color){0.27f,0.62f,1.0f,1.0f};
}
static Color OverlayAppearanceText(void) { return (Color){0.93f,0.95f,0.98f,1.0f}; }
static Color OverlayAppearanceMuted(void) { return (Color){0.60f,0.65f,0.73f,1.0f}; }
static float OverlayAppearanceRowEm(float scale,int value) {
    return (overlay_appearance_text?19.0f:value?16.0f:17.0f)*scale;
}
/* PE2's existing panel bounds, row count/height and label/value anchors are
 * preserved. Neither this painter nor the size setting moves input regions. */
static void OverlayAppearancePaintPanel(OverlaySurface *surface,float scale) {
    FillRoundRect(surface,0,0,680*scale,(float)(surface->h-1),16*scale,
        OverlayAppearancePanel());
}
static void OverlayAppearancePaintFocus(OverlaySurface *surface,float baseline,float scale) {
    Color accent=OverlayAppearanceAccent(),wash=accent;
    wash.a=0.16f;
    FillRoundRect(surface,20*scale,baseline-27*scale,640*scale,40*scale,7*scale,wash);
    float mid=baseline-7*scale;
    if(overlay_appearance_pointer!=OVERLAY_POINTER_BAR)
        DrawChevron(surface,24*scale,mid,5*scale,1,2*scale,accent);
    if(overlay_appearance_pointer!=OVERLAY_POINTER_CHEVRON)
        FillRoundRect(surface,24*scale,mid-10*scale,3*scale,20*scale,1.5f*scale,accent);
}
static void OverlayAppearancePaintRow(OverlaySurface *surface,float baseline,float scale,
    const char *label,const char *value,int selected) {
    char fitted_label[1024],fitted_value[1024];
    float label_em=OverlayAppearanceRowEm(scale,0),value_em=OverlayAppearanceRowEm(scale,1);
    /* Fixed column allocation and a 24-design-pixel gap prevent long Large
     * labels from painting over their values; text alone is elided. */
    OverlayFitRowText(label,label_em,340*scale,fitted_label);
    OverlayFitRowText(value,value_em,252*scale,fitted_value);
    DrawText(surface,32*scale,baseline,label_em,fitted_label,OverlayAppearanceText(),ALIGN_LEFT);
    DrawText(surface,648*scale,baseline,value_em,fitted_value,
        selected?OverlayAppearanceAccent():OverlayAppearanceMuted(),ALIGN_RIGHT);
}
#endif
