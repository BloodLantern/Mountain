#pragma once

#include <array>

#include <Maths/vector2i.hpp>

#include "Mountain/core.hpp"
#include "Mountain/rendering/gpu_texture.hpp"
#include "Mountain/rendering/graphics.hpp"
#include "Mountain/resource/resource.hpp"

/// @file texture.hpp
/// @brief Defines the Mountain::Texture class

namespace Mountain
{
    /// @brief Represents an image in memory.
    class Texture : public Resource
    {
    public:
        /// @brief Allowed extensions for texture files
        MOUNTAIN_API static constexpr std::array FileExtensions
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
        [[nodiscard]]
        const T* GetData() const;

        /// @brief Gets the raw data of the texture
        /// @tparam T Type
        /// @return Data
        template <typename T = char_t>
        [[nodiscard]]
        T* GetData();

        /// @brief Gets the size of the texture
        /// @return Size
        [[nodiscard]]
        MOUNTAIN_API Vector2i GetSize() const;

        MOUNTAIN_API void SetSize(Vector2i newSize);

        [[nodiscard]]
        MOUNTAIN_API Graphics::MagnificationFilter GetFilter() const;
        MOUNTAIN_API void SetFilter(Graphics::MagnificationFilter newFilter);

        /// @brief Binds the texture
        MOUNTAIN_API void Use() const;

        /// @brief Unbinds the texture
        MOUNTAIN_API void Unuse() const;

        /// @brief Get the ID of this texture on the GPU
        [[nodiscard]]
        MOUNTAIN_API uint32_t GetId() const;

        /// @brief Gets the underlying GpuTexture
        [[nodiscard]]
        MOUNTAIN_API GpuTexture GetGpuTexture() const;

    private:
        uint8_t* m_Data = nullptr;
        Vector2i m_Size;
        GpuTexture m_GpuTexture;
        Graphics::MagnificationFilter m_Filter = Graphics::MagnificationFilter::Nearest;
    };
}

#include "Mountain/resource/texture.inl"
