#include "Mountain/rendering/render_target.hpp"

#include <array>

#include <glad/glad.h>

#include "Mountain/window.hpp"
#include "Mountain/rendering/draw.hpp"
#include "Mountain/utils/logger.hpp"

using namespace Mountain;

// ReSharper disable once CppPossiblyUninitializedMember
RenderTarget::RenderTarget(const Vector2i size, const MagnificationFilter filter)
    : m_Size(size)
    , m_Projection(ComputeProjection(size))
{
    // Color Texture
    
    glGenTextures(2, &m_Texture);
    glBindTexture(GL_TEXTURE_2D, m_Texture);

    const int32_t magFilter = MagnificationFilterToOpenGl(filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, magFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
    glBindTexture(GL_TEXTURE_2D, 0);

    // Framebuffer
    
    glGenFramebuffers(1, &m_Framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, m_Framebuffer);
    
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_Texture, 0);

    // Draw buffers

    glGenBuffers(1, &m_Vbo);
    glGenVertexArrays(1, &m_Vao);
    
    glBindVertexArray(m_Vao);

    // VBO

    static constexpr std::array VertexData = {
        // pos          // UVs
        -1.f, -1.f,     0.f, 0.f,
         1.f, -1.f,     1.f, 0.f,
         1.f,  1.f,     1.f, 1.f,
        -1.f,  1.f,     0.f, 1.f
    };
    
    glBindBuffer(GL_ARRAY_BUFFER, m_Vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(VertexData), VertexData.data(), GL_STATIC_DRAW);

    // VAO
    
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(float_t) * 4, nullptr);
    glEnableVertexAttribArray(0);
    
    glBindVertexArray(0);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        Logger::LogError("Incomplete framebuffer after RenderTarget creation");
    
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

RenderTarget::~RenderTarget()
{
    glDeleteVertexArrays(1, &m_Vao);
    glDeleteBuffers(1, &m_Vbo);
    glDeleteFramebuffers(1, &m_Framebuffer);
    glDeleteTextures(2, &m_Texture);
}

void RenderTarget::Use() const
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_Framebuffer);
    glViewport(0, 0, m_Size.x, m_Size.y);
    
    Draw::SetProjectionMatrix(m_Projection);
}

uint32_t RenderTarget::GetTextureId() const
{
    return m_Texture;
}

Vector2i RenderTarget::GetSize() const
{
    return m_Size;
}

void RenderTarget::SetSize(const Vector2i size)
{
    glBindTexture(GL_TEXTURE_2D, m_Texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
    glBindTexture(GL_TEXTURE_2D, 0);
    
    glBindFramebuffer(GL_FRAMEBUFFER, m_Framebuffer);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_Texture, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    
    m_Size = size;
    m_Projection = ComputeProjection(size);
}

MagnificationFilter RenderTarget::GetFilter() const
{
    return m_Filter;
}

void RenderTarget::SetFilter(const MagnificationFilter filter)
{
    glBindTexture(GL_TEXTURE_2D, m_Texture);

    const int32_t magFilter = MagnificationFilterToOpenGl(filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, magFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    
    glBindTexture(GL_TEXTURE_2D, 0);
    
    m_Filter = filter;
}

int32_t RenderTarget::MagnificationFilterToOpenGl(const MagnificationFilter filter)
{
    switch (filter)
    {
        case MagnificationFilter::Linear:
            return GL_LINEAR;
        
        case MagnificationFilter::Nearest:
            return GL_NEAREST;
        
        case MagnificationFilter::Count:
            throw std::invalid_argument("Invalid magnification filter");
    }
    
    throw std::invalid_argument("Invalid magnification filter");
}

Matrix RenderTarget::ComputeProjection(const Vector2i size)
{
    return Matrix::Orthographic(0.f, static_cast<float_t>(size.x), static_cast<float_t>(size.y), 0.f, -1000.f, 1000.f);
}
