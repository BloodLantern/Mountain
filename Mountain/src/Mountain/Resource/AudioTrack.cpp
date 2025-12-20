#include "Mountain/PrecompiledHeader.hpp"

#include "Mountain/Resource/AudioTrack.hpp"

#include <stb_vorbis.h>
#include <minimp3/minimp3.h>
#include <minimp3/minimp3_ex.h>

#include "Mountain/Audio/Audio.hpp"
#include "Mountain/Utils/Logger.hpp"

using namespace Mountain;

AudioTrack::~AudioTrack()
{
    AudioTrack::ResetSourceData();
}

bool AudioTrack::SetSourceData(const u8* const buffer, const s64 length)
{
    const c8* const type = reinterpret_cast<const c8*>(buffer);

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
    m_Buffer = new AudioBuffer(this);
    Audio::RegisterBuffer(m_Buffer);

    m_Loaded = true;
}

void AudioTrack::Unload()
{
    Audio::UnregisterBuffer(m_Buffer);
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
            free(const_cast<u8*>(m_Data));
            break;
    }

    m_DataSize = 0;
    m_Channels = 0;
    m_SampleRate = 0;
    m_BitDepth = 0;

    m_SourceDataSet = false;
}

s32 AudioTrack::GetDataSize() const { return m_DataSize; }

u16 AudioTrack::GetChannels() const { return m_Channels; }

s32 AudioTrack::GetSampleRate() const { return m_SampleRate; }

u16 AudioTrack::GetBitDepth() const { return m_BitDepth; }

const AudioBuffer* AudioTrack::GetBuffer() const { return m_Buffer; }

AudioTrackFormat AudioTrack::GetFormat() const { return m_Format; }

bool AudioTrack::LoadWavefront(const u8* const buffer, const s64 length)
{
    m_Format = AudioTrackFormat::Wavefront;

    s64 offset = 8; // 4 because 'RIFF' has already been checked and 4 because of the file size that we don't need
    const c8* const str = reinterpret_cast<const c8*>(buffer);

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

s64 AudioTrack::LoadWavefrontFormat(const u8* const data)
{
    s64 offset = 8; // 4 because 'fmt ' has already been checked and 4 because of the chunk size that we don't need

    offset += sizeof(u16); // Skip the format type - we don't care about it

    m_Channels = *reinterpret_cast<const decltype(m_Channels)*>(data + offset);
    offset += sizeof(m_Channels);

    m_SampleRate = *reinterpret_cast<const decltype(m_SampleRate)*>(data + offset);
    offset += sizeof(m_SampleRate);

    offset += sizeof(u32); // Skip whatever is this value

    offset += sizeof(u16); // As well as this one

    m_BitDepth = *reinterpret_cast<const decltype(m_BitDepth)*>(data + offset);
    offset += sizeof(m_BitDepth);

    return offset;
}

s64 AudioTrack::LoadWavefrontData(const u8* const data)
{
    const s32 length = *reinterpret_cast<const s32*>(data + 4);
    m_Data = const_cast<u8*>(data + 8);
    m_DataSize = length;

    return length + 8;
}

bool AudioTrack::LoadOggVorbis(const u8* buffer, const s64 length)
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

    m_Channels = static_cast<u16>(channels);
    m_DataSize = static_cast<s32>(decodedSamples * sizeof(short) * channels);
    m_BitDepth = 16;

    m_SourceDataSet = true;
    return true;
}

bool AudioTrack::LoadMp3(const u8* buffer, const s64 length)
{
    m_Format = AudioTrackFormat::Mp3;

    mp3dec_t mp3;
    mp3dec_file_info_t fileInfo;
    if (mp3dec_load_buf(&mp3, buffer, length, &fileInfo, nullptr, nullptr))
        return false;

    m_Data = reinterpret_cast<u8*>(fileInfo.buffer);
    m_DataSize = static_cast<s32>(fileInfo.samples * sizeof(mp3d_sample_t));
    m_Channels = static_cast<u16>(fileInfo.channels);
    m_SampleRate = fileInfo.hz;
    m_BitDepth = 16;

    m_SourceDataSet = true;
    return true;
}
