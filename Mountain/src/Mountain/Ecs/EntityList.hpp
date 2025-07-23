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
        ATTRIBUTE_NODISCARD bool_t All(const ::Mountain::Predicate<EnumeratedType>& predicate) const { return ::Mountain::All(*this, predicate); } ATTRIBUTE_NODISCARD bool_t Any(const ::Mountain::Predicate<EnumeratedType>& predicate) const { return ::Mountain::Any(*this, predicate); } template <typename = ::Mountain::Meta::EnableIf<::Mountain::Meta::IsIntegralOrFloating<EnumeratedType>>> ATTRIBUTE_NODISCARD float_t Average() const { return ::Mountain::Average(*this); } template <typename EnumerableT, typename = ::Mountain::Meta::EnableIf<Meta::IsSame<EnumeratedType, Meta::EnumerableType<EnumerableT>>>> ATTRIBUTE_NODISCARD List<EnumeratedType> Concat(const EnumerableT& enumerable) const { return ::Mountain::Concat(*this, enumerable); } template <typename U, typename = ::Mountain::Meta::EnableIf<::Mountain::Meta::IsEqualityComparableWith<U, EnumeratedType>>> ATTRIBUTE_NODISCARD bool_t Contains(const U& element) const { return ::Mountain::Contains(*this, element); } ATTRIBUTE_NODISCARD bool_t Contains(const ::Mountain::Predicate<EnumeratedType>& predicate) const { return ::Mountain::Contains(*this, predicate); } ATTRIBUTE_NODISCARD ::Mountain::List<EnumeratedType> FindAll(const ::Mountain::Predicate<EnumeratedType>& predicate) const { return ::Mountain::FindAll(*this, predicate); } ATTRIBUTE_NODISCARD EnumeratedType& First() { return ::Mountain::First(*this); } ATTRIBUTE_NODISCARD const EnumeratedType& First() const { return ::Mountain::First(*this); } ATTRIBUTE_NODISCARD EnumeratedType& Last() { return ::Mountain::Last(*this); } ATTRIBUTE_NODISCARD const EnumeratedType& Last() const { return ::Mountain::Last(*this); } ATTRIBUTE_NODISCARD EnumeratedType& Single() { return ::Mountain::Single(*this); } ATTRIBUTE_NODISCARD const EnumeratedType& Single() const { return ::Mountain::Single(*this); } void ForEach(const ::Mountain::Operation<EnumeratedType>& operation) { return ::Mountain::ForEach(*this, operation); } void ForEach(const ::Mountain::Operation<const EnumeratedType>& operation) const { return ::Mountain::ForEach(*this, operation); } template <typename = ::Mountain::Meta::EnableIf< ::Mountain::Meta::IsSortable<Iterator, ::Mountain::Comparer<EnumeratedType>, ::Mountain::Identity>>> void Sort() { return ::Mountain::Sort(*this); } template <typename = ::Mountain::Meta::EnableIf< ::Mountain::Meta::IsSortable<Iterator, ::Mountain::Comparer<EnumeratedType>, ::Mountain::Identity>>> void Sort(const ::Mountain::Comparer<EnumeratedType>& comparer) { return ::Mountain::Sort(*this, comparer); }

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

    CHECK_REQUIREMENT(Requirements::MountainEnumerableWrapper, EntityList);
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
