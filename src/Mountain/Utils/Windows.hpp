#pragma once

#include <string>

#include "Mountain/Core.hpp"

/// @file windows.hpp
/// @brief A way to include the @c <Windows.h> header without some of its conflicting macros.

#undef APIENTRY
#undef XMLDocument
#undef NOMINMAX

// ReSharper disable once CppInconsistentNaming
#define XMLDocument XMLDocument_dont_care
#define NOMINMAX
#include <Windows.h>

#include <psapi.h>
#include <ShlObj.h>
#undef XMLDocument

#undef near
#undef far
#undef MessageBox

#if defined(NTDDI_VERSION) && defined(NTDDI_WIN10_CU) && NTDDI_VERSION >= NTDDI_WIN10_CU
#define WINDOWS_PROCESS_MEMORY_COUNTERS_EX2_AVAILABLE
#endif

namespace Mountain::Windows
{
    MOUNTAIN_API bool_t CheckError();

    MOUNTAIN_API void SilenceError();

    MOUNTAIN_API std::string GetAppdataLocalPath();

    MOUNTAIN_API std::string GetAppdataRoamingPath();
}
