#pragma once

#include <string_view>

#include "core.hpp"

/// @file globals.hpp
/// @brief This file contains global configuration variables that can be modified before any calls to the framework functions.

namespace Mountain
{
    PUBLIC_GLOBAL(bool_t, NoBinaryResources, false);
    PUBLIC_GLOBAL(std::string, BuiltinShadersPath, "");  // NOLINT(readability-redundant-string-init)
}
