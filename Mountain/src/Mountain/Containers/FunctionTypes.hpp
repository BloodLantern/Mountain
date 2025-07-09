#pragma once

#include "Mountain/Core.hpp"

#include "Mountain/Utils/MetaProgramming.hpp"

namespace Mountain
{
    template <typename... Args>
    using Action = std::function<void(Args...)>;

    template <typename T>
    using Predicate = std::function<bool_t(const T& element)>;

    template <typename T>
    using Operation = std::function<void(T& element)>;
    /// @brief Deletes the given element
    template <Concepts::Pointer T>
    const Operation<T> OperationDelete = [](const T& element) { delete element; };

    /// @brief Comparer function that returns @c true if @p lhs is considered less than @p rhs.
    template <typename T>
    using Comparer = std::function<bool_t(const T& lhs, const T& rhs)>;

    template <typename T>
    const Comparer<T> CompareLess = [](const T& lhs, const T& rhs) -> bool_t { return lhs < rhs; };

    template <typename T>
    using Projection = std::function<T(T)>;

    template <typename T>
    constexpr T Identity(T t) { return t; };
}
