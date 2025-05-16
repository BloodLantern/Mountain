#pragma once

#include <mutex>
#include <vector>

#include "Mountain/core.hpp"

namespace Mountain
{
    template <typename T>
    class Pointer;

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

        [[nodiscard]]
        uint64_t GetStrong() const;

        [[nodiscard]]
        uint64_t GetWeak() const;

        [[nodiscard]]
        T* GetPointer();

        [[nodiscard]]
        const T* GetPointer() const;

    private:
        uint64_t m_Strong = 1;

        T* m_Pointer = nullptr;

        std::vector<Pointer<T>*> m_WeakReferenceOwners;

        std::mutex m_Mutex;
    };
}

#include "Mountain/utils/reference_counter.inl"
