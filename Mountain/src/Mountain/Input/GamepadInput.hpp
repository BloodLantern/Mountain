#pragma once

#include <array>
#include <cmath>
#include <string>

#include <Math/vector2.hpp>
#include <Math/vector2i.hpp>

#include <magic_enum/magic_enum.hpp>

#include "Mountain/Core.hpp"
#include "Mountain/Containers/Array.hpp"
#include "SDL3/SDL_gamepad.h"

/// @file GamepadInput.hpp
/// @brief Defines gamepad input types and enumerations.
///
/// Defines the Mountain::GamepadInput struct along with the Mountain::GamepadAxis and Mountain::GamepadButton enumerations.

namespace Mountain
{
    /// @brief Gamepad axis enumeration
    enum class GamepadAxis : uint8_t
    {
        LeftStickHorizontal,
        LeftStickVertical,
        RightStickHorizontal,
        RightStickVertical,
        LeftTrigger,
        RightTrigger
    };

    /// @brief Gamepad stick enumeration
    enum class GamepadStick : uint8_t
    {
        Left,
        Right
    };

    /// @brief Gamepad button enumeration
    ///
    /// Defines the gamepad button values according to the Xbox controller button placements.
    enum class GamepadButton : uint8_t
    {
        /// @brief Xbox A face button
        A,
        /// @brief Xbox B face button
        B,
        /// @brief Xbox X face button
        X,
        /// @brief Xbox Y face button
        Y,
        /// @brief Xbox back button (minus for Switch, share for Playstation)
        Back,
        /// @brief Xbox guide button (TODO verify home for Switch, PS for Playstation)
        Guide,
        /// @brief Xbox start button (plus for Switch, options for Playstation)
        Start,
        /// @brief Left stick press
        LeftStick,
        /// @brief Right stick press
        RightStick,
        /// @brief Left bumper
        LeftBumper,
        /// @brief Right bumper
        RightBumper,
        /// @brief D-pad up
        DirectionalPadUp,
        /// @brief D-pad down
        DirectionalPadDown,
        /// @brief D-pad left
        DirectionalPadLeft,
        /// @brief D-pad right
        DirectionalPadRight,

        /// @brief Misc. button, depends on the controller
        Misc1,
        /// @brief Right primary paddle
        RightPaddle1,
        /// @brief Left primary paddle
        LeftPaddle1,
        /// @brief Right secondary paddle
        RightPaddle2,
        /// @brief Left primary paddle
        LeftPaddle2,

        /// @brief Playstation touchpad
        Touchpad,
        /// @brief Misc. button
        Misc2,
        /// @brief Misc. button
        Misc3,
        /// @brief Misc. button
        Misc4,
        /// @brief Misc. button
        Misc5,
        /// @brief Misc. button
        Misc6,

        // Mountain extensions, not supported as native buttons
        /// @brief Left trigger treated as a button press
        LeftTrigger,
        /// @brief Right trigger treated as a button press
        RightTrigger,

        None,

        /// @brief Xbox series X share button, bound to @c Misc1
        XboxXShare = Misc1,
        /// @brief PS5 microphone button, bound to @c Misc1
        Ps5Microphone = Misc1,
        /// @brief Switch capture button, bound to @c Misc1
        SwitchCapture = Misc1,
    };

    /// @brief Gamepad button
    enum class GamepadButtonStatus : uint8_t
    {
        /// @brief Held down
        Down,
        /// @brief Held up
        Up,
        /// @brief Pressed this frame
        Pressed,
        /// @brief Released this frame
        Released
    };

    using GamepadButtonStatuses = Array<bool_t, magic_enum::enum_count<GamepadButtonStatus>()>;

    /// @brief Information about a gamepad
    class GamepadInput
    {
    public:
        using AxesArray = Array<float_t, magic_enum::enum_count<GamepadAxis>()>;
        using ButtonsArray = Array<GamepadButtonStatuses, magic_enum::enum_count<GamepadButton>()>;
        
        /// @brief Threshold that dictates that an axis analog value becomes 0
        static inline float_t nullAnalogValue = 1.5259022e-05f;

        MOUNTAIN_API GETTER(bool_t, Connected, m_IsConnected)

        MOUNTAIN_API const std::string& GetName() const;

        MOUNTAIN_API float_t GetAxis(GamepadAxis axis) const;

        MOUNTAIN_API Vector2 GetStick(GamepadStick stick) const;

        MOUNTAIN_API Vector2i GetDirectionalPad() const;

        MOUNTAIN_API bool_t GetButton(GamepadButton button, GamepadButtonStatus status = GamepadButtonStatus::Down) const;

        /// @brief Sets the gamepad LED light
        /// @param color Color
        MOUNTAIN_API void SetLight(const Color& color) const;

        /// @brief Performs a rumble
        /// @param lowFrequency Low rumble frequency, value in [0;1]
        /// @param highFrequency High rumble frequency, value in [0;1]
        /// @param duration Rumble duration, in ms
        MOUNTAIN_API void Rumble(float_t lowFrequency, float_t highFrequency, uint32_t duration) const;

        MOUNTAIN_API GETTER(const ButtonsArray&, Buttons, m_Buttons)

        MOUNTAIN_API GETTER(const AxesArray&, Axes, m_Axes)

    private:
        /// @brief Whether the gamepad is connected
        bool_t m_IsConnected = false;
        /// @brief The human-readable name of the gamepad
        std::string m_Name;
        /// @brief Array of axis analog values
        AxesArray m_Axes{};
        /// @brief Array of button statuses
        ButtonsArray m_Buttons{};
        /// @brief Internal id of the gamepad
        SDL_JoystickID m_Id;
        /// @brief Native handle
        SDL_Gamepad* m_Handle;
        
        friend class Input;
    };
}
