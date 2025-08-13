// ReSharper disable CppClangTidyReadabilityRedundantStringInit
#pragma once

#include <string>

#include "Core.hpp"

/// @file Globals.hpp
/// @brief This file contains global configuration variables that can be modified before any calls to the framework functions.

#ifdef MOUNTAIN_EXPORT
#define PUBLIC_GLOBAL(varType, varName, defaultValue) MOUNTAIN_API inline varType varName = defaultValue;
#else
#define PUBLIC_GLOBAL(varType, varName, defaultValue) MOUNTAIN_API varType varName;
#endif

namespace Mountain
{
    /// @brief Whether to <b>not</b> use packaged binary resources.
    /// @details If this is @c true, @c BuiltinShadersPath and @c BuiltinAssetsPath must be set.
    /// This means that instead of using the packaged shader files within the Mountain DLL, the files will instead be loaded from the file system.
    /// This can be useful in case you need to edit the builtin shaders because you can then use hot-reloading.
    PUBLIC_GLOBAL(bool_t, NoBinaryResources, false);
    /// @brief The path to the Mountain builtin shaders directory.
    /// @see NoBinaryResources
    PUBLIC_GLOBAL(std::string, BuiltinShadersPath, "");
    /// @brief The path to the Mountain builtin assets directory.
    /// @see NoBinaryResources
    PUBLIC_GLOBAL(std::string, BuiltinAssetsPath, "");
    /// @brief Whether to debug break when an OpenGL error is reported.
    PUBLIC_GLOBAL(bool_t, BreakOnGraphicsError, false);
    /// @brief Whether to still call @c Game::Update() when @code Time::freezeTimer > 0.f@endcode.
    PUBLIC_GLOBAL(bool_t, ManualFreezeFrames, false);
    /// @brief Whether <b>not</b> to call @c Coroutine::UpdateAll() every frame.
    PUBLIC_GLOBAL(bool_t, ManualCoroutineUpdates, false);
}
