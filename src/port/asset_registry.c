#include "port/asset_bind.h"

#ifdef _WIN32
/* COFF sorts these around the .peassets$m records emitted by PE_ASSET_BIND.
 * Keep the boundaries external to the reader so optimization cannot infer
 * that every record read beyond a local zero marker is itself zero. */
__attribute__((section(".peassets$a"), used)) const PeAssetBinding peAssetsBegin[1] = {{0}};
__attribute__((section(".peassets$z"), used)) const PeAssetBinding peAssetsEnd[1] = {{0}};
#endif
