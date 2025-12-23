

#include "Mountain/Exceptions/ArgumentException.hpp"

using namespace Mountain;

ArgumentException::ArgumentException(
    const c8* message,
    const c8* parameterName
) noexcept
    : Exception(message)
    , m_ParameterName(parameterName)
{
}

const c8* ArgumentException::GetParameterName() const noexcept { return m_ParameterName; }
