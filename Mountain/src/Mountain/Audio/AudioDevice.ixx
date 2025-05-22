export module Mountain:Audio_AudioDevice;

import <AL/alc.h>;

import "Mountain/Core.hpp";

import std;
export import :Core;

export namespace Mountain
{
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
}
