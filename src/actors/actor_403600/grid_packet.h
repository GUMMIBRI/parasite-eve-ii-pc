#ifndef ACTOR_403600_GRID_PACKET_H
#define ACTOR_403600_GRID_PACKET_H
#include <stddef.h>
#include <libgpu.h>
#include "types.h"
#include "common.h"

/// Position and texture coordinate of one vertex of a grid quad, laid out as
/// every vertex of a POLY_FT4 is.
typedef struct {
    s16 x; // Screen position, relative to the centre of the screen
    s16 y;
    u8  u; // Texel of the frame copy drawn at the vertex; `u` is relative to the vertex's page
    u8  v;
} _Actor403600GridVertex;
STATIC_ASSERT_SIZEOF(_Actor403600GridVertex, 6);

/// A quad of the grids this package distorts the screen with, in the layout of
/// a POLY_FT4.
///
/// Its texture is the copy of the frame the grid is drawn over. That copy is
/// 320 pixels wide and a texture page reaches 256, so a vertex's U is kept
/// relative to a page shifted right by its `pageN`, held in what a POLY_FT4
/// leaves as padding. Once all four vertices are placed they are brought onto
/// one page, which `tpage` names. `clut` is never set: the copy is direct
/// colour.
typedef struct {
    O_TAG;
    u_char                 r0, g0, b0, code;
    _Actor403600GridVertex vertex0;
    u_short                clut;
    _Actor403600GridVertex vertex1;
    u_short                tpage;
    _Actor403600GridVertex vertex2;
    u_char                 page0, page1; // Shift of the page `vertex0` and `vertex1` measure U from (0 or 0x40 pixels)
    _Actor403600GridVertex vertex3;
    u_char                 page2, page3; // The same for `vertex2` and `vertex3`
} _Actor403600GridQuad;
STATIC_ASSERT_SIZEOF(_Actor403600GridQuad, sizeof(POLY_FT4));
#ifdef __psyz
_Static_assert(sizeof(_Actor403600GridQuad)==sizeof(POLY_FT4), "Ripple packet must match host GPU layout");
_Static_assert(offsetof(_Actor403600GridQuad,code)==offsetof(POLY_FT4,code), "Ripple command must follow full GPU tag");
#endif

#endif
