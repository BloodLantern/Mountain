#pragma once

#include "core.hpp"

/// @file mouse_input.hpp
/// @brief Defines enumerators related to mouse input

BEGIN_MOUNTAIN

/// @brief %List of mouse buttons
enum class MouseButton
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
    
    Count
};

constexpr size_t MouseButtonCount = static_cast<size_t>(MouseButton::Count);

/// @brief %List of mouse button states
enum class MouseButtonStatus
{
    /// @brief Pressed
    Pressed,
    /// @brief Held down
    Down,
    /// @brief Released
    Release,
    
    Count
};

constexpr size_t MouseButtonStatusCount = static_cast<size_t>(MouseButtonStatus::Count);

END_MOUNTAIN
