#include "Mountain/input/time.hpp"

#include <GLFW/glfw3.h>

#include "Mountain/window.hpp"

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

void Time::WaitForNextFrame()
{
    static std::chrono::time_point<std::chrono::system_clock> frameStart;

    const auto duration = std::chrono::system_clock::now() - frameStart;
    m_LastFrameDuration = std::chrono::duration_cast<std::chrono::duration<float_t>>(duration).count();

    if (m_TargetFps.has_value())
    {
        // FIXME - Wait is not accurate
        const auto start = std::chrono::high_resolution_clock::now();
        const std::chrono::duration<double_t> wait{ 1.0 / static_cast<double_t>(m_TargetFps.value()) };
        while (std::chrono::high_resolution_clock::now() - start < wait) (void) 0;
    }
    
    Window::SwapBuffers();

    frameStart = std::chrono::system_clock::now();
}
