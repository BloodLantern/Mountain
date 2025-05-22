export module Mountain:Input_GamepadInput;

import <magic_enum/magic_enum.hpp>;

import "Mountain/Core.hpp";

import :Core;

/// @file GamepadInput.ixx
/// @brief Defines gamepad input types and enumerations.
///
/// Defines the Mountain::GamepadInput struct along with the Mountain::GamepadAxis and Mountain::GamepadButton enumerations.

export namespace Mountain
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

        None
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

    using GamepadButtonStatuses = std::array<bool_t, magic_enum::enum_count<GamepadButtonStatus>()>;

    /// @brief Information about a gamepad
    class GamepadInput
    {
    public:
        /// @brief Threshold that dictates that an axis analog value becomes 0
        static inline float_t nullAnalogValue = 1.5259022e-05f;

        MOUNTAIN_API bool_t GetConnected() const;

        MOUNTAIN_API const std::string& GetName() const;

        MOUNTAIN_API const std::array<float_t, magic_enum::enum_count<GamepadAxis>()>& GetAxes() const;

        MOUNTAIN_API float_t GetAxis(GamepadAxis axis) const;

        MOUNTAIN_API Vector2 GetStick(GamepadStick stick) const;

        MOUNTAIN_API Vector2i GetDirectionalPad() const;

        MOUNTAIN_API const std::array<GamepadButtonStatuses, magic_enum::enum_count<GamepadButton>()>& GetButtons() const;

        MOUNTAIN_API bool_t GetButton(GamepadButton button, GamepadButtonStatus status = GamepadButtonStatus::Down) const;

    private:
        /// @brief Whether the gamepad is connected
        bool_t m_IsConnected = false;
        /// @brief The human-readable name of the gamepad
        std::string m_Name;
        /// @brief Array of axis analog values
        std::array<float_t, magic_enum::enum_count<GamepadAxis>()> m_Axes{};
        /// @brief Array of button statuses
        std::array<GamepadButtonStatuses, magic_enum::enum_count<GamepadButton>()> m_Buttons{};

        friend class Input;
    };
}
