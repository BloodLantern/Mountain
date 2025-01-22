#pragma once

#include <Maths/vector2i.hpp>

#include "Mountain/core.hpp"
#include "Mountain/rendering/graphics.hpp"

namespace Mountain
{
    /// @brief Low-level interface for OpenGL buffers
    struct MOUNTAIN_API GpuBuffer
    {
        void Create();

        void Delete();

        /// @brief Shorthand for @code Delete(); Create();@endcode
        void Recreate();

        void SetStorage(int64_t size, const void* data, Graphics::BufferStorageFlags flags = Graphics::BufferStorageFlags::None) const;

        void SetSubData(int64_t offset, int64_t size, const void* data) const;

        void SetData(int64_t size, const void* data, Graphics::BufferUsage usage) const;

        void SetDebugName(std::string_view name) const;

        [[nodiscard]]
        bool_t GetImmutable() const;

        [[nodiscard]]
        uint32_t GetId() const;

    private:
        uint32_t m_Id = 0;
    };
}
