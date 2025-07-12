#include "Mountain/PrecompiledHeader.hpp"
#include "Mountain/Ecs/Component/AudioSource.hpp"

#include "Mountain/Audio/Context.hpp"
#include "Mountain/Audio/Sound.hpp"
#include "Mountain/Ecs/Entity.hpp"
#include "Mountain/Ecs/Component/AudioListener.hpp"
#include "Mountain/Input/Input.hpp"
#include "Mountain/Utils/Logger.hpp"

using namespace Mountain;

AudioSource::AudioSource()
{
    SetLooping(true);
}

void AudioSource::Added()
{
    if (m_PlayOnAdded)
        Play();
}

void AudioSource::Update()
{
    // If the track is not in mono, there is no audio spatialization
    if (audioTrack->GetChannels() >= 2)
        return;

    m_Source.SetPosition(m_Entity->position, true);
}

void AudioSource::Play() { if (audioTrack) Play(*audioTrack); }

void AudioSource::Play(AudioTrack& track) const
{
    Sound::GetContext()->MakeCurrent();
    
    if (!track.IsLoaded())
    {
        Logger::LogWarning("Tried to play an AudioTrack ({}) that wasn't loaded in the audio interface. Loading it", track.GetName());
        track.Load();
    }

    m_Source.Start();
}

float_t AudioSource::GetVolume() const { return m_Source.GetInfo().volume; }

void AudioSource::SetVolume(const float_t newVolume)
{
    m_Source.SetVolume(newVolume);
}

float_t AudioSource::GetPitch() const { return m_Source.GetInfo().pitch; }

void AudioSource::SetPitch(const float_t newPitch)
{
    m_Source.SetPitch(newPitch);
}

void AudioSource::SetLooping(const bool_t newLooping) const
{
    m_Source.SetLooping(newLooping);
}
