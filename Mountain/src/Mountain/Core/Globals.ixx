export module Mountain:Core_Globals;

import "Mountain/Core.hpp";

import std;
import :Core_Types;

/// @file Globals.ixx
/// @brief This file contains global configuration variables
/// that can be modified before any calls to the framework functions.

// ReSharper disable CppClangTidyReadabilityRedundantStringInit

export namespace Mountain
{
    /// @brief Whether to <b>not</b> use packaged binary resources
    /// @details If this is @c true, @c BuiltinShadersPath and @c BuiltinAssetsPath must be set.
    /// This means that instead of using the packaged shader files within the Mountain DLL, the files will instead be loaded from the file system.
    /// This can be useful in case you need to edit the builtin shaders because you can then use hot-reloading.
    PUBLIC_GLOBAL(bool_t, NoBinaryResources, false);
    /// @brief The path to the Mountain builtin shaders directory
    /// @see NoBinaryResources
    PUBLIC_GLOBAL(std::string, BuiltinShadersPath, "");
    /// @brief The path to the Mountain builtin assets directory
    /// @see NoBinaryResources
    PUBLIC_GLOBAL(std::string, BuiltinAssetsPath, "");
    /// @brief Whether to debug break when an OpenGL error is reported
    PUBLIC_GLOBAL(bool_t, BreakOnGraphicsError, false);
}
