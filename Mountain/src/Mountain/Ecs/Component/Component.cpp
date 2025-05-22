module Mountain:Ecs_Component_Component;
import :Ecs_Component_Component;

using namespace Mountain;

const Entity* Component::GetEntity() const
{
    return m_Entity;
}

Entity* Component::GetEntity()
{
    return m_Entity;
}
