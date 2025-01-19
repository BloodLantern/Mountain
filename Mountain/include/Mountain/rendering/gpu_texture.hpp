#pragma once

#include <string_view>

#include <Maths/vector2i.hpp>

#include "Mountain/core.hpp"
#include "Mountain/rendering/graphics.hpp"
#include "Mountain/utils/color.hpp"

namespace Mountain
{
    /// @brief Low-level interface for OpenGL textures
    struct GpuTexture
    {
        /// @brief Create the texture on the GPU
        /// @see <a href="https://registry.khronos.org/OpenGL-Refpages/gl4/html/glCreateTextures.xhtml">glCreateTextures()</a>
        MOUNTAIN_API void Create();

        /// @brief Delete the texture on the GPU
        /// @see <a href="https://registry.khronos.org/OpenGL-Refpages/gl4/html/glDeleteTextures.xhtml">glDeleteTextures()</a>
        MOUNTAIN_API void Delete();

        /// @brief Shorthand for @code Delete(); Create();@endcode
        MOUNTAIN_API void Recreate();

        /// @brief Create the texture on the GPU from the given immutable texture
        /// @param originalTextureId The texture ID whose data is to be what this texture will view
        /// @param newInternalFormat The internal format for the newly created texture.
        /// This format must be compatible with the original texture format as per this <a href="https://www.khronos.org/opengl/wiki/Template:Glapi_view_format_map">table</a>.
        /// @param minMipmapLevel The starting mipmap level in the original texture to view
        /// @param mipmapLevels The number of mipmap levels of the original texture to view
        /// @details This creates a new texture that is a <a href="https://www.khronos.org/opengl/wiki/Texture_Storage#Texture_views">view</a> of the given original texture.
        /// @see <a href="https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGenTextures.xhtml">glGenTextures()</a>
        /// <a href="https://registry.khronos.org/OpenGL-Refpages/gl4/html/glTextureView.xhtml">glTextureView()</a>
        /// @note The original texture <b>must</b> be immutable
        MOUNTAIN_API void CreateFrom(uint32_t originalTextureId, Graphics::InternalFormat newInternalFormat, uint32_t minMipmapLevel, uint32_t mipmapLevels);

        /// @brief Create the texture on the GPU from the given immutable texture
        /// @param originalGpuTexture The texture whose data is to be what this texture will view
        /// @param newInternalFormat The internal format for the newly created texture.
        /// This format must be compatible with the original texture format as per this <a href="https://www.khronos.org/opengl/wiki/Template:Glapi_view_format_map">table</a>.
        /// @param minMipmapLevel The starting mipmap level in the original texture to view
        /// @param mipmapLevels The number of mipmap levels of the original texture to view
        /// @details This creates a new texture that is a <a href="https://www.khronos.org/opengl/wiki/Texture_Storage#Texture_views">view</a> of the given original texture.
        /// @see <a href="https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGenTextures.xhtml">glGenTextures()</a>
        /// <a href="https://registry.khronos.org/OpenGL-Refpages/gl4/html/glTextureView.xhtml">glTextureView()</a>
        /// @note The original texture <b>must</b> be immutable
        MOUNTAIN_API void CreateFrom(GpuTexture originalGpuTexture, Graphics::InternalFormat newInternalFormat, uint32_t minMipmapLevel, uint32_t mipmapLevels);

        /// @brief Initialize the immutable data storage on the GPU
        /// @param mipmapLevels The number of mipmap levels to initialize
        /// @param internalFormat The format to use to store the data on the GPU
        /// @param size The size of the texture
        /// @note This will fail if the texture data is already immutable, e.g. a call to @c SetStorage() was already made.
        /// If you want to use this function again, you first need to @c Recreate() the texture.
        /// @see <a href="https://registry.khronos.org/OpenGL-Refpages/gl4/html/glTexStorage2D.xhtml">glTexStorage2D()</a>
        MOUNTAIN_API void SetStorage(Graphics::InternalFormat internalFormat, Vector2i size, int32_t mipmapLevels = 1) const;

        /// @brief Set a portion of the texture data
        /// @param offset The offset from in the texture to set the data from
        /// @param size The size of the data the set
        /// @param dataFormat The format of the given data
        /// @param dataType The type of the given format
        /// @param data The data to set
        /// @param mipmapLevel The mipmap level to set
        /// @see <a href="https://registry.khronos.org/OpenGL-Refpages/gl4/html/glTexSubImage2D.xhtml">glTexSubImage2D()</a>
        MOUNTAIN_API void SetSubData(
            Vector2i offset,
            Vector2i size,
            Graphics::Format dataFormat,
            Graphics::DataType dataType,
            const void* data,
            int32_t mipmapLevel = 0
        ) const;

        /// @brief Initialize and set the initial texture data
        /// @param internalFormat The format to use to store the data on the GPU
        /// @param size The size of the texture
        /// @param dataFormat The format of the given data
        /// @param dataType The type of the given data
        /// @param data The data to set
        /// @param mipmapLevel The mipmap level to set
        /// @see <a href="https://registry.khronos.org/OpenGL-Refpages/gl4/html/glTexImage2D.xhtml">glTexImage2D()</a>
        MOUNTAIN_API void SetData(
            Graphics::InternalFormat internalFormat,
            Vector2i size,
            Graphics::Format dataFormat,
            Graphics::DataType dataType,
            const void* data,
            int32_t mipmapLevel = 0
        ) const;

        /// @see <a href="https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGenerateMipmap.xhtml">glGenerateTextureMipmap()</a>
        MOUNTAIN_API void GenerateMipmap() const;

        /// @brief Adds a friendly debug name for this GpuTexture.
        /// This is used when debugging graphics in external applications such as Nsight or RenderDoc.
        /// This function does nothing if the application isn't compiled in Debug.
        /// @param name The name of this GpuTexture
        /// @see <a href="https://registry.khronos.org/OpenGL-Refpages/gl4/html/glObjectLabel.xhtml">glObjectLabel()</a>
        MOUNTAIN_API void SetDebugName(std::string_view name) const;

        /// @brief Get whether the GpuTexture data is immutable
        /// @see <a href="https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGetTexParameter.xhtml">glGetTexParameteriv()</a>
        [[nodiscard]]
        MOUNTAIN_API bool_t GetImmutable() const;

        /// @see <a href="https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGetTexParameter.xhtml">glGetTexParameteriv()</a>
        [[nodiscard]]
        MOUNTAIN_API Graphics::MagnificationFilter GetMinFilter() const;
        /// @see <a href="https://registry.khronos.org/OpenGL-Refpages/gl4/html/glTexParameter.xhtml">glTexParameteri()</a>
        MOUNTAIN_API void SetMinFilter(Graphics::MagnificationFilter newMinFilter);

        /// @see <a href="https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGetTexParameter.xhtml">glGetTexParameteriv()</a>
        [[nodiscard]]
        MOUNTAIN_API Graphics::MagnificationFilter GetMagFilter() const;
        /// @see <a href="https://registry.khronos.org/OpenGL-Refpages/gl4/html/glTexParameter.xhtml">glTexParameteri()</a>
        MOUNTAIN_API void SetMagFilter(Graphics::MagnificationFilter newMagFilter);

        /// @see <a href="https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGetTexParameter.xhtml">glGetTexParameteriv()</a>
        [[nodiscard]]
        MOUNTAIN_API Graphics::Wrapping GetWrappingHorizontal() const;
        /// @see <a href="https://registry.khronos.org/OpenGL-Refpages/gl4/html/glTexParameter.xhtml">glTexParameteri()</a>
        MOUNTAIN_API void SetWrappingHorizontal(Graphics::Wrapping newWrappingHorizontal);

        /// @see <a href="https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGetTexParameter.xhtml">glGetTexParameteriv()</a>
        [[nodiscard]]
        MOUNTAIN_API Graphics::Wrapping GetWrappingVertical() const;
        /// @see <a href="https://registry.khronos.org/OpenGL-Refpages/gl4/html/glTexParameter.xhtml">glTexParameteri()</a>
        MOUNTAIN_API void SetWrappingVertical(Graphics::Wrapping newWrappingVertical);

        /// @see <a href="https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGetTexParameter.xhtml">glGetTexParameterfv()</a>
        [[nodiscard]]
        MOUNTAIN_API Color GetBorderColor() const;
        /// @see <a href="https://registry.khronos.org/OpenGL-Refpages/gl4/html/glTexParameter.xhtml">glTexParameterfv()</a>
        MOUNTAIN_API void SetBorderColor(Color newBorderColor);

        [[nodiscard]]
        MOUNTAIN_API uint32_t GetId() const;

    private:
        uint32_t m_Id = 0;
    };
}
