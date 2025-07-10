#pragma once

#include <string_view>

#include "Mountain/Core.hpp"

namespace Mountain::Graphics
{
    /// @brief Low-level interface for OpenGL vertex arrays
    struct MOUNTAIN_API GpuVertexArray
    {
        void Create();

        void Delete();

        /// @brief Shorthand for @code Delete(); Create();@endcode
        void Recreate();

        void SetDebugName(std::string_view name) const;

        ATTRIBUTE_NODISCARD
        uint32_t GetId() const;

        ATTRIBUTE_NODISCARD
        explicit operator uint32_t() const;

    private:
        uint32_t m_Id = 0;
    };
}
