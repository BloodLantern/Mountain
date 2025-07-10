#pragma once

#include <mutex>
#include <vector>

#include "Mountain/Core.hpp"
#include "Mountain/Exceptions/ThrowHelper.hpp"

namespace Mountain
{
    template <typename>
    struct Pointer;

    /// @private
    template <typename T>
    class ReferenceCounter
    {
    public:
        using Type = T;

        template <typename... Args>
        explicit ReferenceCounter(Args&&... args);

        ReferenceCounter(const ReferenceCounter& other) = delete;

        ReferenceCounter(ReferenceCounter&& other) = delete;

        ReferenceCounter& operator=(const ReferenceCounter& other) = delete;

        ReferenceCounter& operator=(ReferenceCounter&& other) = delete;

        ~ReferenceCounter();

        void IncStrong();

        void IncWeak(Pointer<T>* weakReferenceOwner);

        // Returns whether the strong ref count becomes 0
        bool DecStrong();

        void DecWeak(const Pointer<T>* weakReferenceOwner);

        ATTRIBUTE_NODISCARD
        uint64_t GetStrong() const;

        ATTRIBUTE_NODISCARD
        uint64_t GetWeak() const;

        ATTRIBUTE_NODISCARD
        T* GetPointer();

        ATTRIBUTE_NODISCARD
        const T* GetPointer() const;

    private:
        uint64_t m_Strong = 1;

        T* m_Pointer = nullptr;

        std::vector<Pointer<T>*> m_WeakReferenceOwners;

        std::mutex m_Mutex;
    };
}

// Start of ReferenceCounter.inl

namespace Mountain
{
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
        if (m_Strong == 0)
            return true;

        if (--m_Strong == 0)
            return true;

        return false;
    }

    template <typename T>
    void ReferenceCounter<T>::DecWeak(const Pointer<T>* const weakReferenceOwner)
    {
        const auto&& it = std::ranges::find(m_WeakReferenceOwners, weakReferenceOwner);

        if (it == m_WeakReferenceOwners.end())
            THROW(InvalidOperationException{"Tried to decrement the weak reference count of a smart pointer with one that wasn't registered"});

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
}
