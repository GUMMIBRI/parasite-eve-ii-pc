#include "mappic/mappic.h"
#include "port/asset_bind.h"

#include <libgpu.h>

#include "common.h"

/// Identity transform and self-parented root for the Water hole shape.
static TmdBone _gMappicS203WaterHoleShapeSkeleton[1];
PE_ASSET_BIND("mappic_s2_02_model_00CF8_000A8_skeleton", _gMappicS203WaterHoleShapeSkeleton);

/// Vertex count of the Water hole shape's sole part (eight vertices).
static u32 _gMappicS203WaterHoleShapePartVerts[1];
PE_ASSET_BIND("mappic_s2_02_model_00CF8_000A8_partVerts", _gMappicS203WaterHoleShapePartVerts);

/// Water hole's map outline in integer model X/Z coordinates, with Y zero.
static SVECTOR _gMappicS203WaterHoleShapeVerts[8];
PE_ASSET_BIND("mappic_s2_02_model_00CF8_000A8_verts", _gMappicS203WaterHoleShapeVerts);

/// Three unlit quads' packed vertex byte offsets and colours, then two group ends and the stream end.
static u32 _gMappicS203WaterHoleShapeStream[15];
PE_ASSET_BIND("mappic_s2_02_model_00CF8_000A8_stream", _gMappicS203WaterHoleShapeStream);

TmdSource gMappicS203WaterHoleShape = {
    .bufferHalfBytes  = 3 * sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS203WaterHoleShapeSkeleton),
    .partVertexCounts = _gMappicS203WaterHoleShapePartVerts,
    .verts            = _gMappicS203WaterHoleShapeVerts,
    .normals          = &_gMappicS203WaterHoleShapeVerts[ARRAY_SIZE(_gMappicS203WaterHoleShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS203WaterHoleShapeSkeleton,
    .stream           = _gMappicS203WaterHoleShapeStream,
};

/// Initial identity pose of the Cellar shape's single self-parented root.
static TmdBone _gMappicS203CellarShapeSkeleton[1];
PE_ASSET_BIND("mappic_s4_00_model_0005C_00154_skeleton", _gMappicS203CellarShapeSkeleton);

/// Six vertices in the Cellar shape's sole part.
static u32 _gMappicS203CellarShapePartVerts[1];
PE_ASSET_BIND("mappic_s4_00_model_0005C_00154_partVerts", _gMappicS203CellarShapePartVerts);

/// Cellar area corners in integer model X/Z coordinates, with Y zero.
static SVECTOR _gMappicS203CellarShapeVerts[6];
PE_ASSET_BIND("mappic_s4_00_model_0005C_00154_verts", _gMappicS203CellarShapeVerts);

/// Two unlit quads' packed vertex byte offsets and colours, then two group ends and the stream end.
static u32 _gMappicS203CellarShapeStream[12];
PE_ASSET_BIND("mappic_s4_00_model_0005C_00154_stream", _gMappicS203CellarShapeStream);

TmdSource gMappicS203CellarShape = {
    .bufferHalfBytes  = 2 * sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS203CellarShapeSkeleton),
    .partVertexCounts = _gMappicS203CellarShapePartVerts,
    .verts            = _gMappicS203CellarShapeVerts,
    .normals          = &_gMappicS203CellarShapeVerts[ARRAY_SIZE(_gMappicS203CellarShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS203CellarShapeSkeleton,
    .stream           = _gMappicS203CellarShapeStream,
};

/// Identity transform and self-parented root for the Underpass shape.
static TmdBone _gMappicS203UnderpassShapeSkeleton[1];
PE_ASSET_BIND("mappic_s2_03_model_001F0_skeleton", _gMappicS203UnderpassShapeSkeleton);

/// Vertex count of the Underpass shape's sole part (ten vertices).
static u32 _gMappicS203UnderpassShapePartVerts[1];
PE_ASSET_BIND("mappic_s2_03_model_001F0_partVerts", _gMappicS203UnderpassShapePartVerts);

/// Underpass's map footprint in integer model X/Z coordinates, with Y zero.
static SVECTOR _gMappicS203UnderpassShapeVerts[10];
PE_ASSET_BIND("mappic_s2_03_model_001F0_verts", _gMappicS203UnderpassShapeVerts);

/// Two unlit triangles and three unlit quads, with packed vertex byte offsets and white colour, then two group ends and the stream end.
static u32 _gMappicS203UnderpassShapeStream[24];
PE_ASSET_BIND("mappic_s2_03_model_001F0_stream", _gMappicS203UnderpassShapeStream);

TmdSource gMappicS203UnderpassShape = {
    .bufferHalfBytes  = 2 * sizeof(POLY_F3) + 3 * sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS203UnderpassShapeSkeleton),
    .partVertexCounts = _gMappicS203UnderpassShapePartVerts,
    .verts            = _gMappicS203UnderpassShapeVerts,
    .normals          = &_gMappicS203UnderpassShapeVerts[ARRAY_SIZE(_gMappicS203UnderpassShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS203UnderpassShapeSkeleton,
    .stream           = _gMappicS203UnderpassShapeStream,
};
