#include "Mountain/Audio/AudioContext.hpp"

#include <AL/al.h>
#include <AL/alc.h>

#include <magic_enum/magic_enum.hpp>

#include "Audio.hpp"
#include "Mountain/Audio/AudioDevice.hpp"
#include "Mountain/Containers/EnumerableExt.hpp"
#include "Mountain/Utils/Logger.hpp"

using namespace Mountain;

AudioContext::AudioContext(AudioDevice& device)
    : m_Handle(alcCreateContext(device.m_Handle, nullptr))
    , m_Device(&device)
{
    if (!m_Handle || AudioDevice::CheckError(m_Device))
    {
        Logger::LogError("Unable to create audio context for device {}", device.GetName());
        return;
    }

    MakeCurrent();

    // Get the context attribute values
    Audio::GetDeviceAttributes(m_Device->m_Handle, m_Attributes);
}

AudioContext::~AudioContext()
{
    alcMakeContextCurrent(nullptr);
    alcDestroyContext(m_Handle);
    AudioDevice::CheckError(m_Device);
}

void AudioContext::MakeCurrent() const { alcMakeContextCurrent(m_Handle); }

bool_t AudioContext::CheckError()
{
    const Audio::Error error = Audio::GetError();

    if (error != Audio::Error::None)
    {
        Logger::LogError("[OpenAL] {}", Audio::GetErrorString(error));
        return true;
    }

    return false;
}

int32_t AudioContext::GetMaxSourceCount(const Audio::SourceType sourceType) const
{
    const Audio::ContextAttribute attr = sourceType == Audio::SourceType::Mono ?
        Audio::ContextAttribute::MonoSourceAmount :
        Audio::ContextAttribute::StereoSourceAmount;

    return Audio::GetDeviceAttribute(m_Attributes, attr);
}

uint32_t AudioContext::GetSource(const Audio::SourceType type)
{
    List<uint32_t>& sources = type == Audio::SourceType::Mono ? m_SourcesMono : m_SourcesStereo;

    List<Audio::SourceState> states(sources.GetSize());

    MakeCurrent();

    ForEach(sources,
        [&] (const uint32_t& s)
        {
            states.Add(Audio::GetSourceState(s));
        }
    );

    uint32_t source = 0;
    for (size_t i = 0; i < sources.GetSize(); i++)
    {
        if (states[i] != Audio::SourceState::Initial)
            continue;

        source = sources[i];
        break;
    }

    if (source != 0)
        return source;

    for (size_t i = 0; i < sources.GetSize(); i++)
    {
        if (states[i] != Audio::SourceState::Stopped)
            continue;

        source = sources[i];
        break;
    }

    if (source != 0)
    {
        // Rewind the source back to the AL_INITIAL state
        alSourceRewind(source);
        return source;
    }

    const int32_t maxCount = GetMaxSourceCount(type);

    if (sources.GetSize() >= static_cast<uint32_t>(maxCount))
    {
        Logger::LogWarning("The maximum amount of audio sources of type {} has been reached, resetting the first one", magic_enum::enum_name(type));
        return sources[0];
    }

    // Reset the error state here to avoid throwing an exception for a different OpenAL error
    CheckError();

    alGenSources(1, &source);

    if (CheckError())
        THROW(InvalidOperationException{"Cannot generate audio source"});

    sources.Add(source);

    return source;
}
