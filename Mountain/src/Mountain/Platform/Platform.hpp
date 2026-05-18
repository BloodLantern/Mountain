#pragma once

#include "Mountain/Core.hpp"

namespace Mountain::Platform
{
    /// @brief Attempt to sleep for the given duration using the operating system's native sleep functions
    /// @param duration The sleep duration
    /// @return Whether the operation succeeded
    MOUNTAIN_API bool Sleep(TimeSpan duration);

    MOUNTAIN_API Guid NewGuid();

    MOUNTAIN_API void Cleanup();
}
