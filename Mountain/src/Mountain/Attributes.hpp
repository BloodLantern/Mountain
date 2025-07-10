#pragma once

#include "Mountain/CompilerSpecific.hpp"

/// @brief Indicates that the function does not return.
#define ATTRIBUTE_NORETURN [[noreturn]]
/// @brief Indicates that dependency chain in release-consume @c std::memory_order propagates in and out of the function.
/// @details This allows the compiler to skip unnecessary memory fence instructions.
#define ATTRIBUTE_CARRIES_DEPENDENCY [[carries_dependency]]
/// @brief Indicates that the name or entity declared with this attribute is deprecated, that is,
/// the use is allowed but discouraged for some reason.
#define ATTRIBUTE_DEPRECATED(reason) [[deprecated(reason)]]
/// @brief Indicates that the fall through from the previous case label is intentional
/// and should not be diagnosed by a compiler that warns on fallthrough.
#define ATTRIBUTE_FALLTHROUGH [[fallthrough]]
/// @brief Suppresses warnings on unused entities.
#define ATTRIBUTE_MAYBE_UNUSED [[maybe_unused]]
/// @brief Encourages the compiler to issue a warning if the return value is discarded.
/// @details If a function declared nodiscard or a function returning an enumeration or class declared nodiscard by value
/// is called from a discarded-value expression other than a cast to void, the compiler is encouraged to issue a warning.
#define ATTRIBUTE_NODISCARD [[nodiscard]]
/// @brief Allows the compiler to optimize for the case where paths of execution including that statement are more likely
/// than any alternative path of execution that does not include such a statement.
#define ATTRIBUTE_LIKELY [[likely]]
/// @brief Allows the compiler to optimize for the case where paths of execution including that statement are less likely
/// than any alternative path of execution that does not include such a statement.
#define ATTRIBUTE_UNLIKELY [[unlikely]]

#ifdef COMPILER_MSVC
    /// @brief Allows this data member to be overlapped with other non-static data members or base class subobjects of its class.
    #define ATTRIBUTE_NO_UNIQUE_ADDRESS [[msvc::no_unique_address]]
#else
    /// @brief Allows this data member to be overlapped with other non-static data members or base class subobjects of its class.
    #define ATTRIBUTE_NO_UNIQUE_ADDRESS [[no_unique_address]]
#endif

#if defined(__JETBRAINS_IDE__) || defined(__RESHARPER__)
    /// @brief The @c [[jetbrains::format]] attribute allows you to enable format inspections for custom printf-like functions
    /// and works similarly to @c [[gnu::format]].
    #define ATTRIBUTE_FORMAT(archetype, stringIndex, firstToCheck) [[jetbrains::format(archetype, stringIndex, firstToCheck)]]
    /// @brief The @c [[jetbrains::pass_by_value]] attribute allows you to suppress the "Pass value by const reference" inspection.
    #define ATTRIBUTE_PASS_BY_VALUE [[jetbrains::pass_by_value]]
    /// @brief The @c [[jetbrains::guard]] attribute can be used to suppress the "Local variable is never used" inspection.
    #define ATTRIBUTE_GUARD [[jetbrains::guard]]
    /// @brief The @c [[jetbrains::has_side_effects]] attribute allows you
    /// to mark operator= as having side effects to suppress the "Assigned value is never used" inspection.
    #define ATTRIBUTE_HAS_SIDE_EFFECTS [[jetbrains::has_side_effects]]
#else
    /// @brief The @c [[jetbrains::format]] attribute allows you to enable format inspections for custom printf-like functions
    /// and works similarly to @c [[gnu::format]].
    #define ATTRIBUTE_FORMAT(...)
    /// @brief The @c [[jetbrains::pass_by_value]] attribute allows you to suppress the "Pass value by const reference" inspection.
    #define ATTRIBUTE_PASS_BY_VALUE
    /// @brief The @c [[jetbrains::guard]] attribute can be used to suppress the "Local variable is never used" inspection.
    #define ATTRIBUTE_GUARD
    /// @brief The @c [[jetbrains::has_side_effects]] attribute allows you
    /// to mark operator= as having side effects to suppress the "Assigned value is never used" inspection.
    #define ATTRIBUTE_HAS_SIDE_EFFECTS
#endif
