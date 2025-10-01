#pragma once

#include "Mountain/Core.hpp"
#include "Mountain/Containers/EnumerableExt.hpp"
#include "Mountain/Containers/List.hpp"

namespace Mountain
{
    class Scene;

    template <Concepts::Entity EntityT>
    class EntityList
    {
        /// @brief The actual list of entities. They are sorted by depth in decreasing order, i.e., higher depth first.
        List<EntityT*> m_Entities;

    public:
        ENUMERABLE_WRAPPER_IMPLEMENTATION(m_Entities)

        ENUMERABLE_EXTENSIONS_IMPLEMENTATION

        void UpdateLists();

        void AddNow(EntityT* entity);

        void AddNextFrame(EntityT* entity);

        template <Concepts::Enumerable EnumerableT>
        void AddRangeNow(const EnumerableT& enumerable);

        template <Concepts::Enumerable EnumerableT>
        void AddRangeNextFrame(const EnumerableT& enumerable);

        void RemoveNow(EntityT* entity);

        void RemoveNextFrame(EntityT* entity);

        void MarkUnsorted();

        void Clear();

        GETTER_NON_CONST(List<EntityT*>&, List, m_Entities)
        GETTER_NON_CONST(List<EntityT*>&, ToAdd, m_ToAdd)
        GETTER_NON_CONST(List<EntityT*>&, ToRemove, m_ToRemove)

    private:
        List<EntityT*> m_ToAdd;
        List<EntityT*> m_ToRemove;

        /// @brief Whether the @c m_Entities list is currently unsorted (and therefore needs to be sorted).
        bool_t m_Unsorted = false;

        Scene* m_Scene = nullptr;

        friend Scene; // The scene needs to be able to set m_Scene
    };

    CHECK_REQUIREMENT(Requirements::MountainEnumerableWrapper, EntityList<Entity>);
}

// Start of EntityList.inl

namespace Mountain
{
    template <Concepts::Entity EntityT>
    void EntityList<EntityT>::UpdateLists()
    {
        if (!m_ToAdd.IsEmpty())
        {
            for (EntityT* entity : m_ToAdd)
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
            for (EntityT* entity : m_ToRemove)
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
            m_Entities.Sort([](const EntityT* lhs, const EntityT* rhs) { return lhs->GetDepth() > rhs->GetDepth(); });
        }

        if (m_ToAdd.IsEmpty())
            return;

        m_ToAdd.ForEach([](EntityT* entity) { entity->Awake(); });
        m_ToAdd.Clear();
    }

    template <Concepts::Entity EntityT>
    void EntityList<EntityT>::AddNow(EntityT* entity)
    {
        m_Entities.Add(entity);
        m_Unsorted = true;
    }

    template <Concepts::Entity EntityT>
    void EntityList<EntityT>::AddNextFrame(EntityT* entity)
    {
        m_ToAdd.Add(entity);
    }

    template <Concepts::Entity EntityT>
    template <Concepts::Enumerable EnumerableT>
    void EntityList<EntityT>::AddRangeNow(const EnumerableT& enumerable)
    {
        m_Entities.AddRange(enumerable);
    }

    template <Concepts::Entity EntityT>
    template <Concepts::Enumerable EnumerableT>
    void EntityList<EntityT>::AddRangeNextFrame(const EnumerableT& enumerable)
    {
        m_ToAdd.AddRange(enumerable);
    }

    template <Concepts::Entity EntityT>
    void EntityList<EntityT>::RemoveNow(EntityT* entity)
    {
        m_Entities.Remove(entity);
    }

    template <Concepts::Entity EntityT>
    void EntityList<EntityT>::RemoveNextFrame(EntityT* entity)
    {
        m_ToAdd.Remove(entity);
        m_ToRemove.Add(entity);
    }

    template <Concepts::Entity EntityT>
    void EntityList<EntityT>::MarkUnsorted()
    {
        m_Unsorted = true;
    }

    template <Concepts::Entity EntityT>
    void EntityList<EntityT>::Clear()
    {
        m_Entities.Clear();
    }
}
