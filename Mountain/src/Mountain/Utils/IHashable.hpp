#pragma once

#include "Mountain/Core.hpp"
#include "Mountain/Utils/MetaProgramming.hpp"

namespace Mountain
{
    interface IHashable
    {
        [[nodiscard]]
        virtual size_t GetHashCode() const = 0;
    };
}

/// @brief @c std::hash template specialization for the @c Mountain::IHashable interface.
template<Mountain::Concepts::Hashable HashableT>
struct std::hash<HashableT>  // NOLINT(cert-dcl58-cpp)
{
    /// @brief Hashes the given @c Mountain::IHashable.
    std::size_t operator()(const HashableT& p) const noexcept { return p.GetHashCode(); }
};
