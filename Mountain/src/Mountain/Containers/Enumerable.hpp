#pragma once

#include "Mountain/Core.hpp"
#include "Mountain/Containers/Enumerator.hpp"

namespace Mountain
{
    template <typename T>
    interface IEnumerable
    {
        using Type = T;

        ATTRIBUTE_NODISCARD
        virtual EnumeratorWrapper<T> begin() = 0;

        ATTRIBUTE_NODISCARD
        virtual EnumeratorWrapper<T> end() = 0;

        ATTRIBUTE_NODISCARD
        virtual EnumeratorWrapper<T> cbegin() const = 0;

        ATTRIBUTE_NODISCARD
        virtual EnumeratorWrapper<T> cend() const = 0;

        ATTRIBUTE_NODISCARD
        virtual EnumeratorWrapper<T> begin() const = 0;

        ATTRIBUTE_NODISCARD
        virtual EnumeratorWrapper<T> end() const = 0;
    };
}
