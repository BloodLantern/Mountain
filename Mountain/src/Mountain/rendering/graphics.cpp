#include "Mountain/rendering/graphics.hpp"

#include <stdexcept>

#include <glad/glad.h>

#include "Mountain/rendering/gpu_texture.hpp"

using namespace Mountain;

void Graphics::BindImage(const uint32_t textureId, const uint32_t shaderBinding, const ImageShaderAccess access)
{
    glBindImageTexture(shaderBinding, textureId, 0, GL_FALSE, 0, GL_READ_ONLY + static_cast<int32_t>(access), GL_RGBA32F);
}

void Graphics::SynchronizeGpuData(const GpuDataSynchronizationType dataType)
{
    if (dataType == GpuDataSynchronizationType::None)
        return;

    glMemoryBarrier(static_cast<GLbitfield>(dataType));
}

void Graphics::BindTexture(uint32_t textureId)
{
    glBindTexture(GL_TEXTURE_2D, textureId);
}

void Graphics::BindTexture(GpuTexture gpuTexture)
{
    BindTexture(gpuTexture.GetId());
}

template <>
Graphics::MagnificationFilter Graphics::FromOpenGl<Graphics::MagnificationFilter>(const int32_t filter)
{
    switch (filter)
    {
        case GL_NEAREST: return MagnificationFilter::Nearest;
        case GL_LINEAR: return MagnificationFilter::Linear;
    }

    throw std::invalid_argument("Invalid magnification filter");
}

template <>
Graphics::Wrapping Graphics::FromOpenGl<Graphics::Wrapping>(const int32_t wrapping)
{
    switch (wrapping)
    {
        case GL_REPEAT: return Wrapping::Repeat;
        case GL_MIRRORED_REPEAT: return Wrapping::MirroredRepeat;
        case GL_CLAMP_TO_EDGE: return Wrapping::ClampToEdge;
        case GL_CLAMP_TO_BORDER: return Wrapping::ClampToBorder;
    }

    throw std::invalid_argument("Invalid wrapping");
}

template <>
Graphics::ShaderType Graphics::FromOpenGl<Graphics::ShaderType>(const int32_t shaderType)
{
    switch (shaderType)
    {
        case GL_VERTEX_SHADER: return ShaderType::Vertex;
        case GL_FRAGMENT_SHADER: return ShaderType::Fragment;
    }

    throw std::invalid_argument("Invalid shader type");
}

template <>
Graphics::InternalFormat Graphics::FromOpenGl<Graphics::InternalFormat>(const int32_t internalFormat)
{
    switch (internalFormat)
    {
        case GL_R8: return InternalFormat::Red8;
        case GL_R8_SNORM: return InternalFormat::Red8Signed;
        case GL_R16: return InternalFormat::Red16;
        case GL_R16_SNORM: return InternalFormat::Red16Signed;
        case GL_RG8: return InternalFormat::RedGreen8;
        case GL_RG8_SNORM: return InternalFormat::RedGreen8Signed;
        case GL_RG16: return InternalFormat::RedGreen16;
        case GL_RG16_SNORM: return InternalFormat::RedGreen16Signed;
        case GL_R3_G3_B2: return InternalFormat::Red3Green3Blue2;
        case GL_RGB4: return InternalFormat::RedGreenBlue4;
        case GL_RGB5: return InternalFormat::RedGreenBlue5;
        case GL_RGB8: return InternalFormat::RedGreenBlue8;
        case GL_RGB8_SNORM: return InternalFormat::RedGreenBlue8Signed;
        case GL_RGB10: return InternalFormat::RedGreenBlue10;
        case GL_RGB12: return InternalFormat::RedGreenBlue12;
        case GL_RGB16: return InternalFormat::RedGreenBlue16;
        case GL_RGB16_SNORM: return InternalFormat::RedGreenBlue16Signed;
        case GL_RGBA2: return InternalFormat::RedGreenBlueAlpha2;
        case GL_RGBA4: return InternalFormat::RedGreenBlueAlpha4;
        case GL_RGB5_A1: return InternalFormat::RedGreenBlue5Alpha1;
        case GL_RGBA8: return InternalFormat::RedGreenBlueAlpha8;
        case GL_RGBA8_SNORM: return InternalFormat::RedGreenBlueAlpha8Signed;
        case GL_RGB10_A2: return InternalFormat::RedGreenBlue10Alpha2;
        case GL_RGB10_A2UI: return InternalFormat::RedGreenBlue10Alpha2UnsignedInt;
        case GL_RGBA12: return InternalFormat::RedGreenBlueAlpha12;
        case GL_RGBA16: return InternalFormat::RedGreenBlueAlpha16;
        case GL_SRGB8: return InternalFormat::SignedRedGreenBlue8;
        case GL_SRGB8_ALPHA8: return InternalFormat::SignedRedGreenBlueAlpha8;
        case GL_R16F: return InternalFormat::Red16Float;
        case GL_RG16F: return InternalFormat::RedGreen16Float;
        case GL_RGB16F: return InternalFormat::RedGreenBlue16Float;
        case GL_RGBA16F: return InternalFormat::RedGreenBlueAlpha16Float;
        case GL_R32F: return InternalFormat::Red32Float;
        case GL_RG32F: return InternalFormat::RedGreen32Float;
        case GL_RGB32F: return InternalFormat::RedGreenBlue32Float;
        case GL_RGBA32F: return InternalFormat::RedGreenBlueAlpha32Float;
        case GL_R11F_G11F_B10F: return InternalFormat::Red11FloatGreen11FloatBlue10Float;
        case GL_RGB9_E5: return InternalFormat::RedGreenBlue9Shared5;
        case GL_R8I: return InternalFormat::Red8Int;
        case GL_R8UI: return InternalFormat::Red8UnsignedInt;
        case GL_R16I: return InternalFormat::Red16Int;
        case GL_R16UI: return InternalFormat::Red16UnsignedInt;
        case GL_R32I: return InternalFormat::Red32Int;
        case GL_R32UI: return InternalFormat::Red32UnsignedInt;
        case GL_RG8I: return InternalFormat::RedGreen8Int;
        case GL_RG8UI: return InternalFormat::RedGreen8UnsignedInt;
        case GL_RG16I: return InternalFormat::RedGreen16Int;
        case GL_RG16UI: return InternalFormat::RedGreen16UnsignedInt;
        case GL_RG32I: return InternalFormat::RedGreen32Int;
        case GL_RG32UI: return InternalFormat::RedGreen32UnsignedInt;
        case GL_RGB8I: return InternalFormat::RedGreenBlue8Int;
        case GL_RGB8UI: return InternalFormat::RedGreenBlue8UnsignedInt;
        case GL_RGB16I: return InternalFormat::RedGreenBlue16Int;
        case GL_RGB16UI: return InternalFormat::RedGreenBlue16UnsignedInt;
        case GL_RGB32I: return InternalFormat::RedGreenBlue32Int;
        case GL_RGB32UI: return InternalFormat::RedGreenBlue32UnsignedInt;
        case GL_RGBA8I: return InternalFormat::RedGreenBlueAlpha8Int;
        case GL_RGBA8UI: return InternalFormat::RedGreenBlueAlpha8UnsignedInt;
        case GL_RGBA16I: return InternalFormat::RedGreenBlueAlpha16Int;
        case GL_RGBA16UI: return InternalFormat::RedGreenBlueAlpha16UnsignedInt;
        case GL_RGBA32I: return InternalFormat::RedGreenBlueAlpha32Int;
        case GL_RGBA32UI: return InternalFormat::RedGreenBlueAlpha32UnsignedInt;
    }

    throw std::invalid_argument("Invalid internal format");
}

template <>
Graphics::Format Graphics::FromOpenGl<Graphics::Format>(const int32_t format)
{
    switch (format)
    {
        case GL_RED: return Format::Red;
        case GL_RG: return Format::RedGreen;
        case GL_RGB: return Format::RedGreenBlue;
        case GL_BGR: return Format::BlueGreenRed;
        case GL_RGBA: return Format::RedGreenBlueAlpha;
        case GL_BGRA: return Format::BlueGreenRedAlpha;
    }

    throw std::invalid_argument("Invalid format");
}

template <>
Graphics::DataType Graphics::FromOpenGl<Graphics::DataType>(const int32_t dataType)
{
    switch (dataType)
    {
        case GL_UNSIGNED_BYTE: return DataType::UnsignedByte;
        case GL_BYTE: return DataType::Byte;
        case GL_UNSIGNED_SHORT: return DataType::UnsignedShort;
        case GL_SHORT: return DataType::Short;
        case GL_UNSIGNED_INT: return DataType::UnsignedInt;
        case GL_INT: return DataType::Int;
        case GL_FLOAT: return DataType::Float;

        case GL_UNSIGNED_BYTE_3_3_2: return DataType::UnsignedByte_3_3_2;
        case GL_UNSIGNED_BYTE_2_3_3_REV: return DataType::UnsignedByte_2_3_3_Reverse;

        case GL_UNSIGNED_SHORT_5_6_5: return DataType::UnsignedShort_5_6_5;
        case GL_UNSIGNED_SHORT_5_6_5_REV: return DataType::UnsignedShort_5_6_5_Reverse;
        case GL_UNSIGNED_SHORT_4_4_4_4: return DataType::UnsignedShort_4_4_4_4;
        case GL_UNSIGNED_SHORT_4_4_4_4_REV: return DataType::UnsignedShort_4_4_4_4_Reverse;
        case GL_UNSIGNED_SHORT_5_5_5_1: return DataType::UnsignedShort_5_5_5_1;
        case GL_UNSIGNED_SHORT_1_5_5_5_REV: return DataType::UnsignedShort_1_5_5_5_Reverse;

        case GL_UNSIGNED_INT_8_8_8_8: return DataType::UnsignedInt_8_8_8_8;
        case GL_UNSIGNED_INT_8_8_8_8_REV: return DataType::UnsignedInt_8_8_8_8_Reverse;
        case GL_UNSIGNED_INT_10_10_10_2: return DataType::UnsignedInt_10_10_10_2;
        case GL_UNSIGNED_INT_2_10_10_10_REV: return DataType::UnsignedInt_2_10_10_10_Reverse;
    }

    throw std::invalid_argument("Invalid data type");
}

template <>
int32_t Graphics::ToOpenGl<Graphics::MagnificationFilter>(const MagnificationFilter filter)
{
    switch (filter)
    {
        case MagnificationFilter::Nearest: return GL_NEAREST;
        case MagnificationFilter::Linear: return GL_LINEAR;

        case MagnificationFilter::Count: throw std::invalid_argument("Invalid magnification filter");
    }

    throw std::invalid_argument("Invalid magnification filter");
}

template <>
int32_t Graphics::ToOpenGl<Graphics::Wrapping>(const Wrapping wrapping)
{
    switch (wrapping)
    {
        case Wrapping::Repeat: return GL_REPEAT;
        case Wrapping::MirroredRepeat: return GL_MIRRORED_REPEAT;
        case Wrapping::ClampToEdge: return GL_CLAMP_TO_EDGE;
        case Wrapping::ClampToBorder: return GL_CLAMP_TO_BORDER;

        case Wrapping::Count: throw std::invalid_argument("Invalid wrapping");
    }

    throw std::invalid_argument("Invalid wrapping");
}

template <>
int32_t Graphics::ToOpenGl<Graphics::ShaderType>(const ShaderType shaderType)
{
    switch (shaderType)
    {
        case ShaderType::Vertex: return GL_VERTEX_SHADER;
        case ShaderType::Fragment: return GL_FRAGMENT_SHADER;

        case ShaderType::Count: throw std::invalid_argument("Invalid shader type");
    }

    throw std::invalid_argument("Invalid shader type");
}

template <>
int32_t Graphics::ToOpenGl<Graphics::InternalFormat>(const InternalFormat internalFormat)
{
    switch (internalFormat)
    {
        case InternalFormat::Red8: return GL_R8;
        case InternalFormat::Red8Signed: return GL_R8_SNORM;
        case InternalFormat::Red16: return GL_R16;
        case InternalFormat::Red16Signed: return GL_R16_SNORM;
        case InternalFormat::RedGreen8: return GL_RG8;
        case InternalFormat::RedGreen8Signed: return GL_RG8_SNORM;
        case InternalFormat::RedGreen16: return GL_RG16;
        case InternalFormat::RedGreen16Signed: return GL_RG16_SNORM;
        case InternalFormat::Red3Green3Blue2: return GL_R3_G3_B2;
        case InternalFormat::RedGreenBlue4: return GL_RGB4;
        case InternalFormat::RedGreenBlue5: return GL_RGB5;
        case InternalFormat::RedGreenBlue8: return GL_RGB8;
        case InternalFormat::RedGreenBlue8Signed: return GL_RGB8_SNORM;
        case InternalFormat::RedGreenBlue10: return GL_RGB10;
        case InternalFormat::RedGreenBlue12: return GL_RGB12;
        case InternalFormat::RedGreenBlue16: return GL_RGB16;
        case InternalFormat::RedGreenBlue16Signed: return GL_RGB16_SNORM;
        case InternalFormat::RedGreenBlueAlpha2: return GL_RGBA2;
        case InternalFormat::RedGreenBlueAlpha4: return GL_RGBA4;
        case InternalFormat::RedGreenBlue5Alpha1: return GL_RGB5_A1;
        case InternalFormat::RedGreenBlueAlpha8: return GL_RGBA8;
        case InternalFormat::RedGreenBlueAlpha8Signed: return GL_RGBA8_SNORM;
        case InternalFormat::RedGreenBlue10Alpha2: return GL_RGB10_A2;
        case InternalFormat::RedGreenBlue10Alpha2UnsignedInt: return GL_RGB10_A2UI;
        case InternalFormat::RedGreenBlueAlpha12: return GL_RGBA12;
        case InternalFormat::RedGreenBlueAlpha16: return GL_RGBA16;
        case InternalFormat::SignedRedGreenBlue8: return GL_SRGB8;
        case InternalFormat::SignedRedGreenBlueAlpha8: return GL_SRGB8_ALPHA8;
        case InternalFormat::Red16Float: return GL_R16F;
        case InternalFormat::RedGreen16Float: return GL_RG16F;
        case InternalFormat::RedGreenBlue16Float: return GL_RGB16F;
        case InternalFormat::RedGreenBlueAlpha16Float: return GL_RGBA16F;
        case InternalFormat::Red32Float: return GL_R32F;
        case InternalFormat::RedGreen32Float: return GL_RG32F;
        case InternalFormat::RedGreenBlue32Float: return GL_RGB32F;
        case InternalFormat::RedGreenBlueAlpha32Float: return GL_RGBA32F;
        case InternalFormat::Red11FloatGreen11FloatBlue10Float: return GL_R11F_G11F_B10F;
        case InternalFormat::RedGreenBlue9Shared5: return GL_RGB9_E5;
        case InternalFormat::Red8Int: return GL_R8I;
        case InternalFormat::Red8UnsignedInt: return GL_R8UI;
        case InternalFormat::Red16Int: return GL_R16I;
        case InternalFormat::Red16UnsignedInt: return GL_R16UI;
        case InternalFormat::Red32Int: return GL_R32I;
        case InternalFormat::Red32UnsignedInt: return GL_R32UI;
        case InternalFormat::RedGreen8Int: return GL_RG8I;
        case InternalFormat::RedGreen8UnsignedInt: return GL_RG8UI;
        case InternalFormat::RedGreen16Int: return GL_RG16I;
        case InternalFormat::RedGreen16UnsignedInt: return GL_RG16UI;
        case InternalFormat::RedGreen32Int: return GL_RG32I;
        case InternalFormat::RedGreen32UnsignedInt: return GL_RG32UI;
        case InternalFormat::RedGreenBlue8Int: return GL_RGB8I;
        case InternalFormat::RedGreenBlue8UnsignedInt: return GL_RGB8UI;
        case InternalFormat::RedGreenBlue16Int: return GL_RGB16I;
        case InternalFormat::RedGreenBlue16UnsignedInt: return GL_RGB16UI;
        case InternalFormat::RedGreenBlue32Int: return GL_RGB32I;
        case InternalFormat::RedGreenBlue32UnsignedInt: return GL_RGB32UI;
        case InternalFormat::RedGreenBlueAlpha8Int: return GL_RGBA8I;
        case InternalFormat::RedGreenBlueAlpha8UnsignedInt: return GL_RGBA8UI;
        case InternalFormat::RedGreenBlueAlpha16Int: return GL_RGBA16I;
        case InternalFormat::RedGreenBlueAlpha16UnsignedInt: return GL_RGBA16UI;
        case InternalFormat::RedGreenBlueAlpha32Int: return GL_RGBA32I;
        case InternalFormat::RedGreenBlueAlpha32UnsignedInt: return GL_RGBA32UI;

        case InternalFormat::Count: throw std::invalid_argument("Invalid internal format");
    }

    throw std::invalid_argument("Invalid internal format");
}

template <>
int32_t Graphics::ToOpenGl<Graphics::Format>(const Format format)
{
    switch (format)
    {
        case Format::Red: return GL_RED;
        case Format::RedGreen: return GL_RG;
        case Format::RedGreenBlue: return GL_RGB;
        case Format::BlueGreenRed: return GL_BGR;
        case Format::RedGreenBlueAlpha: return GL_RGBA;
        case Format::BlueGreenRedAlpha: return GL_BGRA;

        case Format::Count: throw std::invalid_argument("Invalid format");
    }

    throw std::invalid_argument("Invalid format");
}

template <>
int32_t Graphics::ToOpenGl<Graphics::DataType>(const DataType dataType)
{
    switch (dataType)
    {
        case DataType::UnsignedByte: return GL_UNSIGNED_BYTE;
        case DataType::Byte: return GL_BYTE;
        case DataType::UnsignedShort: return GL_UNSIGNED_SHORT;
        case DataType::Short: return GL_SHORT;
        case DataType::UnsignedInt: return GL_UNSIGNED_INT;
        case DataType::Int: return GL_INT;
        case DataType::Float: return GL_FLOAT;

        case DataType::UnsignedByte_3_3_2: return GL_UNSIGNED_BYTE_3_3_2;
        case DataType::UnsignedByte_2_3_3_Reverse: return GL_UNSIGNED_BYTE_2_3_3_REV;

        case DataType::UnsignedShort_5_6_5: return GL_UNSIGNED_SHORT_5_6_5;
        case DataType::UnsignedShort_5_6_5_Reverse: return GL_UNSIGNED_SHORT_5_6_5_REV;
        case DataType::UnsignedShort_4_4_4_4: return GL_UNSIGNED_SHORT_4_4_4_4;
        case DataType::UnsignedShort_4_4_4_4_Reverse: return GL_UNSIGNED_SHORT_4_4_4_4_REV;
        case DataType::UnsignedShort_5_5_5_1: return GL_UNSIGNED_SHORT_5_5_5_1;
        case DataType::UnsignedShort_1_5_5_5_Reverse: return GL_UNSIGNED_SHORT_1_5_5_5_REV;

        case DataType::UnsignedInt_8_8_8_8: return GL_UNSIGNED_INT_8_8_8_8;
        case DataType::UnsignedInt_8_8_8_8_Reverse: return GL_UNSIGNED_INT_8_8_8_8_REV;
        case DataType::UnsignedInt_10_10_10_2: return GL_UNSIGNED_INT_10_10_10_2;
        case DataType::UnsignedInt_2_10_10_10_Reverse: return GL_UNSIGNED_INT_2_10_10_10_REV;

        case DataType::Count: throw std::invalid_argument("Invalid data type");
    }

    throw std::invalid_argument("Invalid data type");
}
