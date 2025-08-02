#pragma once

#include "Mountain/Core.hpp"
#include "Mountain/Ecs/EntityList.hpp"
#include "Mountain/Utils/Event.hpp"

namespace Mountain
{
    class Scene
    {
    public:
        /// @brief Event invoked at the end of the current frame only.
        /// This means that its subscriber list will get cleared on each frame.
        /// @details This event is invoked in @c AfterUpdate() and cleared afterward.
        Event<> onEndOfCurrentFrame;

        Scene() = default;
        DEFAULT_COPY_MOVE_OPERATIONS(Scene)
        DEFAULT_VIRTUAL_DESTRUCTOR(Scene)

        MOUNTAIN_API virtual void Begin();

        MOUNTAIN_API virtual void BeforeUpdate();
        MOUNTAIN_API virtual void Update();
        MOUNTAIN_API virtual void AfterUpdate();

        MOUNTAIN_API virtual void BeforeRender();
        MOUNTAIN_API virtual void Render();
        MOUNTAIN_API virtual void AfterRender();

        MOUNTAIN_API virtual void BeforeRenderDebug();
        MOUNTAIN_API virtual void RenderDebug();
        MOUNTAIN_API virtual void AfterRenderDebug();

        MOUNTAIN_API virtual void End();

        ATTRIBUTE_NODISCARD
        EntityList& GetEntities() { return m_Entities; }
        ATTRIBUTE_NODISCARD
        const EntityList& GetEntities() const { return m_Entities; }

    protected:
        EntityList m_Entities;
    };
}
