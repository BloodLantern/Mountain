#include "Mountain/Core.hpp"

#include "Mountain/Window.hpp"

#include <SDL3/SDL.h>

#include <ImGui/imgui_impl_sdl3.h>

#include "Mountain/Screen.hpp"
#include "Mountain/Input/Input.hpp"
#include "Mountain/Input/Time.hpp"
#include "Mountain/Utils/Logger.hpp"

using namespace Mountain;

void Window::SetPosition(const Vector2i newPosition)
{
    SDL_SetWindowPosition(m_Window, newPosition.x, newPosition.y);
    m_Position = newPosition;
}

void Window::SetSize(const Vector2i newSize)
{
    SDL_SetWindowSize(m_Window, newSize.x, newSize.y);
    m_Size = newSize;
}

Vector2i Window::GetFramebufferSize()
{
    // TODO Verify, or fix?
    return m_Size;
}

void Window::MakeContextCurrent() { SDL_GL_MakeCurrent(m_Window, m_Context); }

void Window::SetVisible(const bool_t newVisible)
{
    if (newVisible)
        SDL_ShowWindow(m_Window);
    else
        SDL_HideWindow(m_Window);

    m_Visible = newVisible;
}

void Window::SetIcon(const Pointer<Texture>& newIcon)
{
    if (!newIcon)
    {
        SDL_SetWindowIcon(m_Window, nullptr);
        return;
    }

    const Vector2i size = newIcon->GetSize();

    SDL_Surface image =
    {
        .flags = SDL_SURFACE_PREALLOCATED,
        .w = size.x,
        .h = size.y,
        .pixels = Pointer(newIcon)->GetData<uint8_t>()
    };

    SDL_SetWindowIcon(m_Window, &image);
}

void Window::SetCursorHidden(const bool_t newCursorHidden) { newCursorHidden ? SDL_HideCursor() : SDL_ShowCursor(); }

void Window::SetCursorPosition(const Vector2 newPosition) { SDL_WarpMouseInWindow(m_Window, newPosition.x, newPosition.y); }

void Window::SetVSync(const bool_t newVsync)
{
    SDL_GL_SetSwapInterval(newVsync);
    m_VSync = newVsync;
}

void Window::SetWindowMode(const WindowMode newWindowMode)
{
    if (newWindowMode == m_WindowMode)
        return;

    static Vector2i lastWindowedPosition = m_Position;
    static Vector2i lastWindowedSize = m_Size;

    if (m_WindowMode == WindowMode::Windowed)
    {
        lastWindowedPosition = m_Position;
        lastWindowedSize = m_Size;
    }

    switch (newWindowMode)
    {
        case WindowMode::Windowed:
            SetPosition(lastWindowedPosition);
            SetSize(lastWindowedSize);
            SDL_SetWindowBordered(m_Window, true);
            break;

        case WindowMode::Borderless:
            // For a borderless fullscreen, we need to disable the window decoration.
            // This is the only difference between windowed and borderless mode.
            SDL_SetWindowBordered(m_Window, false);
            SetPosition(Screen::GetPosition());
            SetSize(Screen::GetSize());
            break;

        case WindowMode::Fullscreen:
            SetPosition(Screen::GetPosition());
            SetSize(Screen::GetSize());
            SDL_SetWindowFullscreenMode(m_Window, Screen::m_VideoModes[m_CurrentScreen]);
            break;
    }

    m_WindowMode = newWindowMode;
}

std::string_view Window::GetTitle() { return SDL_GetWindowTitle(m_Window); }

void Window::SetTitle(const std::string& newTitle) { SDL_SetWindowTitle(m_Window, newTitle.c_str()); }

void Window::Initialize(const std::string& windowTitle, const Vector2i windowSize, const OpenGlVersion& glVersion)
{
    SDL_SetLogOutputFunction([](void* const, int32_t, const SDL_LogPriority priority, const char_t* const message)
    {
        if (priority == SDL_LOG_PRIORITY_ERROR)
            Logger::LogError("SDL error: {}", message);
    }, nullptr);

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_HAPTIC | SDL_INIT_GAMEPAD);

    Screen::Initialize();
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, glVersion.major);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, glVersion.minor);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

#ifdef _DEBUG
    // glfwWindowHint(GLFW_CONTEXT_DEBUG, GLFW_TRUE);
#endif

    m_Window = SDL_CreateWindow(windowTitle.c_str(), windowSize.x, windowSize.y, SDL_WINDOW_OPENGL | SDL_WINDOW_HIDDEN);

    const Vector2i screenSize = Screen::GetSize();
    SDL_SetWindowPosition(m_Window, screenSize.x / 2 - windowSize.x / 2, screenSize.y / 2 - windowSize.y / 2);

    m_Context = SDL_GL_CreateContext(m_Window);

    UpdateFields();

    Time::targetFps = Screen::GetRefreshRate();

    Input::Initialize();
}

void Window::Shutdown()
{
    SDL_DestroyWindow(m_Window);
    SDL_GL_DestroyContext(m_Context);

    Screen::Shutdown();

    SDL_Quit();
}

void Window::UpdateFields()
{
    // Position

    const Vector2i oldPosition = m_Position;

    SDL_GetWindowPosition(m_Window, &m_Position.x, &m_Position.y);

    if (oldPosition != m_Position)
        onPositionChanged(m_Position);

    // Size

    const Vector2i oldSize = m_Size;

    if (m_WindowMode != WindowMode::Windowed)
        m_Size = Screen::GetSize();
    else
        SDL_GetWindowSize(m_Window, &m_Size.x, &m_Size.y);

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

void Window::PollEvents()
{
    SDL_Event event;
    // Poll until all events are handled
    while (SDL_PollEvent(&event))
    {
        ImGui_ImplSDL3_ProcessEvent(&event);

        ProcessWindowEvents(event);
        ProcessKeyboardEvents(event);
        ProcessMouseEvents(event);
        ProcessGamepadEvents(event);
    }
}

void Window::ProcessWindowEvents(const SDL_Event& event)
{
    switch (event.type)
    {
        case SDL_EVENT_QUIT:
        case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
            shouldClose = true;
            break;

        case SDL_EVENT_WINDOW_HIDDEN:
        case SDL_EVENT_WINDOW_MINIMIZED:
            m_Minimized = true;
            break;

        case SDL_EVENT_WINDOW_SHOWN:
        case SDL_EVENT_WINDOW_RESTORED:
            m_Minimized = false;
            break;

        default: break;
    }
}

void Window::ProcessKeyboardEvents(const SDL_Event& event)
{
    SDL_Keycode key = event.key.key;
    if (key & SDLK_SCANCODE_MASK)
    {
        // Remap to 0, then map to enum values
        key = key - SDLK_CAPSLOCK + static_cast<size_t>(Key::NormalEnd);
    }

    switch (event.type)
    {
        case SDL_EVENT_KEY_UP:
        case SDL_EVENT_KEY_DOWN:
            Input::HandleKeyboard(key,
                event.key.down ? KeyAction::Press :
                event.key.repeat ? KeyAction::Repeat : KeyAction::Release);
            break;

        default: break;
    }
}

void Window::ProcessMouseEvents(const SDL_Event& event)
{
    switch (event.type)
    {
        case SDL_EVENT_MOUSE_BUTTON_UP:
        case SDL_EVENT_MOUSE_BUTTON_DOWN:
            // SDL doesn't have a binding for mouse button 0, so we offset everything by 1
            Input::HandleMouseButton(event.button.button - 1, event.button.down);
            break;

        case SDL_EVENT_MOUSE_MOTION:
            Input::HandleMouseMovement({ event.motion.x, event.motion.y });
            break;

        case SDL_EVENT_MOUSE_WHEEL:
            Input::HandleMouseWheel(event.wheel.integer_x, event.wheel.integer_y);
            break;

        default: break;
    }
}

void Window::ProcessGamepadEvents(const SDL_Event& event)
{
    switch (event.type)
    {
        case SDL_EVENT_GAMEPAD_ADDED:
            Input::ConnectGamepad(event.gdevice.which);
            break;

        case SDL_EVENT_GAMEPAD_REMOVED:
            Input::DisconnectGamepad(event.gdevice.which);
            break;

        case SDL_EVENT_GAMEPAD_AXIS_MOTION:
            Input::UpdateGamepadAxis(event.gaxis.which, static_cast<GamepadAxis>(event.gaxis.axis), event.gaxis.value);
            break;

        case SDL_EVENT_GAMEPAD_BUTTON_DOWN:
        case SDL_EVENT_GAMEPAD_BUTTON_UP:
            Input::UpdateGamepadButton(event.gbutton.which, static_cast<GamepadButton>(event.gbutton.button), event.gbutton.down);
            break;

        case SDL_EVENT_JOYSTICK_BATTERY_UPDATED:
            Input::UpdateGamepadBattery(event.gdevice.which, static_cast<int8_t>(event.jbattery.percent),
                static_cast<GamepadBatteryState>(event.jbattery.state));
            break;

        case SDL_EVENT_GAMEPAD_SENSOR_UPDATE:
            if (event.gsensor.sensor == SDL_SENSOR_ACCEL)
            {
                Input::UpdateGamepadAccel(event.gsensor.which, { event.gsensor.data[0], event.gsensor.data[1], event.gsensor.data[2] });
            }
            else if (event.gsensor.sensor == SDL_SENSOR_GYRO)
            {
                Input::UpdateGamepadGyro(event.gsensor.which, { event.gsensor.data[0], event.gsensor.data[1], event.gsensor.data[2] });
            }
            break;

        case SDL_EVENT_GAMEPAD_TOUCHPAD_DOWN:
        case SDL_EVENT_GAMEPAD_TOUCHPAD_MOTION:
        case SDL_EVENT_GAMEPAD_TOUCHPAD_UP:
            Input::UpdateGamepadTouchpad(event.gtouchpad.which, event.gtouchpad.touchpad, event.gtouchpad.finger,
                event.type == SDL_EVENT_GAMEPAD_TOUCHPAD_UP ? Vector2{ -1, -1 } : Vector2{ event.gtouchpad.x, event.gtouchpad.y });
            break;

        default: break;
    }
}

void Window::SwapBuffers() { SDL_GL_SwapWindow(m_Window); }
