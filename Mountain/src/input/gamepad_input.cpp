#include "input/gamepad_input.hpp"

using namespace Mountain;

bool_t GamepadInput::GetConnected() const { return m_IsConnected; }

const std::string& GamepadInput::GetName() const { return m_Name; }

const std::array<float_t, GamepadAxisCount>& GamepadInput::GetAxes() const { return m_Axes; }

float_t GamepadInput::GetAxis(const GamepadAxis axis) const { return m_Axes[static_cast<uint32_t>(axis)]; }

Vector2 GamepadInput::GetStick(const GamepadStick stick) const
{
    const bool_t leftStick = stick == GamepadStick::Left;
    return {
        GetAxis(leftStick ? GamepadAxis::LeftStickHorizontal : GamepadAxis::RightStickHorizontal),
        GetAxis(leftStick ? GamepadAxis::LeftStickVertical : GamepadAxis::RightStickVertical)
    };
}

Vector2i GamepadInput::GetDirectionalPad() const
{
    return {
        GetButton(GamepadButton::DirectionalPadRight) - GetButton(GamepadButton::DirectionalPadLeft),
        GetButton(GamepadButton::DirectionalPadDown) - GetButton(GamepadButton::DirectionalPadUp)
    };
}

const std::array<GamepadButtonStatuses, GamepadButtonCount>& GamepadInput::GetButtons() const { return m_Buttons; }

bool_t GamepadInput::GetButton(const GamepadButton button, const GamepadButtonStatus status) const
{
    return m_Buttons[static_cast<uint32_t>(button)][static_cast<uint32_t>(status)];
}
