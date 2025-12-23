#pragma once

#include "Mountain/Core.hpp"
#include "Mountain/Graphics/Graphics.hpp"

namespace Mountain::Graphics
{
    /// @brief Low-level interface for OpenGL buffers
    struct MOUNTAIN_API GpuBuffer
    {
        void Create();

        void Delete();

        /// @brief Shorthand for @code Delete(); Create();@endcode
        void Recreate();

        void SetStorage(s64 size, const void* data, BufferStorageFlags flags = BufferStorageFlags::None) const;

        void SetSubData(s64 offset, s64 size, const void* data) const;

        void SetData(s64 size, const void* data, BufferUsage usage) const;

        void SetDebugName(std::string_view name) const;

        ATTRIBUTE_NODISCARD
        bool GetImmutable() const;

        GETTER(u32, Id, m_Id)

        ATTRIBUTE_NODISCARD
        explicit operator u32() const;

    private:
        u32 m_Id = 0;
    };
}
