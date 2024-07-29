#pragma once

#include <string>

#include "core.hpp"
#include "audio/audio_context.hpp"

// ReSharper disable once CppInconsistentNaming
struct ALCdevice;

BEGIN_MOUNTAIN

class AudioDevice
{
public:
    MOUNTAIN_API static bool_t CheckError(const AudioDevice* device = nullptr);

    [[nodiscard]]
    MOUNTAIN_API explicit AudioDevice(std::string&& name);

    MOUNTAIN_API ~AudioDevice();

    DELETE_COPY_MOVE_OPERATIONS(AudioDevice)

    MOUNTAIN_API void Reopen(const std::string& newName);

    [[nodiscard]]
    MOUNTAIN_API std::string GetName() const;

private:
    ALCdevice* m_Handle = nullptr;
    std::string m_Name;

    // AudioContext needs to access the handle of this class
    friend class AudioContext;
};

END_MOUNTAIN
