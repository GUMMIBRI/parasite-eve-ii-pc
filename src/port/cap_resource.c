#include "port/cap_asset.h"
#include "main/fs.h"
#include "gameplay/captions.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#ifdef PE2_PS5_HOST
#include "cap_font_map.inc.h"
#endif

extern const TextGlyphCell* gCapGlyphCells;
extern CapSequenceRecord* gCapSelectedSequence;
static struct {
    size_t bytes;
    PeCapAsset* asset;
    const void* raw;
#ifdef PE2_PS5_HOST
    uint64_t fontGeneration;
    unsigned fontMapAttempted;
    PeCapFontMap* fontMap;
#endif
} resources[50];
#ifdef PE2_PS5_HOST
static uint64_t capFontGeneration;
#endif

void peCapResourcesReset(void)
{
    /* Same invalidation boundary as the source RAM bundle. Playback and room
     * caption users must have finished before loading a replacement. */
    gCapFile = NULL;
    gCapGlyphCells = NULL;
    gCapCommandEntries = NULL;
    gCapSelectedSequence = NULL;
    for (unsigned i = 0; i < 50; ++i) {
#ifdef PE2_PS5_HOST
        free(resources[i].fontMap);
        resources[i].fontMap = NULL;
        resources[i].fontGeneration = 0;
        resources[i].fontMapAttempted = 0;
#endif
        peCapFree(resources[i].asset);
        resources[i].asset = NULL;
        resources[i].raw = NULL;
        resources[i].bytes = 0;
    }
}
void peCapSetResourceSize(unsigned slot, size_t bytes)
{
    if (slot < 50) resources[slot].bytes = bytes;
}
CapFile* peCapResolveResource(const void* raw)
{
    if (!raw) return NULL;
    for (unsigned i = 0; i < 50; ++i) {
        if (resources[i].asset && raw == peCapAssetFile(resources[i].asset))
            return peCapAssetFile(resources[i].asset);
        if (gFsResourceSlots[i].kind != FILE_SYSTEM_RESOURCE_DATA || gFsResourceSlots[i].data != raw) continue;
        if (resources[i].asset && resources[i].raw == raw) return peCapAssetFile(resources[i].asset);
        uintptr_t address = (uintptr_t)raw, base = (uintptr_t)gHostRam;
        if (address < base || address - base >= sizeof(gHostRam) ||
            resources[i].bytes > sizeof(gHostRam) - (address - base)) return NULL;
#ifdef PE2_PS5_HOST
        free(resources[i].fontMap);
        resources[i].fontMap = NULL;
        resources[i].fontGeneration = 0;
        resources[i].fontMapAttempted = 0;
#endif
        resources[i].asset = peCapDecode(raw, resources[i].bytes);
        resources[i].raw = raw;
        CapFile* file = peCapAssetFile(resources[i].asset);
#ifdef PE2_PS5_HOST
        /* Never reuse a serial after wrap; unidentifiable resources stay original. */
        if (file && capFontGeneration != UINT64_MAX)
            resources[i].fontGeneration = ++capFontGeneration;
#endif
        if (file && getenv("PE2_TRACE")) {
            fprintf(stderr, "[cap] slot=%u bytes=%zu commands=%d records=%d\n", i,
                    resources[i].bytes, file->commands.table->count, file->sequences.table->count);
        }
        return file;
    }
    return NULL;
}

#ifdef PE2_PS5_HOST
int peCapPlexBindOwner(const void* resolvedFile, PeCapPlexOwner* owner)
{
    if (!owner) return 0;
    memset(owner, 0, sizeof(*owner));
    owner->slot = UINT_MAX;
    unsigned matches = 0;
    for (unsigned i = 0; i < 50; ++i) {
        if (resolvedFile && resources[i].fontGeneration &&
            peCapAssetFile(resources[i].asset) == resolvedFile) {
            owner->slot = i;
            owner->generation = resources[i].fontGeneration;
            ++matches;
        }
    }
    if (matches == 1) return 1;
    owner->slot = UINT_MAX;
    owner->generation = 0;
    return 0;
}

int peCapPlexBeginOwnedRun(const PeCapPlexOwner* owner,
                          const TextGlyphCell* cells, const u16* text,
                          unsigned page, unsigned clut, PeCapPlexRun* run)
{
    if (!run) return 0;
    memset(run, 0, sizeof(*run));
    run->slot = UINT_MAX;
    if (!owner || owner->slot >= 50 || !owner->generation ||
        resources[owner->slot].fontGeneration != owner->generation) return 0;
    CapFile* file = peCapAssetFile(resources[owner->slot].asset);
    if (!file || file->glyphs.cells != cells) return 0;
    /* Reuse the exact existing text/atlas/CLUT/map/full-run admission, with
     * an additional producer-captured resource epoch, never relaxed policy. */
    if (!peCapPlexBeginRun(cells, text, page, clut, run)) return 0;
    if (run->slot == owner->slot && run->generation == owner->generation) return 1;
    memset(run, 0, sizeof(*run));
    run->slot = UINT_MAX;
    return 0;
}

int peCapPlexBeginRun(const TextGlyphCell* cells, const u16* text,
                     unsigned page, unsigned clut, PeCapPlexRun* run)
{
    if (!run) return 0;
    memset(run, 0, sizeof(*run));
    run->slot = UINT_MAX;
    for (unsigned i = 0; i < 50; ++i) {
        CapFile* file = peCapAssetFile(resources[i].asset);
        if (!file || !resources[i].fontGeneration || file->glyphs.cells != cells) continue;
        if (!resources[i].fontMapAttempted) {
            resources[i].fontMapAttempted = 1;
            resources[i].fontMap = capFontReadMap(resources[i].asset);
        }
        if (!capFontPreflight(resources[i].asset, resources[i].fontMap,
                              cells, text, page, clut, &run->token, &run->metricKey)) return 0;
        run->slot = i;
        run->generation = resources[i].fontGeneration;
        return 1;
    }
    return 0;
}

void peCapPlexTagPair(const PeCapPlexRun* run, const void* addPayload,
                     const void* subPayload, unsigned cell)
{
    unsigned character = 0, foreground = 0;
    const PsyzFontToken* token = NULL;
    if (run && run->slot < 50 && run->generation &&
        resources[run->slot].fontGeneration == run->generation &&
        resources[run->slot].asset && resources[run->slot].fontMap &&
        Psyz_FontIdentityValidate(&run->token)) {
        const PeCapFontMap* map = resources[run->slot].fontMap;
        if (cell < map->glyphCount) {
            character = map->ascii[cell];
            foreground = map->foreground;
            token = &run->token;
        }
    }
    /* The pair API commits or clears both payloads atomically. It allocates no
     * font atlas resources while the caller is assembling CAP polygons. */
    if(run && run->metricKey){
        Psyz_GpuMarkPlexCapMetricPair(addPayload,subPayload,
            character?run->metricKey:0,cell,token);
    }else Psyz_GpuMarkPlexCapPair(addPayload, subPayload, character, foreground, token);
}
#endif
