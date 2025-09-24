#pragma once

#include "Mountain/Core.hpp"
#include "Mountain/Exceptions/ArgumentException.hpp"
#include "Mountain/Exceptions/Exception.hpp"
// ReSharper disable once CppUnusedIncludeDirective
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
///
/// In a @c constexpr context, instead use the classic @c throw.
#define THROW(...) \
    do \
    { \
        const auto ex = __VA_ARGS__; \
        static_assert(::Mountain::Meta::IsException<DECLARING_TYPE(ex)>, "The argument of THROW must be an exception value"); \
        ::Mountain::SetCurrentExceptionState(__FUNCTION__, __FILE__, __LINE__); \
        throw ex; \
    } \
    while (false)

#define ENSURE_NOT_NULL(pointerParameter) \
    do \
    { \
        static_assert(::Mountain::Meta::IsPointer<DECLARING_TYPE(pointerParameter)>, "The argument of ENSURE_NOT_NULL must be a pointer"); \
        if (!(pointerParameter)) \
            THROW(ArgumentNullException{"Parameter " #pointerParameter " cannot be null", #pointerParameter}); \
    } \
    while (false)

#define CHECK_OPTIONAL(optionalParameter) \
    do \
    { \
        using Type = DECLARING_TYPE(optionalParameter); \
        constexpr const bool_t standard = ::Mountain::Meta::IsStandardOptional<Type>; \
        static_assert(standard || ::Mountain::Meta::IsMountainOptional<Type>, "The argument of CHECK_OPTIONAL must be a either a std::optional or a Mountain::Optional"); \
         \
        bool_t noValue = false; \
        if constexpr (standard) \
        { \
            if (!(optionalParameter).has_value()) \
                noValue = true; \
        } \
        else \
        { \
            if (!(optionalParameter).HasValue()) \
                noValue = true; \
        } \
         \
        if (noValue) \
            THROW(ArgumentNullException{"Parameter " #optionalParameter " must have a value", #optionalParameter}); \
    } \
    while (false)

#define THROW_HELPER_FUNC(functionName, exceptionType, message) \
    static exceptionType functionName##Exception() { return exceptionType{message}; }  // NOLINT(bugprone-macro-parentheses)

#define THROW_HELPER_FUNC_ARG(functionName, argumentExceptionType, message) \
    static argumentExceptionType functionName##Exception(const char_t* argumentName) { return argumentExceptionType{message, argumentName}; }  // NOLINT(bugprone-macro-parentheses)

namespace Mountain
{
    /// @brief Contains helper functions that return exceptions with preset messages.
    class MOUNTAIN_API ThrowHelper
    {
        STATIC_CLASS(ThrowHelper)

    public:
        THROW_HELPER_FUNC(InvalidIterator, InvalidOperationException, "The given iterator is invalid for this container.")
        THROW_HELPER_FUNC_ARG(IndexOutOfRange, ArgumentOutOfRangeException, "The given index is out of range for this container.")
        THROW_HELPER_FUNC(OptionalNoValue, EmptyOptionalAccess, "Cannot get the value of an empty Optional.")
    };
}

#undef THROW_HELPER_FUNC
