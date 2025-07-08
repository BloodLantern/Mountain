#pragma once

#include "Mountain/Core.hpp"

#include <Math/vector2.hpp>

#include "Mountain/Collision/Collider.hpp"
#include "Mountain/Containers/List.hpp"
#include "Mountain/Utils/MetaProgramming.hpp"

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

        template <Concepts::Component T, typename... Args>
        T* AddComponent(Args&&... args);

        template <Concepts::Component T>
        [[nodiscard]]
        T* GetComponent() const;

        [[nodiscard]]
        MOUNTAIN_API List<Component*>& GetComponents();

        [[nodiscard]]
        MOUNTAIN_API const List<Component*>& GetComponents() const;

        MOUNTAIN_API void RemoveComponent(Component* component);

        template <Concepts::Component T>
        void RemoveComponent();

        MOUNTAIN_API const Collider* GetCollider() const;

        MOUNTAIN_API Collider* GetCollider();

    protected:
        Collider* m_Collider = nullptr;

    private:
        List<Component*> m_Components;
    };
}

// Start of Entity.inl

namespace Mountain
{
    template <Concepts::Component T, typename... Args>
    T* Entity::AddComponent(Args&&... args)
    {
        T* t = new T(std::forward<Args>(args)...);
        AddComponent(t);
        return t;
    }

    template <Concepts::Component T>
    T* Entity::GetComponent() const
    {
        for (auto&& component : m_Components)
        {
            T* t = dynamic_cast<T*>(component);

            if (t)
                return t;
        }

        return nullptr;
    }

    template <Concepts::Component T>
    void Entity::RemoveComponent()
    {
        for (decltype(m_Components)::Iterator it = m_Components.begin(); it != m_Components.end(); it++)
        {
            const T* const t = dynamic_cast<T*>(*it);

            if (t)
            {
                m_Components.RemoveAt(it);
                return;
            }
        }
    }
}
