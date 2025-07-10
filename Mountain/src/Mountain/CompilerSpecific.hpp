#pragma once

#if defined(_WIN32) || defined(__CYGWIN__)
    #define ENVIRONMENT_WINDOWS
#elifdef linux
    #define ENVIRONMENT_LINUX
#else
    #define ENVIRONMENT_UNKNOWN
#endif

#ifdef ENVIRONMENT_UNKNOWN
#error "This library cannot be built under this environment or operating system"
#endif

#if defined(_MSC_VER) && !defined(__llvm__) && !defined(__INTEL_COMPILER)
    #define COMPILER_MSVC
#elif defined(__GNUC__) && !defined(__llvm__) && !defined(__INTEL_COMPILER)
    #define COMPILER_GCC
#elifdef __clang__
    #define COMPILER_CLANG
#endif

#if defined(COMPILER_GCC) || defined(COMPILER_CLANG)
    #define COMPILER_ATTRIBUTE(x) __attribute__((x))
#elifdef COMPILER_MSVC
    #define COMPILER_ATTRIBUTE(x) __declspec(x)
#endif

#ifdef ENVIRONMENT_WINDOWS
    #ifdef MOUNTAIN_EXPORT
        #define SHARED_PUBLIC COMPILER_ATTRIBUTE(dllexport)
    #else
        #define SHARED_PUBLIC COMPILER_ATTRIBUTE(dllimport)
    #endif
    #define SHARED_PRIVATE
#else
    #if __GNUC__ >= 4
        #define SHARED_PUBLIC COMPILER_ATTRIBUTE(visibility("default"))
        #define SHARED_PRIVATE  COMPILER_ATTRIBUTE(visibility("hidden"))
    #else
        #define SHARED_PUBLIC
        #define SHARED_PRIVATE
    #endif
#endif

#ifdef COMPILER_MSVC
    /// @brief Specifies that the given expression is assumed to always evaluate to true at a given point.
    /// @details This allows compiler optimizations based on the information given.
    #define ASSUME(trueExpression) __assume(trueExpression)
#elifdef COMPILER_GCC
    /// @brief Specifies that the given expression is assumed to always evaluate to true at a given point.
    /// @details This allows compiler optimizations based on the information given.
    #define ASSUME(trueExpression) do { if (!(trueExpression)) std::unreachable(); } while (0)
#elifdef COMPILER_CLANG
    /// @brief Specifies that the given expression is assumed to always evaluate to true at a given point.
    /// @details This allows compiler optimizations based on the information given.
    #define ASSUME(trueExpression) __builtin_assume(trueExpression)
#endif
