#pragma once

#include <functional>

#include "magic_enum/magic_enum.hpp"
#include "Mountain/Core.hpp"
#include "Mountain/Audio/Buffer.hpp"
#include "Mountain/Audio/Context.hpp"
#include "Mountain/Audio/Device.hpp"
#include "Mountain/Containers/List.hpp"

// TODO - Add a Sound::Play function

namespace Mountain
{
    /// @brief The type of a sound, determines the volume applied
    /// which is the global volume and the specific sound type volume
    enum class SoundType : uint8_t
    {
        /// @brief No additional modifier applied, just the global one
        Global,

        Music,
        Sound,
        Voice
    };
    
    class Sound
    {
        STATIC_CLASS(Sound)

    public:
        MOUNTAIN_API static bool_t Initialize();

        MOUNTAIN_API static void Shutdown();

        MOUNTAIN_API static void Update();

        /// @brief Returns the current device's context.
        [[nodiscard]]
        MOUNTAIN_API static Audio::Context* GetContext();

        MOUNTAIN_API static void RegisterBuffer(Audio::Buffer* buffer);

        MOUNTAIN_API static void UnregisterBuffer(Audio::Buffer* buffer);

        MOUNTAIN_API static void UpdateContext();

        MOUNTAIN_API static const Audio::Device* GetCurrentDevice();

        MOUNTAIN_API static void SetCurrentDevice(Audio::Device* newCurrentDevice);

        MOUNTAIN_API static const List<std::string>& GetDeviceNames();

        ATTRIBUTE_NODISCARD
        MOUNTAIN_API static float_t GetVolume(SoundType type);
        MOUNTAIN_API static void SetVolume(SoundType type, float_t value);

        MOUNTAIN_API static inline float_t distanceFactor = 0.2f;

    private:
        MOUNTAIN_API static void CheckUpdateDefaultDevice();
        MOUNTAIN_API static void CheckUpdateDefaultList();

        ATTRIBUTE_NODISCARD
        MOUNTAIN_API static float_t ComputeVolume(SoundType type);

        MOUNTAIN_API static inline Array<float_t, magic_enum::enum_count<SoundType>()> m_Volumes;

        MOUNTAIN_API static inline Audio::Device* m_CurrentDevice = nullptr;
        MOUNTAIN_API static inline Audio::Context* m_CurrentContext = nullptr;

        MOUNTAIN_API static inline List<Audio::Buffer*> m_Buffers;
        MOUNTAIN_API static inline List<std::string> m_DeviceNames;

        MOUNTAIN_API static inline bool_t m_DefaultDeviceChanged = false;
        MOUNTAIN_API static inline bool_t m_DeviceListChanged = false;
    };
}
