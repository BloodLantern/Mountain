#pragma once

#include "Mountain/Core.hpp"

#ifdef ENVIRONMENT_LINUX

namespace Mountain::Linux
{
    MOUNTAIN_API bool Sleep(TimeSpan duration);

    MOUNTAIN_API Guid NewGuid();

    MOUNTAIN_API void Cleanup();
}

#endif
