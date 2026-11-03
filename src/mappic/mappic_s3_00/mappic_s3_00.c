#include "mappic/mappic.h"
#include "port/asset_bind.h"

#include <libgpu.h>

#include "common.h"

/// Identity transform and self-parented root for the Water tank area shape.
static TmdBone _gMappicS300WaterTankShapeSkeleton[1];
PE_ASSET_BIND("mappic_s2_00_model_00344_skeleton", _gMappicS300WaterTankShapeSkeleton);

/// Vertex count of the Water tank shape's sole part (ten vertices).
static u32 _gMappicS300WaterTankShapePartVerts[1];
PE_ASSET_BIND("mappic_s2_00_model_00344_partVerts", _gMappicS300WaterTankShapePartVerts);

/// Water tank fill vertices in integer model X/Z coordinates, with Y zero.
static SVECTOR _gMappicS300WaterTankShapeVerts[10];
PE_ASSET_BIND("mappic_s2_00_model_00344_verts", _gMappicS300WaterTankShapeVerts);

/// Four unlit quads, followed by two group ends and the stream end.
///
/// Each face stores packed u16 vertex byte offsets and a colour word. The map
/// uses the geometry to draw textured fills and ignores the stored colours.
static u32 _gMappicS300WaterTankShapeStream[18];
PE_ASSET_BIND("mappic_s2_00_model_00344_stream", _gMappicS300WaterTankShapeStream);

TmdSource gMappicS300WaterTankShape = {
    .bufferHalfBytes  = 4 * sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS300WaterTankShapeSkeleton),
    .partVertexCounts = _gMappicS300WaterTankShapePartVerts,
    .verts            = _gMappicS300WaterTankShapeVerts,
    .normals          = &_gMappicS300WaterTankShapeVerts[ARRAY_SIZE(_gMappicS300WaterTankShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS300WaterTankShapeSkeleton,
    .stream           = _gMappicS300WaterTankShapeStream,
};

/// Identity transform and self-parented root for the Motel room 5 shape.
static TmdBone _gMappicS300MotelRoom5ShapeSkeleton[1];
PE_ASSET_BIND("mappic_s2_02_model_00C48_002A8_skeleton", _gMappicS300MotelRoom5ShapeSkeleton);

/// Vertex count of the Motel room 5 shape's sole part (four vertices).
static u32 _gMappicS300MotelRoom5ShapePartVerts[1];
PE_ASSET_BIND("mappic_s2_02_model_00C48_002A8_partVerts", _gMappicS300MotelRoom5ShapePartVerts);

/// Motel room 5 fill vertices in integer model X/Z coordinates, with Y zero.
static SVECTOR _gMappicS300MotelRoom5ShapeVerts[4];
PE_ASSET_BIND("mappic_s2_02_model_00C48_002A8_verts", _gMappicS300MotelRoom5ShapeVerts);

/// One unlit quad, followed by two group ends and the stream end.
///
/// The face stores packed u16 vertex byte offsets and a colour word. The map
/// uses the geometry to draw a textured fill and ignores the stored colour.
static u32 _gMappicS300MotelRoom5ShapeStream[9];
PE_ASSET_BIND("mappic_s2_02_model_00C48_002A8_stream", _gMappicS300MotelRoom5ShapeStream);

TmdSource gMappicS300MotelRoom5Shape = {
    .bufferHalfBytes  = sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS300MotelRoom5ShapeSkeleton),
    .partVertexCounts = _gMappicS300MotelRoom5ShapePartVerts,
    .verts            = _gMappicS300MotelRoom5ShapeVerts,
    .normals          = &_gMappicS300MotelRoom5ShapeVerts[ARRAY_SIZE(_gMappicS300MotelRoom5ShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS300MotelRoom5ShapeSkeleton,
    .stream           = _gMappicS300MotelRoom5ShapeStream,
};

/// Identity transform and self-parented root for the motel balcony shape.
static TmdBone _gMappicS300MotelBalconyShapeSkeleton[1];
PE_ASSET_BIND("mappic_s2_00_model_0011C_skeleton", _gMappicS300MotelBalconyShapeSkeleton);

/// Vertex count of the motel balcony shape's sole part (twelve vertices).
static u32 _gMappicS300MotelBalconyShapePartVerts[1];
PE_ASSET_BIND("mappic_s2_00_model_0011C_partVerts", _gMappicS300MotelBalconyShapePartVerts);

/// Motel balcony fill vertices in integer model X/Z coordinates, with Y zero.
static SVECTOR _gMappicS300MotelBalconyShapeVerts[12];
PE_ASSET_BIND("mappic_s2_00_model_0011C_verts", _gMappicS300MotelBalconyShapeVerts);

/// Two unlit triangles and four unlit quads, followed by two group ends and the stream end.
///
/// Each face stores packed u16 vertex byte offsets and a colour word. The map
/// uses the geometry to draw textured fills and ignores the stored colours.
static u32 _gMappicS300MotelBalconyShapeStream[27];
PE_ASSET_BIND("mappic_s2_00_model_0011C_stream", _gMappicS300MotelBalconyShapeStream);

TmdSource gMappicS300MotelBalconyShape = {
    .bufferHalfBytes  = 2 * sizeof(POLY_F3) + 4 * sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS300MotelBalconyShapeSkeleton),
    .partVertexCounts = _gMappicS300MotelBalconyShapePartVerts,
    .verts            = _gMappicS300MotelBalconyShapeVerts,
    .normals          = &_gMappicS300MotelBalconyShapeVerts[ARRAY_SIZE(_gMappicS300MotelBalconyShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS300MotelBalconyShapeSkeleton,
    .stream           = _gMappicS300MotelBalconyShapeStream,
};

/// Identity transform and self-parented root for the Motel room 6 shape.
static TmdBone _gMappicS300MotelRoom6ShapeSkeleton[1];
PE_ASSET_BIND("mappic_s2_02_model_00C48_skeleton", _gMappicS300MotelRoom6ShapeSkeleton);

/// Vertex count of the Motel room 6 shape's sole part (four vertices).
static u32 _gMappicS300MotelRoom6ShapePartVerts[1];
PE_ASSET_BIND("mappic_s2_02_model_00C48_partVerts", _gMappicS300MotelRoom6ShapePartVerts);

/// Motel room 6's map outline in integer model X/Z coordinates, with Y zero.
static SVECTOR _gMappicS300MotelRoom6ShapeVerts[4];
PE_ASSET_BIND("mappic_s2_02_model_00C48_verts", _gMappicS300MotelRoom6ShapeVerts);

/// One unlit quad's packed vertex offsets and colour, followed by two group ends and the stream end.
static u32 _gMappicS300MotelRoom6ShapeStream[9];
PE_ASSET_BIND("mappic_s2_02_model_00C48_stream", _gMappicS300MotelRoom6ShapeStream);

TmdSource gMappicS300MotelRoom6Shape = {
    .bufferHalfBytes  = sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS300MotelRoom6ShapeSkeleton),
    .partVertexCounts = _gMappicS300MotelRoom6ShapePartVerts,
    .verts            = _gMappicS300MotelRoom6ShapeVerts,
    .normals          = &_gMappicS300MotelRoom6ShapeVerts[ARRAY_SIZE(_gMappicS300MotelRoom6ShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS300MotelRoom6ShapeSkeleton,
    .stream           = _gMappicS300MotelRoom6ShapeStream,
};

/// Identity transform and self-parented root for the Motel loft shape.
static TmdBone _gMappicS300MotelLoftShapeSkeleton[1];
PE_ASSET_BIND("mappic_s2_02_model_00C48_00218_skeleton", _gMappicS300MotelLoftShapeSkeleton);

/// Vertex count of the Motel loft shape's sole part (four vertices).
static u32 _gMappicS300MotelLoftShapePartVerts[1];
PE_ASSET_BIND("mappic_s2_02_model_00C48_00218_partVerts", _gMappicS300MotelLoftShapePartVerts);

/// Motel loft fill vertices in integer model X/Z coordinates, with Y zero.
static SVECTOR _gMappicS300MotelLoftShapeVerts[4];
PE_ASSET_BIND("mappic_s2_02_model_00C48_00218_verts", _gMappicS300MotelLoftShapeVerts);

/// One unlit quad, followed by two group ends and the stream end.
///
/// The face stores packed u16 vertex byte offsets and a colour word. The map
/// uses the geometry to draw a textured fill and ignores the stored colour.
static u32 _gMappicS300MotelLoftShapeStream[9];
PE_ASSET_BIND("mappic_s2_02_model_00C48_00218_stream", _gMappicS300MotelLoftShapeStream);

TmdSource gMappicS300MotelLoftShape = {
    .bufferHalfBytes  = sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS300MotelLoftShapeSkeleton),
    .partVertexCounts = _gMappicS300MotelLoftShapePartVerts,
    .verts            = _gMappicS300MotelLoftShapeVerts,
    .normals          = &_gMappicS300MotelLoftShapeVerts[ARRAY_SIZE(_gMappicS300MotelLoftShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS300MotelLoftShapeSkeleton,
    .stream           = _gMappicS300MotelLoftShapeStream,
};
