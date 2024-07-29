#include "screen.hpp"

#include <GLFW/glfw3.h>

using namespace Mountain;

Vector2i Screen::GetPosition(const int32_t screenIndex)
{
    if (screenIndex < 0)
        return {};

    Vector2i result;
    glfwGetMonitorPos(m_Monitors[screenIndex], &result.x, &result.y);
    return result;
}

Vector2i Screen::GetSize(const int32_t screenIndex)
{
    if (screenIndex < 0)
        return {};
    
    return { m_VideoModes[screenIndex]->width, m_VideoModes[screenIndex]->height };
}

int32_t Screen::GetRefreshRate(const int32_t screenIndex)
{
    if (screenIndex < 0)
        return {};
    
    return m_VideoModes[screenIndex]->refreshRate;
}

uint32_t Screen::GetScreenCount()
{
    return m_MonitorCount;
}

void Screen::Initialize()
{
    m_Monitors = glfwGetMonitors(reinterpret_cast<int32_t*>(&m_MonitorCount));

    m_VideoModes = new const GLFWvidmode*[m_MonitorCount];
    
    for (uint32_t i = 0; i < m_MonitorCount; i++)
    {
        m_VideoModes[i] = glfwGetVideoMode(m_Monitors[i]);
    }
}

void Screen::Shutdown()
{
    delete m_VideoModes;
}
