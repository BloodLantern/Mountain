#include "Mountain/PrecompiledHeader.hpp"
#include "Context.hpp"

#include <AL/alc.h>

#include <magic_enum/magic_enum.hpp>

#include "Audio.hpp"
#include "Device.hpp"
#include "Mountain/Containers/EnumerableExt.hpp"
#include "Mountain/Utils/Logger.hpp"

using namespace Mountain::Audio;

Context::Context(Device& device)
    : m_Handle(CreateContext(device.m_Handle))
    , m_Device(&device)
{
    if (!m_Handle || Device::CheckError(m_Device))
    {
        Logger::LogError("Unable to create audio context for device {}", device.GetName());
        return;
    }

    MakeCurrent();

    // Get the context attribute values
    GetDeviceAttributes(m_Device->m_Handle, m_Attributes);
}

Context::~Context()
{
    SetContext(nullptr);
    DestroyContext(m_Handle);
    Device::CheckError(m_Device);
}

void Context::MakeCurrent() const { SetContext(m_Handle); }

bool_t Context::CheckError()
{
    const Error error = GetError();

    if (error != Error::None)
    {
        Logger::LogError("[OpenAL] {}", GetErrorString(error));
        return true;
    }

    return false;
}

int32_t Context::GetMaxSourceCount(const SourceType sourceType) const
{
    const ContextAttribute attr = sourceType == SourceType::Mono ? ContextAttribute::MonoSourceAmount : ContextAttribute::StereoSourceAmount;

    return GetDeviceAttribute(m_Attributes, attr);
}

uint32_t Context::GetSource(const SourceType type)
{
    List<uint32_t>& sources = type == SourceType::Mono ? m_SourcesMono : m_SourcesStereo;

    List<SourceState> states(sources.GetSize());

    MakeCurrent();

    ForEach(sources,
        [&] (const uint32_t& s)
        {
            states.Add(GetSourceState(s));
        }
    );

    uint32_t source = 0;
    for (size_t i = 0; i < sources.GetSize(); i++)
    {
        if (states[i] != SourceState::Initial)
            continue;

        source = sources[i];
        break;
    }

    if (source != 0)
        return source;

    for (size_t i = 0; i < sources.GetSize(); i++)
    {
        if (states[i] != SourceState::Stopped)
            continue;

        source = sources[i];
        break;
    }

    if (source != 0)
    {
        // Rewind the source back to the AL_INITIAL state
        RewindSource(source);
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

    source = CreateSource();

    if (CheckError())
        THROW(InvalidOperationException{"Cannot generate audio source"});

    sources.Add(source);

    return source;
}
