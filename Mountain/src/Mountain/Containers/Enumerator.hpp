#pragma once

#include "Mountain/Core.hpp"

namespace Mountain
{
    template <typename T>
    interface IEnumerator;

    template <typename T>
    struct ATTRIBUTE_PASS_BY_VALUE EnumeratorWrapper
    {
        using Type = T;

        EnumeratorWrapper();
        // ReSharper disable once CppNonExplicitConvertingConstructor
        EnumeratorWrapper(IEnumerator<T>* enumerator);
        // ReSharper disable once CppNonExplicitConvertingConstructor
        EnumeratorWrapper(std::shared_ptr<IEnumerator<T>> enumerator);

        /// @brief Gets the element in the container at the current position of the iterator.
        ATTRIBUTE_NODISCARD
        const T* GetCurrent() const;

        /// @brief Sets the iterator to its initial position, which is on the first element in the collection.
        void Reset();

        /// @brief Dereferences this iterator, returning a reference to the current object.
        ATTRIBUTE_NODISCARD
        const T& operator*() const;

        /// @brief Equivalent of @c GetCurrent().
        ATTRIBUTE_NODISCARD
        const T* operator->() const;

        ATTRIBUTE_NODISCARD
        const T& operator[](ptrdiff_t offset) const;

        /// @brief Moves to the next element without bounds checking.
        EnumeratorWrapper<IEnumerator<T>>& operator++();

        /// @brief Moves to the next element without bounds checking.
        EnumeratorWrapper<IEnumerator<T>> operator++(int);

        /// @brief Moves to the previous element without bounds checking.
        EnumeratorWrapper<IEnumerator<T>>& operator--();

        /// @brief Moves to the previous element without bounds checking.
        EnumeratorWrapper<IEnumerator<T>> operator--(int);

        EnumeratorWrapper<IEnumerator<T>>& operator+=(ptrdiff_t rhs);

        EnumeratorWrapper<IEnumerator<T>>& operator-=(ptrdiff_t rhs);

        ATTRIBUTE_NODISCARD
        bool_t operator==(const EnumeratorWrapper<IEnumerator<T>>& other) const;

        ATTRIBUTE_NODISCARD
        std::strong_ordering operator<=>(const EnumeratorWrapper<IEnumerator<T>>& other) const;

        GETTER(std::shared_ptr<IEnumerator<T>>, Enumerator, m_Enumerator)

    private:
        std::shared_ptr<IEnumerator<T>> m_Enumerator;
    };

    template <typename T>
    ATTRIBUTE_NODISCARD
    constexpr EnumeratorWrapper<T> operator+(ptrdiff_t lhs, EnumeratorWrapper<T> rhs) noexcept;

    template <typename T>
    ATTRIBUTE_NODISCARD
    constexpr EnumeratorWrapper<T> operator+(EnumeratorWrapper<T> lhs, ptrdiff_t rhs) noexcept;

    template <typename T>
    ATTRIBUTE_NODISCARD
    constexpr ptrdiff_t operator-(const EnumeratorWrapper<T>& lhs, const EnumeratorWrapper<T>& rhs);

    template <typename T>
    ATTRIBUTE_NODISCARD
    constexpr EnumeratorWrapper<T> operator-(EnumeratorWrapper<T> lhs, ptrdiff_t rhs) noexcept;

    /// @brief Checks whether @p lhs is compatible with @p rhs, e.g., if both are iterating over the same enumerable.
    template <typename T>
    ATTRIBUTE_NODISCARD
    constexpr bool_t CheckCompatible(const EnumeratorWrapper<T>& lhs, const EnumeratorWrapper<T>& rhs) noexcept;

    /// @brief Checks whether @p lhs is compatible with @p rhs and throws an exception if they aren't compatible.
    template <typename T>
    constexpr void CheckCompatibleThrow(const EnumeratorWrapper<T>& lhs, const EnumeratorWrapper<T>& rhs);

    template <typename T>
    interface IEnumerator
    {
        using Type = T;

        /// @brief Gets the element in the container at the current position of the iterator.
        ATTRIBUTE_NODISCARD
        virtual const T* GetCurrent() const = 0;

        /// @brief Sets the iterator to its initial position, which is on the first element in the collection.
        virtual void Reset() = 0;

        /// @brief Dereferences this iterator, returning a reference to the current object.
        ATTRIBUTE_NODISCARD
        virtual const T& operator*() const = 0;

        /// @brief Equivalent of @c GetCurrent().
        ATTRIBUTE_NODISCARD
        virtual const T* operator->() const = 0;

        ATTRIBUTE_NODISCARD
        virtual const T& operator[](ptrdiff_t offset) const = 0;

        /// @brief Moves to the next element without bounds checking.
        virtual IEnumerator& operator++() = 0;

        /// @brief Moves to the next element without bounds checking.
        virtual EnumeratorWrapper<T> operator++(int) = 0;

        /// @brief Moves to the previous element without bounds checking.
        virtual IEnumerator& operator--() = 0;

        /// @brief Moves to the previous element without bounds checking.
        virtual EnumeratorWrapper<T> operator--(int) = 0;

        virtual IEnumerator& operator+=(ptrdiff_t rhs) = 0;

        virtual IEnumerator& operator-=(ptrdiff_t rhs) = 0;

        ATTRIBUTE_NODISCARD
        virtual bool_t operator==(const IEnumerator& other) const = 0;

        ATTRIBUTE_NODISCARD
        virtual std::strong_ordering operator<=>(const IEnumerator&) const = 0;
    };
}

// Start of Enumerator.inl

namespace Mountain
{
    template <typename T>
    EnumeratorWrapper<T>::EnumeratorWrapper() : m_Enumerator{std::make_shared<T>()} {}

    template <typename T>
    EnumeratorWrapper<T>::EnumeratorWrapper(IEnumerator<T>* enumerator) : m_Enumerator{enumerator} {}

    template <typename T>
    EnumeratorWrapper<T>::EnumeratorWrapper(std::shared_ptr<IEnumerator<T>> enumerator) : m_Enumerator{enumerator} {}

    template <typename T>
    const T* EnumeratorWrapper<T>::GetCurrent() const { return m_Enumerator->GetCurrent(); }

    template <typename T>
    void EnumeratorWrapper<T>::Reset() { return m_Enumerator->Reset(); }

    template <typename T>
    const T& EnumeratorWrapper<T>::operator*() const { return **m_Enumerator; }

    template <typename T>
    const T* EnumeratorWrapper<T>::operator->() const { return GetCurrent(); }

    template <typename T>
    const T& EnumeratorWrapper<T>::operator[](ptrdiff_t offset) const { return m_Enumerator[offset]; }

    template <typename T>
    EnumeratorWrapper<IEnumerator<T>>& EnumeratorWrapper<T>::operator++() { return ++*m_Enumerator; }

    template <typename T>
    EnumeratorWrapper<IEnumerator<T>> EnumeratorWrapper<T>::operator++(int) { return (*m_Enumerator)++; }

    template <typename T>
    EnumeratorWrapper<IEnumerator<T>>& EnumeratorWrapper<T>::operator--() { return --*m_Enumerator; }

    template <typename T>
    EnumeratorWrapper<IEnumerator<T>> EnumeratorWrapper<T>::operator--(int) { return (*m_Enumerator)--; }

    template <typename T>
    EnumeratorWrapper<IEnumerator<T>>& EnumeratorWrapper<T>::operator+=(ptrdiff_t rhs) { return *m_Enumerator += rhs; }

    template <typename T>
    EnumeratorWrapper<IEnumerator<T>>& EnumeratorWrapper<T>::operator-=(ptrdiff_t rhs) { return *m_Enumerator -= rhs; }

    template <typename T>
    bool_t EnumeratorWrapper<T>::operator==(const EnumeratorWrapper<IEnumerator<T>>& other) const { return *m_Enumerator == *other.m_Enumerator; }

    template <typename T>
    std::strong_ordering EnumeratorWrapper<T>::operator<=>(const EnumeratorWrapper<IEnumerator<T>>& other) const { return *m_Enumerator <=> *other.m_Enumerator; }
}
