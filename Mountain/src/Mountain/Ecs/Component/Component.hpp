#pragma once

#include "Mountain/Core.hpp"

namespace Mountain
{
    class Scene;
    class Entity;

    /// @brief Represents a behavior that can be attached to an Entity.
    class MOUNTAIN_API Component
    {
        friend class Entity;

    public:
        Component() = default;
        virtual ~Component() = default;

        DEFAULT_VIRTUAL_COPY_MOVE_OPERATIONS(Component)

        /// @brief Called when the component is added to an Entity.
        virtual void Added();

        /// @brief Called when the component is removed from an Entity.
        virtual void Removed();

        /// @brief Updates the component.
        virtual void Update();

        /// @brief Renders the component.
        virtual void Render();

        virtual void DebugRender();

        /// @brief Called when the component's entity is added to a Scene.
        virtual void EntityAdded(Scene& scene);

        /// @brief Called when the component's entity is removed from a Scene.
        virtual void EntityRemoved(Scene& scene);

        /// @brief Called when the component's entity is awake in a Scene.
        virtual void EntityAwake();

        virtual void SceneBegin();

        virtual void SceneEnd();

        /// @brief Get the Entity on which this Component is attached
        [[nodiscard]]
        const Entity* GetEntity() const;

        /// @brief Get the Entity on which this Component is attached
        Entity* GetEntity();

    protected:
        /// @brief Entity bound to the component
        Entity* m_Entity = nullptr;
    };
}
