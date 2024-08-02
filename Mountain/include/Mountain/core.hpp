// ReSharper disable CppClangTidyBugproneMacroParentheses
#pragma once

#include <cmath>
#include <cstdint>
#include <functional>

/// @file core.hpp
/// @brief This file is meant to be included by every single other header file of this project.
///
/// It includes the standard headers @c \<cmath> and @c \<cstdint> so that types such as
/// @c int8_t or @c float_t are defined. It also defines typedefs for @ref char_t and
/// @ref bool_t, as they aren't defined by those standard headers.
///
/// Apart from typedefs, this file declares macros ranging from necessary (@ref MOUNTAIN_API)
/// to useful and of general-use (@ref DEFAULT_COPY_MOVE_OPERATIONS).

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
/// @see @ref char_t for reason.
typedef bool bool_t;

using Action = std::function<void()>;

/// @brief Macro used for DLL export/import.
///
/// This macro should be used at the beginning of static member variable and non-inline function declarations.
#ifdef MOUNTAIN_EXPORT
#define MOUNTAIN_API __declspec(dllexport)
#else
#define MOUNTAIN_API __declspec(dllimport)
#endif

/// @brief Starts the @ref Mountain namespace.
#define BEGIN_MOUNTAIN namespace Mountain {

/// @brief Ends the @ref Mountain namespace.
#define END_MOUNTAIN }

/// @namespace Mountain
/// @brief Contains all declarations of the Mountain Framework.
namespace Mountain {}

/// @brief Creates default copy and move operations for a given @p type.
///
/// ### Usage
/// This macro should be used for any type that defines at least one of:
/// - A non-default destructor (this includes default implementations),
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
///     
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
///     
///     A(int);
///
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

/// @brief Macro used to declare a static class, e.g. a class that cannot be instantiated.
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

// We need this in order to be able to make Doxygen links to std::string conversion operators.
#ifdef DOXYGEN
/// @private
using stdstring = std::string;
#endif

/// @brief Forwards a value with its own type as template.
#define FORWARD(value) std::forward<std::remove_reference_t<decltype(value)>>(value)

/// @brief Defines binary flag operators for an enum type
/// @param enumName The enum
/// @param integerType The integral type in which the flags are used
///
/// This macro **must** be used in the global namespace, as it declares a template specialization of magic_enum
#define ENUM_FLAGS(enumName, integerType)                                                                                                                   \
    inline integerType operator&(const enumName left, const enumName right) { return static_cast<integerType>(left) & static_cast<integerType>(right); }    \
    inline integerType operator|(const enumName left, const enumName right) { return static_cast<integerType>(left) | static_cast<integerType>(right); }    \
    inline integerType operator&(const integerType left, const enumName right) { return left & static_cast<integerType>(right); }                           \
    inline integerType operator|(const integerType left, const enumName right) { return left | static_cast<integerType>(right); }                           \
    inline integerType operator&(const enumName left, const integerType right) { return static_cast<integerType>(left) & right; }                           \
    inline integerType operator|(const enumName left, const integerType right) { return static_cast<integerType>(left) | right; }                           \
    inline integerType& operator&=(integerType& left, const enumName right) { return left = left & right; }                                                 \
    inline integerType& operator|=(integerType& left, const enumName right) { return left = left | right; }                                                 \
                                                                                                                                                            \
    template <>                                                                                                                                             \
    struct magic_enum::customize::enum_range<enumName>                                                                                                      \
    {                                                                                                                                                       \
        static constexpr bool is_flags = true;                                                                                                              \
    };

#define ENUM_COUNT(enumName) constexpr size_t enumName##Count = static_cast<size_t>(enumName::Count);
