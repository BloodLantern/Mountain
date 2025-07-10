#include "Mountain/Audio/Audio.hpp"

#include "AL/alext.h"
#include "Mountain/Exceptions/ThrowHelper.hpp"

using namespace Mountain;

std::string Audio::GetDefaultDeviceName()
{
    return alcGetString(nullptr, ALC_DEFAULT_ALL_DEVICES_SPECIFIER);
}

uint32_t Audio::CreateSource()
{
    uint32_t source;
    alGenSources(1, &source);
    return source;
}

List<uint32_t> Audio::CreateSources(const size_t count)
{
    List<uint32_t> sources;
    sources.Resize(count);
    alGenSources(static_cast<int32_t>(count), sources.GetData());
    return sources;
}

void Audio::DeleteSource(const uint32_t source)
{
    alDeleteSources(1, &source);
}

void Audio::DeleteSources(const List<uint32_t>& sources)
{
    alDeleteSources(static_cast<int32_t>(sources.GetSize()), sources.GetData());
}

void Audio::PlaySource(const uint32_t source)
{
    alSourcePlay(source);
}

void Audio::RewindSource(const uint32_t source)
{
    alSourceRewind(source);
}

void Audio::SetSourceVector(const uint32_t source, const SourceVector type, const Vector3& value)
{
    alSourcefv(source, ToOpenAl(type), value.Data());
}

void Audio::SetSourceFloat(const uint32_t source, const SourceFloat type, const float_t value)
{
    alSourcef(source, ToOpenAl(type), value);
}

void Audio::SetSourceInt(const uint32_t source, const SourceInt type, const int32_t value)
{
    alSourcei(source, ToOpenAl(type), value);
}

void Audio::SetSourceBool(const uint32_t source, const SourceBool type, const bool_t value)
{
    alSourcei(source, ToOpenAl(type), value);
}

Audio::SourceType Audio::GetSourceType(const uint32_t source)
{
    int32_t v;
    alGetSourcei(source, ToOpenAl(SourceInt::SourceType), &v);
    return FromOpenAl<SourceType>(v);
}

void Audio::SetListenerVector(const ListenerVector type, const Vector3& value)
{
    alListenerfv(ToOpenAl(type), value.Data());
}

void Audio::SetListenerFloat(const ListenerFloat type, const float_t value)
{
    alListenerf(ToOpenAl(type), value);
}

void Audio::SetListenerArray(const ListenerArray type, const Array<Vector3, 2>& value)
{
    const Vector3* const ptr = value.GetData();
    alListenerfv(ToOpenAl(type), &ptr->x);
}

template <>
Audio::EventType Audio::FromOpenAl<Audio::EventType>(const int32_t value)
{
    switch (value)
    {
        case ALC_EVENT_TYPE_DEFAULT_DEVICE_CHANGED_SOFT: return EventType::DeviceChanged;
        case ALC_EVENT_TYPE_DEVICE_ADDED_SOFT: return EventType::DeviceAdded;
        case ALC_EVENT_TYPE_DEVICE_REMOVED_SOFT: return EventType::DeviceRemoved;

        default: THROW(ArgumentOutOfRangeException{"Invalid audio event type", "value"});
    }
}

template <>
Audio::SourceVector Audio::FromOpenAl<Audio::SourceVector>(const int32_t value)
{
    switch (value)
    {
        case AL_DIRECTION: return SourceVector::Direction;
        case AL_POSITION: return SourceVector::Position;
        case AL_VELOCITY: return SourceVector::Velocity;

        default: THROW(ArgumentOutOfRangeException{"Invalid source float vector type", "value"});
    }
}

template <>
Audio::SourceFloat Audio::FromOpenAl<Audio::SourceFloat>(const int32_t value)
{
    switch (value)
    {
        case AL_CONE_INNER_ANGLE: return SourceFloat::ConeInnerAngle;
        case AL_CONE_OUTER_ANGLE: return SourceFloat::ConeOuterAngle;
        case AL_CONE_OUTER_GAIN: return SourceFloat::ConeOuterGain;
        case AL_GAIN: return SourceFloat::Gain;
        case AL_MAX_DISTANCE: return SourceFloat::MaxDistance;
        case AL_MAX_GAIN: return SourceFloat::MaxGain;
        case AL_MIN_GAIN: return SourceFloat::MinGain;
        case AL_PITCH: return SourceFloat::Pitch;
        case AL_REFERENCE_DISTANCE: return SourceFloat::ReferenceDistance;
        case AL_ROLLOFF_FACTOR: return SourceFloat::RollOffFactor;
        case AL_SEC_OFFSET: return SourceFloat::SecondsOffset;

        default: THROW(ArgumentOutOfRangeException{"Invalid source float type", "value"});
    }
}

template <>
Audio::SourceInt Audio::FromOpenAl<Audio::SourceInt>(const int32_t value)
{
    switch (value)
    {
        case AL_BUFFER: return SourceInt::Buffer;
        case AL_BYTE_OFFSET: return SourceInt::ByteOffset;
        case AL_SAMPLE_OFFSET: return SourceInt::SampleOffset;
        case AL_SOURCE_TYPE: return SourceInt::SourceType;

        default: THROW(ArgumentOutOfRangeException{"Invalid source int type", "value"});
    }
}

template <>
Audio::SourceBool Audio::FromOpenAl<Audio::SourceBool>(const int32_t value)
{
    switch (value)
    {
        case AL_LOOPING: return SourceBool::Looping;
        case AL_SOURCE_RELATIVE: return SourceBool::SourceRelative;

        default: THROW(ArgumentOutOfRangeException{"Invalid source bool type", "value"});
    }
}

template <>
Audio::SourceType Audio::FromOpenAl<Audio::SourceType>(const int32_t value)
{
    switch (value)
    {
        case AL_STATIC: return SourceType::Static;
        case AL_STREAMING: return SourceType::Streaming;
        case AL_UNDETERMINED: return SourceType::Undetermined;

        default: THROW(ArgumentOutOfRangeException{"Invalid source type", "value"});
    }
}

template <>
Audio::ListenerVector Audio::FromOpenAl<Audio::ListenerVector>(const int32_t value)
{
    switch (value)
    {
        case AL_POSITION: return ListenerVector::Position;
        case AL_VELOCITY: return ListenerVector::Velocity;

        default: THROW(ArgumentOutOfRangeException{"Invalid listener vector type", "value"});
    }
}

template <>
Audio::ListenerFloat Audio::FromOpenAl<Audio::ListenerFloat>(const int32_t value)
{
    switch (value)  // NOLINT(hicpp-multiway-paths-covered)
    {
        case AL_GAIN: return ListenerFloat::Gain;

        default: THROW(ArgumentOutOfRangeException{"Invalid listener float type", "value"});
    }
}

template <>
Audio::ListenerArray Audio::FromOpenAl<Audio::ListenerArray>(const int32_t value)
{
    switch (value)  // NOLINT(hicpp-multiway-paths-covered)
    {
        case AL_ORIENTATION: return ListenerArray::Orientation;

        default: THROW(ArgumentOutOfRangeException{"Invalid listener float type", "value"});
    }
}

int32_t Audio::ToOpenAl(const EventType value)
{
    switch (value)
    {
        case EventType::DeviceChanged: return ALC_EVENT_TYPE_DEFAULT_DEVICE_CHANGED_SOFT;
        case EventType::DeviceAdded: return ALC_EVENT_TYPE_DEVICE_ADDED_SOFT;
        case EventType::DeviceRemoved: return ALC_EVENT_TYPE_DEVICE_REMOVED_SOFT;
    }

    THROW(ArgumentOutOfRangeException{"Invalid audio event type", "value"});
}

int32_t Audio::ToOpenAl(const SourceVector value)
{
    switch (value)
    {
        case SourceVector::Direction: return AL_DIRECTION;
        case SourceVector::Position: return AL_POSITION;
        case SourceVector::Velocity: return AL_VELOCITY;
    }

    THROW(ArgumentOutOfRangeException{"Invalid source float vector type", "value"});
}

int32_t Audio::ToOpenAl(const SourceFloat value)
{
    switch (value)
    {
        case SourceFloat::ConeInnerAngle: return AL_CONE_INNER_ANGLE;
        case SourceFloat::ConeOuterAngle: return AL_CONE_OUTER_ANGLE;
        case SourceFloat::ConeOuterGain: return AL_CONE_OUTER_GAIN;
        case SourceFloat::Gain: return AL_GAIN;
        case SourceFloat::MaxDistance: return AL_MAX_DISTANCE;
        case SourceFloat::MaxGain: return AL_MAX_GAIN;
        case SourceFloat::MinGain: return AL_MIN_GAIN;
        case SourceFloat::Pitch: return AL_PITCH;
        case SourceFloat::ReferenceDistance: return AL_REFERENCE_DISTANCE;
        case SourceFloat::RollOffFactor: return AL_ROLLOFF_FACTOR;
        case SourceFloat::SecondsOffset: return AL_SEC_OFFSET;
    }

    THROW(ArgumentOutOfRangeException{"Invalid source float type", "value"});
}

int32_t Audio::ToOpenAl(const SourceInt value)
{
    switch (value)
    {
        case SourceInt::Buffer: return AL_BUFFER;
        case SourceInt::ByteOffset: return AL_BYTE_OFFSET;
        case SourceInt::SampleOffset: return AL_SAMPLE_OFFSET;
        case SourceInt::SourceType: return AL_SOURCE_TYPE;
    }

    THROW(ArgumentOutOfRangeException{"Invalid source int type", "value"});
}

int32_t Audio::ToOpenAl(const SourceBool value)
{
    switch (value)
    {
        case SourceBool::Looping: return AL_LOOPING;
        case SourceBool::SourceRelative: return AL_SOURCE_RELATIVE;
    }

    THROW(ArgumentOutOfRangeException{"Invalid source bool type", "value"});
}

int32_t Audio::ToOpenAl(const SourceType value)
{
    switch (value)
    {
        case SourceType::Static: return AL_STATIC;
        case SourceType::Streaming: return AL_STREAMING;
        case SourceType::Undetermined: return AL_UNDETERMINED;
    }

    THROW(ArgumentOutOfRangeException{"Invalid source type", "value"});
}

int32_t Audio::ToOpenAl(const ListenerVector value)
{
    switch (value)
    {
        case ListenerVector::Position: return AL_POSITION;
        case ListenerVector::Velocity: return AL_VELOCITY;
    }

    THROW(ArgumentOutOfRangeException{"Invalid listener vector type", "value"});
}

int32_t Audio::ToOpenAl(const ListenerFloat value)
{
    switch (value)
    {
        case ListenerFloat::Gain: return AL_GAIN;
    }

    THROW(ArgumentOutOfRangeException{"Invalid listener float type", "value"});
}

int32_t Audio::ToOpenAl(const ListenerArray value)
{
    switch (value)
    {
        case ListenerArray::Orientation: return AL_ORIENTATION;
    }

    THROW(ArgumentOutOfRangeException{"Invalid listener float type", "value"});
}
