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

const GamepadInput::TouchpadInfo& GamepadInput::GetTouchpad(const size_t index) const
{
    if (!HasCapability(GamepadCapabilities::Touchpad))
    {
        const std::string error = std::format("Trying to access a touchpad on a controller that doesn't have one: {}", GetName());
        THROW(InvalidOperationException{error.c_str()});
    }

    if (index >= m_Touchpads.GetSize())
    {
        THROW(ArgumentOutOfRangeException{"Touchpad index out of range", "index"});
    }

    return m_Touchpads[index];
}

size_t GamepadInput::GetTouchpadAmount() const
{
    return m_Touchpads.GetSize();
}

void GamepadInput::SetLight(const Color& color) const
{
    if (!HasCapability(GamepadCapabilities::Led))
    {
        Logger::LogWarning("Trying to set LED color on a controller that doesn't support it: {}", GetName());
        return;
    }

    m_ColorLight = color;

    const uint8_t r = static_cast<uint8_t>(color.r * 255.f);
    const uint8_t g = static_cast<uint8_t>(color.g * 255.f);
    const uint8_t b = static_cast<uint8_t>(color.b * 255.f);

    if (!SDL_SetGamepadLED(m_Handle, r, g, b))
        Logger::LogError("Failed to set gamepad light: {}", SDL_GetError());
}

void GamepadInput::Rumble(const float_t weak, const float_t strong, const float_t duration) const
{
    if (weak < 0.f || weak > 1.f)
        THROW(ArgumentException("Rumble frequency value should be in the range [0, 1]", "weak"));

    if (strong < 0.f || strong > 1.f)
        THROW(ArgumentException("Rumble frequency value should be in the range [0, 1]", "strong"));

    if (!HasCapability(GamepadCapabilities::Rumble))
    {
        Logger::LogWarning("Trying to use rumble on a controller that doesn't support it: {}", GetName());
        return;
    }

    const uint16_t low = static_cast<uint16_t>(strong * 0xFFFF);
    const uint16_t high = static_cast<uint16_t>(weak * 0xFFFF);
    const uint32_t ms = static_cast<uint16_t>(duration * 1000);

    if (!SDL_RumbleGamepad(m_Handle, low, high, ms))
        Logger::LogError("Failed to perform gamepad rumble: {}", SDL_GetError());
}

bool_t GamepadInput::HasCapability(const GamepadCapabilities capability) const
{
    return m_Capabilities & capability;
}
