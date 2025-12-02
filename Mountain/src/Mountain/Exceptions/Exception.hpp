#pragma once

#include <exception>

#include "Mountain/Core.hpp"

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
    struct MOUNTAIN_API ExceptionState
    {
        const char_t* function = nullptr;
        const char_t* file = nullptr;
        int32_t line = -1;

        ATTRIBUTE_NODISCARD
        std::string ToString() const;
    };

    MOUNTAIN_API void SetCurrentExceptionState(const ExceptionState& state);
    MOUNTAIN_API void SetCurrentExceptionState(const char_t* function, const char_t* file, int32_t line);

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

        ATTRIBUTE_NODISCARD
        MOUNTAIN_API std::string ToString() const;

    private:
        ExceptionState m_State;

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
