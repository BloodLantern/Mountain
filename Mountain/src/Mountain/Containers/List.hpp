#pragma once

#include "Mountain/Core.hpp"
#include "Mountain/Containers/ContiguousIterator.hpp"
#include "Mountain/Exceptions/ThrowHelper.hpp"

/// @file List.hpp
/// @brief Defines the Mountain::List class.

namespace Mountain
{
    // ReSharper disable once CppPolymorphicClassWithNonVirtualPublicDestructor
    /// @brief A dynamic array implementation.
    ///
    /// A more user-friendly list than @c std::vector, based on how @c %List is done in C#
    /// The internal structure and workings are similar to how std::vector works, it uses a capacity that grows exponentially based on powers of 2
    ///
    /// @tparam T Type stored
    ///
    /// @see <a href="https://en.cppreference.com/w/cpp/container/vector">std::vector</a>
    /// @see <a href="https://learn.microsoft.com/en-us/dotnet/api/system.collections.generic.list-1">C# List</a>
    template <typename T>
    class List
    {
    public:
        /// @brief The type of the List<T>. Refers to T.
        using Type = T;
        using Iterator = ContiguousIterator<T>;

        /// @brief Get the element at the given index with bounds checking.
        [[nodiscard]]
        constexpr T& At(size_t index) const;

        /// @brief Get the size of the array. Returns @c Size.
        [[nodiscard]]
        constexpr size_t GetSize() const noexcept;

        [[nodiscard]]
        constexpr T* GetData() const noexcept;

        /// @brief Get the element at the given index without bounds checking.
        [[nodiscard]]
        constexpr T& operator[](size_t index) const noexcept;

        [[nodiscard]]
        constexpr Iterator GetBeginIterator() const noexcept;

        [[nodiscard]]
        constexpr Iterator GetEndIterator() const noexcept;

        [[nodiscard]]
        constexpr Iterator begin() const noexcept;

        [[nodiscard]]
        constexpr Iterator end() const noexcept;

    private:
        T* m_Data = nullptr;
        size_t m_Size = 0;
    };
}

// Start of List.inl

namespace Mountain
{

}
