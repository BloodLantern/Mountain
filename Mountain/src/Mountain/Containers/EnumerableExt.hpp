#pragma once

#include <functional>

#include "Mountain/Core.hpp"
#include "Mountain/Utils/Requirements.hpp"

namespace Mountain
{
    template <typename T>
    using Predicate = std::function<bool_t(const T& element)>;

    template <Requirements::MountainEnumerable T>
    using EnumerablePredicate = Predicate<Meta::MountainEnumerableType<T>>;

    template <typename T>
    using Operation = std::function<void(T& element)>;

    template <Requirements::MountainEnumerable T>
    using EnumerableOperation = Operation<Meta::MountainEnumerableType<T>>;

    /// @brief Comparer function that returns @c true if @p lhs is considered less than @p rhs.
    template <typename T>
    using Comparer = std::function<bool_t(const T& lhs, const T& rhs)>;

    template <Requirements::MountainEnumerable T>
    using EnumerableComparer = Comparer<Meta::MountainEnumerableType<T>>;

    /// @brief Determines whether all elements of a sequence satisfy a condition.
    template <Requirements::MountainEnumerable EnumerableT>
    [[nodiscard]]
    bool_t All(const EnumerableT& enumerable, EnumerablePredicate<Meta::Identity<EnumerableT>> predicate);

    /// @brief Determines whether any element of a sequence satisfies a condition.
    template <Requirements::MountainEnumerable EnumerableT>
    [[nodiscard]]
    bool_t Any(const EnumerableT& enumerable, EnumerablePredicate<Meta::Identity<EnumerableT>> predicate);

    /// @brief Determines whether a sequence contains any elements.
    template <Requirements::MountainEnumerable EnumerableT>
    [[nodiscard]]
    bool_t Any(const EnumerableT& enumerable);

    template
    <
        Requirements::MountainEnumerable EnumerableT,
        typename T,
        typename = Meta::EnableIf<Meta::IsEqualityComparableWith<T, Meta::EnumerableType<EnumerableT>>>
    >
    [[nodiscard]]
    bool_t Contains(const EnumerableT& enumerable, const T& element);

    template <Requirements::MountainEnumerable EnumerableT>
    [[nodiscard]]
    EnumerableT FindAll(const EnumerableT& enumerable, EnumerablePredicate<Meta::Identity<EnumerableT>> predicate);

    template <Requirements::MountainEnumerable EnumerableT>
    [[nodiscard]]
    Meta::MountainEnumerableType<EnumerableT>& First(const EnumerableT& enumerable);

    template <Requirements::MountainEnumerable EnumerableT>
    [[nodiscard]]
    Meta::MountainEnumerableType<EnumerableT>& Last(const EnumerableT& enumerable);

    template <Requirements::MountainEnumerable EnumerableT>
    [[nodiscard]]
    Meta::MountainEnumerableType<EnumerableT>& Single(const EnumerableT& enumerable);

    template <Requirements::MountainEnumerable EnumerableT>
    void ForEach(const EnumerableT& enumerable, EnumerableOperation<Meta::Identity<EnumerableT>> operation);
}
