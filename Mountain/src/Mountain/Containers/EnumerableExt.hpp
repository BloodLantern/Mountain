#pragma once

#include "Mountain/Core.hpp"
#include "Mountain/Utils/Requirements.hpp"

namespace Mountain
{
    /// @brief Refers to the type @p EnumerableT enumerates on.
    template <Requirements::Enumerable EnumerableT>
    using EnumerableType = typename EnumerableT::Iterator::Type;

    template <typename T>
    using Predicate = bool_t(const T& element);

    template <Requirements::Enumerable EnumerableT>
    [[nodiscard]]
    bool_t All(const EnumerableT& enumerable, Predicate<EnumerableType<EnumerableT>> predicate);

    template <Requirements::Enumerable EnumerableT>
    [[nodiscard]]
    bool_t Any(const EnumerableT& enumerable, Predicate<EnumerableType<EnumerableT>> predicate);
}
