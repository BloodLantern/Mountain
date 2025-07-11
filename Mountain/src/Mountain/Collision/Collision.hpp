#pragma once

#include <Math/vector2.hpp>

#include "Mountain/Core.hpp"

namespace Mountain::Collision
{
    /// @brief Check if the lines (p1, p1 + p2) and (p3, p3 + p4) collide.
    /// @return A std::pair where the first element is true if the lines intersect,
    ///         and the second element is the position of the collision.
    MOUNTAIN_API std::pair<bool, Vector2> LinesIntersect(Vector2 p1, Vector2 p2, Vector2 p3, Vector2 p4);
}
