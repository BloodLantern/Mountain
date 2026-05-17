#include "Mountain/Exceptions/Exception.hpp"

using namespace Mountain;

namespace
{
    thread_local ExceptionState currentException;
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

void Mountain::SetCurrentExceptionState(const c8* function, const c8* file, const s32 line)
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

Exception::Exception(const c8* message) noexcept
#ifdef COMPILER_MSVC
    : exception(message)
#else
    : m_Message{message}
#endif
{
    SetStateCurrent();
}

const c8* Exception::GetMessage() const noexcept { return what(); }

const ExceptionState& Exception::GetState() const noexcept { return m_State; }

std::string Exception::ToString() const
{
    return std::format("Exception of type {} occured at {}: {}", GetName(), m_State, GetMessage());
}

void Exception::SetStateCurrent() noexcept { m_State = currentException; }
