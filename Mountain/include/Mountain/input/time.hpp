#pragma once

#include <cmath>
#include <optional>

#include "Mountain/core.hpp"
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
        STATIC_GETTER(float_t, TotalTime, m_TotalTime)

        /// @brief Get the last total elapsed time
        STATIC_GETTER(float_t, LastTotalTime, m_LastTotalTime)

        /// @brief Get the total unscaled elapsed time
        STATIC_GETTER(float_t, TotalTimeUnscaled, m_TotalTimeUnscaled)

        /// @brief Get the last total unscaled elapsed time
        STATIC_GETTER(float_t, LastTotalTimeUnscaled, m_LastTotalTimeUnscaled)

        /// @brief Get the time elapsed since the last frame
        STATIC_GETTER(float_t, DeltaTime, m_DeltaTime)

        /// @brief Get the unscaled delta time
        STATIC_GETTER(float_t, DeltaTimeUnscaled, m_DeltaTimeUnscaled)

        /// @brief Get the total frame count
        STATIC_GETTER(uint64_t, TotalFrameCount, m_TotalFrameCount)

        /// @brief Get the target delta time.
        ///
        /// This is either @code 1.f / GetTargetFps()@endcode
        /// if @code GetTargetFps().has_value()@endcode is @c true,
        /// otherwise @code 1.f / Screen::GetRefreshRate()@endcode
        /// if Window::GetVSync() is @c true,
        /// or @c 0.f if both are @c false.
        ///
        /// @see GetDeltaTime()
        MOUNTAIN_API static float_t GetTargetDeltaTime();

        /// @brief Get how much time the last frame took. If this is equal to the delta time, then the game is lagging.
        STATIC_GETTER(float_t, LastFrameDuration, m_LastFrameDuration)

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
        /// if the delta time between frames is greater than what the targetFps/VSync aim for.
        static void WaitForNextFrame();
        static double_t SleepFor(double_t milliseconds);

        // Calls Initialize, Shutdown, Update and WaitForNextFrame
        friend class Game;
    };
}
