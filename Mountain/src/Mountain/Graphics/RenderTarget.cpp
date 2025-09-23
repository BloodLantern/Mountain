#include "Mountain/PrecompiledHeader.hpp"

#include "Mountain/Graphics/RenderTarget.hpp"

#include "Mountain/Window.hpp"
#include "Mountain/Graphics/Draw.hpp"
#include "Mountain/Utils/Logger.hpp"

using namespace Mountain;

RenderTarget::RenderTarget(const Vector2i size, const Graphics::MagnificationFilter filter) { Initialize(size, filter); }

RenderTarget::~RenderTarget() { Reset(); }

void RenderTarget::Use() const
{
    if (!m_Initialized)
        THROW(InvalidOperationException{"Cannot use an uninitialized RenderTarget"});

    BindFramebuffer(Graphics::FramebufferType::Framebuffer, m_Framebuffer);
    Graphics::SetViewport(Vector2i::Zero(), m_Size);

    Draw::SetProjectionMatrix(m_Projection, false);
    UpdateDrawCamera();
}

void RenderTarget::UpdateDrawCamera() const { Draw::SetCamera(m_CameraMatrix, m_CameraScale, true); }

void RenderTarget::Initialize(const Vector2i size, const Graphics::MagnificationFilter filter)
{
    if (m_Initialized)
        return;

    m_Size = size;
    m_Projection = ComputeProjection(size);

    // Color Texture

    m_Texture.Create();
    m_Texture.SetMinFilter(filter);
    m_Texture.SetMagFilter(filter);
    m_Texture.SetWrappingHorizontal(Graphics::Wrapping::ClampToEdge);
    m_Texture.SetWrappingVertical(Graphics::Wrapping::ClampToEdge);

    m_Texture.SetData(
        Graphics::InternalFormat::RedGreenBlueAlpha32Float,
        size,
        Graphics::Format::RedGreenBlueAlpha,
        Graphics::DataType::UnsignedByte,
        nullptr
    );

    // Framebuffer

    m_Framebuffer.Create();
    m_Framebuffer.SetTexture(m_Texture, Graphics::FramebufferAttachment::Color0, 0);

    if (m_Framebuffer.CheckStatus(Graphics::FramebufferType::Framebuffer) != Graphics::FramebufferStatus::Complete)
        Logger::LogError("Incomplete framebuffer after RenderTarget creation");
    else
        m_Initialized = true;
}

void RenderTarget::Reset()
{
    if (!m_Initialized)
        return;

    m_Size = Vector2i::Zero();
    m_Projection = Matrix::Identity();

    m_Framebuffer.Delete();
    m_Texture.Delete();

    m_Initialized = false;
}

void RenderTarget::Reset(const Vector2i newSize, const Graphics::MagnificationFilter newFilter)
{
    Reset();
    Initialize(newSize, newFilter);
}

LightSource& RenderTarget::NewLightSource() { return m_LightSources.Emplace(); }

void RenderTarget::DeleteLightSource(const LightSource& lightSource)
{
    for (size_t i = 0; i < m_LightSources.GetSize(); ++i)
    {
        if (&m_LightSources[i] != &lightSource)
            continue;

        m_LightSources.RemoveAt(i);
        return;
    }
}

void RenderTarget::ClearLightSources() { m_LightSources.Clear(); }

void RenderTarget::SetDebugName(ATTRIBUTE_MAYBE_UNUSED const std::string_view name) const
{
#ifdef _DEBUG
    const std::string str{name.data(), name.length()};
    m_Framebuffer.SetDebugName(str + " Framebuffer");
    m_Texture.SetDebugName(str + " Texture");
#endif
}

void RenderTarget::SetSize(const Vector2i newSize)
{
    if (!m_Initialized)
        THROW(InvalidOperationException{"Cannot set the size of an uninitialized RenderTarget"});

    m_Texture.SetData(
        Graphics::InternalFormat::RedGreenBlueAlpha32Float,
        newSize,
        Graphics::Format::RedGreenBlueAlpha,
        Graphics::DataType::UnsignedByte,
        nullptr
    );
    m_Framebuffer.SetTexture(m_Texture.GetId(), Graphics::FramebufferAttachment::Color0);

    m_Size = newSize;
    m_Projection = ComputeProjection(newSize);
}

void RenderTarget::SetFilter(const Graphics::MagnificationFilter newFilter)
{
    if (!m_Initialized)
        THROW(InvalidOperationException{"Cannot set the magnification filter of an uninitialized RenderTarget"});

    m_Texture.SetMinFilter(newFilter);
    m_Texture.SetMagFilter(newFilter);
    m_Texture.SetWrappingHorizontal(Graphics::Wrapping::ClampToEdge);
    m_Texture.SetWrappingVertical(Graphics::Wrapping::ClampToEdge);

    m_Filter = newFilter;
}

void RenderTarget::SetCameraMatrix(const Matrix& newCameraMatrix)
{
    m_CameraMatrix = newCameraMatrix;

    // Find the scaling applied by the matrix
    const Vector2 a = m_CameraMatrix * -Vector2::One();
    const Vector2 b = m_CameraMatrix * Vector2{1.f, -1.f};
    const Vector2 c = m_CameraMatrix * Vector2::One();
    m_CameraScale = { (b - a).Length() * 0.5f, (c - b).Length() * 0.5f };

    // Update the Draw class fields only if this RenderTarget is the current one
    int32_t framebuffer;
    Graphics::GetConstant(Graphics::Constant::DrawFramebufferBinding, &framebuffer);
    if (static_cast<uint32_t>(framebuffer) == m_Framebuffer.GetId())
        UpdateDrawCamera();
}

Matrix RenderTarget::ComputeProjection(const Vector2i size)
{
    return Matrix::Orthographic(0.f, static_cast<float_t>(size.x), static_cast<float_t>(size.y), 0.f, -1000.f, 1000.f);
}
