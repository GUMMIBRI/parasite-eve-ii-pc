#ifndef PORT_ASSET_BIND_H
#define PORT_ASSET_BIND_H
#include <stddef.h>

/* An array whose contents come from the user's disc at run time. The array is defined (zero-filled) where the
 * original source had `= { #include "assets/<key>.inc" }`; this registers it so `peAssetsLoad` can fill it from the
 * decoded package named by the key. `aux` is the grid cell array a grid table points into. */
typedef struct PeAssetBinding {
    const char* key;
    void*       dst;
    size_t      size;
    const void* aux;
} PeAssetBinding;

#define PE_ASSET_CAT2(a, b) a##b
#define PE_ASSET_CAT(a, b)  PE_ASSET_CAT2(a, b)
/* The linker set is traversed as contiguous records. ASan global redzones
 * would become fake records; only this immutable registry omits redzones.
 * The destination arrays and loader accesses remain instrumented. */
#ifdef __clang__
#define PE_ASSET_REGISTRY_ATTR __attribute__((no_sanitize("address")))
#else
#define PE_ASSET_REGISTRY_ATTR
#endif
#ifdef __APPLE__
#define PE_ASSET_SECTION __attribute__((section("__DATA,__peassets")))
#else
#define PE_ASSET_SECTION __attribute__((section("peassets")))
#endif
#define PE_ASSET_BIND_AUX(key, array, auxArray)                                                         \
    static const PeAssetBinding PE_ASSET_CAT(_peAssetBinding_, __COUNTER__) PE_ASSET_SECTION PE_ASSET_REGISTRY_ATTR __attribute__((used)) = { \
        key, (void*)&(array), sizeof(array), (auxArray) }
#define PE_ASSET_BIND(key, array) PE_ASSET_BIND_AUX(key, array, NULL)
/* An array of structs the host lays out differently from the disc (pointers are wider): `decode(dst, src, count)`
 * fills `count` elements from consecutive disc records and sets their pointers. */
typedef void (*PeAssetDecode)(void* dst, const unsigned char* src, size_t count);
#define PE_ASSET_BIND_DECODE(key, array, decode) PE_ASSET_BIND_AUX(key, array, (const void*)(PeAssetDecode)(decode))

struct PeDisc;
/* Fills every binding whose package is on the mounted disc. Returns the number filled; bindings of packages on the
 * other disc stay zero until that disc is mounted and this is called again. */
int peAssetsLoad(struct PeDisc* disc);
#endif
