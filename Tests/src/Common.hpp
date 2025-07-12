#pragma once

#include "Mountain/PrecompiledHeader.hpp"

using namespace Mountain;  // NOLINT(clang-diagnostic-header-hygiene)

// Do not use Live++ in the Release configuration
#ifdef NDEBUG
#undef USE_LPP
#endif
