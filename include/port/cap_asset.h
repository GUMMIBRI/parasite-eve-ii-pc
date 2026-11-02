#ifndef PORT_CAP_ASSET_H
#define PORT_CAP_ASSET_H
#include <stddef.h>
#include "gameplay/cap.h"
/* Owned native view of a packed CAP file. Decode copies the bytes; glyphs and
 * text remain packed in that copy, commands and pointer-bearing slots expand.
 * The input is never relocated or modified. NULL indicates malformed data. */
typedef struct PeCapAsset PeCapAsset;
PeCapAsset* peCapDecode(const void* data, size_t bytes);
CapFile* peCapAssetFile(PeCapAsset* asset);
void peCapFree(PeCapAsset* asset);

/* Bundle-owned lazy views, shared by gameplay and overlay caption readers.
 * Reset before another bundle overwrites RAM, after old users have stopped.
 * Sizes are published with the directory; resolve only after payload completion. */
void peCapResourcesReset(void);
void peCapSetResourceSize(unsigned slot, size_t bytes);
CapFile* peCapResolveResource(const void* rawFile);
#endif
