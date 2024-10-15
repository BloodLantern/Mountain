#include "Mountain/input/time.hpp"

#include <GLFW/glfw3.h>

#include "Mountain/window.hpp"
#include "Mountain/utils/windows.hpp"

// ReSharper disable CppInconsistentNaming
using NtQueryTimerResolutionFunc = DWORD (NTAPI *)(OUT PULONG MinimumResolution, OUT PULONG MaximumResolution, OUT PULONG ActualResolution);
// ReSharper restore CppInconsistentNaming
/// Hidden Windows API function from ntdll.dll
NtQueryTimerResolutionFunc NtQueryTimerResolution = reinterpret_cast<NtQueryTimerResolutionFunc>(GetProcAddress(  // NOLINT(clang-diagnostic-cast-function-type-strict)
    GetModuleHandle(L"ntdll.dll"),
    "NtQueryTimerResolution"
));

using namespace Mountain;

float_t Time::GetTotalTime() { return m_TotalTime; }

float_t Time::GetLastTotalTime() { return m_LastTotalTime; }

float_t Time::GetTotalTimeUnscaled() { return m_TotalTimeUnscaled; }

float_t Time::GetLastTotalTimeUnscaled() { return m_LastTotalTimeUnscaled; }

float_t Time::GetDeltaTime() { return m_DeltaTime; }

float_t Time::GetDeltaTimeUnscaled() { return m_DeltaTimeUnscaled; }

uint64_t Time::GetTotalFrameCount() { return m_TotalFrameCount; }

std::optional<uint16_t> Time::GetTargetFps() { return m_TargetFps; }

void Time::SetTargetFps(const std::optional<uint16_t> newTargetFps)
{
    m_TargetFps = newTargetFps;

    glfwSwapInterval(!newTargetFps.has_value());
}

float_t Time::GetLastFrameDuration() { return m_LastFrameDuration; }

void Time::Initialize()
{
    // Initialize the total time to avoid a huge delta time on the first frame
    m_TotalTimeUnscaled = static_cast<decltype(m_TotalTimeUnscaled)>(glfwGetTime());
    
    ULONG min, max, current;
    (void) NtQueryTimerResolution(&min, &max, &current);
    m_LowestSleepThreshold = 1.0 + max / 10000.0;
}

void Time::Update()
{
    m_LastTotalTimeUnscaled = m_TotalTimeUnscaled;
    m_LastTotalTime = m_TotalTime;

    m_TotalTimeUnscaled = static_cast<decltype(m_TotalTimeUnscaled)>(glfwGetTime());

    m_DeltaTimeUnscaled = std::min(m_TotalTimeUnscaled - m_LastTotalTimeUnscaled, maxDeltaTime);
    m_DeltaTime = m_DeltaTimeUnscaled * timeScale;

    freezeTimer -= m_DeltaTimeUnscaled;

    m_TotalTime += m_DeltaTime;

    m_TotalFrameCount++;
}

void Time::SleepForNoMoreThan(const double_t milliseconds)
{
    // Assumption is that std::this_thread::sleep_for(t) will sleep for at least (t), and at most (t + timerResolution)

    if (milliseconds < m_LowestSleepThreshold)
        return;

    const uint32_t sleepTime = static_cast<uint32_t>(milliseconds - GetCurrentTimerResolution());
    if (sleepTime > 1.0)
        std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));
}

void Time::WaitForNextFrame()
{
    using namespace std::chrono;
    static time_point<steady_clock> frameStart;

    m_LastFrameDuration = duration_cast<duration<float_t>>(steady_clock::now() - frameStart).count();

    // FIXME - Wait is not accurate (around 10% error margin)
    if (m_TargetFps.has_value())
    {
        const double_t wait = 1.0 / (static_cast<double_t>(m_TargetFps.value()) - m_LastFrameDuration);
        
        duration<double_t> accumulatedElapsedTime{ 0.0 };
        time_point<steady_clock> previousTime = steady_clock::now();
        const duration<double_t> targetElapsedTime{ wait };
        while (accumulatedElapsedTime < targetElapsedTime)
        {
            time_point<steady_clock> now = steady_clock::now();
            accumulatedElapsedTime += now - previousTime;
            previousTime = now;
            
            const double_t sleepTime = (targetElapsedTime - accumulatedElapsedTime).count();
            SleepForNoMoreThan(sleepTime);
        }
    }
    
    Window::SwapBuffers();

    frameStart = steady_clock::now();
}

double_t Time::GetCurrentTimerResolution()
{
    ULONG min, max, current;
    (void) NtQueryTimerResolution(&min, &max, &current);
    return current / 10000.0;
}
