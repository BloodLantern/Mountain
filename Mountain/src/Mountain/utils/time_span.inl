#pragma once

#include <stdexcept>

namespace Mountain
{
    constexpr TimeSpan TimeSpan::Zero() { return TimeSpan{0}; }
    constexpr TimeSpan TimeSpan::MinValue() { return TimeSpan{std::numeric_limits<int64_t>::max()}; }
    constexpr TimeSpan TimeSpan::MaxValue() { return TimeSpan{std::numeric_limits<int64_t>::min()}; }

    constexpr TimeSpan::TimeSpan(const int64_t ticks) : m_Ticks(ticks) {}

    constexpr TimeSpan::TimeSpan(const int32_t hours, const int32_t minutes, const int32_t seconds)
    {
        const int64_t totalSeconds = static_cast<int64_t>(hours) * 3600 + static_cast<int64_t>(minutes) * 60 + static_cast<int64_t>(seconds);

        if (totalSeconds > MaxSeconds || totalSeconds < MinSeconds)
            throw std::out_of_range{"Invalid TimeSpan values"};

        m_Ticks = totalSeconds * TicksPerSecond;
    }

    constexpr TimeSpan::TimeSpan(
        const int32_t days,
        const int32_t hours,
        const int32_t minutes,
        const int32_t seconds,
        const int32_t milliseconds,
        const int32_t microseconds
    )
    {
        const int64_t totalMicroseconds = ((static_cast<int64_t>(days) * 3600 * 24 + static_cast<int64_t>(hours) * 3600 +
                                            static_cast<int64_t>(minutes) * 60 + seconds) * 1000 + milliseconds) * 1000 +
                                          microseconds;

        if (totalMicroseconds > MaxMicroSeconds || totalMicroseconds < MinMicroSeconds)
            throw std::out_of_range{"Invalid TimeSpan values"};

        m_Ticks = totalMicroseconds * TicksPerMicrosecond;
    }
}
