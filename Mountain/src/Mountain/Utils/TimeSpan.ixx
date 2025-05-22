export module Mountain:Utils_TimeSpan;

import "Mountain/Core.hpp";

import std;
export import :Core;

export namespace Mountain
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

        [[nodiscard]]
        static constexpr TimeSpan Zero();
        [[nodiscard]]
        static constexpr TimeSpan MaxValue();
        [[nodiscard]]
        static constexpr TimeSpan MinValue();

        [[nodiscard]]
        static TimeSpan FromDays(double_t days);
        [[nodiscard]]
        static TimeSpan FromHours(double_t hours);
        [[nodiscard]]
        static TimeSpan FromMinutes(double_t minutes);
        [[nodiscard]]
        static TimeSpan FromSeconds(double_t seconds);
        [[nodiscard]]
        static TimeSpan FromMilliseconds(double_t milliseconds);
        [[nodiscard]]
        static TimeSpan FromMicroseconds(double_t microseconds);
        [[nodiscard]]
        static TimeSpan FromTicks(int64_t ticks);

        [[nodiscard]]
        explicit constexpr TimeSpan(int64_t ticks);
        [[nodiscard]]
        constexpr TimeSpan(int32_t hours, int32_t minutes, int32_t seconds);
        [[nodiscard]]
        constexpr TimeSpan(int32_t days, int32_t hours, int32_t minutes, int32_t seconds, int32_t milliseconds = 0, int32_t microseconds = 0);

        GETTER(int64_t, Ticks, m_Ticks)

        [[nodiscard]]
        int32_t GetDays() const;
        [[nodiscard]]
        int32_t GetHours() const;
        [[nodiscard]]
        int32_t GetMinutes() const;
        [[nodiscard]]
        int32_t GetSeconds() const;
        [[nodiscard]]
        int32_t GetMilliseconds() const;
        [[nodiscard]]
        int32_t GetMicroseconds() const;
        [[nodiscard]]
        int32_t GetNanoseconds() const;

        [[nodiscard]]
        double_t GetTotalDays() const;
        [[nodiscard]]
        double_t GetTotalHours() const;
        [[nodiscard]]
        double_t GetTotalMinutes() const;
        [[nodiscard]]
        double_t GetTotalSeconds() const;
        [[nodiscard]]
        double_t GetTotalMilliseconds() const;
        [[nodiscard]]
        double_t GetTotalMicroseconds() const;
        [[nodiscard]]
        double_t GetTotalNanoseconds() const;

        [[nodiscard]]
        TimeSpan Duration() const;

        [[nodiscard]]
        friend auto operator<=>(TimeSpan, TimeSpan) = default;

        friend TimeSpan operator+(TimeSpan a, TimeSpan b);
        friend TimeSpan operator-(TimeSpan v);
        friend TimeSpan operator-(TimeSpan a, TimeSpan b);
        friend TimeSpan operator*(TimeSpan v, double_t factor);
        friend TimeSpan operator*(double_t factor, TimeSpan v);
        friend TimeSpan operator/(TimeSpan v, double_t divisor);
        friend double_t operator/(TimeSpan a, TimeSpan b);

        friend TimeSpan& operator+=(TimeSpan& a, TimeSpan b);
        friend TimeSpan& operator-=(TimeSpan& a, TimeSpan b);
        friend TimeSpan& operator*=(TimeSpan& v, double_t factor);
        friend TimeSpan& operator/=(TimeSpan& v, double_t divisor);

        friend std::ostream& operator<<(std::ostream& out, const TimeSpan& timeSpan);

    private:
        static constexpr int64_t MaxSeconds = std::numeric_limits<int64_t>::max() / TicksPerSecond;
        static constexpr int64_t MinSeconds = std::numeric_limits<int64_t>::min() / TicksPerSecond;

        static constexpr int64_t MaxMilliSeconds = std::numeric_limits<int64_t>::max() / TicksPerMillisecond;
        static constexpr int64_t MinMilliSeconds = std::numeric_limits<int64_t>::min() / TicksPerMillisecond;

        static constexpr int64_t MaxMicroSeconds = std::numeric_limits<int64_t>::max() / TicksPerMicrosecond;
        static constexpr int64_t MinMicroSeconds = std::numeric_limits<int64_t>::min() / TicksPerMicrosecond;

        static constexpr int64_t TicksPerTenthSecond = TicksPerMillisecond * 100;

        [[nodiscard]]
        static TimeSpan Interval(double_t ticks, double_t scale);
        [[nodiscard]]
        static TimeSpan IntervalFromDoubleTicks(double_t ticks);

        int64_t m_Ticks;
    };
}

/// @brief @c std::hash template specialization for the @c Mountain::TimeSpan type.
export template <>
struct std::hash<Mountain::TimeSpan>
{
    size_t operator()(const Mountain::TimeSpan& timeSpan) const noexcept
    {
        return timeSpan.GetTicks() ^ (timeSpan.GetTicks() >> 32);
    }
};

/// @brief @c std::formatter template specialization for the @c Mountain::TimeSpan type.
export template <>
struct std::formatter<Mountain::TimeSpan>
{
    /// @brief Parses the input formatting options.
    template <class ParseContext>
    constexpr typename ParseContext::iterator parse(ParseContext& ctx)
    {
        auto it = ctx.begin();
        if (it == ctx.end())
            return it;

        if (*it != '}')
            throw std::format_error("Invalid format args for Mountain::TimeSpan");

        return it;
    }

    // ReSharper disable once CppMemberFunctionMayBeStatic
    /// @brief Formats a string using the given instance of Mountain::TimeSpan, according to the given options in the parse function.
    template <class FormatContext>
    typename FormatContext::iterator format(const Mountain::TimeSpan& timeSpan, FormatContext& ctx) const
    {
        std::ostringstream out;

        const bool_t daysCheck = timeSpan.GetDays() > 0;
        const bool_t hoursCheck = timeSpan.GetHours() > 0;
        const bool_t minutesCheck = timeSpan.GetMinutes() > 0;

        if (daysCheck)
            out << timeSpan.GetDays() << '.';

        if (daysCheck || hoursCheck)
            out << std::format("{:2}:", timeSpan.GetHours());

        if (daysCheck || hoursCheck || minutesCheck)
            out << std::format("{:2}:", timeSpan.GetMinutes());

        out << timeSpan.GetSeconds();

        const bool_t millisecondsCheck = timeSpan.GetMilliseconds() > 0;
        const bool_t microsecondsCheck = timeSpan.GetMicroseconds() > 0;
        const bool_t nanosecondsCheck = timeSpan.GetNanoseconds() > 0;

        if (nanosecondsCheck || microsecondsCheck)
            out << std::format(".{:03}", timeSpan.GetMilliseconds());
        else if (millisecondsCheck)
            out << std::format(".{}", timeSpan.GetMilliseconds());

        if (nanosecondsCheck || microsecondsCheck)
            out << std::format("{:03}", timeSpan.GetMicroseconds());
        else if (microsecondsCheck)
            out << std::format(".{}", timeSpan.GetMilliseconds());

        if (nanosecondsCheck)
            out << std::format("{}", timeSpan.GetNanoseconds());

        return std::ranges::copy(std::move(out).str(), ctx.out()).out;
    }
};

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
