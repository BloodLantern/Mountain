#pragma once

#include <Mountain/Mountain.hpp>

using namespace Mountain;  // NOLINT(clang-diagnostic-header-hygiene)

// Do not use Live++ in the Release configuration
#ifdef NDEBUG
#undef LPP_PATH
#endif
