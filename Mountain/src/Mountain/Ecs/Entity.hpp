#pragma once

#include "Mountain/Core.hpp"

#include <Math/vector2.hpp>

#include "Mountain/Collision/Collider.hpp"
#include "Mountain/Containers/List.hpp"
#include "Mountain/Utils/MetaProgramming.hpp"

namespace Mountain
{
    class Scene;

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

        MOUNTAIN_API virtual void Added(Scene& scene);

        MOUNTAIN_API virtual void Removed(Scene& scene);

        /// @brief Called before the first update after being added to a Scene.
        MOUNTAIN_API virtual void Awake();

        MOUNTAIN_API virtual void SceneBegin();

        MOUNTAIN_API virtual void SceneEnd();

        MOUNTAIN_API void AddComponent(Component* component);

        template <Concepts::Component T, typename... Args>
        T* AddComponent(Args&&... args);

        template <Concepts::Component T>
        ATTRIBUTE_NODISCARD
        T* GetComponent() const;

        ATTRIBUTE_NODISCARD
        MOUNTAIN_API List<Component*>& GetComponents();

        ATTRIBUTE_NODISCARD
        MOUNTAIN_API const List<Component*>& GetComponents() const;

        MOUNTAIN_API void RemoveComponent(Component* component);

        template <Concepts::Component T>
        void RemoveComponent();

        ATTRIBUTE_NODISCARD
        MOUNTAIN_API const Collider* GetCollider() const;

        MOUNTAIN_API Collider* GetCollider();

        GETTER(float_t, Depth, m_Depth)

        GETTER(Scene*, Scene, m_Scene)

    protected:
        Collider* m_Collider = nullptr;

        /// @brief The rendering depth of the Entity. The higher the depth, the earlier it will get rendered.
        float_t m_Depth = 0.f;

    private:
        List<Component*> m_Components;

        Scene* m_Scene = nullptr;
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
        for (auto& component : m_Components)
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
