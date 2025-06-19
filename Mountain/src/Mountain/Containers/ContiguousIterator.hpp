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

        /// @brief Gets the element in the container at the current position of the iterator.
        [[nodiscard]]
        constexpr T* GetCurrent() const noexcept;

        /// @brief Moves the iterator to the next element of the container.
        /// @returns @c true if the iterator was successfully moved to the next element;
        /// @c false if the iterator has passed the end of the container.
        constexpr bool_t MoveNext() noexcept;

        /// @brief Moves the iterator to the previous element of the container.
        /// @returns @c true if the iterator was successfully moved to the previous element;
        /// @c false if the iterator has passed the beginning of the container.
        constexpr bool_t MovePrevious() noexcept;

        /// @brief Sets the iterator to its initial position, which is on the first element in the collection.
        constexpr void Reset() noexcept;

        /// @brief Dereferences this iterator, returning a reference to the current object.
        [[nodiscard]]
        constexpr T& operator*() const noexcept;

        /// @brief Equivalent of @c GetCurrent().
        [[nodiscard]]
        constexpr T* operator->() const noexcept;

        /// @brief Moves to the next element without bounds checking.
        constexpr ContiguousIterator& operator++() noexcept;

        /// @brief Moves to the next element without bounds checking.
        constexpr const ContiguousIterator& operator++(int) noexcept;

        /// @brief Moves to the previous element without bounds checking.
        constexpr ContiguousIterator& operator--() noexcept;

        /// @brief Moves to the previous element without bounds checking.
        constexpr const ContiguousIterator& operator--(int) noexcept;

        [[nodiscard]]
        friend constexpr ContiguousIterator operator+(ptrdiff_t lhs, ContiguousIterator rhs) noexcept;

        [[nodiscard]]
        friend constexpr ContiguousIterator operator+(ContiguousIterator lhs, ptrdiff_t rhs) noexcept;

        [[nodiscard]]
        friend constexpr ContiguousIterator& operator+=(ContiguousIterator& lhs, ptrdiff_t rhs) noexcept;

        [[nodiscard]]
        friend constexpr ptrdiff_t operator-(const ContiguousIterator& lhs, const ContiguousIterator& rhs) noexcept;

        [[nodiscard]]
        friend constexpr ContiguousIterator operator-(ContiguousIterator lhs, ptrdiff_t rhs) noexcept;

        [[nodiscard]]
        friend constexpr ContiguousIterator& operator-=(ContiguousIterator& lhs, const ContiguousIterator& rhs) noexcept;

        [[nodiscard]]
        constexpr auto operator<=>(const ContiguousIterator&) const noexcept = default;

        [[nodiscard]]
        constexpr size_t GetIndex() const noexcept;

        [[nodiscard]]
        constexpr size_t GetContainerSize() const noexcept;

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
    constexpr T* ContiguousIterator<T>::GetCurrent() const noexcept { return m_FirstElement + m_Index; }

    template <typename T>
    constexpr bool_t ContiguousIterator<T>::MoveNext() noexcept
    {
        const size_t newIndex = m_Index + 1;
        if (newIndex >= m_ContainerSize)
            return false;

        m_Index = newIndex;
        return true;
    }

    template <typename T>
    constexpr bool_t ContiguousIterator<T>::MovePrevious() noexcept
    {
        if (m_Index == 0)
            return false;

        m_Index--;
        return true;
    }

    template <typename T>
    constexpr void ContiguousIterator<T>::Reset() noexcept { m_Index = 0; }

    template <typename T>
    constexpr T& ContiguousIterator<T>::operator*() const noexcept { return *GetCurrent(); }

    template <typename T>
    constexpr T* ContiguousIterator<T>::operator->() const noexcept { return GetCurrent(); }

    template <typename T>
    constexpr ContiguousIterator<T>& ContiguousIterator<T>::operator++() noexcept
    {
        m_Index++;
        return *this;
    }

    template <typename T>
    constexpr const ContiguousIterator<T>& ContiguousIterator<T>::operator++(int) noexcept
    {
        m_Index++;
        return *this;
    }

    template <typename T>
    constexpr ContiguousIterator<T>& ContiguousIterator<T>::operator--() noexcept
    {
        m_Index--;
        return *this;
    }

    template <typename T>
    constexpr const ContiguousIterator<T>& ContiguousIterator<T>::operator--(int) noexcept
    {
        m_Index--;
        return *this;
    }

    template <typename T>
    constexpr size_t ContiguousIterator<T>::GetIndex() const noexcept { return m_Index; }

    template <typename T>
    constexpr size_t ContiguousIterator<T>::GetContainerSize() const noexcept { return m_ContainerSize; }

    template <typename T>
    constexpr ContiguousIterator<T> operator+(ptrdiff_t lhs, ContiguousIterator<T> rhs) noexcept { return rhs += lhs; }

    template <typename T>
    constexpr ContiguousIterator<T> operator+(ContiguousIterator<T> lhs, ptrdiff_t rhs) noexcept { return lhs += rhs; }

    template <typename T>
    constexpr ContiguousIterator<T>& operator+=(ContiguousIterator<T>& lhs, ptrdiff_t rhs) noexcept
    {
        lhs.m_Index += rhs;
        return lhs;
    }

    template <typename T>
    constexpr ptrdiff_t operator-(const ContiguousIterator<T>& lhs, const ContiguousIterator<T>& rhs) noexcept { return lhs.m_Index - rhs.m_Index; }

    template <typename T>
    constexpr ContiguousIterator<T> operator-(ContiguousIterator<T> lhs, ptrdiff_t rhs) noexcept { return lhs -= rhs; }

    template <typename T>
    constexpr ContiguousIterator<T>& operator-=(ContiguousIterator<T>& lhs, const ContiguousIterator<T>& rhs) noexcept
    {
        lhs.m_Index -= rhs.m_Index;
        return lhs;
    }
}
