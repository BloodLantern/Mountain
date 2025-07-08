#pragma once

#include "Mountain/Core.hpp"

#include <magic_enum/magic_enum.hpp>

#include "Mountain/Containers/FunctionTypes.hpp"
#include "Mountain/Ecs/Component/Component.hpp"
#include "Mountain/Utils/Coroutine.hpp"
#include "Mountain/Utils/MetaProgramming.hpp"

namespace Mountain
{
    struct StateMachineCallbacks
    {
        Action<> update{};
        Action<> begin{};
        Action<> end{};
        CoroutineFunction<> coroutine{};
    };

    template <Concepts::Enum T>
    class StateMachine : public Component
    {
    public:
        using Type = T;
        using UnderlyingType = Meta::UnderlyingEnumType<T>;

        bool_t locked = false;

        using Component::operator=;

        StateMachine() = default;
        ~StateMachine() override;

        // Because of the Coroutine, we cannot copy the StateMachine
        // Delete copy operations
        StateMachine(const StateMachine&) = delete;
        StateMachine& operator=(const StateMachine&) = delete;

        // Define move operations
        [[nodiscard]]
        StateMachine(StateMachine&& other) noexcept;
        StateMachine& operator=(StateMachine&& other) noexcept;

        /// @brief Set the callbacks for when a state begins, updates and ends.
        void SetCallbacks(T state, StateMachineCallbacks&& callbacks);  // NOLINT(cppcoreguidelines-rvalue-reference-param-not-moved)

        void Update() override;

        /// @brief Get the current state
        [[nodiscard]]
        T GetState() const;
        /// @brief Get the current state as an integral type
        [[nodiscard]]
        UnderlyingType GetStateIntegral() const;
        /// @brief Set the new state if @c locked is not set
        void SetState(T newState);
        /// @brief Force the new state
        void ForceState(T newState);
        /// @brief Set the new state if @c locked is not set
        ATTRIBUTE_HAS_SIDE_EFFECTS
        // ReSharper disable once CppEnforceOverridingFunctionStyle
        StateMachine& operator=(T newState);

        /// @brief Get the previous state
        [[nodiscard]]
        T GetPreviousState() const;
        /// @brief Get the previous state as an integral type
        [[nodiscard]]
        UnderlyingType GetPreviousStateIntegral() const;

        /// @brief Get whether the current state changed since the last update
        [[nodiscard]]
        bool_t GetStateChanged() const;

        [[nodiscard]]
        // ReSharper disable once CppNonExplicitConversionOperator
        operator T();

    private:
        template <typename U>
        using FunctionArray = Array<U, magic_enum::enum_count<T>()>;

        FunctionArray<Action<>> m_Begins;
        FunctionArray<Action<>> m_Updates;
        FunctionArray<Action<>> m_Ends;
        FunctionArray<CoroutineFunction<>> m_Coroutines;

        Coroutine m_CurrentCoroutine;

        T m_State = static_cast<T>(0);
        T m_PreviousState = static_cast<T>(0);
        bool_t m_StateChanged = false;
    };
}

// Start of StateMachine.inl

#include "Mountain/Utils/utils.hpp"

namespace Mountain
{
    template <Concepts::Enum T>
    StateMachine<T>::~StateMachine() { m_CurrentCoroutine.DestroySafe(); }

    template <Concepts::Enum T>
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

    template <Concepts::Enum T>
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

    template <Concepts::Enum T>
    void StateMachine<T>::SetCallbacks(T state, StateMachineCallbacks&& callbacks)  // NOLINT(cppcoreguidelines-rvalue-reference-param-not-moved)
    {
        const UnderlyingType index = magic_enum::enum_integer(state);

        m_Begins[index] = std::move(callbacks.begin);
        m_Updates[index] = std::move(callbacks.update);
        m_Ends[index] = std::move(callbacks.end);
        m_Coroutines[index] = std::move(callbacks.coroutine);
    }

    template <Concepts::Enum T>
    void StateMachine<T>::Update()
    {
        if (m_StateChanged)
        {
            const UnderlyingType stateIntegral = GetStateIntegral();

            Utils::CallSafe(m_Begins[stateIntegral]);

            m_CurrentCoroutine = Utils::CallSafe(m_Coroutines[stateIntegral]);

            m_StateChanged = false;
        }

        Utils::CallSafe(m_Updates[GetStateIntegral()]);

        if (m_StateChanged)
            Utils::CallSafe(m_Ends[GetPreviousStateIntegral()]);

        if (m_CurrentCoroutine.Valid())
        {
            m_CurrentCoroutine.Resume();

            if (m_CurrentCoroutine.Finished())
                m_CurrentCoroutine.Destroy();
        }
    }

    template <Concepts::Enum T>
    T StateMachine<T>::GetState() const { return m_State; }

    template <Concepts::Enum T>
    typename StateMachine<T>::UnderlyingType StateMachine<T>::GetStateIntegral() const { return magic_enum::enum_integer(m_State); }

    template <Concepts::Enum T>
    void StateMachine<T>::SetState(T newState)
    {
        if (locked)
            return;

        ForceState(newState);
    }

    template <Concepts::Enum T>
    void StateMachine<T>::ForceState(T newState)
    {
        m_PreviousState = m_State;
        m_StateChanged = true;
        m_State = newState;
    }

    template <Concepts::Enum T>
    StateMachine<T>& StateMachine<T>::operator=(T newState)
    {
        SetState(newState);

        return *this;
    }

    template <Concepts::Enum T>
    T StateMachine<T>::GetPreviousState() const { return m_PreviousState; }

    template <Concepts::Enum T>
    typename StateMachine<T>::UnderlyingType StateMachine<T>::GetPreviousStateIntegral() const { return magic_enum::enum_integer(m_PreviousState); }

    template <Concepts::Enum T>
    bool_t StateMachine<T>::GetStateChanged() const { return m_StateChanged; }

    template <Concepts::Enum T>
    StateMachine<T>::operator T() { return m_State; }
}
