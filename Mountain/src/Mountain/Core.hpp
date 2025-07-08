// ReSharper disable CppClangTidyBugproneMacroParentheses
#pragma once

#include <cmath>
#include <cstdint>
#include <functional>

/// @file Core.hpp
/// @brief This file is meant to be included by every single other header file of this project.
///
/// It includes the standard headers @c \<cmath> and @c \<cstdint> so that types such as
/// @c int8_t or @c float_t are defined. It also defines typedefs for char_t and
/// bool_t, as they aren't defined by those standard headers.
///
/// Apart from typedefs, this file declares macros ranging from necessary (MOUNTAIN_API)
/// to useful and of general-use (DEFAULT_COPY_MOVE_OPERATIONS).

// ReSharper disable once CppEnforceTypeAliasCodeStyle
/// @brief Equivalent to <c>char</c>.
///
/// ### Reason
/// We use a typedef here instead of a type alias for consistency
/// with how the other integral types are defined in the <c>cstdint</c> header.
/// Also, we need to manually add this type because it is considered
/// different to <c>int8_t</c> as the latter is the equivalent of <c>signed char</c>
/// and not <c>char</c>.
typedef char char_t;

// ReSharper disable once CppEnforceTypeAliasCodeStyle
/// @brief Equivalent to <c>bool</c>.
///
/// @see char_t for the reason.
typedef bool bool_t;

/// @brief Macro used for DLL export/import.
///
/// This macro should be used at the beginning of static member variable and non-inline function declarations.
#ifdef MOUNTAIN_EXPORT
#define MOUNTAIN_API __declspec(dllexport)
#else
#define MOUNTAIN_API __declspec(dllimport)
#endif

/// @namespace Mountain
/// @brief Contains all declarations of the Mountain Framework.
namespace Mountain {}

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
#define DEFAULT_COPY_MOVE_OPERATIONS(type)                  \
    type(const type& other) noexcept = default;             \
    type(type&& other) noexcept = default;                  \
    type& operator=(const type& other) noexcept = default;  \
    type& operator=(type&& other) noexcept = default;

#define DEFAULT_VIRTUAL_COPY_MOVE_OPERATIONS(type)                  \
    type(const type& other) noexcept = default;                     \
    type(type&& other) noexcept = default;                          \
    virtual type& operator=(const type& other) noexcept = default;  \
    virtual type& operator=(type&& other) noexcept = default;

/// @brief Deletes the copy and move operations of a given @p type.
///
/// @param type The type to delete the copy and move operations of.
///
/// @see @ref DEFAULT_COPY_MOVE_OPERATIONS for usage.
#define DELETE_COPY_MOVE_OPERATIONS(type)          \
    type(const type& other) = delete;              \
    type(type&& other) = delete;                   \
    type& operator=(const type& other) = delete;   \
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
#define STATIC_CLASS(type)              \
    public:                             \
    type() = delete;                    \
    ~type() = delete;                   \
    DELETE_COPY_MOVE_OPERATIONS(type)   \
    private:

// We need this to be able to make Doxygen links to std::string conversion operators.
#ifdef DOXYGEN
/// @private
using stdstring = std::string;
#endif

/// @brief Defines binary flag operators for an enum type
/// @param enumName The enum
///
/// This macro **must** be used in the global namespace, as it declares a template specialization of magic_enum
#define ENUM_FLAGS(enumName)                                                                                                                                                                                                \
    static_assert(std::is_enum_v<enumName>, "enumName must be a valid enum type");                                                                                                                                          \
                                                                                                                                                                                                                            \
    inline std::underlying_type_t<enumName> operator&(const enumName left, const enumName right) { return static_cast<std::underlying_type_t<enumName>>(left) & static_cast<std::underlying_type_t<enumName>>(right); }     \
    inline std::underlying_type_t<enumName> operator|(const enumName left, const enumName right) { return static_cast<std::underlying_type_t<enumName>>(left) | static_cast<std::underlying_type_t<enumName>>(right); }     \
    inline std::underlying_type_t<enumName> operator&(const std::underlying_type_t<enumName> left, const enumName right) { return left & static_cast<std::underlying_type_t<enumName>>(right); }                            \
    inline std::underlying_type_t<enumName> operator|(const std::underlying_type_t<enumName> left, const enumName right) { return left | static_cast<std::underlying_type_t<enumName>>(right); }                            \
    inline std::underlying_type_t<enumName> operator&(const enumName left, const std::underlying_type_t<enumName> right) { return static_cast<std::underlying_type_t<enumName>>(left) & right; }                            \
    inline std::underlying_type_t<enumName> operator|(const enumName left, const std::underlying_type_t<enumName> right) { return static_cast<std::underlying_type_t<enumName>>(left) | right; }                            \
    inline std::underlying_type_t<enumName>& operator&=(std::underlying_type_t<enumName>& left, const enumName right) { return left = left & right; }                                                                       \
    inline std::underlying_type_t<enumName>& operator|=(std::underlying_type_t<enumName>& left, const enumName right) { return left = left | right; }                                                                       \
                                                                                                                                                                                                                            \
    template <>                                                                                                                                                                                                             \
    struct magic_enum::customize::enum_range<enumName>                                                                                                                                                                      \
    {                                                                                                                                                                                                                       \
        static constexpr bool is_flags = true;                                                                                                                                                                              \
    };

// TODO - Add comparison operators for enum flags

/// @brief Defines global definitions that make OpenGL use the dedicated GPU instead of the integrated one
/// Source: https://www.reddit.com/r/opengl/comments/unc3fy/comment/i8728y3/?utm_source=share&utm_medium=web3x&utm_name=web3xcss&utm_term=1&utm_content=share_button
#define USE_DEDICATED_GPU                                                       \
    extern "C"                                                                  \
    {                                                                           \
        _declspec(dllexport) uint32_t NvOptimusEnablement = 1;                  \
        _declspec(dllexport) int32_t AmdPowerXpressRequestHighPerformance = 1;  \
    }

#ifdef MOUNTAIN_EXPORT
#define PUBLIC_GLOBAL(varType, varName, defaultValue) MOUNTAIN_API inline varType varName = defaultValue;
#else
#define PUBLIC_GLOBAL(varType, varName, defaultValue) MOUNTAIN_API varType varName;
#endif

#define GETTER(type, name, internalName) [[nodiscard]] type Get##name() const noexcept { return internalName; }
#define SETTER(type, name, internalName) void Set##name(const type new##name) noexcept { internalName = new##name; }
#define GETTER_SETTER(type, name, internalName) GETTER(type, name, internalName) SETTER(type, name, internalName)

#define STATIC_GETTER(type, name, internalName) [[nodiscard]] static type Get##name() noexcept { return internalName; }
#define STATIC_SETTER(type, name, internalName) static void Set##name(const type new##name) noexcept { internalName = new##name; }
#define STATIC_GETTER_SETTER(type, name, internalName) STATIC_GETTER(type, name, internalName) STATIC_SETTER(type, name, internalName)

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

#define DEFAULT_VIRTUAL_DESTRUCTOR(type) virtual ~type() = default;

#if defined(__JETBRAINS_IDE__) || defined(__RESHARPER__)
#define ATTRIBUTE_FORMAT(archetype, stringIndex, firstToCheck) [[jetbrains::format(archetype, stringIndex, firstToCheck)]]
#define ATTRIBUTE_PASS_BY_VALUE [[jetbrains::pass_by_value]
#define ATTRIBUTE_GUARD [[jetbrains::guard]]
#define ATTRIBUTE_HAS_SIDE_EFFECTS [[jetbrains::has_side_effects]]
#else
#define ATTRIBUTE_FORMAT(...)
#define ATTRIBUTE_PASS_BY_VALUE
#define ATTRIBUTE_GUARD
#define ATTRIBUTE_HAS_SIDE_EFFECTS
#endif
