#include "Mountain/Input/GamepadInput.hpp"

#include "Mountain/Utils/Color.hpp"
#include "Mountain/Utils/Logger.hpp"

using namespace Mountain;

const std::string& GamepadInput::GetName() const { return m_Name; }

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

bool_t GamepadInput::GetButton(const GamepadButton button, const GamepadButtonStatus status) const
{
    return m_Buttons[static_cast<uint32_t>(button)][static_cast<uint32_t>(status)];
}

void GamepadInput::SetLight(const Color& color) const
{
    const uint8_t r = static_cast<uint8_t>(color.r * 255.f);
    const uint8_t g = static_cast<uint8_t>(color.g * 255.f);
    const uint8_t b = static_cast<uint8_t>(color.b * 255.f);

    if (!SDL_SetGamepadLED(m_Handle, r, g, b))
        Logger::LogError("Failed to set gamepad light : {}", SDL_GetError());
}

void GamepadInput::Rumble(const float_t lowFrequency, const float_t highFrequency, const uint32_t duration) const
{
    if (lowFrequency < 0.f || lowFrequency > 1.f)
        THROW(ArgumentException("Rumble frequency value should be within [0;1]", "lowFrequency"));

    if (highFrequency < 0.f || highFrequency > 1.f)
        THROW(ArgumentException("Rumble frequency value should be within [0;1]", "highFrequency"));

    const uint16_t low = static_cast<uint16_t>(lowFrequency * 0xFFFF);
    const uint16_t high = static_cast<uint16_t>(highFrequency * 0xFFFF);

    if (!SDL_RumbleGamepad(m_Handle, low, high, duration))
        Logger::LogError("Failed to perform gamepad rumble : {}", SDL_GetError());
}
