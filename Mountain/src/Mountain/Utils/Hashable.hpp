#pragma once

#include "Mountain/Core.hpp"
#include "Mountain/Utils/MetaProgramming.hpp"

/// @brief @c std::hash template specialization for the types that support @c GetHashCode().
/// @details The real goal of this formatter specialization is to allow any type that provides a member function @c GetHashCode()
/// to be used in a call to @c std::hash().
template<Mountain::Concepts::Hashable HashableT>
struct std::hash<HashableT>  // NOLINT(cert-dcl58-cpp)
{
    /// @brief Hashes the given type supporting @c GetHashCode().
    std::size_t operator()(const HashableT& p) const noexcept { return p.GetHashCode(); }
};
