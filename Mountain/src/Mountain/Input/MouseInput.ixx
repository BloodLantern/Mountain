export module Mountain:Input_MouseInput;

import Mountain.Core;

/// @file MouseInput.ixx
/// @brief Defines enumerators related to mouse input

export namespace Mountain
{
    /// @brief %List of mouse buttons
    enum class MouseButton : uint8_t
    {
        /// @brief Left click
        Left,
        /// @brief Right click
        Right,
        /// @brief Wheel click
        Middle,
        /// @brief Extension button 3
        Button3,
        /// @brief Extension button 4
        Button4,
        /// @brief Extension button 5
        Button5,
        /// @brief Extension button 6
        Button6,
        /// @brief Extension button 7
        Button7,
        /// @brief Extension button 8
        Button8,

        None
    };

    /// @brief %List of mouse button states
    enum class MouseButtonStatus : uint8_t
    {
        /// @brief Pressed, e.g. @c true the first frame it is down
        Pressed,
        /// @brief Held down
        Down,
        /// @brief Released
        Release
    };
}
