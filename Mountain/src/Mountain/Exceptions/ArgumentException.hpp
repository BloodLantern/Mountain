#pragma once

#include "Mountain/Core.hpp"
#include "Mountain/Exceptions/Exception.hpp"

namespace Mountain
{
    /// @brief The exception that is thrown when one of the arguments provided to a method is not valid.
    class ArgumentException : public Exception
    {
        using Exception::Exception;

    public:
        ATTRIBUTE_NODISCARD
        MOUNTAIN_API ArgumentException(const char_t* message, const char_t* parameterName) noexcept;

        ATTRIBUTE_NODISCARD
        MOUNTAIN_API const char_t* GetParameterName() const noexcept;

        DECLARE_EXCEPTION_NAME(ArgumentException)

    private:
        const char_t* m_ParameterName = nullptr;
    };

    /// @brief The exception that is thrown when a null pointer is passed to a method that does not accept it as a
    /// valid argument.
    DECLARE_DEFAULT_EXCEPTION(ArgumentNullException, ArgumentException);

    /// @brief The exception that is thrown when the value of an argument is outside the allowable range of values
    /// as defined by the invoked method.
    DECLARE_DEFAULT_EXCEPTION(ArgumentOutOfRangeException, ArgumentException);
}
