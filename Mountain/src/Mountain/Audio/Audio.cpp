#include "Mountain/PrecompiledHeader.hpp"

#include "Mountain/Audio/Audio.hpp"

#include <set>

#include <AL/alc.h>
#include <AL/alext.h>

#include <ImGui/imgui.h>

#include "Mountain/Globals.hpp"
#include "Mountain/Audio/AudioContext.hpp"
#include "Mountain/Utils/Logger.hpp"

using namespace Mountain;

bool_t Audio::Initialize()
{
    if (NoBuiltinAudio)
        return true;

    ZoneScoped;

    Logger::LogVerbose("Initializing audio");

    m_CurrentDevice = new AudioDevice(alcGetString(nullptr, ALC_DEFAULT_ALL_DEVICES_SPECIFIER));

    constexpr std::array enabledEvents = {
        ALC_EVENT_TYPE_DEFAULT_DEVICE_CHANGED_SOFT
    };
    alcEventControlSOFT(static_cast<ALCsizei>(enabledEvents.size()), enabledEvents.data(), ALC_TRUE);
    alcEventCallbackSOFT(EventCallback, nullptr);

    m_CurrentContext = new AudioContext(*m_CurrentDevice);

    return true;
}

void Audio::Shutdown()
{
    if (NoBuiltinAudio)
        return;

    ZoneScoped;

    Logger::LogVerbose("Shutting down audio");

    for (auto&& buffer : m_Buffers)
        delete buffer;

    delete m_CurrentContext;

    delete m_CurrentDevice;
}

void Audio::Update()
{
    if (NoBuiltinAudio)
        return;

    ZoneScoped;

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

void Audio::EventCallback(
    const ALCenum eventType,
    ALCenum,
    ALCdevice*,
    ALCsizei,
    const ALCchar*,
    void*
)
{
    // We cannot use OpenAL calls on this thread, so we need to update a flag instead
    if (eventType == ALC_EVENT_TYPE_DEFAULT_DEVICE_CHANGED_SOFT)
        m_DefaultDeviceChanged = true;
}

void Audio::IterateAlStringList(const char_t* list, const std::function<void(const char_t*)>& lambda)
{
    for (int32_t i = 0; list[i] != '\0' || list[i + 1] != '\0'; i++)
    {
        if (i == 0 || list[i - 1] == '\0')
            lambda(list + i);
    }
}
