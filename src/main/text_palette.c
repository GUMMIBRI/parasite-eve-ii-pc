#include "main/text.h"
#include "port/asset_bind.h"
#include "gameplay/gpu_image_upload.h"

/// Four resident 16-color font palettes, packed two RGB555/STP colors per word.
///
/// The 32 `u32` words hold 64 VRAM colors uploaded at (256,243), yielding
/// CLUTs 0x3CD0..0x3CD3. These retain a nontransparent glyph-cell background;
/// the separate glyph palette row supplies transparent cell padding.
#ifdef PE_EMBED_ASSETS
_Alignas(u_long) static u32 _gTextFontPaletteWords[] = {
#include "assets/text_clut0.inc"
};
#else
_Alignas(u_long) static u32 _gTextFontPaletteWords[32];
#endif
PE_ASSET_BIND("text_clut0", _gTextFontPaletteWords);
STATIC_ASSERT_SIZEOF(_gTextFontPaletteWords, 32 * sizeof(u32));

/// Retained two-record font-palette upload list: copy to (256,243), then end.
///
/// No code reads the list. Its 64-color width covers the complete resident
/// font palette row at the same destination used by the live uploader.
static GpuImageUpload _gTextFontPaletteUploadList[2] = {
    {
        .operation   = GPU_IMAGE_UPLOAD_COPY,
        .unknown_2   = 0,
        .destination = { 256, 243, sizeof(_gTextFontPaletteWords) / sizeof(u16), 1 },
        .pixels      = (u_long*)_gTextFontPaletteWords,
    },
    { .operation = GPU_IMAGE_UPLOAD_END },
};

/// Resident glyph-fill and outline palettes, packed two RGB555/STP colors per word.
///
/// The 24 `u32` words hold 48 VRAM colors in three 16-color blocks: fill,
/// translucent-text outline, then ordinary/standalone outline. The live upload
/// at (976,511) yields CLUTs 0x7FFD, 0x7FFE and 0x7FFF. Fill indices 0..10
/// are transparent, including the font texture's cell-padding index 5.
#ifdef PE_EMBED_ASSETS
_Alignas(u_long) static u32 _gTextGlyphPaletteWords[] = {
#include "assets/ui/font/glyph_palettes.inc"
};
#else
_Alignas(u_long) static u32 _gTextGlyphPaletteWords[24];
#endif
PE_ASSET_BIND("ui/font/glyph_palettes", _gTextGlyphPaletteWords);
STATIC_ASSERT_SIZEOF(_gTextGlyphPaletteWords, 24 * sizeof(u32));

/// Retained two-record glyph-palette upload list: copy to (256,240), then end.
///
/// No code reads the list. Its 48-color width covers all three resident glyph
/// palettes. This retained destination differs from the live upload at (976,511);
/// the original purpose of the unused destination is unproven.
static GpuImageUpload _gTextGlyphPaletteUploadList[2] = {
    {
        .operation   = GPU_IMAGE_UPLOAD_COPY,
        .unknown_2   = 0,
        .destination = { 256, 240, sizeof(_gTextGlyphPaletteWords) / sizeof(u16), 1 },
        .pixels      = (u_long*)_gTextGlyphPaletteWords,
    },
    { .operation = GPU_IMAGE_UPLOAD_END },
};

void textUploadPalettes(void)
{
    enum {
        TEXT_FONT_PALETTE_ROW_X  = 256,
        TEXT_FONT_PALETTE_ROW_Y  = 243,
        TEXT_GLYPH_PALETTE_ROW_X = 976,
        TEXT_GLYPH_PALETTE_ROW_Y = 511,
    };
    RECT uploadRect;

    // VRAM widths count 16-bit colors; each RAM word packs two colors.
    uploadRect.x = TEXT_FONT_PALETTE_ROW_X;
    uploadRect.y = TEXT_FONT_PALETTE_ROW_Y;
    uploadRect.w = sizeof(_gTextFontPaletteWords) / sizeof(u16);
    uploadRect.h = 1;
    LoadImage(&uploadRect, (u_long*)_gTextFontPaletteWords);

    // The glyph row contains the fill and both outline palettes.
    uploadRect.x = TEXT_GLYPH_PALETTE_ROW_X;
    uploadRect.y = TEXT_GLYPH_PALETTE_ROW_Y;
    uploadRect.w = sizeof(_gTextGlyphPaletteWords) / sizeof(u16);
    uploadRect.h = 1;
    LoadImage(&uploadRect, (u_long*)_gTextGlyphPaletteWords);
}
