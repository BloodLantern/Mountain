#pragma once

#include <format>
#include <sstream>

#include "Mountain/Core.hpp"
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
        static constexpr s64 NanosecondsPerTick = 100;
        /// @brief Represents the number of ticks in 1 microsecond
        static constexpr s64 TicksPerMicrosecond = 10;
        /// @brief Represents the number of ticks in 1 millisecond
        static constexpr s64 TicksPerMillisecond = TicksPerMicrosecond * 1000;
        /// @brief Represents the number of ticks in 1 second
        static constexpr s64 TicksPerSecond = TicksPerMillisecond * 1000;
        /// @brief Represents the number of ticks in 1 minute
        static constexpr s64 TicksPerMinute = TicksPerSecond * 60;
        /// @brief Represents the number of ticks in 1 hour
        static constexpr s64 TicksPerHour = TicksPerMinute * 60;
        /// @brief Represents the number of ticks in 1 day
        static constexpr s64 TicksPerDay = TicksPerHour * 24;
        /// @brief Represents the number of microseconds in 1 millisecond.
        static constexpr s64 MicrosecondsPerMillisecond = TicksPerMillisecond / TicksPerMicrosecond;
        /// @brief Represents the number of microseconds in 1 second.
        static constexpr s64 MicrosecondsPerSecond = TicksPerSecond / TicksPerMicrosecond;
        /// @brief Represents the number of microseconds in 1 minute.
        static constexpr s64 MicrosecondsPerMinute = TicksPerMinute / TicksPerMicrosecond;
        /// @brief Represents the number of microseconds in 1 hour.
        static constexpr s64 MicrosecondsPerHour = TicksPerHour / TicksPerMicrosecond;
        /// @brief Represents the number of microseconds in 1 day.
        static constexpr s64 MicrosecondsPerDay = TicksPerDay / TicksPerMicrosecond;
        /// @brief Represents the number of milliseconds in 1 second.
        static constexpr s64 MillisecondsPerSecond = TicksPerSecond / TicksPerMillisecond;
        /// @brief Represents the number of milliseconds in 1 minute.
        static constexpr s64 MillisecondsPerMinute = TicksPerMinute / TicksPerMillisecond;
        /// @brief Represents the number of milliseconds in 1 hour.
        static constexpr s64 MillisecondsPerHour = TicksPerHour / TicksPerMillisecond;
        /// @brief Represents the number of milliseconds in 1 day.
        static constexpr s64 MillisecondsPerDay = TicksPerDay / TicksPerMillisecond;
        /// @brief Represents the number of seconds in 1 minute.
        static constexpr s64 SecondsPerMinute = TicksPerMinute / TicksPerSecond;
        /// @brief Represents the number of seconds in 1 hour.
        static constexpr s64 SecondsPerHour = TicksPerHour / TicksPerSecond;
        /// @brief Represents the number of seconds in 1 day.
        static constexpr s64 SecondsPerDay = TicksPerDay / TicksPerSecond;
        /// @brief Represents the number of minutes in 1 hour.
        static constexpr s64 MinutesPerHour = TicksPerHour / TicksPerMinute;
        /// @brief Represents the number of minutes in 1 day.
        static constexpr s64 MinutesPerDay = TicksPerDay / TicksPerMinute;
        /// @brief Represents the number of hours in 1 day.
        static constexpr s32 HoursPerDay = TicksPerDay / TicksPerHour;

        ATTRIBUTE_NODISCARD
        static constexpr TimeSpan Zero();
        ATTRIBUTE_NODISCARD
        static constexpr TimeSpan MaxValue();
        ATTRIBUTE_NODISCARD
        static constexpr TimeSpan MinValue();

        ATTRIBUTE_NODISCARD
        static constexpr TimeSpan FromDays(f64 days);
        ATTRIBUTE_NODISCARD
        static constexpr TimeSpan FromHours(f64 hours);
        ATTRIBUTE_NODISCARD
        static constexpr TimeSpan FromMinutes(f64 minutes);
        ATTRIBUTE_NODISCARD
        static constexpr TimeSpan FromSeconds(f64 seconds);
        ATTRIBUTE_NODISCARD
        static constexpr TimeSpan FromMilliseconds(f64 milliseconds);
        ATTRIBUTE_NODISCARD
        static constexpr TimeSpan FromMicroseconds(f64 microseconds);
        ATTRIBUTE_NODISCARD
        static constexpr TimeSpan FromTicks(s64 ticks);

        explicit constexpr TimeSpan(s64 ticks);
        constexpr TimeSpan(s32 hours, s32 minutes, s32 seconds);
        constexpr TimeSpan(s32 days, s32 hours, s32 minutes, s32 seconds, s32 milliseconds = 0, s32 microseconds = 0);

        GETTER(s64, Ticks, m_Ticks)

        ATTRIBUTE_NODISCARD
        constexpr s32 GetDays() const;
        ATTRIBUTE_NODISCARD
        constexpr s32 GetHours() const;
        ATTRIBUTE_NODISCARD
        constexpr s32 GetMinutes() const;
        ATTRIBUTE_NODISCARD
        constexpr s32 GetSeconds() const;
        ATTRIBUTE_NODISCARD
        constexpr s32 GetMilliseconds() const;
        ATTRIBUTE_NODISCARD
        constexpr s32 GetMicroseconds() const;
        ATTRIBUTE_NODISCARD
        constexpr s32 GetNanoseconds() const;

        ATTRIBUTE_NODISCARD
        constexpr f64 GetTotalDays() const;
        ATTRIBUTE_NODISCARD
        constexpr f64 GetTotalHours() const;
        ATTRIBUTE_NODISCARD
        constexpr f64 GetTotalMinutes() const;
        ATTRIBUTE_NODISCARD
        constexpr f64 GetTotalSeconds() const;
        ATTRIBUTE_NODISCARD
        constexpr f64 GetTotalMilliseconds() const;
        ATTRIBUTE_NODISCARD
        constexpr f64 GetTotalMicroseconds() const;
        ATTRIBUTE_NODISCARD
        constexpr f64 GetTotalNanoseconds() const;

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
        friend constexpr TimeSpan operator*(TimeSpan lhs, f64 rhs);
        ATTRIBUTE_NODISCARD
        friend constexpr TimeSpan operator*(f64 lhs, TimeSpan rhs);
        ATTRIBUTE_NODISCARD
        friend constexpr TimeSpan operator/(TimeSpan lhs, f64 rhs);
        ATTRIBUTE_NODISCARD
        friend constexpr f64 operator/(TimeSpan lhs, TimeSpan rhs);

        friend constexpr TimeSpan& operator+=(TimeSpan& lhs, TimeSpan rhs);
        friend constexpr TimeSpan& operator-=(TimeSpan& lhs, TimeSpan rhs);
        friend constexpr TimeSpan& operator*=(TimeSpan& lhs, f64 rhs);
        friend constexpr TimeSpan& operator/=(TimeSpan& lhs, f64 rhs);

        ATTRIBUTE_NODISCARD
        std::string ToString() const;

        ATTRIBUTE_NODISCARD
        constexpr usize GetHashCode() const;

    private:
        static constexpr s64 MaxSeconds = std::numeric_limits<s64>::max() / TicksPerSecond;
        static constexpr s64 MinSeconds = std::numeric_limits<s64>::min() / TicksPerSecond;

        static constexpr s64 MaxMilliSeconds = std::numeric_limits<s64>::max() / TicksPerMillisecond;
        static constexpr s64 MinMilliSeconds = std::numeric_limits<s64>::min() / TicksPerMillisecond;

        static constexpr s64 MaxMicroSeconds = std::numeric_limits<s64>::max() / TicksPerMicrosecond;
        static constexpr s64 MinMicroSeconds = std::numeric_limits<s64>::min() / TicksPerMicrosecond;

        static constexpr s64 TicksPerTenthSecond = TicksPerMillisecond * 100;

        ATTRIBUTE_NODISCARD
        static constexpr TimeSpan Interval(f64 ticks, f64 scale);
        ATTRIBUTE_NODISCARD
        static constexpr TimeSpan IntervalFromDoubleTicks(f64 ticks);

        s64 m_Ticks = 0;
    };

    CHECK_REQUIREMENT(Requirements::StringConvertible, TimeSpan);
    CHECK_REQUIREMENT(Requirements::Hashable, TimeSpan);
    CHECK_REQUIREMENT(Requirements::Equatable, TimeSpan);
    CHECK_REQUIREMENT(Requirements::Comparable, TimeSpan);
}

// Start of TimeSpan.inl

#include "Mountain/Exceptions/ThrowHelper.hpp"

namespace Mountain
{
    constexpr TimeSpan TimeSpan::Zero() { return TimeSpan{0}; }
    constexpr TimeSpan TimeSpan::MaxValue() { return TimeSpan{std::numeric_limits<s64>::max()}; }
    constexpr TimeSpan TimeSpan::MinValue() { return TimeSpan{std::numeric_limits<s64>::min()}; }

    // ReSharper disable CppClangTidyReadabilitySuspiciousCallArgument
    constexpr TimeSpan TimeSpan::FromDays(const f64 days) { return Interval(days, TicksPerDay); }

    constexpr TimeSpan TimeSpan::FromHours(const f64 hours) { return Interval(hours, TicksPerHour); }

    constexpr TimeSpan TimeSpan::FromMinutes(const f64 minutes) { return Interval(minutes, TicksPerMinute); }

    constexpr TimeSpan TimeSpan::FromSeconds(const f64 seconds) { return Interval(seconds, TicksPerSecond); }

    constexpr TimeSpan TimeSpan::FromMilliseconds(const f64 milliseconds) { return Interval(milliseconds, TicksPerMillisecond); }

    constexpr TimeSpan TimeSpan::FromMicroseconds(const f64 microseconds) { return Interval(microseconds, TicksPerMicrosecond); }
    // ReSharper restore CppClangTidyReadabilitySuspiciousCallArgument

    constexpr TimeSpan TimeSpan::FromTicks(const s64 ticks) { return TimeSpan{ticks}; }

    constexpr s32 TimeSpan::GetDays() const { return static_cast<s32>(m_Ticks / TicksPerDay); }

    constexpr s32 TimeSpan::GetHours() const { return static_cast<s32>(m_Ticks / TicksPerHour % 24); }

    constexpr s32 TimeSpan::GetMinutes() const { return static_cast<s32>(m_Ticks / TicksPerMinute % 60); }

    constexpr s32 TimeSpan::GetSeconds() const { return static_cast<s32>(m_Ticks / TicksPerSecond % 60); }

    constexpr s32 TimeSpan::GetMilliseconds() const { return static_cast<s32>(m_Ticks / TicksPerMillisecond % 1000); }

    constexpr s32 TimeSpan::GetMicroseconds() const { return static_cast<s32>(m_Ticks / TicksPerMicrosecond % 1000); }

    constexpr s32 TimeSpan::GetNanoseconds() const { return static_cast<s32>(m_Ticks % TicksPerMicrosecond * NanosecondsPerTick); }

    constexpr f64 TimeSpan::GetTotalDays() const { return static_cast<f64>(m_Ticks) / TicksPerDay; }

    constexpr f64 TimeSpan::GetTotalHours() const { return static_cast<f64>(m_Ticks) / TicksPerHour; }

    constexpr f64 TimeSpan::GetTotalMinutes() const { return static_cast<f64>(m_Ticks) / TicksPerMinute; }

    constexpr f64 TimeSpan::GetTotalSeconds() const { return static_cast<f64>(m_Ticks) / TicksPerSecond; }

    constexpr f64 TimeSpan::GetTotalMilliseconds() const
    {
        const f64 temp = static_cast<f64>(m_Ticks) / TicksPerMillisecond;

        if (temp > MaxMilliSeconds)
            return MaxMilliSeconds;

        if (temp < MinMilliSeconds)
            return MinMilliSeconds;

        return temp;
    }

    constexpr f64 TimeSpan::GetTotalMicroseconds() const { return static_cast<f64>(m_Ticks) / TicksPerMicrosecond; }

    constexpr f64 TimeSpan::GetTotalNanoseconds() const { return static_cast<f64>(m_Ticks) * NanosecondsPerTick; }

    constexpr TimeSpan TimeSpan::Duration() const
    {
        if (m_Ticks == MinValue().m_Ticks)
            THROW(OverflowException{"TimeSpan Duration overflow"});

        return TimeSpan{m_Ticks >= 0 ? m_Ticks : -m_Ticks};
    }

    constexpr std::chrono::nanoseconds TimeSpan::ToChrono() const
    {
        return std::chrono::nanoseconds{static_cast<s64>(GetTotalNanoseconds())};
    }

    constexpr TimeSpan operator+(const TimeSpan lhs, const TimeSpan rhs)
    {
        const s64 result = lhs.m_Ticks + rhs.m_Ticks;

        // Overflow if signs of operands was identical and result's
        // sign was opposite.
        // >> 63 gives the sign bit (either 64 1's or 64 0's).
        if ((lhs.m_Ticks >> 63 == rhs.m_Ticks >> 63) && (lhs.m_Ticks >> 63 != result >> 63))
            THROW(OverflowException{"TimeSpan sum overflow"});

        return TimeSpan{result};
    }

    constexpr TimeSpan operator-(const TimeSpan value)
    {
        if (value.m_Ticks == TimeSpan::MinValue().m_Ticks)
            THROW(OverflowException{"Cannot negate the MinValue TimeSpan because of Two's Complement"});

        return TimeSpan{-value.m_Ticks};
    }

    constexpr TimeSpan operator-(const TimeSpan lhs, const TimeSpan rhs)
    {
        const s64 result = lhs.m_Ticks - rhs.m_Ticks;

        // Overflow if signs of operands was different and result's
        // sign was opposite from the first argument's sign.
        // >> 63 gives the sign bit (either 64 1's or 64 0's).
        if ((lhs.m_Ticks >> 63 != rhs.m_Ticks >> 63) && (lhs.m_Ticks >> 63 != result >> 63))
            THROW(OverflowException{"TimeSpan difference underflow"});

        return TimeSpan{result};
    }

    constexpr TimeSpan operator*(const TimeSpan lhs, const f64 rhs)
    {
        if (Calc::IsNan(rhs))
            THROW(ArgumentException{"Cannot multiply a TimeSpan by a NaN", "rhs"});

        const f64 ticks = Calc::Round(static_cast<f64>(lhs.m_Ticks) * rhs);
        return TimeSpan::IntervalFromDoubleTicks(ticks);
    }

    constexpr TimeSpan operator*(const f64 lhs, const TimeSpan rhs) { return rhs * lhs; }

    constexpr TimeSpan operator/(const TimeSpan lhs, const f64 rhs)
    {
        if (Calc::IsNan(rhs))
            THROW(ArgumentException{"Cannot divide a TimeSpan by a NaN", "rhs"});

        const f64 ticks = Calc::Round(static_cast<f64>(lhs.m_Ticks) / rhs);
        return TimeSpan::IntervalFromDoubleTicks(ticks);
    }

    constexpr f64 operator/(const TimeSpan lhs, const TimeSpan rhs) { return static_cast<f64>(lhs.m_Ticks) / static_cast<f64>(rhs.m_Ticks); }

    constexpr TimeSpan& operator+=(TimeSpan& lhs, const TimeSpan rhs) { return lhs = lhs + rhs; }

    constexpr TimeSpan& operator-=(TimeSpan& lhs, const TimeSpan rhs) { return lhs = lhs - rhs; }

    constexpr TimeSpan& operator*=(TimeSpan& lhs, const f64 rhs) { return lhs = lhs * rhs; }

    constexpr TimeSpan& operator/=(TimeSpan& lhs, const f64 rhs) { return lhs = lhs / rhs; }

    constexpr TimeSpan::TimeSpan(const s64 ticks) : m_Ticks(ticks) {}

    constexpr TimeSpan::TimeSpan(const s32 hours, const s32 minutes, const s32 seconds)
    {
        const s64 totalSeconds = static_cast<s64>(hours) * 3600 + static_cast<s64>(minutes) * 60 + static_cast<s64>(seconds);

        if (totalSeconds > MaxSeconds || totalSeconds < MinSeconds)
            THROW(ArgumentOutOfRangeException{"Invalid TimeSpan values"});

        m_Ticks = totalSeconds * TicksPerSecond;
    }

    constexpr TimeSpan::TimeSpan(
        const s32 days,
        const s32 hours,
        const s32 minutes,
        const s32 seconds,
        const s32 milliseconds,
        const s32 microseconds
    )
    {
        const s64 totalMicroseconds = ((static_cast<s64>(days) * 3600 * 24 + static_cast<s64>(hours) * 3600 +
                                            static_cast<s64>(minutes) * 60 + seconds) * 1000 + milliseconds) * 1000 +
                                          microseconds;

        if (totalMicroseconds > MaxMicroSeconds || totalMicroseconds < MinMicroSeconds)
            THROW(ArgumentOutOfRangeException{"Invalid TimeSpan values"});

        m_Ticks = totalMicroseconds * TicksPerMicrosecond;
    }

    constexpr usize TimeSpan::GetHashCode() const { return m_Ticks ^ (m_Ticks >> 32); }

    constexpr TimeSpan TimeSpan::Interval(const f64 ticks, const f64 scale)
    {
        if (Calc::IsNan(ticks))
            THROW(ArgumentException{"Cannot create an interval from a NaN amount of ticks", "ticks"});

        return IntervalFromDoubleTicks(ticks * scale);
    }

    constexpr TimeSpan TimeSpan::IntervalFromDoubleTicks(const f64 ticks)
    {
        if (ticks > static_cast<f64>(std::numeric_limits<s64>::max()) || ticks < static_cast<f64>(std::numeric_limits<s64>::min()) || Calc::IsNan(ticks))
            THROW(OverflowException{"Invalid TimeSpan ticks"});

        if (ticks == static_cast<f64>(std::numeric_limits<s64>::max()))
            return MaxValue();

        return TimeSpan{static_cast<s64>(ticks)};
    }
}
