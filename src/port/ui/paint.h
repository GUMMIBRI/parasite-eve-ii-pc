/* Adapted from parasite-eve-pc/src/main/boot/settings_overlay.h.
 * Same Plex font, antialiased panel painter and premultiplied SDL_GPU pipeline. */
static int OverlaySurfaceResize(OverlaySurface *surface, int width, int height) {
    size_t bytes = (size_t)width * (size_t)(height + 1) * 4u;

    if (width == surface->w && height + 1 == surface->h &&
        surface->pixels != NULL) {
        return 1;
    }
    free(surface->pixels);
    surface->pixels = (uint8_t *)calloc(1, bytes);
    surface->w = surface->pixels != NULL ? width : 0;
    surface->h = surface->pixels != NULL ? height + 1 : 0;
    return surface->pixels != NULL;
}

static void OverlaySurfaceRelease(OverlaySurface *surface) {
    free(surface->pixels);
    *surface = (OverlaySurface){0};
}

static float Clamp01(float v) { return v < 0.0f ? 0.0f : v > 1.0f ? 1.0f : v; }

static void BlendPixel(OverlaySurface *s, int x, int y, Color c, float coverage) {
    uint8_t *p;
    float a = c.a * coverage;
    float keep = 1.0f - a;

    /* The last row is the solid texel, not part of the panel. */
    if (x < 0 || y < 0 || x >= s->w || y >= s->h - 1 || a <= 0.0f) return;
    p = s->pixels + ((size_t)y * (size_t)s->w + (size_t)x) * 4u;
    p[0] = (uint8_t)(c.r * a * 255.0f + p[0] * keep + 0.5f);
    p[1] = (uint8_t)(c.g * a * 255.0f + p[1] * keep + 0.5f);
    p[2] = (uint8_t)(c.b * a * 255.0f + p[2] * keep + 0.5f);
    p[3] = (uint8_t)(a * 255.0f + p[3] * keep + 0.5f);
}

/* ---- shapes ---- */

static float RoundRectDistance(float px, float py, float x, float y, float w,
                               float h, float r) {
    float cx = x + w * 0.5f;
    float cy = y + h * 0.5f;
    float qx = fabsf(px - cx) - (w * 0.5f - r);
    float qy = fabsf(py - cy) - (h * 0.5f - r);
    float ox = qx > 0.0f ? qx : 0.0f;
    float oy = qy > 0.0f ? qy : 0.0f;
    float inside = qx > qy ? qx : qy;

    return sqrtf(ox * ox + oy * oy) + (inside < 0.0f ? inside : 0.0f) - r;
}

static void FillRoundRect(OverlaySurface *s, float x, float y, float w, float h,
                          float r, Color c) {
    int x0 = (int)floorf(x) - 1, x1 = (int)ceilf(x + w) + 1;
    int y0 = (int)floorf(y) - 1, y1 = (int)ceilf(y + h) + 1;
    int ix, iy;

    for (iy = y0; iy < y1; iy++) {
        for (ix = x0; ix < x1; ix++) {
            float d = RoundRectDistance((float)ix + 0.5f, (float)iy + 0.5f, x,
                                        y, w, h, r);
            BlendPixel(s, ix, iy, c, Clamp01(0.5f - d));
        }
    }
}

/* A capsule: the thick line segment the chevrons are made of. */
static void DrawSegment(OverlaySurface *s, float ax, float ay, float bx,
                        float by, float width, Color c) {
    float minX = (ax < bx ? ax : bx) - width - 1.0f;
    float maxX = (ax > bx ? ax : bx) + width + 1.0f;
    float minY = (ay < by ? ay : by) - width - 1.0f;
    float maxY = (ay > by ? ay : by) + width + 1.0f;
    float ex = bx - ax, ey = by - ay;
    float length2 = ex * ex + ey * ey;
    int ix, iy;

    for (iy = (int)floorf(minY); iy < (int)ceilf(maxY); iy++) {
        for (ix = (int)floorf(minX); ix < (int)ceilf(maxX); ix++) {
            float px = (float)ix + 0.5f - ax;
            float py = (float)iy + 0.5f - ay;
            float t = length2 > 0.0f ? (px * ex + py * ey) / length2 : 0.0f;
            float qx, qy, d;

            t = Clamp01(t);
            qx = px - ex * t;
            qy = py - ey * t;
            d = sqrtf(qx * qx + qy * qy) - width * 0.5f;
            BlendPixel(s, ix, iy, c, Clamp01(0.5f - d));
        }
    }
}

static void DrawChevron(OverlaySurface *s, float cx, float cy, float size,
                        int direction, float width, Color c) {
    float tipX = cx + (float)direction * size * 0.5f;
    float backX = cx - (float)direction * size * 0.5f;

    DrawSegment(s, backX, cy - size, tipX, cy, width, c);
    DrawSegment(s, backX, cy + size, tipX, cy, width, c);
}

/* ---- text ---- */

static stbtt_fontinfo s_font;
static int s_fontState;

static int OverlayFontReady(void) {
    int offset;

    if (s_fontState != 0) return s_fontState > 0;
    offset = stbtt_GetFontOffsetForIndex(ibm_plex_sans_ttf, 0);
    if (offset < 0 || (size_t)offset >= ibm_plex_sans_ttf_len ||
        !stbtt_InitFont(&s_font, ibm_plex_sans_ttf, offset)) {
        s_fontState = -1;
        return 0;
    }
    s_fontState = 1;
    return 1;
}

static float TextWidth(const char *text, float em) {
    float scale = stbtt_ScaleForMappingEmToPixels(&s_font, em);
    float width = 0.0f;

    for (; *text != '\0'; text++) {
        int advance, bearing;

        stbtt_GetCodepointHMetrics(&s_font, (unsigned char)*text, &advance,
                                   &bearing);
        width += (float)advance * scale;
    }
    return width;
}

typedef enum TextAlign { ALIGN_LEFT, ALIGN_CENTRE, ALIGN_RIGHT } TextAlign;

static void DrawText(OverlaySurface *s, float x, float baseline, float em,
                     const char *text, Color c, TextAlign align) {
    enum { GLYPH_MAX = 256 };
    static uint8_t glyph[GLYPH_MAX * GLYPH_MAX];
    float scale = stbtt_ScaleForMappingEmToPixels(&s_font, em);
    float width = TextWidth(text, em);

    x -= align == ALIGN_CENTRE ? width * 0.5f
         : align == ALIGN_RIGHT ? width : 0.0f;
    for (; *text != '\0'; text++) {
        int codepoint = (unsigned char)*text;
        int advance, bearing, x0, y0, x1, y1, gx, gy;

        stbtt_GetCodepointHMetrics(&s_font, codepoint, &advance, &bearing);
        stbtt_GetCodepointBitmapBox(&s_font, codepoint, scale, scale, &x0, &y0,
                                    &x1, &y1);
        if (x1 - x0 > 0 && y1 - y0 > 0 && x1 - x0 <= GLYPH_MAX &&
            y1 - y0 <= GLYPH_MAX) {
            int gw = x1 - x0, gh = y1 - y0;
            int ox = (int)floorf(x + 0.5f) + x0;
            int oy = (int)floorf(baseline + 0.5f) + y0;

            stbtt_MakeCodepointBitmap(&s_font, glyph, gw, gh, gw, scale, scale,
                                      codepoint);
            for (gy = 0; gy < gh; gy++) {
                for (gx = 0; gx < gw; gx++) {
                    uint8_t coverage = glyph[gy * gw + gx];
                    if (coverage != 0) {
                        BlendPixel(s, ox + gx, oy + gy, c,
                                   (float)coverage / 255.0f);
                    }
                }
            }
        }
        x += (float)advance * scale;
    }
}

/* ---- geometry helpers ---- */

static int OverlayDesignHeight(int rowCount) {
    return OVERLAY_HEADER_H + rowCount * OVERLAY_ROW_H + OVERLAY_ACTION_GAP +
           OVERLAY_FOOTER_H;
}

static void OverlayFitLayout(int designW, int designH, int windowW, int windowH,
                             OverlayLayout *layout) {
    float scale = (float)windowH / (float)OVERLAY_REFERENCE_H;
    float widthLimit = (float)windowW * 0.94f / (float)designW;
    float heightLimit = (float)windowH * 0.94f / (float)designH;

    if (scale > widthLimit) scale = widthLimit;
    if (scale > heightLimit) scale = heightLimit;
    if (scale > 2.5f) scale = 2.5f;
    if (scale < 0.5f) scale = 0.5f;
    scale = floorf(scale * 8.0f) / 8.0f; /* no repaint on every resize pixel */
    layout->scale = scale;
    layout->w = (int)ceilf((float)designW * scale);
    layout->h = (int)ceilf((float)designH * scale);
    layout->x = (windowW - layout->w) / 2;
    layout->y = (windowH - layout->h) / 2;
}

