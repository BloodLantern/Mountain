#include "colliders/collide.hpp"

void mountain::Collide::CheckCollisions(const std::vector<const Collider*> &colliders, ColliderHitCallback callback)
{
    for (std::vector<const Collider*>::const_iterator it = colliders.begin(); it != colliders.end(); it++)
    {
        const Collider* collider = *it;
        for (std::vector<const Collider*>::const_iterator it2 = colliders.begin(); it2 != colliders.end(); it2++)
        {
            const Collider* other = *it2;

            if (other == collider)
                continue;

            if (CheckCollision(*collider, *other))
                callback(*collider->GetEntity(), *other->GetEntity());
        }
    }
}
