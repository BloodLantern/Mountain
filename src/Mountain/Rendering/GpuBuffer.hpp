#pragma once

#include <Math/vector2i.hpp>

#include "Mountain/Core.hpp"
#include "Mountain/Rendering/Graphics.hpp"
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

        void SetStorage(int64_t size, const void* data, Meta::Flags<BufferStorageFlags> flags = Utils::ToFlags(BufferStorageFlags::None)) const;

        void SetSubData(int64_t offset, int64_t size, const void* data) const;

        void SetData(int64_t size, const void* data, BufferUsage usage) const;

        void SetDebugName(std::string_view name) const;

        [[nodiscard]]
        bool_t GetImmutable() const;

        GETTER(uint32_t, Id, m_Id)

        [[nodiscard]]
        explicit operator uint32_t() const;

    private:
        uint32_t m_Id = 0;
    };
}
