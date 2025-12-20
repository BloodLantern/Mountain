#include "Mountain/PrecompiledHeader.hpp"

#include "Mountain/Utils/Stopwatch.hpp"

#include <algorithm>

#include "Mountain/Utils/Windows.hpp"

using namespace Mountain;

namespace
{
    s64 InitializeFrequency()
    {
        s64 result;
        QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&result));
        return result;
    }

    // "Frequency" stores the frequency of the high-resolution performance counter
    // if one exists.
    // Otherwise, it will store TicksPerSecond.
    // The frequency cannot change while the system is running,
    // so we only need to initialize it once.
    s64 frequency = InitializeFrequency();
}

const f64 Stopwatch::TickFrequency = static_cast<f64>(TicksPerSecond) / static_cast<f64>(frequency);

Stopwatch Stopwatch::StartNew()
{
    Stopwatch s;
    s.Start();
    return s;
}

s64 Stopwatch::GetFrequency() { return frequency; }

s64 Stopwatch::GetTimestamp()
{
    s64 timestamp;
    QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&timestamp));
    return timestamp;
}

TimeSpan Stopwatch::GetElapsedTime(const s64 startingTimestamp)
{
    return GetElapsedTime(startingTimestamp, GetTimestamp());
}

TimeSpan Stopwatch::GetElapsedTime(const s64 startingTimestamp, const s64 endingTimestamp)
{
    return TimeSpan{static_cast<s64>(static_cast<f64>(endingTimestamp - startingTimestamp) * TickFrequency)};
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

    const s64 endTimestamp = GetTimestamp();
    const s64 elapsedPeriod = endTimestamp - m_StartTimestamp;
    m_Elapsed += elapsedPeriod;
    m_IsRunning = false;

    // When measuring small time periods, the Stopwatch.Elapsed*
    // functions can return negative values.
    // This is due to bugs in the basic input/output system (BIOS)
    // or the hardware abstraction layer (HAL) on machines with
    // variable-speed CPUs (e.g., Intel SpeedStep).
    m_Elapsed = std::max<s64>(m_Elapsed, 0);
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

s64 Stopwatch::GetElapsedTicks() const
{
    return GetRawElapsedTicks();
}

f64 Stopwatch::GetElapsedMilliseconds() const
{
    return static_cast<f64>(GetElapsedDateTimeTicks()) / TicksPerMillisecond;
}

f64 Stopwatch::GetElapsedSeconds() const
{
    return static_cast<f64>(GetElapsedDateTimeTicks()) / TicksPerSecond;
}

std::string Stopwatch::ToString() const { return GetElapsed().ToString(); }

s64 Stopwatch::GetRawElapsedTicks() const
{
    s64 timeElapsed = m_Elapsed;

    if (m_IsRunning)
    {
        const s64 elapsedUntilNow = GetTimestamp() - m_StartTimestamp;
        timeElapsed += elapsedUntilNow;
    }

    return timeElapsed;
}

s64 Stopwatch::GetElapsedDateTimeTicks() const
{
    return static_cast<s64>(static_cast<f64>(GetRawElapsedTicks()) * TickFrequency);
}
