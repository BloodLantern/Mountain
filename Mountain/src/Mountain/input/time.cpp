#include "Mountain/input/time.hpp"

#include <GLFW/glfw3.h>

#include "Mountain/screen.hpp"
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

float_t Time::GetTargetDeltaTime() { return 1.f / static_cast<float_t>(m_TargetFps.has_value() ? m_TargetFps.value() : Screen::GetRefreshRate()); }

float_t Time::GetLastFrameDuration() { return m_LastFrameDuration; }

void Time::Initialize()
{
    // Initialize the total time to avoid a huge delta time on the first frame
    m_TotalTimeUnscaled = static_cast<float_t>(glfwGetTime());
}

void Time::Update()
{
    m_LastTotalTimeUnscaled = m_TotalTimeUnscaled;
    m_LastTotalTime = m_TotalTime;

    m_TotalTimeUnscaled = static_cast<float_t>(glfwGetTime());

    m_DeltaTimeUnscaled = std::min(m_TotalTimeUnscaled - m_LastTotalTimeUnscaled, maxDeltaTime);
    m_DeltaTime = m_DeltaTimeUnscaled * timeScale;

    freezeTimer -= m_DeltaTimeUnscaled;

    m_TotalTime += m_DeltaTime;

    m_TotalFrameCount++;
}

void Time::WaitForNextFrame()
{
    using namespace std::chrono;
    static time_point<steady_clock> frameStart;

    m_LastFrameDuration = duration_cast<duration<float_t>>(steady_clock::now() - frameStart).count();

    // FIXME - Wait is not accurate (seems to be limited to 60FPS max)
    if (m_TargetFps.has_value())
    {
        const double_t wait = 1.0 / static_cast<double_t>(m_TargetFps.value()) - m_LastFrameDuration;

        if (wait > 0.0)
        {
            using namespace std::chrono_literals;

            auto before = high_resolution_clock::now();
            std::this_thread::sleep_for(duration<double_t>(wait * 0.5f));
            duration<double_t, std::milli> sleep = duration_cast<decltype(sleep)>(high_resolution_clock::now() - before);

            Renderer::DebugString(
                std::format(
                    "wait: {:3.0f}ms, sleep: {}, factor: {}",
                    wait * 1000.0,
                    sleep,
                    duration_cast<duration<double_t>>(sleep).count() / wait
                ),
                0.1f
            );
        }
    }
    
    Window::SwapBuffers();

    frameStart = steady_clock::now();
}
