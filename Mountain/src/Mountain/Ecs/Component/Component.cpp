#include "Mountain/Core.hpp"

#include "Mountain/Ecs/Component/Component.hpp"

using namespace Mountain;

void Component::Added()
{
}

void Component::Removed()
{
}

void Component::EntityAdded(Scene&)
{
}

void Component::EntityRemoved(Scene&)
{
}

void Component::EntityAwake()
{
}

void Component::SceneBegin()
{
}

void Component::SceneEnd()
{
}

void Component::Update()
{
}

void Component::Render()
{
}

void Component::DebugRender()
{
}

const Entity* Component::GetEntity() const
{
    return m_Entity;
}

Entity* Component::GetEntity()
{
    return m_Entity;
}
