﻿#pragma once

#include "Mountain/Core.hpp"

#include <Math/vector2i.hpp>

/// @file screen.hpp
/// @brief Defines the Mountain::Screen class.

// ReSharper disable once CppInconsistentNaming
struct GLFWmonitor;
// ReSharper disable once CppInconsistentNaming
struct GLFWvidmode;

namespace Mountain
{
    /// @brief Represents a screen/monitor
    class MOUNTAIN_API Screen
    {
        STATIC_CLASS(Screen)

    public:
        /// @brief Gets the position of the given screen
        /// @remark If given a negative screen index, will default to @c Window::GetCurrentScreen().
        static Vector2i GetPosition(int32_t screenIndex = -1);

        /// @brief Gets the size of the given screen
        /// @remark If given a negative screen index, will default to @c Window::GetCurrentScreen().
        static Vector2i GetSize(int32_t screenIndex = -1);

        /// @brief Gets the refresh rate of the given screen
        /// @remark If given a negative screen index, will default to @c Window::GetCurrentScreen().
        static int32_t GetRefreshRate(int32_t screenIndex = -1);

        STATIC_GETTER(int32_t, ScreenCount, m_MonitorCount)

    private:
        /// @brief Native handle for the monitors
        static inline GLFWmonitor** m_Monitors = nullptr;

        /// @brief Native handle for the monitors
        static inline const GLFWvidmode** m_VideoModes = nullptr;

        static inline int32_t m_MonitorCount = 0;

        /// @brief Initializes the screen data
        static void Initialize();

        static void Shutdown();

        friend class Window;
    };
}
