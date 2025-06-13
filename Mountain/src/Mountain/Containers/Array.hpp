// ReSharper disable CppMemberFunctionMayBeStatic
#pragma once

#include "Mountain/Core.hpp"
#include "Mountain/Exceptions/ThrowHelper.hpp"
#include "Mountain/Utils/Requirements.hpp"

namespace Mountain
{
    /// @brief Wrapper around a C array.
    template <typename T, size_t Size>
    struct MOUNTAIN_API Array
    {
        using Type = T;

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
        constexpr T* begin() const noexcept;

        [[nodiscard]]
        constexpr T* end() const noexcept;

        CHECK_REQUIREMENT(Array, Requirements::Container);
        CHECK_REQUIREMENT(Array, Requirements::Enumerable);
    };

    template <class T, class... Other>
    explicit Array(T, Other...) -> Array<T, 1 + sizeof...(Other)> requires Meta::AllSame<T, Other...>;
}

// Start of Array.inl

namespace Mountain
{
    template <typename T, size_t Size>
    constexpr T& Array<T, Size>::At(size_t index) const
    {
        if (index >= Size)
            THROW(ArgumentOutOfRangeException{"Cannot get the element at index >= Size", "index"});
        return data[index];
    }

    template <typename T, size_t Size>
    constexpr size_t Array<T, Size>::GetSize() const noexcept { return Size; }

    template <typename T, size_t Size>
    constexpr T* Array<T, Size>::GetData() const noexcept { return data; }

    template <typename T, size_t Size>
    constexpr T& Array<T, Size>::operator[](size_t index) const noexcept { return data[index]; }

    template <typename T, size_t Size>
    constexpr T* Array<T, Size>::begin() const noexcept { return data; }

    template <typename T, size_t Size>
    constexpr T* Array<T, Size>::end() const noexcept { return data + Size; }
}
