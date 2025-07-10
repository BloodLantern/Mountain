#include "Mountain/Ecs/Component/AudioListener.hpp"

#include <array>

#include <ImGui/imgui.h>

#include "Mountain/Audio/Audio.hpp"
#include "Mountain/Audio/AudioContext.hpp"
#include "Mountain/Audio/Sound.hpp"
#include "Mountain/Ecs/Entity.hpp"
#include "Mountain/Input/Time.hpp"

using namespace Mountain;

void AudioListener::Update()
{
    Sound::GetContext()->MakeCurrent();

    const Vector2& position = m_Entity->position * Sound::GetDistanceFactor();

    // Position
    constexpr float_t positionZ = 20.f;
    Audio::SetListenerVector(Audio::ListenerVector::Position, Vector3(position.x, position.y, positionZ * Sound::GetDistanceFactor()));
    AudioContext::CheckError();

    // Velocity
    const Vector2 velocity = dopplerEffect ? (position - m_LastPosition) / Time::GetDeltaTime() : Vector2::Zero();
    Audio::SetListenerVector(Audio::ListenerVector::Velocity, static_cast<Vector3>(velocity));
    AudioContext::CheckError();

    // Orientation
    Audio::SetListenerArray(Audio::ListenerArray::Orientation, { -Vector3::UnitZ(), Vector3::UnitY() });
    AudioContext::CheckError();

    m_LastPosition = position;
}

float_t AudioListener::GetVolume() const
{
    return m_Volume;
}

void AudioListener::SetVolume(const float_t newVolume)
{
    m_Volume = std::max(0.f, newVolume);

    Sound::GetContext()->MakeCurrent();
    Audio::SetListenerFloat(Audio::ListenerFloat::Gain, m_Volume);
    AudioContext::CheckError();
}
