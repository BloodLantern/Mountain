#pragma once

#include <cmath>
#include <optional>

#include "Mountain/core.hpp"
#include "Mountain/game.hpp"
#include "Mountain/utils/stopwatch.hpp"

/// @file time.hpp
/// @brief Defines the Mountain::Time static class.

namespace Mountain
{
    /// @brief Defines utility functions to access information regarding time
    class Time
    {
        STATIC_CLASS(Time)

    public:
        MOUNTAIN_API static inline float_t timeScale = 1.f;

        /// @brief The maximum delta time value. This is to prevent clipping during a lag spike.
        MOUNTAIN_API static inline float_t maxDeltaTime = 0.1f;

        /// @brief If this is above 0, the game updates will be frozen for that amount of time
        MOUNTAIN_API static inline float_t freezeTimer = 0.f;

        MOUNTAIN_API static inline std::optional<double_t> targetFps;

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

        /// @brief Get the target delta time.
        ///
        /// This is either @code 1.f / GetTargetFps()@endcode if @code GetTargetFps().has_value()@endcode is @c true or @code 1.f / Screen::GetRefreshRate()@endcode otherwise.
        ///
        /// @see GetDeltaTime()
        MOUNTAIN_API static float_t GetTargetDeltaTime();

        /// @brief Get how much time the last frame took. If this is equal to the delta time, then the game is lagging.
        MOUNTAIN_API static float_t GetLastFrameDuration();

        // TODO - Add OnInterval function

    private:
        MOUNTAIN_API static inline float_t m_TotalTime = 0.f;
        MOUNTAIN_API static inline float_t m_LastTotalTime = 0.f;
        MOUNTAIN_API static inline float_t m_TotalTimeUnscaled = 0.f;
        MOUNTAIN_API static inline float_t m_LastTotalTimeUnscaled = 0.f;
        MOUNTAIN_API static inline float_t m_DeltaTime = 0.f;
        MOUNTAIN_API static inline float_t m_DeltaTimeUnscaled = 0.f;
        MOUNTAIN_API static inline uint64_t m_TotalFrameCount = 0;

        MOUNTAIN_API static inline float_t m_LastFrameDuration = 0.f;

        MOUNTAIN_API static inline Stopwatch m_Stopwatch;

        static void Initialize();
        static void Shutdown();

        /// @brief Updates the time variables
        /// @remark This is called at the beginning of a frame by the Game class
        static void Update();
        /// @brief Used to wait between frames
        /// @remark This is called at the end of a frame by the Game class.
        /// @remark This function might not wait if the game is not keeping up, that is
        /// if the delta time between frames is greater than what the target FPS/VSync aim for.
        static void WaitForNextFrame();
        static double_t SleepFor(double_t milliseconds);

        friend void Game::Initialize();
        friend bool_t Game::NextFrame();
    };
}
