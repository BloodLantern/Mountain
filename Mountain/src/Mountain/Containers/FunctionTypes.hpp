#pragma once

#include "Mountain/Core.hpp"

namespace Mountain
{
    template <typename T>
    using Predicate = std::function<bool_t(const T& element)>;

    template <typename T>
    using Operation = std::function<void(T& element)>;

    /// @brief Comparer function that returns @c true if @p lhs is considered less than @p rhs.
    template <typename T>
    using Comparer = std::function<bool_t(const T& lhs, const T& rhs)>;

    template <typename T>
    constexpr Comparer<T> CompareLess = [](const T& lhs, const T& rhs) -> bool_t { return lhs < rhs; };

    template <typename T>
    using Projection = std::function<T(T)>;

    template <typename T>
    constexpr Projection<T> Identity = [](const T& t) -> T { return t; };
}
