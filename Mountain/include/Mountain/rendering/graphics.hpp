#pragma once

#include "Mountain/core.hpp"

#include <magic_enum/magic_enum.hpp>

#include "Mountain/utils/meta_programming.hpp"

/// @namespace Mountain::Graphics
/// @brief Low-level graphics API
///
/// You should only use this if you know what you are doing and/or have experience with graphics APIs such as OpenGL.
namespace Mountain::Graphics
{
    struct GpuVertexArray;
    struct GpuBuffer;
    struct GpuTexture;

    enum class ImageShaderAccess : uint8_t
    {
        ReadOnly,
        WriteOnly,
        ReadWrite,

        Count
    };

    ENUM_COUNT(ImageShaderAccess);

    enum class GpuDataSynchronizationType : uint16_t
    {
        None               = 0,

        VertexAttribArray  = 1 << 0,
        ElementArray       = 1 << 1,
        Uniform            = 1 << 2,
        TextureFetch       = 1 << 3,

        // For some reason, the OpenGL bit values skip the 1 << 4 or 0x10 value

        ShaderImageAccess  = 1 << 5,
        Command            = 1 << 6,
        PixelBuffer        = 1 << 7,
        TextureUpdate      = 1 << 8,
        BufferUpdate       = 1 << 9,
        ClientMappedBuffer = 1 << 10,
        Framebuffer        = 1 << 11,
        TransformFeedback  = 1 << 12,
        AtomicCounter      = 1 << 13,
        ShaderStorage      = 1 << 14,
        QueryBuffer        = 1 << 15
    };

    enum class MagnificationFilter : uint8_t
    {
        Nearest,
        Linear,

        Count
    };

    ENUM_COUNT(MagnificationFilter);

    enum class Wrapping : uint8_t
    {
        Repeat,
        MirroredRepeat,
        ClampToEdge,
        ClampToBorder,

        Count
    };

    ENUM_COUNT(Wrapping);

    enum class ShaderType : uint8_t
    {
        Vertex,
        Fragment,

        Count
    };

    ENUM_COUNT(ShaderType);

    enum class InternalFormat : uint8_t
    {
        Red8,
        Red8Signed,
        Red16,
        Red16Signed,

        RedGreen8,
        RedGreen8Signed,
        RedGreen16,
        RedGreen16Signed,

        Red3Green3Blue2,

        RedGreenBlue4,
        RedGreenBlue5,
        RedGreenBlue8,
        RedGreenBlue8Signed,
        RedGreenBlue10,
        RedGreenBlue12,
        RedGreenBlue16,
        RedGreenBlue16Signed,

        RedGreenBlueAlpha2,
        RedGreenBlueAlpha4,
        RedGreenBlue5Alpha1,
        RedGreenBlueAlpha8,
        RedGreenBlueAlpha8Signed,
        RedGreenBlue10Alpha2,
        RedGreenBlue10Alpha2UnsignedInt,
        RedGreenBlueAlpha12,
        RedGreenBlueAlpha16,

        SignedRedGreenBlue8,
        SignedRedGreenBlueAlpha8,

        Red16Float,
        RedGreen16Float,
        RedGreenBlue16Float,
        RedGreenBlueAlpha16Float,

        Red32Float,
        RedGreen32Float,
        RedGreenBlue32Float,
        RedGreenBlueAlpha32Float,

        Red11FloatGreen11FloatBlue10Float,

        RedGreenBlue9Shared5,

        Red8Int,
        Red8UnsignedInt,
        Red16Int,
        Red16UnsignedInt,
        Red32Int,
        Red32UnsignedInt,

        RedGreen8Int,
        RedGreen8UnsignedInt,
        RedGreen16Int,
        RedGreen16UnsignedInt,
        RedGreen32Int,
        RedGreen32UnsignedInt,

        RedGreenBlue8Int,
        RedGreenBlue8UnsignedInt,
        RedGreenBlue16Int,
        RedGreenBlue16UnsignedInt,
        RedGreenBlue32Int,
        RedGreenBlue32UnsignedInt,

        RedGreenBlueAlpha8Int,
        RedGreenBlueAlpha8UnsignedInt,
        RedGreenBlueAlpha16Int,
        RedGreenBlueAlpha16UnsignedInt,
        RedGreenBlueAlpha32Int,
        RedGreenBlueAlpha32UnsignedInt,

        Count
    };

    ENUM_COUNT(InternalFormat);

    enum class Format : uint8_t
    {
        Red,
        RedGreen,
        RedGreenBlue,
        BlueGreenRed,
        RedGreenBlueAlpha,
        BlueGreenRedAlpha,

        Count
    };

    ENUM_COUNT(Format);

    enum class DataType : uint8_t
    {
        UnsignedByte,
        Byte,
        UnsignedShort,
        Short,
        UnsignedInt,
        Int,
        Float,

        // ReSharper disable CppInconsistentNaming
        UnsignedByte_3_3_2,
        UnsignedByte_2_3_3_Reverse,

        UnsignedShort_5_6_5,
        UnsignedShort_5_6_5_Reverse,
        UnsignedShort_4_4_4_4,
        UnsignedShort_4_4_4_4_Reverse,
        UnsignedShort_5_5_5_1,
        UnsignedShort_1_5_5_5_Reverse,

        UnsignedInt_8_8_8_8,
        UnsignedInt_8_8_8_8_Reverse,
        UnsignedInt_10_10_10_2,
        UnsignedInt_2_10_10_10_Reverse,
        // ReSharper restore CppInconsistentNaming

        Count
    };

    ENUM_COUNT(DataType);

    enum class Constant : uint8_t
    {
        ActiveTexture,

        AliasedLineWidthRange,

        ArrayBufferBinding,

        Blend,
        BlendColor,
        BlendDstAlpha,
        BlendDstRgb,
        BlendEquationRgb,
        BlendEquationAlpha,
        BlendSrcAlpha,
        BlendSrcRgb,

        ColorClearValue,
        ColorLogicOp,
        ColorWritemask,

        CompressedTextureFormats,

        MaxComputeShaderStorageBlocks,

        MaxCombinedShaderStorageBlocks,

        MaxComputeUniformBlocks,
        MaxComputeTextureImageUnits,
        MaxComputeUniformComponents,
        MaxComputeAtomicCounters,
        MaxComputeAtomicCounterBuffers,
        MaxCombinedComputeUniformComponents,
        MaxComputeWorkGroupInvocations,
        MaxComputeWorkGroupCount,
        MaxComputeWorkGroupSize,

        DispatchIndirectBufferBinding,

        MaxDebugGroupStackDepth,

        DebugGroupStackDepth,

        ContextFlags,

        CullFace,
        CullFaceMode,

        CurrentProgram,

        DepthClearValue,
        DepthFunc,
        DepthRange,
        DepthTest,
        DepthWritemask,

        Dither,

        DoubleBuffer,

        DrawBuffer,
        DrawBuffer0,
        DrawBuffer1,
        DrawBuffer2,
        DrawBuffer3,
        DrawBuffer4,
        DrawBuffer5,
        DrawBuffer6,
        DrawBuffer7,
        DrawBuffer8,
        DrawBuffer9,
        DrawBuffer10,
        DrawBuffer11,
        DrawBuffer12,
        DrawBuffer13,
        DrawBuffer14,
        DrawBuffer15,
        DrawFramebufferBinding,

        ReadFramebufferBinding,

        ElementArrayBufferBinding,

        FragmentShaderDerivativeHint,

        ImplementationColorReadFormat,
        ImplementationColorReadType,

        LineSmooth,
        LineSmoothHint,
        LineWidth,

        LayerProvokingVertex,

        LogicOpMode,

        MajorVersion,

        Max3dTextureSize,

        MaxArrayTextureLayers,

        MaxClipDistances,

        MaxColorTextureSamples,

        MaxCombinedAtomicCounters,
        MaxCombinedFragmentUniformComponents,
        MaxCombinedGeometryUniformComponents,
        MaxCombinedTextureImageUnits,
        MaxCombinedUniformBlocks,
        MaxCombinedVertexUniformComponents,

        MaxCubeMapTextureSize,

        MaxDepthTextureSamples,

        MaxDrawBuffers,

        MaxDualSourceDrawBuffers,

        MaxElementsIndices,
        MaxElementsVertices,

        MaxFragmentAtomicCounters,
        MaxFragmentShaderStorageBlocks,
        MaxFragmentInputComponents,
        MaxFragmentUniformComponents,
        MaxFragmentUniformVectors,
        MaxFragmentUniformBlocks,

        MaxFramebufferWidth,
        MaxFramebufferHeight,
        MaxFramebufferLayers,
        MaxFramebufferSamples,

        MaxGeometryAtomicCounters,
        MaxGeometryShaderStorageBlocks,
        MaxGeometryInputComponents,
        MaxGeometryOutputComponents,
        MaxGeometryTextureImageUnits,
        MaxGeometryUniformBlocks,
        MaxGeometryUniformComponents,

        MaxIntegerSamples,

        MinMapBufferAlignment,

        MaxLabelLength,

        MaxProgramTexelOffset,
        MinProgramTexelOffset,

        MaxRectangleTextureSize,

        MaxRenderbufferSize,

        MaxSampleMaskWords,

        MaxServerWaitTimeout,

        MaxShaderStorageBufferBindings,

        MaxTessControlAtomicCounters,
        MaxTessEvaluationAtomicCounters,
        MaxTessControlShaderStorageBlocks,
        MaxTessEvaluationShaderStorageBlocks,

        MaxTextureBufferSize,
        MaxTextureImageUnits,
        MaxTextureLodBias,
        MaxTextureSize,

        MaxUniformBufferBindings,
        MaxUniformBlockSize,
        MaxUniformLocations,

        MaxVaryingComponents,
        MaxVaryingVectors,
        MaxVaryingFloats,

        MaxVertexAtomicCounters,
        MaxVertexAttribs,
        MaxVertexShaderStorageBlocks,
        MaxVertexTextureImageUnits,
        MaxVertexUniformComponents,
        MaxVertexUniformVectors,
        MaxVertexOutputComponents,
        MaxVertexUniformBlocks,

        MaxViewportDims,
        MaxViewports,

        MinorVersion,

        NumCompressedTextureFormats,
        NumExtensions,
        NumProgramBinaryFormats,
        NumShaderBinaryFormats,

        PackAlignment,
        PackImageHeight,
        PackLsbFirst,
        PackRowLength,
        PackSkipImages,
        PackSkipPixels,
        PackSkipRows,
        PackSwapBytes,

        PixelPackBufferBinding,
        PixelUnpackBufferBinding,

        PointFadeThresholdSize,

        PrimitiveRestartIndex,

        ProgramBinaryFormats,
        ProgramPipelineBinding,
        ProgramPointSize,

        ProvokingVertex,

        PointSize,
        PointSizeGranularity,
        PointSizeRange,

        PolygonOffsetFactor,
        PolygonOffsetUnits,
        PolygonOffsetFill,
        PolygonOffsetLine,
        PolygonOffsetPoint,
        PolygonSmooth,
        PolygonSmoothHint,

        ReadBuffer,

        RenderbufferBinding,

        SampleBuffers,
        SampleCoverageValue,
        SampleCoverageInvert,
        SampleMaskValue,

        SamplerBinding,

        Samples,

        ScissorBox,
        ScissorTest,

        ShaderCompiler,
        ShaderStorageBufferBinding,
        ShaderStorageBufferOffsetAlignment,

        ShaderStorageBufferStart,
        ShaderStorageBufferSize,

        SmoothLineWidthRange,
        SmoothLineWidthGranularity,

        StencilBackFail,
        StencilBackFunc,
        StencilBackPassDepthFail,
        StencilBackPassDepthPass,
        StencilBackRef,
        StencilBackValueMask,
        StencilBackWritemask,
        StencilClearValue,
        StencilFail,
        StencilFunc,
        StencilPassDepthFail,
        StencilPassDepthPass,
        StencilRef,
        StencilTest,
        StencilValueMask,
        StencilWritemask,

        Stereo,

        SubpixelBits,

        TextureBinding1d,
        TextureBinding1dArray,
        TextureBinding2d,
        TextureBinding2dArray,
        TextureBinding2dMultisample,
        TextureBinding2dMultisampleArray,
        TextureBinding3d,
        TextureBindingBuffer,
        TextureBindingCubeMap,
        TextureBindingRectangle,
        TextureCompressionHint,
        TextureBufferOffsetAlignment,

        Timestamp,

        TransformFeedbackBufferBinding,
        TransformFeedbackBufferStart,
        TransformFeedbackBufferSize,

        UniformBufferBinding,
        UniformBufferOffsetAlignment,
        UniformBufferSize,
        UniformBufferStart,

        UnpackAlignment,
        UnpackImageHeight,
        UnpackLsbFirst,
        UnpackRowLength,
        UnpackSkipImages,
        UnpackSkipPixels,
        UnpackSkipRows,
        UnpackSwapBytes,

        VertexArrayBinding,
        VertexBindingDivisor,
        VertexBindingOffset,
        VertexBindingStride,
        VertexBindingBuffer,

        MaxVertexAttribRelativeOffset,
        MaxVertexAttribBindings,

        Viewport,
        ViewportBoundsRange,
        ViewportIndexProvokingVertex,
        ViewportSubpixelBits,

        MaxElementIndex,

        Count
    };

    ENUM_COUNT(Constant);

    enum class BufferType : uint8_t
    {
        ArrayBuffer,
        AtomicCounterBuffer,
        CopyReadBuffer,
        CopyWriteBuffer,
        DispatchIndirectBuffer,
        DrawIndirectBuffer,
        ElementArrayBuffer,
        PixelPackBuffer,
        PixelUnpackBuffer,
        QueryBuffer,
        ShaderStorageBuffer,
        TextureBuffer,
        TransformFeedbackBuffer,
        UniformBuffer,

        Count
    };

    ENUM_COUNT(BufferType);

    enum class BufferUsage : uint8_t
    {
        StreamDraw,
        StreamRead,
        StreamCopy,
        StaticDraw,
        StaticRead,
        StaticCopy,
        DynamicDraw,
        DynamicRead,
        DynamicCopy,

        Count
    };

    ENUM_COUNT(BufferUsage);

    enum class BufferStorageFlags : uint16_t
    {
        None            = 0,

        MapRead         = 0x001,
        MapWrite        = 0x002,

        MapPersistent   = 0x040,
        MapCoherent     = 0x080,

        DynamicStorage  = 0x100,
        ClientStorage   = 0x200
    };

    enum class MemoryBarrierFlags : uint16_t
    {
        None                        = 0,

        VertexAttribArrayBarrier    = 1 << 0,
        ElementArrayBarrier         = 1 << 1,
        UniformBarrier              = 1 << 2,
        TextureFetchBarrier         = 1 << 3,

        // For some reason, the OpenGL bit values skip the 1 << 4 or 0x10 value

        ShaderImageAccessBarrier    = 1 << 5,
        CommandBarrier              = 1 << 6,
        PixelBufferBarrier          = 1 << 7,
        TextureUpdateBarrier        = 1 << 8,
        BufferUpdateBarrier         = 1 << 9,
        FramebufferBarrier          = 1 << 10,
        TransformFeedbackBarrier    = 1 << 11,
        AtomicCounterBarrier        = 1 << 12,
        ShaderStorageBarrier        = 1 << 13
    };

    enum class DrawMode : uint8_t
    {
        Points,
        LineStrip,
        LineLoop,
        Lines,
        LineStripAdjacency,
        LinesAdjacency,
        TriangleStrip,
        TriangleFan,
        Triangles,
        TriangleStripAdjacency,
        TrianglesAdjacency,
        Patches,

        Count
    };

    ENUM_COUNT(DrawMode);

    enum class ClearFlags : uint16_t
    {
        None            = 0,

        DepthBuffer     = 0x0100,
        StencilBuffer   = 0x0400,
        ColorBuffer     = 0x4000
    };

    template <typename T>
    concept OpenGlConvertibleT = Meta::IsAny<
        T,
        MagnificationFilter,
        Wrapping,
        ShaderType,
        InternalFormat,
        Format,
        DataType,
        Constant,
        BufferType,
        BufferUsage,
        DrawMode
    >;

    MOUNTAIN_API void BindImage(uint32_t textureId, uint32_t shaderBinding, ImageShaderAccess access);

    MOUNTAIN_API void SetActiveTexture(uint8_t activeTexture);

    MOUNTAIN_API void SynchronizeGpuData(GpuDataSynchronizationType dataType);

    MOUNTAIN_API void MemoryBarrier(MemoryBarrierFlags flags);

    MOUNTAIN_API void DrawArrays(DrawMode mode, int32_t first, int32_t count);
    MOUNTAIN_API void DrawArraysInstanced(DrawMode mode, int32_t first, int32_t count, int32_t instanceCount);
    MOUNTAIN_API void DrawElements(DrawMode mode, int32_t count, DataType type, const void* indices);
    MOUNTAIN_API void DrawElementsInstanced(DrawMode mode, int32_t count, DataType type, const void* indices, int32_t instanceCount);

    MOUNTAIN_API void SetClearColor(const Color& newClearColor);
    MOUNTAIN_API void Clear(ClearFlags flags);

    MOUNTAIN_API void BindTexture(uint32_t textureId);
    MOUNTAIN_API void BindTexture(GpuTexture gpuTexture);

    MOUNTAIN_API void BindBuffer(BufferType type, uint32_t bufferId);
    MOUNTAIN_API void BindBuffer(BufferType type, GpuBuffer gpuBuffer);

    MOUNTAIN_API void BindBufferBase(BufferType type, uint32_t index, GpuBuffer gpuBuffer);
    MOUNTAIN_API void BindBufferBase(BufferType type, uint32_t index, uint32_t bufferId);

    MOUNTAIN_API void BindVertexArray(uint32_t vertexArrayId);
    MOUNTAIN_API void BindVertexArray(GpuVertexArray gpuVertexArray);

    MOUNTAIN_API void SetVertexAttribute(uint32_t index, int32_t size, int32_t stride, size_t offset, uint32_t divisor = 0);
    MOUNTAIN_API void SetVertexAttributeInt(uint32_t index, int32_t size, int32_t stride, size_t offset, uint32_t divisor = 0);

    template <OpenGlConvertibleT T>
    // ReSharper disable once CppFunctionIsNotImplemented
    T FromOpenGl(int32_t value);
    template <>
    MOUNTAIN_API MagnificationFilter FromOpenGl<MagnificationFilter>(int32_t value);
    template <>
    MOUNTAIN_API Wrapping FromOpenGl<Wrapping>(int32_t value);
    template <>
    MOUNTAIN_API ShaderType FromOpenGl<ShaderType>(int32_t value);
    template <>
    MOUNTAIN_API InternalFormat FromOpenGl<InternalFormat>(int32_t value);
    template <>
    MOUNTAIN_API Format FromOpenGl<Format>(int32_t value);
    template <>
    MOUNTAIN_API DataType FromOpenGl<DataType>(int32_t value);
    template <>
    MOUNTAIN_API Constant FromOpenGl<Constant>(int32_t value);
    template <>
    MOUNTAIN_API BufferType FromOpenGl<BufferType>(int32_t value);
    template <>
    MOUNTAIN_API BufferUsage FromOpenGl<BufferUsage>(int32_t value);
    template <>
    MOUNTAIN_API DrawMode FromOpenGl<DrawMode>(int32_t value);

    MOUNTAIN_API int32_t ToOpenGl(MagnificationFilter value);
    MOUNTAIN_API int32_t ToOpenGl(Wrapping value);
    MOUNTAIN_API int32_t ToOpenGl(ShaderType value);
    MOUNTAIN_API int32_t ToOpenGl(InternalFormat value);
    MOUNTAIN_API int32_t ToOpenGl(Format value);
    MOUNTAIN_API int32_t ToOpenGl(DataType value);
    MOUNTAIN_API int32_t ToOpenGl(Constant value);
    MOUNTAIN_API int32_t ToOpenGl(BufferType value);
    MOUNTAIN_API int32_t ToOpenGl(BufferUsage value);
    MOUNTAIN_API int32_t ToOpenGl(DrawMode value);
}

ENUM_FLAGS(Mountain::Graphics::GpuDataSynchronizationType);

ENUM_FLAGS(Mountain::Graphics::BufferStorageFlags);

ENUM_FLAGS(Mountain::Graphics::MemoryBarrierFlags);

ENUM_FLAGS(Mountain::Graphics::ClearFlags);
