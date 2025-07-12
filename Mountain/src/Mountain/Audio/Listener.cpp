#include "Mountain/PrecompiledHeader.hpp"
#include "Mountain/Audio/Listener.hpp"

#include "Audio.hpp"
#include "Sound.hpp"
#include "Mountain/Input/Time.hpp"

using namespace Mountain::Audio;

Listener::Listener()
{
    SetListenerArray(ListenerArray::Orientation, { -Vector3::UnitZ(), Vector3::UnitY() });
    SetPosition(Vector2::Zero());
    SetVelocity(Vector2::Zero());
    SetVolume(1.f);
}

void Listener::SetPosition(Vector2 position, const bool_t updateVelocity)
{
    position *= Sound::distanceFactor;

    if (updateVelocity)
        SetVelocity((position - m_Position) / Time::GetDeltaTime());
    
    m_Position = position;
    constexpr float_t positionZ = 20.f;
    SetListenerVector(ListenerVector::Position, Vector3(position.x, position.y, positionZ * Sound::distanceFactor));
}

void Listener::SetVelocity(const Vector2 velocity)
{
    m_Velocity = velocity;
    SetListenerVector(ListenerVector::Velocity, static_cast<Vector3>(velocity));
}

void Listener::SetVolume(const float_t volume)
{
    m_Volume = std::max(0.f, volume);
    SetListenerFloat(ListenerFloat::Gain, m_Volume);
}

float_t Listener::GetVolume() const { return m_Volume; }
