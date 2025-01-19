#pragma once

#include "Mountain/core.hpp"

#include <magic_enum/magic_enum.hpp>

#include "Mountain/utils/meta_programming.hpp"

namespace Mountain
{
    struct GpuTexture;
}

/// @namespace Mountain::Graphics
/// @brief Low-level graphics interface
///
/// You should only use this if you know what you are doing and/or have experience with graphics APIs such as OpenGL.
namespace Mountain::Graphics
{
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

    template <typename T>
    concept OpenGlConvertibleT = Meta::IsAny<T, MagnificationFilter, Wrapping, ShaderType, InternalFormat, Format, DataType>;

    MOUNTAIN_API void BindImage(uint32_t textureId, uint32_t shaderBinding, ImageShaderAccess access);

    MOUNTAIN_API void SynchronizeGpuData(GpuDataSynchronizationType dataType);

    MOUNTAIN_API void BindTexture(uint32_t textureId);
    MOUNTAIN_API void BindTexture(GpuTexture gpuTexture);

    template <OpenGlConvertibleT T>
    T FromOpenGl(int32_t value);
    template <>
    MOUNTAIN_API MagnificationFilter FromOpenGl<MagnificationFilter>(int32_t filter);
    template <>
    MOUNTAIN_API Wrapping FromOpenGl<Wrapping>(int32_t wrapping);
    template <>
    MOUNTAIN_API ShaderType FromOpenGl<ShaderType>(int32_t shaderType);
    template <>
    MOUNTAIN_API InternalFormat FromOpenGl<InternalFormat>(int32_t internalFormat);
    template <>
    MOUNTAIN_API Format FromOpenGl<Format>(int32_t format);
    template <>
    MOUNTAIN_API DataType FromOpenGl<DataType>(int32_t dataType);

    template <OpenGlConvertibleT T>
    int32_t ToOpenGl(T value);
    template <>
    MOUNTAIN_API int32_t ToOpenGl<MagnificationFilter>(MagnificationFilter filter);
    template <>
    MOUNTAIN_API int32_t ToOpenGl<Wrapping>(Wrapping wrapping);
    template <>
    MOUNTAIN_API int32_t ToOpenGl<ShaderType>(ShaderType shaderType);
    template <>
    MOUNTAIN_API int32_t ToOpenGl<InternalFormat>(InternalFormat internalFormat);
    template <>
    MOUNTAIN_API int32_t ToOpenGl<Format>(Format format);
    template <>
    MOUNTAIN_API int32_t ToOpenGl<DataType>(DataType dataType);
}

ENUM_FLAGS(Mountain::Graphics::GpuDataSynchronizationType);
