#pragma once

#include <mutex>

#include "Mountain/Core.hpp"
#include "Mountain/Exceptions/ThrowHelper.hpp"
#include "Mountain/Utils/MetaProgramming.hpp"

#define MOUNTAIN_DEBUG_ALLOCATOR

namespace Mountain
{
    /// @brief A custom allocator.
    class Allocator
    {
        STATIC_CLASS(Allocator)

    public:
        template <Concepts::AllocatorType T>
        [[nodiscard]]
        static T* Allocate(uint64_t size);

        MOUNTAIN_API static void Deallocate(const void* pointer);

        template <Concepts::AllocatorType T, typename... Args>
        [[nodiscard]]
        static T* Construct(Args... args);

        template <Concepts::AllocatorType T>
        static void Destroy(const T* pointer);

        /// @brief Get the number of bytes allocated, not counting the internal allocator allocations
        STATIC_GETTER(uint64_t, AllocatedSize, m_AllocatedSize)

        /// @brief Get the total number of bytes allocated, counting the internal allocator allocations
        [[nodiscard]]
        MOUNTAIN_API static uint64_t GetTotalAllocatedSize() noexcept;

    private:
        struct Block
        {
            Block* previous = nullptr;
            Block* next = nullptr;

            void* pointer = nullptr;

            uint64_t size = 0;
            uint64_t typeSize = 0;
        };

        /// @brief The number of bytes allocated, not counting the memory allocated for internal @c Block objects.
        MOUNTAIN_API static inline uint64_t m_AllocatedSize = 0;

        /// @brief The number @c Block allocated objects.
        MOUNTAIN_API static inline uint64_t m_BlockCount = 0;

        MOUNTAIN_API static inline Block* m_FirstBlock = nullptr; // FIXME - Not initialized to nullptr for some reason ????

        MOUNTAIN_API static inline Block* m_LastBlock = nullptr;

        MOUNTAIN_API static inline std::mutex m_Mutex;

        /// @brief Allocates @p size bytes of memory on the heap using @c std::malloc().
        template <Concepts::AllocatorType T>
        [[nodiscard]]
        static T* Malloc(uint64_t size);

        /// @brief Allocates @c sizeof(T) bytes of memory on the heap using @c std::malloc().
        template <Concepts::AllocatorType T>
        [[nodiscard]]
        static T* Malloc();

        /// @brief Deallocates the previously allocated memory at @p pointer using @c std::free().
        MOUNTAIN_API static void Free(const void* pointer) noexcept;

        template <Concepts::AllocatorType T>
        [[nodiscard]]
        static Block* EmplaceNewBlock(uint64_t size);

        MOUNTAIN_API static void RemoveBlock(const Block* block) noexcept;

        [[nodiscard]]
        MOUNTAIN_API static Block* FindBlock(const void* pointer);
    };
}

// Start of Allocator.inl

#include "Mountain/Globals.hpp"

namespace Mountain
{
    /// @brief Same as doing @c sizeof(T) except that it returns a size of @c 1 for @c void.
    template <typename T>
    constexpr uint64_t Sizeof = sizeof(T);

    template <>
    constexpr uint64_t Sizeof<void> = 1;

    template <Concepts::AllocatorType T>
    T* Allocator::Allocate(const uint64_t size)
    {
        static_assert(Sizeof<T> != 0, "Cannot call Allocator::Allocate on an incomplete type");

        if (size == 0)
            return nullptr;

        const uint64_t byteSize = size * Sizeof<T>;

        T* pointer = Malloc<T>(byteSize);

        if (DebugMemoryAllocations)
        {
            std::scoped_lock lock{m_Mutex};

            Block* newBlock = EmplaceNewBlock<T>(byteSize);
            newBlock->pointer = pointer;
            m_AllocatedSize += byteSize;
        }

        return pointer;
    }

    template <Concepts::AllocatorType T, typename... Args>
    T* Allocator::Construct(Args... args)
    {
        static_assert(Sizeof<T> != 0, "Cannot call Allocator::Construct on an incomplete type");

        T* pointer = Malloc<T>();

        if (DebugMemoryAllocations)
        {
            std::scoped_lock lock{m_Mutex};

            Block* newBlock = EmplaceNewBlock<T>(Sizeof<T>);
            newBlock->pointer = pointer;
            m_AllocatedSize += Sizeof<T>;
        }

        return new (pointer) T{std::forward<Args>(args)...};
    }

    template <Concepts::AllocatorType T>
    void Allocator::Destroy(const T* pointer)
    {
        static_assert(Sizeof<T> != 0, "Cannot call Allocator::Destroy on an incomplete type");

        if (!pointer)
            return;

        pointer->~T();
        Free(pointer);

        if (DebugMemoryAllocations)
        {
            std::scoped_lock lock{m_Mutex};

            const Block* block = FindBlock(pointer);
            m_AllocatedSize -= block->size;
            RemoveBlock(block);
        }
    }

    template <Concepts::AllocatorType T>
    T* Allocator::Malloc(const uint64_t size)
    {
        void* pointer = std::malloc(size);

        if (!pointer)
            THROW(OutOfMemoryException{"std::malloc returned nullptr"});

        return static_cast<T*>(pointer);
    }

    template <Concepts::AllocatorType T>
    T* Allocator::Malloc()
    {
        return Malloc<T>(Sizeof<T>);
    }

    template <Concepts::AllocatorType T>
    Allocator::Block* Allocator::EmplaceNewBlock(const uint64_t size)
    {
        if (size < Sizeof<T> || size % Sizeof<T> != 0)
            THROW(ArgumentException{"Cannot emplace a block with an invalid size", "size"});

        Block* newBlock = Malloc<Block>();
        // Keep in mind that the default constructor hasn't been called, so we need to initialize all fields
        newBlock->previous = nullptr;
        newBlock->next = nullptr;
        newBlock->pointer = nullptr;

        newBlock->typeSize = Sizeof<T>;
        newBlock->size = size;

        if (!m_FirstBlock)
        {
            m_FirstBlock = newBlock;
            m_LastBlock = newBlock;
        }
        else
        {
            m_LastBlock->next = newBlock;
            newBlock->previous = m_LastBlock;
            m_LastBlock = newBlock;
        }

        m_BlockCount++;

        return newBlock;
    }
}

// ReSharper disable CppNonInlineFunctionDefinitionInHeaderFile
// ReSharper disable CppParameterNamesMismatch

/*void* operator new(const std::size_t count)
{
    return Mountain::Allocator::Allocate<void>(count);
}

void operator delete(const void* ptr) noexcept
{
    Mountain::Allocator::Deallocate(ptr);
}

void* operator new[](const std::size_t count)
{
    return Mountain::Allocator::Allocate<void>(count);
}

void operator delete[](const void* ptr) noexcept
{
    Mountain::Allocator::Deallocate(ptr);
}*/

// ReSharper enable CppNonInlineFunctionDefinitionInHeaderFile
// ReSharper enable CppParameterNamesMismatch
