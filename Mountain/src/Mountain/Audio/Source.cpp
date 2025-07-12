#include "Mountain/PrecompiledHeader.hpp"
#include "Mountain/Audio/Source.hpp"

#include "Sound.hpp"
#include "Mountain/Audio/Audio.hpp"
#include "Mountain/Input/Time.hpp"

using namespace Mountain::Audio;

Source::Source()
{
    m_Handle = CreateSource();
    ApplyInfo();
}

Source::Source(const SourceInfo& info)
    : m_Info(info)
{
    m_Handle = CreateSource();
    ApplyInfo();
}

Source::~Source()
{
    DeleteSource(m_Handle);
}

void Source::Start() const
{
    PlaySource(m_Handle);
}

void Source::Pause() const
{
    PauseSource(m_Handle);
}

void Source::Stop() const
{
    StopSource(m_Handle);
}

void Source::SetVolume(const float_t volume)
{
    m_Info.volume = volume;
    SetSourceFloat(m_Handle, SourceFloat::Gain, volume);
}

void Source::SetPitch(const float_t pitch)
{
    m_Info.pitch = pitch;
    SetSourceFloat(m_Handle, SourceFloat::Pitch, pitch);
}

void Source::SetPosition(Vector2 position, const bool_t updateVelocity)
{
    position *= Sound::distanceFactor;

    if (updateVelocity)
        SetVelocity((position - m_Info.position) / Time::GetDeltaTime());

    m_Info.position = position;
    SetSourceVector(m_Handle, SourceVector::Position, static_cast<Vector3>(position));
}

void Source::SetVelocity(const Vector2 velocity)
{
    m_Info.velocity = velocity;
    SetSourceVector(m_Handle, SourceVector::Velocity, static_cast<Vector3>(velocity));
}

void Source::SetInfo(const SourceInfo& info)
{
    m_Info = info;
    ApplyInfo();
}

void Source::SetUnstreamedBuffer(Buffer* const buffer) const
{
    SetSourceInt(m_Handle, SourceInt::Buffer, static_cast<int32_t>(buffer->GetHandle()));
    buffer->busy = true;
}

void Source::SetLooping(const bool_t looping) const
{
    SetSourceBool(m_Handle, SourceBool::Looping, looping);
}

SourceState Source::GetState() const
{
    return GetSourceState(m_Handle);
}

const Source::SourceInfo& Source::GetInfo() const { return m_Info; }

void Source::ApplyInfo()
{
    SetVolume(m_Info.volume);
    SetPitch(m_Info.pitch);
    SetPosition(m_Info.position);
    SetVelocity(m_Info.velocity);
}
