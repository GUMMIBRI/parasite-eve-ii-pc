#include "mappic/mappic.h"
#include "port/asset_bind.h"

#include <libgpu.h>

#include "common.h"

/// Identity transform and self-parented root for the Reservoir shape.
static TmdBone _gMappicS406ReservoirShapeSkeleton[1];
PE_ASSET_BIND("mappic_s2_02_model_00910_000C0_mappic_s4_06_skeleton", _gMappicS406ReservoirShapeSkeleton);

/// Vertex count of the Reservoir shape's sole part (eight vertices).
static u32 _gMappicS406ReservoirShapePartVerts[1];
PE_ASSET_BIND("mappic_s2_02_model_00910_000C0_mappic_s4_06_partVerts", _gMappicS406ReservoirShapePartVerts);

/// Reservoir's map footprint in integer model X/Z coordinates, with Y zero.
static SVECTOR _gMappicS406ReservoirShapeVerts[8];
PE_ASSET_BIND("mappic_s2_02_model_00910_000C0_mappic_s4_06_verts", _gMappicS406ReservoirShapeVerts);

/// Packed command stream for the Reservoir shape's two unlit triangles and two quads.
///
/// Three words per face hold packed SVECTOR byte offsets and white colour.
/// Two group ends precede the stream end; the map reads only the first group.
static u32 _gMappicS406ReservoirShapeStream[21];
PE_ASSET_BIND("mappic_s2_02_model_00910_000C0_mappic_s4_06_stream", _gMappicS406ReservoirShapeStream);

TmdSource gMappicS406ReservoirShape = {
    .bufferHalfBytes  = 2 * sizeof(POLY_F3) + 2 * sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS406ReservoirShapeSkeleton),
    .partVertexCounts = _gMappicS406ReservoirShapePartVerts,
    .verts            = _gMappicS406ReservoirShapeVerts,
    .normals          = &_gMappicS406ReservoirShapeVerts[ARRAY_SIZE(_gMappicS406ReservoirShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS406ReservoirShapeSkeleton,
    .stream           = _gMappicS406ReservoirShapeStream,
};

/// Identity transform and self-parented root for the Upper sewer shape.
static TmdBone _gMappicS406UpperSewerShapeSkeleton[1];
PE_ASSET_BIND("mappic_s4_06_model_0014C_00188_skeleton", _gMappicS406UpperSewerShapeSkeleton);

/// Vertex count of the Upper sewer shape's sole part (eight vertices).
static u32 _gMappicS406UpperSewerShapePartVerts[1];
PE_ASSET_BIND("mappic_s4_06_model_0014C_00188_partVerts", _gMappicS406UpperSewerShapePartVerts);

/// Upper sewer's map footprint in integer model X/Z coordinates, with Y zero.
static SVECTOR _gMappicS406UpperSewerShapeVerts[8];
PE_ASSET_BIND("mappic_s4_06_model_0014C_00188_verts", _gMappicS406UpperSewerShapeVerts);

/// Packed command stream for the Upper sewer shape's three unlit quads.
///
/// Three words per face hold packed SVECTOR byte offsets and white colour.
/// Two group ends precede the stream end; the map reads only the first group.
static u32 _gMappicS406UpperSewerShapeStream[15];
PE_ASSET_BIND("mappic_s4_06_model_0014C_00188_stream", _gMappicS406UpperSewerShapeStream);

TmdSource gMappicS406UpperSewerShape = {
    .bufferHalfBytes  = 3 * sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS406UpperSewerShapeSkeleton),
    .partVertexCounts = _gMappicS406UpperSewerShapePartVerts,
    .verts            = _gMappicS406UpperSewerShapeVerts,
    .normals          = &_gMappicS406UpperSewerShapeVerts[ARRAY_SIZE(_gMappicS406UpperSewerShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS406UpperSewerShapeSkeleton,
    .stream           = _gMappicS406UpperSewerShapeStream,
};

/// Identity transform and self-parented root for the Water supply shape.
static TmdBone _gMappicS406WaterSupplyShapeSkeleton[1];
PE_ASSET_BIND("mappic_s4_06_model_00214_00268_skeleton", _gMappicS406WaterSupplyShapeSkeleton);

/// Vertex count of the Water supply shape's sole part (eight vertices).
static u32 _gMappicS406WaterSupplyShapePartVerts[1];
PE_ASSET_BIND("mappic_s4_06_model_00214_00268_partVerts", _gMappicS406WaterSupplyShapePartVerts);

/// Water supply's map footprint in integer model X/Z coordinates, with Y zero.
static SVECTOR _gMappicS406WaterSupplyShapeVerts[8];
PE_ASSET_BIND("mappic_s4_06_model_00214_00268_verts", _gMappicS406WaterSupplyShapeVerts);

/// Packed command stream for the Water supply shape's two unlit triangles and two quads.
///
/// Three words per face hold packed SVECTOR byte offsets and white colour.
/// Two group ends precede the stream end; the map reads only the first group.
static u32 _gMappicS406WaterSupplyShapeStream[21];
PE_ASSET_BIND("mappic_s4_06_model_00214_00268_stream", _gMappicS406WaterSupplyShapeStream);

TmdSource gMappicS406WaterSupplyShape = {
    .bufferHalfBytes  = 2 * sizeof(POLY_F3) + 2 * sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS406WaterSupplyShapeSkeleton),
    .partVertexCounts = _gMappicS406WaterSupplyShapePartVerts,
    .verts            = _gMappicS406WaterSupplyShapeVerts,
    .normals          = &_gMappicS406WaterSupplyShapeVerts[ARRAY_SIZE(_gMappicS406WaterSupplyShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS406WaterSupplyShapeSkeleton,
    .stream           = _gMappicS406WaterSupplyShapeStream,
};

/// Identity transform and self-parented root for the Lower sewer shape.
static TmdBone _gMappicS406LowerSewerShapeSkeleton[1];
PE_ASSET_BIND("mappic_s2_02_model_00CF8_00330_skeleton", _gMappicS406LowerSewerShapeSkeleton);

/// Vertex count of the Lower sewer shape's sole part (eight vertices).
static u32 _gMappicS406LowerSewerShapePartVerts[1];
PE_ASSET_BIND("mappic_s2_02_model_00CF8_00330_partVerts", _gMappicS406LowerSewerShapePartVerts);

/// Lower sewer's map footprint in integer model X/Z coordinates, with Y zero.
static SVECTOR _gMappicS406LowerSewerShapeVerts[8];
PE_ASSET_BIND("mappic_s2_02_model_00CF8_00330_verts", _gMappicS406LowerSewerShapeVerts);

/// Packed command stream for the Lower sewer shape's three unlit quads.
///
/// Three words per face hold packed SVECTOR byte offsets and white colour.
/// Two group ends precede the stream end; the map reads only the first group.
static u32 _gMappicS406LowerSewerShapeStream[15];
PE_ASSET_BIND("mappic_s2_02_model_00CF8_00330_stream", _gMappicS406LowerSewerShapeStream);

TmdSource gMappicS406LowerSewerShape = {
    .bufferHalfBytes  = 3 * sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS406LowerSewerShapeSkeleton),
    .partVertexCounts = _gMappicS406LowerSewerShapePartVerts,
    .verts            = _gMappicS406LowerSewerShapeVerts,
    .normals          = &_gMappicS406LowerSewerShapeVerts[ARRAY_SIZE(_gMappicS406LowerSewerShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS406LowerSewerShapeSkeleton,
    .stream           = _gMappicS406LowerSewerShapeStream,
};
