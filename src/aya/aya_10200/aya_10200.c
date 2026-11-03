#include "aya/aya.h"
#include "port/asset_bind.h"

#include <psyz.h>
#include <libgpu.h>

#include "common.h"

#include "gameplay/gpu_image_upload.h"

/// Packed facial-frame dimensions, in 16-bit VRAM words and rows.
enum {
    AYA_10200_EYES_FRAME_WIDTH_WORDS  = 25,
    AYA_10200_EYES_FRAME_HEIGHT_ROWS  = 16,
    AYA_10200_MOUTH_FRAME_WIDTH_WORDS = 14,
    AYA_10200_MOUTH_FRAME_HEIGHT_ROWS = 20,
};

/// Initial local transform and self-parented root for first-pair hand slot 0.
///
/// Read-only source tables retain their serialized positions in the data section.
static TmdBone _gAya10200FirstPairHand0ModelSkeleton[1] SECTION(".data");
PE_ASSET_BIND("aya_10200_model_0019C_skeleton", _gAya10200FirstPairHand0ModelSkeleton);

/// Vertex count of the hand's sole part: 23.
static u32 _gAya10200FirstPairHand0ModelPartVerts[1] SECTION(".data");
PE_ASSET_BIND("aya_10200_model_0019C_partVerts", _gAya10200FirstPairHand0ModelPartVerts);

/// Writable first-pair hand-0 vertices in integer coordinates local to the wrist.
static SVECTOR _gAya10200FirstPairHand0ModelVerts[23];
PE_ASSET_BIND("aya_10200_model_0019C_verts", _gAya10200FirstPairHand0ModelVerts);

/// Writable first-pair hand-0 lighting normals with twelve fractional bits and independent indices.
static SVECTOR _gAya10200FirstPairHand0ModelNormals[23];
PE_ASSET_BIND("aya_10200_model_0019C_normals", _gAya10200FirstPairHand0ModelNormals);

/// Writable commands for two textured triangles and twenty textured quads, ending in `TMD_STREAM_END`.
///
/// First model creation resolves each command's draw-handler slot in place.
static u32 _gAya10200FirstPairHand0ModelStream[161];
PE_ASSET_BIND("aya_10200_model_0019C_stream", _gAya10200FirstPairHand0ModelStream);

TmdSource gAya10200FirstPairHand0Model = {
    .handlersResolved    = false,
    .bufferHalfBytes     = (2 * sizeof(POLY_GT3)) + (20 * sizeof(POLY_GT4)),
    .preXformRegionBytes = 0,
    .partCount           = ARRAY_SIZE(_gAya10200FirstPairHand0ModelSkeleton),
    .partVertexCounts    = _gAya10200FirstPairHand0ModelPartVerts,
    .verts               = _gAya10200FirstPairHand0ModelVerts,
    .normals             = _gAya10200FirstPairHand0ModelNormals,
    .skeleton            = _gAya10200FirstPairHand0ModelSkeleton,
    .stream              = _gAya10200FirstPairHand0ModelStream,
};

/// Initial local transform and self-parented root for second-pair hand slot 0.
///
/// Read-only source tables retain their serialized positions in the data section.
static TmdBone _gAya10200SecondPairHand0ModelSkeleton[1] SECTION(".data");
PE_ASSET_BIND("aya_10200_model_0019C_skeleton", _gAya10200SecondPairHand0ModelSkeleton);

/// Vertex count of the hand's sole part: 23.
static u32 _gAya10200SecondPairHand0ModelPartVerts[1] SECTION(".data");
PE_ASSET_BIND("aya_10200_model_0019C_partVerts", _gAya10200SecondPairHand0ModelPartVerts);

/// Writable second-pair hand-0 vertices in integer coordinates local to the wrist.
static SVECTOR _gAya10200SecondPairHand0ModelVerts[23];
PE_ASSET_BIND("aya_10200_model_0019C_verts", _gAya10200SecondPairHand0ModelVerts);

/// Writable second-pair hand-0 lighting normals with twelve fractional bits and independent indices.
static SVECTOR _gAya10200SecondPairHand0ModelNormals[23];
PE_ASSET_BIND("aya_10200_model_0019C_normals", _gAya10200SecondPairHand0ModelNormals);

/// Writable commands for two textured triangles and twenty textured quads, ending in `TMD_STREAM_END`.
///
/// First model creation resolves each command's draw-handler slot in place.
static u32 _gAya10200SecondPairHand0ModelStream[161];
PE_ASSET_BIND("aya_10200_model_0019C_stream", _gAya10200SecondPairHand0ModelStream);

TmdSource gAya10200SecondPairHand0Model = {
    .handlersResolved    = false,
    .bufferHalfBytes     = (2 * sizeof(POLY_GT3)) + (20 * sizeof(POLY_GT4)),
    .preXformRegionBytes = 0,
    .partCount           = ARRAY_SIZE(_gAya10200SecondPairHand0ModelSkeleton),
    .partVertexCounts    = _gAya10200SecondPairHand0ModelPartVerts,
    .verts               = _gAya10200SecondPairHand0ModelVerts,
    .normals             = _gAya10200SecondPairHand0ModelNormals,
    .skeleton            = _gAya10200SecondPairHand0ModelSkeleton,
    .stream              = _gAya10200SecondPairHand0ModelStream,
};

/// Initial local transform and self-parented root for first-pair hand slot 1.
///
/// Read-only source tables retain their serialized positions in the data section.
static TmdBone _gAya10200FirstPairHand1ModelSkeleton[1] SECTION(".data");
PE_ASSET_BIND("aya_10200_model_00A5C_skeleton", _gAya10200FirstPairHand1ModelSkeleton);

/// Vertex count of the hand's sole part: 27.
static u32 _gAya10200FirstPairHand1ModelPartVerts[1] SECTION(".data");
PE_ASSET_BIND("aya_10200_model_00A5C_partVerts", _gAya10200FirstPairHand1ModelPartVerts);

/// Writable first-pair hand-1 vertices in integer coordinates local to the wrist.
static SVECTOR _gAya10200FirstPairHand1ModelVerts[27];
PE_ASSET_BIND("aya_10200_model_00A5C_verts", _gAya10200FirstPairHand1ModelVerts);

/// Writable part-local lighting normals with twelve fractional bits and independent indices.
static SVECTOR _gAya10200FirstPairHand1ModelNormals[27];
PE_ASSET_BIND("aya_10200_model_00A5C_normals", _gAya10200FirstPairHand1ModelNormals);

/// Writable commands for two textured triangles and 24 textured quads, ending in `TMD_STREAM_END`.
///
/// First model creation resolves each command's draw-handler slot in place.
static u32 _gAya10200FirstPairHand1ModelStream[189];
PE_ASSET_BIND("aya_10200_model_00A5C_stream", _gAya10200FirstPairHand1ModelStream);

TmdSource gAya10200FirstPairHand1Model = {
    .handlersResolved    = false,
    .bufferHalfBytes     = (2 * sizeof(POLY_GT3)) + (24 * sizeof(POLY_GT4)),
    .preXformRegionBytes = 0,
    .partCount           = ARRAY_SIZE(_gAya10200FirstPairHand1ModelSkeleton),
    .partVertexCounts    = _gAya10200FirstPairHand1ModelPartVerts,
    .verts               = _gAya10200FirstPairHand1ModelVerts,
    .normals             = _gAya10200FirstPairHand1ModelNormals,
    .skeleton            = _gAya10200FirstPairHand1ModelSkeleton,
    .stream              = _gAya10200FirstPairHand1ModelStream,
};

/// Initial local transform and self-parented root for second-pair hand slot 1.
///
/// Read-only source tables retain their serialized positions in the data section.
static TmdBone _gAya10200SecondPairHand1ModelSkeleton[1] SECTION(".data");
PE_ASSET_BIND("aya_10200_model_00F0C_skeleton", _gAya10200SecondPairHand1ModelSkeleton);

/// Vertex count of the hand's sole part: 23.
static u32 _gAya10200SecondPairHand1ModelPartVerts[1] SECTION(".data");
PE_ASSET_BIND("aya_10200_model_00F0C_partVerts", _gAya10200SecondPairHand1ModelPartVerts);

/// Writable second-pair hand-1 vertices in integer coordinates local to the wrist.
static SVECTOR _gAya10200SecondPairHand1ModelVerts[23];
PE_ASSET_BIND("aya_10200_model_00F0C_verts", _gAya10200SecondPairHand1ModelVerts);

/// Writable part-local lighting normals with twelve fractional bits and independent indices.
static SVECTOR _gAya10200SecondPairHand1ModelNormals[23];
PE_ASSET_BIND("aya_10200_model_00F0C_normals", _gAya10200SecondPairHand1ModelNormals);

/// Writable commands for two textured triangles and twenty textured quads, ending in `TMD_STREAM_END`.
///
/// First model creation resolves each command's draw-handler slot in place.
static u32 _gAya10200SecondPairHand1ModelStream[161];
PE_ASSET_BIND("aya_10200_model_00F0C_stream", _gAya10200SecondPairHand1ModelStream);

TmdSource gAya10200SecondPairHand1Model = {
    .handlersResolved    = false,
    .bufferHalfBytes     = (2 * sizeof(POLY_GT3)) + (20 * sizeof(POLY_GT4)),
    .preXformRegionBytes = 0,
    .partCount           = ARRAY_SIZE(_gAya10200SecondPairHand1ModelSkeleton),
    .partVertexCounts    = _gAya10200SecondPairHand1ModelPartVerts,
    .verts               = _gAya10200SecondPairHand1ModelVerts,
    .normals             = _gAya10200SecondPairHand1ModelNormals,
    .skeleton            = _gAya10200SecondPairHand1ModelSkeleton,
    .stream              = _gAya10200SecondPairHand1ModelStream,
};

/// The player body for resource variant 3, `gAya10200BodyModel`, with its arrays: generated from the asset
/// (characters/aya/10200/aya_10200_body.usda, textured through characters/aya/10200/binding) by
/// tools/buildsteps/gen_model_source.py.
#include "assets/characters/aya/10200/body.inc"

static u32 _gAya10200Image06AC4[200];
PE_ASSET_BIND("aya_10200_image_06AC4", _gAya10200Image06AC4);
/// One open-eyes frame followed by the upload terminator; the destination is rewritten at playback.
static GpuImageUpload _gAya10200EyesOpenUploads[] = {
    { GPU_IMAGE_UPLOAD_COPY, 0, { 0, 0, AYA_10200_EYES_FRAME_WIDTH_WORDS, AYA_10200_EYES_FRAME_HEIGHT_ROWS }, _gAya10200Image06AC4 },
    { GPU_IMAGE_UPLOAD_END },
};

static u32 _gAya10200Image06E04[200];
PE_ASSET_BIND("aya_10200_image_06E04", _gAya10200Image06E04);
/// One half-closed-eyes frame followed by the upload terminator; the destination is rewritten at playback.
static GpuImageUpload _gAya10200EyesHalfClosedUploads[] = {
    { GPU_IMAGE_UPLOAD_COPY, 0, { 0, 0, AYA_10200_EYES_FRAME_WIDTH_WORDS, AYA_10200_EYES_FRAME_HEIGHT_ROWS }, _gAya10200Image06E04 },
    { GPU_IMAGE_UPLOAD_END },
};

static u32 _gAya10200Image07144[200];
PE_ASSET_BIND("aya_10200_image_07144", _gAya10200Image07144);
/// One closed-eyes frame followed by the upload terminator; the destination is rewritten at playback.
static GpuImageUpload _gAya10200EyesClosedUploads[] = {
    { GPU_IMAGE_UPLOAD_COPY, 0, { 0, 0, AYA_10200_EYES_FRAME_WIDTH_WORDS, AYA_10200_EYES_FRAME_HEIGHT_ROWS }, _gAya10200Image07144 },
    { GPU_IMAGE_UPLOAD_END },
};

/// Default mouth frame: packed 8-bit indices, two texels per VRAM word and four per u_long.
static u32 _gAya10200MouthRestPixels[140];
PE_ASSET_BIND("aya_10200_image_07484", _gAya10200MouthRestPixels);
/// One default mouth frame followed by the upload terminator; the destination is rewritten at playback.
static GpuImageUpload _gAya10200MouthRestUploads[] = {
    { GPU_IMAGE_UPLOAD_COPY, 0, { 0, 0, AYA_10200_MOUTH_FRAME_WIDTH_WORDS, AYA_10200_MOUTH_FRAME_HEIGHT_ROWS }, _gAya10200MouthRestPixels },
    { GPU_IMAGE_UPLOAD_END },
};

/// Alternate mouth selector's packed 8-bit frame, identical to the default frame in this package.
static u32 _gAya10200MouthAlternatePixels[140];
PE_ASSET_BIND("aya_10200_image_07484", _gAya10200MouthAlternatePixels);
/// One alternate mouth frame followed by the upload terminator; the destination is rewritten at playback.
static GpuImageUpload _gAya10200MouthAlternateUploads[] = {
    { GPU_IMAGE_UPLOAD_COPY, 0, { 0, 0, AYA_10200_MOUTH_FRAME_WIDTH_WORDS, AYA_10200_MOUTH_FRAME_HEIGHT_ROWS }, _gAya10200MouthAlternatePixels },
    { GPU_IMAGE_UPLOAD_END },
};

GpuImageUpload* gAya10200EyesRestSequence[]    = { _gAya10200EyesOpenUploads, NULL };
GpuImageUpload* gAya10200EyesClosingSequence[] = { _gAya10200EyesOpenUploads, _gAya10200EyesHalfClosedUploads, _gAya10200EyesClosedUploads, NULL };
GpuImageUpload* gAya10200EyesOpeningSequence[] = { _gAya10200EyesClosedUploads, _gAya10200EyesHalfClosedUploads, _gAya10200EyesOpenUploads, NULL };
GpuImageUpload* gAya10200EyesBlinkSequence[]   = {
    _gAya10200EyesOpenUploads,
    _gAya10200EyesHalfClosedUploads,
    _gAya10200EyesClosedUploads,
    _gAya10200EyesHalfClosedUploads,
    _gAya10200EyesOpenUploads,
    NULL,
};
GpuImageUpload* gAya10200MouthRestSequence[]      = { _gAya10200MouthRestUploads, NULL };
GpuImageUpload* gAya10200MouthAlternateSequence[] = { _gAya10200MouthAlternateUploads, NULL };
