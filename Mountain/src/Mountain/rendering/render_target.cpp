#include "Mountain/rendering/render_target.hpp"

#include <array>

#include <glad/glad.h>

#include "Mountain/window.hpp"
#include "Mountain/rendering/draw.hpp"
#include "Mountain/scene/component/light_source.hpp"
#include "Mountain/utils/logger.hpp"

using namespace Mountain;

// ReSharper disable once CppPossiblyUninitializedMember
RenderTarget::RenderTarget(const Vector2i size, const MagnificationFilter filter) { Initialize(size, filter); }

RenderTarget::~RenderTarget() { Reset(); }

void RenderTarget::Use() const
{
    if (!m_Initialized)
        throw std::logic_error("Cannot use an uninitialized RenderTarget");
    
    glBindFramebuffer(GL_FRAMEBUFFER, m_Framebuffer);
    glViewport(0, 0, m_Size.x, m_Size.y);
    
    Draw::SetProjectionMatrix(m_Projection);
    UpdateDrawCamera();
}

void RenderTarget::UpdateDrawCamera() const { Draw::SetCamera(m_CameraMatrix, m_CameraScale); }

void RenderTarget::Initialize(const Vector2i size, const MagnificationFilter filter)
{
    if (m_Initialized)
        return;
    
    m_Size = size;
    m_Projection = ComputeProjection(size);
    
    // Color Texture
    
    glCreateTextures(GL_TEXTURE_2D, 1, &m_Texture);

    const int32_t magFilter = ToOpenGl(filter);
    glTextureParameteri(m_Texture, GL_TEXTURE_MIN_FILTER, magFilter);
    glTextureParameteri(m_Texture, GL_TEXTURE_MAG_FILTER, magFilter);
    
    glTextureParameteri(m_Texture, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTextureParameteri(m_Texture, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glBindTexture(GL_TEXTURE_2D, m_Texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
    glBindTexture(GL_TEXTURE_2D, 0);

    // Framebuffer
    
    glCreateFramebuffers(1, &m_Framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, m_Framebuffer);
    
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_Texture, 0);

    // Draw buffers

    glCreateBuffers(1, &m_Vbo);
    glCreateVertexArrays(1, &m_Vao);
    
    glBindVertexArray(m_Vao);

    // VBO

    static constexpr std::array VertexData = {
        // pos          // UVs
        -1.f, -1.f,     0.f, 0.f,
         1.f, -1.f,     1.f, 0.f,
         1.f,  1.f,     1.f, 1.f,
        -1.f,  1.f,     0.f, 1.f
    };
    
    glNamedBufferData(m_Vbo, sizeof(VertexData), VertexData.data(), GL_STATIC_DRAW);

    // VAO
    
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(float_t) * 4, nullptr);
    glEnableVertexAttribArray(0);
    
    glBindVertexArray(0);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        Logger::LogError("Incomplete framebuffer after RenderTarget creation");
    
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    m_Initialized = true;
}

void RenderTarget::Reset()
{
    if (!m_Initialized)
        return;
    
    m_Size = Vector2i::Zero();
    m_Projection = Matrix::Identity();
    
    glDeleteVertexArrays(1, &m_Vao);
    glDeleteBuffers(1, &m_Vbo);
    glDeleteFramebuffers(1, &m_Framebuffer);
    glDeleteTextures(1, &m_Texture);
    
    m_Initialized = false;
}

void RenderTarget::Reset(const Vector2i newSize, const MagnificationFilter newFilter)
{
    Reset();
    Initialize(newSize, newFilter);
}

LightSource& RenderTarget::NewLightSource()
{
    m_LightSources.Emplace();
    return m_LightSources.Back();
}

void RenderTarget::DeleteLightSource(const LightSource& lightSource)
{
    for (size_t i = 0; i < m_LightSources.GetSize(); ++i)
    {
        if (&m_LightSources[i] == &lightSource)
        {
            m_LightSources.RemoveAt(i);
            return;
        }
    }
}

void RenderTarget::ClearLightSources() { m_LightSources.Clear(); }

const List<LightSource>& RenderTarget::GetLightSources() const { return m_LightSources; }

void RenderTarget::SetDebugName([[maybe_unused]] const std::string_view name) const
{
#ifdef _DEBUG
    glObjectLabel(GL_TEXTURE, m_Texture, static_cast<GLsizei>(name.length()), name.data());
    glObjectLabel(GL_FRAMEBUFFER, m_Framebuffer, static_cast<GLsizei>(name.length()), name.data());
    glObjectLabel(GL_BUFFER, m_Vbo, static_cast<GLsizei>(name.length()), name.data());
    glObjectLabel(GL_VERTEX_ARRAY, m_Vao, static_cast<GLsizei>(name.length()), name.data());
#endif
}

uint32_t RenderTarget::GetTextureId() const { return m_Texture; }

bool_t RenderTarget::GetInitialized() const { return m_Initialized; }

Vector2i RenderTarget::GetSize() const { return m_Size; }

void RenderTarget::SetSize(const Vector2i newSize)
{
    if (!m_Initialized)
        throw std::logic_error("Cannot set the size of an uninitialized RenderTarget");

    glBindTexture(GL_TEXTURE_2D, m_Texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, newSize.x, newSize.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
    glBindTexture(GL_TEXTURE_2D, 0);

    glBindFramebuffer(GL_FRAMEBUFFER, m_Framebuffer);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_Texture, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    
    m_Size = newSize;
    m_Projection = ComputeProjection(newSize);
}

MagnificationFilter RenderTarget::GetFilter() const
{
    return m_Filter;
}

void RenderTarget::SetFilter(const MagnificationFilter newFilter)
{
    if (!m_Initialized)
        throw std::logic_error("Cannot set the filter of an uninitialized RenderTarget");
    
    glBindTexture(GL_TEXTURE_2D, m_Texture);

    const int32_t magFilter = ToOpenGl(newFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, magFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    
    glBindTexture(GL_TEXTURE_2D, 0);
    
    m_Filter = newFilter;
}

const Matrix& RenderTarget::GetCameraMatrix() const { return m_CameraMatrix; }

void RenderTarget::SetCameraMatrix(const Matrix& newCameraMatrix)
{
    m_CameraMatrix = newCameraMatrix;

    // Find the scaling applied by the matrix
    const Vector2 a = m_CameraMatrix * -Vector2::One();
    const Vector2 b = m_CameraMatrix * Vector2(1.f, -1.f);
    const Vector2 c = m_CameraMatrix * Vector2::One();
    m_CameraScale = { (b - a).Length() * 0.5f, (c - b).Length() * 0.5f };

    // Update the Draw class fields only if this RenderTarget is the current one
    GLint framebuffer;
    glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &framebuffer);
    if (framebuffer == static_cast<GLint>(m_Framebuffer))
        UpdateDrawCamera();
}

const Vector2& RenderTarget::GetCameraScale() const { return m_CameraScale; }

int32_t RenderTarget::ToOpenGl(const MagnificationFilter filter)
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
