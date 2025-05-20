module Mountain:Rendering_Screen;

import <GLFW/glfw3.h>;

import Mountain.Core;

using namespace Mountain;

Vector2i Screen::GetPosition(int32_t screenIndex)
{
    if (screenIndex < 0)
        screenIndex = Window::GetCurrentScreen();

    Vector2i result;
    glfwGetMonitorPos(m_Monitors[screenIndex], &result.x, &result.y);
    return result;
}

Vector2i Screen::GetSize(int32_t screenIndex)
{
    if (screenIndex < 0)
        screenIndex = Window::GetCurrentScreen();

    return { m_VideoModes[screenIndex]->width, m_VideoModes[screenIndex]->height };
}

int32_t Screen::GetRefreshRate(int32_t screenIndex)
{
    if (screenIndex < 0)
        screenIndex = Window::GetCurrentScreen();

    return m_VideoModes[screenIndex]->refreshRate;
}

void Screen::Initialize()
{
    m_Monitors = glfwGetMonitors(&m_MonitorCount);

    m_VideoModes = new const GLFWvidmode*[m_MonitorCount];

    for (int32_t i = 0; i < m_MonitorCount; i++)
        m_VideoModes[i] = glfwGetVideoMode(m_Monitors[i]);
}

void Screen::Shutdown()
{
    delete m_VideoModes;
}
