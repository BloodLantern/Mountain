#pragma once

#include "Mountain/utils/utils.hpp"

BEGIN_MOUNTAIN

template <Concepts::EnumT T>
StateMachine<T>::~StateMachine() { m_CurrentCoroutine.DestroySafe(); }

template <Concepts::EnumT T>
StateMachine<T>::StateMachine(StateMachine&& other) noexcept
{
    m_Begins = std::move(other.m_Begins);
    m_Updates = std::move(other.m_Updates);
    m_Ends = std::move(other.m_Ends);
    m_Coroutines = std::move(other.m_Coroutines);
    
    m_CurrentCoroutine = std::move(other.m_CurrentCoroutine);
    
    m_State = other.m_State;
    m_PreviousState = other.m_PreviousState;
    m_StateChanged = other.m_StateChanged;
}

template <Concepts::EnumT T>
StateMachine<T>& StateMachine<T>::operator=(StateMachine&& other) noexcept
{
    m_Begins = std::move(other.m_Begins);
    m_Updates = std::move(other.m_Updates);
    m_Ends = std::move(other.m_Ends);
    m_Coroutines = std::move(other.m_Coroutines);
    
    m_CurrentCoroutine = std::move(other.m_CurrentCoroutine);
    
    m_State = other.m_State;
    m_PreviousState = other.m_PreviousState;
    m_StateChanged = other.m_StateChanged;

    return *this;
}

template <Concepts::EnumT T>
void StateMachine<T>::SetCallbacks(T state, StateMachineCallbacks&& callbacks)  // NOLINT(cppcoreguidelines-rvalue-reference-param-not-moved)
{
    const UnderlyingType index = magic_enum::enum_integer(state);
    
    m_Begins[index] = std::move(callbacks.begin);
    m_Updates[index] = std::move(callbacks.update);
    m_Ends[index] = std::move(callbacks.end);
    m_Coroutines[index] = std::move(callbacks.coroutine);
}

template <Concepts::EnumT T>
void StateMachine<T>::Update()
{
    Utils::CallSafe(m_Updates[GetStateIntegral()]);

    if (m_StateChanged)
    {
        const UnderlyingType stateIntegral = GetStateIntegral();

        Utils::CallSafe(m_Ends[GetPreviousStateIntegral()]);
        Utils::CallSafe(m_Begins[stateIntegral]);

        m_CurrentCoroutine = Utils::CallSafe(m_Coroutines[stateIntegral]);
        
        m_StateChanged = false;
    }
    
    if (m_CurrentCoroutine.Valid())
    {
        m_CurrentCoroutine.Resume();
        
        if (m_CurrentCoroutine.Finished())
            m_CurrentCoroutine.Destroy();
    }
}

template <Concepts::EnumT T>
T StateMachine<T>::GetState() const { return m_State; }

template <Concepts::EnumT T>
typename StateMachine<T>::UnderlyingType StateMachine<T>::GetStateIntegral() const { return magic_enum::enum_integer(m_State); }

template <Concepts::EnumT T>
void StateMachine<T>::SetState(T newState)
{
    if (locked)
        return;
    
    ForceState(newState);
}

template <Concepts::EnumT T>
void StateMachine<T>::ForceState(T newState)
{
    m_PreviousState = m_State;
    m_StateChanged = true;
    m_State = newState;
}

template <Concepts::EnumT T>
StateMachine<T>& StateMachine<T>::operator=(T newState)
{
    SetState(newState);
    
    return *this;
}

template <Concepts::EnumT T>
T StateMachine<T>::GetPreviousState() const { return m_PreviousState; }

template <Concepts::EnumT T>
typename StateMachine<T>::UnderlyingType StateMachine<T>::GetPreviousStateIntegral() const { return magic_enum::enum_integer(m_PreviousState); }

template <Concepts::EnumT T>
bool_t StateMachine<T>::GetStateChanged() const { return m_StateChanged; }

template <Concepts::EnumT T>
StateMachine<T>::operator T() { return m_State; }

END_MOUNTAIN
