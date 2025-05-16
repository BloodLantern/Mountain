#pragma once

#include <memory>

#include "Mountain/core.hpp"
#include "Mountain/Containers/Enumerator.hpp"

namespace Mountain
{
    /// @brief Exposes an enumerator, which supports a simple iteration over a non-templated container.
    interface IDefaultEnumerable
    {
        virtual std::shared_ptr<IDefaultEnumerator> GetDefaultEnumerator() = 0;
    };

    /// @brief Exposes the enumerator, which supports a simple iteration over a container of a specified type.
    /// @tparam T The type the enumerator iterates on.
    template <typename T>
    interface IEnumerable : IDefaultEnumerable
    {
        virtual std::shared_ptr<IEnumerator<T>> GetEnumerator() = 0;
    };
}
