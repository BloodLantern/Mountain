module;

#include <magic_enum/magic_enum.hpp>

module Mountain:Input_GamepadInput;

import std;
import Mountain.Core;

namespace Mountain
{
    bool_t GamepadInput::GetConnected() const { return m_IsConnected; }

    const std::string& GamepadInput::GetName() const { return m_Name; }

    const std::array<float_t, magic_enum::enum_count<GamepadAxis>()>& GamepadInput::GetAxes() const { return m_Axes; }

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

    const std::array<GamepadButtonStatuses, magic_enum::enum_count<GamepadButton>()>& GamepadInput::GetButtons() const { return m_Buttons; }

    bool_t GamepadInput::GetButton(const GamepadButton button, const GamepadButtonStatus status) const
    {
        return m_Buttons[static_cast<uint32_t>(button)][static_cast<uint32_t>(status)];
    }
}
