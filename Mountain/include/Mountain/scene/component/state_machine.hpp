#pragma once

#include "Mountain/core.hpp"

#include <magic_enum/magic_enum.hpp>

#include "Mountain/scene/component/component.hpp"
#include "Mountain/utils/concepts.hpp"
#include "Mountain/utils/coroutine.hpp"
#include "Mountain/utils/meta_programming.hpp"

BEGIN_MOUNTAIN

struct StateMachineCallbacks
{
    Action update{};
    Action begin{};
    Action end{};
    CoroutineFunction<> coroutine{};
};

template <Concepts::EnumT T>
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
    using Array = std::array<U, magic_enum::enum_count<T>()>;
    
    Array<Action> m_Begins;
    Array<Action> m_Updates;
    Array<Action> m_Ends;
    Array<CoroutineFunction<>> m_Coroutines;

    Coroutine m_CurrentCoroutine;

    T m_State = static_cast<T>(0);
    T m_PreviousState = static_cast<T>(0);
    bool_t m_StateChanged = false;
};

END_MOUNTAIN

#include "Mountain/scene/component/state_machine.inl"
