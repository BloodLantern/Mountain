// ReSharper disable CppMemberFunctionMayBeStatic
#pragma once

#include "Mountain/Core.hpp"
#include "Mountain/Containers/ContiguousIterator.hpp"
#include "Mountain/Containers/FunctionTypes.hpp"
#include "Mountain/Exceptions/ThrowHelper.hpp"
#include "Mountain/Utils/Requirements.hpp"

namespace Mountain
{
    /// @brief Wrapper around a C array.
    template <Concepts::ContainerType T, size_t Size>
    struct Array
    {
        using Type = T;
        using Iterator = ContiguousIterator<T>;
        using ConstIterator = ContiguousConstIterator<T>;

        static constexpr size_t MySize = Size;

        T data[Size];

        /// @brief Get the element at the given index with bounds checking.
        [[nodiscard]]
        constexpr T& At(size_t index);

        /// @brief Get the element at the given index with bounds checking.
        [[nodiscard]]
        constexpr const T& At(size_t index) const;

        /// @brief Get the size of the array. Returns @c Size.
        [[nodiscard]]
        constexpr size_t GetSize() const noexcept;

        /// @brief Get whether the array is empty, e.g., whether its size is 0.
        [[nodiscard]]
        constexpr bool_t IsEmpty() const noexcept;

        [[nodiscard]]
        constexpr T* GetData() const noexcept;

        void Fill(const T& value) noexcept;

        void Sort();

        void Sort(Comparer<T> comparer);

        /// @brief Get the element at the given index without bounds checking.
        [[nodiscard]]
        constexpr T& operator[](size_t index) noexcept;

        /// @brief Get the element at the given index without bounds checking.
        [[nodiscard]]
        constexpr const T& operator[](size_t index) const noexcept;

        [[nodiscard]]
        constexpr Iterator GetBeginIterator() noexcept;

        [[nodiscard]]
        constexpr Iterator GetEndIterator() noexcept;

        [[nodiscard]]
        constexpr Iterator begin() noexcept;

        [[nodiscard]]
        constexpr Iterator end() noexcept;

        [[nodiscard]]
        constexpr ConstIterator GetBeginIterator() const noexcept;

        [[nodiscard]]
        constexpr ConstIterator GetEndIterator() const noexcept;

        [[nodiscard]]
        constexpr ConstIterator begin() const noexcept;

        [[nodiscard]]
        constexpr ConstIterator end() const noexcept;

        [[nodiscard]]
        constexpr ConstIterator GetBeginConstIterator() const noexcept;

        [[nodiscard]]
        constexpr ConstIterator GetEndConstIterator() const noexcept;

        [[nodiscard]]
        constexpr ConstIterator cbegin() const noexcept;

        [[nodiscard]]
        constexpr ConstIterator cend() const noexcept;
    };

    template <class T, class... Other>
    explicit Array(T, Other...) -> Array<T, 1 + sizeof...(Other)> requires Meta::AllSame<T, Other...>;

    CHECK_REQUIREMENT(Requirements::MountainEnumerableContainer, Array<Requirements::DefaultType, Requirements::DefaultSize>);
}

// Start of Array.inl

namespace Mountain
{
    template <Concepts::ContainerType T, size_t Size>
    constexpr T& Array<T, Size>::At(size_t index)
    {
        if (index >= Size)
            THROW(ThrowHelper::IndexOutOfRangeException("index"));
        return data[index];
    }

    template <Concepts::ContainerType T, size_t Size>
    constexpr const T& Array<T, Size>::At(size_t index) const
    {
        if (index >= Size)
            THROW(ThrowHelper::IndexOutOfRangeException("index"));
        return data[index];
    }

    template <Concepts::ContainerType T, size_t Size>
    constexpr size_t Array<T, Size>::GetSize() const noexcept { return Size; }

    template <Concepts::ContainerType T, size_t Size>
    constexpr bool_t Array<T, Size>::IsEmpty() const noexcept { return Size == 0; }

    template <Concepts::ContainerType T, size_t Size>
    constexpr T* Array<T, Size>::GetData() const noexcept { return data; }

    template <Concepts::ContainerType T, size_t Size>
    void Array<T, Size>::Fill(const T& value) noexcept
    {
        for (size_t i = 0; i < Size; i++)
            data[i] = value;
    }

    template <Concepts::ContainerType T, size_t Size>
    constexpr T& Array<T, Size>::operator[](size_t index) noexcept { return data[index]; }

    template <Concepts::ContainerType T, size_t Size>
    constexpr const T& Array<T, Size>::operator[](size_t index) const noexcept { return data[index]; }

    template <Concepts::ContainerType T, size_t Size>
    constexpr typename Array<T, Size>::Iterator Array<T, Size>::GetBeginIterator() noexcept { return Iterator{data, 0}; }

    template <Concepts::ContainerType T, size_t Size>
    constexpr typename Array<T, Size>::Iterator Array<T, Size>::GetEndIterator() noexcept { return Iterator{data, Size}; }

    template <Concepts::ContainerType T, size_t Size>
    constexpr typename Array<T, Size>::Iterator Array<T, Size>::begin() noexcept { return GetBeginIterator(); }

    template <Concepts::ContainerType T, size_t Size>
    constexpr typename Array<T, Size>::Iterator Array<T, Size>::end() noexcept { return GetEndIterator(); }

    template <Concepts::ContainerType T, size_t Size>
    constexpr typename Array<T, Size>::ConstIterator Array<T, Size>::GetBeginIterator() const noexcept { return GetBeginConstIterator(); }

    template <Concepts::ContainerType T, size_t Size>
    constexpr typename Array<T, Size>::ConstIterator Array<T, Size>::GetEndIterator() const noexcept { return GetEndConstIterator(); }

    template <Concepts::ContainerType T, size_t Size>
    constexpr typename Array<T, Size>::ConstIterator Array<T, Size>::begin() const noexcept { return GetBeginConstIterator(); }

    template <Concepts::ContainerType T, size_t Size>
    constexpr typename Array<T, Size>::ConstIterator Array<T, Size>::end() const noexcept { return GetEndConstIterator(); }

    template <Concepts::ContainerType T, size_t Size>
    constexpr typename Array<T, Size>::ConstIterator Array<T, Size>::GetBeginConstIterator() const noexcept { return ConstIterator{data, 0}; }

    template <Concepts::ContainerType T, size_t Size>
    constexpr typename Array<T, Size>::ConstIterator Array<T, Size>::GetEndConstIterator() const noexcept { return ConstIterator{data, Size}; }

    template <Concepts::ContainerType T, size_t Size>
    constexpr typename Array<T, Size>::ConstIterator Array<T, Size>::cbegin() const noexcept { return GetBeginConstIterator(); }

    template <Concepts::ContainerType T, size_t Size>
    constexpr typename Array<T, Size>::ConstIterator Array<T, Size>::cend() const noexcept { return GetEndConstIterator(); }
}
