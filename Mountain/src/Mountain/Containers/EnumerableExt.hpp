#pragma once

#include <functional>

#include "Mountain/Core.hpp"
#include "Mountain/Containers/List.hpp"
#include "Mountain/Utils/Requirements.hpp"

namespace Mountain
{
    /// @brief Determines whether all elements of a sequence satisfy a condition.
    template <Requirements::MountainEnumerable EnumerableT>
    [[nodiscard]]
    bool_t All(const EnumerableT& enumerable, EnumerablePredicate<Meta::Identity<EnumerableT>> predicate);

    /// @brief Determines whether any element of a sequence satisfies a condition.
    template <Requirements::MountainEnumerable EnumerableT>
    [[nodiscard]]
    bool_t Any(const EnumerableT& enumerable, EnumerablePredicate<Meta::Identity<EnumerableT>> predicate);

    template
    <
        Requirements::MountainEnumerable EnumerableT,
        typename T,
        typename = Meta::EnableIf<Meta::IsEqualityComparableWith<T, Meta::MountainEnumerableType<EnumerableT>>>
    >
    [[nodiscard]]
    bool_t Contains(const EnumerableT& enumerable, const T& element);

    template <Requirements::MountainEnumerable EnumerableT>
    [[nodiscard]]
    List<Meta::MountainEnumerableType<EnumerableT>>&& FindAll(const EnumerableT& enumerable, EnumerablePredicate<Meta::Identity<EnumerableT>> predicate);

    /// @brief Returns the first element of a sequence.
    template <Requirements::MountainEnumerable EnumerableT>
    [[nodiscard]]
    Meta::MountainEnumerableType<EnumerableT>& First(const EnumerableT& enumerable);

    /// @brief Returns the last element of a sequence.
    template <Requirements::MountainEnumerable EnumerableT>
    [[nodiscard]]
    Meta::MountainEnumerableType<EnumerableT>& Last(const EnumerableT& enumerable);

    /// @brief Returns the only element of a sequence, and throws an exception if there is not exactly one element in the sequence.
    template <Requirements::MountainEnumerable EnumerableT>
    [[nodiscard]]
    Meta::MountainEnumerableType<EnumerableT>& Single(const EnumerableT& enumerable);

    template <Requirements::MountainEnumerable EnumerableT>
    void ForEach(const EnumerableT& enumerable, EnumerableOperation<Meta::Identity<EnumerableT>> operation);

    template <Requirements::MountainEnumerable EnumerableT, typename = Meta::EnableIf<Requirements::Swappable<Meta::MountainEnumerableType<EnumerableT>>>>
    void Sort();

    template <Requirements::MountainEnumerable EnumerableT, typename = Meta::EnableIf<Requirements::Swappable<Meta::MountainEnumerableType<EnumerableT>>>>
    void Sort(EnumerableComparer<EnumerableT> comparer);
}

// Start of EnumerableExt.inl

namespace Mountain
{
    template <Requirements::MountainEnumerable EnumerableT>
    bool_t All(const EnumerableT& enumerable, EnumerablePredicate<Meta::Identity<EnumerableT>> predicate)
    {
        for (const auto& e : enumerable)
        {
            if (!predicate(e))
                return false;
        }

        return true;
    }

    template <Requirements::MountainEnumerable EnumerableT>
    bool_t Any(const EnumerableT& enumerable, EnumerablePredicate<Meta::Identity<EnumerableT>> predicate)
    {
        for (const auto& e : enumerable)
        {
            if (predicate(e))
                return true;
        }

        return false;
    }

    template <Requirements::MountainEnumerable EnumerableT, typename T, typename>
    bool_t Contains(const EnumerableT& enumerable, const T& element)
    {
        for (const auto& e : enumerable)
        {
            if (e == element)
                return true;
        }

        return false;
    }

    template <Requirements::MountainEnumerable EnumerableT>
    size_t GetSize(const EnumerableT& enumerable)
    {
        return enumerable.GetEndConstIterator() - enumerable.GetBeginConstIterator();
    }

    template <Requirements::MountainEnumerable EnumerableT>
    bool_t IsEmpty(const EnumerableT& enumerable)
    {
        return GetSize(enumerable) != 0;
    }

    template <Requirements::MountainEnumerable EnumerableT>
    List<Meta::MountainEnumerableType<EnumerableT>>&& FindAll(const EnumerableT& enumerable, EnumerablePredicate<Meta::Identity<EnumerableT>> predicate)
    {
        List<Meta::MountainEnumerableType<EnumerableT>> result;

        for (const auto& e : enumerable)
        {
            if (predicate(e))
                result.Add(e);
        }

        return std::move(result);
    }

    template <Requirements::MountainEnumerable EnumerableT>
    Meta::MountainEnumerableType<EnumerableT>& First(const EnumerableT& enumerable)
    {
        if (IsEmpty(enumerable))
            THROW(InvalidOperationException{"Cannot get the first element of an empty enumerable."});
        return *enumerable.GetBeginIterator();
    }

    template <Requirements::MountainEnumerable EnumerableT>
    Meta::MountainEnumerableType<EnumerableT>& Last(const EnumerableT& enumerable)
    {
        if (IsEmpty(enumerable))
            THROW(InvalidOperationException{"Cannot get the last element of an empty enumerable."});
        return *(enumerable.GetEndIterator() - 1);
    }

    template <Requirements::MountainEnumerable EnumerableT>
    Meta::MountainEnumerableType<EnumerableT>& Single(const EnumerableT& enumerable)
    {
        if (GetSize(enumerable) != 1)
            THROW(InvalidOperationException{"Cannot get the only element of an enumerable that doesn't have only one element."});
        return *enumerable.GetEndIterator();
    }

    template <Requirements::MountainEnumerable EnumerableT>
    void ForEach(const EnumerableT& enumerable, EnumerableOperation<Meta::Identity<EnumerableT>> operation)
    {
        for (auto& e : enumerable)
            operation(e);
    }
}
