#pragma once

#include "Mountain/Core.hpp"

namespace Mountain::Platform
{
    /// @brief Attempt to sleep for the given duration using the operating system's native sleep functions
    /// @param duration The sleep duration
    /// @return Whether the operation succeeded
    MOUNTAIN_API bool Sleep(TimeSpan duration);

    ATTRIBUTE_NODISCARD
    MOUNTAIN_API Guid NewGuid();

    ATTRIBUTE_NODISCARD
    MOUNTAIN_API DateTime UtcNow();

    MOUNTAIN_API void Cleanup();
}
