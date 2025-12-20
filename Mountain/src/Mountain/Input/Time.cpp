#include "Mountain/PrecompiledHeader.hpp"

#include "Mountain/Input/Time.hpp"

#include "Mountain/Profiler.hpp"

#include "Mountain/Screen.hpp"
#include "Mountain/Window.hpp"
#include "Mountain/Utils/Windows.hpp"

using namespace Mountain;

f32 Time::GetTargetDeltaTime()
{
    if (targetFps.HasValue())
        return 1.f / static_cast<f32>(targetFps.Value());
    return Window::GetVSync() ? 1.f / Screen::GetRefreshRate() : 0.f;
}

bool Time::OnInterval(const f32 interval) { return Calc::OnInterval(m_TotalTime, m_LastTotalTime, interval); }

bool Time::OnIntervalUnscaled(const f32 interval) { return Calc::OnInterval(m_TotalTimeUnscaled, m_LastTotalTimeUnscaled, interval); }

namespace
{
    HANDLE waitableTimer = nullptr;
    f64 accumulatedSleepError = 0.0;
    f64 timeSlept = 0.0;

    bool WaitWaitableTimer(const TimeSpan timeSpan)
    {
        if (!waitableTimer)
            return false;

        const u64 ul = static_cast<u64>(-timeSpan.GetTicks());
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
    ZoneScoped;

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
    ZoneScoped;

    if (waitableTimer)
    {
        CloseHandle(waitableTimer);
        Windows::CheckError();
    }
}

void Time::Update()
{
    ZoneScoped;

    m_LastTotalTimeUnscaled = m_TotalTimeUnscaled;
    m_LastTotalTime = m_TotalTime;

    m_TotalTimeUnscaled = static_cast<f32>(m_Stopwatch.GetElapsedMilliseconds() / 1000.0);

    m_DeltaTimeUnscaled = std::min(m_TotalTimeUnscaled - m_LastTotalTimeUnscaled, maxDeltaTime);
    m_DeltaTime = m_DeltaTimeUnscaled * timeScale;

    freezeTimer -= m_DeltaTimeUnscaled;

    m_TotalTime += m_DeltaTime;

    m_TotalFrameCount++;
}

void Time::WaitForNextFrame()
{
    ZoneScoped;

    // Most of the code for waiting between frames comes from the osu!framework:
    // https://github.com/ppy/osu-framework/blob/master/osu.Framework/Timing/ThrottledFrameClock.cs

    static f64 frameStartMs = 0.0, frameStartMsAfterSwapBuffers = 0.0;

    Graphics::Finish();

    const f64 elapsedMilliseconds = m_Stopwatch.GetElapsedMilliseconds();
    const f64 lastFrameDurationMsWithoutSwapBuffers = elapsedMilliseconds - frameStartMsAfterSwapBuffers;
    m_LastFrameDuration = static_cast<f32>(lastFrameDurationMsWithoutSwapBuffers / 1000.0);

    if (targetFps.HasValue())
    {
        const f64 lastFrameDurationMs = elapsedMilliseconds - frameStartMs;

        const f64 targetFrameDuration = 1000.0 / targetFps.Value();
        const f64 excessFrameTime = targetFrameDuration - lastFrameDurationMs;
        const f64 timeToSleep = std::max(0.0, excessFrameTime + accumulatedSleepError);

        timeSlept = SleepFor(timeToSleep);

        accumulatedSleepError += excessFrameTime - timeSlept;

        // Never allow the sleep error to become too negative and induce too many catch-up frames
        accumulatedSleepError = std::max(-1000.0 / 30.0, accumulatedSleepError);
    }

    frameStartMs = m_Stopwatch.GetElapsedMilliseconds();

    // VSync sleeps here
    Window::SwapBuffers();

    frameStartMsAfterSwapBuffers = m_Stopwatch.GetElapsedMilliseconds();
}

f64 Time::SleepFor(const f64 milliseconds)
{
    if (milliseconds <= 0.0)
        return 0.0;

    const f64 before = m_Stopwatch.GetElapsedMilliseconds();

    const TimeSpan timeSpan = TimeSpan::FromMilliseconds(milliseconds);

    if (!WaitWaitableTimer(timeSpan))
        std::this_thread::sleep_for(timeSpan.ToChrono());

    return m_Stopwatch.GetElapsedMilliseconds() - before;
}
