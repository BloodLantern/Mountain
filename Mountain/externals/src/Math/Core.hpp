#pragma once

/// @file Core.hpp
/// @brief File containing various macros used in the library.
///
/// When building a DLL using this library, define @c MATH_TOOLBOX_DLL_EXPORT.
/// When using a DLL that was built using this library, instead define @c MATH_TOOLBOX_DLL_IMPORT.

//#define MATH_TOOLBOX_DLL_EXPORT

/// @brief Macro preceding all declarations of this library. Used when integrating this library in a DLL.
///
/// If using this library to build a DLL, define @c MATH_TOOLBOX_DLL_EXPORT.
/// If using a DLL that was built using this library, instead define @c MATH_TOOLBOX_DLL_IMPORT.
#if defined(MATH_TOOLBOX_DLL_EXPORT)
#define MATH_API __declspec(dllexport)
#elif defined(MATH_TOOLBOX_DLL_IMPORT)
#define MATH_API __declspec(dllimport)
#else
#define MATH_API
#endif

/// @brief Expands to the square of a value.
#define SQ(x) ((x) * (x))
