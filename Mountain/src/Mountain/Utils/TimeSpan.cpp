#include "Mountain/Utils/TimeSpan.hpp"

#include "Mountain/Exceptions/ThrowHelper.hpp"

using namespace Mountain;

// ReSharper disable CppClangTidyReadabilitySuspiciousCallArgument
TimeSpan TimeSpan::FromDays(const double_t days) { return Interval(days, TicksPerDay); }

TimeSpan TimeSpan::FromHours(const double_t hours) { return Interval(hours, TicksPerHour); }

TimeSpan TimeSpan::FromMinutes(const double_t minutes) { return Interval(minutes, TicksPerMinute); }

TimeSpan TimeSpan::FromSeconds(const double_t seconds) { return Interval(seconds, TicksPerSecond); }

TimeSpan TimeSpan::FromMilliseconds(const double_t milliseconds) { return Interval(milliseconds, TicksPerMillisecond); }

TimeSpan TimeSpan::FromMicroseconds(const double_t microseconds) { return Interval(microseconds, TicksPerMicrosecond); }
// ReSharper restore CppClangTidyReadabilitySuspiciousCallArgument

TimeSpan TimeSpan::FromTicks(const int64_t ticks) { return TimeSpan{ticks}; }

int32_t TimeSpan::GetDays() const { return static_cast<int32_t>(m_Ticks / TicksPerDay); }

int32_t TimeSpan::GetHours() const { return static_cast<int32_t>(m_Ticks / TicksPerHour % 24); }

int32_t TimeSpan::GetMinutes() const { return static_cast<int32_t>(m_Ticks / TicksPerMinute % 60); }

int32_t TimeSpan::GetSeconds() const { return static_cast<int32_t>(m_Ticks / TicksPerSecond % 60); }

int32_t TimeSpan::GetMilliseconds() const { return static_cast<int32_t>(m_Ticks / TicksPerMillisecond % 1000); }

int32_t TimeSpan::GetMicroseconds() const { return static_cast<int32_t>(m_Ticks / TicksPerMicrosecond % 1000); }

int32_t TimeSpan::GetNanoseconds() const { return static_cast<int32_t>(m_Ticks % TicksPerMicrosecond * NanosecondsPerTick); }

double_t TimeSpan::GetTotalDays() const { return static_cast<double_t>(m_Ticks) / TicksPerDay; }

double_t TimeSpan::GetTotalHours() const { return static_cast<double_t>(m_Ticks) / TicksPerHour; }

double_t TimeSpan::GetTotalMinutes() const { return static_cast<double_t>(m_Ticks) / TicksPerMinute; }

double_t TimeSpan::GetTotalSeconds() const { return static_cast<double_t>(m_Ticks) / TicksPerSecond; }

double_t TimeSpan::GetTotalMilliseconds() const
{
    const double_t temp = static_cast<double_t>(m_Ticks) / TicksPerMillisecond;

    if (temp > MaxMilliSeconds)
        return MaxMilliSeconds;

    if (temp < MinMilliSeconds)
        return MinMilliSeconds;

    return temp;
}

double_t TimeSpan::GetTotalMicroseconds() const { return static_cast<double_t>(m_Ticks) / TicksPerMicrosecond; }

double_t TimeSpan::GetTotalNanoseconds() const { return static_cast<double_t>(m_Ticks) * NanosecondsPerTick; }

TimeSpan TimeSpan::Duration() const
{
    if (m_Ticks == MinValue().m_Ticks)
        THROW(OverflowException{"TimeSpan Duration overflow"});
    return TimeSpan{m_Ticks >= 0 ? m_Ticks : -m_Ticks};
}

TimeSpan Mountain::operator+(const TimeSpan a, const TimeSpan b)
{
    const int64_t result = a.m_Ticks + b.m_Ticks;

    // Overflow if signs of operands was identical and result's
    // sign was opposite.
    // >> 63 gives the sign bit (either 64 1's or 64 0's).
    if ((a.m_Ticks >> 63 == b.m_Ticks >> 63) && (a.m_Ticks >> 63 != result >> 63))
        THROW(OverflowException{"TimeSpan sum overflow"});

    return TimeSpan{result};
}

TimeSpan Mountain::operator-(const TimeSpan v)
{
    if (v.m_Ticks == TimeSpan::MinValue().m_Ticks)
        THROW(OverflowException{"Cannot negate the MinValue TimeSpan because of Two's Complement"});
    return TimeSpan{-v.m_Ticks};
}

TimeSpan Mountain::operator-(const TimeSpan a, const TimeSpan b)
{
    const int64_t result = a.m_Ticks + b.m_Ticks;

    // Overflow if signs of operands was different and result's
    // sign was opposite.
    // >> 63 gives the sign bit (either 64 1's or 64 0's).
    if ((a.m_Ticks >> 63 != b.m_Ticks >> 63) && (a.m_Ticks >> 63 != result >> 63))
        THROW(OverflowException{"TimeSpan difference underflow"});

    return TimeSpan{result};
}

TimeSpan Mountain::operator*(const TimeSpan v, const double_t factor)
{
    if (std::isnan(factor))
        THROW(ArgumentException{"Cannot multiply a TimeSpan by a NaN factor", "factor"});

    const double_t ticks = std::round(static_cast<double_t>(v.m_Ticks) * factor);
    return TimeSpan::IntervalFromDoubleTicks(ticks);
}

TimeSpan Mountain::operator*(const double_t factor, const TimeSpan v) { return v * factor; }

TimeSpan Mountain::operator/(const TimeSpan v, const double_t divisor)
{
    if (std::isnan(divisor))
        THROW(ArgumentException{"Cannot divide a TimeSpan by a NaN divisor", "divisor"});

    const double_t ticks = std::round(static_cast<double_t>(v.m_Ticks) / divisor);
    return TimeSpan::IntervalFromDoubleTicks(ticks);
}

double_t Mountain::operator/(const TimeSpan a, const TimeSpan b) { return static_cast<double_t>(a.m_Ticks) / static_cast<double_t>(b.m_Ticks); }

TimeSpan& Mountain::operator+=(TimeSpan& a, const TimeSpan b) { return a = a + b; }

TimeSpan& Mountain::operator-=(TimeSpan& a, const TimeSpan b) { return a = a - b; }

TimeSpan& Mountain::operator*=(TimeSpan& v, const double_t factor) { return v = v * factor; }

TimeSpan& Mountain::operator/=(TimeSpan& v, const double_t divisor) { return v = v / divisor; }

std::string TimeSpan::ToString() const
{
    std::string result;

    const bool_t daysCheck = GetDays() > 0;
    const bool_t hoursCheck = GetHours() > 0;
    const bool_t minutesCheck = GetMinutes() > 0;

    if (daysCheck)
        result += std::format("{}.", GetDays());

    if (daysCheck || hoursCheck)
        result += std::format("{:2}:", GetHours());

    if (daysCheck || hoursCheck || minutesCheck)
        result += std::format("{:2}:", GetMinutes());

    result += std::format("{}", GetSeconds());

    const bool_t millisecondsCheck = GetMilliseconds() > 0;
    const bool_t microsecondsCheck = GetMicroseconds() > 0;
    const bool_t nanosecondsCheck = GetNanoseconds() > 0;

    if (nanosecondsCheck || microsecondsCheck)
        result += std::format(".{:03}", GetMilliseconds());
    else if (millisecondsCheck)
        result += std::format(".{}", GetMilliseconds());

    if (nanosecondsCheck || microsecondsCheck)
        result += std::format("{:03}", GetMicroseconds());
    else if (microsecondsCheck)
        result += std::format(".{}", GetMilliseconds());

    if (nanosecondsCheck)
        result += std::format("{}", GetNanoseconds());

    return result;
}

TimeSpan TimeSpan::Interval(const double_t ticks, const double_t scale)
{
    if (std::isnan(ticks))
        THROW(ArgumentException{"Cannot create an interval from a NaN amount of ticks", "ticks"});
    return IntervalFromDoubleTicks(ticks * scale);
}

TimeSpan TimeSpan::IntervalFromDoubleTicks(const double_t ticks)
{
    if (ticks > static_cast<double_t>(std::numeric_limits<int64_t>::max()) || ticks < static_cast<double_t>(std::numeric_limits<int64_t>::min()) || std::isnan(ticks))
        THROW(OverflowException{"Invalid TimeSpan ticks"});
    if (ticks == static_cast<double_t>(std::numeric_limits<int64_t>::max()))
        return MaxValue();
    return TimeSpan{static_cast<int64_t>(ticks)};
}
