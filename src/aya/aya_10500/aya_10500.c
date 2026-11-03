#include "aya/aya.h"
#include "port/asset_bind.h"

#include <psyz.h>
#include <libgpu.h>

#include "common.h"

#include "gameplay/gpu_image_upload.h"

/// Facial-frame dimensions, in 16-bit VRAM words and rows.
enum {
    AYA_10500_EYES_FRAME_WIDTH_WORDS  = 25,
    AYA_10500_EYES_FRAME_HEIGHT_ROWS  = 16,
    AYA_10500_MOUTH_FRAME_WIDTH_WORDS = 14,
    AYA_10500_MOUTH_FRAME_HEIGHT_ROWS = 20,
};

/// Initial local transform and self-parented root for first-pair hand slot 0.
///
/// Read-only source tables retain their serialized positions in the data section.
#ifdef PE_EMBED_ASSETS
static const TmdBone _gAya10500FirstPairHand0ModelSkeleton[1] SECTION(".data") = {
#include "assets/aya_10200_model_0019C_skeleton.inc"
};
#else
static TmdBone _gAya10500FirstPairHand0ModelSkeleton[1] SECTION(".data");
#endif
PE_ASSET_BIND("aya_10200_model_0019C_skeleton", _gAya10500FirstPairHand0ModelSkeleton);

/// Vertex count of the hand's sole part: 23.
#ifdef PE_EMBED_ASSETS
static const u32 _gAya10500FirstPairHand0ModelPartVerts[ARRAY_SIZE(_gAya10500FirstPairHand0ModelSkeleton)] SECTION(".data") = {
#include "assets/aya_10200_model_0019C_partVerts.inc"
};
#else
static u32 _gAya10500FirstPairHand0ModelPartVerts[1] SECTION(".data");
#endif
PE_ASSET_BIND("aya_10200_model_0019C_partVerts", _gAya10500FirstPairHand0ModelPartVerts);

/// Writable first-pair hand-0 vertices in integer coordinates local to the wrist.
#ifdef PE_EMBED_ASSETS
static SVECTOR _gAya10500FirstPairHand0ModelVerts[23] = {
#include "assets/aya_10200_model_0019C_verts.inc"
};
#else
static SVECTOR _gAya10500FirstPairHand0ModelVerts[23];
#endif
PE_ASSET_BIND("aya_10200_model_0019C_verts", _gAya10500FirstPairHand0ModelVerts);

/// Writable first-pair hand-0 lighting normals with twelve fractional bits and independent indices.
#ifdef PE_EMBED_ASSETS
static SVECTOR _gAya10500FirstPairHand0ModelNormals[23] = {
#include "assets/aya_10200_model_0019C_normals.inc"
};
#else
static SVECTOR _gAya10500FirstPairHand0ModelNormals[23];
#endif
PE_ASSET_BIND("aya_10200_model_0019C_normals", _gAya10500FirstPairHand0ModelNormals);

/// Writable commands for two textured triangles and twenty textured quads, ending in `TMD_STREAM_END`.
///
/// First model creation resolves each command's draw-handler slot in place.
#ifdef PE_EMBED_ASSETS
static u32 _gAya10500FirstPairHand0ModelStream[161] = {
#include "assets/aya_10200_model_0019C_stream.inc"
};
#else
static u32 _gAya10500FirstPairHand0ModelStream[161];
#endif
PE_ASSET_BIND("aya_10200_model_0019C_stream", _gAya10500FirstPairHand0ModelStream);

TmdSource gAya10500FirstPairHand0Model = {
    .handlersResolved    = false,
    .bufferHalfBytes     = (2 * sizeof(POLY_GT3)) + (20 * sizeof(POLY_GT4)),
    .preXformRegionBytes = 0,
    .partCount           = ARRAY_SIZE(_gAya10500FirstPairHand0ModelSkeleton),
    .partVertexCounts    = _gAya10500FirstPairHand0ModelPartVerts,
    .verts               = _gAya10500FirstPairHand0ModelVerts,
    .normals             = _gAya10500FirstPairHand0ModelNormals,
    .skeleton            = _gAya10500FirstPairHand0ModelSkeleton,
    .stream              = _gAya10500FirstPairHand0ModelStream,
};

/// Initial local transform and self-parented root for second-pair hand slot 0.
///
/// Read-only source tables retain their serialized positions in the data section.
#ifdef PE_EMBED_ASSETS
static const TmdBone _gAya10500SecondPairHand0ModelSkeleton[1] SECTION(".data") = {
#include "assets/aya_10200_model_0019C_skeleton.inc"
};
#else
static TmdBone _gAya10500SecondPairHand0ModelSkeleton[1] SECTION(".data");
#endif
PE_ASSET_BIND("aya_10200_model_0019C_skeleton", _gAya10500SecondPairHand0ModelSkeleton);

/// Vertex count of the hand's sole part: 23.
#ifdef PE_EMBED_ASSETS
static const u32 _gAya10500SecondPairHand0ModelPartVerts[ARRAY_SIZE(_gAya10500SecondPairHand0ModelSkeleton)] SECTION(".data") = {
#include "assets/aya_10200_model_0019C_partVerts.inc"
};
#else
static u32 _gAya10500SecondPairHand0ModelPartVerts[1] SECTION(".data");
#endif
PE_ASSET_BIND("aya_10200_model_0019C_partVerts", _gAya10500SecondPairHand0ModelPartVerts);

/// Writable second-pair hand-0 vertices in integer coordinates local to the wrist.
#ifdef PE_EMBED_ASSETS
static SVECTOR _gAya10500SecondPairHand0ModelVerts[23] = {
#include "assets/aya_10200_model_0019C_verts.inc"
};
#else
static SVECTOR _gAya10500SecondPairHand0ModelVerts[23];
#endif
PE_ASSET_BIND("aya_10200_model_0019C_verts", _gAya10500SecondPairHand0ModelVerts);

/// Writable second-pair hand-0 lighting normals with twelve fractional bits and independent indices.
#ifdef PE_EMBED_ASSETS
static SVECTOR _gAya10500SecondPairHand0ModelNormals[23] = {
#include "assets/aya_10200_model_0019C_normals.inc"
};
#else
static SVECTOR _gAya10500SecondPairHand0ModelNormals[23];
#endif
PE_ASSET_BIND("aya_10200_model_0019C_normals", _gAya10500SecondPairHand0ModelNormals);

/// Writable commands for two textured triangles and twenty textured quads, ending in `TMD_STREAM_END`.
///
/// First model creation resolves each command's draw-handler slot in place.
#ifdef PE_EMBED_ASSETS
static u32 _gAya10500SecondPairHand0ModelStream[161] = {
#include "assets/aya_10200_model_0019C_stream.inc"
};
#else
static u32 _gAya10500SecondPairHand0ModelStream[161];
#endif
PE_ASSET_BIND("aya_10200_model_0019C_stream", _gAya10500SecondPairHand0ModelStream);

TmdSource gAya10500SecondPairHand0Model = {
    .handlersResolved    = false,
    .bufferHalfBytes     = (2 * sizeof(POLY_GT3)) + (20 * sizeof(POLY_GT4)),
    .preXformRegionBytes = 0,
    .partCount           = ARRAY_SIZE(_gAya10500SecondPairHand0ModelSkeleton),
    .partVertexCounts    = _gAya10500SecondPairHand0ModelPartVerts,
    .verts               = _gAya10500SecondPairHand0ModelVerts,
    .normals             = _gAya10500SecondPairHand0ModelNormals,
    .skeleton            = _gAya10500SecondPairHand0ModelSkeleton,
    .stream              = _gAya10500SecondPairHand0ModelStream,
};

/// Initial local transform and self-parented root for first-pair hand slot 1.
///
/// Read-only source tables retain their serialized positions in the data section.
#ifdef PE_EMBED_ASSETS
static const TmdBone _gAya10500FirstPairHand1ModelSkeleton[1] SECTION(".data") = {
#include "assets/aya_10200_model_00A5C_skeleton.inc"
};
#else
static TmdBone _gAya10500FirstPairHand1ModelSkeleton[1] SECTION(".data");
#endif
PE_ASSET_BIND("aya_10200_model_00A5C_skeleton", _gAya10500FirstPairHand1ModelSkeleton);

/// Vertex count of the hand's sole part: 27.
#ifdef PE_EMBED_ASSETS
static const u32 _gAya10500FirstPairHand1ModelPartVerts[ARRAY_SIZE(_gAya10500FirstPairHand1ModelSkeleton)] SECTION(".data") = {
#include "assets/aya_10200_model_00A5C_partVerts.inc"
};
#else
static u32 _gAya10500FirstPairHand1ModelPartVerts[1] SECTION(".data");
#endif
PE_ASSET_BIND("aya_10200_model_00A5C_partVerts", _gAya10500FirstPairHand1ModelPartVerts);

/// Writable first-pair hand-1 vertices in integer coordinates local to the wrist.
#ifdef PE_EMBED_ASSETS
static SVECTOR _gAya10500FirstPairHand1ModelVerts[27] = {
#include "assets/aya_10200_model_00A5C_verts.inc"
};
#else
static SVECTOR _gAya10500FirstPairHand1ModelVerts[27];
#endif
PE_ASSET_BIND("aya_10200_model_00A5C_verts", _gAya10500FirstPairHand1ModelVerts);

/// Writable part-local lighting normals with twelve fractional bits and independent indices.
#ifdef PE_EMBED_ASSETS
static SVECTOR _gAya10500FirstPairHand1ModelNormals[27] = {
#include "assets/aya_10200_model_00A5C_normals.inc"
};
#else
static SVECTOR _gAya10500FirstPairHand1ModelNormals[27];
#endif
PE_ASSET_BIND("aya_10200_model_00A5C_normals", _gAya10500FirstPairHand1ModelNormals);

/// Writable commands for two textured triangles and 24 textured quads, ending in `TMD_STREAM_END`.
///
/// First model creation resolves each command's draw-handler slot in place.
#ifdef PE_EMBED_ASSETS
static u32 _gAya10500FirstPairHand1ModelStream[189] = {
#include "assets/aya_10200_model_00A5C_stream.inc"
};
#else
static u32 _gAya10500FirstPairHand1ModelStream[189];
#endif
PE_ASSET_BIND("aya_10200_model_00A5C_stream", _gAya10500FirstPairHand1ModelStream);

TmdSource gAya10500FirstPairHand1Model = {
    .handlersResolved    = false,
    .bufferHalfBytes     = (2 * sizeof(POLY_GT3)) + (24 * sizeof(POLY_GT4)),
    .preXformRegionBytes = 0,
    .partCount           = ARRAY_SIZE(_gAya10500FirstPairHand1ModelSkeleton),
    .partVertexCounts    = _gAya10500FirstPairHand1ModelPartVerts,
    .verts               = _gAya10500FirstPairHand1ModelVerts,
    .normals             = _gAya10500FirstPairHand1ModelNormals,
    .skeleton            = _gAya10500FirstPairHand1ModelSkeleton,
    .stream              = _gAya10500FirstPairHand1ModelStream,
};

/// Initial local transform and self-parented root for second-pair hand slot 1.
///
/// Read-only source tables retain their serialized positions in the data section.
#ifdef PE_EMBED_ASSETS
static const TmdBone _gAya10500SecondPairHand1ModelSkeleton[1] SECTION(".data") = {
#include "assets/aya_10200_model_00F0C_skeleton.inc"
};
#else
static TmdBone _gAya10500SecondPairHand1ModelSkeleton[1] SECTION(".data");
#endif
PE_ASSET_BIND("aya_10200_model_00F0C_skeleton", _gAya10500SecondPairHand1ModelSkeleton);

/// Vertex count of the hand's sole part: 23.
#ifdef PE_EMBED_ASSETS
static const u32 _gAya10500SecondPairHand1ModelPartVerts[ARRAY_SIZE(_gAya10500SecondPairHand1ModelSkeleton)] SECTION(".data") = {
#include "assets/aya_10200_model_00F0C_partVerts.inc"
};
#else
static u32 _gAya10500SecondPairHand1ModelPartVerts[1] SECTION(".data");
#endif
PE_ASSET_BIND("aya_10200_model_00F0C_partVerts", _gAya10500SecondPairHand1ModelPartVerts);

/// Writable second-pair hand-1 vertices in integer coordinates local to the wrist.
#ifdef PE_EMBED_ASSETS
static SVECTOR _gAya10500SecondPairHand1ModelVerts[23] = {
#include "assets/aya_10200_model_00F0C_verts.inc"
};
#else
static SVECTOR _gAya10500SecondPairHand1ModelVerts[23];
#endif
PE_ASSET_BIND("aya_10200_model_00F0C_verts", _gAya10500SecondPairHand1ModelVerts);

/// Writable part-local lighting normals with twelve fractional bits and independent indices.
#ifdef PE_EMBED_ASSETS
static SVECTOR _gAya10500SecondPairHand1ModelNormals[23] = {
#include "assets/aya_10200_model_00F0C_normals.inc"
};
#else
static SVECTOR _gAya10500SecondPairHand1ModelNormals[23];
#endif
PE_ASSET_BIND("aya_10200_model_00F0C_normals", _gAya10500SecondPairHand1ModelNormals);

/// Writable commands for two textured triangles and twenty textured quads, ending in `TMD_STREAM_END`.
///
/// First model creation resolves each command's draw-handler slot in place.
#ifdef PE_EMBED_ASSETS
static u32 _gAya10500SecondPairHand1ModelStream[161] = {
#include "assets/aya_10200_model_00F0C_stream.inc"
};
#else
static u32 _gAya10500SecondPairHand1ModelStream[161];
#endif
PE_ASSET_BIND("aya_10200_model_00F0C_stream", _gAya10500SecondPairHand1ModelStream);

TmdSource gAya10500SecondPairHand1Model = {
    .handlersResolved    = false,
    .bufferHalfBytes     = (2 * sizeof(POLY_GT3)) + (20 * sizeof(POLY_GT4)),
    .preXformRegionBytes = 0,
    .partCount           = ARRAY_SIZE(_gAya10500SecondPairHand1ModelSkeleton),
    .partVertexCounts    = _gAya10500SecondPairHand1ModelPartVerts,
    .verts               = _gAya10500SecondPairHand1ModelVerts,
    .normals             = _gAya10500SecondPairHand1ModelNormals,
    .skeleton            = _gAya10500SecondPairHand1ModelSkeleton,
    .stream              = _gAya10500SecondPairHand1ModelStream,
};

/// Initial body-part transforms and hierarchy, with part 0 as the self-parented root.
///
/// Read-only source tables retain their serialized positions in the data section.
#ifdef PE_EMBED_ASSETS
static const TmdBone _gAya10500BodyModelSkeleton[19] SECTION(".data") = {
#include "assets/aya_10500_model_02BB8_skeleton.inc"
};
#else
static TmdBone _gAya10500BodyModelSkeleton[19] SECTION(".data");
#endif
PE_ASSET_BIND("aya_10500_model_02BB8_skeleton", _gAya10500BodyModelSkeleton);

/// Part-local vertex counts in skeleton order, totaling 358 vertices.
#ifdef PE_EMBED_ASSETS
static const u32 _gAya10500BodyModelPartVerts[ARRAY_SIZE(_gAya10500BodyModelSkeleton)] SECTION(".data") = {
#include "assets/aya_10500_model_02BB8_partVerts.inc"
};
#else
static u32 _gAya10500BodyModelPartVerts[19] SECTION(".data");
#endif
PE_ASSET_BIND("aya_10500_model_02BB8_partVerts", _gAya10500BodyModelPartVerts);

/// Writable body vertices in integer coordinates local to each model part.
#ifdef PE_EMBED_ASSETS
static SVECTOR _gAya10500BodyModelVerts[358] = {
#include "assets/aya_10500_model_02BB8_verts.inc"
};
#else
static SVECTOR _gAya10500BodyModelVerts[358];
#endif
PE_ASSET_BIND("aya_10500_model_02BB8_verts", _gAya10500BodyModelVerts);

/// Writable part-local lighting normals with twelve fractional bits and independent stream indices.
#ifdef PE_EMBED_ASSETS
static SVECTOR _gAya10500BodyModelNormals[379] = {
#include "assets/aya_10500_model_02BB8_normals.inc"
};
#else
static SVECTOR _gAya10500BodyModelNormals[379];
#endif
PE_ASSET_BIND("aya_10500_model_02BB8_normals", _gAya10500BodyModelNormals);

/// Writable commands for 290 textured triangles and 211 textured quads, ending in `TMD_STREAM_END`.
///
/// Handler resolution rewrites the command slots on first model creation.
/// The final group draws 82 triangles and 50 quads from the transformed cache.
#ifdef PE_EMBED_ASSETS
static u32 _gAya10500BodyModelStream[4080] = {
#include "assets/aya_10500_model_02BB8_stream.inc"
};
#else
static u32 _gAya10500BodyModelStream[4080];
#endif
PE_ASSET_BIND("aya_10500_model_02BB8_stream", _gAya10500BodyModelStream);

TmdSource gAya10500BodyModel = {
    .handlersResolved    = false,
    .bufferHalfBytes     = (290 * sizeof(POLY_GT3)) + (211 * sizeof(POLY_GT4)),
    .preXformRegionBytes = (82 * sizeof(POLY_GT3)) + (50 * sizeof(POLY_GT4)),
    .partCount           = ARRAY_SIZE(_gAya10500BodyModelSkeleton),
    .partVertexCounts    = _gAya10500BodyModelPartVerts,
    .verts               = _gAya10500BodyModelVerts,
    .normals             = _gAya10500BodyModelNormals,
    .skeleton            = _gAya10500BodyModelSkeleton,
    .stream              = _gAya10500BodyModelStream,
};

#ifdef PE_EMBED_ASSETS
static u32 _gAya10500Aya10200Image06AC4[] = {
#include "assets/aya_10200_image_06AC4.inc"
};
#else
static u32 _gAya10500Aya10200Image06AC4[200];
#endif
PE_ASSET_BIND("aya_10200_image_06AC4", _gAya10500Aya10200Image06AC4);
/// One open-eyes upload and its terminator; playback supplies the texture-relative destination.
///
/// Records remain writable, and their packed 8-bit pixels stay loaded until
/// the queued GPU transfer completes.
static GpuImageUpload _gAya10500EyesOpenUploads[2] = {
    { GPU_IMAGE_UPLOAD_COPY, 0, { 0, 0, AYA_10500_EYES_FRAME_WIDTH_WORDS, AYA_10500_EYES_FRAME_HEIGHT_ROWS }, _gAya10500Aya10200Image06AC4 },
    { GPU_IMAGE_UPLOAD_END },
};

#ifdef PE_EMBED_ASSETS
static u32 _gAya10500Aya10200Image06E04[] = {
#include "assets/aya_10200_image_06E04.inc"
};
#else
static u32 _gAya10500Aya10200Image06E04[200];
#endif
PE_ASSET_BIND("aya_10200_image_06E04", _gAya10500Aya10200Image06E04);
/// One half-closed-eyes upload and its terminator, with writable destination and borrowed pixels.
static GpuImageUpload _gAya10500EyesHalfClosedUploads[2] = {
    { GPU_IMAGE_UPLOAD_COPY, 0, { 0, 0, AYA_10500_EYES_FRAME_WIDTH_WORDS, AYA_10500_EYES_FRAME_HEIGHT_ROWS }, _gAya10500Aya10200Image06E04 },
    { GPU_IMAGE_UPLOAD_END },
};

#ifdef PE_EMBED_ASSETS
static u32 _gAya10500Aya10200Image07144[] = {
#include "assets/aya_10200_image_07144.inc"
};
#else
static u32 _gAya10500Aya10200Image07144[200];
#endif
PE_ASSET_BIND("aya_10200_image_07144", _gAya10500Aya10200Image07144);
/// One closed-eyes upload and its terminator, with writable destination and borrowed pixels.
static GpuImageUpload _gAya10500EyesClosedUploads[2] = {
    { GPU_IMAGE_UPLOAD_COPY, 0, { 0, 0, AYA_10500_EYES_FRAME_WIDTH_WORDS, AYA_10500_EYES_FRAME_HEIGHT_ROWS }, _gAya10500Aya10200Image07144 },
    { GPU_IMAGE_UPLOAD_END },
};

/// Resting mouth pixels: packed 8-bit palette indices, four texels per u_long.
#ifdef PE_EMBED_ASSETS
static u32 _gAya10500MouthRestPixels[AYA_10500_MOUTH_FRAME_WIDTH_WORDS * AYA_10500_MOUTH_FRAME_HEIGHT_ROWS / 2] = {
#include "assets/aya_10200_image_07484.inc"
};
#else
static u32 _gAya10500MouthRestPixels[140];
#endif
PE_ASSET_BIND("aya_10200_image_07484", _gAya10500MouthRestPixels);
/// One resting-mouth upload and its terminator, with writable destination and borrowed pixels.
static GpuImageUpload _gAya10500MouthRestUploads[2] = {
    { GPU_IMAGE_UPLOAD_COPY, 0, { 0, 0, AYA_10500_MOUTH_FRAME_WIDTH_WORDS, AYA_10500_MOUTH_FRAME_HEIGHT_ROWS }, _gAya10500MouthRestPixels },
    { GPU_IMAGE_UPLOAD_END },
};

/// Alternate mouth selector's packed 8-bit pixels, identical here to the resting mouth.
#ifdef PE_EMBED_ASSETS
static u32 _gAya10500MouthAlternatePixels[AYA_10500_MOUTH_FRAME_WIDTH_WORDS * AYA_10500_MOUTH_FRAME_HEIGHT_ROWS / 2] = {
#include "assets/aya_10200_image_07484.inc"
};
#else
static u32 _gAya10500MouthAlternatePixels[140];
#endif
PE_ASSET_BIND("aya_10200_image_07484", _gAya10500MouthAlternatePixels);
/// One alternate-mouth upload and its terminator, with writable destination and borrowed pixels.
static GpuImageUpload _gAya10500MouthAlternateUploads[2] = {
    { GPU_IMAGE_UPLOAD_COPY, 0, { 0, 0, AYA_10500_MOUTH_FRAME_WIDTH_WORDS, AYA_10500_MOUTH_FRAME_HEIGHT_ROWS }, _gAya10500MouthAlternatePixels },
    { GPU_IMAGE_UPLOAD_END },
};

GpuImageUpload* const gAya10500EyesRestSequence[2] SECTION(".data")    = { _gAya10500EyesOpenUploads, NULL };
GpuImageUpload* const gAya10500EyesClosingSequence[4] SECTION(".data") = { _gAya10500EyesOpenUploads, _gAya10500EyesHalfClosedUploads, _gAya10500EyesClosedUploads, NULL };
GpuImageUpload* const gAya10500EyesOpeningSequence[4] SECTION(".data") = { _gAya10500EyesClosedUploads, _gAya10500EyesHalfClosedUploads, _gAya10500EyesOpenUploads, NULL };
GpuImageUpload* const gAya10500EyesBlinkSequence[6] SECTION(".data")   = {
    _gAya10500EyesOpenUploads,
    _gAya10500EyesHalfClosedUploads,
    _gAya10500EyesClosedUploads,
    _gAya10500EyesHalfClosedUploads,
    _gAya10500EyesOpenUploads,
    NULL,
};
GpuImageUpload* const gAya10500MouthRestSequence[2] SECTION(".data")      = { _gAya10500MouthRestUploads, NULL };
GpuImageUpload* const gAya10500MouthAlternateSequence[2] SECTION(".data") = { _gAya10500MouthAlternateUploads, NULL };
