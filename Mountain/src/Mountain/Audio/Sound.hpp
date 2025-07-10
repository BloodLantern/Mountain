#pragma once

#include <functional>

#include "Mountain/Core.hpp"
#include "Mountain/Audio/Buffer.hpp"
#include "Mountain/Audio/Context.hpp"
#include "Mountain/Audio/Device.hpp"
#include "Mountain/Containers/List.hpp"

// TODO - Add an Audio::Play function

namespace Mountain
{
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

        MOUNTAIN_API static inline float_t distanceFactor = 0.2f;

    private:
        MOUNTAIN_API static inline Audio::Device* m_CurrentDevice = nullptr;
        MOUNTAIN_API static inline Audio::Context* m_CurrentContext = nullptr;

        MOUNTAIN_API static inline List<Audio::Buffer*> m_Buffers;

        MOUNTAIN_API static inline bool_t m_DefaultDeviceChanged = false;
    };
}
