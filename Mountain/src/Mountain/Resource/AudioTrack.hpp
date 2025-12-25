#pragma once

#include "Mountain/Core.hpp"
#include "Mountain/Audio/AudioBuffer.hpp"
#include "Mountain/Resource/Resource.hpp"

namespace Mountain
{
    enum class AudioTrackFormat : u8
    {
        Wavefront,
        OggVorbis,
        Mp3
    };

    class AudioTrack : public Resource
    {
    public:
        /// @brief Allowed extensions for audio files
        MOUNTAIN_API static constexpr Array FileExtensions
        {
            ".wav",
            ".wave",
            ".mp3",
            ".ogg"
        };

        // Same constructor from base class
        using Resource::Resource;

        MOUNTAIN_API ~AudioTrack() override;

        DELETE_COPY_MOVE_OPERATIONS(AudioTrack)

        // We keep both function overloads and only override one
        using Resource::SetSourceData;

        MOUNTAIN_API bool SetSourceData(const u8* buffer, s64 length) override;

        MOUNTAIN_API void Load() override;

        MOUNTAIN_API void Unload() override;

        MOUNTAIN_API void ResetSourceData() override;

        /// @brief Gets the raw data of the texture
        /// @tparam T Type
        /// @return Data
        template <typename T = u8>
        ATTRIBUTE_NODISCARD
        const T* GetData() const;

        /// @brief Gets the raw data of the texture
        /// @tparam T Type
        /// @return Data
        template <typename T = u8>
        ATTRIBUTE_NODISCARD
        T* GetData();

        ATTRIBUTE_NODISCARD
        MOUNTAIN_API s32 GetDataSize() const;

        ATTRIBUTE_NODISCARD
        MOUNTAIN_API u16 GetChannels() const;

        ATTRIBUTE_NODISCARD
        MOUNTAIN_API s32 GetSampleRate() const;

        ATTRIBUTE_NODISCARD
        MOUNTAIN_API u16 GetBitDepth() const;

        ATTRIBUTE_NODISCARD
        MOUNTAIN_API const AudioBuffer* GetBuffer() const;

        ATTRIBUTE_NODISCARD
        MOUNTAIN_API AudioTrackFormat GetFormat() const;

    private:
        /// @brief The raw, uncompressed audio data.
        u8* m_Data = nullptr;
        /// @brief The size of the m_Data buffer.
        s32 m_DataSize = 0;
        /// @brief The number of audio channels. This would be 1 for mono, 2 for stereo, and so on.
        u16 m_Channels = 0;
        /// @brief Also often called frequency.
        s32 m_SampleRate = 0;
        /// @brief The number of bits per sample.
        u16 m_BitDepth = 0;

        AudioBuffer* m_Buffer = nullptr;

        AudioTrackFormat m_Format;

        MOUNTAIN_API bool LoadWavefront(const u8* buffer, s64 length);
        MOUNTAIN_API s64 LoadWavefrontFormat(const u8* data);
        MOUNTAIN_API s64 LoadWavefrontData(const u8* data);

        MOUNTAIN_API bool LoadOggVorbis(const u8* buffer, s64 length);
        MOUNTAIN_API bool LoadMp3(const u8* buffer, s64 length);
    };
}

// Start of AudioTrack.inl

namespace Mountain
{
    template <typename T>
    const T* AudioTrack::GetData() const { return reinterpret_cast<const T*>(m_Data); }

    template <typename T>
    T* AudioTrack::GetData() { return reinterpret_cast<T*>(m_Data); }
}
