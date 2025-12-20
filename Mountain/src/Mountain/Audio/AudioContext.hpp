#pragma once

#include "Mountain/Core.hpp"
#include "Mountain/Containers/List.hpp"

// ReSharper disable once CppInconsistentNaming
struct ALCcontext;

namespace Mountain
{
    class AudioDevice;

    enum class AudioSourceType
    {
        Mono,
        Stereo
    };

    class AudioContext
    {
    public:
        ATTRIBUTE_NODISCARD
        MOUNTAIN_API explicit AudioContext(AudioDevice& device);

        MOUNTAIN_API ~AudioContext();

        DELETE_COPY_MOVE_OPERATIONS(AudioContext)

        MOUNTAIN_API void MakeCurrent() const;

        MOUNTAIN_API static bool CheckError();

        ATTRIBUTE_NODISCARD
        MOUNTAIN_API s32 GetMaxSourceCount(AudioSourceType sourceType) const;

        /// @brief Returns the next available source of the given type.
        ATTRIBUTE_NODISCARD
        MOUNTAIN_API u32 GetSource(AudioSourceType type = AudioSourceType::Mono);

    private:
        ALCcontext* m_Handle = nullptr;
        AudioDevice* m_Device = nullptr;

        List<s32> m_Attributes;

        List<u32> m_SourcesMono;
        List<u32> m_SourcesStereo;
    };
}
