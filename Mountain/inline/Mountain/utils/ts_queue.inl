#pragma once

BEGIN_MOUNTAIN

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

END_MOUNTAIN
