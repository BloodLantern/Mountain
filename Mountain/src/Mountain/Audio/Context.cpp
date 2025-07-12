#include "Mountain/PrecompiledHeader.hpp"
#include "Context.hpp"

#include <AL/alc.h>

#include "Audio.hpp"
#include "Device.hpp"
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
