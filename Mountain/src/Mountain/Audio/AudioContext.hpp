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
        [[nodiscard]]
        MOUNTAIN_API explicit AudioContext(AudioDevice& device);

        MOUNTAIN_API ~AudioContext();

        DELETE_COPY_MOVE_OPERATIONS(AudioContext)

        MOUNTAIN_API void MakeCurrent() const;

        MOUNTAIN_API static bool_t CheckError();

        [[nodiscard]]
        MOUNTAIN_API int32_t GetMaxSourceCount(AudioSourceType sourceType) const;

        /// @brief Returns the next available source of the given type.
        [[nodiscard]]
        MOUNTAIN_API uint32_t GetSource(AudioSourceType type = AudioSourceType::Mono);

    private:
        ALCcontext* m_Handle = nullptr;
        AudioDevice* m_Device = nullptr;

        List<int32_t> m_Attributes;

        List<uint32_t> m_SourcesMono;
        List<uint32_t> m_SourcesStereo;
    };
}
