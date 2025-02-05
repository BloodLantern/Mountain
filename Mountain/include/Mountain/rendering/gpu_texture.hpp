#pragma once

#include <Maths/vector2i.hpp>

#include "Mountain/core.hpp"
#include "Mountain/rendering/graphics.hpp"
#include "Mountain/utils/color.hpp"

namespace Mountain::Graphics
{
    /// @brief Low-level interface for OpenGL textures
    struct MOUNTAIN_API GpuTexture
    {
        /// @brief Create the texture on the GPU
        /// @see <a href="https://registry.khronos.org/OpenGL-Refpages/gl4/html/glCreateTextures.xhtml">glCreateTextures()</a>
        void Create();

        /// @brief Delete the texture on the GPU
        /// @see <a href="https://registry.khronos.org/OpenGL-Refpages/gl4/html/glDeleteTextures.xhtml">glDeleteTextures()</a>
        void Delete();

        /// @brief Shorthand for @code Delete(); Create();@endcode
        void Recreate();

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
        void CreateFrom(uint32_t originalTextureId, InternalFormat newInternalFormat, uint32_t minMipmapLevel, uint32_t mipmapLevels);

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
        void CreateFrom(GpuTexture originalGpuTexture, InternalFormat newInternalFormat, uint32_t minMipmapLevel, uint32_t mipmapLevels);

        /// @brief Initialize the immutable data storage on the GPU
        /// @param mipmapLevels The number of mipmap levels to initialize
        /// @param internalFormat The format to use to store the data on the GPU
        /// @param size The size of the texture
        /// @note This will fail if the texture data is already immutable, e.g. a call to @c SetStorage() was already made.
        /// If you want to use this function again, you first need to @c Recreate() the texture.
        /// @see <a href="https://registry.khronos.org/OpenGL-Refpages/gl4/html/glTexStorage2D.xhtml">glTexStorage2D()</a>
        void SetStorage(InternalFormat internalFormat, Vector2i size, int32_t mipmapLevels = 1) const;

        /// @brief Set a portion of the texture data
        /// @param offset The offset from in the texture to set the data from
        /// @param size The size of the data the set
        /// @param dataFormat The format of the given data
        /// @param dataType The type of the given format
        /// @param data The data to set
        /// @param mipmapLevel The mipmap level to set
        /// @see <a href="https://registry.khronos.org/OpenGL-Refpages/gl4/html/glTexSubImage2D.xhtml">glTexSubImage2D()</a>
        void SetSubData(
            Vector2i offset,
            Vector2i size,
            Format dataFormat,
            DataType dataType,
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
        /// @note This will fail if the texture data is immutable, e.g. a call to @c SetStorage() was already made.
        /// If you want to use this function and the texture data is immutable, you first need to @c Recreate() the texture.
        /// @see <a href="https://registry.khronos.org/OpenGL-Refpages/gl4/html/glTexImage2D.xhtml">glTexImage2D()</a>
        void SetData(
            InternalFormat internalFormat,
            Vector2i size,
            Format dataFormat,
            DataType dataType,
            const void* data,
            int32_t mipmapLevel = 0
        ) const;

        /// @see <a href="https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGenerateMipmap.xhtml">glGenerateTextureMipmap()</a>
        void GenerateMipmap() const;

        /// @brief Adds a friendly debug name for this GpuTexture.
        /// This is used when debugging graphics in external applications such as Nsight or RenderDoc.
        /// This function does nothing if the application isn't compiled in Debug.
        /// @param name The name of this GpuTexture
        /// @see <a href="https://registry.khronos.org/OpenGL-Refpages/gl4/html/glObjectLabel.xhtml">glObjectLabel()</a>
        void SetDebugName(std::string_view name) const;

        /// @brief Get whether the GpuTexture data is immutable
        /// @see <a href="https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGetTexParameter.xhtml">glGetTexParameteriv()</a>
        [[nodiscard]]
        bool_t GetImmutable() const;

        /// @see <a href="https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGetTexParameter.xhtml">glGetTexParameteriv()</a>
        [[nodiscard]]
        MagnificationFilter GetMinFilter() const;
        /// @see <a href="https://registry.khronos.org/OpenGL-Refpages/gl4/html/glTexParameter.xhtml">glTexParameteri()</a>
        void SetMinFilter(MagnificationFilter newMinFilter) const;

        /// @see <a href="https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGetTexParameter.xhtml">glGetTexParameteriv()</a>
        [[nodiscard]]
        MagnificationFilter GetMagFilter() const;
        /// @see <a href="https://registry.khronos.org/OpenGL-Refpages/gl4/html/glTexParameter.xhtml">glTexParameteri()</a>
        void SetMagFilter(MagnificationFilter newMagFilter) const;

        /// @see <a href="https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGetTexParameter.xhtml">glGetTexParameteriv()</a>
        [[nodiscard]]
        Wrapping GetWrappingHorizontal() const;
        /// @see <a href="https://registry.khronos.org/OpenGL-Refpages/gl4/html/glTexParameter.xhtml">glTexParameteri()</a>
        void SetWrappingHorizontal(Wrapping newWrappingHorizontal) const;

        /// @see <a href="https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGetTexParameter.xhtml">glGetTexParameteriv()</a>
        [[nodiscard]]
        Wrapping GetWrappingVertical() const;
        /// @see <a href="https://registry.khronos.org/OpenGL-Refpages/gl4/html/glTexParameter.xhtml">glTexParameteri()</a>
        void SetWrappingVertical(Wrapping newWrappingVertical) const;

        /// @see <a href="https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGetTexParameter.xhtml">glGetTexParameterfv()</a>
        [[nodiscard]]
        Color GetBorderColor() const;
        /// @see <a href="https://registry.khronos.org/OpenGL-Refpages/gl4/html/glTexParameter.xhtml">glTexParameterfv()</a>
        void SetBorderColor(Color newBorderColor) const;

        [[nodiscard]]
        uint32_t GetId() const;

        [[nodiscard]]
        explicit operator uint32_t() const;

    private:
        uint32_t m_Id = 0;
    };
}
