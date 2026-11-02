#include "port/cap_asset.h"
#include "main/fs.h"
#include "gameplay/captions.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

extern const TextGlyphCell* gCapGlyphCells;
extern CapSequenceRecord* gCapSelectedSequence;
static struct { size_t bytes; PeCapAsset* asset; const void* raw; } resources[50];

void peCapResourcesReset(void)
{
    /* Same invalidation boundary as the source RAM bundle. Playback and room
     * caption users must have finished before loading a replacement. */
    gCapFile = NULL;
    gCapGlyphCells = NULL;
    gCapCommandEntries = NULL;
    gCapSelectedSequence = NULL;
    for (unsigned i = 0; i < 50; ++i) {
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
        resources[i].asset = peCapDecode(raw, resources[i].bytes);
        resources[i].raw = raw;
        CapFile* file = peCapAssetFile(resources[i].asset);
        if (file && getenv("PE2_TRACE")) {
            fprintf(stderr, "[cap] slot=%u bytes=%zu commands=%d records=%d\n", i,
                    resources[i].bytes, file->commands.table->count, file->sequences.table->count);
        }
        return file;
    }
    return NULL;
}
