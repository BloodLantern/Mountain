#include "Mountain/PrecompiledHeader.hpp"
#include "Mountain/Audio/Sound.hpp"

#include <set>

#include <ImGui/imgui.h>

#include "Audio.hpp"
#include "Mountain/Audio/Context.hpp"
#include "Mountain/FileSystem/File.hpp"
#include "Mountain/Resource/AudioTrack.hpp"
#include "Mountain/Resource/ResourceManager.hpp"
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

    m_Pool = new Audio::Pool;

    return true;
}

void Sound::Shutdown()
{
    Logger::LogVerbose("Shutting down audio");

    delete m_Pool;
    delete m_CurrentContext;
    delete m_CurrentDevice;
}

void Sound::Update()
{
    CheckUpdateDefaultDevice();
    CheckUpdateDefaultList();
}

void Sound::Play(const std::string& trackName)
{
    Play(ResourceManager::Get<AudioTrack>(trackName));
}

void Sound::Play(const Pointer<AudioTrack>& track)
{
    Play(track, Audio::Source::SourceInfo{});
}

void Sound::Play(const Pointer<AudioTrack>& track, const Audio::Source::SourceInfo& info)
{
    Audio::Source* const source = m_Pool->FindFreeSource();

    if (!source)
    {
        Logger::LogError("Trying to play the sound {} but no sources are available", track->GetName());
        return;
    }

    // if (!track->IsStreamed())
        PlayUnstreamedSound(track, source, info);
}

Audio::Context* Sound::GetContext() { return m_CurrentContext; }

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

void Sound::PlayUnstreamedSound(
    const Pointer<AudioTrack>& track,
    Audio::Source* const source,
    const Audio::Source::SourceInfo& info
)
{
    Audio::Buffer* const buffer = m_Pool->FindFreeBuffer();

    if (!buffer)
    {
        Logger::LogError("Trying to play the sound {} but no buffers are available", track->GetName());
        return;
    }

    buffer->SetData(track.Get());
    Audio::Context::CheckError();

    source->SetInfo(info);
    Audio::Context::CheckError();
    source->SetUnstreamedBuffer(buffer);
    Audio::Context::CheckError();
    source->Start();
    Audio::Context::CheckError();
}

float_t Sound::ComputeVolume(const SoundType type)
{
    const float_t global = m_Volumes[static_cast<size_t>(SoundType::Global)];
    const float_t local = m_Volumes[static_cast<size_t>(type)];

    return global * local;
}
