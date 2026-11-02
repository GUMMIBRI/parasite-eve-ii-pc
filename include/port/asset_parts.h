#ifndef PORT_ASSET_PARTS_H
#define PORT_ASSET_PARTS_H
#include <stdint.h>

typedef struct {
    const char* name; /* package name, e.g. "actor_120300" */
    int         stage, folder, file;
} PeAssetPackage;

enum { PE_ASSET_OP_COPY = 0, PE_ASSET_OP_GRID_TABLE = 1 };

typedef struct {
    const char* key; /* include file name without ".inc"; the table is sorted by key */
    int         package;
    uint32_t    offset, size;
    int         op;
    uint32_t    load;       /* package load address (grid tables) */
    uint32_t    cellsOffset; /* offset of the grid's cell lists in the package (grid tables) */
} PeAssetPart;

extern const PeAssetPackage gPeAssetPackages[];
extern const int            gPeAssetPackageCount;
extern const PeAssetPart    gPeAssetParts[];
extern const int            gPeAssetPartCount;
#endif
