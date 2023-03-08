#include "collide.hpp"

std::pair<bool, Vector2> mountain::Collide::LinesIntersect(const Vector2 &p1, const Vector2 &p2, const Vector2 &p3, const Vector2 &p4)
{
    const float rxs = Vector2::CrossProduct(p2, p4);

    // Lines are collinear or parallel
    if (rxs == 0)
        return std::pair<bool, Vector2>(false, Vector2(0));

    const Vector2 p3mp1 = p3 - p1;
    const float p3mp1xp4 = Vector2::CrossProduct(p3mp1, p4);
    const float p3mp1xp2 = Vector2::CrossProduct(p3mp1, p2);

    const float t = p3mp1xp4 / rxs;
    const float u = p3mp1xp2 / rxs;

    // Lines intersect
    if (t >= 0 && t <= 1 && u >= 0 && u <= 1)
        return std::pair<bool, Vector2>(true, p1 + t * p2);

    // Lines are not collinear or parallel and do not intersect
    return std::pair<bool, Vector2>(false, Vector2(0));

}
void mountain::Collide::CheckCollisions(const std::vector<const Collider *> &colliders, ColliderHitCallback callback)
{
    for (std::vector<const Collider*>::const_iterator it = colliders.begin(); it != colliders.end(); it++)
    {
        const Collider* collider = *it;
        if (collider)
            for (std::vector<const Collider*>::const_iterator it2 = colliders.begin(); it2 != colliders.end(); it2++)
            {
                const Collider* other = *it2;

                if (other == collider || !other)
                    continue;

                if (CheckCollision(*collider, *other))
                    callback(*collider->GetEntity(), *other->GetEntity());
            }
    }
}
