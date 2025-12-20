#include "Mountain/PrecompiledHeader.hpp"

#include "Mountain/Utils/TimeSpan.hpp"

#include "Mountain/Exceptions/ThrowHelper.hpp"

using namespace Mountain;

std::string TimeSpan::ToString() const
{
    std::string result;

    const int64_t ticks = m_Ticks;
    const uint64_t absTicks = ticks >= 0 ? static_cast<uint64_t>(ticks) : 0ULL - static_cast<uint64_t>(ticks);

    if (ticks < 0)
        result += '-';

    const int32_t days = static_cast<int32_t>(absTicks / TicksPerDay);
    const int32_t hours = static_cast<int32_t>(absTicks / TicksPerHour % 24);
    const int32_t minutes = static_cast<int32_t>(absTicks / TicksPerMinute % 60);
    const int32_t seconds = static_cast<int32_t>(absTicks / TicksPerSecond % 60);
    const int32_t fractionalTicks = static_cast<int32_t>(absTicks % TicksPerSecond);

    if (days != 0)
        result += std::format("{}.", days);

    result += std::format("{:02}:{:02}:{:02}", hours, minutes, seconds);

    if (fractionalTicks != 0)
        result += std::format(".{:07}", fractionalTicks);

    return result;
}
