#pragma once

BEGIN_MOUNTAIN

template <Concepts::ComponentT T>
T* Entity::AddComponent()
{
    T* t = new T;
    AddComponent(t);
    return t;
}

template <Concepts::ComponentT T>
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

template <Concepts::ComponentT T>
void Entity::RemoveComponent()
{
    for (decltype(m_Components)::ConstIterator it = m_Components.CBegin(); it != m_Components.CEnd(); it++)
    {
        const T* const t = dynamic_cast<T*>(*it);
        
        if (t)
        {
            m_Components.RemoveAt(it);
            return;
        }
    }
}

END_MOUNTAIN
