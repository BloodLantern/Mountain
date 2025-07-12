#pragma once

#include "Mountain/Core.hpp"

#include <Math/vector2.hpp>

#include "Mountain/Audio/Source.hpp"
#include "Mountain/Ecs/Component/Component.hpp"
#include "Mountain/Resource/AudioTrack.hpp"

namespace Mountain
{
    class AudioSource : public Component
    {
    public:
        Pointer<AudioTrack> audioTrack;

        MOUNTAIN_API AudioSource();

        DELETE_COPY_MOVE_OPERATIONS(AudioSource)

        MOUNTAIN_API void Added() override;

        MOUNTAIN_API void Update() override;

        MOUNTAIN_API void Play();

        MOUNTAIN_API void Play(AudioTrack& track) const;

        MOUNTAIN_API void SetBuffer(const Audio::Buffer* buffer);

        MOUNTAIN_API float_t GetVolume() const;
        MOUNTAIN_API float_t GetPitch() const;

        MOUNTAIN_API void SetVolume(float_t newVolume);
        MOUNTAIN_API void SetPitch(float_t newPitch);
        MOUNTAIN_API void SetLooping(bool_t newLooping) const;

    private:
        Audio::Source m_Source;
        bool_t m_PlayOnAdded = true;
    };
}
