#include "Mountain/window.hpp"

#include <GLFW/glfw3.h>

#include "Mountain/screen.hpp"
#include "Mountain/input/input.hpp"
#include "Mountain/utils/logger.hpp"

using namespace Mountain;

Vector2i Window::GetPosition() { return m_Position; }

void Window::SetPosition(const Vector2i newPosition)
{
    glfwSetWindowPos(m_Window, newPosition.x, newPosition.y);
    m_Position = newPosition;
}

Vector2i Window::GetSize() { return m_Size; }

void Window::SetSize(const Vector2i newSize)
{
    glfwSetWindowSize(m_Window, newSize.x, newSize.y);
    m_Size = newSize;
}

bool_t Window::GetShouldClose() { return glfwWindowShouldClose(m_Window); }

void Window::SetShouldClose(const bool_t newShouldClose) { glfwSetWindowShouldClose(m_Window, newShouldClose); }

void Window::PollEvents() { glfwPollEvents(); }

void Window::MakeContextCurrent() { glfwMakeContextCurrent(m_Window); }

GLFWwindow* Window::GetHandle() { return m_Window; }

void Window::SetVisible(const bool_t newVisible)
{
    if (newVisible)
        glfwShowWindow(m_Window);
    else
        glfwHideWindow(m_Window);
    
    m_Visible = newVisible;
}

void Window::SetIcon(const Pointer<Texture>& icon)
{
    if (!icon)
    {
        glfwSetWindowIcon(m_Window, 1, nullptr);
        return;
    }
    
    const Vector2i size = icon->GetSize();

    const GLFWimage image
    {
        .width = size.x,
        .height = size.y,
        .pixels = Pointer(icon)->GetData<uint8_t>()
    };
    
    glfwSetWindowIcon(m_Window, 1, &image);
}

void Window::SetCursorHidden(const bool_t value) { glfwSetInputMode(m_Window, GLFW_CURSOR, value ? GLFW_CURSOR_HIDDEN : GLFW_CURSOR_NORMAL); }

void Window::SetCursorPosition(const Vector2 newPosition) { glfwSetCursorPos(m_Window, newPosition.x, newPosition.y); }

void Window::SetVSync(const bool_t vsync) { glfwSwapInterval(vsync); }

void Window::SwapBuffers() { glfwSwapBuffers(m_Window); }

FullscreenMode Window::GetFullscreenMode() { return m_FullscreenMode; }

void Window::SetFullscreenMode(const FullscreenMode newMode)
{
    if (newMode == m_FullscreenMode)
        return;
    
    static Vector2i lastWindowedPosition, lastWindowedSize;

    if (m_FullscreenMode == FullscreenMode::Windowed)
    {
        lastWindowedPosition = m_Position;
        lastWindowedSize = m_Size;
    }

    GLFWmonitor* monitor = nullptr;
    Vector2i position;
    Vector2i size;

    switch (newMode)
    {
        case FullscreenMode::Windowed:
            position = lastWindowedPosition;
            size = lastWindowedSize;
            break;
        
        case FullscreenMode::Fullscreen:
            monitor = Screen::m_Monitors[m_CurrentScreen];
            [[fallthrough]];
        
        case FullscreenMode::Borderless:
            // TODO - Window is behind task bar
            position = Vector2i::Zero();
            size = Screen::GetSize(static_cast<int32_t>(m_CurrentScreen));
            break;

        case FullscreenMode::Count:
            throw std::invalid_argument("Invalid fullscreen mode");
    }
    
    glfwSetWindowMonitor(m_Window, monitor, position.x, position.y, size.x, size.y, GLFW_DONT_CARE);

    m_Position = position;
    m_Size = size;
    m_FullscreenMode = newMode;
}

uint32_t Window::GetCurrentScreen() { return m_CurrentScreen; }

void Window::Initialize(const char_t* const windowTitle, const Vector2i windowSize, const bool_t vsync, const OpenGlVersion& glVersion)
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
    glfwWindowHint(GLFW_RESIZABLE, false);
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

    glfwInitHint(GLFW_JOYSTICK_HAT_BUTTONS, false);

    m_Window = glfwCreateWindow(windowSize.x, windowSize.y, windowTitle, nullptr, nullptr);

    MakeContextCurrent();

    // Set vsync
    glfwSwapInterval(vsync);

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
    glfwGetWindowPos(m_Window, &m_Position.x, &m_Position.y);
    glfwGetWindowSize(m_Window, &m_Size.x, &m_Size.y);

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
