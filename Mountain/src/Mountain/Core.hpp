// ReSharper disable CppClangTidyBugproneMacroParentheses
#pragma once

#include <cmath>
#include <csignal>
#include <cstdint>

#include "Mountain/Attributes.hpp"
#include "Mountain/CompilerSpecific.hpp"
#include "Mountain/Configuration.hpp"

/// @file Core.hpp
/// @brief This file is meant to be included in every single other header file of this project.
///
/// It declares typedefs for all numeric types such as @c s8, @c u32, @c f32, @c c8, @c usize...
///
/// Apart from typedefs, this file declares macros ranging from necessary (MOUNTAIN_API)
/// to useful and of general-use (DEFAULT_COPY_MOVE_OPERATIONS).

using s8 = std::int8_t;
using s16 = std::int16_t;
using s32 = std::int32_t;
using s64 = std::int64_t;
using u8 = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using usize = std::size_t;
using c8 = char;
using c16 = wchar_t;
using f32 = float;
using f64 = double;
using nullptr_t = std::nullptr_t;

/// @brief Macro used for DLL export/import.
/// @details This macro should be used at the beginning of static member variable and non-inline function declarations.
#define MOUNTAIN_API SHARED_PUBLIC
#define MOUNTAIN_PRIVATE_API SHARED_PRIVATE

/// @namespace Mountain
/// @brief Contains all declarations of the Mountain Framework.
namespace Mountain {}

#define SQ(x) (x * x)

/// @brief Creates default copy and move operations for a given @p type.
///
/// This macro should be used for any type that defines at least one of:
/// - A non-default destructor (this includes @code = default @endcode implementations),
/// - A non-default copy constructor
/// - A non-default move constructor
/// - A non-default copy operator
/// - A non-default move operator
///
/// It should be used right after the last constructor declaration:
/// @code
/// class A
/// {
/// public:
///     A();
///     A(int);
///
///     DEFAULT_COPY_MOVE_OPERATIONS(A)
/// };
/// @endcode
/// Or after the destructor declaration if there is one:
/// @code
/// class A
/// {
/// public:
///     A();
///     A(int);
///     ~A();
///
///     DEFAULT_COPY_MOVE_OPERATIONS(A)
/// };
/// @endcode
///
/// @param type The type to default the copy and move operations of.
#define DEFAULT_COPY_MOVE_OPERATIONS(type) \
    type(const type& other) noexcept = default; \
    type(type&& other) noexcept = default; \
    type& operator=(const type& other) noexcept = default; \
    type& operator=(type&& other) noexcept = default;

/// @brief Deletes the copy and move operations of a given @p type.
/// @param type The type to delete the copy and move operations of.
/// @see @ref DEFAULT_COPY_MOVE_OPERATIONS for usage.
#define DELETE_COPY_MOVE_OPERATIONS(type) \
    type(const type& other) = delete; \
    type(type&& other) = delete; \
    type& operator=(const type& other) = delete; \
    type& operator=(type&& other) = delete;

/// @brief Macro used to declare a static class, e.g., a class that cannot be instantiated.
///
/// For consistency, this should be the first statement inside the class definition:
/// @code
/// class A
/// {
///     STATIC_CLASS(A)
///
/// public:
///     ...
/// };
/// @endcode
///
/// Also, a static class shouldn't define any other constructors.
///
/// @param type The type to make static.
#define STATIC_CLASS(type) \
    public: \
    type() = delete; \
    ~type() = delete; \
    DELETE_COPY_MOVE_OPERATIONS(type) \
    private:

/// @brief Defines binary flag operators for an enum type.
/// @param enumName The enum to define the flag operations of.
/// @note This macro **must** be used in the global namespace, as it declares a template specialization of a @c magic_enum struct.
#define ENUM_FLAGS(enumName) \
    static_assert(std::is_enum_v<enumName>, "enumName must be a valid enum type"); \
    \
    inline std::underlying_type_t<enumName> operator&(const enumName lhs, const enumName rhs) { return static_cast<std::underlying_type_t<enumName>>(lhs) & static_cast<std::underlying_type_t<enumName>>(rhs); } \
    inline enumName operator|(const enumName lhs, const enumName rhs) { return static_cast<enumName>(static_cast<std::underlying_type_t<enumName>>(lhs) | static_cast<std::underlying_type_t<enumName>>(rhs)); } \
    inline std::underlying_type_t<enumName> operator&(const std::underlying_type_t<enumName> lhs, const enumName rhs) { return lhs & static_cast<std::underlying_type_t<enumName>>(rhs); } \
    inline std::underlying_type_t<enumName> operator|(const std::underlying_type_t<enumName> lhs, const enumName rhs) { return lhs | static_cast<std::underlying_type_t<enumName>>(rhs); } \
    inline std::underlying_type_t<enumName> operator&(const enumName lhs, const std::underlying_type_t<enumName> rhs) { return static_cast<std::underlying_type_t<enumName>>(lhs) & rhs; } \
    inline std::underlying_type_t<enumName> operator|(const enumName lhs, const std::underlying_type_t<enumName> rhs) { return static_cast<std::underlying_type_t<enumName>>(lhs) | rhs; } \
    inline std::underlying_type_t<enumName>& operator&=(std::underlying_type_t<enumName>& lhs, const enumName rhs) { return lhs = lhs & rhs; } \
    inline std::underlying_type_t<enumName>& operator|=(std::underlying_type_t<enumName>& lhs, const enumName rhs) { return lhs = lhs | rhs; } \
    inline enumName& operator&=(enumName& lhs, const enumName rhs) { return lhs = static_cast<enumName>(lhs & rhs); } \
    inline enumName& operator|=(enumName& lhs, const enumName rhs) { return lhs = static_cast<enumName>(lhs | rhs); } \
    \
    template <> \
    struct magic_enum::customize::enum_range<enumName> \
    { \
        static constexpr bool is_flags = true; \
    };

#ifdef ENVIRONMENT_WINDOWS
/// @brief Defines global definitions that make OpenGL use the dedicated GPU instead of the integrated one
/// Source: https://www.reddit.com/r/opengl/comments/unc3fy/comment/i8728y3/?utm_source=share&utm_medium=web3x&utm_name=web3xcss&utm_term=1&utm_content=share_button
#define USE_DEDICATED_GPU \
    extern "C" \
    { \
        _declspec(dllexport) u32 NvOptimusEnablement = 1; \
        _declspec(dllexport) s32 AmdPowerXpressRequestHighPerformance = 1; \
    }
#else
/// @brief On Windows, this makes OpenGL use the dedicated GPU instead of the integrated one. Has no effect on Linux.
/// Source: https://www.reddit.com/r/opengl/comments/unc3fy/comment/i8728y3/?utm_source=share&utm_medium=web3x&utm_name=web3xcss&utm_term=1&utm_content=share_button
#define USE_DEDICATED_GPU
#endif

/// @brief Defines a getter for the field @p internalName, of type @p type, with the name @c Get##name and the given specifiers
#define GETTER_HELPER(type, preSpecifiers, postSpecifiers, name, internalName) ATTRIBUTE_NODISCARD preSpecifiers type Get##name() postSpecifiers noexcept { return internalName; }

/// @brief Defines a getter for the field @p internalName, of type @p type, with the name @c Get##name
#define GETTER(type, name, internalName) GETTER_HELPER(type, , const, name, internalName)
/// @brief Defines a getter for the field @c m_##name, of type @p type, with the name @c Get##name
#define GETTER_M(type, name) GETTER(type, name, m_##name)

/// @brief Defines a static getter for the field @p internalName, of type @p type, with the name @c Get##name
#define STATIC_GETTER(type, name, internalName) GETTER_HELPER(type, static, , name, internalName)
/// @brief Defines a static getter for the field @c m_##name, of type @p type, with the name @c Get##name
#define STATIC_GETTER_M(type, name, internalName) STATIC_GETTER(type, name, m_##name)

/// @brief Defines a constexpr getter for the field @p internalName, of type @p type, with the name @c Get##name
#define CONSTEXPR_GETTER(type, name, internalName) GETTER_HELPER(type, constexpr, const, name, internalName)
/// @brief Defines a constexpr getter for the field @c m_##name, of type @p type, with the name @c Get##name
#define CONSTEXPR_GETTER_M(type, name) CONSTEXPR_GETTER(type, name, m_##name)

/// @brief Defines a static constexpr getter for the field @p internalName, of type @p type, with the name @c Get##name
#define STATIC_CONSTEXPR_GETTER(type, name, internalName) GETTER_HELPER(type, static constexpr, , name, internalName)
/// @brief Defines a static constexpr getter for the field @c m_##name, of type @p type, with the name @c Get##name
#define STATIC_CONSTEXPR_GETTER_M(type, name, internalName) STATIC_CONSTEXPR_GETTER(type, name, m_##name)

/// @brief Defines getters for the field @p internalName, of type @p type, with the name @c Get##name.
/// One getter is @c const and returns a @c const value.
#define GETTER_NON_CONST(type, name, internalName) \
    ATTRIBUTE_NODISCARD type Get##name() noexcept { return internalName; } \
    GETTER(const type, name, internalName)
/// @brief Defines getters for the field @p internalName, of type @p type, with the name @c Get##name.
/// One getter is @c const and returns a @c const value.
#define GETTER_NON_CONST_M(type, name) GETTER_NON_CONST(type, name, m_##name)

// Undefine any Windows interface macro
#undef interface

/// @brief Defines an interface; that is a class that only has public pure virtual member functions.
///
/// This is only a struct under the hood because it declares public members by default and allows for
/// operators to be defined, whereas the @c __interface Microsoft extension doesn't.
/// Also, because an interface isn't supposed to provide implementations for any of the functions it
/// declares, it has the @c novtable specification.
///
/// @see https://learn.microsoft.com/en-us/cpp/cpp/novtable
#define interface struct __declspec(novtable)

/// @brief Defines a default virtual destructor.
/// @param type The type to default the destructor of.
#define DEFAULT_VIRTUAL_DESTRUCTOR(type) virtual ~type() = default;

/// @brief Returns the given parameter converted to string, as if double-quotes had been put around it.
/// @details For example, see the @c MOUNTAIN_VERSION_STRING macro. It is declared as @c STRINGIFY(MOUNTAIN_VERSION).
/// If the declaration was using @c TO_STRING() instead, the result would've been @c "MOUNTAIN_VERSION".
#define TO_STRING(x) #x
/// @brief Returns the given parameter's value converted to string, as if double-quotes had been put around its result.
/// @details For example, see the @c MOUNTAIN_VERSION_STRING macro. It is declared as @c STRINGIFY(MOUNTAIN_VERSION).
/// Because the declaration is using @c STRINGIFY(), the result is the value of @c MOUNTAIN_VERSION, converted to string.
#define STRINGIFY(x) TO_STRING(x)

#define TO_WSTRING(x) L#x
#define WSTRINGIFY(x) TO_WSTRING(x)

#define RAW_STRING_HELPER(x) R ## #x
#define TO_RAW_STRING(x) RAW_STRING_HELPER((x))

#define RAW_WSTRING_HELPER(x) LR ## #x
#define TO_RAW_WSTRING(x) RAW_WSTRING_HELPER((x))

/// @brief Gets a temporary C null-terminated string from a @c std::string_view.
#define STRING_VIEW_TO_C_STR(view) ::std::string{view}.c_str()

/// @brief Gets a temporary C null-terminated string from a @c std::wstring_view.
#define WSTRING_VIEW_TO_C_STR(view) ::std::wstring{view}.c_str()

/// @brief Override default ImGui config header
#define IMGUI_USER_CONFIG "Mountain/ImGuiConfig.hpp"

#define MOUNTAIN_VERSION_STRING STRINGIFY(MOUNTAIN_VERSION)
#define MOUNTAIN_VERSION_WSTRING WSTRINGIFY(MOUNTAIN_VERSION)

#define DEBUG_BREAK() raise(SIGTRAP)
