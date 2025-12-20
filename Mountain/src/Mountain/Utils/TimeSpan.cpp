#include "Mountain/PrecompiledHeader.hpp"

#include "Mountain/Utils/TimeSpan.hpp"

using namespace Mountain;

std::string TimeSpan::ToString() const
{
    std::string result;

    const s64 ticks = m_Ticks;
    const u64 absTicks = ticks >= 0 ? static_cast<u64>(ticks) : 0ULL - static_cast<u64>(ticks);

    if (ticks < 0)
        result += '-';

    const s32 days = static_cast<s32>(absTicks / TicksPerDay);
    const s32 hours = static_cast<s32>(absTicks / TicksPerHour % 24);
    const s32 minutes = static_cast<s32>(absTicks / TicksPerMinute % 60);
    const s32 seconds = static_cast<s32>(absTicks / TicksPerSecond % 60);
    const s32 fractionalTicks = static_cast<s32>(absTicks % TicksPerSecond);

    if (days != 0)
        result += std::format("{}.", days);

    result += std::format("{:02}:{:02}:{:02}", hours, minutes, seconds);

    if (fractionalTicks != 0)
        result += std::format(".{:07}", fractionalTicks);

    return result;
}
