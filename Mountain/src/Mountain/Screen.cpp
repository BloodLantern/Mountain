#include "Mountain/Screen.hpp"

#include "Mountain/Window.hpp"

#include <SDL3/SDL.h>

using namespace Mountain;

Vector2i Screen::GetPosition(int32_t screenIndex)
{
    if (screenIndex < 0)
        screenIndex = Window::GetCurrentScreen();

    SDL_Rect rect;
    SDL_GetDisplayBounds(m_Monitors[screenIndex], &rect);

    return { rect.x, rect.y };
}

Vector2i Screen::GetSize(int32_t screenIndex)
{
    if (screenIndex < 0)
        screenIndex = Window::GetCurrentScreen();

    return { m_VideoModes[screenIndex]->w, m_VideoModes[screenIndex]->h };
}

float_t Screen::GetRefreshRate(int32_t screenIndex)
{
    if (screenIndex < 0)
        screenIndex = Window::GetCurrentScreen();

    return m_VideoModes[screenIndex]->refresh_rate;
}

void Screen::Initialize()
{
    m_Monitors = SDL_GetDisplays(&m_MonitorCount);

    m_VideoModes = new const SDL_DisplayMode*[m_MonitorCount];

    for (int32_t i = 0; i < m_MonitorCount; i++)
        m_VideoModes[i] = SDL_GetCurrentDisplayMode(m_Monitors[i]);
}

void Screen::Shutdown()
{
    delete m_VideoModes;
}
