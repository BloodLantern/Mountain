#pragma once

#include <format>
#include <sstream>
#include <utility>

#include "Mountain/Core.hpp"
#include "Mountain/Utils/ReferenceCounter.hpp"
#include "Mountain/Utils/Requirements.hpp"

/// @file Pointer.hpp
/// @brief Defines the Mountain::Pointer class

namespace Mountain
{
    /// @brief Custom Mountain smart pointer.
    ///        Represents both a @c std::shared_ptr and a @c std::weak_ptr.
    ///
    /// While using @c std::weak_ptr, we realized that it was not very practical because a @c std::shared_ptr needs to be
    /// constructed from the former for the pointed type to be used.
    /// The @c Pointer type is meant to fix this issue by being both a strong and a weak shared pointer.
    ///
    /// The simplest way to create a Pointer to wrap your type is by using the forwarding variadic template function
    /// which allows you to do the following:
    /// @code
    /// struct Type { int i; explicit Type(int i) : i(i) {} };
    ///
    /// Pointer<Type> ptr = Pointer<Type>::New(7);
    /// @endcode
    /// ... and 7 will be forwarded as a parameter to the @c Type(int) constructor.
    ///
    /// There are three other ways of initializing a Pointer:
    /// @code
    /// // 1 - Default initialization of the Pointer: this wraps a nullptr
    /// Pointer<Type> ptr;
    ///
    /// // 2 - Default initialization of the wrapped value: this effectively calls the wrapped type's default constructor
    /// Pointer<Type> ptr = Pointer<Type>::New();
    ///
    /// // 3 - Manually set the Pointer to nullptr: this is actually the same as default initializing it
    /// Pointer<Type> ptr = nullptr;
    /// @endcode
    ///
    /// By default, creating a Pointer with constructor arguments from the pointed type allocates this type on the heap.
    /// Copying this instance of Pointer creates a new weak reference by default, meaning that the copy won't keep the raw
    /// pointer alive.
    /// When all the strong references go out of scope or are destroyed, the underlying pointed type is freed.
    /// A strong reference can still be created if needed, by calling either @c Pointer::CreateStrongReference(),
    /// @c Pointer::ToStrongReference(), or by creating a copy using the copy constructor
    /// and giving a @c true value to the second argument.
    ///
    /// @tparam T The type to point to. Most of the time, this shouldn't be a pointer type.
    ///
    /// @see <a href="https://en.cppreference.com/book/intro/smart_pointers">Smart Pointers</a>
    /// @see <a href="https://en.cppreference.com/w/cpp/memory/shared_ptr">std::shared_ptr</a>
    /// @see <a href="https://en.cppreference.com/w/cpp/memory/weak_ptr">std::weak_ptr</a>
    template <typename T>
    struct Pointer final
    {
        /// @brief The type of ReferenceCounter, and therefore the type this Pointer is pointing to.
        using Type = T;

        /// @brief Creates a Pointer, calling @c new with @p T and forwarding all given arguments to its constructor.
        template <typename... Args>
        static Pointer New(Args&&... args);

        /// @brief Creates a @ref Pointer with a default-initialized value.
        static Pointer New();

        /// @brief Creates an empty @ref Pointer without a reference counter and pointing to @c nullptr.
        Pointer() = default;

        /// @brief Creates a copy of another @ref Pointer, specifying whether it is a weak or strong reference.
        Pointer(const Pointer& other, bool_t strongReference = false);

        /// @brief Creates a Pointer by moving all the values of an existing one.
        Pointer(Pointer&& other) noexcept;

        // ReSharper disable once CppNonExplicitConvertingConstructor
        /// @brief Creates a Pointer from a @c nullptr.
        Pointer(nullptr_t);

        /// @brief Creates a copy of an existing Pointer of a different Type, specifying whether it is a strong reference.
        ///
        /// @tparam U The type of the existing Pointer. This type must be convertible to Type.
        template <typename U>
        explicit Pointer(const Pointer<U>& other, bool_t strongReference = false);

        /// @brief Creates a copy of an existing Pointer of a different Type, specifying whether it is a strong reference.
        template <typename U>
        explicit Pointer(Pointer<U>& other, bool_t strongReference = false);

        /// @brief Creates a Pointer by moving the value of another one of a different Type.
        template <typename U>
        explicit Pointer(Pointer<U>&& other) noexcept;

        /// @brief Destroys this Pointer, deallocating any memory if this is the last strong reference.
        ~Pointer();

        /// @brief Creates a new strong reference to this pointer.
        [[nodiscard]]
        Pointer CreateStrongReference() const;

        /// @brief Gets the underlying raw pointer.
        ///
        /// This is equivalent to calling Pointer::operator T*() const;
        [[nodiscard]]
        const T* Get() const;

        /// @brief Gets the underlying raw pointer.
        ///
        /// This is equivalent to calling Pointer::operator T*();
        [[nodiscard]]
        T* Get();

        /// @brief Returns whether this Pointer is @c nullptr.
        [[nodiscard]]
        bool_t IsValid() const;

        /// @brief Converts this @ref Pointer to a strong reference.
        void ToStrongReference();

        /// @brief Converts this @ref Pointer to a weak reference.
        void ToWeakReference();

        /// @brief Returns the underlying ReferenceCounter.
        [[nodiscard]]
        const ReferenceCounter<T>* GetReferenceCounter() const;

        /// @brief Returns whether this Pointer is holding a strong reference.
        [[nodiscard]]
        bool_t GetIsStrongReference() const;

        /// @brief Resets this Pointer to a @c nullptr.
        ///
        /// @warning
        /// This function is used internally and is not meant to be used except if you really know what you
        /// are doing. This doesn't free the potentially allocated memory. Use it at your own risks.
        void Reset();

        /// @brief Sets this Pointer to the values of @p other.
        Pointer& operator=(const Pointer& other);

        /// @brief Sets this Pointer to the values of @p other, moving all the data.
        Pointer& operator=(Pointer&& other) noexcept;

        /// @brief Sets this Pointer to @c nullptr.
        Pointer& operator=(nullptr_t);

        /// @brief Sets this Pointer to the values of @p other which is a Pointer of another Type.
        template <typename U>
        Pointer& operator=(const Pointer<U>& other);

        /// @brief Sets this Pointer to the values of @p other which is a Pointer of another Type, moving all the data.
        template <typename U>
        Pointer& operator=(Pointer<U>&& other) noexcept;

        /// @brief Converts this @c const Pointer to its underlying @c const raw pointer.
        [[nodiscard]]
        explicit operator const T*() const;

        /// @brief Converts this Pointer to its underlying raw pointer.
        [[nodiscard]]
        explicit operator T*();

        // ReSharper disable once CppNonExplicitConversionOperator
        /// @brief Converts this @ref Pointer to a @c bool_t the same way a raw pointer would.
        [[nodiscard]]
        operator bool_t() const;

        /// @brief Dereferences this Pointer, which gives a reference to the underlying Type.
        [[nodiscard]]
        T& operator*();

        /// @brief Dereferences this @c const Pointer, which gives a @c const reference to the underlying Type.
        [[nodiscard]]
        const T& operator*() const;

        /// @brief Dereferences this Pointer, which gives a reference to the underlying Type.
        [[nodiscard]]
        T* operator->();

        /// @brief Dereferences this @c const Pointer, which gives a @c const reference to the underlying Type.
        [[nodiscard]]
        const T* operator->() const;

        [[nodiscard]]
        std::string ToString() const;

        [[nodiscard]]
        size_t GetHashCode() const;

    private:
        ReferenceCounter<T>* m_ReferenceCounter = nullptr;

        bool_t m_IsStrongReference = false;

        explicit Pointer(ReferenceCounter<T>*&& referenceCounter, bool_t strongReference);

        void SetReferenceCounter(ReferenceCounter<T>* newReferenceCounter);

        void CheckReferenceCounterValid();
    };

    CHECK_REQUIREMENT(Requirements::StringConvertible, Pointer<Requirements::DefaultType>);
    CHECK_REQUIREMENT(Requirements::Hashable, Pointer<Requirements::DefaultType>);
}

// Start of Pointer.inl

namespace Mountain
{
    template <typename T>
    template <typename... Args>
    Pointer<T> Pointer<T>::New(Args&&... args)  // NOLINT(cppcoreguidelines-missing-std-forward)
    {
        return Pointer(new ReferenceCounter<T>(std::forward<Args>(args)...), true);
    }

    template <typename T>
    Pointer<T> Pointer<T>::New()
    {
        return Pointer(new ReferenceCounter<T>, true);
    }

    template <typename T>
    Pointer<T>::Pointer(const Pointer& other, const bool_t strongReference)
        : m_ReferenceCounter(other.m_ReferenceCounter)
        , m_IsStrongReference(strongReference)
    {
        if (!m_ReferenceCounter)
            return;

        if (strongReference)
            m_ReferenceCounter->IncStrong();
        else
            m_ReferenceCounter->IncWeak(this);
    }

    template <typename T>
    Pointer<T>::Pointer(Pointer&& other) noexcept
        : m_ReferenceCounter(std::move(other.m_ReferenceCounter))
        , m_IsStrongReference(other.m_IsStrongReference)
    {
        if (!m_ReferenceCounter)
            return;

        if (!m_IsStrongReference)
        {
            m_ReferenceCounter->DecWeak(&other);
            m_ReferenceCounter->IncWeak(this);
        }

        other.Reset();
    }

    template <typename T>
    Pointer<T>::Pointer(nullptr_t)
    {
    }

    template <typename T>
    template <typename U>
    Pointer<T>::Pointer(const Pointer<U>& other, const bool_t strongReference)
        : m_ReferenceCounter(reinterpret_cast<ReferenceCounter<T>*>(const_cast<ReferenceCounter<U>*>(other.GetReferenceCounter())))
        , m_IsStrongReference(strongReference)
    {
        if (!m_ReferenceCounter)
            return;

        if (strongReference)
            m_ReferenceCounter->IncStrong();
        else
            m_ReferenceCounter->IncWeak(this);
    }

    template <typename T>
    template <typename U>
    Pointer<T>::Pointer(Pointer<U>& other, const bool_t strongReference)
        : Pointer(const_cast<const Pointer<U>&>(other), strongReference)
    {
    }

    template <typename T>
    template <typename U>
    Pointer<T>::Pointer(Pointer<U>&& other) noexcept  // NOLINT(cppcoreguidelines-rvalue-reference-param-not-moved)
        : m_ReferenceCounter(reinterpret_cast<ReferenceCounter<T>*>(const_cast<ReferenceCounter<U>*>(std::move(other.GetReferenceCounter()))))
        , m_IsStrongReference(std::move(other.GetIsStrongReference()))
    {
        if (!m_ReferenceCounter)
            return;

        if (!m_IsStrongReference)
        {
            m_ReferenceCounter->DecWeak(reinterpret_cast<Pointer*>(&other));
            m_ReferenceCounter->IncWeak(this);
        }

        other.Reset();
    }

    template <typename T>
    Pointer<T>::~Pointer()
    {
        SetReferenceCounter(nullptr);
    }

    template <typename T>
    Pointer<T> Pointer<T>::CreateStrongReference() const
    {
        return Pointer(*this, true);
    }

    template <typename T>
    const T* Pointer<T>::Get() const
    {
        return m_ReferenceCounter->GetPointer();
    }

    template <typename T>
    T* Pointer<T>::Get()
    {
        return m_ReferenceCounter->GetPointer();
    }

    template <typename T>
    Pointer<T>& Pointer<T>::operator=(const Pointer& other)  // NOLINT(bugprone-unhandled-self-assignment)
    {
        if (this == &other)
            return *this;

        SetReferenceCounter(other.m_ReferenceCounter);
        if (m_ReferenceCounter)
            m_ReferenceCounter->IncWeak(this);

        return *this;
    }

    template <typename T>
    Pointer<T>& Pointer<T>::operator=(Pointer&& other) noexcept
    {
        if (this == &other)
            return *this;

        SetReferenceCounter(std::move(other.m_ReferenceCounter));
        m_IsStrongReference = other.m_IsStrongReference;

        if (m_ReferenceCounter && !m_IsStrongReference)
        {
            m_ReferenceCounter->DecWeak(&other);
            m_ReferenceCounter->IncWeak(this);
        }

        other.Reset();

        return *this;
    }

    template <typename T>
    Pointer<T>& Pointer<T>::operator=(nullptr_t)
    {
        SetReferenceCounter(nullptr);
        m_IsStrongReference = false;

        return *this;
    }

#ifndef DOXYGEN
    template <typename T>
    template <typename U>
    Pointer<T>& Pointer<T>::operator=(const Pointer<U>& other)
    {
        if (reinterpret_cast<const int8_t*>(this) == reinterpret_cast<const int8_t*>(&other))
            return *this;

        SetReferenceCounter(reinterpret_cast<ReferenceCounter<T>*>(const_cast<ReferenceCounter<U>*>(other.GetReferenceCounter())));
        m_ReferenceCounter->IncWeak(this);

        return *this;
    }

    template <typename T>
    template <typename U>
    Pointer<T>& Pointer<T>::operator=(Pointer<U>&& other) noexcept
    {
        if (reinterpret_cast<const int8_t*>(this) == reinterpret_cast<const int8_t*>(&other))
            return *this;

        SetReferenceCounter(reinterpret_cast<ReferenceCounter<T>*>(const_cast<ReferenceCounter<U>*>(other.GetReferenceCounter())));
        m_IsStrongReference = std::move(other.GetIsStrongReference());

        if (m_ReferenceCounter && !m_IsStrongReference)
        {
            m_ReferenceCounter->DecWeak(reinterpret_cast<const Pointer*>(&other));
            m_ReferenceCounter->IncWeak(this);
        }

        other.Reset();

        return *this;
    }
#endif

    template <typename T>
    Pointer<T>::operator const T*() const
    {
        if (m_ReferenceCounter)
            return m_ReferenceCounter->GetPointer();
        return nullptr;
    }

    template <typename T>
    Pointer<T>::operator T*()
    {
        if (m_ReferenceCounter)
            return m_ReferenceCounter->GetPointer();
        return nullptr;
    }

    template <typename T>
    Pointer<T>::operator bool_t() const { return IsValid(); }

    template <typename T>
    T& Pointer<T>::operator*()
    {
        ENSURE_NOT_NULL(m_ReferenceCounter);
        return *m_ReferenceCounter->GetPointer();
    }

    template <typename T>
    const T& Pointer<T>::operator*() const
    {
        ENSURE_NOT_NULL(m_ReferenceCounter);
        return *m_ReferenceCounter->GetPointer();
    }

    template <typename T>
    T* Pointer<T>::operator->()
    {
        ENSURE_NOT_NULL(m_ReferenceCounter);
        return m_ReferenceCounter->GetPointer();
    }

    template <typename T>
    const T* Pointer<T>::operator->() const
    {
        ENSURE_NOT_NULL(m_ReferenceCounter);
        return m_ReferenceCounter->GetPointer();
    }

    template <typename T>
    std::string Pointer<T>::ToString() const
    {
        return m_ReferenceCounter ? std::format("0x{}", std::bit_cast<size_t>(m_ReferenceCounter->GetPointer())) : "null";
    }

    template <typename T>
    size_t Pointer<T>::GetHashCode() const
    {
        const size_t h1 = std::hash<ReferenceCounter<T>*>{}(const_cast<ReferenceCounter<T>*>(m_ReferenceCounter));
        const size_t h2 = std::hash<bool_t>{}(m_IsStrongReference);
        return h1 ^ (h2 << 1);
    }

    template <typename T>
    bool_t Pointer<T>::IsValid() const { return m_ReferenceCounter != nullptr; }

    template <typename T>
    bool_t Pointer<T>::GetIsStrongReference() const { return m_IsStrongReference; }

    template <typename T>
    void Pointer<T>::ToStrongReference()
    {
        if (m_IsStrongReference)
            return;

        m_ReferenceCounter->IncStrong();
        m_ReferenceCounter->DecWeak(this);
        m_IsStrongReference = true;
    }

    template <typename T>
    void Pointer<T>::ToWeakReference()
    {
        if (!m_IsStrongReference)
            return;

        m_ReferenceCounter->DecStrong();
        m_ReferenceCounter->IncWeak(this);
        m_IsStrongReference = false;
    }

    template <typename T>
    void Pointer<T>::Reset()
    {
        m_ReferenceCounter = nullptr;
        m_IsStrongReference = false;
    }

    template <typename T>
    const ReferenceCounter<T>* Pointer<T>::GetReferenceCounter() const { return m_ReferenceCounter; }

    template <typename T>
    Pointer<T>::Pointer(ReferenceCounter<T>*&& referenceCounter, const bool_t strongReference)  // NOLINT(cppcoreguidelines-rvalue-reference-param-not-moved)
        : m_ReferenceCounter(std::move(referenceCounter))
        , m_IsStrongReference(strongReference)
    {
    }

    template <typename T>
    void Pointer<T>::SetReferenceCounter(ReferenceCounter<T>* newReferenceCounter)
    {
        if (m_ReferenceCounter)
        {
            if (m_IsStrongReference)
            {
                if (m_ReferenceCounter->DecStrong())
                    CheckReferenceCounterValid();
            }
            else
            {
                m_ReferenceCounter->DecWeak(this);
            }
        }

        m_ReferenceCounter = newReferenceCounter;
    }

    template <typename T>
    void Pointer<T>::CheckReferenceCounterValid()
    {
        if (!m_ReferenceCounter)
            return;

        if (m_ReferenceCounter->GetStrong() == 0)
        {
            delete m_ReferenceCounter;
            Reset();
        }
    }

    /// @brief Compares two @c Pointer by checking if they point to the same address.
    template <typename T>
    bool_t operator==(const Pointer<T>& a, const Pointer<T>& b) { return a.Get() == b.Get(); }

    /// @brief Compares two @c Pointer by checking if they point to the same address.
    template <typename T>
    bool_t operator!=(const Pointer<T>& a, const Pointer<T>& b) { return !(a == b); }

    /// @brief Compares two @c Pointer by checking if they point to the same address.
    template <typename T, typename U>
    bool_t operator==(const Pointer<T>& a, const Pointer<U>& b) { return a.Get() == reinterpret_cast<const T*>(b.Get()); }

    /// @brief Compares two @c Pointer by checking if they point to the same address.
    template <typename T, typename U>
    bool_t operator!=(const Pointer<T>& a, const Pointer<U>& b) { return !(a == b); }

    /// @brief Checks if a @ref Pointer is null.
    template <typename T>
    bool_t operator==(const Pointer<T>& a, const nullptr_t) { return !a.IsValid(); }

    /// @brief Checks if a @ref Pointer is not null.
    template <typename T>
    bool_t operator!=(const Pointer<T>& a, const nullptr_t) { return a.IsValid(); }
}
