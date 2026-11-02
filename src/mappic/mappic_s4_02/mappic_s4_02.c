#include "mappic/mappic.h"
#include "port/asset_bind.h"

#include <libgpu.h>

#include "common.h"

/// Identity transform and self-parented root for the Mesa shape.
#ifdef PE_EMBED_ASSETS
static TmdBone _gMappicS402MesaShapeSkeleton[] = {
#include "assets/mappic_s2_02_model_00C48_00070_skeleton.inc"
};
#else
static TmdBone _gMappicS402MesaShapeSkeleton[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_00070_skeleton", _gMappicS402MesaShapeSkeleton);

/// Vertex count of the Mesa shape's sole part (four vertices).
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS402MesaShapePartVerts[] = {
#include "assets/mappic_s2_02_model_00C48_00070_partVerts.inc"
};
#else
static u32 _gMappicS402MesaShapePartVerts[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_00070_partVerts", _gMappicS402MesaShapePartVerts);

/// Mesa's map footprint in integer model X/Z coordinates, with Y zero.
#ifdef PE_EMBED_ASSETS
static SVECTOR _gMappicS402MesaShapeVerts[] = {
#include "assets/mappic_s2_02_model_00C48_00070_verts.inc"
};
#else
static SVECTOR _gMappicS402MesaShapeVerts[4];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_00070_verts", _gMappicS402MesaShapeVerts);

/// One unlit quad's packed vertex byte offsets and white colour, followed by two group ends and the stream end.
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS402MesaShapeStream[] = {
#include "assets/mappic_s2_02_model_00C48_00070_stream.inc"
};
#else
static u32 _gMappicS402MesaShapeStream[9];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_00070_stream", _gMappicS402MesaShapeStream);

TmdSource gMappicS402MesaShape = {
    .bufferHalfBytes  = sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS402MesaShapeSkeleton),
    .partVertexCounts = _gMappicS402MesaShapePartVerts,
    .verts            = _gMappicS402MesaShapeVerts,
    .normals          = &_gMappicS402MesaShapeVerts[ARRAY_SIZE(_gMappicS402MesaShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS402MesaShapeSkeleton,
    .stream           = _gMappicS402MesaShapeStream,
};

/// Identity transform and self-parented root for the Tunnel Entrance shape.
#ifdef PE_EMBED_ASSETS
static TmdBone _gMappicS402TunnelEntranceShapeSkeleton[] = {
#include "assets/mappic_s2_02_model_00C48_00100_skeleton.inc"
};
#else
static TmdBone _gMappicS402TunnelEntranceShapeSkeleton[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_00100_skeleton", _gMappicS402TunnelEntranceShapeSkeleton);

/// Vertex count of the Tunnel Entrance shape's sole part (four vertices).
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS402TunnelEntranceShapePartVerts[] = {
#include "assets/mappic_s2_02_model_00C48_00100_partVerts.inc"
};
#else
static u32 _gMappicS402TunnelEntranceShapePartVerts[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_00100_partVerts", _gMappicS402TunnelEntranceShapePartVerts);

/// Tunnel Entrance's map footprint in integer model X/Z coordinates, with Y zero.
#ifdef PE_EMBED_ASSETS
static SVECTOR _gMappicS402TunnelEntranceShapeVerts[] = {
#include "assets/mappic_s2_02_model_00C48_00100_verts.inc"
};
#else
static SVECTOR _gMappicS402TunnelEntranceShapeVerts[4];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_00100_verts", _gMappicS402TunnelEntranceShapeVerts);

/// One unlit quad's packed vertex byte offsets and white colour, followed by two group ends and the stream end.
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS402TunnelEntranceShapeStream[] = {
#include "assets/mappic_s2_02_model_00C48_00100_stream.inc"
};
#else
static u32 _gMappicS402TunnelEntranceShapeStream[9];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_00100_stream", _gMappicS402TunnelEntranceShapeStream);

TmdSource gMappicS402TunnelEntranceShape = {
    .bufferHalfBytes  = sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS402TunnelEntranceShapeSkeleton),
    .partVertexCounts = _gMappicS402TunnelEntranceShapePartVerts,
    .verts            = _gMappicS402TunnelEntranceShapeVerts,
    .normals          = &_gMappicS402TunnelEntranceShapeVerts[ARRAY_SIZE(_gMappicS402TunnelEntranceShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS402TunnelEntranceShapeSkeleton,
    .stream           = _gMappicS402TunnelEntranceShapeStream,
};

/// Identity transform and self-parented root for the Tunnel shape.
#ifdef PE_EMBED_ASSETS
static TmdBone _gMappicS402TunnelShapeSkeleton[] = {
#include "assets/mappic_s2_02_model_00C48_00190_skeleton.inc"
};
#else
static TmdBone _gMappicS402TunnelShapeSkeleton[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_00190_skeleton", _gMappicS402TunnelShapeSkeleton);

/// Vertex count of the Tunnel shape's sole part (four vertices).
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS402TunnelShapePartVerts[] = {
#include "assets/mappic_s2_02_model_00C48_00190_partVerts.inc"
};
#else
static u32 _gMappicS402TunnelShapePartVerts[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_00190_partVerts", _gMappicS402TunnelShapePartVerts);

/// Tunnel's map footprint in integer model X/Z coordinates, with Y zero.
#ifdef PE_EMBED_ASSETS
static SVECTOR _gMappicS402TunnelShapeVerts[] = {
#include "assets/mappic_s2_02_model_00C48_00190_verts.inc"
};
#else
static SVECTOR _gMappicS402TunnelShapeVerts[4];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_00190_verts", _gMappicS402TunnelShapeVerts);

/// One unlit quad's packed vertex byte offsets and white colour, followed by two group ends and the stream end.
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS402TunnelShapeStream[] = {
#include "assets/mappic_s2_02_model_00C48_00190_stream.inc"
};
#else
static u32 _gMappicS402TunnelShapeStream[9];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_00190_stream", _gMappicS402TunnelShapeStream);

TmdSource gMappicS402TunnelShape = {
    .bufferHalfBytes  = sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS402TunnelShapeSkeleton),
    .partVertexCounts = _gMappicS402TunnelShapePartVerts,
    .verts            = _gMappicS402TunnelShapeVerts,
    .normals          = &_gMappicS402TunnelShapeVerts[ARRAY_SIZE(_gMappicS402TunnelShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS402TunnelShapeSkeleton,
    .stream           = _gMappicS402TunnelShapeStream,
};

/// Identity transform and self-parented root for the Gorge shape.
#ifdef PE_EMBED_ASSETS
static TmdBone _gMappicS402GorgeShapeSkeleton[] = {
#include "assets/mappic_s2_02_model_00C48_00220_skeleton.inc"
};
#else
static TmdBone _gMappicS402GorgeShapeSkeleton[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_00220_skeleton", _gMappicS402GorgeShapeSkeleton);

/// Vertex count of the Gorge shape's sole part (four vertices).
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS402GorgeShapePartVerts[] = {
#include "assets/mappic_s2_02_model_00C48_00220_partVerts.inc"
};
#else
static u32 _gMappicS402GorgeShapePartVerts[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_00220_partVerts", _gMappicS402GorgeShapePartVerts);

/// Gorge's map footprint in integer model X/Z coordinates, with Y zero.
#ifdef PE_EMBED_ASSETS
static SVECTOR _gMappicS402GorgeShapeVerts[] = {
#include "assets/mappic_s2_02_model_00C48_00220_verts.inc"
};
#else
static SVECTOR _gMappicS402GorgeShapeVerts[4];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_00220_verts", _gMappicS402GorgeShapeVerts);

/// One unlit quad's packed vertex byte offsets and white colour, followed by two group ends and the stream end.
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS402GorgeShapeStream[] = {
#include "assets/mappic_s2_02_model_00C48_00220_stream.inc"
};
#else
static u32 _gMappicS402GorgeShapeStream[9];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_00220_stream", _gMappicS402GorgeShapeStream);

TmdSource gMappicS402GorgeShape = {
    .bufferHalfBytes  = sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS402GorgeShapeSkeleton),
    .partVertexCounts = _gMappicS402GorgeShapePartVerts,
    .verts            = _gMappicS402GorgeShapeVerts,
    .normals          = &_gMappicS402GorgeShapeVerts[ARRAY_SIZE(_gMappicS402GorgeShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS402GorgeShapeSkeleton,
    .stream           = _gMappicS402GorgeShapeStream,
};

/// Identity transform and self-parented root for the Refuge shape.
#ifdef PE_EMBED_ASSETS
static TmdBone _gMappicS402RefugeShapeSkeleton[] = {
#include "assets/mappic_s2_02_model_00C48_002B0_skeleton.inc"
};
#else
static TmdBone _gMappicS402RefugeShapeSkeleton[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_002B0_skeleton", _gMappicS402RefugeShapeSkeleton);

/// Vertex count of the Refuge shape's sole part (four vertices).
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS402RefugeShapePartVerts[] = {
#include "assets/mappic_s2_02_model_00C48_002B0_partVerts.inc"
};
#else
static u32 _gMappicS402RefugeShapePartVerts[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_002B0_partVerts", _gMappicS402RefugeShapePartVerts);

/// Refuge's map footprint in integer model X/Z coordinates, with Y zero.
#ifdef PE_EMBED_ASSETS
static SVECTOR _gMappicS402RefugeShapeVerts[] = {
#include "assets/mappic_s2_02_model_00C48_002B0_verts.inc"
};
#else
static SVECTOR _gMappicS402RefugeShapeVerts[4];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_002B0_verts", _gMappicS402RefugeShapeVerts);

/// One unlit quad's packed vertex byte offsets and white colour, followed by two group ends and the stream end.
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS402RefugeShapeStream[] = {
#include "assets/mappic_s2_02_model_00C48_002B0_stream.inc"
};
#else
static u32 _gMappicS402RefugeShapeStream[9];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_002B0_stream", _gMappicS402RefugeShapeStream);

TmdSource gMappicS402RefugeShape = {
    .bufferHalfBytes  = sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS402RefugeShapeSkeleton),
    .partVertexCounts = _gMappicS402RefugeShapePartVerts,
    .verts            = _gMappicS402RefugeShapeVerts,
    .normals          = &_gMappicS402RefugeShapeVerts[ARRAY_SIZE(_gMappicS402RefugeShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS402RefugeShapeSkeleton,
    .stream           = _gMappicS402RefugeShapeStream,
};

/// Identity transform and self-parented root for the Forked Tunnel shape.
#ifdef PE_EMBED_ASSETS
static TmdBone _gMappicS402ForkedTunnelShapeSkeleton[] = {
#include "assets/mappic_s4_00_model_0005C_0035C_skeleton.inc"
};
#else
static TmdBone _gMappicS402ForkedTunnelShapeSkeleton[1];
#endif
PE_ASSET_BIND("mappic_s4_00_model_0005C_0035C_skeleton", _gMappicS402ForkedTunnelShapeSkeleton);

/// Vertex count of the Forked Tunnel shape's sole part (six vertices).
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS402ForkedTunnelShapePartVerts[] = {
#include "assets/mappic_s4_00_model_0005C_0035C_partVerts.inc"
};
#else
static u32 _gMappicS402ForkedTunnelShapePartVerts[1];
#endif
PE_ASSET_BIND("mappic_s4_00_model_0005C_0035C_partVerts", _gMappicS402ForkedTunnelShapePartVerts);

/// Forked Tunnel's map footprint in integer model X/Z coordinates, with Y zero.
#ifdef PE_EMBED_ASSETS
static SVECTOR _gMappicS402ForkedTunnelShapeVerts[] = {
#include "assets/mappic_s4_00_model_0005C_0035C_verts.inc"
};
#else
static SVECTOR _gMappicS402ForkedTunnelShapeVerts[6];
#endif
PE_ASSET_BIND("mappic_s4_00_model_0005C_0035C_verts", _gMappicS402ForkedTunnelShapeVerts);

/// Two unlit quads' packed vertex byte offsets and white colour, followed by two group ends and the stream end.
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS402ForkedTunnelShapeStream[] = {
#include "assets/mappic_s4_00_model_0005C_0035C_stream.inc"
};
#else
static u32 _gMappicS402ForkedTunnelShapeStream[12];
#endif
PE_ASSET_BIND("mappic_s4_00_model_0005C_0035C_stream", _gMappicS402ForkedTunnelShapeStream);

TmdSource gMappicS402ForkedTunnelShape = {
    .bufferHalfBytes  = 2 * sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS402ForkedTunnelShapeSkeleton),
    .partVertexCounts = _gMappicS402ForkedTunnelShapePartVerts,
    .verts            = _gMappicS402ForkedTunnelShapeVerts,
    .normals          = &_gMappicS402ForkedTunnelShapeVerts[ARRAY_SIZE(_gMappicS402ForkedTunnelShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS402ForkedTunnelShapeSkeleton,
    .stream           = _gMappicS402ForkedTunnelShapeStream,
};
