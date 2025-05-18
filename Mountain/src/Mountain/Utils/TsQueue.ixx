module;

#include "Mountain/Core.hpp"

export module Mountain.Utils:TsQueue;

import std;

/// @file TsQueue.ixx
/// @brief Defines the Mountain::TsQueue class.

export namespace Mountain
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

// Start of TsQueue.inl

namespace Mountain
{
    template <typename T>
    T& TsQueue<T>::Front()
    {
        std::scoped_lock lock(m_QueueMutex);
        return m_Queue.front();
    }

    template <typename T>
    const T& TsQueue<T>::Front() const
    {
        std::scoped_lock lock(m_QueueMutex);
        return m_Queue.front();
    }

    template <typename T>
    T& TsQueue<T>::Back()
    {
        std::scoped_lock lock(m_QueueMutex);
        return m_Queue.back();
    }

    template <typename T>
    const T& TsQueue<T>::Back() const
    {
        std::scoped_lock lock(m_QueueMutex);
        return m_Queue.back();
    }

    template <typename T>
    void TsQueue<T>::Push(const T& item)
    {
        std::scoped_lock lock(m_QueueMutex);
        m_Queue.push(item);
    }

    template<typename T>
    void TsQueue<T>::Push(T&& item)
    {
        std::scoped_lock lock(m_QueueMutex);
        m_Queue.push(std::move(item));
    }

    template <typename T>
    bool TsQueue<T>::Empty()
    {
        std::scoped_lock lock(m_QueueMutex);
        return m_Queue.empty();
    }

    template <typename T>
    size_t TsQueue<T>::Count()
    {
        std::scoped_lock lock(m_QueueMutex);
        return m_Queue.size();
    }

    template <typename T>
    T TsQueue<T>::Pop()
    {
        std::scoped_lock lock(m_QueueMutex);
        T item = std::move(m_Queue.front());
        m_Queue.pop();
        return item;
    }

    template <typename T>
    void TsQueue<T>::Clear()
    {
        std::scoped_lock lock(m_QueueMutex);
        while (!m_Queue.empty())
            m_Queue.pop();
    }
}
