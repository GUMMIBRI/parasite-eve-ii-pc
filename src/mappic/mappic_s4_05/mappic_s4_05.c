#include "mappic/mappic.h"
#include "port/asset_bind.h"

#include <libgpu.h>

#include "common.h"

/// Identity transform and self-parented root for the Dumping Hole shape.
static TmdBone _gMappicS405DumpingHoleShapeSkeleton[1];
PE_ASSET_BIND("mappic_s2_02_model_00910_000C0_skeleton", _gMappicS405DumpingHoleShapeSkeleton);

/// Vertex count of the Dumping Hole shape's sole part (eight vertices).
static u32 _gMappicS405DumpingHoleShapePartVerts[1];
PE_ASSET_BIND("mappic_s2_02_model_00910_000C0_partVerts", _gMappicS405DumpingHoleShapePartVerts);

/// Dumping Hole's map footprint in integer model X/Z coordinates, with Y zero.
static SVECTOR _gMappicS405DumpingHoleShapeVerts[8];
PE_ASSET_BIND("mappic_s2_02_model_00910_000C0_verts", _gMappicS405DumpingHoleShapeVerts);

/// Two unlit triangles and two quads with packed vertex byte offsets and white colour.
///
/// The first group contains the mesh; an empty group and `TMD_STREAM_END` follow.
static u32 _gMappicS405DumpingHoleShapeStream[21];
PE_ASSET_BIND("mappic_s2_02_model_00910_000C0_stream", _gMappicS405DumpingHoleShapeStream);

TmdSource gMappicS405DumpingHoleShape = {
    .bufferHalfBytes  = 2 * sizeof(POLY_F3) + 2 * sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS405DumpingHoleShapeSkeleton),
    .partVertexCounts = _gMappicS405DumpingHoleShapePartVerts,
    .verts            = _gMappicS405DumpingHoleShapeVerts,
    .normals          = &_gMappicS405DumpingHoleShapeVerts[ARRAY_SIZE(_gMappicS405DumpingHoleShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS405DumpingHoleShapeSkeleton,
    .stream           = _gMappicS405DumpingHoleShapeStream,
};

/// Identity transform and self-parented root for the Garbage Incinerator shape.
static TmdBone _gMappicS405GarbageIncineratorShapeSkeleton[1];
PE_ASSET_BIND("mappic_s4_05_model_0018C_skeleton", _gMappicS405GarbageIncineratorShapeSkeleton);

/// Vertex count of the Garbage Incinerator shape's sole part (sixteen vertices).
static u32 _gMappicS405GarbageIncineratorShapePartVerts[1];
PE_ASSET_BIND("mappic_s4_05_model_0018C_partVerts", _gMappicS405GarbageIncineratorShapePartVerts);

/// Garbage Incinerator's map footprint in integer model X/Z coordinates, with Y zero.
static SVECTOR _gMappicS405GarbageIncineratorShapeVerts[16];
PE_ASSET_BIND("mappic_s4_05_model_0018C_verts", _gMappicS405GarbageIncineratorShapeVerts);

/// Four unlit triangles and five quads with packed vertex byte offsets and white colour.
///
/// The first group contains the mesh; an empty group and `TMD_STREAM_END` follow.
static u32 _gMappicS405GarbageIncineratorShapeStream[36];
PE_ASSET_BIND("mappic_s4_05_model_0018C_stream", _gMappicS405GarbageIncineratorShapeStream);

TmdSource gMappicS405GarbageIncineratorShape = {
    .bufferHalfBytes  = 4 * sizeof(POLY_F3) + 5 * sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS405GarbageIncineratorShapeSkeleton),
    .partVertexCounts = _gMappicS405GarbageIncineratorShapePartVerts,
    .verts            = _gMappicS405GarbageIncineratorShapeVerts,
    .normals          = &_gMappicS405GarbageIncineratorShapeVerts[ARRAY_SIZE(_gMappicS405GarbageIncineratorShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS405GarbageIncineratorShapeSkeleton,
    .stream           = _gMappicS405GarbageIncineratorShapeStream,
};

/// Identity transform and self-parented root for the Incinerator Control Room shape.
static TmdBone _gMappicS405IncineratorControlRoomShapeSkeleton[1];
PE_ASSET_BIND("mappic_s4_00_model_0005C_002C8_skeleton", _gMappicS405IncineratorControlRoomShapeSkeleton);

/// Vertex count of the Incinerator Control Room shape's sole part (six vertices).
static u32 _gMappicS405IncineratorControlRoomShapePartVerts[1];
PE_ASSET_BIND("mappic_s4_00_model_0005C_002C8_partVerts", _gMappicS405IncineratorControlRoomShapePartVerts);

/// Incinerator Control Room's map footprint in integer model X/Z coordinates, with Y zero.
static SVECTOR _gMappicS405IncineratorControlRoomShapeVerts[6];
PE_ASSET_BIND("mappic_s4_00_model_0005C_002C8_verts", _gMappicS405IncineratorControlRoomShapeVerts);

/// Two unlit quads with packed vertex byte offsets and white colour.
///
/// The first group contains the mesh; an empty group and `TMD_STREAM_END` follow.
static u32 _gMappicS405IncineratorControlRoomShapeStream[12];
PE_ASSET_BIND("mappic_s4_00_model_0005C_002C8_stream", _gMappicS405IncineratorControlRoomShapeStream);

TmdSource gMappicS405IncineratorControlRoomShape = {
    .bufferHalfBytes  = 2 * sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS405IncineratorControlRoomShapeSkeleton),
    .partVertexCounts = _gMappicS405IncineratorControlRoomShapePartVerts,
    .verts            = _gMappicS405IncineratorControlRoomShapeVerts,
    .normals          = &_gMappicS405IncineratorControlRoomShapeVerts[ARRAY_SIZE(_gMappicS405IncineratorControlRoomShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS405IncineratorControlRoomShapeSkeleton,
    .stream           = _gMappicS405IncineratorControlRoomShapeStream,
};

/// Identity transform and self-parented root for the B3 Elevator Hall shape.
static TmdBone _gMappicS405ElevatorHallShapeSkeleton[1];
PE_ASSET_BIND("mappic_s4_05_model_00384_skeleton", _gMappicS405ElevatorHallShapeSkeleton);

/// Vertex count of the B3 Elevator Hall shape's sole part (fourteen vertices).
static u32 _gMappicS405ElevatorHallShapePartVerts[1];
PE_ASSET_BIND("mappic_s4_05_model_00384_partVerts", _gMappicS405ElevatorHallShapePartVerts);

/// B3 Elevator Hall's map footprint in integer model X/Z coordinates, with Y zero.
static SVECTOR _gMappicS405ElevatorHallShapeVerts[14];
PE_ASSET_BIND("mappic_s4_05_model_00384_verts", _gMappicS405ElevatorHallShapeVerts);

/// Two unlit triangles and five quads with packed vertex byte offsets and white colour.
///
/// The first group contains the mesh; an empty group and `TMD_STREAM_END` follow.
static u32 _gMappicS405ElevatorHallShapeStream[30];
PE_ASSET_BIND("mappic_s4_05_model_00384_stream", _gMappicS405ElevatorHallShapeStream);

TmdSource gMappicS405ElevatorHallShape = {
    .bufferHalfBytes  = 2 * sizeof(POLY_F3) + 5 * sizeof(POLY_F4),
    .partCount        = ARRAY_SIZE(_gMappicS405ElevatorHallShapeSkeleton),
    .partVertexCounts = _gMappicS405ElevatorHallShapePartVerts,
    .verts            = _gMappicS405ElevatorHallShapeVerts,
    .normals          = &_gMappicS405ElevatorHallShapeVerts[ARRAY_SIZE(_gMappicS405ElevatorHallShapeVerts)], // Empty normal pool at the vertex end.
    .skeleton         = _gMappicS405ElevatorHallShapeSkeleton,
    .stream           = _gMappicS405ElevatorHallShapeStream,
};
