#pragma once

#include <cmath>

#include "core.hpp"

/// @file time.hpp
/// @brief Defines the Mountain::Time static class.

BEGIN_MOUNTAIN

// TODO - Add a target delta time for fixed FPS (60FPS on a 144Hz screen for example)

/// @brief Defines utility functions to access information regarding time
class Time
{
    STATIC_CLASS(Time)

    friend class Game;

public:
    MOUNTAIN_API static inline float_t timeScale = 1.f;
    
    /// @brief Gets the total elapsed time
    MOUNTAIN_API static float_t GetTotalTime();

    /// @brief Gets the last total elapsed time
    MOUNTAIN_API static float_t GetLastTotalTime();
    
    /// @brief Gets the total unscaled elapsed time
    MOUNTAIN_API static float_t GetTotalTimeUnscaled();

    /// @brief Gets the last total unscaled elapsed time
    MOUNTAIN_API static float_t GetLastTotalTimeUnscaled();
    
    /// @brief Gets the delta time
    MOUNTAIN_API static float_t GetDeltaTime();
    
    /// @brief Gets the unscaled delta time
    MOUNTAIN_API static float_t GetDeltaTimeUnscaled();

    /// @brief Gets the total frame count
    MOUNTAIN_API static uint64_t GetTotalFrameCount();

private:
    MOUNTAIN_API static inline float_t m_TotalTime = 0.f;
    MOUNTAIN_API static inline float_t m_LastTotalTime = 0.f;
    MOUNTAIN_API static inline float_t m_TotalTimeUnscaled = 0.f;
    MOUNTAIN_API static inline float_t m_LastTotalTimeUnscaled = 0.f;
    MOUNTAIN_API static inline float_t m_DeltaTime = 0.f;
    MOUNTAIN_API static inline float_t m_DeltaTimeUnscaled = 0.f;
    MOUNTAIN_API static inline uint64_t m_TotalFrameCount = 0;
    
    /// @brief Updates the time variables using GLFW.
    ///        This function should be called exactly once each frame.
    static void Update();
};

END_MOUNTAIN
