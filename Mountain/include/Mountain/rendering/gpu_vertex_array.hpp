#pragma once

#include <string_view>

#include "Mountain/core.hpp"

namespace Mountain
{
    /// @brief Low-level interface for OpenGL vertex arrays
    struct GpuVertexArray
    {
        MOUNTAIN_API void Create();

        MOUNTAIN_API void Delete();

        /// @brief Shorthand for @code Delete(); Create();@endcode
        MOUNTAIN_API void Recreate();

        MOUNTAIN_API void SetDebugName(std::string_view name) const;

        [[nodiscard]]
        MOUNTAIN_API uint32_t GetId() const;

    private:
        uint32_t m_Id = 0;
    };
}
