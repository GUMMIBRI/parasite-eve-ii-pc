/* Adapted from parasite-eve-pc/src/main/boot/settings_overlay.h. */
typedef struct OverlayGpuVertex {
    float x, y;
    float r, g, b, a;
    float u, v;
} OverlayGpuVertex;

static SDL_Window *s_overlayGpuWindow;
static SDL_GPUDevice *s_overlayGpuDevice;
static SDL_GPUGraphicsPipeline *s_overlayPipeline;
static SDL_GPUSampler *s_overlaySampler;
static SDL_GPUTexture *s_overlayTexture;
static SDL_GPUBuffer *s_overlayVertexBuffer;
static int s_overlayTextureW, s_overlayTextureH;
static int s_overlayWindowW, s_overlayWindowH;
static OverlaySurface s_overlaySurface;
static OverlayLayout s_overlayLayout;
static HostOverlayState s_overlayState;
static PsyzOverlayInitCB_SDL3GPU s_prevOverlayInit;
static PsyzOverlayRenderCB_SDL3GPU s_prevOverlayRender;
static PsyzOverlayDestroyCB s_prevOverlayDestroy;

static void Host_OverlayReleaseGpuResources(void) {
    if (s_overlayGpuDevice != NULL) {
        if (s_overlayTexture != NULL) {
            SDL_ReleaseGPUTexture(s_overlayGpuDevice, s_overlayTexture);
        }
        if (s_overlayVertexBuffer != NULL) {
            SDL_ReleaseGPUBuffer(s_overlayGpuDevice, s_overlayVertexBuffer);
        }
        if (s_overlaySampler != NULL) {
            SDL_ReleaseGPUSampler(s_overlayGpuDevice, s_overlaySampler);
        }
        if (s_overlayPipeline != NULL) {
            SDL_ReleaseGPUGraphicsPipeline(s_overlayGpuDevice, s_overlayPipeline);
        }
    }
    s_overlayTexture = NULL;
    s_overlayVertexBuffer = NULL;
    s_overlaySampler = NULL;
    s_overlayPipeline = NULL;
    s_overlayTextureW = s_overlayTextureH = 0;
    s_overlayWindowW = s_overlayWindowH = 0;
}

static void Host_OverlayDestroyGPU(void) {
    if (s_prevOverlayDestroy != NULL) {
        s_prevOverlayDestroy();
    }
    Host_OverlayReleaseGpuResources();
    OverlaySurfaceRelease(&s_overlaySurface);
    s_overlayGpuDevice = NULL;
    s_overlayGpuWindow = NULL;
}

static void Host_OverlayInitGPU(SDL_Window *window, SDL_GPUDevice *device) {
    if (s_prevOverlayInit != NULL) {
        s_prevOverlayInit(window, device);
    }
    if (s_overlayGpuDevice != NULL && s_overlayGpuDevice != device) {
        Host_OverlayReleaseGpuResources();
    }
    s_overlayGpuWindow = window;
    s_overlayGpuDevice = device;
}

static SDL_GPUShader *Host_CreateOverlayShader(
    SDL_GPUDevice *device,
    SDL_GPUShaderStage stage,
    const unsigned char *spirv,
    size_t spirvSize,
    const unsigned char *msl,
    size_t mslSize,
    const unsigned char *dxil,
    size_t dxilSize,
    Uint32 samplers,
    Uint32 uniforms
) {
    SDL_GPUShaderFormat formats = SDL_GetGPUShaderFormats(device);
    SDL_GPUShaderCreateInfo info;
    SDL_zero(info);
    info.stage = stage;
    info.num_samplers = samplers;
    info.num_uniform_buffers = uniforms;
    if (formats & SDL_GPU_SHADERFORMAT_SPIRV) {
        info.code = spirv;
        info.code_size = spirvSize;
        info.entrypoint = "main";
        info.format = SDL_GPU_SHADERFORMAT_SPIRV;
    } else if (formats & SDL_GPU_SHADERFORMAT_MSL) {
        info.code = msl;
        info.code_size = mslSize;
        info.entrypoint = "main0";
        info.format = SDL_GPU_SHADERFORMAT_MSL;
    } else if (formats & SDL_GPU_SHADERFORMAT_DXIL) {
        info.code = dxil;
        info.code_size = dxilSize;
        info.entrypoint = "main";
        info.format = SDL_GPU_SHADERFORMAT_DXIL;
    } else {
        return NULL;
    }
    return SDL_CreateGPUShader(device, &info);
}

static int Host_EnsureOverlayPipeline(SDL_GPUDevice *device, SDL_GPUTextureFormat format) {
    if (format == SDL_GPU_TEXTUREFORMAT_INVALID) {
        return 0;
    }
    if (s_overlayGpuDevice != NULL && s_overlayGpuDevice != device) {
        Host_OverlayReleaseGpuResources();
    }
    s_overlayGpuDevice = device;
    if (s_overlayPipeline != NULL && s_overlaySampler != NULL && s_overlayVertexBuffer != NULL) {
        return 1;
    }

    SDL_GPUShader *vertex = Host_CreateOverlayShader(
        device,
        SDL_GPU_SHADERSTAGE_VERTEX,
        tri_texture_vert_spv,
        sizeof(tri_texture_vert_spv),
        tri_texture_vert_msl,
        sizeof(tri_texture_vert_msl),
        tri_texture_vert_dxil,
        sizeof(tri_texture_vert_dxil),
        0,
        1
    );
    SDL_GPUShader *fragment = Host_CreateOverlayShader(
        device,
        SDL_GPU_SHADERSTAGE_FRAGMENT,
        texture_rgba_frag_spv,
        sizeof(texture_rgba_frag_spv),
        texture_rgba_frag_msl,
        sizeof(texture_rgba_frag_msl),
        texture_rgba_frag_dxil,
        sizeof(texture_rgba_frag_dxil),
        1,
        1
    );
    if (vertex == NULL || fragment == NULL) {
        if (vertex != NULL) {
            SDL_ReleaseGPUShader(device, vertex);
        }
        if (fragment != NULL) {
            SDL_ReleaseGPUShader(device, fragment);
        }
        return 0;
    }

    SDL_GPUVertexBufferDescription vbd;
    SDL_zero(vbd);
    vbd.slot = 0;
    vbd.pitch = sizeof(OverlayGpuVertex);
    vbd.input_rate = SDL_GPU_VERTEXINPUTRATE_VERTEX;

    SDL_GPUVertexAttribute attribs[3];
    SDL_zero(attribs);
    attribs[0].location = 0;
    attribs[0].buffer_slot = 0;
    attribs[0].format = SDL_GPU_VERTEXELEMENTFORMAT_FLOAT2;
    attribs[0].offset = 0;
    attribs[1].location = 1;
    attribs[1].buffer_slot = 0;
    attribs[1].format = SDL_GPU_VERTEXELEMENTFORMAT_FLOAT4;
    attribs[1].offset = 2 * sizeof(float);
    attribs[2].location = 2;
    attribs[2].buffer_slot = 0;
    attribs[2].format = SDL_GPU_VERTEXELEMENTFORMAT_FLOAT2;
    attribs[2].offset = 6 * sizeof(float);

    SDL_GPUColorTargetDescription color;
    SDL_zero(color);
    color.format = format;
    color.blend_state.enable_blend = true;
    color.blend_state.src_color_blendfactor = SDL_GPU_BLENDFACTOR_ONE;
    color.blend_state.dst_color_blendfactor = SDL_GPU_BLENDFACTOR_ONE_MINUS_SRC_ALPHA;
    color.blend_state.color_blend_op = SDL_GPU_BLENDOP_ADD;
    color.blend_state.src_alpha_blendfactor = SDL_GPU_BLENDFACTOR_ONE;
    color.blend_state.dst_alpha_blendfactor = SDL_GPU_BLENDFACTOR_ONE_MINUS_SRC_ALPHA;
    color.blend_state.alpha_blend_op = SDL_GPU_BLENDOP_ADD;

    SDL_GPUGraphicsPipelineCreateInfo info;
    SDL_zero(info);
    info.vertex_shader = vertex;
    info.fragment_shader = fragment;
    info.primitive_type = SDL_GPU_PRIMITIVETYPE_TRIANGLELIST;
    info.rasterizer_state.cull_mode = SDL_GPU_CULLMODE_NONE;
    info.vertex_input_state.num_vertex_buffers = 1;
    info.vertex_input_state.vertex_buffer_descriptions = &vbd;
    info.vertex_input_state.num_vertex_attributes = 3;
    info.vertex_input_state.vertex_attributes = attribs;
    info.target_info.color_target_descriptions = &color;
    info.target_info.num_color_targets = 1;
    s_overlayPipeline = SDL_CreateGPUGraphicsPipeline(device, &info);
    SDL_ReleaseGPUShader(device, vertex);
    SDL_ReleaseGPUShader(device, fragment);

    SDL_GPUSamplerCreateInfo sampler;
    SDL_zero(sampler);
    sampler.min_filter = SDL_GPU_FILTER_NEAREST;
    sampler.mag_filter = SDL_GPU_FILTER_NEAREST;
    sampler.address_mode_u = SDL_GPU_SAMPLERADDRESSMODE_CLAMP_TO_EDGE;
    sampler.address_mode_v = SDL_GPU_SAMPLERADDRESSMODE_CLAMP_TO_EDGE;
    sampler.address_mode_w = SDL_GPU_SAMPLERADDRESSMODE_CLAMP_TO_EDGE;
    s_overlaySampler = SDL_CreateGPUSampler(device, &sampler);

    SDL_GPUBufferCreateInfo bci;
    SDL_zero(bci);
    bci.usage = SDL_GPU_BUFFERUSAGE_VERTEX;
    bci.size = sizeof(OverlayGpuVertex) * 12;
    s_overlayVertexBuffer = SDL_CreateGPUBuffer(device, &bci);

    if (s_overlayPipeline == NULL || s_overlaySampler == NULL || s_overlayVertexBuffer == NULL) {
        Host_OverlayReleaseGpuResources();
        return 0;
    }
    return 1;
}

static void Host_WriteOverlayQuad(
    OverlayGpuVertex *out,
    float x0,
    float y0,
    float x1,
    float y1,
    float u0,
    float v0,
    float u1,
    float v1,
    float alpha
) {
    out[0] = (OverlayGpuVertex){x0, y0, 1.0f, 1.0f, 1.0f, alpha, u0, v0};
    out[1] = (OverlayGpuVertex){x1, y0, 1.0f, 1.0f, 1.0f, alpha, u1, v0};
    out[2] = (OverlayGpuVertex){x0, y1, 1.0f, 1.0f, 1.0f, alpha, u0, v1};
    out[3] = (OverlayGpuVertex){x0, y1, 1.0f, 1.0f, 1.0f, alpha, u0, v1};
    out[4] = (OverlayGpuVertex){x1, y0, 1.0f, 1.0f, 1.0f, alpha, u1, v0};
    out[5] = (OverlayGpuVertex){x1, y1, 1.0f, 1.0f, 1.0f, alpha, u1, v1};
}

static int s_overlayIsFps;
static int Host_UploadOverlaySurfaceAndVertices(SDL_GPUDevice *device) {
    if (s_overlaySurface.w <= 0 || s_overlaySurface.h <= 0 || s_overlayWindowW <= 0 ||
        s_overlayWindowH <= 0 || s_overlayVertexBuffer == NULL) {
        return 0;
    }
    if (s_overlayTexture == NULL || s_overlayTextureW != s_overlaySurface.w ||
        s_overlayTextureH != s_overlaySurface.h) {
        SDL_GPUTextureCreateInfo info;
        if (s_overlayTexture != NULL) {
            SDL_ReleaseGPUTexture(device, s_overlayTexture);
        }
        SDL_zero(info);
        info.type = SDL_GPU_TEXTURETYPE_2D;
        info.format = SDL_GPU_TEXTUREFORMAT_R8G8B8A8_UNORM;
        info.usage = SDL_GPU_TEXTUREUSAGE_SAMPLER;
        info.width = (Uint32)s_overlaySurface.w;
        info.height = (Uint32)s_overlaySurface.h;
        info.layer_count_or_depth = 1;
        info.num_levels = 1;
        s_overlayTexture = SDL_CreateGPUTexture(device, &info);
        if (s_overlayTexture == NULL) {
            s_overlayTextureW = 0;
            s_overlayTextureH = 0;
            return 0;
        }
        s_overlayTextureW = s_overlaySurface.w;
        s_overlayTextureH = s_overlaySurface.h;
    }

    OverlayGpuVertex verts[12];
    float w = (float)s_overlayWindowW;
    float h = (float)s_overlayWindowH;
    float solidU = 0.5f / (float)s_overlayTextureW;
    float solidV = ((float)s_overlayTextureH - 0.5f) / (float)s_overlayTextureH;
    Host_WriteOverlayQuad(verts, -1.0f, 1.0f, 1.0f, -1.0f, solidU, solidV, solidU, solidV, s_overlayIsFps?0.0f:0.62f);

    float x0 = (float)s_overlayLayout.x / w * 2.0f - 1.0f;
    float y0 = 1.0f - (float)s_overlayLayout.y / h * 2.0f;
    float x1 = (float)(s_overlayLayout.x + s_overlayLayout.w) / w * 2.0f - 1.0f;
    float y1 = 1.0f - (float)(s_overlayLayout.y + s_overlayLayout.h) / h * 2.0f;
    float panelV1 = (float)(s_overlayTextureH - 1) / (float)s_overlayTextureH;
    Host_WriteOverlayQuad(verts + 6, x0, y0, x1, y1, 0.0f, 0.0f, 1.0f, panelV1, 1.0f);

    Uint32 texBytes = (Uint32)((size_t)s_overlaySurface.w * (size_t)s_overlaySurface.h * 4u);
    Uint32 vtxBytes = (Uint32)sizeof(verts);
    SDL_GPUTransferBufferCreateInfo transferInfo;
    SDL_zero(transferInfo);
    transferInfo.usage = SDL_GPU_TRANSFERBUFFERUSAGE_UPLOAD;
    transferInfo.size = texBytes + vtxBytes;
    SDL_GPUTransferBuffer *transfer = SDL_CreateGPUTransferBuffer(device, &transferInfo);
    if (transfer == NULL) {
        return 0;
    }
    uint8_t *mapped = (uint8_t *)SDL_MapGPUTransferBuffer(device, transfer, false);
    if (mapped == NULL) {
        SDL_ReleaseGPUTransferBuffer(device, transfer);
        return 0;
    }
    memcpy(mapped, s_overlaySurface.pixels, texBytes);
    memcpy(mapped + texBytes, verts, vtxBytes);
    SDL_UnmapGPUTransferBuffer(device, transfer);

    SDL_GPUCommandBuffer *command = SDL_AcquireGPUCommandBuffer(device);
    if (command == NULL) {
        SDL_ReleaseGPUTransferBuffer(device, transfer);
        return 0;
    }
    SDL_GPUCopyPass *copy = SDL_BeginGPUCopyPass(command);
    if(!copy){SDL_CancelGPUCommandBuffer(command);SDL_ReleaseGPUTransferBuffer(device,transfer);return 0;}

    SDL_GPUTextureTransferInfo texSrc;
    SDL_zero(texSrc);
    texSrc.transfer_buffer = transfer;
    texSrc.offset = 0;
    texSrc.pixels_per_row = (Uint32)s_overlaySurface.w;
    texSrc.rows_per_layer = (Uint32)s_overlaySurface.h;

    SDL_GPUTextureRegion texDst;
    SDL_zero(texDst);
    texDst.texture = s_overlayTexture;
    texDst.w = (Uint32)s_overlaySurface.w;
    texDst.h = (Uint32)s_overlaySurface.h;
    texDst.d = 1;
    SDL_UploadToGPUTexture(copy, &texSrc, &texDst, false);

    SDL_GPUTransferBufferLocation vtxSrc;
    SDL_zero(vtxSrc);
    vtxSrc.transfer_buffer = transfer;
    vtxSrc.offset = texBytes;

    SDL_GPUBufferRegion vtxDst;
    SDL_zero(vtxDst);
    vtxDst.buffer = s_overlayVertexBuffer;
    vtxDst.offset = 0;
    vtxDst.size = vtxBytes;
    SDL_UploadToGPUBuffer(copy, &vtxSrc, &vtxDst, false);

    SDL_EndGPUCopyPass(copy);
    bool submitted=SDL_SubmitGPUCommandBuffer(command);
    SDL_ReleaseGPUTransferBuffer(device, transfer);
    return submitted;
}


static void Host_OverlayRenderGPU(SDL_GPUCommandBuffer *command, SDL_GPURenderPass *pass) {
    if (s_prevOverlayRender != NULL) {
        s_prevOverlayRender(command, pass);
    }
#ifdef PE_PS5_GPU_NATIVE
    if(!s_overlayState.open&&host_options.show_fps)Host_FpsRefreshGPU();
    if ((!s_overlayState.open&&(!host_options.show_fps||!s_overlayIsFps)) || s_overlayPipeline == NULL || s_overlayTexture == NULL ||
        s_overlayVertexBuffer == NULL || s_overlayWindowW <= 0 || s_overlayWindowH <= 0) {
        return;
    }
#else
    if (!s_overlayState.open || s_overlayPipeline == NULL || s_overlayTexture == NULL ||
        s_overlayVertexBuffer == NULL || s_overlayWindowW <= 0 || s_overlayWindowH <= 0) {
        return;
    }
#endif

    static const float kIdentityMvp[16] = {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };
    static const float kColorScale[4] = {1.0f, 0.0f, 0.0f, 0.0f};

    SDL_GPUViewport viewport = {
        0.0f, 0.0f, (float)s_overlayWindowW, (float)s_overlayWindowH, 0.0f, 1.0f
    };
    SDL_Rect scissor = {0, 0, s_overlayWindowW, s_overlayWindowH};
    SDL_SetGPUViewport(pass, &viewport);
    SDL_SetGPUScissor(pass, &scissor);
    SDL_BindGPUGraphicsPipeline(pass, s_overlayPipeline);

    SDL_GPUTextureSamplerBinding samplerBind;
    SDL_zero(samplerBind);
    samplerBind.texture = s_overlayTexture;
    samplerBind.sampler = s_overlaySampler;
    SDL_BindGPUFragmentSamplers(pass, 0, &samplerBind, 1);

    SDL_GPUBufferBinding vtxBind;
    SDL_zero(vtxBind);
    vtxBind.buffer = s_overlayVertexBuffer;
    vtxBind.offset = 0;
    SDL_BindGPUVertexBuffers(pass, 0, &vtxBind, 1);

    SDL_PushGPUVertexUniformData(command, 0, kIdentityMvp, sizeof(kIdentityMvp));
    SDL_PushGPUFragmentUniformData(command, 0, kColorScale, sizeof(kColorScale));
    SDL_DrawGPUPrimitives(pass, 12, 1, 0, 0);
}
