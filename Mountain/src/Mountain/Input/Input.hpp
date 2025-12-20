#pragma once

#include <array>

#include "Mountain/Core.hpp"
#include "Mountain/Window.hpp"
#include "Mountain/Input/GamepadInput.hpp"
#include "Mountain/Input/KeyboardInput.hpp"
#include "Mountain/Input/MouseInput.hpp"

/// @file input.hpp
/// @brief Defines the Mountain::Input static class.

namespace Mountain
{
    /// @brief Used to fetch inputs from the current @ref Window.
    class Input
    {
        STATIC_CLASS(Input)

    public:
        static constexpr usize GamepadMax = 15;

        /// @brief Check if a specified key is of the specified status
        /// @param key Key to check
        /// @param status Key status
        /// @return Result
        MOUNTAIN_API static bool GetKey(Key key, KeyStatus status = KeyStatus::Down);

        /// @brief Check if a specified mouse button is of the specified status
        /// @param mouseButton Mouse button to check
        /// @param status Mouse button status
        /// @return Result
        MOUNTAIN_API static bool GetMouseButton(MouseButton mouseButton, MouseButtonStatus status = MouseButtonStatus::Down);

        /// @brief Get a gamepad input
        /// @param gamepadId Gamepad id
        /// @return Result
        MOUNTAIN_API static const GamepadInput& GetGamepad(u32 gamepadId);

        /// @brief Get how many controllers are currently connected
        MOUNTAIN_API static u32 GetGamepadsConnected();

        /// @brief Get whether a gamepad is currently connected
        MOUNTAIN_API static bool IsGamepadConnected(u32 index);

        /// @brief Get the mouse position relative to the window
        MOUNTAIN_API static Vector2 GetMousePosition();

        /// @brief Get how much the mouse moved last frame
        MOUNTAIN_API static Vector2 GetMouseDelta();

        /// @brief Get how much the mouse wheel moved last frame
        MOUNTAIN_API static Vector2 GetMouseWheel();

    private:
        using KeyStatuses = Array<bool, magic_enum::enum_count<KeyStatus>()>;

        using MouseStatuses = Array<bool, magic_enum::enum_count<MouseButtonStatus>()>;

        MOUNTAIN_API static inline u32 m_CurrentBoundWindow = 0;

        MOUNTAIN_API static inline Array<KeyStatuses, static_cast<usize>(Key::Count)> m_Keyboard;

        MOUNTAIN_API static inline Array<MouseStatuses, magic_enum::enum_count<MouseButton>()> m_Mouse;

        MOUNTAIN_API static inline Array<GamepadInput, GamepadMax> m_Gamepads;

        MOUNTAIN_API static inline Vector2 m_LastMousePosition;

        MOUNTAIN_API static inline Vector2 m_MousePosition;

        MOUNTAIN_API static inline Vector2 m_MouseDelta;

        MOUNTAIN_API static inline Vector2 m_MouseWheel;

        /// @brief Initialize the input manager
        MOUNTAIN_API static void Initialize();

        MOUNTAIN_API static void Reset();

        static void HandleKeyboard(usize key, KeyAction action);

        static void HandleMouseButton(usize mouseButton, bool pressed);
        static void HandleMouseMovement(Vector2 newPosition);
        static void HandleMouseWheel(s32 wheelX, s32 wheelY);

        static void ConnectGamepad(u32 id);
        static void DisconnectGamepad(u32 id);
        static void UpdateGamepadButton(u32 id, GamepadButton button, bool down);
        static void UpdateGamepadAxis(u32 id, GamepadAxis axis, s16 value);
        static void UpdateGamepadBattery(u32 id, s8 percent, GamepadBatteryState state);
        static void UpdateGamepadGyro(u32 id, const Vector3& gyro);
        static void UpdateGamepadAccel(u32 id, const Vector3& accel);
        static void UpdateGamepadTouchpad(u32 id, usize touchpad, usize finger, Vector2 location);

        friend class Window;
        friend class Game;
    };
}
