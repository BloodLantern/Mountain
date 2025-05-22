module;

#include <AL/al.h>

module Mountain:Ecs_Component_AudioSource;
import :Ecs_Component_AudioSource;

import <ImGui/imgui.h>;

import :Audio;
import :Input;
import :Ecs_Entity;

using namespace Mountain;

AudioSource::AudioSource()
{
    Audio::GetContext()->MakeCurrent();
    alGenSources(1, &m_Handle);
    AudioContext::CheckError();
    SetLooping(true);
}

AudioSource::~AudioSource()
{
    Audio::GetContext()->MakeCurrent();
    alDeleteSources(1, &m_Handle);
    AudioContext::CheckError();
}

void AudioSource::Added()
{
    // Update pitch and volume in OpenAL
    SetVolume(m_Volume);
    SetPitch(m_Pitch);

    if (m_PlayOnAdded)
        Play();
}

void AudioSource::Update()
{
    // If the track is not in mono, there is no audio spatialization
    if (audioTrack->GetChannels() >= 2)
        return;

    Audio::GetContext()->MakeCurrent();

    const Vector2& position = m_Entity->position * Audio::GetDistanceFactor();

    // Position
    constexpr float_t positionZ = -20.f;
    alSourcefv(m_Handle, AL_POSITION, Vector3(position.x, position.y, positionZ * Audio::GetDistanceFactor()).Data());
    AudioContext::CheckError();

    const float_t deltaTime = Time::GetDeltaTime();
    const Vector2 velocity = deltaTime == 0.f ? Vector2::Zero() : (position - m_LastPosition) / deltaTime;
    std::array direction = { Vector3::UnitZ(), Vector3::UnitY() };

    // Velocity
    alSourcefv(m_Handle, AL_VELOCITY, static_cast<Vector3>(velocity).Data());
    AudioContext::CheckError();

    // Direction
    alSourcefv(m_Handle, AL_DIRECTION, direction[0].Data());
    AudioContext::CheckError();

    m_LastPosition = position;
}

void AudioSource::Play() { if (audioTrack) Play(*audioTrack); }

void AudioSource::Play(AudioTrack& track)
{
    Audio::GetContext()->MakeCurrent();

    if (!track.IsLoaded())
    {
        Logger::LogWarning("Tried to play an AudioTrack ({}) that wasn't loaded in the audio interface. Loading it", track.GetName());
        track.Load();
    }

    alSourceRewind(m_Handle);
    SetBuffer(track.GetBuffer());
    alSourcePlay(m_Handle);
    AudioContext::CheckError();
}

// ReSharper disable once CppMemberFunctionMayBeConst
void AudioSource::SetBuffer(const AudioBuffer* buffer)
{
    Audio::GetContext()->MakeCurrent();
    alSourcei(m_Handle, AL_BUFFER, static_cast<int32_t>(buffer->GetHandle()));
    AudioContext::CheckError();
}

float_t AudioSource::GetVolume() const
{
    return m_Volume;
}

void AudioSource::SetVolume(const float_t newVolume)
{
    m_Volume = std::max(0.f, newVolume);

    Audio::GetContext()->MakeCurrent();
    alSourcef(m_Handle, AL_GAIN, m_Volume);
    AudioContext::CheckError();
}

float_t AudioSource::GetPitch() const
{
    return m_Pitch;
}

void AudioSource::SetPitch(const float_t newPitch)
{
    m_Pitch = std::max(0.f, newPitch);

    Audio::GetContext()->MakeCurrent();
    alSourcef(m_Handle, AL_PITCH, m_Pitch);
    AudioContext::CheckError();
}

bool_t AudioSource::GetLooping() const
{
    return m_Looping;
}

void AudioSource::SetLooping(const bool_t newLooping)
{
    m_Looping = newLooping;

    Audio::GetContext()->MakeCurrent();
    alSourcei(m_Handle, AL_LOOPING, m_Looping);
    AudioContext::CheckError();
}
