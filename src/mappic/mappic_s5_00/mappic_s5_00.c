#include "mappic/mappic.h"
#include "port/asset_bind.h"

#include <libgpu.h>

#include "common.h"

/// Identity transform and self-parented root for the Observatory shape.
#ifdef PE_EMBED_ASSETS
static TmdBone _gMappicS500ObservatoryShapeSkeleton[] = {
#include "assets/mappic_s5_00_model_000A4_skeleton.inc"
};
#else
static TmdBone _gMappicS500ObservatoryShapeSkeleton[1];
#endif
PE_ASSET_BIND("mappic_s5_00_model_000A4_skeleton", _gMappicS500ObservatoryShapeSkeleton);

/// Vertex count of the Observatory shape's sole part (fifteen vertices).
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS500ObservatoryShapePartVerts[] = {
#include "assets/mappic_s5_00_model_000A4_partVerts.inc"
};
#else
static u32 _gMappicS500ObservatoryShapePartVerts[1];
#endif
PE_ASSET_BIND("mappic_s5_00_model_000A4_partVerts", _gMappicS500ObservatoryShapePartVerts);

/// Observatory's map footprint in integer model X/Z coordinates, with Y zero.
#ifdef PE_EMBED_ASSETS
static SVECTOR _gMappicS500ObservatoryShapeVerts[] = {
#include "assets/mappic_s5_00_model_000A4_verts.inc"
};
#else
static SVECTOR _gMappicS500ObservatoryShapeVerts[15];
#endif
PE_ASSET_BIND("mappic_s5_00_model_000A4_verts", _gMappicS500ObservatoryShapeVerts);

/// One unlit triangle and six quads with packed vertex byte offsets and white colour, followed by two group ends and the stream end.
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS500ObservatoryShapeStream[] = {
#include "assets/mappic_s5_00_model_000A4_stream.inc"
};
#else
static u32 _gMappicS500ObservatoryShapeStream[30];
#endif
PE_ASSET_BIND("mappic_s5_00_model_000A4_stream", _gMappicS500ObservatoryShapeStream);

TmdSource gMappicS500ObservatoryShape = {
    .bufferHalfBytes  = sizeof(POLY_F3) + 6 * sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS500ObservatoryShapeSkeleton),
    .partVertexCounts = _gMappicS500ObservatoryShapePartVerts,
    .verts            = _gMappicS500ObservatoryShapeVerts,
    .normals          = &_gMappicS500ObservatoryShapeVerts[ARRAY_SIZE(_gMappicS500ObservatoryShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS500ObservatoryShapeSkeleton,
    .stream           = _gMappicS500ObservatoryShapeStream,
};

/// Identity transform and self-parented root for the EVE access tunnel shape.
#ifdef PE_EMBED_ASSETS
static TmdBone _gMappicS500EveAccessTunnelShapeSkeleton[] = {
#include "assets/mappic_s2_02_model_00C48_001AC_mappic_s5_00_skeleton.inc"
};
#else
static TmdBone _gMappicS500EveAccessTunnelShapeSkeleton[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_001AC_mappic_s5_00_skeleton", _gMappicS500EveAccessTunnelShapeSkeleton);

/// Vertex count of the EVE access tunnel shape's sole part (four vertices).
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS500EveAccessTunnelShapePartVerts[] = {
#include "assets/mappic_s2_02_model_00C48_001AC_mappic_s5_00_partVerts.inc"
};
#else
static u32 _gMappicS500EveAccessTunnelShapePartVerts[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_001AC_mappic_s5_00_partVerts", _gMappicS500EveAccessTunnelShapePartVerts);

/// EVE access tunnel's map footprint in integer model X/Z coordinates, with Y zero.
#ifdef PE_EMBED_ASSETS
static SVECTOR _gMappicS500EveAccessTunnelShapeVerts[] = {
#include "assets/mappic_s2_02_model_00C48_001AC_mappic_s5_00_verts.inc"
};
#else
static SVECTOR _gMappicS500EveAccessTunnelShapeVerts[4];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_001AC_mappic_s5_00_verts", _gMappicS500EveAccessTunnelShapeVerts);

/// One unlit quad's packed vertex byte offsets and white colour, followed by two group ends and the stream end.
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS500EveAccessTunnelShapeStream[] = {
#include "assets/mappic_s2_02_model_00C48_001AC_mappic_s5_00_stream.inc"
};
#else
static u32 _gMappicS500EveAccessTunnelShapeStream[9];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_001AC_mappic_s5_00_stream", _gMappicS500EveAccessTunnelShapeStream);

TmdSource gMappicS500EveAccessTunnelShape = {
    .bufferHalfBytes  = sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS500EveAccessTunnelShapeSkeleton),
    .partVertexCounts = _gMappicS500EveAccessTunnelShapePartVerts,
    .verts            = _gMappicS500EveAccessTunnelShapeVerts,
    .normals          = &_gMappicS500EveAccessTunnelShapeVerts[ARRAY_SIZE(_gMappicS500EveAccessTunnelShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS500EveAccessTunnelShapeSkeleton,
    .stream           = _gMappicS500EveAccessTunnelShapeStream,
};

/// Identity transform and self-parented root for the North promenade shape.
#ifdef PE_EMBED_ASSETS
static TmdBone _gMappicS500NorthPromenadeShapeSkeleton[] = {
#include "assets/mappic_s5_00_model_00270_skeleton.inc"
};
#else
static TmdBone _gMappicS500NorthPromenadeShapeSkeleton[1];
#endif
PE_ASSET_BIND("mappic_s5_00_model_00270_skeleton", _gMappicS500NorthPromenadeShapeSkeleton);

/// Vertex count of the North promenade shape's sole part (fifteen vertices).
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS500NorthPromenadeShapePartVerts[] = {
#include "assets/mappic_s5_00_model_00270_partVerts.inc"
};
#else
static u32 _gMappicS500NorthPromenadeShapePartVerts[1];
#endif
PE_ASSET_BIND("mappic_s5_00_model_00270_partVerts", _gMappicS500NorthPromenadeShapePartVerts);

/// North promenade's map footprint in integer model X/Z coordinates, with Y zero.
#ifdef PE_EMBED_ASSETS
static SVECTOR _gMappicS500NorthPromenadeShapeVerts[] = {
#include "assets/mappic_s5_00_model_00270_verts.inc"
};
#else
static SVECTOR _gMappicS500NorthPromenadeShapeVerts[15];
#endif
PE_ASSET_BIND("mappic_s5_00_model_00270_verts", _gMappicS500NorthPromenadeShapeVerts);

/// One unlit triangle and six quads with packed vertex byte offsets and white colour, followed by two group ends and the stream end.
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS500NorthPromenadeShapeStream[] = {
#include "assets/mappic_s5_00_model_00270_stream.inc"
};
#else
static u32 _gMappicS500NorthPromenadeShapeStream[30];
#endif
PE_ASSET_BIND("mappic_s5_00_model_00270_stream", _gMappicS500NorthPromenadeShapeStream);

TmdSource gMappicS500NorthPromenadeShape = {
    .bufferHalfBytes  = sizeof(POLY_F3) + 6 * sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS500NorthPromenadeShapeSkeleton),
    .partVertexCounts = _gMappicS500NorthPromenadeShapePartVerts,
    .verts            = _gMappicS500NorthPromenadeShapeVerts,
    .normals          = &_gMappicS500NorthPromenadeShapeVerts[ARRAY_SIZE(_gMappicS500NorthPromenadeShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS500NorthPromenadeShapeSkeleton,
    .stream           = _gMappicS500NorthPromenadeShapeStream,
};

/// Identity transform and self-parented root for the Forest zone shape.
#ifdef PE_EMBED_ASSETS
static TmdBone _gMappicS500ForestZoneShapeSkeleton[] = {
#include "assets/mappic_s2_02_model_00C48_00378_mappic_s5_00_skeleton.inc"
};
#else
static TmdBone _gMappicS500ForestZoneShapeSkeleton[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_00378_mappic_s5_00_skeleton", _gMappicS500ForestZoneShapeSkeleton);

/// Vertex count of the Forest zone shape's sole part (four vertices).
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS500ForestZoneShapePartVerts[] = {
#include "assets/mappic_s2_02_model_00C48_00378_mappic_s5_00_partVerts.inc"
};
#else
static u32 _gMappicS500ForestZoneShapePartVerts[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_00378_mappic_s5_00_partVerts", _gMappicS500ForestZoneShapePartVerts);

/// Forest zone's map footprint in integer model X/Z coordinates, with Y zero.
#ifdef PE_EMBED_ASSETS
static SVECTOR _gMappicS500ForestZoneShapeVerts[] = {
#include "assets/mappic_s2_02_model_00C48_00378_mappic_s5_00_verts.inc"
};
#else
static SVECTOR _gMappicS500ForestZoneShapeVerts[4];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_00378_mappic_s5_00_verts", _gMappicS500ForestZoneShapeVerts);

/// One unlit quad's packed vertex byte offsets and white colour, followed by two group ends and the stream end.
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS500ForestZoneShapeStream[] = {
#include "assets/mappic_s2_02_model_00C48_00378_mappic_s5_00_stream.inc"
};
#else
static u32 _gMappicS500ForestZoneShapeStream[9];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_00378_mappic_s5_00_stream", _gMappicS500ForestZoneShapeStream);

TmdSource gMappicS500ForestZoneShape = {
    .bufferHalfBytes  = sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS500ForestZoneShapeSkeleton),
    .partVertexCounts = _gMappicS500ForestZoneShapePartVerts,
    .verts            = _gMappicS500ForestZoneShapeVerts,
    .normals          = &_gMappicS500ForestZoneShapeVerts[ARRAY_SIZE(_gMappicS500ForestZoneShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS500ForestZoneShapeSkeleton,
    .stream           = _gMappicS500ForestZoneShapeStream,
};

/// Identity transform and self-parented root for the Submarine tunnel shape.
#ifdef PE_EMBED_ASSETS
static TmdBone _gMappicS500SubmarineTunnelShapeSkeleton[] = {
#include "assets/mappic_s2_02_model_00C48_00408_skeleton.inc"
};
#else
static TmdBone _gMappicS500SubmarineTunnelShapeSkeleton[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_00408_skeleton", _gMappicS500SubmarineTunnelShapeSkeleton);

/// Vertex count of the Submarine tunnel shape's sole part (four vertices).
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS500SubmarineTunnelShapePartVerts[] = {
#include "assets/mappic_s2_02_model_00C48_00408_partVerts.inc"
};
#else
static u32 _gMappicS500SubmarineTunnelShapePartVerts[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_00408_partVerts", _gMappicS500SubmarineTunnelShapePartVerts);

/// Submarine tunnel's map footprint in integer model X/Z coordinates, with Y zero.
#ifdef PE_EMBED_ASSETS
static SVECTOR _gMappicS500SubmarineTunnelShapeVerts[] = {
#include "assets/mappic_s2_02_model_00C48_00408_verts.inc"
};
#else
static SVECTOR _gMappicS500SubmarineTunnelShapeVerts[4];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_00408_verts", _gMappicS500SubmarineTunnelShapeVerts);

/// One unlit quad's packed vertex byte offsets and white colour, followed by two group ends and the stream end.
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS500SubmarineTunnelShapeStream[] = {
#include "assets/mappic_s2_02_model_00C48_00408_stream.inc"
};
#else
static u32 _gMappicS500SubmarineTunnelShapeStream[9];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_00408_stream", _gMappicS500SubmarineTunnelShapeStream);

TmdSource gMappicS500SubmarineTunnelShape = {
    .bufferHalfBytes  = sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS500SubmarineTunnelShapeSkeleton),
    .partVertexCounts = _gMappicS500SubmarineTunnelShapePartVerts,
    .verts            = _gMappicS500SubmarineTunnelShapeVerts,
    .normals          = &_gMappicS500SubmarineTunnelShapeVerts[ARRAY_SIZE(_gMappicS500SubmarineTunnelShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS500SubmarineTunnelShapeSkeleton,
    .stream           = _gMappicS500SubmarineTunnelShapeStream,
};

/// Identity transform and self-parented root for the Pavilion shape.
#ifdef PE_EMBED_ASSETS
static TmdBone _gMappicS500PavilionShapeSkeleton[] = {
#include "assets/mappic_s2_02_model_00C48_00498_skeleton.inc"
};
#else
static TmdBone _gMappicS500PavilionShapeSkeleton[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_00498_skeleton", _gMappicS500PavilionShapeSkeleton);

/// Vertex count of the Pavilion shape's sole part (four vertices).
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS500PavilionShapePartVerts[] = {
#include "assets/mappic_s2_02_model_00C48_00498_partVerts.inc"
};
#else
static u32 _gMappicS500PavilionShapePartVerts[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_00498_partVerts", _gMappicS500PavilionShapePartVerts);

/// Pavilion's map footprint in integer model X/Z coordinates, with Y zero.
#ifdef PE_EMBED_ASSETS
static SVECTOR _gMappicS500PavilionShapeVerts[] = {
#include "assets/mappic_s2_02_model_00C48_00498_verts.inc"
};
#else
static SVECTOR _gMappicS500PavilionShapeVerts[4];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_00498_verts", _gMappicS500PavilionShapeVerts);

/// One unlit quad's packed vertex byte offsets and white colour, followed by two group ends and the stream end.
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS500PavilionShapeStream[] = {
#include "assets/mappic_s2_02_model_00C48_00498_stream.inc"
};
#else
static u32 _gMappicS500PavilionShapeStream[9];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_00498_stream", _gMappicS500PavilionShapeStream);

TmdSource gMappicS500PavilionShape = {
    .bufferHalfBytes  = sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS500PavilionShapeSkeleton),
    .partVertexCounts = _gMappicS500PavilionShapePartVerts,
    .verts            = _gMappicS500PavilionShapeVerts,
    .normals          = &_gMappicS500PavilionShapeVerts[ARRAY_SIZE(_gMappicS500PavilionShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS500PavilionShapeSkeleton,
    .stream           = _gMappicS500PavilionShapeStream,
};

/// Identity transform and self-parented root for the Island shape.
#ifdef PE_EMBED_ASSETS
static TmdBone _gMappicS500IslandShapeSkeleton[] = {
#include "assets/mappic_s4_06_model_0014C_00560_skeleton.inc"
};
#else
static TmdBone _gMappicS500IslandShapeSkeleton[1];
#endif
PE_ASSET_BIND("mappic_s4_06_model_0014C_00560_skeleton", _gMappicS500IslandShapeSkeleton);

/// Vertex count of the Island shape's sole part (eight vertices).
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS500IslandShapePartVerts[] = {
#include "assets/mappic_s4_06_model_0014C_00560_partVerts.inc"
};
#else
static u32 _gMappicS500IslandShapePartVerts[1];
#endif
PE_ASSET_BIND("mappic_s4_06_model_0014C_00560_partVerts", _gMappicS500IslandShapePartVerts);

/// Island's map footprint in integer model X/Z coordinates, with Y zero.
#ifdef PE_EMBED_ASSETS
static SVECTOR _gMappicS500IslandShapeVerts[] = {
#include "assets/mappic_s4_06_model_0014C_00560_verts.inc"
};
#else
static SVECTOR _gMappicS500IslandShapeVerts[8];
#endif
PE_ASSET_BIND("mappic_s4_06_model_0014C_00560_verts", _gMappicS500IslandShapeVerts);

/// Three unlit quads with packed vertex byte offsets and white colour, followed by two group ends and the stream end.
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS500IslandShapeStream[] = {
#include "assets/mappic_s4_06_model_0014C_00560_stream.inc"
};
#else
static u32 _gMappicS500IslandShapeStream[15];
#endif
PE_ASSET_BIND("mappic_s4_06_model_0014C_00560_stream", _gMappicS500IslandShapeStream);

TmdSource gMappicS500IslandShape = {
    .bufferHalfBytes  = 3 * sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS500IslandShapeSkeleton),
    .partVertexCounts = _gMappicS500IslandShapePartVerts,
    .verts            = _gMappicS500IslandShapeVerts,
    .normals          = &_gMappicS500IslandShapeVerts[ARRAY_SIZE(_gMappicS500IslandShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS500IslandShapeSkeleton,
    .stream           = _gMappicS500IslandShapeStream,
};

/// Identity transform and self-parented root for the Garden shape.
#ifdef PE_EMBED_ASSETS
static TmdBone _gMappicS500GardenShapeSkeleton[] = {
#include "assets/mappic_s5_00_model_005FC_skeleton.inc"
};
#else
static TmdBone _gMappicS500GardenShapeSkeleton[1];
#endif
PE_ASSET_BIND("mappic_s5_00_model_005FC_skeleton", _gMappicS500GardenShapeSkeleton);

/// Vertex count of the Garden shape's sole part (ten vertices).
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS500GardenShapePartVerts[] = {
#include "assets/mappic_s5_00_model_005FC_partVerts.inc"
};
#else
static u32 _gMappicS500GardenShapePartVerts[1];
#endif
PE_ASSET_BIND("mappic_s5_00_model_005FC_partVerts", _gMappicS500GardenShapePartVerts);

/// Garden's map footprint in integer model X/Z coordinates, with Y zero.
#ifdef PE_EMBED_ASSETS
static SVECTOR _gMappicS500GardenShapeVerts[] = {
#include "assets/mappic_s5_00_model_005FC_verts.inc"
};
#else
static SVECTOR _gMappicS500GardenShapeVerts[10];
#endif
PE_ASSET_BIND("mappic_s5_00_model_005FC_verts", _gMappicS500GardenShapeVerts);

/// Two unlit triangles and three quads with packed vertex byte offsets and white colour, followed by two group ends and the stream end.
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS500GardenShapeStream[] = {
#include "assets/mappic_s5_00_model_005FC_stream.inc"
};
#else
static u32 _gMappicS500GardenShapeStream[24];
#endif
PE_ASSET_BIND("mappic_s5_00_model_005FC_stream", _gMappicS500GardenShapeStream);

TmdSource gMappicS500GardenShape = {
    .bufferHalfBytes  = 2 * sizeof(POLY_F3) + 3 * sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS500GardenShapeSkeleton),
    .partVertexCounts = _gMappicS500GardenShapePartVerts,
    .verts            = _gMappicS500GardenShapeVerts,
    .normals          = &_gMappicS500GardenShapeVerts[ARRAY_SIZE(_gMappicS500GardenShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS500GardenShapeSkeleton,
    .stream           = _gMappicS500GardenShapeStream,
};

/// Identity transform and self-parented root for the shared Power plant shape.
#ifdef PE_EMBED_ASSETS
static TmdBone _gMappicS500PowerPlantsShapeSkeleton[] = {
#include "assets/mappic_s2_02_model_00C48_006EC_skeleton.inc"
};
#else
static TmdBone _gMappicS500PowerPlantsShapeSkeleton[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_006EC_skeleton", _gMappicS500PowerPlantsShapeSkeleton);

/// Vertex count of the shared Power plant shape's sole part (four vertices).
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS500PowerPlantsShapePartVerts[] = {
#include "assets/mappic_s2_02_model_00C48_006EC_partVerts.inc"
};
#else
static u32 _gMappicS500PowerPlantsShapePartVerts[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_006EC_partVerts", _gMappicS500PowerPlantsShapePartVerts);

/// Power plants 1 and 2's shared map footprint in integer model X/Z coordinates, with Y zero.
#ifdef PE_EMBED_ASSETS
static SVECTOR _gMappicS500PowerPlantsShapeVerts[] = {
#include "assets/mappic_s2_02_model_00C48_006EC_verts.inc"
};
#else
static SVECTOR _gMappicS500PowerPlantsShapeVerts[4];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_006EC_verts", _gMappicS500PowerPlantsShapeVerts);

/// One unlit quad's packed vertex byte offsets and white colour, followed by two group ends and the stream end.
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS500PowerPlantsShapeStream[] = {
#include "assets/mappic_s2_02_model_00C48_006EC_stream.inc"
};
#else
static u32 _gMappicS500PowerPlantsShapeStream[9];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_006EC_stream", _gMappicS500PowerPlantsShapeStream);

TmdSource gMappicS500PowerPlantsShape = {
    .bufferHalfBytes  = sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS500PowerPlantsShapeSkeleton),
    .partVertexCounts = _gMappicS500PowerPlantsShapePartVerts,
    .verts            = _gMappicS500PowerPlantsShapeVerts,
    .normals          = &_gMappicS500PowerPlantsShapeVerts[ARRAY_SIZE(_gMappicS500PowerPlantsShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS500PowerPlantsShapeSkeleton,
    .stream           = _gMappicS500PowerPlantsShapeStream,
};

/// Identity transform and self-parented root for the Savanna zone shape.
#ifdef PE_EMBED_ASSETS
static TmdBone _gMappicS500SavannaZoneShapeSkeleton[] = {
#include "assets/mappic_s2_02_model_00C48_0077C_skeleton.inc"
};
#else
static TmdBone _gMappicS500SavannaZoneShapeSkeleton[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_0077C_skeleton", _gMappicS500SavannaZoneShapeSkeleton);

/// Vertex count of the Savanna zone shape's sole part (four vertices).
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS500SavannaZoneShapePartVerts[] = {
#include "assets/mappic_s2_02_model_00C48_0077C_partVerts.inc"
};
#else
static u32 _gMappicS500SavannaZoneShapePartVerts[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_0077C_partVerts", _gMappicS500SavannaZoneShapePartVerts);

/// Savanna zone's map footprint in integer model X/Z coordinates, with Y zero.
#ifdef PE_EMBED_ASSETS
static SVECTOR _gMappicS500SavannaZoneShapeVerts[] = {
#include "assets/mappic_s2_02_model_00C48_0077C_verts.inc"
};
#else
static SVECTOR _gMappicS500SavannaZoneShapeVerts[4];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_0077C_verts", _gMappicS500SavannaZoneShapeVerts);

/// One unlit quad's packed vertex byte offsets and white colour, followed by two group ends and the stream end.
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS500SavannaZoneShapeStream[] = {
#include "assets/mappic_s2_02_model_00C48_0077C_stream.inc"
};
#else
static u32 _gMappicS500SavannaZoneShapeStream[9];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_0077C_stream", _gMappicS500SavannaZoneShapeStream);

TmdSource gMappicS500SavannaZoneShape = {
    .bufferHalfBytes  = sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS500SavannaZoneShapeSkeleton),
    .partVertexCounts = _gMappicS500SavannaZoneShapePartVerts,
    .verts            = _gMappicS500SavannaZoneShapeVerts,
    .normals          = &_gMappicS500SavannaZoneShapeVerts[ARRAY_SIZE(_gMappicS500SavannaZoneShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS500SavannaZoneShapeSkeleton,
    .stream           = _gMappicS500SavannaZoneShapeStream,
};

/// Identity transform and self-parented root for the South promenade shape.
#ifdef PE_EMBED_ASSETS
static TmdBone _gMappicS500SouthPromenadeShapeSkeleton[] = {
#include "assets/mappic_s5_00_model_00840_skeleton.inc"
};
#else
static TmdBone _gMappicS500SouthPromenadeShapeSkeleton[1];
#endif
PE_ASSET_BIND("mappic_s5_00_model_00840_skeleton", _gMappicS500SouthPromenadeShapeSkeleton);

/// Vertex count of the South promenade shape's sole part (fifteen vertices).
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS500SouthPromenadeShapePartVerts[] = {
#include "assets/mappic_s5_00_model_00840_partVerts.inc"
};
#else
static u32 _gMappicS500SouthPromenadeShapePartVerts[1];
#endif
PE_ASSET_BIND("mappic_s5_00_model_00840_partVerts", _gMappicS500SouthPromenadeShapePartVerts);

/// South promenade's map footprint in integer model X/Z coordinates, with Y zero.
#ifdef PE_EMBED_ASSETS
static SVECTOR _gMappicS500SouthPromenadeShapeVerts[] = {
#include "assets/mappic_s5_00_model_00840_verts.inc"
};
#else
static SVECTOR _gMappicS500SouthPromenadeShapeVerts[15];
#endif
PE_ASSET_BIND("mappic_s5_00_model_00840_verts", _gMappicS500SouthPromenadeShapeVerts);

/// One unlit triangle and six quads with packed vertex byte offsets and white colour, followed by two group ends and the stream end.
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS500SouthPromenadeShapeStream[] = {
#include "assets/mappic_s5_00_model_00840_stream.inc"
};
#else
static u32 _gMappicS500SouthPromenadeShapeStream[30];
#endif
PE_ASSET_BIND("mappic_s5_00_model_00840_stream", _gMappicS500SouthPromenadeShapeStream);

TmdSource gMappicS500SouthPromenadeShape = {
    .bufferHalfBytes  = sizeof(POLY_F3) + 6 * sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS500SouthPromenadeShapeSkeleton),
    .partVertexCounts = _gMappicS500SouthPromenadeShapePartVerts,
    .verts            = _gMappicS500SouthPromenadeShapeVerts,
    .normals          = &_gMappicS500SouthPromenadeShapeVerts[ARRAY_SIZE(_gMappicS500SouthPromenadeShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS500SouthPromenadeShapeSkeleton,
    .stream           = _gMappicS500SouthPromenadeShapeStream,
};

/// Identity transform and self-parented root for the Altar shape.
#ifdef PE_EMBED_ASSETS
static TmdBone _gMappicS500AltarShapeSkeleton[] = {
#include "assets/mappic_s2_02_model_00C48_00948_skeleton.inc"
};
#else
static TmdBone _gMappicS500AltarShapeSkeleton[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_00948_skeleton", _gMappicS500AltarShapeSkeleton);

/// Vertex count of the Altar shape's sole part (four vertices).
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS500AltarShapePartVerts[] = {
#include "assets/mappic_s2_02_model_00C48_00948_partVerts.inc"
};
#else
static u32 _gMappicS500AltarShapePartVerts[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_00948_partVerts", _gMappicS500AltarShapePartVerts);

/// Altar's map footprint in integer model X/Z coordinates, with Y zero.
#ifdef PE_EMBED_ASSETS
static SVECTOR _gMappicS500AltarShapeVerts[] = {
#include "assets/mappic_s2_02_model_00C48_00948_verts.inc"
};
#else
static SVECTOR _gMappicS500AltarShapeVerts[4];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_00948_verts", _gMappicS500AltarShapeVerts);

/// One unlit quad's packed vertex byte offsets and white colour, followed by two group ends and the stream end.
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS500AltarShapeStream[] = {
#include "assets/mappic_s2_02_model_00C48_00948_stream.inc"
};
#else
static u32 _gMappicS500AltarShapeStream[9];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_00948_stream", _gMappicS500AltarShapeStream);

TmdSource gMappicS500AltarShape = {
    .bufferHalfBytes  = sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS500AltarShapeSkeleton),
    .partVertexCounts = _gMappicS500AltarShapePartVerts,
    .verts            = _gMappicS500AltarShapeVerts,
    .normals          = &_gMappicS500AltarShapeVerts[ARRAY_SIZE(_gMappicS500AltarShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS500AltarShapeSkeleton,
    .stream           = _gMappicS500AltarShapeStream,
};

/// Identity transform and self-parented root for the Shrine shape.
#ifdef PE_EMBED_ASSETS
static TmdBone _gMappicS500ShrineShapeSkeleton[] = {
#include "assets/mappic_s5_00_model_00A14_skeleton.inc"
};
#else
static TmdBone _gMappicS500ShrineShapeSkeleton[1];
#endif
PE_ASSET_BIND("mappic_s5_00_model_00A14_skeleton", _gMappicS500ShrineShapeSkeleton);

/// Vertex count of the Shrine shape's sole part (sixteen vertices).
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS500ShrineShapePartVerts[] = {
#include "assets/mappic_s5_00_model_00A14_partVerts.inc"
};
#else
static u32 _gMappicS500ShrineShapePartVerts[1];
#endif
PE_ASSET_BIND("mappic_s5_00_model_00A14_partVerts", _gMappicS500ShrineShapePartVerts);

/// Shrine's map footprint in integer model X/Z coordinates, with Y zero.
#ifdef PE_EMBED_ASSETS
static SVECTOR _gMappicS500ShrineShapeVerts[] = {
#include "assets/mappic_s5_00_model_00A14_verts.inc"
};
#else
static SVECTOR _gMappicS500ShrineShapeVerts[16];
#endif
PE_ASSET_BIND("mappic_s5_00_model_00A14_verts", _gMappicS500ShrineShapeVerts);

/// Four triangles and five quads with packed vertex byte offsets and unlit white colour.
/// Two group ends and the stream end follow the polygon commands.
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS500ShrineShapeStream[] = {
#include "assets/mappic_s5_00_model_00A14_stream.inc"
};
#else
static u32 _gMappicS500ShrineShapeStream[36];
#endif
PE_ASSET_BIND("mappic_s5_00_model_00A14_stream", _gMappicS500ShrineShapeStream);

TmdSource gMappicS500ShrineShape = {
    .bufferHalfBytes  = 4 * sizeof(POLY_F3) + 5 * sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS500ShrineShapeSkeleton),
    .partVertexCounts = _gMappicS500ShrineShapePartVerts,
    .verts            = _gMappicS500ShrineShapeVerts,
    .normals          = &_gMappicS500ShrineShapeVerts[ARRAY_SIZE(_gMappicS500ShrineShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS500ShrineShapeSkeleton,
    .stream           = _gMappicS500ShrineShapeStream,
};

/// Identity transform and self-parented root for the Woodland path shape.
#ifdef PE_EMBED_ASSETS
static TmdBone _gMappicS500WoodlandPathShapeSkeleton[] = {
#include "assets/mappic_s5_00_model_00B50_skeleton.inc"
};
#else
static TmdBone _gMappicS500WoodlandPathShapeSkeleton[1];
#endif
PE_ASSET_BIND("mappic_s5_00_model_00B50_skeleton", _gMappicS500WoodlandPathShapeSkeleton);

/// Vertex count of the Woodland path shape's sole part (twelve vertices).
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS500WoodlandPathShapePartVerts[] = {
#include "assets/mappic_s5_00_model_00B50_partVerts.inc"
};
#else
static u32 _gMappicS500WoodlandPathShapePartVerts[1];
#endif
PE_ASSET_BIND("mappic_s5_00_model_00B50_partVerts", _gMappicS500WoodlandPathShapePartVerts);

/// Woodland path's map footprint in integer model X/Z coordinates, with Y zero.
#ifdef PE_EMBED_ASSETS
static SVECTOR _gMappicS500WoodlandPathShapeVerts[] = {
#include "assets/mappic_s5_00_model_00B50_verts.inc"
};
#else
static SVECTOR _gMappicS500WoodlandPathShapeVerts[12];
#endif
PE_ASSET_BIND("mappic_s5_00_model_00B50_verts", _gMappicS500WoodlandPathShapeVerts);

/// Five quads with packed vertex byte offsets and unlit white colour.
/// Two group ends and the stream end follow the polygon commands.
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS500WoodlandPathShapeStream[] = {
#include "assets/mappic_s5_00_model_00B50_stream.inc"
};
#else
static u32 _gMappicS500WoodlandPathShapeStream[21];
#endif
PE_ASSET_BIND("mappic_s5_00_model_00B50_stream", _gMappicS500WoodlandPathShapeStream);

TmdSource gMappicS500WoodlandPathShape = {
    .bufferHalfBytes  = 5 * sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS500WoodlandPathShapeSkeleton),
    .partVertexCounts = _gMappicS500WoodlandPathShapePartVerts,
    .verts            = _gMappicS500WoodlandPathShapeVerts,
    .normals          = &_gMappicS500WoodlandPathShapeVerts[ARRAY_SIZE(_gMappicS500WoodlandPathShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS500WoodlandPathShapeSkeleton,
    .stream           = _gMappicS500WoodlandPathShapeStream,
};

/// Identity transform and self-parented root for the Bridge shape.
#ifdef PE_EMBED_ASSETS
static TmdBone _gMappicS500BridgeShapeSkeleton[] = {
#include "assets/mappic_s2_02_model_00910_00C84_skeleton.inc"
};
#else
static TmdBone _gMappicS500BridgeShapeSkeleton[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00910_00C84_skeleton", _gMappicS500BridgeShapeSkeleton);

/// Vertex count of the Bridge shape's sole part (eight vertices).
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS500BridgeShapePartVerts[] = {
#include "assets/mappic_s2_02_model_00910_00C84_partVerts.inc"
};
#else
static u32 _gMappicS500BridgeShapePartVerts[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00910_00C84_partVerts", _gMappicS500BridgeShapePartVerts);

/// Bridge's map footprint in integer model X/Z coordinates, with Y zero.
#ifdef PE_EMBED_ASSETS
static SVECTOR _gMappicS500BridgeShapeVerts[] = {
#include "assets/mappic_s2_02_model_00910_00C84_verts.inc"
};
#else
static SVECTOR _gMappicS500BridgeShapeVerts[8];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00910_00C84_verts", _gMappicS500BridgeShapeVerts);

/// Two triangles and two quads with packed vertex byte offsets and unlit white colour.
/// Two group ends and the stream end follow the polygon commands.
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS500BridgeShapeStream[] = {
#include "assets/mappic_s2_02_model_00910_00C84_stream.inc"
};
#else
static u32 _gMappicS500BridgeShapeStream[21];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00910_00C84_stream", _gMappicS500BridgeShapeStream);

TmdSource gMappicS500BridgeShape = {
    .bufferHalfBytes  = 2 * sizeof(POLY_F3) + 2 * sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS500BridgeShapeSkeleton),
    .partVertexCounts = _gMappicS500BridgeShapePartVerts,
    .verts            = _gMappicS500BridgeShapeVerts,
    .normals          = &_gMappicS500BridgeShapeVerts[ARRAY_SIZE(_gMappicS500BridgeShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS500BridgeShapeSkeleton,
    .stream           = _gMappicS500BridgeShapeStream,
};

/// Identity transform and self-parented root for the Island shape in the altar variant.
#ifdef PE_EMBED_ASSETS
static TmdBone _gMappicS500IslandAltarVariantShapeSkeleton[] = {
#include "assets/mappic_s5_00_model_00D28_skeleton.inc"
};
#else
static TmdBone _gMappicS500IslandAltarVariantShapeSkeleton[1];
#endif
PE_ASSET_BIND("mappic_s5_00_model_00D28_skeleton", _gMappicS500IslandAltarVariantShapeSkeleton);

/// Eleven vertices belong to the Island altar variant's sole part.
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS500IslandAltarVariantShapePartVerts[] = {
#include "assets/mappic_s5_00_model_00D28_partVerts.inc"
};
#else
static u32 _gMappicS500IslandAltarVariantShapePartVerts[1];
#endif
PE_ASSET_BIND("mappic_s5_00_model_00D28_partVerts", _gMappicS500IslandAltarVariantShapePartVerts);

/// Island's altar-variant footprint in integer model X/Z coordinates, with Y zero.
#ifdef PE_EMBED_ASSETS
static SVECTOR _gMappicS500IslandAltarVariantShapeVerts[] = {
#include "assets/mappic_s5_00_model_00D28_verts.inc"
};
#else
static SVECTOR _gMappicS500IslandAltarVariantShapeVerts[11];
#endif
PE_ASSET_BIND("mappic_s5_00_model_00D28_verts", _gMappicS500IslandAltarVariantShapeVerts);

/// One triangle and four quads with packed vertex byte offsets and unlit white colour.
/// Two group ends and the stream end follow the polygon commands.
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS500IslandAltarVariantShapeStream[] = {
#include "assets/mappic_s5_00_model_00D28_stream.inc"
};
#else
static u32 _gMappicS500IslandAltarVariantShapeStream[24];
#endif
PE_ASSET_BIND("mappic_s5_00_model_00D28_stream", _gMappicS500IslandAltarVariantShapeStream);

TmdSource gMappicS500IslandAltarVariantShape = {
    .bufferHalfBytes  = sizeof(POLY_F3) + 4 * sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS500IslandAltarVariantShapeSkeleton),
    .partVertexCounts = _gMappicS500IslandAltarVariantShapePartVerts,
    .verts            = _gMappicS500IslandAltarVariantShapeVerts,
    .normals          = &_gMappicS500IslandAltarVariantShapeVerts[ARRAY_SIZE(_gMappicS500IslandAltarVariantShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS500IslandAltarVariantShapeSkeleton,
    .stream           = _gMappicS500IslandAltarVariantShapeStream,
};

/// Identity transform and self-parented root for the Bridge shape in the altar variant.
#ifdef PE_EMBED_ASSETS
static TmdBone _gMappicS500BridgeAltarVariantShapeSkeleton[] = {
#include "assets/mappic_s5_00_model_00E0C_skeleton.inc"
};
#else
static TmdBone _gMappicS500BridgeAltarVariantShapeSkeleton[1];
#endif
PE_ASSET_BIND("mappic_s5_00_model_00E0C_skeleton", _gMappicS500BridgeAltarVariantShapeSkeleton);

/// Seven vertices belong to the Bridge altar variant's sole part.
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS500BridgeAltarVariantShapePartVerts[] = {
#include "assets/mappic_s5_00_model_00E0C_partVerts.inc"
};
#else
static u32 _gMappicS500BridgeAltarVariantShapePartVerts[1];
#endif
PE_ASSET_BIND("mappic_s5_00_model_00E0C_partVerts", _gMappicS500BridgeAltarVariantShapePartVerts);

/// Bridge's altar-variant footprint in integer model X/Z coordinates, with Y zero.
#ifdef PE_EMBED_ASSETS
static SVECTOR _gMappicS500BridgeAltarVariantShapeVerts[] = {
#include "assets/mappic_s5_00_model_00E0C_verts.inc"
};
#else
static SVECTOR _gMappicS500BridgeAltarVariantShapeVerts[7];
#endif
PE_ASSET_BIND("mappic_s5_00_model_00E0C_verts", _gMappicS500BridgeAltarVariantShapeVerts);

/// One triangle and two quads with packed vertex byte offsets and unlit white colour.
/// Two group ends and the stream end follow the polygon commands.
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS500BridgeAltarVariantShapeStream[] = {
#include "assets/mappic_s5_00_model_00E0C_stream.inc"
};
#else
static u32 _gMappicS500BridgeAltarVariantShapeStream[18];
#endif
PE_ASSET_BIND("mappic_s5_00_model_00E0C_stream", _gMappicS500BridgeAltarVariantShapeStream);

TmdSource gMappicS500BridgeAltarVariantShape = {
    .bufferHalfBytes  = sizeof(POLY_F3) + 2 * sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS500BridgeAltarVariantShapeSkeleton),
    .partVertexCounts = _gMappicS500BridgeAltarVariantShapePartVerts,
    .verts            = _gMappicS500BridgeAltarVariantShapeVerts,
    .normals          = &_gMappicS500BridgeAltarVariantShapeVerts[ARRAY_SIZE(_gMappicS500BridgeAltarVariantShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS500BridgeAltarVariantShapeSkeleton,
    .stream           = _gMappicS500BridgeAltarVariantShapeStream,
};

/// Identity transform and self-parented root for the Pyramid shape.
#ifdef PE_EMBED_ASSETS
static TmdBone _gMappicS500PyramidShapeSkeleton[] = {
#include "assets/mappic_s2_02_model_00CF8_00F1C_skeleton.inc"
};
#else
static TmdBone _gMappicS500PyramidShapeSkeleton[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00CF8_00F1C_skeleton", _gMappicS500PyramidShapeSkeleton);

/// Vertex count of the Pyramid shape's sole part (eight vertices).
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS500PyramidShapePartVerts[] = {
#include "assets/mappic_s2_02_model_00CF8_00F1C_partVerts.inc"
};
#else
static u32 _gMappicS500PyramidShapePartVerts[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00CF8_00F1C_partVerts", _gMappicS500PyramidShapePartVerts);

/// Pyramid's map footprint in integer model X/Z coordinates, with Y zero.
#ifdef PE_EMBED_ASSETS
static SVECTOR _gMappicS500PyramidShapeVerts[] = {
#include "assets/mappic_s2_02_model_00CF8_00F1C_verts.inc"
};
#else
static SVECTOR _gMappicS500PyramidShapeVerts[8];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00CF8_00F1C_verts", _gMappicS500PyramidShapeVerts);

/// Three quads with packed vertex byte offsets and unlit white colour.
/// Two group ends and the stream end follow the polygon commands.
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS500PyramidShapeStream[] = {
#include "assets/mappic_s2_02_model_00CF8_00F1C_stream.inc"
};
#else
static u32 _gMappicS500PyramidShapeStream[15];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00CF8_00F1C_stream", _gMappicS500PyramidShapeStream);

TmdSource gMappicS500PyramidShape = {
    .bufferHalfBytes  = 3 * sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS500PyramidShapeSkeleton),
    .partVertexCounts = _gMappicS500PyramidShapePartVerts,
    .verts            = _gMappicS500PyramidShapeVerts,
    .normals          = &_gMappicS500PyramidShapeVerts[ARRAY_SIZE(_gMappicS500PyramidShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS500PyramidShapeSkeleton,
    .stream           = _gMappicS500PyramidShapeStream,
};
