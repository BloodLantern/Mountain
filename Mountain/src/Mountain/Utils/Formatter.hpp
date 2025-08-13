// ReSharper disable CppMemberFunctionMayBeStatic
// ReSharper disable CppClangTidyCertDcl58Cpp
#pragma once

#include <filesystem>
#include <format>
#include <sstream>

#include <magic_enum/magic_enum.hpp>

#include "Mountain/Utils/MetaProgramming.hpp"

/// @file Formatter.hpp
/// @brief Defines template specializations of @c std::formatter for external types.
///
/// This file also defines the Formattable concept, as it seems it isn't included in the C++23 MSVC STL.
///
/// In this file, we don't follow our conventions on some things because it is mostly an extension of the STL.
///
/// @see <a href="https://en.cppreference.com/w/cpp/utility/format/formatter">std::formatter</a>
/// @see <a href="https://en.cppreference.com/w/cpp/utility/format/formattable">std::formattable</a>

/// @brief @c std::formatter template specialization for the @c std::filesystem::path type.
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
            throw Mountain::FormatException{"Invalid format arguments for std::filesystem::path"};

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
/// @note This is a different specialization than the one for @c Mountain::Exception.
/// @see <a href="https://en.cppreference.com/w/cpp/error/exception">std::exception</a>
template <Mountain::Concepts::StandardException ExceptionT>
struct std::formatter<ExceptionT>
{
    /// @brief Parses the input formatting options.
    template <class ParseContext>
    constexpr typename ParseContext::iterator parse(ParseContext& ctx)
    {
        auto it = ctx.begin();
        if (it == ctx.end())
            return it;

        if (*it != '}')
            throw Mountain::FormatException{"Invalid format arguments for std::exception"};

        return it;
    }

    /// @brief Formats a string using the given instance of @c std::exception, according to the given options in the parse function.
    template <class FormatContext>
    typename FormatContext::iterator format(const ExceptionT& ex, FormatContext& ctx) const
    {
        std::ostringstream out;

        out << ex.what();

        return std::ranges::copy(std::move(out).str(), ctx.out()).out;
    }
};

/// @brief @c std::formatter template specialization for any @c enum type.
/// @details This prints the @c enum value as a string using @c magic_enum::enum_name(), or as an integer if the @c d format is used.
template <Mountain::Concepts::Enum EnumT>
struct std::formatter<EnumT>
{
    /// @brief Parses the input formatting options.
    template <class ParseContext>
    constexpr typename ParseContext::iterator parse(ParseContext& ctx)
    {
        auto it = ctx.begin();
        if (it == ctx.end())
            return it;

        if (*it == ':')
        {
            it++;
            if (*it != 'd')
                throw Mountain::FormatException{"Invalid format arguments for enum"};

            m_PrintAsInteger = true;
            it++;
        }

        if (*it != '}')
            throw Mountain::FormatException{"Invalid format arguments for enum"};

        return it;
    }

    /// @brief Formats a string using the given @c enum value, according to the given options in the parse function.
    template <class FormatContext>
    typename FormatContext::iterator format(const EnumT& e, FormatContext& ctx) const
    {
        std::ostringstream out;

        if (m_PrintAsInteger)
            out << static_cast<Mountain::Meta::UnderlyingEnumType<EnumT>>(e);
        else
            out << magic_enum::enum_name(e);

        return std::ranges::copy(std::move(out).str(), ctx.out()).out;
    }

private:
    bool_t m_PrintAsInteger = false;
};
