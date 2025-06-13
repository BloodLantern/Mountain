#pragma once

#include "Mountain/Core.hpp"
#include "Mountain/Exceptions/Exception.hpp"
#include "Mountain/Utils/MetaProgramming.hpp"

#define CHECK_REQUIREMENT(type, requirement) \
    static_assert(requirement<type>, "Type " #type " doesn't match the requirements of " #requirement)  // NOLINT(bugprone-macro-parentheses)

#define REQUIRES_FUNCTION_RETURN_TYPE(value, function, expectedReturnType) \
    value.function(); \
    { value.function() } -> expectedReturnType  // NOLINT(bugprone-macro-parentheses)

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
        REQUIRES_FUNCTION_RETURN_TYPE(cv, ToString, std::string);
    };

    /// @brief Requires a type to have a member @c GetHashCode() function that returns a @c size_t.
    template <typename T>
    concept Hashable = requires (const T& cv)
    {
        REQUIRES_FUNCTION_RETURN_TYPE(cv, GetHashCode, size_t);
    };

    template <typename T>
    concept Container = requires (T& v, const T& cv)
    {
        REQUIRES_FUNCTION_RETURN_TYPE(cv, GetSize, size_t);
    };

    template <typename T>
    concept Enumerator = requires (T& v, const T& cv)
    {
    };

    template <typename T>
    concept Enumerable = requires (T& v, const T& cv)
    {
        typename T::Enumerator;
        requires Enumerator<typename T::Enumerator>;
        REQUIRES_FUNCTION_RETURN_TYPE(v, GetEnumerator, std::shared_ptr<typename T::Enumerator>);
        REQUIRES_FUNCTION_RETURN_TYPE(cv, GetEnumerator, std::shared_ptr<const typename T::Enumerator>);
        REQUIRES_FUNCTION_RETURN_TYPE(v, begin, decltype(v.GetEnumerator()));
        REQUIRES_FUNCTION_RETURN_TYPE(cv, begin, decltype(v.GetEnumerator()));
        REQUIRES_FUNCTION_RETURN_TYPE(v, end, decltype(v.GetEnumerator()));
        REQUIRES_FUNCTION_RETURN_TYPE(cv, end, decltype(v.GetEnumerator()));
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
