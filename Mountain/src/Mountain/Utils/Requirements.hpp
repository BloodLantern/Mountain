#pragma once

#include "Mountain/Core.hpp"
#include "Mountain/Exceptions/Exception.hpp"

// ReSharper disable CppClangTidyBugproneMacroParentheses

#define CHECK_REQUIREMENT(type, requirement) \
    static_assert(requirement<type>, "Type " #type " doesn't match the requirements of " #requirement)

#define REQUIRES_FUNCTION(value, function, expectedReturnType, ...) \
    value.function(__VA_ARGS__); \
    { value.function(__VA_ARGS__) } -> expectedReturnType

#define REQUIRES_OPERATOR(value, operator, expectedReturnType, otherValue) \
    value operator otherValue; \
    { value operator otherValue } -> expectedReturnType

// ReSharper enable CppClangTidyBugproneMacroParentheses

namespace Mountain::Requirements
{
    /// @brief Requires a type to be formattable.
    /// @details A type @p T is considered formattable if a template specialization of @c std::formatter exists for @p T.
    template<typename T>
    concept Formattable = requires(T& v, std::format_context ctx)
    {
        std::formatter<std::remove_cvref_t<T>>().format(v, ctx);
    };

    /// @brief Requires a type to have a member @c ToString() function that returns a @c std::string.
    template <typename T>
    concept StringConvertible = requires (const T& cv)
    {
        REQUIRES_FUNCTION(cv, ToString, std::string);
    };

    /// @brief Requires a type to have a member @c GetHashCode() function that returns a @c size_t.
    template <typename T>
    concept Hashable = requires (const T& cv)
    {
        REQUIRES_FUNCTION(cv, GetHashCode, size_t);
    };

    template <typename T>
    concept Container = requires (T& v, const T& cv)
    {
        typename T::Type;
        requires Concepts::ContainerType<typename T::Type>;
        REQUIRES_FUNCTION(cv, GetSize, size_t);
    };

    template <typename T>
    concept Iterator = requires (T& v, const T& cv)
    {
        typename T::Type;
        requires Concepts::ContainerType<typename T::Type>;
        REQUIRES_FUNCTION(cv, GetCurrent, typename T::Type*);
        REQUIRES_FUNCTION(v, MoveNext, bool_t);
        REQUIRES_FUNCTION(v, Reset, void);
        REQUIRES_FUNCTION(cv, operator*, typename T::Type&);
        REQUIRES_FUNCTION(cv, operator->, typename T::Type*);
        // We don't care about the return type of both operator++
        ++v;
        v++;
        REQUIRES_OPERATOR(cv, ==, bool_t, cv);
        REQUIRES_OPERATOR(cv, !=, bool_t, cv);
        REQUIRES_OPERATOR(cv, <, bool_t, cv);
        REQUIRES_OPERATOR(cv, >, bool_t, cv);
        REQUIRES_OPERATOR(cv, <=, bool_t, cv);
        REQUIRES_OPERATOR(cv, >=, bool_t, cv);
    };

    template <typename T>
    concept Enumerable = requires (T& v, const T& cv)
    {
        typename T::Iterator;
        requires Iterator<typename T::Iterator>;
        REQUIRES_FUNCTION(cv, GetBeginIterator, typename T::Iterator);
        REQUIRES_FUNCTION(cv, GetEndIterator, typename T::Iterator);
        REQUIRES_FUNCTION(cv, begin, typename T::Iterator);
        REQUIRES_FUNCTION(cv, end, typename T::Iterator);
    };
}

// ReSharper disable CppMemberFunctionMayBeStatic
// ReSharper disable CppClangTidyCertDcl58Cpp

/// @brief @c std::formatter template specialization for the types that support @c ToString().
/// @details The real goal of this formatter specialization is to allow any type that provides a member function @c ToString()
/// to be used in a call to @c std::format().
template <Mountain::Requirements::StringConvertible StringConvertibleT>
struct std::formatter<StringConvertibleT>
{
    /// @brief Parses the input formatting options.
    template <class ParseContextT>
    constexpr typename ParseContextT::iterator parse(ParseContextT& ctx)
    {
        auto it = ctx.begin();
        if (it == ctx.end())
            return it;

        if (*it != '}')
            throw Mountain::FormatException{"Invalid format arguments for Mountain::ToString()"};

        return it;
    }

    /// @brief Formats a string using the given type supporting @c ToString(), according to the given options in the parse function.
    template <class FormatContextT>
    typename FormatContextT::iterator format(const StringConvertibleT& sc, FormatContextT& ctx) const
    {
        std::ostringstream out;

        out << sc.ToString();

        return std::ranges::copy(std::move(out).str(), ctx.out()).out;
    }
};

/// @brief @c std::hash template specialization for the types that support @c GetHashCode().
/// @details The real goal of this formatter specialization is to allow any type that provides a member function @c GetHashCode()
/// to be used in a call to @c std::hash::operator().
template<Mountain::Requirements::Hashable HashableT>
struct std::hash<HashableT>  // NOLINT(cert-dcl58-cpp)
{
    /// @brief Hashes the given type supporting @c GetHashCode().
    std::size_t operator()(const HashableT& p) const noexcept { return p.GetHashCode(); }
};

// ReSharper enable CppMemberFunctionMayBeStatic
// ReSharper enable CppClangTidyCertDcl58Cpp
