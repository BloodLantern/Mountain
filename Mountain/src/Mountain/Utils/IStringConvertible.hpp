#pragma once

#include <string>

#include "Mountain/Core.hpp"
#include "Mountain/Exceptions/Exception.hpp"
#include "Mountain/Utils/MetaProgramming.hpp"

namespace Mountain
{
    /// @brief Returns a string that represents the given object.
    template <typename T>
    [[nodiscard]]
    std::string ToString(const T&)
    {
        // ReSharper disable once CppStaticAssertFailure
        static_assert(false, "The ToString() function hasn't been specialized for this type");
    }
}

// ReSharper disable CppMemberFunctionMayBeStatic
// ReSharper disable CppClangTidyCertDcl58Cpp

/// @brief @c std::formatter template specialization for the @c Mountain::IStringConvertible interface.
/// @details The real goal of this formatter specialization is to allow any class that implements @c Mountain::IStringConvertible
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
            throw Mountain::FormatException{"Invalid format arguments for Mountain::IStringConvertible"};

        return it;
    }

    /// @brief Formats a string using the given instance of @c Mountain::IStringConvertible, according to the given options in the parse function.
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
