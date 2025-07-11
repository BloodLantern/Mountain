#include "Mountain/Core.hpp"

#include "Mountain/Ecs/Entity.hpp"

#include "Mountain/Ecs/Component/Component.hpp"

using namespace Mountain;

Entity::Entity(const Vector2& position)
    : position(position)
{
}

Entity::~Entity()
{
    for (const Component* const component : m_Components)
        delete component;
}

void Entity::Update()
{
    for (Component* component : m_Components)
        component->Update();
}

void Entity::Render()
{
    for (Component* component : m_Components)
        component->Render();
}

void Entity::RenderDebug()
{
    for (Component* component : m_Components)
        component->DebugRender();
}

void Entity::Added(Scene& scene)
{
    m_Scene = &scene;
    for (Component* component : m_Components)
        component->EntityAdded(scene);
}

void Entity::Removed(Scene& scene)
{
    for (Component* component : m_Components)
        component->EntityRemoved(scene);
    m_Scene = nullptr;
}

void Entity::Awake()
{
    for (Component* component : m_Components)
        component->EntityAwake();
}

void Entity::SceneBegin()
{
    for (Component* component : m_Components)
        component->SceneBegin();
}

void Entity::SceneEnd()
{
    for (Component* component : m_Components)
        component->SceneEnd();
}

void Entity::AddComponent(Component* component)
{
    m_Components.Add(component);
    component->m_Entity = this;
    component->Added();
}

List<Component*>& Entity::GetComponents() { return m_Components; }

const List<Component*>& Entity::GetComponents() const { return m_Components; }

void Entity::RemoveComponent(Component* component)
{
    m_Components.Remove(component);
    component->Removed();
    delete component;
}

const Collider* Entity::GetCollider() const { return m_Collider; }

Collider* Entity::GetCollider() { return m_Collider; }
