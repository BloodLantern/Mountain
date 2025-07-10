#include "Mountain/Audio/Sound.hpp"

#include <set>

#include <ImGui/imgui.h>

#include "Audio.hpp"
#include "Mountain/Audio/Context.hpp"
#include "Mountain/Utils/Logger.hpp"

using namespace Mountain;

bool_t Sound::Initialize()
{
    Logger::LogVerbose("Initializing audio");

    m_CurrentDevice = new Audio::Device(Audio::GetDefaultDeviceName());

    constexpr Array enabledEvents = {
        Audio::EventType::DeviceChanged
    };
    SetEventCallback(enabledEvents, [](const Audio::EventType type, const std::string&)
    {
        // We cannot use OpenAL calls on this thread, so we need to update a flag instead
        if (type == Audio::EventType::DeviceChanged)
            m_DefaultDeviceChanged = true;
    });

    m_CurrentContext = new Audio::Context(*m_CurrentDevice);

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

Audio::Context* Sound::GetContext() { return m_CurrentContext; }

void Sound::RegisterBuffer(Audio::Buffer* const buffer) { m_Buffers.Add(buffer); }

void Sound::UnregisterBuffer(Audio::Buffer* const buffer) { m_Buffers.Remove(buffer); }

void Sound::UpdateContext()
{
    delete m_CurrentContext;
    m_CurrentContext = new Audio::Context(*m_CurrentDevice);
}

const Audio::Device* Sound::GetCurrentDevice() { return m_CurrentDevice; }

void Sound::SetCurrentDevice(Audio::Device* newCurrentDevice)
{
    m_CurrentDevice = newCurrentDevice;
    UpdateContext();
}
