#include "Mountain/scene/entity.hpp"

#include "Mountain/scene/component.hpp"

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

void Entity::DebugRender()
{
    for (Component* component : m_Components)
        component->DebugRender();
}

void Entity::AddComponent(Component* component)
{
    m_Components.Add(component);
    component->m_Entity = this;
    component->Added();
}

decltype(Entity::m_Components)& Entity::GetComponents() { return m_Components; }

const decltype(Entity::m_Components)& Entity::GetComponents() const { return m_Components; }

void Entity::RemoveComponent(Component* component)
{
    m_Components.Remove(component);
    component->Removed();
    delete component;
}

const Collider* Entity::GetCollider() const { return m_Collider; }

Collider* Entity::GetCollider() { return m_Collider; }

void Entity::SetCollider(Collider* newCollider)
{
    m_Collider = newCollider;
    m_Collider->m_Entity = this;
}
