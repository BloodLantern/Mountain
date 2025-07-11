﻿#pragma once

#include "Mountain/Core.hpp"

namespace Mountain
{
    class AudioTrack;
    class AudioContext;

    class MOUNTAIN_API AudioBuffer
    {
    public:
        AudioBuffer();

        explicit AudioBuffer(int32_t size);

        explicit AudioBuffer(const AudioTrack* track);

        ~AudioBuffer();

        DEFAULT_COPY_MOVE_OPERATIONS(AudioBuffer)

        void SetData(const AudioTrack* track);

        void SetData(const void* data, int32_t length, uint16_t channels, uint16_t bitDepth, int32_t sampleRate);

        ATTRIBUTE_NODISCARD
        uint32_t GetHandle() const;

    private:
        uint32_t m_Handle = 0;

        int32_t m_Format = 0;

        AudioContext* m_Context = nullptr;

        ATTRIBUTE_NODISCARD
        static int32_t AlFormatFromData(uint16_t channels, uint16_t bitDepth);
    };
}
