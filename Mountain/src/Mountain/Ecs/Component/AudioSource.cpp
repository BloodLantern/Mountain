#include "Mountain/Ecs/Component/AudioSource.hpp"

#include <ImGui/imgui.h>

#include "Mountain/Audio/Audio.hpp"
#include "Mountain/Audio/Context.hpp"
#include "Mountain/Audio/Sound.hpp"
#include "Mountain/Ecs/Entity.hpp"
#include "Mountain/Ecs/Component/AudioListener.hpp"
#include "Mountain/Input/Input.hpp"
#include "Mountain/Input/Time.hpp"
#include "Mountain/Utils/Logger.hpp"

using namespace Mountain;

AudioSource::AudioSource()
{
    Sound::GetContext()->MakeCurrent();
    m_Handle = Audio::CreateSource();
    Audio::Context::CheckError();
    SetLooping(true);
}

AudioSource::~AudioSource()
{
    Sound::GetContext()->MakeCurrent();
    Audio::DeleteSource(m_Handle);
    Audio::Context::CheckError();
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
    
    Sound::GetContext()->MakeCurrent();

    const Vector2& position = m_Entity->position * Sound::distanceFactor;

    // Position
    constexpr float_t positionZ = -20.f;
    Audio::SetSourceVector(m_Handle, Audio::SourceVector::Position, Vector3(position.x, position.y, positionZ * Sound::distanceFactor));
    Audio::Context::CheckError();

    const float_t deltaTime = Time::GetDeltaTime();
    const Vector2 velocity = deltaTime == 0.f ? Vector2::Zero() : (position - m_LastPosition) / deltaTime;

    // Velocity
    Audio::SetSourceVector(m_Handle, Audio::SourceVector::Velocity, static_cast<Vector3>(velocity));
    Audio::Context::CheckError();

    // Direction
    SetSourceVector(m_Handle, Audio::SourceVector::Direction, Vector3::UnitZ());
    Audio::Context::CheckError();

    m_LastPosition = position;
}

void AudioSource::Play() { if (audioTrack) Play(*audioTrack); }

void AudioSource::Play(AudioTrack& track)
{
    Sound::GetContext()->MakeCurrent();
    
    if (!track.IsLoaded())
    {
        Logger::LogWarning("Tried to play an AudioTrack ({}) that wasn't loaded in the audio interface. Loading it", track.GetName());
        track.Load();
    }

    Audio::RewindSource(m_Handle);
    SetBuffer(track.GetBuffer());
    Audio::PlaySource(m_Handle);
    Audio::Context::CheckError();
}

// ReSharper disable once CppMemberFunctionMayBeConst
void AudioSource::SetBuffer(const Audio::Buffer* buffer)
{
    Sound::GetContext()->MakeCurrent();
    SetSourceInt(m_Handle, Audio::SourceInt::Buffer, static_cast<int32_t>(buffer->GetHandle()));
    Audio::Context::CheckError();
}

float_t AudioSource::GetVolume() const
{
    return m_Volume;
}

void AudioSource::SetVolume(const float_t newVolume)
{
    m_Volume = std::max(0.f, newVolume);

    Sound::GetContext()->MakeCurrent();
    SetSourceFloat(m_Handle, Audio::SourceFloat::Gain, m_Volume);
    Audio::Context::CheckError();
}

float_t AudioSource::GetPitch() const
{
    return m_Pitch;
}

void AudioSource::SetPitch(const float_t newPitch)
{
    m_Pitch = std::max(0.f, newPitch);

    Sound::GetContext()->MakeCurrent();
    SetSourceFloat(m_Handle, Audio::SourceFloat::Pitch, m_Pitch);
    Audio::Context::CheckError();
}

bool_t AudioSource::GetLooping() const
{
    return m_Looping;
}

void AudioSource::SetLooping(const bool_t newLooping)
{
    m_Looping = newLooping;
    
    Sound::GetContext()->MakeCurrent();
    SetSourceBool(m_Handle, Audio::SourceBool::Looping, m_Looping);
    Audio::Context::CheckError();
}
