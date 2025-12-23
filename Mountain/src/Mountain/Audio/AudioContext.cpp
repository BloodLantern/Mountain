

#include "Mountain/Audio/AudioContext.hpp"

#include <AL/al.h>
#include <AL/alc.h>

#include <magic_enum/magic_enum.hpp>

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
    s32 size = 0;
    alcGetIntegerv(m_Device->m_Handle, ALC_ATTRIBUTES_SIZE, 1, &size);
    m_Attributes.Resize(size);
    alcGetIntegerv(m_Device->m_Handle, ALC_ALL_ATTRIBUTES, size, m_Attributes.GetData());
}

AudioContext::~AudioContext()
{
    alcMakeContextCurrent(nullptr);
    alcDestroyContext(m_Handle);
    AudioDevice::CheckError(m_Device);
}

void AudioContext::MakeCurrent() const { alcMakeContextCurrent(m_Handle); }

bool AudioContext::CheckError()
{
    const ALCenum error = alGetError();

    if (error != AL_NO_ERROR)
    {
        Logger::LogError("[OpenAL] {}", std::string_view(alGetString(error)));
        return true;
    }

    return false;
}

s32 AudioContext::GetMaxSourceCount(const AudioSourceType sourceType) const
{
    s32 result = 0;

    for (usize i = 0; i < m_Attributes.GetSize(); i++)
    {
        if ((sourceType == AudioSourceType::Mono && m_Attributes[i] == ALC_MONO_SOURCES) || (sourceType == AudioSourceType::Stereo && m_Attributes[i] == ALC_STEREO_SOURCES))
            result += m_Attributes[i + 1];
    }

    return result;
}

u32 AudioContext::GetSource(const AudioSourceType type)
{
    List<u32>& sources = type == AudioSourceType::Mono ? m_SourcesMono : m_SourcesStereo;

    List<s32> states(sources.GetSize());

    MakeCurrent();

    ForEach(sources,
        [&] (const u32& s)
        {
            s32 value = 0;
            alGetSourcei(s, AL_SOURCE_STATE, &value);
            states.Add(value);
        }
    );

    u32 source = 0;
    for (usize i = 0; i < sources.GetSize(); i++)
    {
        if (states[i] != AL_INITIAL)
            continue;

        source = sources[i];
        break;
    }

    if (source != 0)
        return source;

    for (usize i = 0; i < sources.GetSize(); i++)
    {
        if (states[i] != AL_STOPPED)
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

    const s32 maxCount = GetMaxSourceCount(type);

    if (sources.GetSize() >= static_cast<u32>(maxCount))
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
