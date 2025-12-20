// ReSharper disable CppMemberFunctionMayBeStatic
#pragma once

#include "Mountain/Core.hpp"
#include "Mountain/Containers/ContiguousIterator.hpp"
// ReSharper disable once CppUnusedIncludeDirective
#include "Mountain/Containers/EnumerableExt.hpp"
#include "Mountain/Containers/FunctionTypes.hpp"
#include "Mountain/Utils/Requirements.hpp"

namespace Mountain
{
    /// @brief Wrapper around a C array.
    template <Concepts::ContainerType T, usize Size>
    struct Array
    {
        using Type = T;
        using ContainedType = Type;
        using EnumeratedType = Type;
        using Iterator = ContiguousIterator<T>;
        using ConstIterator = ContiguousConstIterator<T>;

        static constexpr usize MySize = Size;

        T data[Size];

        /// @brief Get the element at the given index with bounds checking.
        ATTRIBUTE_NODISCARD
        constexpr T& At(usize index);

        /// @brief Get the element at the given index with bounds checking.
        ATTRIBUTE_NODISCARD
        constexpr const T& At(usize index) const;

        /// @brief Get the size of the array. Returns @c Size.
        ATTRIBUTE_NODISCARD
        constexpr usize GetSize() const noexcept;

        /// @brief Get whether the array is empty, i.e., whether its size is 0.
        ATTRIBUTE_NODISCARD
        constexpr bool IsEmpty() const noexcept;

        ATTRIBUTE_NODISCARD
        constexpr T* GetData() noexcept;

        ATTRIBUTE_NODISCARD
        constexpr const T* GetData() const noexcept;

        void Fill(const T& value) noexcept;

        /// @brief Get the element at the given index without bounds checking.
        ATTRIBUTE_NODISCARD
        constexpr T& operator[](usize index) noexcept;

        /// @brief Get the element at the given index without bounds checking.
        ATTRIBUTE_NODISCARD
        constexpr const T& operator[](usize index) const noexcept;

        ATTRIBUTE_NODISCARD
        constexpr Iterator begin() noexcept;

        ATTRIBUTE_NODISCARD
        constexpr Iterator end() noexcept;

        ATTRIBUTE_NODISCARD
        constexpr ConstIterator begin() const noexcept;

        ATTRIBUTE_NODISCARD
        constexpr ConstIterator end() const noexcept;

        ATTRIBUTE_NODISCARD
        constexpr ConstIterator cbegin() const noexcept;

        ATTRIBUTE_NODISCARD
        constexpr ConstIterator cend() const noexcept;

        ENUMERABLE_EXTENSIONS_IMPLEMENTATION

        template <typename U, typename = Meta::EnableIf<Meta::IsConvertibleTo<EnumeratedType, U>>>
        ATTRIBUTE_NODISCARD
        Array<U, Size> Cast() const
        {
            Array<U, Size> result;

            for (usize i = 0; i < Size; i++)
                result[i] = static_cast<U>((*this)[i]);

            return result;
        }

        template <Concepts::Invocable<EnumeratedType> ProjectionFunctionT, typename U = decltype(ProjectionFunctionT{}(EnumeratedType{}))>
        ATTRIBUTE_NODISCARD
        Array<U, Size> Select(const ProjectionFunctionT& function) const
        {
            Array<U, Size> result;

            for (usize i = 0; i < Size; i++)
                result[i] = function((*this)[i]);

            return result;
        }
    };

    template <class T, class... Other>
    Array(T, Other...) -> Array<T, 1 + sizeof...(Other)> requires Meta::AllSame<T, Other...>;

    CHECK_REQUIREMENT(Requirements::MountainEnumerableContainer, Array<Requirements::DefaultType, Requirements::DefaultSize>);
}

// Start of Array.inl

#include "Mountain/Exceptions/ThrowHelper.hpp"

namespace Mountain
{
    template <Concepts::ContainerType T, usize Size>
    constexpr T& Array<T, Size>::At(usize index)
    {
        if (index >= Size)
            THROW(ThrowHelper::IndexOutOfRangeException("index"));
        return data[index];
    }

    template <Concepts::ContainerType T, usize Size>
    constexpr const T& Array<T, Size>::At(usize index) const
    {
        if (index >= Size)
            THROW(ThrowHelper::IndexOutOfRangeException("index"));
        return data[index];
    }

    template <Concepts::ContainerType T, usize Size>
    constexpr usize Array<T, Size>::GetSize() const noexcept { return Size; }

    template <Concepts::ContainerType T, usize Size>
    constexpr bool Array<T, Size>::IsEmpty() const noexcept { return Size == 0; }

    template <Concepts::ContainerType T, usize Size>
    constexpr T* Array<T, Size>::GetData() noexcept { return data; }
    template <Concepts::ContainerType T, usize Size>
    constexpr const T* Array<T, Size>::GetData() const noexcept { return data; }

    template <Concepts::ContainerType T, usize Size>
    void Array<T, Size>::Fill(const T& value) noexcept
    {
        for (usize i = 0; i < Size; i++)
            data[i] = value;
    }

    template <Concepts::ContainerType T, usize Size>
    constexpr T& Array<T, Size>::operator[](usize index) noexcept { return data[index]; }

    template <Concepts::ContainerType T, usize Size>
    constexpr const T& Array<T, Size>::operator[](usize index) const noexcept { return data[index]; }

    template <Concepts::ContainerType T, usize Size>
    constexpr typename Array<T, Size>::Iterator Array<T, Size>::begin() noexcept { return Iterator{data, 0}; }

    template <Concepts::ContainerType T, usize Size>
    constexpr typename Array<T, Size>::Iterator Array<T, Size>::end() noexcept { return Iterator{data, Size}; }

    template <Concepts::ContainerType T, usize Size>
    constexpr typename Array<T, Size>::ConstIterator Array<T, Size>::begin() const noexcept { return cbegin(); }

    template <Concepts::ContainerType T, usize Size>
    constexpr typename Array<T, Size>::ConstIterator Array<T, Size>::end() const noexcept { return cend(); }

    template <Concepts::ContainerType T, usize Size>
    constexpr typename Array<T, Size>::ConstIterator Array<T, Size>::cbegin() const noexcept { return ConstIterator{data, 0}; }

    template <Concepts::ContainerType T, usize Size>
    constexpr typename Array<T, Size>::ConstIterator Array<T, Size>::cend() const noexcept { return ConstIterator{data, Size}; }
}
