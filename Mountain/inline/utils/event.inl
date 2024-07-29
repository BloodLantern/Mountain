#pragma once

#include "utils/utils.hpp"

BEGIN_MOUNTAIN

template <typename... Args>
void Event<Args...>::Invoke(Args... args) const
{
    m_Functions.Iterate([&args...](const StdFunctionT* f) -> void
    {
        (*f)(std::forward<Args>(args)...);
    });
}

template <typename... Args>
void Event<Args...>::operator()(Args... args) const { Invoke(args...); }

template <typename... Args>
void Event<Args...>::Clear()
{
    m_Functions.Clear();
}

template <typename... Args>
Event<Args...>& Event<Args...>::operator+=(StdFunctionT func)
{
    m_Functions.Add(std::forward<StdFunctionT>(func));

    return *this;
}

template <typename ... Args>
Event<Args...>& Event<Args...>::operator-=(const StdFunctionT& func)
{
    for (size_t i = 0; i < m_Functions.GetSize(); i++)
    {
        if (Utils::FunctionAddress(m_Functions[i]) == Utils::FunctionAddress(func))
        {
            m_Functions.RemoveAt(i);
            break;
        }
    }

    return *this;
}

END_MOUNTAIN
