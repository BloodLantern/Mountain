#pragma once

#include <exception>
#include <string>

#include "Mountain/Core.hpp"

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
        [[nodiscard]]
        MOUNTAIN_API Exception() noexcept;
        [[nodiscard]]
        MOUNTAIN_API Exception(Exception&& other) noexcept = default;
        [[nodiscard]]
        MOUNTAIN_API Exception& operator=(Exception&& other) noexcept = default;
        MOUNTAIN_API ~Exception() override = default;

        [[nodiscard]]
        MOUNTAIN_API Exception(const Exception& other) noexcept;
        [[nodiscard]]
        MOUNTAIN_API Exception& operator=(const Exception& other) noexcept;

        [[nodiscard]]
        MOUNTAIN_API explicit Exception(const char_t* message) noexcept;

        [[nodiscard]]
        MOUNTAIN_API const char_t* GetMessage() const noexcept;
        [[nodiscard]]
        MOUNTAIN_API const ExceptionState& GetState() const noexcept;

    private:
        ExceptionState m_State;

        void SetStateCurrent() noexcept;
    };

    /// @brief The exception that is thrown when a method call is invalid for the object's current state.
    DECLARE_DEFAULT_EXCEPTION(InvalidOperationException, Exception)

    /// @brief The exception that is thrown when a value of a @c Globals variable is invalid.
    DECLARE_DEFAULT_EXCEPTION(InvalidGlobalValueException, InvalidOperationException)

    /// @brief The exception that is thrown when a requested method or operation is not implemented.
    DECLARE_DEFAULT_EXCEPTION(NotImplementedException, Exception)

    DECLARE_DEFAULT_EXCEPTION(RuntimeError, Exception)
}
