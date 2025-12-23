#include "Mountain/Input/GamepadInput.hpp"

#include <SDL3/SDL_gamepad.h>

#include "Mountain/Utils/Color.hpp"
#include "Mountain/Utils/Logger.hpp"

using namespace Mountain;

const std::string& GamepadInput::GetName() const { return m_Name; }

f32 GamepadInput::GetAxis(const GamepadAxis axis) const { return m_Axes[static_cast<u32>(axis)]; }

Vector2 GamepadInput::GetStick(const GamepadStick stick) const
{
    const bool leftStick = stick == GamepadStick::Left;
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

bool GamepadInput::GetButton(const GamepadButton button, const GamepadButtonStatus status) const
{
    return m_Buttons[static_cast<u32>(button)][static_cast<u32>(status)];
}

const GamepadInput::TouchpadInfo& GamepadInput::GetTouchpad(const usize index) const
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

usize GamepadInput::GetTouchpadAmount() const
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

    const u8 r = static_cast<u8>(color.r * 255.f);
    const u8 g = static_cast<u8>(color.g * 255.f);
    const u8 b = static_cast<u8>(color.b * 255.f);

    if (!SDL_SetGamepadLED(m_Handle, r, g, b))
        Logger::LogError("Failed to set gamepad light: {}", SDL_GetError());
}

void GamepadInput::Rumble(const f32 weak, const f32 strong, const f32 duration) const
{
    if (weak < 0.f || weak > 1.f)
        THROW(ArgumentOutOfRangeException("Rumble frequency value should be in the range [0, 1]", "weak"));

    if (strong < 0.f || strong > 1.f)
        THROW(ArgumentOutOfRangeException("Rumble frequency value should be in the range [0, 1]", "strong"));

    if (!HasCapability(GamepadCapabilities::Rumble))
    {
        Logger::LogWarning("Trying to use rumble on a controller that doesn't support it: {}", GetName());
        return;
    }

    const u16 low = static_cast<u16>(strong * 0xFFFF);
    const u16 high = static_cast<u16>(weak * 0xFFFF);
    const u32 ms = static_cast<u16>(duration * 1000);

    if (!SDL_RumbleGamepad(m_Handle, low, high, ms))
        Logger::LogError("Failed to perform gamepad rumble: {}", SDL_GetError());
}

bool GamepadInput::HasCapability(const GamepadCapabilities capability) const
{
    return m_Capabilities & capability;
}
