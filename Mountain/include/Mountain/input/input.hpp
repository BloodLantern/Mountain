#pragma once

#include <array>

#include "Mountain/core.hpp"
#include "Mountain/window.hpp"
#include "Mountain/input/gamepad_input.hpp"
#include "Mountain/input/keyboard_input.hpp"
#include "Mountain/input/mouse_input.hpp"

/// @file input.hpp
/// @brief Defines the Mountain::Input static class.

BEGIN_MOUNTAIN

/// @brief Used to fetch inputs from the current @ref Window.
class Input
{
    STATIC_CLASS(Input)
    
public:
    static constexpr size_t GamepadMax = 15;
    
    /// @brief Check if a specified key is of the specified status
    /// @param key Key to check
    /// @param status Key status
    /// @return Result
    MOUNTAIN_API static bool_t GetKey(Key key, KeyStatus status = KeyStatus::Down);

    /// @brief Check if a specified mouse button is of the specified status
    /// @param mouseButton Mouse button to check
    /// @param status Mouse button status
    /// @return Result
    MOUNTAIN_API static bool_t GetMouseButton(MouseButton mouseButton, MouseButtonStatus status = MouseButtonStatus::Down);

    /// @brief Get a gamepad input
    /// @param gamepadId Gamepad id
    /// @return Result
    MOUNTAIN_API static const GamepadInput& GetGamepad(uint32_t gamepadId);

    /// @brief Get how many controllers are currently connected
    MOUNTAIN_API static uint32_t GetGamepadsConnected();

    /// @brief Get whether a gamepad is currently connected
    MOUNTAIN_API static bool_t IsGamepadConnected(uint32_t index);

    /// @brief Get the mouse position
    /// @return Mouse position
    MOUNTAIN_API static Vector2 GetMousePosition();

    /// @brief Get the mouse position delta
    MOUNTAIN_API static Vector2 GetMouseDelta();

    /// @brief Get the mouse wheel delta
    MOUNTAIN_API static Vector2 GetMouseWheel();

private:
    using KeyStatuses = std::array<bool_t, KeyStatusCount>;
    
    using MouseStatuses = std::array<bool_t, MouseButtonStatusCount>;
    
    MOUNTAIN_API static inline uint32_t m_CurrentBoundWindow = 0;
    
    MOUNTAIN_API static inline std::array<KeyStatuses, KeyCount> m_Keyboard;

    MOUNTAIN_API static inline std::array<MouseStatuses, MouseButtonCount> m_Mouse;
    
    MOUNTAIN_API static inline std::array<GamepadInput, GamepadMax> m_Gamepads;
    
    MOUNTAIN_API static inline Vector2 m_LastMousePosition;
    
    MOUNTAIN_API static inline Vector2 m_MousePosition;
    
    MOUNTAIN_API static inline Vector2 m_MouseDelta;
    
    MOUNTAIN_API static inline Vector2 m_MouseWheel;

    MOUNTAIN_API static inline GLFWwindow* m_WindowHandle = nullptr;

    /// @brief Initialize the input manager
    MOUNTAIN_API static void Initialize();

    /// @brief Update the input manager
    MOUNTAIN_API static void Update();

    MOUNTAIN_API static void Reset();

    static void HandleKeyboard(GLFWwindow* window, int32_t key, int32_t scancode, int32_t action, int32_t mods);
    
    static void HandleMouseButton(GLFWwindow* window, int32_t mouseButton, int32_t action, int32_t mods);
    
    static void HandleMouseWheel(GLFWwindow* window, double_t wheelX, double_t wheelY);
    
    static void HandleJoyStickCallBack(int32_t jid, int32_t event);
    
    static void UpdateGamepads();

    static void UpdateConnectedGamepads();

    friend class Window;
    friend class Game;
};

END_MOUNTAIN
