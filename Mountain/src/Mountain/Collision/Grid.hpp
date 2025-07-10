#pragma once

#include "Mountain/Collision/Collider.hpp"

#include <Math/vector2i.hpp>

#include "Mountain/Containers/List.hpp"

namespace Mountain
{
    class Grid : public Collider
    {
    public:
        /// @brief The size of the grid in tiles.
        Vector2i gridSize;
        /// @brief The size of a tile in the grid in pixels.
        Vector2 tileSize;
        /// @brief The tile array, stored in [y, x] indices
        List<List<bool_t>> tiles;

        MOUNTAIN_API Grid();
        MOUNTAIN_API Grid(Vector2i size, Vector2 tileSize);
        MOUNTAIN_API Grid(Vector2i size, Vector2 tileSize, Vector2 off);

        // Inherited via Collider
        MOUNTAIN_API void RenderDebug(const Color& color) const override;
        ATTRIBUTE_NODISCARD
        MOUNTAIN_API bool_t CheckCollision(Vector2 point) const override;
        ATTRIBUTE_NODISCARD
        MOUNTAIN_API bool_t CheckCollision(const Hitbox& hitbox) const override;
        ATTRIBUTE_NODISCARD
        MOUNTAIN_API bool_t CheckCollision(const Circle& circle) const override;
        ATTRIBUTE_NODISCARD
        MOUNTAIN_API bool_t CheckCollision(const Grid& grid) const override;
        ATTRIBUTE_NODISCARD
        MOUNTAIN_API bool_t CheckCollision(const ColliderList& list) const override;

        ATTRIBUTE_NODISCARD
        MOUNTAIN_API float_t Left() const override;
        ATTRIBUTE_NODISCARD
        MOUNTAIN_API float_t Right() const override;
        ATTRIBUTE_NODISCARD
        MOUNTAIN_API float_t Top() const override;
        ATTRIBUTE_NODISCARD
        MOUNTAIN_API float_t Bottom() const override;

        ATTRIBUTE_NODISCARD
        MOUNTAIN_API float AbsoluteLeft() const override;
        ATTRIBUTE_NODISCARD
        MOUNTAIN_API float AbsoluteRight() const override;
        ATTRIBUTE_NODISCARD
        MOUNTAIN_API float AbsoluteTop() const override;
        ATTRIBUTE_NODISCARD
        MOUNTAIN_API float AbsoluteBottom() const override;

        ATTRIBUTE_NODISCARD
        MOUNTAIN_API float Width() const override;
        ATTRIBUTE_NODISCARD
        MOUNTAIN_API float Height() const override;
        ATTRIBUTE_NODISCARD
        MOUNTAIN_API Vector2 Size() const override;

        ATTRIBUTE_NODISCARD
        MOUNTAIN_API List<bool_t>& operator[](size_t y);
        ATTRIBUTE_NODISCARD
        MOUNTAIN_API const List<bool_t>& operator[](size_t y) const;

        ATTRIBUTE_NODISCARD
        MOUNTAIN_API bool_t At(size_t y, size_t x) const;
        ATTRIBUTE_NODISCARD
        MOUNTAIN_API bool_t At(Vector2i tilePosition) const;

    private:
        void ResizeGrid();
    };
}
