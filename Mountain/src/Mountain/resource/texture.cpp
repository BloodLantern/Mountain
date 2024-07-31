#include "Mountain/resource/texture.hpp"

#include <glad/glad.h>

#include <stb_image.h>

#include "Mountain/utils/logger.hpp"

using namespace Mountain;

Texture::~Texture()
{
    if (m_Loaded)
        Texture::Unload();
    
    if (m_SourceDataSet)
        Texture::ResetSourceData();
}

bool_t Texture::SetSourceData(const uint8_t* const buffer, const int64_t length)
{
    m_Data = stbi_load_from_memory(buffer, static_cast<int32_t>(length), &m_Size.x, &m_Size.y, nullptr, STBI_rgb_alpha);
    
    m_SourceDataSet = true;

    return true;
}

void Texture::Load()
{
    glGenTextures(1, &m_Id);
    glBindTexture(GL_TEXTURE_2D, m_Id);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Size.x, m_Size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_Data);
    glBindTexture(GL_TEXTURE_2D, 0);
    
    m_Loaded = true;
}

void Texture::Unload()
{
    glDeleteTextures(1, &m_Id);
    
    m_Loaded = false;
}

void Texture::ResetSourceData()
{
    m_Data = nullptr;
    m_Size = Vector2i::Zero();
    
    m_SourceDataSet = false;
}

Vector2i Texture::GetSize() const
{
    return m_Size;
}

void Texture::Use() const
{
    glBindTexture(GL_TEXTURE_2D, m_Id);
}

// ReSharper disable once CppMemberFunctionMayBeStatic
void Texture::Unuse() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

uint32_t Texture::GetId() const
{
    return m_Id;
}
