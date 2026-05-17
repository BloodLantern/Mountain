#pragma once

#include <exception>

#include "Mountain/Core.hpp"

// ReSharper disable CppClangTidyBugproneMacroParentheses
#define DECLARE_EXCEPTION_NAME(exceptionType) ATTRIBUTE_NODISCARD const c8* GetName() const noexcept override { return #exceptionType; }

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
    struct MOUNTAIN_API ExceptionState
    {
        const c8* function = nullptr;
        const c8* file = nullptr;
        s32 line = -1;

        ATTRIBUTE_NODISCARD
        std::string ToString() const;
    };

    MOUNTAIN_API void SetCurrentExceptionState(const ExceptionState& state);
    MOUNTAIN_API void SetCurrentExceptionState(const c8* function, const c8* file, s32 line);

    /// @brief Represents errors that occur during application execution.
    class Exception : public std::exception
    {
    public:
        ATTRIBUTE_NODISCARD
        MOUNTAIN_API Exception() noexcept;
        ATTRIBUTE_NODISCARD
        Exception(Exception&& other) noexcept = default;
        ATTRIBUTE_NODISCARD
        Exception& operator=(Exception&& other) noexcept = default;
        ~Exception() override = default;

        ATTRIBUTE_NODISCARD
        MOUNTAIN_API Exception(const Exception& other) noexcept;
        ATTRIBUTE_NODISCARD
        MOUNTAIN_API Exception& operator=(const Exception& other) noexcept;

        ATTRIBUTE_NODISCARD
        MOUNTAIN_API explicit Exception(const c8* message) noexcept;

        ATTRIBUTE_NODISCARD
        MOUNTAIN_API const c8* GetMessage() const noexcept;
        ATTRIBUTE_NODISCARD
        MOUNTAIN_API const ExceptionState& GetState() const noexcept;

        ATTRIBUTE_NODISCARD
        virtual const c8* GetName() const noexcept { return "Exception"; }

        ATTRIBUTE_NODISCARD
        MOUNTAIN_API std::string ToString() const;

    private:
        ExceptionState m_State;
#ifndef COMPILER_MSVC
        const c8* m_Message = "";
#endif

        void SetStateCurrent() noexcept;
    };

    /// @brief The exception that is thrown when a method call is invalid for the object's current state.
    DECLARE_DEFAULT_EXCEPTION(InvalidOperationException, Exception);

    /// @brief The exception that is thrown when a value of a global Mountain variable is invalid.
    DECLARE_DEFAULT_EXCEPTION(InvalidGlobalValueException, InvalidOperationException);

    /// @brief The exception that is thrown when a requested method or operation is not implemented.
    DECLARE_DEFAULT_EXCEPTION(NotImplementedException, Exception);

    DECLARE_DEFAULT_EXCEPTION(FormatException, Exception);

    DECLARE_DEFAULT_EXCEPTION(OverflowException, Exception);

    DECLARE_DEFAULT_EXCEPTION(OutOfMemoryException, Exception);

    DECLARE_DEFAULT_EXCEPTION(EmptyOptionalAccess, InvalidOperationException);
}

#include "Mountain/Utils/Requirements.hpp"

namespace Mountain
{
    CHECK_REQUIREMENT(Requirements::StringConvertible, ExceptionState);
    CHECK_REQUIREMENT(Requirements::StringConvertible, Exception);
}
