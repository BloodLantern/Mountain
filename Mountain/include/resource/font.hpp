#pragma once

#include <array>
#include <map>

#include "core.hpp"
#include "texture.hpp"
#include "resource/resource.hpp"

BEGIN_MOUNTAIN

/// @brief Holds the necessary information to draw text using a Font.
class Font : public Resource
{
public:
    /// @brief Allowed extensions for font files
    MOUNTAIN_API static constexpr std::array<const char_t*, 1> FileExtensions
    {
        ".ttf"
    };

    DEFAULT_COPY_MOVE_OPERATIONS(Font)

    // Same constructor from base class
    using Resource::Resource;
    
    MOUNTAIN_API ~Font() override;
    
    MOUNTAIN_API bool_t Load(const Pointer<File>& file, uint32_t size);  // NOLINT(clang-diagnostic-overloaded-virtual)

    MOUNTAIN_API void Unload() override;

    MOUNTAIN_API float_t CalcTextSize(std::string_view text, float_t scale = 1.f) const;

private:
    struct Character
    {
        uint32_t textureId;
        Vector2i size;       // Size of glyph
        Vector2i bearing;    // Offset from baseline to left/top of glyph
        uint32_t advance;
    };

    std::map<char_t, Character> m_Characters;

    uint32_t m_Size = 0;
    
    void CreateInInterface() override;
    
    void DestroyInInterface() override;

    friend class Draw;
};

END_MOUNTAIN

