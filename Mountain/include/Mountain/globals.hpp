#pragma once

#include <string_view>

#include "core.hpp"

/// @file globals.hpp
/// @brief This file contains global configuration variables that can be modified before any calls to the framework functions.

namespace Mountain
{
    /// @brief Whether to <b>not</b> use packaged binary resources
    /// @details If this is @c true, @c BuiltinShadersPath must be set to the Mountain builtin shaders location.
    /// This means that instead of using the packaged shader files within the Mountain DLL, the files will instead be loaded from the file system.
    /// This can be useful in case you need to edit the builtin shaders because you can then use hot-reloading.
    PUBLIC_GLOBAL(bool_t, NoBinaryResources, false);
    /// @brief The path to the Mountain builtin shaders directory
    /// @see NoBinaryResources
    PUBLIC_GLOBAL(std::string, BuiltinShadersPath, "");  // NOLINT(readability-redundant-string-init)
    /// @brief Whether to debug break when an OpenGL error is reported
    PUBLIC_GLOBAL(bool_t, BreakOnGraphicsError, false);
}
