#pragma once

#include <vector2i.hpp>

#include "collider.hpp"

namespace mountain
{
    class Grid : public Collider
    {
    public:
        Vector2i GridSize; // The size of the grid in tiles.
        Vector2 TileSize; // The size of a tile in the grid in pixels.
        bool* const* const Tiles;

        Grid(const Vector2i size, const Vector2 tileSize);
        Grid(const Vector2i size, const Vector2 tileSize, const Vector2 position);
        ~Grid();

        // Inherited via Collider
        void Draw(const Color color) const override;
        bool CheckCollision(const Vector2& point) const override;
        bool CheckCollision(const Hitbox& hitbox) const override;
        bool CheckCollision(const Circle& circle) const override;
        bool CheckCollision(const Grid& grid) const override;
        bool CheckCollision(const ColliderList& list) const override;

        inline float Left() const override { return Position.x; }
        inline float Right() const override { return Position.x + Width(); }
        inline float Top() const override { return Position.y; }
        inline float Bottom() const override { return Position.y + Height(); }
        inline float Width() const override { return GridSize.x * TileSize.x; }
        inline float Height() const override { return GridSize.y * TileSize.y; }
        inline Vector2 Size() const override { return GridSize * TileSize; }
        inline Vector2 Center() const override { return Position + Size() / 2; }
    };
}
