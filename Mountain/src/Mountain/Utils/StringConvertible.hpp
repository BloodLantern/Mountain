#pragma once

#include "Mountain/Core.hpp"
#include "Mountain/Exceptions/Exception.hpp"

namespace Mountain::Concepts
{
    /// @brief Requires a type to have a member @c ToString() function.
    template <class T>
    concept StringConvertible = requires(const T& value)
    {
        value.ToString();
    };
}

// ReSharper disable CppMemberFunctionMayBeStatic
// ReSharper disable CppClangTidyCertDcl58Cpp

/// @brief @c std::formatter template specialization for the types that support @c ToString().
/// @details The real goal of this formatter specialization is to allow any type that provides a member function @c ToString()
/// to be used in a call to @c std::format().
template <Mountain::Concepts::StringConvertible StringConvertibleT>
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

// ReSharper enable CppMemberFunctionMayBeStatic
// ReSharper enable CppClangTidyCertDcl58Cpp
