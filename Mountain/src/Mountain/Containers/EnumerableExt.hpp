#pragma once

#include "Mountain/Core.hpp"
#include "Mountain/Containers/FunctionTypes.hpp"
#include "Mountain/Utils/Requirements.hpp"

#define ENUMERABLE_EXTENSIONS_DEFINITIONS(type) \
    [[nodiscard]] \
    bool_t All(const Predicate<Type>& predicate) const { return ::Mountain::All(*this, predicate); } \
    \
    [[nodiscard]] \
    bool_t Any(const Predicate<Type>& predicate) const { return ::Mountain::Any(*this, predicate); } \
    \
    template <typename T, typename = Meta::EnableIf<Meta::IsEqualityComparableWith<T, Type>>> \
    [[nodiscard]] \
    bool_t Contains(const T& element) const { return ::Mountain::Contains(*this, element); } \
    \
    [[nodiscard]] \
    List<Type> FindAll(const Predicate<Type>& predicate) const { return ::Mountain::FindAll(*this, predicate); } \
    \
    [[nodiscard]] \
    Type& First() { return ::Mountain::First(*this); } \
    \
    [[nodiscard]] \
    const Type& First() const { return ::Mountain::First(*this); } \
    \
    [[nodiscard]] \
    Type& Last() { return ::Mountain::Last(*this); } \
    \
    [[nodiscard]] \
    const Type& Last() const { return ::Mountain::Last(*this); } \
    \
    [[nodiscard]] \
    Type& Single() { return ::Mountain::Single(*this); } \
    \
    [[nodiscard]] \
    const Type& Single() const { return ::Mountain::Single(*this); } \
    \
    void ForEach(const Operation<Type>& operation) { return ::Mountain::ForEach(*this, operation); } \
    \
    void ForEach(const Operation<const Type>& operation) const { return ::Mountain::ForEach(*this, operation); } \
    \
    template <typename = Meta::EnableIf<Meta::IsSortable<Iterator, Comparer<T>, Projection<T>>>> \
    void Sort() { return ::Mountain::Sort(*this); } \
    \
    template <typename = Meta::EnableIf<Meta::IsSortable<Iterator, Comparer<T>, Projection<T>>>> \
    void Sort(const Comparer<Type>& comparer) { return ::Mountain::Sort(*this, comparer); }

namespace Mountain
{
    template <Concepts::DynamicContainerType T>
    class List;

    /// @brief Determines whether all elements of a sequence satisfy a condition.
    template <Requirements::MountainEnumerable EnumerableT,
        typename T = Meta::MountainEnumerableType<EnumerableT>>
    [[nodiscard]]
    bool_t All(const EnumerableT& enumerable, const Predicate<Meta::Identity<T>>& predicate);

    /// @brief Determines whether any element of a sequence satisfies a condition.
    template <Requirements::MountainEnumerable EnumerableT,
        typename T = Meta::MountainEnumerableType<EnumerableT>>
    [[nodiscard]]
    bool_t Any(const EnumerableT& enumerable, const Predicate<Meta::Identity<T>>& predicate);

    template <Requirements::MountainEnumerable EnumerableT,
        typename T,
        typename = Meta::EnableIf<Meta::IsEqualityComparableWith<T, Meta::MountainEnumerableType<EnumerableT>>>>
    [[nodiscard]]
    bool_t Contains(const EnumerableT& enumerable, const T& element);

    template <Requirements::MountainEnumerable EnumerableT,
        typename T = Meta::MountainEnumerableType<EnumerableT>>
    [[nodiscard]]
    List<T> FindAll(const EnumerableT& enumerable, const Predicate<Meta::Identity<T>>& predicate);

    template <Requirements::MountainEnumerable EnumerableT,
        typename T = Meta::MountainEnumerableType<EnumerableT>>
    [[nodiscard]]
    std::optional<T&> FindFirst(EnumerableT& enumerable, const Predicate<Meta::Identity<T>>& predicate);

    template <Requirements::MountainEnumerable EnumerableT,
        typename T = Meta::MountainEnumerableType<EnumerableT>>
    [[nodiscard]]
    std::optional<const T&> FindFirst(const EnumerableT& enumerable, const Predicate<Meta::Identity<T>>& predicate);

    template <Requirements::MountainEnumerable EnumerableT,
        typename T = Meta::MountainEnumerableType<EnumerableT>>
    [[nodiscard]]
    std::optional<T&> FindLast(EnumerableT& enumerable, const Predicate<Meta::Identity<T>>& predicate);

    template <Requirements::MountainEnumerable EnumerableT,
        typename T = Meta::MountainEnumerableType<EnumerableT>>
    [[nodiscard]]
    std::optional<const T&> FindLast(const EnumerableT& enumerable, const Predicate<Meta::Identity<T>>& predicate);

    /// @brief Returns the first element of a sequence.
    template <Requirements::MountainEnumerable EnumerableT,
        typename T = Meta::MountainEnumerableType<EnumerableT>>
    [[nodiscard]]
    T& First(EnumerableT& enumerable);

    /// @brief Returns the first element of a sequence.
    template <Requirements::MountainEnumerable EnumerableT,
        typename T = Meta::MountainEnumerableType<EnumerableT>>
    [[nodiscard]]
    const T& First(const EnumerableT& enumerable);

    /// @brief Returns the last element of a sequence.
    template <Requirements::MountainEnumerable EnumerableT,
        typename T = Meta::MountainEnumerableType<EnumerableT>>
    [[nodiscard]]
    T& Last(EnumerableT& enumerable);

    /// @brief Returns the last element of a sequence.
    template <Requirements::MountainEnumerable EnumerableT,
        typename T = Meta::MountainEnumerableType<EnumerableT>>
    [[nodiscard]]
    const T& Last(const EnumerableT& enumerable);

    /// @brief Returns the only element of a sequence and throws an exception if there is not exactly one element in the sequence.
    template <Requirements::MountainEnumerable EnumerableT,
        typename T = Meta::MountainEnumerableType<EnumerableT>>
    [[nodiscard]]
    T& Single(EnumerableT& enumerable);

    /// @brief Returns the only element of a sequence and throws an exception if there is not exactly one element in the sequence.
    template <Requirements::MountainEnumerable EnumerableT,
        typename T = Meta::MountainEnumerableType<EnumerableT>>
    [[nodiscard]]
    const T& Single(const EnumerableT& enumerable);

    template <Requirements::MountainEnumerable EnumerableT,
        typename T = Meta::MountainEnumerableType<EnumerableT>>
    void ForEach(EnumerableT& enumerable, const Operation<Meta::Identity<T>>& operation);

    template <Requirements::MountainEnumerable EnumerableT,
        typename T = Meta::MountainEnumerableType<EnumerableT>>
    void ForEach(const EnumerableT& enumerable, const Operation<const Meta::Identity<T>>& operation);

    template <Requirements::MountainEnumerable EnumerableT,
        typename T = Meta::MountainEnumerableType<EnumerableT>,
        typename = Meta::EnableIf<Meta::IsSortable<typename EnumerableT::Iterator, Comparer<T>, Projection<T>>>>
    void Sort(EnumerableT& enumerable);

    template <Requirements::MountainEnumerable EnumerableT,
        typename T = Meta::MountainEnumerableType<EnumerableT>,
        typename = Meta::EnableIf<Meta::IsSortable<typename EnumerableT::Iterator, Comparer<T>, Projection<T>>>>
    void Sort(EnumerableT& enumerable, const Comparer<Meta::Identity<T>>& comparer);
}

// Start of EnumerableExt.inl

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
        for (const T& e : enumerable)
        {
            if (predicate(e))
                return true;
        }

        return false;
    }

    template <Requirements::MountainEnumerable EnumerableT, typename T, typename>
    bool_t Contains(const EnumerableT& enumerable, const T& element)
    {
        return Any(enumerable, [&](const Meta::MountainEnumerableType<EnumerableT>& e) { return e == element; });
    }

    template <Requirements::MountainEnumerable EnumerableT>
    size_t GetSize(const EnumerableT& enumerable)
    {
        return enumerable.GetEndConstIterator() - enumerable.GetBeginConstIterator();
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
    std::optional<T&> FindFirst(EnumerableT& enumerable, const Predicate<Meta::Identity<T>>& predicate)
    {
        for (T& e : enumerable)
        {
            if (predicate(e))
                return e;
        }

        return {};
    }

    template <Requirements::MountainEnumerable EnumerableT, typename T>
    std::optional<const T&> FindFirst(const EnumerableT& enumerable, const Predicate<Meta::Identity<T>>& predicate)
    {
        for (const T& e : enumerable)
        {
            if (predicate(e))
                return e;
        }

        return {};
    }

    template <Requirements::MountainEnumerable EnumerableT, typename T>
    std::optional<T&> FindLast(EnumerableT& enumerable, const Predicate<Meta::Identity<T>>& predicate)
    {
        for (typename EnumerableT::Iterator it = enumerable.GetEndIterator() - 1; it + 1 != enumerable.GetBeginIterator(); it--)
        {
            T& value = *it;
            if (predicate(value))
                return value;
        }

        return {};
    }

    template <Requirements::MountainEnumerable EnumerableT, typename T>
    std::optional<const T&> FindLast(const EnumerableT& enumerable, const Predicate<Meta::Identity<T>>& predicate)
    {
        for (typename EnumerableT::ConstIterator it = enumerable.GetEndConstIterator() - 1; it + 1 != enumerable.GetBeginConstIterator(); it--)
        {
            const T& value = *it;
            if (predicate(value))
                return value;
        }

        return {};
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
        return *enumerable.GetBeginIterator();
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
        return *--enumerable.GetEndIterator();
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
        return *enumerable.GetBeginIterator();
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
        return Sort(enumerable, CompareLess);
    }

    template <Requirements::MountainEnumerable EnumerableT, typename T, typename>
    void Sort(EnumerableT& enumerable, const Comparer<Meta::Identity<T>>& comparer)
    {
        std::ranges::sort(enumerable, comparer);
    }
}
