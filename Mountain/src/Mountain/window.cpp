#include "Mountain/window.hpp"

#include <GLFW/glfw3.h>

#include "Mountain/screen.hpp"
#include "Mountain/input/input.hpp"
#include "Mountain/input/time.hpp"
#include "Mountain/utils/logger.hpp"

using namespace Mountain;

void Window::SetPosition(const Vector2i newPosition)
{
    glfwSetWindowPos(m_Window, newPosition.x, newPosition.y);
    m_Position = newPosition;
}

void Window::SetSize(const Vector2i newSize)
{
    glfwSetWindowSize(m_Window, newSize.x, newSize.y);
    m_Size = newSize;
}

bool_t Window::GetShouldClose() { return glfwWindowShouldClose(m_Window); }

void Window::SetShouldClose(const bool_t newShouldClose) { glfwSetWindowShouldClose(m_Window, newShouldClose); }

void Window::MakeContextCurrent() { glfwMakeContextCurrent(m_Window); }

void Window::SetVisible(const bool_t newVisible)
{
    if (newVisible)
        glfwShowWindow(m_Window);
    else
        glfwHideWindow(m_Window);
    
    m_Visible = newVisible;
}

void Window::SetIcon(const Pointer<Texture>& newIcon)
{
    if (!newIcon)
    {
        glfwSetWindowIcon(m_Window, 1, nullptr);
        return;
    }
    
    const Vector2i size = newIcon->GetSize();

    const GLFWimage image
    {
        .width = size.x,
        .height = size.y,
        .pixels = Pointer(newIcon)->GetData<uint8_t>()
    };
    
    glfwSetWindowIcon(m_Window, 1, &image);
}

void Window::SetCursorHidden(const bool_t newCursorHidden) { glfwSetInputMode(m_Window, GLFW_CURSOR, newCursorHidden ? GLFW_CURSOR_HIDDEN : GLFW_CURSOR_NORMAL); }

void Window::SetCursorPosition(const Vector2 newPosition) { glfwSetCursorPos(m_Window, newPosition.x, newPosition.y); }

void Window::SetVSync(const bool_t newVsync)
{
    glfwSwapInterval(newVsync);
    m_VSync = newVsync;
}

void Window::SetWindowMode(const WindowMode newWindowMode)
{
    if (newWindowMode == m_WindowMode)
        return;

    static Vector2i lastWindowedPosition = m_Position, lastWindowedSize = m_Size;

    switch (m_WindowMode)
    {
        case WindowMode::Windowed:
            lastWindowedPosition = m_Position;
            lastWindowedSize = m_Size;
            break;
            
        case WindowMode::Borderless:
            glfwSetWindowAttrib(m_Window, GLFW_DECORATED, true);
            break;

        default: ;
    }

    GLFWmonitor* monitor = nullptr;
    Vector2i position;
    Vector2i size;

    switch (newWindowMode)
    {
        case WindowMode::Windowed:
            position = lastWindowedPosition;
            size = lastWindowedSize;
            break;

        case WindowMode::Borderless:
            // For a borderless fullscreen, we need to disable the window decoration.
            // This is the only difference between windowed and borderless mode.
            size = Screen::GetSize() + Vector2i::UnitX();
            glfwSetWindowAttrib(m_Window, GLFW_DECORATED, false);
            break;

        case WindowMode::Fullscreen:
            monitor = Screen::m_Monitors[m_CurrentScreen];
            size = Screen::GetSize();
            break;
    }

    glfwSetWindowMonitor(m_Window, monitor, position.x, position.y, size.x, size.y, GLFW_DONT_CARE);

    m_WindowMode = newWindowMode;
}

std::string_view Window::GetTitle() { return glfwGetWindowTitle(m_Window); }

void Window::SetTitle(const std::string& newTitle) { glfwSetWindowTitle(m_Window, newTitle.c_str()); }

void Window::Initialize(const std::string& windowTitle, const Vector2i windowSize, const OpenGlVersion& glVersion)
{
    glfwSetErrorCallback(
        [](int error, const char* description)
        {
            Logger::LogError("GLFW error {}: {}", error, description);
        }
    );
    
    glfwInit();

    Screen::Initialize();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, glVersion.major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, glVersion.minor);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

#ifdef _DEBUG
    glfwWindowHint(GLFW_CONTEXT_DEBUG, GLFW_TRUE);
#endif
    
    const Vector2i screenSize = Screen::GetSize();
    glfwWindowHint(GLFW_POSITION_X, screenSize.x / 2 - windowSize.x / 2);
    glfwWindowHint(GLFW_POSITION_Y, screenSize.y / 2 - windowSize.y / 2);

    glfwInitHint(GLFW_JOYSTICK_HAT_BUTTONS, false);

    m_Window = glfwCreateWindow(windowSize.x, windowSize.y, windowTitle.c_str(), nullptr, nullptr);

    MakeContextCurrent();

    glfwSetWindowIconifyCallback(m_Window, WindowMinimizeCallback);

    UpdateFields();

    Time::targetFps = Screen::GetRefreshRate();

    Input::Initialize();
}

void Window::Shutdown()
{
    glfwDestroyWindow(m_Window);

    Screen::Shutdown();
    
    glfwTerminate();
}

void Window::UpdateFields()
{
    // Position
    
    const Vector2i oldPosition = m_Position;
    
    glfwGetWindowPos(m_Window, &m_Position.x, &m_Position.y);
    
    if (oldPosition != m_Position)
        onPositionChanged(m_Position);

    // Size
    
    const Vector2i oldSize = m_Size;
    
    if (m_WindowMode != WindowMode::Windowed)
        m_Size = Screen::GetSize();
    else
        glfwGetWindowSize(m_Window, &m_Size.x, &m_Size.y);
    
    if (oldSize != m_Size)
        onSizeChanged(m_Size);

    UpdateCurrentScreen();
}

void Window::UpdateCurrentScreen()
{
    const Vector2i windowPosition = GetPosition();
    const Vector2i windowSize = GetSize();

    int32_t bestOverlap = 0;

    for (int32_t i = 0; i < Screen::GetScreenCount(); i++)
    {
        Vector2i screenPosition = Screen::GetPosition(i);
        const Vector2i screenSize = Screen::GetSize(i);

        const int32_t overlap = std::max(0, std::min(windowPosition.x + windowSize.x, screenPosition.x + screenSize.x) - std::max(windowPosition.x, screenPosition.x))
                              * std::max(0, std::min(windowPosition.y + windowSize.y, screenPosition.y + screenSize.y) - std::max(windowPosition.y, screenPosition.y));

        if (bestOverlap < overlap)
        {
            bestOverlap = overlap;
            m_CurrentScreen = i;
        }
    }
}

void Window::PollEvents() { glfwPollEvents(); }

void Window::SwapBuffers() { glfwSwapBuffers(m_Window); }

// ReSharper disable once CppParameterMayBeConstPtrOrRef
void Window::WindowMinimizeCallback(GLFWwindow* const window, const int32_t minimized)
{
    if (window != m_Window)
        return;

    m_Minimized = minimized;
}
