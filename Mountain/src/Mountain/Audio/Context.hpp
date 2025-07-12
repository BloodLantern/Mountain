#pragma once

#include "Audio.hpp"
#include "Mountain/Core.hpp"
#include "Mountain/Containers/List.hpp"

// ReSharper disable once CppInconsistentNaming
struct ALCcontext;

namespace Mountain::Audio
{
    class Device;

    class Context
    {
    public:
        ATTRIBUTE_NODISCARD
        MOUNTAIN_API explicit Context(Device& device);

        MOUNTAIN_API ~Context();

        DELETE_COPY_MOVE_OPERATIONS(Context)

        MOUNTAIN_API void MakeCurrent() const;

        MOUNTAIN_API static bool_t CheckError();

    private:
        ALCcontext* m_Handle = nullptr;
        Device* m_Device = nullptr;

        List<int32_t> m_Attributes;
    };
}
