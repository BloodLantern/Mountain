#pragma once

#include "Mountain/Core.hpp"

#include <Math/vector2i.hpp>

#include <SDL3/SDL_video.h>

/// @file screen.hpp
/// @brief Defines the Mountain::Screen class.

namespace Mountain
{
    /// @brief Represents a screen/monitor
    class MOUNTAIN_API Screen
    {
        STATIC_CLASS(Screen)

    public:
        /// @brief Gets the position of the given screen
        /// @remark If given a negative screen index, will default to @c Window::GetCurrentScreen().
        ATTRIBUTE_NODISCARD
        static Vector2i GetPosition(int32_t screenIndex = -1);

        /// @brief Gets the size of the given screen
        /// @remark If given a negative screen index, will default to @c Window::GetCurrentScreen().
        ATTRIBUTE_NODISCARD
        static Vector2i GetSize(int32_t screenIndex = -1);

        /// @brief Gets the refresh rate of the given screen
        /// @remark If given a negative screen index, will default to @c Window::GetCurrentScreen().
        ATTRIBUTE_NODISCARD
        static float_t GetRefreshRate(int32_t screenIndex = -1);

        STATIC_GETTER(int32_t, ScreenCount, m_MonitorCount)

    private:
        /// @brief Native handle for the monitors
        static inline SDL_DisplayID* m_Monitors = nullptr;

        /// @brief Native handle for the monitors
        static inline const SDL_DisplayMode** m_VideoModes = nullptr;

        static inline int32_t m_MonitorCount = 0;

        /// @brief Initializes the screen data
        static void Initialize();

        static void Shutdown();

        friend class Window;
    };
}
