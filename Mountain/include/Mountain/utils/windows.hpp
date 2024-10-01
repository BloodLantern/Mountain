#pragma once

#include <string>

#include "Mountain/core.hpp"

/// @file windows.hpp
/// @brief A way to include the @c <Windows.h> header without some of its conflicting macros.

#undef APIENTRY
// ReSharper disable once CppInconsistentNaming
#define XMLDocument XMLDocument_dont_care
#include <Windows.h>

#include <ShlObj_core.h>
#undef XMLDocument

#undef near
#undef far
#undef min
#undef max
#undef MessageBox

BEGIN_MOUNTAIN

namespace Windows
{
    MOUNTAIN_API bool_t CheckError();

    MOUNTAIN_API void SilenceError();

    MOUNTAIN_API std::string GetAppdataLocalPath();

    MOUNTAIN_API std::string GetAppdataRoamingPath();
}

END_MOUNTAIN
