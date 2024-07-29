#include "scene/component.hpp"

using namespace Mountain;

const Entity* Component::GetEntity() const
{
    return m_Entity;
}

Entity* Component::GetEntity()
{
    return m_Entity;
}
