#pragma once

#include "Mountain/core.hpp"

namespace Mountain
{
    /// @brief Supports a simple iteration over a non-templated container.
    interface IDefaultEnumerator
    {
        /// @brief Gets the element in the collection at the current position of the enumerator.
        [[nodiscard]]
        virtual void* GetCurrent() const = 0;

        /// @brief Advances the enumerator to the next element of the collection.
        /// @returns @c true if the enumerator was successfully advanced to the next element;
        /// @c false if the enumerator has passed the end of the collection.
        [[nodiscard]]
        virtual bool MoveNext() = 0;

        /// @brief Sets the enumerator to its initial position, which is before the first element in the collection.
        virtual void Reset() = 0;

        /// @brief Equivalent of @c GetCurrent().
        virtual void* operator->() const = 0;

        virtual IDefaultEnumerator& operator++() const = 0;

        virtual const IDefaultEnumerator& operator++(int) const = 0;
    };

    /// @brief Supports a simple iteration over a templated container.
    /// @tparam T The type to iterate on.
    template <typename T>
    interface IEnumerator : IDefaultEnumerator
    {
        /// @brief Gets the element in the collection at the current position of the enumerator.
        T* GetCurrent() const override = 0;

        /// @brief Dereferences this enumerator, returning a reference to the current object.
        virtual T& operator*() const = 0;

        /// @brief Equivalent of @c GetCurrent().
        T* operator->() const override = 0;
    };
}
