#pragma once

#include "core.hpp"

BEGIN_MOUNTAIN

class Entity;

/// @brief Represents a behavior that can be attached to an Entity.
class MOUNTAIN_API Component
{
    friend class Entity;
    
public:
    Component() = default;
    virtual ~Component() = default;

    DEFAULT_COPY_MOVE_OPERATIONS(Component)

    /// @brief Called when the component is added to an Entity
    virtual void Added() {}

    /// @brief Called when the component is removed from an Entity
    virtual void Removed() {}

    /// @brief Updates the component
    virtual void Update() {}

    /// @brief Renders the component
    virtual void Render() {}

    virtual void DebugRender() {}

    /// @brief Get the Entity on which this Component is attached
    [[nodiscard]]
    const Entity* GetEntity() const;
    
    /// @brief Get the Entity on which this Component is attached
    Entity* GetEntity();

protected:
    /// @brief Entity bound to the component
    Entity* m_Entity = nullptr;
};

END_MOUNTAIN
