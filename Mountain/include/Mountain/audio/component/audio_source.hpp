#pragma once

#include "Mountain/core.hpp"

#include <Maths/vector2.hpp>

#include "Mountain/resource/audio_track.hpp"
#include "Mountain/scene/component/component.hpp"

BEGIN_MOUNTAIN

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

    MOUNTAIN_API float_t GetVolume() const;

    MOUNTAIN_API void SetVolume(float_t newVolume);

    MOUNTAIN_API float_t GetPitch() const;

    MOUNTAIN_API void SetPitch(float_t newPitch);

    MOUNTAIN_API bool_t GetLooping() const;

    MOUNTAIN_API void SetLooping(bool_t newLooping);

private:
    uint32_t m_Handle = 0;
    
    /// @brief Volume in the range [0, inf]. Default value is 1.
    float_t m_Volume = 1.f;
    
    /// @brief Pitch in the range [0, inf]. Default value is 1.
    float_t m_Pitch = 1.f;

    bool_t m_Looping = false;

    bool_t m_PlayOnAdded = true;

    Vector2 m_LastPosition;
};

END_MOUNTAIN
