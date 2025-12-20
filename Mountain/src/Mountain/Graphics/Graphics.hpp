#pragma once

#include "Mountain/Core.hpp"

#include <magic_enum/magic_enum.hpp>

#include "Mountain/Utils/MetaProgramming.hpp"
#include "Mountain/Utils/Utils.hpp"

/// @namespace Mountain::Graphics
/// @brief Low-level graphics API
///
/// You should only use this if you know what you are doing and/or have experience with graphics APIs such as OpenGL.
namespace Mountain::Graphics
{
    struct GpuFramebuffer;
    struct GpuVertexArray;
    struct GpuBuffer;
    struct GpuTexture;

#pragma region Enums
    enum class ImageShaderAccess : u8
    {
        ReadOnly,
        WriteOnly,
        ReadWrite
    };

    enum class GpuDataSynchronizationFlags : u16
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
        QueryBuffer        = 1 << 15,

        All                = 0xFFFF
    };

    enum class MagnificationFilter : u8
    {
        Nearest,
        Linear
    };

    enum class Wrapping : u8
    {
        Repeat,
        MirroredRepeat,
        ClampToEdge,
        ClampToBorder
    };

    enum class ShaderType : u8
    {
        Vertex,
        Fragment,
        Geometry
    };

    enum class InternalFormat : u8
    {
        DepthComponent,
        DepthStencil,
        Red,
        RedGreen,
        RedGreenBlue,
        RedGreenBlueAlpha,

        DepthComponent16,
        DepthComponent24,
        DepthComponent32Float,

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
        RedGreenBlueAlpha32UnsignedInt
    };

    enum class Format : u8
    {
        Red,
        RedGreen,
        RedGreenBlue,
        BlueGreenRed,
        RedGreenBlueAlpha,
        BlueGreenRedAlpha,

        DepthComponent
    };

    enum class DataType : u8
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
        UnsignedInt_2_10_10_10_Reverse
        // ReSharper restore CppInconsistentNaming
    };

    enum class Constant : u8
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

        MaxElementIndex
    };

    enum class BufferType : u8
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
        UniformBuffer
    };

    /// @brief Defines the intended usage of a buffer.
    /// @details The frequency of access may be one of these:
    /// - @c Stream: The data store contents will be modified once and used at most a few times.
    /// - @c Static: The data store contents will be modified once and used many times.
    /// - @c Dynamic: The data store contents will be modified repeatedly and used many times.
    /// @details The nature of access may be one of these:
    /// - @c Draw: The data store contents are modified by the application, and used as the source for GL drawing and image specification commands.
    /// - @c Read: The data store contents are modified by reading data from the GL, and used to return that data when queried by the application.
    /// - @c Copy: The data store contents are modified by reading data from the GL, and used as the source for GL drawing and image specification commands.
    enum class BufferUsage : u8
    {
        StreamDraw,
        StreamRead,
        StreamCopy,
        StaticDraw,
        StaticRead,
        StaticCopy,
        DynamicDraw,
        DynamicRead,
        DynamicCopy
    };

    enum class BufferStorageFlags : u16
    {
        None            = 0,

        MapRead         = 0x001,
        MapWrite        = 0x002,

        MapPersistent   = 0x040,
        MapCoherent     = 0x080,

        DynamicStorage  = 0x100,
        ClientStorage   = 0x200
    };

    enum class MemoryBarrierFlags : u16
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

    enum class DrawMode : u8
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
        Patches
    };

    enum class ClearFlags : u16
    {
        None            = 0,

        DepthBuffer     = 0x0100,
        StencilBuffer   = 0x0400,
        ColorBuffer     = 0x4000
    };

    enum class BlendFunction : u8
    {
        Zero,
        One,
        SrcColor,
        OneMinusSrcColor,
        DstColor,
        OneMinusDstColor,
        SrcAlpha,
        OneMinusSrcAlpha,
        DstAlpha,
        OneMinusDstAlpha,
        ConstantColor,
        OneMinusConstantColor,
        ConstantAlpha,
        OneMinusConstantAlpha
    };

    enum class FramebufferType : u8
    {
        DrawFramebuffer,
        ReadFramebuffer,
        Framebuffer
    };

    enum class FramebufferStatus : u8
    {
        /// @brief The framebuffer is ready to be used.
        Complete,
        /// @brief The specified framebuffer is the default read or draw framebuffer, but the default framebuffer does not exist.
        Undefined,
        /// @brief At least one of the framebuffer attachment points are framebuffer incomplete.
        IncompleteAttachment,
        /// @brief The framebuffer does not have at least one image attached to it.
        IncompleteMissingAttachment,
        IncompleteDrawBuffer,
        IncompleteReadBuffer,
        /// @brief The combination of internal formats of the attached images violates an implementation-dependent set of restrictions.
        Unsupported,
        IncompleteMultisample,
        IncompleteLayerTargets
    };

    enum class FramebufferAttachment : u8
    {
        Color0,
        Color1,
        Color2,
        Color3,
        Color4,
        Color5,
        Color6,
        Color7,
        Color8,
        Color9,
        Color10,
        Color11,
        Color12,
        Color13,
        Color14,
        Color15,
        Color16,
        Color17,
        Color18,
        Color19,
        Color20,
        Color21,
        Color22,
        Color23,
        Color24,
        Color25,
        Color26,
        Color27,
        Color28,
        Color29,
        Color30,
        Color31,
        Depth,
        Stencil,
        DepthStencil
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
        DrawMode,
        BlendFunction,
        FramebufferType,
        FramebufferStatus,
        FramebufferAttachment
    >;
#pragma endregion

    MOUNTAIN_API void BindImage(u32 textureId, u32 shaderBinding, ImageShaderAccess access);

    MOUNTAIN_API void SetActiveTexture(u8 activeTexture);

    MOUNTAIN_API void SynchronizeGpuData(GpuDataSynchronizationFlags flags = GpuDataSynchronizationFlags::None);

    MOUNTAIN_API void MemoryBarrier(MemoryBarrierFlags flags = MemoryBarrierFlags::None);

    MOUNTAIN_API void DrawArrays(DrawMode mode, s32 first, s32 vertexCount);
    MOUNTAIN_API void DrawArraysInstanced(DrawMode mode, s32 first, s32 vertexCount, s32 instanceCount);
    MOUNTAIN_API void DrawElements(DrawMode mode, s32 vertexCount, DataType type, const void* indices);
    MOUNTAIN_API void DrawElementsInstanced(DrawMode mode, s32 vertexCount, DataType type, const void* indices, s32 instanceCount);

    MOUNTAIN_API void SetClearColor(const Color& newClearColor);
    MOUNTAIN_API void Clear(ClearFlags flags);

    MOUNTAIN_API void BindTexture(u32 textureId);
    MOUNTAIN_API void BindTexture(GpuTexture gpuTexture);

    MOUNTAIN_API void BindBuffer(BufferType type, u32 bufferId);
    MOUNTAIN_API void BindBuffer(BufferType type, GpuBuffer gpuBuffer);

    MOUNTAIN_API void BindBufferBase(BufferType type, u32 index, u32 bufferId);
    MOUNTAIN_API void BindBufferBase(BufferType type, u32 index, GpuBuffer gpuBuffer);

    MOUNTAIN_API void BindVertexArray(u32 vertexArrayId);
    MOUNTAIN_API void BindVertexArray(GpuVertexArray gpuVertexArray);

    MOUNTAIN_API void SetVertexAttribute(u32 index, s32 size, s32 stride, usize offset, u32 divisor = 0);
    MOUNTAIN_API void SetVertexAttributeInt(u32 index, s32 size, s32 stride, usize offset, u32 divisor = 0);

    MOUNTAIN_API void BindFramebuffer(FramebufferType type, u32 framebufferId);
    MOUNTAIN_API void BindFramebuffer(FramebufferType type, GpuFramebuffer gpuFramebuffer);

    /// @brief Copy data from one texture to another
    /// @param sourceTextureId The texture ID from which the data will get copied
    /// @param sourceMipmapLevel The mipmap level of the source texture to copy the data from
    /// @param sourceOffset The offset in the source texture to start copying from
    /// @param destinationTextureId The texture ID to which the data will get copied
    /// @param destinationOffset The offset in the destination texture to start copying to
    /// @param destinationMipmapLevel The mipmap level of the destination texture to copy the data to
    /// @param size The amount of data to copy
    MOUNTAIN_API void CopyTextureData(
        u32 sourceTextureId,
        s32 sourceMipmapLevel,
        Vector2i sourceOffset,
        u32 destinationTextureId,
        s32 destinationMipmapLevel,
        Vector2i destinationOffset,
        Vector2i size
    );

    ATTRIBUTE_NODISCARD
    s32 GetProgramUniformLocation(u32 shaderProgramId, const c8* uniformName);

    /// @brief Sets an int (signed, 32 bits) variable in a shader
    MOUNTAIN_API void SetProgramUniform(u32 shaderProgramId, const c8* uniformName, s32 value);
    /// @brief Sets an uint (unsigned, 32 bits) variable in a shader
    MOUNTAIN_API void SetProgramUniform(u32 shaderProgramId, const c8* uniformName, u32 value);
    /// @brief Sets a bool (signed, 32 bits) variable in a shader
    MOUNTAIN_API void SetProgramUniform(u32 shaderProgramId, const c8* uniformName, bool value);
    /// @brief Sets a float (32 bits) variable in a shader
    MOUNTAIN_API void SetProgramUniform(u32 shaderProgramId, const c8* uniformName, f32 value);
    /// @brief Sets a Vector2 (2 floats, 64 bits) variable in a shader
    MOUNTAIN_API void SetProgramUniform(u32 shaderProgramId, const c8* uniformName, Vector2i value);
    /// @brief Sets a Vector2 (2 floats, 64 bits) variable in a shader
    MOUNTAIN_API void SetProgramUniform(u32 shaderProgramId, const c8* uniformName, Vector2 value);
    /// @brief Sets a Vector3 (3 floats, 96 bits) variable in a shader
    MOUNTAIN_API void SetProgramUniform(u32 shaderProgramId, const c8* uniformName, const Vector3& value);
    /// @brief Sets a Vector4 (4 floats, 128 bits) variable in a shader
    MOUNTAIN_API void SetProgramUniform(u32 shaderProgramId, const c8* uniformName, const Vector4& value);
    /// @brief Sets a Color (4 floats, 128 bits) variable in a shader
    MOUNTAIN_API void SetProgramUniform(u32 shaderProgramId, const c8* uniformName, const Color& value);
    /// @brief Sets a Matrix2 (4 floats, 128 bits) variable in a shader
    MOUNTAIN_API void SetProgramUniform(u32 shaderProgramId, const c8* uniformName, const Matrix2& value);
    /// @brief Sets a Matrix3 (9 floats, 288 bits) variable in a shader
    MOUNTAIN_API void SetProgramUniform(u32 shaderProgramId, const c8* uniformName, const Matrix3& value);
    /// @brief Sets a Matrix (16 floats, 512 bits) variable in a shader
    MOUNTAIN_API void SetProgramUniform(u32 shaderProgramId, const c8* uniformName, const Matrix& value);

    /// @brief Sets an int (signed, 32 bits) variable in a shader
    MOUNTAIN_API void SetProgramUniform(u32 shaderProgramId, s32 uniformLocation, s32 value);
    /// @brief Sets an uint (unsigned, 32 bits) variable in a shader
    MOUNTAIN_API void SetProgramUniform(u32 shaderProgramId, s32 uniformLocation, u32 value);
    /// @brief Sets a bool (signed, 32 bits) variable in a shader
    MOUNTAIN_API void SetProgramUniform(u32 shaderProgramId, s32 uniformLocation, bool value);
    /// @brief Sets a float (32 bits) variable in a shader
    MOUNTAIN_API void SetProgramUniform(u32 shaderProgramId, s32 uniformLocation, f32 value);
    /// @brief Sets a Vector2 (2 floats, 64 bits) variable in a shader
    MOUNTAIN_API void SetProgramUniform(u32 shaderProgramId, s32 uniformLocation, Vector2i value);
    /// @brief Sets a Vector2 (2 floats, 64 bits) variable in a shader
    MOUNTAIN_API void SetProgramUniform(u32 shaderProgramId, s32 uniformLocation, Vector2 value);
    /// @brief Sets a Vector3 (3 floats, 96 bits) variable in a shader
    MOUNTAIN_API void SetProgramUniform(u32 shaderProgramId, s32 uniformLocation, const Vector3& value);
    /// @brief Sets a Vector4 (4 floats, 128 bits) variable in a shader
    MOUNTAIN_API void SetProgramUniform(u32 shaderProgramId, s32 uniformLocation, const Vector4& value);
    /// @brief Sets a Color (4 floats, 128 bits) variable in a shader
    MOUNTAIN_API void SetProgramUniform(u32 shaderProgramId, s32 uniformLocation, const Color& value);
    /// @brief Sets a Matrix2 (4 floats, 128 bits) variable in a shader
    MOUNTAIN_API void SetProgramUniform(u32 shaderProgramId, s32 uniformLocation, const Matrix2& value);
    /// @brief Sets a Matrix3 (9 floats, 288 bits) variable in a shader
    MOUNTAIN_API void SetProgramUniform(u32 shaderProgramId, s32 uniformLocation, const Matrix3& value);
    /// @brief Sets a Matrix (16 floats, 512 bits) variable in a shader
    MOUNTAIN_API void SetProgramUniform(u32 shaderProgramId, s32 uniformLocation, const Matrix& value);

    /// @brief Sets an enum (cast to a 32 bits unsigned integer) variable in a shader
    template <Concepts::Enum T>
    void SetProgramUniform(u32 shaderProgramId, const c8* uniformName, T value);

    MOUNTAIN_API void SetViewport(Vector2i position, Vector2i size);

    ATTRIBUTE_NODISCARD
    MOUNTAIN_API u32 GetLastError();
    ATTRIBUTE_NODISCARD
    MOUNTAIN_API const c8* GetLastErrorString();

    ATTRIBUTE_NODISCARD
    MOUNTAIN_API bool IsConstantEnabled(Constant constant);
    ATTRIBUTE_NODISCARD
    MOUNTAIN_API bool IsConstantEnabled(Constant constant, u32 index);

    MOUNTAIN_API void GetConstant(Constant constant, bool* outData);
    MOUNTAIN_API void GetConstant(Constant constant, f64* outData);
    MOUNTAIN_API void GetConstant(Constant constant, f32* outData);
    MOUNTAIN_API void GetConstant(Constant constant, s32* outData);
    MOUNTAIN_API void GetConstant(Constant constant, s64* outData);
    MOUNTAIN_API void GetConstant(Constant constant, u32 index, bool* outData);
    MOUNTAIN_API void GetConstant(Constant constant, u32 index, f64* outData);
    MOUNTAIN_API void GetConstant(Constant constant, u32 index, f32* outData);
    MOUNTAIN_API void GetConstant(Constant constant, u32 index, s32* outData);
    MOUNTAIN_API void GetConstant(Constant constant, u32 index, s64* outData);

    MOUNTAIN_API void SetConstantEnabled(Constant constant, bool enabled);
    MOUNTAIN_API void SetConstantEnabled(Constant constant, u32 index, bool enabled);
    MOUNTAIN_API void EnableConstant(Constant constant);
    MOUNTAIN_API void EnableConstant(Constant constant, u32 index);
    MOUNTAIN_API void DisableConstant(Constant constant);
    MOUNTAIN_API void DisableConstant(Constant constant, u32 index);

    MOUNTAIN_API void SetBlendFunction(BlendFunction sourceFactors, BlendFunction destinationFactors);
    MOUNTAIN_API void SetBlendFunction(u32 drawBuffer, BlendFunction sourceFactors, BlendFunction destinationFactors);

    MOUNTAIN_API void SetViewport(s32 x, s32 y, s32 width, s32 height);

    /// @brief Equivalent to @c glFlush().
    /// @warning This is different from @c Draw::Flush().
    MOUNTAIN_API void Flush();
    MOUNTAIN_API void Finish();

    template <OpenGlConvertibleT T>
    ATTRIBUTE_NODISCARD
    // ReSharper disable once CppFunctionIsNotImplemented
    T FromOpenGl(s32 value);
    template <>
    ATTRIBUTE_NODISCARD
    MOUNTAIN_API MagnificationFilter FromOpenGl<MagnificationFilter>(s32 value);
    template <>
    ATTRIBUTE_NODISCARD
    MOUNTAIN_API Wrapping FromOpenGl<Wrapping>(s32 value);
    template <>
    ATTRIBUTE_NODISCARD
    MOUNTAIN_API ShaderType FromOpenGl<ShaderType>(s32 value);
    template <>
    ATTRIBUTE_NODISCARD
    MOUNTAIN_API InternalFormat FromOpenGl<InternalFormat>(s32 value);
    template <>
    ATTRIBUTE_NODISCARD
    MOUNTAIN_API Format FromOpenGl<Format>(s32 value);
    template <>
    ATTRIBUTE_NODISCARD
    MOUNTAIN_API DataType FromOpenGl<DataType>(s32 value);
    template <>
    ATTRIBUTE_NODISCARD
    MOUNTAIN_API Constant FromOpenGl<Constant>(s32 value);
    template <>
    ATTRIBUTE_NODISCARD
    MOUNTAIN_API BufferType FromOpenGl<BufferType>(s32 value);
    template <>
    ATTRIBUTE_NODISCARD
    MOUNTAIN_API BufferUsage FromOpenGl<BufferUsage>(s32 value);
    template <>
    ATTRIBUTE_NODISCARD
    MOUNTAIN_API DrawMode FromOpenGl<DrawMode>(s32 value);
    template <>
    ATTRIBUTE_NODISCARD
    MOUNTAIN_API BlendFunction FromOpenGl<BlendFunction>(s32 value);
    template <>
    ATTRIBUTE_NODISCARD
    MOUNTAIN_API FramebufferType FromOpenGl<FramebufferType>(s32 value);
    template <>
    ATTRIBUTE_NODISCARD
    MOUNTAIN_API FramebufferStatus FromOpenGl<FramebufferStatus>(s32 value);
    template <>
    ATTRIBUTE_NODISCARD
    MOUNTAIN_API FramebufferAttachment FromOpenGl<FramebufferAttachment>(s32 value);

    ATTRIBUTE_NODISCARD
    MOUNTAIN_API s32 ToOpenGl(MagnificationFilter value);
    ATTRIBUTE_NODISCARD
    MOUNTAIN_API s32 ToOpenGl(Wrapping value);
    ATTRIBUTE_NODISCARD
    MOUNTAIN_API s32 ToOpenGl(ShaderType value);
    ATTRIBUTE_NODISCARD
    MOUNTAIN_API s32 ToOpenGl(InternalFormat value);
    ATTRIBUTE_NODISCARD
    MOUNTAIN_API s32 ToOpenGl(Format value);
    ATTRIBUTE_NODISCARD
    MOUNTAIN_API s32 ToOpenGl(DataType value);
    ATTRIBUTE_NODISCARD
    MOUNTAIN_API s32 ToOpenGl(Constant value);
    ATTRIBUTE_NODISCARD
    MOUNTAIN_API s32 ToOpenGl(BufferType value);
    ATTRIBUTE_NODISCARD
    MOUNTAIN_API s32 ToOpenGl(BufferUsage value);
    ATTRIBUTE_NODISCARD
    MOUNTAIN_API s32 ToOpenGl(DrawMode value);
    ATTRIBUTE_NODISCARD
    MOUNTAIN_API s32 ToOpenGl(BlendFunction value);
    ATTRIBUTE_NODISCARD
    MOUNTAIN_API s32 ToOpenGl(FramebufferType value);
    ATTRIBUTE_NODISCARD
    MOUNTAIN_API s32 ToOpenGl(FramebufferStatus value);
    ATTRIBUTE_NODISCARD
    MOUNTAIN_API s32 ToOpenGl(FramebufferAttachment value);
}

ENUM_FLAGS(Mountain::Graphics::GpuDataSynchronizationFlags);

ENUM_FLAGS(Mountain::Graphics::BufferStorageFlags);

ENUM_FLAGS(Mountain::Graphics::MemoryBarrierFlags);

ENUM_FLAGS(Mountain::Graphics::ClearFlags);

// Start of Graphics.inl

namespace Mountain::Graphics
{
    template <Concepts::Enum T>
    void SetProgramUniform(const u32 shaderProgramId, const c8* uniformName, const T value)
    {
        return SetProgramUniform(shaderProgramId, uniformName, static_cast<u32>(value));
    }
}
