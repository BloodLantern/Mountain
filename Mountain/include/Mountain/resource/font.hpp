#pragma once

#include <array>
#include <map>

#include <Maths/vector2i.hpp>

#include "Mountain/core.hpp"
#include "Mountain/rendering/gpu_texture.hpp"
#include "Mountain/resource/resource.hpp"

namespace Mountain
{
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

        /// This also loads the font
        MOUNTAIN_API bool_t SetSourceData(const Pointer<File>& file, uint32_t size);  // NOLINT(clang-diagnostic-overloaded-virtual)

        /// This also unloads the font
        MOUNTAIN_API void ResetSourceData() override;

        MOUNTAIN_API Vector2 CalcTextSize(std::string_view text) const;

    private:
        struct Character
        {
            Graphics::GpuTexture texture{};
            Vector2i size;       // Size of glyph
            Vector2i bearing;    // Offset from baseline to left/top of glyph
            uint32_t advance;
        };

        std::map<char_t, Character> m_Characters;

        uint32_t m_Size = 0;

        void Load() override;

        void Unload() override;

        friend class Draw;
    };
}

