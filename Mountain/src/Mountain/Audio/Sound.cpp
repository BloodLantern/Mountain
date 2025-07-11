#include "Mountain/Audio/Sound.hpp"

#include <set>

#include <ImGui/imgui.h>

#include "Audio.hpp"
#include "magic_enum/magic_enum_containers.hpp"
#include "Mountain/Audio/Context.hpp"
#include "Mountain/Utils/Logger.hpp"

using namespace Mountain;

bool_t Sound::Initialize()
{
    Logger::LogVerbose("Initializing audio");

    m_CurrentDevice = new Audio::Device(Audio::GetDefaultDeviceName());
    Audio::GetAllDevices(m_DeviceNames);
    
    constexpr Array enabledEvents = {
        Audio::EventType::DeviceChanged,
        Audio::EventType::DeviceAdded,
        Audio::EventType::DeviceRemoved,
    };

    SetEventCallback(enabledEvents, [](const Audio::EventType type, const std::string&)
    {
        // We cannot use OpenAL calls on this thread, so we need to update a flag instead
        switch (type)
        {
            case Audio::EventType::DeviceChanged:
                m_DefaultDeviceChanged = true;
                break;

            case Audio::EventType::DeviceAdded:
            case Audio::EventType::DeviceRemoved:
                m_DeviceListChanged = true;
                break;
        }
    });

    m_CurrentContext = new Audio::Context(*m_CurrentDevice);

    // Initialize everything at 100% for now, TODO save settings/config
    m_Volumes.Fill(1.f);

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
    CheckUpdateDefaultDevice();
    CheckUpdateDefaultList();
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

const List<std::string>& Sound::GetDeviceNames() { return m_DeviceNames; }

float_t Sound::GetVolume(const SoundType type) { return m_Volumes[static_cast<size_t>(type)]; }

void Sound::SetVolume(const SoundType type, const float_t value)
{
    m_Volumes[static_cast<size_t>(type)] = std::clamp(value, 0.f, 1.f);
}

void Sound::CheckUpdateDefaultDevice()
{
    if (!m_DefaultDeviceChanged)
        return;

    const std::string defaultDevice = Audio::GetDefaultDeviceName();
        
    if (m_CurrentDevice->GetName() == defaultDevice)
        return;
        
    m_CurrentDevice->Reopen(defaultDevice);
    m_DefaultDeviceChanged = false;

}

void Sound::CheckUpdateDefaultList()
{
    if (!m_DeviceListChanged)
        return;

    Audio::GetAllDevices(m_DeviceNames);
    m_DeviceListChanged = false;
}

float_t Sound::ComputeVolume(const SoundType type)
{
    const float_t global = m_Volumes[static_cast<size_t>(SoundType::Global)];
    const float_t local = m_Volumes[static_cast<size_t>(type)];

    return global * local;
}
