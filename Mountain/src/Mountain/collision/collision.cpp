#include "Mountain/collision/collision.hpp"

using namespace Mountain;

std::pair<bool, Vector2> Collision::LinesIntersect(const Vector2 p1, const Vector2 p2, const Vector2 p3, const Vector2 p4)
{
    const float rxs = Vector2::Cross(p2, p4);

    // Lines are collinear or parallel
    if (rxs == 0)
        return std::pair(false, Vector2{});

    const Vector2 p3Mp1 = p3 - p1;
    const float p3Mp1Xp4 = Vector2::Cross(p3Mp1, p4);
    const float p3Mp1Xp2 = Vector2::Cross(p3Mp1, p2);

    const float t = p3Mp1Xp4 / rxs;
    const float u = p3Mp1Xp2 / rxs;

    // Lines intersect
    if (t >= 0 && t <= 1 && u >= 0 && u <= 1)
        return std::pair(true, p1 + t * p2);

    // Lines are not collinear or parallel and do not intersect
    return std::pair(false, Vector2{});
}
