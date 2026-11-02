#ifndef PORT_GPU_LEN_H
#define PORT_GPU_LEN_H
/* Force-included into the game sources (CMake) after PsyZ's libgpu.h.
 *
 * The GPU backend walks a primitive as `len` 32-bit command words, the PS1 meaning of the tag's length
 * byte. The decomp computes it from the PS1 struct size (`sizeof(*p) / sizeof(u32) - 1`,
 * `... / sizeof(u_long)`), which is wrong for the host structs (8-byte tag/pointers, padding). Derive the
 * word count from the primitive type instead; unknown types keep the caller's value.
 * DR_MODE reserves two command slots but callers may intentionally emit only
 * one. Preserve explicit 0..2 counts; normalize host-size-derived counts to 2. */
#include <libgpu.h>

#undef setlen
#define PE_GPU_LEN(p, fallback) \
    _Generic((p), \
        POLY_F3*: 4, POLY_F4*: 5, POLY_FT3*: 7, POLY_FT4*: 9, POLY_G3*: 6, POLY_G4*: 8, POLY_GT3*: 9, POLY_GT4*: 12, \
        LINE_F2*: 3, LINE_F3*: 5, LINE_F4*: 6, LINE_G2*: 4, LINE_G3*: 7, LINE_G4*: 9, \
        TILE*: 3, TILE_1*: 2, TILE_8*: 2, TILE_16*: 2, SPRT*: 4, SPRT_8*: 3, SPRT_16*: 3, \
        DR_MODE*: ((fallback) <= 2 ? (fallback) : 2), DR_TPAGE*: 1, DR_AREA*: 2, DR_OFFSET*: 2, DR_MOVE*: 5, DR_ENV*: 15, \
        default: (fallback))
#define setlen(p, _len) (((P_TAG*)(p))->len = (u_char)PE_GPU_LEN(p, (_len)))
#endif
