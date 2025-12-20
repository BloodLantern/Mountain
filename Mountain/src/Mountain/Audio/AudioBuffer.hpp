#pragma once

#include "Mountain/Core.hpp"

namespace Mountain
{
    class AudioTrack;
    class AudioContext;

    class MOUNTAIN_API AudioBuffer
    {
    public:
        AudioBuffer();

        explicit AudioBuffer(s32 size);

        explicit AudioBuffer(const AudioTrack* track);

        ~AudioBuffer();

        DEFAULT_COPY_MOVE_OPERATIONS(AudioBuffer)

        void SetData(const AudioTrack* track);

        void SetData(const void* data, s32 length, u16 channels, u16 bitDepth, s32 sampleRate);

        ATTRIBUTE_NODISCARD
        u32 GetHandle() const;

    private:
        u32 m_Handle = 0;

        s32 m_Format = 0;

        AudioContext* m_Context = nullptr;

        ATTRIBUTE_NODISCARD
        static s32 AlFormatFromData(u16 channels, u16 bitDepth);
    };
}
