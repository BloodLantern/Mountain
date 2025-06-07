#pragma once

#include "Mountain/Core.hpp"
#include "Mountain/Exceptions/Exception.hpp"
#include "Mountain/Exceptions/ArgumentException.hpp"
#include "Mountain/Utils/MetaProgramming.hpp"

/// @brief Macro used to throw Mountain Exceptions.
///
/// This macro should be used in the following way:
/// @code
/// THROW(Exception{"Message"});
/// @endcode
/// Or, in case of an exception that requires multiple parameters, add surrounding parentheses:
/// @code
/// THROW((ArgumentException{"Message", parameter}));
/// @endcode
/// You can use any exception type,
/// but it is recommended to only use exceptions that inherit from @c Mountain::Exception.
/// Here is a short list:
/// - @c Exception
/// - @c InvalidOperationException
/// - @c ArgumentException
/// - @c ArgumentNullException
/// - @c ArgumentOutOfRangeException
#define THROW(exception) \
    do \
    { \
        const auto ex = exception; \
        static_assert(::Mountain::Meta::IsException<decltype(ex)>); \
        ::Mountain::currentException = {__FUNCTION__, __FILE__, __LINE__}; \
        throw ex; \
    } \
    while (false)

#define ENSURE_NOT_NULL(pointerParameter) \
    do \
    { \
        static_assert(::Mountain::Meta::IsPointer<decltype(pointerParameter)>); \
        if (!(pointerParameter)) \
            THROW((ArgumentNullException{"Parameter " #pointerParameter " cannot be null", #pointerParameter})); \
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
        /// @brief Returns an @c InvalidOperationException with the message: "The container has been modified while iterating over it."
        THROW_HELPER_FUNC(ContainerModified, InvalidOperationException, "The container has been modified while iterating over it.")
    };
}

#undef THROW_HELPER_FUNC
