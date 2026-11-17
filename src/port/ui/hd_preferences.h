/* MPL-2.0. Native host selection of external, read-only character texture packs.
 * Included by host_ui.c after its existing GPU overlay implementation. */
#ifndef PE2_NATIVE_HD_PREFERENCES_H
#define PE2_NATIVE_HD_PREFERENCES_H
#include <psyz/gpu.h>
#include <psyz/hd_upload.h>

/* Public renderer implementations/header remain manager-owned. */
extern int Psyz_GpuSetHdBackgrounds(int enabled,const char *root);
extern int Psyz_GpuGetHdBackgrounds(void);
extern const char *Psyz_GpuHdBackgroundsStatus(void);

static int pe_hd_background_preference=1;
static char pe_hd_background_error[128];
static int pe_hd_preference;
static int pe_hd_active_disc;
static int pe_hd_renderer_ready;
static char pe_hd_bound_root[1024];
static char pe_hd_selection_error[128];

static const char *PeHdExplicitRoot(void)
{
    const char *root = getenv("PE2_HD_CHARACTER_ROOT");
    return root && root[0] ? root : NULL;
}

/* Background selection is independent of player HD and never resets its
 * atlas. The renderer owns admission, display resources and safe root changes. */
static int PeHdTryBackgroundRoot(const char *root)
{
    if (strlen(root) >= sizeof pe_hd_bound_root) return 0;
    return Psyz_GpuSetHdBackgrounds(pe_hd_background_preference,root) >= 0;
}

static void PeHdApplyBackgroundPreference(void)
{
    pe_hd_background_error[0]=0;
    if (!pe_hd_renderer_ready) return;
    Psyz_GpuSetHdBackgrounds(0,NULL);
    if (!pe_hd_background_preference && !Psyz_VideoGetWidescreen()) return;
    if (pe_hd_active_disc != 1 && pe_hd_active_disc != 2) {
        snprintf(pe_hd_background_error,sizeof pe_hd_background_error,"Waiting for a validated game disc");
        return;
    }
    const char *explicit_root=PeHdExplicitRoot();
    if (explicit_root) {
        /* An explicitly chosen common replacement root never falls through. */
        if (!PeHdTryBackgroundRoot(explicit_root))
            snprintf(pe_hd_background_error,sizeof pe_hd_background_error,"Configured background pack unavailable; originals retained");
        return;
    }
    /* Prefer the same successfully selected current-disc player root when
     * it is enabled; this read-only choice never enables player textures. */
    if (pe_hd_preference && !pe_hd_selection_error[0] && pe_hd_bound_root[0] &&
        PeHdTryBackgroundRoot(pe_hd_bound_root)) return;
    const char *serial=pe_hd_active_disc == 1 ? "SLUS-01042" : "SLUS-01055";
    char root[1024];
    for (unsigned usb=0;usb<8;++usb) {
        snprintf(root,sizeof root,"/mnt/usb%u/parasite-eve-ii/hd-textures/%s/replacements",usb,serial);
        if (PeHdTryBackgroundRoot(root)) return;
    }
    snprintf(pe_hd_background_error,sizeof pe_hd_background_error,"Disc %d background pack unavailable; originals retained",pe_hd_active_disc);
}

static const char *PeHdBackgroundStatus(void)
{
    if (!pe_hd_background_preference) return "Off";
    if (!pe_hd_renderer_ready) return "Waiting for renderer";
    if (pe_hd_background_error[0]) return pe_hd_background_error;
    return Psyz_GpuHdBackgroundsStatus();
}

static void PeHdToggleBackgroundPreference(void)
{
    pe_hd_background_preference=!pe_hd_background_preference;
    PeHdApplyBackgroundPreference();
}

static int PeHdRequested(void)
{
    return PeHdExplicitRoot() != NULL || pe_hd_preference;
}

/* A root change must retire both queued readers and immutable shared cells.
 * The checked GPU API leaves everything intact on a failed retirement. */
static int PeHdTryRoot(const char *root)
{
    char index[1200];
    if (strlen(root) >= sizeof pe_hd_bound_root ||
        snprintf(index, sizeof index, "%s/upload-index.txt", root) >= (int)sizeof index)
        return 0;
    FILE *probe = fopen(index, "rb");
    if (!probe) return 0;
    fclose(probe);
    if (pe_hd_bound_root[0] && strcmp(root, pe_hd_bound_root)) {
        if (!Psyz_GpuTryResetSpriteAtlases()) {
            snprintf(pe_hd_selection_error, sizeof pe_hd_selection_error,
                     "Pack switch unavailable; originals retained");
            return -1;
        }
        pe_hd_bound_root[0] = 0;
    }
    if (Psyz_GpuSetHdUploadCharacters(1, root) < 0) return 0;
    strcpy(pe_hd_bound_root, root);
    return 1;
}

static void PeHdApplyPreference(void)
{
    pe_hd_selection_error[0] = 0;
    if (!pe_hd_renderer_ready) return;
    /* Disable the old selection before probing. Invalid explicit roots never
     * fall through to another pack or keep the previous disc's pack active. */
    Psyz_GpuSetHdUploadCharacters(0, NULL);
    if (!PeHdRequested()) return;
    if (pe_hd_active_disc != 1 && pe_hd_active_disc != 2) {
        snprintf(pe_hd_selection_error, sizeof pe_hd_selection_error,
                 "Waiting for a validated game disc");
        return;
    }
    const char *explicit_root = PeHdExplicitRoot();
    if (explicit_root) {
        int result = PeHdTryRoot(explicit_root);
        if (!result)
            snprintf(pe_hd_selection_error, sizeof pe_hd_selection_error,
                     "Configured pack unavailable; originals retained");
        return;
    }
    const char *serial = pe_hd_active_disc == 1 ? "SLUS-01042" : "SLUS-01055";
    char root[1024];
    int result;
    for (unsigned usb = 0; usb < 8; ++usb) {
        snprintf(root, sizeof root, "/mnt/usb%u/parasite-eve-ii/hd-textures/%s/replacements", usb, serial);
        result = PeHdTryRoot(root);
        if (result) return;
    }
    snprintf(pe_hd_selection_error, sizeof pe_hd_selection_error,
             "Disc %d pack unavailable; originals retained", pe_hd_active_disc);
}

static const char *PeHdStatus(void)
{
    if (!PeHdRequested()) return "Off";
    if (!pe_hd_renderer_ready) return "Waiting for renderer";
    if (pe_hd_selection_error[0]) return pe_hd_selection_error;
    return Psyz_GpuHdUploadCharactersStatus();
}

static void PeHdTogglePreference(void)
{
    if (!PeHdExplicitRoot()) pe_hd_preference = !pe_hd_preference;
    PeHdApplyPreference();
}

static void PeHdSelectValidatedDisc(int number)
{
    pe_hd_active_disc = number;
    PeHdApplyPreference();
    PeHdApplyBackgroundPreference();
}

static void PeHdOverlayInitGPU(SDL_Window *window, SDL_GPUDevice *device)
{
    Host_OverlayInitGPU(window, device);
    pe_hd_renderer_ready = device != NULL;
    PeHdApplyPreference();
    PeHdApplyBackgroundPreference();
}
#endif
