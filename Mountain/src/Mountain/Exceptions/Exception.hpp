#pragma once

#include <exception>

#include "Mountain/Core.hpp"
#include "Mountain/Utils/MetaProgramming.hpp"

// ReSharper disable CppClangTidyBugproneMacroParentheses
#define DECLARE_EXCEPTION_NAME(exceptionType) ATTRIBUTE_NODISCARD const char_t* GetName() const noexcept override { return #exceptionType; }

#define DECLARE_DEFAULT_EXCEPTION(exceptionType, parentType) \
    class exceptionType : public parentType \
    { \
        using parentType::parentType; \
         \
        DECLARE_EXCEPTION_NAME(exceptionType) \
    }
// ReSharper enable CppClangTidyBugproneMacroParentheses

namespace Mountain
{
    struct ExceptionState
    {
        const char_t* function = nullptr;
        const char_t* file = nullptr;
        int line = -1;
    };

    inline ExceptionState currentException;

    /// @brief Represents errors that occur during application execution.
    class Exception : public std::exception
    {
    public:
        ATTRIBUTE_NODISCARD
        MOUNTAIN_API Exception() noexcept;
        ATTRIBUTE_NODISCARD
        MOUNTAIN_API Exception(Exception&& other) noexcept = default;
        ATTRIBUTE_NODISCARD
        MOUNTAIN_API Exception& operator=(Exception&& other) noexcept = default;
        MOUNTAIN_API ~Exception() override = default;

        ATTRIBUTE_NODISCARD
        MOUNTAIN_API Exception(const Exception& other) noexcept;
        ATTRIBUTE_NODISCARD
        MOUNTAIN_API Exception& operator=(const Exception& other) noexcept;

        ATTRIBUTE_NODISCARD
        MOUNTAIN_API explicit Exception(const char_t* message) noexcept;

        ATTRIBUTE_NODISCARD
        MOUNTAIN_API const char_t* GetMessage() const noexcept;
        ATTRIBUTE_NODISCARD
        MOUNTAIN_API const ExceptionState& GetState() const noexcept;

        ATTRIBUTE_NODISCARD
        virtual const char_t* GetName() const noexcept { return "Exception"; }

    private:
        ExceptionState m_State;

        void SetStateCurrent() noexcept;
    };

    /// @brief The exception that is thrown when a method call is invalid for the object's current state.
    DECLARE_DEFAULT_EXCEPTION(InvalidOperationException, Exception);

    /// @brief The exception that is thrown when a value of a @c Globals variable is invalid.
    DECLARE_DEFAULT_EXCEPTION(InvalidGlobalValueException, InvalidOperationException);

    /// @brief The exception that is thrown when a requested method or operation is not implemented.
    DECLARE_DEFAULT_EXCEPTION(NotImplementedException, Exception);

    DECLARE_DEFAULT_EXCEPTION(FormatException, Exception);

    DECLARE_DEFAULT_EXCEPTION(OverflowException, Exception);

    DECLARE_DEFAULT_EXCEPTION(OutOfMemoryException, Exception);
}

/// @brief @c std::formatter template specialization for the @c Mountain::ExceptionState type.
template <>
struct std::formatter<Mountain::ExceptionState>  // NOLINT(cert-dcl58-cpp)
{
    /// @brief Parses the input formatting options.
    template <class ParseContext>
    constexpr typename ParseContext::iterator parse(ParseContext& ctx)
    {
        auto it = ctx.begin();
        if (it == ctx.end())
            return it;

        if (*it != '}')
            throw Mountain::FormatException{"Invalid format arguments for Exception"};

        return it;
    }

    /// @brief Formats a string using the given instance of @c Mountain::Exception, according to the given options in the parse function.
    template <class FormatContext>
    // ReSharper disable once CppMemberFunctionMayBeStatic
    typename FormatContext::iterator format(const Mountain::ExceptionState& state, FormatContext& ctx) const
    {
        std::ostringstream out;

        out << std::format("{}:{} (Function {})", state.file, state.line, state.function);

        return std::ranges::copy(std::move(out).str(), ctx.out()).out;
    }
};

/// @brief @c std::formatter template specialization for the @c Mountain::Exception type.
template <Mountain::Concepts::MountainException ExceptionT>
struct std::formatter<ExceptionT>  // NOLINT(cert-dcl58-cpp)
{
    /// @brief Parses the input formatting options.
    template <class ParseContext>
    constexpr typename ParseContext::iterator parse(ParseContext& ctx)
    {
        auto it = ctx.begin();
        if (it == ctx.end())
            return it;

        if (*it != '}')
            throw Mountain::FormatException{"Invalid format arguments for Exception"};

        return it;
    }

    /// @brief Formats a string using the given instance of @c Mountain::Exception, according to the given options in the parse function.
    template <class FormatContext>
    // ReSharper disable once CppMemberFunctionMayBeStatic
    typename FormatContext::iterator format(const ExceptionT& ex, FormatContext& ctx) const
    {
        std::ostringstream out;

        const Mountain::ExceptionState& state = ex.GetState();
        out << "Exception of type "
            << ex.GetName()
            << " occured at "
            << state.file
            << ':'
            << state.line
            << " (Function "
            << state.function
            << "): "
            << ex.GetMessage();

        return std::ranges::copy(std::move(out).str(), ctx.out()).out;
    }
};
