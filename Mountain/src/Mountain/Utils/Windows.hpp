#pragma once

#include <string>

#include "Mountain/Core.hpp"

/// @file windows.hpp
/// @brief A way to include the @c <Windows.h> header without some of its conflicting macros.

#undef APIENTRY
// ReSharper disable once CppInconsistentNaming
#define XMLDocument XMLDocument_dont_care
#define NOMINMAX
#include <Windows.h>

#include <ShlObj_core.h>
#undef XMLDocument

#undef near
#undef far
#undef MessageBox

namespace Mountain::Windows
{
    MOUNTAIN_API bool_t CheckError();

    MOUNTAIN_API void SilenceError();

    MOUNTAIN_API std::string GetAppdataLocalPath();

    MOUNTAIN_API std::string GetAppdataRoamingPath();
}
