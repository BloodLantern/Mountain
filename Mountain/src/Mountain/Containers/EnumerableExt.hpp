#pragma once

#include "Mountain/Core.hpp"
#include "Mountain/Containers/FunctionTypes.hpp"
#include "Mountain/Utils/Requirements.hpp"

/// @brief Defines member functions for all enumerable extensions
#define ENUMERABLE_EXTENSIONS_IMPLEMENTATION \
    ATTRIBUTE_NODISCARD \
    bool_t All(const ::Mountain::Predicate<EnumeratedType>& predicate) const { return ::Mountain::All(*this, predicate); } \
    \
    ATTRIBUTE_NODISCARD \
    bool_t Any(const ::Mountain::Predicate<EnumeratedType>& predicate) const { return ::Mountain::Any(*this, predicate); } \
    \
    template <typename = ::Mountain::Meta::EnableIf<::Mountain::Meta::IsIntegralOrFloating<EnumeratedType>>> \
    ATTRIBUTE_NODISCARD \
    float_t Average() const { return ::Mountain::Average<::Mountain::Meta::RemoveCvRefSpecifier<decltype(*this)>, EnumeratedType>(*this); } \
    \
    template <::Mountain::Requirements::MountainEnumerable EnumerableT, typename = ::Mountain::Meta::EnableIf<Meta::IsSame<EnumeratedType, ::Mountain::Meta::EnumerableType<EnumerableT>>>> \
    ATTRIBUTE_NODISCARD \
    List<EnumeratedType> Concat(const EnumerableT& enumerable) const { return ::Mountain::Concat(*this, enumerable); } \
    \
    template <typename U, typename = ::Mountain::Meta::EnableIf<::Mountain::Meta::IsEqualityComparableWith<U, EnumeratedType>>> \
    ATTRIBUTE_NODISCARD \
    bool_t Contains(const U& element) const { return ::Mountain::Contains(*this, element); } \
    \
    ATTRIBUTE_NODISCARD \
    bool_t Contains(const ::Mountain::Predicate<EnumeratedType>& predicate) const { return ::Mountain::Contains(*this, predicate); } \
    \
    ATTRIBUTE_NODISCARD \
    size_t Count(const ::Mountain::Predicate<EnumeratedType>& predicate) const { return ::Mountain::Count(*this, predicate); } \
    \
    ATTRIBUTE_NODISCARD \
    ::Mountain::List<EnumeratedType> FindAll(const ::Mountain::Predicate<EnumeratedType>& predicate) const \
    { return ::Mountain::FindAll(*this, predicate); } \
    \
    ATTRIBUTE_NODISCARD \
    EnumeratedType* FindFirst(const ::Mountain::Predicate<EnumeratedType>& predicate) { return ::Mountain::FindFirst(*this, predicate); } \
    \
    ATTRIBUTE_NODISCARD \
    const EnumeratedType* FindFirst(const ::Mountain::Predicate<EnumeratedType>& predicate) const { return ::Mountain::FindFirst(*this, predicate); } \
    \
    ATTRIBUTE_NODISCARD \
    EnumeratedType* FindLast(const ::Mountain::Predicate<EnumeratedType>& predicate) { return ::Mountain::FindLast(*this, predicate); } \
    \
    ATTRIBUTE_NODISCARD \
    const EnumeratedType* FindLast(const ::Mountain::Predicate<EnumeratedType>& predicate) const { return ::Mountain::FindLast(*this, predicate); } \
    \
    ATTRIBUTE_NODISCARD \
    EnumeratedType& First() { return ::Mountain::First(*this); } \
    \
    ATTRIBUTE_NODISCARD \
    const EnumeratedType& First() const { return ::Mountain::First(*this); } \
    \
    ATTRIBUTE_NODISCARD \
    EnumeratedType& Last() { return ::Mountain::Last(*this); } \
    \
    ATTRIBUTE_NODISCARD \
    const EnumeratedType& Last() const { return ::Mountain::Last(*this); } \
    \
    ATTRIBUTE_NODISCARD \
    EnumeratedType& Single() { return ::Mountain::Single(*this); } \
    \
    ATTRIBUTE_NODISCARD \
    const EnumeratedType& Single() const { return ::Mountain::Single(*this); } \
    \
    void ForEach(const ::Mountain::Operation<EnumeratedType>& operation) { return ::Mountain::ForEach(*this, operation); } \
    \
    void ForEach(const ::Mountain::Operation<const EnumeratedType>& operation) const { return ::Mountain::ForEach(*this, operation); } \
    \
    template <typename = ::Mountain::Meta::EnableIf< \
        ::Mountain::Meta::IsSortable<Iterator, ::Mountain::Comparer<EnumeratedType>, ::Mountain::Identity>>> \
    void Sort() { return ::Mountain::Sort(*this); } \
    \
    template <typename = ::Mountain::Meta::EnableIf< \
        ::Mountain::Meta::IsSortable<Iterator, ::Mountain::Comparer<EnumeratedType>, ::Mountain::Identity>>> \
    void Sort(const ::Mountain::Comparer<EnumeratedType>& comparer) { return ::Mountain::Sort(*this, comparer); } \
    \
    bool_t IsValidIndex(const size_t index) const { return ::Mountain::IsValidIndex(*this, index); }

namespace Mountain
{
    template <Concepts::DynamicContainerType T>
    class List;

    template <Concepts::ContainerType T, size_t Size>
    struct Array;

    /// @brief Determines whether all elements of a sequence satisfy a condition.
    template <Requirements::MountainEnumerable EnumerableT, typename T = Meta::MountainEnumerableType<EnumerableT>>
    ATTRIBUTE_NODISCARD
    bool_t All(const EnumerableT& enumerable, const Predicate<Meta::Identity<T>>& predicate);

    /// @brief Determines whether any element of a sequence satisfies a condition.
    template <Requirements::MountainEnumerable EnumerableT, typename T = Meta::MountainEnumerableType<EnumerableT>>
    ATTRIBUTE_NODISCARD
    bool_t Any(const EnumerableT& enumerable, const Predicate<Meta::Identity<T>>& predicate);

    /// @brief Computes the average of a sequence of integral or floating values.
    template <Requirements::MountainEnumerable EnumerableT,
        typename T = Meta::MountainEnumerableType<EnumerableT>,
        typename = Meta::EnableIf<Meta::IsIntegralOrFloating<T>>>
    ATTRIBUTE_NODISCARD
    float_t Average(const EnumerableT& enumerable);

    template <Requirements::MountainEnumerable EnumerableT,
        Requirements::MountainEnumerable EnumerableU,
        typename T = Meta::EnumerableType<EnumerableT>,
        typename = Meta::EnableIf<Meta::IsSame<T, Meta::EnumerableType<EnumerableU>>>>
    ATTRIBUTE_NODISCARD
    List<T> Concat(const EnumerableT& firstEnumerable, const EnumerableU& secondEnumerable);

    template <typename T, size_t Size>
    ATTRIBUTE_NODISCARD
    Array<T, Size * 2> Concat(const Array<T, Size>& firstEnumerable, const Array<T, Size>& secondEnumerable);

    template <Requirements::MountainEnumerable EnumerableT,
        typename T,
        typename = Meta::EnableIf<Meta::IsEqualityComparableWith<T, Meta::MountainEnumerableType<EnumerableT>>>>
    ATTRIBUTE_NODISCARD
    bool_t Contains(const EnumerableT& enumerable, const T& element);

    template <Requirements::MountainEnumerable EnumerableT, typename T = Meta::EnumerableType<EnumerableT>>
    ATTRIBUTE_NODISCARD
    bool_t Contains(const EnumerableT& enumerable, const Predicate<Meta::Identity<T>>& predicate);

    template <Requirements::MountainEnumerable EnumerableT, typename T = Meta::EnumerableType<EnumerableT>>
    ATTRIBUTE_NODISCARD
    size_t Count(const EnumerableT& enumerable, const Predicate<Meta::Identity<T>>& predicate);

    template <Requirements::MountainEnumerable EnumerableT, typename T = Meta::MountainEnumerableType<EnumerableT>>
    ATTRIBUTE_NODISCARD
    List<T> FindAll(const EnumerableT& enumerable, const Predicate<Meta::Identity<T>>& predicate);

    template <Requirements::MountainEnumerable EnumerableT, typename T = Meta::MountainEnumerableType<EnumerableT>>
    ATTRIBUTE_NODISCARD
    T* FindFirst(EnumerableT& enumerable, const Predicate<Meta::Identity<T>>& predicate);

    template <Requirements::MountainEnumerable EnumerableT, typename T = Meta::MountainEnumerableType<EnumerableT>>
    ATTRIBUTE_NODISCARD
    const T* FindFirst(const EnumerableT& enumerable, const Predicate<Meta::Identity<T>>& predicate);

    template <Requirements::MountainEnumerable EnumerableT, typename T = Meta::MountainEnumerableType<EnumerableT>>
    ATTRIBUTE_NODISCARD
    T* FindLast(EnumerableT& enumerable, const Predicate<Meta::Identity<T>>& predicate);

    template <Requirements::MountainEnumerable EnumerableT, typename T = Meta::MountainEnumerableType<EnumerableT>>
    ATTRIBUTE_NODISCARD
    const T* FindLast(const EnumerableT& enumerable, const Predicate<Meta::Identity<T>>& predicate);

    /// @brief Returns the first element of a sequence.
    template <Requirements::MountainEnumerable EnumerableT, typename T = Meta::MountainEnumerableType<EnumerableT>>
    ATTRIBUTE_NODISCARD
    T& First(EnumerableT& enumerable);

    /// @brief Returns the first element of a sequence.
    template <Requirements::MountainEnumerable EnumerableT, typename T = Meta::MountainEnumerableType<EnumerableT>>
    ATTRIBUTE_NODISCARD
    const T& First(const EnumerableT& enumerable);

    /// @brief Returns the last element of a sequence.
    template <Requirements::MountainEnumerable EnumerableT, typename T = Meta::MountainEnumerableType<EnumerableT>>
    ATTRIBUTE_NODISCARD
    T& Last(EnumerableT& enumerable);

    /// @brief Returns the last element of a sequence.
    template <Requirements::MountainEnumerable EnumerableT, typename T = Meta::MountainEnumerableType<EnumerableT>>
    ATTRIBUTE_NODISCARD
    const T& Last(const EnumerableT& enumerable);

    /// @brief Returns the only element of a sequence and throws an exception if there is not exactly one element in the sequence.
    template <Requirements::MountainEnumerable EnumerableT, typename T = Meta::MountainEnumerableType<EnumerableT>>
    ATTRIBUTE_NODISCARD
    T& Single(EnumerableT& enumerable);

    /// @brief Returns the only element of a sequence and throws an exception if there is not exactly one element in the sequence.
    template <Requirements::MountainEnumerable EnumerableT, typename T = Meta::MountainEnumerableType<EnumerableT>>
    ATTRIBUTE_NODISCARD
    const T& Single(const EnumerableT& enumerable);

    template <Requirements::MountainEnumerable EnumerableT, typename T = Meta::MountainEnumerableType<EnumerableT>>
    void ForEach(EnumerableT& enumerable, const Operation<Meta::Identity<T>>& operation);

    template <Requirements::MountainEnumerable EnumerableT, typename T = Meta::MountainEnumerableType<EnumerableT>>
    void ForEach(const EnumerableT& enumerable, const Operation<const Meta::Identity<T>>& operation);

    template <Requirements::MountainEnumerable EnumerableT,
        typename T = Meta::MountainEnumerableType<EnumerableT>,
        typename = Meta::EnableIf<Meta::IsSortable<typename EnumerableT::Iterator, Comparer<T>, Identity>>>
    void Sort(EnumerableT& enumerable);

    template <Requirements::MountainEnumerable EnumerableT,
        typename T = Meta::MountainEnumerableType<EnumerableT>,
        typename = Meta::EnableIf<Meta::IsSortable<typename EnumerableT::Iterator, Comparer<T>, Identity>>>
    void Sort(EnumerableT& enumerable, const Comparer<Meta::Identity<T>>& comparer);

    template <Requirements::MountainEnumerable EnumerableT>
    bool_t IsValidIndex(const EnumerableT& enumerable, size_t index);
}

// Start of EnumerableExt.inl

#include "Mountain/Containers/Array.hpp"
#include "Mountain/Containers/List.hpp"

namespace Mountain
{
    template <Requirements::MountainEnumerable EnumerableT, typename T>
    bool_t All(const EnumerableT& enumerable, const Predicate<Meta::Identity<T>>& predicate)
    {
        for (const T& e : enumerable)
        {
            if (!predicate(e))
                return false;
        }

        return true;
    }

    template <Requirements::MountainEnumerable EnumerableT, typename T>
    bool_t Any(const EnumerableT& enumerable, const Predicate<Meta::Identity<T>>& predicate)
    {
        for (const T& e : enumerable)  // NOLINT(readability-use-anyofallof)
        {
            if (predicate(e))
                return true;
        }

        return false;
    }

    template <Requirements::MountainEnumerable EnumerableT, typename T, typename>
    float_t Average(const EnumerableT& enumerable)
    {
        float_t result = 0.f;

        for (const T& e : enumerable)
        {
            result += e;
        }

        return result / GetSize(enumerable);
    }

    template <Requirements::MountainEnumerable EnumerableT, Requirements::MountainEnumerable EnumerableU, typename T, typename>
    List<T> Concat(const EnumerableT& firstEnumerable, const EnumerableU& secondEnumerable)
    {
        List<T>result;
        result.Reserve(GetSize(firstEnumerable) + GetSize(secondEnumerable));

        result.AddRange(firstEnumerable);
        result.AddRange(secondEnumerable);

        return result;
    }

    template <typename T, size_t Size>
    Array<T, Size * 2> Concat(const Array<T, Size>& firstEnumerable, const Array<T, Size>& secondEnumerable)
    {
        Array<T, Size * 2> result;
        size_t i = 0;

        for (const T& e : firstEnumerable)
        {
            result[i] = e;
            i++;
        }
        for (const T& e : secondEnumerable)
        {
            result[i] = e;
            i++;
        }

        return result;
    }

    template <Requirements::MountainEnumerable EnumerableT, typename T, typename>
    bool_t Contains(const EnumerableT& enumerable, const T& element)
    {
        return Any(enumerable, [&](const Meta::MountainEnumerableType<EnumerableT>& e) { return e == element; });
    }

    template <Requirements::MountainEnumerable EnumerableT, typename T>
    bool_t Contains(const EnumerableT& enumerable, const Predicate<Meta::Identity<T>>& predicate)
    {
        return FindFirst(enumerable, predicate) != nullptr;
    }

    template <Requirements::MountainEnumerable EnumerableT, typename T>
    size_t Count(const EnumerableT& enumerable, const Predicate<Meta::Identity<T>>& predicate)
    {
        size_t result = 0;

        for (const T& e : enumerable)
        {
            if (predicate(e))
                result++;
        }

        return result;
    }

    template <Requirements::MountainEnumerable EnumerableT>
    size_t GetSize(const EnumerableT& enumerable)
    {
        return enumerable.cend() - enumerable.cbegin();
    }

    template <Requirements::MountainEnumerable EnumerableT>
    bool_t IsEmpty(const EnumerableT& enumerable)
    {
        return GetSize(enumerable) == 0;
    }

    template <Requirements::MountainEnumerable EnumerableT, typename T>
    List<T> FindAll(const EnumerableT& enumerable, const Predicate<Meta::Identity<T>>& predicate)
    {
        List<T> result;

        for (const T& e : enumerable)
        {
            if (predicate(e))
                result.Add(e);
        }

        return result;
    }

    template <Requirements::MountainEnumerable EnumerableT, typename T>
    T* FindFirst(EnumerableT& enumerable, const Predicate<Meta::Identity<T>>& predicate)
    {
        for (T& e : enumerable)
        {
            if (predicate(e))
                return &e;
        }

        return nullptr;
    }

    template <Requirements::MountainEnumerable EnumerableT, typename T>
    const T* FindFirst(const EnumerableT& enumerable, const Predicate<Meta::Identity<T>>& predicate)
    {
        for (const T& e : enumerable)
        {
            if (predicate(e))
                return &e;
        }

        return nullptr;
    }

    template <Requirements::MountainEnumerable EnumerableT, typename T>
    T* FindLast(EnumerableT& enumerable, const Predicate<Meta::Identity<T>>& predicate)
    {
        for (typename EnumerableT::Iterator it = enumerable.end() - 1; it + 1 != enumerable.begin(); it--)
        {
            T& value = *it;
            if (predicate(value))
                return &value;
        }

        return nullptr;
    }

    template <Requirements::MountainEnumerable EnumerableT, typename T>
    const T* FindLast(const EnumerableT& enumerable, const Predicate<Meta::Identity<T>>& predicate)
    {
        for (typename EnumerableT::ConstIterator it = enumerable.GetEndConstIterator() - 1; it + 1 != enumerable.GetBeginConstIterator(); it--)
        {
            const T& value = *it;
            if (predicate(value))
                return &value;
        }

        return nullptr;
    }

    template <Requirements::MountainEnumerable EnumerableT, typename T>
    T& First(EnumerableT& enumerable)
    {
        return const_cast<T&>(First(const_cast<const EnumerableT&>(enumerable)));
    }

    template <Requirements::MountainEnumerable EnumerableT, typename T>
    const T& First(const EnumerableT& enumerable)
    {
        if (IsEmpty(enumerable))
            THROW(InvalidOperationException{"Cannot get the first element of an empty enumerable."});
        return *enumerable.begin();
    }

    template <Requirements::MountainEnumerable EnumerableT, typename T>
    T& Last(EnumerableT& enumerable)
    {
        return const_cast<T&>(Last(const_cast<const EnumerableT&>(enumerable)));
    }

    template <Requirements::MountainEnumerable EnumerableT, typename T>
    const T& Last(const EnumerableT& enumerable)
    {
        if (IsEmpty(enumerable))
            THROW(InvalidOperationException{"Cannot get the last element of an empty enumerable."});
        return *--enumerable.end();
    }

    template <Requirements::MountainEnumerable EnumerableT, typename T>
    T& Single(EnumerableT& enumerable)
    {
        return const_cast<T&>(Single(const_cast<const EnumerableT&>(enumerable)));
    }

    template <Requirements::MountainEnumerable EnumerableT, typename T>
    const T& Single(const EnumerableT& enumerable)
    {
        if (GetSize(enumerable) != 1)
            THROW(InvalidOperationException{"Cannot get the only element of an enumerable that doesn't have only one element."});
        return *enumerable.begin();
    }

    template <Requirements::MountainEnumerable EnumerableT, typename T>
    void ForEach(EnumerableT& enumerable, const Operation<Meta::Identity<T>>& operation)
    {
        for (T& e : enumerable)
            operation(e);
    }

    template <Requirements::MountainEnumerable EnumerableT, typename T>
    void ForEach(const EnumerableT& enumerable, const Operation<const Meta::Identity<T>>& operation)
    {
        for (const T& e : enumerable)
            operation(e);
    }

    template <Requirements::MountainEnumerable EnumerableT, typename T, typename>
    void Sort(EnumerableT& enumerable)
    {
        return Sort(enumerable, CompareLess<T>);
    }

    template <Requirements::MountainEnumerable EnumerableT, typename T, typename>
    void Sort(EnumerableT& enumerable, const Comparer<Meta::Identity<T>>& comparer)
    {
        std::ranges::sort(enumerable, comparer);
    }

    template <Requirements::MountainEnumerable EnumerableT>
    bool_t IsValidIndex(const EnumerableT& enumerable, const size_t index)
    {
        return !IsEmpty(enumerable) && index < GetSize(enumerable);
    }
}
