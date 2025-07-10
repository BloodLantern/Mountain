#include "Mountain/Audio/Device.hpp"

#include "Audio.hpp"
#include "Mountain/Utils/Logger.hpp"

using namespace Mountain::Audio;

bool_t Device::CheckError(const Device* device)
{
    ALCdevice* const handle = device ? device->m_Handle : nullptr;

    const ContextError error = GetContextError(handle);

    if (error != ContextError::None)
    {
        Logger::LogError("[OpenAL Context] {}", GetContextErrorString(handle, error));
        return true;
    }

    return false;
}

Device::Device(std::string&& name)
    : m_Handle(OpenDevice(name))
    , m_Name(std::move(name))
{
    if (!m_Handle || CheckError(this))
    {
        Logger::LogError("Unable to open audio device {}", m_Name);
        return;
    }
}

Device::~Device() { CloseDevice(m_Handle); }

void Device::Reopen(const std::string& newName)
{
    ReopenDevice(m_Handle, newName);
    m_Name = newName;
}
