#pragma once

#include "Mountain/core.hpp"

#include <vector>

#include "Mountain/collision/collider.hpp"
#include "Mountain/scene/entity.hpp"

BEGIN_MOUNTAIN

class MOUNTAIN_API Collide
{
    STATIC_CLASS(Collide)
    
public:
    /// @brief Check if the lines (p1, p1 + p2) and (p3, p3 + p4) collide.
    /// @return A std::pair where the first element is true if the lines intersect,
    ///         and the second element is the position of the collision.
    static std::pair<bool, Vector2> LinesIntersect(Vector2 p1, Vector2 p2, Vector2 p3, Vector2 p4);
};

END_MOUNTAIN
