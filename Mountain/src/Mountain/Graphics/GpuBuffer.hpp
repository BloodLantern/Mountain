#pragma once

#include <Math/vector2i.hpp>

#include "Mountain/Core.hpp"
#include "Mountain/Graphics/Graphics.hpp"
#include "Mountain/Utils/Utils.hpp"

namespace Mountain::Graphics
{
    /// @brief Low-level interface for OpenGL buffers
    struct MOUNTAIN_API GpuBuffer
    {
        void Create();

        void Delete();

        /// @brief Shorthand for @code Delete(); Create();@endcode
        void Recreate();

        void SetStorage(int64_t size, const void* data, BufferStorageFlags flags = BufferStorageFlags::None) const;

        void SetSubData(int64_t offset, int64_t size, const void* data) const;

        void SetData(int64_t size, const void* data, BufferUsage usage) const;

        void SetDebugName(std::string_view name) const;

        ATTRIBUTE_NODISCARD
        bool_t GetImmutable() const;

        GETTER(uint32_t, Id, m_Id)

        ATTRIBUTE_NODISCARD
        explicit operator uint32_t() const;

    private:
        uint32_t m_Id = 0;
    };
}
