#include "Mountain/Rendering/GpuTexture.hpp"

#include <glad/glad.h>

using namespace Mountain::Graphics;

void GpuTexture::Create() { glCreateTextures(GL_TEXTURE_2D, 1, &m_Id); }

void GpuTexture::Delete() { glDeleteTextures(1, &m_Id); m_Id = 0; }

void GpuTexture::Recreate() { Delete(); Create(); }

void GpuTexture::CreateViewFrom(
    const uint32_t originalTextureId,
    const InternalFormat newInternalFormat,
    const uint32_t minMipmapLevel,
    const uint32_t mipmapLevels
)
{
    glGenTextures(1, &m_Id);
    glTextureView(m_Id, GL_TEXTURE_2D, originalTextureId, ToOpenGl(newInternalFormat), minMipmapLevel, mipmapLevels, 0, 1);
}

void GpuTexture::CreateViewFrom(
    const GpuTexture originalGpuTexture,
    const InternalFormat newInternalFormat,
    const uint32_t minMipmapLevel,
    const uint32_t mipmapLevels
)
{
    CreateViewFrom(originalGpuTexture.m_Id, newInternalFormat, minMipmapLevel, mipmapLevels);
}

void GpuTexture::SetStorage(const InternalFormat internalFormat, const Vector2i size, const int32_t mipmapLevels) const
{
    glTextureStorage2D(m_Id, mipmapLevels, ToOpenGl(internalFormat), size.x, size.y);
}

void GpuTexture::SetSubData(
    const Vector2i offset,
    const Vector2i size,
    const Format dataFormat,
    const DataType dataType,
    const void* data,
    const int32_t mipmapLevel
) const
{
    glTextureSubImage2D(m_Id, mipmapLevel, offset.x, offset.y, size.x, size.y, ToOpenGl(dataFormat), ToOpenGl(dataType), data); }

void GpuTexture::SetData(
    const InternalFormat internalFormat,
    const Vector2i size,
    const Format dataFormat,
    const DataType dataType,
    const void* data,
    const int32_t mipmapLevel
) const
{
    BindTexture(m_Id);
    glTexImage2D(GL_TEXTURE_2D, mipmapLevel, ToOpenGl(internalFormat), size.x, size.y, 0, ToOpenGl(dataFormat), ToOpenGl(dataType), data);
    BindTexture(0);
}

void GpuTexture::GenerateMipmap() const { glGenerateTextureMipmap(m_Id); }

void GpuTexture::SetDebugName(ATTRIBUTE_MAYBE_UNUSED const std::string_view name) const
{
#ifdef _DEBUG
    glObjectLabel(GL_TEXTURE, m_Id, static_cast<GLsizei>(name.length()), name.data());
#endif
}

bool_t GpuTexture::GetImmutable() const
{
    GLint result;
    glGetTextureParameteriv(m_Id, GL_TEXTURE_IMMUTABLE_FORMAT, &result);
    return result;
}

MagnificationFilter GpuTexture::GetMinFilter() const
{
    GLint result;
    glGetTextureParameteriv(m_Id, GL_TEXTURE_MIN_FILTER, &result);
    return Graphics::FromOpenGl<MagnificationFilter>(result);
}

void GpuTexture::SetMinFilter(const MagnificationFilter newMinFilter) const
{
    glTextureParameteri(m_Id, GL_TEXTURE_MIN_FILTER, ToOpenGl(newMinFilter));
}

MagnificationFilter GpuTexture::GetMagFilter() const
{
    GLint result;
    glGetTextureParameteriv(m_Id, GL_TEXTURE_MAG_FILTER, &result);
    return Graphics::FromOpenGl<MagnificationFilter>(result);
}

void GpuTexture::SetMagFilter(const MagnificationFilter newMagFilter) const
{
    glTextureParameteri(m_Id, GL_TEXTURE_MAG_FILTER, ToOpenGl(newMagFilter));
}

Wrapping GpuTexture::GetWrappingHorizontal() const
{
    GLint result;
    glGetTextureParameteriv(m_Id, GL_TEXTURE_WRAP_S, &result);
    return Graphics::FromOpenGl<Wrapping>(result);
}

void GpuTexture::SetWrappingHorizontal(const Wrapping newWrappingHorizontal) const
{
    glTextureParameteri(m_Id, GL_TEXTURE_WRAP_S, ToOpenGl(newWrappingHorizontal));
}

Wrapping GpuTexture::GetWrappingVertical() const
{
    GLint result;
    glGetTextureParameteriv(m_Id, GL_TEXTURE_WRAP_T, &result);
    return Graphics::FromOpenGl<Wrapping>(result);
}

void GpuTexture::SetWrappingVertical(const Wrapping newWrappingVertical) const
{
    glTextureParameteri(m_Id, GL_TEXTURE_WRAP_T, ToOpenGl(newWrappingVertical));
}

Mountain::Color GpuTexture::GetBorderColor() const
{
    GLfloat result[4];
    glGetTextureParameterfv(m_Id, GL_TEXTURE_BORDER_COLOR, result);
    return Color{result};
}

void GpuTexture::SetBorderColor(Color newBorderColor) const
{
    glTextureParameterfv(m_Id, GL_TEXTURE_BORDER_COLOR, newBorderColor.Data());
}

uint32_t GpuTexture::GetId() const { return m_Id; }

GpuTexture::operator unsigned int() const { return m_Id; }
