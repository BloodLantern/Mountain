#pragma once

#include "Mountain/Core.hpp"

#include <Math/vector2.hpp>

#include "Mountain/Ecs/Component/Component.hpp"
#include "Mountain/Resource/AudioTrack.hpp"

namespace Mountain
{
    class AudioSource : public Component
    {
    public:
        Pointer<AudioTrack> audioTrack;

        MOUNTAIN_API AudioSource();

        MOUNTAIN_API ~AudioSource() override;

        DELETE_COPY_MOVE_OPERATIONS(AudioSource)

        MOUNTAIN_API void Added() override;

        MOUNTAIN_API void Update() override;

        MOUNTAIN_API void Play();

        MOUNTAIN_API void Play(AudioTrack& track);

        MOUNTAIN_API void SetBuffer(const AudioBuffer* buffer);

        MOUNTAIN_API f32 GetVolume() const;

        MOUNTAIN_API void SetVolume(f32 newVolume);

        MOUNTAIN_API f32 GetPitch() const;

        MOUNTAIN_API void SetPitch(f32 newPitch);

        MOUNTAIN_API bool GetLooping() const;

        MOUNTAIN_API void SetLooping(bool newLooping);

    private:
        u32 m_Handle = 0;

        /// @brief Volume in the range [0, inf]. Default value is 1.
        f32 m_Volume = 1.f;

        /// @brief Pitch in the range [0, inf]. Default value is 1.
        f32 m_Pitch = 1.f;

        bool m_Looping = false;

        bool m_PlayOnAdded = true;

        Vector2 m_LastPosition;
    };
}
