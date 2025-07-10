#pragma once

#include <string>

#include "Mountain/Core.hpp"

// ReSharper disable once CppInconsistentNaming
struct ALCdevice;

namespace Mountain
{
    class AudioDevice
    {
    public:
        MOUNTAIN_API static bool_t CheckError(const AudioDevice* device = nullptr);

        ATTRIBUTE_NODISCARD
        MOUNTAIN_API explicit AudioDevice(std::string&& name);

        MOUNTAIN_API ~AudioDevice();

        DELETE_COPY_MOVE_OPERATIONS(AudioDevice)

        MOUNTAIN_API void Reopen(const std::string& newName);

        ATTRIBUTE_NODISCARD
        MOUNTAIN_API std::string GetName() const;

    private:
        ALCdevice* m_Handle = nullptr;
        std::string m_Name;

        // AudioContext needs to access the handle of this class
        friend class AudioContext;
    };
}
