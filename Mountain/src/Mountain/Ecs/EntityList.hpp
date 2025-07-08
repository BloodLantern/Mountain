#pragma once

#include "Mountain/Core.hpp"
#include "Mountain/Containers/List.hpp"

namespace Mountain
{
    class EntityList
    {
        List<Entity*> m_Entities;

    public:
        using WrappedEnumerable = decltype(m_Entities);

        [[nodiscard]]
        WrappedEnumerable& GetEnumerable();
        [[nodiscard]]
        const WrappedEnumerable& GetEnumerable() const;

    private:
    };

    CHECK_REQUIREMENT(Requirements::MountainEnumerableWrapper, EntityList);
}
