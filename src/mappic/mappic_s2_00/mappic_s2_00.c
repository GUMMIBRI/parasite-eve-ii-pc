#include "mappic/mappic.h"
#include "port/asset_bind.h"

#include <libgpu.h>

#include "common.h"

/// Identity transform and self-parented root for the Motel room 6 shape.
#ifdef PE_EMBED_ASSETS
static TmdBone _gMappicS200MotelRoom6ShapeSkeleton[] = {
#include "assets/mappic_s2_02_model_00C48_skeleton.inc"
};
#else
static TmdBone _gMappicS200MotelRoom6ShapeSkeleton[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_skeleton", _gMappicS200MotelRoom6ShapeSkeleton);

/// Vertex count of the Motel room 6 shape's sole part (four vertices).
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS200MotelRoom6ShapePartVerts[] = {
#include "assets/mappic_s2_02_model_00C48_partVerts.inc"
};
#else
static u32 _gMappicS200MotelRoom6ShapePartVerts[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_partVerts", _gMappicS200MotelRoom6ShapePartVerts);

/// Motel room 6's map outline in integer model X/Z coordinates, with Y zero.
#ifdef PE_EMBED_ASSETS
static SVECTOR _gMappicS200MotelRoom6ShapeVerts[] = {
#include "assets/mappic_s2_02_model_00C48_verts.inc"
};
#else
static SVECTOR _gMappicS200MotelRoom6ShapeVerts[4];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_verts", _gMappicS200MotelRoom6ShapeVerts);

/// One unlit quad's packed vertex offsets and colour, followed by two group ends and the stream end.
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS200MotelRoom6ShapeStream[] = {
#include "assets/mappic_s2_02_model_00C48_stream.inc"
};
#else
static u32 _gMappicS200MotelRoom6ShapeStream[9];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_stream", _gMappicS200MotelRoom6ShapeStream);

TmdSource gMappicS200MotelRoom6Shape = {
    .bufferHalfBytes  = sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS200MotelRoom6ShapeSkeleton),
    .partVertexCounts = _gMappicS200MotelRoom6ShapePartVerts,
    .verts            = _gMappicS200MotelRoom6ShapeVerts,
    .normals          = &_gMappicS200MotelRoom6ShapeVerts[ARRAY_SIZE(_gMappicS200MotelRoom6ShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS200MotelRoom6ShapeSkeleton,
    .stream           = _gMappicS200MotelRoom6ShapeStream,
};

/// Identity transform and self-parented root for the motel balcony shape.
#ifdef PE_EMBED_ASSETS
static TmdBone _gMappicS200MotelBalconyShapeSkeleton[] = {
#include "assets/mappic_s2_00_model_0011C_skeleton.inc"
};
#else
static TmdBone _gMappicS200MotelBalconyShapeSkeleton[1];
#endif
PE_ASSET_BIND("mappic_s2_00_model_0011C_skeleton", _gMappicS200MotelBalconyShapeSkeleton);

/// Vertex count of the motel balcony shape's sole part (twelve vertices).
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS200MotelBalconyShapePartVerts[] = {
#include "assets/mappic_s2_00_model_0011C_partVerts.inc"
};
#else
static u32 _gMappicS200MotelBalconyShapePartVerts[1];
#endif
PE_ASSET_BIND("mappic_s2_00_model_0011C_partVerts", _gMappicS200MotelBalconyShapePartVerts);

/// Motel balcony fill vertices in integer model X/Z coordinates, with Y zero.
#ifdef PE_EMBED_ASSETS
static SVECTOR _gMappicS200MotelBalconyShapeVerts[] = {
#include "assets/mappic_s2_00_model_0011C_verts.inc"
};
#else
static SVECTOR _gMappicS200MotelBalconyShapeVerts[12];
#endif
PE_ASSET_BIND("mappic_s2_00_model_0011C_verts", _gMappicS200MotelBalconyShapeVerts);

/// Two unlit triangles and four unlit quads, followed by two group ends and the stream end.
///
/// Each face stores packed u16 vertex byte offsets and a colour word. The map
/// uses the geometry to draw textured fills and ignores the stored colours.
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS200MotelBalconyShapeStream[] = {
#include "assets/mappic_s2_00_model_0011C_stream.inc"
};
#else
static u32 _gMappicS200MotelBalconyShapeStream[27];
#endif
PE_ASSET_BIND("mappic_s2_00_model_0011C_stream", _gMappicS200MotelBalconyShapeStream);

TmdSource gMappicS200MotelBalconyShape = {
    .bufferHalfBytes  = 2 * sizeof(POLY_F3) + 4 * sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS200MotelBalconyShapeSkeleton),
    .partVertexCounts = _gMappicS200MotelBalconyShapePartVerts,
    .verts            = _gMappicS200MotelBalconyShapeVerts,
    .normals          = &_gMappicS200MotelBalconyShapeVerts[ARRAY_SIZE(_gMappicS200MotelBalconyShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS200MotelBalconyShapeSkeleton,
    .stream           = _gMappicS200MotelBalconyShapeStream,
};

/// Identity transform and self-parented root for the Motel loft shape.
#ifdef PE_EMBED_ASSETS
static TmdBone _gMappicS200MotelLoftShapeSkeleton[] = {
#include "assets/mappic_s2_02_model_00C48_00218_skeleton.inc"
};
#else
static TmdBone _gMappicS200MotelLoftShapeSkeleton[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_00218_skeleton", _gMappicS200MotelLoftShapeSkeleton);

/// Vertex count of the Motel loft shape's sole part (four vertices).
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS200MotelLoftShapePartVerts[] = {
#include "assets/mappic_s2_02_model_00C48_00218_partVerts.inc"
};
#else
static u32 _gMappicS200MotelLoftShapePartVerts[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_00218_partVerts", _gMappicS200MotelLoftShapePartVerts);

/// Motel loft fill vertices in integer model X/Z coordinates, with Y zero.
#ifdef PE_EMBED_ASSETS
static SVECTOR _gMappicS200MotelLoftShapeVerts[] = {
#include "assets/mappic_s2_02_model_00C48_00218_verts.inc"
};
#else
static SVECTOR _gMappicS200MotelLoftShapeVerts[4];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_00218_verts", _gMappicS200MotelLoftShapeVerts);

/// One unlit quad, followed by two group ends and the stream end.
///
/// The face stores packed u16 vertex byte offsets and a colour word. The map
/// uses the geometry to draw a textured fill and ignores the stored colour.
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS200MotelLoftShapeStream[] = {
#include "assets/mappic_s2_02_model_00C48_00218_stream.inc"
};
#else
static u32 _gMappicS200MotelLoftShapeStream[9];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_00218_stream", _gMappicS200MotelLoftShapeStream);

TmdSource gMappicS200MotelLoftShape = {
    .bufferHalfBytes  = sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS200MotelLoftShapeSkeleton),
    .partVertexCounts = _gMappicS200MotelLoftShapePartVerts,
    .verts            = _gMappicS200MotelLoftShapeVerts,
    .normals          = &_gMappicS200MotelLoftShapeVerts[ARRAY_SIZE(_gMappicS200MotelLoftShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS200MotelLoftShapeSkeleton,
    .stream           = _gMappicS200MotelLoftShapeStream,
};

/// Identity transform and self-parented root for the Motel room 5 shape.
#ifdef PE_EMBED_ASSETS
static TmdBone _gMappicS200MotelRoom5ShapeSkeleton[] = {
#include "assets/mappic_s2_02_model_00C48_002A8_skeleton.inc"
};
#else
static TmdBone _gMappicS200MotelRoom5ShapeSkeleton[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_002A8_skeleton", _gMappicS200MotelRoom5ShapeSkeleton);

/// Vertex count of the Motel room 5 shape's sole part (four vertices).
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS200MotelRoom5ShapePartVerts[] = {
#include "assets/mappic_s2_02_model_00C48_002A8_partVerts.inc"
};
#else
static u32 _gMappicS200MotelRoom5ShapePartVerts[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_002A8_partVerts", _gMappicS200MotelRoom5ShapePartVerts);

/// Motel room 5 fill vertices in integer model X/Z coordinates, with Y zero.
#ifdef PE_EMBED_ASSETS
static SVECTOR _gMappicS200MotelRoom5ShapeVerts[] = {
#include "assets/mappic_s2_02_model_00C48_002A8_verts.inc"
};
#else
static SVECTOR _gMappicS200MotelRoom5ShapeVerts[4];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_002A8_verts", _gMappicS200MotelRoom5ShapeVerts);

/// One unlit quad, followed by two group ends and the stream end.
///
/// The face stores packed u16 vertex byte offsets and a colour word. The map
/// uses the geometry to draw a textured fill and ignores the stored colour.
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS200MotelRoom5ShapeStream[] = {
#include "assets/mappic_s2_02_model_00C48_002A8_stream.inc"
};
#else
static u32 _gMappicS200MotelRoom5ShapeStream[9];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_002A8_stream", _gMappicS200MotelRoom5ShapeStream);

TmdSource gMappicS200MotelRoom5Shape = {
    .bufferHalfBytes  = sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS200MotelRoom5ShapeSkeleton),
    .partVertexCounts = _gMappicS200MotelRoom5ShapePartVerts,
    .verts            = _gMappicS200MotelRoom5ShapeVerts,
    .normals          = &_gMappicS200MotelRoom5ShapeVerts[ARRAY_SIZE(_gMappicS200MotelRoom5ShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS200MotelRoom5ShapeSkeleton,
    .stream           = _gMappicS200MotelRoom5ShapeStream,
};

/// Identity transform and self-parented root for the Water tank area shape.
#ifdef PE_EMBED_ASSETS
static TmdBone _gMappicS200WaterTankShapeSkeleton[] = {
#include "assets/mappic_s2_00_model_00344_skeleton.inc"
};
#else
static TmdBone _gMappicS200WaterTankShapeSkeleton[1];
#endif
PE_ASSET_BIND("mappic_s2_00_model_00344_skeleton", _gMappicS200WaterTankShapeSkeleton);

/// Vertex count of the Water tank shape's sole part (ten vertices).
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS200WaterTankShapePartVerts[] = {
#include "assets/mappic_s2_00_model_00344_partVerts.inc"
};
#else
static u32 _gMappicS200WaterTankShapePartVerts[1];
#endif
PE_ASSET_BIND("mappic_s2_00_model_00344_partVerts", _gMappicS200WaterTankShapePartVerts);

/// Water tank fill vertices in integer model X/Z coordinates, with Y zero.
#ifdef PE_EMBED_ASSETS
static SVECTOR _gMappicS200WaterTankShapeVerts[] = {
#include "assets/mappic_s2_00_model_00344_verts.inc"
};
#else
static SVECTOR _gMappicS200WaterTankShapeVerts[10];
#endif
PE_ASSET_BIND("mappic_s2_00_model_00344_verts", _gMappicS200WaterTankShapeVerts);

/// Four unlit quads, followed by two group ends and the stream end.
///
/// Each face stores packed u16 vertex byte offsets and a colour word. The map
/// uses the geometry to draw textured fills and ignores the stored colours.
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS200WaterTankShapeStream[] = {
#include "assets/mappic_s2_00_model_00344_stream.inc"
};
#else
static u32 _gMappicS200WaterTankShapeStream[18];
#endif
PE_ASSET_BIND("mappic_s2_00_model_00344_stream", _gMappicS200WaterTankShapeStream);

TmdSource gMappicS200WaterTankShape = {
    .bufferHalfBytes  = 4 * sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS200WaterTankShapeSkeleton),
    .partVertexCounts = _gMappicS200WaterTankShapePartVerts,
    .verts            = _gMappicS200WaterTankShapeVerts,
    .normals          = &_gMappicS200WaterTankShapeVerts[ARRAY_SIZE(_gMappicS200WaterTankShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS200WaterTankShapeSkeleton,
    .stream           = _gMappicS200WaterTankShapeStream,
};
