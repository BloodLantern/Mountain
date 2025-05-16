#pragma once

#include <mutex>
#include <queue>

/// @file ts_queue.hpp
/// @brief Defines the Mountain::TsQueue class.

namespace Mountain
{
    /// @brief Thread-Safe Queue
    ///
    /// @tparam T The type of data to store.
    ///
    /// @see <a href="https://en.cppreference.com/w/cpp/container/queue">std::queue</a>
    template <typename T>
    class TsQueue
    {
    public:
        /// @brief Default constructs a TsQueue.
        TsQueue() = default;

        /// @brief Default destructs the TsQueue.
        ~TsQueue() = default;

        // Prevent copy construction because of the mutex
        DELETE_COPY_MOVE_OPERATIONS(TsQueue)

        /// @brief Gets a reference to the front item in the queue
        /// @returns Item
        T& Front();

        /// @brief Gets a reference to the front item in the queue
        /// @returns Item
        const T& Front() const;

        /// @brief Gets a reference to the back item in the queue
        /// @returns Item
        T& Back();

        /// @brief Gets a reference to the back item in the queue
        /// @returns Item
        const T& Back() const;

        /// @brief Pushes a new item on the back of the queue by copying it
        /// @param item Item
        void Push(const T& item);

        /// @brief Pushes a new item on the back of the queue by moving it
        /// @param item Item
        void Push(T&& item);

        /// @brief Checks if the queue is empty
        /// @returns Empty
        bool Empty();

        /// @brief Get the number of items in the queue
        /// @returns Count
        size_t Count();

        /// @brief Pops the item on the front of the queue
        /// @returns Item
        T Pop();

        /// @brief Clears the queue
        void Clear();

    private:
        // Mutex guarding the queue
        std::mutex m_QueueMutex;

        std::queue<T> m_Queue;
    };
}

#include "Mountain/utils/ts_queue.inl"
