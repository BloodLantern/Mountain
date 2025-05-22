export module Mountain:Resource_AudioTrack;

import "Mountain/Core.hpp";

import std;
export import :Core;
export import :Resource_Resource;
export import :Audio_AudioBuffer;

export namespace Mountain
{
    enum class MOUNTAIN_API AudioTrackFormat : uint8_t
    {
        Wavefront,
        OggVorbis,
        Mp3
    };

    class AudioTrack : public Resource
    {
    public:
        /// @brief Allowed extensions for audio files
        MOUNTAIN_API static constexpr std::array FileExtensions
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

        MOUNTAIN_API bool_t SetSourceData(const uint8_t* buffer, int64_t length) override;

        MOUNTAIN_API void Load() override;

        MOUNTAIN_API void Unload() override;

        MOUNTAIN_API void ResetSourceData() override;

        /// @brief Gets the raw data of the texture
        /// @tparam T Type
        /// @return Data
        template <typename T = uint8_t>
        [[nodiscard]]
        const T* GetData() const;

        /// @brief Gets the raw data of the texture
        /// @tparam T Type
        /// @return Data
        template <typename T = uint8_t>
        [[nodiscard]]
        T* GetData();

        [[nodiscard]]
        MOUNTAIN_API int32_t GetDataSize() const;

        [[nodiscard]]
        MOUNTAIN_API uint16_t GetChannels() const;

        [[nodiscard]]
        MOUNTAIN_API int32_t GetSampleRate() const;

        [[nodiscard]]
        MOUNTAIN_API uint16_t GetBitDepth() const;

        [[nodiscard]]
        MOUNTAIN_API const AudioBuffer* GetBuffer() const;

        [[nodiscard]]
        MOUNTAIN_API AudioTrackFormat GetFormat() const;

    private:
        /// @brief The raw, uncompressed audio data.
        uint8_t* m_Data = nullptr;
        /// @brief The size of the m_Data buffer.
        int32_t m_DataSize = 0;
        /// @brief The number of audio channels. This would be 1 for mono, 2 for stereo, and so on.
        uint16_t m_Channels = 0;
        /// @brief Also often called frequency.
        int32_t m_SampleRate = 0;
        /// @brief The number of bits per sample.
        uint16_t m_BitDepth = 0;

        AudioBuffer* m_Buffer = nullptr;

        AudioTrackFormat m_Format;

        MOUNTAIN_API bool_t LoadWavefront(const uint8_t* buffer, int64_t length);
        MOUNTAIN_API int64_t LoadWavefrontFormat(const uint8_t* data);
        MOUNTAIN_API int64_t LoadWavefrontData(const uint8_t* data);

        MOUNTAIN_API bool_t LoadOggVorbis(const uint8_t* buffer, int64_t length);
        MOUNTAIN_API bool_t LoadMp3(const uint8_t* buffer, int64_t length);
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
