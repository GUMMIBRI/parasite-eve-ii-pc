#include "mappic/mappic.h"
#include "port/asset_bind.h"

#include <libgpu.h>

#include "common.h"

/// Identity transform and self-parented root for the Gas Station shape.
#ifdef PE_EMBED_ASSETS
static TmdBone _gMappicS202GasStationShapeSkeleton[] = {
#include "assets/mappic_s4_00_model_0005C_skeleton.inc"
};
#else
static TmdBone _gMappicS202GasStationShapeSkeleton[1];
#endif
PE_ASSET_BIND("mappic_s4_00_model_0005C_skeleton", _gMappicS202GasStationShapeSkeleton);

/// Vertex count of the Gas Station shape's sole part (six vertices).
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS202GasStationShapePartVerts[] = {
#include "assets/mappic_s4_00_model_0005C_partVerts.inc"
};
#else
static u32 _gMappicS202GasStationShapePartVerts[1];
#endif
PE_ASSET_BIND("mappic_s4_00_model_0005C_partVerts", _gMappicS202GasStationShapePartVerts);

/// Gas Station's map footprint in integer model X/Z coordinates, with Y zero.
#ifdef PE_EMBED_ASSETS
static SVECTOR _gMappicS202GasStationShapeVerts[] = {
#include "assets/mappic_s4_00_model_0005C_verts.inc"
};
#else
static SVECTOR _gMappicS202GasStationShapeVerts[6];
#endif
PE_ASSET_BIND("mappic_s4_00_model_0005C_verts", _gMappicS202GasStationShapeVerts);

/// Two unlit quads' packed vertex byte offsets and white colour, followed by two group ends and the stream end.
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS202GasStationShapeStream[] = {
#include "assets/mappic_s4_00_model_0005C_stream.inc"
};
#else
static u32 _gMappicS202GasStationShapeStream[12];
#endif
PE_ASSET_BIND("mappic_s4_00_model_0005C_stream", _gMappicS202GasStationShapeStream);

TmdSource gMappicS202GasStationShape = {
    .bufferHalfBytes  = 2 * sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS202GasStationShapeSkeleton),
    .partVertexCounts = _gMappicS202GasStationShapePartVerts,
    .verts            = _gMappicS202GasStationShapeVerts,
    .normals          = &_gMappicS202GasStationShapeVerts[ARRAY_SIZE(_gMappicS202GasStationShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS202GasStationShapeSkeleton,
    .stream           = _gMappicS202GasStationShapeStream,
};

/// Identity transform and self-parented root for the Main Street shape.
#ifdef PE_EMBED_ASSETS
static TmdBone _gMappicS202MainStreetShapeSkeleton[] = {
#include "assets/mappic_s2_02_model_00C48_0011C_skeleton.inc"
};
#else
static TmdBone _gMappicS202MainStreetShapeSkeleton[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_0011C_skeleton", _gMappicS202MainStreetShapeSkeleton);

/// Vertex count of the Main Street shape's sole part (four vertices).
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS202MainStreetShapePartVerts[] = {
#include "assets/mappic_s2_02_model_00C48_0011C_partVerts.inc"
};
#else
static u32 _gMappicS202MainStreetShapePartVerts[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_0011C_partVerts", _gMappicS202MainStreetShapePartVerts);

/// Main Street's map footprint in integer model X/Z coordinates, with Y zero.
#ifdef PE_EMBED_ASSETS
static SVECTOR _gMappicS202MainStreetShapeVerts[] = {
#include "assets/mappic_s2_02_model_00C48_0011C_verts.inc"
};
#else
static SVECTOR _gMappicS202MainStreetShapeVerts[4];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_0011C_verts", _gMappicS202MainStreetShapeVerts);

/// One unlit quad's packed vertex byte offsets and white colour, followed by two group ends and the stream end.
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS202MainStreetShapeStream[] = {
#include "assets/mappic_s2_02_model_00C48_0011C_stream.inc"
};
#else
static u32 _gMappicS202MainStreetShapeStream[9];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_0011C_stream", _gMappicS202MainStreetShapeStream);

TmdSource gMappicS202MainStreetShape = {
    .bufferHalfBytes  = sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS202MainStreetShapeSkeleton),
    .partVertexCounts = _gMappicS202MainStreetShapePartVerts,
    .verts            = _gMappicS202MainStreetShapeVerts,
    .normals          = &_gMappicS202MainStreetShapeVerts[ARRAY_SIZE(_gMappicS202MainStreetShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS202MainStreetShapeSkeleton,
    .stream           = _gMappicS202MainStreetShapeStream,
};

/// Identity transform and self-parented root for the General Store shape.
#ifdef PE_EMBED_ASSETS
static TmdBone _gMappicS202GeneralStoreShapeSkeleton[] = {
#include "assets/mappic_s2_02_model_00C48_001AC_skeleton.inc"
};
#else
static TmdBone _gMappicS202GeneralStoreShapeSkeleton[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_001AC_skeleton", _gMappicS202GeneralStoreShapeSkeleton);

/// Vertex count of the General Store shape's sole part (four vertices).
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS202GeneralStoreShapePartVerts[] = {
#include "assets/mappic_s2_02_model_00C48_001AC_partVerts.inc"
};
#else
static u32 _gMappicS202GeneralStoreShapePartVerts[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_001AC_partVerts", _gMappicS202GeneralStoreShapePartVerts);

/// General Store's map footprint in integer model X/Z coordinates, with Y zero.
#ifdef PE_EMBED_ASSETS
static SVECTOR _gMappicS202GeneralStoreShapeVerts[] = {
#include "assets/mappic_s2_02_model_00C48_001AC_verts.inc"
};
#else
static SVECTOR _gMappicS202GeneralStoreShapeVerts[4];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_001AC_verts", _gMappicS202GeneralStoreShapeVerts);

/// Packed command stream for the General Store shape's single unlit quad.
///
/// Four SVECTOR byte offsets and white colour; two group ends precede the
/// stream end. The map reads only the first group.
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS202GeneralStoreShapeStream[] = {
#include "assets/mappic_s2_02_model_00C48_001AC_stream.inc"
};
#else
static u32 _gMappicS202GeneralStoreShapeStream[9];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_001AC_stream", _gMappicS202GeneralStoreShapeStream);

TmdSource gMappicS202GeneralStoreShape = {
    .bufferHalfBytes  = sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS202GeneralStoreShapeSkeleton),
    .partVertexCounts = _gMappicS202GeneralStoreShapePartVerts,
    .verts            = _gMappicS202GeneralStoreShapeVerts,
    .normals          = &_gMappicS202GeneralStoreShapeVerts[ARRAY_SIZE(_gMappicS202GeneralStoreShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS202GeneralStoreShapeSkeleton,
    .stream           = _gMappicS202GeneralStoreShapeStream,
};

/// Identity transform and self-parented root for the Back Street shape.
#ifdef PE_EMBED_ASSETS
static TmdBone _gMappicS202BackStreetShapeSkeleton[] = {
#include "assets/mappic_s4_00_model_0005C_00258_skeleton.inc"
};
#else
static TmdBone _gMappicS202BackStreetShapeSkeleton[1];
#endif
PE_ASSET_BIND("mappic_s4_00_model_0005C_00258_skeleton", _gMappicS202BackStreetShapeSkeleton);

/// Vertex count of the Back Street shape's sole part (six vertices).
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS202BackStreetShapePartVerts[] = {
#include "assets/mappic_s4_00_model_0005C_00258_partVerts.inc"
};
#else
static u32 _gMappicS202BackStreetShapePartVerts[1];
#endif
PE_ASSET_BIND("mappic_s4_00_model_0005C_00258_partVerts", _gMappicS202BackStreetShapePartVerts);

/// Back Street's map footprint in integer model X/Z coordinates, with Y zero.
#ifdef PE_EMBED_ASSETS
static SVECTOR _gMappicS202BackStreetShapeVerts[] = {
#include "assets/mappic_s4_00_model_0005C_00258_verts.inc"
};
#else
static SVECTOR _gMappicS202BackStreetShapeVerts[6];
#endif
PE_ASSET_BIND("mappic_s4_00_model_0005C_00258_verts", _gMappicS202BackStreetShapeVerts);

/// Packed command stream for the Back Street shape's two unlit quads.
///
/// Four SVECTOR byte offsets and white colour per quad; two group ends precede
/// the stream end. The map reads only the first group.
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS202BackStreetShapeStream[] = {
#include "assets/mappic_s4_00_model_0005C_00258_stream.inc"
};
#else
static u32 _gMappicS202BackStreetShapeStream[12];
#endif
PE_ASSET_BIND("mappic_s4_00_model_0005C_00258_stream", _gMappicS202BackStreetShapeStream);

TmdSource gMappicS202BackStreetShape = {
    .bufferHalfBytes  = 2 * sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS202BackStreetShapeSkeleton),
    .partVertexCounts = _gMappicS202BackStreetShapePartVerts,
    .verts            = _gMappicS202BackStreetShapeVerts,
    .normals          = &_gMappicS202BackStreetShapeVerts[ARRAY_SIZE(_gMappicS202BackStreetShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS202BackStreetShapeSkeleton,
    .stream           = _gMappicS202BackStreetShapeStream,
};

/// Identity transform and self-parented root for the Souvenir Shop shape.
#ifdef PE_EMBED_ASSETS
static TmdBone _gMappicS202SouvenirShopShapeSkeleton[] = {
#include "assets/mappic_s2_02_model_00C48_002E8_skeleton.inc"
};
#else
static TmdBone _gMappicS202SouvenirShopShapeSkeleton[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_002E8_skeleton", _gMappicS202SouvenirShopShapeSkeleton);

/// Vertex count of the Souvenir Shop shape's sole part (four vertices).
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS202SouvenirShopShapePartVerts[] = {
#include "assets/mappic_s2_02_model_00C48_002E8_partVerts.inc"
};
#else
static u32 _gMappicS202SouvenirShopShapePartVerts[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_002E8_partVerts", _gMappicS202SouvenirShopShapePartVerts);

/// Souvenir Shop's map footprint in integer model X/Z coordinates, with Y zero.
#ifdef PE_EMBED_ASSETS
static SVECTOR _gMappicS202SouvenirShopShapeVerts[] = {
#include "assets/mappic_s2_02_model_00C48_002E8_verts.inc"
};
#else
static SVECTOR _gMappicS202SouvenirShopShapeVerts[4];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_002E8_verts", _gMappicS202SouvenirShopShapeVerts);

/// Packed command stream for the Souvenir Shop shape's single unlit quad.
///
/// Four SVECTOR byte offsets and white colour; two group ends precede the
/// stream end. The map reads only the first group.
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS202SouvenirShopShapeStream[] = {
#include "assets/mappic_s2_02_model_00C48_002E8_stream.inc"
};
#else
static u32 _gMappicS202SouvenirShopShapeStream[9];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_002E8_stream", _gMappicS202SouvenirShopShapeStream);

TmdSource gMappicS202SouvenirShopShape = {
    .bufferHalfBytes  = sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS202SouvenirShopShapeSkeleton),
    .partVertexCounts = _gMappicS202SouvenirShopShapePartVerts,
    .verts            = _gMappicS202SouvenirShopShapeVerts,
    .normals          = &_gMappicS202SouvenirShopShapeVerts[ARRAY_SIZE(_gMappicS202SouvenirShopShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS202SouvenirShopShapeSkeleton,
    .stream           = _gMappicS202SouvenirShopShapeStream,
};

/// Identity transform and self-parented root for the Warehouse shape.
#ifdef PE_EMBED_ASSETS
static TmdBone _gMappicS202WarehouseShapeSkeleton[] = {
#include "assets/mappic_s2_02_model_00C48_00378_skeleton.inc"
};
#else
static TmdBone _gMappicS202WarehouseShapeSkeleton[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_00378_skeleton", _gMappicS202WarehouseShapeSkeleton);

/// Vertex count of the Warehouse shape's sole part (four vertices).
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS202WarehouseShapePartVerts[] = {
#include "assets/mappic_s2_02_model_00C48_00378_partVerts.inc"
};
#else
static u32 _gMappicS202WarehouseShapePartVerts[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_00378_partVerts", _gMappicS202WarehouseShapePartVerts);

/// Warehouse's map footprint in integer model X/Z coordinates, with Y zero.
#ifdef PE_EMBED_ASSETS
static SVECTOR _gMappicS202WarehouseShapeVerts[] = {
#include "assets/mappic_s2_02_model_00C48_00378_verts.inc"
};
#else
static SVECTOR _gMappicS202WarehouseShapeVerts[4];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_00378_verts", _gMappicS202WarehouseShapeVerts);

/// Packed command stream for the Warehouse shape's single unlit quad.
///
/// Four SVECTOR byte offsets and white colour; two group ends precede the
/// stream end. The map reads only the first group.
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS202WarehouseShapeStream[] = {
#include "assets/mappic_s2_02_model_00C48_00378_stream.inc"
};
#else
static u32 _gMappicS202WarehouseShapeStream[9];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_00378_stream", _gMappicS202WarehouseShapeStream);

TmdSource gMappicS202WarehouseShape = {
    .bufferHalfBytes  = sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS202WarehouseShapeSkeleton),
    .partVertexCounts = _gMappicS202WarehouseShapePartVerts,
    .verts            = _gMappicS202WarehouseShapeVerts,
    .normals          = &_gMappicS202WarehouseShapeVerts[ARRAY_SIZE(_gMappicS202WarehouseShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS202WarehouseShapeSkeleton,
    .stream           = _gMappicS202WarehouseShapeStream,
};

/// Identity transform and self-parented root for the Dilapidated house shape.
#ifdef PE_EMBED_ASSETS
static TmdBone _gMappicS202DilapidatedHouseShapeSkeleton[] = {
#include "assets/mappic_s4_00_model_0005C_00424_skeleton.inc"
};
#else
static TmdBone _gMappicS202DilapidatedHouseShapeSkeleton[1];
#endif
PE_ASSET_BIND("mappic_s4_00_model_0005C_00424_skeleton", _gMappicS202DilapidatedHouseShapeSkeleton);

/// Vertex count of the Dilapidated house shape's sole part (six vertices).
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS202DilapidatedHouseShapePartVerts[] = {
#include "assets/mappic_s4_00_model_0005C_00424_partVerts.inc"
};
#else
static u32 _gMappicS202DilapidatedHouseShapePartVerts[1];
#endif
PE_ASSET_BIND("mappic_s4_00_model_0005C_00424_partVerts", _gMappicS202DilapidatedHouseShapePartVerts);

/// Dilapidated house's map footprint in integer model X/Z coordinates, with Y zero.
#ifdef PE_EMBED_ASSETS
static SVECTOR _gMappicS202DilapidatedHouseShapeVerts[] = {
#include "assets/mappic_s4_00_model_0005C_00424_verts.inc"
};
#else
static SVECTOR _gMappicS202DilapidatedHouseShapeVerts[6];
#endif
PE_ASSET_BIND("mappic_s4_00_model_0005C_00424_verts", _gMappicS202DilapidatedHouseShapeVerts);

/// Two unlit quads' packed vertex byte offsets and white colour, then two group ends and the stream end.
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS202DilapidatedHouseShapeStream[] = {
#include "assets/mappic_s4_00_model_0005C_00424_stream.inc"
};
#else
static u32 _gMappicS202DilapidatedHouseShapeStream[12];
#endif
PE_ASSET_BIND("mappic_s4_00_model_0005C_00424_stream", _gMappicS202DilapidatedHouseShapeStream);

TmdSource gMappicS202DilapidatedHouseShape = {
    .bufferHalfBytes  = 2 * sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS202DilapidatedHouseShapeSkeleton),
    .partVertexCounts = _gMappicS202DilapidatedHouseShapePartVerts,
    .verts            = _gMappicS202DilapidatedHouseShapeVerts,
    .normals          = &_gMappicS202DilapidatedHouseShapeVerts[ARRAY_SIZE(_gMappicS202DilapidatedHouseShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS202DilapidatedHouseShapeSkeleton,
    .stream           = _gMappicS202DilapidatedHouseShapeStream,
};

/// Identity transform and self-parented root for the Motel room 1 shape.
#ifdef PE_EMBED_ASSETS
static TmdBone _gMappicS202MotelRoom1ShapeSkeleton[] = {
#include "assets/mappic_s2_02_model_00C48_004B4_skeleton.inc"
};
#else
static TmdBone _gMappicS202MotelRoom1ShapeSkeleton[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_004B4_skeleton", _gMappicS202MotelRoom1ShapeSkeleton);

/// Vertex count of the Motel room 1 shape's sole part (four vertices).
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS202MotelRoom1ShapePartVerts[] = {
#include "assets/mappic_s2_02_model_00C48_004B4_partVerts.inc"
};
#else
static u32 _gMappicS202MotelRoom1ShapePartVerts[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_004B4_partVerts", _gMappicS202MotelRoom1ShapePartVerts);

/// Motel room 1's map footprint in integer model X/Z coordinates, with Y zero.
#ifdef PE_EMBED_ASSETS
static SVECTOR _gMappicS202MotelRoom1ShapeVerts[] = {
#include "assets/mappic_s2_02_model_00C48_004B4_verts.inc"
};
#else
static SVECTOR _gMappicS202MotelRoom1ShapeVerts[4];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_004B4_verts", _gMappicS202MotelRoom1ShapeVerts);

/// Packed command stream for the Motel room 1 shape's single unlit quad.
///
/// Four SVECTOR byte offsets and white colour; two group ends precede the
/// stream end. The map reads only the first group.
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS202MotelRoom1ShapeStream[] = {
#include "assets/mappic_s2_02_model_00C48_004B4_stream.inc"
};
#else
static u32 _gMappicS202MotelRoom1ShapeStream[9];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_004B4_stream", _gMappicS202MotelRoom1ShapeStream);

TmdSource gMappicS202MotelRoom1Shape = {
    .bufferHalfBytes  = sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS202MotelRoom1ShapeSkeleton),
    .partVertexCounts = _gMappicS202MotelRoom1ShapePartVerts,
    .verts            = _gMappicS202MotelRoom1ShapeVerts,
    .normals          = &_gMappicS202MotelRoom1ShapeVerts[ARRAY_SIZE(_gMappicS202MotelRoom1ShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS202MotelRoom1ShapeSkeleton,
    .stream           = _gMappicS202MotelRoom1ShapeStream,
};

/// Identity transform and self-parented root for the Motel room 2 shape.
#ifdef PE_EMBED_ASSETS
static TmdBone _gMappicS202MotelRoom2ShapeSkeleton[] = {
#include "assets/mappic_s2_02_model_00C48_00544_skeleton.inc"
};
#else
static TmdBone _gMappicS202MotelRoom2ShapeSkeleton[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_00544_skeleton", _gMappicS202MotelRoom2ShapeSkeleton);

/// Vertex count of the Motel room 2 shape's sole part (four vertices).
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS202MotelRoom2ShapePartVerts[] = {
#include "assets/mappic_s2_02_model_00C48_00544_partVerts.inc"
};
#else
static u32 _gMappicS202MotelRoom2ShapePartVerts[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_00544_partVerts", _gMappicS202MotelRoom2ShapePartVerts);

/// Motel room 2's map footprint in integer model X/Z coordinates, with Y zero.
#ifdef PE_EMBED_ASSETS
static SVECTOR _gMappicS202MotelRoom2ShapeVerts[] = {
#include "assets/mappic_s2_02_model_00C48_00544_verts.inc"
};
#else
static SVECTOR _gMappicS202MotelRoom2ShapeVerts[4];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_00544_verts", _gMappicS202MotelRoom2ShapeVerts);

/// Packed command stream for the Motel room 2 shape's single unlit quad.
///
/// Four SVECTOR byte offsets and white colour; two group ends precede the
/// stream end. The map reads only the first group.
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS202MotelRoom2ShapeStream[] = {
#include "assets/mappic_s2_02_model_00C48_00544_stream.inc"
};
#else
static u32 _gMappicS202MotelRoom2ShapeStream[9];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_00544_stream", _gMappicS202MotelRoom2ShapeStream);

TmdSource gMappicS202MotelRoom2Shape = {
    .bufferHalfBytes  = sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS202MotelRoom2ShapeSkeleton),
    .partVertexCounts = _gMappicS202MotelRoom2ShapePartVerts,
    .verts            = _gMappicS202MotelRoom2ShapeVerts,
    .normals          = &_gMappicS202MotelRoom2ShapeVerts[ARRAY_SIZE(_gMappicS202MotelRoom2ShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS202MotelRoom2ShapeSkeleton,
    .stream           = _gMappicS202MotelRoom2ShapeStream,
};

/// Identity transform and self-parented root for the Motel room 3 shape.
#ifdef PE_EMBED_ASSETS
static TmdBone _gMappicS202MotelRoom3ShapeSkeleton[] = {
#include "assets/mappic_s2_02_model_00C48_005D4_skeleton.inc"
};
#else
static TmdBone _gMappicS202MotelRoom3ShapeSkeleton[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_005D4_skeleton", _gMappicS202MotelRoom3ShapeSkeleton);

/// Vertex count of the Motel room 3 shape's sole part (four vertices).
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS202MotelRoom3ShapePartVerts[] = {
#include "assets/mappic_s2_02_model_00C48_005D4_partVerts.inc"
};
#else
static u32 _gMappicS202MotelRoom3ShapePartVerts[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_005D4_partVerts", _gMappicS202MotelRoom3ShapePartVerts);

/// Motel room 3's map footprint in integer model X/Z coordinates, with Y zero.
#ifdef PE_EMBED_ASSETS
static SVECTOR _gMappicS202MotelRoom3ShapeVerts[] = {
#include "assets/mappic_s2_02_model_00C48_005D4_verts.inc"
};
#else
static SVECTOR _gMappicS202MotelRoom3ShapeVerts[4];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_005D4_verts", _gMappicS202MotelRoom3ShapeVerts);

/// Packed command stream for the Motel room 3 shape's single unlit quad.
///
/// Four SVECTOR byte offsets and white colour; two group ends precede the
/// stream end. The map reads only the first group.
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS202MotelRoom3ShapeStream[] = {
#include "assets/mappic_s2_02_model_00C48_005D4_stream.inc"
};
#else
static u32 _gMappicS202MotelRoom3ShapeStream[9];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_005D4_stream", _gMappicS202MotelRoom3ShapeStream);

TmdSource gMappicS202MotelRoom3Shape = {
    .bufferHalfBytes  = sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS202MotelRoom3ShapeSkeleton),
    .partVertexCounts = _gMappicS202MotelRoom3ShapePartVerts,
    .verts            = _gMappicS202MotelRoom3ShapeVerts,
    .normals          = &_gMappicS202MotelRoom3ShapeVerts[ARRAY_SIZE(_gMappicS202MotelRoom3ShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS202MotelRoom3ShapeSkeleton,
    .stream           = _gMappicS202MotelRoom3ShapeStream,
};

/// Identity transform and self-parented root for the Motel room 4 shape.
#ifdef PE_EMBED_ASSETS
static TmdBone _gMappicS202MotelRoom4ShapeSkeleton[] = {
#include "assets/mappic_s2_02_model_00C48_00664_skeleton.inc"
};
#else
static TmdBone _gMappicS202MotelRoom4ShapeSkeleton[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_00664_skeleton", _gMappicS202MotelRoom4ShapeSkeleton);

/// Vertex count of the Motel room 4 shape's sole part (four vertices).
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS202MotelRoom4ShapePartVerts[] = {
#include "assets/mappic_s2_02_model_00C48_00664_partVerts.inc"
};
#else
static u32 _gMappicS202MotelRoom4ShapePartVerts[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_00664_partVerts", _gMappicS202MotelRoom4ShapePartVerts);

/// Motel room 4's map footprint in integer model X/Z coordinates, with Y zero.
#ifdef PE_EMBED_ASSETS
static SVECTOR _gMappicS202MotelRoom4ShapeVerts[] = {
#include "assets/mappic_s2_02_model_00C48_00664_verts.inc"
};
#else
static SVECTOR _gMappicS202MotelRoom4ShapeVerts[4];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_00664_verts", _gMappicS202MotelRoom4ShapeVerts);

/// Packed command stream for the Motel room 4 shape's single unlit quad.
///
/// Four SVECTOR byte offsets and white colour; two group ends precede the
/// stream end. The map reads only the first group.
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS202MotelRoom4ShapeStream[] = {
#include "assets/mappic_s2_02_model_00C48_00664_stream.inc"
};
#else
static u32 _gMappicS202MotelRoom4ShapeStream[9];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_00664_stream", _gMappicS202MotelRoom4ShapeStream);

TmdSource gMappicS202MotelRoom4Shape = {
    .bufferHalfBytes  = sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS202MotelRoom4ShapeSkeleton),
    .partVertexCounts = _gMappicS202MotelRoom4ShapePartVerts,
    .verts            = _gMappicS202MotelRoom4ShapeVerts,
    .normals          = &_gMappicS202MotelRoom4ShapeVerts[ARRAY_SIZE(_gMappicS202MotelRoom4ShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS202MotelRoom4ShapeSkeleton,
    .stream           = _gMappicS202MotelRoom4ShapeStream,
};

/// Identity transform and self-parented root for the Parking lot shape.
#ifdef PE_EMBED_ASSETS
static TmdBone _gMappicS202ParkingLotShapeSkeleton[] = {
#include "assets/mappic_s2_02_model_00710_skeleton.inc"
};
#else
static TmdBone _gMappicS202ParkingLotShapeSkeleton[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00710_skeleton", _gMappicS202ParkingLotShapeSkeleton);

/// Vertex count of the Parking lot shape's sole part (twelve vertices).
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS202ParkingLotShapePartVerts[] = {
#include "assets/mappic_s2_02_model_00710_partVerts.inc"
};
#else
static u32 _gMappicS202ParkingLotShapePartVerts[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00710_partVerts", _gMappicS202ParkingLotShapePartVerts);

/// Parking lot's map footprint in integer model X/Z coordinates, with Y zero.
#ifdef PE_EMBED_ASSETS
static SVECTOR _gMappicS202ParkingLotShapeVerts[] = {
#include "assets/mappic_s2_02_model_00710_verts.inc"
};
#else
static SVECTOR _gMappicS202ParkingLotShapeVerts[12];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00710_verts", _gMappicS202ParkingLotShapeVerts);

/// Packed command stream for the Parking lot shape's five unlit quads.
///
/// Each quad has four SVECTOR byte offsets and white colour; two group ends
/// precede the stream end. The map reads only the first group.
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS202ParkingLotShapeStream[] = {
#include "assets/mappic_s2_02_model_00710_stream.inc"
};
#else
static u32 _gMappicS202ParkingLotShapeStream[21];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00710_stream", _gMappicS202ParkingLotShapeStream);

TmdSource gMappicS202ParkingLotShape = {
    .bufferHalfBytes  = 5 * sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS202ParkingLotShapeSkeleton),
    .partVertexCounts = _gMappicS202ParkingLotShapePartVerts,
    .verts            = _gMappicS202ParkingLotShapeVerts,
    .normals          = &_gMappicS202ParkingLotShapeVerts[ARRAY_SIZE(_gMappicS202ParkingLotShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS202ParkingLotShapeSkeleton,
    .stream           = _gMappicS202ParkingLotShapeStream,
};

/// Identity transform and self-parented root for the Toilet shape.
#ifdef PE_EMBED_ASSETS
static TmdBone _gMappicS202ToiletShapeSkeleton[] = {
#include "assets/mappic_s2_02_model_00C48_007F4_skeleton.inc"
};
#else
static TmdBone _gMappicS202ToiletShapeSkeleton[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_007F4_skeleton", _gMappicS202ToiletShapeSkeleton);

/// Vertex count of the Toilet shape's sole part (four vertices).
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS202ToiletShapePartVerts[] = {
#include "assets/mappic_s2_02_model_00C48_007F4_partVerts.inc"
};
#else
static u32 _gMappicS202ToiletShapePartVerts[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_007F4_partVerts", _gMappicS202ToiletShapePartVerts);

/// Toilet's map footprint in integer model X/Z coordinates, with Y zero.
#ifdef PE_EMBED_ASSETS
static SVECTOR _gMappicS202ToiletShapeVerts[] = {
#include "assets/mappic_s2_02_model_00C48_007F4_verts.inc"
};
#else
static SVECTOR _gMappicS202ToiletShapeVerts[4];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_007F4_verts", _gMappicS202ToiletShapeVerts);

/// Packed command stream for the Toilet shape's unlit quad.
///
/// Four SVECTOR byte offsets and white colour precede two group ends and
/// the stream end. The map reads only the first group.
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS202ToiletShapeStream[] = {
#include "assets/mappic_s2_02_model_00C48_007F4_stream.inc"
};
#else
static u32 _gMappicS202ToiletShapeStream[9];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_007F4_stream", _gMappicS202ToiletShapeStream);

TmdSource gMappicS202ToiletShape = {
    .bufferHalfBytes  = sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS202ToiletShapeSkeleton),
    .partVertexCounts = _gMappicS202ToiletShapePartVerts,
    .verts            = _gMappicS202ToiletShapeVerts,
    .normals          = &_gMappicS202ToiletShapeVerts[ARRAY_SIZE(_gMappicS202ToiletShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS202ToiletShapeSkeleton,
    .stream           = _gMappicS202ToiletShapeStream,
};

/// Identity transform and self-parented root for the Motel lobby shape.
#ifdef PE_EMBED_ASSETS
static TmdBone _gMappicS202MotelLobbyShapeSkeleton[] = {
#include "assets/mappic_s2_02_model_00C48_00884_skeleton.inc"
};
#else
static TmdBone _gMappicS202MotelLobbyShapeSkeleton[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_00884_skeleton", _gMappicS202MotelLobbyShapeSkeleton);

/// Vertex count of the Motel lobby shape's sole part (four vertices).
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS202MotelLobbyShapePartVerts[] = {
#include "assets/mappic_s2_02_model_00C48_00884_partVerts.inc"
};
#else
static u32 _gMappicS202MotelLobbyShapePartVerts[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_00884_partVerts", _gMappicS202MotelLobbyShapePartVerts);

/// Motel lobby's map footprint in integer model X/Z coordinates, with Y zero.
#ifdef PE_EMBED_ASSETS
static SVECTOR _gMappicS202MotelLobbyShapeVerts[] = {
#include "assets/mappic_s2_02_model_00C48_00884_verts.inc"
};
#else
static SVECTOR _gMappicS202MotelLobbyShapeVerts[4];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_00884_verts", _gMappicS202MotelLobbyShapeVerts);

/// Packed command stream for the Motel lobby shape's single unlit quad.
///
/// Four SVECTOR byte offsets and white colour; two group ends precede the
/// stream end. The map reads only the first group.
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS202MotelLobbyShapeStream[] = {
#include "assets/mappic_s2_02_model_00C48_00884_stream.inc"
};
#else
static u32 _gMappicS202MotelLobbyShapeStream[9];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_00884_stream", _gMappicS202MotelLobbyShapeStream);

TmdSource gMappicS202MotelLobbyShape = {
    .bufferHalfBytes  = sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS202MotelLobbyShapeSkeleton),
    .partVertexCounts = _gMappicS202MotelLobbyShapePartVerts,
    .verts            = _gMappicS202MotelLobbyShapeVerts,
    .normals          = &_gMappicS202MotelLobbyShapeVerts[ARRAY_SIZE(_gMappicS202MotelLobbyShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS202MotelLobbyShapeSkeleton,
    .stream           = _gMappicS202MotelLobbyShapeStream,
};

/// Identity transform and self-parented root for the Saloon G & R shape.
#ifdef PE_EMBED_ASSETS
static TmdBone _gMappicS202SaloonGRShapeSkeleton[] = {
#include "assets/mappic_s2_02_model_00910_skeleton.inc"
};
#else
static TmdBone _gMappicS202SaloonGRShapeSkeleton[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00910_skeleton", _gMappicS202SaloonGRShapeSkeleton);

/// Vertex count of the Saloon G & R shape's sole part (eight vertices).
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS202SaloonGRShapePartVerts[] = {
#include "assets/mappic_s2_02_model_00910_partVerts.inc"
};
#else
static u32 _gMappicS202SaloonGRShapePartVerts[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00910_partVerts", _gMappicS202SaloonGRShapePartVerts);

/// Saloon G & R's map footprint in integer model X/Z coordinates, with Y zero.
#ifdef PE_EMBED_ASSETS
static SVECTOR _gMappicS202SaloonGRShapeVerts[] = {
#include "assets/mappic_s2_02_model_00910_verts.inc"
};
#else
static SVECTOR _gMappicS202SaloonGRShapeVerts[8];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00910_verts", _gMappicS202SaloonGRShapeVerts);

/// Packed command stream for the Saloon G & R shape's two unlit triangles and two unlit quads.
///
/// Elements contain SVECTOR byte offsets and white colour; two group ends
/// precede the stream end. The map reads only the first group.
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS202SaloonGRShapeStream[] = {
#include "assets/mappic_s2_02_model_00910_stream.inc"
};
#else
static u32 _gMappicS202SaloonGRShapeStream[21];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00910_stream", _gMappicS202SaloonGRShapeStream);

TmdSource gMappicS202SaloonGRShape = {
    .bufferHalfBytes  = 2 * sizeof(POLY_F3) + 2 * sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS202SaloonGRShapeSkeleton),
    .partVertexCounts = _gMappicS202SaloonGRShapePartVerts,
    .verts            = _gMappicS202SaloonGRShapeVerts,
    .normals          = &_gMappicS202SaloonGRShapeVerts[ARRAY_SIZE(_gMappicS202SaloonGRShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS202SaloonGRShapeSkeleton,
    .stream           = _gMappicS202SaloonGRShapeStream,
};

/// Identity transform and self-parented root for the G & R Kitchen shape.
#ifdef PE_EMBED_ASSETS
static TmdBone _gMappicS202GRKitchenShapeSkeleton[] = {
#include "assets/mappic_s2_02_model_00C48_009F4_skeleton.inc"
};
#else
static TmdBone _gMappicS202GRKitchenShapeSkeleton[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_009F4_skeleton", _gMappicS202GRKitchenShapeSkeleton);

/// Vertex count of the G & R Kitchen shape's sole part (four vertices).
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS202GRKitchenShapePartVerts[] = {
#include "assets/mappic_s2_02_model_00C48_009F4_partVerts.inc"
};
#else
static u32 _gMappicS202GRKitchenShapePartVerts[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_009F4_partVerts", _gMappicS202GRKitchenShapePartVerts);

/// G & R Kitchen's map footprint in integer model X/Z coordinates, with Y zero.
#ifdef PE_EMBED_ASSETS
static SVECTOR _gMappicS202GRKitchenShapeVerts[] = {
#include "assets/mappic_s2_02_model_00C48_009F4_verts.inc"
};
#else
static SVECTOR _gMappicS202GRKitchenShapeVerts[4];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_009F4_verts", _gMappicS202GRKitchenShapeVerts);

/// Packed command stream for the G & R Kitchen shape's single unlit quad.
///
/// Four SVECTOR byte offsets and white colour; two group ends precede the
/// stream end. The map reads only the first group.
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS202GRKitchenShapeStream[] = {
#include "assets/mappic_s2_02_model_00C48_009F4_stream.inc"
};
#else
static u32 _gMappicS202GRKitchenShapeStream[9];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_009F4_stream", _gMappicS202GRKitchenShapeStream);

TmdSource gMappicS202GRKitchenShape = {
    .bufferHalfBytes  = sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS202GRKitchenShapeSkeleton),
    .partVertexCounts = _gMappicS202GRKitchenShapePartVerts,
    .verts            = _gMappicS202GRKitchenShapeVerts,
    .normals          = &_gMappicS202GRKitchenShapeVerts[ARRAY_SIZE(_gMappicS202GRKitchenShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS202GRKitchenShapeSkeleton,
    .stream           = _gMappicS202GRKitchenShapeStream,
};

/// Identity transform and self-parented root for the Water Tower shape.
#ifdef PE_EMBED_ASSETS
static TmdBone _gMappicS202WaterTowerShapeSkeleton[] = {
#include "assets/mappic_s4_00_model_0005C_00AA0_skeleton.inc"
};
#else
static TmdBone _gMappicS202WaterTowerShapeSkeleton[1];
#endif
PE_ASSET_BIND("mappic_s4_00_model_0005C_00AA0_skeleton", _gMappicS202WaterTowerShapeSkeleton);

/// Vertex count of the Water Tower shape's sole part (six vertices).
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS202WaterTowerShapePartVerts[] = {
#include "assets/mappic_s4_00_model_0005C_00AA0_partVerts.inc"
};
#else
static u32 _gMappicS202WaterTowerShapePartVerts[1];
#endif
PE_ASSET_BIND("mappic_s4_00_model_0005C_00AA0_partVerts", _gMappicS202WaterTowerShapePartVerts);

/// Water Tower's map footprint in integer model X/Z coordinates, with Y zero.
#ifdef PE_EMBED_ASSETS
static SVECTOR _gMappicS202WaterTowerShapeVerts[] = {
#include "assets/mappic_s4_00_model_0005C_00AA0_verts.inc"
};
#else
static SVECTOR _gMappicS202WaterTowerShapeVerts[6];
#endif
PE_ASSET_BIND("mappic_s4_00_model_0005C_00AA0_verts", _gMappicS202WaterTowerShapeVerts);

/// Packed command stream for the Water Tower shape's two unlit quads.
///
/// Each quad has four packed SVECTOR byte offsets and white colour; two group
/// ends precede the stream end. The map reads only the first group.
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS202WaterTowerShapeStream[] = {
#include "assets/mappic_s4_00_model_0005C_00AA0_stream.inc"
};
#else
static u32 _gMappicS202WaterTowerShapeStream[12];
#endif
PE_ASSET_BIND("mappic_s4_00_model_0005C_00AA0_stream", _gMappicS202WaterTowerShapeStream);

TmdSource gMappicS202WaterTowerShape = {
    .bufferHalfBytes  = 2 * sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS202WaterTowerShapeSkeleton),
    .partVertexCounts = _gMappicS202WaterTowerShapePartVerts,
    .verts            = _gMappicS202WaterTowerShapeVerts,
    .normals          = &_gMappicS202WaterTowerShapeVerts[ARRAY_SIZE(_gMappicS202WaterTowerShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS202WaterTowerShapeSkeleton,
    .stream           = _gMappicS202WaterTowerShapeStream,
};

/// Identity transform and self-parented root for the Breezeway shape.
#ifdef PE_EMBED_ASSETS
static TmdBone _gMappicS202BreezewayShapeSkeleton[] = {
#include "assets/mappic_s4_00_model_0005C_00B4C_skeleton.inc"
};
#else
static TmdBone _gMappicS202BreezewayShapeSkeleton[1];
#endif
PE_ASSET_BIND("mappic_s4_00_model_0005C_00B4C_skeleton", _gMappicS202BreezewayShapeSkeleton);

/// Vertex count of the Breezeway shape's sole part (six vertices).
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS202BreezewayShapePartVerts[] = {
#include "assets/mappic_s4_00_model_0005C_00B4C_partVerts.inc"
};
#else
static u32 _gMappicS202BreezewayShapePartVerts[1];
#endif
PE_ASSET_BIND("mappic_s4_00_model_0005C_00B4C_partVerts", _gMappicS202BreezewayShapePartVerts);

/// Breezeway's map footprint in integer model X/Z coordinates, with Y zero.
#ifdef PE_EMBED_ASSETS
static SVECTOR _gMappicS202BreezewayShapeVerts[] = {
#include "assets/mappic_s4_00_model_0005C_00B4C_verts.inc"
};
#else
static SVECTOR _gMappicS202BreezewayShapeVerts[6];
#endif
PE_ASSET_BIND("mappic_s4_00_model_0005C_00B4C_verts", _gMappicS202BreezewayShapeVerts);

/// Packed command stream for the Breezeway shape's two unlit quads.
///
/// Each quad has four packed SVECTOR byte offsets and white colour; two group
/// ends precede the stream end. The map reads only the first group.
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS202BreezewayShapeStream[] = {
#include "assets/mappic_s4_00_model_0005C_00B4C_stream.inc"
};
#else
static u32 _gMappicS202BreezewayShapeStream[12];
#endif
PE_ASSET_BIND("mappic_s4_00_model_0005C_00B4C_stream", _gMappicS202BreezewayShapeStream);

TmdSource gMappicS202BreezewayShape = {
    .bufferHalfBytes  = 2 * sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS202BreezewayShapeSkeleton),
    .partVertexCounts = _gMappicS202BreezewayShapePartVerts,
    .verts            = _gMappicS202BreezewayShapeVerts,
    .normals          = &_gMappicS202BreezewayShapeVerts[ARRAY_SIZE(_gMappicS202BreezewayShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS202BreezewayShapeSkeleton,
    .stream           = _gMappicS202BreezewayShapeStream,
};

/// Identity transform and self-parented root for the Factory shape.
#ifdef PE_EMBED_ASSETS
static TmdBone _gMappicS202FactoryShapeSkeleton[] = {
#include "assets/mappic_s2_02_model_00C48_00BDC_skeleton.inc"
};
#else
static TmdBone _gMappicS202FactoryShapeSkeleton[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_00BDC_skeleton", _gMappicS202FactoryShapeSkeleton);

/// Vertex count of the Factory shape's sole part (four vertices).
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS202FactoryShapePartVerts[] = {
#include "assets/mappic_s2_02_model_00C48_00BDC_partVerts.inc"
};
#else
static u32 _gMappicS202FactoryShapePartVerts[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_00BDC_partVerts", _gMappicS202FactoryShapePartVerts);

/// Factory's map footprint in integer model X/Z coordinates, with Y zero.
#ifdef PE_EMBED_ASSETS
static SVECTOR _gMappicS202FactoryShapeVerts[] = {
#include "assets/mappic_s2_02_model_00C48_00BDC_verts.inc"
};
#else
static SVECTOR _gMappicS202FactoryShapeVerts[4];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_00BDC_verts", _gMappicS202FactoryShapeVerts);

/// Packed command stream for the Factory shape's single unlit quad.
///
/// Four vertex byte offsets and white colour are followed by two group ends
/// and the stream end. The map reads only the first group.
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS202FactoryShapeStream[] = {
#include "assets/mappic_s2_02_model_00C48_00BDC_stream.inc"
};
#else
static u32 _gMappicS202FactoryShapeStream[9];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_00BDC_stream", _gMappicS202FactoryShapeStream);

TmdSource gMappicS202FactoryShape = {
    .bufferHalfBytes  = sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS202FactoryShapeSkeleton),
    .partVertexCounts = _gMappicS202FactoryShapePartVerts,
    .verts            = _gMappicS202FactoryShapeVerts,
    .normals          = &_gMappicS202FactoryShapeVerts[ARRAY_SIZE(_gMappicS202FactoryShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS202FactoryShapeSkeleton,
    .stream           = _gMappicS202FactoryShapeStream,
};

/// Identity transform and self-parented root for the Garage shape.
#ifdef PE_EMBED_ASSETS
static TmdBone _gMappicS202GarageShapeSkeleton[] = {
#include "assets/mappic_s2_02_model_00C48_00C6C_skeleton.inc"
};
#else
static TmdBone _gMappicS202GarageShapeSkeleton[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_00C6C_skeleton", _gMappicS202GarageShapeSkeleton);

/// Vertex count of the Garage shape's sole part (four vertices).
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS202GarageShapePartVerts[] = {
#include "assets/mappic_s2_02_model_00C48_00C6C_partVerts.inc"
};
#else
static u32 _gMappicS202GarageShapePartVerts[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_00C6C_partVerts", _gMappicS202GarageShapePartVerts);

/// Garage's map footprint in integer model X/Z coordinates, with Y zero.
#ifdef PE_EMBED_ASSETS
static SVECTOR _gMappicS202GarageShapeVerts[] = {
#include "assets/mappic_s2_02_model_00C48_00C6C_verts.inc"
};
#else
static SVECTOR _gMappicS202GarageShapeVerts[4];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_00C6C_verts", _gMappicS202GarageShapeVerts);

/// Packed command stream for the Garage shape's single unlit quad.
///
/// Four vertex byte offsets and white colour are followed by two group ends
/// and the stream end. The map reads only the first group.
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS202GarageShapeStream[] = {
#include "assets/mappic_s2_02_model_00C48_00C6C_stream.inc"
};
#else
static u32 _gMappicS202GarageShapeStream[9];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_00C6C_stream", _gMappicS202GarageShapeStream);

TmdSource gMappicS202GarageShape = {
    .bufferHalfBytes  = sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS202GarageShapeSkeleton),
    .partVertexCounts = _gMappicS202GarageShapePartVerts,
    .verts            = _gMappicS202GarageShapeVerts,
    .normals          = &_gMappicS202GarageShapeVerts[ARRAY_SIZE(_gMappicS202GarageShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS202GarageShapeSkeleton,
    .stream           = _gMappicS202GarageShapeStream,
};

/// Identity transform and self-parented root for the Driveway shape.
#ifdef PE_EMBED_ASSETS
static TmdBone _gMappicS202DrivewayShapeSkeleton[] = {
#include "assets/mappic_s2_02_model_00CF8_skeleton.inc"
};
#else
static TmdBone _gMappicS202DrivewayShapeSkeleton[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00CF8_skeleton", _gMappicS202DrivewayShapeSkeleton);

/// Vertex count of the Driveway shape's sole part (eight vertices).
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS202DrivewayShapePartVerts[] = {
#include "assets/mappic_s2_02_model_00CF8_partVerts.inc"
};
#else
static u32 _gMappicS202DrivewayShapePartVerts[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00CF8_partVerts", _gMappicS202DrivewayShapePartVerts);

/// Driveway's map footprint in integer model X/Z coordinates, with Y zero.
#ifdef PE_EMBED_ASSETS
static SVECTOR _gMappicS202DrivewayShapeVerts[] = {
#include "assets/mappic_s2_02_model_00CF8_verts.inc"
};
#else
static SVECTOR _gMappicS202DrivewayShapeVerts[8];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00CF8_verts", _gMappicS202DrivewayShapeVerts);

/// Packed command stream for the Driveway shape's three unlit quads.
///
/// Each quad has four vertex byte offsets and white colour. Two group ends
/// and the stream end follow; the map reads only the first group.
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS202DrivewayShapeStream[] = {
#include "assets/mappic_s2_02_model_00CF8_stream.inc"
};
#else
static u32 _gMappicS202DrivewayShapeStream[15];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00CF8_stream", _gMappicS202DrivewayShapeStream);

TmdSource gMappicS202DrivewayShape = {
    .bufferHalfBytes  = 3 * sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS202DrivewayShapeSkeleton),
    .partVertexCounts = _gMappicS202DrivewayShapePartVerts,
    .verts            = _gMappicS202DrivewayShapeVerts,
    .normals          = &_gMappicS202DrivewayShapeVerts[ARRAY_SIZE(_gMappicS202DrivewayShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS202DrivewayShapeSkeleton,
    .stream           = _gMappicS202DrivewayShapeStream,
};

/// Identity transform and self-parented root for the Junk yard shape.
#ifdef PE_EMBED_ASSETS
static TmdBone _gMappicS202JunkYardShapeSkeleton[] = {
#include "assets/mappic_s2_02_model_00DD0_skeleton.inc"
};
#else
static TmdBone _gMappicS202JunkYardShapeSkeleton[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00DD0_skeleton", _gMappicS202JunkYardShapeSkeleton);

/// Vertex count of the Junk yard shape's sole part (ten vertices).
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS202JunkYardShapePartVerts[] = {
#include "assets/mappic_s2_02_model_00DD0_partVerts.inc"
};
#else
static u32 _gMappicS202JunkYardShapePartVerts[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00DD0_partVerts", _gMappicS202JunkYardShapePartVerts);

/// Junk yard's map footprint in integer model X/Z coordinates, with Y zero.
#ifdef PE_EMBED_ASSETS
static SVECTOR _gMappicS202JunkYardShapeVerts[] = {
#include "assets/mappic_s2_02_model_00DD0_verts.inc"
};
#else
static SVECTOR _gMappicS202JunkYardShapeVerts[10];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00DD0_verts", _gMappicS202JunkYardShapeVerts);

/// Packed command stream for the Junk yard shape's two unlit triangles and three unlit quads.
///
/// Vertex byte offsets and white colours are followed by two group ends and
/// the stream end. The map reads only the first group and supplies its texture.
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS202JunkYardShapeStream[] = {
#include "assets/mappic_s2_02_model_00DD0_stream.inc"
};
#else
static u32 _gMappicS202JunkYardShapeStream[24];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00DD0_stream", _gMappicS202JunkYardShapeStream);

TmdSource gMappicS202JunkYardShape = {
    .bufferHalfBytes  = 2 * sizeof(POLY_F3) + 3 * sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS202JunkYardShapeSkeleton),
    .partVertexCounts = _gMappicS202JunkYardShapePartVerts,
    .verts            = _gMappicS202JunkYardShapeVerts,
    .normals          = &_gMappicS202JunkYardShapeVerts[ARRAY_SIZE(_gMappicS202JunkYardShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS202JunkYardShapeSkeleton,
    .stream           = _gMappicS202JunkYardShapeStream,
};

/// Identity transform and self-parented root for the Trailer Coach shape.
#ifdef PE_EMBED_ASSETS
static TmdBone _gMappicS202TrailerCoachShapeSkeleton[] = {
#include "assets/mappic_s2_02_model_00C48_00EC0_skeleton.inc"
};
#else
static TmdBone _gMappicS202TrailerCoachShapeSkeleton[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_00EC0_skeleton", _gMappicS202TrailerCoachShapeSkeleton);

/// Vertex count of the Trailer Coach shape's sole part (four vertices).
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS202TrailerCoachShapePartVerts[] = {
#include "assets/mappic_s2_02_model_00C48_00EC0_partVerts.inc"
};
#else
static u32 _gMappicS202TrailerCoachShapePartVerts[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_00EC0_partVerts", _gMappicS202TrailerCoachShapePartVerts);

/// Trailer Coach's map footprint in integer model X/Z coordinates, with Y zero.
#ifdef PE_EMBED_ASSETS
static SVECTOR _gMappicS202TrailerCoachShapeVerts[] = {
#include "assets/mappic_s2_02_model_00C48_00EC0_verts.inc"
};
#else
static SVECTOR _gMappicS202TrailerCoachShapeVerts[4];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_00EC0_verts", _gMappicS202TrailerCoachShapeVerts);

/// Packed command stream for the Trailer Coach shape's single unlit quad.
///
/// Four vertex byte offsets and white colour are followed by two group ends
/// and the stream end. The map reads only the first group and supplies its texture.
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS202TrailerCoachShapeStream[] = {
#include "assets/mappic_s2_02_model_00C48_00EC0_stream.inc"
};
#else
static u32 _gMappicS202TrailerCoachShapeStream[9];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_00EC0_stream", _gMappicS202TrailerCoachShapeStream);

TmdSource gMappicS202TrailerCoachShape = {
    .bufferHalfBytes  = sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS202TrailerCoachShapeSkeleton),
    .partVertexCounts = _gMappicS202TrailerCoachShapePartVerts,
    .verts            = _gMappicS202TrailerCoachShapeVerts,
    .normals          = &_gMappicS202TrailerCoachShapeVerts[ARRAY_SIZE(_gMappicS202TrailerCoachShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS202TrailerCoachShapeSkeleton,
    .stream           = _gMappicS202TrailerCoachShapeStream,
};
