// ReSharper disable CppMemberFunctionMayBeStatic
#pragma once

#include "Mountain/Core.hpp"
#include "Mountain/Containers/ContiguousIterator.hpp"
#include "Mountain/Exceptions/ThrowHelper.hpp"
#include "Mountain/Utils/Requirements.hpp"

namespace Mountain
{
    /// @brief Wrapper around a C array.
    template <Concepts::ContainerType T, size_t Size>
    struct MOUNTAIN_API Array
    {
        using Type = T;
        using Iterator = ContiguousIterator<T>;

        T data[Size];

        /// @brief Get the element at the given index with bounds checking.
        [[nodiscard]]
        constexpr T& At(size_t index) const;

        /// @brief Get the size of the array. Returns @c Size.
        [[nodiscard]]
        constexpr size_t GetSize() const noexcept;

        [[nodiscard]]
        constexpr T* GetData() const noexcept;

        /// @brief Get the element at the given index without bounds checking.
        [[nodiscard]]
        constexpr T& operator[](size_t index) const noexcept;

        [[nodiscard]]
        constexpr Iterator GetBeginIterator() const noexcept;

        [[nodiscard]]
        constexpr Iterator GetEndIterator() const noexcept;

        [[nodiscard]]
        constexpr Iterator begin() const noexcept;

        [[nodiscard]]
        constexpr Iterator end() const noexcept;

        CHECK_REQUIREMENT(Array, Requirements::Container);
        CHECK_REQUIREMENT(Array, Requirements::Enumerable);
    };

    template <class T, class... Other>
    explicit Array(T, Other...) -> Array<T, 1 + sizeof...(Other)> requires Meta::AllSame<T, Other...>;
}

// Start of Array.inl

namespace Mountain
{
    template <Concepts::ContainerType T, size_t Size>
    constexpr T& Array<T, Size>::At(size_t index) const
    {
        if (index >= Size)
            THROW(ArgumentOutOfRangeException{"Cannot get the element at index >= Size", "index"});
        return data[index];
    }

    template <Concepts::ContainerType T, size_t Size>
    constexpr size_t Array<T, Size>::GetSize() const noexcept { return Size; }

    template <Concepts::ContainerType T, size_t Size>
    constexpr T* Array<T, Size>::GetData() const noexcept { return data; }

    template <Concepts::ContainerType T, size_t Size>
    constexpr T& Array<T, Size>::operator[](size_t index) const noexcept { return data[index]; }

    template <Concepts::ContainerType T, size_t Size>
    constexpr typename Array<T, Size>::Iterator Array<T, Size>::GetBeginIterator() const noexcept { return { .m_FirstElement = data, .m_ContainerSize = Size }; }

    template <Concepts::ContainerType T, size_t Size>
    constexpr typename Array<T, Size>::Iterator Array<T, Size>::GetEndIterator() const noexcept { return { .m_FirstElement = data, .m_Index = Size, .m_ContainerSize = Size }; }

    template <Concepts::ContainerType T, size_t Size>
    constexpr typename Array<T, Size>::Iterator Array<T, Size>::begin() const noexcept { return GetBeginIterator(); }

    template <Concepts::ContainerType T, size_t Size>
    constexpr typename Array<T, Size>::Iterator Array<T, Size>::end() const noexcept { return GetEndIterator(); }
}
