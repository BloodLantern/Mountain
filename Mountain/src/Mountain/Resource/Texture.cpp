module;

#include <stb_image.h>

module Mountain:Resource_Texture;
import :Resource_Texture;

import :Utils;
import :Rendering_Graphics;
import :Rendering_GpuTexture;

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
    m_GpuTexture.Create();
    m_GpuTexture.SetDebugName(m_Name);

    m_GpuTexture.SetMinFilter(m_Filter);
    m_GpuTexture.SetMagFilter(m_Filter);

    m_GpuTexture.SetWrappingHorizontal(Graphics::Wrapping::ClampToEdge);
    m_GpuTexture.SetWrappingVertical(Graphics::Wrapping::ClampToEdge);

    m_GpuTexture.SetStorage(Graphics::InternalFormat::RedGreenBlueAlpha32Float, m_Size);
    if (m_Data)
        m_GpuTexture.SetSubData(Vector2i::Zero(), m_Size, Graphics::Format::RedGreenBlueAlpha, Graphics::DataType::UnsignedByte, m_Data);

    m_Loaded = true;
}

void Texture::Unload()
{
    m_GpuTexture.Delete();

    m_Loaded = false;
}

void Texture::ResetSourceData()
{
    m_Data = nullptr;
    m_Size = Vector2i::Zero();

    m_SourceDataSet = false;
}

Vector2i Texture::GetSize() const { return m_Size; }

void Texture::SetSize(const Vector2i newSize)
{
    if (m_Loaded)
        throw std::logic_error{ "Texture::SetSize cannot be called once the Texture has been loaded" };
    m_Size = newSize;
}

Graphics::MagnificationFilter Texture::GetFilter() const { return m_Filter; }

void Texture::SetFilter(const Graphics::MagnificationFilter newFilter)
{
    if (m_Loaded)
    {
        m_GpuTexture.SetMinFilter(newFilter);
        m_GpuTexture.SetMagFilter(newFilter);

        m_GpuTexture.SetWrappingHorizontal(Graphics::Wrapping::ClampToEdge);
        m_GpuTexture.SetWrappingVertical(Graphics::Wrapping::ClampToEdge);
    }

    m_Filter = newFilter;
}

void Texture::Use() const { Graphics::BindTexture(m_GpuTexture); }

// ReSharper disable once CppMemberFunctionMayBeStatic
void Texture::Unuse() const { Graphics::BindTexture(0); }

uint32_t Texture::GetId() const { return m_GpuTexture.GetId(); }

Graphics::GpuTexture Texture::GetGpuTexture() const { return m_GpuTexture; }
