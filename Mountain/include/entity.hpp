#pragma once

#include <vector2.hpp>

namespace mountain
{
    class Collider;

    class Entity
    {
    public:
        Entity(const Vector2& position) : mPosition(position) {}
        virtual ~Entity() = default;

        virtual void Update(const float deltaTime) = 0;
        virtual void Draw() = 0;

        const Vector2& GetPosition() const { return mPosition; }
        void SetPosition(const Vector2& position) { mPosition = position; }
        const Collider* GetCollider() const { return mCollider; }
        void SetCollider(Collider& collider) { mCollider = &collider; }

    protected:
        Vector2 mPosition = 0;
        Collider* mCollider = nullptr;
    };
}
