#include "Mountain/rendering/gpu_texture.hpp"

#include <glad/glad.h>

using namespace Mountain;

void GpuTexture::Create() { glCreateTextures(GL_TEXTURE_2D, 1, &m_Id); }

void GpuTexture::Delete() { glDeleteTextures(1, &m_Id); }

void GpuTexture::CreateFrom(
    uint32_t originalTextureId,
    Graphics::InternalFormat newInternalFormat,
    uint32_t minMipmapLevel,
    uint32_t mipmapLevels
)
{
    glGenTextures(1, &m_Id);
    glTextureView(m_Id, GL_TEXTURE_2D, originalTextureId, ToOpenGl(newInternalFormat), minMipmapLevel, mipmapLevels, 0, 1);
}

void GpuTexture::CreateFrom(
    GpuTexture originalGpuTexture,
    Graphics::InternalFormat newInternalFormat,
    uint32_t minMipmapLevel,
    uint32_t mipmapLevels
)
{
    CreateFrom(originalGpuTexture.m_Id, newInternalFormat, minMipmapLevel, mipmapLevels);
}

void GpuTexture::SetStorage(Graphics::InternalFormat internalFormat, Vector2i size, int32_t mipmapLevels) const
{
    glTextureStorage2D(m_Id, mipmapLevels, ToOpenGl(internalFormat), size.x, size.y);
}

void GpuTexture::SetSubData(
    Vector2i offset,
    Vector2i size,
    Graphics::Format dataFormat,
    Graphics::DataType dataType,
    const void* data,
    int32_t mipmapLevel
) const
{
    glTextureSubImage2D(m_Id, mipmapLevel, offset.x, offset.y, size.x, size.y, ToOpenGl(dataFormat), ToOpenGl(dataType), data); }

void GpuTexture::SetData(
    Graphics::InternalFormat internalFormat,
    Vector2i size,
    Graphics::Format dataFormat,
    Graphics::DataType dataType,
    const void* data,
    int32_t mipmapLevel
) const
{
    Graphics::BindTexture(m_Id);
    glTexImage2D(GL_TEXTURE_2D, mipmapLevel, ToOpenGl(internalFormat), size.x, size.y, 0, ToOpenGl(dataFormat), ToOpenGl(dataType), data);
    Graphics::BindTexture(0);
}

void GpuTexture::GenerateMipmap() const { glGenerateTextureMipmap(m_Id); }

void GpuTexture::SetDebugName(std::string_view name) const
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

Graphics::MagnificationFilter GpuTexture::GetMinFilter() const
{
    GLint result;
    glGetTextureParameteriv(m_Id, GL_TEXTURE_MIN_FILTER, &result);
    return Graphics::FromOpenGl<Graphics::MagnificationFilter>(result);
}

void GpuTexture::SetMinFilter(Graphics::MagnificationFilter newMinFilter)
{
    glTextureParameteri(m_Id, GL_TEXTURE_MIN_FILTER, ToOpenGl(newMinFilter));
}

Graphics::MagnificationFilter GpuTexture::GetMagFilter() const
{
    GLint result;
    glGetTextureParameteriv(m_Id, GL_TEXTURE_MAG_FILTER, &result);
    return Graphics::FromOpenGl<Graphics::MagnificationFilter>(result);
}

void GpuTexture::SetMagFilter(Graphics::MagnificationFilter newMagFilter)
{
    glTextureParameteri(m_Id, GL_TEXTURE_MAG_FILTER, ToOpenGl(newMagFilter));
}

Graphics::Wrapping GpuTexture::GetWrappingHorizontal() const
{
    GLint result;
    glGetTextureParameteriv(m_Id, GL_TEXTURE_WRAP_S, &result);
    return Graphics::FromOpenGl<Graphics::Wrapping>(result);
}

void GpuTexture::SetWrappingHorizontal(Graphics::Wrapping newWrappingHorizontal)
{
    glTextureParameteri(m_Id, GL_TEXTURE_WRAP_S, ToOpenGl(newWrappingHorizontal));
}

Graphics::Wrapping GpuTexture::GetWrappingVertical() const
{
    GLint result;
    glGetTextureParameteriv(m_Id, GL_TEXTURE_WRAP_T, &result);
    return Graphics::FromOpenGl<Graphics::Wrapping>(result);
}

void GpuTexture::SetWrappingVertical(Graphics::Wrapping newWrappingVertical)
{
    glTextureParameteri(m_Id, GL_TEXTURE_WRAP_T, ToOpenGl(newWrappingVertical));
}

Color GpuTexture::GetBorderColor() const
{
    GLfloat result[4];
    glGetTextureParameterfv(m_Id, GL_TEXTURE_BORDER_COLOR, result);
    return Color{result};
}

void GpuTexture::SetBorderColor(Color newBorderColor)
{
    glTextureParameterfv(m_Id, GL_TEXTURE_BORDER_COLOR, newBorderColor.Data());
}

uint32_t GpuTexture::GetId() const { return m_Id; }
