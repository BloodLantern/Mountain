#pragma once

#include <Maths/vector2i.hpp>

#include "Mountain/core.hpp"
#include "Mountain/rendering/graphics.hpp"

namespace Mountain
{
    /// @brief Low-level interface for OpenGL buffers
    struct GpuBuffer
    {
        MOUNTAIN_API void Create();

        MOUNTAIN_API void Delete();

        /// @brief Shorthand for @code Delete(); Create();@endcode
        MOUNTAIN_API void Recreate();

        MOUNTAIN_API void SetStorage(int64_t size, const void* data, Graphics::BufferStorageFlags flags = Graphics::BufferStorageFlags::None) const;

        MOUNTAIN_API void SetSubData(int64_t offset, int64_t size, const void* data) const;

        MOUNTAIN_API void SetData(int64_t size, const void* data, Graphics::BufferUsage usage) const;

        MOUNTAIN_API void SetDebugName(std::string_view name) const;

        [[nodiscard]]
        MOUNTAIN_API bool_t GetImmutable() const;

        [[nodiscard]]
        MOUNTAIN_API uint32_t GetId() const;

    private:
        uint32_t m_Id = 0;
    };
}
