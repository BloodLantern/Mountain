#pragma once

#include "Mountain/collision/collider.hpp"

#include <Maths/vector2i.hpp>

#include "Mountain/utils/list.hpp"

namespace Mountain
{
    // TODO - Add a template type instead of bool_t

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
    [[nodiscard]]
    MOUNTAIN_API bool_t CheckCollision(Vector2 point) const override;
    [[nodiscard]]
    MOUNTAIN_API bool_t CheckCollision(const Hitbox& hitbox) const override;
    [[nodiscard]]
    MOUNTAIN_API bool_t CheckCollision(const Circle& circle) const override;
    [[nodiscard]]
    MOUNTAIN_API bool_t CheckCollision(const Grid& grid) const override;
    [[nodiscard]]
    MOUNTAIN_API bool_t CheckCollision(const ColliderList& list) const override;

        [[nodiscard]]
        MOUNTAIN_API float_t Left() const override;
        [[nodiscard]]
        MOUNTAIN_API float_t Right() const override;
        [[nodiscard]]
        MOUNTAIN_API float_t Top() const override;
        [[nodiscard]]
        MOUNTAIN_API float_t Bottom() const override;

        [[nodiscard]]
        MOUNTAIN_API float AbsoluteLeft() const override;
        [[nodiscard]]
        MOUNTAIN_API float AbsoluteRight() const override;
        [[nodiscard]]
        MOUNTAIN_API float AbsoluteTop() const override;
        [[nodiscard]]
        MOUNTAIN_API float AbsoluteBottom() const override;

        [[nodiscard]]
        MOUNTAIN_API float Width() const override;
        [[nodiscard]]
        MOUNTAIN_API float Height() const override;
        [[nodiscard]]
        MOUNTAIN_API Vector2 Size() const override;

        [[nodiscard]]
        MOUNTAIN_API List<bool_t>& operator[](size_t y);
        [[nodiscard]]
        MOUNTAIN_API const List<bool_t>& operator[](size_t y) const;

        [[nodiscard]]
        MOUNTAIN_API bool_t At(size_t y, size_t x) const;
        [[nodiscard]]
        MOUNTAIN_API bool_t At(Vector2i tilePosition) const;

    private:
        void ResizeGrid();
    };
}
