#pragma once

#include "Mountain/Core.hpp"
#include "Mountain/Exceptions/ArgumentException.hpp"
#include "Mountain/Exceptions/Exception.hpp"
#include "Mountain/Utils/MetaProgramming.hpp"

/// @brief Macro used to throw Mountain Exceptions.
///
/// This macro should be used in the following way:
/// @code
/// THROW(Exception{"Message"});
/// @endcode
/// You can use any exception type,
/// but it is recommended to only use exceptions that inherit from @c Mountain::Exception.
/// Here is a short list:
/// - @c Exception
/// - @c InvalidOperationException
/// - @c ArgumentException
/// - @c ArgumentNullException
/// - @c ArgumentOutOfRangeException
#define THROW(...) \
    do \
    { \
        const auto ex = __VA_ARGS__; \
        static_assert(::Mountain::Meta::IsException<decltype(ex)>, "The argument of THROW must be an exception value"); \
        ::Mountain::currentException = {__FUNCTION__, __FILE__, __LINE__}; \
        throw ex; \
    } \
    while (false)

#define ENSURE_NOT_NULL(pointerParameter) \
    do \
    { \
        static_assert(::Mountain::Meta::IsPointer<decltype(pointerParameter)>, "The argument of ENSURE_NOT_NULL must be a pointer"); \
        if (!(pointerParameter)) \
            THROW(ArgumentNullException{"Parameter " #pointerParameter " cannot be null", #pointerParameter}); \
    } \
    while (false)

#define THROW_HELPER_FUNC(functionName, exceptionType, message) \
    static exceptionType functionName##Exception() { return exceptionType{message}; }  // NOLINT(bugprone-macro-parentheses)

namespace Mountain
{
    /// @brief Contains helper functions that return exceptions with preset messages.
    class MOUNTAIN_API ThrowHelper
    {
        STATIC_CLASS(ThrowHelper)

    public:
        /// @brief Returns an @c InvalidOperationException with the message: "The given iterator is invalid for this container."
        THROW_HELPER_FUNC(InvalidIterator, InvalidOperationException, "The given iterator is invalid for this container.")
    };
}

#undef THROW_HELPER_FUNC
