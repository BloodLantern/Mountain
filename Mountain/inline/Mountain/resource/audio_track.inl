#pragma once

namespace Mountain
{
    template <typename T>
    const T* AudioTrack::GetData() const { return reinterpret_cast<const T*>(m_Data); }

    template <typename T>
    T* AudioTrack::GetData() { return reinterpret_cast<T*>(m_Data); }
}
