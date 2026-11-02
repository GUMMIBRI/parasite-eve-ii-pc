#include "aya/aya.h"
#include "port/asset_bind.h"

#include <psyz.h>
#include <libgpu.h>

#include "common.h"

#include "gameplay/gpu_image_upload.h"

/// Facial-frame dimensions, in 16-bit VRAM words and rows.
enum {
    AYA_10300_EYES_FRAME_WIDTH_WORDS  = 25,
    AYA_10300_EYES_FRAME_HEIGHT_ROWS  = 16,
    AYA_10300_MOUTH_FRAME_WIDTH_WORDS = 14,
    AYA_10300_MOUTH_FRAME_HEIGHT_ROWS = 20,
};

/// Nineteen initial part transforms and parent indices copied into each player body.
///
/// Read-only pose and count tables retain their serialized positions in .data.
#ifdef PE_EMBED_ASSETS
static const TmdBone _gAya10300BodyModelSkeleton[19] SECTION(".data") = {
#include "assets/aya_10300_model_019A8_skeleton.inc"
};
#else
static TmdBone _gAya10300BodyModelSkeleton[19] SECTION(".data");
#endif
PE_ASSET_BIND("aya_10300_model_019A8_skeleton", _gAya10300BodyModelSkeleton);

/// Vertex counts for consecutive part-local groups in skeleton order, totaling 352.
#ifdef PE_EMBED_ASSETS
static const u32 _gAya10300BodyModelPartVerts[ARRAY_SIZE(_gAya10300BodyModelSkeleton)] SECTION(".data") = {
#include "assets/aya_10300_model_019A8_partVerts.inc"
};
#else
static u32 _gAya10300BodyModelPartVerts[19] SECTION(".data");
#endif
PE_ASSET_BIND("aya_10300_model_019A8_partVerts", _gAya10300BodyModelPartVerts);

/// Writable body vertices in integer coordinates local to their skeletal parts.
#ifdef PE_EMBED_ASSETS
static SVECTOR _gAya10300BodyModelVerts[352] = {
#include "assets/aya_10300_model_019A8_verts.inc"
};
#else
static SVECTOR _gAya10300BodyModelVerts[352];
#endif
PE_ASSET_BIND("aya_10300_model_019A8_verts", _gAya10300BodyModelVerts);

/// Writable body lighting normals with twelve fractional bits, indexed independently of vertices.
#ifdef PE_EMBED_ASSETS
static SVECTOR _gAya10300BodyModelNormals[373] = {
#include "assets/aya_10300_model_019A8_normals.inc"
};
#else
static SVECTOR _gAya10300BodyModelNormals[373];
#endif
PE_ASSET_BIND("aya_10300_model_019A8_normals", _gAya10300BodyModelNormals);

/// Writable commands for nineteen skeletal groups and a final pre-transformed group.
///
/// First model creation resolves handler slots in place; `TMD_STREAM_END` is
/// the last word. Projection commands populate the pre-transformed region.
#ifdef PE_EMBED_ASSETS
static u32 _gAya10300BodyModelStream[3829] = {
#include "assets/aya_10300_model_019A8_stream.inc"
};
#else
static u32 _gAya10300BodyModelStream[3829];
#endif
PE_ASSET_BIND("aya_10300_model_019A8_stream", _gAya10300BodyModelStream);

TmdSource gAya10300BodyModel = {
    .handlersResolved    = false,
    .bufferHalfBytes     = (236 * sizeof(POLY_GT3)) + (232 * sizeof(POLY_GT4)),
    .preXformRegionBytes = (66 * sizeof(POLY_GT3)) + (53 * sizeof(POLY_GT4)),
    .partCount           = ARRAY_SIZE(_gAya10300BodyModelSkeleton),
    .partVertexCounts    = _gAya10300BodyModelPartVerts,
    .verts               = _gAya10300BodyModelVerts,
    .normals             = _gAya10300BodyModelNormals,
    .skeleton            = _gAya10300BodyModelSkeleton,
    .stream              = _gAya10300BodyModelStream,
};

/// Initial local transform and self-parented root for first-pair hand slot 0.
#ifdef PE_EMBED_ASSETS
static const TmdBone _gAya10300FirstPairHand0ModelSkeleton[1] SECTION(".data") = {
#include "assets/aya_10300_model_05734_skeleton.inc"
};
#else
static TmdBone _gAya10300FirstPairHand0ModelSkeleton[1] SECTION(".data");
#endif
PE_ASSET_BIND("aya_10300_model_05734_skeleton", _gAya10300FirstPairHand0ModelSkeleton);

/// Vertex count of the hand's sole part: 23.
#ifdef PE_EMBED_ASSETS
static const u32 _gAya10300FirstPairHand0ModelPartVerts[ARRAY_SIZE(_gAya10300FirstPairHand0ModelSkeleton)] SECTION(".data") = {
#include "assets/aya_10300_model_05734_partVerts.inc"
};
#else
static u32 _gAya10300FirstPairHand0ModelPartVerts[1] SECTION(".data");
#endif
PE_ASSET_BIND("aya_10300_model_05734_partVerts", _gAya10300FirstPairHand0ModelPartVerts);

/// Writable first-pair hand-0 vertices in integer coordinates local to the wrist.
#ifdef PE_EMBED_ASSETS
static SVECTOR _gAya10300FirstPairHand0ModelVerts[23] = {
#include "assets/aya_10300_model_05734_verts.inc"
};
#else
static SVECTOR _gAya10300FirstPairHand0ModelVerts[23];
#endif
PE_ASSET_BIND("aya_10300_model_05734_verts", _gAya10300FirstPairHand0ModelVerts);

/// Writable first-pair hand-0 lighting normals with twelve fractional bits.
#ifdef PE_EMBED_ASSETS
static SVECTOR _gAya10300FirstPairHand0ModelNormals[23] = {
#include "assets/aya_10300_model_05734_normals.inc"
};
#else
static SVECTOR _gAya10300FirstPairHand0ModelNormals[23];
#endif
PE_ASSET_BIND("aya_10300_model_05734_normals", _gAya10300FirstPairHand0ModelNormals);

/// Writable commands for two textured triangles and twenty textured quads, ending in `TMD_STREAM_END`.
#ifdef PE_EMBED_ASSETS
static u32 _gAya10300FirstPairHand0ModelStream[161] = {
#include "assets/aya_10300_model_05734_stream.inc"
};
#else
static u32 _gAya10300FirstPairHand0ModelStream[161];
#endif
PE_ASSET_BIND("aya_10300_model_05734_stream", _gAya10300FirstPairHand0ModelStream);

TmdSource gAya10300FirstPairHand0Model = {
    .handlersResolved    = false,
    .bufferHalfBytes     = (2 * sizeof(POLY_GT3)) + (20 * sizeof(POLY_GT4)),
    .preXformRegionBytes = 0,
    .partCount           = ARRAY_SIZE(_gAya10300FirstPairHand0ModelSkeleton),
    .partVertexCounts    = _gAya10300FirstPairHand0ModelPartVerts,
    .verts               = _gAya10300FirstPairHand0ModelVerts,
    .normals             = _gAya10300FirstPairHand0ModelNormals,
    .skeleton            = _gAya10300FirstPairHand0ModelSkeleton,
    .stream              = _gAya10300FirstPairHand0ModelStream,
};

/// Initial local transform and self-parented root for second-pair hand slot 0.
///
/// Read-only source tables retain their serialized positions in the data section.
#ifdef PE_EMBED_ASSETS
static const TmdBone _gAya10300SecondPairHand0ModelSkeleton[1] SECTION(".data") = {
#include "assets/aya_10200_model_0019C_skeleton.inc"
};
#else
static TmdBone _gAya10300SecondPairHand0ModelSkeleton[1] SECTION(".data");
#endif
PE_ASSET_BIND("aya_10200_model_0019C_skeleton", _gAya10300SecondPairHand0ModelSkeleton);

/// Vertex count of the hand's sole part: 23.
#ifdef PE_EMBED_ASSETS
static const u32 _gAya10300SecondPairHand0ModelPartVerts[ARRAY_SIZE(_gAya10300SecondPairHand0ModelSkeleton)] SECTION(".data") = {
#include "assets/aya_10200_model_0019C_partVerts.inc"
};
#else
static u32 _gAya10300SecondPairHand0ModelPartVerts[1] SECTION(".data");
#endif
PE_ASSET_BIND("aya_10200_model_0019C_partVerts", _gAya10300SecondPairHand0ModelPartVerts);

/// Writable second-pair hand-0 vertices in integer coordinates local to the wrist.
#ifdef PE_EMBED_ASSETS
static SVECTOR _gAya10300SecondPairHand0ModelVerts[23] = {
#include "assets/aya_10200_model_0019C_verts.inc"
};
#else
static SVECTOR _gAya10300SecondPairHand0ModelVerts[23];
#endif
PE_ASSET_BIND("aya_10200_model_0019C_verts", _gAya10300SecondPairHand0ModelVerts);

/// Writable second-pair hand-0 lighting normals with twelve fractional bits and independent indices.
#ifdef PE_EMBED_ASSETS
static SVECTOR _gAya10300SecondPairHand0ModelNormals[23] = {
#include "assets/aya_10200_model_0019C_normals.inc"
};
#else
static SVECTOR _gAya10300SecondPairHand0ModelNormals[23];
#endif
PE_ASSET_BIND("aya_10200_model_0019C_normals", _gAya10300SecondPairHand0ModelNormals);

/// Writable commands for two textured triangles and twenty textured quads, ending in `TMD_STREAM_END`.
///
/// First model creation resolves each command's draw-handler slot in place.
#ifdef PE_EMBED_ASSETS
static u32 _gAya10300SecondPairHand0ModelStream[161] = {
#include "assets/aya_10200_model_0019C_stream.inc"
};
#else
static u32 _gAya10300SecondPairHand0ModelStream[161];
#endif
PE_ASSET_BIND("aya_10200_model_0019C_stream", _gAya10300SecondPairHand0ModelStream);

TmdSource gAya10300SecondPairHand0Model = {
    .handlersResolved    = false,
    .bufferHalfBytes     = (2 * sizeof(POLY_GT3)) + (20 * sizeof(POLY_GT4)),
    .preXformRegionBytes = 0,
    .partCount           = ARRAY_SIZE(_gAya10300SecondPairHand0ModelSkeleton),
    .partVertexCounts    = _gAya10300SecondPairHand0ModelPartVerts,
    .verts               = _gAya10300SecondPairHand0ModelVerts,
    .normals             = _gAya10300SecondPairHand0ModelNormals,
    .skeleton            = _gAya10300SecondPairHand0ModelSkeleton,
    .stream              = _gAya10300SecondPairHand0ModelStream,
};

/// Initial local transform and self-parented root for first-pair hand slot 1.
#ifdef PE_EMBED_ASSETS
static const TmdBone _gAya10300FirstPairHand1ModelSkeleton[1] SECTION(".data") = {
#include "assets/aya_10300_model_05FF4_skeleton.inc"
};
#else
static TmdBone _gAya10300FirstPairHand1ModelSkeleton[1] SECTION(".data");
#endif
PE_ASSET_BIND("aya_10300_model_05FF4_skeleton", _gAya10300FirstPairHand1ModelSkeleton);

/// Vertex count of the hand's sole part: 27.
#ifdef PE_EMBED_ASSETS
static const u32 _gAya10300FirstPairHand1ModelPartVerts[ARRAY_SIZE(_gAya10300FirstPairHand1ModelSkeleton)] SECTION(".data") = {
#include "assets/aya_10300_model_05FF4_partVerts.inc"
};
#else
static u32 _gAya10300FirstPairHand1ModelPartVerts[1] SECTION(".data");
#endif
PE_ASSET_BIND("aya_10300_model_05FF4_partVerts", _gAya10300FirstPairHand1ModelPartVerts);

/// Writable first-pair hand-1 vertices in integer coordinates local to the wrist.
#ifdef PE_EMBED_ASSETS
static SVECTOR _gAya10300FirstPairHand1ModelVerts[27] = {
#include "assets/aya_10300_model_05FF4_verts.inc"
};
#else
static SVECTOR _gAya10300FirstPairHand1ModelVerts[27];
#endif
PE_ASSET_BIND("aya_10300_model_05FF4_verts", _gAya10300FirstPairHand1ModelVerts);

/// Writable first-pair hand-1 lighting normals with twelve fractional bits.
#ifdef PE_EMBED_ASSETS
static SVECTOR _gAya10300FirstPairHand1ModelNormals[27] = {
#include "assets/aya_10300_model_05FF4_normals.inc"
};
#else
static SVECTOR _gAya10300FirstPairHand1ModelNormals[27];
#endif
PE_ASSET_BIND("aya_10300_model_05FF4_normals", _gAya10300FirstPairHand1ModelNormals);

/// Writable commands for two textured triangles and twenty-four textured quads, ending in `TMD_STREAM_END`.
#ifdef PE_EMBED_ASSETS
static u32 _gAya10300FirstPairHand1ModelStream[189] = {
#include "assets/aya_10300_model_05FF4_stream.inc"
};
#else
static u32 _gAya10300FirstPairHand1ModelStream[189];
#endif
PE_ASSET_BIND("aya_10300_model_05FF4_stream", _gAya10300FirstPairHand1ModelStream);

TmdSource gAya10300FirstPairHand1Model = {
    .handlersResolved    = false,
    .bufferHalfBytes     = (2 * sizeof(POLY_GT3)) + (24 * sizeof(POLY_GT4)),
    .preXformRegionBytes = 0,
    .partCount           = ARRAY_SIZE(_gAya10300FirstPairHand1ModelSkeleton),
    .partVertexCounts    = _gAya10300FirstPairHand1ModelPartVerts,
    .verts               = _gAya10300FirstPairHand1ModelVerts,
    .normals             = _gAya10300FirstPairHand1ModelNormals,
    .skeleton            = _gAya10300FirstPairHand1ModelSkeleton,
    .stream              = _gAya10300FirstPairHand1ModelStream,
};

/// Initial local transform and self-parented root for second-pair hand slot 1.
#ifdef PE_EMBED_ASSETS
static const TmdBone _gAya10300SecondPairHand1ModelSkeleton[1] SECTION(".data") = {
#include "assets/aya_10300_model_064A4_skeleton.inc"
};
#else
static TmdBone _gAya10300SecondPairHand1ModelSkeleton[1] SECTION(".data");
#endif
PE_ASSET_BIND("aya_10300_model_064A4_skeleton", _gAya10300SecondPairHand1ModelSkeleton);

/// Vertex count of the hand's sole part: 23.
#ifdef PE_EMBED_ASSETS
static const u32 _gAya10300SecondPairHand1ModelPartVerts[ARRAY_SIZE(_gAya10300SecondPairHand1ModelSkeleton)] SECTION(".data") = {
#include "assets/aya_10300_model_064A4_partVerts.inc"
};
#else
static u32 _gAya10300SecondPairHand1ModelPartVerts[1] SECTION(".data");
#endif
PE_ASSET_BIND("aya_10300_model_064A4_partVerts", _gAya10300SecondPairHand1ModelPartVerts);

/// Writable second-pair hand-1 vertices in integer coordinates local to the wrist.
#ifdef PE_EMBED_ASSETS
static SVECTOR _gAya10300SecondPairHand1ModelVerts[23] = {
#include "assets/aya_10300_model_064A4_verts.inc"
};
#else
static SVECTOR _gAya10300SecondPairHand1ModelVerts[23];
#endif
PE_ASSET_BIND("aya_10300_model_064A4_verts", _gAya10300SecondPairHand1ModelVerts);

/// Writable second-pair hand-1 lighting normals with twelve fractional bits.
#ifdef PE_EMBED_ASSETS
static SVECTOR _gAya10300SecondPairHand1ModelNormals[23] = {
#include "assets/aya_10300_model_064A4_normals.inc"
};
#else
static SVECTOR _gAya10300SecondPairHand1ModelNormals[23];
#endif
PE_ASSET_BIND("aya_10300_model_064A4_normals", _gAya10300SecondPairHand1ModelNormals);

/// Writable commands for two textured triangles and twenty textured quads, ending in `TMD_STREAM_END`.
#ifdef PE_EMBED_ASSETS
static u32 _gAya10300SecondPairHand1ModelStream[161] = {
#include "assets/aya_10300_model_064A4_stream.inc"
};
#else
static u32 _gAya10300SecondPairHand1ModelStream[161];
#endif
PE_ASSET_BIND("aya_10300_model_064A4_stream", _gAya10300SecondPairHand1ModelStream);

TmdSource gAya10300SecondPairHand1Model = {
    .handlersResolved    = false,
    .bufferHalfBytes     = (2 * sizeof(POLY_GT3)) + (20 * sizeof(POLY_GT4)),
    .preXformRegionBytes = 0,
    .partCount           = ARRAY_SIZE(_gAya10300SecondPairHand1ModelSkeleton),
    .partVertexCounts    = _gAya10300SecondPairHand1ModelPartVerts,
    .verts               = _gAya10300SecondPairHand1ModelVerts,
    .normals             = _gAya10300SecondPairHand1ModelNormals,
    .skeleton            = _gAya10300SecondPairHand1ModelSkeleton,
    .stream              = _gAya10300SecondPairHand1ModelStream,
};

#ifdef PE_EMBED_ASSETS
static u_long _gAya10300Image0674C[] = {
#include "assets/aya_10300_image_0674C.inc"
};
#else
static u_long _gAya10300Image0674C[200];
#endif
PE_ASSET_BIND("aya_10300_image_0674C", _gAya10300Image0674C);
/// Open eyes: one copy and an upload terminator; playback rewrites the destination.
static GpuImageUpload _gAya10300EyesOpenUploads[2] = {
    { GPU_IMAGE_UPLOAD_COPY, 0, { 0, 0, AYA_10300_EYES_FRAME_WIDTH_WORDS, AYA_10300_EYES_FRAME_HEIGHT_ROWS }, _gAya10300Image0674C },
    { GPU_IMAGE_UPLOAD_END },
};

#ifdef PE_EMBED_ASSETS
static u_long _gAya10300Image06A8C[] = {
#include "assets/aya_10300_image_06A8C.inc"
};
#else
static u_long _gAya10300Image06A8C[200];
#endif
PE_ASSET_BIND("aya_10300_image_06A8C", _gAya10300Image06A8C);
/// Half-closed eyes: one copy and an upload terminator; playback rewrites the destination.
static GpuImageUpload _gAya10300EyesHalfClosedUploads[2] = {
    { GPU_IMAGE_UPLOAD_COPY, 0, { 0, 0, AYA_10300_EYES_FRAME_WIDTH_WORDS, AYA_10300_EYES_FRAME_HEIGHT_ROWS }, _gAya10300Image06A8C },
    { GPU_IMAGE_UPLOAD_END },
};

#ifdef PE_EMBED_ASSETS
static u_long _gAya10300Image06DCC[] = {
#include "assets/aya_10300_image_06DCC.inc"
};
#else
static u_long _gAya10300Image06DCC[200];
#endif
PE_ASSET_BIND("aya_10300_image_06DCC", _gAya10300Image06DCC);
/// Closed eyes: one copy and an upload terminator; playback rewrites the destination.
static GpuImageUpload _gAya10300EyesClosedUploads[2] = {
    { GPU_IMAGE_UPLOAD_COPY, 0, { 0, 0, AYA_10300_EYES_FRAME_WIDTH_WORDS, AYA_10300_EYES_FRAME_HEIGHT_ROWS }, _gAya10300Image06DCC },
    { GPU_IMAGE_UPLOAD_END },
};

#ifdef PE_EMBED_ASSETS
static u_long _gAya10300Image0710C[] = {
#include "assets/aya_10300_image_0710C.inc"
};
#else
static u_long _gAya10300Image0710C[140];
#endif
PE_ASSET_BIND("aya_10300_image_0710C", _gAya10300Image0710C);
/// Resting mouth: one copy and an upload terminator; playback rewrites the destination.
static GpuImageUpload _gAya10300MouthRestUploads[2] = {
    { GPU_IMAGE_UPLOAD_COPY, 0, { 0, 0, AYA_10300_MOUTH_FRAME_WIDTH_WORDS, AYA_10300_MOUTH_FRAME_HEIGHT_ROWS }, _gAya10300Image0710C },
    { GPU_IMAGE_UPLOAD_END },
};

#ifdef PE_EMBED_ASSETS
static u_long _gAya10300Image0735C[] = {
#include "assets/aya_10300_image_0735C.inc"
};
#else
static u_long _gAya10300Image0735C[140];
#endif
PE_ASSET_BIND("aya_10300_image_0735C", _gAya10300Image0735C);
/// Open mouth: one copy and an upload terminator; playback rewrites the destination.
static GpuImageUpload _gAya10300MouthOpenUploads[2] = {
    { GPU_IMAGE_UPLOAD_COPY, 0, { 0, 0, AYA_10300_MOUTH_FRAME_WIDTH_WORDS, AYA_10300_MOUTH_FRAME_HEIGHT_ROWS }, _gAya10300Image0735C },
    { GPU_IMAGE_UPLOAD_END },
};

GpuImageUpload* const gAya10300EyesRestSequence[2] SECTION(".data")    = { _gAya10300EyesOpenUploads, NULL };
GpuImageUpload* const gAya10300EyesClosingSequence[4] SECTION(".data") = { _gAya10300EyesOpenUploads, _gAya10300EyesHalfClosedUploads, _gAya10300EyesClosedUploads, NULL };
GpuImageUpload* const gAya10300EyesOpeningSequence[4] SECTION(".data") = { _gAya10300EyesClosedUploads, _gAya10300EyesHalfClosedUploads, _gAya10300EyesOpenUploads, NULL };
GpuImageUpload* const gAya10300EyesBlinkSequence[6] SECTION(".data")   = {
    _gAya10300EyesOpenUploads,
    _gAya10300EyesHalfClosedUploads,
    _gAya10300EyesClosedUploads,
    _gAya10300EyesHalfClosedUploads,
    _gAya10300EyesOpenUploads,
    NULL,
};
GpuImageUpload* const gAya10300MouthRestSequence[2] SECTION(".data") = { _gAya10300MouthRestUploads, NULL };
GpuImageUpload* const gAya10300MouthOpenSequence[2] SECTION(".data") = { _gAya10300MouthOpenUploads, NULL };
