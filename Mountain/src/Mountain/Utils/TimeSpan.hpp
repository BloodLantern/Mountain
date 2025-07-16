#pragma once

#include <format>
#include <sstream>

#include "Mountain/Core.hpp"
#include "Mountain/Exceptions/ThrowHelper.hpp"
#include "Mountain/Utils/Requirements.hpp"
#include "Mountain/Utils/Utils.hpp"

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
        static constexpr TimeSpan FromDays(double_t days);
        ATTRIBUTE_NODISCARD
        static constexpr TimeSpan FromHours(double_t hours);
        ATTRIBUTE_NODISCARD
        static constexpr TimeSpan FromMinutes(double_t minutes);
        ATTRIBUTE_NODISCARD
        static constexpr TimeSpan FromSeconds(double_t seconds);
        ATTRIBUTE_NODISCARD
        static constexpr TimeSpan FromMilliseconds(double_t milliseconds);
        ATTRIBUTE_NODISCARD
        static constexpr TimeSpan FromMicroseconds(double_t microseconds);
        ATTRIBUTE_NODISCARD
        static constexpr TimeSpan FromTicks(int64_t ticks);

        explicit constexpr TimeSpan(int64_t ticks);
        constexpr TimeSpan(int32_t hours, int32_t minutes, int32_t seconds);
        constexpr TimeSpan(int32_t days, int32_t hours, int32_t minutes, int32_t seconds, int32_t milliseconds = 0, int32_t microseconds = 0);

        GETTER(int64_t, Ticks, m_Ticks)

        ATTRIBUTE_NODISCARD
        constexpr int32_t GetDays() const;
        ATTRIBUTE_NODISCARD
        constexpr int32_t GetHours() const;
        ATTRIBUTE_NODISCARD
        constexpr int32_t GetMinutes() const;
        ATTRIBUTE_NODISCARD
        constexpr int32_t GetSeconds() const;
        ATTRIBUTE_NODISCARD
        constexpr int32_t GetMilliseconds() const;
        ATTRIBUTE_NODISCARD
        constexpr int32_t GetMicroseconds() const;
        ATTRIBUTE_NODISCARD
        constexpr int32_t GetNanoseconds() const;

        ATTRIBUTE_NODISCARD
        constexpr double_t GetTotalDays() const;
        ATTRIBUTE_NODISCARD
        constexpr double_t GetTotalHours() const;
        ATTRIBUTE_NODISCARD
        constexpr double_t GetTotalMinutes() const;
        ATTRIBUTE_NODISCARD
        constexpr double_t GetTotalSeconds() const;
        ATTRIBUTE_NODISCARD
        constexpr double_t GetTotalMilliseconds() const;
        ATTRIBUTE_NODISCARD
        constexpr double_t GetTotalMicroseconds() const;
        ATTRIBUTE_NODISCARD
        constexpr double_t GetTotalNanoseconds() const;

        /// @brief Returns a new @c TimeSpan whose value is the absolute value of the current @c TimeSpan.
        ATTRIBUTE_NODISCARD
        constexpr TimeSpan Duration() const;

        ATTRIBUTE_NODISCARD
        constexpr std::chrono::nanoseconds ToChrono() const;

        ATTRIBUTE_NODISCARD
        friend std::strong_ordering operator<=>(TimeSpan, TimeSpan) = default;

        ATTRIBUTE_NODISCARD
        friend constexpr TimeSpan operator+(TimeSpan lhs, TimeSpan rhs);
        ATTRIBUTE_NODISCARD
        friend constexpr TimeSpan operator-(TimeSpan value);
        ATTRIBUTE_NODISCARD
        friend constexpr TimeSpan operator-(TimeSpan lhs, TimeSpan rhs);
        ATTRIBUTE_NODISCARD
        friend constexpr TimeSpan operator*(TimeSpan lhs, double_t rhs);
        ATTRIBUTE_NODISCARD
        friend constexpr TimeSpan operator*(double_t lhs, TimeSpan rhs);
        ATTRIBUTE_NODISCARD
        friend constexpr TimeSpan operator/(TimeSpan lhs, double_t rhs);
        ATTRIBUTE_NODISCARD
        friend constexpr double_t operator/(TimeSpan lhs, TimeSpan rhs);

        friend constexpr TimeSpan& operator+=(TimeSpan& lhs, TimeSpan rhs);
        friend constexpr TimeSpan& operator-=(TimeSpan& lhs, TimeSpan rhs);
        friend constexpr TimeSpan& operator*=(TimeSpan& lhs, double_t rhs);
        friend constexpr TimeSpan& operator/=(TimeSpan& lhs, double_t rhs);

        ATTRIBUTE_NODISCARD
        std::string ToString() const;

        ATTRIBUTE_NODISCARD
        constexpr size_t GetHashCode() const;

    private:
        static constexpr int64_t MaxSeconds = std::numeric_limits<int64_t>::max() / TicksPerSecond;
        static constexpr int64_t MinSeconds = std::numeric_limits<int64_t>::min() / TicksPerSecond;

        static constexpr int64_t MaxMilliSeconds = std::numeric_limits<int64_t>::max() / TicksPerMillisecond;
        static constexpr int64_t MinMilliSeconds = std::numeric_limits<int64_t>::min() / TicksPerMillisecond;

        static constexpr int64_t MaxMicroSeconds = std::numeric_limits<int64_t>::max() / TicksPerMicrosecond;
        static constexpr int64_t MinMicroSeconds = std::numeric_limits<int64_t>::min() / TicksPerMicrosecond;

        static constexpr int64_t TicksPerTenthSecond = TicksPerMillisecond * 100;

        ATTRIBUTE_NODISCARD
        static constexpr TimeSpan Interval(double_t ticks, double_t scale);
        ATTRIBUTE_NODISCARD
        static constexpr TimeSpan IntervalFromDoubleTicks(double_t ticks);

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

    // ReSharper disable CppClangTidyReadabilitySuspiciousCallArgument
    constexpr TimeSpan TimeSpan::FromDays(const double_t days) { return Interval(days, TicksPerDay); }

    constexpr TimeSpan TimeSpan::FromHours(const double_t hours) { return Interval(hours, TicksPerHour); }

    constexpr TimeSpan TimeSpan::FromMinutes(const double_t minutes) { return Interval(minutes, TicksPerMinute); }

    constexpr TimeSpan TimeSpan::FromSeconds(const double_t seconds) { return Interval(seconds, TicksPerSecond); }

    constexpr TimeSpan TimeSpan::FromMilliseconds(const double_t milliseconds) { return Interval(milliseconds, TicksPerMillisecond); }

    constexpr TimeSpan TimeSpan::FromMicroseconds(const double_t microseconds) { return Interval(microseconds, TicksPerMicrosecond); }
    // ReSharper restore CppClangTidyReadabilitySuspiciousCallArgument

    constexpr TimeSpan TimeSpan::FromTicks(const int64_t ticks) { return TimeSpan{ticks}; }

    constexpr int32_t TimeSpan::GetDays() const { return static_cast<int32_t>(m_Ticks / TicksPerDay); }

    constexpr int32_t TimeSpan::GetHours() const { return static_cast<int32_t>(m_Ticks / TicksPerHour % 24); }

    constexpr int32_t TimeSpan::GetMinutes() const { return static_cast<int32_t>(m_Ticks / TicksPerMinute % 60); }

    constexpr int32_t TimeSpan::GetSeconds() const { return static_cast<int32_t>(m_Ticks / TicksPerSecond % 60); }

    constexpr int32_t TimeSpan::GetMilliseconds() const { return static_cast<int32_t>(m_Ticks / TicksPerMillisecond % 1000); }

    constexpr int32_t TimeSpan::GetMicroseconds() const { return static_cast<int32_t>(m_Ticks / TicksPerMicrosecond % 1000); }

    constexpr int32_t TimeSpan::GetNanoseconds() const { return static_cast<int32_t>(m_Ticks % TicksPerMicrosecond * NanosecondsPerTick); }

    constexpr double_t TimeSpan::GetTotalDays() const { return static_cast<double_t>(m_Ticks) / TicksPerDay; }

    constexpr double_t TimeSpan::GetTotalHours() const { return static_cast<double_t>(m_Ticks) / TicksPerHour; }

    constexpr double_t TimeSpan::GetTotalMinutes() const { return static_cast<double_t>(m_Ticks) / TicksPerMinute; }

    constexpr double_t TimeSpan::GetTotalSeconds() const { return static_cast<double_t>(m_Ticks) / TicksPerSecond; }

    constexpr double_t TimeSpan::GetTotalMilliseconds() const
    {
        const double_t temp = static_cast<double_t>(m_Ticks) / TicksPerMillisecond;

        if (temp > MaxMilliSeconds)
            return MaxMilliSeconds;

        if (temp < MinMilliSeconds)
            return MinMilliSeconds;

        return temp;
    }

    constexpr double_t TimeSpan::GetTotalMicroseconds() const { return static_cast<double_t>(m_Ticks) / TicksPerMicrosecond; }

    constexpr double_t TimeSpan::GetTotalNanoseconds() const { return static_cast<double_t>(m_Ticks) * NanosecondsPerTick; }

    constexpr TimeSpan TimeSpan::Duration() const
    {
        if (m_Ticks == MinValue().m_Ticks)
            throw OverflowException{"TimeSpan Duration overflow"};
        return TimeSpan{m_Ticks >= 0 ? m_Ticks : -m_Ticks};
    }

    constexpr std::chrono::nanoseconds TimeSpan::ToChrono() const
    {
        return std::chrono::nanoseconds{static_cast<int64_t>(GetTotalNanoseconds())};
    }

    constexpr TimeSpan operator+(const TimeSpan lhs, const TimeSpan rhs)
    {
        const int64_t result = lhs.m_Ticks + rhs.m_Ticks;

        // Overflow if signs of operands was identical and result's
        // sign was opposite.
        // >> 63 gives the sign bit (either 64 1's or 64 0's).
        if ((lhs.m_Ticks >> 63 == rhs.m_Ticks >> 63) && (lhs.m_Ticks >> 63 != result >> 63))
            throw OverflowException{"TimeSpan sum overflow"};

        return TimeSpan{result};
    }

    constexpr TimeSpan operator-(const TimeSpan value)
    {
        if (value.m_Ticks == TimeSpan::MinValue().m_Ticks)
            throw OverflowException{"Cannot negate the MinValue TimeSpan because of Two's Complement"};
        return TimeSpan{-value.m_Ticks};
    }

    constexpr TimeSpan operator-(const TimeSpan lhs, const TimeSpan rhs)
    {
        const int64_t result = lhs.m_Ticks + rhs.m_Ticks;

        // Overflow if signs of operands was different and result's
        // sign was opposite.
        // >> 63 gives the sign bit (either 64 1's or 64 0's).
        if ((lhs.m_Ticks >> 63 != rhs.m_Ticks >> 63) && (lhs.m_Ticks >> 63 != result >> 63))
            throw OverflowException{"TimeSpan difference underflow"};

        return TimeSpan{result};
    }

    constexpr TimeSpan operator*(const TimeSpan lhs, const double_t rhs)
    {
        if (Calc::IsNan(rhs))
            throw ArgumentException{"Cannot multiply a TimeSpan by a NaN", TO_STRING(rhs)};

        const double_t ticks = Calc::Round(static_cast<double_t>(lhs.m_Ticks) * rhs);
        return TimeSpan::IntervalFromDoubleTicks(ticks);
    }

    constexpr TimeSpan operator*(const double_t lhs, const TimeSpan rhs) { return rhs * lhs; }

    constexpr TimeSpan operator/(const TimeSpan lhs, const double_t rhs)
    {
        if (Calc::IsNan(rhs))
            throw ArgumentException{"Cannot divide a TimeSpan by a NaN", TO_STRING(rhs)};

        const double_t ticks = Calc::Round(static_cast<double_t>(lhs.m_Ticks) / rhs);
        return TimeSpan::IntervalFromDoubleTicks(ticks);
    }

    constexpr double_t operator/(const TimeSpan lhs, const TimeSpan rhs) { return static_cast<double_t>(lhs.m_Ticks) / static_cast<double_t>(rhs.m_Ticks); }

    constexpr TimeSpan& operator+=(TimeSpan& lhs, const TimeSpan rhs) { return lhs = lhs + rhs; }

    constexpr TimeSpan& operator-=(TimeSpan& lhs, const TimeSpan rhs) { return lhs = lhs - rhs; }

    constexpr TimeSpan& operator*=(TimeSpan& lhs, const double_t rhs) { return lhs = lhs * rhs; }

    constexpr TimeSpan& operator/=(TimeSpan& lhs, const double_t rhs) { return lhs = lhs / rhs; }

    constexpr TimeSpan::TimeSpan(const int64_t ticks) : m_Ticks(ticks) {}

    constexpr TimeSpan::TimeSpan(const int32_t hours, const int32_t minutes, const int32_t seconds)
    {
        const int64_t totalSeconds = static_cast<int64_t>(hours) * 3600 + static_cast<int64_t>(minutes) * 60 + static_cast<int64_t>(seconds);

        if (totalSeconds > MaxSeconds || totalSeconds < MinSeconds)
            throw ArgumentOutOfRangeException{"Invalid TimeSpan values"};

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
            throw ArgumentOutOfRangeException{"Invalid TimeSpan values"};

        m_Ticks = totalMicroseconds * TicksPerMicrosecond;
    }

    constexpr size_t TimeSpan::GetHashCode() const { return m_Ticks ^ (m_Ticks >> 32); }

    constexpr TimeSpan TimeSpan::Interval(const double_t ticks, const double_t scale)
    {
        if (Calc::IsNan(ticks))
            throw ArgumentException{"Cannot create an interval from a NaN amount of ticks", TO_STRING(ticks)};
        return IntervalFromDoubleTicks(ticks * scale);
    }

    constexpr TimeSpan TimeSpan::IntervalFromDoubleTicks(const double_t ticks)
    {
        if (ticks > static_cast<double_t>(std::numeric_limits<int64_t>::max()) || ticks < static_cast<double_t>(std::numeric_limits<int64_t>::min()) || std::isnan(ticks))
            throw OverflowException{"Invalid TimeSpan ticks"};
        if (ticks == static_cast<double_t>(std::numeric_limits<int64_t>::max()))
            return MaxValue();
        return TimeSpan{static_cast<int64_t>(ticks)};
    }
}
