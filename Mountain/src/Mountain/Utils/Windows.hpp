#pragma once

/// @file windows.hpp
/// @brief A way to include the @c Windows.h header without some of its conflicting macros.

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
