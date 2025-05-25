#pragma once

#include "Mountain/Core.hpp"
#include "Mountain/Exceptions/Exception.hpp"
#include "Mountain/Exceptions/ArgumentException.hpp"
#include "Mountain/Utils/MetaProgramming.hpp"

/// @brief Macro used to throw Mountain Exceptions.
///
/// This macro should be used in the following way:
/// @code
/// THROW Exception{"Message"};
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
/// Also, a thing to note is that any use of this macro requires to be in a multi-line scope.
/// This means that you can't use it in a single-line @c if, @c for, @c while or any other similar statement.
/// For example, this doesn't work:
/// @code
/// if (condition)
///     THROW Exception{"Message"};
/// @endcode
/// Instead, do the following:
/// @code
/// if (condition)
/// {
///     THROW Exception{"Message"};
/// }
/// @endcode
#define THROW ::Mountain::currentException = {__FUNCTION__, __FILE__, __LINE__}; throw

#define ENSURE_NOT_NULL(pointerParameter) \
    static_assert(::Mountain::Meta::IsPointer<decltype(pointerParameter)>);\
    if (!(pointerParameter))\
    {\
        THROW ArgumentNullException{"Parameter " #pointerParameter " cannot be null", #pointerParameter};\
    }

#define THROW_HELPER_FUNC(functionName, exceptionType, message) \
    static exceptionType functionName##Exception() { return exceptionType{message}; }  // NOLINT(bugprone-macro-parentheses)

namespace Mountain
{
    class MOUNTAIN_API ThrowHelper
    {
        STATIC_CLASS(ThrowHelper)

    public:
        THROW_HELPER_FUNC(ContainerModified, InvalidOperationException, "The container has been modified while iterating over it.")

        void Func(int* param)
        {
            ENSURE_NOT_NULL(param)
        }
    };
}

#undef THROW_HELPER_FUNC
