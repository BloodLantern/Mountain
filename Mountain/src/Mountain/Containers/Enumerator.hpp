#pragma once

#include "Mountain/Core.hpp"

namespace Mountain
{
    template <typename T, class Enumerator>
    interface IEnumeratorBase
    {
    private:
        IEnumeratorBase() = default;
        friend Enumerator;

    public:
        /// @brief Gets the element in the collection at the current position of the enumerator.
        [[nodiscard]]
        virtual T* GetCurrent() const = 0;

        /// @brief Advances the enumerator to the next element of the collection.
        /// @returns @c true if the enumerator was successfully advanced to the next element;
        /// @c false if the enumerator has passed the end of the collection.
        virtual bool MoveNext() = 0;

        /// @brief Sets the enumerator to its initial position, which is before the first element in the collection.
        virtual void Reset() = 0;

        /// @brief Equivalent of @c GetCurrent().
        [[nodiscard]]
        virtual T* operator->() const = 0;

        virtual Enumerator& operator++() = 0;

        virtual const Enumerator& operator++(int) = 0;
    };

    /// @brief Supports a simple iteration over a non-templated container.
    interface INonTemplatedEnumerator : IEnumeratorBase<void, INonTemplatedEnumerator>
    {
    };

    /// @brief Supports a simple iteration over a templated container.
    /// @tparam T The type to iterate on.
    template <typename T>
    interface IEnumerator : IEnumeratorBase<T, IEnumerator<T>>
    {
        /// @brief Dereferences this enumerator, returning a reference to the current object.
        [[nodiscard]]
        virtual T& operator*() const = 0;
    };
}
