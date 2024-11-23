#include "Mountain/resource/font.hpp"

#include <ranges>

#include <glad/glad.h>

#include <ft2build.h>

#include "Mountain/rendering/renderer.hpp"
#include "Mountain/utils/logger.hpp"

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
        
        if (static_cast<float_t>(character.size.y) > result.y)
            result.y = static_cast<float_t>(character.size.y);
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
            Logger::LogError("Failed to load Glyph in Font {}", m_Name);
            continue;
        }

        const Vector2i glyphSize = Vector2i(static_cast<int32_t>(face->glyph->bitmap.width), static_cast<int32_t>(face->glyph->bitmap.rows));

        Character character {
            .size = glyphSize,
            .bearing = { face->glyph->bitmap_left, face->glyph->bitmap_top },
            .advance = static_cast<uint32_t>(face->glyph->advance.x)
        };
        
        glGenTextures(1, &character.textureId);
        glBindTexture(GL_TEXTURE_2D, character.textureId);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            glyphSize.x,
            glyphSize.y,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer
        );
        // set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        m_Characters.emplace(c, character);
    }
    
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

    FT_Done_Face(face);
    
    m_Loaded = true;
}

void Font::Unload()
{
    for (auto&& character : m_Characters | std::views::values)
        glDeleteTextures(1, &character.textureId);

    m_Loaded = false;
}
