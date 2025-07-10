#pragma once

#include <format>
#include <sstream>

#include "Mountain/Core.hpp"
#include "Mountain/Exceptions/ThrowHelper.hpp"
#include "Mountain/Utils/Requirements.hpp"

namespace Mountain
{
    /// @brief C++ reimplementation of the .NET TimeSpan struct
    /// @details Represents a time interval.
    /// @see Source: https://github.com/dotnet/runtime/blob/release/8.0/src/libraries/System.Private.CoreLib/src/System/TimeSpan.cs
    struct MOUNTAIN_API TimeSpan
    {
        /// @brief Represents the number of nanoseconds per tick
        static constexpr int64_t NanosecondsPerTick = 100;
        /// @brief Represents the number of ticks in 1 microsecond
        static constexpr int64_t TicksPerMicrosecond = 10;
        /// @brief Represents the number of ticks in 1 millisecond
        static constexpr int64_t TicksPerMillisecond = TicksPerMicrosecond * 1000;
        /// @brief Represents the number of ticks in 1 second
        static constexpr int64_t TicksPerSecond = TicksPerMillisecond * 1000;
        /// @brief Represents the number of ticks in 1 minute
        static constexpr int64_t TicksPerMinute = TicksPerSecond * 60;
        /// @brief Represents the number of ticks in 1 hour
        static constexpr int64_t TicksPerHour = TicksPerMinute * 60;
        /// @brief Represents the number of ticks in 1 day
        static constexpr int64_t TicksPerDay = TicksPerHour * 24;
        /// @brief Represents the number of microseconds in 1 millisecond.
        static constexpr int64_t MicrosecondsPerMillisecond = TicksPerMillisecond / TicksPerMicrosecond;
        /// @brief Represents the number of microseconds in 1 second.
        static constexpr int64_t MicrosecondsPerSecond = TicksPerSecond / TicksPerMicrosecond;
        /// @brief Represents the number of microseconds in 1 minute.
        static constexpr int64_t MicrosecondsPerMinute = TicksPerMinute / TicksPerMicrosecond;
        /// @brief Represents the number of microseconds in 1 hour.
        static constexpr int64_t MicrosecondsPerHour = TicksPerHour / TicksPerMicrosecond;
        /// @brief Represents the number of microseconds in 1 day.
        static constexpr int64_t MicrosecondsPerDay = TicksPerDay / TicksPerMicrosecond;
        /// @brief Represents the number of milliseconds in 1 second.
        static constexpr int64_t MillisecondsPerSecond = TicksPerSecond / TicksPerMillisecond;
        /// @brief Represents the number of milliseconds in 1 minute.
        static constexpr int64_t MillisecondsPerMinute = TicksPerMinute / TicksPerMillisecond;
        /// @brief Represents the number of milliseconds in 1 hour.
        static constexpr int64_t MillisecondsPerHour = TicksPerHour / TicksPerMillisecond;
        /// @brief Represents the number of milliseconds in 1 day.
        static constexpr int64_t MillisecondsPerDay = TicksPerDay / TicksPerMillisecond;
        /// @brief Represents the number of seconds in 1 minute.
        static constexpr int64_t SecondsPerMinute = TicksPerMinute / TicksPerSecond;
        /// @brief Represents the number of seconds in 1 hour.
        static constexpr int64_t SecondsPerHour = TicksPerHour / TicksPerSecond;
        /// @brief Represents the number of seconds in 1 day.
        static constexpr int64_t SecondsPerDay = TicksPerDay / TicksPerSecond;
        /// @brief Represents the number of minutes in 1 hour.
        static constexpr int64_t MinutesPerHour = TicksPerHour / TicksPerMinute;
        /// @brief Represents the number of minutes in 1 day.
        static constexpr int64_t MinutesPerDay = TicksPerDay / TicksPerMinute;
        /// @brief Represents the number of hours in 1 day.
        static constexpr int32_t HoursPerDay = TicksPerDay / TicksPerHour;

        ATTRIBUTE_NODISCARD
        static constexpr TimeSpan Zero();
        ATTRIBUTE_NODISCARD
        static constexpr TimeSpan MaxValue();
        ATTRIBUTE_NODISCARD
        static constexpr TimeSpan MinValue();

        ATTRIBUTE_NODISCARD
        static TimeSpan FromDays(double_t days);
        ATTRIBUTE_NODISCARD
        static TimeSpan FromHours(double_t hours);
        ATTRIBUTE_NODISCARD
        static TimeSpan FromMinutes(double_t minutes);
        ATTRIBUTE_NODISCARD
        static TimeSpan FromSeconds(double_t seconds);
        ATTRIBUTE_NODISCARD
        static TimeSpan FromMilliseconds(double_t milliseconds);
        ATTRIBUTE_NODISCARD
        static TimeSpan FromMicroseconds(double_t microseconds);
        ATTRIBUTE_NODISCARD
        static TimeSpan FromTicks(int64_t ticks);

        explicit constexpr TimeSpan(int64_t ticks);
        constexpr TimeSpan(int32_t hours, int32_t minutes, int32_t seconds);
        constexpr TimeSpan(int32_t days, int32_t hours, int32_t minutes, int32_t seconds, int32_t milliseconds = 0, int32_t microseconds = 0);

        GETTER(int64_t, Ticks, m_Ticks)

        ATTRIBUTE_NODISCARD
        int32_t GetDays() const;
        ATTRIBUTE_NODISCARD
        int32_t GetHours() const;
        ATTRIBUTE_NODISCARD
        int32_t GetMinutes() const;
        ATTRIBUTE_NODISCARD
        int32_t GetSeconds() const;
        ATTRIBUTE_NODISCARD
        int32_t GetMilliseconds() const;
        ATTRIBUTE_NODISCARD
        int32_t GetMicroseconds() const;
        ATTRIBUTE_NODISCARD
        int32_t GetNanoseconds() const;

        ATTRIBUTE_NODISCARD
        double_t GetTotalDays() const;
        ATTRIBUTE_NODISCARD
        double_t GetTotalHours() const;
        ATTRIBUTE_NODISCARD
        double_t GetTotalMinutes() const;
        ATTRIBUTE_NODISCARD
        double_t GetTotalSeconds() const;
        ATTRIBUTE_NODISCARD
        double_t GetTotalMilliseconds() const;
        ATTRIBUTE_NODISCARD
        double_t GetTotalMicroseconds() const;
        ATTRIBUTE_NODISCARD
        double_t GetTotalNanoseconds() const;

        ATTRIBUTE_NODISCARD
        TimeSpan Duration() const;

        ATTRIBUTE_NODISCARD
        friend std::strong_ordering operator<=>(TimeSpan, TimeSpan) = default;

        ATTRIBUTE_NODISCARD
        friend TimeSpan operator+(TimeSpan lhs, TimeSpan rhs);
        ATTRIBUTE_NODISCARD
        friend TimeSpan operator-(TimeSpan value);
        ATTRIBUTE_NODISCARD
        friend TimeSpan operator-(TimeSpan lhs, TimeSpan rhs);
        ATTRIBUTE_NODISCARD
        friend TimeSpan operator*(TimeSpan lhs, double_t rhs);
        ATTRIBUTE_NODISCARD
        friend TimeSpan operator*(double_t lhs, TimeSpan rhs);
        ATTRIBUTE_NODISCARD
        friend TimeSpan operator/(TimeSpan lhs, double_t rhs);
        ATTRIBUTE_NODISCARD
        friend double_t operator/(TimeSpan lhs, TimeSpan rhs);

        friend TimeSpan& operator+=(TimeSpan& lhs, TimeSpan rhs);
        friend TimeSpan& operator-=(TimeSpan& lhs, TimeSpan rhs);
        friend TimeSpan& operator*=(TimeSpan& lhs, double_t rhs);
        friend TimeSpan& operator/=(TimeSpan& lhs, double_t rhs);

        ATTRIBUTE_NODISCARD
        std::string ToString() const;

        ATTRIBUTE_NODISCARD
        size_t GetHashCode() const;

    private:
        static constexpr int64_t MaxSeconds = std::numeric_limits<int64_t>::max() / TicksPerSecond;
        static constexpr int64_t MinSeconds = std::numeric_limits<int64_t>::min() / TicksPerSecond;

        static constexpr int64_t MaxMilliSeconds = std::numeric_limits<int64_t>::max() / TicksPerMillisecond;
        static constexpr int64_t MinMilliSeconds = std::numeric_limits<int64_t>::min() / TicksPerMillisecond;

        static constexpr int64_t MaxMicroSeconds = std::numeric_limits<int64_t>::max() / TicksPerMicrosecond;
        static constexpr int64_t MinMicroSeconds = std::numeric_limits<int64_t>::min() / TicksPerMicrosecond;

        static constexpr int64_t TicksPerTenthSecond = TicksPerMillisecond * 100;

        ATTRIBUTE_NODISCARD
        static TimeSpan Interval(double_t ticks, double_t scale);
        ATTRIBUTE_NODISCARD
        static TimeSpan IntervalFromDoubleTicks(double_t ticks);

        int64_t m_Ticks = 0;
    };

    CHECK_REQUIREMENT(Requirements::StringConvertible, TimeSpan);
    CHECK_REQUIREMENT(Requirements::Hashable, TimeSpan);
}

// Start of TimeSpan.inl

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
            THROW(ArgumentOutOfRangeException{"Invalid TimeSpan values"});

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
            THROW(ArgumentOutOfRangeException{"Invalid TimeSpan values"});

        m_Ticks = totalMicroseconds * TicksPerMicrosecond;
    }
}
