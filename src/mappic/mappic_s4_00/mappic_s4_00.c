#include "mappic/mappic.h"
#include "port/asset_bind.h"

#include <libgpu.h>

#include "common.h"

/// Identity transform and self-parented root for the Cavern shape.
#ifdef PE_EMBED_ASSETS
static TmdBone _gMappicS400CavernShapeSkeleton[] = {
#include "assets/mappic_s4_00_model_0005C_0008C_skeleton.inc"
};
#else
static TmdBone _gMappicS400CavernShapeSkeleton[1];
#endif
PE_ASSET_BIND("mappic_s4_00_model_0005C_0008C_skeleton", _gMappicS400CavernShapeSkeleton);

/// Six vertices in the Cavern shape's sole part.
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS400CavernShapePartVerts[] = {
#include "assets/mappic_s4_00_model_0005C_0008C_partVerts.inc"
};
#else
static u32 _gMappicS400CavernShapePartVerts[1];
#endif
PE_ASSET_BIND("mappic_s4_00_model_0005C_0008C_partVerts", _gMappicS400CavernShapePartVerts);

/// Cavern's map footprint in integer model X/Z coordinates, with Y zero.
#ifdef PE_EMBED_ASSETS
static SVECTOR _gMappicS400CavernShapeVerts[] = {
#include "assets/mappic_s4_00_model_0005C_0008C_verts.inc"
};
#else
static SVECTOR _gMappicS400CavernShapeVerts[6];
#endif
PE_ASSET_BIND("mappic_s4_00_model_0005C_0008C_verts", _gMappicS400CavernShapeVerts);

/// Packed command stream for the Cavern shape's two unlit quads.
///
/// Elements contain four SVECTOR byte offsets and white colour; two group
/// ends precede the stream end. The map reads only the first group.
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS400CavernShapeStream[] = {
#include "assets/mappic_s4_00_model_0005C_0008C_stream.inc"
};
#else
static u32 _gMappicS400CavernShapeStream[12];
#endif
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
#ifdef PE_EMBED_ASSETS
static TmdBone _gMappicS400SecretPassageShapeSkeleton[] = {
#include "assets/mappic_s4_00_model_00148_skeleton.inc"
};
#else
static TmdBone _gMappicS400SecretPassageShapeSkeleton[1];
#endif
PE_ASSET_BIND("mappic_s4_00_model_00148_skeleton", _gMappicS400SecretPassageShapeSkeleton);

/// Fourteen vertices in the Secret Passage shape's sole part.
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS400SecretPassageShapePartVerts[] = {
#include "assets/mappic_s4_00_model_00148_partVerts.inc"
};
#else
static u32 _gMappicS400SecretPassageShapePartVerts[1];
#endif
PE_ASSET_BIND("mappic_s4_00_model_00148_partVerts", _gMappicS400SecretPassageShapePartVerts);

/// Secret Passage's map footprint in integer model X/Z coordinates, with Y zero.
#ifdef PE_EMBED_ASSETS
static SVECTOR _gMappicS400SecretPassageShapeVerts[] = {
#include "assets/mappic_s4_00_model_00148_verts.inc"
};
#else
static SVECTOR _gMappicS400SecretPassageShapeVerts[14];
#endif
PE_ASSET_BIND("mappic_s4_00_model_00148_verts", _gMappicS400SecretPassageShapeVerts);

/// Packed command stream for the Secret Passage shape's six unlit quads.
///
/// Elements contain four SVECTOR byte offsets and white colour; two group
/// ends precede the stream end. The map reads only the first group.
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS400SecretPassageShapeStream[] = {
#include "assets/mappic_s4_00_model_00148_stream.inc"
};
#else
static u32 _gMappicS400SecretPassageShapeStream[24];
#endif
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
