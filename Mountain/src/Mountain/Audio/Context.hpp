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

        ATTRIBUTE_NODISCARD
        MOUNTAIN_API int32_t GetMaxSourceCount(SourceType sourceType) const;

        /// @brief Returns the next available source of the given type.
        ATTRIBUTE_NODISCARD
        MOUNTAIN_API uint32_t GetSource(SourceType type = SourceType::Mono);

    private:
        ALCcontext* m_Handle = nullptr;
        Device* m_Device = nullptr;

        List<int32_t> m_Attributes;

        List<uint32_t> m_SourcesMono;
        List<uint32_t> m_SourcesStereo;
    };
}
