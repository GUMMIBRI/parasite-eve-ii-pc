#include "aya/aya.h"
#include "port/asset_bind.h"

#include <psyz.h>
#include <libgpu.h>

#include "common.h"

#include "gameplay/gpu_image_upload.h"

/// Facial-frame dimensions in 16-bit VRAM words and rows.
enum {
    AYA_10400_EYES_FRAME_WIDTH_WORDS  = 25,
    AYA_10400_EYES_FRAME_HEIGHT_ROWS  = 16,
    AYA_10400_MOUTH_FRAME_WIDTH_WORDS = 14,
    AYA_10400_MOUTH_FRAME_HEIGHT_ROWS = 20,
};

/// Nineteen initial local transforms and parent indices copied into each player body.
///
/// Read-only pose and count tables retain their serialized positions in .data.
#ifdef PE_EMBED_ASSETS
static const TmdBone _gAya10400BodyModelSkeleton[19] SECTION(".data") = {
#include "assets/aya_10400_model_01A48_skeleton.inc"
};
#else
static TmdBone _gAya10400BodyModelSkeleton[19] SECTION(".data");
#endif
PE_ASSET_BIND("aya_10400_model_01A48_skeleton", _gAya10400BodyModelSkeleton);

/// Vertex counts for consecutive part-local groups in skeleton order, totaling 362.
#ifdef PE_EMBED_ASSETS
static const u32 _gAya10400BodyModelPartVerts[ARRAY_SIZE(_gAya10400BodyModelSkeleton)] SECTION(".data") = {
#include "assets/aya_10400_model_01A48_partVerts.inc"
};
#else
static u32 _gAya10400BodyModelPartVerts[19] SECTION(".data");
#endif
PE_ASSET_BIND("aya_10400_model_01A48_partVerts", _gAya10400BodyModelPartVerts);

/// Writable body vertices in integer coordinates local to their skeletal parts.
#ifdef PE_EMBED_ASSETS
static SVECTOR _gAya10400BodyModelVerts[362] = {
#include "assets/aya_10400_model_01A48_verts.inc"
};
#else
static SVECTOR _gAya10400BodyModelVerts[362];
#endif
PE_ASSET_BIND("aya_10400_model_01A48_verts", _gAya10400BodyModelVerts);

/// Writable body lighting normals with twelve fractional bits, indexed independently of vertices.
#ifdef PE_EMBED_ASSETS
static SVECTOR _gAya10400BodyModelNormals[383] = {
#include "assets/aya_10400_model_01A48_normals.inc"
};
#else
static SVECTOR _gAya10400BodyModelNormals[383];
#endif
PE_ASSET_BIND("aya_10400_model_01A48_normals", _gAya10400BodyModelNormals);

/// Writable commands for nineteen skeletal groups and a final pre-transformed group.
///
/// Handler slots resolve in place; `TMD_STREAM_END` is the last word.
/// Projection commands populate the first region of each primitive-buffer half.
#ifdef PE_EMBED_ASSETS
static u32 _gAya10400BodyModelStream[4017] = {
#include "assets/aya_10400_model_01A48_stream.inc"
};
#else
static u32 _gAya10400BodyModelStream[4017];
#endif
PE_ASSET_BIND("aya_10400_model_01A48_stream", _gAya10400BodyModelStream);

TmdSource gAya10400BodyModel = {
    .handlersResolved    = false,
    .bufferHalfBytes     = (260 * sizeof(POLY_GT3)) + (230 * sizeof(POLY_GT4)),
    .preXformRegionBytes = (80 * sizeof(POLY_GT3)) + (50 * sizeof(POLY_GT4)),
    .partCount           = ARRAY_SIZE(_gAya10400BodyModelSkeleton),
    .partVertexCounts    = _gAya10400BodyModelPartVerts,
    .verts               = _gAya10400BodyModelVerts,
    .normals             = _gAya10400BodyModelNormals,
    .skeleton            = _gAya10400BodyModelSkeleton,
    .stream              = _gAya10400BodyModelStream,
};

/// Initial local transform and self-parented root for hand slot 0 in either pair.
#ifdef PE_EMBED_ASSETS
static const TmdBone _gAya10400Hand0ModelSkeleton[1] SECTION(".data") = {
#include "assets/aya_10400_model_05AC4_skeleton.inc"
};
#else
static TmdBone _gAya10400Hand0ModelSkeleton[1] SECTION(".data");
#endif
PE_ASSET_BIND("aya_10400_model_05AC4_skeleton", _gAya10400Hand0ModelSkeleton);

/// Vertex count of the shared hand's sole part: 23.
#ifdef PE_EMBED_ASSETS
static const u32 _gAya10400Hand0ModelPartVerts[ARRAY_SIZE(_gAya10400Hand0ModelSkeleton)] SECTION(".data") = {
#include "assets/aya_10400_model_05AC4_partVerts.inc"
};
#else
static u32 _gAya10400Hand0ModelPartVerts[1] SECTION(".data");
#endif
PE_ASSET_BIND("aya_10400_model_05AC4_partVerts", _gAya10400Hand0ModelPartVerts);

/// Writable shared hand-0 vertices in integer coordinates local to the wrist.
#ifdef PE_EMBED_ASSETS
static SVECTOR _gAya10400Hand0ModelVerts[23] = {
#include "assets/aya_10400_model_05AC4_verts.inc"
};
#else
static SVECTOR _gAya10400Hand0ModelVerts[23];
#endif
PE_ASSET_BIND("aya_10400_model_05AC4_verts", _gAya10400Hand0ModelVerts);

/// Writable shared hand-0 lighting normals with twelve fractional bits.
#ifdef PE_EMBED_ASSETS
static SVECTOR _gAya10400Hand0ModelNormals[23] = {
#include "assets/aya_10400_model_05AC4_normals.inc"
};
#else
static SVECTOR _gAya10400Hand0ModelNormals[23];
#endif
PE_ASSET_BIND("aya_10400_model_05AC4_normals", _gAya10400Hand0ModelNormals);

/// Writable commands for four textured triangles and nineteen textured quads, ending in `TMD_STREAM_END`.
#ifdef PE_EMBED_ASSETS
static u32 _gAya10400Hand0ModelStream[166] = {
#include "assets/aya_10400_model_05AC4_stream.inc"
};
#else
static u32 _gAya10400Hand0ModelStream[166];
#endif
PE_ASSET_BIND("aya_10400_model_05AC4_stream", _gAya10400Hand0ModelStream);

TmdSource gAya10400Hand0Model = {
    .handlersResolved    = false,
    .bufferHalfBytes     = (4 * sizeof(POLY_GT3)) + (19 * sizeof(POLY_GT4)),
    .preXformRegionBytes = 0,
    .partCount           = ARRAY_SIZE(_gAya10400Hand0ModelSkeleton),
    .partVertexCounts    = _gAya10400Hand0ModelPartVerts,
    .verts               = _gAya10400Hand0ModelVerts,
    .normals             = _gAya10400Hand0ModelNormals,
    .skeleton            = _gAya10400Hand0ModelSkeleton,
    .stream              = _gAya10400Hand0ModelStream,
};

/// Initial local transform and self-parented root for first-pair hand slot 1.
#ifdef PE_EMBED_ASSETS
static const TmdBone _gAya10400FirstPairHand1ModelSkeleton[1] SECTION(".data") = {
#include "assets/aya_10400_model_05F58_skeleton.inc"
};
#else
static TmdBone _gAya10400FirstPairHand1ModelSkeleton[1] SECTION(".data");
#endif
PE_ASSET_BIND("aya_10400_model_05F58_skeleton", _gAya10400FirstPairHand1ModelSkeleton);

/// Vertex count of the first-pair hand's sole part: 27.
#ifdef PE_EMBED_ASSETS
static const u32 _gAya10400FirstPairHand1ModelPartVerts[ARRAY_SIZE(_gAya10400FirstPairHand1ModelSkeleton)] SECTION(".data") = {
#include "assets/aya_10400_model_05F58_partVerts.inc"
};
#else
static u32 _gAya10400FirstPairHand1ModelPartVerts[1] SECTION(".data");
#endif
PE_ASSET_BIND("aya_10400_model_05F58_partVerts", _gAya10400FirstPairHand1ModelPartVerts);

/// Writable first-pair hand-1 vertices in integer coordinates local to the wrist.
#ifdef PE_EMBED_ASSETS
static SVECTOR _gAya10400FirstPairHand1ModelVerts[27] = {
#include "assets/aya_10400_model_05F58_verts.inc"
};
#else
static SVECTOR _gAya10400FirstPairHand1ModelVerts[27];
#endif
PE_ASSET_BIND("aya_10400_model_05F58_verts", _gAya10400FirstPairHand1ModelVerts);

/// Writable first-pair hand-1 lighting normals with twelve fractional bits.
#ifdef PE_EMBED_ASSETS
static SVECTOR _gAya10400FirstPairHand1ModelNormals[27] = {
#include "assets/aya_10400_model_05F58_normals.inc"
};
#else
static SVECTOR _gAya10400FirstPairHand1ModelNormals[27];
#endif
PE_ASSET_BIND("aya_10400_model_05F58_normals", _gAya10400FirstPairHand1ModelNormals);

/// Writable commands for two textured triangles and twenty-four textured quads, ending in `TMD_STREAM_END`.
#ifdef PE_EMBED_ASSETS
static u32 _gAya10400FirstPairHand1ModelStream[189] = {
#include "assets/aya_10400_model_05F58_stream.inc"
};
#else
static u32 _gAya10400FirstPairHand1ModelStream[189];
#endif
PE_ASSET_BIND("aya_10400_model_05F58_stream", _gAya10400FirstPairHand1ModelStream);

TmdSource gAya10400FirstPairHand1Model = {
    .handlersResolved    = false,
    .bufferHalfBytes     = (2 * sizeof(POLY_GT3)) + (24 * sizeof(POLY_GT4)),
    .preXformRegionBytes = 0,
    .partCount           = ARRAY_SIZE(_gAya10400FirstPairHand1ModelSkeleton),
    .partVertexCounts    = _gAya10400FirstPairHand1ModelPartVerts,
    .verts               = _gAya10400FirstPairHand1ModelVerts,
    .normals             = _gAya10400FirstPairHand1ModelNormals,
    .skeleton            = _gAya10400FirstPairHand1ModelSkeleton,
    .stream              = _gAya10400FirstPairHand1ModelStream,
};

/// Initial local transform and self-parented root for second-pair hand slot 1.
#ifdef PE_EMBED_ASSETS
static const TmdBone _gAya10400SecondPairHand1ModelSkeleton[1] SECTION(".data") = {
#include "assets/aya_10400_model_06408_skeleton.inc"
};
#else
static TmdBone _gAya10400SecondPairHand1ModelSkeleton[1] SECTION(".data");
#endif
PE_ASSET_BIND("aya_10400_model_06408_skeleton", _gAya10400SecondPairHand1ModelSkeleton);

/// Vertex count of the second-pair hand's sole part: 23.
#ifdef PE_EMBED_ASSETS
static const u32 _gAya10400SecondPairHand1ModelPartVerts[ARRAY_SIZE(_gAya10400SecondPairHand1ModelSkeleton)] SECTION(".data") = {
#include "assets/aya_10400_model_06408_partVerts.inc"
};
#else
static u32 _gAya10400SecondPairHand1ModelPartVerts[1] SECTION(".data");
#endif
PE_ASSET_BIND("aya_10400_model_06408_partVerts", _gAya10400SecondPairHand1ModelPartVerts);

/// Writable second-pair hand-1 vertices in integer coordinates local to the wrist.
#ifdef PE_EMBED_ASSETS
static SVECTOR _gAya10400SecondPairHand1ModelVerts[23] = {
#include "assets/aya_10400_model_06408_verts.inc"
};
#else
static SVECTOR _gAya10400SecondPairHand1ModelVerts[23];
#endif
PE_ASSET_BIND("aya_10400_model_06408_verts", _gAya10400SecondPairHand1ModelVerts);

/// Writable second-pair hand-1 lighting normals with twelve fractional bits.
#ifdef PE_EMBED_ASSETS
static SVECTOR _gAya10400SecondPairHand1ModelNormals[23] = {
#include "assets/aya_10400_model_06408_normals.inc"
};
#else
static SVECTOR _gAya10400SecondPairHand1ModelNormals[23];
#endif
PE_ASSET_BIND("aya_10400_model_06408_normals", _gAya10400SecondPairHand1ModelNormals);

/// Writable commands for four textured triangles and nineteen textured quads, ending in `TMD_STREAM_END`.
#ifdef PE_EMBED_ASSETS
static u32 _gAya10400SecondPairHand1ModelStream[166] = {
#include "assets/aya_10400_model_06408_stream.inc"
};
#else
static u32 _gAya10400SecondPairHand1ModelStream[166];
#endif
PE_ASSET_BIND("aya_10400_model_06408_stream", _gAya10400SecondPairHand1ModelStream);

TmdSource gAya10400SecondPairHand1Model = {
    .handlersResolved    = false,
    .bufferHalfBytes     = (4 * sizeof(POLY_GT3)) + (19 * sizeof(POLY_GT4)),
    .preXformRegionBytes = 0,
    .partCount           = ARRAY_SIZE(_gAya10400SecondPairHand1ModelSkeleton),
    .partVertexCounts    = _gAya10400SecondPairHand1ModelPartVerts,
    .verts               = _gAya10400SecondPairHand1ModelVerts,
    .normals             = _gAya10400SecondPairHand1ModelNormals,
    .skeleton            = _gAya10400SecondPairHand1ModelSkeleton,
    .stream              = _gAya10400SecondPairHand1ModelStream,
};

#ifdef PE_EMBED_ASSETS
static u_long _gAya10400Image066C4[] = {
#include "assets/aya_10400_image_066C4.inc"
};
#else
static u_long _gAya10400Image066C4[200];
#endif
PE_ASSET_BIND("aya_10400_image_066C4", _gAya10400Image066C4);
/// One-copy upload list for open eyes: 50x16 8-bit texels.
///
/// Playback supplies the destination at texture U/V (0, 78). Records remain
/// writable; their payload must stay loaded until the GPU transfer completes.
static GpuImageUpload _gAya10400EyesOpenUploads[2] = {
    { GPU_IMAGE_UPLOAD_COPY, 0, { 0, 0, AYA_10400_EYES_FRAME_WIDTH_WORDS, AYA_10400_EYES_FRAME_HEIGHT_ROWS }, _gAya10400Image066C4 },
    { GPU_IMAGE_UPLOAD_END },
};

#ifdef PE_EMBED_ASSETS
static u_long _gAya10400Image06A04[] = {
#include "assets/aya_10400_image_06A04.inc"
};
#else
static u_long _gAya10400Image06A04[200];
#endif
PE_ASSET_BIND("aya_10400_image_06A04", _gAya10400Image06A04);
/// One-copy upload list for half-closed eyes: 50x16 8-bit texels.
///
/// Placement, writable records and payload lifetime follow `_gAya10400EyesOpenUploads`.
static GpuImageUpload _gAya10400EyesHalfClosedUploads[2] = {
    { GPU_IMAGE_UPLOAD_COPY, 0, { 0, 0, AYA_10400_EYES_FRAME_WIDTH_WORDS, AYA_10400_EYES_FRAME_HEIGHT_ROWS }, _gAya10400Image06A04 },
    { GPU_IMAGE_UPLOAD_END },
};

#ifdef PE_EMBED_ASSETS
static u_long _gAya10400Image06D44[] = {
#include "assets/aya_10400_image_06D44.inc"
};
#else
static u_long _gAya10400Image06D44[200];
#endif
PE_ASSET_BIND("aya_10400_image_06D44", _gAya10400Image06D44);
/// One-copy upload list for closed eyes: 50x16 8-bit texels.
///
/// Placement, writable records and payload lifetime follow `_gAya10400EyesOpenUploads`.
static GpuImageUpload _gAya10400EyesClosedUploads[2] = {
    { GPU_IMAGE_UPLOAD_COPY, 0, { 0, 0, AYA_10400_EYES_FRAME_WIDTH_WORDS, AYA_10400_EYES_FRAME_HEIGHT_ROWS }, _gAya10400Image06D44 },
    { GPU_IMAGE_UPLOAD_END },
};

#ifdef PE_EMBED_ASSETS
static u_long _gAya10400Image07084[] = {
#include "assets/aya_10400_image_07084.inc"
};
#else
static u_long _gAya10400Image07084[140];
#endif
PE_ASSET_BIND("aya_10400_image_07084", _gAya10400Image07084);
/// One-copy upload list for the resting, closed mouth: 28x20 8-bit texels.
///
/// Playback supplies the destination at texture U/V (12, 104), with an eight-tick
/// frame cadence. Records remain writable; keep the payload through GPU completion.
static GpuImageUpload _gAya10400MouthClosedUploads[2] = {
    { GPU_IMAGE_UPLOAD_COPY, 0, { 0, 0, AYA_10400_MOUTH_FRAME_WIDTH_WORDS, AYA_10400_MOUTH_FRAME_HEIGHT_ROWS }, _gAya10400Image07084 },
    { GPU_IMAGE_UPLOAD_END },
};

#ifdef PE_EMBED_ASSETS
static u_long _gAya10400Image072D4[] = {
#include "assets/aya_10400_image_072D4.inc"
};
#else
static u_long _gAya10400Image072D4[140];
#endif
PE_ASSET_BIND("aya_10400_image_072D4", _gAya10400Image072D4);
/// One-copy upload list for the open mouth: 28x20 8-bit texels.
///
/// Placement, writable records and payload lifetime follow `_gAya10400MouthClosedUploads`.
static GpuImageUpload _gAya10400MouthOpenUploads[2] = {
    { GPU_IMAGE_UPLOAD_COPY, 0, { 0, 0, AYA_10400_MOUTH_FRAME_WIDTH_WORDS, AYA_10400_MOUTH_FRAME_HEIGHT_ROWS }, _gAya10400Image072D4 },
    { GPU_IMAGE_UPLOAD_END },
};

GpuImageUpload* const gAya10400EyesRestSequence[2] SECTION(".data")    = { _gAya10400EyesOpenUploads, NULL };
GpuImageUpload* const gAya10400EyesClosingSequence[4] SECTION(".data") = { _gAya10400EyesOpenUploads, _gAya10400EyesHalfClosedUploads, _gAya10400EyesClosedUploads, NULL };
GpuImageUpload* const gAya10400EyesOpeningSequence[4] SECTION(".data") = { _gAya10400EyesClosedUploads, _gAya10400EyesHalfClosedUploads, _gAya10400EyesOpenUploads, NULL };
GpuImageUpload* const gAya10400EyesBlinkSequence[6] SECTION(".data")   = {
    _gAya10400EyesOpenUploads,
    _gAya10400EyesHalfClosedUploads,
    _gAya10400EyesClosedUploads,
    _gAya10400EyesHalfClosedUploads,
    _gAya10400EyesOpenUploads,
    NULL,
};
GpuImageUpload* const gAya10400MouthRestSequence[2] SECTION(".data") = { _gAya10400MouthClosedUploads, NULL };
GpuImageUpload* const gAya10400MouthOpenSequence[2] SECTION(".data") = { _gAya10400MouthOpenUploads, NULL };
