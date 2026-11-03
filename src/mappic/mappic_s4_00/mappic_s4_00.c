#include "mappic/mappic.h"
#include "port/asset_bind.h"

#include <libgpu.h>

#include "common.h"

/// Identity transform and self-parented root for the Cavern shape.
static TmdBone _gMappicS400CavernShapeSkeleton[1];
PE_ASSET_BIND("mappic_s4_00_model_0005C_0008C_skeleton", _gMappicS400CavernShapeSkeleton);

/// Six vertices in the Cavern shape's sole part.
static u32 _gMappicS400CavernShapePartVerts[1];
PE_ASSET_BIND("mappic_s4_00_model_0005C_0008C_partVerts", _gMappicS400CavernShapePartVerts);

/// Cavern's map footprint in integer model X/Z coordinates, with Y zero.
static SVECTOR _gMappicS400CavernShapeVerts[6];
PE_ASSET_BIND("mappic_s4_00_model_0005C_0008C_verts", _gMappicS400CavernShapeVerts);

/// Packed command stream for the Cavern shape's two unlit quads.
///
/// Elements contain four SVECTOR byte offsets and white colour; two group
/// ends precede the stream end. The map reads only the first group.
static u32 _gMappicS400CavernShapeStream[12];
PE_ASSET_BIND("mappic_s4_00_model_0005C_0008C_stream", _gMappicS400CavernShapeStream);

TmdSource gMappicS400CavernShape = {
    .bufferHalfBytes  = 2 * sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS400CavernShapeSkeleton),
    .partVertexCounts = _gMappicS400CavernShapePartVerts,
    .verts            = _gMappicS400CavernShapeVerts,
    .normals          = &_gMappicS400CavernShapeVerts[ARRAY_SIZE(_gMappicS400CavernShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS400CavernShapeSkeleton,
    .stream           = _gMappicS400CavernShapeStream,
};

/// Identity transform and self-parented root for the Secret Passage shape.
static TmdBone _gMappicS400SecretPassageShapeSkeleton[1];
PE_ASSET_BIND("mappic_s4_00_model_00148_skeleton", _gMappicS400SecretPassageShapeSkeleton);

/// Fourteen vertices in the Secret Passage shape's sole part.
static u32 _gMappicS400SecretPassageShapePartVerts[1];
PE_ASSET_BIND("mappic_s4_00_model_00148_partVerts", _gMappicS400SecretPassageShapePartVerts);

/// Secret Passage's map footprint in integer model X/Z coordinates, with Y zero.
static SVECTOR _gMappicS400SecretPassageShapeVerts[14];
PE_ASSET_BIND("mappic_s4_00_model_00148_verts", _gMappicS400SecretPassageShapeVerts);

/// Packed command stream for the Secret Passage shape's six unlit quads.
///
/// Elements contain four SVECTOR byte offsets and white colour; two group
/// ends precede the stream end. The map reads only the first group.
static u32 _gMappicS400SecretPassageShapeStream[24];
PE_ASSET_BIND("mappic_s4_00_model_00148_stream", _gMappicS400SecretPassageShapeStream);

TmdSource gMappicS400SecretPassageShape = {
    .bufferHalfBytes  = 6 * sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS400SecretPassageShapeSkeleton),
    .partVertexCounts = _gMappicS400SecretPassageShapePartVerts,
    .verts            = _gMappicS400SecretPassageShapeVerts,
    .normals          = &_gMappicS400SecretPassageShapeVerts[ARRAY_SIZE(_gMappicS400SecretPassageShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS400SecretPassageShapeSkeleton,
    .stream           = _gMappicS400SecretPassageShapeStream,
};
