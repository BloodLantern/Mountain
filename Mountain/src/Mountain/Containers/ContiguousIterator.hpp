#pragma once

#include "Mountain/Core.hpp"
#include "Mountain/Utils/Requirements.hpp"

namespace Mountain
{
    /// @brief Supports a simple iteration over a templated container whose elements are stored contiguously.
    /// @tparam T The type to iterate on.
    template <typename T>
    struct ContiguousIterator
    {
        using Type = T;

        /// @brief Gets the element in the container at the current position of the enumerator.
        [[nodiscard]]
        constexpr T* GetCurrent() const;

        /// @brief Advances the enumerator to the next element of the container.
        /// @returns @c true if the enumerator was successfully advanced to the next element;
        /// @c false if the enumerator has passed the end of the container.
        constexpr bool_t MoveNext();

        /// @brief Sets the enumerator to its initial position, which is on the first element in the collection.
        constexpr void Reset();

        /// @brief Dereferences this iterator, returning a reference to the current object.
        [[nodiscard]]
        constexpr T& operator*() const;

        /// @brief Equivalent of @c GetCurrent().
        [[nodiscard]]
        constexpr T* operator->() const;

        /// @brief Calls @c MoveNext().
        constexpr ContiguousIterator& operator++();

        /// @brief Calls @c MoveNext().
        constexpr const ContiguousIterator& operator++(int);

        [[nodiscard]]
        auto operator<=>(const ContiguousIterator&) const = default;

    private:
        T* m_FirstElement = nullptr;
        size_t m_Index = 0;
        size_t m_ContainerSize = 0;

        CHECK_REQUIREMENT(ContiguousIterator, Requirements::Iterator);
    };
}

// Start of ContiguousIterator.inl

namespace Mountain
{
    template <typename T>
    constexpr T* ContiguousIterator<T>::GetCurrent() const { return m_FirstElement + m_Index; }

    template <typename T>
    constexpr bool_t ContiguousIterator<T>::MoveNext() { return ++m_Index < m_ContainerSize; }

    template <typename T>
    constexpr void ContiguousIterator<T>::Reset() { m_Index = 0; }

    template <typename T>
    constexpr T& ContiguousIterator<T>::operator*() const { return *GetCurrent(); }

    template <typename T>
    constexpr T* ContiguousIterator<T>::operator->() const { return GetCurrent(); }

    template <typename T>
    constexpr ContiguousIterator<T>& ContiguousIterator<T>::operator++()
    {
        m_Index++;
        return *this;
    }

    template <typename T>
    constexpr const ContiguousIterator<T>& ContiguousIterator<T>::operator++(int)
    {
        m_Index++;
        return *this;
    }
}
