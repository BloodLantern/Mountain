#pragma once

#include <chrono>
#include <coroutine>
#include <functional>
#include <unordered_map>

#include "Mountain/Core.hpp"
#include "Mountain/Utils/Guid.hpp"

/// @file coroutine.hpp
/// @brief Defines the Coroutine class.

namespace Mountain
{
    // Everything named using the snake_case convention in this file is required by C++20 coroutines: https://en.cppreference.com/w/cpp/language/coroutines

    /// @brief Wrapper around C++20 Coroutines.
    ///
    /// ### Usage
    /// Example Coroutine usage:
    /// @code
    /// Coroutine Function()
    /// {
    ///     using std::chrono_literals;
    ///
    ///     // Do something
    ///
    ///     // Wait for 750 milliseconds
    ///     co_await 750ms;
    ///
    ///     // Do something else
    ///
    ///     // Wait for 0.5 seconds
    ///     co_await 0.5f;
    ///
    ///     // Wait for next resume (most of the time, this is the next frame)
    ///     co_yield nullptr;
    ///
    ///     // Exit the Coroutine at any moment using co_return
    ///     if (condition)
    ///         co_return;
    /// }
    ///
    /// // Somewhere else
    /// Coroutine routine = Function();
    ///
    /// // Here you can do whatever you want with the Coroutine
    /// routine.Resume();
    /// @endcode
    ///
    /// Instead of manually resuming the Coroutine, the framework can do it for you:
    /// @code
    /// Guid id = Coroutine::Start(Function());
    /// @endcode
    ///
    /// And the Coroutine will be resumed automatically each frame.
    /// Use the returned @c Guid with the static functions in the Coroutine class.
    ///
    /// @see <a href="https://en.cppreference.com/w/cpp/language/coroutines">C++20 Coroutines</a>
    class Coroutine
    {
        struct Awaitable;

    public:
        /// @brief Promise type for C++20 coroutines.
        ///
        /// This is necessary for the coroutine to function and needs to be public but shouldn't be used
        /// manually.
        struct promise_type
        {
            /// @brief The last @c co_await value
            TimeSpan awaitValue = TimeSpan::Zero();

            /// @brief Returns the object that will be returns to the caller of a CoroutineFunc
            MOUNTAIN_API Coroutine get_return_object();

            /// @brief Empty implementation
            MOUNTAIN_API std::suspend_always initial_suspend();

            /// @brief Empty implementation
            MOUNTAIN_API std::suspend_always final_suspend() noexcept;

            /// @brief Logs the exception and rethrows it
            ATTRIBUTE_NORETURN
            MOUNTAIN_API void unhandled_exception();

            /// @brief Called when @c co_return is used in a Coroutine body. Empty implementation
            MOUNTAIN_API void return_void();

            /// @brief Converts a @c TimeSpan value to an @c Awaitable. Called when @c co_await is used with a @c TimeSpan value.
            MOUNTAIN_API Awaitable await_transform(const TimeSpan& duration);

            /// @brief Converts an @c std::chrono::duration value to an @c Awaitable.
            /// Called when @c co_await is used with an @c std::chrono::duration value.
            MOUNTAIN_API Awaitable await_transform(const std::chrono::duration<double_t>& duration);

            /// @brief Converts a @c float_t value to an @c Awaitable. Called when @c co_await is used with a @c float_t value.
            MOUNTAIN_API Awaitable await_transform(float_t duration);

            /// @brief Yields the coroutine using a @c nullptr value. The coroutine will be resumed on the next frame.
            MOUNTAIN_API std::suspend_always yield_value(nullptr_t);
        };

    private:
        struct Awaitable
        {
            /// @brief Returns @c false if @c await_suspend should be called
            MOUNTAIN_API bool_t await_ready();

            /// @brief Empty implementation
            MOUNTAIN_API void await_suspend(std::coroutine_handle<promise_type>);

            /// @brief Empty implementation
            MOUNTAIN_API void await_resume();
        };

        MOUNTAIN_API static inline std::unordered_map<Guid, Coroutine> m_RunningRoutines;

    public:
        /// @brief The coroutine handle type.
        using HandleType = std::coroutine_handle<promise_type>;

        /// @brief Starts a coroutine, assigning it a @c Guid.
        /// @details This will run the beginning of the coroutine body. If it
        /// finishes without yielding, this function returns @c Guid::Empty().
        /// Otherwise, it returns the @c Guid that was assigned to the coroutine.
        MOUNTAIN_API static Guid Start(Coroutine&& coroutine);

        /// @brief Starts a coroutine using an existing coroutine @c Guid.
        /// @details This stops the existing coroutine if it is still running
        /// and assigns the guid with a newly created one.
        MOUNTAIN_API static void Start(Coroutine&& coroutine, Guid* coroutineId);

        MOUNTAIN_API static void UpdateAll();

        MOUNTAIN_API static void Stop(const Guid& coroutineId);

        MOUNTAIN_API static void StopAll();

        ATTRIBUTE_NODISCARD
        MOUNTAIN_API static bool_t IsRunning(const Guid& coroutineId);

        ATTRIBUTE_NODISCARD
        MOUNTAIN_API static bool_t IsRunningAndNotEmpty(const Guid& coroutineId);

        ATTRIBUTE_NODISCARD
        MOUNTAIN_API static size_t GetRunningCount();

        bool_t useUnscaledDeltaTime = false;

        MOUNTAIN_API Coroutine() = default;

        /// @brief Constructs a new Coroutine from the given handle.
        ATTRIBUTE_NODISCARD
        // ReSharper disable once CppNonExplicitConvertingConstructor
        MOUNTAIN_API Coroutine(HandleType handle);

        MOUNTAIN_API Coroutine& operator=(HandleType handle) noexcept;

        MOUNTAIN_API ~Coroutine();

        // Delete copy operations
        Coroutine(const Coroutine&) = delete;
        Coroutine& operator=(const Coroutine&) = delete;

        // Define move operations
        ATTRIBUTE_NODISCARD
        MOUNTAIN_API Coroutine(Coroutine&& other) noexcept;
        MOUNTAIN_API Coroutine& operator=(Coroutine&& other) noexcept;

        /// @brief Resumes the Coroutine.
        /// @remark If @c Valid() is @c false, this is undefined behavior. Consider using @c ResumeSafe() instead.
        MOUNTAIN_API void Resume() const;

        /// @brief Safely resumes the Coroutine by first checking if @c Valid() is @c true.
        /// @see @c Resume()
        MOUNTAIN_API void ResumeSafe() const;

        /// @brief Returns whether the Coroutine finished its execution.
        /// @remark If @c Valid() is @c false, this is undefined behavior. Consider using @c FinishedSafe() instead.
        ATTRIBUTE_NODISCARD
        MOUNTAIN_API bool_t Finished() const;

        /// @brief Safely returns whether the Coroutine finished its execution by first checking if @c Valid() is @c true.
        ///
        /// If @c Valid() is @c false, returns @c false.
        ///
        /// @see @c Finished()
        ATTRIBUTE_NODISCARD
        MOUNTAIN_API bool_t FinishedSafe() const;

        /// @brief Destroys the Coroutine. It can't be resumed afterward.
        /// @remark If @c Valid() is @c false, this is undefined behavior. Consider using @c DestroySafe() instead.
        MOUNTAIN_API void Destroy();

        /// @brief Safely destroys the Coroutine by first checking if @c Valid() is @c true.
        /// @see @c Destroy()
        MOUNTAIN_API void DestroySafe();

        /// @brief Gets whether the Coroutine is valid, e.g. if it hasn't been default-initialized.
        /// @remark This still returns @c true even when the Coroutine is finished.
        ATTRIBUTE_NODISCARD
        MOUNTAIN_API bool_t Valid() const;

        /// @brief Resets the Coroutine.
        /// @warning <b>This does not release the allocated memory</b>, make sure to call @c Destroy() beforehand.
        MOUNTAIN_API void Reset();

        /// @brief Returns the Guid of this Coroutine.
        ATTRIBUTE_NODISCARD
        MOUNTAIN_API Guid GetId() const;

    private:
        HandleType m_Handle;

        Guid m_Id;

        Coroutine(const Guid& guid, HandleType handle);
    };

    /// @brief Coroutine function prototype.
    template <typename... Args>
    using CoroutineFunction = std::function<Coroutine(Args...)>;
}
