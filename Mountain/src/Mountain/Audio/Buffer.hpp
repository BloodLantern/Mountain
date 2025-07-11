#pragma once

#include "Mountain/Core.hpp"
#include "Mountain/Audio/Context.hpp"

namespace Mountain
{
    class AudioTrack;
}

namespace Mountain::Audio
{
    class MOUNTAIN_API Buffer
    {
    public:
        Buffer();

        explicit Buffer(const AudioTrack* track);

        ~Buffer();

        DEFAULT_COPY_MOVE_OPERATIONS(Buffer)

        void SetData(const AudioTrack* track);

        void SetData(const void* data, int32_t length, uint16_t channels, uint16_t bitDepth, int32_t sampleRate);

        ATTRIBUTE_NODISCARD
        uint32_t GetHandle() const;

    private:
        uint32_t m_Handle = 0;

        Context* m_Context = nullptr;
    };
}
