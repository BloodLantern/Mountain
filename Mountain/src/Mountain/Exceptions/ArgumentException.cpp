#include "Mountain/PrecompiledHeader.hpp"

#include "Mountain/Exceptions/ArgumentException.hpp"

using namespace Mountain;

ArgumentException::ArgumentException(
    const char_t* message,
    const char_t* parameterName
) noexcept
    : Exception(message)
    , m_ParameterName(parameterName)
{
}

const char_t* ArgumentException::GetParameterName() const noexcept { return m_ParameterName; }
