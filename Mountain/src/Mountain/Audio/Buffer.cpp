#include "Mountain/Audio/Buffer.hpp"

#include <AL/al.h>

#include "Sound.hpp"
#include "Mountain/Audio/Context.hpp"
#include "Mountain/Resource/AudioTrack.hpp"

using namespace Mountain::Audio;

Buffer::Buffer()
    : m_Context(Sound::GetContext())
{
    m_Context->MakeCurrent();
    alGenBuffers(1, &m_Handle);
}

Buffer::Buffer(const int32_t size)
    : Buffer()
{
    alBufferi(m_Handle, AL_SIZE, size);
}

Buffer::Buffer(const AudioTrack* track)
    : Buffer()
{
    SetData(track);
}

Buffer::~Buffer()
{
    m_Context->MakeCurrent();
    alDeleteBuffers(1, &m_Handle);
}

void Buffer::SetData(const AudioTrack* track)
{
    SetData(track->GetData(), track->GetDataSize(), track->GetChannels(), track->GetBitDepth(), track->GetSampleRate());
}

// ReSharper disable once CppMemberFunctionMayBeConst
void Buffer::SetData(const void* const data, const int32_t length, const uint16_t channels, const uint16_t bitDepth, const int32_t sampleRate)
{
    m_Context->MakeCurrent();
    alBufferData(m_Handle, ToOpenAl(GetFormat(channels, bitDepth)), data, length, sampleRate);
    Context::CheckError();
}

uint32_t Buffer::GetHandle() const
{
    return m_Handle;
}
