#include "Mountain/Core.hpp"

#include "Mountain/Ecs/Component/AudioListener.hpp"

#include <array>

#include <AL/al.h>

#include <ImGui/imgui.h>

#include "Mountain/Audio/Audio.hpp"
#include "Mountain/Audio/AudioContext.hpp"
#include "Mountain/Ecs/Entity.hpp"
#include "Mountain/Input/Time.hpp"

using namespace Mountain;

void AudioListener::Update()
{
    Audio::GetContext()->MakeCurrent();

    const Vector2& position = m_Entity->position * Audio::GetDistanceFactor();

    // Position
    constexpr float_t positionZ = 20.f;
    alListenerfv(AL_POSITION, Vector3(position.x, position.y, positionZ * Audio::GetDistanceFactor()).Data());
    AudioContext::CheckError();
    AudioContext::CheckError();

    const Vector2 velocity = dopplerEffect ? (position - m_LastPosition) / Time::GetDeltaTime() : Vector2::Zero();
    constexpr std::array orientation = { -Vector3::UnitZ(), Vector3::UnitY() };

    // Velocity
    alListenerfv(AL_VELOCITY, static_cast<Vector3>(velocity).Data());
    AudioContext::CheckError();

    // Orientation
    alListenerfv(AL_ORIENTATION, orientation[0].Data());
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

    Audio::GetContext()->MakeCurrent();
    alListenerf(AL_GAIN, m_Volume);
    AudioContext::CheckError();
}
