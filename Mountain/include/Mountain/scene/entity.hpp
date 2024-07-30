#pragma once

#include "Mountain/core.hpp"

#include <Maths/vector2.hpp>

#include "Mountain/collision/collider.hpp"
#include "Mountain/utils/concepts.hpp"
#include "Mountain/utils/list.hpp"

BEGIN_MOUNTAIN

class Entity
{
    List<Component*> m_Components;
    
public:
    Vector2 position;

    MOUNTAIN_API explicit Entity(const Vector2& position);

    MOUNTAIN_API virtual ~Entity();

    DELETE_COPY_MOVE_OPERATIONS(Entity)

    MOUNTAIN_API virtual void Update();

    MOUNTAIN_API virtual void Render();

    MOUNTAIN_API virtual void DebugRender();

    MOUNTAIN_API void AddComponent(Component* component);

    template <Concepts::ComponentT T>
    T* AddComponent();

    template <Concepts::ComponentT T>
    [[nodiscard]]
    T* GetComponent() const;

    [[nodiscard]]
    MOUNTAIN_API decltype(m_Components)& GetComponents();

    [[nodiscard]]
    MOUNTAIN_API const decltype(m_Components)& GetComponents() const;

    MOUNTAIN_API void RemoveComponent(Component* component);

    template <Concepts::ComponentT T>
    void RemoveComponent();

    MOUNTAIN_API const Collider* GetCollider() const;

    MOUNTAIN_API Collider* GetCollider();

    MOUNTAIN_API void SetCollider(Collider* newCollider);

protected:
    Collider* m_Collider = nullptr;
};

END_MOUNTAIN

#include "Mountain/scene/entity.inl"
