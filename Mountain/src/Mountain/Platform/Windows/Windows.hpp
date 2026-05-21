#pragma once

#include "Mountain/Core.hpp"

#ifdef ENVIRONMENT_WINDOWS

#include <string>

#include "Mountain/Utils/TimeSpan.hpp"

/// @file Windows.hpp
/// @brief A way to include the @c <Windows.h> header without some of its conflicting macros.

#undef APIENTRY
#undef interface
// ReSharper disable once CppInconsistentNaming
#define XMLDocument XMLDocument_dont_care
#define NOMINMAX
#include <Windows.h>

#include <psapi.h>
#include <ShlObj_core.h>
#undef XMLDocument

#undef near
#undef far
#undef MessageBox
#undef GetMessage

namespace Mountain::Windows
{
    MOUNTAIN_API bool CheckError();

    MOUNTAIN_API void SilenceError();

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

    ATTRIBUTE_NODISCARD
    MOUNTAIN_API std::string GetAppdataLocalPath();

    ATTRIBUTE_NODISCARD
    MOUNTAIN_API std::string GetAppdataRoamingPath();
}

#endif
