#include "mappic/mappic.h"
#include "port/asset_bind.h"

#include <libgpu.h>

#include "common.h"

/// Identity transform and self-parented root for the B1 elevator hall shape.
static TmdBone _gMappicS403B1ElevatorHallShapeSkeleton[1];
PE_ASSET_BIND("mappic_s4_06_model_0014C_skeleton", _gMappicS403B1ElevatorHallShapeSkeleton);

/// Vertex count of the B1 elevator hall shape's sole part (eight vertices).
static u32 _gMappicS403B1ElevatorHallShapePartVerts[1];
PE_ASSET_BIND("mappic_s4_06_model_0014C_partVerts", _gMappicS403B1ElevatorHallShapePartVerts);

/// B1 elevator hall's map footprint in integer model X/Z coordinates, with Y zero.
static SVECTOR _gMappicS403B1ElevatorHallShapeVerts[8];
PE_ASSET_BIND("mappic_s4_06_model_0014C_verts", _gMappicS403B1ElevatorHallShapeVerts);

/// Three unlit quads' packed vertex byte offsets and white colour, followed by two group ends and the stream end.
static u32 _gMappicS403B1ElevatorHallShapeStream[15];
PE_ASSET_BIND("mappic_s4_06_model_0014C_stream", _gMappicS403B1ElevatorHallShapeStream);

TmdSource gMappicS403B1ElevatorHallShape = {
    .bufferHalfBytes  = 3 * sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS403B1ElevatorHallShapeSkeleton),
    .partVertexCounts = _gMappicS403B1ElevatorHallShapePartVerts,
    .verts            = _gMappicS403B1ElevatorHallShapeVerts,
    .normals          = &_gMappicS403B1ElevatorHallShapeVerts[ARRAY_SIZE(_gMappicS403B1ElevatorHallShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS403B1ElevatorHallShapeSkeleton,
    .stream           = _gMappicS403B1ElevatorHallShapeStream,
};

/// Identity transform and self-parented root for the B1 south maintenance walkway shape.
static TmdBone _gMappicS403B1SouthMaintenanceWalkwayShapeSkeleton[1];
PE_ASSET_BIND("mappic_s4_00_model_0005C_00154_mappic_s4_03_skeleton", _gMappicS403B1SouthMaintenanceWalkwayShapeSkeleton);

/// Vertex count of the B1 south maintenance walkway shape's sole part (six vertices).
static u32 _gMappicS403B1SouthMaintenanceWalkwayShapePartVerts[1];
PE_ASSET_BIND("mappic_s4_00_model_0005C_00154_mappic_s4_03_partVerts", _gMappicS403B1SouthMaintenanceWalkwayShapePartVerts);

/// B1 south maintenance walkway's map footprint in integer model X/Z coordinates, with Y zero.
static SVECTOR _gMappicS403B1SouthMaintenanceWalkwayShapeVerts[6];
PE_ASSET_BIND("mappic_s4_00_model_0005C_00154_mappic_s4_03_verts", _gMappicS403B1SouthMaintenanceWalkwayShapeVerts);

/// Two unlit quads' packed vertex byte offsets and white colour, followed by two group ends and the stream end.
static u32 _gMappicS403B1SouthMaintenanceWalkwayShapeStream[12];
PE_ASSET_BIND("mappic_s4_00_model_0005C_00154_mappic_s4_03_stream", _gMappicS403B1SouthMaintenanceWalkwayShapeStream);

TmdSource gMappicS403B1SouthMaintenanceWalkwayShape = {
    .bufferHalfBytes  = 2 * sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS403B1SouthMaintenanceWalkwayShapeSkeleton),
    .partVertexCounts = _gMappicS403B1SouthMaintenanceWalkwayShapePartVerts,
    .verts            = _gMappicS403B1SouthMaintenanceWalkwayShapeVerts,
    .normals          = &_gMappicS403B1SouthMaintenanceWalkwayShapeVerts[ARRAY_SIZE(_gMappicS403B1SouthMaintenanceWalkwayShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS403B1SouthMaintenanceWalkwayShapeSkeleton,
    .stream           = _gMappicS403B1SouthMaintenanceWalkwayShapeStream,
};

/// Identity transform and self-parented root for the B1 storeroom shape.
static TmdBone _gMappicS403B1StoreroomShapeSkeleton[1];
PE_ASSET_BIND("mappic_s2_02_model_00C48_001E4_skeleton", _gMappicS403B1StoreroomShapeSkeleton);

/// Vertex count of the B1 storeroom shape's sole part (four vertices).
static u32 _gMappicS403B1StoreroomShapePartVerts[1];
PE_ASSET_BIND("mappic_s2_02_model_00C48_001E4_partVerts", _gMappicS403B1StoreroomShapePartVerts);

/// B1 storeroom's map footprint in integer model X/Z coordinates, with Y zero.
static SVECTOR _gMappicS403B1StoreroomShapeVerts[4];
PE_ASSET_BIND("mappic_s2_02_model_00C48_001E4_verts", _gMappicS403B1StoreroomShapeVerts);

/// One unlit quad's packed vertex byte offsets and white colour, followed by two group ends and the stream end.
static u32 _gMappicS403B1StoreroomShapeStream[9];
PE_ASSET_BIND("mappic_s2_02_model_00C48_001E4_stream", _gMappicS403B1StoreroomShapeStream);

TmdSource gMappicS403B1StoreroomShape = {
    .bufferHalfBytes  = sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS403B1StoreroomShapeSkeleton),
    .partVertexCounts = _gMappicS403B1StoreroomShapePartVerts,
    .verts            = _gMappicS403B1StoreroomShapeVerts,
    .normals          = &_gMappicS403B1StoreroomShapeVerts[ARRAY_SIZE(_gMappicS403B1StoreroomShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS403B1StoreroomShapeSkeleton,
    .stream           = _gMappicS403B1StoreroomShapeStream,
};

/// Identity transform and self-parented root for the B1 north maintenance walkway shape.
static TmdBone _gMappicS403B1NorthMaintenanceWalkwayShapeSkeleton[1];
PE_ASSET_BIND("mappic_s4_00_model_0005C_00290_skeleton", _gMappicS403B1NorthMaintenanceWalkwayShapeSkeleton);

/// Vertex count of the B1 north maintenance walkway shape's sole part (six vertices).
static u32 _gMappicS403B1NorthMaintenanceWalkwayShapePartVerts[1];
PE_ASSET_BIND("mappic_s4_00_model_0005C_00290_partVerts", _gMappicS403B1NorthMaintenanceWalkwayShapePartVerts);

/// B1 north maintenance walkway's map footprint in integer model X/Z coordinates, with Y zero.
static SVECTOR _gMappicS403B1NorthMaintenanceWalkwayShapeVerts[6];
PE_ASSET_BIND("mappic_s4_00_model_0005C_00290_verts", _gMappicS403B1NorthMaintenanceWalkwayShapeVerts);

/// Two unlit quads' packed vertex byte offsets and white colour, followed by two group ends and the stream end.
static u32 _gMappicS403B1NorthMaintenanceWalkwayShapeStream[12];
PE_ASSET_BIND("mappic_s4_00_model_0005C_00290_stream", _gMappicS403B1NorthMaintenanceWalkwayShapeStream);

TmdSource gMappicS403B1NorthMaintenanceWalkwayShape = {
    .bufferHalfBytes  = 2 * sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS403B1NorthMaintenanceWalkwayShapeSkeleton),
    .partVertexCounts = _gMappicS403B1NorthMaintenanceWalkwayShapePartVerts,
    .verts            = _gMappicS403B1NorthMaintenanceWalkwayShapeVerts,
    .normals          = &_gMappicS403B1NorthMaintenanceWalkwayShapeVerts[ARRAY_SIZE(_gMappicS403B1NorthMaintenanceWalkwayShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS403B1NorthMaintenanceWalkwayShapeSkeleton,
    .stream           = _gMappicS403B1NorthMaintenanceWalkwayShapeStream,
};

/// Identity transform and self-parented root for the B1 armory shape.
static TmdBone _gMappicS403B1ArmoryShapeSkeleton[1];
PE_ASSET_BIND("mappic_s4_00_model_0005C_0033C_skeleton", _gMappicS403B1ArmoryShapeSkeleton);

/// Vertex count of the B1 armory shape's sole part (six vertices).
static u32 _gMappicS403B1ArmoryShapePartVerts[1];
PE_ASSET_BIND("mappic_s4_00_model_0005C_0033C_partVerts", _gMappicS403B1ArmoryShapePartVerts);

/// B1 armory's map footprint in integer model X/Z coordinates, with Y zero.
static SVECTOR _gMappicS403B1ArmoryShapeVerts[6];
PE_ASSET_BIND("mappic_s4_00_model_0005C_0033C_verts", _gMappicS403B1ArmoryShapeVerts);

/// Two unlit quads' packed vertex byte offsets and white colour, followed by two group ends and the stream end.
static u32 _gMappicS403B1ArmoryShapeStream[12];
PE_ASSET_BIND("mappic_s4_00_model_0005C_0033C_stream", _gMappicS403B1ArmoryShapeStream);

TmdSource gMappicS403B1ArmoryShape = {
    .bufferHalfBytes  = 2 * sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS403B1ArmoryShapeSkeleton),
    .partVertexCounts = _gMappicS403B1ArmoryShapePartVerts,
    .verts            = _gMappicS403B1ArmoryShapeVerts,
    .normals          = &_gMappicS403B1ArmoryShapeVerts[ARRAY_SIZE(_gMappicS403B1ArmoryShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS403B1ArmoryShapeSkeleton,
    .stream           = _gMappicS403B1ArmoryShapeStream,
};

/// Identity transform and self-parented root for the B1 sleeping quarters shape.
static TmdBone _gMappicS403B1SleepingQuartersShapeSkeleton[1];
PE_ASSET_BIND("mappic_s4_00_model_0005C_003E8_skeleton", _gMappicS403B1SleepingQuartersShapeSkeleton);

/// Vertex count of the B1 sleeping quarters shape's sole part (six vertices).
static u32 _gMappicS403B1SleepingQuartersShapePartVerts[1];
PE_ASSET_BIND("mappic_s4_00_model_0005C_003E8_partVerts", _gMappicS403B1SleepingQuartersShapePartVerts);

/// B1 sleeping quarters' map footprint in integer model X/Z coordinates, with Y zero.
static SVECTOR _gMappicS403B1SleepingQuartersShapeVerts[6];
PE_ASSET_BIND("mappic_s4_00_model_0005C_003E8_verts", _gMappicS403B1SleepingQuartersShapeVerts);

/// Two unlit quads' packed vertex byte offsets and white colour, followed by two group ends and the stream end.
static u32 _gMappicS403B1SleepingQuartersShapeStream[12];
PE_ASSET_BIND("mappic_s4_00_model_0005C_003E8_stream", _gMappicS403B1SleepingQuartersShapeStream);

TmdSource gMappicS403B1SleepingQuartersShape = {
    .bufferHalfBytes  = 2 * sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS403B1SleepingQuartersShapeSkeleton),
    .partVertexCounts = _gMappicS403B1SleepingQuartersShapePartVerts,
    .verts            = _gMappicS403B1SleepingQuartersShapeVerts,
    .normals          = &_gMappicS403B1SleepingQuartersShapeVerts[ARRAY_SIZE(_gMappicS403B1SleepingQuartersShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS403B1SleepingQuartersShapeSkeleton,
    .stream           = _gMappicS403B1SleepingQuartersShapeStream,
};

/// Identity transform and self-parented root for the B1 main corridor shape.
static TmdBone _gMappicS403B1MainCorridorShapeSkeleton[1];
PE_ASSET_BIND("mappic_s2_02_model_00910_004C8_skeleton", _gMappicS403B1MainCorridorShapeSkeleton);

/// Vertex count of the B1 main corridor shape's sole part (eight vertices).
static u32 _gMappicS403B1MainCorridorShapePartVerts[1];
PE_ASSET_BIND("mappic_s2_02_model_00910_004C8_partVerts", _gMappicS403B1MainCorridorShapePartVerts);

/// B1 main corridor's map footprint in integer model X/Z coordinates, with Y zero.
static SVECTOR _gMappicS403B1MainCorridorShapeVerts[8];
PE_ASSET_BIND("mappic_s2_02_model_00910_004C8_verts", _gMappicS403B1MainCorridorShapeVerts);

/// Two unlit triangles and two quads, with packed vertex byte offsets and white colour, then two group ends and the stream end.
static u32 _gMappicS403B1MainCorridorShapeStream[21];
PE_ASSET_BIND("mappic_s2_02_model_00910_004C8_stream", _gMappicS403B1MainCorridorShapeStream);

TmdSource gMappicS403B1MainCorridorShape = {
    .bufferHalfBytes  = 2 * sizeof(POLY_F3) + 2 * sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS403B1MainCorridorShapeSkeleton),
    .partVertexCounts = _gMappicS403B1MainCorridorShapePartVerts,
    .verts            = _gMappicS403B1MainCorridorShapeVerts,
    .normals          = &_gMappicS403B1MainCorridorShapeVerts[ARRAY_SIZE(_gMappicS403B1MainCorridorShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS403B1MainCorridorShapeSkeleton,
    .stream           = _gMappicS403B1MainCorridorShapeStream,
};

/// Identity transform and self-parented root for the B1 sterilization room shape.
static TmdBone _gMappicS403B1SterilizationRoomShapeSkeleton[1];
PE_ASSET_BIND("mappic_s2_02_model_00C48_00558_skeleton", _gMappicS403B1SterilizationRoomShapeSkeleton);

/// Vertex count of the B1 sterilization room shape's sole part (four vertices).
static u32 _gMappicS403B1SterilizationRoomShapePartVerts[1];
PE_ASSET_BIND("mappic_s2_02_model_00C48_00558_partVerts", _gMappicS403B1SterilizationRoomShapePartVerts);

/// B1 sterilization room's map footprint in integer model X/Z coordinates, with Y zero.
static SVECTOR _gMappicS403B1SterilizationRoomShapeVerts[4];
PE_ASSET_BIND("mappic_s2_02_model_00C48_00558_verts", _gMappicS403B1SterilizationRoomShapeVerts);

/// One unlit quad's packed vertex byte offsets and white colour, followed by two group ends and the stream end.
static u32 _gMappicS403B1SterilizationRoomShapeStream[9];
PE_ASSET_BIND("mappic_s2_02_model_00C48_00558_stream", _gMappicS403B1SterilizationRoomShapeStream);

TmdSource gMappicS403B1SterilizationRoomShape = {
    .bufferHalfBytes  = sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS403B1SterilizationRoomShapeSkeleton),
    .partVertexCounts = _gMappicS403B1SterilizationRoomShapePartVerts,
    .verts            = _gMappicS403B1SterilizationRoomShapeVerts,
    .normals          = &_gMappicS403B1SterilizationRoomShapeVerts[ARRAY_SIZE(_gMappicS403B1SterilizationRoomShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS403B1SterilizationRoomShapeSkeleton,
    .stream           = _gMappicS403B1SterilizationRoomShapeStream,
};

/// Identity transform and self-parented root for the B1 pod access tunnel shape.
static TmdBone _gMappicS403B1PodAccessTunnelShapeSkeleton[1];
PE_ASSET_BIND("mappic_s2_03_model_001F0_00654_skeleton", _gMappicS403B1PodAccessTunnelShapeSkeleton);

/// Vertex count of the B1 pod access tunnel shape's sole part (ten vertices).
static u32 _gMappicS403B1PodAccessTunnelShapePartVerts[1];
PE_ASSET_BIND("mappic_s2_03_model_001F0_00654_partVerts", _gMappicS403B1PodAccessTunnelShapePartVerts);

/// B1 pod access tunnel's map footprint in integer model X/Z coordinates, with Y zero.
static SVECTOR _gMappicS403B1PodAccessTunnelShapeVerts[10];
PE_ASSET_BIND("mappic_s2_03_model_001F0_00654_verts", _gMappicS403B1PodAccessTunnelShapeVerts);

/// Two unlit triangles and three quads, with packed vertex byte offsets and white colour, then two group ends and the stream end.
static u32 _gMappicS403B1PodAccessTunnelShapeStream[24];
PE_ASSET_BIND("mappic_s2_03_model_001F0_00654_stream", _gMappicS403B1PodAccessTunnelShapeStream);

TmdSource gMappicS403B1PodAccessTunnelShape = {
    .bufferHalfBytes  = 2 * sizeof(POLY_F3) + 3 * sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS403B1PodAccessTunnelShapeSkeleton),
    .partVertexCounts = _gMappicS403B1PodAccessTunnelShapePartVerts,
    .verts            = _gMappicS403B1PodAccessTunnelShapeVerts,
    .normals          = &_gMappicS403B1PodAccessTunnelShapeVerts[ARRAY_SIZE(_gMappicS403B1PodAccessTunnelShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS403B1PodAccessTunnelShapeSkeleton,
    .stream           = _gMappicS403B1PodAccessTunnelShapeStream,
};

/// Identity transform and self-parented root for the B1 control room shape.
static TmdBone _gMappicS403B1ControlRoomShapeSkeleton[1];
PE_ASSET_BIND("mappic_s4_06_model_00214_skeleton", _gMappicS403B1ControlRoomShapeSkeleton);

/// Vertex count of the B1 control room shape's sole part (eight vertices).
static u32 _gMappicS403B1ControlRoomShapePartVerts[1];
PE_ASSET_BIND("mappic_s4_06_model_00214_partVerts", _gMappicS403B1ControlRoomShapePartVerts);

/// B1 control room's map footprint in integer model X/Z coordinates, with Y zero.
static SVECTOR _gMappicS403B1ControlRoomShapeVerts[8];
PE_ASSET_BIND("mappic_s4_06_model_00214_verts", _gMappicS403B1ControlRoomShapeVerts);

/// Two unlit triangles and two quads, with packed vertex byte offsets and white colour, then two group ends and the stream end.
static u32 _gMappicS403B1ControlRoomShapeStream[21];
PE_ASSET_BIND("mappic_s4_06_model_00214_stream", _gMappicS403B1ControlRoomShapeStream);

TmdSource gMappicS403B1ControlRoomShape = {
    .bufferHalfBytes  = 2 * sizeof(POLY_F3) + 2 * sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS403B1ControlRoomShapeSkeleton),
    .partVertexCounts = _gMappicS403B1ControlRoomShapePartVerts,
    .verts            = _gMappicS403B1ControlRoomShapeVerts,
    .normals          = &_gMappicS403B1ControlRoomShapeVerts[ARRAY_SIZE(_gMappicS403B1ControlRoomShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS403B1ControlRoomShapeSkeleton,
    .stream           = _gMappicS403B1ControlRoomShapeStream,
};

/// Identity transform and self-parented root for the B1 access tunnel shape.
static TmdBone _gMappicS403B1AccessTunnelShapeSkeleton[1];
PE_ASSET_BIND("mappic_s4_00_model_0005C_007E0_skeleton", _gMappicS403B1AccessTunnelShapeSkeleton);

/// Vertex count of the B1 access tunnel shape's sole part (six vertices).
static u32 _gMappicS403B1AccessTunnelShapePartVerts[1];
PE_ASSET_BIND("mappic_s4_00_model_0005C_007E0_partVerts", _gMappicS403B1AccessTunnelShapePartVerts);

/// B1 access tunnel's map footprint in integer model X/Z coordinates, with Y zero.
static SVECTOR _gMappicS403B1AccessTunnelShapeVerts[6];
PE_ASSET_BIND("mappic_s4_00_model_0005C_007E0_verts", _gMappicS403B1AccessTunnelShapeVerts);

/// Two unlit quads' packed vertex byte offsets and white colour, followed by two group ends and the stream end.
static u32 _gMappicS403B1AccessTunnelShapeStream[12];
PE_ASSET_BIND("mappic_s4_00_model_0005C_007E0_stream", _gMappicS403B1AccessTunnelShapeStream);

TmdSource gMappicS403B1AccessTunnelShape = {
    .bufferHalfBytes  = 2 * sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS403B1AccessTunnelShapeSkeleton),
    .partVertexCounts = _gMappicS403B1AccessTunnelShapePartVerts,
    .verts            = _gMappicS403B1AccessTunnelShapeVerts,
    .normals          = &_gMappicS403B1AccessTunnelShapeVerts[ARRAY_SIZE(_gMappicS403B1AccessTunnelShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS403B1AccessTunnelShapeSkeleton,
    .stream           = _gMappicS403B1AccessTunnelShapeStream,
};

/// Identity transform and self-parented root for the B1 underground parking shape.
static TmdBone _gMappicS403B1UndergroundParkingShapeSkeleton[1];
PE_ASSET_BIND("mappic_s2_02_model_00910_008C0_skeleton", _gMappicS403B1UndergroundParkingShapeSkeleton);

/// Vertex count of the B1 underground parking shape's sole part (eight vertices).
static u32 _gMappicS403B1UndergroundParkingShapePartVerts[1];
PE_ASSET_BIND("mappic_s2_02_model_00910_008C0_partVerts", _gMappicS403B1UndergroundParkingShapePartVerts);

/// B1 underground parking's map footprint in integer model X/Z coordinates, with Y zero.
static SVECTOR _gMappicS403B1UndergroundParkingShapeVerts[8];
PE_ASSET_BIND("mappic_s2_02_model_00910_008C0_verts", _gMappicS403B1UndergroundParkingShapeVerts);

/// Two unlit triangles and two quads, with packed vertex byte offsets and white colour, then two group ends and the stream end.
static u32 _gMappicS403B1UndergroundParkingShapeStream[21];
PE_ASSET_BIND("mappic_s2_02_model_00910_008C0_stream", _gMappicS403B1UndergroundParkingShapeStream);

TmdSource gMappicS403B1UndergroundParkingShape = {
    .bufferHalfBytes  = 2 * sizeof(POLY_F3) + 2 * sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS403B1UndergroundParkingShapeSkeleton),
    .partVertexCounts = _gMappicS403B1UndergroundParkingShapePartVerts,
    .verts            = _gMappicS403B1UndergroundParkingShapeVerts,
    .normals          = &_gMappicS403B1UndergroundParkingShapeVerts[ARRAY_SIZE(_gMappicS403B1UndergroundParkingShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS403B1UndergroundParkingShapeSkeleton,
    .stream           = _gMappicS403B1UndergroundParkingShapeStream,
};

/// Identity transform and self-parented root for the B1 GOLEM freezer 1 shape.
static TmdBone _gMappicS403B1GolemFreezer1ShapeSkeleton[1];
PE_ASSET_BIND("mappic_s4_06_model_00214_009A0_skeleton", _gMappicS403B1GolemFreezer1ShapeSkeleton);

/// Vertex count of the B1 GOLEM freezer 1 shape's sole part (eight vertices).
static u32 _gMappicS403B1GolemFreezer1ShapePartVerts[1];
PE_ASSET_BIND("mappic_s4_06_model_00214_009A0_partVerts", _gMappicS403B1GolemFreezer1ShapePartVerts);

/// B1 GOLEM freezer 1's map footprint in integer model X/Z coordinates, with Y zero.
static SVECTOR _gMappicS403B1GolemFreezer1ShapeVerts[8];
PE_ASSET_BIND("mappic_s4_06_model_00214_009A0_verts", _gMappicS403B1GolemFreezer1ShapeVerts);

/// Two unlit triangles and two quads, with packed vertex byte offsets and white colour, then two group ends and the stream end.
static u32 _gMappicS403B1GolemFreezer1ShapeStream[21];
PE_ASSET_BIND("mappic_s4_06_model_00214_009A0_stream", _gMappicS403B1GolemFreezer1ShapeStream);

TmdSource gMappicS403B1GolemFreezer1Shape = {
    .bufferHalfBytes  = 2 * sizeof(POLY_F3) + 2 * sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS403B1GolemFreezer1ShapeSkeleton),
    .partVertexCounts = _gMappicS403B1GolemFreezer1ShapePartVerts,
    .verts            = _gMappicS403B1GolemFreezer1ShapeVerts,
    .normals          = &_gMappicS403B1GolemFreezer1ShapeVerts[ARRAY_SIZE(_gMappicS403B1GolemFreezer1ShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS403B1GolemFreezer1ShapeSkeleton,
    .stream           = _gMappicS403B1GolemFreezer1ShapeStream,
};

/// Identity transform and self-parented root for the B1 transfer tunnel shape.
static TmdBone _gMappicS403B1TransferTunnelShapeSkeleton[1];
PE_ASSET_BIND("mappic_s2_02_model_00C48_00A30_skeleton", _gMappicS403B1TransferTunnelShapeSkeleton);

/// Vertex count of the B1 transfer tunnel shape's sole part (four vertices).
static u32 _gMappicS403B1TransferTunnelShapePartVerts[1];
PE_ASSET_BIND("mappic_s2_02_model_00C48_00A30_partVerts", _gMappicS403B1TransferTunnelShapePartVerts);

/// B1 transfer tunnel's map footprint in integer model X/Z coordinates, with Y zero.
static SVECTOR _gMappicS403B1TransferTunnelShapeVerts[4];
PE_ASSET_BIND("mappic_s2_02_model_00C48_00A30_verts", _gMappicS403B1TransferTunnelShapeVerts);

/// One unlit quad's packed vertex byte offsets and white colour, followed by two group ends and the stream end.
static u32 _gMappicS403B1TransferTunnelShapeStream[9];
PE_ASSET_BIND("mappic_s2_02_model_00C48_00A30_stream", _gMappicS403B1TransferTunnelShapeStream);

TmdSource gMappicS403B1TransferTunnelShape = {
    .bufferHalfBytes  = sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS403B1TransferTunnelShapeSkeleton),
    .partVertexCounts = _gMappicS403B1TransferTunnelShapePartVerts,
    .verts            = _gMappicS403B1TransferTunnelShapeVerts,
    .normals          = &_gMappicS403B1TransferTunnelShapeVerts[ARRAY_SIZE(_gMappicS403B1TransferTunnelShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS403B1TransferTunnelShapeSkeleton,
    .stream           = _gMappicS403B1TransferTunnelShapeStream,
};

/// Identity transform and self-parented root for the B1 control room access tunnel shape.
static TmdBone _gMappicS403B1ControlRoomAccessTunnelShapeSkeleton[1];
PE_ASSET_BIND("mappic_s2_02_model_00C48_00AC0_skeleton", _gMappicS403B1ControlRoomAccessTunnelShapeSkeleton);

/// Vertex count of the B1 control room access tunnel shape's sole part (four vertices).
static u32 _gMappicS403B1ControlRoomAccessTunnelShapePartVerts[1];
PE_ASSET_BIND("mappic_s2_02_model_00C48_00AC0_partVerts", _gMappicS403B1ControlRoomAccessTunnelShapePartVerts);

/// B1 control room access tunnel's map footprint in integer model X/Z coordinates, with Y zero.
static SVECTOR _gMappicS403B1ControlRoomAccessTunnelShapeVerts[4];
PE_ASSET_BIND("mappic_s2_02_model_00C48_00AC0_verts", _gMappicS403B1ControlRoomAccessTunnelShapeVerts);

/// One unlit quad's packed vertex byte offsets and white colour, followed by two group ends and the stream end.
static u32 _gMappicS403B1ControlRoomAccessTunnelShapeStream[9];
PE_ASSET_BIND("mappic_s2_02_model_00C48_00AC0_stream", _gMappicS403B1ControlRoomAccessTunnelShapeStream);

TmdSource gMappicS403B1ControlRoomAccessTunnelShape = {
    .bufferHalfBytes  = sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS403B1ControlRoomAccessTunnelShapeSkeleton),
    .partVertexCounts = _gMappicS403B1ControlRoomAccessTunnelShapePartVerts,
    .verts            = _gMappicS403B1ControlRoomAccessTunnelShapeVerts,
    .normals          = &_gMappicS403B1ControlRoomAccessTunnelShapeVerts[ARRAY_SIZE(_gMappicS403B1ControlRoomAccessTunnelShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS403B1ControlRoomAccessTunnelShapeSkeleton,
    .stream           = _gMappicS403B1ControlRoomAccessTunnelShapeStream,
};

/// Identity transform and self-parented root for the B1 pod deck shape.
static TmdBone _gMappicS403B1PodDeckShapeSkeleton[1];
PE_ASSET_BIND("mappic_s4_03_model_00B5C_skeleton", _gMappicS403B1PodDeckShapeSkeleton);

/// Vertex count of the B1 pod deck shape's sole part (ten vertices).
static u32 _gMappicS403B1PodDeckShapePartVerts[1];
PE_ASSET_BIND("mappic_s4_03_model_00B5C_partVerts", _gMappicS403B1PodDeckShapePartVerts);

/// B1 pod deck's map footprint in integer model X/Z coordinates, with Y zero.
static SVECTOR _gMappicS403B1PodDeckShapeVerts[10];
PE_ASSET_BIND("mappic_s4_03_model_00B5C_verts", _gMappicS403B1PodDeckShapeVerts);

/// Two unlit triangles and three quads, with packed vertex byte offsets and white colour, then two group ends and the stream end.
static u32 _gMappicS403B1PodDeckShapeStream[24];
PE_ASSET_BIND("mappic_s4_03_model_00B5C_stream", _gMappicS403B1PodDeckShapeStream);

TmdSource gMappicS403B1PodDeckShape = {
    .bufferHalfBytes  = 2 * sizeof(POLY_F3) + 3 * sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS403B1PodDeckShapeSkeleton),
    .partVertexCounts = _gMappicS403B1PodDeckShapePartVerts,
    .verts            = _gMappicS403B1PodDeckShapeVerts,
    .normals          = &_gMappicS403B1PodDeckShapeVerts[ARRAY_SIZE(_gMappicS403B1PodDeckShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS403B1PodDeckShapeSkeleton,
    .stream           = _gMappicS403B1PodDeckShapeStream,
};
