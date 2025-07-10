#include "Mountain/Audio/Sound.hpp"

#include <set>

#include <AL/alc.h>

#include <ImGui/imgui.h>

#include "Audio.hpp"
#include "Mountain/Audio/AudioContext.hpp"
#include "Mountain/Utils/Logger.hpp"

using namespace Mountain;

bool_t Sound::Initialize()
{
    Logger::LogVerbose("Initializing audio");
    
    m_CurrentDevice = new AudioDevice(Audio::GetDefaultDeviceName());

    constexpr Array enabledEvents = {
        Audio::EventType::DeviceChanged
    };
    Audio::SetEventCallback(enabledEvents, [](const Audio::EventType type, const std::string&)
    {
        // We cannot use OpenAL calls on this thread, so we need to update a flag instead
        if (type == Audio::EventType::DeviceChanged)
            m_DefaultDeviceChanged = true;
    });

    m_CurrentContext = new AudioContext(*m_CurrentDevice);

    return true;
}

void Sound::Shutdown()
{
    Logger::LogVerbose("Shutting down audio");

    for (auto&& buffer : m_Buffers)
        delete buffer;

    delete m_CurrentContext;

    delete m_CurrentDevice;
}

void Sound::Update()
{
    if (!m_DefaultDeviceChanged)
        return;

    const std::string defaultDevice = Audio::GetDefaultDeviceName();
        
    if (m_CurrentDevice->GetName() == defaultDevice)
        return;
        
    m_CurrentDevice->Reopen(defaultDevice);
    m_DefaultDeviceChanged = false;
}

AudioContext* Sound::GetContext() { return m_CurrentContext; }

void Sound::RegisterBuffer(AudioBuffer* buffer) { m_Buffers.Add(buffer); }

void Sound::UnregisterBuffer(AudioBuffer* buffer) { m_Buffers.Remove(buffer); }

void Sound::UpdateContext()
{
    delete m_CurrentContext;
    m_CurrentContext = new AudioContext(*m_CurrentDevice);
}

const AudioDevice* Sound::GetCurrentDevice() { return m_CurrentDevice; }

void Sound::SetCurrentDevice(AudioDevice* newCurrentDevice)
{
    m_CurrentDevice = newCurrentDevice;
    UpdateContext();
}

float_t Sound::GetDistanceFactor() { return m_DistanceFactor; }

void Sound::SetDistanceFactor(const float_t newDistanceFactor) { m_DistanceFactor = newDistanceFactor; }
