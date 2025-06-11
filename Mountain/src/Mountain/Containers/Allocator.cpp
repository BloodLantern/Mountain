#include "Mountain/Containers/Allocator.hpp"

using namespace Mountain;

void Allocator::Deallocate(const void* pointer)
{
    if (!pointer)
        return;

    Free(pointer);

    if (DebugMemoryAllocations)
    {
        std::scoped_lock lock{m_Mutex};

        const Block* block = FindBlock(pointer);
        m_AllocatedSize -= block->size;
        RemoveBlock(block);
    }
}

uint64_t Allocator::GetTotalAllocatedSize() noexcept { return m_AllocatedSize + m_BlockCount * Sizeof<Block>; }

void Allocator::Free(const void* pointer) noexcept
{
    // We can const_cast here because the memory must have been allocated as non-const anyway
    std::free(const_cast<void*>(pointer));
}

void Allocator::RemoveBlock(const Block* block) noexcept
{
    if (block->previous)
        block->previous->next = block->next;
    if (block->next)
        block->next->previous = block->previous;

    if (block == m_FirstBlock)
        m_FirstBlock = block->next;
    if (block == m_LastBlock)
        m_LastBlock = block->previous;

    m_BlockCount--;

    Free(block);
}

Allocator::Block* Allocator::FindBlock(const void* pointer)
{
    Block* block = m_FirstBlock;
    while (block->next != nullptr && block->next != pointer) block = block->next;

    if (block->next == nullptr && block->pointer != pointer)
        THROW(ThrowHelper::AllocatorBlockNotFoundException());

    return block;
}
