#pragma once

#include "Mountain/core.hpp"

#include <Maths/vector2.hpp>

#include "Mountain/collision/collider.hpp"
#include "Mountain/utils/concepts.hpp"
#include "Mountain/utils/list.hpp"

namespace Mountain
{
    class Entity
    {
    public:
        Vector2 position;

        MOUNTAIN_API Entity() = default;

        MOUNTAIN_API explicit Entity(const Vector2& position);

        MOUNTAIN_API virtual ~Entity();

        DEFAULT_COPY_MOVE_OPERATIONS(Entity)

        MOUNTAIN_API virtual void Update();

        MOUNTAIN_API virtual void Render();

        MOUNTAIN_API virtual void RenderDebug();

        MOUNTAIN_API void AddComponent(Component* component);

        template <Concepts::ComponentT T, typename... Args>
        T* AddComponent(Args&&... args);

        template <Concepts::ComponentT T>
        [[nodiscard]]
        T* GetComponent() const;

        [[nodiscard]]
        MOUNTAIN_API List<Component*>& GetComponents();

        [[nodiscard]]
        MOUNTAIN_API const List<Component*>& GetComponents() const;

        MOUNTAIN_API void RemoveComponent(Component* component);

        template <Concepts::ComponentT T>
        void RemoveComponent();

        MOUNTAIN_API const Collider* GetCollider() const;

        MOUNTAIN_API Collider* GetCollider();

    protected:
        Collider* m_Collider = nullptr;

    private:
        List<Component*> m_Components;
    };
}

#include "Mountain/scene/entity.inl"
