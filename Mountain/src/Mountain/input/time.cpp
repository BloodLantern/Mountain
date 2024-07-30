#include "Mountain/input/time.hpp"

#include <GLFW/glfw3.h>

using namespace Mountain;

float_t Time::GetTotalTime() { return m_TotalTime; }

float_t Time::GetLastTotalTime() { return m_LastTotalTime; }

float_t Time::GetTotalTimeUnscaled() { return m_TotalTimeUnscaled; }

float_t Time::GetLastTotalTimeUnscaled() { return m_LastTotalTimeUnscaled; }

float_t Time::GetDeltaTime() { return m_DeltaTime; }

float_t Time::GetDeltaTimeUnscaled() { return m_DeltaTimeUnscaled; }

uint64_t Time::GetTotalFrameCount() { return m_TotalFrameCount; }

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

    m_TotalTime += m_DeltaTime;

    m_TotalFrameCount++;
}
