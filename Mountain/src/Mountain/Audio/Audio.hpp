#pragma once

#include <functional>

#include "Mountain/Core.hpp"
#include "Mountain/Audio/AudioBuffer.hpp"
#include "Mountain/Audio/AudioDevice.hpp"
#include "Mountain/Containers/List.hpp"

// OpenAL type forward declaration

// ReSharper disable once CppEnforceTypeAliasCodeStyle
// ReSharper disable once CppInconsistentNaming
typedef char ALCchar;
// ReSharper disable once CppEnforceTypeAliasCodeStyle
// ReSharper disable once CppInconsistentNaming
typedef int ALCsizei;
// ReSharper disable once CppEnforceTypeAliasCodeStyle
// ReSharper disable once CppInconsistentNaming
typedef int ALCenum;

// TODO - Add an Audio::Play function

namespace Mountain
{
    class Audio
    {
        STATIC_CLASS(Audio)

    public:
        MOUNTAIN_API static bool_t Initialize();

        MOUNTAIN_API static void Shutdown();

        MOUNTAIN_API static void Update();

        /// @brief Returns the current device's context.
        ATTRIBUTE_NODISCARD
        MOUNTAIN_API static AudioContext* GetContext();

        MOUNTAIN_API static void RegisterBuffer(AudioBuffer* buffer);

        MOUNTAIN_API static void UnregisterBuffer(AudioBuffer* buffer);

        MOUNTAIN_API static void UpdateContext();

        MOUNTAIN_API static const AudioDevice* GetCurrentDevice();

        MOUNTAIN_API static void SetCurrentDevice(AudioDevice* newCurrentDevice);

        MOUNTAIN_API static float_t GetDistanceFactor();

        MOUNTAIN_API static void SetDistanceFactor(float_t newDistanceFactor);

    private:
        MOUNTAIN_API static inline AudioDevice* m_CurrentDevice = nullptr;
        MOUNTAIN_API static inline AudioContext* m_CurrentContext = nullptr;

        MOUNTAIN_API static inline List<AudioBuffer*> m_Buffers;

        MOUNTAIN_API static inline float_t m_DistanceFactor = 0.2f;

        MOUNTAIN_API static inline bool_t m_DefaultDeviceChanged = false;

        static void EventCallback(ALCenum eventType, ALCenum deviceType, ALCdevice* device, ALCsizei length, const ALCchar* message, void* userParam);

        /// @brief Iterates over an OpenAL string list, applying the given lambda on each string.
        ///
        /// OpenAL string lists are strings separated by null characters, and ending with two consecutive null characters.
        static void IterateAlStringList(const char_t* list, const std::function<void(const char_t*)>& lambda);
    };
}
