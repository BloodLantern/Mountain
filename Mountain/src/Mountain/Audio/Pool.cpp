#include "Mountain/PrecompiledHeader.hpp"
#include "Mountain/Audio/Pool.hpp"

#include "Mountain/Ecs/Component/AudioSource.hpp"

using namespace Mountain::Audio;

Pool::Pool()
{
    for (size_t i = 0; i < MaxSourceAmount; i++)
        m_Sources[i] = new Source();

    for (size_t i = 0; i < MaxBufferAmount; i++)
        m_Buffers[i] = new Buffer();
}

Pool::~Pool()
{
    for (size_t i = 0; i < MaxSourceAmount; i++)
        delete m_Sources[i];

    for (size_t i = 0; i < MaxBufferAmount; i++)
        delete m_Buffers[i];
}

Source* Pool::FindFreeSource()
{
    Source* result = *FindFirst(
        m_Sources,
        [](const Source* source) -> bool_t 
        {
            const SourceState state = source->GetState();
            return state == SourceState::Initial || state == SourceState::Stopped;
        }
    );

    if (result)
        return result;

    // Possibly add other ways to find a free source if necessary, like finding very far away sounds

    return nullptr;
}

Buffer* Pool::FindFreeBuffer()
{
    return *FindFirst( m_Buffers, [](const Buffer* buffer) -> bool_t { return !buffer->busy; });
}
