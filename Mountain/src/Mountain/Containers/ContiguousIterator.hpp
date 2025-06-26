#pragma once

#include "Mountain/Core.hpp"
#include "Mountain/Exceptions/ThrowHelper.hpp"
#include "Mountain/Utils/Requirements.hpp"

namespace Mountain
{
    /// @brief Supports a simple read-only iteration over a templated container whose elements are stored contiguously.
    /// @tparam T The type to iterate on.
    template <typename T>
    struct ContiguousConstIterator
    {
        using Type = T;
        using value_type = T; // Necessary to satisfy the various std iterator concepts
        using iterator_concept = std::contiguous_iterator_tag; // Same as above

        ContiguousConstIterator() = default;

        ContiguousConstIterator(const T* firstElement, size_t index) noexcept;

        /// @brief Gets the element in the container at the current position of the iterator.
        [[nodiscard]]
        constexpr const T* GetCurrent() const noexcept;

        /// @brief Sets the iterator to its initial position, which is on the first element in the collection.
        constexpr void Reset() noexcept;

        /// @brief Dereferences this iterator, returning a reference to the current object.
        [[nodiscard]]
        constexpr const T& operator*() const noexcept;

        /// @brief Equivalent of @c GetCurrent().
        [[nodiscard]]
        constexpr const T* operator->() const noexcept;

        [[nodiscard]]
        constexpr const T& operator[](ptrdiff_t offset) const noexcept;

        /// @brief Moves to the next element without bounds checking.
        constexpr ContiguousConstIterator& operator++() noexcept;

        /// @brief Moves to the next element without bounds checking.
        constexpr ContiguousConstIterator operator++(int) noexcept;

        /// @brief Moves to the previous element without bounds checking.
        constexpr ContiguousConstIterator& operator--() noexcept;

        /// @brief Moves to the previous element without bounds checking.
        constexpr ContiguousConstIterator operator--(int) noexcept;

        [[nodiscard]]
        friend constexpr ContiguousConstIterator operator+(ptrdiff_t lhs, ContiguousConstIterator rhs) noexcept;

        [[nodiscard]]
        friend constexpr ContiguousConstIterator operator+(ContiguousConstIterator lhs, ptrdiff_t rhs) noexcept;

        [[nodiscard]]
        friend constexpr ContiguousConstIterator& operator+=(ContiguousConstIterator& lhs, ptrdiff_t rhs) noexcept;

        [[nodiscard]]
        friend constexpr ptrdiff_t operator-(const ContiguousConstIterator& lhs, const ContiguousConstIterator& rhs) noexcept;

        [[nodiscard]]
        friend constexpr ContiguousConstIterator operator-(ContiguousConstIterator lhs, ptrdiff_t rhs) noexcept;

        [[nodiscard]]
        friend constexpr ContiguousConstIterator& operator-=(ContiguousConstIterator& lhs, ptrdiff_t rhs) noexcept;

        [[nodiscard]]
        constexpr bool_t operator==(const ContiguousConstIterator& other) const;

        [[nodiscard]]
        constexpr std::strong_ordering operator<=>(const ContiguousConstIterator&) const;

        [[nodiscard]]
        constexpr T* GetFirstElement() const noexcept;

        [[nodiscard]]
        constexpr size_t GetIndex() const noexcept;

        /// @brief Checks whether @p lhs is compatible with @p rhs, e.g., if both are iterating over the same enumerable.
        [[nodiscard]]
        friend constexpr bool_t CheckCompatible(const ContiguousConstIterator& lhs, const ContiguousConstIterator& rhs) noexcept;

    protected:
        const T* m_FirstElement = nullptr;
        size_t m_Index = 0;
    };

    /// @brief Checks whether @p lhs is compatible with @p rhs and throws an exception if they aren't compatible.
    template <typename T>
    constexpr void CheckCompatibleThrow(const ContiguousConstIterator<T>& lhs, const ContiguousConstIterator<T>& rhs);

    CHECK_REQUIREMENT(Requirements::MountainConstIterator, ContiguousConstIterator<Requirements::DefaultType>);
    CHECK_REQUIREMENT(std::contiguous_iterator, ContiguousConstIterator<Requirements::DefaultType>);

    /// @brief Supports a simple iteration over a templated container whose elements are stored contiguously.
    /// @tparam T The type to iterate on.
    template <typename T>
    struct ContiguousIterator : ContiguousConstIterator<T>
    {
        using Base = ContiguousConstIterator<T>;
        using Type = T;
        using value_type = T; // Necessary to satisfy the various std iterator concepts

        using ContiguousConstIterator<T>::ContiguousConstIterator;

        /// @brief Gets the element in the container at the current position of the iterator.
        [[nodiscard]]
        constexpr T* GetCurrent() const noexcept;

        /// @brief Dereferences this iterator, returning a reference to the current object.
        [[nodiscard]]
        constexpr T& operator*() const noexcept;

        /// @brief Equivalent of @c GetCurrent().
        [[nodiscard]]
        constexpr T* operator->() const noexcept;

        [[nodiscard]]
        constexpr T& operator[](ptrdiff_t offset) const noexcept;

        /// @brief Moves to the next element without bounds checking.
        constexpr ContiguousIterator& operator++() noexcept;

        /// @brief Moves to the next element without bounds checking.
        constexpr ContiguousIterator operator++(int) noexcept;

        /// @brief Moves to the previous element without bounds checking.
        constexpr ContiguousIterator& operator--() noexcept;

        /// @brief Moves to the previous element without bounds checking.
        constexpr ContiguousIterator operator--(int) noexcept;

        [[nodiscard]]
        friend constexpr ContiguousIterator operator+(ptrdiff_t lhs, ContiguousIterator rhs) noexcept;

        [[nodiscard]]
        friend constexpr ContiguousIterator operator+(ContiguousIterator lhs, ptrdiff_t rhs) noexcept;

        [[nodiscard]]
        friend constexpr ContiguousIterator& operator+=(ContiguousIterator& lhs, ptrdiff_t rhs) noexcept;

        [[nodiscard]]
        friend constexpr ptrdiff_t operator-(const ContiguousIterator& lhs, const ContiguousIterator& rhs);

        [[nodiscard]]
        friend constexpr ContiguousIterator operator-(ContiguousIterator lhs, ptrdiff_t rhs) noexcept;

        [[nodiscard]]
        friend constexpr ContiguousIterator& operator-=(ContiguousIterator& lhs, ptrdiff_t rhs) noexcept;
    };

    /// @brief Checks whether @p lhs is compatible with @p rhs, e.g., if both are iterating over the same enumerable.
    template <typename T>
    [[nodiscard]]
    constexpr bool_t CheckCompatible(const ContiguousIterator<T>& lhs, const ContiguousIterator<T>& rhs) noexcept;

    /// @brief Checks whether @p lhs is compatible with @p rhs and throws an exception if they aren't compatible.
    template <typename T>
    constexpr void CheckCompatibleThrow(const ContiguousIterator<T>& lhs, const ContiguousIterator<T>& rhs);

    CHECK_REQUIREMENT(Requirements::MountainIterator, ContiguousIterator<Requirements::DefaultType>);
    CHECK_REQUIREMENT(std::contiguous_iterator, ContiguousIterator<Requirements::DefaultType>);
}

// Start of ContiguousIterator.inl

namespace Mountain
{
    template <typename T>
    ContiguousConstIterator<T>::ContiguousConstIterator(const T* firstElement, const size_t index) noexcept
        : m_FirstElement(firstElement), m_Index(index)
    {
    }

    template <typename T>
    constexpr const T* ContiguousConstIterator<T>::GetCurrent() const noexcept { return m_FirstElement + m_Index; }

    template <typename T>
    constexpr void ContiguousConstIterator<T>::Reset() noexcept { m_Index = 0; }

    template <typename T>
    constexpr const T& ContiguousConstIterator<T>::operator*() const noexcept { return *GetCurrent(); }

    template <typename T>
    constexpr const T* ContiguousConstIterator<T>::operator->() const noexcept { return GetCurrent(); }

    template <typename T>
    constexpr const T& ContiguousConstIterator<T>::operator[](ptrdiff_t offset) const noexcept { return *(*this + offset); }

    template <typename T>
    constexpr ContiguousConstIterator<T>& ContiguousConstIterator<T>::operator++() noexcept
    {
        m_Index++;
        return *this;
    }

    template <typename T>
    constexpr ContiguousConstIterator<T> ContiguousConstIterator<T>::operator++(int) noexcept
    {
        ContiguousConstIterator old = *this;
        m_Index++;
        return old;
    }

    template <typename T>
    constexpr ContiguousConstIterator<T>& ContiguousConstIterator<T>::operator--() noexcept
    {
        m_Index--;
        return *this;
    }

    template <typename T>
    constexpr ContiguousConstIterator<T> ContiguousConstIterator<T>::operator--(int) noexcept
    {
        ContiguousConstIterator old = *this;
        m_Index--;
        return old;
    }

    template <typename T>
    constexpr bool_t ContiguousConstIterator<T>::operator==(const ContiguousConstIterator& other) const
    {
        CheckCompatibleThrow(*this, other);
        return m_Index == other.m_Index;
    }

    template <typename T>
    constexpr std::strong_ordering ContiguousConstIterator<T>::operator<=>(const ContiguousConstIterator& other) const
    {
        CheckCompatibleThrow(*this, other);
        return m_Index <=> other.m_Index;
    }

    template <typename T>
    constexpr T* ContiguousConstIterator<T>::GetFirstElement() const noexcept { return m_FirstElement; }

    template <typename T>
    constexpr size_t ContiguousConstIterator<T>::GetIndex() const noexcept { return m_Index; }

    template <typename T>
    constexpr ContiguousConstIterator<T> operator+(ptrdiff_t lhs, ContiguousConstIterator<T> rhs) noexcept { return rhs += lhs; }

    template <typename T>
    constexpr ContiguousConstIterator<T> operator+(ContiguousConstIterator<T> lhs, ptrdiff_t rhs) noexcept { return lhs += rhs; }

    template <typename T>
    constexpr ContiguousConstIterator<T>& operator+=(ContiguousConstIterator<T>& lhs, ptrdiff_t rhs) noexcept
    {
        lhs.m_Index += rhs;
        return lhs;
    }

    template <typename T>
    constexpr ptrdiff_t operator-(const ContiguousConstIterator<T>& lhs, const ContiguousConstIterator<T>& rhs)
    {
        CheckCompatibleThrow(lhs, rhs);
        return lhs.m_Index - rhs.m_Index;
    }

    template <typename T>
    constexpr ContiguousConstIterator<T> operator-(ContiguousConstIterator<T> lhs, ptrdiff_t rhs) noexcept { return lhs -= rhs; }

    template <typename T>
    constexpr ContiguousConstIterator<T>& operator-=(ContiguousConstIterator<T>& lhs, ptrdiff_t rhs) noexcept
    {
        lhs.m_Index -= rhs;
        return lhs;
    }

    template <typename T>
    constexpr bool_t CheckCompatible(const ContiguousConstIterator<T>& lhs, const ContiguousConstIterator<T>& rhs) noexcept
    {
        return lhs.m_FirstElement == rhs.m_FirstElement;
    }

    template <typename T>
    constexpr void CheckCompatibleThrow(const ContiguousConstIterator<T>& lhs, const ContiguousConstIterator<T>& rhs)
    {
        if (!CheckCompatible(lhs, rhs))
            THROW(InvalidOperationException{"Incompatible iterators."});
    }

    template <typename T>
    constexpr T* ContiguousIterator<T>::GetCurrent() const noexcept
    {
        return const_cast<T*>(Base::GetCurrent());
    }

    template <typename T>
    constexpr T& ContiguousIterator<T>::operator*() const noexcept
    {
        return const_cast<T&>(Base::operator*());
    }

    template <typename T>
    constexpr T* ContiguousIterator<T>::operator->() const noexcept
    {
        return const_cast<T*>(Base::operator->());
    }

    template <typename T>
    constexpr T& ContiguousIterator<T>::operator[](ptrdiff_t offset) const noexcept
    {
        return const_cast<T&>(Base::operator[](offset));
    }

    template <typename T>
    constexpr ContiguousIterator<T>& ContiguousIterator<T>::operator++() noexcept
    {
        Base::operator++();
        return *this;
    }

    template <typename T>
    constexpr ContiguousIterator<T> ContiguousIterator<T>::operator++(int) noexcept
    {
        ContiguousIterator old = *this;
        Base::operator++();
        return old;
    }

    template <typename T>
    constexpr ContiguousIterator<T>& ContiguousIterator<T>::operator--() noexcept
    {
        Base::operator--();
        return *this;
    }

    template <typename T>
    constexpr ContiguousIterator<T> ContiguousIterator<T>::operator--(int) noexcept
    {
        ContiguousIterator old = *this;
        Base::operator--();
        return old;
    }

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
    constexpr ptrdiff_t operator-(const ContiguousIterator<T>& lhs, const ContiguousIterator<T>& rhs)
    {
        CheckCompatibleThrow(lhs, rhs);
        return lhs.m_Index - rhs.m_Index;
    }

    template <typename T>
    constexpr ContiguousIterator<T> operator-(ContiguousIterator<T> lhs, ptrdiff_t rhs) noexcept { return lhs -= rhs; }

    template <typename T>
    constexpr ContiguousIterator<T>& operator-=(ContiguousIterator<T>& lhs, ptrdiff_t rhs) noexcept
    {
        lhs.m_Index -= rhs;
        return lhs;
    }

    template <typename T>
    constexpr bool_t CheckCompatible(const ContiguousIterator<T>& lhs, const ContiguousIterator<T>& rhs) noexcept
    {
        return CheckCompatible(static_cast<ContiguousConstIterator<T>>(lhs), static_cast<ContiguousConstIterator<T>>(rhs));
    }

    template <typename T>
    constexpr void CheckCompatibleThrow(const ContiguousIterator<T>& lhs, const ContiguousIterator<T>& rhs)
    {
        return CheckCompatibleThrow(static_cast<ContiguousConstIterator<T>>(lhs), static_cast<ContiguousConstIterator<T>>(rhs));
    }
}
