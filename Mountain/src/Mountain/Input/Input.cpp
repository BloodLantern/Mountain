#include "Mountain/Input/Input.hpp"

#include <GLFW/glfw3.h>

#include "Mountain/Utils/Logger.hpp"

using namespace Mountain;

bool_t Input::GetKey(const Key key, const KeyStatus status)
{
    return m_Keyboard.at(static_cast<size_t>(key)).at(static_cast<size_t>(status));
}

bool_t Input::GetMouseButton(const MouseButton mouseButton, const MouseButtonStatus status)
{
    return m_Mouse.at(static_cast<size_t>(mouseButton)).at(static_cast<size_t>(status));
}

const GamepadInput& Input::GetGamepad(uint32_t gamepadId)
{
    if (gamepadId > GamepadMax)
    {
        Logger::LogError("Invalid gamepad ID {}", gamepadId);
        THROW((ArgumentException{"Invalid gamepad ID", "gamepadId"}));
    }

    return m_Gamepads.at(gamepadId);
}

uint32_t Input::GetGamepadsConnected()
{
    return static_cast<uint32_t>(std::ranges::count_if(m_Gamepads, [](auto&& gamepad) -> bool_t { return gamepad.m_IsConnected; }));
}

bool_t Input::IsGamepadConnected(const uint32_t index) { return m_Gamepads[index].m_IsConnected; }

Vector2 Input::GetMousePosition() { return m_MousePosition; }

void Input::HandleKeyboard(GLFWwindow*, const int32_t key, const int32_t, const int32_t action, const int32_t)
{
    if (static_cast<size_t>(key) > m_Keyboard.size())
        return;

    KeyStatuses& keyStatuses = m_Keyboard.at(static_cast<size_t>(key));

    switch (action)
    {
        case GLFW_RELEASE:
            keyStatuses.at(static_cast<size_t>(KeyStatus::Down)) = false;
            keyStatuses.at(static_cast<size_t>(KeyStatus::Release)) = true;
            keyStatuses.at(static_cast<size_t>(KeyStatus::Repeat)) = false;
            break;

        case GLFW_PRESS:
            keyStatuses.at(static_cast<size_t>(KeyStatus::Pressed)) = true;
            keyStatuses.at(static_cast<size_t>(KeyStatus::Down)) = true;
            break;

        case GLFW_REPEAT:
            keyStatuses.at(static_cast<size_t>(KeyStatus::Repeat)) = true;
            break;

        default:
            break;
    }
}

void Input::HandleMouseButton(GLFWwindow*, const int32_t mouseButton, const int32_t action, int32_t)
{
    MouseStatuses& keyStatuses = m_Mouse.at(static_cast<size_t>(mouseButton));

    switch (action)
    {
        case GLFW_RELEASE:
            keyStatuses.at(static_cast<size_t>(MouseButtonStatus::Down)) = false;
            keyStatuses.at(static_cast<size_t>(MouseButtonStatus::Release)) = true;
            break;

        case GLFW_PRESS:
            keyStatuses.at(static_cast<size_t>(MouseButtonStatus::Pressed)) = true;
            keyStatuses.at(static_cast<size_t>(MouseButtonStatus::Down)) = true;
            break;

        default:
            break;
    }
}

void Input::HandleMouseWheel(GLFWwindow*, const double_t wheelX, const double_t wheelY)
{
    m_MouseWheel += { static_cast<float_t>(wheelX), static_cast<float_t>(wheelY) };
}

void Input::HandleJoyStickCallBack(const int32_t jid, const int32_t event)
{
    GamepadInput& gamepad = m_Gamepads[jid];
    switch (event)
    {
        case GLFW_CONNECTED:
            gamepad.m_IsConnected = true;
            break;

        case GLFW_DISCONNECTED:
            gamepad.m_IsConnected = false;
            break;

        default:
            break;
    }
}
void Input::UpdateGamepads()
{
    for (uint32_t i = 0; i < GamepadMax; i++)
    {
        GamepadInput& gamepad = m_Gamepads[i];

        if (!gamepad.m_IsConnected)
            continue;

        GLFWgamepadstate state;

        if (!glfwGetGamepadState(static_cast<int32_t>(i), &state))
            return;

        for (uint32_t k = 0; k < magic_enum::enum_count<GamepadAxis>(); k++)
        {
            float_t& axisValue = gamepad.m_Axes[k];
            axisValue = Calc::MakeZero(state.axes[k], GamepadInput::nullAnalogValue);

            const GamepadAxis axis = static_cast<GamepadAxis>(k);
            if (axis == GamepadAxis::LeftTrigger || axis == GamepadAxis::RightTrigger)
                axisValue = std::max(0.f, axisValue);
        }

        for (uint32_t k = 0; k < magic_enum::enum_count<GamepadButton>(); k++)
        {
            GamepadButtonStatuses& statuses = gamepad.m_Buttons.at(k);
            const bool_t wasDown = statuses.at(static_cast<size_t>(GamepadButtonStatus::Down));
            const bool_t wasUp = statuses.at(static_cast<size_t>(GamepadButtonStatus::Up));

            if (k < std::size(state.buttons))
            {
                switch (state.buttons[k])
                {
                    case GLFW_RELEASE:
                        if (wasUp)
                            break;

                        statuses.at(static_cast<size_t>(GamepadButtonStatus::Down)) = false;
                        statuses.at(static_cast<size_t>(GamepadButtonStatus::Up)) = true;
                        statuses.at(static_cast<size_t>(GamepadButtonStatus::Pressed)) = false;
                        statuses.at(static_cast<size_t>(GamepadButtonStatus::Released)) = wasDown;
                        break;

                    case GLFW_PRESS:
                        if (wasDown)
                            break;

                        statuses.at(static_cast<size_t>(GamepadButtonStatus::Down)) = true;
                        statuses.at(static_cast<size_t>(GamepadButtonStatus::Up)) = false;
                        statuses.at(static_cast<size_t>(GamepadButtonStatus::Pressed)) = wasUp;
                        statuses.at(static_cast<size_t>(GamepadButtonStatus::Released)) = false;
                        break;

                    default:
                        break;
                }
            }
            else
            {
                // Mountain extensions
                switch (static_cast<GamepadButton>(k))
                {
                    case GamepadButton::LeftTrigger:
                    case GamepadButton::RightTrigger:
                    {
                        const GamepadAxis trigger = static_cast<GamepadAxis>(
                                k
                                - static_cast<int32_t>(GamepadButton::LeftTrigger)
                                + static_cast<int32_t>(GamepadAxis::LeftTrigger)
                            );

                        const bool_t release = gamepad.m_Axes[static_cast<size_t>(trigger)] < GamepadInput::nullAnalogValue;

                        if (release)
                        {
                            statuses.at(static_cast<size_t>(GamepadButtonStatus::Down)) = false;
                            statuses.at(static_cast<size_t>(GamepadButtonStatus::Up)) = true;
                            statuses.at(static_cast<size_t>(GamepadButtonStatus::Pressed)) = false;
                            statuses.at(static_cast<size_t>(GamepadButtonStatus::Released)) = wasDown;
                        }
                        else
                        {

                            statuses.at(static_cast<size_t>(GamepadButtonStatus::Down)) = true;
                            statuses.at(static_cast<size_t>(GamepadButtonStatus::Up)) = false;
                            statuses.at(static_cast<size_t>(GamepadButtonStatus::Pressed)) = wasUp;
                            statuses.at(static_cast<size_t>(GamepadButtonStatus::Released)) = false;
                        }
                        break;
                    }

                    default:
                        break;
                }
            }
        }

        gamepad.m_Name = glfwGetJoystickName(static_cast<int32_t>(i));
    }
}

void Input::UpdateConnectedGamepads()
{
    for (int32_t i = 0; i < static_cast<int32_t>(GamepadMax); i++)
    {
        const int32_t present = glfwJoystickPresent(i);
        GamepadInput& gamepad = m_Gamepads.at(static_cast<size_t>(i));
        gamepad.m_IsConnected = static_cast<bool_t>(present);
    }
}

void Input::Update()
{
    m_LastMousePosition = m_MousePosition;

    double_t x, y;
    glfwGetCursorPos(Window::GetHandle(), &x, &y);

    m_MousePosition = { static_cast<float_t>(x), static_cast<float_t>(y) };
    m_MouseDelta = m_MousePosition - m_LastMousePosition;

    UpdateGamepads();
}

void Input::Reset()
{
    for (auto& button : m_Mouse)
    {
        button.at(static_cast<size_t>(MouseButtonStatus::Pressed)) = false;
        button.at(static_cast<size_t>(MouseButtonStatus::Release)) = false;
    }

    m_MouseWheel = Vector2::Zero();

    for (auto& key : m_Keyboard)
    {
        key.at(static_cast<size_t>(KeyStatus::Pressed)) = false;
        key.at(static_cast<size_t>(KeyStatus::Release)) = false;
        key.at(static_cast<size_t>(KeyStatus::Repeat)) = false;
    }

    for (auto& gamepad : m_Gamepads)
    {
        for (auto& button : gamepad.m_Buttons)
        {
            button.at(static_cast<size_t>(GamepadButtonStatus::Pressed)) = false;
            button.at(static_cast<size_t>(GamepadButtonStatus::Released)) = false;
        }
    }
}

Vector2 Input::GetMouseDelta() { return m_MouseDelta; }

Vector2 Input::GetMouseWheel() { return m_MouseWheel; }

void Input::Initialize()
{
    Logger::LogVerbose("Initializing input");

    glfwSetKeyCallback(Window::GetHandle(), HandleKeyboard);
    glfwSetMouseButtonCallback(Window::GetHandle(), HandleMouseButton);
    glfwSetScrollCallback(Window::GetHandle(), HandleMouseWheel);
    glfwSetJoystickCallback(HandleJoyStickCallBack);

    KeyStatuses defaultKeys;
    defaultKeys.fill(false);
    m_Keyboard.fill(defaultKeys);

    MouseStatuses defaultMouseButtons;
    defaultMouseButtons.fill(false);
    m_Mouse.fill(defaultMouseButtons);

    UpdateConnectedGamepads();
}
