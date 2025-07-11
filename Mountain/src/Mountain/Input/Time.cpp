#include "Mountain/Core.hpp"

#include "Mountain/Input/Time.hpp"

#include "Mountain/Screen.hpp"
#include "Mountain/Window.hpp"
#include "Mountain/Utils/Windows.hpp"

using namespace Mountain;

float_t Time::GetTargetDeltaTime()
{
    if (targetFps.has_value())
        return 1.f / static_cast<float_t>(targetFps.value());
    return Window::GetVSync() ? 1.f / Screen::GetRefreshRate() : 0.f;
}

bool_t Time::OnInterval(const float_t interval) { return Calc::OnInterval(m_TotalTime, m_LastTotalTime, interval); }

bool_t Time::OnIntervalUnscaled(const float_t interval) { return Calc::OnInterval(m_TotalTimeUnscaled, m_LastTotalTimeUnscaled, interval); }

namespace
{
    HANDLE waitableTimer = nullptr;
    double_t accumulatedSleepError = 0.0;
    double_t timeSlept = 0.0;

    bool_t WaitWaitableTimer(const TimeSpan timeSpan)
    {
        if (!waitableTimer)
            return false;

        const uint64_t ul = static_cast<uint64_t>(-timeSpan.GetTicks());
        const FILETIME waitDuration{
            .dwLowDateTime = static_cast<DWORD>(ul & 0xFFFFFFFF),
            .dwHighDateTime = static_cast<DWORD>(ul >> 32)
        };

        if (SetWaitableTimerEx(waitableTimer, reinterpret_cast<const LARGE_INTEGER*>(&waitDuration), 0, nullptr, nullptr, nullptr, 0))
        {
            WaitForSingleObject(waitableTimer, INFINITE);
            Windows::CheckError();
            return true;
        }

        Windows::SilenceError();

        return false;
    }
}

void Time::Initialize()
{
    m_Stopwatch.Start();

    // Attempt to create a high-resolution timer, only available since Windows 10, version 1803
    waitableTimer = CreateWaitableTimerEx(nullptr, nullptr, CREATE_WAITABLE_TIMER_MANUAL_RESET | CREATE_WAITABLE_TIMER_HIGH_RESOLUTION, TIMER_ALL_ACCESS);

    // Fall back to a more supported version if not available.
    // This is still far more accurate than std::this_thread::sleep_for.
    if (!waitableTimer)
        waitableTimer = CreateWaitableTimerEx(nullptr, nullptr, CREATE_WAITABLE_TIMER_MANUAL_RESET, TIMER_ALL_ACCESS);

    Windows::SilenceError();
}

void Time::Shutdown()
{
    if (waitableTimer)
    {
        CloseHandle(waitableTimer);
        Windows::CheckError();
    }
}

void Time::Update()
{
    m_LastTotalTimeUnscaled = m_TotalTimeUnscaled;
    m_LastTotalTime = m_TotalTime;

    m_TotalTimeUnscaled = static_cast<float_t>(m_Stopwatch.GetElapsedMilliseconds() / 1000.0);

    m_DeltaTimeUnscaled = std::min(m_TotalTimeUnscaled - m_LastTotalTimeUnscaled, maxDeltaTime);
    m_DeltaTime = m_DeltaTimeUnscaled * timeScale;

    freezeTimer -= m_DeltaTimeUnscaled;

    m_TotalTime += m_DeltaTime;

    m_TotalFrameCount++;
}

void Time::WaitForNextFrame()
{
    // Most of the code for waiting between frames comes from the osu!framework:
    // https://github.com/ppy/osu-framework/blob/master/osu.Framework/Timing/ThrottledFrameClock.cs

    static double_t frameStartMs = 0.0;

    const double_t lastFrameDurationMs = m_Stopwatch.GetElapsedMilliseconds() - frameStartMs;
    m_LastFrameDuration = static_cast<float_t>(lastFrameDurationMs / 1000.0);

    // FIXME - When sleeping between frames to reach to target FPS, it seems we sleep for slightly too long
    if (targetFps.has_value())
    {
        const double_t targetFrameDuration = 1000.0 / targetFps.value();
        const double_t excessFrameTime = targetFrameDuration - lastFrameDurationMs;
        const double_t timeToSleep = std::max(0.0, excessFrameTime + accumulatedSleepError);

        timeSlept = SleepFor(timeToSleep);

        accumulatedSleepError += excessFrameTime - timeSlept;

        // Never allow the sleep error to become too negative and induce too many catch-up frames
        accumulatedSleepError = std::max(-1000.0 / 30.0, accumulatedSleepError);
    }
    else
    {
        // Even when running at unlimited frame-rate, we should call the scheduler
        // to give lower-priority background processes a chance to do work.
        timeSlept = SleepFor(0.0);
    }

    Window::SwapBuffers();

    frameStartMs = m_Stopwatch.GetElapsedMilliseconds();
}

double_t Time::SleepFor(const double_t milliseconds)
{
    if (milliseconds <= 0.0)
        return 0.0;

    const double_t before = m_Stopwatch.GetElapsedMilliseconds();

    const TimeSpan timeSpan = TimeSpan::FromMilliseconds(milliseconds);

    if (!WaitWaitableTimer(timeSpan))
        std::this_thread::sleep_for(std::chrono::nanoseconds{static_cast<int64_t>(timeSpan.GetTotalNanoseconds())});

    return m_Stopwatch.GetElapsedMilliseconds() - before;
}
