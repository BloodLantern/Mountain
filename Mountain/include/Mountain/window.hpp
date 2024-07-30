#pragma once

#include <Maths/vector2i.hpp>

#include "Mountain/core.hpp"
#include "Mountain/rendering/renderer.hpp"
#include "Mountain/resource/texture.hpp"

/// @file window.hpp
/// @brief Defines the Mountain::Window class.

// ReSharper disable once CppInconsistentNaming
struct GLFWwindow;

BEGIN_MOUNTAIN

enum class FullscreenMode
{
    Windowed,
    Fullscreen,
    Borderless,
    Count
};

constexpr size_t FullscreenModeCount = static_cast<size_t>(FullscreenMode::Count);

/// @brief A wrapper for the main window
class MOUNTAIN_API Window
{
    STATIC_CLASS(Window)

    friend class Renderer;
    
public:
    /// @brief Gets the screen position in pixels of the window
    /// @return Position
    [[nodiscard]]
    static Vector2i GetPosition();

    static void SetPosition(Vector2i newPosition);

    /// @brief Gets the size in pixels of the window
    /// @return Size
    [[nodiscard]]
    static Vector2i GetSize();

    static void SetSize(Vector2i newSize);

    /// @brief Gets whether the window should close
    [[nodiscard]]
    static bool_t GetShouldClose();

    /// @brief Sets whether the window should close
    static void SetShouldClose(bool_t newShouldClose);

    /// @brief Polls the events of the window
    static void PollEvents();

    /// @brief Sets the window to be the current context
    static void MakeContextCurrent();
    
    /// @brief Gets the native handle of the window
    /// @return Native handle
    [[nodiscard]]
    static GLFWwindow* GetHandle();

    /// @brief Sets whether the window should be visible or hidden.
    static void SetVisible(bool_t newVisible);

    /// @brief Sets the icon for the window
    /// @param icon Icon
    static void SetIcon(Pointer<Texture> icon);

    /// @brief Handles hiding or displaying the cursor
    /// @param value @c true hides, @c false displays
    static void SetCursorHidden(bool_t value);

    /// @brief Sets the mouse cursor position in screen space.
    static void SetCursorPosition(Vector2 newPosition);
    
    static void SetVSync(bool_t vsync);

    static void SwapBuffers();

    static FullscreenMode GetFullscreenMode();

    static void SetFullscreenMode(FullscreenMode newMode);

    static uint32_t GetCurrentScreen();

private:
    /// @brief Native window handle
    static inline GLFWwindow* m_Window = nullptr;

    static inline FullscreenMode m_FullscreenMode = FullscreenMode::Windowed;

    static inline uint32_t m_CurrentScreen;

    static inline Vector2i m_Position;
    static inline Vector2i m_Size;

    static inline bool_t m_Visible;

    /// @brief Initializes the window
    static void Initialize(const char_t* windowTitle, Vector2i windowSize, bool_t vsync, const OpenGlVersion &glVersion);

    /// @brief Terminates the window
    static void Shutdown();

    static void UpdateFields();

    static void UpdateCurrentScreen();
};
    
END_MOUNTAIN
