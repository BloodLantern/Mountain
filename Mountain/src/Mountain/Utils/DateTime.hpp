#pragma once

#include "Mountain/Core.hpp"
#include "Mountain/Containers/Array.hpp"
#include "Mountain/Utils/TimeSpan.hpp"

namespace Mountain
{
    enum class DayOfWeek : uint8_t
    {
        Monday,
        Tuesday,
        Wednesday,
        Thursday,
        Friday,
        Saturday,
        Sunday
    };

    struct DateTime
    {
        static constexpr DateTime MinValue();
        static constexpr DateTime MaxValue();
        static constexpr DateTime UnixEpoch();

        MOUNTAIN_API static DateTime Now();

        MOUNTAIN_API static DateTime UtcNow();

        MOUNTAIN_API static DateTime Today();

        constexpr DateTime() = default;

        explicit constexpr DateTime(int64_t ticks);

        explicit constexpr DateTime(uint64_t dateData);

        constexpr DateTime(int32_t year, int32_t month, int32_t day);

        constexpr DateTime(
            int32_t year,
            int32_t month,
            int32_t day,
            int32_t hour,
            int32_t minute,
            int32_t second
        );

        constexpr DateTime(
            int32_t year,
            int32_t month,
            int32_t day,
            int32_t hour,
            int32_t minute,
            int32_t second,
            int32_t millisecond
            );

        constexpr DateTime(
            int32_t year,
            int32_t month,
            int32_t day,
            int32_t hour,
            int32_t minute,
            int32_t second,
            int32_t millisecond,
            int32_t microsecond
        );

        ATTRIBUTE_NODISCARD
        constexpr DateTime GetDate() const;
        ATTRIBUTE_NODISCARD
        constexpr TimeSpan GetTimeOfDay() const;

        ATTRIBUTE_NODISCARD
        constexpr DayOfWeek GetDayOfWeek() const;
        ATTRIBUTE_NODISCARD
        constexpr int32_t GetDayOfYear() const;

        ATTRIBUTE_NODISCARD
        constexpr int32_t GetYear() const;
        ATTRIBUTE_NODISCARD
        constexpr int32_t GetMonth() const;
        ATTRIBUTE_NODISCARD
        constexpr int32_t GetDay() const;
        ATTRIBUTE_NODISCARD
        constexpr int32_t GetHour() const;
        ATTRIBUTE_NODISCARD
        constexpr int32_t GetMinute() const;
        ATTRIBUTE_NODISCARD
        constexpr int32_t GetSecond() const;
        ATTRIBUTE_NODISCARD
        constexpr int32_t GetMillisecond() const;
        ATTRIBUTE_NODISCARD
        constexpr int32_t GetMicrosecond() const;
        ATTRIBUTE_NODISCARD
        constexpr int32_t GetNanosecond() const;

        friend constexpr TimeSpan operator-(DateTime lhs, DateTime rhs);

        friend constexpr DateTime& operator+=(DateTime& lhs, TimeSpan rhs);
        friend constexpr DateTime& operator-=(DateTime& lhs, TimeSpan rhs);

        ATTRIBUTE_NODISCARD
        friend constexpr std::strong_ordering operator<=>(DateTime, DateTime) = default;

        ATTRIBUTE_NODISCARD
        std::string ToString() const;

        ATTRIBUTE_NODISCARD
        constexpr size_t GetHashCode() const;

        ATTRIBUTE_NODISCARD
        constexpr int64_t GetTicks() const;

        constexpr GETTER(uint64_t, DateData, m_DateData)

    private:
        /// @brief Number of days in a non-leap year
        static constexpr int32_t DaysPerYear = 365;
        /// @brief Number of days in 4 years
        static constexpr int32_t DaysPer4Years = DaysPerYear * 4 + 1;       // 1,461
        /// @brief Number of days in 100 years
        static constexpr int32_t DaysPer100Years = DaysPer4Years * 25 - 1;  // 36,524
        /// @brief Number of days in 400 years
        static constexpr int32_t DaysPer400Years = DaysPer100Years * 4 + 1; // 146,097

        /// @brief Number of days from 1/1/0001 to 12/31/1600
        static constexpr int32_t DaysTo1601 = DaysPer400Years * 4;          // 584,388
        /// @brief Number of days from 1/1/0001 to 12/30/1899
        static constexpr int32_t DaysTo1899 = DaysPer400Years * 4 + DaysPer100Years * 3 - 367;
        /// @brief Number of days from 1/1/0001 to 12/31/1969
        static constexpr int32_t DaysTo1970 = DaysPer400Years * 4 + DaysPer100Years * 3 + DaysPer4Years * 17 + DaysPerYear; // 719,162
        /// @brief Number of days from 1/1/0001 to 12/31/9999
        static constexpr int32_t DaysTo10000 = DaysPer400Years * 25 - 366;  // 3,652,059

        static constexpr int64_t MinTicks = 0;
        static constexpr int64_t MaxTicks = DaysTo10000 * TimeSpan::TicksPerDay - 1;
        static constexpr int64_t MaxMicroseconds = MaxTicks / TimeSpan::TicksPerMicrosecond;
        static constexpr int64_t MaxMillis = MaxTicks / TimeSpan::TicksPerMillisecond;
        static constexpr int64_t MaxSeconds = MaxTicks / TimeSpan::TicksPerSecond;
        static constexpr int64_t MaxMinutes = MaxTicks / TimeSpan::TicksPerMinute;
        static constexpr int64_t MaxHours = MaxTicks / TimeSpan::TicksPerHour;
        static constexpr int64_t MaxDays = static_cast<int64_t>(DaysTo10000) - 1;

        static constexpr int64_t UnixEpochTicks = DaysTo1970 * TimeSpan::TicksPerDay;
        static constexpr int64_t FileTimeOffset = DaysTo1601 * TimeSpan::TicksPerDay;
        static constexpr int64_t DoubleDateOffset = DaysTo1899 * TimeSpan::TicksPerDay;

        static constexpr Array<uint32_t, 13> DaysToMonth365 = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365};
        static constexpr Array<uint32_t, 13> DaysToMonth366 = {0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366};

        static constexpr Array<uint8_t, 12> DaysInMonth365 = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        static constexpr Array<uint8_t, 12> DaysInMonth366 = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

        static constexpr uint64_t TicksMask = 0x3FFFFFFFFFFFFFFF;
        static constexpr uint64_t FlagsMask = 0xC000000000000000;
        static constexpr int64_t TicksCeiling = 0x4000000000000000;
        static constexpr uint64_t KindUtc = 0x4000000000000000;
        static constexpr uint64_t KindLocal = 0x8000000000000000;
        static constexpr uint64_t KindLocalAmbiguousDst = 0xC000000000000000;
        static constexpr int32_t KindShift = 62;

        static constexpr uint32_t EafMultiplier = ((1ull << 32) + DaysPer4Years - 1) / DaysPer4Years;
        static constexpr uint32_t EafDivider = EafMultiplier * 4;

        static constexpr uint64_t TicksPer6Hours = TimeSpan::TicksPerHour * 6;
        /// @brief Days between March 1 and January 1
        static constexpr int32_t March1BasedDayOfNewYear = 306;

        ATTRIBUTE_NODISCARD
        constexpr uint64_t GetUTicks() const;

        ATTRIBUTE_NODISCARD
        constexpr uint64_t GetInternalKind() const;

        static constexpr uint64_t DateToTicks(int32_t year, int32_t month, int32_t day);
        static constexpr uint32_t DaysToYear(uint32_t year);
        static constexpr bool_t IsLeapYear(int32_t year);
        static constexpr uint64_t TimeToTicks(int32_t hour, int32_t minute, int32_t second);

        uint64_t m_DateData = 0;
    };

    CHECK_REQUIREMENT(Requirements::StringConvertible, DateTime);
    CHECK_REQUIREMENT(Requirements::Hashable, DateTime);

    ATTRIBUTE_NODISCARD
    constexpr DateTime operator+(DateTime dateTime, TimeSpan timeSpan);
    ATTRIBUTE_NODISCARD
    constexpr DateTime operator-(DateTime dateTime, TimeSpan timeSpan);
}

// Start of DateTime.inl

namespace Mountain
{
    constexpr DateTime DateTime::MinValue() { return DateTime{}; }

    constexpr DateTime DateTime::MaxValue() { return DateTime{MaxTicks}; }

    constexpr DateTime DateTime::UnixEpoch() { return DateTime{UnixEpochTicks}; }

    constexpr DateTime::DateTime(const int64_t ticks)
    {
        if (static_cast<uint64_t>(ticks) > MaxTicks)
            THROW(ArgumentOutOfRangeException{"Invalid ticks value.", "ticks"});
        m_DateData = static_cast<uint64_t>(ticks);
    }

    constexpr DateTime::DateTime(const uint64_t dateData)
        : m_DateData{dateData}
    {
    }

    constexpr DateTime::DateTime(const int32_t year, const int32_t month, const int32_t day)
    {
        m_DateData = DateToTicks(year, month, day);
    }

    constexpr DateTime::DateTime(const int32_t year, const int32_t month, const int32_t day, const int32_t hour, const int32_t minute, const int32_t second)
    {
        m_DateData = DateToTicks(year, month, day) + TimeToTicks(hour, minute, second);
    }

    constexpr DateTime::DateTime(
        const int32_t year,
        const int32_t month,
        const int32_t day,
        const int32_t hour,
        const int32_t minute,
        const int32_t second,
        const int32_t millisecond
    )
        : DateTime(year, month, day, hour, minute, second)
    {
        if (static_cast<uint32_t>(millisecond) >= TimeSpan::MillisecondsPerSecond)
            THROW(ArgumentOutOfRangeException{"Invalid millisecond value.", "millisecond"});
        m_DateData += static_cast<uint64_t>(millisecond) * static_cast<uint64_t>(TimeSpan::TicksPerMillisecond);
    }

    constexpr DateTime::DateTime(
        const int32_t year,
        const int32_t month,
        const int32_t day,
        const int32_t hour,
        const int32_t minute,
        const int32_t second,
        const int32_t millisecond,
        const int32_t microsecond
    )
        : DateTime(year, month, day, hour, minute, second, millisecond)
    {
        if (static_cast<uint32_t>(microsecond) >= TimeSpan::MicrosecondsPerMillisecond)
            THROW(ArgumentOutOfRangeException{"Invalid microsecond value.", "microsecond"});
        m_DateData += static_cast<uint64_t>(microsecond) * static_cast<uint64_t>(TimeSpan::TicksPerMicrosecond);
    }

    constexpr DateTime DateTime::GetDate() const
    {
        return DateTime{GetUTicks() / TimeSpan::TicksPerDay * TimeSpan::TicksPerDay | GetInternalKind()};
    }

    constexpr TimeSpan DateTime::GetTimeOfDay() const
    {
        return TimeSpan{static_cast<int64_t>(GetUTicks() % TimeSpan::TicksPerDay)};
    }

    constexpr DayOfWeek DateTime::GetDayOfWeek() const
    {
        return static_cast<DayOfWeek>((static_cast<uint32_t>(GetUTicks() / TimeSpan::TicksPerDay) + 1) % 7);
    }

    constexpr int32_t DateTime::GetDayOfYear() const
    {
        return 1 + static_cast<int32_t>(((static_cast<uint32_t>(GetUTicks() / TicksPer6Hours) | 3U)
                                         % static_cast<uint32_t>(DaysPer400Years) | 3U) * EafMultiplier / EafDivider);
    }

    constexpr int32_t DateTime::GetYear() const
    {
        // y100 = number of whole 100-year periods since 1/1/0001
        // r1 = (day number within 100-year period) * 4

        const uint32_t left = static_cast<uint32_t>((m_DateData & TicksMask) / TicksPer6Hours) | 3U;
        constexpr uint32_t right = DaysPer400Years;

        const uint32_t quotient = left / right;
        const uint32_t y100 = quotient;
        const uint32_t r1 = left - (quotient * right);

        return 1 + static_cast<int32_t>(100 * y100 + (r1 | 3) / DaysPer4Years);
    }

    constexpr int32_t DateTime::GetMonth() const
    {
        // r1 = (day number within 100-year period) * 4
        const uint32_t r1 = ((static_cast<uint32_t>(GetUTicks() / TicksPer6Hours) | 3U) + 1224) % DaysPer400Years;
        const uint64_t u2 = static_cast<uint64_t>(EafMultiplier) * r1 | 3U;
        const uint16_t daySinceMarch1 = static_cast<uint16_t>(static_cast<uint32_t>(u2) / EafDivider);
        const int n3 = 2141 * daySinceMarch1 + 197913;
        return static_cast<uint16_t>(n3 >> 16) - (daySinceMarch1 >= March1BasedDayOfNewYear ? 12 : 0);
    }

    constexpr int32_t DateTime::GetDay() const
    {
        // r1 = (day number within 100-year period) * 4
        const uint32_t r1 = ((static_cast<uint32_t>(GetUTicks() / TicksPer6Hours) | 3U) + 1224) % DaysPer400Years;
        const uint64_t u2 = static_cast<uint64_t>(EafMultiplier) * (r1 | 3U);
        const uint16_t daySinceMarch1 = static_cast<uint16_t>(static_cast<uint32_t>(u2) / EafDivider);
        const int n3 = 2141 * daySinceMarch1 + 197913;
        // Return 1-based day-of-month
        return static_cast<uint16_t>(n3) / 2141 + 1;
    }

    constexpr int32_t DateTime::GetHour() const
    {
        return static_cast<int32_t>(static_cast<uint32_t>(GetUTicks() / TimeSpan::TicksPerHour) % 24);
    }

    constexpr int32_t DateTime::GetMinute() const
    {
        return static_cast<int32_t>(GetUTicks() / TimeSpan::TicksPerMinute % 60);
    }

    constexpr int32_t DateTime::GetSecond() const
    {
        return static_cast<int32_t>(GetUTicks() / TimeSpan::TicksPerSecond % 60);
    }

    constexpr int32_t DateTime::GetMillisecond() const
    {
        return static_cast<int32_t>(GetUTicks() / TimeSpan::TicksPerMillisecond % 1000);
    }

    constexpr int32_t DateTime::GetMicrosecond() const
    {
        return static_cast<int32_t>(GetUTicks() / TimeSpan::TicksPerMicrosecond % 1000);
    }

    constexpr int32_t DateTime::GetNanosecond() const
    {
        return static_cast<int32_t>(GetUTicks() % TimeSpan::TicksPerMicrosecond) * 100;
    }

    constexpr TimeSpan operator-(const DateTime lhs, const DateTime rhs)
    {
        return TimeSpan{lhs.GetTicks() - rhs.GetTicks()};
    }

    constexpr DateTime& operator+=(DateTime& lhs, const TimeSpan rhs)
    {
        lhs = DateTime{lhs.GetTicks() + rhs.GetTicks()};
        return lhs;
    }

    constexpr DateTime& operator-=(DateTime& lhs, const TimeSpan rhs)
    {
        lhs = DateTime{lhs.GetTicks() - rhs.GetTicks()};
        return lhs;
    }

    constexpr size_t DateTime::GetHashCode() const
    {
        const int64_t ticks = GetTicks();
        return static_cast<int32_t>(ticks) ^ static_cast<int32_t>(ticks >> 32);
    }

    constexpr int64_t DateTime::GetTicks() const
    {
        return static_cast<int64_t>(m_DateData & TicksMask);
    }

    constexpr uint64_t DateTime::GetUTicks() const { return m_DateData & TicksMask; }

    constexpr uint64_t DateTime::GetInternalKind() const { return m_DateData & FlagsMask; }

    constexpr uint64_t DateTime::DateToTicks(const int32_t year, const int32_t month, const int32_t day)
    {
        if (year < 1 || year > 9999 || month < 1 || month > 12 || day < 1)
            THROW(ArgumentOutOfRangeException{"At least one of year, month, day has an invalid value."});

        Array days = IsLeapYear(year) ? DaysToMonth366 : DaysToMonth365;
        if (static_cast<uint32_t>(day) > days[month] - days[month - 1])
            THROW(ArgumentOutOfRangeException{"At least one of year, month, day has an invalid value."});

        const uint32_t n = DaysToYear(static_cast<uint32_t>(year)) + days[month - 1] + static_cast<uint32_t>(day) - 1;
        return n * static_cast<uint64_t>(TimeSpan::TicksPerDay);
    }

    constexpr uint32_t DateTime::DaysToYear(const uint32_t year)
    {
        const uint32_t y = year - 1;
        const uint32_t cent = y / 100;
        return y * (365 * 4 + 1) / 4 - cent + cent / 4;
    }

    constexpr bool_t DateTime::IsLeapYear(const int32_t year)
    {
        if (year < 1 || year > 9999)
            THROW(ArgumentOutOfRangeException{"Invalid year value.", "year"});
        if ((year & 3) != 0) return false;
        if ((year & 15) == 0) return true;
        return static_cast<uint32_t>(year) % 25 != 0;
    }

    constexpr uint64_t DateTime::TimeToTicks(const int32_t hour, const int32_t minute, const int32_t second)
    {
        if (static_cast<uint32_t>(hour) >= 24 || static_cast<uint32_t>(minute) >= 60 || static_cast<uint32_t>(second) >= 60)
            THROW(ArgumentOutOfRangeException{"At least one of hour, minute, second has an invalid value."});

        const int32_t totalSeconds = hour * 3600 + minute * 60 + second;
        return static_cast<uint32_t>(totalSeconds) * static_cast<uint64_t>(TimeSpan::TicksPerSecond);
    }

    constexpr DateTime operator+(DateTime dateTime, const TimeSpan timeSpan)
    {
        return dateTime += timeSpan;
    }

    constexpr DateTime operator-(DateTime dateTime, const TimeSpan timeSpan)
    {
        return dateTime -= timeSpan;
    }
}
