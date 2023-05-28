#pragma once

#include <mutex>
#include <functional>
#include <queue>
#include <cassert>

/// <summary>
/// Thread-Safe Queue
/// </summary>
/// <typeparam name="T">The type of data to store</typeparam>
template <typename T>
class TsQueue
{
public:
	// Default constructor
	TsQueue() = default;

	// Prevent copy construction because of the mutex
	TsQueue(const TsQueue<T>&) = delete;

	/// <summary>
	/// Gets a reference to the front item in the queue
	/// </summary>
	/// <returns>Item</returns>
	const T& Front()
	{
		std::scoped_lock lock(mQueueMutex);
		return mQueue.front();
	}

	/// <summary>
	/// Gets a reference to the back item in the queue
	/// </summary>
	/// <returns>Item</returns>
	const T& Back()
	{
		std::scoped_lock lock(mQueueMutex);
		return mQueue.back();
	}

	/// <summary>
	/// Pushes a new item on the back of the queue
	/// </summary>
	/// <param name="item">Item</param>
	void Push(const T& item)
	{
		std::scoped_lock lock(mQueueMutex);
		mQueue.push(std::move(item));
	}

	/// <summary>
	/// Checks if the queue is empty
	/// </summary>
	/// <returns>Empty</returns>
	bool Empty()
	{
		std::scoped_lock lock(mQueueMutex);
		return mQueue.empty();
	}

	/// <summary>
	/// Get the number of items in the queue
	/// </summary>
	/// <returns>Count</returns>
	size_t Count()
	{
		std::scoped_lock lock(mQueueMutex);
		return mQueue.size();
	}

	/// <summary>
	/// Pops the item on the front of the queue
	/// </summary>
	/// <returns>Item</returns>
	T Pop()
	{
		std::scoped_lock lock(mQueueMutex);
		T item = std::move(mQueue.front());
		mQueue.pop();
		return item;
	}

private:
	// Mutex guarding the queue
	std::mutex mQueueMutex;

	std::queue<T> mQueue;
};
