#pragma once

#include <functional>
#include <vector>

#include "Mountain/Core.hpp"

#include "Mountain/Containers/Enumerable.hpp"
#include "Mountain/Containers/Enumerator.hpp"
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
    class List : IEnumerable<T>
    {
        static constexpr size_t DefaultCapacity = 0;

    public:
        struct Enumerator : IEnumerator<T>
        {
            explicit Enumerator(List& list);
            virtual ~Enumerator() = default;
            DEFAULT_COPY_MOVE_OPERATIONS(Enumerator)

            // IEnumeratorBase implementation

            [[nodiscard]]
            T* GetCurrent() const override;
            bool MoveNext() override;
            void Reset() override;
            [[nodiscard]]
            T* operator->() const override;
            IEnumerator<T>& operator++() override;
            const IEnumerator<T>& operator++(int) override;

            // IEnumerator implementation

            [[nodiscard]]
            T& operator*() const override;

        private:
            List* m_List = nullptr;
            size_t m_NextIndex = 0;
            T* m_Current = nullptr;
            uint32_t m_Version;

            bool MoveNextRare();
        };


        // IEnumerable implementation

        [[nodiscard]]
        std::shared_ptr<IEnumerator<T>> GetEnumerator() override;


        /// @brief The type of the List<T>. Refers to T.
        using Type = T;

    private:
        uint32_t m_Version = 0;
    };
}

// Start of List.inl

namespace Mountain
{
    template <typename T>
    List<T>::Enumerator::Enumerator(List& list)
        : m_List(&list)
        , m_Version(list.m_Version)
    {
    }

    template <typename T>
    bool List<T>::Enumerator::MoveNext()
    {
        if (m_Version == m_List->m_Version && m_NextIndex < m_List->GetSize())
        {
            //m_Current = &m_List->operator[](m_NextIndex); FIXME
            m_NextIndex++;
            return true;
        }

        return MoveNextRare();
    }

    template <typename T>
    void List<T>::Enumerator::Reset()
    {
        m_NextIndex = 0;
        m_Current = nullptr;
    }

    template <typename T>
    IEnumerator<T>& List<T>::Enumerator::operator++()
    {
        MoveNext();
        return *this;
    }

    template <typename T>
    const IEnumerator<T>& List<T>::Enumerator::operator++(int)
    {
        MoveNext();
        return *this;
    }

    template <typename T>
    T* List<T>::Enumerator::GetCurrent() const
    {
        return m_Current;
    }

    template <typename T>
    T& List<T>::Enumerator::operator*() const
    {
        return *GetCurrent();
    }

    template <typename T>
    T* List<T>::Enumerator::operator->() const
    {
        return GetCurrent();
    }

    template <typename T>
    bool List<T>::Enumerator::MoveNextRare()
    {
        if (m_Version != m_List->m_Version)
            THROW(ThrowHelper::ContainerModifiedException());

        m_NextIndex = m_List->GetSize() + 1;
        m_Current = nullptr;
        return false;
    }

    template <typename T>
    std::shared_ptr<IEnumerator<T>> List<T>::GetEnumerator()
    {
        return std::make_shared<Enumerator>(*this);
    }
}
