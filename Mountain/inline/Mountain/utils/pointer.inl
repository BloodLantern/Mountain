#pragma once

BEGIN_MOUNTAIN

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
    , m_IsStrongReference(std::move(other.m_IsStrongReference))
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
    m_IsStrongReference = std::move(other.m_IsStrongReference);

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
    if (this == &other)
        return *this;
    
    SetReferenceCounter(reinterpret_cast<ReferenceCounter<T>*>(other.GetReferenceCounter()));
    m_ReferenceCounter->IncWeak(this);
    
    return *this;
}

template <typename T>
template <typename U>
Pointer<T>& Pointer<T>::operator=(Pointer<U>&& other) noexcept
{
    if (reinterpret_cast<int8_t*>(this) == reinterpret_cast<int8_t*>(&other))
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
    if (!m_ReferenceCounter)
        throw std::runtime_error("Cannot dereference a null Pointer");
    return *m_ReferenceCounter->GetPointer();
}

template <typename T>
const T& Pointer<T>::operator*() const
{
    if (!m_ReferenceCounter)
        throw std::runtime_error("Cannot dereference a null Pointer");
    return *m_ReferenceCounter->GetPointer();
}

template <typename T>
T* Pointer<T>::operator->()
{
    if (!m_ReferenceCounter)
        throw std::runtime_error("Cannot dereference a null Pointer");
    return m_ReferenceCounter->GetPointer();
}

template <typename T>
const T* Pointer<T>::operator->() const
{
    if (!m_ReferenceCounter)
        throw std::runtime_error("Cannot dereference a null Pointer");
    return m_ReferenceCounter->GetPointer();
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

/// @brief Compares two @ref Pointer "Pointers" by checking if they point to the same address.
template <typename T>
bool_t operator==(const Pointer<T>& a, const Pointer<T>& b) { return static_cast<const T*>(a) == static_cast<const T*>(b); }

/// @brief Compares two @ref Pointer "Pointers" by checking if they point to the same address.
template <typename T>
bool_t operator!=(const Pointer<T>& a, const Pointer<T>& b) { return !(a == b); }

/// @brief Compares two @ref Pointer "Pointers" by checking if they point to the same address.
template <typename T, typename U>
bool_t operator==(const Pointer<T>& a, const Pointer<U>& b) { return static_cast<const T*>(a) == reinterpret_cast<const T*>(static_cast<const U*>(b)); }

/// @brief Compares two @ref Pointer "Pointers" by checking if they point to the same address.
template <typename T, typename U>
bool_t operator!=(const Pointer<T>& a, const Pointer<U>& b) { return !(a == b); }

/// @brief Checks if a @ref Pointer is null.
template <typename T>
bool_t operator==(const Pointer<T>& a, const nullptr_t) { return !a.IsValid(); }

/// @brief Checks if a @ref Pointer is not null.
template <typename T>
bool_t operator!=(const Pointer<T>& a, const nullptr_t) { return a.IsValid(); }

/// @brief Prints the given Pointer to an output stream according to the @ref Mountain::Pointer<T>::operator stdstring() const "Pointer to string conversion".
template <typename T>
std::ostream& operator<<(std::ostream& stream, const Pointer<T>& ptr) { return stream << static_cast<std::string>(ptr); }

END_MOUNTAIN
