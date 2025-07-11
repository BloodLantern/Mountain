#include "Mountain/PrecompiledHeader.hpp"

#include "Mountain/Ecs/Component/AudioListener.hpp"

#include <array>

#include <ImGui/imgui.h>

#include "Mountain/Audio/Audio.hpp"
#include "Mountain/Audio/Sound.hpp"
#include "Mountain/Ecs/Entity.hpp"
#include "Mountain/Input/Time.hpp"

using namespace Mountain;

void AudioListener::Update()
{
    Sound::GetContext()->MakeCurrent();

    const Vector2& position = m_Entity->position * Sound::distanceFactor;

    // Position
    constexpr float_t positionZ = 20.f;
    SetListenerVector(Audio::ListenerVector::Position, Vector3(position.x, position.y, positionZ * Sound::distanceFactor));
    Audio::Context::CheckError();

    // Velocity
    const Vector2 velocity = dopplerEffect ? (position - m_LastPosition) / Time::GetDeltaTime() : Vector2::Zero();
    SetListenerVector(Audio::ListenerVector::Velocity, static_cast<Vector3>(velocity));
    Audio::Context::CheckError();

    // Orientation
    SetListenerArray(Audio::ListenerArray::Orientation, { -Vector3::UnitZ(), Vector3::UnitY() });
    Audio::Context::CheckError();

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
    SetListenerFloat(Audio::ListenerFloat::Gain, m_Volume);
    Audio::Context::CheckError();
}
