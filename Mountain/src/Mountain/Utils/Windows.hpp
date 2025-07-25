#pragma once

#include "Mountain/Core.hpp"

#ifdef ENVIRONMENT_WINDOWS

#include <string>

/// @file windows.hpp
/// @brief A way to include the @c <Windows.h> header without some of its conflicting macros.

#undef APIENTRY
#undef interface
// ReSharper disable once CppInconsistentNaming
#define XMLDocument XMLDocument_dont_care
#define NOMINMAX
#include <Windows.h>

#include <ShlObj_core.h>
#undef XMLDocument

#undef near
#undef far
#undef MessageBox
#undef GetMessage

namespace Mountain::Windows
{
    MOUNTAIN_API bool_t CheckError();

    MOUNTAIN_API void SilenceError();

    ATTRIBUTE_NODISCARD
    MOUNTAIN_API std::string GetAppdataLocalPath();

    ATTRIBUTE_NODISCARD
    MOUNTAIN_API std::string GetAppdataRoamingPath();
}

#endif
