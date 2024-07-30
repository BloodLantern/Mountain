#pragma once

#include <array>

#include <Maths/vector2i.hpp>

#include "Mountain/core.hpp"
#include "Mountain/resource/resource.hpp"

/// @file texture.hpp
/// @brief Defines the Mountain::Texture class

BEGIN_MOUNTAIN

/// @brief Represents an image in memory.
class Texture final : public Resource
{
public:
    /// @brief Allowed extensions for texture files
    MOUNTAIN_API static constexpr std::array<const char_t*, 3> FileExtensions
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

    /// @brief Gets the number of channels of the file of the texture
    /// @return Number of channels
    [[nodiscard]]
    MOUNTAIN_API int32_t GetDataChannels() const;

    /// @brief Gets the loaded number of channels of the texture
    /// @return Number of channels
    [[nodiscard]]
    MOUNTAIN_API int32_t GetChannels() const;

    /// @brief Binds the texture
    MOUNTAIN_API void Use() const;
    
    /// @brief Unbinds the texture
    MOUNTAIN_API void Unuse() const;

    /// @brief Gets the texture id
    /// @return Texture id
    [[nodiscard]]
    MOUNTAIN_API uint32_t GetId() const;
    
private:
    uint8_t* m_Data = nullptr;
    Vector2i m_Size;
    int32_t m_DataChannels = 0;
    uint32_t m_Id = 0;
};

END_MOUNTAIN

#include "Mountain/resource/texture.inl"
