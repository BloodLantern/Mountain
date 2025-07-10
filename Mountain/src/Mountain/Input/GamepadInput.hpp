#pragma once

#include <array>
#include <cmath>
#include <string>

#include <Math/vector2.hpp>
#include <Math/vector2i.hpp>

#include <magic_enum/magic_enum.hpp>

#include "Mountain/Core.hpp"
#include "Mountain/Containers/Array.hpp"
#include "Mountain/Utils/Color.hpp"
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

    /// @brief Gamepad battery state
    enum class GamepadBatteryState : uint8_t
    {
        /// @brief Unknown power level
        Unknown,
        /// @brief Not plugged in, running on the battery
        OnBattery,
        /// @brief Plugged in, no battery available
        NoBattery,
        /// @brief Plugged in, charging the battery
        Charging,
        /// @brief Plugged in, battery fully charged
        Charged
    };

    /// @brief Describes the special capabilities of a gamepad
    enum class GamepadCapabilities : uint8_t
    {
        /// @brief No capabilities
        None =          0,
        /// @brief The gamepad has a colored LED (e.g. PS4 controller)
        Led =           1 << 0,
        /// @brief The gamepad has rumble
        Rumble =        1 << 1,
        /// @brief The gamepad has a touchpad
        Touchpad =      1 << 2,
        /// @brief The gamepad has a gyroscope
        Gyroscope =     1 << 3,
        /// @brief The gamepad has an accelerometer
        Accelerometer = 1 << 4
    };

    using GamepadButtonStatuses = Array<bool_t, magic_enum::enum_count<GamepadButtonStatus>()>;

    /// @brief Information about a gamepad
    class GamepadInput
    {
    public:
        using AxesArray = Array<float_t, magic_enum::enum_count<GamepadAxis>()>;
        using ButtonsArray = Array<GamepadButtonStatuses, magic_enum::enum_count<GamepadButton>()>;

        /// @brief Information about a touchpad on a gamepad
        struct TouchpadInfo
        {
            /// @brief Maximum number of fingers supported on the touchpad
            uint8_t nbrOfFingersMax;
            /// @brief Fingers position on the touchpad, negative if none
            Array<Vector2, 5> fingerLocations;
        };

        /// @brief Threshold that dictates that an axis analog value becomes 0
        static inline float_t nullAnalogValue = 1.5259022e-05f;

        MOUNTAIN_API GETTER(bool_t, Connected, m_IsConnected)

        [[nodiscard]]
        MOUNTAIN_API const std::string& GetName() const;

        [[nodiscard]]
        MOUNTAIN_API float_t GetAxis(GamepadAxis axis) const;

        [[nodiscard]]
        MOUNTAIN_API Vector2 GetStick(GamepadStick stick) const;

        [[nodiscard]]
        MOUNTAIN_API Vector2i GetDirectionalPad() const;

        [[nodiscard]]
        MOUNTAIN_API bool_t GetButton(GamepadButton button, GamepadButtonStatus status = GamepadButtonStatus::Down) const;

        [[nodiscard]]
        MOUNTAIN_API const TouchpadInfo& GetTouchpad(size_t index) const;

        [[nodiscard]]
        MOUNTAIN_API size_t GetTouchpadAmount() const;

        /// @brief Sets the gamepad LED color if there's one
        /// @param color Color
        MOUNTAIN_API void SetLight(const Color& color) const;

        /// @brief Performs a rumble
        /// @param weak Weak rumble frequency, value in [0;1]
        /// @param strong Strong rumble frequency, value in [0;1]
        /// @param duration Rumble duration, in seconds
        MOUNTAIN_API void Rumble(float_t weak, float_t strong, float_t duration) const;

        /// @brief Checks whether the gamepad has a specified capability
        /// @param capability Capability
        /// @return Whether the gamepad has it
        [[nodiscard]]
        MOUNTAIN_API bool_t HasCapability(GamepadCapabilities capability) const;

        MOUNTAIN_API GETTER(const ButtonsArray&, Buttons, m_Buttons)

        MOUNTAIN_API GETTER(const AxesArray&, Axes, m_Axes)

        MOUNTAIN_API GETTER(const Color&, Light, m_ColorLight)

        MOUNTAIN_API GETTER(const Vector3&, Gyroscope, m_Gyroscope)
        MOUNTAIN_API GETTER(const Vector3&, Accelerometer, m_Accelerometer)

        MOUNTAIN_API GETTER(int8_t, Battery, m_Battery)
        MOUNTAIN_API GETTER(GamepadBatteryState, BatteryState, m_BatteryState)

    private:
        /// @brief Whether the gamepad is connected
        bool_t m_IsConnected = false;
        /// @brief The human-readable name of the gamepad
        std::string m_Name;
        /// @brief Array of axis analog values
        AxesArray m_Axes{};
        /// @brief Array of button statuses
        ButtonsArray m_Buttons{};
        /// @brief Battery level of the controller (-1 if there's no battery)
        int8_t m_Battery;
        /// @brief Battery state
        GamepadBatteryState m_BatteryState;
        /// @brief Gamepad capabilities
        GamepadCapabilities m_Capabilities;

        /// @brief Current game pad light, if any
        mutable Color m_ColorLight;
        /// @brief Gamepad gyroscope values, if any
        Vector3 m_Gyroscope;
        /// @brief Gamepad accelerometer values, if any
        Vector3 m_Accelerometer;
        /// @brief Touchpads info, if any
        List<TouchpadInfo> m_Touchpads;

        /// @brief Internal id of the gamepad
        SDL_JoystickID m_Id;
        /// @brief Native handle
        SDL_Gamepad* m_Handle;
        
        friend class Input;
    };
}

ENUM_FLAGS(Mountain::GamepadCapabilities)
