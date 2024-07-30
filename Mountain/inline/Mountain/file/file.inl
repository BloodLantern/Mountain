#pragma once

BEGIN_MOUNTAIN

template <typename T>
const T* File::GetData() const
{
    return reinterpret_cast<const T*>(m_Data);
}

template <typename T>
T* File::GetData()
{
    return reinterpret_cast<T*>(m_Data);
}

END_MOUNTAIN
