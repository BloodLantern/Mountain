#include "Mountain/Resource/AudioTrack.hpp"

#include <minimp3.h>
#include <minimp3_ex.h>
#include <stb_vorbis.h>

#include "Mountain/Audio/Audio.hpp"
#include "Mountain/Audio/Sound.hpp"
#include "Mountain/Utils/Logger.hpp"

using namespace Mountain;

AudioTrack::~AudioTrack()
{
    AudioTrack::ResetSourceData();
}

bool_t AudioTrack::SetSourceData(const uint8_t* const buffer, const int64_t length)
{
    const char_t* const type = reinterpret_cast<const char_t*>(buffer);

    if (std::strncmp(type, "RIFF", 4) == 0)
        return LoadWavefront(buffer, length);
    if (std::strncmp(type, "Ogg", 3) == 0)
        return LoadOggVorbis(buffer, length);
    if (std::strncmp(type, "ID3", 3) == 0)
        return LoadMp3(buffer, length);

    Logger::LogError("Unsupported file format {}", std::string_view(type, 4));
    return false;
}

void AudioTrack::Load()
{
    m_Buffer = new Audio::Buffer(this);
    Sound::RegisterBuffer(m_Buffer);

    m_Loaded = true;
}

void AudioTrack::Unload()
{
    Sound::UnregisterBuffer(m_Buffer);
    delete m_Buffer;
    m_Buffer = nullptr;

    m_Loaded = false;
}

void AudioTrack::ResetSourceData()
{
    if (!m_SourceDataSet)
        return;

    switch (m_Format)
    {
        case AudioTrackFormat::Wavefront:
            // The data was new-ed by the File wrapper, so we don't need to delete it here
            m_Data = nullptr;
            break;

        case AudioTrackFormat::OggVorbis:
        case AudioTrackFormat::Mp3:
            // The buffer was malloc-ed from the third-party library
            free(const_cast<uint8_t*>(m_Data));
            break;
    }

    m_DataSize = 0;
    m_Channels = 0;
    m_SampleRate = 0;
    m_BitDepth = 0;

    m_SourceDataSet = false;
}

int32_t AudioTrack::GetDataSize() const { return m_DataSize; }

uint16_t AudioTrack::GetChannels() const { return m_Channels; }

int32_t AudioTrack::GetSampleRate() const { return m_SampleRate; }

uint16_t AudioTrack::GetBitDepth() const { return m_BitDepth; }

const Audio::Buffer* AudioTrack::GetBuffer() const { return m_Buffer; }

AudioTrackFormat AudioTrack::GetFormat() const { return m_Format; }

bool_t AudioTrack::LoadWavefront(const uint8_t* const buffer, const int64_t length)
{
    m_Format = AudioTrackFormat::Wavefront;

    int64_t offset = 8; // 4 because 'RIFF' has already been checked and 4 because of the file size that we don't need
    const char_t* const str = reinterpret_cast<const char_t*>(buffer);

    if (std::strncmp(str + offset, "WAVE", 4) != 0)
        return false;
    offset += 4;

    while (offset < length)
    {
        if (strncmp(str + offset, "fmt ", 4) == 0)
            offset += LoadWavefrontFormat(buffer + offset);
        else if (strncmp(str + offset, "data", 4) == 0)
            offset += LoadWavefrontData(buffer + offset);
        else
            offset++;
    }

    m_SourceDataSet = true;
    return true;
}

int64_t AudioTrack::LoadWavefrontFormat(const uint8_t* const data)
{
    int64_t offset = 8; // 4 because 'fmt ' has already been checked and 4 because of the chunk size that we don't need

    offset += sizeof(uint16_t); // Skip the format type - we don't care about it

    m_Channels = *reinterpret_cast<const decltype(m_Channels)*>(data + offset);
    offset += sizeof(m_Channels);

    m_SampleRate = *reinterpret_cast<const decltype(m_SampleRate)*>(data + offset);
    offset += sizeof(m_SampleRate);

    offset += sizeof(uint32_t); // Skip whatever is this value

    offset += sizeof(uint16_t); // As well as this one

    m_BitDepth = *reinterpret_cast<const decltype(m_BitDepth)*>(data + offset);
    offset += sizeof(m_BitDepth);

    return offset;
}

int64_t AudioTrack::LoadWavefrontData(const uint8_t* const data)
{
    const int32_t length = *reinterpret_cast<const int32_t*>(data + 4);
    m_Data = const_cast<uint8_t*>(data + 8);
    m_DataSize = length;

    return length + 8;
}

bool_t AudioTrack::LoadOggVorbis(const uint8_t* buffer, const int64_t length)
{
    m_Format = AudioTrackFormat::OggVorbis;

    int channels;
    const int decodedSamples = stb_vorbis_decode_memory(
        buffer,
        static_cast<int>(length),
        &channels,
        &m_SampleRate,
        reinterpret_cast<short**>(&m_Data)
    );

    if (decodedSamples == -1)
        return false;

    m_Channels = static_cast<uint16_t>(channels);
    m_DataSize = static_cast<int32_t>(decodedSamples * sizeof(short) * channels);
    m_BitDepth = 16;

    m_SourceDataSet = true;
    return true;
}

bool_t AudioTrack::LoadMp3(const uint8_t* buffer, const int64_t length)
{
    m_Format = AudioTrackFormat::Mp3;

    mp3dec_t mp3;
    mp3dec_file_info_t fileInfo;
    if (mp3dec_load_buf(&mp3, buffer, length, &fileInfo, nullptr, nullptr))
        return false;

    m_Data = reinterpret_cast<uint8_t*>(fileInfo.buffer);
    m_DataSize = static_cast<int32_t>(fileInfo.samples * sizeof(mp3d_sample_t));
    m_Channels = static_cast<uint16_t>(fileInfo.channels);
    m_SampleRate = fileInfo.hz;
    m_BitDepth = 16;

    m_SourceDataSet = true;
    return true;
}
