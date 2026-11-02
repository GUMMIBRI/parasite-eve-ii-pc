#include "mappic/mappic.h"
#include "port/asset_bind.h"

#include <libgpu.h>

#include "common.h"

/// Identity transform and self-parented root for the Gas Station shape.
#ifdef PE_EMBED_ASSETS
static TmdBone _gMappicS302GasStationShapeSkeleton[] = {
#include "assets/mappic_s4_00_model_0005C_skeleton.inc"
};
#else
static TmdBone _gMappicS302GasStationShapeSkeleton[1];
#endif
PE_ASSET_BIND("mappic_s4_00_model_0005C_skeleton", _gMappicS302GasStationShapeSkeleton);

/// Vertex count of the Gas Station shape's sole part (six vertices).
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS302GasStationShapePartVerts[] = {
#include "assets/mappic_s4_00_model_0005C_partVerts.inc"
};
#else
static u32 _gMappicS302GasStationShapePartVerts[1];
#endif
PE_ASSET_BIND("mappic_s4_00_model_0005C_partVerts", _gMappicS302GasStationShapePartVerts);

/// Gas Station's map footprint in integer model X/Z coordinates, with Y zero.
#ifdef PE_EMBED_ASSETS
static SVECTOR _gMappicS302GasStationShapeVerts[] = {
#include "assets/mappic_s4_00_model_0005C_verts.inc"
};
#else
static SVECTOR _gMappicS302GasStationShapeVerts[6];
#endif
PE_ASSET_BIND("mappic_s4_00_model_0005C_verts", _gMappicS302GasStationShapeVerts);

/// Two unlit quads' packed vertex byte offsets and white colour, followed by two group ends and the stream end.
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS302GasStationShapeStream[] = {
#include "assets/mappic_s4_00_model_0005C_stream.inc"
};
#else
static u32 _gMappicS302GasStationShapeStream[12];
#endif
PE_ASSET_BIND("mappic_s4_00_model_0005C_stream", _gMappicS302GasStationShapeStream);

TmdSource gMappicS302GasStationShape = {
    .bufferHalfBytes  = 2 * sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS302GasStationShapeSkeleton),
    .partVertexCounts = _gMappicS302GasStationShapePartVerts,
    .verts            = _gMappicS302GasStationShapeVerts,
    .normals          = &_gMappicS302GasStationShapeVerts[ARRAY_SIZE(_gMappicS302GasStationShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS302GasStationShapeSkeleton,
    .stream           = _gMappicS302GasStationShapeStream,
};

/// Identity transform and self-parented root for the Main Street shape.
#ifdef PE_EMBED_ASSETS
static TmdBone _gMappicS302MainStreetShapeSkeleton[] = {
#include "assets/mappic_s2_02_model_00C48_0011C_skeleton.inc"
};
#else
static TmdBone _gMappicS302MainStreetShapeSkeleton[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_0011C_skeleton", _gMappicS302MainStreetShapeSkeleton);

/// Vertex count of the Main Street shape's sole part (four vertices).
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS302MainStreetShapePartVerts[] = {
#include "assets/mappic_s2_02_model_00C48_0011C_partVerts.inc"
};
#else
static u32 _gMappicS302MainStreetShapePartVerts[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_0011C_partVerts", _gMappicS302MainStreetShapePartVerts);

/// Main Street's map footprint in integer model X/Z coordinates, with Y zero.
#ifdef PE_EMBED_ASSETS
static SVECTOR _gMappicS302MainStreetShapeVerts[] = {
#include "assets/mappic_s2_02_model_00C48_0011C_verts.inc"
};
#else
static SVECTOR _gMappicS302MainStreetShapeVerts[4];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_0011C_verts", _gMappicS302MainStreetShapeVerts);

/// One unlit quad's packed vertex byte offsets and white colour, followed by two group ends and the stream end.
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS302MainStreetShapeStream[] = {
#include "assets/mappic_s2_02_model_00C48_0011C_stream.inc"
};
#else
static u32 _gMappicS302MainStreetShapeStream[9];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_0011C_stream", _gMappicS302MainStreetShapeStream);

TmdSource gMappicS302MainStreetShape = {
    .bufferHalfBytes  = sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS302MainStreetShapeSkeleton),
    .partVertexCounts = _gMappicS302MainStreetShapePartVerts,
    .verts            = _gMappicS302MainStreetShapeVerts,
    .normals          = &_gMappicS302MainStreetShapeVerts[ARRAY_SIZE(_gMappicS302MainStreetShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS302MainStreetShapeSkeleton,
    .stream           = _gMappicS302MainStreetShapeStream,
};

/// Identity transform and self-parented root for the General Store shape.
#ifdef PE_EMBED_ASSETS
static TmdBone _gMappicS302GeneralStoreShapeSkeleton[] = {
#include "assets/mappic_s2_02_model_00C48_001AC_skeleton.inc"
};
#else
static TmdBone _gMappicS302GeneralStoreShapeSkeleton[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_001AC_skeleton", _gMappicS302GeneralStoreShapeSkeleton);

/// Vertex count of the General Store shape's sole part (four vertices).
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS302GeneralStoreShapePartVerts[] = {
#include "assets/mappic_s2_02_model_00C48_001AC_partVerts.inc"
};
#else
static u32 _gMappicS302GeneralStoreShapePartVerts[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_001AC_partVerts", _gMappicS302GeneralStoreShapePartVerts);

/// General Store's map footprint in integer model X/Z coordinates, with Y zero.
#ifdef PE_EMBED_ASSETS
static SVECTOR _gMappicS302GeneralStoreShapeVerts[] = {
#include "assets/mappic_s2_02_model_00C48_001AC_verts.inc"
};
#else
static SVECTOR _gMappicS302GeneralStoreShapeVerts[4];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_001AC_verts", _gMappicS302GeneralStoreShapeVerts);

/// Packed command stream for the General Store shape's single unlit quad.
///
/// Four SVECTOR byte offsets and white colour; two group ends precede the
/// stream end. The map reads only the first group.
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS302GeneralStoreShapeStream[] = {
#include "assets/mappic_s2_02_model_00C48_001AC_stream.inc"
};
#else
static u32 _gMappicS302GeneralStoreShapeStream[9];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_001AC_stream", _gMappicS302GeneralStoreShapeStream);

TmdSource gMappicS302GeneralStoreShape = {
    .bufferHalfBytes  = sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS302GeneralStoreShapeSkeleton),
    .partVertexCounts = _gMappicS302GeneralStoreShapePartVerts,
    .verts            = _gMappicS302GeneralStoreShapeVerts,
    .normals          = &_gMappicS302GeneralStoreShapeVerts[ARRAY_SIZE(_gMappicS302GeneralStoreShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS302GeneralStoreShapeSkeleton,
    .stream           = _gMappicS302GeneralStoreShapeStream,
};

/// Identity transform and self-parented root for the Back Street shape.
#ifdef PE_EMBED_ASSETS
static TmdBone _gMappicS302BackStreetShapeSkeleton[] = {
#include "assets/mappic_s4_00_model_0005C_00258_skeleton.inc"
};
#else
static TmdBone _gMappicS302BackStreetShapeSkeleton[1];
#endif
PE_ASSET_BIND("mappic_s4_00_model_0005C_00258_skeleton", _gMappicS302BackStreetShapeSkeleton);

/// Vertex count of the Back Street shape's sole part (six vertices).
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS302BackStreetShapePartVerts[] = {
#include "assets/mappic_s4_00_model_0005C_00258_partVerts.inc"
};
#else
static u32 _gMappicS302BackStreetShapePartVerts[1];
#endif
PE_ASSET_BIND("mappic_s4_00_model_0005C_00258_partVerts", _gMappicS302BackStreetShapePartVerts);

/// Back Street's map footprint in integer model X/Z coordinates, with Y zero.
#ifdef PE_EMBED_ASSETS
static SVECTOR _gMappicS302BackStreetShapeVerts[] = {
#include "assets/mappic_s4_00_model_0005C_00258_verts.inc"
};
#else
static SVECTOR _gMappicS302BackStreetShapeVerts[6];
#endif
PE_ASSET_BIND("mappic_s4_00_model_0005C_00258_verts", _gMappicS302BackStreetShapeVerts);

/// Packed command stream for the Back Street shape's two unlit quads.
///
/// Four SVECTOR byte offsets and white colour per quad; two group ends precede
/// the stream end. The map reads only the first group.
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS302BackStreetShapeStream[] = {
#include "assets/mappic_s4_00_model_0005C_00258_stream.inc"
};
#else
static u32 _gMappicS302BackStreetShapeStream[12];
#endif
PE_ASSET_BIND("mappic_s4_00_model_0005C_00258_stream", _gMappicS302BackStreetShapeStream);

TmdSource gMappicS302BackStreetShape = {
    .bufferHalfBytes  = 2 * sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS302BackStreetShapeSkeleton),
    .partVertexCounts = _gMappicS302BackStreetShapePartVerts,
    .verts            = _gMappicS302BackStreetShapeVerts,
    .normals          = &_gMappicS302BackStreetShapeVerts[ARRAY_SIZE(_gMappicS302BackStreetShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS302BackStreetShapeSkeleton,
    .stream           = _gMappicS302BackStreetShapeStream,
};

/// Identity transform and self-parented root for the Souvenir Shop shape.
#ifdef PE_EMBED_ASSETS
static TmdBone _gMappicS302SouvenirShopShapeSkeleton[] = {
#include "assets/mappic_s2_02_model_00C48_002E8_skeleton.inc"
};
#else
static TmdBone _gMappicS302SouvenirShopShapeSkeleton[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_002E8_skeleton", _gMappicS302SouvenirShopShapeSkeleton);

/// Vertex count of the Souvenir Shop shape's sole part (four vertices).
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS302SouvenirShopShapePartVerts[] = {
#include "assets/mappic_s2_02_model_00C48_002E8_partVerts.inc"
};
#else
static u32 _gMappicS302SouvenirShopShapePartVerts[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_002E8_partVerts", _gMappicS302SouvenirShopShapePartVerts);

/// Souvenir Shop's map footprint in integer model X/Z coordinates, with Y zero.
#ifdef PE_EMBED_ASSETS
static SVECTOR _gMappicS302SouvenirShopShapeVerts[] = {
#include "assets/mappic_s2_02_model_00C48_002E8_verts.inc"
};
#else
static SVECTOR _gMappicS302SouvenirShopShapeVerts[4];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_002E8_verts", _gMappicS302SouvenirShopShapeVerts);

/// Packed command stream for the Souvenir Shop shape's single unlit quad.
///
/// Four SVECTOR byte offsets and white colour; two group ends precede the
/// stream end. The map reads only the first group.
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS302SouvenirShopShapeStream[] = {
#include "assets/mappic_s2_02_model_00C48_002E8_stream.inc"
};
#else
static u32 _gMappicS302SouvenirShopShapeStream[9];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_002E8_stream", _gMappicS302SouvenirShopShapeStream);

TmdSource gMappicS302SouvenirShopShape = {
    .bufferHalfBytes  = sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS302SouvenirShopShapeSkeleton),
    .partVertexCounts = _gMappicS302SouvenirShopShapePartVerts,
    .verts            = _gMappicS302SouvenirShopShapeVerts,
    .normals          = &_gMappicS302SouvenirShopShapeVerts[ARRAY_SIZE(_gMappicS302SouvenirShopShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS302SouvenirShopShapeSkeleton,
    .stream           = _gMappicS302SouvenirShopShapeStream,
};

/// Identity transform and self-parented root for the Warehouse shape.
#ifdef PE_EMBED_ASSETS
static TmdBone _gMappicS302WarehouseShapeSkeleton[] = {
#include "assets/mappic_s2_02_model_00C48_00378_skeleton.inc"
};
#else
static TmdBone _gMappicS302WarehouseShapeSkeleton[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_00378_skeleton", _gMappicS302WarehouseShapeSkeleton);

/// Vertex count of the Warehouse shape's sole part (four vertices).
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS302WarehouseShapePartVerts[] = {
#include "assets/mappic_s2_02_model_00C48_00378_partVerts.inc"
};
#else
static u32 _gMappicS302WarehouseShapePartVerts[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_00378_partVerts", _gMappicS302WarehouseShapePartVerts);

/// Warehouse's map footprint in integer model X/Z coordinates, with Y zero.
#ifdef PE_EMBED_ASSETS
static SVECTOR _gMappicS302WarehouseShapeVerts[] = {
#include "assets/mappic_s2_02_model_00C48_00378_verts.inc"
};
#else
static SVECTOR _gMappicS302WarehouseShapeVerts[4];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_00378_verts", _gMappicS302WarehouseShapeVerts);

/// Packed command stream for the Warehouse shape's single unlit quad.
///
/// Four SVECTOR byte offsets and white colour; two group ends precede the
/// stream end. The map reads only the first group.
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS302WarehouseShapeStream[] = {
#include "assets/mappic_s2_02_model_00C48_00378_stream.inc"
};
#else
static u32 _gMappicS302WarehouseShapeStream[9];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_00378_stream", _gMappicS302WarehouseShapeStream);

TmdSource gMappicS302WarehouseShape = {
    .bufferHalfBytes  = sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS302WarehouseShapeSkeleton),
    .partVertexCounts = _gMappicS302WarehouseShapePartVerts,
    .verts            = _gMappicS302WarehouseShapeVerts,
    .normals          = &_gMappicS302WarehouseShapeVerts[ARRAY_SIZE(_gMappicS302WarehouseShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS302WarehouseShapeSkeleton,
    .stream           = _gMappicS302WarehouseShapeStream,
};

/// Identity transform and self-parented root for the Dilapidated House shape.
#ifdef PE_EMBED_ASSETS
static TmdBone _gMappicS302DilapidatedHouseShapeSkeleton[] = {
#include "assets/mappic_s3_02_model_003F4_skeleton.inc"
};
#else
static TmdBone _gMappicS302DilapidatedHouseShapeSkeleton[1];
#endif
PE_ASSET_BIND("mappic_s3_02_model_003F4_skeleton", _gMappicS302DilapidatedHouseShapeSkeleton);

/// Six vertices in the Dilapidated House shape's sole part.
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS302DilapidatedHouseShapePartVerts[] = {
#include "assets/mappic_s3_02_model_003F4_partVerts.inc"
};
#else
static u32 _gMappicS302DilapidatedHouseShapePartVerts[1];
#endif
PE_ASSET_BIND("mappic_s3_02_model_003F4_partVerts", _gMappicS302DilapidatedHouseShapePartVerts);

/// Dilapidated House's map footprint in integer model X/Z coordinates, with Y zero.
#ifdef PE_EMBED_ASSETS
static SVECTOR _gMappicS302DilapidatedHouseShapeVerts[] = {
#include "assets/mappic_s3_02_model_003F4_verts.inc"
};
#else
static SVECTOR _gMappicS302DilapidatedHouseShapeVerts[6];
#endif
PE_ASSET_BIND("mappic_s3_02_model_003F4_verts", _gMappicS302DilapidatedHouseShapeVerts);

/// Packed command stream for the Dilapidated House shape's four unlit triangles.
///
/// Elements contain three SVECTOR byte offsets and white colour; two group
/// ends precede the stream end. The map reads only the first group.
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS302DilapidatedHouseShapeStream[] = {
#include "assets/mappic_s3_02_model_003F4_stream.inc"
};
#else
static u32 _gMappicS302DilapidatedHouseShapeStream[18];
#endif
PE_ASSET_BIND("mappic_s3_02_model_003F4_stream", _gMappicS302DilapidatedHouseShapeStream);

TmdSource gMappicS302DilapidatedHouseShape = {
    .bufferHalfBytes  = 4 * sizeof(POLY_F3),
    .partCount        = ARRAY_SIZE(_gMappicS302DilapidatedHouseShapeSkeleton),
    .partVertexCounts = _gMappicS302DilapidatedHouseShapePartVerts,
    .verts            = _gMappicS302DilapidatedHouseShapeVerts,
    .normals          = &_gMappicS302DilapidatedHouseShapeVerts[ARRAY_SIZE(_gMappicS302DilapidatedHouseShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS302DilapidatedHouseShapeSkeleton,
    .stream           = _gMappicS302DilapidatedHouseShapeStream,
};

/// Identity transform and self-parented root for the Motel room 1 shape.
#ifdef PE_EMBED_ASSETS
static TmdBone _gMappicS302MotelRoom1ShapeSkeleton[] = {
#include "assets/mappic_s2_02_model_00C48_004B4_skeleton.inc"
};
#else
static TmdBone _gMappicS302MotelRoom1ShapeSkeleton[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_004B4_skeleton", _gMappicS302MotelRoom1ShapeSkeleton);

/// Vertex count of the Motel room 1 shape's sole part (four vertices).
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS302MotelRoom1ShapePartVerts[] = {
#include "assets/mappic_s2_02_model_00C48_004B4_partVerts.inc"
};
#else
static u32 _gMappicS302MotelRoom1ShapePartVerts[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_004B4_partVerts", _gMappicS302MotelRoom1ShapePartVerts);

/// Motel room 1's map footprint in integer model X/Z coordinates, with Y zero.
#ifdef PE_EMBED_ASSETS
static SVECTOR _gMappicS302MotelRoom1ShapeVerts[] = {
#include "assets/mappic_s2_02_model_00C48_004B4_verts.inc"
};
#else
static SVECTOR _gMappicS302MotelRoom1ShapeVerts[4];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_004B4_verts", _gMappicS302MotelRoom1ShapeVerts);

/// Packed command stream for the Motel room 1 shape's single unlit quad.
///
/// Four SVECTOR byte offsets and white colour; two group ends precede the
/// stream end. The map reads only the first group.
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS302MotelRoom1ShapeStream[] = {
#include "assets/mappic_s2_02_model_00C48_004B4_stream.inc"
};
#else
static u32 _gMappicS302MotelRoom1ShapeStream[9];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_004B4_stream", _gMappicS302MotelRoom1ShapeStream);

TmdSource gMappicS302MotelRoom1Shape = {
    .bufferHalfBytes  = sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS302MotelRoom1ShapeSkeleton),
    .partVertexCounts = _gMappicS302MotelRoom1ShapePartVerts,
    .verts            = _gMappicS302MotelRoom1ShapeVerts,
    .normals          = &_gMappicS302MotelRoom1ShapeVerts[ARRAY_SIZE(_gMappicS302MotelRoom1ShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS302MotelRoom1ShapeSkeleton,
    .stream           = _gMappicS302MotelRoom1ShapeStream,
};

/// Identity transform and self-parented root for the Motel room 2 shape.
#ifdef PE_EMBED_ASSETS
static TmdBone _gMappicS302MotelRoom2ShapeSkeleton[] = {
#include "assets/mappic_s2_02_model_00C48_00544_skeleton.inc"
};
#else
static TmdBone _gMappicS302MotelRoom2ShapeSkeleton[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_00544_skeleton", _gMappicS302MotelRoom2ShapeSkeleton);

/// Vertex count of the Motel room 2 shape's sole part (four vertices).
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS302MotelRoom2ShapePartVerts[] = {
#include "assets/mappic_s2_02_model_00C48_00544_partVerts.inc"
};
#else
static u32 _gMappicS302MotelRoom2ShapePartVerts[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_00544_partVerts", _gMappicS302MotelRoom2ShapePartVerts);

/// Motel room 2's map footprint in integer model X/Z coordinates, with Y zero.
#ifdef PE_EMBED_ASSETS
static SVECTOR _gMappicS302MotelRoom2ShapeVerts[] = {
#include "assets/mappic_s2_02_model_00C48_00544_verts.inc"
};
#else
static SVECTOR _gMappicS302MotelRoom2ShapeVerts[4];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_00544_verts", _gMappicS302MotelRoom2ShapeVerts);

/// Packed command stream for the Motel room 2 shape's single unlit quad.
///
/// Four SVECTOR byte offsets and white colour; two group ends precede the
/// stream end. The map reads only the first group.
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS302MotelRoom2ShapeStream[] = {
#include "assets/mappic_s2_02_model_00C48_00544_stream.inc"
};
#else
static u32 _gMappicS302MotelRoom2ShapeStream[9];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_00544_stream", _gMappicS302MotelRoom2ShapeStream);

TmdSource gMappicS302MotelRoom2Shape = {
    .bufferHalfBytes  = sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS302MotelRoom2ShapeSkeleton),
    .partVertexCounts = _gMappicS302MotelRoom2ShapePartVerts,
    .verts            = _gMappicS302MotelRoom2ShapeVerts,
    .normals          = &_gMappicS302MotelRoom2ShapeVerts[ARRAY_SIZE(_gMappicS302MotelRoom2ShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS302MotelRoom2ShapeSkeleton,
    .stream           = _gMappicS302MotelRoom2ShapeStream,
};

/// Identity transform and self-parented root for the Motel room 3 shape.
#ifdef PE_EMBED_ASSETS
static TmdBone _gMappicS302MotelRoom3ShapeSkeleton[] = {
#include "assets/mappic_s2_02_model_00C48_005D4_skeleton.inc"
};
#else
static TmdBone _gMappicS302MotelRoom3ShapeSkeleton[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_005D4_skeleton", _gMappicS302MotelRoom3ShapeSkeleton);

/// Vertex count of the Motel room 3 shape's sole part (four vertices).
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS302MotelRoom3ShapePartVerts[] = {
#include "assets/mappic_s2_02_model_00C48_005D4_partVerts.inc"
};
#else
static u32 _gMappicS302MotelRoom3ShapePartVerts[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_005D4_partVerts", _gMappicS302MotelRoom3ShapePartVerts);

/// Motel room 3's map footprint in integer model X/Z coordinates, with Y zero.
#ifdef PE_EMBED_ASSETS
static SVECTOR _gMappicS302MotelRoom3ShapeVerts[] = {
#include "assets/mappic_s2_02_model_00C48_005D4_verts.inc"
};
#else
static SVECTOR _gMappicS302MotelRoom3ShapeVerts[4];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_005D4_verts", _gMappicS302MotelRoom3ShapeVerts);

/// Packed command stream for the Motel room 3 shape's single unlit quad.
///
/// Four SVECTOR byte offsets and white colour; two group ends precede the
/// stream end. The map reads only the first group.
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS302MotelRoom3ShapeStream[] = {
#include "assets/mappic_s2_02_model_00C48_005D4_stream.inc"
};
#else
static u32 _gMappicS302MotelRoom3ShapeStream[9];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_005D4_stream", _gMappicS302MotelRoom3ShapeStream);

TmdSource gMappicS302MotelRoom3Shape = {
    .bufferHalfBytes  = sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS302MotelRoom3ShapeSkeleton),
    .partVertexCounts = _gMappicS302MotelRoom3ShapePartVerts,
    .verts            = _gMappicS302MotelRoom3ShapeVerts,
    .normals          = &_gMappicS302MotelRoom3ShapeVerts[ARRAY_SIZE(_gMappicS302MotelRoom3ShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS302MotelRoom3ShapeSkeleton,
    .stream           = _gMappicS302MotelRoom3ShapeStream,
};

/// Identity transform and self-parented root for the Motel room 4 shape.
#ifdef PE_EMBED_ASSETS
static TmdBone _gMappicS302MotelRoom4ShapeSkeleton[] = {
#include "assets/mappic_s2_02_model_00C48_00664_skeleton.inc"
};
#else
static TmdBone _gMappicS302MotelRoom4ShapeSkeleton[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_00664_skeleton", _gMappicS302MotelRoom4ShapeSkeleton);

/// Vertex count of the Motel room 4 shape's sole part (four vertices).
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS302MotelRoom4ShapePartVerts[] = {
#include "assets/mappic_s2_02_model_00C48_00664_partVerts.inc"
};
#else
static u32 _gMappicS302MotelRoom4ShapePartVerts[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_00664_partVerts", _gMappicS302MotelRoom4ShapePartVerts);

/// Motel room 4's map footprint in integer model X/Z coordinates, with Y zero.
#ifdef PE_EMBED_ASSETS
static SVECTOR _gMappicS302MotelRoom4ShapeVerts[] = {
#include "assets/mappic_s2_02_model_00C48_00664_verts.inc"
};
#else
static SVECTOR _gMappicS302MotelRoom4ShapeVerts[4];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_00664_verts", _gMappicS302MotelRoom4ShapeVerts);

/// Packed command stream for the Motel room 4 shape's single unlit quad.
///
/// Four SVECTOR byte offsets and white colour; two group ends precede the
/// stream end. The map reads only the first group.
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS302MotelRoom4ShapeStream[] = {
#include "assets/mappic_s2_02_model_00C48_00664_stream.inc"
};
#else
static u32 _gMappicS302MotelRoom4ShapeStream[9];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_00664_stream", _gMappicS302MotelRoom4ShapeStream);

TmdSource gMappicS302MotelRoom4Shape = {
    .bufferHalfBytes  = sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS302MotelRoom4ShapeSkeleton),
    .partVertexCounts = _gMappicS302MotelRoom4ShapePartVerts,
    .verts            = _gMappicS302MotelRoom4ShapeVerts,
    .normals          = &_gMappicS302MotelRoom4ShapeVerts[ARRAY_SIZE(_gMappicS302MotelRoom4ShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS302MotelRoom4ShapeSkeleton,
    .stream           = _gMappicS302MotelRoom4ShapeStream,
};

/// Identity transform and self-parented root for the Parking lot shape.
#ifdef PE_EMBED_ASSETS
static TmdBone _gMappicS302ParkingLotShapeSkeleton[] = {
#include "assets/mappic_s2_02_model_00710_skeleton.inc"
};
#else
static TmdBone _gMappicS302ParkingLotShapeSkeleton[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00710_skeleton", _gMappicS302ParkingLotShapeSkeleton);

/// Vertex count of the Parking lot shape's sole part (twelve vertices).
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS302ParkingLotShapePartVerts[] = {
#include "assets/mappic_s2_02_model_00710_partVerts.inc"
};
#else
static u32 _gMappicS302ParkingLotShapePartVerts[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00710_partVerts", _gMappicS302ParkingLotShapePartVerts);

/// Parking lot's map footprint in integer model X/Z coordinates, with Y zero.
#ifdef PE_EMBED_ASSETS
static SVECTOR _gMappicS302ParkingLotShapeVerts[] = {
#include "assets/mappic_s2_02_model_00710_verts.inc"
};
#else
static SVECTOR _gMappicS302ParkingLotShapeVerts[12];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00710_verts", _gMappicS302ParkingLotShapeVerts);

/// Packed command stream for the Parking lot shape's five unlit quads.
///
/// Each quad has four SVECTOR byte offsets and white colour; two group ends
/// precede the stream end. The map reads only the first group.
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS302ParkingLotShapeStream[] = {
#include "assets/mappic_s2_02_model_00710_stream.inc"
};
#else
static u32 _gMappicS302ParkingLotShapeStream[21];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00710_stream", _gMappicS302ParkingLotShapeStream);

TmdSource gMappicS302ParkingLotShape = {
    .bufferHalfBytes  = 5 * sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS302ParkingLotShapeSkeleton),
    .partVertexCounts = _gMappicS302ParkingLotShapePartVerts,
    .verts            = _gMappicS302ParkingLotShapeVerts,
    .normals          = &_gMappicS302ParkingLotShapeVerts[ARRAY_SIZE(_gMappicS302ParkingLotShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS302ParkingLotShapeSkeleton,
    .stream           = _gMappicS302ParkingLotShapeStream,
};

/// Identity transform and self-parented root for the Toilet shape.
#ifdef PE_EMBED_ASSETS
static TmdBone _gMappicS302ToiletShapeSkeleton[] = {
#include "assets/mappic_s2_02_model_00C48_007F4_skeleton.inc"
};
#else
static TmdBone _gMappicS302ToiletShapeSkeleton[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_007F4_skeleton", _gMappicS302ToiletShapeSkeleton);

/// Vertex count of the Toilet shape's sole part (four vertices).
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS302ToiletShapePartVerts[] = {
#include "assets/mappic_s2_02_model_00C48_007F4_partVerts.inc"
};
#else
static u32 _gMappicS302ToiletShapePartVerts[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_007F4_partVerts", _gMappicS302ToiletShapePartVerts);

/// Toilet's map footprint in integer model X/Z coordinates, with Y zero.
#ifdef PE_EMBED_ASSETS
static SVECTOR _gMappicS302ToiletShapeVerts[] = {
#include "assets/mappic_s2_02_model_00C48_007F4_verts.inc"
};
#else
static SVECTOR _gMappicS302ToiletShapeVerts[4];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_007F4_verts", _gMappicS302ToiletShapeVerts);

/// Packed command stream for the Toilet shape's unlit quad.
///
/// Four SVECTOR byte offsets and white colour precede two group ends and
/// the stream end. The map reads only the first group.
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS302ToiletShapeStream[] = {
#include "assets/mappic_s2_02_model_00C48_007F4_stream.inc"
};
#else
static u32 _gMappicS302ToiletShapeStream[9];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_007F4_stream", _gMappicS302ToiletShapeStream);

TmdSource gMappicS302ToiletShape = {
    .bufferHalfBytes  = sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS302ToiletShapeSkeleton),
    .partVertexCounts = _gMappicS302ToiletShapePartVerts,
    .verts            = _gMappicS302ToiletShapeVerts,
    .normals          = &_gMappicS302ToiletShapeVerts[ARRAY_SIZE(_gMappicS302ToiletShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS302ToiletShapeSkeleton,
    .stream           = _gMappicS302ToiletShapeStream,
};

/// Identity transform and self-parented root for the Motel lobby shape.
#ifdef PE_EMBED_ASSETS
static TmdBone _gMappicS302MotelLobbyShapeSkeleton[] = {
#include "assets/mappic_s2_02_model_00C48_00884_skeleton.inc"
};
#else
static TmdBone _gMappicS302MotelLobbyShapeSkeleton[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_00884_skeleton", _gMappicS302MotelLobbyShapeSkeleton);

/// Vertex count of the Motel lobby shape's sole part (four vertices).
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS302MotelLobbyShapePartVerts[] = {
#include "assets/mappic_s2_02_model_00C48_00884_partVerts.inc"
};
#else
static u32 _gMappicS302MotelLobbyShapePartVerts[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_00884_partVerts", _gMappicS302MotelLobbyShapePartVerts);

/// Motel lobby's map footprint in integer model X/Z coordinates, with Y zero.
#ifdef PE_EMBED_ASSETS
static SVECTOR _gMappicS302MotelLobbyShapeVerts[] = {
#include "assets/mappic_s2_02_model_00C48_00884_verts.inc"
};
#else
static SVECTOR _gMappicS302MotelLobbyShapeVerts[4];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_00884_verts", _gMappicS302MotelLobbyShapeVerts);

/// Packed command stream for the Motel lobby shape's single unlit quad.
///
/// Four SVECTOR byte offsets and white colour; two group ends precede the
/// stream end. The map reads only the first group.
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS302MotelLobbyShapeStream[] = {
#include "assets/mappic_s2_02_model_00C48_00884_stream.inc"
};
#else
static u32 _gMappicS302MotelLobbyShapeStream[9];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_00884_stream", _gMappicS302MotelLobbyShapeStream);

TmdSource gMappicS302MotelLobbyShape = {
    .bufferHalfBytes  = sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS302MotelLobbyShapeSkeleton),
    .partVertexCounts = _gMappicS302MotelLobbyShapePartVerts,
    .verts            = _gMappicS302MotelLobbyShapeVerts,
    .normals          = &_gMappicS302MotelLobbyShapeVerts[ARRAY_SIZE(_gMappicS302MotelLobbyShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS302MotelLobbyShapeSkeleton,
    .stream           = _gMappicS302MotelLobbyShapeStream,
};

/// Identity transform and self-parented root for the Saloon G & R shape.
#ifdef PE_EMBED_ASSETS
static TmdBone _gMappicS302SaloonGRShapeSkeleton[] = {
#include "assets/mappic_s2_02_model_00910_skeleton.inc"
};
#else
static TmdBone _gMappicS302SaloonGRShapeSkeleton[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00910_skeleton", _gMappicS302SaloonGRShapeSkeleton);

/// Vertex count of the Saloon G & R shape's sole part (eight vertices).
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS302SaloonGRShapePartVerts[] = {
#include "assets/mappic_s2_02_model_00910_partVerts.inc"
};
#else
static u32 _gMappicS302SaloonGRShapePartVerts[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00910_partVerts", _gMappicS302SaloonGRShapePartVerts);

/// Saloon G & R's map footprint in integer model X/Z coordinates, with Y zero.
#ifdef PE_EMBED_ASSETS
static SVECTOR _gMappicS302SaloonGRShapeVerts[] = {
#include "assets/mappic_s2_02_model_00910_verts.inc"
};
#else
static SVECTOR _gMappicS302SaloonGRShapeVerts[8];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00910_verts", _gMappicS302SaloonGRShapeVerts);

/// Packed command stream for the Saloon G & R shape's two unlit triangles and two unlit quads.
///
/// Elements contain SVECTOR byte offsets and white colour; two group ends
/// precede the stream end. The map reads only the first group.
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS302SaloonGRShapeStream[] = {
#include "assets/mappic_s2_02_model_00910_stream.inc"
};
#else
static u32 _gMappicS302SaloonGRShapeStream[21];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00910_stream", _gMappicS302SaloonGRShapeStream);

TmdSource gMappicS302SaloonGRShape = {
    .bufferHalfBytes  = 2 * sizeof(POLY_F3) + 2 * sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS302SaloonGRShapeSkeleton),
    .partVertexCounts = _gMappicS302SaloonGRShapePartVerts,
    .verts            = _gMappicS302SaloonGRShapeVerts,
    .normals          = &_gMappicS302SaloonGRShapeVerts[ARRAY_SIZE(_gMappicS302SaloonGRShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS302SaloonGRShapeSkeleton,
    .stream           = _gMappicS302SaloonGRShapeStream,
};

/// Identity transform and self-parented root for the G & R Kitchen shape.
#ifdef PE_EMBED_ASSETS
static TmdBone _gMappicS302GRKitchenShapeSkeleton[] = {
#include "assets/mappic_s2_02_model_00C48_009F4_skeleton.inc"
};
#else
static TmdBone _gMappicS302GRKitchenShapeSkeleton[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_009F4_skeleton", _gMappicS302GRKitchenShapeSkeleton);

/// Vertex count of the G & R Kitchen shape's sole part (four vertices).
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS302GRKitchenShapePartVerts[] = {
#include "assets/mappic_s2_02_model_00C48_009F4_partVerts.inc"
};
#else
static u32 _gMappicS302GRKitchenShapePartVerts[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_009F4_partVerts", _gMappicS302GRKitchenShapePartVerts);

/// G & R Kitchen's map footprint in integer model X/Z coordinates, with Y zero.
#ifdef PE_EMBED_ASSETS
static SVECTOR _gMappicS302GRKitchenShapeVerts[] = {
#include "assets/mappic_s2_02_model_00C48_009F4_verts.inc"
};
#else
static SVECTOR _gMappicS302GRKitchenShapeVerts[4];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_009F4_verts", _gMappicS302GRKitchenShapeVerts);

/// Packed command stream for the G & R Kitchen shape's single unlit quad.
///
/// Four SVECTOR byte offsets and white colour; two group ends precede the
/// stream end. The map reads only the first group.
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS302GRKitchenShapeStream[] = {
#include "assets/mappic_s2_02_model_00C48_009F4_stream.inc"
};
#else
static u32 _gMappicS302GRKitchenShapeStream[9];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_009F4_stream", _gMappicS302GRKitchenShapeStream);

TmdSource gMappicS302GRKitchenShape = {
    .bufferHalfBytes  = sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS302GRKitchenShapeSkeleton),
    .partVertexCounts = _gMappicS302GRKitchenShapePartVerts,
    .verts            = _gMappicS302GRKitchenShapeVerts,
    .normals          = &_gMappicS302GRKitchenShapeVerts[ARRAY_SIZE(_gMappicS302GRKitchenShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS302GRKitchenShapeSkeleton,
    .stream           = _gMappicS302GRKitchenShapeStream,
};

/// Identity transform and self-parented root for the Water Tower shape.
#ifdef PE_EMBED_ASSETS
static TmdBone _gMappicS302WaterTowerShapeSkeleton[] = {
#include "assets/mappic_s4_00_model_0005C_00AA0_skeleton.inc"
};
#else
static TmdBone _gMappicS302WaterTowerShapeSkeleton[1];
#endif
PE_ASSET_BIND("mappic_s4_00_model_0005C_00AA0_skeleton", _gMappicS302WaterTowerShapeSkeleton);

/// Vertex count of the Water Tower shape's sole part (six vertices).
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS302WaterTowerShapePartVerts[] = {
#include "assets/mappic_s4_00_model_0005C_00AA0_partVerts.inc"
};
#else
static u32 _gMappicS302WaterTowerShapePartVerts[1];
#endif
PE_ASSET_BIND("mappic_s4_00_model_0005C_00AA0_partVerts", _gMappicS302WaterTowerShapePartVerts);

/// Water Tower's map footprint in integer model X/Z coordinates, with Y zero.
#ifdef PE_EMBED_ASSETS
static SVECTOR _gMappicS302WaterTowerShapeVerts[] = {
#include "assets/mappic_s4_00_model_0005C_00AA0_verts.inc"
};
#else
static SVECTOR _gMappicS302WaterTowerShapeVerts[6];
#endif
PE_ASSET_BIND("mappic_s4_00_model_0005C_00AA0_verts", _gMappicS302WaterTowerShapeVerts);

/// Packed command stream for the Water Tower shape's two unlit quads.
///
/// Each quad has four packed SVECTOR byte offsets and white colour; two group
/// ends precede the stream end. The map reads only the first group.
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS302WaterTowerShapeStream[] = {
#include "assets/mappic_s4_00_model_0005C_00AA0_stream.inc"
};
#else
static u32 _gMappicS302WaterTowerShapeStream[12];
#endif
PE_ASSET_BIND("mappic_s4_00_model_0005C_00AA0_stream", _gMappicS302WaterTowerShapeStream);

TmdSource gMappicS302WaterTowerShape = {
    .bufferHalfBytes  = 2 * sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS302WaterTowerShapeSkeleton),
    .partVertexCounts = _gMappicS302WaterTowerShapePartVerts,
    .verts            = _gMappicS302WaterTowerShapeVerts,
    .normals          = &_gMappicS302WaterTowerShapeVerts[ARRAY_SIZE(_gMappicS302WaterTowerShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS302WaterTowerShapeSkeleton,
    .stream           = _gMappicS302WaterTowerShapeStream,
};

/// Identity transform and self-parented root for the Breezeway shape.
#ifdef PE_EMBED_ASSETS
static TmdBone _gMappicS302BreezewayShapeSkeleton[] = {
#include "assets/mappic_s4_00_model_0005C_00B4C_skeleton.inc"
};
#else
static TmdBone _gMappicS302BreezewayShapeSkeleton[1];
#endif
PE_ASSET_BIND("mappic_s4_00_model_0005C_00B4C_skeleton", _gMappicS302BreezewayShapeSkeleton);

/// Vertex count of the Breezeway shape's sole part (six vertices).
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS302BreezewayShapePartVerts[] = {
#include "assets/mappic_s4_00_model_0005C_00B4C_partVerts.inc"
};
#else
static u32 _gMappicS302BreezewayShapePartVerts[1];
#endif
PE_ASSET_BIND("mappic_s4_00_model_0005C_00B4C_partVerts", _gMappicS302BreezewayShapePartVerts);

/// Breezeway's map footprint in integer model X/Z coordinates, with Y zero.
#ifdef PE_EMBED_ASSETS
static SVECTOR _gMappicS302BreezewayShapeVerts[] = {
#include "assets/mappic_s4_00_model_0005C_00B4C_verts.inc"
};
#else
static SVECTOR _gMappicS302BreezewayShapeVerts[6];
#endif
PE_ASSET_BIND("mappic_s4_00_model_0005C_00B4C_verts", _gMappicS302BreezewayShapeVerts);

/// Packed command stream for the Breezeway shape's two unlit quads.
///
/// Each quad has four packed SVECTOR byte offsets and white colour; two group
/// ends precede the stream end. The map reads only the first group.
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS302BreezewayShapeStream[] = {
#include "assets/mappic_s4_00_model_0005C_00B4C_stream.inc"
};
#else
static u32 _gMappicS302BreezewayShapeStream[12];
#endif
PE_ASSET_BIND("mappic_s4_00_model_0005C_00B4C_stream", _gMappicS302BreezewayShapeStream);

TmdSource gMappicS302BreezewayShape = {
    .bufferHalfBytes  = 2 * sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS302BreezewayShapeSkeleton),
    .partVertexCounts = _gMappicS302BreezewayShapePartVerts,
    .verts            = _gMappicS302BreezewayShapeVerts,
    .normals          = &_gMappicS302BreezewayShapeVerts[ARRAY_SIZE(_gMappicS302BreezewayShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS302BreezewayShapeSkeleton,
    .stream           = _gMappicS302BreezewayShapeStream,
};

/// Identity transform and self-parented root for the Factory shape.
#ifdef PE_EMBED_ASSETS
static TmdBone _gMappicS302FactoryShapeSkeleton[] = {
#include "assets/mappic_s2_02_model_00C48_00BDC_skeleton.inc"
};
#else
static TmdBone _gMappicS302FactoryShapeSkeleton[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_00BDC_skeleton", _gMappicS302FactoryShapeSkeleton);

/// Vertex count of the Factory shape's sole part (four vertices).
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS302FactoryShapePartVerts[] = {
#include "assets/mappic_s2_02_model_00C48_00BDC_partVerts.inc"
};
#else
static u32 _gMappicS302FactoryShapePartVerts[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_00BDC_partVerts", _gMappicS302FactoryShapePartVerts);

/// Factory's map footprint in integer model X/Z coordinates, with Y zero.
#ifdef PE_EMBED_ASSETS
static SVECTOR _gMappicS302FactoryShapeVerts[] = {
#include "assets/mappic_s2_02_model_00C48_00BDC_verts.inc"
};
#else
static SVECTOR _gMappicS302FactoryShapeVerts[4];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_00BDC_verts", _gMappicS302FactoryShapeVerts);

/// Packed command stream for the Factory shape's single unlit quad.
///
/// Four vertex byte offsets and white colour are followed by two group ends
/// and the stream end. The map reads only the first group.
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS302FactoryShapeStream[] = {
#include "assets/mappic_s2_02_model_00C48_00BDC_stream.inc"
};
#else
static u32 _gMappicS302FactoryShapeStream[9];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_00BDC_stream", _gMappicS302FactoryShapeStream);

TmdSource gMappicS302FactoryShape = {
    .bufferHalfBytes  = sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS302FactoryShapeSkeleton),
    .partVertexCounts = _gMappicS302FactoryShapePartVerts,
    .verts            = _gMappicS302FactoryShapeVerts,
    .normals          = &_gMappicS302FactoryShapeVerts[ARRAY_SIZE(_gMappicS302FactoryShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS302FactoryShapeSkeleton,
    .stream           = _gMappicS302FactoryShapeStream,
};

/// Identity transform and self-parented root for the Garage shape.
#ifdef PE_EMBED_ASSETS
static TmdBone _gMappicS302GarageShapeSkeleton[] = {
#include "assets/mappic_s2_02_model_00C48_00C6C_skeleton.inc"
};
#else
static TmdBone _gMappicS302GarageShapeSkeleton[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_00C6C_skeleton", _gMappicS302GarageShapeSkeleton);

/// Vertex count of the Garage shape's sole part (four vertices).
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS302GarageShapePartVerts[] = {
#include "assets/mappic_s2_02_model_00C48_00C6C_partVerts.inc"
};
#else
static u32 _gMappicS302GarageShapePartVerts[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_00C6C_partVerts", _gMappicS302GarageShapePartVerts);

/// Garage's map footprint in integer model X/Z coordinates, with Y zero.
#ifdef PE_EMBED_ASSETS
static SVECTOR _gMappicS302GarageShapeVerts[] = {
#include "assets/mappic_s2_02_model_00C48_00C6C_verts.inc"
};
#else
static SVECTOR _gMappicS302GarageShapeVerts[4];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_00C6C_verts", _gMappicS302GarageShapeVerts);

/// Packed command stream for the Garage shape's single unlit quad.
///
/// Four vertex byte offsets and white colour are followed by two group ends
/// and the stream end. The map reads only the first group.
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS302GarageShapeStream[] = {
#include "assets/mappic_s2_02_model_00C48_00C6C_stream.inc"
};
#else
static u32 _gMappicS302GarageShapeStream[9];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_00C6C_stream", _gMappicS302GarageShapeStream);

TmdSource gMappicS302GarageShape = {
    .bufferHalfBytes  = sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS302GarageShapeSkeleton),
    .partVertexCounts = _gMappicS302GarageShapePartVerts,
    .verts            = _gMappicS302GarageShapeVerts,
    .normals          = &_gMappicS302GarageShapeVerts[ARRAY_SIZE(_gMappicS302GarageShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS302GarageShapeSkeleton,
    .stream           = _gMappicS302GarageShapeStream,
};

/// Identity transform and self-parented root for the Driveway shape.
#ifdef PE_EMBED_ASSETS
static TmdBone _gMappicS302DrivewayShapeSkeleton[] = {
#include "assets/mappic_s2_02_model_00CF8_skeleton.inc"
};
#else
static TmdBone _gMappicS302DrivewayShapeSkeleton[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00CF8_skeleton", _gMappicS302DrivewayShapeSkeleton);

/// Vertex count of the Driveway shape's sole part (eight vertices).
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS302DrivewayShapePartVerts[] = {
#include "assets/mappic_s2_02_model_00CF8_partVerts.inc"
};
#else
static u32 _gMappicS302DrivewayShapePartVerts[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00CF8_partVerts", _gMappicS302DrivewayShapePartVerts);

/// Driveway's map footprint in integer model X/Z coordinates, with Y zero.
#ifdef PE_EMBED_ASSETS
static SVECTOR _gMappicS302DrivewayShapeVerts[] = {
#include "assets/mappic_s2_02_model_00CF8_verts.inc"
};
#else
static SVECTOR _gMappicS302DrivewayShapeVerts[8];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00CF8_verts", _gMappicS302DrivewayShapeVerts);

/// Packed command stream for the Driveway shape's three unlit quads.
///
/// Each quad has four vertex byte offsets and white colour. Two group ends
/// and the stream end follow; the map reads only the first group.
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS302DrivewayShapeStream[] = {
#include "assets/mappic_s2_02_model_00CF8_stream.inc"
};
#else
static u32 _gMappicS302DrivewayShapeStream[15];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00CF8_stream", _gMappicS302DrivewayShapeStream);

TmdSource gMappicS302DrivewayShape = {
    .bufferHalfBytes  = 3 * sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS302DrivewayShapeSkeleton),
    .partVertexCounts = _gMappicS302DrivewayShapePartVerts,
    .verts            = _gMappicS302DrivewayShapeVerts,
    .normals          = &_gMappicS302DrivewayShapeVerts[ARRAY_SIZE(_gMappicS302DrivewayShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS302DrivewayShapeSkeleton,
    .stream           = _gMappicS302DrivewayShapeStream,
};

/// Identity transform and self-parented root for the Junk yard shape.
#ifdef PE_EMBED_ASSETS
static TmdBone _gMappicS302JunkYardShapeSkeleton[] = {
#include "assets/mappic_s2_02_model_00DD0_skeleton.inc"
};
#else
static TmdBone _gMappicS302JunkYardShapeSkeleton[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00DD0_skeleton", _gMappicS302JunkYardShapeSkeleton);

/// Vertex count of the Junk yard shape's sole part (ten vertices).
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS302JunkYardShapePartVerts[] = {
#include "assets/mappic_s2_02_model_00DD0_partVerts.inc"
};
#else
static u32 _gMappicS302JunkYardShapePartVerts[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00DD0_partVerts", _gMappicS302JunkYardShapePartVerts);

/// Junk yard's map footprint in integer model X/Z coordinates, with Y zero.
#ifdef PE_EMBED_ASSETS
static SVECTOR _gMappicS302JunkYardShapeVerts[] = {
#include "assets/mappic_s2_02_model_00DD0_verts.inc"
};
#else
static SVECTOR _gMappicS302JunkYardShapeVerts[10];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00DD0_verts", _gMappicS302JunkYardShapeVerts);

/// Packed command stream for the Junk yard shape's two unlit triangles and three unlit quads.
///
/// Vertex byte offsets and white colours are followed by two group ends and
/// the stream end. The map reads only the first group and supplies its texture.
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS302JunkYardShapeStream[] = {
#include "assets/mappic_s2_02_model_00DD0_stream.inc"
};
#else
static u32 _gMappicS302JunkYardShapeStream[24];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00DD0_stream", _gMappicS302JunkYardShapeStream);

TmdSource gMappicS302JunkYardShape = {
    .bufferHalfBytes  = 2 * sizeof(POLY_F3) + 3 * sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS302JunkYardShapeSkeleton),
    .partVertexCounts = _gMappicS302JunkYardShapePartVerts,
    .verts            = _gMappicS302JunkYardShapeVerts,
    .normals          = &_gMappicS302JunkYardShapeVerts[ARRAY_SIZE(_gMappicS302JunkYardShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS302JunkYardShapeSkeleton,
    .stream           = _gMappicS302JunkYardShapeStream,
};

/// Identity transform and self-parented root for the Trailer Coach shape.
#ifdef PE_EMBED_ASSETS
static TmdBone _gMappicS302TrailerCoachShapeSkeleton[] = {
#include "assets/mappic_s2_02_model_00C48_00EC0_skeleton.inc"
};
#else
static TmdBone _gMappicS302TrailerCoachShapeSkeleton[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_00EC0_skeleton", _gMappicS302TrailerCoachShapeSkeleton);

/// Vertex count of the Trailer Coach shape's sole part (four vertices).
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS302TrailerCoachShapePartVerts[] = {
#include "assets/mappic_s2_02_model_00C48_00EC0_partVerts.inc"
};
#else
static u32 _gMappicS302TrailerCoachShapePartVerts[1];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_00EC0_partVerts", _gMappicS302TrailerCoachShapePartVerts);

/// Trailer Coach's map footprint in integer model X/Z coordinates, with Y zero.
#ifdef PE_EMBED_ASSETS
static SVECTOR _gMappicS302TrailerCoachShapeVerts[] = {
#include "assets/mappic_s2_02_model_00C48_00EC0_verts.inc"
};
#else
static SVECTOR _gMappicS302TrailerCoachShapeVerts[4];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_00EC0_verts", _gMappicS302TrailerCoachShapeVerts);

/// Packed command stream for the Trailer Coach shape's single unlit quad.
///
/// Four vertex byte offsets and white colour are followed by two group ends
/// and the stream end. The map reads only the first group and supplies its texture.
#ifdef PE_EMBED_ASSETS
static u32 _gMappicS302TrailerCoachShapeStream[] = {
#include "assets/mappic_s2_02_model_00C48_00EC0_stream.inc"
};
#else
static u32 _gMappicS302TrailerCoachShapeStream[9];
#endif
PE_ASSET_BIND("mappic_s2_02_model_00C48_00EC0_stream", _gMappicS302TrailerCoachShapeStream);

TmdSource gMappicS302TrailerCoachShape = {
    .bufferHalfBytes  = sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS302TrailerCoachShapeSkeleton),
    .partVertexCounts = _gMappicS302TrailerCoachShapePartVerts,
    .verts            = _gMappicS302TrailerCoachShapeVerts,
    .normals          = &_gMappicS302TrailerCoachShapeVerts[ARRAY_SIZE(_gMappicS302TrailerCoachShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS302TrailerCoachShapeSkeleton,
    .stream           = _gMappicS302TrailerCoachShapeStream,
};
