#include "Mountain/PrecompiledHeader.hpp"

#include "Mountain/Ecs/EntityList.hpp"

#include "Mountain/Ecs/Entity.hpp"

using namespace Mountain;

namespace
{
    const Comparer<Entity*> EntityDepthComparer = [](const Entity* lhs, const Entity* rhs) { return lhs->GetDepth() > rhs->GetDepth(); };
}

void EntityList::UpdateLists()
{
    if (!m_ToAdd.IsEmpty())
    {
        for (Entity* entity : m_ToAdd)
        {
            if (m_Entities.Contains(entity))
                continue;

            m_Entities.Add(entity);

            if (m_Scene)
                entity->Added(*m_Scene);
        }

        m_Unsorted = true;
    }

    if (!m_ToRemove.IsEmpty())
    {
        for (Entity* entity : m_ToRemove)
        {
            if (!m_Entities.Contains(entity))
                continue;

            m_Entities.Remove(entity);

            if (m_Scene)
                entity->Removed(*m_Scene);
        }

        m_ToRemove.Clear();
    }

    if (m_Unsorted)
    {
        m_Unsorted = false;
        m_Entities.Sort(EntityDepthComparer);
    }

    if (m_ToAdd.IsEmpty())
        return;

    m_ToAdd.ForEach([](Entity* entity) { entity->Awake(); });
    m_ToAdd.Clear();
}

void EntityList::AddNow(Entity* entity)
{
    m_Entities.Add(entity);
    m_Unsorted = true;
}

void EntityList::AddNextFrame(Entity* entity)
{
    m_ToAdd.Add(entity);
}

void EntityList::RemoveNow(Entity* entity)
{
    m_Entities.Remove(entity);
}

void EntityList::RemoveNextFrame(Entity* entity)
{
    m_ToRemove.Add(entity);
}

void EntityList::MarkUnsorted()
{
    m_Unsorted = true;
}

void EntityList::Clear()
{
    m_Entities.Clear();
}
