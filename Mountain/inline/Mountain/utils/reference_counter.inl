#pragma once

#include <stdexcept>

BEGIN_MOUNTAIN

template <typename T>
template <typename... Args>
ReferenceCounter<T>::ReferenceCounter(Args&&... args) // NOLINT(cppcoreguidelines-missing-std-forward)
    : m_Pointer(new T(std::forward<Args>(args)...))
{
}

template <typename T>
ReferenceCounter<T>::~ReferenceCounter()
{
    for (auto& weakReferenceOwner : m_WeakReferenceOwners)
        weakReferenceOwner->Reset();
    
    delete m_Pointer;
}

template <typename T>
void ReferenceCounter<T>::IncStrong()
{
    m_Strong++;
}

template <typename T>
void ReferenceCounter<T>::IncWeak(Pointer<T>* weakReferenceOwner)
{
    std::scoped_lock lock(m_Mutex);
    m_WeakReferenceOwners.push_back(weakReferenceOwner);
}

template <typename T>   
bool ReferenceCounter<T>::DecStrong()
{
    if (m_Strong == 0 || --m_Strong == 0)
        return true;

    return false;
}

template <typename T>
void ReferenceCounter<T>::DecWeak(const Pointer<T>* const weakReferenceOwner)
{
    const auto&& it = std::find(m_WeakReferenceOwners.begin(), m_WeakReferenceOwners.end(), weakReferenceOwner);
    
    if (it == m_WeakReferenceOwners.end())
        throw std::runtime_error("Tried to decrement the weak reference count of a smart pointer with one that wasn't registered");
    
    m_WeakReferenceOwners.erase(it);
}

template <typename T>
uint64_t ReferenceCounter<T>::GetStrong() const
{
    return m_Strong;
}

template <typename T>
uint64_t ReferenceCounter<T>::GetWeak() const
{
    return m_WeakReferenceOwners.size();
}

template <typename T>
T* ReferenceCounter<T>::GetPointer()
{
    return m_Pointer;
}

template <typename T>
const T* ReferenceCounter<T>::GetPointer() const
{
    return m_Pointer;
}

END_MOUNTAIN
