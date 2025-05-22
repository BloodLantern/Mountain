module;

#include <AL/alext.h>

module Mountain:Audio_AudioDevice;
import :Audio_AudioDevice;

import :Utils_Logger;

using namespace Mountain;

bool_t AudioDevice::CheckError(const AudioDevice* device)
{
    ALCdevice* const handle = device ? device->m_Handle : nullptr;

    const ALCenum error = alcGetError(handle);

    if (error != ALC_NO_ERROR)
    {
        Logger::LogError("[OpenAL Context] {}", std::string_view(alcGetString(handle, error)));
        return true;
    }

    return false;
}

AudioDevice::AudioDevice(std::string&& name)
    : m_Handle(alcOpenDevice(name.c_str()))
    , m_Name(std::move(name))
{
    if (!m_Handle || CheckError(this))
    {
        Logger::LogError("Unable to open audio device {}", m_Name);
        return;
    }
}

AudioDevice::~AudioDevice() { alcCloseDevice(m_Handle); }

void AudioDevice::Reopen(const std::string& newName)
{
    alcReopenDeviceSOFT(m_Handle, newName.c_str(), nullptr);
    m_Name = newName;
}

std::string AudioDevice::GetName() const { return m_Name; }
