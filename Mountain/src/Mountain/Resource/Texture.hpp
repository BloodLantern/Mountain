#pragma once

#include <array>

#include <Math/vector2i.hpp>

#include "Mountain/Core.hpp"
#include "Mountain/Graphics/GpuTexture.hpp"
#include "Mountain/Graphics/Graphics.hpp"
#include "Mountain/Resource/Resource.hpp"

/// @file texture.hpp
/// @brief Defines the Mountain::Texture class

namespace Mountain
{
    /// @brief Represents an image in memory.
    class Texture : public Resource
    {
    public:
        /// @brief Allowed extensions for texture files
        MOUNTAIN_API static constexpr Array FileExtensions
        {
            ".jpg",
            ".jpeg",
            ".png"
        };

        // Same constructor from base class
        using Resource::Resource;

        DELETE_COPY_MOVE_OPERATIONS(Texture)

        // We keep both function overloads and only override one
        using Resource::SetSourceData;

        MOUNTAIN_API ~Texture() override;

        MOUNTAIN_API bool_t SetSourceData(const uint8_t* buffer, int64_t length) override;

        MOUNTAIN_API void Load() override;

        MOUNTAIN_API void Unload() override;

        MOUNTAIN_API void ResetSourceData() override;

        /// @brief Gets the raw data of the texture
        /// @tparam T Type
        /// @return Data
        template <typename T = char_t>
        ATTRIBUTE_NODISCARD
        const T* GetData() const;

        /// @brief Gets the raw data of the texture
        /// @tparam T Type
        /// @return Data
        template <typename T = char_t>
        ATTRIBUTE_NODISCARD
        T* GetData();

        /// @brief Gets the size of the texture
        /// @return Size
        ATTRIBUTE_NODISCARD
        MOUNTAIN_API Vector2i GetSize() const;

        MOUNTAIN_API void SetSize(Vector2i newSize);

        ATTRIBUTE_NODISCARD
        MOUNTAIN_API Graphics::MagnificationFilter GetFilter() const;
        MOUNTAIN_API void SetFilter(Graphics::MagnificationFilter newFilter);

        /// @brief Binds the texture
        MOUNTAIN_API void Use() const;

        /// @brief Unbinds the texture
        MOUNTAIN_API void Unuse() const;

        /// @brief Get the ID of this texture on the GPU
        ATTRIBUTE_NODISCARD
        MOUNTAIN_API uint32_t GetId() const;

        /// @brief Gets the underlying GpuTexture
        ATTRIBUTE_NODISCARD
        MOUNTAIN_API Graphics::GpuTexture GetGpuTexture() const;

    private:
        uint8_t* m_Data = nullptr;
        Vector2i m_Size;
        Graphics::GpuTexture m_GpuTexture;
        Graphics::MagnificationFilter m_Filter = Graphics::MagnificationFilter::Nearest;
    };
}

// Start of Texture.inl

namespace Mountain
{
    template<typename T>
    const T* Texture::GetData() const { return reinterpret_cast<const T*>(m_Data); }

    template<typename T>
    T* Texture::GetData() { return reinterpret_cast<T*>(m_Data); }
}
