#pragma once

#include <Math/vector2i.hpp>

#include "Mountain/Core.hpp"
#include "Mountain/Rendering/Renderer.hpp"
#include "Mountain/Resource/Texture.hpp"
#include "Mountain/Utils/Event.hpp"

/// @file window.hpp
/// @brief Defines the Mountain::Window class.

// ReSharper disable once CppInconsistentNaming
struct GLFWwindow;

namespace Mountain
{
    enum class WindowMode : uint8_t
    {
        Windowed,
        Borderless,
        Fullscreen
    };

    /// @brief A wrapper for the main window
    class Window
    {
        STATIC_CLASS(Window)

    public:
        /// @brief Event called when the window position changed. The parameter is the new position.
        MOUNTAIN_API static inline Event<Vector2i> onPositionChanged;
        /// @brief Event called when the window size changed. The parameter is the new size.
        MOUNTAIN_API static inline Event<Vector2i> onSizeChanged;

        /// @brief Get the screen position in pixels of the window
        STATIC_GETTER(Vector2i, Position, m_Position)

        MOUNTAIN_API static void SetPosition(Vector2i newPosition);

        /// @brief Get the size in pixels of the window
        STATIC_GETTER(Vector2i, Size, m_Size)

        MOUNTAIN_API static void SetSize(Vector2i newSize);

        /// @brief Get whether the window should close
        [[nodiscard]]
        MOUNTAIN_API static bool_t GetShouldClose();

        /// @brief Set whether the window should close
        MOUNTAIN_API static void SetShouldClose(bool_t newShouldClose);

        /// @brief Set the window to be the current context
        MOUNTAIN_API static void MakeContextCurrent();

        /// @brief Get the native handle of the window
        STATIC_GETTER(GLFWwindow*, Handle, m_Window)

        /// @brief Get whether the window is visible or hidden.
        STATIC_GETTER(bool_t, Visible, m_Visible)

        /// @brief Set whether the window should be visible or hidden.
        MOUNTAIN_API static void SetVisible(bool_t newVisible);

        /// @brief Set the icon for the window
        MOUNTAIN_API static void SetIcon(const Pointer<Texture>& newIcon);

        /// @brief Handle hiding or displaying the cursor
        /// @param newCursorHidden @c true hides, @c false displays
        MOUNTAIN_API static void SetCursorHidden(bool_t newCursorHidden);

        /// @brief Set the mouse cursor position in screen space
        MOUNTAIN_API static void SetCursorPosition(Vector2 newPosition);

        STATIC_GETTER(bool_t, VSync, m_VSync)

        MOUNTAIN_API static void SetVSync(bool_t newVsync);

        STATIC_GETTER(WindowMode, WindowMode, m_WindowMode)

        MOUNTAIN_API static void SetWindowMode(WindowMode newWindowMode);

        /// @brief Get the index of the screen on which this window currently is
        STATIC_GETTER(int32_t, CurrentScreen, m_CurrentScreen)

        [[nodiscard]]
        MOUNTAIN_API static std::string_view GetTitle();

        MOUNTAIN_API static void SetTitle(const std::string& newTitle);

        STATIC_GETTER(bool_t, Minimized, m_Minimized)

    private:
        /// @brief Native window handle
        MOUNTAIN_API static inline GLFWwindow* m_Window = nullptr;

        MOUNTAIN_API static inline WindowMode m_WindowMode = WindowMode::Windowed;

        MOUNTAIN_API static inline int32_t m_CurrentScreen;

        MOUNTAIN_API static inline Vector2i m_Position;
        MOUNTAIN_API static inline Vector2i m_Size;

        MOUNTAIN_API static inline bool_t m_Visible;
        MOUNTAIN_API static inline bool_t m_Minimized = false;

        MOUNTAIN_API static inline bool_t m_VSync = false;

        /// @brief Initializes the window
        static void Initialize(const std::string& windowTitle, Vector2i windowSize, const OpenGlVersion &glVersion);

        /// @brief Terminates the window
        static void Shutdown();

        static void UpdateFields();

        static void UpdateCurrentScreen();

        static void PollEvents();

        static void SwapBuffers();

        static void WindowMinimizeCallback(GLFWwindow* window, int32_t minimized);

        // Calls Initialize, UpdateFields and Shutdown
        friend class Renderer;
        // Calls PollEvents
        friend class Game;
        // Calls SwapBuffers
        friend class Time;
    };
}
