#include "audio/audio.hpp"

#include <set>

#include <AL/alc.h>
#include <AL/alext.h>

#include "ImGui/imgui.h"
#include "utils/logger.hpp"

using namespace Mountain;

bool_t Audio::Initialize()
{
    Logger::LogDebug("Initializing audio");
    
    m_CurrentDevice = new AudioDevice(alcGetString(nullptr, ALC_DEFAULT_ALL_DEVICES_SPECIFIER));

    constexpr std::array enabledEvents = {
        ALC_EVENT_TYPE_DEVICE_ADDED_SOFT,
        ALC_EVENT_TYPE_DEVICE_REMOVED_SOFT,
        ALC_EVENT_TYPE_DEFAULT_DEVICE_CHANGED_SOFT
    };
    alcEventControlSOFT(enabledEvents.size(), enabledEvents.data(), ALC_TRUE);
    alcEventCallbackSOFT(EventCallback, nullptr);
    
    m_CurrentContext = new AudioContext(*m_CurrentDevice);

    return true;
}

void Audio::Shutdown()
{
    Logger::LogDebug("Shutting down audio");

    for (auto&& buffer : m_Buffers)
        delete buffer;

    delete m_CurrentContext;

    delete m_CurrentDevice;
}

void Audio::Update()
{
    if (!m_DefaultDeviceChanged)
        return;

    const std::string defaultDevice = alcGetString(nullptr, ALC_DEFAULT_ALL_DEVICES_SPECIFIER);
        
    if (m_CurrentDevice->GetName() == defaultDevice)
        return;
        
    m_CurrentDevice->Reopen(defaultDevice);
    m_DefaultDeviceChanged = false;
}

AudioContext* Audio::GetContext() { return m_CurrentContext; }

void Audio::RegisterBuffer(AudioBuffer* buffer) { m_Buffers.Add(buffer); }

void Audio::UnregisterBuffer(AudioBuffer* buffer) { m_Buffers.Remove(buffer); }

void Audio::UpdateContext()
{
    delete m_CurrentContext;
    m_CurrentContext = new AudioContext(*m_CurrentDevice);
}

const AudioDevice* Audio::GetCurrentDevice() { return m_CurrentDevice; }

void Audio::SetCurrentDevice(AudioDevice* newCurrentDevice)
{
    m_CurrentDevice = newCurrentDevice;
    UpdateContext();
}

float_t Audio::GetDistanceFactor() { return m_DistanceFactor; }

void Audio::SetDistanceFactor(const float_t newDistanceFactor) { m_DistanceFactor = newDistanceFactor; }

void Audio::DebugDevices()
{
    ImGui::Begin("Audio debug");

    ImGui::SeparatorText("Registered current device");
    ImGui::Text("%s", m_CurrentDevice->GetName().c_str());
    
    // Use std::set to make sure we don't create duplicate devices
    std::set<std::string> deviceNameList;

    // Get all available devices if the extension is present (this should always be the case)
    if (alcIsExtensionPresent(nullptr, "ALC_ENUMERATE_ALL_EXT"))
    {
        const char_t* const deviceNames = alcGetString(nullptr, ALC_ALL_DEVICES_SPECIFIER);
        IterateAlStringList(deviceNames, [&](const char_t* const str) { deviceNameList.emplace(str); });
    }

    // Just in case the enumeration extension isn't present, add the default device
    deviceNameList.emplace(alcGetString(nullptr, ALC_DEFAULT_ALL_DEVICES_SPECIFIER));
    
    ImGui::SeparatorText("Current available devices");
    ImGui::Text("DEFAULT - %s", alcGetString(nullptr, ALC_DEFAULT_ALL_DEVICES_SPECIFIER));
    for (std::string device : deviceNameList)
    {
        ImGui::Text("%s", device.c_str());
    }
    
    ImGui::End();
}

void Audio::EventCallback(
    const ALCenum eventType,
    ALCenum deviceType,
    ALCdevice* device,
    ALCsizei length,
    const ALCchar* message,
    void*
)
{
    // We cannot use OpenAL calls on this thread, so we need to update a flag instead
    if (eventType == ALC_EVENT_TYPE_DEFAULT_DEVICE_CHANGED_SOFT)
        m_DefaultDeviceChanged = true;
    
    Logger::LogInfo("Received audio event callback: eventType={:X}, deviceType={:X}, device={}, length={}, message={}", eventType, deviceType, static_cast<void*>(device), length, message);
}

void Audio::IterateAlStringList(const char_t* list, const std::function<void(const char_t*)>& lambda)
{
    for (int32_t i = 0; list[i] != '\0' || list[i + 1] != '\0'; i++)
    {
        if (i == 0 || list[i - 1] == '\0')
            lambda(list + i);
    }
}
