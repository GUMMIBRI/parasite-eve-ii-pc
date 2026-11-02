#include "mappic/mappic.h"
#include "port/asset_bind.h"

#include <libgpu.h>

#include "common.h"

/// Identity transform and self-parented root for the Parking garage shape.
#ifdef PE_EMBED_ASSETS
static TmdBone _gMappicS503ParkingGarageShapeSkeleton[] = {
#include "assets/mappic_s2_02_model_00C48_00070_mappic_s5_03_skeleton.inc"
};
#else
static TmdBone _gMappicS503ParkingGarageShapeSkeleton[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_00070_mappic_s5_03_skeleton", _gMappicS503ParkingGarageShapeSkeleton);

/// Vertex count of the Parking garage shape's sole part (four vertices).
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS503ParkingGarageShapePartVerts[] = {
#include "assets/mappic_s2_02_model_00C48_00070_mappic_s5_03_partVerts.inc"
};
#else
static u32 _gMappicS503ParkingGarageShapePartVerts[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_00070_mappic_s5_03_partVerts", _gMappicS503ParkingGarageShapePartVerts);

/// Parking garage fill vertices in integer model X/Z coordinates, with Y zero.
#ifdef PE_EMBED_ASSETS
static SVECTOR _gMappicS503ParkingGarageShapeVerts[] = {
#include "assets/mappic_s2_02_model_00C48_00070_mappic_s5_03_verts.inc"
};
#else
static SVECTOR _gMappicS503ParkingGarageShapeVerts[4];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_00070_mappic_s5_03_verts", _gMappicS503ParkingGarageShapeVerts);

/// One unlit quad, followed by two group ends and the stream end.
///
/// The face stores packed u16 vertex byte offsets and a colour word. The map
/// uses the geometry to draw a textured fill and ignores the stored colour.
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS503ParkingGarageShapeStream[] = {
#include "assets/mappic_s2_02_model_00C48_00070_mappic_s5_03_stream.inc"
};
#else
static u32 _gMappicS503ParkingGarageShapeStream[9];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_00070_mappic_s5_03_stream", _gMappicS503ParkingGarageShapeStream);

TmdSource gMappicS503ParkingGarageShape = {
    .bufferHalfBytes  = sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS503ParkingGarageShapeSkeleton),
    .partVertexCounts = _gMappicS503ParkingGarageShapePartVerts,
    .verts            = _gMappicS503ParkingGarageShapeVerts,
    .normals          = &_gMappicS503ParkingGarageShapeVerts[ARRAY_SIZE(_gMappicS503ParkingGarageShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS503ParkingGarageShapeSkeleton,
    .stream           = _gMappicS503ParkingGarageShapeStream,
};

/// Identity transform and self-parented root for the Vehicular airlock shape.
#ifdef PE_EMBED_ASSETS
static TmdBone _gMappicS503VehicularAirlockShapeSkeleton[] = {
#include "assets/mappic_s2_02_model_00C48_00100_mappic_s5_03_skeleton.inc"
};
#else
static TmdBone _gMappicS503VehicularAirlockShapeSkeleton[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_00100_mappic_s5_03_skeleton", _gMappicS503VehicularAirlockShapeSkeleton);

/// Vertex count of the Vehicular airlock shape's sole part (four vertices).
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS503VehicularAirlockShapePartVerts[] = {
#include "assets/mappic_s2_02_model_00C48_00100_mappic_s5_03_partVerts.inc"
};
#else
static u32 _gMappicS503VehicularAirlockShapePartVerts[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_00100_mappic_s5_03_partVerts", _gMappicS503VehicularAirlockShapePartVerts);

/// Vehicular airlock fill vertices in integer model X/Z coordinates, with Y zero.
#ifdef PE_EMBED_ASSETS
static SVECTOR _gMappicS503VehicularAirlockShapeVerts[] = {
#include "assets/mappic_s2_02_model_00C48_00100_mappic_s5_03_verts.inc"
};
#else
static SVECTOR _gMappicS503VehicularAirlockShapeVerts[4];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_00100_mappic_s5_03_verts", _gMappicS503VehicularAirlockShapeVerts);

/// One unlit quad, followed by two group ends and the stream end.
///
/// The face stores packed u16 vertex byte offsets and a colour word. The map
/// uses the geometry to draw a textured fill and ignores the stored colour.
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS503VehicularAirlockShapeStream[] = {
#include "assets/mappic_s2_02_model_00C48_00100_mappic_s5_03_stream.inc"
};
#else
static u32 _gMappicS503VehicularAirlockShapeStream[9];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_00100_mappic_s5_03_stream", _gMappicS503VehicularAirlockShapeStream);

TmdSource gMappicS503VehicularAirlockShape = {
    .bufferHalfBytes  = sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS503VehicularAirlockShapeSkeleton),
    .partVertexCounts = _gMappicS503VehicularAirlockShapePartVerts,
    .verts            = _gMappicS503VehicularAirlockShapeVerts,
    .normals          = &_gMappicS503VehicularAirlockShapeVerts[ARRAY_SIZE(_gMappicS503VehicularAirlockShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS503VehicularAirlockShapeSkeleton,
    .stream           = _gMappicS503VehicularAirlockShapeStream,
};

/// Identity transform and self-parented root for the Bulwark shape.
#ifdef PE_EMBED_ASSETS
static TmdBone _gMappicS503BulwarkShapeSkeleton[] = {
#include "assets/mappic_s4_06_model_00214_001E0_skeleton.inc"
};
#else
static TmdBone _gMappicS503BulwarkShapeSkeleton[1];
#endif
PE_ASSET_BIND("mappic_s4_06_model_00214_001E0_skeleton", _gMappicS503BulwarkShapeSkeleton);

/// Vertex count of the Bulwark shape's sole part (eight vertices).
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS503BulwarkShapePartVerts[] = {
#include "assets/mappic_s4_06_model_00214_001E0_partVerts.inc"
};
#else
static u32 _gMappicS503BulwarkShapePartVerts[1];
#endif
PE_ASSET_BIND("mappic_s4_06_model_00214_001E0_partVerts", _gMappicS503BulwarkShapePartVerts);

/// Bulwark fill vertices in integer model X/Z coordinates, with Y zero.
#ifdef PE_EMBED_ASSETS
static SVECTOR _gMappicS503BulwarkShapeVerts[] = {
#include "assets/mappic_s4_06_model_00214_001E0_verts.inc"
};
#else
static SVECTOR _gMappicS503BulwarkShapeVerts[8];
#endif
PE_ASSET_BIND("mappic_s4_06_model_00214_001E0_verts", _gMappicS503BulwarkShapeVerts);

/// Two unlit triangles and two unlit quads, followed by two group ends and the stream end.
///
/// Each face stores packed u16 vertex byte offsets and a colour word. The map
/// uses the geometry to draw textured fills and ignores the stored colours.
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS503BulwarkShapeStream[] = {
#include "assets/mappic_s4_06_model_00214_001E0_stream.inc"
};
#else
static u32 _gMappicS503BulwarkShapeStream[21];
#endif
PE_ASSET_BIND("mappic_s4_06_model_00214_001E0_stream", _gMappicS503BulwarkShapeStream);

TmdSource gMappicS503BulwarkShape = {
    .bufferHalfBytes  = 2 * sizeof(POLY_F3) + 2 * sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS503BulwarkShapeSkeleton),
    .partVertexCounts = _gMappicS503BulwarkShapePartVerts,
    .verts            = _gMappicS503BulwarkShapeVerts,
    .normals          = &_gMappicS503BulwarkShapeVerts[ARRAY_SIZE(_gMappicS503BulwarkShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS503BulwarkShapeSkeleton,
    .stream           = _gMappicS503BulwarkShapeStream,
};

/// Identity transform and self-parented root for the Heliport shape.
#ifdef PE_EMBED_ASSETS
static TmdBone _gMappicS503HeliportShapeSkeleton[] = {
#include "assets/mappic_s2_02_model_00910_002C0_skeleton.inc"
};
#else
static TmdBone _gMappicS503HeliportShapeSkeleton[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00910_002C0_skeleton", _gMappicS503HeliportShapeSkeleton);

/// Vertex count of the Heliport shape's sole part (eight vertices).
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS503HeliportShapePartVerts[] = {
#include "assets/mappic_s2_02_model_00910_002C0_partVerts.inc"
};
#else
static u32 _gMappicS503HeliportShapePartVerts[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00910_002C0_partVerts", _gMappicS503HeliportShapePartVerts);

/// Heliport fill vertices in integer model X/Z coordinates, with Y zero.
#ifdef PE_EMBED_ASSETS
static SVECTOR _gMappicS503HeliportShapeVerts[] = {
#include "assets/mappic_s2_02_model_00910_002C0_verts.inc"
};
#else
static SVECTOR _gMappicS503HeliportShapeVerts[8];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00910_002C0_verts", _gMappicS503HeliportShapeVerts);

/// Two unlit triangles and two unlit quads, followed by two group ends and the stream end.
///
/// Each face stores packed u16 vertex byte offsets and a colour word. The map
/// uses the geometry to draw textured fills and ignores the stored colours.
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS503HeliportShapeStream[] = {
#include "assets/mappic_s2_02_model_00910_002C0_stream.inc"
};
#else
static u32 _gMappicS503HeliportShapeStream[21];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00910_002C0_stream", _gMappicS503HeliportShapeStream);

TmdSource gMappicS503HeliportShape = {
    .bufferHalfBytes  = 2 * sizeof(POLY_F3) + 2 * sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS503HeliportShapeSkeleton),
    .partVertexCounts = _gMappicS503HeliportShapePartVerts,
    .verts            = _gMappicS503HeliportShapeVerts,
    .normals          = &_gMappicS503HeliportShapeVerts[ARRAY_SIZE(_gMappicS503HeliportShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS503HeliportShapeSkeleton,
    .stream           = _gMappicS503HeliportShapeStream,
};

/// Identity transform and self-parented root for the Airlock shape.
#ifdef PE_EMBED_ASSETS
static TmdBone _gMappicS503AirlockShapeSkeleton[] = {
#include "assets/mappic_s2_02_model_00CF8_00388_skeleton.inc"
};
#else
static TmdBone _gMappicS503AirlockShapeSkeleton[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00CF8_00388_skeleton", _gMappicS503AirlockShapeSkeleton);

/// Vertex count of the Airlock shape's sole part (eight vertices).
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS503AirlockShapePartVerts[] = {
#include "assets/mappic_s2_02_model_00CF8_00388_partVerts.inc"
};
#else
static u32 _gMappicS503AirlockShapePartVerts[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00CF8_00388_partVerts", _gMappicS503AirlockShapePartVerts);

/// Airlock fill vertices in integer model X/Z coordinates, with Y zero.
#ifdef PE_EMBED_ASSETS
static SVECTOR _gMappicS503AirlockShapeVerts[] = {
#include "assets/mappic_s2_02_model_00CF8_00388_verts.inc"
};
#else
static SVECTOR _gMappicS503AirlockShapeVerts[8];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00CF8_00388_verts", _gMappicS503AirlockShapeVerts);

/// Three unlit quads, followed by two group ends and the stream end.
///
/// Each face stores packed u16 vertex byte offsets and a colour word. The map
/// uses the geometry to draw textured fills and ignores the stored colours.
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS503AirlockShapeStream[] = {
#include "assets/mappic_s2_02_model_00CF8_00388_stream.inc"
};
#else
static u32 _gMappicS503AirlockShapeStream[15];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00CF8_00388_stream", _gMappicS503AirlockShapeStream);

TmdSource gMappicS503AirlockShape = {
    .bufferHalfBytes  = 3 * sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS503AirlockShapeSkeleton),
    .partVertexCounts = _gMappicS503AirlockShapePartVerts,
    .verts            = _gMappicS503AirlockShapeVerts,
    .normals          = &_gMappicS503AirlockShapeVerts[ARRAY_SIZE(_gMappicS503AirlockShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS503AirlockShapeSkeleton,
    .stream           = _gMappicS503AirlockShapeStream,
};

/// Identity transform and self-parented root for the Guardroom shape.
#ifdef PE_EMBED_ASSETS
static TmdBone _gMappicS503GuardroomShapeSkeleton[] = {
#include "assets/mappic_s2_02_model_00C48_00418_skeleton.inc"
};
#else
static TmdBone _gMappicS503GuardroomShapeSkeleton[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_00418_skeleton", _gMappicS503GuardroomShapeSkeleton);

/// Vertex count of the Guardroom shape's sole part (four vertices).
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS503GuardroomShapePartVerts[] = {
#include "assets/mappic_s2_02_model_00C48_00418_partVerts.inc"
};
#else
static u32 _gMappicS503GuardroomShapePartVerts[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_00418_partVerts", _gMappicS503GuardroomShapePartVerts);

/// Guardroom fill vertices in integer model X/Z coordinates, with Y zero.
#ifdef PE_EMBED_ASSETS
static SVECTOR _gMappicS503GuardroomShapeVerts[] = {
#include "assets/mappic_s2_02_model_00C48_00418_verts.inc"
};
#else
static SVECTOR _gMappicS503GuardroomShapeVerts[4];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_00418_verts", _gMappicS503GuardroomShapeVerts);

/// One unlit quad, followed by two group ends and the stream end.
///
/// The face stores packed u16 vertex byte offsets and a colour word. The map
/// uses the geometry to draw a textured fill and ignores the stored colour.
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS503GuardroomShapeStream[] = {
#include "assets/mappic_s2_02_model_00C48_00418_stream.inc"
};
#else
static u32 _gMappicS503GuardroomShapeStream[9];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_00418_stream", _gMappicS503GuardroomShapeStream);

TmdSource gMappicS503GuardroomShape = {
    .bufferHalfBytes  = sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS503GuardroomShapeSkeleton),
    .partVertexCounts = _gMappicS503GuardroomShapePartVerts,
    .verts            = _gMappicS503GuardroomShapeVerts,
    .normals          = &_gMappicS503GuardroomShapeVerts[ARRAY_SIZE(_gMappicS503GuardroomShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS503GuardroomShapeSkeleton,
    .stream           = _gMappicS503GuardroomShapeStream,
};
