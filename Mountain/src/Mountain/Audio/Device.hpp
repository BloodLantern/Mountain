#pragma once

#include <string>

#include "Mountain/Core.hpp"

// ReSharper disable once CppInconsistentNaming
struct ALCdevice;

namespace Mountain::Audio
{
    class Device
    {
    public:
        MOUNTAIN_API static bool_t CheckError(const Device* device = nullptr);

        ATTRIBUTE_NODISCARD
        MOUNTAIN_API explicit Device(std::string&& name);

        MOUNTAIN_API ~Device();

        DELETE_COPY_MOVE_OPERATIONS(Device)

        MOUNTAIN_API void Reopen(const std::string& newName);

        MOUNTAIN_API
        GETTER(const std::string&, Name, m_Name)

    private:
        ALCdevice* m_Handle = nullptr;
        std::string m_Name;

        // AudioContext needs to access the handle of this class
        friend class Context;
    };
}
