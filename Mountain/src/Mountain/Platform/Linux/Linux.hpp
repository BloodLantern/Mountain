#pragma once

#include "Mountain/Core.hpp"

#ifdef ENVIRONMENT_LINUX

namespace Mountain::Linux
{
    MOUNTAIN_API bool Sleep(TimeSpan duration);

    ATTRIBUTE_NODISCARD
    MOUNTAIN_API Guid NewGuid();

    ATTRIBUTE_NODISCARD
    MOUNTAIN_API DateTime UtcNow();

    ATTRIBUTE_NODISCARD
    MOUNTAIN_API usize GetMemoryUsage();

    ATTRIBUTE_NODISCARD
    MOUNTAIN_API s64 GetTimerFrequency();

    ATTRIBUTE_NODISCARD
    MOUNTAIN_API s64 GetTimestamp();

    MOUNTAIN_API void Cleanup();
}

#endif
