#include "Mountain/PrecompiledHeader.hpp"

#include "Mountain/Utils/Stopwatch.hpp"

#include <algorithm>

#include "Mountain/Utils/Windows.hpp"

using namespace Mountain;

namespace
{
    int64_t InitializeFrequency()
    {
        int64_t result;
        QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&result));
        return result;
    }

    // "Frequency" stores the frequency of the high-resolution performance counter
    // if one exists.
    // Otherwise, it will store TicksPerSecond.
    // The frequency cannot change while the system is running,
    // so we only need to initialize it once.
    int64_t frequency = InitializeFrequency();
}

const double_t Stopwatch::TickFrequency = static_cast<double_t>(TicksPerSecond) / static_cast<double_t>(frequency);

Stopwatch Stopwatch::StartNew()
{
    Stopwatch s;
    s.Start();
    return s;
}

int64_t Stopwatch::GetFrequency() { return frequency; }

int64_t Stopwatch::GetTimestamp()
{
    int64_t timestamp;
    QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&timestamp));
    return timestamp;
}

TimeSpan Stopwatch::GetElapsedTime(const int64_t startingTimestamp)
{
    return GetElapsedTime(startingTimestamp, GetTimestamp());
}

TimeSpan Stopwatch::GetElapsedTime(const int64_t startingTimestamp, const int64_t endingTimestamp)
{
    return TimeSpan{static_cast<int64_t>(static_cast<double_t>(endingTimestamp - startingTimestamp) * TickFrequency)};
}

void Stopwatch::Start()
{
    if (m_IsRunning)
        return;

    m_StartTimestamp = GetTimestamp();
    m_IsRunning = true;
}

void Stopwatch::Stop()
{
    if (!m_IsRunning)
        return;

    const int64_t endTimestamp = GetTimestamp();
    const int64_t elapsedPeriod = endTimestamp - m_StartTimestamp;
    m_Elapsed += elapsedPeriod;
    m_IsRunning = false;

    // When measuring small time periods, the Stopwatch.Elapsed*
    // functions can return negative values.
    // This is due to bugs in the basic input/output system (BIOS)
    // or the hardware abstraction layer (HAL) on machines with
    // variable-speed CPUs (e.g., Intel SpeedStep).
    m_Elapsed = std::max<int64_t>(m_Elapsed, 0);
}

void Stopwatch::Reset()
{
    m_StartTimestamp = 0;
    m_Elapsed = 0;
    m_IsRunning = false;
}

void Stopwatch::Restart()
{
    m_Elapsed = 0;
    m_StartTimestamp = GetTimestamp();
    m_IsRunning = true;
}

TimeSpan Stopwatch::GetElapsed() const
{
    return TimeSpan{GetElapsedDateTimeTicks()};
}

int64_t Stopwatch::GetElapsedTicks() const
{
    return GetRawElapsedTicks();
}

double_t Stopwatch::GetElapsedMilliseconds() const
{
    return static_cast<double_t>(GetElapsedDateTimeTicks()) / TicksPerMillisecond;
}

double_t Stopwatch::GetElapsedSeconds() const
{
    return static_cast<double_t>(GetElapsedDateTimeTicks()) / TicksPerSecond;
}

std::string Stopwatch::ToString() const { return GetElapsed().ToString(); }

int64_t Stopwatch::GetRawElapsedTicks() const
{
    int64_t timeElapsed = m_Elapsed;

    if (m_IsRunning)
    {
        const int64_t currentTimestamp = GetTimestamp();
        const int64_t elapsedUntilNow = currentTimestamp - m_StartTimestamp;
        timeElapsed += elapsedUntilNow;
    }

    return timeElapsed;
}

int64_t Stopwatch::GetElapsedDateTimeTicks() const
{
    return static_cast<int64_t>(static_cast<double_t>(GetRawElapsedTicks()) * TickFrequency);
}
