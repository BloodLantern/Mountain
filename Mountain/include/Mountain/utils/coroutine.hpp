#pragma once

#include <chrono>
#include <coroutine>
#include <functional>
#include <unordered_map>

#include "Mountain/core.hpp"
#include "Mountain/utils/guid.hpp"

/// @file coroutine.hpp
/// @brief Defines the Coroutine class.

BEGIN_MOUNTAIN

// Everything named using the snake_case convention in this file is required by C++20 coroutines: https://en.cppreference.com/w/cpp/language/coroutines

/// @brief Wrapper around C++20 Coroutines.
/// @see <a href="https://en.cppreference.com/w/cpp/language/coroutines">C++20 Coroutines</a>
class Coroutine
{
    struct Awaitable;
    
public:
    /// @brief Default duration type for Coroutine wait, equivalent to floating-point seconds
    using AwaitType = std::chrono::duration<double_t>;

    /// @brief Promise type for C++20 coroutines.
    ///
    /// This is necessary for the coroutine to function and needs to be public but mustn't be used
    /// manually.
    struct promise_type
    {
        /// @brief The last @c co_await value
        AwaitType awaitValue = AwaitType::zero();

        /// @brief Whether the Coroutine reached either a @c co_return statement, or the end of the function body.
        bool_t finished = false;

        /// @brief Returns the object that will be returns to the caller of a CoroutineFunc
        MOUNTAIN_API Coroutine get_return_object();

        /// @brief Empty implementation
        MOUNTAIN_API std::suspend_always initial_suspend();

        /// @brief Empty implementation
        MOUNTAIN_API std::suspend_always final_suspend() noexcept;

        /// @brief Logs the exception and rethrows it
        MOUNTAIN_API void unhandled_exception();

        /// @brief Called when @c co_return is used in a Coroutine body. Sets @c finished to @c true.
        MOUNTAIN_API void return_void();

        /// @brief Converts a @c AwaitType value to an @c Awaitable. Called when @c co_await is used with an @c AwaitType value.
        MOUNTAIN_API Awaitable await_transform(const AwaitType& duration);

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

    MOUNTAIN_API static Guid Start(const Coroutine& coroutine);

    /// @brief Starts a coroutine using an existing coroutine Guid.
    ///
    /// This stops the existing coroutine if it is still running and assigns the guid with a newly created one.
    MOUNTAIN_API static void Start(const Coroutine& coroutine, Guid* coroutineId);

    MOUNTAIN_API static void UpdateAll();

    MOUNTAIN_API static void Stop(const Guid& coroutineId);

    MOUNTAIN_API static void StopAll();

    MOUNTAIN_API static bool_t IsRunning(const Guid& coroutineId);

    MOUNTAIN_API static bool_t IsRunningAndNotEmpty(const Guid& coroutineId);

    MOUNTAIN_API static size_t GetRunningCount();

    // ReSharper disable once CppNonExplicitConvertingConstructor
    /// @brief Constructs a new Coroutine from the given handle.
    ///
    /// This can be obtained as easily as this:
    /// @code
    /// Coroutine Function()
    /// {
    ///     using std::chrono_literals;
    ///     
    ///     // Do something
    ///     
    ///     co_await 750ms;
    ///
    ///     // Do something else
    /// }
    ///
    /// // Somewhere else
    /// Coroutine routine = Function();
    ///
    /// // Here you can do whatever you want with the Coroutine
    /// routine.Resume();
    /// @endcode
    MOUNTAIN_API Coroutine(HandleType handle);

    /// @brief Resumes the Coroutine.
    MOUNTAIN_API void Resume() const;

    /// @brief Returns whether the Coroutine finished its execution.
    /// @see promise_type::finished
    MOUNTAIN_API bool_t Finished() const;

    /// @brief Destroys the Coroutine. It can't be resumed afterwards.
    MOUNTAIN_API void Destroy() const;

    /// @brief Returns the Guid of this Coroutine.
    MOUNTAIN_API Guid GetId() const;

private:
    HandleType m_Handle;

    Guid m_Id;
    
    MOUNTAIN_API Coroutine(const Guid& guid, HandleType handle);
};

/// @brief Coroutine function prototype.
template <typename... Args>
using CoroutineFunc = std::function<Coroutine(Args...)>;

END_MOUNTAIN
