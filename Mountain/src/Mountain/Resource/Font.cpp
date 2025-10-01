#include "Mountain/PrecompiledHeader.hpp"

#include "Mountain/Resource/Font.hpp"

#include <algorithm>
#include <ranges>

#include <glad/glad.h>

#include <ft2build.h>

#include "Mountain/Graphics/Renderer.hpp"
#include "Mountain/Utils/Logger.hpp"

#include FT_FREETYPE_H

using namespace Mountain;

Font::~Font()
{
    if (m_Loaded)
        Font::Unload();

    if (m_SourceDataSet)
        Font::ResetSourceData();
}

bool_t Font::SetSourceData(const Pointer<File>& file, const uint32_t size)
{
    if (m_SourceDataSet)
        return false;

    Resource::SetSourceData(file);

    m_Size = size;
    Load();

    m_SourceDataSet = true;

    return true;
}

void Font::ResetSourceData()
{
    if (!m_SourceDataSet)
        return;

    Unload();
    m_Size = 0;

    m_SourceDataSet = false;
}

Vector2 Font::CalcTextSize(const std::string_view text) const
{
    Vector2 result;

    for (const char_t c : text)
    {
        const Character& character = m_Characters.at(c);

        result.x += static_cast<float_t>(character.advance >> 6);

        result.y = std::max(static_cast<float_t>(character.size.y), result.y);
    }

    return result;
}

void Font::Load()
{
    if (m_Loaded)
        return;

    FT_Face face = nullptr;
    if (FT_New_Memory_Face(Renderer::m_Freetype, m_File->GetData<uint8_t>(), static_cast<FT_Long>(m_File->GetSize()), 0, &face))
    {
        Logger::LogError("Failed to load Font {}", m_Name);
        return;
    }

    FT_Set_Pixel_Sizes(face, 0, m_Size);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    for (uint8_t c = 0; c < 128; c++)
    {
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            Logger::LogError("Failed to load glyph {} ({:X}) in Font {}", c, c, m_Name);
            continue;
        }

        const Vector2i glyphSize = Vector2i(static_cast<int32_t>(face->glyph->bitmap.width), static_cast<int32_t>(face->glyph->bitmap.rows));

        Character character {
            .size = glyphSize,
            .bearing = { face->glyph->bitmap_left, face->glyph->bitmap_top },
            .advance = static_cast<uint32_t>(face->glyph->advance.x)
        };

        if (glyphSize != Vector2i::Zero())
        {
            character.texture.Create();
            character.texture.SetStorage(Graphics::InternalFormat::Red8, glyphSize);
            character.texture.SetSubData(Vector2i::Zero(), glyphSize, Graphics::Format::Red, Graphics::DataType::UnsignedByte, face->glyph->bitmap.buffer);
            character.texture.SetMinFilter(Graphics::MagnificationFilter::Linear);
            character.texture.SetMagFilter(Graphics::MagnificationFilter::Linear);
            character.texture.SetWrappingHorizontal(Graphics::Wrapping::ClampToEdge);
            character.texture.SetWrappingVertical(Graphics::Wrapping::ClampToEdge);
        }

        m_Characters.emplace(c, character);
    }

    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

    FT_Done_Face(face);

    m_Loaded = true;
}

void Font::Unload()
{
    for (auto&& character : m_Characters | std::views::values)
        character.texture.Delete();

    m_Loaded = false;
}
