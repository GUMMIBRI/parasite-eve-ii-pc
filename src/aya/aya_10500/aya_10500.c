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
static TmdBone _gAya10500FirstPairHand0ModelSkeleton[1] SECTION(".data");
PE_ASSET_BIND("aya_10200_model_0019C_skeleton", _gAya10500FirstPairHand0ModelSkeleton);

/// Vertex count of the hand's sole part: 23.
static u32 _gAya10500FirstPairHand0ModelPartVerts[1] SECTION(".data");
PE_ASSET_BIND("aya_10200_model_0019C_partVerts", _gAya10500FirstPairHand0ModelPartVerts);

/// Writable first-pair hand-0 vertices in integer coordinates local to the wrist.
static SVECTOR _gAya10500FirstPairHand0ModelVerts[23];
PE_ASSET_BIND("aya_10200_model_0019C_verts", _gAya10500FirstPairHand0ModelVerts);

/// Writable first-pair hand-0 lighting normals with twelve fractional bits and independent indices.
static SVECTOR _gAya10500FirstPairHand0ModelNormals[23];
PE_ASSET_BIND("aya_10200_model_0019C_normals", _gAya10500FirstPairHand0ModelNormals);

/// Writable commands for two textured triangles and twenty textured quads, ending in `TMD_STREAM_END`.
///
/// First model creation resolves each command's draw-handler slot in place.
static u32 _gAya10500FirstPairHand0ModelStream[161];
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
static TmdBone _gAya10500SecondPairHand0ModelSkeleton[1] SECTION(".data");
PE_ASSET_BIND("aya_10200_model_0019C_skeleton", _gAya10500SecondPairHand0ModelSkeleton);

/// Vertex count of the hand's sole part: 23.
static u32 _gAya10500SecondPairHand0ModelPartVerts[1] SECTION(".data");
PE_ASSET_BIND("aya_10200_model_0019C_partVerts", _gAya10500SecondPairHand0ModelPartVerts);

/// Writable second-pair hand-0 vertices in integer coordinates local to the wrist.
static SVECTOR _gAya10500SecondPairHand0ModelVerts[23];
PE_ASSET_BIND("aya_10200_model_0019C_verts", _gAya10500SecondPairHand0ModelVerts);

/// Writable second-pair hand-0 lighting normals with twelve fractional bits and independent indices.
static SVECTOR _gAya10500SecondPairHand0ModelNormals[23];
PE_ASSET_BIND("aya_10200_model_0019C_normals", _gAya10500SecondPairHand0ModelNormals);

/// Writable commands for two textured triangles and twenty textured quads, ending in `TMD_STREAM_END`.
///
/// First model creation resolves each command's draw-handler slot in place.
static u32 _gAya10500SecondPairHand0ModelStream[161];
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
static TmdBone _gAya10500FirstPairHand1ModelSkeleton[1] SECTION(".data");
PE_ASSET_BIND("aya_10200_model_00A5C_skeleton", _gAya10500FirstPairHand1ModelSkeleton);

/// Vertex count of the hand's sole part: 27.
static u32 _gAya10500FirstPairHand1ModelPartVerts[1] SECTION(".data");
PE_ASSET_BIND("aya_10200_model_00A5C_partVerts", _gAya10500FirstPairHand1ModelPartVerts);

/// Writable first-pair hand-1 vertices in integer coordinates local to the wrist.
static SVECTOR _gAya10500FirstPairHand1ModelVerts[27];
PE_ASSET_BIND("aya_10200_model_00A5C_verts", _gAya10500FirstPairHand1ModelVerts);

/// Writable part-local lighting normals with twelve fractional bits and independent indices.
static SVECTOR _gAya10500FirstPairHand1ModelNormals[27];
PE_ASSET_BIND("aya_10200_model_00A5C_normals", _gAya10500FirstPairHand1ModelNormals);

/// Writable commands for two textured triangles and 24 textured quads, ending in `TMD_STREAM_END`.
///
/// First model creation resolves each command's draw-handler slot in place.
static u32 _gAya10500FirstPairHand1ModelStream[189];
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
static TmdBone _gAya10500SecondPairHand1ModelSkeleton[1] SECTION(".data");
PE_ASSET_BIND("aya_10200_model_00F0C_skeleton", _gAya10500SecondPairHand1ModelSkeleton);

/// Vertex count of the hand's sole part: 23.
static u32 _gAya10500SecondPairHand1ModelPartVerts[1] SECTION(".data");
PE_ASSET_BIND("aya_10200_model_00F0C_partVerts", _gAya10500SecondPairHand1ModelPartVerts);

/// Writable second-pair hand-1 vertices in integer coordinates local to the wrist.
static SVECTOR _gAya10500SecondPairHand1ModelVerts[23];
PE_ASSET_BIND("aya_10200_model_00F0C_verts", _gAya10500SecondPairHand1ModelVerts);

/// Writable part-local lighting normals with twelve fractional bits and independent indices.
static SVECTOR _gAya10500SecondPairHand1ModelNormals[23];
PE_ASSET_BIND("aya_10200_model_00F0C_normals", _gAya10500SecondPairHand1ModelNormals);

/// Writable commands for two textured triangles and twenty textured quads, ending in `TMD_STREAM_END`.
///
/// First model creation resolves each command's draw-handler slot in place.
static u32 _gAya10500SecondPairHand1ModelStream[161];
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
static TmdBone _gAya10500BodyModelSkeleton[19] SECTION(".data");
PE_ASSET_BIND("aya_10500_model_02BB8_skeleton", _gAya10500BodyModelSkeleton);

/// Part-local vertex counts in skeleton order, totaling 358 vertices.
static u32 _gAya10500BodyModelPartVerts[19] SECTION(".data");
PE_ASSET_BIND("aya_10500_model_02BB8_partVerts", _gAya10500BodyModelPartVerts);

/// Writable body vertices in integer coordinates local to each model part.
static SVECTOR _gAya10500BodyModelVerts[358];
PE_ASSET_BIND("aya_10500_model_02BB8_verts", _gAya10500BodyModelVerts);

/// Writable part-local lighting normals with twelve fractional bits and independent stream indices.
static SVECTOR _gAya10500BodyModelNormals[379];
PE_ASSET_BIND("aya_10500_model_02BB8_normals", _gAya10500BodyModelNormals);

/// Writable commands for 290 textured triangles and 211 textured quads, ending in `TMD_STREAM_END`.
///
/// Handler resolution rewrites the command slots on first model creation.
/// The final group draws 82 triangles and 50 quads from the transformed cache.
static u32 _gAya10500BodyModelStream[4080];
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

static u32 _gAya10500Aya10200Image06AC4[200];
PE_ASSET_BIND("aya_10200_image_06AC4", _gAya10500Aya10200Image06AC4);
/// One open-eyes upload and its terminator; playback supplies the texture-relative destination.
///
/// Records remain writable, and their packed 8-bit pixels stay loaded until
/// the queued GPU transfer completes.
static GpuImageUpload _gAya10500EyesOpenUploads[2] = {
    { GPU_IMAGE_UPLOAD_COPY, 0, { 0, 0, AYA_10500_EYES_FRAME_WIDTH_WORDS, AYA_10500_EYES_FRAME_HEIGHT_ROWS }, _gAya10500Aya10200Image06AC4 },
    { GPU_IMAGE_UPLOAD_END },
};

static u32 _gAya10500Aya10200Image06E04[200];
PE_ASSET_BIND("aya_10200_image_06E04", _gAya10500Aya10200Image06E04);
/// One half-closed-eyes upload and its terminator, with writable destination and borrowed pixels.
static GpuImageUpload _gAya10500EyesHalfClosedUploads[2] = {
    { GPU_IMAGE_UPLOAD_COPY, 0, { 0, 0, AYA_10500_EYES_FRAME_WIDTH_WORDS, AYA_10500_EYES_FRAME_HEIGHT_ROWS }, _gAya10500Aya10200Image06E04 },
    { GPU_IMAGE_UPLOAD_END },
};

static u32 _gAya10500Aya10200Image07144[200];
PE_ASSET_BIND("aya_10200_image_07144", _gAya10500Aya10200Image07144);
/// One closed-eyes upload and its terminator, with writable destination and borrowed pixels.
static GpuImageUpload _gAya10500EyesClosedUploads[2] = {
    { GPU_IMAGE_UPLOAD_COPY, 0, { 0, 0, AYA_10500_EYES_FRAME_WIDTH_WORDS, AYA_10500_EYES_FRAME_HEIGHT_ROWS }, _gAya10500Aya10200Image07144 },
    { GPU_IMAGE_UPLOAD_END },
};

/// Resting mouth pixels: packed 8-bit palette indices, four texels per u_long.
static u32 _gAya10500MouthRestPixels[140];
PE_ASSET_BIND("aya_10200_image_07484", _gAya10500MouthRestPixels);
/// One resting-mouth upload and its terminator, with writable destination and borrowed pixels.
static GpuImageUpload _gAya10500MouthRestUploads[2] = {
    { GPU_IMAGE_UPLOAD_COPY, 0, { 0, 0, AYA_10500_MOUTH_FRAME_WIDTH_WORDS, AYA_10500_MOUTH_FRAME_HEIGHT_ROWS }, _gAya10500MouthRestPixels },
    { GPU_IMAGE_UPLOAD_END },
};

/// Alternate mouth selector's packed 8-bit pixels, identical here to the resting mouth.
static u32 _gAya10500MouthAlternatePixels[140];
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
