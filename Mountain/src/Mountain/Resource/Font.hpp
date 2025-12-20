#pragma once

#include <array>
#include <map>

#include <Math/vector2i.hpp>

#include "Mountain/Core.hpp"
#include "Mountain/Graphics/GpuTexture.hpp"
#include "Mountain/Resource/Resource.hpp"

namespace Mountain
{
    /// @brief Holds the necessary information to draw text using a Font.
    class Font : public Resource
    {
    public:
        /// @brief Allowed extensions for font files
        MOUNTAIN_API static constexpr Array<const c8*, 1> FileExtensions
        {
            ".ttf"
        };

        DEFAULT_COPY_MOVE_OPERATIONS(Font)

        // Same constructor from base class
        using Resource::Resource;

        MOUNTAIN_API ~Font() override;

        /// This also loads the font
        MOUNTAIN_API bool SetSourceData(const Pointer<File>& file, u32 size);  // NOLINT(clang-diagnostic-overloaded-virtual)

        /// This also unloads the font
        MOUNTAIN_API void ResetSourceData() override;

        MOUNTAIN_API Vector2 CalcTextSize(std::string_view text) const;

    private:
        struct Character
        {
            Graphics::GpuTexture texture{};
            Vector2i size;       // Size of glyph
            Vector2i bearing;    // Offset from baseline to left/top of glyph
            u32 advance;
        };

        std::map<c8, Character> m_Characters;

        u32 m_Size = 0;

        void Load() override;

        void Unload() override;

        friend class Draw;
    };
}
