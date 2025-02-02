#include "Mountain/window.hpp"

#include <GLFW/glfw3.h>

#include "Mountain/screen.hpp"
#include "Mountain/input/input.hpp"
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

void Window::PollEvents() { glfwPollEvents(); }

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

void Window::SetVSync(const bool_t newVsync) { glfwSwapInterval(newVsync); }

void Window::SetWindowMode(const WindowMode newWindowMode)
{
    if (newWindowMode == m_WindowMode)
        return;

    static Vector2i lastWindowedPosition = m_Position, lastWindowedSize = m_Size;

    if (m_WindowMode == WindowMode::Windowed)
    {
        lastWindowedPosition = m_Position;
        lastWindowedSize = m_Size;
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
            // For a borderless fullscreen, we set the window size to the screen size plus one on the X axis
            // This is a hack to make the borderless thing work because otherwise it would default to an exclusive fullscreen.
            // I learnt about this hack there: https://github.com/ppy/osu-framework/blob/7774e64cd84232b5e1fe08d527acfe39b67ef989/osu.Framework/Platform/Windows/SDL2WindowsWindow.cs#L270
            size = Screen::GetSize(static_cast<int32_t>(m_CurrentScreen)) + Vector2i::UnitX();
            break;

        case WindowMode::Fullscreen:
            monitor = Screen::m_Monitors[m_CurrentScreen];
            size = Screen::GetSize(static_cast<int32_t>(m_CurrentScreen));
            break;
    }

    glfwSetWindowMonitor(m_Window, monitor, position.x, position.y, size.x, size.y, GLFW_DONT_CARE);

    m_WindowMode = newWindowMode;
}

uint32_t Window::GetCurrentScreen() { return m_CurrentScreen; }

std::string_view Window::GetTitle() { return glfwGetWindowTitle(m_Window); }

void Window::SetTitle(const std::string& newTitle) { glfwSetWindowTitle(m_Window, newTitle.c_str()); }

bool_t Window::GetMinimized()
{
    return m_Minimized;
}

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

    // Set vsync
    glfwSwapInterval(1);

    glfwSetWindowIconifyCallback(m_Window, WindowMinimizeCallback);

    UpdateFields();

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

    // Current screen
    
    UpdateCurrentScreen();
}

void Window::UpdateCurrentScreen()
{
    const Vector2i windowPosition = GetPosition();
    const Vector2i windowSize = GetSize();

    int32_t bestOverlap = 0;

    for (uint32_t i = 0; i < Screen::GetScreenCount(); i++)
    {
        const int32_t screenIndex = static_cast<int32_t>(i);
        
        Vector2i screenPosition = Screen::GetPosition(screenIndex);
        const Vector2i screenSize = Screen::GetSize(screenIndex);

        const int32_t overlap = std::max(0, std::min(windowPosition.x + windowSize.x, screenPosition.x + screenSize.x) - std::max(windowPosition.x, screenPosition.x))
                              * std::max(0, std::min(windowPosition.y + windowSize.y, screenPosition.y + screenSize.y) - std::max(windowPosition.y, screenPosition.y));

        if (bestOverlap < overlap)
        {
            bestOverlap = overlap;
            m_CurrentScreen = i;
        }
    }
}

void Window::SwapBuffers() { glfwSwapBuffers(m_Window); }

// ReSharper disable once CppParameterMayBeConstPtrOrRef
void Window::WindowMinimizeCallback(GLFWwindow* const window, const int minimized)
{
    if (window != m_Window)
        return;

    m_Minimized = minimized;
}
