#include "mappic/mappic.h"
#include "port/asset_bind.h"

#include <libgpu.h>

#include "common.h"

/// Identity transform and self-parented root for the Water hole shape.
#ifdef PE_EMBED_ASSETS
static TmdBone _gMappicS303WaterHoleShapeSkeleton[] = {
#include "assets/mappic_s2_02_model_00CF8_000A8_skeleton.inc"
};
#else
static TmdBone _gMappicS303WaterHoleShapeSkeleton[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00CF8_000A8_skeleton", _gMappicS303WaterHoleShapeSkeleton);

/// Vertex count of the Water hole shape's sole part (eight vertices).
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS303WaterHoleShapePartVerts[] = {
#include "assets/mappic_s2_02_model_00CF8_000A8_partVerts.inc"
};
#else
static u32 _gMappicS303WaterHoleShapePartVerts[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00CF8_000A8_partVerts", _gMappicS303WaterHoleShapePartVerts);

/// Water hole's map outline in integer model X/Z coordinates, with Y zero.
#ifdef PE_EMBED_ASSETS
static SVECTOR _gMappicS303WaterHoleShapeVerts[] = {
#include "assets/mappic_s2_02_model_00CF8_000A8_verts.inc"
};
#else
static SVECTOR _gMappicS303WaterHoleShapeVerts[8];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00CF8_000A8_verts", _gMappicS303WaterHoleShapeVerts);

/// Three unlit quads' packed vertex byte offsets and colours, then two group ends and the stream end.
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS303WaterHoleShapeStream[] = {
#include "assets/mappic_s2_02_model_00CF8_000A8_stream.inc"
};
#else
static u32 _gMappicS303WaterHoleShapeStream[15];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00CF8_000A8_stream", _gMappicS303WaterHoleShapeStream);

TmdSource gMappicS303WaterHoleShape = {
    .bufferHalfBytes  = 3 * sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS303WaterHoleShapeSkeleton),
    .partVertexCounts = _gMappicS303WaterHoleShapePartVerts,
    .verts            = _gMappicS303WaterHoleShapeVerts,
    .normals          = &_gMappicS303WaterHoleShapeVerts[ARRAY_SIZE(_gMappicS303WaterHoleShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS303WaterHoleShapeSkeleton,
    .stream           = _gMappicS303WaterHoleShapeStream,
};

/// Initial identity pose of the Cellar shape's single self-parented root.
#ifdef PE_EMBED_ASSETS
static TmdBone _gMappicS303CellarShapeSkeleton[] = {
#include "assets/mappic_s4_00_model_0005C_00154_skeleton.inc"
};
#else
static TmdBone _gMappicS303CellarShapeSkeleton[1];
#endif
PE_ASSET_BIND("mappic_s4_00_model_0005C_00154_skeleton", _gMappicS303CellarShapeSkeleton);

/// Six vertices in the Cellar shape's sole part.
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS303CellarShapePartVerts[] = {
#include "assets/mappic_s4_00_model_0005C_00154_partVerts.inc"
};
#else
static u32 _gMappicS303CellarShapePartVerts[1];
#endif
PE_ASSET_BIND("mappic_s4_00_model_0005C_00154_partVerts", _gMappicS303CellarShapePartVerts);

/// Cellar area corners in integer model X/Z coordinates, with Y zero.
#ifdef PE_EMBED_ASSETS
static SVECTOR _gMappicS303CellarShapeVerts[] = {
#include "assets/mappic_s4_00_model_0005C_00154_verts.inc"
};
#else
static SVECTOR _gMappicS303CellarShapeVerts[6];
#endif
PE_ASSET_BIND("mappic_s4_00_model_0005C_00154_verts", _gMappicS303CellarShapeVerts);

/// Two unlit quads' packed vertex byte offsets and colours, then two group ends and the stream end.
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS303CellarShapeStream[] = {
#include "assets/mappic_s4_00_model_0005C_00154_stream.inc"
};
#else
static u32 _gMappicS303CellarShapeStream[12];
#endif
PE_ASSET_BIND("mappic_s4_00_model_0005C_00154_stream", _gMappicS303CellarShapeStream);

TmdSource gMappicS303CellarShape = {
    .bufferHalfBytes  = 2 * sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS303CellarShapeSkeleton),
    .partVertexCounts = _gMappicS303CellarShapePartVerts,
    .verts            = _gMappicS303CellarShapeVerts,
    .normals          = &_gMappicS303CellarShapeVerts[ARRAY_SIZE(_gMappicS303CellarShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS303CellarShapeSkeleton,
    .stream           = _gMappicS303CellarShapeStream,
};

/// Identity transform and self-parented root for the Underpass shape.
#ifdef PE_EMBED_ASSETS
static TmdBone _gMappicS303UnderpassShapeSkeleton[] = {
#include "assets/mappic_s2_03_model_001F0_00250_skeleton.inc"
};
#else
static TmdBone _gMappicS303UnderpassShapeSkeleton[1];
#endif
PE_ASSET_BIND("mappic_s2_03_model_001F0_00250_skeleton", _gMappicS303UnderpassShapeSkeleton);

/// Ten vertices in the Underpass shape's sole part.
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS303UnderpassShapePartVerts[] = {
#include "assets/mappic_s2_03_model_001F0_00250_partVerts.inc"
};
#else
static u32 _gMappicS303UnderpassShapePartVerts[1];
#endif
PE_ASSET_BIND("mappic_s2_03_model_001F0_00250_partVerts", _gMappicS303UnderpassShapePartVerts);

/// Underpass's map footprint in integer model X/Z coordinates, with Y zero.
#ifdef PE_EMBED_ASSETS
static SVECTOR _gMappicS303UnderpassShapeVerts[] = {
#include "assets/mappic_s2_03_model_001F0_00250_verts.inc"
};
#else
static SVECTOR _gMappicS303UnderpassShapeVerts[10];
#endif
PE_ASSET_BIND("mappic_s2_03_model_001F0_00250_verts", _gMappicS303UnderpassShapeVerts);

/// Packed command stream for the Underpass shape's two unlit triangles and three unlit quads.
///
/// Elements contain SVECTOR byte offsets and white colour; two group ends
/// precede the stream end. The map reads only the first group.
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS303UnderpassShapeStream[] = {
#include "assets/mappic_s2_03_model_001F0_00250_stream.inc"
};
#else
static u32 _gMappicS303UnderpassShapeStream[24];
#endif
PE_ASSET_BIND("mappic_s2_03_model_001F0_00250_stream", _gMappicS303UnderpassShapeStream);

TmdSource gMappicS303UnderpassShape = {
    .bufferHalfBytes  = 2 * sizeof(POLY_F3) + 3 * sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS303UnderpassShapeSkeleton),
    .partVertexCounts = _gMappicS303UnderpassShapePartVerts,
    .verts            = _gMappicS303UnderpassShapeVerts,
    .normals          = &_gMappicS303UnderpassShapeVerts[ARRAY_SIZE(_gMappicS303UnderpassShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS303UnderpassShapeSkeleton,
    .stream           = _gMappicS303UnderpassShapeStream,
};
