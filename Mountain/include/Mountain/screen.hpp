#pragma once

#include "Mountain/core.hpp"

#include <Maths/vector2i.hpp>

/// @file screen.hpp
/// @brief Defines the Mountain::Screen class.

// ReSharper disable once CppInconsistentNaming
struct GLFWmonitor;
// ReSharper disable once CppInconsistentNaming
struct GLFWvidmode;

BEGIN_MOUNTAIN

/// @brief Represents a screen/monitor
class MOUNTAIN_API Screen
{
    STATIC_CLASS(Screen)
    
public:
    /// @brief Gets the position of the screen
    /// @return Screen position
    static Vector2i GetPosition(int32_t screenIndex = 0);
    
    /// @brief Gets the size of the screen
    /// @return Screen size
    static Vector2i GetSize(int32_t screenIndex = 0);

    /// @brief Gets the refresh rate of the screen
    /// @return Refresh rate
    static int32_t GetRefreshRate(int32_t screenIndex = 0);

    static uint32_t GetScreenCount();

private:
    /// @brief Native handle for the monitors
    static inline GLFWmonitor** m_Monitors = nullptr;
    
    /// @brief Native handle for the monitors
    static inline const GLFWvidmode** m_VideoModes = nullptr;

    static inline uint32_t m_MonitorCount = 0;

    /// @brief Initializes the screen data
    static void Initialize();

    static void Shutdown();

    friend class Window;
};

END_MOUNTAIN
