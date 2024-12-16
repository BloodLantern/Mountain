#pragma once

#include <cmath>
#include <optional>

#include "Mountain/core.hpp"

/// @file time.hpp
/// @brief Defines the Mountain::Time static class.

namespace Mountain
{
    /// @brief Defines utility functions to access information regarding time
    class Time
    {
        STATIC_CLASS(Time)

        friend class Game;

    public:
        MOUNTAIN_API static inline float_t timeScale = 1.f;

        /// @brief The maximum delta time value. This is to prevent clipping during a lag spike
        MOUNTAIN_API static inline float_t maxDeltaTime = 0.1f;

        /// @brief If this is above 0, the game updates will be frozen for that amount of time
        MOUNTAIN_API static inline float_t freezeTimer = 0.f;

        /// @brief Get the total elapsed time
        MOUNTAIN_API static float_t GetTotalTime();

        /// @brief Get the last total elapsed time
        MOUNTAIN_API static float_t GetLastTotalTime();

        /// @brief Get the total unscaled elapsed time
        MOUNTAIN_API static float_t GetTotalTimeUnscaled();

        /// @brief Get the last total unscaled elapsed time
        MOUNTAIN_API static float_t GetLastTotalTimeUnscaled();

        /// @brief Get the time elapsed since last frame
        MOUNTAIN_API static float_t GetDeltaTime();

        /// @brief Get the unscaled delta time
        MOUNTAIN_API static float_t GetDeltaTimeUnscaled();

        /// @brief Get the total frame count
        MOUNTAIN_API static uint64_t GetTotalFrameCount();

        /// @brief Get the target FPS. If this isn't set, the game is using vertical synchronization.
        MOUNTAIN_API static std::optional<uint16_t> GetTargetFps();

        /// @brief Set the target FPS. If the given value is empty, will use vertical synchronization instead.
        MOUNTAIN_API static void SetTargetFps(std::optional<uint16_t> newTargetFps);

        /// @brief Get how much time the last frame took. If this is equal to the delta time, then the game is lagging.
        MOUNTAIN_API static float_t GetLastFrameDuration();

        /// @brief Sleep as long as possible without exceeding the specified period
        MOUNTAIN_API static void SleepForNoMoreThan(double_t milliseconds);

    private:
        MOUNTAIN_API static inline float_t m_TotalTime = 0.f;
        MOUNTAIN_API static inline float_t m_LastTotalTime = 0.f;
        MOUNTAIN_API static inline float_t m_TotalTimeUnscaled = 0.f;
        MOUNTAIN_API static inline float_t m_LastTotalTimeUnscaled = 0.f;
        MOUNTAIN_API static inline float_t m_DeltaTime = 0.f;
        MOUNTAIN_API static inline float_t m_DeltaTimeUnscaled = 0.f;
        MOUNTAIN_API static inline uint64_t m_TotalFrameCount = 0;
        MOUNTAIN_API static inline std::optional<uint16_t> m_TargetFps;

        MOUNTAIN_API static inline float_t m_LastFrameDuration = 0.f;

        MOUNTAIN_API static inline double_t m_LowestSleepThreshold = 0.0;

        static void Initialize();

        /// @brief Updates the time variables using GLFW.
        ///        This function should be called exactly once each frame.
        static void Update();
        static void WaitForNextFrame();

        static double_t GetCurrentTimerResolution();
    };
}
