#include "Mountain/PrecompiledHeader.hpp"

#include "Mountain/Exceptions/Exception.hpp"

using namespace Mountain;

namespace
{
    ExceptionState currentException;
}

std::string ExceptionState::ToString() const
{
    return std::format("{}:{} (Function {})", file, line, function);
}

void Mountain::SetCurrentExceptionState(const ExceptionState& state)
{
    currentException = state;

    // If we set the current exception state, we can assume an exception will be thrown very soon.
    // For debugging purposes, we synchronize the logs to make sure the output stream is flushed when the exception is thrown.
    Logger::Synchronize();
}

void Mountain::SetCurrentExceptionState(const char_t* function, const char_t* file, int32_t line)
{
    return SetCurrentExceptionState(ExceptionState{function, file, line});
}

Exception::Exception() noexcept { SetStateCurrent(); }

Exception::Exception(const Exception& other) noexcept : exception(other) { m_State = other.m_State; }

Exception& Exception::operator=(const Exception& other) noexcept
{
    if (this == &other)
        return *this;

    exception::operator=(other);

    m_State = other.m_State;

    return *this;
}

Exception::Exception(const char_t* message) noexcept : exception(message) { SetStateCurrent(); }

const char_t* Exception::GetMessage() const noexcept { return what(); }

const ExceptionState& Exception::GetState() const noexcept { return m_State; }

std::string Exception::ToString() const
{
    return std::format("Exception of type {} occured at {}: {}", GetName(), m_State, GetMessage());
}

void Exception::SetStateCurrent() noexcept { m_State = currentException; }
