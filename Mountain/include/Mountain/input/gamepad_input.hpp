#pragma once

#include <array>
#include <cmath>
#include <string>

#include <Maths/vector2.hpp>
#include <Maths/vector2i.hpp>

#include "Mountain/core.hpp"

/// @file gamepad_input.hpp
/// @brief Defines gamepad input types and enumerations.
/// 
/// Defines the Mountain::GamepadInput struct along with the Mountain::GamepadAxis and Mountain::GamepadButton enumerations.

BEGIN_MOUNTAIN

/// @brief Gamepad axis enumeration
enum class GamepadAxis
{
    LeftStickHorizontal,
    LeftStickVertical,
    RightStickHorizontal,
    RightStickVertical,
    LeftTrigger,
    RightTrigger,

    Count,

    None
};

constexpr size_t GamepadAxisCount = static_cast<size_t>(GamepadAxis::Count);

/// @brief Gamepad stick enumeration
enum class GamepadStick
{
    Left,
    Right,

    Count,

    None
};

constexpr size_t GamepadStickCount = static_cast<size_t>(GamepadStick::Count);

/// @brief Gamepad button enumeration
///
/// Defines the gamepad button values according to the Xbox controller button placements.
enum class GamepadButton
{
    A,
    B,
    X,
    Y,
    LeftBumper,
    RightBumper,
    Back,
    Start,
    Guide,
    LeftStick,
    RightStick,
    DirectionalPadUp,
    DirectionalPadRight,
    DirectionalPadDown,
    DirectionalPadLeft,

    // Mountain extensions, not supported by GLFW as buttons
    LeftTrigger,
    RightTrigger,

    Count,

    None
};

constexpr size_t GamepadButtonCount = static_cast<size_t>(GamepadButton::Count);

/// @brief Gamepad button
enum class GamepadButtonStatus
{
    /// @brief Held down
    Down,
    /// @brief Held up
    Up,
    /// @brief Pressed this frame
    Pressed,
    /// @brief Released this frame
    Released,
    
    Count
};

constexpr size_t GamepadButtonStatusCount = static_cast<size_t>(GamepadButtonStatus::Count);

using GamepadButtonStatuses = std::array<bool_t, GamepadButtonStatusCount>;

/// @brief Information about a gamepad
class GamepadInput
{
public:
    /// @brief Threshold that dictates that an axis analog value becomes 0
    static inline float_t nullAnalogValue = 1.5259022e-05f;

    MOUNTAIN_API bool_t GetConnected() const;
    
    MOUNTAIN_API const std::string& GetName() const;
    
    MOUNTAIN_API const std::array<float_t, GamepadAxisCount>& GetAxes() const;
    
    MOUNTAIN_API float_t GetAxis(GamepadAxis axis) const;
    
    MOUNTAIN_API Vector2 GetStick(GamepadStick stick) const;
    
    MOUNTAIN_API Vector2i GetDirectionalPad() const;
    
    MOUNTAIN_API const std::array<GamepadButtonStatuses, GamepadButtonCount>& GetButtons() const;
    
    MOUNTAIN_API bool_t GetButton(GamepadButton button, GamepadButtonStatus status = GamepadButtonStatus::Down) const;

private:
    /// @brief Whether the gamepad is connected
    bool_t m_IsConnected = false;
    /// @brief The human-readable name of the gamepad
    std::string m_Name;
    /// @brief Array of axis analog values
    std::array<float_t, GamepadAxisCount> m_Axes{};
    /// @brief Array of button statuses
    std::array<GamepadButtonStatuses, GamepadButtonCount> m_Buttons{};
    
    friend class Input;
};

END_MOUNTAIN
