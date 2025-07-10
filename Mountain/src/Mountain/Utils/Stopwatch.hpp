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
        static int64_t GetFrequency();
        ATTRIBUTE_NODISCARD
        static int64_t GetTimestamp();
        ATTRIBUTE_NODISCARD
        static TimeSpan GetElapsedTime(int64_t startingTimestamp);
        ATTRIBUTE_NODISCARD
        static TimeSpan GetElapsedTime(int64_t startingTimestamp, int64_t endingTimestamp);

        void Start();
        void Stop();
        void Reset();
        void Restart();

        GETTER(bool_t, IsRunning, m_IsRunning)

        ATTRIBUTE_NODISCARD
        TimeSpan GetElapsed() const;
        ATTRIBUTE_NODISCARD
        int64_t GetElapsedTicks() const;
        ATTRIBUTE_NODISCARD
        double_t GetElapsedMilliseconds() const;
        ATTRIBUTE_NODISCARD
        double_t GetElapsedSeconds() const;

        ATTRIBUTE_NODISCARD
        std::string ToString() const;

    private:
        static constexpr int64_t TicksPerMillisecond = 10000;
        static constexpr int64_t TicksPerSecond = TicksPerMillisecond * 1000;

        static const double_t TickFrequency;

        int64_t m_StartTimestamp = 0;
        int64_t m_Elapsed = 0;
        bool_t m_IsRunning = false;

        ATTRIBUTE_NODISCARD
        int64_t GetRawElapsedTicks() const;
        ATTRIBUTE_NODISCARD
        int64_t GetElapsedDateTimeTicks() const;
    };

    CHECK_REQUIREMENT(Requirements::StringConvertible, Stopwatch);
}
