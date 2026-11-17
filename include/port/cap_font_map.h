/* MPL-2.0. Optional source-owned CAP dialogue font mapping. */
#ifndef PORT_CAP_FONT_MAP_H
#define PORT_CAP_FONT_MAP_H
#ifdef PE2_PS5_HOST
#include "main/text.h"
#include <psyz/cap_font.h>

typedef struct {
    uint64_t generation;
    unsigned slot;
    PsyzFontToken token;
    uint64_t metricKey;
} PeCapPlexRun;

/* Selection identity captured by a producer at actual resolved-resource load.
 * No raw/table pointers survive in this handle; retirement is generation-owned. */
typedef struct { uint64_t generation; unsigned slot; } PeCapPlexOwner;
int peCapPlexBindOwner(const void* resolvedFile, PeCapPlexOwner* owner);
int peCapPlexBeginOwnedRun(const PeCapPlexOwner* owner,
                          const TextGlyphCell* cells, const u16* text,
                          unsigned page, unsigned clut, PeCapPlexRun* run);

/* No map, unknown source or unsupported complete run returns original rendering.
 * The result borrows no file/table/text pointers; generation is checked at tag. */
int peCapPlexBeginRun(const TextGlyphCell* cells, const u16* text,
                      unsigned page, unsigned clut, PeCapPlexRun* run);
void peCapPlexTagPair(const PeCapPlexRun* run, const void* addPayload,
                      const void* subPayload, unsigned cell);
#endif
#endif
