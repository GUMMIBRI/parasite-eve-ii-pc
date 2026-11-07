#ifndef PORT_BACKGROUNDS_H
#define PORT_BACKGROUNDS_H

/* Saved user preference; actual widescreen requires reviewed artwork coverage. */
void peBackgroundSetWidescreen(int enabled);
int peBackgroundGetWidescreen(void);
/* Call before drawing a frame. A missing/narrow span keeps original rendering.
 * Only an artwork presenter may supply a span beyond the original 0..320. */
int peBackgroundSetCoverage(int buffer_y, int left, int right);
#endif
