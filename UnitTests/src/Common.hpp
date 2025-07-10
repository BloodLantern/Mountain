#pragma once

#include <gtest/gtest.h>

#define UNIT_TESTS

#include <Mountain/Core.hpp>

using namespace Mountain;  // NOLINT(clang-diagnostic-header-hygiene)

#ifdef COMPILER_MSVC
#pragma warning(disable: 4834) // discarding return value of function with 'nodiscard' attribute
#pragma warning(disable: 4723) // potential divide by 0
#endif
