#pragma once

#include <format>
#include <sstream>

#include "Mountain/Core.hpp"
#include "Mountain/Utils/TimeSpan.hpp"

namespace Mountain
{
    /// @brief C++ reimplementation of the .NET Stopwatch class
    /// @details Provides a set of methods that can be used to accurately measure elapsed time.
    /// @see Source: https://github.com/dotnet/runtime/blob/release/8.0/src/libraries/System.Private.CoreLib/src/System/Diagnostics/Stopwatch.cs
    class MOUNTAIN_API Stopwatch
    {
    public:
        [[nodiscard]]
        static Stopwatch StartNew();

        [[nodiscard]]
        static int64_t GetFrequency();
        [[nodiscard]]
        static int64_t GetTimestamp();
        [[nodiscard]]
        static TimeSpan GetElapsedTime(int64_t startingTimestamp);
        [[nodiscard]]
        static TimeSpan GetElapsedTime(int64_t startingTimestamp, int64_t endingTimestamp);

        void Start();
        void Stop();
        void Reset();
        void Restart();

        GETTER(bool_t, IsRunning, m_IsRunning)

        [[nodiscard]]
        TimeSpan GetElapsed() const;
        [[nodiscard]]
        int64_t GetElapsedTicks() const;
        [[nodiscard]]
        double_t GetElapsedMilliseconds() const;
        [[nodiscard]]
        double_t GetElapsedSeconds() const;

        [[nodiscard]]
        std::string ToString() const;

    private:
        static constexpr int64_t TicksPerMillisecond = 10000;
        static constexpr int64_t TicksPerSecond = TicksPerMillisecond * 1000;

        static const double_t TickFrequency;

        int64_t m_StartTimestamp = 0;
        int64_t m_Elapsed = 0;
        bool_t m_IsRunning = false;

        [[nodiscard]]
        int64_t GetRawElapsedTicks() const;
        [[nodiscard]]
        int64_t GetElapsedDateTimeTicks() const;
    };

    CHECK_REQUIREMENT(Requirements::StringConvertible, Stopwatch);
}
