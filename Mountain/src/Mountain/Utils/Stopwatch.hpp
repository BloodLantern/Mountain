#pragma once

#include <format>
#include <sstream>

#include "Mountain/Core.hpp"
#include "Mountain/Utils/TimeSpan.hpp"

#define START_STOPWATCH const ::Mountain::Stopwatch stopwatch = ::Mountain::Stopwatch::StartNew()

namespace Mountain
{
    /// @brief C++ reimplementation of the .NET Stopwatch class
    /// @details Provides a set of methods that can be used to accurately measure elapsed time.
    /// @see Source: https://github.com/dotnet/runtime/blob/release/8.0/src/libraries/System.Private.CoreLib/src/System/Diagnostics/Stopwatch.cs
    class MOUNTAIN_API Stopwatch
    {
    public:
        ATTRIBUTE_NODISCARD
        static Stopwatch StartNew();

        ATTRIBUTE_NODISCARD
        static s64 GetFrequency();
        ATTRIBUTE_NODISCARD
        static s64 GetTimestamp();
        ATTRIBUTE_NODISCARD
        static TimeSpan GetElapsedTime(s64 startingTimestamp);
        ATTRIBUTE_NODISCARD
        static TimeSpan GetElapsedTime(s64 startingTimestamp, s64 endingTimestamp);

        void Start();
        void Stop();
        void Reset();
        void Restart();

        GETTER(bool, IsRunning, m_IsRunning)

        ATTRIBUTE_NODISCARD
        TimeSpan GetElapsed() const;
        ATTRIBUTE_NODISCARD
        s64 GetElapsedTicks() const;
        ATTRIBUTE_NODISCARD
        f64 GetElapsedMilliseconds() const;
        ATTRIBUTE_NODISCARD
        f64 GetElapsedSeconds() const;

        ATTRIBUTE_NODISCARD
        std::string ToString() const;

    private:
        static constexpr s64 TicksPerMillisecond = 10000;
        static constexpr s64 TicksPerSecond = TicksPerMillisecond * 1000;

        static const f64 TickFrequency;

        s64 m_StartTimestamp = 0;
        s64 m_Elapsed = 0;
        bool m_IsRunning = false;

        ATTRIBUTE_NODISCARD
        s64 GetRawElapsedTicks() const;
        ATTRIBUTE_NODISCARD
        s64 GetElapsedDateTimeTicks() const;
    };

    CHECK_REQUIREMENT(Requirements::StringConvertible, Stopwatch);
}
