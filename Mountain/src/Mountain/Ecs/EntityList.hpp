#pragma once

#include "Mountain/Core.hpp"
#include "Mountain/Containers/EnumerableExt.hpp"
#include "Mountain/Containers/List.hpp"

namespace Mountain
{
    class Scene;

    class EntityList
    {
        /// @brief The actual list of entities. They are sorted by depth in decreasing order, i.e., higher depth first.
        List<Entity*> m_Entities;

    public:
        ENUMERABLE_WRAPPER_IMPLEMENTATION(m_Entities)
        ENUMERABLE_EXTENSIONS_IMPLEMENTATION

        MOUNTAIN_API void UpdateLists();

        MOUNTAIN_API void AddNow(Entity* entity);

        MOUNTAIN_API void AddNextFrame(Entity* entity);

        template <Concepts::Enumerable EnumerableT>
        void AddRangeNow(const EnumerableT& enumerable);

        template <Concepts::Enumerable EnumerableT>
        void AddRangeNextFrame(const EnumerableT& enumerable);

        MOUNTAIN_API void RemoveNow(Entity* entity);

        MOUNTAIN_API void RemoveNextFrame(Entity* entity);

        MOUNTAIN_API void MarkUnsorted();

    private:
        List<Entity*> m_ToAdd;
        List<Entity*> m_ToRemove;

        /// @brief Whether the @c m_Entities list is currently unsorted (and therefore needs to be sorted).
        bool_t m_Unsorted = false;

        Scene* m_Scene = nullptr;

        friend Scene; // The scene needs to be able to set m_Scene
    };

}

// Start of EntityList.inl

namespace Mountain
{
    template <Concepts::Enumerable EnumerableT>
    void EntityList::AddRangeNow(const EnumerableT& enumerable)
    {
        m_Entities.AddRange(enumerable);
    }

    template <Concepts::Enumerable EnumerableT>
    void EntityList::AddRangeNextFrame(const EnumerableT& enumerable)
    {
        m_ToAdd.AddRange(enumerable);
    }
}
