#pragma once

#include <cmath>
#include <cstdint>

/// @file definitions.hpp
/// @brief File containing various macros used in the library.
/// 
/// When building a DLL using this library, define <c>MATH_TOOLBOX_DLL_EXPORT</c>. When using a DLL that was built using this library, instead define <c>MATH_TOOLBOX_DLL_IMPORT</c>.

/// @brief Macro preceding all declarations of this library. Used when integrating this library in a DLL.
///
/// If using this library to build a DLL, define <c>MATH_TOOLBOX_DLL_EXPORT</c>. If using a DLL that was built using this library, instead define <c>MATH_TOOLBOX_DLL_IMPORT</c>.
#if defined(MATH_TOOLBOX_DLL_EXPORT)
#define MATH_TOOLBOX __declspec(dllexport)
#elif defined(MATH_TOOLBOX_DLL_IMPORT)
#define MATH_TOOLBOX __declspec(dllimport)
#else
#define MATH_TOOLBOX
#endif

// ReSharper disable once CppEnforceTypeAliasCodeStyle
/// @private
typedef bool bool_t;
// ReSharper disable once CppEnforceTypeAliasCodeStyle
/// @private
typedef char char_t;

/// @brief Expands to the square of a value.
#define SQ(x) ((x) * (x))
