// ReSharper disable CppMemberFunctionMayBeStatic
// ReSharper disable CppClangTidyCertDcl58Cpp
#pragma once

#include <filesystem>
#include <format>
#include <sstream>

#include "Mountain/Utils/Concepts.hpp"

/// @file Formatter.hpp
/// @brief Defines template specializations of @c std::formatter for external types.
///
/// This file also defines the Formattable concept, as it seems it isn't included in the C++23 MSVC STL.
///
/// In this file, we don't follow our conventions on some things because it is mostly an extension of the STL.
///
/// @see <a href="https://en.cppreference.com/w/cpp/utility/format/formatter">std::formatter</a>
/// @see <a href="https://en.cppreference.com/w/cpp/utility/format/formattable">std::formattable</a>

// These definitions must be in the std namespace

/// @brief @c std::formatter template specialization for the @c std::filesystem::path type.
///
/// @see <a href="https://en.cppreference.com/w/cpp/filesystem/path">std::filesystem::path</a>
template <>
struct std::formatter<std::filesystem::path>
{
    /// @brief Parses the input formatting options.
    template <class ParseContext>
    constexpr typename ParseContext::iterator parse(ParseContext& ctx)
    {
        auto it = ctx.begin();
        if (it == ctx.end())
            return it;

        if (*it != '}')
            throw std::format_error("Invalid format args for std::filesystem::path");

        return it;
    }

    /// @brief Formats a string using the given instance of @c std::filesystem::path, according to the given options in the parse function.
    template <class FormatContext>
    typename FormatContext::iterator format(const std::filesystem::path& path, FormatContext& ctx) const
    {
        std::ostringstream out;

        out << path.generic_string();

        return std::ranges::copy(std::move(out).str(), ctx.out()).out;
    }
};

/// @brief @c std::formatter template specialization for the @c std::exception type.
///
/// @see <a href="https://en.cppreference.com/w/cpp/error/exception">std::exception</a>
template <Mountain::Concepts::ExceptionT Exception>
struct std::formatter<Exception>
{
    /// @brief Parses the input formatting options.
    template <class ParseContext>
    constexpr typename ParseContext::iterator parse(ParseContext& ctx)
    {
        auto it = ctx.begin();
        if (it == ctx.end())
            return it;

        if (*it != '}')
            throw std::format_error("Invalid format args for std::exception");

        return it;
    }

    /// @brief Formats a string using the given instance of @c std::exception, according to the given options in the parse function.
    template <class FormatContext>
    typename FormatContext::iterator format(const Exception& ex, FormatContext& ctx) const
    {
        std::ostringstream out;

        out << ex.what();

        return std::ranges::copy(std::move(out).str(), ctx.out()).out;
    }
};
