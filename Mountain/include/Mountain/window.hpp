#pragma once

#include <Maths/vector2i.hpp>

#include "Mountain/core.hpp"
#include "Mountain/rendering/renderer.hpp"
#include "Mountain/resource/texture.hpp"
#include "Mountain/utils/event.hpp"

/// @file window.hpp
/// @brief Defines the Mountain::Window class.

// ReSharper disable once CppInconsistentNaming
struct GLFWwindow;

namespace Mountain
{
    /// @brief A wrapper for the main window
    class Window
    {
        STATIC_CLASS(Window)

    public:
        /// @brief Event called when the window position changed. The parameter is the new position.
        MOUNTAIN_API static inline Event<Vector2i> onPositionChanged;
        /// @brief Event called when the window size changed. The parameter is the new size.
        MOUNTAIN_API static inline Event<Vector2i> onSizeChanged;

        /// @brief Gets the screen position in pixels of the window
        /// @return Position
        [[nodiscard]]
        MOUNTAIN_API static Vector2i GetPosition();

        MOUNTAIN_API static void SetPosition(Vector2i newPosition);

        /// @brief Gets the size in pixels of the window
        /// @return Size
        [[nodiscard]]
        MOUNTAIN_API static Vector2i GetSize();

        MOUNTAIN_API static void SetSize(Vector2i newSize);

        /// @brief Gets whether the window should close
        [[nodiscard]]
        MOUNTAIN_API static bool_t GetShouldClose();

        /// @brief Sets whether the window should close
        MOUNTAIN_API static void SetShouldClose(bool_t newShouldClose);

        /// @brief Polls the events of the window
        MOUNTAIN_API static void PollEvents();

        /// @brief Sets the window to be the current context
        MOUNTAIN_API static void MakeContextCurrent();

        /// @brief Gets the native handle of the window
        /// @return Native handle
        [[nodiscard]]
        MOUNTAIN_API static GLFWwindow* GetHandle();

        /// @brief Gets whether the window is visible or hidden.
        [[nodiscard]]
        MOUNTAIN_API static bool_t GetVisible();

        /// @brief Sets whether the window should be visible or hidden.
        MOUNTAIN_API static void SetVisible(bool_t newVisible);

        /// @brief Sets the icon for the window
        /// @param newIcon Icon
        MOUNTAIN_API static void SetIcon(const Pointer<Texture>& newIcon);

        /// @brief Handles hiding or displaying the cursor
        /// @param newCursorHidden @c true hides, @c false displays
        MOUNTAIN_API static void SetCursorHidden(bool_t newCursorHidden);

        /// @brief Sets the mouse cursor position in screen space.
        MOUNTAIN_API static void SetCursorPosition(Vector2 newPosition);

        MOUNTAIN_API static void SetVSync(bool_t newVsync);

        /// @brief Gets whether the window is in fullscreen mode
        [[nodiscard]]
        MOUNTAIN_API static bool_t GetFullscreen();

        /// @brief Sets whether the window is in fullscreen mode
        MOUNTAIN_API static void SetFullscreen(bool_t newFullscreen);

        /// @brief Gets the index of the screen on which this window currently is
        [[nodiscard]]
        MOUNTAIN_API static uint32_t GetCurrentScreen();

        [[nodiscard]]
        MOUNTAIN_API static std::string_view GetTitle();

        MOUNTAIN_API static void SetTitle(std::string_view newTitle);

        [[nodiscard]]
        MOUNTAIN_API static bool_t GetMinimized();

    private:
        /// @brief Native window handle
        static inline GLFWwindow* m_Window = nullptr;

        static inline bool_t m_Fullscreen = false;

        static inline uint32_t m_CurrentScreen;

        static inline Vector2i m_Position;
        static inline Vector2i m_Size;

        static inline bool_t m_Visible;
        static inline bool_t m_Minimized = false;

        /// @brief Initializes the window
        static void Initialize(std::string_view windowTitle, Vector2i windowSize, const OpenGlVersion &glVersion);

        /// @brief Terminates the window
        static void Shutdown();

        static void UpdateFields();

        static void UpdateCurrentScreen();

        static void SwapBuffers();

        static void WindowMinimizeCallback(GLFWwindow* window, int minimized);

        friend class Renderer;
        friend class Game;
        friend class Time;
    };
}
