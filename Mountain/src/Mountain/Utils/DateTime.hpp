#pragma once

#include "Mountain/Core.hpp"
#include "Mountain/Containers/Array.hpp"
#include "Mountain/Utils/TimeSpan.hpp"

namespace Mountain
{
    enum class DateTimeKind : u8
    {
        Unspecified,
        Utc,
        Local
    };

    enum class DayOfWeek : u8
    {
        Monday,
        Tuesday,
        Wednesday,
        Thursday,
        Friday,
        Saturday,
        Sunday
    };

    /// @brief C++ reimplementation of the .NET DateTime struct
    /// @details Represents an instant in time, typically expressed as a date and time of day.
    /// @see Source: https://github.com/dotnet/runtime/blob/release/8.0/src/libraries/System.Private.CoreLib/src/System/DateTime.cs
    struct DateTime
    {
        static constexpr DateTime MinValue();
        static constexpr DateTime MaxValue();
        static constexpr DateTime UnixEpoch();

        MOUNTAIN_API static DateTime Now();

        MOUNTAIN_API static DateTime UtcNow();

        MOUNTAIN_API static DateTime Today();

        constexpr DateTime() = default;

        explicit constexpr DateTime(s64 ticks);

        explicit constexpr DateTime(u64 dateData);

        constexpr DateTime(s32 year, s32 month, s32 day);

        constexpr DateTime(
            s32 year,
            s32 month,
            s32 day,
            s32 hour,
            s32 minute,
            s32 second
        );

        constexpr DateTime(
            s32 year,
            s32 month,
            s32 day,
            s32 hour,
            s32 minute,
            s32 second,
            s32 millisecond
        );

        constexpr DateTime(
            s32 year,
            s32 month,
            s32 day,
            s32 hour,
            s32 minute,
            s32 second,
            s32 millisecond,
            s32 microsecond
        );

        ATTRIBUTE_NODISCARD
        constexpr DateTime GetDate() const;
        ATTRIBUTE_NODISCARD
        constexpr TimeSpan GetTimeOfDay() const;

        ATTRIBUTE_NODISCARD
        constexpr DayOfWeek GetDayOfWeek() const;
        ATTRIBUTE_NODISCARD
        constexpr s32 GetDayOfYear() const;

        ATTRIBUTE_NODISCARD
        constexpr s32 GetYear() const;
        ATTRIBUTE_NODISCARD
        constexpr s32 GetMonth() const;
        ATTRIBUTE_NODISCARD
        constexpr s32 GetDay() const;
        ATTRIBUTE_NODISCARD
        constexpr s32 GetHour() const;
        ATTRIBUTE_NODISCARD
        constexpr s32 GetMinute() const;
        ATTRIBUTE_NODISCARD
        constexpr s32 GetSecond() const;
        ATTRIBUTE_NODISCARD
        constexpr s32 GetMillisecond() const;
        ATTRIBUTE_NODISCARD
        constexpr s32 GetMicrosecond() const;
        ATTRIBUTE_NODISCARD
        constexpr s32 GetNanosecond() const;

        friend constexpr TimeSpan operator-(DateTime lhs, DateTime rhs);

        friend constexpr DateTime& operator+=(DateTime& lhs, TimeSpan rhs);
        friend constexpr DateTime& operator-=(DateTime& lhs, TimeSpan rhs);

        ATTRIBUTE_NODISCARD
        friend constexpr std::strong_ordering operator<=>(DateTime, DateTime) = default;

        ATTRIBUTE_NODISCARD
        MOUNTAIN_API std::string ToString() const;

        ATTRIBUTE_NODISCARD
        constexpr usize GetHashCode() const;

        ATTRIBUTE_NODISCARD
        constexpr s64 GetTicks() const;

        ATTRIBUTE_NODISCARD
        constexpr DateTimeKind GetKind() const;

        CONSTEXPR_GETTER_M(u64, DateData)

    private:
        /// @brief Number of days in a non-leap year
        static constexpr s32 DaysPerYear = 365;
        /// @brief Number of days in 4 years
        static constexpr s32 DaysPer4Years = DaysPerYear * 4 + 1;       // 1,461
        /// @brief Number of days in 100 years
        static constexpr s32 DaysPer100Years = DaysPer4Years * 25 - 1;  // 36,524
        /// @brief Number of days in 400 years
        static constexpr s32 DaysPer400Years = DaysPer100Years * 4 + 1; // 146,097

        /// @brief Number of days from 1/1/0001 to 12/31/1600
        static constexpr s32 DaysTo1601 = DaysPer400Years * 4;          // 584,388
        /// @brief Number of days from 1/1/0001 to 12/30/1899
        static constexpr s32 DaysTo1899 = DaysPer400Years * 4 + DaysPer100Years * 3 - 367;
        /// @brief Number of days from 1/1/0001 to 12/31/1969
        static constexpr s32 DaysTo1970 = DaysPer400Years * 4 + DaysPer100Years * 3 + DaysPer4Years * 17 + DaysPerYear; // 719,162
        /// @brief Number of days from 1/1/0001 to 12/31/9999
        static constexpr s32 DaysTo10000 = DaysPer400Years * 25 - 366;  // 3,652,059

        static constexpr s64 MinTicks = 0;
        static constexpr s64 MaxTicks = DaysTo10000 * TimeSpan::TicksPerDay - 1;
        static constexpr s64 MaxMicroseconds = MaxTicks / TimeSpan::TicksPerMicrosecond;
        static constexpr s64 MaxMillis = MaxTicks / TimeSpan::TicksPerMillisecond;
        static constexpr s64 MaxSeconds = MaxTicks / TimeSpan::TicksPerSecond;
        static constexpr s64 MaxMinutes = MaxTicks / TimeSpan::TicksPerMinute;
        static constexpr s64 MaxHours = MaxTicks / TimeSpan::TicksPerHour;
        static constexpr s64 MaxDays = static_cast<s64>(DaysTo10000) - 1;

        static constexpr s64 UnixEpochTicks = DaysTo1970 * TimeSpan::TicksPerDay;
        static constexpr s64 FileTimeOffset = DaysTo1601 * TimeSpan::TicksPerDay;
        static constexpr s64 DoubleDateOffset = DaysTo1899 * TimeSpan::TicksPerDay;

        static constexpr Array<u32, 13> DaysToMonth365 = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365};
        static constexpr Array<u32, 13> DaysToMonth366 = {0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366};

        static constexpr Array<u8, 12> DaysInMonth365 = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        static constexpr Array<u8, 12> DaysInMonth366 = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

        static constexpr u64 TicksMask = 0x3FFFFFFFFFFFFFFF;
        static constexpr u64 FlagsMask = 0xC000000000000000;
        static constexpr s64 TicksCeiling = 0x4000000000000000;
        static constexpr u64 KindUtc = 0x4000000000000000;
        static constexpr u64 KindLocal = 0x8000000000000000;
        static constexpr u64 KindLocalAmbiguousDst = 0xC000000000000000;
        static constexpr s32 KindShift = 62;

        static constexpr u32 EafMultiplier = ((1ull << 32) + DaysPer4Years - 1) / DaysPer4Years;
        static constexpr u32 EafDivider = EafMultiplier * 4;

        static constexpr u64 TicksPer6Hours = TimeSpan::TicksPerHour * 6;
        /// @brief Days between March 1 and January 1
        static constexpr s32 March1BasedDayOfNewYear = 306;

        ATTRIBUTE_NODISCARD
        constexpr u64 GetUTicks() const;

        ATTRIBUTE_NODISCARD
        constexpr u64 GetInternalKind() const;

        static constexpr u64 DateToTicks(s32 year, s32 month, s32 day);
        static constexpr u32 DaysToYear(u32 year);
        static constexpr bool IsLeapYear(s32 year);
        static constexpr u64 TimeToTicks(s32 hour, s32 minute, s32 second);

        /// @brief The data is stored as an unsigned 64-bit integer
        ///
        /// - Bits 01-62: The value of 100-nanosecond ticks where 0 represents 1/1/0001 12:00am, up until the value
        ///               12/31/9999 23:59:59.9999999
        /// - Bits 63-64: A four-state value that describes the DateTimeKind value of the date time, with a second
        ///               value for the rare case where the date time is local, but is in an overlapped daylight
        ///               savings time hour, and it is in daylight savings time. This allows distinction of these
        ///               otherwise ambiguous local times and prevents data loss when round tripping from Local to
        ///               UTC time.
        u64 m_DateData = 0;
    };

    CHECK_REQUIREMENT(Requirements::StringConvertible, DateTime);
    CHECK_REQUIREMENT(Requirements::Hashable, DateTime);
    CHECK_REQUIREMENT(Requirements::Equatable, DateTime);
    CHECK_REQUIREMENT(Requirements::Comparable, DateTime);

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

    constexpr DateTime::DateTime(const s64 ticks)
    {
        if (static_cast<u64>(ticks) > MaxTicks)
            THROW(ArgumentOutOfRangeException{"Invalid ticks value.", "ticks"});
        m_DateData = static_cast<u64>(ticks);
    }

    constexpr DateTime::DateTime(const u64 dateData)
        : m_DateData{dateData}
    {
    }

    constexpr DateTime::DateTime(const s32 year, const s32 month, const s32 day)
    {
        m_DateData = DateToTicks(year, month, day);
    }

    constexpr DateTime::DateTime(const s32 year, const s32 month, const s32 day, const s32 hour, const s32 minute, const s32 second)
    {
        m_DateData = DateToTicks(year, month, day) + TimeToTicks(hour, minute, second);
    }

    constexpr DateTime::DateTime(
        const s32 year,
        const s32 month,
        const s32 day,
        const s32 hour,
        const s32 minute,
        const s32 second,
        const s32 millisecond
    )
        : DateTime(year, month, day, hour, minute, second)
    {
        if (static_cast<u32>(millisecond) >= TimeSpan::MillisecondsPerSecond)
            THROW(ArgumentOutOfRangeException{"Invalid millisecond value.", "millisecond"});
        m_DateData += static_cast<u64>(millisecond) * static_cast<u64>(TimeSpan::TicksPerMillisecond);
    }

    constexpr DateTime::DateTime(
        const s32 year,
        const s32 month,
        const s32 day,
        const s32 hour,
        const s32 minute,
        const s32 second,
        const s32 millisecond,
        const s32 microsecond
    )
        : DateTime(year, month, day, hour, minute, second, millisecond)
    {
        if (static_cast<u32>(microsecond) >= TimeSpan::MicrosecondsPerMillisecond)
            THROW(ArgumentOutOfRangeException{"Invalid microsecond value.", "microsecond"});
        m_DateData += static_cast<u64>(microsecond) * static_cast<u64>(TimeSpan::TicksPerMicrosecond);
    }

    constexpr DateTime DateTime::GetDate() const
    {
        return DateTime{GetUTicks() / TimeSpan::TicksPerDay * TimeSpan::TicksPerDay | GetInternalKind()};
    }

    constexpr TimeSpan DateTime::GetTimeOfDay() const
    {
        return TimeSpan{static_cast<s64>(GetUTicks() % TimeSpan::TicksPerDay)};
    }

    constexpr DayOfWeek DateTime::GetDayOfWeek() const
    {
        return static_cast<DayOfWeek>(static_cast<u32>(GetUTicks() / TimeSpan::TicksPerDay) % 7);
    }

    constexpr s32 DateTime::GetDayOfYear() const
    {
        return 1 + static_cast<s32>(((static_cast<u32>(GetUTicks() / TicksPer6Hours) | 3U)
                                         % static_cast<u32>(DaysPer400Years) | 3U) * EafMultiplier / EafDivider);
    }

    constexpr s32 DateTime::GetYear() const
    {
        // y100 = number of whole 100-year periods since 1/1/0001
        // r1 = (day number within 100-year period) * 4

        const u32 left = static_cast<u32>((m_DateData & TicksMask) / TicksPer6Hours) | 3U;
        constexpr u32 right = DaysPer400Years;

        const u32 quotient = left / right;
        const u32 y100 = quotient;
        const u32 r1 = left - (quotient * right);

        return 1 + static_cast<s32>(100 * y100 + (r1 | 3) / DaysPer4Years);
    }

    constexpr s32 DateTime::GetMonth() const
    {
        // r1 = (day number within 100-year period) * 4
        const u32 r1 = ((static_cast<u32>(GetUTicks() / TicksPer6Hours) | 3U) + 1224) % DaysPer400Years;
        const u64 u2 = static_cast<u64>(EafMultiplier) * r1 | 3U;
        const u16 daySinceMarch1 = static_cast<u16>(static_cast<u32>(u2) / EafDivider);
        const int n3 = 2141 * daySinceMarch1 + 197913;
        return static_cast<u16>(n3 >> 16) - (daySinceMarch1 >= March1BasedDayOfNewYear ? 12 : 0);
    }

    constexpr s32 DateTime::GetDay() const
    {
        // r1 = (day number within 100-year period) * 4
        const u32 r1 = ((static_cast<u32>(GetUTicks() / TicksPer6Hours) | 3U) + 1224) % DaysPer400Years;
        const u64 u2 = static_cast<u64>(EafMultiplier) * (r1 | 3U);
        const u16 daySinceMarch1 = static_cast<u16>(static_cast<u32>(u2) / EafDivider);
        const int n3 = 2141 * daySinceMarch1 + 197913;
        // Return 1-based day-of-month
        return static_cast<u16>(n3) / 2141 + 1;
    }

    constexpr s32 DateTime::GetHour() const
    {
        return static_cast<s32>(static_cast<u32>(GetUTicks() / TimeSpan::TicksPerHour) % 24);
    }

    constexpr s32 DateTime::GetMinute() const
    {
        return static_cast<s32>(GetUTicks() / TimeSpan::TicksPerMinute % 60);
    }

    constexpr s32 DateTime::GetSecond() const
    {
        return static_cast<s32>(GetUTicks() / TimeSpan::TicksPerSecond % 60);
    }

    constexpr s32 DateTime::GetMillisecond() const
    {
        return static_cast<s32>(GetUTicks() / TimeSpan::TicksPerMillisecond % 1000);
    }

    constexpr s32 DateTime::GetMicrosecond() const
    {
        return static_cast<s32>(GetUTicks() / TimeSpan::TicksPerMicrosecond % 1000);
    }

    constexpr s32 DateTime::GetNanosecond() const
    {
        return static_cast<s32>(GetUTicks() % TimeSpan::TicksPerMicrosecond) * 100;
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

    constexpr usize DateTime::GetHashCode() const
    {
        const s64 ticks = GetTicks();
        return static_cast<s32>(ticks) ^ static_cast<s32>(ticks >> 32);
    }

    constexpr s64 DateTime::GetTicks() const
    {
        return static_cast<s64>(m_DateData & TicksMask);
    }

    constexpr DateTimeKind DateTime::GetKind() const
    {
        const u32 kind = static_cast<u32>(m_DateData >> KindShift);
        // values 0-2 map directly to DateTimeKind, 3 (LocalAmbiguousDst) needs to be mapped to 2 (Local) using bit0 NAND bit1
        return static_cast<DateTimeKind>(kind & ~(kind >> 1));
    }

    constexpr u64 DateTime::GetUTicks() const { return m_DateData & TicksMask; }

    constexpr u64 DateTime::GetInternalKind() const { return m_DateData & FlagsMask; }

    constexpr u64 DateTime::DateToTicks(const s32 year, const s32 month, const s32 day)
    {
        if (year < 1 || year > 9999 || month < 1 || month > 12 || day < 1)
            THROW(ArgumentOutOfRangeException{"At least one of year, month, day has an invalid value."});

        Array days = IsLeapYear(year) ? DaysToMonth366 : DaysToMonth365;
        if (static_cast<u32>(day) > days[month] - days[month - 1])
            THROW(ArgumentOutOfRangeException{"At least one of year, month, day has an invalid value."});

        const u32 n = DaysToYear(static_cast<u32>(year)) + days[month - 1] + static_cast<u32>(day) - 1;
        return n * static_cast<u64>(TimeSpan::TicksPerDay);
    }

    constexpr u32 DateTime::DaysToYear(const u32 year)
    {
        const u32 y = year - 1;
        const u32 cent = y / 100;
        return y * (365 * 4 + 1) / 4 - cent + cent / 4;
    }

    constexpr bool DateTime::IsLeapYear(const s32 year)
    {
        if (year < 1 || year > 9999)
            THROW(ArgumentOutOfRangeException{"Invalid year value.", "year"});
        if ((year & 3) != 0) return false;
        if ((year & 15) == 0) return true;
        return static_cast<u32>(year) % 25 != 0;
    }

    constexpr u64 DateTime::TimeToTicks(const s32 hour, const s32 minute, const s32 second)
    {
        if (static_cast<u32>(hour) >= 24 || static_cast<u32>(minute) >= 60 || static_cast<u32>(second) >= 60)
            THROW(ArgumentOutOfRangeException{"At least one of hour, minute, second has an invalid value."});

        const s32 totalSeconds = hour * 3600 + minute * 60 + second;
        return static_cast<u32>(totalSeconds) * static_cast<u64>(TimeSpan::TicksPerSecond);
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
