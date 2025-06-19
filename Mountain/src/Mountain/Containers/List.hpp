#pragma once

#include "Mountain/Core.hpp"
#include "Mountain/Containers/ContiguousIterator.hpp"
#include "Mountain/Exceptions/ThrowHelper.hpp"
#include "Mountain/Utils/Utils.hpp"

/// @file List.hpp
/// @brief Defines the Mountain::List class.

namespace Mountain
{
    // ReSharper disable once CppPolymorphicClassWithNonVirtualPublicDestructor
    /// @brief A dynamic array implementation.
    ///
    /// A more user-friendly list than @c std::vector, based on how @c %List is done in C#
    /// The internal structure and workings are similar to how std::vector works, it uses a capacity that grows exponentially based on powers of 2
    ///
    /// @tparam T Type stored
    ///
    /// @see <a href="https://en.cppreference.com/w/cpp/container/vector">std::vector</a>
    /// @see <a href="https://learn.microsoft.com/en-us/dotnet/api/system.collections.generic.list-1">C# List</a>
    template <typename T>
    class List
    {
    public:
        /// @brief The type of the List<T>. Refers to T.
        using Type = T;
        using Iterator = ContiguousIterator<T>;

        void Add(T&& element);

        void Add(const T& element);

        template <typename... Args>
        T& Emplace(Args&&... args);

        void Resize(size_t newSize);

        void Resize(size_t newSize, const T& newElementsValue);

        void Reserve(size_t newMinimumCapacity);

        size_t GetCapacity() const;

        void Shrink();

        void Clear();

        bool_t IsEmpty() const;

        void Remove(const T& value);

        void RemoveAt(size_t index);

        /// @brief Get the element at the given index with bounds checking.
        [[nodiscard]]
        T& At(size_t index) const;

        /// @brief Get the size of the list.
        [[nodiscard]]
        size_t GetSize() const noexcept;

        [[nodiscard]]
        T* GetData() const noexcept;

        /// @brief Get the element at the given index without bounds checking.
        [[nodiscard]]
        T& operator[](size_t index) const noexcept;

        [[nodiscard]]
        Iterator GetBeginIterator() const noexcept;

        [[nodiscard]]
        Iterator GetEndIterator() const noexcept;

        [[nodiscard]]
        Iterator begin() const noexcept;

        [[nodiscard]]
        Iterator end() const noexcept;

    private:
        T* m_Data = nullptr;
        size_t m_Size = 0;
        size_t m_Capacity = 0;

        void Reallocate(size_t targetCapacity);
        void IncreaseCapacity();

        CHECK_REQUIREMENT(List, Requirements::Container);
        CHECK_REQUIREMENT(List, Requirements::Enumerable);
    };
}

// Start of List.inl

namespace Mountain
{
    template <typename T>
    void List<T>::Add(T&& element)
    {
        if (m_Size == m_Capacity)
            IncreaseCapacity();

        m_Data[m_Size++] = std::move(element);
    }

    template <typename T>
    void List<T>::Add(const T& element)
    {
        if (m_Size == m_Capacity)
            IncreaseCapacity();

        m_Data[m_Size++] = element;
    }

    template <typename T>
    template <typename ... Args>
    T& List<T>::Emplace(Args&&... args)
    {
        if (m_Size == m_Capacity)
            IncreaseCapacity();

        return m_Data[m_Size++] = T{std::forward<Args>(args)...};
    }

    template <typename T>
    void List<T>::Resize(const size_t newSize) { Resize(newSize, {}); }

    template <typename T>
    void List<T>::Resize(const size_t newSize, const T& newElementsValue)
    {
        if (m_Size == newSize)
            return;

        if (m_Size > newSize)
        {
            // Container size is decreasing, we need to destroy elements
            const size_t difference = m_Size - newSize;
            for (size_t i = 1; i <= difference; i++)
                m_Data[m_Size - i].~T();
        }
        else // m_Size < newSize
        {
            // Container size is increasing, we need to emplace the new elements
            const size_t difference = newSize - m_Size;
            for (size_t i = 0; i < difference; i++)
                m_Data[m_Size + i] = newElementsValue;
        }

        m_Size = newSize;
    }

    template <typename T>
    void List<T>::Reserve(const size_t newMinimumCapacity)
    {
        if (m_Capacity >= newMinimumCapacity)
            return;

        const size_t targetCapacity = std::bit_ceil(newMinimumCapacity);

        Reallocate(targetCapacity);

        m_Capacity = targetCapacity;
    }

    template <typename T>
    size_t List<T>::GetCapacity() const { return m_Capacity; }

    template <typename T>
    void List<T>::Shrink()
    {
        if (m_Size == m_Capacity)
            return;

        Reallocate(m_Size);
    }

    template <typename T>
    void List<T>::Clear()
    {
    }

    template <typename T>
    bool_t List<T>::IsEmpty() const { return m_Size == 0; }

    template <typename T>
    void List<T>::Remove(const T& value)
    {
    }

    template <typename T>
    void List<T>::RemoveAt(size_t index)
    {
    }

    template <typename T>
    T& List<T>::At(const size_t index) const
    {
        if (index >= m_Size)
            THROW(ArgumentOutOfRangeException{"Cannot get the element at index >= Size", "index"});
        return m_Data[index];
    }

    template <typename T>
    size_t List<T>::GetSize() const noexcept { return m_Size; }

    template <typename T>
    T* List<T>::GetData() const noexcept { return m_Data; }

    template <typename T>
    T& List<T>::operator[](const size_t index) const noexcept { return m_Data[index]; }

    template <typename T>
    typename List<T>::Iterator List<T>::GetBeginIterator() const noexcept
    {
        return Iterator{ .m_FirstElement = m_Data, .m_ContainerSize = m_Size };
    }

    template <typename T>
    typename List<T>::Iterator List<T>::GetEndIterator() const noexcept
    {
        return Iterator{ .m_FirstElement = m_Data, .m_Index = m_Size, .m_ContainerSize = m_Size };
    }

    template <typename T>
    typename List<T>::Iterator List<T>::begin() const noexcept { return GetBeginIterator(); }

    template <typename T>
    typename List<T>::Iterator List<T>::end() const noexcept { return GetEndIterator(); }

    template <typename T>
    void List<T>::Reallocate(const size_t targetCapacity)
    {
        const size_t targetCapacityBytes = targetCapacity * sizeof(T);

        T* newData = static_cast<T*>(std::malloc(targetCapacityBytes));
        std::memcpy(newData, m_Data, std::min(m_Capacity * sizeof(T), targetCapacityBytes));
        std::free(m_Data);
        m_Data = newData;
    }

    template <typename T>
    void List<T>::IncreaseCapacity() { Reserve(m_Capacity * 2); }
}
