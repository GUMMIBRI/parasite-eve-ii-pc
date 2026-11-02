#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef __APPLE__
#include <mach-o/getsect.h>
#include <mach-o/dyld.h>
#endif

#include "port/asset_bind.h"
#include "port/asset_parts.h"
#include "port/disc_assets.h"
int peAssetsDump(const char* path);

#ifdef __APPLE__
extern const struct mach_header_64 _mh_execute_header;
static const PeAssetBinding* bindings(size_t* count)
{
    unsigned long size = 0;
    const uint8_t* p = getsectiondata(&_mh_execute_header, "__DATA", "__peassets", &size);
    *count = p ? size / sizeof(PeAssetBinding) : 0;
    return (const PeAssetBinding*)p;
}
#else
extern const PeAssetBinding __start_peassets[], __stop_peassets[];
static const PeAssetBinding* bindings(size_t* count)
{
    *count = (size_t)(__stop_peassets - __start_peassets);
    return __start_peassets;
}
#endif

static const PeAssetPart* findPart(const char* key)
{
    int lo = 0, hi = gPeAssetPartCount - 1;
    while (lo <= hi) {
        int mid = (lo + hi) / 2, c = strcmp(key, gPeAssetParts[mid].key);
        if (c == 0) return &gPeAssetParts[mid];
        if (c < 0) hi = mid - 1; else lo = mid + 1;
    }
    return NULL;
}

int peAssetsLoad(struct PeDisc* disc)
{
    static uint8_t* pkgData[4096];
    static size_t   pkgSize[4096];
    size_t          n;
    const PeAssetBinding* b = bindings(&n);
    int filled = 0, missing = 0, wrong = 0;

    for (size_t i = 0; i < n; i++) {
        const PeAssetPart* part = findPart(b[i].key);
        if (!part) { fprintf(stderr, "[assets] no layout for %s\n", b[i].key); wrong++; continue; }
        size_t want = part->op == PE_ASSET_OP_GRID_TABLE ? (size_t)part->size / 4 * sizeof(void*) : part->size;
        if (want != b[i].size) {
            fprintf(stderr, "[assets] %s: array is %zu bytes, layout says %zu\n", b[i].key, b[i].size, want);
            wrong++;
            continue;
        }
        int pi = part->package;
        if (!pkgData[pi]) {
            const PeAssetPackage* pk = &gPeAssetPackages[pi];
            pkgData[pi] = pk->stage < 0 ? peDiscReadFile(disc, "SLUS_010.42", &pkgSize[pi])
                                        : peDiscReadPackage(disc, pk->stage, pk->folder, pk->file, &pkgSize[pi]);
        }
        if (!pkgData[pi]) { missing++; continue; }
        if ((size_t)part->offset + part->size > pkgSize[pi]) {
            fprintf(stderr, "[assets] %s: past the end of %s\n", b[i].key, gPeAssetPackages[pi].name);
            wrong++;
            continue;
        }
        const uint8_t* src = pkgData[pi] + part->offset;
        if (part->op == PE_ASSET_OP_COPY) {
            memcpy(b[i].dst, src, part->size);
        } else {
            const uint32_t* words = (const uint32_t*)(const void*)src; /* PS1 addresses; little endian host */
            const int16_t*  cells = (const int16_t*)b[i].aux;
            const int16_t** out = (const int16_t**)b[i].dst;
            for (uint32_t k = 0; k < part->size / 4; k++) {
                uint32_t w;
                memcpy(&w, &words[k], 4);
                out[k] = w ? cells + (w - part->load - part->cellsOffset) / 2 : NULL;
            }
        }
        filled++;
    }
    if (wrong) fprintf(stderr, "[assets] %d bindings could not be filled\n", wrong);
    if (missing) fprintf(stderr, "[assets] %d bindings wait for the other disc\n", missing);
    return filled;
}

/* Development check: one line per binding, "<key> <hash of the bytes>". Grid tables hash their cell indices, not
 * addresses. Running this on a build with PE_EMBED_ASSETS and on a runtime-loaded build must give identical files. */
int peAssetsDump(const char* path)
{
    size_t n;
    const PeAssetBinding* b = bindings(&n);
    FILE* f = fopen(path, "w");
    if (!f) return 0;
    for (size_t i = 0; i < n; i++) {
        uint64_t h = 1469598103934665603ull;
        const PeAssetPart* part = findPart(b[i].key);
        if (part && part->op == PE_ASSET_OP_GRID_TABLE) {
            const int16_t** t = (const int16_t**)b[i].dst;
            for (size_t k = 0; k < b[i].size / sizeof(void*); k++) {
                long v = t[k] ? (long)(t[k] - (const int16_t*)b[i].aux) : -1;
                h = (h ^ (uint64_t)v) * 1099511628211ull;
            }
        } else {
            const uint8_t* d = b[i].dst;
            for (size_t k = 0; k < b[i].size; k++) h = (h ^ d[k]) * 1099511628211ull;
        }
        fprintf(f, "%s %016llx\n", b[i].key, (unsigned long long)h);
    }
    fclose(f);
    return 1;
}
