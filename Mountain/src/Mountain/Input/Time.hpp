#pragma once

#include <cmath>

#include "Mountain/Core.hpp"
#include "Mountain/Utils/Optional.hpp"
#include "Mountain/Utils/Stopwatch.hpp"

/// @file time.hpp
/// @brief Defines the Mountain::Time static class.

namespace Mountain
{
    /// @brief Defines utility functions to access information regarding time
    class Time
    {
        STATIC_CLASS(Time)

    public:
        MOUNTAIN_API static inline f32 timeScale = 1.f;

        /// @brief The maximum delta time value. This is mainly to prevent clipping through collisions during a lag spike.
        MOUNTAIN_API static inline f32 maxDeltaTime = 0.1f;

        /// @brief If this is above 0, the game updates will be frozen for that amount of time
        MOUNTAIN_API static inline f32 freezeTimer = 0.f;

        MOUNTAIN_API static inline Optional<f64> targetFps;

        // TODO - Add backgroundTargetFps for when the window is unfocused

        /// @brief Get the total elapsed time
        STATIC_GETTER(f32, TotalTime, m_TotalTime)

        /// @brief Get the last total elapsed time
        STATIC_GETTER(f32, LastTotalTime, m_LastTotalTime)

        /// @brief Get the total unscaled elapsed time
        STATIC_GETTER(f32, TotalTimeUnscaled, m_TotalTimeUnscaled)

        /// @brief Get the last total unscaled elapsed time
        STATIC_GETTER(f32, LastTotalTimeUnscaled, m_LastTotalTimeUnscaled)

        /// @brief Get the time elapsed since the last frame
        STATIC_GETTER(f32, DeltaTime, m_DeltaTime)

        /// @brief Get the unscaled delta time
        STATIC_GETTER(f32, DeltaTimeUnscaled, m_DeltaTimeUnscaled)

        /// @brief Get the total frame count
        STATIC_GETTER(u64, TotalFrameCount, m_TotalFrameCount)

        /// @brief Get the target delta time.
        ///
        /// This is either @code 1.f / GetTargetFps()@endcode
        /// if @code GetTargetFps().has_value()@endcode is @c true,
        /// otherwise @code 1.f / Screen::GetRefreshRate()@endcode
        /// if @c Window::GetVSync() is @c true,
        /// or @c 0.f if both are @c false.
        ///
        /// @see GetDeltaTime()
        MOUNTAIN_API static f32 GetTargetDeltaTime();

        /// @brief Get how much time the last frame took. If this is greater or equal to the delta time, it means that the game is lagging.
        STATIC_GETTER(f32, LastFrameDuration, m_LastFrameDuration)

        /// @brief Returns @c true on the given time interval
        /// @details This is shorthand for writing @code Calc::OnInterval(Time::GetTotalTime(),
        /// Time::GetLastTotalTime(), interval)@endcode
        /// @param interval The time interval between each @c true result
        /// @return @c true if the interval has passed, @c false otherwise
        ATTRIBUTE_NODISCARD
        MOUNTAIN_API static bool OnInterval(f32 interval);

        /// @brief Returns @c true on the given time interval
        /// @details This is shorthand for writing @code Calc::OnInterval(Time::GetTotalTimeUnscaled(),
        /// Time::GetLastTotalTimeUnscaled(), interval)@endcode
        /// @param interval The time interval between each @c true result
        /// @return @c true if the interval has passed, @c false otherwise
        ATTRIBUTE_NODISCARD
        MOUNTAIN_API static bool OnIntervalUnscaled(f32 interval);

    private:
        MOUNTAIN_API static inline f32 m_TotalTime = 0.f;
        MOUNTAIN_API static inline f32 m_LastTotalTime = 0.f;
        MOUNTAIN_API static inline f32 m_TotalTimeUnscaled = 0.f;
        MOUNTAIN_API static inline f32 m_LastTotalTimeUnscaled = 0.f;
        MOUNTAIN_API static inline f32 m_DeltaTime = 0.f;
        MOUNTAIN_API static inline f32 m_DeltaTimeUnscaled = 0.f;
        MOUNTAIN_API static inline u64 m_TotalFrameCount = 0;

        MOUNTAIN_API static inline f32 m_LastFrameDuration = 0.f;

        MOUNTAIN_API static inline Stopwatch m_Stopwatch;

        static void Initialize();

        /// @brief Updates the time variables
        /// @remark This is called at the beginning of a frame by the Game class
        static void Update();
        /// @brief Used to wait between frames
        /// @remark This is called at the end of a frame by the Game class.
        /// @remark This function might not wait if the game is not keeping up, that is
        /// if the delta time between frames is greater than what the targetFps/VSync aim for.
        static void WaitForNextFrame();
        /// @brief Sleeps for <i>at least</i> the given amount of time.
        /// @param milliseconds The minimum amount of time to sleep, in milliseconds.
        /// @return The actual sleep duration, in milliseconds.
        static f64 SleepFor(f64 milliseconds);

        // Calls Initialize, Shutdown, Update and WaitForNextFrame
        friend class Game;
    };
}
