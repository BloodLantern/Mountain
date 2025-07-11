#include "Mountain/Core.hpp"

#include "Mountain/Exceptions/Exception.hpp"

using namespace Mountain;

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

void Exception::SetStateCurrent() noexcept { m_State = currentException; }
